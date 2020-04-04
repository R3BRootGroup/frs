#include "FrsSciTcal2RawPosPar.h"

#include "FrsSciRawPosPar.h"
#include "FrsSciTcalData.h"

#include "R3BEventHeader.h"

#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRuntimeDb.h"
#include "TGeoManager.h"

#include "TClonesArray.h"
#include "TMath.h"
#include "TObjArray.h"
#include "TRandom.h"

#include <iostream>
#include <stdlib.h>

// *** ************************************ *** //
// *** FrsSci Pmt Right (Tcal Data)         *** //
// ***     * channel=1                      *** //
// *** ************************************ *** //
// *** FrsSci Pmt Left (Tcal Data)          *** //
// ***     * channel=2                      *** //
// *** ************************************ *** //

// FrsSciTcal2RawPosPar: Default Constructor --------------------------
FrsSciTcal2RawPosPar::FrsSciTcal2RawPosPar()
    : FairTask("FrsSciTcal2RawPosPar", 1)
    , fNumDetectors(2)
    , fNumChannels(2)
    , fNumParsPerSignal(2)
    , fMinStatistics(100)
    , fTcal(NULL)
    , fRawPosPar(NULL)
    , fOutputFile(NULL)
{
    fNumSignals=fNumDetectors*fNumChannels;
}

// FrsSciTcal2RawPosPar: Standard Constructor --------------------------
FrsSciTcal2RawPosPar::FrsSciTcal2RawPosPar(const char* name, Int_t iVerbose)
    : FairTask(name, iVerbose)
    , fNumDetectors(2)
    , fNumChannels(2)
    , fNumParsPerSignal(2)
    , fMinStatistics(100)
    , fTcal(NULL)
    , fRawPosPar(NULL)
    , fOutputFile(NULL)

{
    fNumSignals=fNumDetectors*fNumChannels;
}

// FrsSciTcal2RawPosPar: Destructor ----------------------------------------
FrsSciTcal2RawPosPar::~FrsSciTcal2RawPosPar()
{
    if (fRawPosPar)
        delete fRawPosPar;
}

// -----   Public method Init   --------------------------------------------
InitStatus FrsSciTcal2RawPosPar::Init()
{

    LOG(INFO) << "FrsSciTcal2RawPosPar::Init";

    FairRootManager* rm = FairRootManager::Instance();
    if (!rm)
    {
        return kFATAL;
    }

    // --- --------------- --- //
    // --- INPUT TCAL DATA --- //
    // --- ---------------- --- //

    // scintillator at S2 and S4
    fTcal = (TClonesArray*)rm->GetObject("FrsSciTcalData");
    if (!fTcal)
    {
        LOG(ERROR) << "FrsSciTcal2RawPosPar::Couldn't get handle on FrsSciTcalData container";
        return kFATAL;
    }

    // --- ---------------------------------------- --- //
    // --- SOF SCI SINGLE TCAL PARAMETERS CONTAINER --- //
    // --- ---------------------------------------- --- //

    FairRuntimeDb* rtdb = FairRuntimeDb::instance();
    if (!rtdb)
    {
        return kFATAL;
    }

    fRawPosPar = (FrsSciRawPosPar*)rtdb->getContainer("FrsSciRawPosPar");
    if (!fRawPosPar)
    {
        LOG(ERROR) << "FrsSciTcal2RawPosPar::Couldn't get handle on FrsSciRawPosPar container";
        return kFATAL;
    }

    // --- ---------------------- --- //
    // --- HISTOGRAMS DECLARATION --- //
    // --- ---------------------- --- //

    char name[100];
    fh_RawPosMult1 = new TH1D*[fNumDetectors];
    for (Int_t det = 0; det < fNumDetectors; det++)
    {
        sprintf(name, "PosRaw_Sci%i", det + 1);
        fh_RawPosMult1[det] = new TH1D(name, name, 40000, -20, 20);
    }

#if NUMBER_OF_DETECTORS == 2
    sprintf(name, "RawTof_from_S2_to_S4");
    fh_RawTofMult1 = new TH1D(name, name, 100000, -1000, 1000);
#endif
    return kSUCCESS;
}

// -----   Public method ReInit   --------------------------------------------
InitStatus FrsSciTcal2RawPosPar::ReInit() { return kSUCCESS; }

// -----   Public method Exec   --------------------------------------------
void FrsSciTcal2RawPosPar::Exec(Option_t* opt)
{

    // --- ------------------------------ --- //
    // --- LOOP OVER TCAL HITS FOR SofSci --- //
    // --- ------------------------------ --- //

    // nHitsSci = number of hits per event
    UInt_t nHitsSci = fTcal->GetEntries(); // can be very high especially for S2 detector
    UShort_t mult[fNumDetectors * fNumChannels];
    Double_t iRawTimeNs[fNumDetectors * fNumChannels];
    UShort_t iDet; // 0 based Det number
    UShort_t iPmt; // 0 based Pmt number

    for (UShort_t d = 0; d < fNumDetectors; d++)
    {
        for (UShort_t ch = 0; ch < fNumChannels; ch++)
        {
            mult[d * fNumChannels + ch] = 0;
            iRawTimeNs[d * fNumChannels + ch] = 0;
        }
    }

    // CALCULATE THE MULTIPLICITY FOR EACH SIGNAL
    for (UInt_t ihit = 0; ihit < nHitsSci; ihit++)
    {
        FrsSciTcalData* hitSci = (FrsSciTcalData*)fTcal->At(ihit);
        if (!hitSci)
        {
            LOG(WARNING) << "FrsSciTcal2RawPosPar::Exec() : could not get TcalHitSci";
            continue; // should not happen
        }
        iDet = hitSci->GetDetector() - 1; // get the 0 based Det number
        iPmt = hitSci->GetPmt() - 1;      // get the 0 based Pmt number
        iRawTimeNs[iDet * fNumChannels + iPmt] = hitSci->GetRawTimeNs();
        mult[iDet * fNumChannels + iPmt]++;
    } // end of for(ihit)

    // FILL THE HISTOGRAM ONLY FOR MULT=1 IN RIGHT AND MULT=1 IN LEFT
    for (UShort_t d = 0; d < fNumDetectors; d++)
    {
        // check if mult=1 at RIGHT PMT [0] and mult=1 at LEFT PMT [1]
        // ATTENTION : x increasing from left to right : TrawRIGHT-TrawLEFT
        if ((mult[d * fNumChannels] == 1) && (mult[d * fNumChannels + 1] == 1))
        {
            fh_RawPosMult1[d]->Fill(iRawTimeNs[d * fNumChannels] -
                                    iRawTimeNs[d * fNumChannels + 1]);
        }
    }
}

// ---- Public method Reset   --------------------------------------------------
void FrsSciTcal2RawPosPar::Reset() {}

void FrsSciTcal2RawPosPar::FinishEvent() {}

// ---- Public method Finish   --------------------------------------------------
void FrsSciTcal2RawPosPar::FinishTask()
{
    CalculateRawPosRawPosParams();
    fRawPosPar->printParams();
}

// ------------------------------
void FrsSciTcal2RawPosPar::CalculateRawPosRawPosParams()
{
    LOG(INFO) << "FrsSciTcal2RawPosPar: CalculateRawPosRawPosParams()";

    fRawPosPar->SetNumDetectors(fNumDetectors);
    fRawPosPar->SetNumChannels(fNumChannels);
    fRawPosPar->SetNumSignals(fNumSignals);
    fRawPosPar->SetNumParsPerSignal(fNumParsPerSignal);

    Double_t iMax;
    Int_t bin, binLimit;
    for (Int_t sig = 0; sig < fNumDetectors; sig++)
    {
        if (fh_RawPosMult1[sig]->GetEntries() > fMinStatistics)
        {
            iMax = fh_RawPosMult1[sig]->GetMaximum();
            // LOWER LIMIT
            bin = 1;
            binLimit = 1;
            while ((bin <= fh_RawPosMult1[sig]->GetNbinsX()) && (binLimit == 1))
            {
                if (fh_RawPosMult1[sig]->GetBinContent(bin) > (iMax *0.05))
                    binLimit = bin;
                bin++;
            }
            fRawPosPar->SetSignalParams(fh_RawPosMult1[sig]->GetBinLowEdge(binLimit), sig * 2);
            // HIGHER LIMIT
            bin = fh_RawPosMult1[sig]->GetNbinsX();
            binLimit = fh_RawPosMult1[sig]->GetNbinsX();
            while ((bin >= 1) && (binLimit == fh_RawPosMult1[sig]->GetNbinsX()))
            {
                if (fh_RawPosMult1[sig]->GetBinContent(bin) > (iMax *0.05))
                    binLimit = bin;
                bin--;
            }
            fRawPosPar->SetSignalParams(fh_RawPosMult1[sig]->GetBinLowEdge(binLimit), sig * 2 + 1);
        }
        fh_RawPosMult1[sig]->Write();
    }

    fRawPosPar->setChanged();
    return;
}

ClassImp(FrsSciTcal2RawPosPar)

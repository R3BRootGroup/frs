#include "FrsSciTcal2RawTofPar.h"

#include "FrsSciRawTofPar.h"
#include "FrsSciTcalData.h"

#include "R3BEventHeader.h"

#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRuntimeDb.h"
#include "TGeoManager.h"

#include "TClonesArray.h"
#include "TMath.h"
#include "TRandom.h"

#include <iostream>
#include <stdlib.h>

// *** ************************************ *** //
// *** Sci Pmt Right (Tcal Data)            *** //
// ***     * channel=1                      *** //
// *** ************************************ *** //
// *** Sci Pmt Left (Tcal Data)             *** //
// ***     * channel=2                      *** //
// *** ************************************ *** //

// FrsSciTcal2RawTofPar: Default Constructor --------------------------
FrsSciTcal2RawTofPar::FrsSciTcal2RawTofPar()
    : FairTask("FrsSciTcal2RawTofPar", 1)
    , fNumDetectors(2)
    , fNumChannels(2)
    , fFirstStaSci(1)
    , fNumSignals(1)
    , fNumParsPerSignal(2)
    , fMinStatistics(100)
    , fTcal(NULL)
    , fRawTofPar(NULL)
{
}

// FrsSciTcal2RawTofPar: Standard Constructor --------------------------
FrsSciTcal2RawTofPar::FrsSciTcal2RawTofPar(const char* name, Int_t iVerbose)
    : FairTask(name, iVerbose)
    , fNumDetectors(2)
    , fNumChannels(2)
    , fFirstStaSci(1)
    , fNumSignals(1)
    , fNumParsPerSignal(2)
    , fMinStatistics(100)
    , fTcal(NULL)
    , fRawTofPar(NULL)
{
}

// FrsSciTcal2RawTofPar: Destructor ----------------------------------------
FrsSciTcal2RawTofPar::~FrsSciTcal2RawTofPar()
{
    if (fRawTofPar)
        delete fRawTofPar;
}

// -----   Public method Init   --------------------------------------------
InitStatus FrsSciTcal2RawTofPar::Init()
{

    LOG(INFO) << "FrsSciTcal2RawTofPar::Init";

    FairRootManager* rm = FairRootManager::Instance();
    if (!rm)
    {
        return kFATAL;
    }

    // --- --------------- --- //
    // --- INPUT TCAL DATA --- //
    // --- ---------------- --- //

    fTcal = (TClonesArray*)rm->GetObject("FrsSciTcalData");
    if (!fTcal)
    {
        LOG(ERROR) << "FrsSciTcal2RawTofPar::Couldn't get handle on FrsSciTcalData container";
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

    fRawTofPar = (FrsSciRawTofPar*)rtdb->getContainer("FrsSciRawTofPar");
    if (!fRawTofPar)
    {
        LOG(ERROR) << "FrsSciTcal2RawTofPar::Couldn't get handle on FrsSciRawTofPar container";
        return kFATAL;
    }

    // --- ---------------------- --- //
    // --- HISTOGRAMS DECLARATION --- //
    // --- ---------------------- --- //

    char name[100];
    fh_RawTofMult1 = new TH1D*[fNumSignals];
    for (Int_t detstart = 0; detstart < 1; detstart++)
    {
        sprintf(name, "TofRaw_Sci%i_to_Sci%i", 20+detstart+1, 40+detstart+1);
        fh_RawTofMult1[detstart] = new TH1D(name, name, 40000, -2000, 2000);
    }

    return kSUCCESS;
}

// -----   Public method ReInit   --------------------------------------------
InitStatus FrsSciTcal2RawTofPar::ReInit() { return kSUCCESS; }

// -----   Public method Exec   --------------------------------------------
void FrsSciTcal2RawTofPar::Exec(Option_t* opt)
{

    // --- ------------------------------ --- //
    // --- LOOP OVER TCAL HITS FOR SofSci --- //
    // --- ------------------------------ --- //

    // nHitsSci = number of hits per event
    UInt_t nHitsSci = fTcal->GetEntries(); // can be very high especially for S2 detector
    UShort_t mult[fNumDetectors * fNumChannels];
    Double_t iRawTimeNs[fNumDetectors * fNumChannels];
    Double_t iTrawStart, iTrawStop;
    UShort_t iDet; // 0 based Det number
    UShort_t iPmt; // 0 based Pmt number
    UShort_t rank;

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
            LOG(WARNING) << "FrsSciTcal2RawTofPar::Exec() : could not get hitSci";
            continue; // should not happen
        }
        iDet = hitSci->GetDetector() - 1; // get the 0 based DetiMax=20 number
        iPmt = hitSci->GetPmt() - 1;      // get the 0 based Pmt number
        iRawTimeNs[iDet * fNumChannels + iPmt] = hitSci->GetRawTimeNs();
        mult[iDet * fNumChannels + iPmt]++;
    } // end of for(ihit)

    // FILL THE HISTOGRAM ONLY FOR MULT=1 IN RIGHT AND MULT=1 IN LEFT
    UShort_t dstop = fNumDetectors - 1;
    for (UShort_t dstart = 0; dstart < fNumDetectors - 1; dstart++)
    {
        // check if mult=1 at RIGHT PMT [0] and mult=1 at LEFT PMT [1]
        if ((mult[dstart * fNumChannels] == 1) && (mult[dstart * fNumChannels + 1] == 1) &&
            (mult[dstop * fNumChannels] == 1) && (mult[dstop * fNumChannels + 1] == 1))
        {
            iTrawStart = 0.5 * (iRawTimeNs[dstart * fNumChannels] +
                                iRawTimeNs[dstart * fNumChannels + 1]);
            iTrawStop = 0.5 * (iRawTimeNs[dstop * fNumChannels] +
                               iRawTimeNs[dstop * fNumChannels + 1]);
            fh_RawTofMult1[dstart]->Fill(iTrawStop - iTrawStart);
        }
    }
}

// ---- Public method Reset   --------------------------------------------------
void FrsSciTcal2RawTofPar::Reset() {}

void FrsSciTcal2RawTofPar::FinishEvent() {}

// ---- Public method Finish   --------------------------------------------------
void FrsSciTcal2RawTofPar::FinishTask()
{
    CalculateRawTofParams();
    fRawTofPar->printParams();
}

// ------------------------------
void FrsSciTcal2RawTofPar::CalculateRawTofParams()
{
    LOG(INFO) << "FrsSciTcal2RawTofPar: CalculateRawTofParams()";

    fRawTofPar->SetFirstStart(fFirstStaSci);
    fRawTofPar->SetNumSignals(fNumSignals);
    fRawTofPar->SetNumParsPerSignal(fNumParsPerSignal);

    Double_t iMax = 0;
    Int_t bin, binLimit;
    for (Int_t sig = 0; sig < fNumSignals; sig++)
    {
        iMax = fh_RawTofMult1[sig]->GetMaximum();
        if (fh_RawTofMult1[sig]->GetEntries() > fMinStatistics && iMax > 0)
        {
            // LOWER LIMIT
            bin = 1;
            binLimit = 1;
            while ((bin <= fh_RawTofMult1[sig]->GetNbinsX()) && (binLimit == 1))
            {
                if (fh_RawTofMult1[sig]->GetBinContent(bin) > (iMax *0.05))
                    binLimit = bin;
                bin++;
            }
            fRawTofPar->SetSignalParams(fh_RawTofMult1[sig]->GetBinLowEdge(binLimit), sig * 2);
            // HIGHER LIMIT
            bin = fh_RawTofMult1[sig]->GetNbinsX();
            binLimit = fh_RawTofMult1[sig]->GetNbinsX();
            while ((bin >= 1) && (binLimit == fh_RawTofMult1[sig]->GetNbinsX()))
            {
                if (fh_RawTofMult1[sig]->GetBinContent(bin) > (iMax *0.05))
                    binLimit = bin;
                bin--;
            }
            fRawTofPar->SetSignalParams(fh_RawTofMult1[sig]->GetBinLowEdge(binLimit), sig * 2 + 1);
        }
        fh_RawTofMult1[sig]->Write();
    }

    fRawTofPar->setChanged();
    return;
}

ClassImp(FrsSciTcal2RawTofPar)

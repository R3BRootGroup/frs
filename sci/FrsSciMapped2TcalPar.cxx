#include "FrsSciMapped2TcalPar.h"

#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRuntimeDb.h"
#include "FrsSciTcalPar.h"
#include "R3BEventHeader.h"
#include "TClonesArray.h"
#include "TF1.h"
#include "TGeoManager.h"
#include "TH1F.h"
#include "TMath.h"
#include "TObjArray.h"
#include "TRandom.h"
#include "VftxSciMappedData.h"

#include <iostream>
#include <stdlib.h>

// FrsSciMapped2TcalPar: Default Constructor --------------------------
FrsSciMapped2TcalPar::FrsSciMapped2TcalPar()
    : FairTask("FRSSciMapped2TcalPar", 1)
    , fNumDetectors(2)
    , fNumChannels(2)
    , fNumTcalParsPerSignal(1000)
    , fMinStatistics(0)
    , fMapped(NULL)
    , fTcalPar(NULL)
{
    fNumSignals = fNumDetectors * fNumChannels;
}

// FrsSciMapped2TcalPar: Standard Constructor --------------------------
FrsSciMapped2TcalPar::FrsSciMapped2TcalPar(const char* name, Int_t iVerbose)
    : FairTask(name, iVerbose)
    , fNumDetectors(2)
    , fNumChannels(2)
    , fNumTcalParsPerSignal(1000)
    , fMinStatistics(0)
    , fMapped(NULL)
    , fTcalPar(NULL)

{
    fNumSignals = fNumDetectors * fNumChannels;
}

// FrsSciMapped2TcalPar: Destructor ----------------------------------------
FrsSciMapped2TcalPar::~FrsSciMapped2TcalPar()
{
    if (fTcalPar)
        delete fTcalPar;
}

// -----   Public method Init   --------------------------------------------
InitStatus FrsSciMapped2TcalPar::Init()
{

    LOG(info) << "FrsSciMapped2TcalPar: Init";

    FairRootManager* rm = FairRootManager::Instance();
    if (!rm)
    {
        return kFATAL;
    }

    // --- ----------------- --- //
    // --- INPUT MAPPED DATA --- //
    // --- ----------------- --- //

    // scintillator at S2 and S4
    fMapped = (TClonesArray*)rm->GetObject("VftxSciMappedData");
    if (!fMapped)
    {
        LOG(error) << "FrsSciMapped2TcalPar::Init() Couldn't get handle on VftxSciMappedData container";
        return kFATAL;
    }

    // --- --------------------------------- --- //
    // --- SOF SCI TCAL PARAMETERS CONTAINER --- //
    // --- --------------------------------- --- //

    FairRuntimeDb* rtdb = FairRuntimeDb::instance();
    if (!rtdb)
    {
        return kFATAL;
    }

    fTcalPar = (FrsSciTcalPar*)rtdb->getContainer("FrsSciTcalPar");
    if (!fTcalPar)
    {
        LOG(error) << "FrsSciMapped2TcalPar::Init() Couldn't get handle on FrsSciTcalPar container";
        return kFATAL;
    }
    else
    {
        fTcalPar->SetNumDetectors(fNumDetectors);
        fTcalPar->SetNumChannels(fNumChannels);
        fTcalPar->SetNumSignals(fNumDetectors, fNumChannels);
        fTcalPar->SetNumTcalParsPerSignal(fNumTcalParsPerSignal);
    }

    // --- ---------------------- --- //
    // --- HISTOGRAMS DECLARATION --- //
    // --- ---------------------- --- //
    // --- In 1-based numbering:  --- //
    // --- detector 1 : at S2     --- //
    // --- detector 2 : at S4     --- //
    // --- channel 1  : Pmt R     --- //
    // --- channel 2  : Pmt L     --- //
    // --- ---------------------- --- //
    char name[100];
    fh_TimeFineBin = new TH1F*[fNumSignals];
    fh_TimeFineNs = new TH1F*[fNumSignals];
    for (Int_t det = 0; det < fNumDetectors; det++)
    {
        for (Int_t ch = 0; ch < fNumChannels; ch++)
        {
            sprintf(name, "TimeFineBin_Sci%i_Ch%i_Sig%i", det + 1, ch + 1, det * fNumChannels + ch);
            fh_TimeFineBin[det * fNumChannels + ch] =
                new TH1F(name, name, fNumTcalParsPerSignal, 0, fNumTcalParsPerSignal);
            sprintf(name, "TimeFineNs_Sci%i_Ch%i_Sig%i", det + 1, ch + 1, det * fNumChannels + ch);
            fh_TimeFineNs[det * fNumChannels + ch] =
                new TH1F(name, name, fNumTcalParsPerSignal, 0, fNumTcalParsPerSignal);
        }
    }

    return kSUCCESS;
}

// -----   Public method ReInit   --------------------------------------------
InitStatus FrsSciMapped2TcalPar::ReInit() { return kSUCCESS; }

// -----   Public method Exec   --------------------------------------------
void FrsSciMapped2TcalPar::Exec(Option_t*)
{

    // --- -------------------------------- --- //
    // --- LOOP OVER MAPPED HITS FOR SofSci --- //
    // --- -------------------------------- --- //

    // nHitsSci = number of hits per event
    // for the scintillator this number of hits can be very large especially for the detector at S2
    UInt_t nHitsSci = fMapped->GetEntries(); // can be very high especially for S2 detector
    UInt_t iSignalSci;
    for (UInt_t ihit = 0; ihit < nHitsSci; ihit++)
    {
        VftxSciMappedData* hitSci = (VftxSciMappedData*)fMapped->At(ihit);
        if (!hitSci)
        {
            LOG(warn) << "FrsSciMapped2TcalPar::Exec() : could not get hitSci";
            continue; // should not happen
        }

        // *** ******************************************* *** //
        // ***         Numbers of det and channel          *** //
        // ***   in Mapped and TcalPar Data are 1-based    *** //
        // *** ******************************************* *** //
        // *** SofSci at S2, Pmt Right (Mapped Data)       *** //
        // ***     * det=1                                 *** //
        // ***     * channel=1                             *** //
        // *** SofSci at S2, Pmt Right (Tcal Data)         *** //
        // ***     * det=1                                 *** //
        // ***     * channel=1                             *** //
        // ***     * signal=0                              *** //
        // *** ******************************************* *** //
        // *** SofSci at S2, Pmt Left (Mapped Data)        *** //
        // ***     * det=1                                 *** //
        // ***     * channel=2                             *** //
        // *** SofSci at S2, Pmt Left (Tcal Data)          *** //
        // ***     * det=1                                 *** //
        // ***     * channel=2                             *** //
        // ***     * signal=1                              *** //
        // *** ******************************************* *** //
        // *** SofSci at S4, Pmt Right (Mapped Data)       *** //
        // ***     * det=2                                 *** //
        // ***     * channel=1                             *** //
        // *** SofSci at S4, Pmt Right(Tcal Data)          *** //
        // ***     * det=2                                 *** //
        // ***     * channel=1                             *** //
        // ***     * signal=3                              *** //
        // *** ******************************************* *** //
        // *** SofSci at S4, Pmt Left (Mapped Data)        *** //
        // ***     * det=2                                 *** //
        // ***     * channel=2                             *** //
        // *** SofSci at S4, Pmt Left (Tcal Data)          *** //
        // ***     * det=2                                 *** //
        // ***     * channel=2                             *** //
        // ***     * signal=4                              *** //
        // *** ******************************************* *** //
        iSignalSci = (hitSci->GetDetector() - 1) * fNumChannels + (hitSci->GetPmt() - 1);
        if ((0 <= iSignalSci) && (iSignalSci <= fNumSignals))
            fh_TimeFineBin[iSignalSci]->Fill(hitSci->GetTimeFine());
        else
            LOG(error) << "FrsSciMapped2TcalPar::Exec() Number of signals out of range: " << iSignalSci
                       << " instead of [0," << fNumSignals << "]: det=" << hitSci->GetDetector()
                       << ",  fNumChannels = " << fNumChannels << ",  pmt = " << hitSci->GetPmt();

    } // end of loop over the number of hits per event in MappedSci
}

// ---- Public method Reset   --------------------------------------------------
void FrsSciMapped2TcalPar::Reset() {}

void FrsSciMapped2TcalPar::FinishEvent() {}

// ---- Public method Finish   --------------------------------------------------
void FrsSciMapped2TcalPar::FinishTask()
{
    CalculateVftxTcalParams();
    fTcalPar->printParams();
}

//------------------
void FrsSciMapped2TcalPar::CalculateVftxTcalParams()
{
    LOG(info) << "FrsSciMapped2TcalPar: CalculateVftxTcalParams()";

    UInt_t IntegralTot;
    UInt_t IntegralPartial;
    Double_t Bin2Ns[fNumTcalParsPerSignal];

    for (Int_t sig = 0; sig < fNumSignals; sig++)
    {
        if (fh_TimeFineBin[sig]->GetEntries() > fMinStatistics)
        {
            IntegralTot = fh_TimeFineBin[sig]->Integral();
            IntegralPartial = 0;
            for (Int_t bin = 0; bin < fNumTcalParsPerSignal; bin++)
            {
                IntegralPartial += fh_TimeFineBin[sig]->GetBinContent(bin + 1);
                Bin2Ns[bin] = 5. * ((Double_t)IntegralPartial) / (Double_t)IntegralTot;
                fh_TimeFineNs[sig]->SetBinContent(bin + 1, Bin2Ns[bin]);
                fTcalPar->SetSignalTcalParams(Bin2Ns[bin], sig * fNumTcalParsPerSignal + bin);
            }
        }
        fh_TimeFineNs[sig]->Write(); // empty histo if stat <fMinStatistics
        fh_TimeFineBin[sig]->Write();
    }
    fTcalPar->setChanged();
    return;
}

ClassImp(FrsSciMapped2TcalPar)

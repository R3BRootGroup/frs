// -------------------------------------------------------------------------
// -----              FRSMusicMapped2CalPar source file                -----
// -----            Created 29/05/18  by J.L. Rodriguez-Sanchez        -----
// -------------------------------------------------------------------------

#include "FRSMusicMapped2CalPar.h"

#include "FRSMusicCalPar.h"
#include "FRSMusicMappedData.h"
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRuntimeDb.h"
#include "R3BEventHeader.h"
#include "TClonesArray.h"
#include "TF1.h"
#include "TGeoManager.h"
#include "TGeoMatrix.h"
#include "TH1F.h"
#include "TMath.h"
#include "TObjArray.h"
#include "TRandom.h"
#include "TVector3.h"

#include <iostream>
#include <stdlib.h>

using namespace std;

// FRSMusicMapped2CalPar: Default Constructor --------------------------
FRSMusicMapped2CalPar::FRSMusicMapped2CalPar()
    : FairTask("FRS Music Pedestal Finder ", 1)
    , fAnode_Par(NULL)
    , fMusicMappedDataCA(NULL)
    , fNumDets(0)
    , fNumAnodes(8)
    , fMaxSigma(200)
    , fMinStatistics(0)
    , fMapHistos_left(0)
    , fMapHistos_right(0)
    , fMapHistos_bins(0)
    , fSigma(0)
    , fMean(0)
    , fOutputFile(NULL)
{}

// FRSMusicMapped2CalPar: Standard Constructor --------------------------
FRSMusicMapped2CalPar::FRSMusicMapped2CalPar(const char* name, Int_t iVerbose)
    : FairTask(name, iVerbose)
    , fAnode_Par(NULL)
    , fMusicMappedDataCA(NULL)
    , fNumDets(0)
    , fNumAnodes(8)
    , fMaxSigma(200)
    , fMinStatistics(0)
    , fMapHistos_left(0)
    , fMapHistos_right(0)
    , fMapHistos_bins(0)
    , fSigma(0)
    , fMean(0)
    , fOutputFile(NULL)
{}

// FRSMusicMapped2CalPar: Destructor ----------------------------------------
FRSMusicMapped2CalPar::~FRSMusicMapped2CalPar()
{

    LOG(INFO) << "FRSMusicMapped2CalPar: Delete instance";
    if (fMusicMappedDataCA)
        delete fMusicMappedDataCA;
}

// -----   Public method Init   --------------------------------------------
InitStatus FRSMusicMapped2CalPar::Init()
{
    LOG(INFO) << "FRSMusicMapped2CalPar: Init";

    char name[100];

    fh_Map_energy_anode = new TH1F*[fNumAnodes * fNumDets];
    for (Int_t i = 0; i < fNumAnodes * fNumDets; i++) {
        sprintf(name, "fh_Map_energy_anode_%i", i + 1);
        fh_Map_energy_anode[i] = new TH1F(name, name, fMapHistos_bins, fMapHistos_left, fMapHistos_right);
    }

    FairRootManager* rootManager = FairRootManager::Instance();
    if (!rootManager) {
        return kFATAL;
    }

    fMusicMappedDataCA = (TClonesArray*)rootManager->GetObject("FRSMusicMappedData");
    if (!fMusicMappedDataCA) {
        return kFATAL;
    }

    FairRuntimeDb* rtdb = FairRuntimeDb::instance();
    if (!rtdb) {
        return kFATAL;
    }

    fAnode_Par = (FRSMusicCalPar*)rtdb->getContainer("frsmusicCalPar");
    if (!fAnode_Par) {
        LOG(ERROR) << "FRSMusicMapped2CalPar::Init() Couldn't get handle on frsmusicCalPar container";
        return kFATAL;
    }

    return kSUCCESS;
}

// -----   Public method ReInit   --------------------------------------------
InitStatus FRSMusicMapped2CalPar::ReInit()
{

    // MOVE PAR SETTINGS IN INIT TO SETPARCONTAINERS AND CALL ALSO IT HERE
    // SetParContainers();

    return kSUCCESS;
}

// -----   Public method Exec   --------------------------------------------
void FRSMusicMapped2CalPar::Exec(Option_t* opt)
{

    Int_t nHits = fMusicMappedDataCA->GetEntries();
    if (!nHits)
        return;

    FRSMusicMappedData* MapHit;
    Int_t detId, anodeId;

    for (Int_t i = 0; i < nHits; i++) {
        MapHit = (FRSMusicMappedData*)(fMusicMappedDataCA->At(i));
        detId = MapHit->GetDetectorId();
        anodeId = MapHit->GetAnodeId();

        // Fill Histos
        fh_Map_energy_anode[anodeId + fNumAnodes * detId]->Fill(MapHit->GetEnergy());
    }
}

// ---- Public method Reset   --------------------------------------------------
void FRSMusicMapped2CalPar::Reset() {}

void FRSMusicMapped2CalPar::FinishEvent() {}

// ---- Public method Finish   --------------------------------------------------
void FRSMusicMapped2CalPar::FinishTask()
{

    SearchPedestals();
    // fAnode_Par->printParams();
}

//------------------
void FRSMusicMapped2CalPar::SearchPedestals()
{

    LOG(INFO) << "FRSMusicMapped2CalPar: Search pedestals";

    Int_t numPars = 3;   // by default number of parameters=3

    fAnode_Par->SetNumDets(fNumDets);
    fAnode_Par->SetNumAnodes(fNumAnodes);
    fAnode_Par->GetAnodeCalParams()->Set(numPars * fNumAnodes * fNumDets);

    for (Int_t d = 0; d < fNumDets; d++) {
        for (Int_t i = 0; i < fNumAnodes; i++) {

            if (fh_Map_energy_anode[i + d * fNumAnodes]->GetEntries() > fMinStatistics) {

                TF1* f1 = new TF1("f1", "gaus", fMapHistos_left, fMapHistos_right);
                f1->SetParameter(1, 100.);
                f1->SetParameter(2, 2.);

                fh_Map_energy_anode[i + d * fNumAnodes]->Fit("f1", "RQ0");

                // Fill container:
                fAnode_Par->SetAnodeCalParams(f1->GetParameter(0), numPars * i + d * numPars * fNumAnodes);
                if (f1->GetParameter(2) < fMaxSigma) {
                    fAnode_Par->SetAnodeCalParams(f1->GetParameter(1), numPars * i + d * numPars * fNumAnodes + 1);
                } else {
                    fAnode_Par->SetAnodeCalParams(-1, numPars * i + d * fNumAnodes + 1);   // dead anode
                }
                fAnode_Par->SetAnodeCalParams(f1->GetParameter(2), numPars * i + d * numPars * fNumAnodes + 2);
            } else {
                fAnode_Par->SetAnodeCalParams(-1, numPars * i + d * numPars * fNumAnodes + 1);   // dead anode
                fAnode_Par->SetAnodeCalParams(0, numPars * i + d * numPars * fNumAnodes + 2);
                LOG(WARNING) << "Histogram NO Fitted, detector: " << d + 1 << ", anode: " << i + 1;
            }
        }
    }

    fAnode_Par->setChanged();
    return;
}

ClassImp(FRSMusicMapped2CalPar)

// -------------------------------------------------------------------------
// -----               FRSMusicCal2HitPar source file                  -----
// -----             Created 29/05/18  by J.L. Rodriguez-Sanchez       -----
// -------------------------------------------------------------------------
#include "FRSMusicCal2HitPar.h"

#include "FRSMusicCalData.h"
#include "FRSMusicHitPar.h"
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRuntimeDb.h"
#include "R3BEventHeader.h"
#include "TClonesArray.h"
#include "TF1.h"
#include "TGeoManager.h"
#include "TGeoMatrix.h"
#include "TGraph.h"
#include "TH1F.h"
#include "TMath.h"
#include "TObjArray.h"
#include "TRandom.h"
#include "TSpectrum.h"
#include "TVector3.h"

#include <iostream>
#include <stdlib.h>

using namespace std;

// FRSMusicCal2HitPar: Default Constructor --------------------------
FRSMusicCal2HitPar::FRSMusicCal2HitPar()
    : FairTask("FRS Music Atomic number Finder ", 1)
    , fDet_Par(NULL)
    , fMusicCalDataCA(NULL)
    , fNumDets(5)
    , fMaxZ(100)
    , fMaxSigma(200)
    , fMinStatistics(100)
    , fMapHistos_left(0)
    , fMapHistos_right(100)
    , fMapHistos_bins(500)
    , fSigma(0)
    , fMean(0)
    , fOutputFile(NULL)
{
}

// FRSMusicCal2HitPar: Standard Constructor --------------------------
FRSMusicCal2HitPar::FRSMusicCal2HitPar(const char* name, Int_t iVerbose)
    : FairTask(name, iVerbose)
    , fDet_Par(NULL)
    , fMusicCalDataCA(NULL)
    , fNumDets(5)
    , fMaxZ(100)
    , fMaxSigma(200)
    , fMinStatistics(100)
    , fMapHistos_left(0)
    , fMapHistos_right(100)
    , fMapHistos_bins(500)
    , fSigma(0)
    , fMean(0)
    , fOutputFile(NULL)
{
}

// FRSMusicCal2HitPar: Destructor ----------------------------------------
FRSMusicCal2HitPar::~FRSMusicCal2HitPar()
{
    LOG(info) << "FRSMusicCal2HitPar: Delete instance";
    if (fMusicCalDataCA)
        delete fMusicCalDataCA;
}

// -----   Public method Init   --------------------------------------------
InitStatus FRSMusicCal2HitPar::Init()
{

    LOG(info) << "FRSMusicCal2HitPar: Init";

    char name[100];

    fh_Cal_energy_det = new TH1F*[fNumDets];
    for (Int_t i = 0; i < fNumDets; i++)
    {
        sprintf(name, "fh_Map_energy_det_%i", i + 1);
        fh_Cal_energy_det[i] = new TH1F(name, name, fMapHistos_bins, fMapHistos_left, fMapHistos_right);
    }

    FairRootManager* rootManager = FairRootManager::Instance();
    if (!rootManager)
    {
        return kFATAL;
    }

    fMusicCalDataCA = (TClonesArray*)rootManager->GetObject("FRSMusicCalData");
    if (!fMusicCalDataCA)
    {
        return kFATAL;
    }

    FairRuntimeDb* rtdb = FairRuntimeDb::instance();
    if (!rtdb)
    {
        return kFATAL;
    }

    fDet_Par = (FRSMusicHitPar*)rtdb->getContainer("frsmusicHitPar");
    if (!fDet_Par)
    {
        LOG(error) << "FRSMusicCal2HitPar::Init() Couldn't get handle on frsmusicHitPar container";
        return kFATAL;
    }

    return kSUCCESS;
}

// -----   Public method ReInit   --------------------------------------------
InitStatus FRSMusicCal2HitPar::ReInit()
{

    // MOVE PAR SETTINGS IN INIT TO SETPARCONTAINERS AND CALL ALSO IT HERE
    // SetParContainers();

    return kSUCCESS;
}

// -----   Public method Exec   --------------------------------------------
void FRSMusicCal2HitPar::Exec(Option_t* opt)
{

    Int_t nHits = fMusicCalDataCA->GetEntries();
    if (!nHits)
        return;

    FRSMusicCalData* CalDat;
    Int_t detId, anodeId;
    Double_t energyperanode[5][8]; // max 5 detectors and 8 anodes
    Int_t nbdet = 0;

    for (Int_t i = 0; i < 5; i++)
        for (Int_t j = 0; j < 8; j++)
            energyperanode[i][j] = 0;

    for (Int_t i = 0; i < nHits; i++)
    {
        CalDat = (FRSMusicCalData*)(fMusicCalDataCA->At(i));
        detId = CalDat->GetDetectorId();
        anodeId = CalDat->GetAnodeId();

        energyperanode[detId][anodeId] = CalDat->GetEnergy();
        nbdet = detId;
    }

    /* calculate truncated dE from 8 anodes, Munich MUSIC */
    for (Int_t i = 0; i <= nbdet; i++)
    {

        Float_t r1 = sqrt(energyperanode[i][0] * energyperanode[i][1]);
        Float_t r2 = sqrt(energyperanode[i][2] * energyperanode[i][3]);
        Float_t r3 = sqrt(energyperanode[i][4] * energyperanode[i][5]);
        Float_t r4 = sqrt(energyperanode[i][6] * energyperanode[i][7]);

        if ((r1 > 0) && (r2 > 0) && (r3 > 0) && (r4 > 0))
        {
            // Fill Histos
            Double_t charge = sqrt(sqrt(sqrt(r1 * r2) * sqrt(r3 * r4)));
            if (charge > 0.)
                fh_Cal_energy_det[i]->Fill(charge);
            // std::cout << i << " z = " << charge << std::endl;
        }
    }
}

// ---- Public method Reset   --------------------------------------------------
void FRSMusicCal2HitPar::Reset() {}

void FRSMusicCal2HitPar::FinishEvent() {}

// ---- Public method Finish   --------------------------------------------------
void FRSMusicCal2HitPar::FinishTask()
{

    SearchZ();
    fDet_Par->printParams();

    for (Int_t i = 0; i < fNumDets; i++)
        fh_Cal_energy_det[i]->Write();
}

//------------------
void FRSMusicCal2HitPar::SearchZ()
{

    LOG(info) << "FRSMusicCal2HitPar: Search atomic numbers (Z)";

    Int_t numPars = 2; // by default number of parameters=3

    fDet_Par->SetNumDets(fNumDets);
    fDet_Par->GetDetectorHitParams()->Set(numPars * fNumDets);

    int fNumPeaks = 8;
    TSpectrum* ss = new TSpectrum(fNumPeaks);

    for (Int_t i = 0; i < fNumDets; i++)
    {

        Int_t nfound = 0;

        if (fh_Cal_energy_det[i]->GetEntries() > fMinStatistics)
        {
            // Sigma=1 is better than other values!
            nfound = ss->Search(fh_Cal_energy_det[i], 1, "", 0.1);

            Int_t idx[nfound];
            Int_t idy[nfound];

            Double_t* xpeaks = ss->GetPositionX();
            // Double_t *ypeaks = ss->GetPositionY();
            TMath::Sort(nfound, xpeaks, idx, kTRUE);
            // TMath::Sort(nfound, ypeaks, idy, kTRUE);

            // Calibrated Spectrum
            Double_t X[nfound];
            Double_t Y[nfound];

            if (nfound < 2)
                LOG(error) << "FRSMusicCal2HitPar::SearchZ() Couldn't get the sufficient parameters:" << nfound << "<2";

            nfound = TMath::Min(nfound, fNumPeaks);

            for (Int_t j = 0; j < nfound; j++)
            {
                // if(ypeaks[idy[j]]>5.){
                X[j] = xpeaks[idx[j]];
                Y[j] = fMaxZ - j;
                // }
                // std::cout << X[j] << " " << Y[j] << std::endl;
            }

            // X[nfound]=0.;
            // Y[nfound]=0.;

            TF1* f1 = new TF1("f1", "[0]+[1]*x", fMapHistos_left, fMapHistos_right);
            TGraph* graph = new TGraph(nfound, X, Y);
            graph->Fit("f1", "QR"); // Quiet mode (minimum printing)

            if (nfound > 1)
            {
                for (Int_t h = 0; h < numPars; h++)
                    fDet_Par->SetDetectorHitParams(f1->GetParameter(h), numPars * i + h);
            }
            else
            {
                fDet_Par->SetDetectorHitParams(0, numPars * i);
                fDet_Par->SetDetectorHitParams(1, numPars * i + 1);
                LOG(info) << "FRSMusicCal2HitPar::SearchZ() default parameters: a0=0 and a1=1";
            }
        }
    }

    delete ss;
    fDet_Par->setChanged();
    return;
}

ClassImp(FRSMusicCal2HitPar)

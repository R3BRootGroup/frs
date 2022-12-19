// -------------------------------------------------------------------------
// -----         R3BFrsHit2AnaS4Par source file                        -----
// -----             Created 29/07/18  by J.L. Rodriguez-Sanchez       -----
// -------------------------------------------------------------------------
#include "R3BFrsHit2AnaS4Par.h"

#include "FRSMusicHitData.h"
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRuntimeDb.h"
#include "R3BEventHeader.h"
#include "R3BFrsAnaPar.h"
#include "R3BFrsMappedData.h"
#include "R3BTpcHitData.h"
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

Double_t const c = 299792458.0;     // Light velocity
Double_t const e = 1.60217662e-19;  // Electron charge
Double_t const u = 1.660538921e-27; // Atomic mass unit

using namespace std;

// R3BFrsHit2AnaS4Par: Default Constructor --------------------------
R3BFrsHit2AnaS4Par::R3BFrsHit2AnaS4Par()
    : FairTask("FRS analysis S2-S4", 1)
    , fCutZ(0)
    , fNb(0)
    , fMagS2S4(0)
    , fDispS2S4(0)
    , fPathS2S4(0)
    , fTOFS2S4(0)
    , fDisTpcS2(0)
    , fDisTpcS4(0)
    , fPosFocalS2(0)
    , fPosFocalS4(0)
    , fNbRhos(4)
    , fNbBfiels(4)
    , fRhos(NULL)
    , fBfields(NULL)
    , fFrsMappedDataCA(NULL)
    , fTpcHitDataCA(NULL)
    , fMusicHitDataCA(NULL)
    , fFrs_Par(NULL)
{
}

// R3BFrsHit2AnaS4Par: Standard Constructor --------------------------
R3BFrsHit2AnaS4Par::R3BFrsHit2AnaS4Par(const char* name, Int_t iVerbose)
    : FairTask(name, iVerbose)
    , fCutZ(0)
    , fNb(0)
    , fMagS2S4(0)
    , fDispS2S4(0)
    , fPathS2S4(0)
    , fTOFS2S4(0)
    , fDisTpcS2(0)
    , fDisTpcS4(0)
    , fPosFocalS2(0)
    , fPosFocalS4(0)
    , fNbRhos(4)
    , fNbBfiels(4)
    , fRhos(NULL)
    , fBfields(NULL)
    , fFrsMappedDataCA(NULL)
    , fTpcHitDataCA(NULL)
    , fMusicHitDataCA(NULL)
    , fFrs_Par(NULL)
{
}

// R3BFrsHit2AnaS4Par: Destructor ----------------------------------------
R3BFrsHit2AnaS4Par::~R3BFrsHit2AnaS4Par() {}

// -----   Public method Init   --------------------------------------------
InitStatus R3BFrsHit2AnaS4Par::Init()
{

    LOG(info) << "R3BFrsHit2AnaS4Par: Init";

    frho_S0_S2 = 0.5 * (fRhos->GetAt(0) + fRhos->GetAt(1));
    fBfield_S0_S2 = 0.5 * (fBfields->GetAt(0) + fBfields->GetAt(1));
    frho_S2_S4 = 0.5 * (fRhos->GetAt(2) + fRhos->GetAt(3));
    fBfield_S2_S4 = 0.5 * (fBfields->GetAt(2) + fBfields->GetAt(3));

    LOG(info) << "R3BFrsHit2AnaS4Par: Rho (S0-S2): " << frho_S0_S2;
    LOG(info) << "R3BFrsHit2AnaS4Par: B (S0-S2): " << fBfield_S0_S2;
    LOG(info) << "R3BFrsHit2AnaS4Par: Rho (S2-S4): " << frho_S2_S4;
    LOG(info) << "R3BFrsHit2AnaS4Par: B (S2-S4): " << fBfield_S2_S4;
    LOG(info) << "R3BFrsHit2AnaS4Par: Corrections for Z = " << fCutZ;

    fh_anglevsAq = new TH2F("hh", "hh", 1000, -10., 10., 1000, 0., 5.);
    graph = new TGraph(1000);
    h_Profile = new TProfile("h_Profile", "AoQ vs angle S2-S4 Profile", 1000, -5, 5, 0., 5.);

    FairRootManager* rootManager = FairRootManager::Instance();
    if (!rootManager)
    {
        return kFATAL;
    }

    fFrsMappedDataCA = (TClonesArray*)rootManager->GetObject("FrsMappedData");
    if (!fFrsMappedDataCA)
    {
        return kFATAL;
    }

    fTpcHitDataCA = (TClonesArray*)rootManager->GetObject("TpcHitData");
    if (!fTpcHitDataCA)
    {
        return kFATAL;
    }

    fMusicHitDataCA = (TClonesArray*)rootManager->GetObject("FRSMusicHitData");
    if (!fMusicHitDataCA)
    {
        return kFATAL;
    }

    FairRuntimeDb* rtdb = FairRuntimeDb::instance();
    if (!rtdb)
    {
        return kFATAL;
    }

    fFrs_Par = (R3BFrsAnaPar*)rtdb->getContainer("frsAnaPar");
    if (!fFrs_Par)
    {
        LOG(error) << "R3BFrsHit2AnaS4Par::Init() Couldn't get handle on frsAnaPar container";
        return kFATAL;
    }

    return kSUCCESS;
}

// -----   Public method ReInit   --------------------------------------------
InitStatus R3BFrsHit2AnaS4Par::ReInit()
{

    // MOVE PAR SETTINGS IN INIT TO SETPARCONTAINERS AND CALL ALSO IT HERE
    // SetParContainers();

    return kSUCCESS;
}

// -----   Public method Exec   --------------------------------------------
void R3BFrsHit2AnaS4Par::Exec(Option_t* opt)
{

    Double_t fZ = 0., fAq = 0.;

    Int_t nHitFrs = fFrsMappedDataCA->GetEntries();
    Int_t nHitMusic = fMusicHitDataCA->GetEntries();
    Int_t nHitTpc = fTpcHitDataCA->GetEntries();
    // LOG(info) << nHitMusic << " " << nHitTpc ;
    if (!nHitMusic || !nHitFrs || nHitTpc < 4)
        return; // FIXME:include here warn!

    R3BFrsMappedData** MapFrs = new R3BFrsMappedData*[nHitFrs];
    FRSMusicHitData** HitMusic = new FRSMusicHitData*[nHitMusic];
    R3BTpcHitData** HitTpc = new R3BTpcHitData*[nHitTpc];

    // Z from musics ------------------------------------
    Double_t countz = 0;
    for (Int_t i = 0; i < nHitMusic; i++)
    {
        HitMusic[i] = (FRSMusicHitData*)(fMusicHitDataCA->At(i));
        if (HitMusic[i]->GetZ() > 1)
        {
            fZ = fZ + HitMusic[i]->GetZ();
            countz++;
        }
    }
    if (countz > 0)
    {
        fZ = fZ / countz;
    }
    else
    {
        fZ = 0.;
    }

    // Positions from TPCs ------------------------------
    Double_t tpc_x[4];
    Int_t detID = 0;
    for (Int_t i = 0; i < nHitTpc; i++)
    {
        HitTpc[i] = (R3BTpcHitData*)(fTpcHitDataCA->At(i));
        detID = HitTpc[i]->GetDetectorId();
        tpc_x[detID] = HitTpc[i]->GetX();
    }

    Int_t SCI24_TofRR = 0.;
    Int_t SCI24_TofLL = 0.;

    for (Int_t i = 0; i < nHitFrs; i++)
    {
        MapFrs[i] = (R3BFrsMappedData*)(fFrsMappedDataCA->At(i));
        SCI24_TofRR = MapFrs[i]->GetSCI41RT();
        SCI24_TofLL = MapFrs[i]->GetSCI41LT();
        // LOG(info) << SCI24_TofRR << " " << SCI24_TofLL ;
    }

    // FOCAL POSITION S2
    double angle_S2_mrad = (tpc_x[1] - tpc_x[0]) / fDisTpcS2 * 1000.;
    double x_position_focal_S2 = (tpc_x[1] + fPosFocalS2 * tan(angle_S2_mrad / 1000.));

    // FOCAL POSITION S4
    double angle_S4_mrad = (tpc_x[3] - tpc_x[2]) / fDisTpcS4 * 1000.;
    double x_position_focal_S4 = tpc_x[2] + fPosFocalS4 * tan(angle_S4_mrad / 1000.);

    // Velocity S2-S4
    double TAC_CAL_SC24_LL = -0.01045;
    double TAC_CAL_SC24_RR = -0.01095;
    double ToF_star_S2_S4 = 0.5 * (TAC_CAL_SC24_LL * SCI24_TofLL + TAC_CAL_SC24_RR * SCI24_TofRR);
    double Beta_S2_S4 = ((fPathS2S4 / (fTOFS2S4 + ToF_star_S2_S4)) * pow(10., 7)) / c;
    double Gamma_S2_S4 = 1. / (sqrt(1. - (Beta_S2_S4) * (Beta_S2_S4)));

    // Brho and A/q
    double Brho_S4 = fBfield_S2_S4 * frho_S2_S4 *
                     (1. - (((x_position_focal_S4 / 1000.) - fMagS2S4 * (x_position_focal_S2 / 1000.)) / fDispS2S4));
    fAq = (Brho_S4 * e) / (Gamma_S2_S4 * Beta_S2_S4 * c * u);

    // Fill histograms for calibrations
    if (fZ > fCutZ - 0.5 && fZ < fCutZ + 0.5)
    {
        fh_anglevsAq->Fill(angle_S4_mrad, fAq);
        graph->SetPoint(fNb, angle_S4_mrad, fAq);
        fNb++;
    }

    if (HitMusic)
        delete HitMusic;
    if (HitTpc)
        delete HitTpc;
    return;
}

// ---- Public method Reset   --------------------------------------------------
void R3BFrsHit2AnaS4Par::Reset() {}

void R3BFrsHit2AnaS4Par::FinishEvent() {}

// ---- Public method Finish   --------------------------------------------------
void R3BFrsHit2AnaS4Par::FinishTask()
{
    // Set Cal parameters --------------------------------
    Int_t NbParms = 3;
    fFrs_Par->SetNumParameters(NbParms);
    fFrs_Par->GetFrsAnaParams()->Set(NbParms);

    fFrs_Par->SetMagnificationS2S4(fMagS2S4);
    fFrs_Par->SetDispersionS2S4(fDispS2S4);
    fFrs_Par->SetPathS2S4(fPathS2S4);
    fFrs_Par->SetTOFS2S4(fTOFS2S4);
    fFrs_Par->SetDistTpcS2(fDisTpcS2);
    fFrs_Par->SetDistTpcS4(fDisTpcS4);
    fFrs_Par->SetRhoS0S2(frho_S0_S2);
    fFrs_Par->SetRhoS2S4(frho_S2_S4);
    fFrs_Par->SetBfiedS0S2(fBfield_S0_S2);
    fFrs_Par->SetBfiedS2S4(fBfield_S2_S4);
    fFrs_Par->SetPosFocalS2(fPosFocalS2);
    fFrs_Par->SetPosFocalS4(fPosFocalS4);

    LOG(info) << "mean " << fh_anglevsAq->GetMean(1) << ", " << fh_anglevsAq->GetMean(2);
    // LOG(info)<<"mean "<<graph->GetMean(1)<<", "<<graph->GetMean(2);

    for (Int_t i = 0; i < graph->GetN(); i++)
    {
        Double_t a[2];
        graph->GetPoint(i, a[0], a[1]);
        h_Profile->Fill(a[0] - fh_anglevsAq->GetMean(1), a[1] - fh_anglevsAq->GetMean(2));
    }

    h_Profile->Fit("pol1");

    TF1* fitAoQ_angle = h_Profile->GetFunction("pol1");

    fFrs_Par->SetFrsAnaParams(fh_anglevsAq->GetMean(1), 0);
    fFrs_Par->SetFrsAnaParams(fh_anglevsAq->GetMean(2), 1);
    fFrs_Par->SetFrsAnaParams(fitAoQ_angle->GetParameter(1), 2);

    fFrs_Par->setChanged();
    h_Profile->Write();
    fh_anglevsAq->Write();

    // fFrs_Par->printParams();
}

ClassImp(R3BFrsHit2AnaS4Par)

// ----------------------------------------------------------------------
// -----         R3BFrsHit2AnaS4 source file                        -----
// -----             Created 29/07/18  by J.L. Rodriguez-Sanchez    -----
// ----------------------------------------------------------------------

// ROOT headers
#include "TClonesArray.h"
#include "TF1.h"
#include "TMath.h"
#include "TRandom.h"

// Fair headers
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRuntimeDb.h"

#include <iomanip>

// FRS headers
#include "R3BFrsAnaPar.h"
#include "R3BFrsS4Data.h"
#include "R3BFrsHit2AnaS4.h"
#include "R3BFrsMappedData.h"
#include "FRSMusicHitData.h"
#include "R3BTpcHitData.h"
#include "FrsSciSingleTcalData.h"

Double_t const c = 299792458.0;     // Light velocity
Double_t const e = 1.60217662e-19;  // Electron charge
Double_t const u = 1.660538921e-27; // Atomic mass unit

// R3BFrsHit2AnaS4: Default Constructor --------------------------
R3BFrsHit2AnaS4::R3BFrsHit2AnaS4()
    : FairTask("R3B TPC Hit-Calibrator", 1)
    , fOffsetAq(0)
    , fOffsetZ(0)
    , fParm0(0)
    , fParm1(0)
    , fRotS4(0)
    , fAnaParams(NULL)
    , fFrs_Par(NULL)
    , fFrsMappedDataCA(NULL)
    , fTpcHitDataCA(NULL)
    , fMusicHitDataCA(NULL)
    , fFrsDataCA(NULL)
    , fOnline(kFALSE)
{
}

// R3BFrsHit2AnaS4Par: Standard Constructor --------------------------
R3BFrsHit2AnaS4::R3BFrsHit2AnaS4(const char* name, Int_t iVerbose)
    : FairTask(name, iVerbose)
    , fOffsetAq(0)
    , fOffsetZ(0)
    , fParm0(0)
    , fParm1(0)
    , fRotS4(0)
    , fAnaParams(NULL)
    , fFrs_Par(NULL)
    , fFrsMappedDataCA(NULL)
    , fTpcHitDataCA(NULL)
    , fMusicHitDataCA(NULL)
    , fFrsDataCA(NULL)
    , fOnline(kFALSE)
{
}

// Virtual R3BFrsHit2AnaS4: Destructor
R3BFrsHit2AnaS4::~R3BFrsHit2AnaS4()
{
    LOG(INFO) << "R3BFrsHit2AnaS4: Delete instance";
    if (fFrsMappedDataCA)
    {
        delete fFrsMappedDataCA;
    }
    if (fMusicHitDataCA)
    {
        delete fMusicHitDataCA;
    }
    if (fTpcHitDataCA)
    {
        delete fTpcHitDataCA;
    }
    if (fFrsDataCA)
    {
        delete fFrsDataCA;
    }
}

void R3BFrsHit2AnaS4::SetParContainers()
{
    // Parameter Container
    // Reading musicCalPar from FairRuntimeDb
    FairRuntimeDb* rtdb = FairRuntimeDb::instance();
    if (!rtdb)
    {
        LOG(ERROR) << "FairRuntimeDb not opened!";
    }

    fFrs_Par = (R3BFrsAnaPar*)rtdb->getContainer("frsAnaPar");
    if (!fFrs_Par)
    {
        LOG(ERROR) << "R3BFrsHit2AnaS4Par::Init() Couldn't get handle on frsAnaPar container";
    }
    else
    {
        LOG(INFO) << "R3BFrsHit2AnaS4Par:: frsAnaPar container open";
    }
}

void R3BFrsHit2AnaS4::SetParameter()
{
    //--- Parameter Container ---
    fMagS2S4 = fFrs_Par->GetMagnificationS2S4();
    fDispS2S4 = fFrs_Par->GetDispersionS2S4();
    fPathS2S4 = fFrs_Par->GetPathS2S4();
    fTOFS2S4 = fFrs_Par->GetTOFS2S4();
    fDisTpcS2 = fFrs_Par->GetDistTpcS2();
    fDisTpcS4 = fFrs_Par->GetDistTpcS4();
    frho_S0_S2 = fFrs_Par->GetRhoS0S2();
    frho_S2_S4 = fFrs_Par->GetRhoS2S4();
    fBfield_S0_S2 = fFrs_Par->GetBfiedS0S2();
    fBfield_S2_S4 = fFrs_Par->GetBfiedS2S4();
    fPosFocalS2 = fFrs_Par->GetPosFocalS2();
    fPosFocalS4 = fFrs_Par->GetPosFocalS4();
    LOG(INFO) << "R3BFrsHit2AnaS4: Rho (S0-S2): " << frho_S0_S2;
    LOG(INFO) << "R3BFrsHit2AnaS4: B (S0-S2): " << fBfield_S0_S2;
    LOG(INFO) << "R3BFrsHit2AnaS4: Rho (S2-S4): " << frho_S2_S4;
    LOG(INFO) << "R3BFrsHit2AnaS4: B (S2-S4): " << fBfield_S2_S4;
    LOG(INFO) << "R3BFrsHit2AnaS4: Distance between TPCs at S2[mm]: " << fDisTpcS2;
    LOG(INFO) << "R3BFrsHit2AnaS4: Distance between TPCs at S4[mm]: " << fDisTpcS4;
    LOG(INFO) << "R3BFrsHit2AnaS4: Pos for focal plane at S2[mm]: " << fPosFocalS2;
    LOG(INFO) << "R3BFrsHit2AnaS4: Pos for focal plane at S4[mm]: " << fPosFocalS4;

    Int_t NumParams = fFrs_Par->GetNumParameters(); // Number of Parameters
    fAnaParams = new TArrayF();
    fAnaParams->Set(NumParams);
    fAnaParams = fFrs_Par->GetFrsAnaParams(); // Array with the parameters
    fParm0 = fAnaParams->GetAt(0);
    fParm1 = fAnaParams->GetAt(1);
    fRotS4 = fAnaParams->GetAt(2);
    LOG(INFO) << "R3BFrsHit2AnaS4: Params " << fParm0 << " : " << fParm1 << " : " << fRotS4;
}

// -----   Public method Init   --------------------------------------------
InitStatus R3BFrsHit2AnaS4::Init()
{
    LOG(INFO) << "R3BFrsHit2AnaS4: Init FRS analysis from S2 to S4";

    // INPUT DATA
    FairRootManager* rootManager = FairRootManager::Instance();
    if (!rootManager)
    {
        return kFATAL;
    }

    //fFrsMappedDataCA = (TClonesArray*)rootManager->GetObject("FrsMappedData");
    fFrsMappedDataCA = (TClonesArray*)rootManager->GetObject("FrsSciSingleTcalData");

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

    // OUTPUT DATA
    fFrsDataCA = new TClonesArray("R3BFrsS4Data", 10);
    if (!fOnline)
    {
        rootManager->Register("FrsData", "Analysis FRS", fFrsDataCA, kTRUE);
    }
    else
    {
        rootManager->Register("FrsData", "Analysis FRS", fFrsDataCA, kFALSE);
    }

    SetParameter();
    return kSUCCESS;
}

// -----   Public method ReInit   ----------------------------------------------
InitStatus R3BFrsHit2AnaS4::ReInit()
{
    SetParContainers();
    return kSUCCESS;
}

// -----   Public method Execution   --------------------------------------------
void R3BFrsHit2AnaS4::Exec(Option_t* option)
{

    // if(++nEvents % 10000 == 0)
    // LOG(INFO) << nEvents ;

    // Reset entries in output arrays, local arrays
    Reset();

    Double_t fZ = 0., fAq = 0.;

    Int_t nHitFrs = fFrsMappedDataCA->GetEntries();
    Int_t nHitMusic = fMusicHitDataCA->GetEntries();
    Int_t nHitTpc = fTpcHitDataCA->GetEntries();
    // LOG(INFO) << nHitMusic << " " << nHitTpc ;
    if (!nHitMusic || !nHitFrs || !nHitTpc)
        return; // FIXME:include here warning!

//    R3BFrsMappedData** MapFrs = new R3BFrsMappedData*[nHitFrs];
    FrsSciSingleTcalData** MapFrs = new FrsSciSingleTcalData*[nHitFrs];
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

    Double_t SCI24_TofRR = 0.;
    Double_t SCI24_TofLL = 0.;

    for (Int_t i = 0; i < nHitFrs; i++)
    {
        MapFrs[i] = (FrsSciSingleTcalData*)(fFrsMappedDataCA->At(i));
        SCI24_TofRR = MapFrs[i]->GetRawTofNs(0);
        SCI24_TofLL = MapFrs[i]->GetRawTofNs(0);
        //SCI24_TofRR = MapFrs[i]->GetSCI41RT();
        //SCI24_TofLL = MapFrs[i]->GetSCI41LT();
        // LOG(INFO) << SCI24_TofRR << " " << SCI24_TofLL ;
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
    double ToF_star_S2_S4 = 0.5 * (SCI24_TofLL + SCI24_TofRR);
    double Beta_S2_S4 = ((fPathS2S4 / (fTOFS2S4 + ToF_star_S2_S4)) * pow(10., 7)) / c;
    double Gamma_S2_S4 = 1. / (sqrt(1. - (Beta_S2_S4) * (Beta_S2_S4)));

    // Brho and A/q
    double Brho_S4 = fBfield_S2_S4 * frho_S2_S4 *
                     (1. - (((x_position_focal_S4 / 1000.) - fMagS2S4 * (x_position_focal_S2 / 1000.)) / fDispS2S4));
    fAq = (Brho_S4 * e) / (Gamma_S2_S4 * Beta_S2_S4 * c * u);

    // Correction for dependence on angle
    fAq = (fAq - fParm1) * cos(-1. * fRotS4) + (angle_S4_mrad - fParm0) * sin(-1. * fRotS4) + fParm1;

    // Fill the data
    AddData(fZ + fOffsetZ, fAq + fOffsetAq, x_position_focal_S2, angle_S2_mrad, x_position_focal_S4, Beta_S2_S4);

    if (HitMusic)
        delete HitMusic;
    if (HitTpc)
        delete HitTpc;
    if (MapFrs)
        delete MapFrs;
    return;
}

// -----   Protected method Finish   --------------------------------------------
void R3BFrsHit2AnaS4::Finish() {}

// -----   Public method Reset   ------------------------------------------------
void R3BFrsHit2AnaS4::Reset()
{
    LOG(DEBUG) << "Clearing FrsData Structure";
    if (fFrsDataCA)
        fFrsDataCA->Clear();
}

// -----   Private method AddData  --------------------------------------------
R3BFrsS4Data* R3BFrsHit2AnaS4::AddData(Double_t z, Double_t aq, Double_t xs2, Double_t as2, Double_t xs4, Double_t as4)
{
    // It fills the R3BFrsData
    TClonesArray& clref = *fFrsDataCA;
    Int_t size = clref.GetEntriesFast();
    return new (clref[size]) R3BFrsS4Data(z, aq, xs2, as2, xs4, as4);
}

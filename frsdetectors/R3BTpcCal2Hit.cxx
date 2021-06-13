// ----------------------------------------------------------------------
// -----               R3BTpcCal2Hit source file                    -----
// -----         Created 29/07/18  by J.L. Rodriguez-Sanchez        -----
// ----------------------------------------------------------------------

// ROOT headers
#include "TClonesArray.h"
#include "TMath.h"
#include "TRandom.h"

// Fair headers
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRuntimeDb.h"

#include <iomanip>

// TPC headers
#include "R3BTpcCal2Hit.h"
#include "R3BTpcCalData.h"
#include "R3BTpcCalPar.h"
#include "R3BTpcHitData.h"

// R3BTpcCal2Hit: Default Constructor --------------------------
R3BTpcCal2Hit::R3BTpcCal2Hit()
    : FairTask("R3B TPC Hit-Calibrator", 1)
    , fNumDets(4)
    , fCal_Par(NULL)
    , fTpcHitDataCA(NULL)
    , fTpcCalDataCA(NULL)
    , fOnline(kFALSE)
{
}

// R3BTpcCal2HitPar: Standard Constructor --------------------------
R3BTpcCal2Hit::R3BTpcCal2Hit(const char* name, Int_t iVerbose)
    : FairTask(name, iVerbose)
    , fNumDets(4)
    , fCal_Par(NULL)
    , fTpcHitDataCA(NULL)
    , fTpcCalDataCA(NULL)
    , fOnline(kFALSE)
{
}

// Virtual R3BTpcCal2Hit: Destructor
R3BTpcCal2Hit::~R3BTpcCal2Hit()
{
    LOG(INFO) << "R3BTpcCal2Hit: Delete instance";
    if (fTpcCalDataCA)
        delete fTpcCalDataCA;
    if (fTpcHitDataCA)
        delete fTpcHitDataCA;
}

void R3BTpcCal2Hit::SetParContainers()
{

    // Parameter Container
    // Reading tpcCalPar from FairRuntimeDb
    FairRuntimeDb* rtdb = FairRuntimeDb::instance();
    if (!rtdb)
    {
        LOG(ERROR) << "FairRuntimeDb not opened!";
    }

    fCal_Par = (R3BTpcCalPar*)rtdb->getContainer("tpcCalPar");
    if (!fCal_Par)
    {
        LOG(ERROR) << "R3BTpcCal2Hit::Init() Couldn't get handle on tpcCalPar container";
    }
    else
    {
        LOG(INFO) << "R3BTpcCal2Hit:: tpcCalPar container open";
    }
}

void R3BTpcCal2Hit::SetParameter()
{

    //--- Parameter Container ---
    fNumDets = fCal_Par->GetNumDets(); // Number of Detectors
    LOG(INFO) << "R3BTpcCal2Hit: Nb detectors: " << fNumDets;
}

// -----   Public method Init   --------------------------------------------
InitStatus R3BTpcCal2Hit::Init()
{
    LOG(INFO) << "R3BTpcCal2Hit: Init";

    // INPUT DATA
    FairRootManager* rootManager = FairRootManager::Instance();
    if (!rootManager)
    {
        return kFATAL;
    }

    fTpcCalDataCA = (TClonesArray*)rootManager->GetObject("TpcCalData");
    if (!fTpcCalDataCA)
    {
        return kFATAL;
    }

    // OUTPUT DATA
    // Hit data
    fTpcHitDataCA = new TClonesArray("R3BTpcHitData", 10);
    if (!fOnline)
    {
        rootManager->Register("TpcHitData", "TPC Hit", fTpcHitDataCA, kTRUE);
    }
    else
    {
        rootManager->Register("TpcHitData", "TPC Hit", fTpcHitDataCA, kFALSE);
    }

    SetParameter();
    return kSUCCESS;
}

// -----   Public method ReInit   ----------------------------------------------
InitStatus R3BTpcCal2Hit::ReInit()
{
    SetParContainers();
    return kSUCCESS;
}

// -----   Public method Execution   --------------------------------------------
void R3BTpcCal2Hit::Exec(Option_t* option)
{

    // Reset entries in output arrays, local arrays
    Reset();

    if (!fCal_Par)
    {
        LOG(ERROR) << "NO Container Parameter!!";
    }

    Int_t nHits = fTpcCalDataCA->GetEntries();
    if (!nHits)
        return;

    R3BTpcCalData** CalDat = new R3BTpcCalData*[nHits];

    Int_t detId, secId, xyId;
    Double_t fx=-999., fy=-999.;

    Double_t tpc_x[fNumDets], tpc_y[fNumDets];
    Int_t count_x[fNumDets], count_y[fNumDets];
    for (Int_t i = 0; i < fNumDets; i++)
    {
        tpc_x[i] = -500.;
        count_x[i] = 0;
        tpc_y[i] = -500.;
        count_y[i] = 0;
    }

    for (Int_t i = 0; i < nHits; i++)
    {
        CalDat[i] = (R3BTpcCalData*)(fTpcCalDataCA->At(i));
        detId = CalDat[i]->GetDetectorId();
        secId = CalDat[i]->GetSecId();
        xyId = CalDat[i]->GetXYId();

        // std::cout << detId << " " << secId << " " << xyId << std::endl;

        if (xyId == 0)
        { // for X
            if (CalDat[i]->GetPosition() >= -100. && CalDat[i]->GetPosition() <= 100.)
            {
                if (tpc_x[detId] == -500)
                    tpc_x[detId] = 0.;
                tpc_x[detId] = tpc_x[detId] + CalDat[i]->GetPosition();
                count_x[detId]++;
            }
        }
        else
        { // for Y
            if (CalDat[i]->GetPosition() >= -100. && CalDat[i]->GetPosition() <= 100.)
            {
                if (tpc_y[detId] == -500)
                    tpc_y[detId] = 0.;
                tpc_y[detId] = tpc_y[detId] + CalDat[i]->GetPosition();
                count_y[detId]++;
            }
        }
    }

    for (Int_t i = 0; i < fNumDets; i++)
    {
        if (count_x[i] > 0)// && count_y[i] > 0)
        {
            fx = tpc_x[i] / count_x[i];
            if(count_y[i] > 0)fy = tpc_y[i] / count_y[i];
            // std::cout << i << " " << fx << " " << fy << std::endl;
            AddHitData(i, fx, fy);
        }
    }

    if (CalDat)
        delete CalDat;
    return;
}

// -----   Protected method Finish   --------------------------------------------
void R3BTpcCal2Hit::Finish() {}

// -----   Public method Reset   ------------------------------------------------
void R3BTpcCal2Hit::Reset()
{
    LOG(DEBUG) << "Clearing TpcHitData Structure";
    if (fTpcHitDataCA)
        fTpcHitDataCA->Clear();
}

// -----   Private method AddHitData  --------------------------------------------
R3BTpcHitData* R3BTpcCal2Hit::AddHitData(Int_t detid, Double_t x, Double_t y)
{
    // It fills the R3BTpcHitData
    TClonesArray& clref = *fTpcHitDataCA;
    Int_t size = clref.GetEntriesFast();
    return new (clref[size]) R3BTpcHitData(detid, x, y);
}

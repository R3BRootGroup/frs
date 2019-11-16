// ----------------------------------------------------------------------
// -----             R3BMWMapped2Hit source file                    -----
// -----         Created 27/03/19  by J.L. Rodriguez-Sanchez        -----
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

// MW headers
#include "R3BMWMapped2Hit.h"
#include "R3BMwHitData.h"
#include "R3BMwMappedData.h"

// R3BMWMapped2Hit: Default Constructor --------------------------
R3BMWMapped2Hit::R3BMWMapped2Hit()
    : FairTask("R3B MW Mapped to Hit", 1)
    , fNumDets(13)
    , fMw11MappedDataCA(NULL)
    , fMw21MappedDataCA(NULL)
    , fMw22MappedDataCA(NULL)
    , fMw31MappedDataCA(NULL)
    , fMw51MappedDataCA(NULL)
    , fMw71MappedDataCA(NULL)
    , fMw81MappedDataCA(NULL)
    , fMw82MappedDataCA(NULL)
    , fMwHitDataCA(NULL)
    , fOnline(kFALSE)
{
}

// R3BMWMapped2HitPar: Standard Constructor --------------------------
R3BMWMapped2Hit::R3BMWMapped2Hit(const char* name, Int_t iVerbose)
    : FairTask(name, iVerbose)
    , fNumDets(13)
    , fMw11MappedDataCA(NULL)
    , fMw21MappedDataCA(NULL)
    , fMw22MappedDataCA(NULL)
    , fMw31MappedDataCA(NULL)
    , fMw51MappedDataCA(NULL)
    , fMw71MappedDataCA(NULL)
    , fMw81MappedDataCA(NULL)
    , fMw82MappedDataCA(NULL)
    , fMwHitDataCA(NULL)
    , fOnline(kFALSE)
{
}

// Virtual R3BMWMapped2Hit: Destructor
R3BMWMapped2Hit::~R3BMWMapped2Hit()
{
    LOG(INFO) << "R3BMWMapped2Hit: Delete instance";
    if (fMwHitDataCA)
        delete fMwHitDataCA;
    if (fMw11MappedDataCA)
        delete fMw11MappedDataCA;
    if (fMw21MappedDataCA)
        delete fMw21MappedDataCA;
    if (fMw22MappedDataCA)
        delete fMw22MappedDataCA;
    if (fMw31MappedDataCA)
        delete fMw31MappedDataCA;
    if (fMw51MappedDataCA)
        delete fMw51MappedDataCA;
    if (fMw71MappedDataCA)
        delete fMw71MappedDataCA;
    if (fMw81MappedDataCA)
        delete fMw81MappedDataCA;
    if (fMw82MappedDataCA)
        delete fMw82MappedDataCA;
}

void R3BMWMapped2Hit::SetParContainers()
{

    // Parameter Container
    // Reading tpcCalPar from FairRuntimeDb
    FairRuntimeDb* rtdb = FairRuntimeDb::instance();
    if (!rtdb)
    {
        LOG(ERROR) << "FairRuntimeDb not opened!";
    }
}

void R3BMWMapped2Hit::SetParameter()
{

    //--- Parameter Container ---
    // fNumDets=fCal_Par->GetNumDets();//Number of Detectors
    LOG(INFO) << "R3BMWMapped2Hit: Nb detectors: " << fNumDets;

    x_factor[0] = 0.25;   // MW11 [mm/ns] 14.09.05 CN+AM 2ns/mm delay line
    x_factor[1] = 0.25;   // MW21
    x_factor[2] = 0.25;   // MW22
    x_factor[3] = 0.25;   // MW31
    x_factor[4] = 0.25;   // MW41
    x_factor[5] = 0.25;   // MW42
    x_factor[6] = 0.25;   // MW51
    x_factor[7] = 0.25;   // MW61
    x_factor[8] = 0.25;   // MW71
    x_factor[9] = 0.25;   // MW81
    x_factor[10] = 0.125; // MW82 [mm/ns] 11.05.06  CN 4ns/mm delay line
    x_factor[11] = 0.25;  // MWB1
    x_factor[12] = 0.25;  // MWB2

    x_offset[0] = 5.0;    // MW11 Feb 2014
    x_offset[1] = -2.0;   // MW21 Feb 2014
    x_offset[2] = -1.5;   // MW22 Feb 2014
    x_offset[3] = -0.205; // MW31 Feb 2014
    x_offset[4] = 0.;     // MW41
    x_offset[5] = -9.;    // MW42
    x_offset[6] = 0.;     // MW51
    x_offset[7] = 0.;     // MW61
    x_offset[8] = 1.642;  // MW71
    x_offset[9] = 1.;     // MW81
    x_offset[10] = -5.;   // MW82
    x_offset[11] = 0.;    // MWB1
    x_offset[12] = 0.;    // MWB2

    y_factor[0] = 0.25;   // MW11 [mm/ns] 14.09.05 CN+AM 2ns/mm delay line
    y_factor[1] = 0.25;   // MW21
    y_factor[2] = 0.25;   // MW22
    y_factor[3] = 0.25;   // MW31
    y_factor[4] = 0.25;   // MW41
    y_factor[5] = 0.25;   // MW42
    y_factor[6] = 0.25;   // MW51
    y_factor[7] = 0.25;   // MW61
    y_factor[8] = 0.25;   // MW71
    y_factor[9] = 0.25;   // MW81
    y_factor[10] = 0.125; // MW82  [mm/ns] 11.05.06  CN 4ns/mm delay line
    y_factor[11] = 0.25;  // MWB1
    y_factor[12] = 0.25;  // MWB2

    y_offset[0] = -14.0;  // MW11 Feb 2014
    y_offset[1] = 21.0;   // MW21 Feb 2014
    y_offset[2] = -1.0;   // MW22 Feb 2014
    y_offset[3] = 0.0;    // MW31 Feb 2014
    y_offset[4] = 0.;     // MW41
    y_offset[5] = 0.;     // MW42
    y_offset[6] = 0.;     // MW51
    y_offset[7] = 0.;     // MW61
    y_offset[8] = -2.736; // MW71
    y_offset[9] = 3.2;    // MW81
    y_offset[10] = 0.764; // MW82
    y_offset[11] = 0.;    // MWB1
    y_offset[12] = 0.;    // MWB2

    gain_tdc[0][0] = 0.302929; //  MW11 Anode (#ch  0 TDC V775a) // 13.01.2008
    gain_tdc[1][0] = 0.303253; //  MW11 XL    (#ch 17 TDC V775a)
    gain_tdc[2][0] = 0.303975; //  MW11 XR    (#ch 16 TDC V775a)
    gain_tdc[3][0] = 0.308414; //  MW11 YU    (#ch 18 TDC V775a)
    gain_tdc[4][0] = 0.309826; //  MW11 YD    (#ch 19 TDC V775a)

    gain_tdc[0][1] = 0.306064; //  MW21 Anode (#ch  1 TDC V775a) // 13.01.2008
    gain_tdc[1][1] = 0.306958; //  MW21 XL    (#ch 21 TDC V775a)
    gain_tdc[2][1] = 0.307799; //  MW21 XR    (#ch 20 TDC V775a)
    gain_tdc[3][1] = 0.297774; //  MW21 YU    (#ch 22 TDC V775a)
    gain_tdc[4][1] = 0.310235; //  MW21 YD    (#ch 23 TDC V775a)

    gain_tdc[0][2] = 0.301179; // MW22 Anode (#ch  2 TDC V775a) // 13.01.2008
    gain_tdc[1][2] = 0.311121; //  MW22 XL    (#ch 25 TDC V775a)
    gain_tdc[2][2] = 0.303233; //  MW22 XR    (#ch 24 TDC V775a)
    gain_tdc[3][2] = 0.300558; //  MW22 YU    (#ch 26 TDC V775a)
    gain_tdc[4][2] = 0.301105; //  MW22 YD    (#ch 27 TDC V775a)

    gain_tdc[0][3] = 0.304426; //  MW31 Anode (#ch  3 TDC V775a) // 13.01.2008
    gain_tdc[1][3] = 0.312163; //  MW31 XL    (#ch 29 TDC V775a)
    gain_tdc[2][3] = 0.305609; //  MW31 XR    (#ch 28 TDC V775a)
    gain_tdc[3][3] = 0.304716; //  MW31 YU    (#ch 30 TDC V775a)
    gain_tdc[4][3] = 0.293695; //  MW31 YD    (#ch 31 TDC V775a)

    gain_tdc[0][4] = 0.298871; //  MW41 Anode (#ch  4 TDC V775a) // 13.01.2008
    gain_tdc[1][4] = 0.284086; //  MW41 XL    (#ch 1 TDC V775b)
    gain_tdc[2][4] = 0.288656; //  MW41 XR    (#ch 0 TDC V775b)
    gain_tdc[3][4] = 0.286589; //  MW41 YU    (#ch 2 TDC V775b)
    gain_tdc[4][4] = 0.29269;  //  MW41 YD    (#ch 3 TDC V775b)

    gain_tdc[0][5] = 0.297881; //  MW42 Anode (#ch  5 TDC V775a) // 13.01.2008
    gain_tdc[1][5] = 0.287364; //  MW42 XL    (#ch 5 TDC V775b)
    gain_tdc[2][5] = 0.289636; //  MW42 XR    (#ch 4 TDC V775b)
    gain_tdc[3][5] = 0.291135; //  MW42 YU    (#ch 6 TDC V775b)
    gain_tdc[4][5] = 0.289867; //  MW42 YD    (#ch 7 TDC V775b)

    gain_tdc[0][6] = 0.307892; //  MW51 Anode (#ch  6 TDC V775a) // 13.01.2008
    gain_tdc[1][6] = 0.289894; //  MW51 XL    (#ch  9 TDC V775b)
    gain_tdc[2][6] = 0.292366; //  MW51 XR    (#ch  8 TDC V775b)
    gain_tdc[3][6] = 0.284708; //  MW51 YU    (#ch 10 TDC V775b)
    gain_tdc[4][6] = 0.28186;  //  MW51 YD    (#ch 11 TDC V775b)

    gain_tdc[0][7] = 0.298266; //  MW61 Anode (#ch  7 TDC V775a) // 13.01.2008
    gain_tdc[1][7] = 0.311;    //  MW61 XL    (#ch ? TDC V775b)
    gain_tdc[2][7] = 0.305;    //  MW61 XR    (#ch ? TDC V775b)
    gain_tdc[3][7] = 0.337;    //  MW61 YU    (#ch ? TDC V775b)
    gain_tdc[4][7] = 0.289;    //  MW61 YD    (#ch ? TDC V775b)

    gain_tdc[0][8] = 0.303602; //  MW71 Anode (#ch  8 TDC V775a) // 13.01.2008
    gain_tdc[1][8] = 0.300082; //  MW71 XL    (#ch 13 TDC V775b)
    gain_tdc[2][8] = 0.286092; //  MW71 XR    (#ch 12 TDC V775b)
    gain_tdc[3][8] = 0.294287; //  MW71 YU    (#ch 14 TDC V775b)
    gain_tdc[4][8] = 0.291341; //  MW71 YD    (#ch 15 TDC V775b)

    gain_tdc[0][9] = 0.306041; //  MW81 Anode (#ch  9 TDC V775a) // 13.01.2008
    gain_tdc[1][9] = 0.288468; //  MW81 XL    (#ch 17 TDC V775b)
    gain_tdc[2][9] = 0.293831; //  MW81 XR    (#ch 16 TDC V775b)
    gain_tdc[3][9] = 0.281296; //  MW81 YU    (#ch 18 TDC V775b)
    gain_tdc[4][9] = 0.279099; //  MW81 YD    (#ch 19 TDC V775b)

    gain_tdc[0][10] = 0.31314;  //  MW82 Anode (#ch 10 TDC V775a) // 13.01.2008
    gain_tdc[1][10] = 0.287279; //  MW82 XL    (#ch 21 TDC V775b)
    gain_tdc[2][10] = 0.284028; //  MW82 XR    (#ch 20 TDC V775b)
    gain_tdc[3][10] = 0.28051;  //  MW82 YU    (#ch 22 TDC V775b)
    gain_tdc[4][10] = 0.28743;  //  MW82 YD    (#ch 23 TDC V775b)

    gain_tdc[0][11] = 0.299973; //  MWB21 Anode (#ch 11 TDC V775a) // 13.01.2008
    gain_tdc[1][11] = 0.311;    //  MWB21 XL    (#ch ? TDC V775b)
    gain_tdc[2][11] = 0.305;    //  MWB21 XR    (#ch ? TDC V775b)
    gain_tdc[3][11] = 0.337;    //  MWB21 YU    (#ch ? TDC V775b)
    gain_tdc[4][11] = 0.289;    //  MWB21 YD    (#ch ? TDC V775b)

    gain_tdc[0][12] = 0.306923; //  MWB22 Anode (#ch 12 TDC V775a) // 13.01.2008
    gain_tdc[1][12] = 0.311;    //  MWB22 XL    (#ch ? TDC V775b)
    gain_tdc[2][12] = 0.305;    //  MWB22 XR    (#ch ? TDC V775b)
    gain_tdc[3][12] = 0.337;    //  MWB22 YU    (#ch ? TDC V775b)
    gain_tdc[4][12] = 0.289;    //  MWB22 YD    (#ch ? TDC V775b)
}

// -----   Public method Init   --------------------------------------------
InitStatus R3BMWMapped2Hit::Init()
{
    LOG(INFO) << "R3BMWMapped2Hit: Init";

    // INPUT DATA
    FairRootManager* rootManager = FairRootManager::Instance();
    if (!rootManager)
    {
        return kFATAL;
    }
    fMw11MappedDataCA = (TClonesArray*)rootManager->GetObject("MW11MappedData");
    if (!fMw11MappedDataCA)
    {
        LOG(WARNING) << "R3BMWMapped2Hit: Not found object MW11MappedData";
    }
    fMw21MappedDataCA = (TClonesArray*)rootManager->GetObject("MW21MappedData");
    if (!fMw21MappedDataCA)
    {
        LOG(WARNING) << "R3BMWMapped2Hit: Not found object MW21MappedData";
    }
    fMw22MappedDataCA = (TClonesArray*)rootManager->GetObject("MW22MappedData");
    if (!fMw22MappedDataCA)
    {
        LOG(WARNING) << "R3BMWMapped2Hit: Not found object MW22MappedData";
    }
    fMw31MappedDataCA = (TClonesArray*)rootManager->GetObject("MW31MappedData");
    if (!fMw31MappedDataCA)
    {
        LOG(WARNING) << "R3BMWMapped2Hit: Not found object MW31MappedData";
    }
    fMw51MappedDataCA = (TClonesArray*)rootManager->GetObject("MW51MappedData");
    if (!fMw51MappedDataCA)
    {
        LOG(WARNING) << "R3BMWMapped2Hit: Not found object MW51MappedData";
    }
    fMw71MappedDataCA = (TClonesArray*)rootManager->GetObject("MW71MappedData");
    if (!fMw71MappedDataCA)
    {
        LOG(WARNING) << "R3BMWMapped2Hit: Not found object MW71MappedData";
    }
    fMw81MappedDataCA = (TClonesArray*)rootManager->GetObject("MW81MappedData");
    if (!fMw81MappedDataCA)
    {
        LOG(WARNING) << "R3BMWMapped2Hit: Not found object MW81MappedData";
    }
    fMw82MappedDataCA = (TClonesArray*)rootManager->GetObject("MW82MappedData");
    if (!fMw82MappedDataCA)
    {
        LOG(WARNING) << "R3BMWMapped2Hit: Not found object MW82MappedData";
    }

    // OUTPUT DATA
    // Hit data
    fMwHitDataCA = new TClonesArray("R3BMwHitData", 10);
    if (!fOnline)
    {
        rootManager->Register("MwHitData", "MW Hit", fMwHitDataCA, kTRUE);
    }
    else
    {
        rootManager->Register("MwHitData", "MW Hit", fMwHitDataCA, kFALSE);
    }

    SetParameter();
    return kSUCCESS;
}

// -----   Public method ReInit   ----------------------------------------------
InitStatus R3BMWMapped2Hit::ReInit()
{
    SetParContainers();
    return kSUCCESS;
}

// -----   Public method Execution   --------------------------------------------
void R3BMWMapped2Hit::Exec(Option_t* option)
{
    // Reset entries in output arrays, local arrays
    Reset();
    if(fMw11MappedDataCA)MakeHit(fMw11MappedDataCA);
    if(fMw21MappedDataCA)MakeHit(fMw21MappedDataCA);
    if(fMw22MappedDataCA)MakeHit(fMw22MappedDataCA);
    if(fMw31MappedDataCA)MakeHit(fMw31MappedDataCA);
    if(fMw51MappedDataCA)MakeHit(fMw51MappedDataCA);
    if(fMw71MappedDataCA)MakeHit(fMw71MappedDataCA);
    if(fMw81MappedDataCA)MakeHit(fMw81MappedDataCA);
    if(fMw82MappedDataCA)MakeHit(fMw82MappedDataCA);

}

// -----   Public method Make Hit   ---------------------------------------------
void R3BMWMapped2Hit::MakeHit(TClonesArray* fMwMappedData)
{

    Int_t nHits = fMwMappedData->GetEntries();
    if (!nHits)
        return;
    R3BMwMappedData** MapDat = new R3BMwMappedData*[nHits];
    Int_t detId;
    Double_t fx, fy;
    Double_t an, xr, xl, yu, yd, xsum = 0, ysum = 0;

    for (Int_t i = 0; i < nHits; i++)
    {
        MapDat[i] = (R3BMwMappedData*)(fMwMappedData->At(i));
        detId = MapDat[i]->GetDetId();
        an = MapDat[i]->GetAn();
        xr = MapDat[i]->GetXr();
        xl = MapDat[i]->GetXl();
        yu = MapDat[i]->GetYu();
        yd = MapDat[i]->GetYd();

        // std::cout<< gain_tdc[1][detId] <<" "<<gain_tdc[2][detId] <<std::endl;
        // std::cout<< nHits <<" " << detId <<std::endl;
        // Control sum for x and y
        xsum = 1000 + (xl - an) + (xr - an);
        ysum = 1000 + (yu - an) + (yd - an);
        if (xsum > 1 && xsum < 8000 && ysum > 1 && ysum < 8000)
        {
            // X position
            Double_t r_x = xl * gain_tdc[1][detId] - xr * gain_tdc[2][detId];
            fx = x_factor[detId] * r_x + x_offset[detId];
            // Y position
            Double_t r_y = yd * gain_tdc[4][detId] - yu * gain_tdc[3][detId];
            fy = y_factor[detId] * r_y + y_offset[detId];
            AddHitData(detId, fx, fy);
        }
    }
    if (MapDat)
        delete MapDat;
    return;
}

// -----   Protected method Finish   --------------------------------------------
void R3BMWMapped2Hit::Finish() {}

// -----   Public method Reset   ------------------------------------------------
void R3BMWMapped2Hit::Reset()
{
    LOG(DEBUG) << "Clearing MwHitData Structure";
    if (fMwHitDataCA)
        fMwHitDataCA->Clear();
}

// -----   Private method AddHitData  --------------------------------------------
R3BMwHitData* R3BMWMapped2Hit::AddHitData(Int_t detid, Double_t x, Double_t y)
{
    // It fills the R3BMwHitData
    TClonesArray& clref = *fMwHitDataCA;
    Int_t size = clref.GetEntriesFast();
    return new (clref[size]) R3BMwHitData(detid, x, y);
}

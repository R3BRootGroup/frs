// ----------------------------------------------------------------------
// -----              R3BTpcMapped2Cal source file                  -----
// -----        Created 22/07/18  by J.L. Rodriguez-Sanchez         -----
// ----------------------------------------------------------------------

// ROOT headers
#include "TClonesArray.h"
#include "TMath.h"

// Fair headers
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRuntimeDb.h"

#include <iomanip>

// TPC headers
#include "R3BTpcCalData.h"
#include "R3BTpcCalPar.h"
#include "R3BTpcMapped2Cal.h"
#include "R3BTpcMappedData.h"

// R3BTpcMapped2Cal: Default Constructor --------------------------
R3BTpcMapped2Cal::R3BTpcMapped2Cal()
    : FairTask("R3B Tpc Calibrator", 1)
    , NumDets(0)
    , NumAnodes(8)
    , NumParams(0)
    , fNumAnodesX(2)
    , fNumAnodesY(4)
    , CalParams(NULL)
    , CsumMaxParams(NULL)
    , CsumMinParams(NULL)
    , fCal_Par(NULL)
    , fTpcMappedDataCA(NULL)
    , fTpcCalDataCA(NULL)
    , fOnline(kFALSE)
{
}

// R3BTpcMapped2CalPar: Standard Constructor --------------------------
R3BTpcMapped2Cal::R3BTpcMapped2Cal(const char* name, Int_t iVerbose)
    : FairTask(name, iVerbose)
    , NumDets(0)
    , NumAnodes(8)
    , NumParams(0)
    , fNumAnodesX(2)
    , fNumAnodesY(4)
    , CalParams(NULL)
    , CsumMaxParams(NULL)
    , CsumMinParams(NULL)
    , fCal_Par(NULL)
    , fTpcMappedDataCA(NULL)
    , fTpcCalDataCA(NULL)
    , fOnline(kFALSE)
{
}

// Virtual R3BTpcMapped2Cal: Destructor
R3BTpcMapped2Cal::~R3BTpcMapped2Cal()
{
    LOG(INFO) << "R3BTpcMapped2Cal: Delete instance";
    if (fTpcMappedDataCA)
        delete fTpcMappedDataCA;
    if (fTpcCalDataCA)
        delete fTpcCalDataCA;
}

void R3BTpcMapped2Cal::SetParContainers()
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
        LOG(ERROR) << "R3BTpcMapped2CalPar::Init() Couldn't get handle on tpcCalPar container";
    }
    else
    {
        LOG(INFO) << "R3BTpcMapped2CalPar:: tpcCalPar container open";
    }
}

void R3BTpcMapped2Cal::SetParameter()
{

    //--- Parameter Container ---
    NumDets = fCal_Par->GetNumDets();            // Number of Detectors
    NumAnodes = fCal_Par->GetNumDT();            // Number of anodes
    NumParams = fCal_Par->GetNumParametersFit(); // Number of Parameters

    LOG(INFO) << "R3BTpcMapped2Cal: Nb detectors: " << NumDets;
    LOG(INFO) << "R3BTpcMapped2Cal: Nb anodes: " << NumAnodes;
    LOG(INFO) << "R3BTpcMapped2Cal: Nb parameters from fit: " << NumParams;

    CsumMaxParams = new TArrayF();
    Int_t array_size = NumDets * fNumAnodesY;
    CsumMaxParams->Set(array_size);
    CsumMaxParams = fCal_Par->GetTpcCsumMaxParams(); // Array with the CsumMax parameters

    CsumMinParams = new TArrayF();
    array_size = NumDets * fNumAnodesY;
    CsumMinParams->Set(array_size);
    CsumMinParams = fCal_Par->GetTpcCsumMinParams(); // Array with the CsumMin parameters

    CalParams = new TArrayF();
    array_size = NumDets * NumAnodes * NumParams;
    CalParams->Set(array_size);
    CalParams = fCal_Par->GetTpcCalParams(); // Array with the Cal parameters

    // Count the number of DTs per TPC detector no fitted
    for (Int_t d = 0; d < NumDets; d++)
    {
        Int_t numdeadanodes = 0;
        for (Int_t i = 0; i < NumAnodes; i++)
            if (CalParams->GetAt(NumParams * i + NumAnodes * d * NumParams) == 0)
                numdeadanodes++;
        LOG(INFO) << "R3BTpcMapped2Cal: Nb of NO fitted sections in TPC " << d + 1 << ": " << numdeadanodes;
    }
    // fCal_Par->printParams();
}

// -----   Public method Init   --------------------------------------------
InitStatus R3BTpcMapped2Cal::Init()
{
    LOG(INFO) << "R3BTpcMapped2Cal: Init";

    // INPUT DATA
    FairRootManager* rootManager = FairRootManager::Instance();
    if (!rootManager)
    {
        return kFATAL;
    }

    fTpcMappedDataCA = (TClonesArray*)rootManager->GetObject("TpcMappedData");
    if (!fTpcMappedDataCA)
    {
        return kFATAL;
    }

    // OUTPUT DATA
    // Calibrated data
    fTpcCalDataCA = new TClonesArray("R3BTpcCalData", 10);
    if (!fOnline)
    {
        rootManager->Register("TpcCalData", "TPC Cal", fTpcCalDataCA, kTRUE);
    }
    else
    {
        rootManager->Register("TpcCalData", "TPC Cal", fTpcCalDataCA, kFALSE);
    }

    SetParameter();
    return kSUCCESS;
}

// -----   Public method ReInit   ----------------------------------------------
InitStatus R3BTpcMapped2Cal::ReInit()
{
    SetParContainers();
    return kSUCCESS;
}

// -----   Public method Execution   --------------------------------------------
void R3BTpcMapped2Cal::Exec(Option_t* option)
{
    // Reset entries in output arrays, local arrays
    Reset();

    if (!fCal_Par)
    {
        LOG(ERROR) << "NO Container Parameter!!";
    }

    // Reading the Input -- Mapped Data --
    Int_t nHits = fTpcMappedDataCA->GetEntries();
    if (nHits != NumDets && nHits > 0)
        LOG(WARNING) << "R3BTpcMapped2Cal: nHits=" << nHits << " NumDets=" << NumDets;
    if (!nHits)
        return;

    R3BTpcMappedData* MapHit;
    Int_t detId, xyId, secId;

    Double_t x0, x0cal, x1, x1cal, y;
    for (Int_t i = 0; i < nHits; i++)
    {
        MapHit = (R3BTpcMappedData*)(fTpcMappedDataCA->At(i));
        detId = MapHit->GetDetectorId();

        fTpcdt[0] = (MapHit->GetTpcdt())[0];
        fTpcdt[1] = (MapHit->GetTpcdt())[1];
        fTpcdt[2] = (MapHit->GetTpcdt())[2];
        fTpcdt[3] = (MapHit->GetTpcdt())[3];
        fTpcrt[0] = (MapHit->GetTpcrt())[0];
        fTpcrt[1] = (MapHit->GetTpcrt())[1];
        fTpclt[0] = (MapHit->GetTpclt())[0];
        fTpclt[1] = (MapHit->GetTpclt())[1];

        // Init control sum for TPC
        for (int j = 0; j < fNumAnodesY; j++)
        {
            tpc_csum[j] = 0.;
            b_tpc_csum[j] = kFALSE;
        }

        for (Int_t j = 0; j < fNumAnodesY; j++)
        {
            // calculate control sums
            if (j < 2)
            {
                tpc_csum[j] = (fTpclt[0] + fTpcrt[0] - 2 * fTpcdt[j]);
            }
            else
            {
                tpc_csum[j] = (fTpclt[1] + fTpcrt[1] - 2 * fTpcdt[j]);
            }

             std::cout<<detId<<" "<<j<<" "<<fTpclt[0]<<" "<<fTpcrt[0]<<" "<<fTpclt[1]<<" "<<fTpcrt[1]<<" "<<fTpcdt[j]<<std::endl;

            if (tpc_csum[j] > CsumMinParams->GetAt(detId * fNumAnodesY + j) &&
                tpc_csum[j] < CsumMaxParams->GetAt(detId * fNumAnodesY + j))
                b_tpc_csum[j] = kTRUE;

            if ((fTpclt[0] == 0 && fTpcrt[0] == 0 && j < 2) || (fTpclt[1] == 0 && fTpcrt[1] == 0 && j > 1))
            {
                b_tpc_csum[j] = kFALSE;
            }

            if (b_tpc_csum[j])
            {
                // if(tpc_csum[j]<CsumMinParams->GetAt(detId*fNumAnodesY+j))std::cout <<" det: "<<detId<<" j;"<<j<< "
                // "<<  CsumMinParams->GetAt(detId*fNumAnodesY+j) <<" "<< tpc_csum[j] << std::endl;
                y = CalParams->GetAt(NumParams * j + detId * NumParams * NumAnodes) +
                    fTpcdt[j] * CalParams->GetAt(NumParams * j + detId * NumParams * NumAnodes + 1);
                AddCalData(detId, 1, j, y, tpc_csum[j]);
            }

        } // j<4

        Int_t index = fNumAnodesY;
        if (b_tpc_csum[0] || b_tpc_csum[1])
        {
            // fh_Map_dt_x[2*detId]->Fill(fTpclt->GetAt(0)-fTpcrt->GetAt(0));
            x0 = fTpclt[0] - fTpcrt[0];
            x0cal = CalParams->GetAt(NumParams * index + detId * NumParams * NumAnodes) +
                    x0 * CalParams->GetAt(NumParams * index + detId * NumParams * NumAnodes + 1);
            AddCalData(detId, 0, 0, x0cal, x0);
        }

        index++;
        if (b_tpc_csum[2] || b_tpc_csum[3])
        {
            // fh_Map_dt_x[1+2*detId]->Fill(fTpclt->GetAt(1)-fTpcrt->GetAt(1));
            x1 = fTpclt[1] - fTpcrt[1];
            x1cal = CalParams->GetAt(NumParams * index + detId * NumParams * NumAnodes) +
                    x1 * CalParams->GetAt(NumParams * index + detId * NumParams * NumAnodes + 1);
            AddCalData(detId, 0, 1, x1cal, x1);
        }
    }
    return;
}

// -----   Protected method Finish   --------------------------------------------
void R3BTpcMapped2Cal::Finish() {}

// -----   Public method Reset   ------------------------------------------------
void R3BTpcMapped2Cal::Reset()
{
    LOG(DEBUG) << "Clearing TpcCalData Structure";
    if (fTpcCalDataCA)
        fTpcCalDataCA->Clear();
}

// -----   Private method AddCalData  --------------------------------------------
R3BTpcCalData* R3BTpcMapped2Cal::AddCalData(Int_t detId,
                                            Int_t xyId,
                                            Int_t secId,
                                            Double_t position,
                                            Double_t controlpar)
{
    // It fills the R3BTpcCalData
    TClonesArray& clref = *fTpcCalDataCA;
    Int_t size = clref.GetEntriesFast();
    return new (clref[size]) R3BTpcCalData(detId, xyId, secId, position, controlpar);
}

ClassImp(R3BTpcMapped2Cal)

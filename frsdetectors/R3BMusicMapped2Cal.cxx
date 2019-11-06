// ----------------------------------------------------------------------
// -----             R3BMusicMapped2Cal source file                 -----
// -----         Created 22/07/18  by J.L. Rodriguez-Sanchez        -----
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

// Music headers
#include "R3BMusicCalData.h"
#include "R3BMusicCalPar.h"
#include "R3BMusicMapped2Cal.h"
#include "R3BMusicMappedData.h"

// R3BMusicMapped2Cal: Default Constructor --------------------------
R3BMusicMapped2Cal::R3BMusicMapped2Cal()
    : FairTask("R3B Music Calibrator", 1)
    , NumDets(0)
    , NumAnodes(8)
    , NumParams(0)
    , MaxSigma(200)
    , CalParams(NULL)
    , fCal_Par(NULL)
    , fMusicMappedDataCA(NULL)
    , fMusicCalDataCA(NULL)
    , fOnline(kFALSE)
{
}

// R3BMusicMapped2CalPar: Standard Constructor --------------------------
R3BMusicMapped2Cal::R3BMusicMapped2Cal(const char* name, Int_t iVerbose)
    : FairTask(name, iVerbose)
    , NumDets(0)
    , NumAnodes(8)
    , NumParams(0)
    , MaxSigma(200)
    , CalParams(NULL)
    , fCal_Par(NULL)
    , fMusicMappedDataCA(NULL)
    , fMusicCalDataCA(NULL)
    , fOnline(kFALSE)
{
}

// Virtual R3BMusicMapped2Cal: Destructor
R3BMusicMapped2Cal::~R3BMusicMapped2Cal()
{
    LOG(INFO) << "R3BMusicMapped2Cal: Delete instance";
    if (fMusicMappedDataCA)
        delete fMusicMappedDataCA;
    if (fMusicCalDataCA)
        delete fMusicCalDataCA;
}

void R3BMusicMapped2Cal::SetParContainers()
{

    // Parameter Container
    // Reading musicCalPar from FairRuntimeDb
    FairRuntimeDb* rtdb = FairRuntimeDb::instance();
    if (!rtdb)
    {
        LOG(ERROR) << "FairRuntimeDb not opened!";
    }

    fCal_Par = (R3BMusicCalPar*)rtdb->getContainer("musicCalPar");
    if (!fCal_Par)
    {
        LOG(ERROR) << "R3BMusicMapped2CalPar::Init() Couldn't get handle on musicCalPar container";
    }
    else
    {
        LOG(INFO) << "R3BMusicMapped2CalPar:: musicCalPar container open";
    }
}

void R3BMusicMapped2Cal::SetParameter()
{

    //--- Parameter Container ---
    NumDets = fCal_Par->GetNumDets();            // Number of Detectors
    NumAnodes = fCal_Par->GetNumAnodes();        // Number of anodes
    NumParams = fCal_Par->GetNumParametersFit(); // Number of Parameters

    LOG(INFO) << "R3BMusicMapped2Cal: Nb detectors: " << NumDets;
    LOG(INFO) << "R3BMusicMapped2Cal: Nb anodes: " << NumAnodes;
    LOG(INFO) << "R3BMusicMapped2Cal: Nb parameters from pedestal fit: " << NumParams;

    CalParams = new TArrayF();
    Int_t array_size = NumDets * NumAnodes * NumParams;
    CalParams->Set(array_size);
    CalParams = fCal_Par->GetAnodeCalParams(); // Array with the Cal parameters

    // Count the number of dead anodes per Music detector
    for (Int_t d = 0; d < NumDets; d++)
    {
        Int_t numdeadanodes = 0;
        for (Int_t i = 0; i < NumAnodes; i++)
            if (CalParams->GetAt(NumParams * i + 1 + NumAnodes * d * NumParams) == -1)
                numdeadanodes++;
        LOG(INFO) << "R3BMusicMapped2Cal: Nb of dead anodes in MUSIC " << d + 1 << ": " << numdeadanodes;
    }
}

// -----   Public method Init   --------------------------------------------
InitStatus R3BMusicMapped2Cal::Init()
{
    LOG(INFO) << "R3BMusicMapped2Cal: Init";

    // INPUT DATA
    FairRootManager* rootManager = FairRootManager::Instance();
    if (!rootManager)
    {
        return kFATAL;
    }

    fMusicMappedDataCA = (TClonesArray*)rootManager->GetObject("MusicMappedData");
    if (!fMusicMappedDataCA)
    {
        return kFATAL;
    }

    // OUTPUT DATA
    // Calibrated data
    fMusicCalDataCA = new TClonesArray("R3BMusicCalData", 10);
    if (!fOnline)
    {
        rootManager->Register("MusicCalData", "MUSIC Cal", fMusicCalDataCA, kTRUE);
    }
    else
    {
        rootManager->Register("MusicCalData", "MUSIC Cal", fMusicCalDataCA, kFALSE);
    }

    SetParameter();
    return kSUCCESS;
}

// -----   Public method ReInit   ----------------------------------------------
InitStatus R3BMusicMapped2Cal::ReInit()
{
    SetParContainers();
    return kSUCCESS;
}

// -----   Public method Execution   --------------------------------------------
void R3BMusicMapped2Cal::Exec(Option_t* option)
{
    // Reset entries in output arrays, local arrays
    Reset();

    if (!fCal_Par)
    {
        LOG(ERROR) << "NO Container Parameter!!";
    }

    // Reading the Input -- Mapped Data --
    Int_t nHits = fMusicMappedDataCA->GetEntries();
    if (nHits != NumAnodes * NumDets && nHits > 0)
        LOG(WARNING) << "R3BMusicMapped2Cal: nHits!=" << nHits << " NumAnodes:NumDets" << NumAnodes << ":" << NumDets;
    if (!nHits)
        return;

    R3BMusicMappedData** mappedData = new R3BMusicMappedData*[nHits];
    Int_t detId;
    Int_t anodeId;
    Double_t energy;
    Double_t pedestal = 0.;
    Double_t sigma = 0.;

    for (Int_t i = 0; i < nHits; i++)
    {
        mappedData[i] = (R3BMusicMappedData*)(fMusicMappedDataCA->At(i));
        detId = mappedData[i]->GetDetectorId();
        anodeId = mappedData[i]->GetAnodeId();

        pedestal = CalParams->GetAt(NumParams * anodeId + 1 + detId * NumAnodes * NumParams);
        // sigma=CalParams->GetAt(NumParams*anodeId+2+detId*NumAnodes*NumParams);

        // std::cout << detId << " " << anodeId<<" "<< mappedData[i]->GetEnergy()<< " " << pedestal << std::endl;

        energy = mappedData[i]->GetEnergy() - pedestal;

        if (pedestal != -1)
            AddCalData(detId, anodeId, energy);
    }

    if (mappedData)
        delete mappedData;
    return;
}

// -----   Protected method Finish   --------------------------------------------
void R3BMusicMapped2Cal::Finish() {}

// -----   Public method Reset   ------------------------------------------------
void R3BMusicMapped2Cal::Reset()
{
    LOG(DEBUG) << "Clearing MusicCalData Structure";
    if (fMusicCalDataCA)
        fMusicCalDataCA->Clear();
}

// -----   Private method AddCalData  --------------------------------------------
R3BMusicCalData* R3BMusicMapped2Cal::AddCalData(Int_t detid, Int_t anodeid, Double_t energy)
{
    // It fills the R3BMusicCalData
    TClonesArray& clref = *fMusicCalDataCA;
    Int_t size = clref.GetEntriesFast();
    return new (clref[size]) R3BMusicCalData(detid, anodeid, energy);
}

ClassImp(R3BMusicMapped2Cal)

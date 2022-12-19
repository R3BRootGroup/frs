// ----------------------------------------------------------------------
// -----             FRSMusicMapped2Cal source file                 -----
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
#include "FRSMusicCalData.h"
#include "FRSMusicCalPar.h"
#include "FRSMusicMapped2Cal.h"
#include "FRSMusicMappedData.h"

// FRSMusicMapped2Cal: Default Constructor --------------------------
FRSMusicMapped2Cal::FRSMusicMapped2Cal()
    : FairTask("FRS Music Calibrator", 1)
    , NumDets(0)
    , NumAnodes(8)
    , NumParams(0)
    , MaxSigma(200)
    , CalParams(NULL)
    , fCal_Par(NULL)
    , fMusicMappedDataCA(NULL)
    , fMusicCalDataCA(NULL)
    , fOnline(kFALSE)
{}

// FRSMusicMapped2CalPar: Standard Constructor --------------------------
FRSMusicMapped2Cal::FRSMusicMapped2Cal(const char* name, Int_t iVerbose)
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
{}

// Virtual FRSMusicMapped2Cal: Destructor
FRSMusicMapped2Cal::~FRSMusicMapped2Cal()
{
    LOG(INFO) << "FRSMusicMapped2Cal: Delete instance";
    if (fMusicMappedDataCA)
        delete fMusicMappedDataCA;
    if (fMusicCalDataCA)
        delete fMusicCalDataCA;
}

void FRSMusicMapped2Cal::SetParContainers()
{

    // Parameter Container
    // Reading musicCalPar from FairRuntimeDb
    FairRuntimeDb* rtdb = FairRuntimeDb::instance();
    if (!rtdb) {
        LOG(error) << "FairRuntimeDb not opened!";
    }

    fCal_Par = (FRSMusicCalPar*)rtdb->getContainer("frsmusicCalPar");
    if (!fCal_Par) {
        LOG(error) << "FRSMusicMapped2CalPar::Init() Couldn't get handle on frsmusicCalPar container";
    } else {
        LOG(INFO) << "FRSMusicMapped2CalPar:: frsmusicCalPar container open";
    }
}

void FRSMusicMapped2Cal::SetParameter()
{

    //--- Parameter Container ---
    NumDets = fCal_Par->GetNumDets();              // Number of Detectors
    NumAnodes = fCal_Par->GetNumAnodes();          // Number of anodes
    NumParams = fCal_Par->GetNumParametersFit();   // Number of Parameters

    LOG(INFO) << "FRSMusicMapped2Cal: Nb detectors: " << NumDets;
    LOG(INFO) << "FRSMusicMapped2Cal: Nb anodes: " << NumAnodes;
    LOG(INFO) << "FRSMusicMapped2Cal: Nb parameters from pedestal fit: " << NumParams;

    CalParams = new TArrayF();
    Int_t array_size = NumDets * NumAnodes * NumParams;
    CalParams->Set(array_size);
    CalParams = fCal_Par->GetAnodeCalParams();   // Array with the Cal parameters

    // Count the number of dead anodes per Music detector
    for (Int_t d = 0; d < NumDets; d++) {
        Int_t numdeadanodes = 0;
        for (Int_t i = 0; i < NumAnodes; i++)
            if (CalParams->GetAt(NumParams * i + 1 + NumAnodes * d * NumParams) == -1)
                numdeadanodes++;
        LOG(INFO) << "FRSMusicMapped2Cal: Nb of dead anodes in MUSIC " << d + 1 << ": " << numdeadanodes;
    }
}

// -----   Public method Init   --------------------------------------------
InitStatus FRSMusicMapped2Cal::Init()
{
    LOG(INFO) << "FRSMusicMapped2Cal: Init";

    // INPUT DATA
    FairRootManager* rootManager = FairRootManager::Instance();
    if (!rootManager) {
        return kfatal;
    }

    fMusicMappedDataCA = (TClonesArray*)rootManager->GetObject("FRSMusicMappedData");
    if (!fMusicMappedDataCA) {
        return kfatal;
    }

    // OUTPUT DATA
    // Calibrated data
    fMusicCalDataCA = new TClonesArray("FRSMusicCalData", 10);
    if (!fOnline) {
        rootManager->Register("FRSMusicCalData", "MUSIC Cal", fMusicCalDataCA, kTRUE);
    } else {
        rootManager->Register("FRSMusicCalData", "MUSIC Cal", fMusicCalDataCA, kFALSE);
    }

    SetParameter();
    return kSUCCESS;
}

// -----   Public method ReInit   ----------------------------------------------
InitStatus FRSMusicMapped2Cal::ReInit()
{
    SetParContainers();
    return kSUCCESS;
}

// -----   Public method Execution   --------------------------------------------
void FRSMusicMapped2Cal::Exec(Option_t* option)
{
    // Reset entries in output arrays, local arrays
    Reset();

    if (!fCal_Par) {
        LOG(error) << "NO Container Parameter!!";
    }

    // Reading the Input -- Mapped Data --
    Int_t nHits = fMusicMappedDataCA->GetEntries();
    if (nHits != NumAnodes * NumDets && nHits > 0)
        LOG(warn) << "FRSMusicMapped2Cal: nHits!=" << nHits << " NumAnodes:NumDets" << NumAnodes << ":" << NumDets;
    if (!nHits)
        return;

    FRSMusicMappedData** mappedData = new FRSMusicMappedData*[nHits];
    Int_t detId;
    Int_t anodeId;
    Double_t energy;
    Double_t pedestal = 0.;
    Double_t sigma = 0.;

    for (Int_t i = 0; i < nHits; i++) {
        mappedData[i] = (FRSMusicMappedData*)(fMusicMappedDataCA->At(i));
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
void FRSMusicMapped2Cal::Finish() {}

// -----   Public method Reset   ------------------------------------------------
void FRSMusicMapped2Cal::Reset()
{
    LOG(DEBUG) << "Clearing MusicCalData Structure";
    if (fMusicCalDataCA)
        fMusicCalDataCA->Clear();
}

// -----   Private method AddCalData  --------------------------------------------
FRSMusicCalData* FRSMusicMapped2Cal::AddCalData(Int_t detid, Int_t anodeid, Double_t energy)
{
    // It fills the FRSMusicCalData
    TClonesArray& clref = *fMusicCalDataCA;
    Int_t size = clref.GetEntriesFast();
    return new (clref[size]) FRSMusicCalData(detid, anodeid, energy);
}

ClassImp(FRSMusicMapped2Cal)

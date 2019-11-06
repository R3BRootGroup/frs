// ----------------------------------------------------------------------
// -----                R3BSeetramMapped2Cal source file            -----
// -----          Created 10/08/18  by J.L. Rodriguez-Sanchez       -----
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

// Seetram and frs headers
#include "R3BFrsMappedData.h"
#include "R3BSeetramCalData.h"
#include "R3BSeetramCalPar.h"
#include "R3BSeetramMapped2Cal.h"

// R3BSeetramMapped2Cal: Default Constructor --------------------------
R3BSeetramMapped2Cal::R3BSeetramMapped2Cal()
    : FairTask("R3B Seetram Calibrator", 1)
    , NumParams(0)
    , fclock1hz(0)
    , firstclock1hz(0)
    , fclock10hz(0)
    , firstclock10hz(0)
    , fclock100khz(0)
    , firstclock100khz(0)
    , faceptrigcounts(0)
    , ffreetrigcounts(0)
    , fseecounts(0)
    , ficcounts(0)
    , fsci00counts(0)
    , fsci01counts(0)
    , fsci02counts(0)
    , fsci21counts(0)
    , fsci41counts(0)
    , fdumcounts(0)
    , firstEvt(kTRUE)
    , CalParams(NULL)
    , fCal_Par(NULL)
    , fFrsMappedDataCA(NULL)
    , fSeetramCalDataCA(NULL)
    , fOnline(kFALSE)
{
}

// R3BSeetramMapped2CalPar: Standard Constructor --------------------------
R3BSeetramMapped2Cal::R3BSeetramMapped2Cal(const char* name, Int_t iVerbose)
    : FairTask(name, iVerbose)
    , NumParams(0)
    , fclock1hz(0)
    , firstclock1hz(0)
    , fclock10hz(0)
    , firstclock10hz(0)
    , fclock100khz(0)
    , firstclock100khz(0)
    , faceptrigcounts(0)
    , ffreetrigcounts(0)
    , fseecounts(0)
    , ficcounts(0)
    , fsci00counts(0)
    , fsci01counts(0)
    , fsci02counts(0)
    , fsci21counts(0)
    , fsci41counts(0)
    , fdumcounts(0)
    , firstEvt(kTRUE)
    , CalParams(NULL)
    , fCal_Par(NULL)
    , fFrsMappedDataCA(NULL)
    , fSeetramCalDataCA(NULL)
    , fOnline(kFALSE)
{
}

// Virtual R3BSeetramMapped2Cal: Destructor
R3BSeetramMapped2Cal::~R3BSeetramMapped2Cal()
{
    LOG(INFO) << "R3BSeetramMapped2Cal: Delete instance";
    if (fFrsMappedDataCA)
        delete fFrsMappedDataCA;
    if (fSeetramCalDataCA)
        delete fSeetramCalDataCA;
}

void R3BSeetramMapped2Cal::SetParContainers()
{

    // Parameter Container
    // Reading seetramCalPar from FairRuntimeDb
    FairRuntimeDb* rtdb = FairRuntimeDb::instance();
    if (!rtdb)
    {
        LOG(ERROR) << "FairRuntimeDb not opened!";
    }

    fCal_Par = (R3BSeetramCalPar*)rtdb->getContainer("seetramCalPar");
    if (!fCal_Par)
    {
        LOG(ERROR) << "R3BSeetramMapped2CalPar::Init() Couldn't get handle on seetramCalPar container";
    }
    else
    {
        LOG(INFO) << "R3BSeetramMapped2CalPar:: seetramCalPar container open";
    }
}

void R3BSeetramMapped2Cal::SetParameter()
{

    //--- Parameter Container ---
    NumParams = fCal_Par->GetNumParametersFit(); // Number of Parameters

    LOG(INFO) << "R3BSeetramMapped2Cal: Nb parameters for calibration: " << NumParams;

    CalParams = new TArrayF();
    Int_t array_size = NumParams;
    CalParams->Set(array_size);
    CalParams = fCal_Par->GetSeetramCalParams(); // Array with the Cal parameters
    /*
      //Count the number of dead anodes per Music detector
      for(Int_t d = 0; d < NumDets; d++){
      Int_t numdeadanodes=0;
      for(Int_t i = 0; i < NumAnodes; i++)if(CalParams->GetAt(NumParams*i+1+NumAnodes*d*NumParams)==-1)numdeadanodes++;
      LOG(INFO)<<"R3BSeetramMapped2Cal: Nb of dead anodes in MUSIC " <<d+1<< ": "<< numdeadanodes;
      }
    */
}

// -----   Public method Init   --------------------------------------------
InitStatus R3BSeetramMapped2Cal::Init()
{
    LOG(INFO) << "R3BSeetramMapped2Cal: Init";

    // INPUT DATA
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

    // OUTPUT DATA
    // Calibrated data
    fSeetramCalDataCA = new TClonesArray("R3BSeetramCalData", 10);
    if (!fOnline)
    {
        rootManager->Register("SeetramCalData", "Seetram Cal", fSeetramCalDataCA, kTRUE);
    }
    else
    {
        rootManager->Register("SeetramCalData", "Seetram Cal", fSeetramCalDataCA, kFALSE);
    }

    // SetParameter();
    return kSUCCESS;
}

// -----   Public method ReInit   ----------------------------------------------
InitStatus R3BSeetramMapped2Cal::ReInit()
{
    SetParContainers();
    return kSUCCESS;
}

// -----   Public method Execution   --------------------------------------------
void R3BSeetramMapped2Cal::Exec(Option_t* option)
{

    // Reset entries in output arrays, local arrays
    Reset();

    if (!fCal_Par)
    {
        // LOG(ERROR)<<"NO Container for Seetram detector!!";
    }

    // Reading the Input -- Mapped Data --
    Int_t nHits = fFrsMappedDataCA->GetEntries();
    // if(nHits==0)LOG(WARNING) << "R3BSeetramMapped2Cal: nHits=" <<nHits;
    if (!nHits)
        return;

    R3BFrsMappedData** mappedData = new R3BFrsMappedData*[nHits];

    // fseecounts = 0;
    // firstEvt = kTRUE;

    for (Int_t i = 0; i < nHits; i++)
    {
        mappedData[i] = (R3BFrsMappedData*)(fFrsMappedDataCA->At(i));

        if (firstEvt)
        {
            firstEvt = kFALSE;
            faceptrigcounts = 0;
            ffreetrigcounts = 0;
            fseecounts = 0;
            ficcounts = 0;
            fsci00counts = 0;
            fsci01counts = 0;
            fsci02counts = 0;
            fsci21counts = 0;
            fsci41counts = 0;
            fdumcounts = 0;
            fclock1hz = mappedData[i]->GetClock1Hz();
            fclock10hz = mappedData[i]->GetClock10Hz();
            fclock100khz = mappedData[i]->GetClock100kHz();
            faceptrigcounter = mappedData[i]->GetAccTrig();
            ffreetrigcounter = mappedData[i]->GetFreeTrig();
            fseecounter = mappedData[i]->GetSeetramNew();
            fdumcounter = mappedData[i]->GetSeetramOld();
            ficcounter = mappedData[i]->GetIc();
            fsci00counter = mappedData[i]->GetSCI00();
            fsci01counter = mappedData[i]->GetSCI01();
            fsci02counter = mappedData[i]->GetSCI02();
            fsci21counter = mappedData[i]->GetSCI00(); // FIXME
            fsci41counter = mappedData[i]->GetSCI02();
            firstclock1hz = fclock1hz;
            firstclock10hz = fclock10hz;
            firstclock100khz = fclock100khz;
        }

        if (mappedData[i]->GetClock1Hz() < fclock1hz)
        {
            // firstclock1hz=-1*(fclock1hz-firstclock1hz)+mappedData[i]->GetClock1Hz();
            firstclock1hz = -(4294967295 - firstclock1hz) + mappedData[i]->GetClock1Hz();
            firstclock10hz = -(4294967295 - firstclock10hz) + mappedData[i]->GetClock10Hz();
            firstclock100khz = -(4294967295 - firstclock100khz) + mappedData[i]->GetClock100kHz();
            fclock1hz = mappedData[i]->GetClock1Hz();
            fclock10hz = mappedData[i]->GetClock10Hz();
            fclock100khz = mappedData[i]->GetClock100kHz();
            faceptrigcounter = mappedData[i]->GetAccTrig();
            ffreetrigcounter = mappedData[i]->GetFreeTrig();
            fseecounter = mappedData[i]->GetSeetramNew();
            fdumcounter = mappedData[i]->GetSeetramOld();
            ficcounter = mappedData[i]->GetIc();
            fsci00counter = mappedData[i]->GetSCI00();
            fsci01counter = mappedData[i]->GetSCI01();
            fsci02counter = mappedData[i]->GetSCI02();
            fsci21counter = mappedData[i]->GetSCI00(); // FIXME
            fsci41counter = mappedData[i]->GetSCI02();
        }

        if (mappedData[i]->GetClock1Hz() == fclock1hz)
        {
            faceptrigcounts = faceptrigcounts + (mappedData[i]->GetAccTrig() - faceptrigcounter);
            ffreetrigcounts = ffreetrigcounts + (mappedData[i]->GetFreeTrig() - ffreetrigcounter);
            fseecounts = fseecounts + (mappedData[i]->GetSeetramNew() - fseecounter);
            ficcounts = ficcounts + (mappedData[i]->GetIc() - ficcounter);
            fdumcounts = fdumcounts + (mappedData[i]->GetSeetramOld() - fdumcounter);
            fsci00counts = fsci00counts + (mappedData[i]->GetSCI00() - fsci00counter);
            fsci01counts = fsci01counts + (mappedData[i]->GetSCI01() - fsci01counter);
            fsci02counts = fsci02counts + (mappedData[i]->GetSCI02() - fsci02counter);

            fsci21counts = fsci21counts + (mappedData[i]->GetSCI00() - fsci21counter); // FIXME
            fsci41counts = fsci41counts + (mappedData[i]->GetSCI02() - fsci41counter);

            faceptrigcounter = mappedData[i]->GetAccTrig();
            ffreetrigcounter = mappedData[i]->GetFreeTrig();
            fseecounter = mappedData[i]->GetSeetramNew();
            fdumcounter = mappedData[i]->GetSeetramOld();
            ficcounter = mappedData[i]->GetIc();
            fsci00counter = mappedData[i]->GetSCI00();
            fsci01counter = mappedData[i]->GetSCI01();
            fsci02counter = mappedData[i]->GetSCI02();
            fsci21counter = mappedData[i]->GetSCI00(); // FIXME
            fsci41counter = mappedData[i]->GetSCI02();
        }
        else
        {
            // fseecounts=fseecounts;
            // std::cout << fclock1hz-firstclock1hz << " "<< fseecounts  << std::endl;
            // AddCalData(faceptrigcounts, ffreetrigcounts, fseecounts, ficcounts, fdumcounts, fsci00counts,
            // fsci01counts, fsci02counts, fclock1hz-firstclock1hz);
            AddCalData(faceptrigcounts,
                       ffreetrigcounts,
                       fseecounts,
                       ficcounts,
                       fdumcounts,
                       fsci21counts,
                       fsci01counts,
                       fsci41counts,
                       fclock1hz - firstclock1hz);
            fclock1hz = mappedData[i]->GetClock1Hz();
            faceptrigcounts = 0;
            ffreetrigcounts = 0;
            fseecounts = 0;
            ficcounts = 0;
            fdumcounts = 0;
            fsci00counts = 0;
            fsci01counts = 0;
            fsci02counts = 0;
            fsci21counts = 0;
            fsci41counts = 0;
            faceptrigcounts = faceptrigcounts + (mappedData[i]->GetAccTrig() - faceptrigcounter);
            ffreetrigcounts = ffreetrigcounts + (mappedData[i]->GetFreeTrig() - ffreetrigcounter);
            fseecounts = fseecounts + (mappedData[i]->GetSeetramNew() - fseecounter);
            ficcounts = ficcounts + (mappedData[i]->GetIc() - ficcounter);
            fdumcounts = fdumcounts + (mappedData[i]->GetSeetramOld() - fdumcounter);
            fsci00counts = fsci00counts + (mappedData[i]->GetSCI00() - fsci00counter);
            fsci01counts = fsci01counts + (mappedData[i]->GetSCI01() - fsci01counter);
            fsci02counts = fsci02counts + (mappedData[i]->GetSCI02() - fsci02counter);

            fsci21counts = fsci21counts + (mappedData[i]->GetSCI00() - fsci21counter);
            fsci41counts = fsci41counts + (mappedData[i]->GetSCI02() - fsci41counter);

            faceptrigcounter = mappedData[i]->GetAccTrig();
            ffreetrigcounter = mappedData[i]->GetFreeTrig();
            fseecounter = mappedData[i]->GetSeetramNew();
            fdumcounter = mappedData[i]->GetSeetramOld();
            ficcounter = mappedData[i]->GetIc();
            fsci00counter = mappedData[i]->GetSCI00();
            fsci01counter = mappedData[i]->GetSCI01();
            fsci02counter = mappedData[i]->GetSCI02();
            fsci21counter = mappedData[i]->GetSCI00(); // FIXME
            fsci41counter = mappedData[i]->GetSCI02();
        }
    }
    if (mappedData)
        delete mappedData;
    return;
}

// -----   Protected method Finish   --------------------------------------------
void R3BSeetramMapped2Cal::Finish() {}

// -----   Public method Reset   ------------------------------------------------
void R3BSeetramMapped2Cal::Reset()
{
    LOG(DEBUG) << "Clearing SeetramCalData Structure";
    if (fSeetramCalDataCA)
        fSeetramCalDataCA->Clear();
}

// -----   Private method AddCalData  --------------------------------------------
R3BSeetramCalData* R3BSeetramMapped2Cal::AddCalData(Int_t acc,
                                                    Int_t free,
                                                    Int_t seetram,
                                                    Int_t ic,
                                                    Int_t dum,
                                                    Int_t sci00,
                                                    Int_t sci01,
                                                    Int_t sci02,
                                                    Int_t clock1seg)
{
    // It fills the R3BSeetramCalData
    TClonesArray& clref = *fSeetramCalDataCA;
    Int_t size = clref.GetEntriesFast();
    return new (clref[size]) R3BSeetramCalData(acc, free, seetram, ic, dum, sci00, sci01, sci02, clock1seg);
}

ClassImp(R3BSeetramMapped2Cal)

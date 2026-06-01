// ----------------------------------------------------------------------
// -----                FrsRatesSpill source file                   -----
// -----          Created 17/11/19  by J.L. Rodriguez-Sanchez       -----
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
#include "FrsRatesSpill.h"
#include "FrsSpillMappedData.h"
#include "R3BSeetramCalData.h"

// FrsRatesSpill: Default Constructor --------------------------
FrsRatesSpill::FrsRatesSpill()
    : FairTask("Rate per Spill", 1)
    , fspill(0)
    , fclock1hz(0)
    , firstclock1hz(0)
    , fclock10hz(0)
    , firstclock10hz(0)
    , fclock100khz(0)
    , firstclock100khz(0)
    , fstart(0)
    , firststart(0)
    , fstop(0)
    , firststop(0)
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
    , fFrsMappedDataCA(NULL)
    , fSpillCalDataCA(NULL)
    , fOnline(kFALSE)
{
}

// FrsRatesSpillPar: Standard Constructor --------------------------
FrsRatesSpill::FrsRatesSpill(const char* name, Int_t iVerbose)
    : FairTask(name, iVerbose)
    , fspill(0)
    , fclock1hz(0)
    , firstclock1hz(0)
    , fclock10hz(0)
    , firstclock10hz(0)
    , fclock100khz(0)
    , firstclock100khz(0)
    , fstart(0)
    , firststart(0)
    , fstop(0)
    , firststop(0)
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
    , fFrsMappedDataCA(NULL)
    , fSpillCalDataCA(NULL)
    , fOnline(kFALSE)
{
}

// Virtual FrsRatesSpill: Destructor
FrsRatesSpill::~FrsRatesSpill()
{
    LOG(info) << "FrsRatesSpill: Delete instance";

    if (fSpillCalDataCA)
        delete fSpillCalDataCA;
}

// -----   Public method Init   --------------------------------------------
InitStatus FrsRatesSpill::Init()
{
    LOG(info) << "FrsRatesSpill: Init";

    // INPUT DATA
    FairRootManager* rootManager = FairRootManager::Instance();
    if (!rootManager)
    {
        return kFATAL;
    }

    fFrsMappedDataCA = (TClonesArray*)rootManager->GetObject("FrsSpillMappedData");
    if (!fFrsMappedDataCA)
    {
        return kFATAL;
    }

    // OUTPUT DATA
    fSpillCalDataCA = new TClonesArray("R3BSeetramCalData");
    if (!fOnline)
    {
        rootManager->Register("FrsSpillData", "Spill info", fSpillCalDataCA, kTRUE);
    }
    else
    {
        rootManager->Register("FrsSpillData", "Spill info", fSpillCalDataCA, kFALSE);
    }

    return kSUCCESS;
}

// -----   Public method ReInit   ----------------------------------------------
InitStatus FrsRatesSpill::ReInit() { return kSUCCESS; }

// -----   Public method Execution   --------------------------------------------
void FrsRatesSpill::Exec(Option_t* option)
{
    // Reset entries in output arrays, local arrays
    Reset();

    // Reading the Input -- Mapped Data --
    auto nHits = fFrsMappedDataCA->GetEntries();
    if (nHits == 0)
        return;

    for (Int_t i = 0; i < nHits; i++)
    {
        auto mappedData = (FrsSpillMappedData*)(fFrsMappedDataCA->At(i));

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
            fclock1hz = mappedData->GetClock1Hz();
            fclock10hz = mappedData->GetClock10Hz();
            fclock100khz = mappedData->GetClock100kHz();
            faceptrigcounter = mappedData->GetAccTrig();
            ffreetrigcounter = mappedData->GetFreeTrig();
            fseecounter = mappedData->GetSeetramNew();
            fdumcounter = mappedData->GetSeetramOld();
            ficcounter = mappedData->GetIc01();
            fsci00counter = mappedData->GetSCI00();
            fsci01counter = mappedData->GetSCI01();
            fsci02counter = mappedData->GetSCI02();
            fsci21counter = mappedData->GetSCI21L();
            fsci41counter = mappedData->GetSCI41L();
            firstclock1hz = fclock1hz;
            firstclock10hz = fclock10hz;
            firstclock100khz = fclock100khz;
            fstart = mappedData->GetStartExt();
            firststart = fstart;
            fstop = mappedData->GetStopExt();
            firststop = fstop;
        }

        if (mappedData->GetStartExt() == fstart && mappedData->GetStopExt() == fstop)
        { // nothing
        }
        else if (mappedData->GetStartExt() > fstart && mappedData->GetStopExt() == fstop)
        {
            faceptrigcounts = faceptrigcounts + (mappedData->GetAccTrig() - faceptrigcounter);
            ffreetrigcounts = ffreetrigcounts + (mappedData->GetFreeTrig() - ffreetrigcounter);
            fseecounts = fseecounts + (mappedData->GetSeetramNew() - fseecounter);
            ficcounts = ficcounts + (mappedData->GetIc01() - ficcounter);
            fdumcounts = fdumcounts + (mappedData->GetSeetramOld() - fdumcounter);
            fsci00counts = fsci00counts + (mappedData->GetSCI00() - fsci00counter);
            fsci01counts = fsci01counts + (mappedData->GetSCI01() - fsci01counter);
            fsci02counts = fsci02counts + (mappedData->GetSCI02() - fsci02counter);

            fsci21counts = fsci21counts + (mappedData->GetSCI21L() - fsci21counter);
            fsci41counts = fsci41counts + (mappedData->GetSCI41L() - fsci41counter);

            faceptrigcounter = mappedData->GetAccTrig();
            ffreetrigcounter = mappedData->GetFreeTrig();
            fseecounter = mappedData->GetSeetramNew();
            fdumcounter = mappedData->GetSeetramOld();
            ficcounter = mappedData->GetIc01();
            fsci00counter = mappedData->GetSCI00();
            fsci01counter = mappedData->GetSCI01();
            fsci02counter = mappedData->GetSCI02();
            fsci21counter = mappedData->GetSCI21L();
            fsci41counter = mappedData->GetSCI41L();
        }
        else
        {
            // std::cout<<"spill " << mappedData->GetStopExt() <<" " <<fstop <<std::endl;
            AddCalData(faceptrigcounts,
                       ffreetrigcounts,
                       fseecounts,
                       ficcounts,
                       fdumcounts,
                       fsci21counts,
                       fsci01counts,
                       fsci41counts,
                       fspill);
            fspill++;

            fclock1hz = mappedData->GetClock1Hz();
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
            faceptrigcounts = faceptrigcounts + (mappedData->GetAccTrig() - faceptrigcounter);
            ffreetrigcounts = ffreetrigcounts + (mappedData->GetFreeTrig() - ffreetrigcounter);
            fseecounts = fseecounts + (mappedData->GetSeetramNew() - fseecounter);
            ficcounts = ficcounts + (mappedData->GetIc01() - ficcounter);
            fdumcounts = fdumcounts + (mappedData->GetSeetramOld() - fdumcounter);
            fsci00counts = fsci00counts + (mappedData->GetSCI00() - fsci00counter);
            fsci01counts = fsci01counts + (mappedData->GetSCI01() - fsci01counter);
            fsci02counts = fsci02counts + (mappedData->GetSCI02() - fsci02counter);

            fsci21counts = fsci21counts + (mappedData->GetSCI21L() - fsci21counter);
            fsci41counts = fsci41counts + (mappedData->GetSCI41L() - fsci41counter);

            faceptrigcounter = mappedData->GetAccTrig();
            ffreetrigcounter = mappedData->GetFreeTrig();
            fseecounter = mappedData->GetSeetramNew();
            fdumcounter = mappedData->GetSeetramOld();
            ficcounter = mappedData->GetIc01();
            fsci00counter = mappedData->GetSCI00();
            fsci01counter = mappedData->GetSCI01();
            fsci02counter = mappedData->GetSCI02();
            fsci21counter = mappedData->GetSCI21L();
            fsci41counter = mappedData->GetSCI41L();
            fstart = mappedData->GetStartExt();
            fstop = mappedData->GetStopExt();
        }
    }

    /*
            if (mappedData->GetClock1Hz() < fclock1hz)
            {
                // firstclock1hz=-1*(fclock1hz-firstclock1hz)+mappedData->GetClock1Hz();
                firstclock1hz = -(4294967295 - firstclock1hz) + mappedData->GetClock1Hz();
                firstclock10hz = -(4294967295 - firstclock10hz) + mappedData->GetClock10Hz();
                firstclock100khz = -(4294967295 - firstclock100khz) + mappedData->GetClock100kHz();
                fclock1hz = mappedData->GetClock1Hz();
                fclock10hz = mappedData->GetClock10Hz();
                fclock100khz = mappedData->GetClock100kHz();
                faceptrigcounter = mappedData->GetAccTrig();
                ffreetrigcounter = mappedData->GetFreeTrig();
                fseecounter = mappedData->GetSeetramNew();
                fdumcounter = mappedData->GetSeetramOld();
                ficcounter = mappedData->GetIc();
                fsci00counter = mappedData->GetSCI00();
                fsci01counter = mappedData->GetSCI01();
                fsci02counter = mappedData->GetSCI02();
                fsci21counter = mappedData->GetSCI00(); // FIXME
                fsci41counter = mappedData->GetSCI02();
            }

            if (mappedData->GetClock1Hz() == fclock1hz)
            {
                faceptrigcounts = faceptrigcounts + (mappedData->GetAccTrig() - faceptrigcounter);
                ffreetrigcounts = ffreetrigcounts + (mappedData->GetFreeTrig() - ffreetrigcounter);
                fseecounts = fseecounts + (mappedData->GetSeetramNew() - fseecounter);
                ficcounts = ficcounts + (mappedData->GetIc() - ficcounter);
                fdumcounts = fdumcounts + (mappedData->GetSeetramOld() - fdumcounter);
                fsci00counts = fsci00counts + (mappedData->GetSCI00() - fsci00counter);
                fsci01counts = fsci01counts + (mappedData->GetSCI01() - fsci01counter);
                fsci02counts = fsci02counts + (mappedData->GetSCI02() - fsci02counter);

                fsci21counts = fsci21counts + (mappedData->GetSCI00() - fsci21counter); // FIXME
                fsci41counts = fsci41counts + (mappedData->GetSCI02() - fsci41counter);

                faceptrigcounter = mappedData->GetAccTrig();
                ffreetrigcounter = mappedData->GetFreeTrig();
                fseecounter = mappedData->GetSeetramNew();
                fdumcounter = mappedData->GetSeetramOld();
                ficcounter = mappedData->GetIc();
                fsci00counter = mappedData->GetSCI00();
                fsci01counter = mappedData->GetSCI01();
                fsci02counter = mappedData->GetSCI02();
                fsci21counter = mappedData->GetSCI00(); // FIXME
                fsci41counter = mappedData->GetSCI02();
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
                fclock1hz = mappedData->GetClock1Hz();
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
                faceptrigcounts = faceptrigcounts + (mappedData->GetAccTrig() - faceptrigcounter);
                ffreetrigcounts = ffreetrigcounts + (mappedData->GetFreeTrig() - ffreetrigcounter);
                fseecounts = fseecounts + (mappedData->GetSeetramNew() - fseecounter);
                ficcounts = ficcounts + (mappedData->GetIc() - ficcounter);
                fdumcounts = fdumcounts + (mappedData->GetSeetramOld() - fdumcounter);
                fsci00counts = fsci00counts + (mappedData->GetSCI00() - fsci00counter);
                fsci01counts = fsci01counts + (mappedData->GetSCI01() - fsci01counter);
                fsci02counts = fsci02counts + (mappedData->GetSCI02() - fsci02counter);

                fsci21counts = fsci21counts + (mappedData->GetSCI00() - fsci21counter);
                fsci41counts = fsci41counts + (mappedData->GetSCI02() - fsci41counter);

                faceptrigcounter = mappedData->GetAccTrig();
                ffreetrigcounter = mappedData->GetFreeTrig();
                fseecounter = mappedData->GetSeetramNew();
                fdumcounter = mappedData->GetSeetramOld();
                ficcounter = mappedData->GetIc();
                fsci00counter = mappedData->GetSCI00();
                fsci01counter = mappedData->GetSCI01();
                fsci02counter = mappedData->GetSCI02();
                fsci21counter = mappedData->GetSCI00(); // FIXME
                fsci41counter = mappedData->GetSCI02();
            }
        }
    */

    return;
}

// -----   Protected method Finish   --------------------------------------------
void FrsRatesSpill::Finish() {}

// -----   Public method Reset   ------------------------------------------------
void FrsRatesSpill::Reset()
{
    LOG(debug) << "Clearing SeetramCalData Structure";
    if (fSpillCalDataCA)
        fSpillCalDataCA->Clear();
}

// -----   Private method AddCalData  --------------------------------------------
R3BSeetramCalData* FrsRatesSpill::AddCalData(Int_t acc,
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
    TClonesArray& clref = *fSpillCalDataCA;
    Int_t size = clref.GetEntriesFast();
    return new (clref[size]) R3BSeetramCalData(acc, free, seetram, ic, dum, sci00, sci01, sci02, clock1seg);
}

ClassImp(FrsRatesSpill)

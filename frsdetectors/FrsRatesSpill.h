// ----------------------------------------------------------------------
// -----                                                            -----
// -----                     FrsRatesSpill                          -----
// -----             Created 17/11/19  by J.L. Rodriguez-Sanchez    -----
// ----------------------------------------------------------------------

#ifndef FrsRatesSpill_H
#define FrsRatesSpill_H

#include "FairTask.h"
#include "R3BSeetramCalData.h"
#include "TH1F.h"

class TClonesArray;

class FrsRatesSpill : public FairTask
{

  public:
    /** Default constructor **/
    FrsRatesSpill();

    /** Standard constructor **/
    FrsRatesSpill(const char* name, Int_t iVerbose = 1);

    /** Destructor **/
    virtual ~FrsRatesSpill();

    /** Virtual method Exec **/
    virtual void Exec(Option_t* option);

    /** Virtual method Reset **/
    virtual void Reset();

    // Fair specific
    /** Virtual method Init **/
    virtual InitStatus Init();

    /** Virtual method ReInit **/
    virtual InitStatus ReInit();

    /** Virtual method Finish **/
    virtual void Finish();

    /** Accessor to select online mode **/
    void SetOnline(Bool_t option) { fOnline = option; }

  private:
    Int_t fspill;
    Int_t fstart;
    Int_t firststart;
    Int_t fstop;
    Int_t firststop;

    // clocks
    Int_t fclock1hz;
    Int_t fclock10hz;
    Int_t fclock100khz;
    Int_t firstclock1hz;
    Int_t firstclock10hz;
    Int_t firstclock100khz;

    // Triggers
    Int_t faceptrigcounts;
    Int_t faceptrigcounter;
    Int_t ffreetrigcounts;
    Int_t ffreetrigcounter;

    // seetram
    Int_t fseecounts;
    Int_t fseecounter;

    // IC
    Int_t ficcounts;
    Int_t ficcounter;

    // sci00
    Int_t fsci00counts;
    Int_t fsci00counter;

    // sci01
    Int_t fsci01counts;
    Int_t fsci01counter;

    // sci02
    Int_t fsci02counts;
    Int_t fsci02counter;

    // dummy
    Int_t fdumcounts;
    Int_t fdumcounter;

    // sci21
    Int_t fsci21counts;
    Int_t fsci21counter;

    // sci41
    Int_t fsci41counts;
    Int_t fsci41counter;

    Bool_t firstEvt;

    Bool_t fOnline; // Don't store data for online

    TClonesArray* fFrsMappedDataCA; /**< Array with FRS Mapped- input data. >*/
    TClonesArray* fSpillCalDataCA;  /**< Array with output data. >*/

    /** Private method AddCalData **/
    //** Adds a SeetramCalData to the CalCollection
    R3BSeetramCalData* AddCalData(Int_t acctrigger,
                                  Int_t freetrigger,
                                  Int_t Seecounts,
                                  Int_t IcCounts,
                                  Int_t DumCounts,
                                  Int_t Sci00Counts,
                                  Int_t Sci01Counts,
                                  Int_t Sci02Counts,
                                  Int_t clock1seg);

  public:
    // Class definition
    ClassDef(FrsRatesSpill, 1)
};

#endif

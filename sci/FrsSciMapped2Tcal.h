// *** *************************************************************** *** //
// ***                  FrsSciMapped2Tcal                           *** //
// ***    convert Mapped data to tcal data                             *** //
// ***    from the fine and coarse times, calculate a raw time in ns   *** //
// *** *************************************************************** *** //

#ifndef _FrsSciMapped2Tcal_
#define _FrsSciMapped2Tcal_

#include "FairTask.h"

// ROOT headers
#include "TClonesArray.h"
#include "TMath.h"
#include "TRandom.h"
class TRandom3;

// Fair headers
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"

// FrsSci headers
#include "VftxSciMappedData.h"
#include "FrsSciTcalData.h"
#include "FrsSciTcalPar.h"

class FrsSciMapped2Tcal : public FairTask
{

  public:
    // --- Default constructor --- //
    FrsSciMapped2Tcal();

    // --- Standard constructor --- //
    FrsSciMapped2Tcal(const char* name, Int_t iVerbose = 1);

    // --- Destructor --- //
    virtual ~FrsSciMapped2Tcal();

    virtual void Exec(Option_t* option);

    virtual void SetParContainers();

    virtual InitStatus Init();

    virtual InitStatus ReInit();

    virtual void Finish();

    /** Virtual method Reset **/
    virtual void Reset();

    void SetOnline(Bool_t option) { fOnline = option; }

    Double_t CalculateTimeNs(UShort_t det, UShort_t pmt, UInt_t tf, UInt_t tc);

  private:
    Bool_t fOnline; // Don't store data for online

    TClonesArray* fMapped;   // input data - FrsSci
    FrsSciTcalPar* fTcalPar; // tcal parameters container - FrsSci
    TClonesArray* fTcal;     // output data

    UInt_t fNumTcal; // number of Tcal items per event
    UInt_t fNevent;

    TRandom rand;

    /** Private method CalData **/
    //** Adds a CalData to the detector
    FrsSciTcalData* AddCalData(Int_t iDet, Int_t iCh, Double_t tns);

  public:
    ClassDef(FrsSciMapped2Tcal, 1)
};

#endif // _FrsSciMapped2Tcal_

// ----------------------------------------------------------------------
// -----                                                            -----
// -----                     R3BTpcCal2Hit                          -----
// -----             Created 29/07/18  by J.L. Rodriguez-Sanchez    -----
// ----------------------------------------------------------------------

#ifndef R3BTpcCal2Hit_H
#define R3BTpcCal2Hit_H

#include "FairTask.h"
#include "R3BTpcCalData.h"
#include "R3BTpcHitData.h"
#include "TH1F.h"

#include <TRandom.h>

class TClonesArray;
class R3BTpcCalPar;

class R3BTpcCal2Hit : public FairTask
{

  public:
    /** Default constructor **/
    R3BTpcCal2Hit();

    /** Standard constructor **/
    R3BTpcCal2Hit(const char* name, Int_t iVerbose = 1);

    /** Destructor **/
    virtual ~R3BTpcCal2Hit();

    /** Virtual method Exec **/
    virtual void Exec(Option_t* option);

    /** Virtual method Reset **/
    virtual void Reset();

    virtual void SetParContainers();

    // Fair specific
    /** Virtual method Init **/
    virtual InitStatus Init();

    /** Virtual method ReInit **/
    virtual InitStatus ReInit();

    /** Virtual method Finish **/
    virtual void Finish();

    /** Accessor to select online mode **/
    void SetOnline(Bool_t option) { fOnline = option; }

    /** Accessor functions **/
    const Int_t GetNumDetectors() { return fNumDets; }
    void SetNumDetectors(Int_t numberDet) { fNumDets = numberDet; }

  private:
    void SetParameter();

    Int_t fNumDets;

    Bool_t fOnline; // Don't store data for online

    R3BTpcCalPar* fCal_Par; /**< Parameter container. >*/

    TClonesArray* fTpcCalDataCA; /**< Array with TPC Cal- input data. >*/
    TClonesArray* fTpcHitDataCA; /**< Array with TPC Hit- output data. >*/

    /** Private method TpcHitData **/
    //** Adds a TpcHitData to the detector
    R3BTpcHitData* AddHitData(Int_t detid, Double_t x, Double_t y);

  public:
    // Class definition
    ClassDef(R3BTpcCal2Hit, 1)
};

#endif

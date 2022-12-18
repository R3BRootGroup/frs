// ----------------------------------------------------------------------
// -----                                                            -----
// -----                     R3BMWMapped2Hit                        -----
// -----             Created 27/03/19  by J.L. Rodriguez-Sanchez    -----
// ----------------------------------------------------------------------

#ifndef R3BMWMapped2Hit_H
#define R3BMWMapped2Hit_H

#include "FairTask.h"
#include "R3BMwHitData.h"

class TClonesArray;

class R3BMWMapped2Hit : public FairTask
{

  public:
    /** Default constructor **/
    R3BMWMapped2Hit();

    /** Standard constructor **/
    R3BMWMapped2Hit(const char* name, Int_t iVerbose = 1);

    /** Destructor **/
    virtual ~R3BMWMapped2Hit();

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
    void MakeHit(TClonesArray* fMwMappedData);

    Int_t fNumDets;

    Bool_t fOnline;   // Don't store data for online

    TClonesArray* fMw11MappedDataCA; /**< Array with MW Mapped- input data. >*/
    TClonesArray* fMw21MappedDataCA;
    TClonesArray* fMw22MappedDataCA;
    TClonesArray* fMw31MappedDataCA;
    TClonesArray* fMw51MappedDataCA;
    TClonesArray* fMw71MappedDataCA;
    TClonesArray* fMw81MappedDataCA;
    TClonesArray* fMw82MappedDataCA;

    TClonesArray* fMwHitDataCA; /**< Array with MW Hit- output data.   >*/

    /** Private method MwHitData **/
    //** Adds a MwHitData to the detector
    R3BMwHitData* AddHitData(Int_t detid, Double_t x, Double_t y);

    Double_t gain_tdc[5][13];
    Double_t x_factor[13], x_offset[13];
    Double_t y_factor[13], y_offset[13];

  public:
    // Class definition
    ClassDef(R3BMWMapped2Hit, 1)
};

#endif

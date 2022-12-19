// ----------------------------------------------------------------------
// -----                                                            -----
// -----                     R3BTpcMapped2Cal                       -----
// -----             Created 22/07/18  by J.L. Rodriguez-Sanchez    -----
// ----------------------------------------------------------------------

#ifndef R3BTpcMapped2Cal_H
#define R3BTpcMapped2Cal_H

#include "FairTask.h"
#include "R3BTpcCalData.h"
#include "R3BTpcMappedData.h"
#include "TH1F.h"

class TClonesArray;
class R3BTpcCalPar;

class R3BTpcMapped2Cal : public FairTask
{

  public:
    /** Default constructor **/
    R3BTpcMapped2Cal();

    /** Standard constructor **/
    R3BTpcMapped2Cal(const char* name, Int_t iVerbose = 1);

    /** Destructor **/
    virtual ~R3BTpcMapped2Cal();

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

  private:
    void SetParameter();

    Int_t NumDets; // Number of TPCs
    Int_t NumAnodes;
    Int_t NumParams;

    Int_t fNumAnodesX;
    Int_t fNumAnodesY;

    TArrayF* CalParams;
    TArrayF* CsumMaxParams;
    TArrayF* CsumMinParams;

    Bool_t fOnline; // Don't store data for online

    R3BTpcCalPar* fCal_Par;         // Parameter container.
    TClonesArray* fTpcMappedDataCA; // Array with Tpc Mapped- input data.
    TClonesArray* fTpcCalDataCA;    // Array with Tpc Cal- output data.

    Bool_t b_tpc_csum[4]; // for tpcs control sum
    Bool_t b_tpc_xy[6];
    Float_t tpc_csum[4];

    Int_t fTpcdt[4], fTpclt[2], fTpcrt[2];

    /** Private method AddCalData **/
    //** Adds a TpcCalData to the anodeCalCollection
    R3BTpcCalData* AddCalData(Int_t detId, Int_t xyId, Int_t secId, Double_t position, Double_t controlpar);

  public:
    // Class definition
    ClassDef(R3BTpcMapped2Cal, 1)
};

#endif

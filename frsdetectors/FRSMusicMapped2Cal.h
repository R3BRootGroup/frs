// ----------------------------------------------------------------------
// -----                                                            -----
// -----                     FRSMusicMapped2Cal                     -----
// -----             Created 22/07/18  by J.L. Rodriguez-Sanchez    -----
// ----------------------------------------------------------------------

#ifndef FRSMusicMapped2Cal_H
#define FRSMusicMapped2Cal_H

#include "FRSMusicCalData.h"
#include "FRSMusicMappedData.h"
#include "FairTask.h"
#include "TH1F.h"

#include <TRandom.h>

class TClonesArray;
class FRSMusicCalPar;

class FRSMusicMapped2Cal : public FairTask
{

  public:
    /** Default constructor **/
    FRSMusicMapped2Cal();

    /** Standard constructor **/
    FRSMusicMapped2Cal(const char* name, Int_t iVerbose = 1);

    /** Destructor **/
    virtual ~FRSMusicMapped2Cal();

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

    Int_t NumDets;
    Int_t NumAnodes;
    Int_t NumParams;
    Int_t MaxSigma;
    TArrayF* CalParams;

    Bool_t fOnline; // Don't store data for online

    FRSMusicCalPar* fCal_Par;         /**< Parameter container. >*/
    TClonesArray* fMusicMappedDataCA; /**< Array with Music Mapped-input data. >*/
    TClonesArray* fMusicCalDataCA;    /**< Array with Music Cal-output data. >*/

    /** Private method AddCalData **/
    //** Adds a FRSMusicCalData to the anodeCalCollection
    FRSMusicCalData* AddCalData(Int_t detid, Int_t anodeid, Double_t energy);

  public:
    // Class definition
    ClassDef(FRSMusicMapped2Cal, 1)
};

#endif

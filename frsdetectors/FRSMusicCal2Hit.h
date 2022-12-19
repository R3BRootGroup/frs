// ----------------------------------------------------------------------
// -----                                                            -----
// -----                     FRSMusicCal2Hit                     -----
// -----             Created 22/07/18  by J.L. Rodriguez-Sanchez    -----
// ----------------------------------------------------------------------

#ifndef FRSMusicCal2Hit_H
#define FRSMusicCal2Hit_H

#include "FRSMusicCal2HitPar.h"
#include "FRSMusicCalData.h"
#include "FRSMusicHitData.h"
#include "FairTask.h"
#include "TH1F.h"

#include <TRandom.h>

class TClonesArray;
class FRSMusicHitPar;

class FRSMusicCal2Hit : public FairTask
{

  public:
    /** Default constructor **/
    FRSMusicCal2Hit();

    /** Standard constructor **/
    FRSMusicCal2Hit(const char* name, Int_t iVerbose = 1);

    /** Destructor **/
    virtual ~FRSMusicCal2Hit();

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

    /** Method to select online mode **/
    void SetOnline(Bool_t option) { fOnline = option; }

  private:
    void SetParameter();

    Int_t NumDets; // Number of Musics
    Int_t NumAnodes;
    Int_t NumParams;
    Int_t MaxSigma;
    TArrayF* CalParams;

    Bool_t fOnline; // Don't store data for online

    FRSMusicHitPar* fCal_Par;      /**< Parameter container. >*/
    TClonesArray* fMusicCalDataCA; /**< Array with Music Cal- input data. >*/
    TClonesArray* fMusicHitDataCA; /**< Array with Music Hit- output data. >*/

    /** Private method FRSMusicHitData **/
    //** Adds a FRSMusicHitData to the detector
    FRSMusicHitData* AddHitData(Int_t detid, Double_t charge);

  public:
    // Class definition
    ClassDef(FRSMusicCal2Hit, 1)
};

#endif

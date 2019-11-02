// ----------------------------------------------------------------------
// -----                                                            -----
// -----                     R3BMusicCal2Hit                     -----
// -----             Created 22/07/18  by J.L. Rodriguez-Sanchez    -----
// ----------------------------------------------------------------------

#ifndef R3BMusicCal2Hit_H
#define R3BMusicCal2Hit_H

#include "FairTask.h"
#include "R3BMusicCal2HitPar.h"
#include "R3BMusicCalData.h"
#include "R3BMusicHitData.h"
#include "TH1F.h"
#include <TRandom.h>

class TClonesArray;
class R3BMusicHitPar;

class R3BMusicCal2Hit : public FairTask
{

  public:
    /** Default constructor **/
    R3BMusicCal2Hit();

    /** Standard constructor **/
    R3BMusicCal2Hit(const char* name, Int_t iVerbose = 1);

    /** Destructor **/
    virtual ~R3BMusicCal2Hit();

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

    R3BMusicHitPar* fCal_Par;      /**< Parameter container. >*/
    TClonesArray* fMusicCalDataCA; /**< Array with Music Cal- input data. >*/
    TClonesArray* fMusicHitDataCA; /**< Array with Music Hit- output data. >*/

    /** Private method MusicHitData **/
    //** Adds a MusicHitData to the detector
    R3BMusicHitData* AddHitData(Int_t detid, Double_t charge);

  public:
    // Class definition
    ClassDef(R3BMusicCal2Hit, 1)
};

#endif

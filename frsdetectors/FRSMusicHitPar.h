// ------------------------------------------------------------------
// -----            FRSMusicHitPar source file                  -----
// -----         Created 29/05/18  by J.L. Rodriguez-Sanchez    -----
// ------------------------------------------------------------------

#ifndef FRSMusicHitPar_H
#define FRSMusicHitPar_H

#include "FairParGenericSet.h" // for FairParGenericSet
#include "TArrayF.h"
#include "TObjArray.h"
#include "TObject.h"

#include <TObjString.h>

using namespace std;

class FairParamList;

class FRSMusicHitPar : public FairParGenericSet
{

  public:
    /** Standard constructor **/
    FRSMusicHitPar(const char* name = "frsmusicHitPar",
                   const char* title = "FRS MUSIC Hit Parameters",
                   const char* context = "FRSMUSICHitParContext");

    /** Destructor **/
    virtual ~FRSMusicHitPar();

    /** Method to reset all parameters **/
    virtual void clear();

    /** Method to store all parameters using FairRuntimeDB **/
    virtual void putParams(FairParamList* list);

    /** Method to retrieve all parameters using FairRuntimeDB**/
    Bool_t getParams(FairParamList* list);

    /** Method to print values of parameters to the standard output **/
    void printParams();

    /** Accessor functions **/
    const Double_t GetNumDets() { return fNumDets; }
    const Double_t GetNumParametersFit() { return fNumParamsFit; }
    TArrayF* GetDetectorHitParams() { return fDetHitParams; }

    void SetNumDets(Int_t numberDets) { fNumDets = numberDets; }
    void SetNumParametersFit(Int_t numberParams) { fNumParamsFit = numberParams; }
    void SetDetectorHitParams(Double_t cc, Int_t ii) { fDetHitParams->AddAt(cc, ii); }

    /** Create more Methods if you need them! **/

  private:
    TArrayF* fDetHitParams; // Calibration Parameters for detector
    Int_t fNumDets;         // number of detectors
    Int_t fNumParamsFit;    /* number of cal parameters in the fit
                 gaus: A_fit & B_fit & C_fit*/

    const FRSMusicHitPar& operator=(const FRSMusicHitPar&); /*< an assignment operator>*/

    FRSMusicHitPar(const FRSMusicHitPar&); /*< a copy constructor >*/

    ClassDef(FRSMusicHitPar, 1);
};

#endif

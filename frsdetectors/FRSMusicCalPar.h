// ------------------------------------------------------------------
// -----            FRSMusicCalPar source file                  -----
// -----         Created 29/05/18  by J.L. Rodriguez-Sanchez    -----
// ------------------------------------------------------------------

#ifndef FRSMusicCalPar_H
#define FRSMusicCalPar_H

#include "FairParGenericSet.h" // for FairParGenericSet
#include "TArrayF.h"
#include "TObjArray.h"
#include "TObject.h"

#include <TObjString.h>

using namespace std;

class FairParamList;

class FRSMusicCalPar : public FairParGenericSet
{

  public:
    /** Standard constructor **/
    FRSMusicCalPar(const char* name = "frsmusicCalPar",
                   const char* title = "FRS MUSIC Parameters",
                   const char* context = "FRSMUSICCalParContext");

    /** Destructor **/
    virtual ~FRSMusicCalPar();

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
    const Double_t GetNumAnodes() { return fNumAnodes; }
    const Double_t GetNumParametersFit() { return fNumParamsFit; }
    TArrayF* GetAnodeCalParams() { return fAnodeCalParams; }

    void SetNumDets(Int_t numberDets) { fNumDets = numberDets; }
    void SetNumAnodes(Int_t numberAnodes) { fNumAnodes = numberAnodes; }
    void SetNumParametersFit(Int_t numberParams) { fNumParamsFit = numberParams; }
    void SetAnodeCalParams(Double_t cc, Int_t ii) { fAnodeCalParams->AddAt(cc, ii); }

    /** Create more Methods if you need them! **/

  private:
    TArrayF* fAnodeCalParams; // Calibration Parameters for anodes
    Int_t fNumDets;           // number of detectors
    Int_t fNumAnodes;         // number of anodes
    Int_t fNumParamsFit;      /* number of cal parameters in the fit
                                 gaus: A_fit & B_fit & C_fit*/

    const FRSMusicCalPar& operator=(const FRSMusicCalPar&); /*< an assignment operator>*/

    FRSMusicCalPar(const FRSMusicCalPar&); /*< a copy constructor >*/

    ClassDef(FRSMusicCalPar, 1);
};

#endif

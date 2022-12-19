// ------------------------------------------------------------------
// -----              R3BSeetramCalPar source file              -----
// -----         Created 15/07/18  by J.L. Rodriguez-Sanchez    -----
// ------------------------------------------------------------------

#ifndef R3BSeetramCalPar_H
#define R3BSeetramCalPar_H

#include "FairParGenericSet.h"
#include "TArrayF.h"
#include "TObjArray.h"
#include "TObject.h"

#include <TObjString.h>

using namespace std;

class FairParamList;

class R3BSeetramCalPar : public FairParGenericSet
{

  public:
    /** Standard constructor **/
    R3BSeetramCalPar(const char* name = "seetramCalPar",
                     const char* title = "Seetram Parameters",
                     const char* context = "SeetramCalParContext");

    /** Destructor **/
    virtual ~R3BSeetramCalPar();

    /** Method to reset all parameters **/
    virtual void clear();

    /** Method to store all parameters using FairRuntimeDB **/
    virtual void putParams(FairParamList* list);

    /** Method to retrieve all parameters using FairRuntimeDB**/
    Bool_t getParams(FairParamList* list);

    /** Method to print values of parameters to the standard output **/
    void printParams();

    /** Accessor functions **/
    const Double_t GetNumParametersFit() { return fNumParamsFit; }
    TArrayF* GetSeetramCalParams() { return fSeetramCalParams; }

    void SetNumParametersFit(Int_t numberParams) { fNumParamsFit = numberParams; }
    void SetSeetramCalParams(Double_t cc, Int_t ii) { fSeetramCalParams->AddAt(cc, ii); }

    /** Create more Methods if you need them! **/

  private:
    TArrayF* fSeetramCalParams; // Calibration Parameters
    Int_t fNumParamsFit;

    const R3BSeetramCalPar& operator=(const R3BSeetramCalPar&); /*< an assignment operator>*/

    R3BSeetramCalPar(const R3BSeetramCalPar&); /*< a copy constructor >*/

    ClassDef(R3BSeetramCalPar, 1);
};

#endif

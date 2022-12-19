// ------------------------------------------------------------------
// -----               R3BTpcCalPar source file                 -----
// -----       Created 29/07/18  by J.L. Rodriguez-Sanchez      -----
// ------------------------------------------------------------------

#ifndef R3BTpcCalPar_H
#define R3BTpcCalPar_H

#include "FairParGenericSet.h" // for FairParGenericSet
#include "TArrayF.h"
#include "TObjArray.h"
#include "TObject.h"

#include <TObjString.h>

using namespace std;

class FairParamList;

class R3BTpcCalPar : public FairParGenericSet
{

  public:
    /** Standard constructor **/
    R3BTpcCalPar(const char* name = "tpcCalPar",
                 const char* title = "TPC Parameters",
                 const char* context = "TPCCalParContext");

    /** Destructor **/
    virtual ~R3BTpcCalPar();

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
    const Double_t GetNumDT() { return fNumDT; }
    const Double_t GetNumParametersFit() { return fNumParamsFit; }
    TArrayF* GetTpcCalParams() { return fTpcCalParams; }
    TArrayF* GetTpcCsumMaxParams() { return fTpcCsumMaxParams; }
    TArrayF* GetTpcCsumMinParams() { return fTpcCsumMinParams; }

    void SetNumDets(Int_t numberDets) { fNumDets = numberDets; }
    void SetNumDT(Int_t numberdts) { fNumDT = numberdts; }
    void SetNumParametersFit(Int_t numberParams) { fNumParamsFit = numberParams; }
    void SetTpcCalParams(Double_t cc, Int_t ii) { fTpcCalParams->AddAt(cc, ii); }
    void SetTpcCsumMaxParams(Double_t cc, Int_t ii) { fTpcCsumMaxParams->AddAt(cc, ii); }
    void SetTpcCsumMinParams(Double_t cc, Int_t ii) { fTpcCsumMinParams->AddAt(cc, ii); }

    /** Create more Methods if you need them! **/

  private:
    TArrayF* fTpcCalParams;     // Calibration Parameters for anodes
    TArrayF* fTpcCsumMaxParams; // Maximum Csum Parameters for TPCs
    TArrayF* fTpcCsumMinParams; // Minimum Csum Parameters for TPCs
    Int_t fNumDets;             // number of detectors
    Int_t fNumDT;               // number of anodes
    Int_t fNumParamsFit;        /* number of cal parameters in the fit
                      gaus: A_fit & B_fit & C_fit*/

    const R3BTpcCalPar& operator=(const R3BTpcCalPar&); /*< an assignment operator>*/

    R3BTpcCalPar(const R3BTpcCalPar&); /*< a copy constructor >*/

    ClassDef(R3BTpcCalPar, 2);
};

#endif

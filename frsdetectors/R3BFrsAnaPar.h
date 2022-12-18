// ------------------------------------------------------------------
// -----         R3BFrsAnaPar source file                       -----
// -----         Created 29/07/18  by J.L. Rodriguez-Sanchez    -----
// ------------------------------------------------------------------

#ifndef R3BFrsAnaPar_H
#define R3BFrsAnaPar_H

#include "FairParGenericSet.h"   // for FairParGenericSet
#include "TArrayF.h"
#include "TObjArray.h"
#include "TObject.h"

#include <TObjString.h>

using namespace std;

class FairParamList;

class R3BFrsAnaPar : public FairParGenericSet
{

  public:
    /** Standard constructor **/
    R3BFrsAnaPar(const char* name = "frsAnaPar",
                 const char* title = "FRS S2-S4 Parameters",
                 const char* context = "FRSANAParContext");

    /** Destructor **/
    virtual ~R3BFrsAnaPar();

    /** Method to reset all parameters **/
    virtual void clear();

    /** Method to store all parameters using FairRuntimeDB **/
    virtual void putParams(FairParamList* list);

    /** Method to retrieve all parameters using FairRuntimeDB**/
    Bool_t getParams(FairParamList* list);

    /** Method to print values of parameters to the standard output **/
    void printParams();

    /** Accessor functions **/
    const Int_t GetNumParameters() { return fNumParams; }
    const Double_t GetMagnificationS2S4() { return fMagS2S4; }
    const Double_t GetDispersionS2S4() { return fDispS2S4; }
    const Double_t GetPathS2S4() { return fPathS2S4; }
    const Double_t GetTOFS2S4() { return fTOFS2S4; }
    const Double_t GetDistTpcS2() { return fDisTpcS2; }
    const Double_t GetDistTpcS4() { return fDisTpcS4; }
    const Double_t GetRhoS0S2() { return frho_S0_S2; }
    const Double_t GetRhoS2S4() { return frho_S2_S4; }
    const Double_t GetBfiedS0S2() { return fBfield_S0_S2; }
    const Double_t GetBfiedS2S4() { return fBfield_S2_S4; }
    const Double_t GetPosFocalS2() { return fPosFocalS2; }
    const Double_t GetPosFocalS4() { return fPosFocalS4; }

    TArrayF* GetFrsAnaParams() { return fAnaParams; }

    void SetNumParameters(Int_t numberParams) { fNumParams = numberParams; }
    void SetMagnificationS2S4(Double_t theMag) { fMagS2S4 = theMag; }
    void SetDispersionS2S4(Double_t theDisp) { fDispS2S4 = theDisp; }
    void SetPathS2S4(Double_t thePath) { fPathS2S4 = thePath; }
    void SetTOFS2S4(Double_t theTOF) { fTOFS2S4 = theTOF; }
    void SetDistTpcS2(Double_t theDis) { fDisTpcS2 = theDis; }
    void SetDistTpcS4(Double_t theDis) { fDisTpcS4 = theDis; }
    void SetRhoS0S2(Double_t theRho) { frho_S0_S2 = theRho; }
    void SetRhoS2S4(Double_t theRho) { frho_S2_S4 = theRho; }
    void SetBfiedS0S2(Double_t theB) { fBfield_S0_S2 = theB; }
    void SetBfiedS2S4(Double_t theB) { fBfield_S2_S4 = theB; }
    void SetPosFocalS2(Double_t thePos) { fPosFocalS2 = thePos; }
    void SetPosFocalS4(Double_t thePos) { fPosFocalS4 = thePos; }

    void SetFrsAnaParams(Double_t cc, Int_t ii) { fAnaParams->AddAt(cc, ii); }

    /** Create more Methods if you need them! **/

  private:
    TArrayF* fAnaParams;   // Parameters for frs
                           // Int_t fNumDets;        // number of detectors
    Int_t fNumParams;      /* number of cal parameters in the fit*/

    Double_t fMagS2S4;
    Double_t fDispS2S4;
    Double_t fPathS2S4, fTOFS2S4;
    Double_t fDisTpcS2, fDisTpcS4, fPosFocalS2, fPosFocalS4;
    Double_t frho_S0_S2, fBfield_S0_S2, frho_S2_S4, fBfield_S2_S4;

    const R3BFrsAnaPar& operator=(const R3BFrsAnaPar&); /*< an assignment operator>*/

    R3BFrsAnaPar(const R3BFrsAnaPar&); /*< a copy constructor >*/

    ClassDef(R3BFrsAnaPar, 1);
};

#endif

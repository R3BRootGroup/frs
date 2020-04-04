#ifndef __FrsSciRawTofPar_H__
#define __FrsSciRawTofPar_H__

#include "FairParGenericSet.h" // for FairParGenericSet
#include "TArrayF.h"
#include "TObjArray.h"
#include "TObject.h"
#include <TObjString.h>

class FairParamList;

class FrsSciRawTofPar : public FairParGenericSet
{

  public:
    /** Standard constructor **/
    FrsSciRawTofPar(const char* name = "FrsSciRawTofPar",
                       const char* title = "FrsSciRawTof Parameters",
                       const char* context = "FrsSciRawTofParContext");

    /** Destructor **/
    virtual ~FrsSciRawTofPar();

    /** Method to reset all parameters **/
    virtual void clear();

    /** Method to store all parameters using FairRuntimeDB **/
    virtual void putParams(FairParamList* list);

    /** Method to retrieve all parameters using FairRuntimeDB**/
    Bool_t getParams(FairParamList* list);

    /** Method to print values of parameters to the standard output **/
    void printParams();

    /** Accessor functions **/
    const Int_t GetFirstStart() { return fFirstStaSci; }
    const Int_t GetNumSignals() { return fNumSignals; }
    const Double_t GetNumParsPerSignal() { return fNumParsPerSignal; }
    TArrayF* GetAllSignalsRawTofParams() { return fAllSignalsRawTofParams; }
    Double_t GetSignalRawTofParams(UInt_t rank) { return (Double_t)fAllSignalsRawTofParams->GetAt(rank); }

    void SetFirstStart(Int_t detFirstStart) { fFirstStaSci = detFirstStart; }
    void SetNumSignals(Int_t nsig) { fNumSignals = nsig; }
    void SetNumParsPerSignal(Int_t npars) { fNumParsPerSignal = npars; }
    void SetSignalParams(Double_t parval, UInt_t rank) { fAllSignalsRawTofParams->AddAt(parval, rank); }

  private:
    TArrayF* fAllSignalsRawTofParams; // Calibration Parameters for all signals of one detector
    Int_t fFirstStaSci;      // if nDets>2, start the mult selection with detectors number fFirstStaSci (1-based)
    Int_t fNumSignals;       // = number of Tof spectra with mult=1 = NUMBER_OF_SCI_DETECTORs-1
    Int_t fNumParsPerSignal; // = 2
    const FrsSciRawTofPar& operator=(const FrsSciRawTofPar&);
    FrsSciRawTofPar(const FrsSciRawTofPar&); // a copy constructor

    ClassDef(FrsSciRawTofPar, 1);
};

#endif //__FrsSciRawTofPar_H__

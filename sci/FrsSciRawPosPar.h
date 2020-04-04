#ifndef __FrsSciRawPosPar_H__
#define __FrsSciRawPosPar_H__

#include "FairParGenericSet.h" // for FairParGenericSet

#include "TArrayF.h"
#include "TObjArray.h"
#include "TObject.h"
#include <TObjString.h>

class FairParamList;

class FrsSciRawPosPar : public FairParGenericSet
{

  public:
    /** Standard constructor **/
    FrsSciRawPosPar(const char* name = "FrsSciRawPosPar",
                       const char* title = "FrsSciRawPos Parameters",
                       const char* context = "FrsSciPosParContext");

    /** Destructor **/
    virtual ~FrsSciRawPosPar();

    /** Method to reset all parameters **/
    virtual void clear();

    /** Method to store all parameters using FairRuntimeDB **/
    virtual void putParams(FairParamList* list);

    /** Method to retrieve all parameters using FairRuntimeDB**/
    Bool_t getParams(FairParamList* list);

    /** Method to print values of parameters to the standard output **/
    void printParams();

    /** Accessor functions **/
    const Double_t GetNumDetectors() { return fNumDetectors; }
    const Double_t GetNumChannels() { return fNumChannels; }
    const Double_t GetNumSignals() { return fNumSignals; }
    const Double_t GetNumParsPerSignal() { return fNumParsPerSignal; }
    TArrayF* GetAllSignalsTcalParams() { return fAllSignalsRawPosParams; }
    Double_t GetSignalTcalParams(UInt_t rank) { return (Double_t)fAllSignalsRawPosParams->GetAt(rank); }

    void SetNumDetectors(Int_t ndets) { fNumDetectors = ndets; }
    void SetNumChannels(Int_t nchs) { fNumChannels = nchs; }
    void SetNumSignals(Int_t ndets) { fNumSignals = ndets; }
    void SetNumParsPerSignal(Int_t npars) { fNumParsPerSignal = npars; }
    void SetSignalParams(Double_t parval, UInt_t rank) { fAllSignalsRawPosParams->AddAt(parval, rank); }

    /** Create more Methods if you need them! **/

  private:
    TArrayF* fAllSignalsRawPosParams; // Calibration Parameters for all signals of one detector
    Int_t fNumChannels;               // number of detectors
    Int_t fNumDetectors;              // number of channels of SciTcal data = 3 (need for Tcal2SingleTcal)
    Int_t fNumSignals;                // =fNumDetectors if RawPos
    Int_t fNumParsPerSignal;
    const FrsSciRawPosPar& operator=(const FrsSciRawPosPar&); /*< an assignment operator>*/

    FrsSciRawPosPar(const FrsSciRawPosPar&); // a copy constructor

    ClassDef(FrsSciRawPosPar, 1);
};

#endif //__FrsSciRawPosPar_H__

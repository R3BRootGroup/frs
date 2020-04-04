#ifndef __FrsSciTcalPar_H__
#define __FrsSciTcalPar_H__

#include "FairParGenericSet.h" // for FairParGenericSet

#include "TArrayF.h"
#include "TObjArray.h"
#include "TObject.h"
#include <TObjString.h>

class FairParamList;

class FrsSciTcalPar : public FairParGenericSet
{

  public:
    /** Standard constructor **/
    FrsSciTcalPar(const char* name = "FrsSciTcalPar",
                  const char* title = "FrsSciTcal Parameters",
                  const char* context = "FrsSciTcalParContext");

    /** Destructor **/
    virtual ~FrsSciTcalPar();

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
    const Double_t GetNumTcalParsPerSignal() { return fNumTcalParsPerSignal; }
    TArrayF* GetAllSignalsTcalParams() { return fAllSignalsTcalParams; }
    Double_t GetSignalTcalParams(UInt_t rank) { return (Double_t)fAllSignalsTcalParams->GetAt(rank); }

    void SetNumDetectors(Int_t NumberOfDetectors) { fNumDetectors = NumberOfDetectors; }
    void SetNumChannels(Int_t NumberOfChannels) { fNumChannels = NumberOfChannels; }
    void SetNumSignals(Int_t NumberOfDetectors, Int_t NumberOfChannels)
    {
        fNumSignals = NumberOfDetectors * NumberOfChannels;
    }
    void SetNumTcalParsPerSignal(Int_t NumberOfTcalParsPerSignal) { fNumTcalParsPerSignal = NumberOfTcalParsPerSignal; }
    void SetSignalTcalParams(Double_t ft_ns, UInt_t rank) { fAllSignalsTcalParams->AddAt(ft_ns, rank); }

    /** Create more Methods if you need them! **/

  private:
    TArrayF* fAllSignalsTcalParams; // Calibration Parameters for all signals of one detector
    Int_t fNumDetectors;            // number of detectors (=2 for Sci)
    Int_t fNumChannels;             // number of channels  (=2 for Sci)
    Int_t fNumSignals;              // =fNumDetectors * fNumChannels
    Int_t fNumTcalParsPerSignal;
    const FrsSciTcalPar& operator=(const FrsSciTcalPar&); /*< an assignment operator>*/

    FrsSciTcalPar(const FrsSciTcalPar&); // a copy constructor

    ClassDef(FrsSciTcalPar, 1);
};

#endif //__FrsSciTcalPar_H__

#ifndef __FrsSciTcal2RawPosPar_H__
#define __FrsSciTcal2RawPosPar_H__

#include "FairTask.h"
#include "TH1D.h"
#include "TH1F.h"

class TClonesArray;
class FrsSciRawPosPar;
class R3BEventHeader;

class FrsSciTcal2RawPosPar : public FairTask
{

  public:
    /** Default constructor **/
    FrsSciTcal2RawPosPar();

    /** Standard constructor **/
    FrsSciTcal2RawPosPar(const char* name, Int_t iVerbose = 1);

    /** Destructor **/
    virtual ~FrsSciTcal2RawPosPar();

    /** Virtual method Init **/
    virtual InitStatus Init();

    /** Virtual method Exec **/
    virtual void Exec(Option_t* opt);

    /** Virtual method FinishEvent **/
    virtual void FinishEvent();

    /** Virtual method FinishTask **/
    virtual void FinishTask();

    /** Virtual method Reset **/
    virtual void Reset();

    /** Virtual method ReInit **/
    virtual InitStatus ReInit();

    /** Virtual method calculate the PosRaw Single Tcal Parameters **/
    virtual void CalculateRawPosRawPosParams();

    void SetOutputFile(const char* outFile);

    /** Accessor functions **/
    const Double_t GetNumDetectors() { return fNumDetectors; }
    const Double_t GetNumChannels() { return fNumChannels; }
    const Double_t GetNumSignals() { return fNumSignals; }
    const Int_t GetMinStatistics() { return fMinStatistics; }

    void SetNumDetectors(Int_t n) { fNumDetectors = n; }
    void SetNumChannels(Int_t n) { fNumChannels = n; }
    void SetNumSignals()
    {
        if (fNumDetectors)
            fNumSignals = fNumDetectors;
    }
    void SetNumParsPerSignal(Int_t n) { fNumParsPerSignal = n; }
    void SetMinStatistics(Int_t minstat) { fMinStatistics = minstat; }

  protected:
    Int_t fNumDetectors;     // number of detectors 2
    Int_t fNumChannels;      // number of channels at the Tcal level
    Int_t fNumSignals;       // number of signal = fNumDetectors if RawPos used
    Int_t fNumParsPerSignal; // =2 for each signal
    Int_t fMinStatistics;    // minimum statistics to proceed with the calibration

    // calibration parameters
    FrsSciRawPosPar* fRawPosPar;

    // input data
    TClonesArray* fTcal;

    // histograms
    TH1D** fh_RawPosMult1;
    char* fOutputFile;

  public:
    ClassDef(FrsSciTcal2RawPosPar, 1);
};

#endif //__FrsSciTcal2RawPosPar_H__

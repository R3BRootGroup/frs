#ifndef __FrsSciMapped2TcalPar_H__
#define __FrsSciMapped2TcalPar_H__

#include "FairTask.h"
#include "TH1F.h"

class TClonesArray;
class FrsSciTcalPar;
class R3BEventHeader;

class FrsSciMapped2TcalPar : public FairTask
{

  public:
    /** Default constructor **/
    FrsSciMapped2TcalPar();

    /** Standard constructor **/
    FrsSciMapped2TcalPar(const char* name, Int_t iVerbose = 1);

    /** Destructor **/
    virtual ~FrsSciMapped2TcalPar();

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

    /** Virtual method calculate the Vftx Tcal Parameters **/
    virtual void CalculateVftxTcalParams();

    void SetOutputFile(const char* outFile);

    /** Accessor functions **/
    const Double_t GetNumDetectors() { return fNumDetectors; }
    const Double_t GetNumChannels() { return fNumChannels; }
    const Double_t GetNumSignals() { return fNumSignals; }
    const Int_t GetMinStatistics() { return fMinStatistics; }

    void SetNumDetectors(Int_t NumberOfDetectors) { fNumDetectors = NumberOfDetectors; }
    void SetNumChannels(Int_t NumberOfChannels) { fNumChannels = NumberOfChannels; }
    void SetNumSignals(Int_t NumberOfDetectors, Int_t NumberOfChannels)
    {

        fNumSignals = NumberOfDetectors * NumberOfChannels;
    }
    void SetNumTcalParsPerSignal(Int_t NumberOfTcalParsPerSignal) { fNumTcalParsPerSignal = NumberOfTcalParsPerSignal; }
    void SetMinStatistics(Int_t minstat) { fMinStatistics = minstat; }

  protected:
    Int_t fNumDetectors;         // number of detectors (=2 for Sci)
    Int_t fNumChannels;          // number of channels  (=2 for Sci)
    Int_t fNumSignals;           // number of signal    (=4 for Sci)
    Int_t fNumTcalParsPerSignal; // =1000 for each signal
    Int_t fMinStatistics;        // minimum statistics to proceed with the calibration

    // calibration parameters
    FrsSciTcalPar* fTcalPar; // Tcal Parameters

    // input data
    TClonesArray* fMapped; // Array with mapped data from scintillator detectors

    // histograms
    TH1F** fh_TimeFineBin;
    TH1F** fh_TimeFineNs;
    char* fOutputFile;

  public:
    ClassDef(FrsSciMapped2TcalPar, 0);
};

#endif //__FrsSciMapped2TcalPar_H__

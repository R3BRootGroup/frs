#ifndef __FrsSciTcal2RawTofPar_H__
#define __FrsSciTcal2RawTofPar_H__

#include "FairTask.h"
#include "TH1D.h"
#include "TH1F.h"


class TClonesArray;
class FrsSciRawTofPar;
class R3BEventHeader;

class FrsSciTcal2RawTofPar : public FairTask
{

  public:
    /** Default constructor **/
    FrsSciTcal2RawTofPar();

    /** Standard constructor **/
    FrsSciTcal2RawTofPar(const char* name, Int_t iVerbose = 1);

    /** Destructor **/
    virtual ~FrsSciTcal2RawTofPar();

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

    /** Virtual method calculate the TofRaw Single Tcal Parameters **/
    virtual void CalculateRawTofParams();

    void SetOutputFile(const char* outFile);

    /** Accessor functions **/
    const Int_t GetFirstStaSci() { return fFirstStaSci; }
    const Double_t GetNumSignals() { return fNumSignals; }
    const Int_t GetMinStatistics() { return fMinStatistics; }

    void SetFirstStaSci(Int_t firststa) { fFirstStaSci = firststa; }
    void SetNumSignals() { fNumSignals = fNumDetectors - 1; }
    void SetNumParsPerSignal(Int_t n) { fNumParsPerSignal = n; }
    void SetMinStatistics(Int_t minstat) { fMinStatistics = minstat; }

  protected:
    Int_t fNumDetectors;     // number of detectors 2
    Int_t fNumChannels;      // number of channels at the Tcal level
    Int_t fFirstStaSci;
    Int_t fNumSignals;       // number of signal = number of detector -1 (Tof selection from S2 to S4)
    Int_t fNumParsPerSignal; // =2 for each sci-pair
    Int_t fMinStatistics;    // minimum statistics to proceed to the calibration

    // calibration parameters
    FrsSciRawTofPar* fRawTofPar;

    // input data
    TClonesArray* fTcal;

    // histograms
    TH1D** fh_RawTofMult1;

  public:
    ClassDef(FrsSciTcal2RawTofPar, 0);
};

#endif //__FrsSciTcal2RawTofPar_H__

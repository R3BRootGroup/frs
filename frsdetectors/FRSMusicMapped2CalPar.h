// -------------------------------------------------------------------------
// -----              FRSMusicMapped2CalPar source file                -----
// -----           Created 29/05/18  by J.L. Rodriguez-Sanchez         -----
// -------------------------------------------------------------------------

#ifndef FRSMusicMapped2CalPar_H
#define FRSMusicMapped2CalPar_H

#include "FairTask.h"
#include "TH1F.h"

class TClonesArray;
class FRSMusicCalPar;
class R3BEventHeader;

class FRSMusicMapped2CalPar : public FairTask
{

  public:
    /** Default constructor **/
    FRSMusicMapped2CalPar();

    /** Standard constructor **/
    FRSMusicMapped2CalPar(const char* name, Int_t iVerbose = 1);

    /** Destructor **/
    virtual ~FRSMusicMapped2CalPar();

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

    /** Virtual method Search pedestals **/
    virtual void SearchPedestals();

    void SetOutputFile(const char* outFile);

    /** Accessor functions **/
    const Int_t GetNumDetectors() { return fNumDets; }
    const Int_t GetNumAnodes() { return fNumAnodes; }
    const Int_t GetCalRange_left() { return fMapHistos_left; }
    const Int_t GetCalRange_right() { return fMapHistos_right; }
    const Int_t GetCalRange_bins() { return fMapHistos_bins; }
    const Double_t GetSigma() { return fSigma; }
    const Double_t GetMean() { return fMean; }
    const Int_t GetMinStatistics() { return fMinStatistics; }
    const Int_t GetMaxSigma() { return fMaxSigma; }

    void SetNumDetectors(Int_t numberDet) { fNumDets = numberDet; }
    void SetNumAnodes(Int_t numberAnodes) { fNumAnodes = numberAnodes; }
    void SetCalRange_left(Int_t Histos_left) { fMapHistos_left = Histos_left; }
    void SetCalRange_right(Int_t Histos_right) { fMapHistos_right = Histos_right; }
    void SetCalRange_bins(Int_t Histos_bins) { fMapHistos_bins = Histos_bins; }
    void SetSigma(Double_t sigma) { fSigma = sigma; }
    void SetMean(Double_t mean) { fMean = mean; }
    void SetMinStatistics(Int_t minstat) { fMinStatistics = minstat; }
    void SetMaxSigma(Double_t sigma) { fMaxSigma = sigma; }

  protected:
    // Number of histograms, limits and bining
    Int_t fNumDets;
    Int_t fNumAnodes;
    Int_t fMapHistos_left;
    Int_t fMapHistos_right;
    Int_t fMapHistos_bins;
    Int_t fMaxSigma;   // Maximum sigma to mark dead anodes, pedestal -1

    // Minimum statistics and parameters
    Int_t fMinStatistics;
    Double_t fSigma;
    Double_t fMean;

    FRSMusicCalPar* fAnode_Par;       /**< Parameter container. >*/
    TClonesArray* fMusicMappedDataCA; /**< Array with Music Mapped input data. >*/

    TH1F** fh_Map_energy_anode;
    char* fOutputFile;

  public:
    ClassDef(FRSMusicMapped2CalPar, 0);
};

#endif

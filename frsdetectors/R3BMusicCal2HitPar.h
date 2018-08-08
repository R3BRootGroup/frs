// -------------------------------------------------------------------------
// -----         R3BMusicCal2HitPar source file                  -----
// -----             Created 29/05/18  by J.L. Rodriguez-Sanchez       -----
// -------------------------------------------------------------------------

#ifndef R3BMusicCal2HitPar_H
#define R3BMusicCal2HitPar_H

#include "FairTask.h"
#include "TH1F.h"

class TClonesArray;
class R3BMusicHitPar;
class R3BEventHeader;

class R3BMusicCal2HitPar : public FairTask {
  
 public:
  
  /** Default constructor **/
  R3BMusicCal2HitPar();
  
  /** Standard constructor **/
  R3BMusicCal2HitPar(const char* name, Int_t iVerbose=1);
  
  /** Destructor **/
  virtual ~R3BMusicCal2HitPar();
  
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
  
  /** Virtual method Search Zs **/
  virtual void SearchZ();
  
  void SetOutputFile(const char *outFile);
  
  /** Accessor functions **/
  const Int_t GetNumDetectors(){return fNumDets;}
  const Int_t GetCalRange_left(){return fMapHistos_left;}
  const Int_t GetCalRange_right(){return fMapHistos_right;}
  const Int_t GetCalRange_bins(){return fMapHistos_bins;}	 
  const Double_t GetSigma(){return fSigma;}
  const Double_t GetMean(){return fMean;}
  const Int_t GetMinStatistics(){return fMinStatistics;}
  const Int_t GetMaxSigma(){return fMaxSigma;}
  const Int_t GetMaxZ(){return fMaxZ;}
  
  void SetNumDetectors(Int_t numberDet){fNumDets=numberDet;}
  void SetCalRange_left(Int_t Histos_left){fMapHistos_left=Histos_left;}
  void SetCalRange_right(Int_t Histos_right){fMapHistos_right=Histos_right;}
  void SetCalRange_bins(Int_t Histos_bins){fMapHistos_bins=Histos_bins;}
  void SetSigma(Double_t sigma){fSigma=sigma;}
  void SetMean(Double_t mean){fMean=mean;}
  void SetMinStatistics(Int_t minstat){fMinStatistics=minstat;}
  void SetMaxSigma(Double_t sigma){fMaxSigma=sigma;}
  void SetMaxZ(Int_t MaxZ){fMaxZ=MaxZ;}

 protected:
  //Number of histograms, limits and bining
  Int_t fNumDets;
  Int_t fMapHistos_left;		
  Int_t fMapHistos_right;
  Int_t fMapHistos_bins;
  Int_t fMaxSigma;//Maximum sigma to mark dead anodes, pedestal -1
  Int_t fMaxZ;//Maximum atomic number (Z) for calibration

  //Minimum statistics and parameters
  Int_t fMinStatistics;
  Double_t fSigma;
  Double_t fMean;

  R3BMusicHitPar* fDet_Par;  /**< Parameter container. >*/ 
  TClonesArray* fMusicCalDataCA; /**< Array with Music Cal- input data. >*/

  TArrayF* fZPeaks;
  
  TH1F** fh_Cal_energy_det;
  char *fOutputFile;
  
 public:
  ClassDef(R3BMusicCal2HitPar,0);
};

#endif

// -------------------------------------------------------------------------
// -----              R3BTpcMapped2CalPar source file                  -----
// -----         Created 29/07/18  by J.L. Rodriguez-Sanchez           -----
// -------------------------------------------------------------------------

#ifndef R3BTpcMapped2CalPar_H
#define R3BTpcMapped2CalPar_H

#include "FairTask.h"
#include "TH1F.h"
#include "TH2F.h"

class TClonesArray;
class R3BTpcCalPar;
class R3BEventHeader;

class R3BTpcMapped2CalPar : public FairTask {
  
 public:
  
  /** Default constructor **/
  R3BTpcMapped2CalPar();
  
  /** Standard constructor **/
  R3BTpcMapped2CalPar(const char* name, Int_t iVerbose=1);
  
  /** Destructor **/
  virtual ~R3BTpcMapped2CalPar();
  
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
  
  /** Virtual method Search parameters **/
  virtual void SearchCalParXY();

  void SearchMax(double *xpeaks, double *ypeaks, int nf, double *xpos);
  
  void SetOutputFile(const char *outFile);
  
  /** Accessor functions **/
  const Int_t GetNumDetectors(){return fNumDets;}
  const Int_t GetNumAnodesX(){return fNumAnodesX;}
  const Int_t GetNumAnodesY(){return fNumAnodesY;}
  const Int_t GetCalRange_left(){return fMapHistos_left;}
  const Int_t GetCalRange_right(){return fMapHistos_right;}
  const Int_t GetCalRange_bins(){return fMapHistos_bins;}	 
  const Double_t GetDeltaX(){return fDeltaX;}
  const Double_t GetDeltaY(){return fDeltaY;}
  const Int_t GetMinStatistics(){return fMinStatistics;}

  TArrayF* GetMaxCsum() {return fLim_Csum_Max;}
  TArrayF* GetMinCsum() {return fLim_Csum_Min;}
  
  void SetNumDetectors(Int_t numberDet){fNumDets=numberDet;}
  void SetNumAnodesX(Int_t numberAnodes){fNumAnodesX=numberAnodes;}
  void SetNumAnodesY(Int_t numberAnodes){fNumAnodesY=numberAnodes;}
  void SetCalRange_left(Int_t Histos_left){fMapHistos_left=Histos_left;}
  void SetCalRange_right(Int_t Histos_right){fMapHistos_right=Histos_right;}
  void SetCalRange_bins(Int_t Histos_bins){fMapHistos_bins=Histos_bins;}
  void SetDeltaX(Double_t x){fDeltaX=x;}
  void SetDeltaY(Double_t y){fDeltaY=y;}
  void SetMinStatistics(Int_t minstat){fMinStatistics=minstat;}
  void SetMaxXCal(Int_t max){fMaxX=max;}

  void SetMaxCsum(TArrayF* theCsum) {
    fLim_Csum_Max = theCsum;
    fNbCsumLines = theCsum->GetSize();
  }

  void SetMinCsum(TArrayF* theCsum) {
    fLim_Csum_Min = theCsum;
    fNbCsumLines = theCsum->GetSize();
  }

 protected:
  //Number of histograms, limits and bining
  Int_t fNumDets;
  Int_t fNumAnodesX;
  Int_t fNumAnodesY;
  Int_t fMapHistos_left;		
  Int_t fMapHistos_right;
  Int_t fMapHistos_bins;
  Int_t fMaxX;

  TArrayF* fLim_Csum_Max;
  Int_t fNbCsumLines;
  TArrayF* fLim_Csum_Min;

  //Minimum statistics and parameters
  Int_t fMinStatistics;

  //Distance between TPC SCI fibers
  Double_t fDeltaX;//mm
  Double_t fDeltaY;//mm

  // TPC part
  Float_t lim_csum[6][6][2];
  Float_t lim_csum1[6][2];
  Float_t lim_csum2[6][2];// = {{1530,1800},{1430,1800},{1545,1800},{1575,1800},{1440,1800},{1410,1800}};
  Float_t lim_csum3[6][2];// = {{1540,1800},{1490,1840},{1540,1820},{1475,1840},{1410,1875},{1450,1820}};
  Float_t lim_csum4[6][2];// = {{1510,1880},{1460,1810},{1545,1885},{1520,1880},{1480,1840},{1470,1870}};

  Bool_t b_tpc_csum[4];//for tpcs
  Bool_t b_tpc_xy[6];
  Float_t tpc_csum[4];

  Int_t fTpcdt[4], fTpclt[2], fTpcrt[2];

  R3BTpcCalPar* fTpc_Par;         /**< Parameter container. >*/ 
  TClonesArray* fTpcMappedDataCA; /**< Array with Tpc Mapped- input data. >*/
  
  TH1F** fh_Map_dt_y;
  TH1F** fh_Map_dt_x;
  TH1F** fh_Map_csum;
  TH2F** fh_Map_xy;
  char *fOutputFile;
  
 public:
  ClassDef(R3BTpcMapped2CalPar,0);
};

#endif

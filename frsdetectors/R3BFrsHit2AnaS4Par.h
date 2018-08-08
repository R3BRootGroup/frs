// -------------------------------------------------------------------------
// -----         R3BFrsHit2AnaS4Par source file                        -----
// -----             Created 29/07/18  by J.L. Rodriguez-Sanchez       -----
// -------------------------------------------------------------------------

#ifndef R3BFrsHit2AnaS4Par_H
#define R3BFrsHit2AnaS4Par_H

#include "FairTask.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TProfile.h"
#include "TGraph.h"

class TClonesArray;
class R3BFrsAnaPar;
class R3BEventHeader;

class R3BFrsHit2AnaS4Par : public FairTask {
  
 public:
  
  /** Default constructor **/
  R3BFrsHit2AnaS4Par();
  
  /** Standard constructor **/
  R3BFrsHit2AnaS4Par(const char* name, Int_t iVerbose=1);
  
  /** Destructor **/
  virtual ~R3BFrsHit2AnaS4Par();
  
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
  
  /** Accessor functions **/
  void SetZforCal(Double_t theCut){fCutZ=theCut;}
  void SetMagnificationS2S4(Double_t theMag){fMagS2S4=theMag;}
  void SetDispersionS2S4(Double_t theDisp){fDispS2S4=theDisp;}
  void SetPathS2S4(Double_t thePath){fPathS2S4=thePath;}
  void SetTOFS2S4(Double_t theTOF){fTOFS2S4=theTOF;}
  void SetDistTpcS2(Double_t theDis){fDisTpcS2=theDis;}
  void SetDistTpcS4(Double_t theDis){fDisTpcS4=theDis;}
  void SetPosFocalS2(Double_t thePos){fPosFocalS2=thePos;}
  void SetPosFocalS4(Double_t thePos){fPosFocalS4=thePos;}

  void SetRhos(TArrayF* theRhos) {
    fRhos = theRhos;
    fNbRhos = theRhos->GetSize();
  }

  void SetBfieds(TArrayF* theBfield) {
    fBfields = theBfield;
    fNbBfiels = theBfield->GetSize();
  }

 protected:

  Int_t fCutZ,fNb;
  Double_t fMagS2S4;
  Double_t fDispS2S4;
  Double_t fPathS2S4, fTOFS2S4;
  Double_t fDisTpcS2, fDisTpcS4;
  Double_t fPosFocalS2, fPosFocalS4;
  Double_t frho_S0_S2, fBfield_S0_S2, frho_S2_S4, fBfield_S2_S4;

  TArrayF* fRhos;
  Int_t fNbRhos;
  TArrayF* fBfields;
  Int_t fNbBfiels;

  TF1 *fitXposS2_S4, *fitXposS2_S4b;
  TF1 *fitAoQ_ToF;
  
  TClonesArray* fFrsMappedDataCA;/**< Array with FRS mapped- input data. >*/
  TClonesArray* fMusicHitDataCA; /**< Array with MUSIC Hit- input data. >*/
  TClonesArray* fTpcHitDataCA;   /**< Array with TPC Hit- input data.   >*/
  R3BFrsAnaPar* fFrs_Par;        /**< Parameter container. >*/ 

  TH2F* fh_anglevsAq;
  TGraph* graph;
  TProfile* h_Profile; 
  
 public:
  ClassDef(R3BFrsHit2AnaS4Par,0);
};

#endif

// ------------------------------------------------------------
// -----                  R3BFrsOnlineSpectra             -----
// -----    Created 29/07/18  by J.L. Rodriguez-Sanchez   -----
// -----           Fill FRS online histograms             -----
// ------------------------------------------------------------

#ifndef R3BFrsOnlineSpectra_H
#define R3BFrsOnlineSpectra_H

#define N_MUS_DET 3
#define N_TPC_DET 6

#include "FairTask.h"
#include <sstream>
#include <fstream>
#include <iostream>
#include <array>
#include "TMath.h"
#include <cstdlib>
#include "TH1.h"
#include "TH2F.h"
#include "TCanvas.h"

class TClonesArray;
class R3BEventHeader;

/**
 * This taks reads FRS data and plots online histograms 
 */
class R3BFrsOnlineSpectra : public FairTask {
  
 public:
  /**
   * Default constructor.
   * Creates an instance of the task with default parameters.
   */
  R3BFrsOnlineSpectra();
  
  /**
   * Standard constructor.
   * Creates an instance of the task.
   * @param name a name of the task.
   * @param iVerbose a verbosity level.
   */
  R3BFrsOnlineSpectra(const char* name, Int_t iVerbose = 1);
  
  /**
   * Destructor.
   * Frees the memory used by the object.
   */
  virtual ~R3BFrsOnlineSpectra();
  
  /**
   * Method for task initialization.
   * This function is called by the framework before
   * the event loop.
   * @return Initialization status. kSUCCESS, kERROR or kFATAL.
   */
  virtual InitStatus Init();
  
  /**
   * Method for event loop implementation.
   * Is called by the framework every time a new event is read.
   * @param option an execution option.
   */
  virtual void Exec(Option_t* option);
  
  /**
   * A method for finish of processing of an event.
   * Is called by the framework for each event after executing
   * the tasks.
   */
  virtual void FinishEvent();
  
  /**
   * Method for finish of the task execution.
   * Is called by the framework after processing the event loop.
   */
  virtual void FinishTask();

  /**
   * Methods to clean histograms.
   */
  void Reset_GENERAL_Histo();
  void Reset_SEETRAM_Histo();
  void Reset_FRS_Histo();
  void Reset_MUSIC_Histo();
  void Reset_TPC_Histo();
  void Reset_SCI_Histo();
  void Reset_MW_Histo();
  
  private:
  
  TClonesArray* fMappedItemsFrs;     /**< Array with mapped items.           */
  TClonesArray* fMapItemsMusic;      /**< Array with map items for musics.   */
  TClonesArray* fCalItemsMusic;      /**< Array with cal items for musics.   */
  TClonesArray* fHitItemsMusic;      /**< Array with hit items for musics.   */
  TClonesArray* fCalItemsTpc;        /**< Array with cal items for tpcs.     */
  TClonesArray* fHitItemsTpc;        /**< Array with hit items for tpcs.     */
  TClonesArray* fCalItemsSeetram;    /**< Array with cal items for Seetram.  */
  TClonesArray* fHitItemsMw;         /**< Array with hit items for MWs.      */
  TClonesArray* fAnaItemsFrs;        /**< Array with analysis items for frs. */
  TClonesArray* fWRItemsMaster;      /**< Array with WR-Master items.        */
  
  // check for trigger should be done globablly (somewhere else)
  R3BEventHeader* header;               /**< Event header.      */
  Int_t fTrigger;                       /**< Trigger value.     */
  Int_t fNEvents;        	   	/**< Event counter.     */
  bool fFirstWr;
  uint64_t fFirstValueWR;
  Int_t fWrrange;
  
  //Canvas
  TCanvas* cTrigger, *cWr, *cTrigCom;
  TCanvas* cMus1,* cMus2,* cMus3,* cMus1cal,* cMus2cal,* cMus3cal,* cMushit[N_MUS_DET], *c2ID, *c1ID,*cSCI21, *cSCI41, *cSCI42,*cSCI81, *cSCI_21_41, *cSCI_21_81, *cMu41_mu42;
  TCanvas* cTpcCal[N_TPC_DET], *cCalx, *cCalx31, *cSee, *cSeet, *cIc, *cSci00, *cSci01, *cSci02, *cSeeCom, *cTrackS2, *cTrackS4;
  TCanvas* cSCI_tof2141L,*cSCI_tof2141R,*cSCI_tof2141,*cSCI_tof2141RL,*cSCI_tof21pos,*cSCI_tof41pos;
  TCanvas* cHitx,* cHity,* cHitxy;
  TCanvas* cTransS2,* cTransS4;
  TCanvas* cMW1,* cMW2;

  //Unpack
  TH1F* fh_trigger, *fh_TrigC, *fh_TrigFree, *fh_wr;

  //MW
  TH2F* fh_mw[13];
  
  //Seetram
  Int_t fOffsetSeetram;
  Int_t fOffsetSeetramC;
  Int_t fseetram_range;//seg
  Int_t fseetram_rangeC;//seg
  TH1F* fh_Seetram;
  TH1F* fh_Seetramt;
  TH1F* fh_Ic;
  TH1F* fh_Sci00;
  TH1F* fh_Sci01;
  TH1F* fh_Sci02;
  TH1F* fh_SeetramC;
  TH1F* fh_SeetramtC;
  TH1F* fh_IcC;
  TH1F* fh_Sci00C;

  //TPCs
  TH1F* fh_tpc_csum[N_TPC_DET*4];//max 6 tpcs * 4DT
  TH1F* fh_tpc_deltax[N_TPC_DET];//max 6 tpcs
  TH1F* fh_Tpc_hitx[N_TPC_DET];
  TH1F* fh_Tpc_hity[N_TPC_DET];
  TH2F* fh_Tpc_hitxy[N_TPC_DET];
  TH2F* fh_ts2,*fh_ts4,*fh_tr2,*fh_tr4;

  //SCI
  TH1F* fh_sci21le, *fh_sci21re;
  TH2F* fh_sci21lere;
  TH1F* fh_sci41le, *fh_sci41re;
  TH1F* fh_sci41lt, *fh_sci41rt, *fh_sci41t;
  TH2F* fh_sci41lere;
  TH1F* fh_sci42le, *fh_sci42re;
  TH2F* fh_sci42lere;
  TH1F* fh_sci81le, *fh_sci81re;
  TH2F* fh_sci81lere;
  TH2F* fh_sci2141E, *fh_sci2181E;
  TH2F* fh_sci41_lr_t;
  TH1F* fh_sci21pos,* fh_sci41pos;

  //MUSICs
  TH1F* fh_music_energy_per_anode[N_MUS_DET*8];
  TH1F* fh_music_energy_per_anodecal[N_MUS_DET*8];
  TH1F* fh_music_Z[N_MUS_DET];
  TH2F* fh_mu41_mu42;

  //FRS ID histograms
  TH1F* fh_Frs_Z;
  TH1F* fh_Frs_Aq;
  TH2F* fh_Frs_ID;
  
  public:
  ClassDef(R3BFrsOnlineSpectra, 1)
};

#endif

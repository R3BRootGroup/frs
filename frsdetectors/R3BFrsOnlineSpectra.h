// ------------------------------------------------------------
// -----                  R3BFrsOnlineSpectra             -----
// -----    Created 29/07/18  by J.L. Rodriguez-Sanchez   -----
// -----           Fill FRS online histograms             -----
// ------------------------------------------------------------

#ifndef R3BFrsOnlineSpectra_H
#define R3BFrsOnlineSpectra_H

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
  void Reset_FRS_Histo();
  void Reset_MUSIC_Histo();
  void Reset_TPC_Histo();
  void Reset_SCI_Histo();
  
 private:
  
  TClonesArray* fMappedItemsFrs;     /**< Array with mapped items. */
  TClonesArray* fCalItemsMusic;      /**< Array with cal items for musics. */
  TClonesArray* fHitItemsMusic;      /**< Array with hit items for musics. */
  TClonesArray* fCalItemsTpc;        /**< Array with cal items for tpcs. */
  TClonesArray* fHitItemsTpc;        /**< Array with hit items for tpcs. */
  TClonesArray* fAnaItemsFrs;        /**< Array with analysis items for frs. */
  
  // check for trigger should be done globablly (somewhere else)
  R3BEventHeader* header;               /**< Event header. */
  Int_t fTrigger;                       /**< Trigger value. */
  Int_t fNEvents;        	   	/**< Event counter. */
  
  //Canvas
  TCanvas* cMus1,* cMus2,*c2ID,*c1ID,*cSCI21,*cSCI41,*cSCI81;
  TCanvas* cTpcCal[4], *cCalx;
  TCanvas* cHitx,* cHity,* cHitxy;

  //TPCs
  TH1F* fh_tpc_csum[24];//max 6 tpcs * 4DT
  TH1F* fh_tpc_deltax[6];//max 6 tpcs
  TH1F* fh_Tpc_hitx[4];
  TH1F* fh_Tpc_hity[4];
  TH2F* fh_Tpc_hitxy[4];

  //SCI
  TH1F* fh_sci21le, *fh_sci21re;
  TH2F* fh_sci21lere;
  TH1F* fh_sci41le, *fh_sci41re;
  TH2F* fh_sci41lere;
  TH1F* fh_sci81le, *fh_sci81re;
  TH2F* fh_sci81lere;

  //MUSICs
  TH1F* fh_music_energy_per_anode[16];

  //FRS ID histograms
  TH1F* fh_Frs_Z;
  TH1F* fh_Frs_Aq;
  TH2F* fh_Frs_ID;
  
 public:
  ClassDef(R3BFrsOnlineSpectra, 1)
};

#endif

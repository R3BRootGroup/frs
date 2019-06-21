// ------------------------------------------------------------
// -----                  R3BWasaOnlineSpectra            -----
// -----    Created 23/09/18  by J.L. Rodriguez-Sanchez   -----
// -----           Fill WASA online histograms            -----
// ------------------------------------------------------------

#ifndef R3BWasaOnlineSpectra_H
#define R3BWasaOnlineSpectra_H

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
 * This taks reads WASA data and plots online histograms 
 */
class R3BWasaOnlineSpectra : public FairTask {
  
 public:
  /**
   * Default constructor.
   * Creates an instance of the task with default parameters.
   */
  R3BWasaOnlineSpectra();
  
  /**
   * Standard constructor.
   * Creates an instance of the task.
   * @param name a name of the task.
   * @param iVerbose a verbosity level.
   */
  R3BWasaOnlineSpectra(const char* name, Int_t iVerbose = 1);
  
  /**
   * Destructor.
   * Frees the memory used by the object.
   */
  virtual ~R3BWasaOnlineSpectra();
  
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
  void Reset_MDC_Histo();
  
  private:
  
  TClonesArray* fMappedItemsMdc;     /**< Array with mapped items. */
  
  // check for trigger should be done globablly (somewhere else)
  R3BEventHeader* header;               /**< Event header. */
  Int_t fTrigger;                       /**< Trigger value. */
  Int_t fNEvents;        	   	/**< Event counter. */

  //MDC
  TCanvas* cMdcWasa[12*2];
  TH1F* fh_mdc[192*2];
  
  public:
  ClassDef(R3BWasaOnlineSpectra, 1)
};

#endif

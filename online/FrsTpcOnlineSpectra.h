// ------------------------------------------------------------
// -----                  FrsTpcOnlineSpectra             -----
// -----    Created 16/11/19  by J.L. Rodriguez-Sanchez   -----
// -----           Fill FRS online histograms             -----
// ------------------------------------------------------------

#ifndef FrsTpcOnlineSpectra_H
#define FrsTpcOnlineSpectra_H

#define N_TPC_DET 6

#include "FairTask.h"
#include "TCanvas.h"
#include "TH1.h"
#include "TH2F.h"
#include "TMath.h"
#include <array>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>

class TClonesArray;
class R3BEventHeader;

/**
 * This taks reads FRS data and plots online histograms
 */
class FrsTpcOnlineSpectra : public FairTask
{

  public:
    /**
     * Default constructor.
     * Creates an instance of the task with default parameters.
     */
    FrsTpcOnlineSpectra();

    /**
     * Standard constructor.
     * Creates an instance of the task.
     * @param name a name of the task.
     * @param iVerbose a verbosity level.
     */
    FrsTpcOnlineSpectra(const char* name, Int_t iVerbose = 1);

    /**
     * Destructor.
     * Frees the memory used by the object.
     */
    virtual ~FrsTpcOnlineSpectra();

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
    void Reset_TPC_Histo();


  private:
    TClonesArray* fMappedItemsFrs;  /**< Array with mapped items.           */
    TClonesArray* fCalItemsTpc;     /**< Array with cal items for tpcs.     */
    TClonesArray* fHitItemsTpc;     /**< Array with hit items for tpcs.     */

    // check for trigger should be done globablly (somewhere else)
    R3BEventHeader* header; /**< Event header.      */
    Int_t fNEvents;         /**< Event counter.     */


    // Canvas
    TCanvas *cTpcCal[N_TPC_DET], *cCalx, *cCalx31, *cSee, *cSeet, *cIc, *cSci00, *cSci01, *cSci02, *cSeeCom, *cTrackS2, *cTrackS4;
    TCanvas *cHitx, *cHity, *cHitxy;
    TCanvas *cTransS2, *cTransS4;

    // TPCs
    TH1F* fh_tpc_csum[N_TPC_DET * 4]; // max 6 tpcs * 4DT
    TH1F* fh_tpc_deltax[N_TPC_DET];   // max 6 tpcs
    TH1F* fh_Tpc_hitx[N_TPC_DET];
    TH1F* fh_Tpc_hity[N_TPC_DET];
    TH2F* fh_Tpc_hitxy[N_TPC_DET];
    TH2F *fh_ts2, *fh_ts4, *fh_tr2, *fh_tr4;


  public:
    ClassDef(FrsTpcOnlineSpectra, 1)
};

#endif

// ------------------------------------------------------------
// -----                  FrsMWOnlineSpectra              -----
// -----    Created 16/11/19  by J.L. Rodriguez-Sanchez   -----
// -----            Fill FRS online histograms            -----
// ------------------------------------------------------------

#ifndef FrsMWOnlineSpectra_H
#define FrsMWOnlineSpectra_H

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
#include <vector>

#define MWDET_MAX 13

class TClonesArray;
class R3BEventHeader;

/**
 * This taks reads MW data and plots online histograms
 */
class FrsMWOnlineSpectra : public FairTask
{

  public:
    /**
     * Default constructor.
     * Creates an instance of the task with default parameters.
     */
    FrsMWOnlineSpectra();

    /**
     * Standard constructor.
     * Creates an instance of the task.
     * @param name a name of the task.
     * @param iVerbose a verbosity level.
     * @param namedet a name of the detector.
     */
    FrsMWOnlineSpectra(const TString& name, Int_t iVerbose = 1, const TString& namedet = "MW");

    /**
     * Destructor.
     * Frees the memory used by the object.
     */
    virtual ~FrsMWOnlineSpectra();

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
    virtual void Reset_Histo();

  private:
    TClonesArray* fMapItemsMw; /**< Array with Mapped items. */
    TClonesArray* fHitItemsMw; /**< Array with Hit items. */

    // check for trigger should be done globablly (somewhere else)
    R3BEventHeader* header; /**< Event header.      */
    Int_t fNEvents;         /**< Event counter.     */
    TString fNameDet;

    // Canvas
    TCanvas *cMWPCCal, *cMWPCCal2D;

    // Histograms for Mapped data
    TH1F* fh1_mw_a;
    TH1F* fh1_mw_xl;
    TH1F* fh1_mw_xr;
    TH1F* fh1_mw_yu;
    TH1F* fh1_mw_yd;
    TH1F* fh1_mw_xsum;
    TH1F* fh1_mw_ysum;

    // Histograms for Cal data
    TH1F* fh1_mw_x;
    TH1F* fh1_mw_y;
    TH2F* fh2_mw_xy;

    const char* fDetectorNames[MWDET_MAX + 1] = { "MW11", "MW21", "MW22", "MW31", "MW41", "MW42", "MW51",
                                                  "MW61", "MW71", "MW81", "MW82", "MWB1", "MWB2", NULL };

  public:
    ClassDef(FrsMWOnlineSpectra, 1)
};

#endif

// ------------------------------------------------------------
// -----                  FrsMusicOnlineSpectra           -----
// -----    Created 16/11/19  by J.L. Rodriguez-Sanchez   -----
// -----            Fill FRS online histograms            -----
// ------------------------------------------------------------

#ifndef FrsMusicOnlineSpectra_H
#define FrsMusicOnlineSpectra_H

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

#define N_ANODES 8
#define MUSDET_MAX 3

class TClonesArray;
class R3BEventHeader;

/**
 * This taks reads Music data and plots online histograms
 */
class FrsMusicOnlineSpectra : public FairTask
{

  public:
    /**
     * Default constructor.
     * Creates an instance of the task with default parameters.
     */
    FrsMusicOnlineSpectra();

    /**
     * Standard constructor.
     * Creates an instance of the task.
     * @param name a name of the task.
     * @param iVerbose a verbosity level.
     * @param namedet a name of the detector.
     */
    FrsMusicOnlineSpectra(const TString& name, Int_t iVerbose = 1, const TString& namedet = "MUSIC");

    /**
     * Destructor.
     * Frees the memory used by the object.
     */
    virtual ~FrsMusicOnlineSpectra();

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
    TClonesArray* fMapItems; /**< Array with Mapped items. */
    TClonesArray* fCalItems; /**< Array with Cal items. */
    TClonesArray* fHitItems; /**< Array with Hit items. */

    // check for trigger should be done globablly (somewhere else)
    R3BEventHeader* header; /**< Event header.      */
    Int_t fNEvents;         /**< Event counter.     */
    TString fNameDet;

    // Canvas
    TCanvas *cMusE, *cMusECal;
    TCanvas *cMusT, *cMusTCal;
    TCanvas *cMushit;

    // Histograms for Mapped data
    TH1F* fh_music_energy_per_anode[N_ANODES];
    TH1F* fh_music_t_per_anode[N_ANODES];

    // Histograms for Cal data
    TH1F* fh_music_energy_per_anodecal[N_ANODES];

    // Histograms for Hit data
    TH1F* fh_music_Z;

    const char *fDetectorNames[MUSDET_MAX + 1] =
    {
      "Music41",
      "Music42",
      "Music43",
      NULL
   };

  public:
    ClassDef(FrsMusicOnlineSpectra, 1)
};

#endif

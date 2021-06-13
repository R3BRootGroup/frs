// ----------------------------------------------------------------------
// -----                                                            -----
// -----                     R3BFrsHit2AnaS4                        -----
// -----             Created 29/07/18  by J.L. Rodriguez-Sanchez    -----
// ----------------------------------------------------------------------

#ifndef R3BFrsHit2AnaS4_H
#define R3BFrsHit2AnaS4_H

#include "FairTask.h"
#include "R3BFrsS4Data.h"
#include "TF1.h"
#include "TH1F.h"
#include <TRandom.h>

class TClonesArray;
class R3BFrsAnaPar;

class R3BFrsHit2AnaS4 : public FairTask
{

  public:
    /** Default constructor **/
    R3BFrsHit2AnaS4();

    /** Standard constructor **/
    R3BFrsHit2AnaS4(const char* name, Int_t iVerbose = 1);

    /** Destructor **/
    virtual ~R3BFrsHit2AnaS4();

    /** Virtual method Exec **/
    virtual void Exec(Option_t* option);

    /** Virtual method Reset **/
    virtual void Reset();

    virtual void SetParContainers();

    // Fair specific
    /** Virtual method Init **/
    virtual InitStatus Init();

    /** Virtual method ReInit **/
    virtual InitStatus ReInit();

    /** Virtual method Finish **/
    virtual void Finish();

    /** Accessor to select online mode **/
    void SetOnline(Bool_t option) { fOnline = option; }

    /** Accessor functions **/
    void SetOffsetAq(Double_t theAq) { fOffsetAq = theAq; }
    void SetOffsetZ(Double_t theZ) { fOffsetZ = theZ; }

  private:
    void SetParameter();

    Double_t fOffsetAq, fOffsetZ; // Offsets in A/q and Z
    TArrayF* fAnaParams;          // Parameters for frs
    R3BFrsAnaPar* fFrs_Par;       // Parameter container

    Double_t fMagS2S4;
    Double_t fDispS2S4;
    Double_t fPathS2S4, fTOFS2S4;
    Double_t fDisTpcS2, fDisTpcS4, fPosFocalS2, fPosFocalS4;
    Double_t frho_S0_S2, fBfield_S0_S2, frho_S2_S4, fBfield_S2_S4;
    Double_t fRotS4, fParm0, fParm1;

    Bool_t fOnline; // Don't store data for online

    TClonesArray* fFrsMappedDataCA; /**< Array with FRS mapped- input data. >*/
    TClonesArray* fMusicHitDataCA;  /**< Array with MUSIC Hit- input data. >*/
    TClonesArray* fTpcHitDataCA;    /**< Array with TPC Hit- input data.   >*/
    TClonesArray* fFrsDataCA;       /**< Array with FRS data- output data. >*/

    /** Private method FrsData **/
    //** Adds a FrsData to the analysis
    R3BFrsS4Data* AddData(Double_t z, Double_t aq, Double_t xs2, Double_t as2, Double_t xs4, Double_t as4);

  public:
    // Class definition
    ClassDef(R3BFrsHit2AnaS4, 1)
};

#endif

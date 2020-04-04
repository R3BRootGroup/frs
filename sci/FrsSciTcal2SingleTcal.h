// *** *************************************************************** *** //
// ***                  FrsSciTcal2SingleTcal                        *** //
// *** ---> whatever multiplicity per PMT, select the propoer hit      *** //
// *** *************************************************************** *** //

#ifndef FRSSCI_TCAL2SINGLETCAL
#define FRSSCI_TCAL2SINGLETCAL

#include "FairTask.h"

#include "FrsSciRawPosPar.h"
#include "FrsSciSingleTcalData.h"

#include "FrsSciRawTofPar.h"

#include "TClonesArray.h"
#include "TMath.h"
#include "TRandom.h"
class TRandom3;

class FrsSciTcal2SingleTcal : public FairTask
{

  public:
    // --- Default constructor --- //
    FrsSciTcal2SingleTcal();

    // --- Standard constructor --- //
    FrsSciTcal2SingleTcal(const char* name, Int_t iVerbose = 1);

    // --- Destructor --- //
    virtual ~FrsSciTcal2SingleTcal();

    virtual InitStatus Init();
    virtual void SetParContainers();
    virtual InitStatus ReInit();
    virtual void Exec(Option_t* option);
    virtual void FinishEvent();
    virtual void FinishTask();

    void SetOnline(Bool_t option) { fOnline = option; }

  private:
    TClonesArray* fTcal;
    TClonesArray* fSingleTcal;
    FrsSciRawPosPar* fRawPosPar;
    FrsSciRawTofPar* fRawTofPar;

    Bool_t fOnline; // Don't store data for online

    UInt_t fNumSingleTcal;

    UInt_t fNevent;

    TRandom rand;

  public:
    ClassDef(FrsSciTcal2SingleTcal, 1)
};

#endif // FRSSCI_TCAL2SINGLETCAL

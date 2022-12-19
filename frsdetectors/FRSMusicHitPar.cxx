// ------------------------------------------------------------------
// -----            FRSMusicHitPar source file                  -----
// -----         Created 29/05/18  by J.L. Rodriguez-Sanchez    -----
// ------------------------------------------------------------------

#include "FRSMusicHitPar.h"

#include "FairLogger.h"
#include "FairParamList.h"
#include "TArrayF.h"
#include "TMath.h"
#include "TString.h"

#include <iostream>

using std::cout;
using std::endl;

// ---- Standard Constructor ---------------------------------------------------
FRSMusicHitPar::FRSMusicHitPar(const char* name, const char* title, const char* context)
    : FairParGenericSet(name, title, context)
{
    fDetHitParams = new TArrayF(2); // 2CalibrationParameters
    fNumDets = 1;
    fNumParamsFit = 2; // 2nd order
}

// ----  Destructor ------------------------------------------------------------
FRSMusicHitPar::~FRSMusicHitPar()
{
    clear();
    delete fDetHitParams;
}

// ----  Method clear ----------------------------------------------------------
void FRSMusicHitPar::clear()
{
    status = kFALSE;
    resetInputVersions();
}

// ----  Method putParams ------------------------------------------------------
void FRSMusicHitPar::putParams(FairParamList* list)
{
    LOG(info) << "FRSMusicHitPar::putParams() called";
    if (!list)
    {
        return;
    }

    Int_t array_size = fNumDets * fNumParamsFit;
    LOG(info) << "Array Size: " << array_size;

    fDetHitParams->Set(array_size);

    list->add("frsmusicHitPar", *fDetHitParams);
    list->add("frsmusicDetNumberPar", fNumDets);
    list->add("frsmusicHitParamsFitPar", fNumParamsFit);
}

// ----  Method getParams ------------------------------------------------------
Bool_t FRSMusicHitPar::getParams(FairParamList* list)
{
    LOG(info) << "FRSMusicHitPar::getParams() called";
    if (!list)
    {
        return kFALSE;
    }

    if (!list->fill("frsmusicDetNumberPar", &fNumDets))
    {
        return kFALSE;
    }

    if (!list->fill("frsmusicHitParamsFitPar", &fNumParamsFit))
    {
        return kFALSE;
    }

    Int_t array_size = fNumDets * fNumParamsFit;
    LOG(info) << "Array Size: " << array_size;
    fDetHitParams->Set(array_size);

    if (!(list->fill("frsmusicHitPar", fDetHitParams)))
    {
        LOG(info) << "---Could not initialize frsmusicHitPar";
        return kFALSE;
    }

    return kTRUE;
}

// ----  Method printParams ----------------------------------------------------
void FRSMusicHitPar::printParams()
{
    LOG(info) << "FRSMusicHitPar: music detector Parameters: ";
    Int_t array_size = fNumDets * fNumParamsFit;

    for (Int_t d = 0; d < fNumDets; d++)
    {
        LOG(info) << "Music detector number: " << d;
        for (Int_t j = 0; j < fNumParamsFit; j++)
        {
            LOG(info) << "FitParam(" << j << ") = " << fDetHitParams->GetAt(d * fNumParamsFit + j);
        }
    }
}

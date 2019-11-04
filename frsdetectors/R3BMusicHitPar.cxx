// ------------------------------------------------------------------
// -----            R3BMusicHitPar source file                  -----
// -----         Created 29/05/18  by J.L. Rodriguez-Sanchez    -----
// ------------------------------------------------------------------

#include "R3BMusicHitPar.h"

#include "FairLogger.h"
#include "FairParamList.h"

#include "TArrayF.h"
#include "TMath.h"
#include "TString.h"

#include <iostream>

using std::cout;
using std::endl;

// ---- Standard Constructor ---------------------------------------------------
R3BMusicHitPar::R3BMusicHitPar(const char* name, const char* title, const char* context)
    : FairParGenericSet(name, title, context)
{
    fDetHitParams = new TArrayF(2); // 2CalibrationParameters
    fNumDets = 1;
    fNumParamsFit = 2; // 2nd order
}

// ----  Destructor ------------------------------------------------------------
R3BMusicHitPar::~R3BMusicHitPar()
{
    clear();
    delete fDetHitParams;
}

// ----  Method clear ----------------------------------------------------------
void R3BMusicHitPar::clear()
{
    status = kFALSE;
    resetInputVersions();
}

// ----  Method putParams ------------------------------------------------------
void R3BMusicHitPar::putParams(FairParamList* list)
{
    LOG(INFO) << "R3BMusicHitPar::putParams() called";
    if (!list)
    {
        return;
    }

    Int_t array_size = fNumDets * fNumParamsFit;
    LOG(INFO) << "Array Size: " << array_size;

    fDetHitParams->Set(array_size);

    list->add("musicHitPar", *fDetHitParams);
    list->add("musicDetNumberPar", fNumDets);
    list->add("musicHitParamsFitPar", fNumParamsFit);
}

// ----  Method getParams ------------------------------------------------------
Bool_t R3BMusicHitPar::getParams(FairParamList* list)
{
    LOG(INFO) << "R3BMusicHitPar::getParams() called";
    if (!list)
    {
        return kFALSE;
    }

    if (!list->fill("musicDetNumberPar", &fNumDets))
    {
        return kFALSE;
    }

    if (!list->fill("musicHitParamsFitPar", &fNumParamsFit))
    {
        return kFALSE;
    }

    Int_t array_size = fNumDets * fNumParamsFit;
    LOG(INFO) << "Array Size: " << array_size;
    fDetHitParams->Set(array_size);

    if (!(list->fill("musicHitPar", fDetHitParams)))
    {
        LOG(INFO) << "---Could not initialize musicHitPar";
        return kFALSE;
    }

    return kTRUE;
}

// ----  Method printParams ----------------------------------------------------
void R3BMusicHitPar::printParams()
{
    LOG(INFO) << "R3BMusicHitPar: music detector Parameters: ";
    Int_t array_size = fNumDets * fNumParamsFit;

    for (Int_t d = 0; d < fNumDets; d++)
    {
        LOG(INFO) << "Music detector number: " << d;
        for (Int_t j = 0; j < fNumParamsFit; j++)
        {
            LOG(INFO) << "FitParam(" << j << ") = " << fDetHitParams->GetAt(d * fNumParamsFit + j);
        }
    }
}

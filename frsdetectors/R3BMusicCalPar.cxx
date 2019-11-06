// ------------------------------------------------------------------
// -----         R3BMusicCalPar source file                  -----
// -----         Created 29/05/18  by J.L. Rodriguez-Sanchez    -----
// ------------------------------------------------------------------

#include "R3BMusicCalPar.h"

#include "FairLogger.h"
#include "FairParamList.h"

#include "TArrayF.h"
#include "TMath.h"
#include "TString.h"

#include <iostream>

using std::cout;
using std::endl;

// ---- Standard Constructor ---------------------------------------------------
R3BMusicCalPar::R3BMusicCalPar(const char* name, const char* title, const char* context)
    : FairParGenericSet(name, title, context)
{
    fAnodeCalParams = new TArrayF(24); // 8anodes*3CalibrationParameters
    fNumDets = 1;
    fNumAnodes = 8;
    fNumParamsFit = 3; // gaus
}

// ----  Destructor ------------------------------------------------------------
R3BMusicCalPar::~R3BMusicCalPar()
{
    clear();
    delete fAnodeCalParams;
}

// ----  Method clear ----------------------------------------------------------
void R3BMusicCalPar::clear()
{
    status = kFALSE;
    resetInputVersions();
}

// ----  Method putParams ------------------------------------------------------
void R3BMusicCalPar::putParams(FairParamList* list)
{
    LOG(INFO) << "R3BMusicCalPar::putParams() called";
    if (!list)
    {
        return;
    }

    Int_t array_size = fNumDets * fNumAnodes * fNumParamsFit;
    LOG(INFO) << "Array Size: " << array_size;

    fAnodeCalParams->Set(array_size);

    list->add("musicCalPar", *fAnodeCalParams);
    list->add("musicDetNumberPar", fNumDets);
    list->add("musicAnodeNumberPar", fNumAnodes);
    list->add("musicAnodeParamsFitPar", fNumParamsFit);
}

// ----  Method getParams ------------------------------------------------------
Bool_t R3BMusicCalPar::getParams(FairParamList* list)
{
    LOG(INFO) << "R3BMusicCalPar::getParams() called";
    if (!list)
    {
        return kFALSE;
    }

    if (!list->fill("musicDetNumberPar", &fNumDets))
    {
        return kFALSE;
    }

    if (!list->fill("musicAnodeNumberPar", &fNumAnodes))
    {
        return kFALSE;
    }

    if (!list->fill("musicAnodeParamsFitPar", &fNumParamsFit))
    {
        return kFALSE;
    }

    Int_t array_size = fNumDets * fNumAnodes * fNumParamsFit;
    LOG(INFO) << "Array Size: " << array_size;
    fAnodeCalParams->Set(array_size);

    if (!(list->fill("musicCalPar", fAnodeCalParams)))
    {
        LOG(INFO) << "---Could not initialize musicCalPar";
        return kFALSE;
    }

    return kTRUE;
}

// ----  Method printParams ----------------------------------------------------
void R3BMusicCalPar::printParams()
{
    LOG(INFO) << "R3BMusicCalPar: music anode Parameters: ";
    Int_t array_size = fNumDets * fNumAnodes * fNumParamsFit;

    for (Int_t d = 0; d < fNumDets; d++)
    {
        LOG(INFO) << "Music detector number: " << d;
        for (Int_t i = 0; i < fNumAnodes; i++)
        {
            LOG(INFO) << "Anode number: " << i;
            for (Int_t j = 0; j < fNumParamsFit; j++)
            {
                LOG(INFO) << "FitParam(" << j
                          << ") = " << fAnodeCalParams->GetAt(d * fNumParamsFit * fNumAnodes + i * fNumParamsFit + j);
            }
        }
    }
}

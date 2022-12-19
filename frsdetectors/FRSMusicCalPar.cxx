// ------------------------------------------------------------------
// -----            FRSMusicCalPar source file                  -----
// -----         Created 29/05/18  by J.L. Rodriguez-Sanchez    -----
// ------------------------------------------------------------------

#include "FRSMusicCalPar.h"

#include "FairLogger.h"
#include "FairParamList.h"
#include "TArrayF.h"
#include "TMath.h"
#include "TString.h"

#include <iostream>

using std::cout;
using std::endl;

// ---- Standard Constructor ---------------------------------------------------
FRSMusicCalPar::FRSMusicCalPar(const char* name, const char* title, const char* context)
    : FairParGenericSet(name, title, context)
{
    fAnodeCalParams = new TArrayF(24); // 8anodes*3CalibrationParameters
    fNumDets = 1;
    fNumAnodes = 8;
    fNumParamsFit = 3; // gaus
}

// ----  Destructor ------------------------------------------------------------
FRSMusicCalPar::~FRSMusicCalPar()
{
    clear();
    delete fAnodeCalParams;
}

// ----  Method clear ----------------------------------------------------------
void FRSMusicCalPar::clear()
{
    status = kFALSE;
    resetInputVersions();
}

// ----  Method putParams ------------------------------------------------------
void FRSMusicCalPar::putParams(FairParamList* list)
{
    LOG(info) << "FRSMusicCalPar::putParams() called";
    if (!list)
    {
        return;
    }

    Int_t array_size = fNumDets * fNumAnodes * fNumParamsFit;
    LOG(info) << "Array Size: " << array_size;

    fAnodeCalParams->Set(array_size);

    list->add("frsmusicCalPar", *fAnodeCalParams);
    list->add("frsmusicDetNumberPar", fNumDets);
    list->add("frsmusicAnodeNumberPar", fNumAnodes);
    list->add("frsmusicAnodeParamsFitPar", fNumParamsFit);
}

// ----  Method getParams ------------------------------------------------------
Bool_t FRSMusicCalPar::getParams(FairParamList* list)
{
    LOG(info) << "FRSMusicCalPar::getParams() called";
    if (!list)
    {
        return kFALSE;
    }

    if (!list->fill("frsmusicDetNumberPar", &fNumDets))
    {
        return kFALSE;
    }

    if (!list->fill("frsmusicAnodeNumberPar", &fNumAnodes))
    {
        return kFALSE;
    }

    if (!list->fill("frsmusicAnodeParamsFitPar", &fNumParamsFit))
    {
        return kFALSE;
    }

    Int_t array_size = fNumDets * fNumAnodes * fNumParamsFit;
    LOG(info) << "Array Size: " << array_size;
    fAnodeCalParams->Set(array_size);

    if (!(list->fill("frsmusicCalPar", fAnodeCalParams)))
    {
        LOG(info) << "---Could not initialize frsmusicCalPar";
        return kFALSE;
    }

    return kTRUE;
}

// ----  Method printParams ----------------------------------------------------
void FRSMusicCalPar::printParams()
{
    LOG(info) << "FRSMusicCalPar: music anode Parameters: ";
    Int_t array_size = fNumDets * fNumAnodes * fNumParamsFit;

    for (Int_t d = 0; d < fNumDets; d++)
    {
        LOG(info) << "Music detector number: " << d;
        for (Int_t i = 0; i < fNumAnodes; i++)
        {
            LOG(info) << "Anode number: " << i;
            for (Int_t j = 0; j < fNumParamsFit; j++)
            {
                LOG(info) << "FitParam(" << j
                          << ") = " << fAnodeCalParams->GetAt(d * fNumParamsFit * fNumAnodes + i * fNumParamsFit + j);
            }
        }
    }
}

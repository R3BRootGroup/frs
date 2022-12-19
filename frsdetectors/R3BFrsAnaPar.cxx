// ------------------------------------------------------------------
// -----         R3BFrsAnaPar source file                       -----
// -----         Created 29/07/18  by J.L. Rodriguez-Sanchez    -----
// ------------------------------------------------------------------

#include "R3BFrsAnaPar.h"

#include "FairLogger.h"
#include "FairParamList.h"
#include "TArrayF.h"
#include "TMath.h"
#include "TString.h"

#include <iostream>

using std::cout;
using std::endl;

// ---- Standard Constructor ---------------------------------------------------
R3BFrsAnaPar::R3BFrsAnaPar(const char* name, const char* title, const char* context)
    : FairParGenericSet(name, title, context)
    , fNumParams(3)
    , // 2 offsets + 1 angle
    fMagS2S4(0)
    , fDispS2S4(0)
    , fPathS2S4(0)
    , fTOFS2S4(0)
    , fDisTpcS2(0)
    , fDisTpcS4(0)
    , fPosFocalS2(0)
    , fPosFocalS4(0)
    , frho_S0_S2(0)
    , fBfield_S0_S2(0)
    , frho_S2_S4(0)
    , fBfield_S2_S4(0)
{
    fAnaParams = new TArrayF(fNumParams);
}

// ----  Destructor ------------------------------------------------------------
R3BFrsAnaPar::~R3BFrsAnaPar()
{
    clear();
    delete fAnaParams;
}

// ----  Method clear ----------------------------------------------------------
void R3BFrsAnaPar::clear()
{
    status = kFALSE;
    resetInputVersions();
}

// ----  Method putParams ------------------------------------------------------
void R3BFrsAnaPar::putParams(FairParamList* list)
{
    LOG(info) << "R3BFrsAnaPar::putParams() called";
    if (!list)
    {
        return;
    }

    Int_t array_size = fNumParams;
    LOG(info) << "Array Size: " << array_size;
    fAnaParams->Set(array_size);

    list->add("frsAnaPar", *fAnaParams);
    list->add("frsAnaNumberPar", fNumParams);
    list->add("MagnificationS2S4", fMagS2S4);
    list->add("DisperisionS2S4", fDispS2S4);
    list->add("PathS2S4", fPathS2S4);
    list->add("ToFS2S4", fTOFS2S4);
    list->add("DistTpcS2", fDisTpcS2);
    list->add("DistTpcS4", fDisTpcS4);
    list->add("PosFocalS2", fPosFocalS2);
    list->add("PosFocalS4", fPosFocalS4);
    list->add("Rho_S0_S2", frho_S0_S2);
    list->add("Bfield_S0_S2", fBfield_S0_S2);
    list->add("Rho_S2_S4", frho_S2_S4);
    list->add("Bfield_S2_S4", fBfield_S2_S4);
}

// ----  Method getParams ------------------------------------------------------
Bool_t R3BFrsAnaPar::getParams(FairParamList* list)
{
    LOG(info) << "R3BFrsAnaPar::getParams() called";
    if (!list)
    {
        return kFALSE;
    }

    if (!list->fill("MagnificationS2S4", &fMagS2S4))
    {
        return kFALSE;
    }

    if (!list->fill("DisperisionS2S4", &fDispS2S4))
    {
        return kFALSE;
    }
    if (!list->fill("PathS2S4", &fPathS2S4))
    {
        return kFALSE;
    }
    if (!list->fill("ToFS2S4", &fTOFS2S4))
    {
        return kFALSE;
    }
    if (!list->fill("DistTpcS2", &fDisTpcS2))
    {
        return kFALSE;
    }
    if (!list->fill("DistTpcS4", &fDisTpcS4))
    {
        return kFALSE;
    }
    if (!list->fill("PosFocalS2", &fPosFocalS2))
    {
        return kFALSE;
    }
    if (!list->fill("PosFocalS4", &fPosFocalS4))
    {
        return kFALSE;
    }
    if (!list->fill("Rho_S0_S2", &frho_S0_S2))
    {
        return kFALSE;
    }
    if (!list->fill("Bfield_S0_S2", &fBfield_S0_S2))
    {
        return kFALSE;
    }
    if (!list->fill("Rho_S2_S4", &frho_S2_S4))
    {
        return kFALSE;
    }
    if (!list->fill("Bfield_S2_S4", &fBfield_S2_S4))
    {
        return kFALSE;
    }

    if (!list->fill("frsAnaNumberPar", &fNumParams))
    {
        return kFALSE;
    }

    Int_t array_size = fNumParams;
    LOG(info) << "Array Size: " << array_size;
    fAnaParams->Set(array_size);

    if (!(list->fill("frsAnaPar", fAnaParams)))
    {
        LOG(info) << "---Could not initialize frsAnaPar";
        return kFALSE;
    }

    return kTRUE;
}

// ----  Method printParams ----------------------------------------------------
void R3BFrsAnaPar::printParams()
{
    LOG(info) << "R3BFrsAnaPar: Frs Analysis Parameters: ";
    Int_t array_size = fNumParams;
    std::cout << "Params = " << fAnaParams->GetAt(0) << "," << fAnaParams->GetAt(1) << ", " << fAnaParams->GetAt(2)
              << std::endl;
}

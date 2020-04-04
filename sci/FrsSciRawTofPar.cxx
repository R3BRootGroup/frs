#include "FrsSciRawTofPar.h"

#include "FairLogger.h"
#include "FairParamList.h"

#include "TArrayF.h"
#include "TMath.h"
#include "TString.h"

#include <iostream>

using std::cout;
using std::endl;

// ---- Standard Constructor ---------------------------------------------------
FrsSciRawTofPar::FrsSciRawTofPar(const char* name, const char* title, const char* context)
    : FairParGenericSet(name, title, context)
    , fFirstStaSci(1)
    , fNumSignals(1)//(NUMBER_OF_SOFSCI_DETECTORS - 1) with NUMBER_OF_SOFSCI_DETECTORS=2
    , fNumParsPerSignal(2)
{
    fAllSignalsRawTofParams = new TArrayF(2*fNumSignals);
}

// ----  Destructor ------------------------------------------------------------
FrsSciRawTofPar::~FrsSciRawTofPar()
{
    clear();
    if (fAllSignalsRawTofParams)
    {
        delete fAllSignalsRawTofParams;
    }
}

// ----  Method clear ----------------------------------------------------------
void FrsSciRawTofPar::clear()
{
    status = kFALSE;
    resetInputVersions();
}

// ----  Method putParams ------------------------------------------------------
void FrsSciRawTofPar::putParams(FairParamList* list)
{
    LOG(INFO) << "FrsSciRawTofPar::putParams() called";
    if (!list)
    {
        return;
    }

    Int_t array_size = fNumSignals * fNumParsPerSignal;
    LOG(INFO) << "Array Size: " << array_size;

    fAllSignalsRawTofParams->Set(array_size);

    list->add("RawTofPar", *fAllSignalsRawTofParams);
    list->add("selectionFirstStart", fFirstStaSci);
    list->add("nSignalsRawTofPar", fNumSignals);
    list->add("nRawTofParsPerSignal", fNumParsPerSignal);
}

// ----  Method getParams ------------------------------------------------------
Bool_t FrsSciRawTofPar::getParams(FairParamList* list)
{
    LOG(INFO) << "FrsSciRawTofPar::getParams() called";
    if (!list)
    {
        return kFALSE;
    }
    if (!list->fill("selectionFirstStart", &fFirstStaSci))
    {
        return kFALSE;
    }
    if (!list->fill("nSignalsRawTofPar", &fNumSignals))
    {
        return kFALSE;
    }
    if (!list->fill("nRawTofParsPerSignal", &fNumParsPerSignal))
    {
        return kFALSE;
    }

    Int_t array_size = fNumSignals * fNumParsPerSignal;
    LOG(INFO) << "Array Size: " << array_size;
    fAllSignalsRawTofParams->Set(array_size);

    if (!(list->fill("RawTofPar", fAllSignalsRawTofParams)))
    {
        LOG(INFO) << "---Could not initialize fAllSignalsRawTofParams";
        return kFALSE;
    }

    return kTRUE;
}

// ----  Method printParams ----------------------------------------------------
void FrsSciRawTofPar::printParams()
{
    LOG(INFO) << "FrsSciRawTofPar: SofSciRawTof Parameters: ";
    Int_t array_size = fNumSignals * fNumParsPerSignal;

    cout << "--- --------------------------------------------" << endl;
    cout << "--- Single Tcal RawTof Parameters :  " << endl;
    cout << "--- --------------------------------------------" << endl;
    for (Int_t param = 0; param < array_size; param++)
    {
        cout << "LIMIT " << param << " = " << fAllSignalsRawTofParams->GetAt(param) << endl;
    }
}

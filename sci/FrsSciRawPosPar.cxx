#include "FrsSciRawPosPar.h"

#include "FairLogger.h"
#include "FairParamList.h"

#include "TArrayF.h"
#include "TMath.h"
#include "TString.h"

#include <iostream>

using std::cout;
using std::endl;

// ---- Standard Constructor ---------------------------------------------------
FrsSciRawPosPar::FrsSciRawPosPar(const char* name, const char* title, const char* context)
    : FairParGenericSet(name, title, context)
    , fNumDetectors(2)
    , fNumChannels(2)
    , fNumParsPerSignal(2)
{

    fNumSignals = fNumDetectors * fNumChannels;
    fAllSignalsRawPosParams = new TArrayF(fNumDetectors*2);
}

// ----  Destructor ------------------------------------------------------------
FrsSciRawPosPar::~FrsSciRawPosPar()
{
    clear();
    if (fAllSignalsRawPosParams)
    {
        delete fAllSignalsRawPosParams;
    }
}

// ----  Method clear ----------------------------------------------------------
void FrsSciRawPosPar::clear()
{
    status = kFALSE;
    resetInputVersions();
}

// ----  Method putParams ------------------------------------------------------
void FrsSciRawPosPar::putParams(FairParamList* list)
{
    LOG(INFO) << "FrsSciRawPosPar::putParams() called";
    if (!list)
    {
        return;
    }

    Int_t array_size = fNumDetectors * fNumParsPerSignal;
    LOG(INFO) << "Array Size: " << array_size;

    fAllSignalsRawPosParams->Set(array_size);

    list->add("RawPosPar", *fAllSignalsRawPosParams);
    list->add("nDetectorsRawPosPar", fNumDetectors);
    list->add("nChannelsRawPosPar", fNumChannels);
    list->add("nSignalsRawPosPar", fNumSignals);
    list->add("nRawPosParsPerSignal", fNumParsPerSignal);
}

// ----  Method getParams ------------------------------------------------------
Bool_t FrsSciRawPosPar::getParams(FairParamList* list)
{
    LOG(INFO) << "FrsSciRawPosPar::getParams() called";
    if (!list)
    {
        return kFALSE;
    }
    if (!list->fill("nDetectorsRawPosPar", &fNumDetectors))
    {
        return kFALSE;
    }
    if (!list->fill("nChannelsRawPosPar", &fNumChannels))
    {
        return kFALSE;
    }
    if (!list->fill("nSignalsRawPosPar", &fNumSignals))
    {
        return kFALSE;
    }
    if (!list->fill("nRawPosParsPerSignal", &fNumParsPerSignal))
    {
        return kFALSE;
    }

    Int_t array_size = fNumDetectors * fNumParsPerSignal;
    LOG(INFO) << "Array Size: " << array_size;
    fAllSignalsRawPosParams->Set(array_size);

    if (!(list->fill("RawPosPar", fAllSignalsRawPosParams)))
    {
        LOG(INFO) << "---Could not initialize fAllSignalsRawPosParams";
        return kFALSE;
    }

    return kTRUE;
}

// ----  Method printParams ----------------------------------------------------
void FrsSciRawPosPar::printParams()
{
    LOG(INFO) << "FrsSciRawPosPar: SofSciRawPos Parameters: ";
    Int_t array_size = fNumDetectors * fNumParsPerSignal;

    cout << "--- --------------------------------------------" << endl;
    cout << "--- Single Tcal Parameters :  " << endl;
    cout << "--- --------------------------------------------" << endl;
    for (Int_t param = 0; param < array_size; param++)
    {
        cout << "LIMIT " << param << " = " << fAllSignalsRawPosParams->GetAt(param) << endl;
    }
}

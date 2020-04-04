#include "FrsSciTcalPar.h"

#include "FairLogger.h"
#include "FairParamList.h"

#include "TArrayF.h"
#include "TMath.h"
#include "TString.h"

#include <iostream>

#define MAX_TCALPAR 64000

using std::cout;
using std::endl;

// ---- Standard Constructor ---------------------------------------------------
FrsSciTcalPar::FrsSciTcalPar(const char* name, const char* title, const char* context)
    : FairParGenericSet(name, title, context)
    , fNumDetectors(2)
    , fNumChannels(2)
    , fNumTcalParsPerSignal(10)
{
    fNumSignals = fNumDetectors * fNumChannels;
    fAllSignalsTcalParams = new TArrayF(MAX_TCALPAR);
}

// ----  Destructor ------------------------------------------------------------
FrsSciTcalPar::~FrsSciTcalPar()
{
    clear();
    if (fAllSignalsTcalParams)
    {
        delete fAllSignalsTcalParams;
    }
}

// ----  Method clear ----------------------------------------------------------
void FrsSciTcalPar::clear()
{
    status = kFALSE;
    resetInputVersions();
}

// ----  Method putParams ------------------------------------------------------
void FrsSciTcalPar::putParams(FairParamList* list)
{
    LOG(INFO) << "FrsSciTcalPar::putParams() called";
    if (!list)
    {
        return;
    }

    Int_t array_size = fNumSignals * fNumTcalParsPerSignal;
    LOG(INFO) << "Array Size: " << array_size;

    fAllSignalsTcalParams->Set(array_size);

    list->add("TcalPar", *fAllSignalsTcalParams);
    list->add("nDetectorsTcalPar", fNumDetectors);
    list->add("nChannelsTcalPar", fNumChannels);
    list->add("nSignalsTcalPar", fNumSignals);
    list->add("nTcalParsPerSignal", fNumTcalParsPerSignal);
}

// ----  Method getParams ------------------------------------------------------
Bool_t FrsSciTcalPar::getParams(FairParamList* list)
{
    LOG(INFO) << "FrsSciTcalPar::getParams() called";
    if (!list)
    {
        return kFALSE;
    }
    if (!list->fill("nDetectorsTcalPar", &fNumDetectors))
    {
        return kFALSE;
    }
    if (!list->fill("nChannelsTcalPar", &fNumChannels))
    {
        return kFALSE;
    }
    if (!list->fill("nSignalsTcalPar", &fNumSignals))
    {
        return kFALSE;
    }
    if (!list->fill("nTcalParsPerSignal", &fNumTcalParsPerSignal))
    {
        return kFALSE;
    }

    Int_t array_size = fNumSignals * fNumTcalParsPerSignal;
    LOG(INFO) << "Array Size: " << array_size;
    fAllSignalsTcalParams->Set(array_size);

    if (!(list->fill("TcalPar", fAllSignalsTcalParams)))
    {
        LOG(INFO) << "---Could not initialize fAllSignalsTcalParams";
        return kFALSE;
    }

    return kTRUE;
}

// ----  Method printParams ----------------------------------------------------
void FrsSciTcalPar::printParams()
{
    LOG(INFO) << "FrsSciTcalPar: SofTcal Parameters: ";
    Int_t array_size = fNumSignals * fNumTcalParsPerSignal;

    for (Int_t d = 0; d < fNumDetectors; d++)
    {
        for (Int_t ch = 0; ch < fNumChannels; ch++)
        {
            Int_t sig = d * fNumChannels + ch;
            cout << "--- --------------------------------------------" << endl;
            cout << "--- Vftx Tcal Param for signal number: " << sig << endl;
            cout << "---       detector " << d + 1 << endl;
            cout << "---       channel " << ch + 1 << endl;
            cout << "--- --------------------------------------------" << endl;
            /*
              for (Int_t bin = 0; bin < fNumTcalParsPerSignal; bin++)
              {
              cout << "FineTime at Bin (" << bin << ") = " << fAllSignalsTcalParams->GetAt(sig * 1000 + bin)
              << endl;
              }
            */
        }
    }
}

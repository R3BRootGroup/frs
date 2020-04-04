#include "FrsSciTcalData.h"

FrsSciTcalData::FrsSciTcalData()
    : fDetector(0)
    , fPmt(0)
    , fRawTimeNs(0)
{
}

FrsSciTcalData::FrsSciTcalData(UShort_t detector, UShort_t pmt, Double_t tns)
    : fDetector(detector)
    , fPmt(pmt)
    , fRawTimeNs(tns)
{
}
ClassImp(FrsSciTcalData)

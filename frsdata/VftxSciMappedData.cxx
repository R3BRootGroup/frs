#include "VftxSciMappedData.h"

VftxSciMappedData::VftxSciMappedData()
    : fDetector(0)
    , fPmt(0)
    , fTimeCoarse(0)
    , fTimeFine(0)
{
}

VftxSciMappedData::VftxSciMappedData(UShort_t detector, UShort_t pmt, UInt_t tc, UInt_t tf)
    : fDetector(detector)
    , fPmt(pmt)
    , fTimeCoarse(tc)
    , fTimeFine(tf)
{
}

ClassImp(VftxSciMappedData)

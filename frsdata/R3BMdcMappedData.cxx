// ---------------------------------------------------------------------------
// -----                                                                 -----
// -----                      R3BMdcMappedData                           -----
// -----                  Created 23/09/2018 by J.L. Rodriguez           -----
// -----                                                                 -----
// ---------------------------------------------------------------------------

#include "R3BMdcMappedData.h"

R3BMdcMappedData::R3BMdcMappedData()
    : fAnodeId(0)
    , fEnergy(0)
{
}

//------------------------------

R3BMdcMappedData::R3BMdcMappedData(Int_t anodeId, Int_t energy)
    : fAnodeId(anodeId)
    , fEnergy(energy)
{
}

ClassImp(R3BMdcMappedData)

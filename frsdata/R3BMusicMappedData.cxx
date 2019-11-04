// ---------------------------------------------------------------------------
// -----                                                                 -----
// -----                      R3BMusicMappedData                         -----
// -----                  Created 21/07/2018 by J.L. Rodriguez           -----
// -----                                                                 -----
// ---------------------------------------------------------------------------

#include "R3BMusicMappedData.h"

R3BMusicMappedData::R3BMusicMappedData()
    : fDetId(0)
    , fAnodeId(0)
    , fEnergy(0)
{
}

//------------------------------

R3BMusicMappedData::R3BMusicMappedData(Int_t detId, Int_t anodeId, Int_t energy)
    : fDetId(detId)
    , fAnodeId(anodeId)
    , fEnergy(energy)
{
}

ClassImp(R3BMusicMappedData)

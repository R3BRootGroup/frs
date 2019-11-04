// ---------------------------------------------------------------------------
// -----                                                                 -----
// -----                      R3BMusicCalData                         -----
// -----                  Created 21/07/2018 by J.L. Rodriguez           -----
// -----                                                                 -----
// ---------------------------------------------------------------------------

#include "R3BMusicCalData.h"

R3BMusicCalData::R3BMusicCalData()
    : fDetId(0)
    , fAnodeId(0)
    , fEnergy(0)
{
}

//------------------------------

R3BMusicCalData::R3BMusicCalData(Int_t detId, Int_t anodeId, Int_t energy)
    : fDetId(detId)
    , fAnodeId(anodeId)
    , fEnergy(energy)
{
}

ClassImp(R3BMusicCalData)

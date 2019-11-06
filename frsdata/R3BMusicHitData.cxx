// ---------------------------------------------------------------------------
// -----                                                                 -----
// -----                      R3BMusicHitData                         -----
// -----                  Created 21/07/2018 by J.L. Rodriguez           -----
// -----                                                                 -----
// ---------------------------------------------------------------------------

#include "R3BMusicHitData.h"

R3BMusicHitData::R3BMusicHitData()
    : fDetId(0)
    , fCharge(0)
{
}

//------------------------------

R3BMusicHitData::R3BMusicHitData(Int_t detId, Double_t charge)
    : fDetId(detId)
    , fCharge(charge)
{
}

ClassImp(R3BMusicHitData)

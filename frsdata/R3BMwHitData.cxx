// ---------------------------------------------------------------------------
// -----                                                                 -----
// -----                      R3BMwHitData                              -----
// -----                  Created 29/07/2018 by J.L. Rodriguez           -----
// -----                                                                 -----
// ---------------------------------------------------------------------------

#include "R3BMwHitData.h"

R3BMwHitData::R3BMwHitData()
    : fDetId(0)
    , fX(-500)
    , fY(-500)
{
}

//------------------------------

R3BMwHitData::R3BMwHitData(Int_t detId, Double_t x, Double_t y)
    : fDetId(detId)
    , fX(x)
    , fY(y)
{
}

ClassImp(R3BMwHitData)

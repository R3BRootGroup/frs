// ---------------------------------------------------------------------------
// -----                                                                 -----
// -----                      R3BTpcHitData                              -----
// -----                  Created 29/07/2018 by J.L. Rodriguez           -----
// -----                                                                 -----
// ---------------------------------------------------------------------------

#include "R3BTpcHitData.h"

R3BTpcHitData::R3BTpcHitData()
    : fDetId(0)
    , fX(-500)
    , fY(-500)
{}

//------------------------------

R3BTpcHitData::R3BTpcHitData(Int_t detId, Double_t x, Double_t y)
    : fDetId(detId)
    , fX(x)
    , fY(y)
{}

ClassImp(R3BTpcHitData)

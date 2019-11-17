// ---------------------------------------------------------------------------
// -----                                                                 -----
// -----                      FRSMusicHitData                         -----
// -----                  Created 21/07/2018 by J.L. Rodriguez           -----
// -----                                                                 -----
// ---------------------------------------------------------------------------

#include "FRSMusicHitData.h"

FRSMusicHitData::FRSMusicHitData()
    : fDetId(0)
    , fCharge(0)
{
}

//------------------------------

FRSMusicHitData::FRSMusicHitData(Int_t detId, Double_t charge)
    : fDetId(detId)
    , fCharge(charge)
{
}

ClassImp(FRSMusicHitData)

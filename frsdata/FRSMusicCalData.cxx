// ---------------------------------------------------------------------------
// -----                                                                 -----
// -----                      FRSMusicCalData                            -----
// -----                  Created 21/07/2018 by J.L. Rodriguez           -----
// -----                                                                 -----
// ---------------------------------------------------------------------------

#include "FRSMusicCalData.h"

FRSMusicCalData::FRSMusicCalData()
    : fDetId(0)
    , fAnodeId(0)
    , fEnergy(0)
{
}

//------------------------------

FRSMusicCalData::FRSMusicCalData(Int_t detId, Int_t anodeId, Int_t energy)
    : fDetId(detId)
    , fAnodeId(anodeId)
    , fEnergy(energy)
{
}

ClassImp(FRSMusicCalData)

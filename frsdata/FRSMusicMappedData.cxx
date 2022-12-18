// ---------------------------------------------------------------------------
// -----                                                                 -----
// -----                      FRSMusicMappedData                         -----
// -----                  Created 21/07/2018 by J.L. Rodriguez           -----
// -----                                                                 -----
// ---------------------------------------------------------------------------

#include "FRSMusicMappedData.h"

FRSMusicMappedData::FRSMusicMappedData()
    : fDetId(0)
    , fAnodeId(0)
    , fEnergy(0)
{}

//------------------------------

FRSMusicMappedData::FRSMusicMappedData(Int_t detId, Int_t anodeId, Int_t energy)
    : fDetId(detId)
    , fAnodeId(anodeId)
    , fEnergy(energy)
{}

ClassImp(FRSMusicMappedData)

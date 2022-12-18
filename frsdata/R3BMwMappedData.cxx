// ---------------------------------------------------------------------------
// -----                                                                 -----
// -----                      R3BMwMappedData                            -----
// -----                  Created 27/03/2019 by J.L. Rodriguez           -----
// -----                                                                 -----
// ---------------------------------------------------------------------------

#include "R3BMwMappedData.h"

R3BMwMappedData::R3BMwMappedData()
    : fDetId(0)
    , fAn(0)
    , fXr(0)
    , fXl(0)
    , fYu(0)
    , fYd(0)
{}

//------------------------------

R3BMwMappedData::R3BMwMappedData(Int_t detId, Double_t an, Double_t xr, Double_t xl, Double_t yu, Double_t yd)
    : fDetId(detId)
    , fAn(an)
    , fXr(xr)
    , fXl(xl)
    , fYu(yu)
    , fYd(yd)
{}

ClassImp(R3BMwMappedData)

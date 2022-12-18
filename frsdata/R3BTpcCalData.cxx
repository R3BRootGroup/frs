// ---------------------------------------------------------------------------
// -----                                                                 -----
// -----                      R3BTpcCalData                              -----
// -----                  Created 29/07/2018 by J.L. Rodriguez           -----
// -----                                                                 -----
// ---------------------------------------------------------------------------

#include "R3BTpcCalData.h"

R3BTpcCalData::R3BTpcCalData()
    : fDetId(0)
    , fXYId(0)
    , fSecId(0)
    , fPos(-500.)
    , fControlPar(0)
{}

//------------------------------

R3BTpcCalData::R3BTpcCalData(Int_t detId, Int_t xyId, Int_t secId, Double_t position, Double_t controlpar)
    : fDetId(detId)
    , fXYId(xyId)
    , fSecId(secId)
    , fPos(position)
    , fControlPar(controlpar)
{}

ClassImp(R3BTpcCalData)

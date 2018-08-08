// ---------------------------------------------------------------------------
// -----                                                                 -----
// -----                      R3BFrsData                                 -----
// -----                  Created 29/07/2018 by J.L. Rodriguez           -----
// -----                                                                 -----
// ---------------------------------------------------------------------------

#include "R3BFrsData.h"

R3BFrsData::R3BFrsData()
  : fZ(0),
    fAq(0)
{
}

//------------------------------

R3BFrsData::R3BFrsData(Double_t z, Double_t aq)
  : fZ(z),
    fAq(aq)
{
}


ClassImp(R3BFrsData)

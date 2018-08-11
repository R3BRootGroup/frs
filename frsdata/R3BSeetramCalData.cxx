// ---------------------------------------------------------------------------
// -----                                                                 -----
// -----                      R3BSeetramCalData                       -----
// -----                  Created 10/08/2018 by J.L. Rodriguez           -----
// -----                                                                 -----
// ---------------------------------------------------------------------------

#include "R3BSeetramCalData.h"

R3BSeetramCalData::R3BSeetramCalData()
  : fSeeCounts(0),
    fClock1seg(0)
{
}

//------------------------------

R3BSeetramCalData::R3BSeetramCalData(Int_t SeeCounts, Int_t Clock1seg)
  : fSeeCounts(SeeCounts),
    fClock1seg(Clock1seg)
{
}

ClassImp(R3BSeetramCalData)

// ---------------------------------------------------------------------------
// -----                                                                 -----
// -----                      R3BSeetramCalData                       -----
// -----                  Created 10/08/2018 by J.L. Rodriguez           -----
// -----                                                                 -----
// ---------------------------------------------------------------------------

#include "R3BSeetramCalData.h"

R3BSeetramCalData::R3BSeetramCalData()
    : fAcctrig(0)
    , fFreetrig(0)
    , fSeeCounts(0)
    , fIcCounts(0)
    , fDumCounts(0)
    , fSci00Counts(0)
    , fSci01Counts(0)
    , fSci02Counts(0)
    , fClock1seg(0)
{}

//------------------------------

R3BSeetramCalData::R3BSeetramCalData(Int_t AccTriggerCounts,
                                     Int_t FreeTriggerCounts,
                                     Int_t SeeCounts,
                                     Int_t IcCounts,
                                     Int_t DumCounts,
                                     Int_t Sci00Counts,
                                     Int_t Sci01Counts,
                                     Int_t Sci02Counts,
                                     Int_t Clock1seg)
    : fAcctrig(AccTriggerCounts)
    , fFreetrig(FreeTriggerCounts)
    , fSeeCounts(SeeCounts)
    , fIcCounts(IcCounts)
    , fDumCounts(DumCounts)
    , fSci00Counts(Sci00Counts)
    , fSci01Counts(Sci01Counts)
    , fSci02Counts(Sci02Counts)
    , fClock1seg(Clock1seg)
{}

ClassImp(R3BSeetramCalData)

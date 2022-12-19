// ----------------------------------------------------------------
// -----              R3BFrsMappedData               -----
// -----             Created 19-01-2018 by Rodriguez             -----
// ----------------------------------------------------------------

#include "R3BFrsMappedData.h"

R3BFrsMappedData::R3BFrsMappedData()
    : fAccTrig(0)
    , fClock100kHz(0)
    , fClock10Hz(0)
    , fClock1Hz(0)
    , fTrigger(-1)
    , fFreeTrig(0)
    , fSpill(0)
    , fSeenew(0)
    , fSeeold(0)
    , fIc(0)
    , fSCI00(0)
    , fSCI01(0)
    , fSCI02(0)
    , fSCI21RT(0)
    , fSCI41RT(0)
    , fSCI42RT(0)
    , fSCI43RT(0)
    , fSCI21LT(0)
    , fSCI41LT(0)
    , fSCI42LT(0)
    , fSCI43LT(0)
    , fSCI21RE(0)
    , fSCI41RE(0)
    , fSCI42RE(0)
    , fSCI43RE(0)
    , fSCI21LE(0)
    , fSCI41LE(0)
    , fSCI42LE(0)
    , fSCI43LE(0)
{
}

R3BFrsMappedData::R3BFrsMappedData(Int_t AccTrig,
                                   Int_t Clock100kHz,
                                   Int_t Clock1Hz,
                                   Int_t Clock10Hz,
                                   Int_t Trigger,
                                   Int_t FreeTrig,
                                   Int_t Spill,
                                   Int_t Seenew,
                                   Int_t Seeold,
                                   Int_t Ic,
                                   Int_t SCI00,
                                   Int_t SCI01,
                                   Int_t SCI02,
                                   Int_t SCI21LE,
                                   Int_t SCI21RE,
                                   Int_t SCI21LT,
                                   Int_t SCI21RT,
                                   Int_t SCI41LE,
                                   Int_t SCI41RE,
                                   Int_t SCI41LT,
                                   Int_t SCI41RT,
                                   Int_t SCI42LE,
                                   Int_t SCI42RE,
                                   Int_t SCI42LT,
                                   Int_t SCI42RT,
                                   Int_t SCI43LE,
                                   Int_t SCI43RE,
                                   Int_t SCI43LT,
                                   Int_t SCI43RT,
                                   Int_t SCI81LE,
                                   Int_t SCI81RE,
                                   Int_t SCI81LT,
                                   Int_t SCI81RT)
    : fAccTrig(AccTrig)
    , fClock100kHz(Clock100kHz)
    , fClock10Hz(Clock10Hz)
    , fClock1Hz(Clock1Hz)
    , fTrigger(Trigger)
    , fFreeTrig(FreeTrig)
    , fSpill(Spill)
    , fSeenew(Seenew)
    , fSeeold(Seeold)
    , fIc(Ic)
    , fSCI00(SCI00)
    , fSCI01(SCI01)
    , fSCI02(SCI02)
    , fSCI21LE(SCI21LE)
    , fSCI21RE(SCI21RE)
    , fSCI21LT(SCI21LT)
    , fSCI21RT(SCI21RT)
    , fSCI41LE(SCI41LE)
    , fSCI41RE(SCI41RE)
    , fSCI41LT(SCI41LT)
    , fSCI41RT(SCI41RT)
    , fSCI42LE(SCI42LE)
    , fSCI42RE(SCI42RE)
    , fSCI42LT(SCI42LT)
    , fSCI42RT(SCI42RT)
    , fSCI43LE(SCI43LE)
    , fSCI43RE(SCI43RE)
    , fSCI43LT(SCI43LT)
    , fSCI43RT(SCI43RT)
    , fSCI81LE(SCI81LE)
    , fSCI81RE(SCI81RE)
    , fSCI81LT(SCI81LT)
    , fSCI81RT(SCI81RT)
{
}

R3BFrsMappedData::R3BFrsMappedData(const R3BFrsMappedData& right)
    : fAccTrig(right.fAccTrig)
    , fClock100kHz(right.fClock100kHz)
    , fClock10Hz(right.fClock10Hz)
    , fClock1Hz(right.fClock1Hz)
    , fTrigger(right.fTrigger)
    , fFreeTrig(right.fFreeTrig)
    , fSpill(right.fSpill)
    , fSeenew(right.fSeenew)
    , fSeeold(right.fSeeold)
    , fIc(right.fIc)
    , fSCI00(right.fSCI00)
    , fSCI01(right.fSCI01)
    , fSCI02(right.fSCI02)
    , fSCI21RT(right.fSCI21RT)
    , fSCI41RT(right.fSCI41RT)
    , fSCI42RT(right.fSCI42RT)
    , fSCI43RT(right.fSCI43RT)
    , fSCI21LT(right.fSCI21LT)
    , fSCI41LT(right.fSCI41LT)
    , fSCI42LT(right.fSCI42LT)
    , fSCI43LT(right.fSCI43LT)
    , fSCI21RE(right.fSCI21RE)
    , fSCI41RE(right.fSCI41RE)
    , fSCI42RE(right.fSCI42RE)
    , fSCI43RE(right.fSCI43RE)
    , fSCI21LE(right.fSCI21LE)
    , fSCI41LE(right.fSCI41LE)
    , fSCI42LE(right.fSCI42LE)
    , fSCI43LE(right.fSCI43LE)
{
}

ClassImp(R3BFrsMappedData)

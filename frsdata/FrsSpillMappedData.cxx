// ----------------------------------------------------------------
// -----              FrsSpillMappedData                      -----
// -----             Created 16-11-2019 by Rodriguez          -----
// ----------------------------------------------------------------

#include "FrsSpillMappedData.h"

FrsSpillMappedData::FrsSpillMappedData()
    : fClock100kHz(0)
    , fClock10Hz(0)
    , fClock1Hz(0)
    , fAccTrig(0)
    , fFreeTrig(0)
    , fSeenew(0)
    , fSeeold(0)
    , fIC01(0)
    , fICC(0)
    , fSCI00(0)
    , fSCI01(0)
    , fSCI02(0)
    , fSCI21R(0)
    , fSCI41R(0)
    , fSCI42R(0)
    , fSCI43R(0)
    , fSCI81R(0)
    , fSCI21L(0)
    , fSCI41L(0)
    , fSCI42L(0)
    , fSCI43L(0)
    , fSCI81L(0)
{}

FrsSpillMappedData::FrsSpillMappedData(Int_t Clock100kHz,
                                       Int_t Clock10Hz,
                                       Int_t Clock1Hz,
                                       Int_t StartExt,
                                       Int_t StopExt,
                                       Int_t AccTrig,
                                       Int_t FreeTrig,
                                       Int_t Seenew,
                                       Int_t Seeold,
                                       Int_t IC01,
                                       Int_t ICC,
                                       Int_t SCI00,
                                       Int_t SCI01,
                                       Int_t SCI02,
                                       Int_t SCI21L,
                                       Int_t SCI21R,
                                       Int_t SCI41L,
                                       Int_t SCI41R,
                                       Int_t SCI42L,
                                       Int_t SCI42R,
                                       Int_t SCI43L,
                                       Int_t SCI43R,
                                       Int_t SCI81L,
                                       Int_t SCI81R)
    : fClock100kHz(Clock100kHz)
    , fClock10Hz(Clock10Hz)
    , fClock1Hz(Clock1Hz)
    , fStartExt(StartExt)
    , fStopExt(StopExt)
    , fAccTrig(AccTrig)
    , fFreeTrig(FreeTrig)
    , fSeenew(Seenew)
    , fSeeold(Seeold)
    , fIC01(IC01)
    , fICC(ICC)
    , fSCI00(SCI00)
    , fSCI01(SCI01)
    , fSCI02(SCI02)
    , fSCI21L(SCI21L)
    , fSCI21R(SCI21R)
    , fSCI41L(SCI41L)
    , fSCI41R(SCI41R)
    , fSCI42L(SCI42L)
    , fSCI42R(SCI42R)
    , fSCI43L(SCI43L)
    , fSCI43R(SCI43R)
    , fSCI81L(SCI81L)
    , fSCI81R(SCI81R)
{}

FrsSpillMappedData::FrsSpillMappedData(const FrsSpillMappedData& right)
    : fClock100kHz(right.fClock100kHz)
    , fClock10Hz(right.fClock10Hz)
    , fClock1Hz(right.fClock1Hz)
    , fStartExt(right.fStartExt)
    , fStopExt(right.fStopExt)
    , fAccTrig(right.fAccTrig)
    , fFreeTrig(right.fFreeTrig)
    , fSeenew(right.fSeenew)
    , fSeeold(right.fSeeold)
    , fIC01(right.fIC01)
    , fICC(right.fICC)
    , fSCI00(right.fSCI00)
    , fSCI01(right.fSCI01)
    , fSCI02(right.fSCI02)
    , fSCI21R(right.fSCI21R)
    , fSCI41R(right.fSCI41R)
    , fSCI42R(right.fSCI42R)
    , fSCI43R(right.fSCI43R)
    , fSCI81R(right.fSCI81R)
    , fSCI21L(right.fSCI21L)
    , fSCI41L(right.fSCI41L)
    , fSCI42L(right.fSCI42L)
    , fSCI43L(right.fSCI43L)
    , fSCI81L(right.fSCI81L)
{}

ClassImp(FrsSpillMappedData)

// -------------------------------------------------------------
// -----              FrsSpillMappedData                   -----
// -----         Created 16-11-2019 by Jose Luis Rodriguez -----
// -------------------------------------------------------------

#ifndef FrsSpillMappedData_H
#define FrsSpillMappedData_H

#include "TObject.h"

class FrsSpillMappedData : public TObject
{
  public:
    // Default Constructor
    FrsSpillMappedData();

    /** Standard Constructor
     **/
    FrsSpillMappedData(Int_t Clock100kHz,
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
                       Int_t SCI81R);

    FrsSpillMappedData(const FrsSpillMappedData&);

    // Destructor
    virtual ~FrsSpillMappedData() {}

    // Getters
    inline Int_t GetClock100kHz() { return fClock100kHz; }
    inline Int_t GetClock10Hz() { return fClock10Hz; }
    inline Int_t GetClock1Hz() { return fClock1Hz; }

    inline Int_t GetStartExt() { return fStartExt; }
    inline Int_t GetStopExt() { return fStopExt; }
    inline Int_t GetAccTrig() { return fAccTrig; }
    inline Int_t GetFreeTrig() { return fFreeTrig; }

    inline Int_t GetSeetramNew() { return fSeenew; }
    inline Int_t GetSeetramOld() { return fSeeold; }
    inline Int_t GetIc01() { return fIC01; }
    inline Int_t GetIcc() { return fICC; }
    inline Int_t GetSCI00() { return fSCI00; }
    inline Int_t GetSCI01() { return fSCI01; }
    inline Int_t GetSCI02() { return fSCI02; }

    inline Int_t GetSCI21L() { return fSCI21L; }
    inline Int_t GetSCI41L() { return fSCI41L; }
    inline Int_t GetSCI42L() { return fSCI42L; }
    inline Int_t GetSCI43L() { return fSCI43L; }
    inline Int_t GetSCI81L() { return fSCI81L; }

    inline Int_t GetSCI21R() { return fSCI21R; }
    inline Int_t GetSCI41R() { return fSCI41R; }
    inline Int_t GetSCI42R() { return fSCI42R; }
    inline Int_t GetSCI43R() { return fSCI43R; }
    inline Int_t GetSCI81R() { return fSCI81R; }

  protected:
    Int_t fClock100kHz;
    Int_t fClock10Hz;
    Int_t fClock1Hz;
    Int_t fStartExt;
    Int_t fStopExt;
    Int_t fAccTrig;
    Int_t fFreeTrig;
    Int_t fSeenew;
    Int_t fSeeold;
    Int_t fIC01;
    Int_t fICC;
    Int_t fSCI00, fSCI01, fSCI02;             // plastics at S0
    Int_t fSCI21R, fSCI41R, fSCI42R, fSCI43R; // R plastics at S2 and S4
    Int_t fSCI21L, fSCI41L, fSCI42L, fSCI43L; // L plastics at S2 and S4
    Int_t fSCI81L, fSCI81R;                   // plastic at S8

  public:
    ClassDef(FrsSpillMappedData, 1)
};

#endif

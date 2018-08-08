// -------------------------------------------------------------
// -----              R3BFrsMappedData                     -----
// -----         Created 19-01-2018 by Jose Luis Rodriguez -----
// -------------------------------------------------------------

#ifndef R3BFRSMAPPEDITEM_H
#define R3BFRSMAPPEDITEM_H

#include "TObject.h"

class R3BFrsMappedData : public TObject
{
  public:
    // Default Constructor
    R3BFrsMappedData();

    /** Standard Constructor
     **/
    R3BFrsMappedData( Int_t AccTrig,Int_t Clock100Hz,Int_t Clock1Hz,Int_t Clock10Hz,Int_t DeadTime,Int_t FreeTrig, Int_t Spill, Int_t Seenew
, Int_t SCI00
, Int_t SCI01
, Int_t SCI02
, Int_t SCI21LE
, Int_t SCI21RE
, Int_t SCI21LT
, Int_t SCI21RT
, Int_t SCI41LE
, Int_t SCI41RE
, Int_t SCI41LT
, Int_t SCI41RT
, Int_t SCI42LE
, Int_t SCI42RE
, Int_t SCI42LT
, Int_t SCI42RT
, Int_t SCI43LE
, Int_t SCI43RE
, Int_t SCI43LT
, Int_t SCI43RT
, Int_t SCI81LE
, Int_t SCI81RE
, Int_t SCI81LT
, Int_t SCI81RT
);


    R3BFrsMappedData(const R3BFrsMappedData&);
   
    // Destructor
    virtual ~R3BFrsMappedData(){ }

  //Getters
  inline  Int_t GetSeetramNew() { return fSeenew;   }
  inline  Int_t GetSpill()      { return fSpill;  } 
  inline  Int_t GetAccTrig()    { return fAccTrig;  } 
  inline  Int_t GetDeadTime()   { return fDeadTime;  } 
  inline  Int_t GetFreeTrig()   { return fFreeTrig;  } 
  inline  Int_t GetClock100Hz() { return fClock100Hz;  } 
  inline  Int_t GetClock10Hz()  { return fClock10Hz;  } 
  inline  Int_t GetClock1Hz()   { return fClock1Hz;  } 

  inline  Int_t GetSCI00()      { return fSCI00; }
  inline  Int_t GetSCI01()      { return fSCI01; }
  inline  Int_t GetSCI02()      { return fSCI02; }

  inline  Int_t GetSCI21LT()      { return fSCI21LT; }
  inline  Int_t GetSCI41LT()      { return fSCI41LT; }
  inline  Int_t GetSCI42LT()      { return fSCI42LT; }
  inline  Int_t GetSCI43LT()      { return fSCI43LT; }
  inline  Int_t GetSCI81LT()      { return fSCI81LT; }

  inline  Int_t GetSCI21LE()      { return fSCI21LE; }
  inline  Int_t GetSCI41LE()      { return fSCI41LE; }
  inline  Int_t GetSCI42LE()      { return fSCI42LE; }
  inline  Int_t GetSCI43LE()      { return fSCI43LE; }
  inline  Int_t GetSCI81LE()      { return fSCI81LE; }

  inline  Int_t GetSCI21RT()      { return fSCI21RT; }
  inline  Int_t GetSCI41RT()      { return fSCI41RT; }
  inline  Int_t GetSCI42RT()      { return fSCI42RT; }
  inline  Int_t GetSCI43RT()      { return fSCI43RT; }
  inline  Int_t GetSCI81RT()      { return fSCI81RT; }

  inline  Int_t GetSCI21RE()      { return fSCI21RE; }
  inline  Int_t GetSCI41RE()      { return fSCI41RE; }
  inline  Int_t GetSCI42RE()      { return fSCI42RE; }
  inline  Int_t GetSCI43RE()      { return fSCI43RE; }
  inline  Int_t GetSCI81RE()      { return fSCI81RE; }



  protected:

    Int_t fAccTrig;
    Int_t fClock100Hz;
    Int_t fClock1Hz;
    Int_t fClock10Hz;
    Int_t fDeadTime;
    Int_t fFreeTrig;
    Int_t fSpill;
    Int_t fSeenew;

    Int_t fSCI00,fSCI01,fSCI02;//plastics at S0

    Int_t fSCI21RT,fSCI41RT,fSCI42RT,fSCI43RT;//time right pm of plastics at S2 and S4
    Int_t fSCI21LT,fSCI41LT,fSCI42LT,fSCI43LT;//time left pm of plastics at S2 and S4
    Int_t fSCI21RE,fSCI41RE,fSCI42RE,fSCI43RE;//energy right pm of plastics at S2 and S4
    Int_t fSCI21LE,fSCI41LE,fSCI42LE,fSCI43LE;//energy left pm of plastics at S2 and S4

    Int_t fSCI81LE,fSCI81RE,fSCI81LT,fSCI81RT;//energy and time for plastics at S8


  public:
    ClassDef(R3BFrsMappedData, 1)
};

#endif


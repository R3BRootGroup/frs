// ---------------------------------------------------------------------------
// -----                                                                 -----
// -----                      R3BSeetramCalData                       -----
// -----                  Created 10/08/2018 by J.L. Rodriguez           -----
// -----                                                                 -----
// ---------------------------------------------------------------------------

#ifndef R3BSeetramCalData_H
#define R3BSeetramCalData_H
#include "TObject.h"

class R3BSeetramCalData : public TObject {

public:
  // Default Constructor
  R3BSeetramCalData();
  
  /** Standard Constructor
   *@param AccTrigerCounts   Accepted trigger counter
   *@param FreeTriggerCounts Free trigger counter
   *@param SeeCounts         Seetram counter
   *@param IcCounts          Ic counter
   *@param DumCounts         Dummy counter
   *@param Sci00Counts       Sci00 counter
   *@param Sci01Counts       Sci01 counter
   *@param Sci02Counts       Sci02 counter
   *@param Clock1seg         Anode unique identifier
   **/
  R3BSeetramCalData(Int_t AccTrigger, Int_t FreeTrigger, Int_t SeeCounts, Int_t IcCounts, Int_t DumCounts, Int_t Sci00Counts, Int_t Sci01Counts, Int_t Sci02Counts, Int_t Clock1seg);
  
  //Destructor
  ~R3BSeetramCalData() { }
  
  //Getters
  inline const Int_t GetAccTrigCounts() const { return fAcctrig;  }
  inline const Int_t GetFreeTrigCounts() const{ return fFreetrig;  }
  inline const Int_t GetSeeCounts() const     { return fSeeCounts;  }
  inline const Int_t GetIcCounts() const      { return fIcCounts;   }
  inline const Int_t GetDumCounts() const     { return fDumCounts;  }
  inline const Int_t GetSci00Counts() const   { return fSci00Counts;}
  inline const Int_t GetSci01Counts() const   { return fSci01Counts;}
  inline const Int_t GetSci02Counts() const   { return fSci02Counts;}
  inline const Int_t GetClock1seg() const     { return fClock1seg;  }
  
protected:
  Int_t fAcctrig, fFreetrig;     //
  Int_t fSeeCounts, fClock1seg;  //
  Int_t fIcCounts, fDumCounts;   //
  Int_t fSci00Counts, fSci01Counts, fSci02Counts;  // 
   
public:
  ClassDef(R3BSeetramCalData,1)
};

#endif

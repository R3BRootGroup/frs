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
   *@param fSeeCounts     Detector unique identifier
   *@param fClock1seg     Anode unique identifier
   **/
  R3BSeetramCalData(Int_t fSeeCounts, Int_t fClock1seg);
  
  //Destructor
  ~R3BSeetramCalData() { }
  
  //Getters
  inline const Int_t& GetSeeCounts() const { return fSeeCounts; }
  inline const Int_t& GetClock1seg() const { return fClock1seg; }
  
protected:
  Int_t fSeeCounts, fClock1seg;  // 
   
public:
  ClassDef(R3BSeetramCalData,1)
};

#endif

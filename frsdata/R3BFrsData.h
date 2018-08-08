// ---------------------------------------------------------------------------
// -----                                                                 -----
// -----                      R3BFrsData                                 -----
// -----                  Created 29/07/2018 by J.L. Rodriguez           -----
// -----                                                                 -----
// ---------------------------------------------------------------------------

#ifndef R3BFrsData_H
#define R3BFrsData_H
#include "TObject.h"

class R3BFrsData : public TObject {

public:
  // Default Constructor
  R3BFrsData();
  
  /** Standard Constructor
   *@param fZ      Z of fragments
   *@param fAq     A/q of fragments
   **/
  R3BFrsData(Double_t z, Double_t aq);
  
  //Destructor
  ~R3BFrsData() { }
  
  //Getters
  inline const Double_t& GetZ()     const { return fZ;  }
  inline const Double_t& GetAq()    const { return fAq; }
  
protected:
  Double_t fZ, fAq;  //
   
public:
  ClassDef(R3BFrsData,1)
};

#endif

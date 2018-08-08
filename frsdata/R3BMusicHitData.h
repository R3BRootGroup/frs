// ---------------------------------------------------------------------------
// -----                                                                 -----
// -----                      R3BMusicHitData                            -----
// -----                  Created 12/05/2018 by J.L. Rodriguez           -----
// -----                                                                 -----
// ---------------------------------------------------------------------------

#ifndef R3BMusicHitData_H
#define R3BMusicHitData_H
#include "TObject.h"

class R3BMusicHitData : public TObject {

public:
  // Default Constructor
  R3BMusicHitData();
  
  /** Standard Constructor
   *@param detId       Detector unique identifier
   *@param charge      Total energy deposited in the detector in units of Z
   **/
  R3BMusicHitData(Int_t detId, Double_t charge);
  
  //Destructor
  ~R3BMusicHitData() { }
  
  //Getters
  inline const Int_t& GetDetectorId() const { return fDetId;   }
  inline const Double_t& GetZ()     const { return fCharge;  } 
  
protected:
  Int_t fDetId;  // detector unique identifiers
  Double_t fCharge;        // total energy in units of Z
   
public:
  ClassDef(R3BMusicHitData,1)
};

#endif

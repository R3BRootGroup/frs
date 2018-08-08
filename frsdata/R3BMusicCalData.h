// ---------------------------------------------------------------------------
// -----                                                                 -----
// -----                      R3BMusicCalData                            -----
// -----                  Created 12/05/2018 by J.L. Rodriguez           -----
// -----                                                                 -----
// ---------------------------------------------------------------------------

#ifndef R3BMusicCalData_H
#define R3BMusicCalData_H
#include "TObject.h"

class R3BMusicCalData : public TObject {

public:
  // Default Constructor
  R3BMusicCalData();
  
  /** Standard Constructor
   *@param detId       Detector unique identifier
   *@param anodeId     Anode unique identifier
   *@param energy      Total energy deposited in the anode
   **/
  R3BMusicCalData(Int_t detId, Int_t anodeId, Int_t energy);
  
  //Destructor
  ~R3BMusicCalData() { }
  
  //Getters
  inline const Int_t& GetDetectorId() const { return fDetId;   }
  inline const Int_t& GetAnodeId()    const { return fAnodeId; }
  inline const Int_t& GetEnergy()     const { return fEnergy;  } 
  
protected:
  Int_t fDetId, fAnodeId;  // detector and anode unique identifiers
  Int_t fEnergy;           // total energy in the anode
   
public:
  ClassDef(R3BMusicCalData,1)
};

#endif

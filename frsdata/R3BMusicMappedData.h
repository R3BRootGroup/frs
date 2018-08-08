// ---------------------------------------------------------------------------
// -----                                                                 -----
// -----                      R3BMusicMappedData                         -----
// -----                  Created 12/05/2018 by J.L. Rodriguez           -----
// -----                                                                 -----
// ---------------------------------------------------------------------------

#ifndef R3BMusicMappedData_H
#define R3BMusicMappedData_H
#include "TObject.h"

class R3BMusicMappedData : public TObject {

public:
  // Default Constructor
  R3BMusicMappedData();
  
  /** Standard Constructor
   *@param detId       Detector unique identifier
   *@param anodeId     Anode unique identifier
   *@param energy      Total energy deposited in the anode
   **/
  R3BMusicMappedData(Int_t detId, Int_t anodeId, Int_t energy);
  
  //Destructor
  ~R3BMusicMappedData() { }
  
  //Getters
  inline const Int_t& GetDetectorId() const { return fDetId;   }
  inline const Int_t& GetAnodeId()    const { return fAnodeId; }
  inline const Int_t& GetEnergy()     const { return fEnergy;  } 
  
protected:
  Int_t fDetId, fAnodeId;  // detector and anode unique identifiers
  Int_t fEnergy;           // total energy in the anode
   
public:
  ClassDef(R3BMusicMappedData,1)
};

#endif

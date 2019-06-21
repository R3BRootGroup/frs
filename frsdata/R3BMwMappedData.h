// ---------------------------------------------------------------------------
// -----                                                                 -----
// -----                      R3BMwMappedData                            -----
// -----                  Created 27/03/2019 by J.L. Rodriguez           -----
// -----                                                                 -----
// ---------------------------------------------------------------------------

#ifndef R3BMwMappedData_H
#define R3BMwMappedData_H
#include "TObject.h"

class R3BMwMappedData : public TObject {

public:
  // Default Constructor
  R3BMwMappedData();
  
  /** Standard Constructor
   *@param detId      Detector unique identifier
   *@param
   *@param 
   **/
  R3BMwMappedData(Int_t detId, Double_t an, Double_t xr, Double_t xl, Double_t yu, Double_t yd);
  
  //Destructor
  ~R3BMwMappedData() { }
  
  //Getters
  inline const Int_t GetDetId()  const { return fDetId;}
  inline const Double_t GetAn()   const { return fAn;  }
  inline const Double_t GetXr()   const { return fXr;  } 
  inline const Double_t GetXl()   const { return fXl;  } 
  inline const Double_t GetYu()   const { return fYu;  } 
  inline const Double_t GetYd()   const { return fYd;  } 
  
protected:
  Int_t fDetId;
  Double_t fAn, fXr, fXl, fYu, fYd;
   
public:
  ClassDef(R3BMwMappedData,1)
};

#endif

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
  R3BFrsData(Double_t z, Double_t aq, Double_t xs2, Double_t as2, Double_t xs4, Double_t as4);
  
  //Destructor
  ~R3BFrsData() { }
  
  //Getters
  inline const Double_t GetZ()     const { return fZ;  }
  inline const Double_t GetAq()    const { return fAq; }
  inline const Double_t GetXS2()   const { return fXS2;}
  inline const Double_t GetXS4()   const { return fXS4;}
  inline const Double_t GetAS2()   const { return fAS2;}
  inline const Double_t GetAS4()   const { return fAS4;}
  
protected:
  Double_t fZ, fAq;  //ID
  Double_t fXS2, fAS2;  //Focal info at S2
  Double_t fXS4, fAS4;  //Focal info at S4
   
public:
  ClassDef(R3BFrsData,1)
};

#endif

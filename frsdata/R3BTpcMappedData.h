// ---------------------------------------------------------------------------
// -----                                                                 -----
// -----                      R3BTpcMappedData                           -----
// -----                  Created 12/05/2018 by J.L. Rodriguez           -----
// -----                                                                 -----
// ---------------------------------------------------------------------------

#ifndef R3BTpcMappedData_H
#define R3BTpcMappedData_H
#include "TObject.h"

class TArrayI;

class R3BTpcMappedData : public TObject {

public:
  // Default Constructor
  R3BTpcMappedData();
  
  /** Standard Constructor
   *@param detId       Detector unique identifier
   *@param      Anode unique identifier
   *@param       Total energy deposited in the anode
   **/
   R3BTpcMappedData(Int_t detId, TArrayI* tpc_ae, TArrayI* tpc_le, TArrayI* tpc_re, TArrayI* tpc_dt, TArrayI* tpc_lt, TArrayI* tpc_rt);
  
  //Destructor
  ~R3BTpcMappedData() { }
  
  //Getters
  inline const Int_t& GetDetectorId() const { return fDetId;   }
  TArrayI* GetTpcdt() const { return fTpc_dt; }
  TArrayI* GetTpcrt() const { return fTpc_rt; }
  TArrayI* GetTpclt() const { return fTpc_lt; }
  TArrayI* GetTpcae() const { return fTpc_ae; }
  TArrayI* GetTpcre() const { return fTpc_re; }
  TArrayI* GetTpcle() const { return fTpc_le; }
  
protected:
  Int_t fDetId;  // detector and anode unique identifiers

  /** Arrays **/
  TArrayI* fTpc_ae;
  TArrayI* fTpc_le;
  TArrayI* fTpc_re;
  TArrayI* fTpc_dt;
  TArrayI* fTpc_rt;
  TArrayI* fTpc_lt;

   
public:
  ClassDef(R3BTpcMappedData,1)
};

#endif

// ---------------------------------------------------------------------------
// -----                                                                 -----
// -----                      R3BTpcMappedData                           -----
// -----                  Created 12/05/2018 by J.L. Rodriguez           -----
// -----                                                                 -----
// ---------------------------------------------------------------------------

#ifndef R3BTpcMappedData_H
#define R3BTpcMappedData_H
#include "TObject.h"

class R3BTpcMappedData : public TObject {

public:
  // Default Constructor
  R3BTpcMappedData();
  
  /** Standard Constructor
   *@param detId    Detector unique identifier
   *@param tpc_ae, tpc_le and tpc_re    Energy per anode
   *@param tpc_dt, tpc_lt and tpc_rt    Drift times per anode
   **/
   R3BTpcMappedData(Int_t detId, Int_t tpc_ae[4], Int_t tpc_le[2], Int_t tpc_re[2], Int_t tpc_dt[4], Int_t tpc_lt[2], Int_t tpc_rt[2]);

  //Destructor
  ~R3BTpcMappedData() { }
  
  //Getters
  inline const Int_t GetDetectorId() const { return fDetId;}
  inline const Int_t* GetTpcdt()   const { return ftpc_dt; }
  inline const Int_t* GetTpcrt()   const { return ftpc_rt; }
  inline const Int_t* GetTpclt()   const { return ftpc_lt; }
  inline const Int_t* GetTpcae()   const { return ftpc_ae; }
  inline const Int_t* GetTpcre()   const { return ftpc_re; }
  inline const Int_t* GetTpcle()   const { return ftpc_le; }

protected:
  Int_t fDetId;      // detector unique identifier
  Int_t ftpc_ae[4], ftpc_le[2], ftpc_re[2]; 
  Int_t ftpc_dt[4], ftpc_lt[2], ftpc_rt[2];

public:
  ClassDef(R3BTpcMappedData,1)
};

#endif

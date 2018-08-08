// ---------------------------------------------------------------------------
// -----                                                                 -----
// -----                      R3BTpcMappedData                           -----
// -----                  Created 21/07/2018 by J.L. Rodriguez           -----
// -----                                                                 -----
// ---------------------------------------------------------------------------

#include "R3BTpcMappedData.h"
#include "TArrayI.h"

R3BTpcMappedData::R3BTpcMappedData()
  : fDetId(0)
{

  fTpc_ae = fTpc_re = fTpc_le = fTpc_dt = fTpc_lt = fTpc_rt = NULL;

}

//------------------------------
R3BTpcMappedData::R3BTpcMappedData(Int_t detId, TArrayI* tpc_ae, TArrayI* tpc_le, TArrayI* tpc_re, TArrayI* tpc_dt, TArrayI* tpc_lt, TArrayI* tpc_rt)
  : fDetId(detId)
{
  fTpc_ae = new TArrayI(*(tpc_ae));
  fTpc_le = new TArrayI(*(tpc_le));
  fTpc_re = new TArrayI(*(tpc_re));
  fTpc_dt = new TArrayI(*(tpc_dt));
  fTpc_lt = new TArrayI(*(tpc_lt));
  fTpc_rt = new TArrayI(*(tpc_rt));
}


ClassImp(R3BTpcMappedData)

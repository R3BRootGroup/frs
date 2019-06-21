// ---------------------------------------------------------------------------
// -----                                                                 -----
// -----                      R3BTpcMappedData                           -----
// -----                  Created 21/07/2018 by J.L. Rodriguez           -----
// -----                                                                 -----
// ---------------------------------------------------------------------------

#include "R3BTpcMappedData.h"

R3BTpcMappedData::R3BTpcMappedData()
  : fDetId(0)
{
//Energy
ftpc_ae[0]=0;
ftpc_ae[1]=0;
ftpc_ae[2]=0;
ftpc_ae[3]=0;
ftpc_re[0]=0;
ftpc_re[1]=0;
ftpc_le[0]=0;
ftpc_le[1]=0;
//Drift times
ftpc_dt[0]=0;
ftpc_dt[1]=0;
ftpc_dt[2]=0;
ftpc_dt[3]=0;
ftpc_rt[0]=0;
ftpc_rt[1]=0;
ftpc_lt[0]=0;
ftpc_lt[1]=0;
}

//------------------------------
R3BTpcMappedData::R3BTpcMappedData(Int_t detId, Int_t tpc_ae[4], Int_t tpc_le[2], Int_t tpc_re[2], Int_t tpc_dt[4], Int_t tpc_lt[2], Int_t tpc_rt[2])
  : fDetId(detId)
{
//Energy
ftpc_ae[0]=tpc_ae[0];
ftpc_ae[1]=tpc_ae[1];
ftpc_ae[2]=tpc_ae[2];
ftpc_ae[3]=tpc_ae[3];
ftpc_re[0]=tpc_re[0];
ftpc_re[1]=tpc_re[1];
ftpc_le[0]=tpc_le[0];
ftpc_le[1]=tpc_le[1];
//Drift times
ftpc_dt[0]=tpc_dt[0];
ftpc_dt[1]=tpc_dt[1];
ftpc_dt[2]=tpc_dt[2];
ftpc_dt[3]=tpc_dt[3];
ftpc_rt[0]=tpc_rt[0];
ftpc_rt[1]=tpc_rt[1];
ftpc_lt[0]=tpc_lt[0];
ftpc_lt[1]=tpc_lt[1];
}

ClassImp(R3BTpcMappedData)

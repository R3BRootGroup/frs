// ----------------------------------------------------------------------
// -----            R3BFrsReader source file                        -----
// -----            Created 29/07/18  by J.L. Rodriguez-Sanchez     -----
// ----------------------------------------------------------------------

#include "FairLogger.h"
#include "R3BFrsReader.h"
  
#include "TClonesArray.h"
#include "FairRootManager.h"
#include "R3BFrsMappedData.h"
#include "R3BMusicMappedData.h"
#include "R3BTpcMappedData.h"

#include <iostream>
#include <fstream>
#include <cstring>
#include "Riostream.h"
#include "TROOT.h"
#include "TSystem.h"
#include <stdio.h>
#include "TVectorD.h"

extern "C" {
#include "ext_data_client.h"
#include "ext_h101_frs.h"
}

R3BFrsReader::R3BFrsReader(EXT_STR_h101_FRS* data,
    UInt_t offset)
	: R3BReader("R3BFrsReader"),
  fNEvent(0),
  fData(data),
  fOffset(offset),
  fOnline(kFALSE),
  fLogger(FairLogger::GetLogger()),
  fArray(new TClonesArray("R3BFrsMappedData")),
  fArrayMusic(new TClonesArray("R3BMusicMappedData")),
  fArrayTpc(new TClonesArray("R3BTpcMappedData")) {

}

R3BFrsReader::~R3BFrsReader() {
  if (fArray){
		delete fArray;
	}
  if (fArrayMusic){
		delete fArrayMusic;
	}
  if (fArrayTpc){
		delete fArrayTpc;
	}
}

Bool_t R3BFrsReader::Init(ext_data_struct_info *a_struct_info) {
	int ok;

	EXT_STR_h101_FRS_ITEMS_INFO(ok, *a_struct_info, fOffset,
	    EXT_STR_h101_FRS, 0);

	if (!ok) {
		perror("ext_data_struct_info_item");
		fLogger->Debug(MESSAGE_ORIGIN,
		    "Failed to setup structure information.");
		return kFALSE;
	}

    // Register output array in tree
  if(!fOnline){
    FairRootManager::Instance()->Register("FrsMappedData", "FRS", fArray, kTRUE);
    FairRootManager::Instance()->Register("MusicMappedData", "FRS Musics", fArrayMusic, kTRUE);
    FairRootManager::Instance()->Register("TpcMappedData", "FRS TPCs", fArrayTpc, kTRUE);
  }else{
    FairRootManager::Instance()->Register("FrsMappedData", "FRS", fArray, kFALSE);
    FairRootManager::Instance()->Register("MusicMappedData", "FRS Musics", fArrayMusic, kFALSE);
    FairRootManager::Instance()->Register("TpcMappedData", "FRS TPCs", fArrayTpc, kFALSE);
  }  

	return kTRUE;
}

Bool_t R3BFrsReader::Read() {
  EXT_STR_h101_FRS_onion_t *data =
	    (EXT_STR_h101_FRS_onion_t *) fData;

	/* Display data */
	fLogger->Debug(MESSAGE_ORIGIN, "R3BFrsReader::Read() Event data");

  //Scalers and plastics
  new ((*fArray)[fArray->GetEntriesFast()]) R3BFrsMappedData(
fData->AccTrig,
fData->ClockhundredHz,
fData->ClockoneHz,
fData->ClocktenHz,
fData->DeadTime,
fData->FreeTrig, 
fData->Spill, 
fData->Seenew, 
fData->SCIN1, 
fData->SCIN2, 
fData->SCIN3, 
fData->SC1LdE,
fData->SC1RdE,
fData->SC1Lt,
fData->SC1Rt,
fData->SC2LdE,
fData->SC2RdE,
fData->SC2Lt,
fData->SC2Rt,
fData->SC3LdE,
fData->SC3RdE,
fData->SC3Lt,
fData->SC3Rt,
fData->SC4LdE,
fData->SC4RdE,
fData->SC4Lt,
fData->SC4Rt,
fData->SC5LdE,
fData->SC5RdE,
fData->SC5Lt,
fData->SC5Rt
);

  //Music1-S4
  new ((*fArrayMusic)[fArrayMusic->GetEntriesFast()]) R3BMusicMappedData(0,0,fData->MUS1A1);
  new ((*fArrayMusic)[fArrayMusic->GetEntriesFast()]) R3BMusicMappedData(0,1,fData->MUS1A2);
  new ((*fArrayMusic)[fArrayMusic->GetEntriesFast()]) R3BMusicMappedData(0,2,fData->MUS1A3);
  new ((*fArrayMusic)[fArrayMusic->GetEntriesFast()]) R3BMusicMappedData(0,3,fData->MUS1A4);
  new ((*fArrayMusic)[fArrayMusic->GetEntriesFast()]) R3BMusicMappedData(0,4,fData->MUS1A5);
  new ((*fArrayMusic)[fArrayMusic->GetEntriesFast()]) R3BMusicMappedData(0,5,fData->MUS1A6);
  new ((*fArrayMusic)[fArrayMusic->GetEntriesFast()]) R3BMusicMappedData(0,6,fData->MUS1A7);
  new ((*fArrayMusic)[fArrayMusic->GetEntriesFast()]) R3BMusicMappedData(0,7,fData->MUS1A8);

  //Music2-S4
  new ((*fArrayMusic)[fArrayMusic->GetEntriesFast()]) R3BMusicMappedData(1,0,fData->MUS2A1);
  new ((*fArrayMusic)[fArrayMusic->GetEntriesFast()]) R3BMusicMappedData(1,1,fData->MUS2A2);
  new ((*fArrayMusic)[fArrayMusic->GetEntriesFast()]) R3BMusicMappedData(1,2,fData->MUS2A3);
  new ((*fArrayMusic)[fArrayMusic->GetEntriesFast()]) R3BMusicMappedData(1,3,fData->MUS2A4);
  new ((*fArrayMusic)[fArrayMusic->GetEntriesFast()]) R3BMusicMappedData(1,4,fData->MUS2A5);
  new ((*fArrayMusic)[fArrayMusic->GetEntriesFast()]) R3BMusicMappedData(1,5,fData->MUS2A6);
  new ((*fArrayMusic)[fArrayMusic->GetEntriesFast()]) R3BMusicMappedData(1,6,fData->MUS2A7);
  new ((*fArrayMusic)[fArrayMusic->GetEntriesFast()]) R3BMusicMappedData(1,7,fData->MUS2A8);

  //TPC1-S2
  TArrayI* tpc_ae=new TArrayI(); 
  TArrayI* tpc_le=new TArrayI(); 
  TArrayI* tpc_re=new TArrayI(); 
  TArrayI* tpc_dt=new TArrayI(); 
  TArrayI* tpc_lt=new TArrayI(); 
  TArrayI* tpc_rt=new TArrayI();

  tpc_le->Set(2);
  tpc_re->Set(2);
  tpc_ae->Set(4);
  tpc_dt->Set(4);
  tpc_lt->Set(2);
  tpc_rt->Set(2);

  tpc_rt->AddAt(fData->TPC1RT1,0);
  tpc_rt->AddAt(fData->TPC1RT2,1);
  tpc_lt->AddAt(fData->TPC1LT1,0);
  tpc_lt->AddAt(fData->TPC1LT2,1);

  tpc_dt->AddAt(fData->TPC1DT1,0);
  tpc_dt->AddAt(fData->TPC1DT2,1);
  tpc_dt->AddAt(fData->TPC1DT3,2);
  tpc_dt->AddAt(fData->TPC1DT4,3);

  new ((*fArrayTpc)[fArrayTpc->GetEntriesFast()]) R3BTpcMappedData(0,tpc_ae, tpc_le, tpc_re, tpc_dt, tpc_lt,  tpc_rt);

  //TPC2-S2
  tpc_dt=new TArrayI(); 
  tpc_lt=new TArrayI(); 
  tpc_rt=new TArrayI();
  tpc_dt->Set(4);
  tpc_lt->Set(2);
  tpc_rt->Set(2);

  tpc_rt->AddAt(fData->TPC2RT1,0);
  tpc_rt->AddAt(fData->TPC2RT2,1);
  tpc_lt->AddAt(fData->TPC2LT1,0);
  tpc_lt->AddAt(fData->TPC2LT2,1);

  tpc_dt->AddAt(fData->TPC2DT1,0);
  tpc_dt->AddAt(fData->TPC2DT2,1);
  tpc_dt->AddAt(fData->TPC2DT3,2);
  tpc_dt->AddAt(fData->TPC2DT4,3);

  new ((*fArrayTpc)[fArrayTpc->GetEntriesFast()]) R3BTpcMappedData(1,tpc_ae, tpc_le, tpc_re, tpc_dt, tpc_lt,  tpc_rt);

  //TPC3-S4
  tpc_dt=new TArrayI(); 
  tpc_lt=new TArrayI(); 
  tpc_rt=new TArrayI();
  tpc_dt->Set(4);
  tpc_lt->Set(2);
  tpc_rt->Set(2);

  tpc_rt->AddAt(fData->TPC3RT1,0);
  tpc_rt->AddAt(fData->TPC3RT2,1);
  tpc_lt->AddAt(fData->TPC3LT1,0);
  tpc_lt->AddAt(fData->TPC3LT2,1);

  tpc_dt->AddAt(fData->TPC3DT1,0);
  tpc_dt->AddAt(fData->TPC3DT2,1);
  tpc_dt->AddAt(fData->TPC3DT3,2);
  tpc_dt->AddAt(fData->TPC3DT4,3);

  new ((*fArrayTpc)[fArrayTpc->GetEntriesFast()]) R3BTpcMappedData(2,tpc_ae, tpc_le, tpc_re, tpc_dt, tpc_lt,  tpc_rt);

  //TPC4-S4
  tpc_dt=new TArrayI(); 
  tpc_lt=new TArrayI(); 
  tpc_rt=new TArrayI();
  tpc_dt->Set(4);
  tpc_lt->Set(2);
  tpc_rt->Set(2);

  tpc_rt->AddAt(fData->TPC4RT1,0);
  tpc_rt->AddAt(fData->TPC4RT2,1);
  tpc_lt->AddAt(fData->TPC4LT1,0);
  tpc_lt->AddAt(fData->TPC4LT2,1);

  tpc_dt->AddAt(fData->TPC4DT1,0);
  tpc_dt->AddAt(fData->TPC4DT2,1);
  tpc_dt->AddAt(fData->TPC4DT3,2);
  tpc_dt->AddAt(fData->TPC4DT4,3);

  new ((*fArrayTpc)[fArrayTpc->GetEntriesFast()]) R3BTpcMappedData(3,tpc_ae, tpc_le, tpc_re, tpc_dt, tpc_lt,  tpc_rt);

  //End

    fNEvent++;
    return kTRUE;
}

void R3BFrsReader::Reset() {
    // Reset the output array
    fArray->Clear();
    fArrayMusic->Clear();
    fArrayTpc->Clear();
//	fNEvent = 0;
}

ClassImp(R3BFrsReader)

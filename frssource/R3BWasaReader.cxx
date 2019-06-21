// ----------------------------------------------------------------------
// -----            R3BWasaReader source file                       -----
// -----            Created 23/09/18  by J.L. Rodriguez-Sanchez     -----
// ----------------------------------------------------------------------

#include "FairLogger.h"
#include "R3BWasaReader.h"
  
#include "TClonesArray.h"
#include "FairRootManager.h"
#include "R3BMdcMappedData.h"

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
#include "ext_h101_wasa.h"
}

R3BWasaReader::R3BWasaReader(EXT_STR_h101_WASA* data,
    UInt_t offset)
	: R3BReader("R3BWasaReader"),
  fNEvent(0),
  fData(data),
  fOffset(offset),
  fOnline(kFALSE),
  fLogger(FairLogger::GetLogger()),
  fArrayMdcWasa(new TClonesArray("R3BMdcMappedData")) {

}

R3BWasaReader::~R3BWasaReader() {
  if (fArrayMdcWasa){
		delete fArrayMdcWasa;
	}
}

Bool_t R3BWasaReader::Init(ext_data_struct_info *a_struct_info) {
	int ok;
        LOG(INFO) << "R3BWasaReader::Init" << FairLogger::endl;

	EXT_STR_h101_WASA_ITEMS_INFO(ok, *a_struct_info, fOffset,
	    EXT_STR_h101_WASA, 0);

	if (!ok) {
            LOG(ERROR)<<"R3BWasaReader::Failed to setup structure information."<<FairLogger::endl;
	    return kFALSE;
	}

    // Register output array in tree
  if(!fOnline){
    FairRootManager::Instance()->Register("MdcMappedData", "MDC", fArrayMdcWasa, kTRUE);
  }else{
    FairRootManager::Instance()->Register("MdcMappedData", "MDC", fArrayMdcWasa, kFALSE);
  }  

	return kTRUE;
}

Bool_t R3BWasaReader::Read() {
  EXT_STR_h101_WASA_onion_t *data =
	    (EXT_STR_h101_WASA_onion_t *) fData;

  /* Display data */
  LOG(DEBUG)<<"R3BWasaReader::Read() Event data."<<FairLogger::endl;

  //SELECT THE FOR LOOP BASED ON THE MAPPING...
  for (int wire = 0; wire < fData->WASA_ENE; ++wire) {

    int channelNumber = fData->WASA_ENEI[wire];
    int energy = fData->WASA_ENEv[wire];

    new ((*fArrayMdcWasa)[fArrayMdcWasa->GetEntriesFast()]) R3BMdcMappedData(channelNumber, energy);
	}


    fNEvent++;
    return kTRUE;
}

void R3BWasaReader::Reset() {
    // Reset the output array
    fArrayMdcWasa->Clear();

//	fNEvent = 0;
}

ClassImp(R3BWasaReader)

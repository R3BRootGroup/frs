#include "FrsTpcReader.h"
#include "FairLogger.h"

#include "TMath.h"
#include "TRandom.h"

#include "FairRootManager.h"
#include "R3BTpcMappedData.h"
#include "TClonesArray.h"
#include "TFile.h"

#include "Riostream.h"
#include "TFile.h"
#include "TROOT.h"
#include "TRandom3.h"
#include "TSystem.h"
#include "TVectorD.h"
#include <cstring>
#include <fstream>
#include <iostream>
#include <stdio.h>

extern "C" {
#include "ext_data_client.h"
#include "ext_h101_tpc.h"
}
FrsTpcReader::FrsTpcReader(EXT_STR_h101_TPC* data, UInt_t offset)
    : R3BReader("FrsTpcReader")
    , fNEvent(0)
    , fData(data)
    , fOffset(offset)
    , fOnline(kFALSE)
    , fLogger(FairLogger::GetLogger())
    , fArray(new TClonesArray("R3BTpcMappedData"))
{
}

FrsTpcReader::~FrsTpcReader()
{
    LOG(INFO) << "FrsTpcReader::Delete instance";
    if (fArray)
    {
        delete fArray;
    }
}

Bool_t FrsTpcReader::Init(ext_data_struct_info* a_struct_info)
{
    LOG(INFO) << "FrsTpcReader::Init ";
    Int_t ok;
    EXT_STR_h101_TPC_ITEMS_INFO(ok, *a_struct_info, fOffset, EXT_STR_h101_TPC, 0);

    if (!ok)
    {
        perror("ext_data_struct_info_item");
        LOG(ERROR) << "FrsTpcReader::Failed to setup structure information.";
        return kFALSE;
    }
 
    // Register output array in tree
    if (!fOnline)
    {
 
        FairRootManager::Instance()->Register("TpcMappedData", "FRS TPCs", fArray, kTRUE);
    }
    else
    {
        FairRootManager::Instance()->Register("TpcMappedData", "FRS TPCs", fArray, kFALSE);
    }

    return kTRUE;
}

Bool_t FrsTpcReader::Read()
{
    //
    Reset();
    /* Display data */
    LOG(DEBUG) << "FrsTpcReader::Read() Event data.";
/*
    // Times
    tpc_rt[0] = fData->TPC1RT1;
    tpc_rt[1] = fData->TPC1RT2;
    tpc_lt[0] = fData->TPC1LT1;
    tpc_lt[1] = fData->TPC1LT2;
    tpc_dt[0] = fData->TPC1DT1;
    tpc_dt[1] = fData->TPC1DT2;
    tpc_dt[2] = fData->TPC1DT3;
    tpc_dt[3] = fData->TPC1DT4;

    // Energy
    tpc_re[0] = fData->TPC1AR1;
    tpc_re[1] = fData->TPC1AR2;
    tpc_le[0] = fData->TPC1AL1;
    tpc_le[1] = fData->TPC1AL2;
    tpc_ae[0] = fData->TPC1A1;
    tpc_ae[1] = fData->TPC1A2;
    tpc_ae[2] = fData->TPC1A3;
    tpc_ae[3] = fData->TPC1A4;

    new ((*fArray)[fArray->GetEntriesFast()]) R3BTpcMappedData(0, tpc_ae, tpc_le, tpc_re, tpc_dt, tpc_lt, tpc_rt);

    // Times
    tpc_rt[0] = fData->TPC2RT1;
    tpc_rt[1] = fData->TPC2RT2;
    tpc_lt[0] = fData->TPC2LT1;
    tpc_lt[1] = fData->TPC2LT2;
    tpc_dt[0] = fData->TPC2DT1;
    tpc_dt[1] = fData->TPC2DT2;
    tpc_dt[2] = fData->TPC2DT3;
    tpc_dt[3] = fData->TPC2DT4;

    // Energy
    tpc_re[0] = fData->TPC2AR1;
    tpc_re[1] = fData->TPC2AR2;
    tpc_le[0] = fData->TPC2AL1;
    tpc_le[1] = fData->TPC2AL2;
    tpc_ae[0] = fData->TPC2A1;
    tpc_ae[1] = fData->TPC2A2;
    tpc_ae[2] = fData->TPC2A3;
    tpc_ae[3] = fData->TPC2A4;

    new ((*fArray)[fArray->GetEntriesFast()]) R3BTpcMappedData(1, tpc_ae, tpc_le, tpc_re, tpc_dt, tpc_lt, tpc_rt);
*/
    // Times
    tpc_rt[0] = fData->TPC3RT1;
    tpc_rt[1] = fData->TPC3RT2;
    tpc_lt[0] = fData->TPC3LT1;
    tpc_lt[1] = fData->TPC3LT2;
    tpc_dt[0] = fData->TPC3DT1;
    tpc_dt[1] = fData->TPC3DT2;
    tpc_dt[2] = fData->TPC3DT3;
    tpc_dt[3] = fData->TPC3DT4;

    // Energy
    tpc_re[0] = fData->TPC3AR1;
    tpc_re[1] = fData->TPC3AR2;
    tpc_le[0] = fData->TPC3AL1;
    tpc_le[1] = fData->TPC3AL2;
    tpc_ae[0] = fData->TPC3A1;
    tpc_ae[1] = fData->TPC3A2;
    tpc_ae[2] = fData->TPC3A3;
    tpc_ae[3] = fData->TPC3A4;

    new ((*fArray)[fArray->GetEntriesFast()]) R3BTpcMappedData(0, tpc_ae, tpc_le, tpc_re, tpc_dt, tpc_lt, tpc_rt);

    // Times
    tpc_rt[0] = fData->TPC4RT1;
    tpc_rt[1] = fData->TPC4RT2;
    tpc_lt[0] = fData->TPC4LT1;
    tpc_lt[1] = fData->TPC4LT2;
    tpc_dt[0] = fData->TPC4DT1;
    tpc_dt[1] = fData->TPC4DT2;
    tpc_dt[2] = fData->TPC4DT3;
    tpc_dt[3] = fData->TPC4DT4;

    // Energy
    tpc_re[0] = fData->TPC4AR1;
    tpc_re[1] = fData->TPC4AR2;
    tpc_le[0] = fData->TPC4AL1;
    tpc_le[1] = fData->TPC4AL2;
    tpc_ae[0] = fData->TPC4A1;
    tpc_ae[1] = fData->TPC4A2;
    tpc_ae[2] = fData->TPC4A3;
    tpc_ae[3] = fData->TPC4A4;

    new ((*fArray)[fArray->GetEntriesFast()]) R3BTpcMappedData(1, tpc_ae, tpc_le, tpc_re, tpc_dt, tpc_lt, tpc_rt);

    // Times
    tpc_rt[0] = fData->TPC5RT1;
    tpc_rt[1] = fData->TPC5RT2;
    tpc_lt[0] = fData->TPC5LT1;
    tpc_lt[1] = fData->TPC5LT2;
    tpc_dt[0] = fData->TPC5DT1;
    tpc_dt[1] = fData->TPC5DT2;
    tpc_dt[2] = fData->TPC5DT3;
    tpc_dt[3] = fData->TPC5DT4;

    // Energy
    tpc_re[0] = fData->TPC5AR1;
    tpc_re[1] = fData->TPC5AR2;
    tpc_le[0] = fData->TPC5AL1;
    tpc_le[1] = fData->TPC5AL2;
    tpc_ae[0] = fData->TPC5A1;
    tpc_ae[1] = fData->TPC5A2;
    tpc_ae[2] = fData->TPC5A3;
    tpc_ae[3] = fData->TPC5A4;

    new ((*fArray)[fArray->GetEntriesFast()]) R3BTpcMappedData(2, tpc_ae, tpc_le, tpc_re, tpc_dt, tpc_lt, tpc_rt);


    // Times
    tpc_rt[0] = fData->TPC6RT1;
    tpc_rt[1] = fData->TPC6RT2;
    tpc_lt[0] = fData->TPC6LT1;
    tpc_lt[1] = fData->TPC6LT2;
    tpc_dt[0] = fData->TPC6DT1;
    tpc_dt[1] = fData->TPC6DT2;
    tpc_dt[2] = fData->TPC6DT3;
    tpc_dt[3] = fData->TPC6DT4;

    // Energy
    tpc_re[0] = fData->TPC6AR1;
    tpc_re[1] = fData->TPC6AR2;
    tpc_le[0] = fData->TPC6AL1;
    tpc_le[1] = fData->TPC6AL2;
    tpc_ae[0] = fData->TPC6A1;
    tpc_ae[1] = fData->TPC6A2;
    tpc_ae[2] = fData->TPC6A3;
    tpc_ae[3] = fData->TPC6A4;

    new ((*fArray)[fArray->GetEntriesFast()]) R3BTpcMappedData(3, tpc_ae, tpc_le, tpc_re, tpc_dt, tpc_lt, tpc_rt);

    fNEvent++;
    return kTRUE;
}

void FrsTpcReader::Reset()
{
    // Reset the output array
    fArray->Clear();
    //	fNEvent = 0;
}

ClassImp(FrsTpcReader)

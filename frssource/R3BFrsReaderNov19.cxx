#include "R3BFrsReaderNov19.h"
#include "FairLogger.h"

#include "TMath.h"
#include "TRandom.h"

#include "FairRootManager.h"
#include "R3BEventHeader.h"
#include "R3BFrsMappedData.h"
#include "FrsSpillMappedData.h"
#include "FRSMusicMappedData.h"
#include "R3BMwMappedData.h"
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
#include "ext_h101_frs.h"
}
R3BFrsReaderNov19::R3BFrsReaderNov19(EXT_STR_h101_FRS* data, UInt_t offset)
    : R3BReader("R3BFrsReaderNov19")
    , fNEvent(0)
    , fData(data)
    , fOffset(offset)
    , fOnline(kFALSE)
    , fLogger(FairLogger::GetLogger())
    , fArray(new TClonesArray("R3BFrsMappedData"))
    , fArraySpill(new TClonesArray("FrsSpillMappedData"))
    //, fArrayMusic(new TClonesArray("FRSMusicMappedData"))
    //, fArrayTpc(new TClonesArray("R3BTpcMappedData"))
    , fArrayMW11(new TClonesArray("R3BMwMappedData"))
    , fArrayMW21(new TClonesArray("R3BMwMappedData"))
    , fArrayMW22(new TClonesArray("R3BMwMappedData"))
    , fArrayMW31(new TClonesArray("R3BMwMappedData"))
    , fArrayMW51(new TClonesArray("R3BMwMappedData"))
    , fArrayMW71(new TClonesArray("R3BMwMappedData"))
    , fArrayMW81(new TClonesArray("R3BMwMappedData"))
    , fArrayMW82(new TClonesArray("R3BMwMappedData"))
    , fEventHeader(nullptr)
{
}

R3BFrsReaderNov19::~R3BFrsReaderNov19()
{
    LOG(INFO) << "R3BFrsReaderNov19::Delete instance";
    if (fArray)
    {
        delete fArray;
    }
    if (fArraySpill)
    {
        delete fArraySpill;
    }
    //if (fArrayMusic)
    //{
     //   delete fArrayMusic;
   // }
/*
    if (fArrayTpc)
    {
        delete fArrayTpc;
    }*/
    if (fArrayMW11)
    {
        delete fArrayMW11;
    }
    if (fArrayMW21)
    {
        delete fArrayMW21;
    }
    if (fArrayMW22)
    {
        delete fArrayMW22;
    }
    if (fArrayMW31)
    {
        delete fArrayMW31;
    }
    if (fArrayMW51)
    {
        delete fArrayMW51;
    }
    if (fArrayMW71)
    {
        delete fArrayMW71;
    }
    if (fArrayMW81)
    {
        delete fArrayMW81;
    }
    if (fArrayMW82)
    {
        delete fArrayMW82;
    }
}

Bool_t R3BFrsReaderNov19::Init(ext_data_struct_info* a_struct_info)
{
    LOG(INFO) << "R3BFrsReaderNov19::Init ";
    Int_t ok;
    EXT_STR_h101_FRS_ITEMS_INFO(ok, *a_struct_info, fOffset, EXT_STR_h101_FRS, 0);

    if (!ok)
    {
        perror("ext_data_struct_info_item");
        LOG(ERROR) << "R3BFrsReaderNov19::Failed to setup structure information.";
        return kFALSE;
    }

    FairRootManager* mgr = FairRootManager::Instance();
    fEventHeader = (R3BEventHeader*)mgr->GetObject("R3BEventHeader");

    // Register output array in tree
    if (!fOnline)
    {
        FairRootManager::Instance()->Register("FrsMappedData", "FRS", fArray, kTRUE);
        FairRootManager::Instance()->Register("FrsSpillMappedData", "FRS Spill", fArraySpill, kTRUE);
        //FairRootManager::Instance()->Register("FRSMusicMappedData", "FRS Musics", fArrayMusic, kTRUE);
      //  FairRootManager::Instance()->Register("TpcMappedData", "FRS TPCs", fArrayTpc, kTRUE);
        FairRootManager::Instance()->Register("MW11MappedData", "FRS MW11", fArrayMW11, kTRUE);
        FairRootManager::Instance()->Register("MW21MappedData", "FRS MW21", fArrayMW21, kTRUE);
        FairRootManager::Instance()->Register("MW22MappedData", "FRS MW22", fArrayMW22, kTRUE);
        FairRootManager::Instance()->Register("MW31MappedData", "FRS MW31", fArrayMW31, kTRUE);
        FairRootManager::Instance()->Register("MW51MappedData", "FRS MW51", fArrayMW51, kTRUE);
        FairRootManager::Instance()->Register("MW71MappedData", "FRS MW71", fArrayMW71, kTRUE);
        FairRootManager::Instance()->Register("MW81MappedData", "FRS MW81", fArrayMW81, kTRUE);
        FairRootManager::Instance()->Register("MW82MappedData", "FRS MW82", fArrayMW82, kTRUE);
    }
    else
    {
        FairRootManager::Instance()->Register("FrsMappedData", "FRS", fArray, kFALSE);
        FairRootManager::Instance()->Register("FrsSpillMappedData", "FRS Spill", fArraySpill, kFALSE);
        //FairRootManager::Instance()->Register("FRSMusicMappedData", "FRS Musics", fArrayMusic, kFALSE);
       // FairRootManager::Instance()->Register("TpcMappedData", "FRS TPCs", fArrayTpc, kFALSE);
        FairRootManager::Instance()->Register("MW11MappedData", "FRS MW11", fArrayMW11, kFALSE);
        FairRootManager::Instance()->Register("MW21MappedData", "FRS MW21", fArrayMW21, kFALSE);
        FairRootManager::Instance()->Register("MW22MappedData", "FRS MW22", fArrayMW22, kFALSE);
        FairRootManager::Instance()->Register("MW31MappedData", "FRS MW31", fArrayMW31, kFALSE);
        FairRootManager::Instance()->Register("MW51MappedData", "FRS MW51", fArrayMW51, kFALSE);
        FairRootManager::Instance()->Register("MW71MappedData", "FRS MW71", fArrayMW71, kFALSE);
        FairRootManager::Instance()->Register("MW81MappedData", "FRS MW81", fArrayMW81, kFALSE);
        FairRootManager::Instance()->Register("MW82MappedData", "FRS MW82", fArrayMW82, kFALSE);
    }

    return kTRUE;
}

Bool_t R3BFrsReaderNov19::Read()
{
    //
    Reset();
    /* Display data */
    LOG(DEBUG) << "R3BFrsReaderNov19::Read() Event data.";
/*
    new ((*fArray)[fArray->GetEntriesFast()]) R3BFrsMappedData(fData->AccTrig,
                                                               fData->ClockhundredkHz,
                                                               fData->ClockoneHz,
                                                               fData->ClocktenHz,
                                                               fEventHeader->GetTrigger(),
                                                               fData->FreeTrig,
                                                               fData->Spill,
                                                               fData->Seenew,
                                                               fData->Seeold,
                                                               fData->ICNewCurrent,
                                                               fData->SCI1L, // sci21
                                                               fData->SCIN2, // sci01
                                                               fData->SCI2L, // sci41
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
                                                               fData->SC5Rt);


    new ((*fArraySpill)[fArraySpill->GetEntriesFast()]) FrsSpillMappedData(
                                                               fData->ClockhundredkHz,
                                                               fData->ClocktenHz,
                                                               fData->ClockoneHz,
                                                               fData->StartExt,
                                                               fData->StopExt,
                                                               fData->AccTrig,
                                                               fData->FreeTrig,
                                                               fData->Seenew,
                                                               fData->Seeold,
                                                               fData->ICNewCurrent,
                                                               0, 
                                                               0, 
                                                               0,0,0,0,0,0,0,0,0,0,0,0 
                                                               );

    new ((*fArrayMusic)[fArrayMusic->GetEntriesFast()]) FRSMusicMappedData(0, 0, fData->MUS1A1);
    new ((*fArrayMusic)[fArrayMusic->GetEntriesFast()]) FRSMusicMappedData(0, 1, fData->MUS1A2);
    new ((*fArrayMusic)[fArrayMusic->GetEntriesFast()]) FRSMusicMappedData(0, 2, fData->MUS1A3);
    new ((*fArrayMusic)[fArrayMusic->GetEntriesFast()]) FRSMusicMappedData(0, 3, fData->MUS1A4);
    new ((*fArrayMusic)[fArrayMusic->GetEntriesFast()]) FRSMusicMappedData(0, 4, fData->MUS1A5);
    new ((*fArrayMusic)[fArrayMusic->GetEntriesFast()]) FRSMusicMappedData(0, 5, fData->MUS1A6);
    new ((*fArrayMusic)[fArrayMusic->GetEntriesFast()]) FRSMusicMappedData(0, 6, fData->MUS1A7);
    new ((*fArrayMusic)[fArrayMusic->GetEntriesFast()]) FRSMusicMappedData(0, 7, fData->MUS1A8);

    new ((*fArrayMusic)[fArrayMusic->GetEntriesFast()]) FRSMusicMappedData(1, 0, fData->MUS2A1);
    new ((*fArrayMusic)[fArrayMusic->GetEntriesFast()]) FRSMusicMappedData(1, 1, fData->MUS2A2);
    new ((*fArrayMusic)[fArrayMusic->GetEntriesFast()]) FRSMusicMappedData(1, 2, fData->MUS2A3);
    new ((*fArrayMusic)[fArrayMusic->GetEntriesFast()]) FRSMusicMappedData(1, 3, fData->MUS2A4);
    new ((*fArrayMusic)[fArrayMusic->GetEntriesFast()]) FRSMusicMappedData(1, 4, fData->MUS2A5);
    new ((*fArrayMusic)[fArrayMusic->GetEntriesFast()]) FRSMusicMappedData(1, 5, fData->MUS2A6);
    new ((*fArrayMusic)[fArrayMusic->GetEntriesFast()]) FRSMusicMappedData(1, 6, fData->MUS2A7);
    new ((*fArrayMusic)[fArrayMusic->GetEntriesFast()]) FRSMusicMappedData(1, 7, fData->MUS2A8);

    new ((*fArrayMusic)[fArrayMusic->GetEntriesFast()]) FRSMusicMappedData(1, 0, fData->MUS3A1);
    new ((*fArrayMusic)[fArrayMusic->GetEntriesFast()]) FRSMusicMappedData(1, 1, fData->MUS3A2);
    new ((*fArrayMusic)[fArrayMusic->GetEntriesFast()]) FRSMusicMappedData(1, 2, fData->MUS3A3);
    new ((*fArrayMusic)[fArrayMusic->GetEntriesFast()]) FRSMusicMappedData(1, 3, fData->MUS3A4);
    new ((*fArrayMusic)[fArrayMusic->GetEntriesFast()]) FRSMusicMappedData(1, 4, fData->MUS3A5);
    new ((*fArrayMusic)[fArrayMusic->GetEntriesFast()]) FRSMusicMappedData(1, 5, fData->MUS3A6);
    new ((*fArrayMusic)[fArrayMusic->GetEntriesFast()]) FRSMusicMappedData(1, 6, fData->MUS3A7);
    new ((*fArrayMusic)[fArrayMusic->GetEntriesFast()]) FRSMusicMappedData(1, 7, fData->MUS3A8);

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

    new ((*fArrayTpc)[fArrayTpc->GetEntriesFast()]) R3BTpcMappedData(0, tpc_ae, tpc_le, tpc_re, tpc_dt, tpc_lt, tpc_rt);

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

    new ((*fArrayTpc)[fArrayTpc->GetEntriesFast()]) R3BTpcMappedData(1, tpc_ae, tpc_le, tpc_re, tpc_dt, tpc_lt, tpc_rt);
*/

/*
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

    new ((*fArrayTpc)[fArrayTpc->GetEntriesFast()]) R3BTpcMappedData(0, tpc_ae, tpc_le, tpc_re, tpc_dt, tpc_lt, tpc_rt);

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

    new ((*fArrayTpc)[fArrayTpc->GetEntriesFast()]) R3BTpcMappedData(1, tpc_ae, tpc_le, tpc_re, tpc_dt, tpc_lt, tpc_rt);

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

    new ((*fArrayTpc)[fArrayTpc->GetEntriesFast()]) R3BTpcMappedData(2, tpc_ae, tpc_le, tpc_re, tpc_dt, tpc_lt, tpc_rt);


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

    new ((*fArrayTpc)[fArrayTpc->GetEntriesFast()]) R3BTpcMappedData(3, tpc_ae, tpc_le, tpc_re, tpc_dt, tpc_lt, tpc_rt);

*/



//---------------------------------------------------------------------------------------------------------
// Dynamical online starts here. 16/11/2019. At the moment only MWs!
//
//

    if (fData->MWAN1 > 0)//MW11
    {
        new ((*fArrayMW11)[fArrayMW11->GetEntriesFast()])
            R3BMwMappedData(0, fData->MWAN1, fData->MW1XR, fData->MW1XL, fData->MW1YU, fData->MW1YD);
    }
    if (fData->MWAN2 > 0)//MW21
    {
        new ((*fArrayMW21)[fArrayMW21->GetEntriesFast()])
            R3BMwMappedData(1, fData->MWAN2, fData->MW2XR, fData->MW2XL, fData->MW2YU, fData->MW2YD);
    }
    if (fData->MWAN3 > 0)//MW22
    {
        new ((*fArrayMW22)[fArrayMW22->GetEntriesFast()])
            R3BMwMappedData(2, fData->MWAN3, fData->MW3XR, fData->MW3XL, fData->MW3YU, fData->MW3YD);
    }
    if (fData->MWAN4 > 0)//MW31
    {
        new ((*fArrayMW31)[fArrayMW31->GetEntriesFast()])
            R3BMwMappedData(3, fData->MWAN4, fData->MW4XR, fData->MW4XL, fData->MW4YU, fData->MW4YD);
    }
    if (fData->MWAN5 > 0)//MW51
    {
        new ((*fArrayMW51)[fArrayMW51->GetEntriesFast()])
            R3BMwMappedData(6, fData->MWAN5, fData->MW5XR, fData->MW5XL, fData->MW5YU, fData->MW5YD);
    }
    if (fData->MWAN6 > 0)//MW71
    {
        new ((*fArrayMW71)[fArrayMW71->GetEntriesFast()])
            R3BMwMappedData(8, fData->MWAN6, fData->MW6XR, fData->MW6XL, fData->MW6YU, fData->MW6YD);
    }
    if (fData->MWAN7 > 0)//MW81
    {
        new ((*fArrayMW81)[fArrayMW81->GetEntriesFast()])
            R3BMwMappedData(9, fData->MWAN7, fData->MW7XR, fData->MW7XL, fData->MW7YU, fData->MW7YD);
    }
    if (fData->MWAN8 > 0)//MW82
    {
        new ((*fArrayMW82)[fArrayMW82->GetEntriesFast()])
            R3BMwMappedData(10, fData->MWAN8, fData->MW8XR, fData->MW8XL, fData->MW8YU, fData->MW8YD);
    }

    fNEvent++;
    return kTRUE;
}

void R3BFrsReaderNov19::Reset()
{
    // Reset the output array
    fArray->Clear();
    fArraySpill->Clear();
    //fArrayMusic->Clear();
    //fArrayTpc->Clear();
    fArrayMW11->Clear();
    fArrayMW21->Clear();
    fArrayMW22->Clear();
    fArrayMW31->Clear();
    fArrayMW51->Clear();
    fArrayMW71->Clear();
    fArrayMW81->Clear();
    fArrayMW82->Clear();
    //	fNEvent = 0;
}

ClassImp(R3BFrsReaderNov19)

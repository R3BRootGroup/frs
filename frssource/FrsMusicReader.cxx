
#include "FrsMusicReader.h"
#include "FairLogger.h"
#include "FairRootManager.h"

#include "TClonesArray.h"
#include "TMath.h"
#include "TRandom.h"

#include "FRSMusicMappedData.h"

extern "C"
{
#include "ext_data_client.h"
#include "ext_h101_frsmusic.h"
}
FrsMusicReader::FrsMusicReader(EXT_STR_h101_FRSMUSIC* data, UInt_t offset)
    : R3BReader("FrsMusicReader")
    , fNEvent(0)
    , fNbDet(2)
    , fData(data)
    , fOffset(offset)
    , fOnline(kFALSE)
    , fLogger(FairLogger::GetLogger())
    , fArray(new TClonesArray("FRSMusicMappedData"))
{
}

FrsMusicReader::~FrsMusicReader()
{
    LOG(INFO) << "FrsMusicReader::Delete instance";
    if (fArray)
    {
        delete fArray;
    }
}

Bool_t FrsMusicReader::Init(ext_data_struct_info* a_struct_info)
{
    Int_t ok;
    EXT_STR_h101_FRSMUSIC_ITEMS_INFO(ok, *a_struct_info, fOffset, EXT_STR_h101_FRSMUSIC, 0);
    if (!ok)
    {
        perror("ext_data_struct_info_item");
        LOG(ERROR) << "FrsMusicReader::Failed to setup structure information.";
        return kFALSE;
    }

    FairRootManager* mgr = FairRootManager::Instance();
    // Register output array in tree
    if (!fOnline)
        FairRootManager::Instance()->Register("FRSMusicMappedData", "FRS Musics", fArray, kTRUE);
    else
        FairRootManager::Instance()->Register("FRSMusicMappedData", "FRS Musics", fArray, kFALSE);

    return kTRUE;
}

Bool_t FrsMusicReader::Read()
{
    Reset();
    /* Display data */
    LOG(DEBUG) << "FrsMusicReader::Read() Event data.";

    EXT_STR_h101_FRSMUSIC_onion* data = (EXT_STR_h101_FRSMUSIC_onion*)fData;

    for (Int_t d = 0; d < fNbDet; d++)
    {
        UShort_t nAnodes = data->MUS[d].A;

        for (UShort_t a = 0; a < nAnodes; a++)
        {
            UShort_t idAnode = data->MUS[d].AI[a];
            Int_t Anode_E = data->MUS[d].Av[a];
            new ((*fArray)[fArray->GetEntriesFast()]) FRSMusicMappedData(d, idAnode - 1, Anode_E);
        }
    }

    fNEvent++;
    return kTRUE;
}

void FrsMusicReader::Reset()
{
    // Reset the output array
    fArray->Clear();
}

ClassImp(FrsMusicReader)

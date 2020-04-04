#include "FairLogger.h"

#include "FairRootManager.h"
#include "VftxSciMappedData.h"
#include "VftxSciReader.h"

extern "C"
{
#include "ext_data_client.h"
#include "ext_h101_frssci.h"
}

#define NUM_SCI_DETECTORS 2 // for s474

#include <iostream>

using namespace std;

VftxSciReader::VftxSciReader(EXT_STR_h101_frssci* data, UInt_t offset)
    : R3BReader("VftxSciReader")
    , fData(data)
    , fOffset(offset)
    , fOnline(kFALSE)
    , fArray(new TClonesArray("VftxSciMappedData")) // class name
    , fNumEntries(0)
{
}

VftxSciReader::~VftxSciReader()
{
    LOG(INFO) << "VftxSciReader: Delete instance";
    if (fArray)
    {
        delete fArray;
    }
}

Bool_t VftxSciReader::Init(ext_data_struct_info* a_struct_info)
{
    Int_t ok;
    LOG(INFO) << "VftxSciReader::Init";
    EXT_STR_h101_frssci_ITEMS_INFO(ok, *a_struct_info, fOffset, EXT_STR_h101_frssci, 0);
    if (!ok)
    {
        perror("ext_data_struct_info_item");
        LOG(ERROR) << "VftxSciReader::Failed to setup structure information.";
        return kFALSE;
    }

    // Register output array in tree
    if (!fOnline)
    {
        FairRootManager::Instance()->Register("VftxSciMappedData", "VftxSci", fArray, kTRUE);
    }
    else
    {
        FairRootManager::Instance()->Register("VftxSciMappedData", "VftxSci", fArray, kFALSE);
    }
    fArray->Clear();

    // clear struct_writer's output struct. Seems ucesb doesn't do that
    // for channels that are unknown to the current ucesb config.
    EXT_STR_h101_frssci_onion* data = (EXT_STR_h101_frssci_onion*)fData;
    for (int d = 0; d < NUM_SCI_DETECTORS; d++)
        data->FRSSCI[d].TFM = 0;

    return kTRUE;
}

Bool_t VftxSciReader::Read()
{
    // Convert plain raw data to multi-dimensional array
    EXT_STR_h101_frssci_onion* data = (EXT_STR_h101_frssci_onion*)fData;


    // loop over all detectors
    for (int d = 0; d < NUM_SCI_DETECTORS; d++)
    {
        uint32_t numberOfPMTsWithHits_TF = data->FRSSCI[d].TFM;
        uint32_t numberOfPMTsWithHits_TC = data->FRSSCI[d].TCM;
        if (numberOfPMTsWithHits_TF != numberOfPMTsWithHits_TC)
        {
            LOG(ERROR) << "VftxSciReader::Read() Error in unpacking, unconsistency between TF and TC for VftxSci !";
        }
        else
        {
            // loop over channels with hits
            uint32_t curChannelStart = 0;
            for (Int_t pmmult = 0; pmmult < numberOfPMTsWithHits_TF; pmmult++)
            {
                uint32_t pmtid_TF = data->FRSSCI[d].TFMI[pmmult];
                uint32_t pmtid_TC = data->FRSSCI[d].TCMI[pmmult];
                if (pmtid_TF != pmtid_TC)
                {
                    LOG(ERROR) << "VftxSciReader::Read() Error in unpacking, unconsistency between the PMT id for TF "
                                  "and TC for VftxSci !";
                }
                uint32_t nextChannelStart = data->FRSSCI[d].TFME[pmmult];
                // put the mapped items {det,pmt,finetime, coarsetime} one after the other in the fArray
                for (Int_t hit = curChannelStart; hit < nextChannelStart; hit++)
                {
                    auto item = new ((*fArray)[fNumEntries++])
		      VftxSciMappedData(d+1, // from 1 to 4
					    pmtid_TF, // from 1 to 2
					    data->FRSSCI[d].TCv[hit], 
					    data->FRSSCI[d].TFv[hit]);
                }
                curChannelStart = nextChannelStart;
            }
        }
    } // end of for(d)
    return kTRUE;
}

void VftxSciReader::Reset()
{
    // Reset the output array
    fArray->Clear();
    fNumEntries = 0;
}

ClassImp(VftxSciReader)

// ------------------------------------------------------------
// -----                  R3BWasaOnlineSpectra            -----
// -----    Created 23/09/18  by J.L. Rodriguez-Sanchez   -----
// -----           Fill WASA online histograms            -----
// ------------------------------------------------------------

/*
 * This task should fill histograms with WASA online data  
 */

#include "R3BWasaOnlineSpectra.h"
#include "R3BMdcMappedData.h"
#include "R3BEventHeader.h"
#include "THttpServer.h"

#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"
#include "FairRootManager.h"
#include "FairLogger.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TCanvas.h"
#include "TFolder.h"

#include "TClonesArray.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <fstream>
#include <ctime>
#include <array>
#include "TMath.h"

using namespace std;

R3BWasaOnlineSpectra::R3BWasaOnlineSpectra()
  : FairTask("WasaOnlineSpectra", 1)
  , fMappedItemsMdc(NULL)
  , fTrigger(-1)
  , fNEvents(0) 
{
}

R3BWasaOnlineSpectra::R3BWasaOnlineSpectra(const char* name, Int_t iVerbose)
  : FairTask(name, iVerbose)
  , fMappedItemsMdc(NULL)
  , fTrigger(-1)
  , fNEvents(0)
{
}

R3BWasaOnlineSpectra::~R3BWasaOnlineSpectra() {
}

InitStatus R3BWasaOnlineSpectra::Init() {
  
  LOG(INFO) << "R3BWasaOnlineSpectra::Init ";
  
  // try to get a handle on the EventHeader. EventHeader may not be 
  // present though and hence may be null. Take care when using.
  
  FairRootManager* mgr = FairRootManager::Instance();
  if (NULL == mgr)
  LOG(fatal)<<"R3BWasaOnlineSpectra::Init FairRootManager not found";
  header = (R3BEventHeader*)mgr->GetObject("R3BEventHeader");

  FairRunOnline *run = FairRunOnline::Instance();
  run->GetHttpServer()->Register("",this);

  //get access to Mapped data
  fMappedItemsMdc = (TClonesArray*)mgr->GetObject("MdcMappedData");
  if (!fMappedItemsMdc)
  LOG(fatal)<<"R3BWasaOnlineSpectra::Init MdcMappedData not found";

  //create histograms of all detectors 

    char Name1[255];
    char Name2[255];

    //  CANVAS 1  -------------------------------     
    for(Int_t i=0;i<12*2;i++){// 192/16=12
     sprintf(Name1, "Canvas_MDC_%d", i+1);
     cMdcWasa[i]=new TCanvas(Name1, "info for Mdc", 10, 10, 800, 700);
     cMdcWasa[i]->Divide(4,4);
    }
    
    //MDC HISTO
    for(Int_t i=0;i<12*2;i++){//number of canvas
     for(Int_t j=0;j<16;j++){//16 histo per canvas
      sprintf(Name2, "fh_mdc_%d", i*16+j);
      fh_mdc[i*16+j] = new TH1F(Name2, Name2, 500, 0, 4092);
      fh_mdc[i*16+j]->GetXaxis()->SetTitle("Channels");
      fh_mdc[i*16+j]->GetYaxis()->SetTitle("Counts");
      fh_mdc[i*16+j]->GetXaxis()->CenterTitle(true);
      fh_mdc[i*16+j]->GetYaxis()->CenterTitle(true);
      cMdcWasa[i]->cd(j+1);
      fh_mdc[i*16+j]->SetFillColor(kGreen-3);
      fh_mdc[i*16+j]->SetLineColor(1);
      fh_mdc[i*16+j]->Draw("");
     }
    }


    //MAIN FOLDER-WASA
    TFolder* mainfolWasa = new TFolder("WASA","WASA info");
    for(Int_t i=0;i<12*2;i++)mainfolWasa->Add(cMdcWasa[i]);

    run->AddObject(mainfolWasa);

    //Register command to reset histograms
    run->GetHttpServer()->RegisterCommand("Reset_MDC", Form("/Objects/%s/->Reset_MDC_Histo()", GetName()));

  return kSUCCESS;
}

void R3BWasaOnlineSpectra::Reset_MDC_Histo()
{
    LOG(INFO) << "R3BWasaOnlineSpectra::Reset_MDC_Histo";

    for(Int_t i=0;i<192*2;i++)fh_mdc[i]->Reset();

}

void R3BWasaOnlineSpectra::Exec(Option_t* option) {
  
  FairRootManager* mgr = FairRootManager::Instance();
  if (NULL == mgr)
    LOG(fatal)<<"R3BWasaOnlineSpectra::Exec FairRootManager not found";

  //Fill mapped data
  if(fMappedItemsMdc && fMappedItemsMdc->GetEntriesFast()){
    Int_t nHits = fMappedItemsMdc->GetEntriesFast();
    for (Int_t ihit = 0; ihit < nHits; ihit++){
      R3BMdcMappedData* hit = 
	(R3BMdcMappedData*)fMappedItemsMdc->At(ihit);
      if (!hit) continue;
      fh_mdc[hit->GetAnodeId()]->Fill(hit->GetEnergy());
     // std::cout << hit->GetAnodeId() << std::endl;
    }
  }


  fNEvents += 1;
}


void R3BWasaOnlineSpectra::FinishEvent() {

    if (fMappedItemsMdc)
    {
        fMappedItemsMdc->Clear();
    }

}


void R3BWasaOnlineSpectra::FinishTask() {

    if (fMappedItemsMdc){
	 for(Int_t i=0;i<12*2;i++)cMdcWasa[i]->Write();
    }

}

ClassImp(R3BWasaOnlineSpectra)

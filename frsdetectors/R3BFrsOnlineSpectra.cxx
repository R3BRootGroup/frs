// ------------------------------------------------------------
// -----                  R3BFrsOnlineSpectra             -----
// -----    Created 29/07/18  by J.L. Rodriguez-Sanchez   -----
// -----           Fill FRS online histograms             -----
// ------------------------------------------------------------

/*
 * This task should fill histograms with FRS online data  
 */

#include "R3BFrsOnlineSpectra.h"
#include "R3BFrsMappedData.h"
#include "R3BMusicCalData.h"
#include "R3BMusicHitData.h"
#include "R3BTpcCalData.h"
#include "R3BTpcHitData.h"
#include "R3BFrsData.h"
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

R3BFrsOnlineSpectra::R3BFrsOnlineSpectra()
  : FairTask("FrsOnlineSpectra", 1)
  , fMappedItemsFrs(NULL)
  , fCalItemsMusic(NULL)
  , fHitItemsMusic(NULL)
  , fHitItemsTpc(NULL)
  , fCalItemsTpc(NULL)
  , fAnaItemsFrs(NULL)
  , fTrigger(-1)
  , fNEvents(0) 
{
}

R3BFrsOnlineSpectra::R3BFrsOnlineSpectra(const char* name, Int_t iVerbose)
  : FairTask(name, iVerbose)
  , fMappedItemsFrs(NULL)
  , fCalItemsMusic(NULL)
  , fHitItemsMusic(NULL)
  , fHitItemsTpc(NULL)
  , fCalItemsTpc(NULL)
  , fAnaItemsFrs(NULL)
  , fTrigger(-1)
  , fNEvents(0)
{
}

R3BFrsOnlineSpectra::~R3BFrsOnlineSpectra() {
}

InitStatus R3BFrsOnlineSpectra::Init() {
  
  LOG(INFO) << "R3BFrsOnlineSpectra::Init " << FairLogger::endl;
  
  // try to get a handle on the EventHeader. EventHeader may not be 
  // present though and hence may be null. Take care when using.
  
  FairRootManager* mgr = FairRootManager::Instance();
  if (NULL == mgr)
  FairLogger::GetLogger()->Fatal(MESSAGE_ORIGIN,"R3BFrsOnlineSpectra::Init FairRootManager not found");
  header = (R3BEventHeader*)mgr->GetObject("R3BEventHeader");

  FairRunOnline *run = FairRunOnline::Instance();
  run->GetHttpServer()->Register("",this);

  //get access to Mapped data
  fMappedItemsFrs = (TClonesArray*)mgr->GetObject("FrsMappedData");
  if (!fMappedItemsFrs) { return kFATAL;}

  //get access to Cal Music data
  fCalItemsMusic = (TClonesArray*)mgr->GetObject("MusicCalData");  

  //get access to Hit Music data
  fHitItemsMusic = (TClonesArray*)mgr->GetObject("MusicHitData");

  //get access to Cal Tpc data
  fCalItemsTpc = (TClonesArray*)mgr->GetObject("TpcCalData");

  //get access to Hit Tpc data
  fHitItemsTpc = (TClonesArray*)mgr->GetObject("TpcHitData");

  //get access to Analysis Frs data
  fAnaItemsFrs = (TClonesArray*)mgr->GetObject("FrsData");

  //create histograms of all detectors  

/*  
    //Energy range for strips
    Double_t bins=200;
    Double_t maxE=3500;
    Double_t minE=0;
    



    char Name1[255]; 
    char Name2[255];

    //Mapped data
    for(Int_t i=0;i<4;i++){//one histo per detector
     sprintf(Name1, "fh_Ams_energy_allStrips_%d", i+1);	  
     sprintf(Name2, "Energy vs strip number for AMS Det: %d", i+1);
     fh_Ams_energy_allStrips[i] = new TH2F(Name1, Name2, 1024, 0, 1024, bins, minE, maxE);    
     fh_Ams_energy_allStrips[i]->GetXaxis()->SetTitle("Strip number");
     fh_Ams_energy_allStrips[i]->GetYaxis()->SetTitle("Energy [channels]");
     fh_Ams_energy_allStrips[i]->GetYaxis()->SetTitleOffset(1.4);
     fh_Ams_energy_allStrips[i]->GetXaxis()->CenterTitle(true);
     fh_Ams_energy_allStrips[i]->GetYaxis()->CenterTitle(true);
     cMap->cd(i+1);
     fh_Ams_energy_allStrips[i]->Draw("col"); 
    }

    //Cal data
    for(Int_t i=0;i<4;i++){//two histo per detector
     for(Int_t j=0;j<2;j++){
      sprintf(Name1, "fh_Ams_energy_allCalStrips_%d", i*2+j);	  
      sprintf(Name2, "Cal_Energy vs strip number for AMS Det: %d and Side: %d", i+1, j);
      if(j==0)
      fh_Ams_energy_allCalStrips[i*2+j] = new TH2F(Name1, Name2, 640, 0, 640, bins, minE, maxE);
      else
      fh_Ams_energy_allCalStrips[i*2+j] = new TH2F(Name1, Name2, 384, 0, 384, bins, minE, maxE);
      fh_Ams_energy_allCalStrips[i*2+j]->GetXaxis()->SetTitle("Strip number");
      fh_Ams_energy_allCalStrips[i*2+j]->GetYaxis()->SetTitle("Energy [channels]");
      fh_Ams_energy_allCalStrips[i*2+j]->GetYaxis()->SetTitleOffset(1.4);
      fh_Ams_energy_allCalStrips[i*2+j]->GetXaxis()->CenterTitle(true);
      fh_Ams_energy_allCalStrips[i*2+j]->GetYaxis()->CenterTitle(true);
      cCal->cd(i*2+1+j);
      fh_Ams_energy_allCalStrips[i*2+j]->Draw("col");
     }
    }

    //Hit data
    for(Int_t i=0;i<4;i++){//one histo per detector
     sprintf(Name1, "fh_Ams_hit_%d", i+1);	  
     sprintf(Name2, "Y vs X for AMS Det: %d", i+1);
     fh_Ams_hit[i] = new TH2F(Name1, Name2, 350, 0, 70., 200, 0, 40.);    
     fh_Ams_hit[i]->GetXaxis()->SetTitle("X [mm]");
     fh_Ams_hit[i]->GetYaxis()->SetTitle("Y [mm]");
     fh_Ams_hit[i]->GetXaxis()->CenterTitle(true);
     fh_Ams_hit[i]->GetYaxis()->CenterTitle(true);
     fh_Ams_hit[i]->GetYaxis()->SetTitleOffset(1.1);
     fh_Ams_hit[i]->GetXaxis()->SetTitleOffset(1.1);
     cHit->cd(i+1);
     fh_Ams_hit[i]->Draw("col"); 
    }
*/


    char Name1[255];
    char Name2[255];

    //  CANVAS 1  -------------------------------     
    cMus1 = new TCanvas("Music41_E", "Music41 info", 10, 10, 800, 700);
    cMus1->Divide(4,2);
    cMus2 = new TCanvas("Music42_E", "Music42 info", 10, 10, 800, 700);
    cMus2->Divide(4,2);

    //Music: Cal data
    for(Int_t i=0;i<2;i++){//number of Musics
     for(Int_t j=0;j<8;j++){//8 histo per detector
      sprintf(Name1, "fh_music_energy_%d", i*8+j);
      if(i==0)sprintf(Name2, "Music41 anode %d", j+1);
      else sprintf(Name2, "Music42 anode %d", j+1);
      fh_music_energy_per_anode[i*8+j] = new TH1F(Name1, Name2, 500, 0, 4092);
      fh_music_energy_per_anode[i*8+j]->GetXaxis()->SetTitle("Channels");
      fh_music_energy_per_anode[i*8+j]->GetYaxis()->SetTitle("Counts");
      fh_music_energy_per_anode[i*8+j]->GetYaxis()->SetTitleOffset(1.2);
      fh_music_energy_per_anode[i*8+j]->GetXaxis()->CenterTitle(true);
      fh_music_energy_per_anode[i*8+j]->GetYaxis()->CenterTitle(true);
      fh_music_energy_per_anode[i*8+j]->GetXaxis()->SetLabelSize(0.045);
      fh_music_energy_per_anode[i*8+j]->GetXaxis()->SetTitleSize(0.045);
      if(i==0)cMus1->cd(j+1);
      else cMus2->cd(j+1);
      fh_music_energy_per_anode[i*8+j]->SetFillColor(3);
      fh_music_energy_per_anode[i*8+j]->SetLineColor(1);
      fh_music_energy_per_anode[i*8+j]->Draw("");
     }
    }

    //  CANVAS 2  -------------------------------     
    cTpcCal[0] = new TCanvas("TPC21_csum", "CSum info for Tpcs", 10, 10, 800, 700);
    cTpcCal[0]->Divide(2,2);
    cTpcCal[1] = new TCanvas("TPC22_csum", "CSum info for Tpcs", 10, 10, 800, 700);
    cTpcCal[1]->Divide(2,2);
    cTpcCal[2] = new TCanvas("TPC41_csum", "CSum info for Tpcs", 10, 10, 800, 700);
    cTpcCal[2]->Divide(2,2);
    cTpcCal[3] = new TCanvas("TPC42_csum", "CSum info for Tpcs", 10, 10, 800, 700);
    cTpcCal[3]->Divide(2,2);
    cCalx = new TCanvas("TPC_DeltaX", "DeltaX info for Tpcs", 10, 10, 800, 700);
    cCalx->Divide(2,2);

    //Csum tpc data
    for(Int_t i=0;i<4;i++){//number of TPCs
      sprintf(Name1, "fh_tpc_deltax_%d", i+1);
      if(i<2)sprintf(Name2, "DeltaX for TPC 2%d at S2", i+1);
      else sprintf(Name2, "DeltaX for TPC 4%d at S4", i-1);
      fh_tpc_deltax[i] = new TH1F(Name1, Name2, 150, -500, 500);
      fh_tpc_deltax[i]->GetXaxis()->SetTitle("Channels");
      fh_tpc_deltax[i]->GetYaxis()->SetTitle("Counts");
      fh_tpc_deltax[i]->GetYaxis()->SetTitleOffset(1.2);
      fh_tpc_deltax[i]->GetXaxis()->CenterTitle(true);
      fh_tpc_deltax[i]->GetYaxis()->CenterTitle(true);
      fh_tpc_deltax[i]->GetXaxis()->SetLabelSize(0.045);
      fh_tpc_deltax[i]->GetXaxis()->SetTitleSize(0.045);
      cCalx->cd(i+1);
      fh_tpc_deltax[i]->SetFillColor(3);
      fh_tpc_deltax[i]->SetLineColor(1);
      fh_tpc_deltax[i]->Draw("");
     for(Int_t j=0;j<4;j++){//4 histo per detector
      sprintf(Name1, "fh_tpc_csum_%d", i*4+j);
      if(i<2)sprintf(Name2, "CSum for TPC 2%d and DT- %d", i+1, j);
      else sprintf(Name2, "CSum for TPC 4%d and DT- %d", i-1, j);
      fh_tpc_csum[i*4+j] = new TH1F(Name1, Name2, 500, 0, 4092);
      fh_tpc_csum[i*4+j]->GetXaxis()->SetTitle("Channels");
      fh_tpc_csum[i*4+j]->GetYaxis()->SetTitle("Counts");
      fh_tpc_csum[i*4+j]->GetYaxis()->SetTitleOffset(1.2);
      fh_tpc_csum[i*4+j]->GetXaxis()->CenterTitle(true);
      fh_tpc_csum[i*4+j]->GetYaxis()->CenterTitle(true);
      fh_tpc_csum[i*4+j]->GetXaxis()->SetLabelSize(0.045);
      fh_tpc_csum[i*4+j]->GetXaxis()->SetTitleSize(0.045);
      cTpcCal[i]->cd(j+1);
      fh_tpc_csum[i*4+j]->SetFillColor(3);
      fh_tpc_csum[i*4+j]->SetLineColor(1);
      fh_tpc_csum[i*4+j]->Draw("");
     }
    }


    //  CANVAS 3  -------------------------------     

    cHit = new TCanvas("TPC_position_X", "TPC Hit info", 10, 10, 800, 700);
    cHit->Divide(2,2);

    //Hit TPC data
    for(Int_t i=0;i<4;i++){//one histo per detector
     sprintf(Name1, "fh_Tpc_hit_%d", i+1);	  
     if(i<2)sprintf(Name2, "X for TPC 2%d at S2", i+1);
     else   sprintf(Name2, "X for TPC 4%d at S4", i-1);
     fh_Tpc_hit[i] = new TH1F(Name1, Name2, 500, -100, 100.);    
     fh_Tpc_hit[i]->GetXaxis()->SetTitle("X [mm]");
     fh_Tpc_hit[i]->GetYaxis()->SetTitle("Counts");
     fh_Tpc_hit[i]->GetXaxis()->CenterTitle(true);
     fh_Tpc_hit[i]->GetYaxis()->CenterTitle(true);
     fh_Tpc_hit[i]->GetYaxis()->SetTitleOffset(1.15);
     fh_Tpc_hit[i]->GetXaxis()->SetTitleOffset(1.1);
     fh_Tpc_hit[i]->GetXaxis()->SetLabelSize(0.045);
     fh_Tpc_hit[i]->GetXaxis()->SetTitleSize(0.045);
     fh_Tpc_hit[i]->GetYaxis()->SetLabelSize(0.045);
     fh_Tpc_hit[i]->GetYaxis()->SetTitleSize(0.045);
     fh_Tpc_hit[i]->SetFillColor(2);
     fh_Tpc_hit[i]->SetLineColor(1);
     cHit->cd(i+1);
     fh_Tpc_hit[i]->Draw("col"); 
    }


    //  CANVAS 4  -------------------------------         
    c1ID = new TCanvas("FRS_ID", "frs info", 10, 10, 800, 700);

    //Analysis FRS data
    fh_Frs_Z = new TH1F("fh_Frs_Z", "Atomic number (Z)", 800, 40, 90.);
    fh_Frs_Z->GetXaxis()->SetTitle("Z");
    fh_Frs_Z->GetYaxis()->SetTitle("Counts");
    fh_Frs_Z->GetXaxis()->CenterTitle(true);
    fh_Frs_Z->GetYaxis()->CenterTitle(true);
    fh_Frs_Z->GetYaxis()->SetTitleOffset(1.1);
    fh_Frs_Z->GetXaxis()->SetTitleOffset(1.1);
    fh_Frs_Z->GetXaxis()->SetLabelSize(0.045);
    fh_Frs_Z->GetXaxis()->SetTitleSize(0.045);
    fh_Frs_Z->GetYaxis()->SetLabelSize(0.045);
    fh_Frs_Z->GetYaxis()->SetTitleSize(0.045);
    fh_Frs_Z->SetFillColor(4);
    fh_Frs_Z->SetLineColor(1);

    TPad *c1_1 = new TPad("pad11",fh_Frs_Z->GetName(),0.,0.51,0.49,0.98);
    c1_1->Draw();
    c1_1->cd();
    fh_Frs_Z->Draw("");
    c1_1->Modified();
    c1ID->cd();

    fh_Frs_Aq = new TH1F("fh_Frs_Aq", "A/q for fragments", 500, 2.38, 2.63);
    fh_Frs_Aq->GetXaxis()->SetTitle("A/q");
    fh_Frs_Aq->GetYaxis()->SetTitle("Counts");
    fh_Frs_Aq->GetXaxis()->SetLabelSize(0.045);
    fh_Frs_Aq->GetXaxis()->SetTitleSize(0.045);
    fh_Frs_Aq->GetXaxis()->CenterTitle(true);
    fh_Frs_Aq->GetYaxis()->CenterTitle(true);
    fh_Frs_Aq->GetYaxis()->SetTitleOffset(1.1);
    fh_Frs_Aq->GetXaxis()->SetTitleOffset(1.1);
    fh_Frs_Aq->GetYaxis()->SetLabelSize(0.045);
    fh_Frs_Aq->GetYaxis()->SetTitleSize(0.045);
    fh_Frs_Aq->SetFillColor(4);
    fh_Frs_Aq->SetLineColor(1);

    TPad *c1_2 = new TPad("pad12",fh_Frs_Aq->GetName(),0.,0.01,0.49,0.49);
    // c1_2->SetLogy();
    c1_2->Draw();
    c1_2->cd();
    fh_Frs_Aq->Draw("");
    c1_2->Modified();
    c1ID->cd();

    fh_Frs_ID = new TH2F("fh_Frs_ID", "FRS ID of fragments", 300, 2.45, 2.6, 200, 45, 55.);
    fh_Frs_ID->GetXaxis()->SetTitle("A/q");
    fh_Frs_ID->GetYaxis()->SetTitle("Atomic number (Z)");
    fh_Frs_ID->GetXaxis()->CenterTitle(true);
    fh_Frs_ID->GetYaxis()->CenterTitle(true);
    fh_Frs_ID->GetXaxis()->SetLabelSize(0.04);
    fh_Frs_ID->GetXaxis()->SetTitleSize(0.04);
    fh_Frs_ID->GetYaxis()->SetTitleOffset(1.1);
    fh_Frs_ID->GetXaxis()->SetTitleOffset(1.1);
    fh_Frs_ID->GetYaxis()->SetLabelSize(0.045);
    fh_Frs_ID->GetYaxis()->SetTitleSize(0.045);

    TPad *c1_3 = new TPad("pad13",fh_Frs_ID->GetName(),0.51,0.01,0.98,0.98);
    c1_3->Draw();
    c1_3->cd();
    fh_Frs_ID->Draw("col"); 
    c1_3->Modified();
    c1ID->cd();


    //  CANVAS 5  -------------------------------        
    cSCI21 = new TCanvas("SCI21_E", "sci21 info", 10, 10, 800, 700);

    //Analysis SCI21 data
    fh_sci21le = new TH1F("fh_sci21le", "SCI21-Left-Energy", 500, 0, 4092);
    fh_sci21le->GetXaxis()->SetTitle("Channels");
    fh_sci21le->GetYaxis()->SetTitle("Counts");
    fh_sci21le->GetXaxis()->CenterTitle(true);
    fh_sci21le->GetYaxis()->CenterTitle(true);
    fh_sci21le->GetYaxis()->SetTitleOffset(1.1);
    fh_sci21le->GetXaxis()->SetTitleOffset(1.1);
    fh_sci21le->GetXaxis()->SetLabelSize(0.045);
    fh_sci21le->GetXaxis()->SetTitleSize(0.045);
    fh_sci21le->GetYaxis()->SetLabelSize(0.045);
    fh_sci21le->GetYaxis()->SetTitleSize(0.045);
    fh_sci21le->SetFillColor(3);
    fh_sci21le->SetLineColor(1);

    TPad *c21 = new TPad("c21",fh_sci21le->GetName(),0.,0.51,0.49,0.98);
    c21->Draw();
    c21->cd();
    fh_sci21le->Draw("");
    c21->Modified();
    cSCI21->cd();

    fh_sci21re = new TH1F("fh_sci21re", "SCI21-Right-Energy", 500, 0, 4092);
    fh_sci21re->GetXaxis()->SetTitle("Channels");
    fh_sci21re->GetYaxis()->SetTitle("Counts");
    fh_sci21re->GetXaxis()->CenterTitle(true);
    fh_sci21re->GetYaxis()->CenterTitle(true);
    fh_sci21re->GetYaxis()->SetTitleOffset(1.1);
    fh_sci21re->GetXaxis()->SetTitleOffset(1.1);
    fh_sci21re->GetXaxis()->SetLabelSize(0.045);
    fh_sci21re->GetXaxis()->SetTitleSize(0.045);
    fh_sci21re->GetYaxis()->SetLabelSize(0.045);
    fh_sci21re->GetYaxis()->SetTitleSize(0.045);
    fh_sci21re->SetFillColor(3);
    fh_sci21re->SetLineColor(1);

    TPad *c22 = new TPad("c22",fh_sci21re->GetName(),0.,0.01,0.49,0.49);
    c22->Draw();
    c22->cd();
    fh_sci21re->Draw("");
    c22->Modified();
    cSCI21->cd();

    fh_sci21lere = new TH2F("fh_sci21lere", "SCI21-Energy", 200, 0, 4092, 200, 0, 4092);
    fh_sci21lere->GetXaxis()->SetTitle("Right [Channels]");
    fh_sci21lere->GetYaxis()->SetTitle("Left [Channels]");
    fh_sci21lere->GetXaxis()->CenterTitle(true);
    fh_sci21lere->GetYaxis()->CenterTitle(true);
    fh_sci21lere->GetXaxis()->SetLabelSize(0.03);
    fh_sci21lere->GetXaxis()->SetTitleSize(0.04);
    fh_sci21lere->GetYaxis()->SetTitleOffset(1.45);
    fh_sci21lere->GetXaxis()->SetTitleOffset(1.1);
    fh_sci21lere->GetYaxis()->SetLabelSize(0.03);
    fh_sci21lere->GetYaxis()->SetTitleSize(0.04);

    TPad *c23 = new TPad("c23",fh_sci21lere->GetName(),0.51,0.01,0.98,0.98);
    c23->Draw();
    c23->cd();
    c23->SetLeftMargin(0.14);
    fh_sci21lere->Draw("col"); 
    c23->Modified();
    cSCI21->cd();


   //  CANVAS 6  -------------------------------        
    cSCI41 = new TCanvas("SCI41_E", "sci41 info", 10, 10, 800, 700);

    //Analysis SCI41 data
    fh_sci41le = new TH1F("fh_sci41le", "SCI41-Left-Energy", 500, 0, 4092);
    fh_sci41le->GetXaxis()->SetTitle("Channels");
    fh_sci41le->GetYaxis()->SetTitle("Counts");
    fh_sci41le->GetXaxis()->CenterTitle(true);
    fh_sci41le->GetYaxis()->CenterTitle(true);
    fh_sci41le->GetYaxis()->SetTitleOffset(1.1);
    fh_sci41le->GetXaxis()->SetTitleOffset(1.1);
    fh_sci41le->GetXaxis()->SetLabelSize(0.045);
    fh_sci41le->GetXaxis()->SetTitleSize(0.045);
    fh_sci41le->GetYaxis()->SetLabelSize(0.045);
    fh_sci41le->GetYaxis()->SetTitleSize(0.045);
    fh_sci41le->SetFillColor(3);
    fh_sci41le->SetLineColor(1);

    TPad *c41 = new TPad("c41",fh_sci41le->GetName(),0.,0.51,0.49,0.98);
    c41->Draw();
    c41->cd();
    fh_sci41le->Draw("");
    c41->Modified();
    cSCI41->cd();

    fh_sci41re = new TH1F("fh_sci41re", "SCI41-Right-Energy", 500, 0, 4092);
    fh_sci41re->GetXaxis()->SetTitle("Channels");
    fh_sci41re->GetYaxis()->SetTitle("Counts");
    fh_sci41re->GetXaxis()->CenterTitle(true);
    fh_sci41re->GetYaxis()->CenterTitle(true);
    fh_sci41re->GetYaxis()->SetTitleOffset(1.1);
    fh_sci41re->GetXaxis()->SetTitleOffset(1.1);
    fh_sci41re->GetXaxis()->SetLabelSize(0.045);
    fh_sci41re->GetXaxis()->SetTitleSize(0.045);
    fh_sci41re->GetYaxis()->SetLabelSize(0.045);
    fh_sci41re->GetYaxis()->SetTitleSize(0.045);
    fh_sci41re->SetFillColor(3);
    fh_sci41re->SetLineColor(1);

    TPad *c42 = new TPad("c42",fh_sci41re->GetName(),0.,0.01,0.49,0.49);
    c42->Draw();
    c42->cd();
    fh_sci41re->Draw("");
    c42->Modified();
    cSCI41->cd();

    fh_sci41lere = new TH2F("fh_sci41lere", "SCI41-Energy", 200, 0, 4092, 200, 0, 4092);
    fh_sci41lere->GetXaxis()->SetTitle("Right [Channels]");
    fh_sci41lere->GetYaxis()->SetTitle("Left [Channels]");
    fh_sci41lere->GetXaxis()->CenterTitle(true);
    fh_sci41lere->GetYaxis()->CenterTitle(true);
    fh_sci41lere->GetXaxis()->SetLabelSize(0.03);
    fh_sci41lere->GetXaxis()->SetTitleSize(0.04);
    fh_sci41lere->GetYaxis()->SetTitleOffset(1.45);
    fh_sci41lere->GetXaxis()->SetTitleOffset(1.1);
    fh_sci41lere->GetYaxis()->SetLabelSize(0.03);
    fh_sci41lere->GetYaxis()->SetTitleSize(0.04);

    TPad *c43 = new TPad("c43",fh_sci41lere->GetName(),0.51,0.01,0.98,0.98);
    c43->Draw();
    c43->cd();
    c43->SetLeftMargin(0.14);
    fh_sci41lere->Draw("col"); 
    c43->Modified();
    cSCI41->cd();


    //MAIN FOLDER-FRS
    TFolder* mainfolFrs = new TFolder("FRS","FRS info");      
    mainfolFrs->Add(c1ID);
    mainfolFrs->Add(cMus1);
    mainfolFrs->Add(cMus2);
    mainfolFrs->Add(cHit);
    mainfolFrs->Add(cTpcCal[0]);
    mainfolFrs->Add(cTpcCal[1]);
    mainfolFrs->Add(cTpcCal[2]);
    mainfolFrs->Add(cTpcCal[3]);
    mainfolFrs->Add(cCalx);
    mainfolFrs->Add(cSCI21);
    mainfolFrs->Add(cSCI41);
    run->AddObject(mainfolFrs);

    //Register command to reset histograms
    run->GetHttpServer()->RegisterCommand("Reset_FRS_ID", Form("/Objects/%s/->Reset_FRS_Histo()", GetName()));
    run->GetHttpServer()->RegisterCommand("Reset_MUSICs", Form("/Objects/%s/->Reset_MUSIC_Histo()", GetName()));
    run->GetHttpServer()->RegisterCommand("Reset_TPCs", Form("/Objects/%s/->Reset_TPC_Histo()", GetName()));
    run->GetHttpServer()->RegisterCommand("Reset_SCIs", Form("/Objects/%s/->Reset_SCI_Histo()", GetName()));
    
  return kSUCCESS;
}

void R3BFrsOnlineSpectra::Reset_FRS_Histo()
{
    LOG(INFO) << "R3BFrsOnlineSpectra::Reset_FRS_Histo" << FairLogger::endl;

    fh_Frs_Z->Reset();
    fh_Frs_Aq->Reset();
    fh_Frs_ID->Reset();

}

void R3BFrsOnlineSpectra::Reset_SCI_Histo()
{
    LOG(INFO) << "R3BFrsOnlineSpectra::Reset_SCI_Histo" << FairLogger::endl;

    fh_sci21le->Reset();
    fh_sci21re->Reset();
    fh_sci21lere->Reset();
    fh_sci41le->Reset();
    fh_sci41re->Reset();
    fh_sci41lere->Reset();

}

void R3BFrsOnlineSpectra::Reset_MUSIC_Histo()
{
    LOG(INFO) << "R3BFrsOnlineSpectra::Reset_MUSIC_Histo" << FairLogger::endl;

    //Cal data
    for(Int_t i=0;i<16;i++)
    fh_music_energy_per_anode[i]->Reset();

}

void R3BFrsOnlineSpectra::Reset_TPC_Histo()
{
    LOG(INFO) << "R3BFrsOnlineSpectra::Reset_TPC_Histo" << FairLogger::endl;

    //Hit data
    for(Int_t i=0;i<4;i++){
     fh_Tpc_hit[i]->Reset();
     fh_tpc_deltax[i]->Reset();
    }
    //Cal data
    for(Int_t i=0;i<16;i++)
    fh_tpc_csum[i]->Reset();

}

void R3BFrsOnlineSpectra::Exec(Option_t* option) {
  
  FairRootManager* mgr = FairRootManager::Instance();
  if (NULL == mgr)
    LOG(FATAL) << "R3BFrsOnlineSpectra::Exec FairRootManager not found" << FairLogger::endl;

  //Fill mapped data
  if(fMappedItemsFrs && fMappedItemsFrs->GetEntriesFast()){
    Int_t nHits = fMappedItemsFrs->GetEntriesFast();
    for (Int_t ihit = 0; ihit < nHits; ihit++){
      R3BFrsMappedData* hit = 
	(R3BFrsMappedData*)fMappedItemsFrs->At(ihit);
      if (!hit) continue;
       fh_sci21le->Fill(hit->GetSCI21LE());
       fh_sci21re->Fill(hit->GetSCI21RE());
       fh_sci21lere->Fill(hit->GetSCI21RE(),hit->GetSCI21LE());
       fh_sci41le->Fill(hit->GetSCI41LE());
       fh_sci41re->Fill(hit->GetSCI41RE());
       fh_sci41lere->Fill(hit->GetSCI41RE(),hit->GetSCI41LE());
    }
  }

  //Fill cal music data
  if(fCalItemsMusic && fCalItemsMusic->GetEntriesFast()){
    Int_t nHits = fCalItemsMusic->GetEntriesFast();
       // std::cout << "hit:"<<nHits << std::endl;
    for (Int_t ihit = 0; ihit < nHits; ihit++){
      R3BMusicCalData* hit = 
	(R3BMusicCalData*)fCalItemsMusic->At(ihit);
      if (!hit) continue;
        //std::cout << "hit:"<<hit->GetDetectorId() << " " << hit->GetEnergy() << std::endl;
       fh_music_energy_per_anode[hit->GetDetectorId()*8+hit->GetAnodeId()]->Fill(hit->GetEnergy());
    }
  }

  //Fill hit music data
  if(fHitItemsMusic && fHitItemsMusic->GetEntriesFast()){
    Int_t nHits = fHitItemsMusic->GetEntriesFast();
       // std::cout << "hit:"<<nHits << std::endl;
  /*  for (Int_t ihit = 0; ihit < nHits; ihit++){
      R3BAmsStripCalData* hit = 
	(R3BAmsStripCalData*)fCalItemsAms->At(ihit);
      if (!hit) continue;
        //std::cout << "hit:"<<hit->GetDetId() << " " << hit->GetSideId() << std::endl;
       fh_Ams_energy_allCalStrips[hit->GetDetId()*2+hit->GetSideId()]->Fill(hit->GetStripId(),hit->GetEnergy());
    }
*/
  }

  //Fill cal tpc data
  Int_t deltaX[8];
  if(fCalItemsTpc && fCalItemsTpc->GetEntriesFast()){
    Int_t nHits = fCalItemsTpc->GetEntriesFast();
    //std::cout << nHits << std::endl;
    for (Int_t ihit = 0; ihit < nHits; ihit++){
      R3BTpcCalData* hit = 
	(R3BTpcCalData*)fCalItemsTpc->At(ihit);
      if (!hit) continue;
      if(hit->GetXYId()){
       fh_tpc_csum[hit->GetDetectorId()*4+hit->GetSecId()]->Fill(hit->GetControlPar());
      }else{
       deltaX[hit->GetDetectorId()*2+hit->GetSecId()]=hit->GetControlPar();
      }
    }
   //DeltaX for TPCs: X1-X0
   fh_tpc_deltax[0]->Fill(deltaX[1]-deltaX[0]);
   fh_tpc_deltax[1]->Fill(deltaX[3]-deltaX[2]);
   fh_tpc_deltax[2]->Fill(deltaX[5]-deltaX[4]);
   fh_tpc_deltax[3]->Fill(deltaX[7]-deltaX[6]);
  }

  //Fill FRS data
  if(fAnaItemsFrs && fAnaItemsFrs->GetEntriesFast()){
    Int_t nHits = fAnaItemsFrs->GetEntriesFast();
    //std::cout << nHits << std::endl;
    for (Int_t ihit = 0; ihit < nHits; ihit++){
      R3BFrsData* hit = 
	(R3BFrsData*)fAnaItemsFrs->At(ihit);
      if (!hit) continue;
      fh_Frs_Z->Fill(hit->GetZ());
      fh_Frs_Aq->Fill(hit->GetAq());
      fh_Frs_ID->Fill(hit->GetAq(),hit->GetZ());}
  }

  //Fill hit tpc data
  if(fHitItemsTpc && fHitItemsTpc->GetEntriesFast()){
    Int_t nHits = fHitItemsTpc->GetEntriesFast();
    //std::cout << nHits << std::endl;
    for (Int_t ihit = 0; ihit < nHits; ihit++){
      R3BTpcHitData* hit = 
	(R3BTpcHitData*)fHitItemsTpc->At(ihit);
      if (!hit) continue;
      fh_Tpc_hit[hit->GetDetectorId()]->Fill(hit->GetX());
    }
  }

  fNEvents += 1;
}


void R3BFrsOnlineSpectra::FinishEvent() {

    if (fMappedItemsFrs)
    {
        fMappedItemsFrs->Clear();
    }
    if (fCalItemsMusic)
    {
        fCalItemsMusic->Clear();
    }
    if (fCalItemsTpc)
    {
        fCalItemsTpc->Clear();
    }
    if (fHitItemsTpc)
    {
        fHitItemsTpc->Clear();
    }
    if (fAnaItemsFrs)
    {
        fAnaItemsFrs->Clear();
    }
}


void R3BFrsOnlineSpectra::FinishTask() {

    if (fMappedItemsFrs){
	cSCI21->Write();
	cSCI41->Write();
    }
    if(fCalItemsMusic){
	cMus1->Write();
	cMus2->Write();
    }
    if (fCalItemsTpc)
    {  
        cCalx->Write();
	cTpcCal[0]->Write();
	cTpcCal[1]->Write();
	cTpcCal[2]->Write();
	cTpcCal[3]->Write();
    }
    if (fHitItemsTpc)
    {
	cHit->Write();
    }
    if (fAnaItemsFrs)
    {
	c1ID->Write();
    }
}

ClassImp(R3BFrsOnlineSpectra)

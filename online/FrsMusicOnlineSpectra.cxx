// ------------------------------------------------------------
// -----                FrsMusicOnlineSpectra                -----
// -----    Created 16/11/19  by J.L. Rodriguez-Sanchez   -----
// -----           Fill MW  online histograms             -----
// ------------------------------------------------------------

/*
 * This task should fill histograms with FRS online data
 */

#include "FrsMusicOnlineSpectra.h"
#include "FRSMusicMappedData.h"
#include "FRSMusicCalData.h"
#include "FRSMusicHitData.h"
#include "R3BEventHeader.h"
#include "THttpServer.h"

#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"
#include "TCanvas.h"
#include "TFolder.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TVector3.h"

#include "TClonesArray.h"
#include "TLegend.h"
#include "TLegendEntry.h"
#include "TMath.h"
#include "TRandom.h"
#include <array>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdlib.h>

using namespace std;

FrsMusicOnlineSpectra::FrsMusicOnlineSpectra()
    : FairTask("FrsMusicOnlineSpectra", 1)
    , fMapItems(NULL)
    , fCalItems(NULL)
    , fHitItems(NULL)
    , fNameDet("MUSIC")
    , fNEvents(0)
{
}

FrsMusicOnlineSpectra::FrsMusicOnlineSpectra(const TString& name, Int_t iVerbose, const TString& namedet)
    : FairTask(name, iVerbose)
    , fMapItems(NULL)
    , fCalItems(NULL)
    , fHitItems(NULL)
    , fNameDet(namedet)
    , fNEvents(0)
{
}

FrsMusicOnlineSpectra::~FrsMusicOnlineSpectra()
{
    LOG(INFO) << "Frs" + fNameDet + "OnlineSpectra::Delete instance";
    if (fMapItems)
        delete fMapItems;
    if (fCalItems)
        delete fCalItems;
    if (fHitItems)
        delete fHitItems;
}

InitStatus FrsMusicOnlineSpectra::Init()
{

    LOG(INFO) << "Frs" + fNameDet + "OnlineSpectra::Init ";

    FairRootManager* mgr = FairRootManager::Instance();
    if (NULL == mgr)
        LOG(FATAL) << "Frs" + fNameDet + "OnlineSpectra::Init FairRootManager not found";
    // header = (R3BEventHeader*)mgr->GetObject("R3BEventHeader");

    FairRunOnline* run = FairRunOnline::Instance();
    run->GetHttpServer()->Register("", this);

    // get access to mapped data of the Music detector
    fMapItems = (TClonesArray*)mgr->GetObject("FRSMusicMappedData");
    if (!fMapItems)
    {
        return kFATAL;
    }
    // get access to Cal Music data
    fCalItems = (TClonesArray*)mgr->GetObject("FRSMusicCalData");
    if (!fCalItems)
    {
        LOG(WARNING) << "FrsMusicOnlineSpectra: Not found object FRSMusicCalData";
    }

    // get access to Hit Music data
    fHitItems = (TClonesArray*)mgr->GetObject("FRSMusicHitData");
    if (!fHitItems)
    {
        LOG(WARNING) << "FrsMusicOnlineSpectra: Not found object FRSMusicHitData";
    }

    // Create histograms for detectors
    TString Name1;
    TString Name2;

    // Mapped data
    //  CANVAS 1  -------------------------------
    Name1 =  fNameDet + "_E_raw";
    Name2 = fNameDet + ": ERaw info";
    cMusE = new TCanvas(Name1, Name2, 10, 10, 800, 700);
    cMusE->Divide(4, 2);

        for (Int_t j = 0; j < N_ANODES; j++)
        { // N_ANODES histograms per detector
            Name1 =  fNameDet + "_E"+j;
            Name2 = fNameDet + ": E_"+j+" (channels)";
            fh_music_energy_per_anode[j] = new TH1F(Name1, Name2, 500, 0, 4092);
            fh_music_energy_per_anode[j]->GetXaxis()->SetTitle("Energy");
            fh_music_energy_per_anode[j]->GetYaxis()->SetTitle("Counts");
            fh_music_energy_per_anode[j]->GetYaxis()->SetTitleOffset(1.2);
            fh_music_energy_per_anode[j]->GetXaxis()->CenterTitle(true);
            fh_music_energy_per_anode[j]->GetYaxis()->CenterTitle(true);
            fh_music_energy_per_anode[j]->GetXaxis()->SetLabelSize(0.045);
            fh_music_energy_per_anode[j]->GetXaxis()->SetTitleSize(0.045);
            fh_music_energy_per_anode[j]->SetFillColor(kGreen - 3);
            fh_music_energy_per_anode[j]->SetLineColor(1);
            cMusE->cd(j + 1);
            fh_music_energy_per_anode[j]->Draw("");
        }
    
    //  CANVAS 2  -------------------------------
    Name1 =  fNameDet + "_T_raw";
    Name2 = fNameDet + ": TRaw info";
    cMusT = new TCanvas(Name1, Name2, 10, 10, 800, 700);
    cMusT->Divide(4, 2);

        for (Int_t j = 0; j < N_ANODES; j++)
        { // N_ANODES histograms per detector
            Name1 =  fNameDet + "_T"+j;
            Name2 = fNameDet + ": T_"+j+" (channels)";
            fh_music_t_per_anode[j] = new TH1F(Name1, Name2, 500, 0, 4092);
            fh_music_t_per_anode[j]->GetXaxis()->SetTitle("T");
            fh_music_t_per_anode[j]->GetYaxis()->SetTitle("Counts");
            fh_music_t_per_anode[j]->GetYaxis()->SetTitleOffset(1.2);
            fh_music_t_per_anode[j]->GetXaxis()->CenterTitle(true);
            fh_music_t_per_anode[j]->GetYaxis()->CenterTitle(true);
            fh_music_t_per_anode[j]->GetXaxis()->SetLabelSize(0.045);
            fh_music_t_per_anode[j]->GetXaxis()->SetTitleSize(0.045);
            fh_music_t_per_anode[j]->SetFillColor(kGreen - 3);
            fh_music_t_per_anode[j]->SetLineColor(1);
            cMusT->cd(j + 1);
            fh_music_t_per_anode[j]->Draw("");
        }


    // Cal data
    //  CANVAS 3  -------------------------------
    Name1 =  fNameDet + "_E_cal";
    Name2 = fNameDet + ": ECal info";
    cMusECal = new TCanvas(Name1, Name2, 10, 10, 800, 700);
    cMusECal->Divide(4, 2);

        for (Int_t j = 0; j < N_ANODES; j++)
        { // N_ANODES histograms per detector
            Name1 =  fNameDet + "_ECal"+j;
            Name2 = fNameDet + ": ECal_"+j+" (channels)";
            fh_music_energy_per_anodecal[j] = new TH1F(Name1, Name2, 500, 0, 4092);
            fh_music_energy_per_anodecal[j]->GetXaxis()->SetTitle("Energy");
            fh_music_energy_per_anodecal[j]->GetYaxis()->SetTitle("Counts");
            fh_music_energy_per_anodecal[j]->GetYaxis()->SetTitleOffset(1.2);
            fh_music_energy_per_anodecal[j]->GetXaxis()->CenterTitle(true);

            fh_music_energy_per_anodecal[j]->GetYaxis()->CenterTitle(true);
            fh_music_energy_per_anodecal[j]->GetXaxis()->SetLabelSize(0.045);
            fh_music_energy_per_anodecal[j]->GetXaxis()->SetTitleSize(0.045);
            fh_music_energy_per_anodecal[j]->SetFillColor(kGreen - 3);
            fh_music_energy_per_anodecal[j]->SetLineColor(1);
            cMusECal->cd(j + 1);
            fh_music_energy_per_anodecal[j]->Draw("");
        }

    //  CANVAS 4  -------------------------------
    Name1 =  fNameDet + "_Z";
    Name2 = fNameDet + ": Z info";
    cMushit = new TCanvas(Name1, Name2, 10, 10, 800, 700);
    Name1 =  fNameDet + "_Z";
    Name2 = fNameDet + ": Z (charge)";
    fh_music_Z = new TH1F(Name1, Name2, 2800, 0, 82);
    fh_music_Z->GetXaxis()->SetTitle("Charge-Z");
    fh_music_Z->GetYaxis()->SetTitle("Counts");
    fh_music_Z->GetYaxis()->SetTitleOffset(1.2);
    fh_music_Z->GetXaxis()->CenterTitle(true);
    fh_music_Z->GetYaxis()->CenterTitle(true);
    fh_music_Z->GetXaxis()->SetLabelSize(0.045);
    fh_music_Z->GetXaxis()->SetTitleSize(0.045);
    fh_music_Z->SetFillColor(kGreen - 3);
    fh_music_Z->SetLineColor(1);
    fh_music_Z->Draw("");

    // MAIN FOLDER
    TFolder* mainfol = new TFolder(fNameDet, fNameDet + " info");
    mainfol->Add(cMusE);
    mainfol->Add(cMusT);
    mainfol->Add(cMusECal);
    mainfol->Add(cMushit);
    run->AddObject(mainfol);

    // Register command to reset histograms
    //run->GetHttpServer()->RegisterCommand("Reset_" + fNameDet + "_HIST",
    //                                      Form("/Objects/%s/->Reset_Histo()", GetName()));

    return kSUCCESS;
}

void FrsMusicOnlineSpectra::Reset_Histo()
{
    LOG(INFO) << "Frs" + fNameDet + "OnlineSpectra::Reset_Histo";
    // Map data
    for (Int_t i = 0; i < N_ANODES; i++)
    {
        fh_music_energy_per_anode[i]->Reset();
        fh_music_t_per_anode[i]->Reset();
    }
    // Cal data
    for (Int_t i = 0; i < N_ANODES; i++)
    {
        fh_music_energy_per_anodecal[i]->Reset();
        //fh_music_t_per_anode[i]->Reset();
    }
    fh_music_Z->Reset();
}

void FrsMusicOnlineSpectra::Exec(Option_t* option)
{
    FairRootManager* mgr = FairRootManager::Instance();
    if (NULL == mgr)
        LOG(FATAL) << "Frs" + fNameDet + "OnlineSpectra::Exec FairRootManager not found";

    // Fill map music data
    if (fMapItems && fMapItems->GetEntriesFast())
    {
        Int_t nHits = fMapItems->GetEntriesFast();
        for (Int_t ihit = 0; ihit < nHits; ihit++)
        {
            FRSMusicMappedData* hit = (FRSMusicMappedData*)fMapItems->At(ihit);
            if (!hit)
                continue;
            if( TString(fDetectorNames[hit->GetDetectorId()]).CompareTo(fNameDet)==0 ){
             fh_music_energy_per_anode[hit->GetAnodeId()]->Fill(hit->GetEnergy());
            }
        }

    }

    // Fill cal music data
    if (fCalItems && fCalItems->GetEntriesFast())
    {
        Int_t nHits = fCalItems->GetEntriesFast();
        // std::cout << "hit:"<<nHits << std::endl;
        for (Int_t ihit = 0; ihit < nHits; ihit++)
        {
            FRSMusicCalData* hit = (FRSMusicCalData*)fCalItems->At(ihit);
            if (!hit)
                continue;
            if( TString(fDetectorNames[hit->GetDetectorId()]).CompareTo(fNameDet)==0 ){
             fh_music_energy_per_anodecal[hit->GetAnodeId()]->Fill(hit->GetEnergy());
            }
        }
    }

    // Fill hit music data
    if (fHitItems && fHitItems->GetEntriesFast())
    {
        Int_t nHits = fHitItems->GetEntriesFast();
        for (Int_t ihit = 0; ihit < nHits; ihit++)
        {
            FRSMusicHitData* hit = (FRSMusicHitData*)fHitItems->At(ihit);
            if (!hit)
                continue;
            if( TString(fDetectorNames[hit->GetDetectorId()]).CompareTo(fNameDet)==0 )
             fh_music_Z->Fill(hit->GetZ());
        }
    }

    fNEvents += 1;
}

void FrsMusicOnlineSpectra::FinishEvent()
{
    if (fMapItems)
    {
        fMapItems->Clear();
    }
    if (fCalItems)
    {
        fCalItems->Clear();
    }
    if (fHitItems)
    {
        fHitItems->Clear();
    }
}

void FrsMusicOnlineSpectra::FinishTask()
{
    if (fMapItems)
    {
        cMusE->Write();
        cMusT->Write();
    }
    if (fCalItems)
    {
        cMusECal->Write();
    }
    if (fHitItems)
    {
        cMushit->Write();
    }
}

ClassImp(FrsMusicOnlineSpectra)

// ------------------------------------------------------------
// -----                  FrsTpcOnlineSpectra             -----
// -----    Created 16/11/19  by J.L. Rodriguez-Sanchez   -----
// -----           Fill FRS online histograms             -----
// ------------------------------------------------------------

/*
 * This task should fill histograms with FRS online data
 */

#include "FrsTpcOnlineSpectra.h"

#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"
#include "R3BEventHeader.h"
#include "R3BFrsS4Data.h"
#include "R3BTpcCalData.h"
#include "R3BTpcHitData.h"
#include "R3BWRData.h"
#include "TCanvas.h"
#include "TClonesArray.h"
#include "TFolder.h"
#include "TH1F.h"
#include "TH2F.h"
#include "THttpServer.h"
#include "TLegend.h"
#include "TLegendEntry.h"
#include "TMath.h"
#include "TRandom.h"
#include "TVector3.h"

#include <array>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>

double tpcpos[4] = {2960., 3985., 415., 1535.};   // FIXME

using namespace std;

FrsTpcOnlineSpectra::FrsTpcOnlineSpectra()
    : FairTask("FrsTpcOnlineSpectra", 1)
    , fHitItemsTpc(NULL)
    , fCalItemsTpc(NULL)
    , fNEvents(0)
{}

FrsTpcOnlineSpectra::FrsTpcOnlineSpectra(const char* name, Int_t iVerbose)
    : FairTask(name, iVerbose)
    , fHitItemsTpc(NULL)
    , fCalItemsTpc(NULL)
    , fNEvents(0)
{}

FrsTpcOnlineSpectra::~FrsTpcOnlineSpectra()
{
    LOG(INFO) << "FrsTpcOnlineSpectra::Delete instance";
    if (fHitItemsTpc)
        delete fHitItemsTpc;
    if (fCalItemsTpc)
        delete fCalItemsTpc;
}

InitStatus FrsTpcOnlineSpectra::Init()
{

    LOG(INFO) << "FrsTpcOnlineSpectra::Init ";

    // try to get a handle on the EventHeader. EventHeader may not be
    // present though and hence may be null. Take care when using.

    FairRootManager* mgr = FairRootManager::Instance();
    if (NULL == mgr)
        LOG(FATAL) << "FrsTpcOnlineSpectra::Init FairRootManager not found";
    header = (R3BEventHeader*)mgr->GetObject("R3BEventHeader");

    FairRunOnline* run = FairRunOnline::Instance();
    run->GetHttpServer()->Register("", this);

    // get access to Cal Tpc data
    fCalItemsTpc = (TClonesArray*)mgr->GetObject("TpcCalData");

    // get access to Hit Tpc data
    fHitItemsTpc = (TClonesArray*)mgr->GetObject("TpcHitData");

    // create histograms of all detectors

    char Name1[255];
    char Name2[255];

    //  CANVAS 2  -------------------------------
    cTpcCal[0] = new TCanvas("TPC21_csum", "CSum info for Tpcs", 10, 10, 800, 700);
    cTpcCal[0]->Divide(2, 2);
    cTpcCal[1] = new TCanvas("TPC22_csum", "CSum info for Tpcs", 10, 10, 800, 700);
    cTpcCal[1]->Divide(2, 2);
    cTpcCal[2] = new TCanvas("TPC41_csum", "CSum info for Tpcs", 10, 10, 800, 700);
    cTpcCal[2]->Divide(2, 2);
    cTpcCal[3] = new TCanvas("TPC42_csum", "CSum info for Tpcs", 10, 10, 800, 700);
    cTpcCal[3]->Divide(2, 2);
    cTpcCal[4] = new TCanvas("TPC31_csum", "CSum info for Tpcs", 10, 10, 800, 700);
    cTpcCal[4]->Divide(2, 2);
    cCalx = new TCanvas("TPC_DeltaX", "DeltaX info for Tpcs", 10, 10, 800, 700);
    cCalx->Divide(2, 2);
    // cCalx31 = new TCanvas("TPC31_Summary", "Info for Tpc 31", 10, 10, 800, 700);
    // cCalx31->Divide(2, 2);

    // Csum tpc data
    for (Int_t i = 0; i < 4; i++) {   // number of TPCs
        sprintf(Name1, "fh_tpc_deltax_%d", i + 1);
        if (i < 2)
            sprintf(Name2, "DeltaX for TPC 2%d at S2", i + 1);
        else
            sprintf(Name2, "DeltaX for TPC 4%d at S4", i - 1);
        fh_tpc_deltax[i] = new TH1F(Name1, Name2, 150, -500, 500);
        fh_tpc_deltax[i]->GetXaxis()->SetTitle("Channels");
        fh_tpc_deltax[i]->GetYaxis()->SetTitle("Counts");
        fh_tpc_deltax[i]->GetYaxis()->SetTitleOffset(1.2);
        fh_tpc_deltax[i]->GetXaxis()->CenterTitle(true);
        fh_tpc_deltax[i]->GetYaxis()->CenterTitle(true);
        fh_tpc_deltax[i]->GetXaxis()->SetLabelSize(0.045);
        fh_tpc_deltax[i]->GetXaxis()->SetTitleSize(0.045);
        cCalx->cd(i + 1);
        fh_tpc_deltax[i]->SetFillColor(kGreen - 3);
        fh_tpc_deltax[i]->SetLineColor(1);
        fh_tpc_deltax[i]->Draw("");
        for (Int_t j = 0; j < 4; j++) {   // 4 histo per detector
            sprintf(Name1, "fh_tpc_csum_%d", i * 4 + j);
            if (i < 2)
                sprintf(Name2, "CSum for TPC 2%d and DT- %d", i + 1, j);
            else
                sprintf(Name2, "CSum for TPC 4%d and DT- %d", i - 1, j);
            fh_tpc_csum[i * 4 + j] = new TH1F(Name1, Name2, 1000, -4092, 4092);
            fh_tpc_csum[i * 4 + j]->GetXaxis()->SetTitle("Channels");
            fh_tpc_csum[i * 4 + j]->GetYaxis()->SetTitle("Counts");
            fh_tpc_csum[i * 4 + j]->GetYaxis()->SetTitleOffset(1.2);
            fh_tpc_csum[i * 4 + j]->GetXaxis()->CenterTitle(true);
            fh_tpc_csum[i * 4 + j]->GetYaxis()->CenterTitle(true);
            fh_tpc_csum[i * 4 + j]->GetXaxis()->SetLabelSize(0.045);
            fh_tpc_csum[i * 4 + j]->GetXaxis()->SetTitleSize(0.045);
            cTpcCal[i]->cd(j + 1);
            fh_tpc_csum[i * 4 + j]->SetFillColor(kGreen - 3);
            fh_tpc_csum[i * 4 + j]->SetLineColor(1);
            fh_tpc_csum[i * 4 + j]->Draw("");
        }
    }

    //  CANVAS 3  -------------------------------
    cHitx = new TCanvas("TPC_position_X", "TPC Hit info", 10, 10, 800, 700);
    cHitx->Divide(2, 2);

    // Hit TPC data
    for (Int_t i = 0; i < 4; i++) {   // one histo per detector
        sprintf(Name1, "fh_Tpc_hitx_%d", i + 1);
        if (i < 2)
            sprintf(Name2, "X for TPC 2%d at S2", i + 1);
        else if (i < 4)
            sprintf(Name2, "X for TPC 4%d at S4", i - 1);
        // else
        //    sprintf(Name2, "X for TPC 31 at S4");
        fh_Tpc_hitx[i] = new TH1F(Name1, Name2, 500, -100, 100.);
        fh_Tpc_hitx[i]->GetXaxis()->SetTitle("X [mm]");
        fh_Tpc_hitx[i]->GetYaxis()->SetTitle("Counts");
        fh_Tpc_hitx[i]->GetXaxis()->CenterTitle(true);
        fh_Tpc_hitx[i]->GetYaxis()->CenterTitle(true);
        fh_Tpc_hitx[i]->GetYaxis()->SetTitleOffset(1.15);
        fh_Tpc_hitx[i]->GetXaxis()->SetTitleOffset(1.1);
        fh_Tpc_hitx[i]->GetXaxis()->SetLabelSize(0.045);
        fh_Tpc_hitx[i]->GetXaxis()->SetTitleSize(0.045);
        fh_Tpc_hitx[i]->GetYaxis()->SetLabelSize(0.045);
        fh_Tpc_hitx[i]->GetYaxis()->SetTitleSize(0.045);
        fh_Tpc_hitx[i]->SetFillColor(2);
        fh_Tpc_hitx[i]->SetLineColor(1);
        // if (i < 4)
        cHitx->cd(i + 1);
        // else
        // cCalx31->cd(2);
        fh_Tpc_hitx[i]->Draw("");
    }

    //  CANVAS 4  -------------------------------
    cHity = new TCanvas("TPC_position_Y", "TPC Hit info", 10, 10, 800, 700);
    cHity->Divide(2, 2);

    // Hit TPC data
    for (Int_t i = 0; i < 4; i++) {   // one histo per detector
        sprintf(Name1, "fh_Tpc_hity_%d", i + 1);
        if (i < 2)
            sprintf(Name2, "Y for TPC 2%d at S2", i + 1);
        else if (i < 4)
            sprintf(Name2, "Y for TPC 4%d at S4", i - 1);
        // else
        //   sprintf(Name2, "Y for TPC 31 at S4");
        fh_Tpc_hity[i] = new TH1F(Name1, Name2, 500, -100, 100.);
        fh_Tpc_hity[i]->GetXaxis()->SetTitle("Y [mm]");
        fh_Tpc_hity[i]->GetYaxis()->SetTitle("Counts");
        fh_Tpc_hity[i]->GetXaxis()->CenterTitle(true);
        fh_Tpc_hity[i]->GetYaxis()->CenterTitle(true);
        fh_Tpc_hity[i]->GetYaxis()->SetTitleOffset(1.15);
        fh_Tpc_hity[i]->GetXaxis()->SetTitleOffset(1.1);
        fh_Tpc_hity[i]->GetXaxis()->SetLabelSize(0.045);
        fh_Tpc_hity[i]->GetXaxis()->SetTitleSize(0.045);
        fh_Tpc_hity[i]->GetYaxis()->SetLabelSize(0.045);
        fh_Tpc_hity[i]->GetYaxis()->SetTitleSize(0.045);
        fh_Tpc_hity[i]->SetFillColor(2);
        fh_Tpc_hity[i]->SetLineColor(1);
        // if (i < 4)
        cHity->cd(i + 1);
        // else
        //  cCalx31->cd(3);
        fh_Tpc_hity[i]->Draw("");
    }

    //  CANVAS 5  -------------------------------
    cHitxy = new TCanvas("TPC_position_XY", "TPC Hit info", 10, 10, 800, 700);
    cHitxy->Divide(2, 2);

    // Hit TPC data
    for (Int_t i = 0; i < 4; i++) {   // one histo per detector
        sprintf(Name1, "fh_Tpc_hitxy_%d", i + 1);
        if (i < 2)
            sprintf(Name2, "XY for TPC 2%d at S2", i + 1);
        else if (i < 4)
            sprintf(Name2, "XY for TPC 4%d at S4", i - 1);
        // else
        // sprintf(Name2, "XY for TPC 31 at S4");
        fh_Tpc_hitxy[i] = new TH2F(Name1, Name2, 500, -100, 100., 500, -100, 100.);
        fh_Tpc_hitxy[i]->GetXaxis()->SetTitle("X [mm]");
        fh_Tpc_hitxy[i]->GetYaxis()->SetTitle("Y [mm]");
        fh_Tpc_hitxy[i]->GetXaxis()->CenterTitle(true);
        fh_Tpc_hitxy[i]->GetYaxis()->CenterTitle(true);
        fh_Tpc_hitxy[i]->GetYaxis()->SetTitleOffset(1.15);
        fh_Tpc_hitxy[i]->GetXaxis()->SetTitleOffset(1.1);
        fh_Tpc_hitxy[i]->GetXaxis()->SetLabelSize(0.045);
        fh_Tpc_hitxy[i]->GetXaxis()->SetTitleSize(0.045);
        fh_Tpc_hitxy[i]->GetYaxis()->SetLabelSize(0.045);
        fh_Tpc_hitxy[i]->GetYaxis()->SetTitleSize(0.045);
        // if (i < 4)
        cHitxy->cd(i + 1);
        // else
        //   cCalx31->cd(4);
        fh_Tpc_hitxy[i]->Draw("col");
    }

    //  CANVAS 11  -------------------------------
    cTransS2 = new TCanvas("Position_Angle_S2", "Transmission info at S2", 10, 10, 800, 700);

    fh_ts2 = new TH2F("fh_ts2", "Focal Plane at S2", 500, -100, 100, 500, -18, 18);
    fh_ts2->GetXaxis()->SetTitle("Position [mm]");
    fh_ts2->GetYaxis()->SetTitle("Angle [mrad]");
    fh_ts2->GetXaxis()->CenterTitle(true);
    fh_ts2->GetYaxis()->CenterTitle(true);
    fh_ts2->GetXaxis()->SetLabelSize(0.03);
    fh_ts2->GetXaxis()->SetTitleSize(0.04);
    fh_ts2->GetYaxis()->SetTitleOffset(1.15);
    fh_ts2->GetXaxis()->SetTitleOffset(1.1);
    fh_ts2->GetYaxis()->SetLabelSize(0.03);
    fh_ts2->GetYaxis()->SetTitleSize(0.04);
    fh_ts2->Draw("colz");

    cTrackS2 = new TCanvas("Tracking_S2", "Tracking info at S2", 10, 10, 800, 700);
    fh_tr2 = new TH2F("fh_tr2", "Tracking at S2", 200, 0, 4100, 200, -100, 100);
    fh_tr2->GetXaxis()->SetTitle("Position Z [mm]");
    fh_tr2->GetYaxis()->SetTitle("Position X [mm]");
    fh_tr2->GetXaxis()->CenterTitle(true);
    fh_tr2->GetYaxis()->CenterTitle(true);
    fh_tr2->GetXaxis()->SetLabelSize(0.03);
    fh_tr2->GetXaxis()->SetTitleSize(0.04);
    fh_tr2->GetYaxis()->SetTitleOffset(1.15);
    fh_tr2->GetXaxis()->SetTitleOffset(1.1);
    fh_tr2->GetYaxis()->SetLabelSize(0.03);
    fh_tr2->GetYaxis()->SetTitleSize(0.04);
    fh_tr2->Draw("colz");

    //  CANVAS 12  -------------------------------
    cTransS4 = new TCanvas("Position_Angle_S4", "Transmission info at S4", 10, 10, 800, 700);
    fh_ts4 = new TH2F("fh_ts4", "Focal Plane at S4", 500, -100, 100, 500, -18, 18);
    fh_ts4->GetXaxis()->SetTitle("Position [mm]");
    fh_ts4->GetYaxis()->SetTitle("Angle [mrad]");
    fh_ts4->GetXaxis()->CenterTitle(true);
    fh_ts4->GetYaxis()->CenterTitle(true);
    fh_ts4->GetXaxis()->SetLabelSize(0.03);
    fh_ts4->GetXaxis()->SetTitleSize(0.04);
    fh_ts4->GetYaxis()->SetTitleOffset(1.15);
    fh_ts4->GetXaxis()->SetTitleOffset(1.1);
    fh_ts4->GetYaxis()->SetLabelSize(0.03);
    fh_ts4->GetYaxis()->SetTitleSize(0.04);
    fh_ts4->Draw("col");

    cTrackS4 = new TCanvas("Tracking_S4", "Tracking info at S4", 10, 10, 800, 700);
    fh_tr4 = new TH2F("fh_tr4", "Tracking at S4", 200, 0, 3000, 200, -100, 100);
    fh_tr4->GetXaxis()->SetTitle("Position Z [mm]");
    fh_tr4->GetYaxis()->SetTitle("Position X [mm]");
    fh_tr4->GetXaxis()->CenterTitle(true);
    fh_tr4->GetYaxis()->CenterTitle(true);
    fh_tr4->GetXaxis()->SetLabelSize(0.03);
    fh_tr4->GetXaxis()->SetTitleSize(0.04);
    fh_tr4->GetYaxis()->SetTitleOffset(1.15);
    fh_tr4->GetXaxis()->SetTitleOffset(1.1);
    fh_tr4->GetYaxis()->SetLabelSize(0.03);
    fh_tr4->GetYaxis()->SetTitleSize(0.04);
    fh_tr4->Draw("col");

    // MAIN FOLDER-TPC
    TFolder* mainfolTpc = new TFolder("TPC", "TPC info");
    mainfolTpc->Add(cHitx);
    mainfolTpc->Add(cHity);
    mainfolTpc->Add(cHitxy);
    mainfolTpc->Add(cTpcCal[0]);
    mainfolTpc->Add(cTpcCal[1]);
    mainfolTpc->Add(cTpcCal[2]);
    mainfolTpc->Add(cTpcCal[3]);
    // mainfolTpc->Add(cTpcCal[3]);
    mainfolTpc->Add(cCalx);
    // mainfolTpc->Add(cCalx31);
    mainfolTpc->Add(cTransS2);
    mainfolTpc->Add(cTransS4);
    mainfolTpc->Add(cTrackS2);
    mainfolTpc->Add(cTrackS4);
    run->AddObject(mainfolTpc);

    // Register command to reset histograms
    run->GetHttpServer()->RegisterCommand("Reset_TPCs", Form("/Objects/%s/->Reset_TPC_Histo()", GetName()));

    return kSUCCESS;
}

void FrsTpcOnlineSpectra::Reset_TPC_Histo()
{
    LOG(INFO) << "FrsTpcOnlineSpectra::Reset_TPC_Histo";
    // Hit data
    for (Int_t i = 0; i < 4; i++) {
        fh_Tpc_hitx[i]->Reset();
        fh_Tpc_hity[i]->Reset();
        fh_Tpc_hitxy[i]->Reset();
        fh_tpc_deltax[i]->Reset();
    }
    fh_tr2->Reset();
    fh_ts2->Reset();
    fh_ts4->Reset();
    fh_tr4->Reset();
    // Cal data
    for (Int_t i = 0; i < 16; i++)
        fh_tpc_csum[i]->Reset();
}

void FrsTpcOnlineSpectra::Exec(Option_t* option)
{
    FairRootManager* mgr = FairRootManager::Instance();
    if (NULL == mgr)
        LOG(FATAL) << "FrsTpcOnlineSpectra::Exec FairRootManager not found";

    // Fill cal tpc data
    Int_t deltaX[10];
    if (fCalItemsTpc && fCalItemsTpc->GetEntriesFast()) {
        Int_t nHits = fCalItemsTpc->GetEntriesFast();
        // std::cout << nHits << std::endl;
        for (Int_t ihit = 0; ihit < nHits; ihit++) {
            R3BTpcCalData* hit = (R3BTpcCalData*)fCalItemsTpc->At(ihit);
            if (!hit)
                continue;
            if (hit->GetXYId()) {
                fh_tpc_csum[hit->GetDetectorId() * 4 + hit->GetSecId()]->Fill(hit->GetControlPar());
            } else {
                deltaX[hit->GetDetectorId() * 2 + hit->GetSecId()] = hit->GetControlPar();
            }
        }
        // DeltaX for TPCs: X1-X0
        fh_tpc_deltax[0]->Fill(deltaX[1] - deltaX[0]);
        fh_tpc_deltax[1]->Fill(deltaX[3] - deltaX[2]);
        fh_tpc_deltax[2]->Fill(deltaX[5] - deltaX[4]);
        fh_tpc_deltax[3]->Fill(deltaX[7] - deltaX[6]);
    }

    // Fill hit tpc data
    if (fHitItemsTpc && fHitItemsTpc->GetEntriesFast()) {
        Int_t nHits = fHitItemsTpc->GetEntriesFast();
        // std::cout << nHits << std::endl;
        TVector3 master[4];
        int detid[4];
        detid[0] = 0;
        detid[1] = 0;
        detid[2] = 0;
        detid[3] = 0;
        for (Int_t ihit = 0; ihit < nHits; ihit++) {
            R3BTpcHitData* hit = (R3BTpcHitData*)fHitItemsTpc->At(ihit);
            if (!hit)
                continue;
            fh_Tpc_hitx[hit->GetDetectorId()]->Fill(hit->GetX());
            fh_Tpc_hity[hit->GetDetectorId()]->Fill(hit->GetY());
            fh_Tpc_hitxy[hit->GetDetectorId()]->Fill(hit->GetX(), hit->GetY());
            master[hit->GetDetectorId()].SetXYZ(tpcpos[hit->GetDetectorId()], hit->GetX(), 0.);
            detid[hit->GetDetectorId()] = 1;
        }
        double zr = 0.;
        if (detid[0] == 1 && detid[1] == 1)
            fh_ts2->Fill(master[0].Y() + (master[1] - master[0]).Phi() * 2012., (master[1] - master[0]).Phi() * 1000.);
        if (detid[2] == 1 && detid[3] == 1)
            fh_ts4->Fill(master[2].Y() + (master[3] - master[2]).Phi() * 2349., (master[3] - master[2]).Phi() * 1000.);
        for (Int_t j = 0; j < 10; j++) {
            zr = gRandom->Uniform(0., 4050.);
            if (master[0].Y() > -100. && master[0].Y() < 100. && master[1].Y() > -100. && master[1].Y() < 100.
                && abs((master[1] - master[0]).Phi()) < 0.016 && detid[0] == 1 && detid[1] == 1)
                fh_tr2->Fill(zr, master[0].Y() + (master[1] - master[0]).Phi() * zr);
            if (master[2].Y() > -100. && master[2].Y() < 100. && master[3].Y() > -100. && master[3].Y() < 100.
                && abs((master[3] - master[2]).Phi()) < 0.016 && detid[2] == 1 && detid[3] == 1)
                fh_tr4->Fill(zr, master[2].Y() + (master[3] - master[2]).Phi() * zr);
        }
    }

    fNEvents += 1;
}

void FrsTpcOnlineSpectra::FinishEvent()
{
    if (fCalItemsTpc) {
        fCalItemsTpc->Clear();
    }
    if (fHitItemsTpc) {
        fHitItemsTpc->Clear();
    }
}

void FrsTpcOnlineSpectra::FinishTask()
{
    if (fCalItemsTpc) {
        cCalx->Write();
        for (Int_t i = 0; i < 4; i++) {
            cTpcCal[i]->Write();
        }
    }
    if (fHitItemsTpc) {
        cHitx->Write();
        cHity->Write();
        cHitxy->Write();
        // cCalx31->Write();
        cTransS2->Write();
        cTransS4->Write();
        cTrackS2->Write();
        cTrackS4->Write();
    }
}

ClassImp(FrsTpcOnlineSpectra)

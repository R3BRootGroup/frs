// ------------------------------------------------------------
// -----                FrsMWOnlineSpectra                -----
// -----    Created 16/11/19  by J.L. Rodriguez-Sanchez   -----
// -----           Fill MW  online histograms             -----
// ------------------------------------------------------------

/*
 * This task should fill histograms with FRS online data
 */

#include "FrsMWOnlineSpectra.h"
#include "R3BMwMappedData.h"
#include "R3BMwHitData.h"
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

FrsMWOnlineSpectra::FrsMWOnlineSpectra()
    : FairTask("FrsMWOnlineSpectra", 1)
    , fMapItemsMw(NULL)
    , fHitItemsMw(NULL)
    , fNameDet("MW")
    , fNEvents(0)
{
}

FrsMWOnlineSpectra::FrsMWOnlineSpectra(const TString& name, Int_t iVerbose, const TString& namedet)
    : FairTask(name, iVerbose)
    , fMapItemsMw(NULL)
    , fHitItemsMw(NULL)
    , fNameDet(namedet)
    , fNEvents(0)
{
}

FrsMWOnlineSpectra::~FrsMWOnlineSpectra()
{
    LOG(INFO) << "Frs" + fNameDet + "OnlineSpectra::Delete instance";
    if (fMapItemsMw)
        delete fMapItemsMw;
    if (fHitItemsMw)
        delete fHitItemsMw;
}

InitStatus FrsMWOnlineSpectra::Init()
{

    LOG(INFO) << "Frs" + fNameDet + "OnlineSpectra::Init ";

    // try to get a handle on the EventHeader. EventHeader may not be
    // present though and hence may be null. Take care when using.

    FairRootManager* mgr = FairRootManager::Instance();
    if (NULL == mgr)
        LOG(FATAL) << "Frs" + fNameDet + "OnlineSpectra::Init FairRootManager not found";
    // header = (R3BEventHeader*)mgr->GetObject("R3BEventHeader");

    FairRunOnline* run = FairRunOnline::Instance();
    run->GetHttpServer()->Register("", this);

    // get access to mapped data of the MW detector
    fMapItemsMw = (TClonesArray*)mgr->GetObject(fNameDet + "MappedData");
    if (!fMapItemsMw)
    {
        return kFATAL;
    }

    // get access to hit data of the MW detector
    fHitItemsMw = (TClonesArray*)mgr->GetObject("MwHitData");
    if (!fHitItemsMw)
    {
        LOG(WARNING) << "FrsMWOnlineSpectra: Not found object MwHitData";
    }

    // Create histograms for detectors
    TString Name1;
    TString Name2;

    // MW: Mapped data
    Name1 =  fNameDet + "_A";
    Name2 = fNameDet + ": Anode (channels)";
    fh1_mw_a = new TH1F(Name1, Name2, 1000, 1,4096);
    Name1 =  fNameDet + "_XL";
    Name2 = fNameDet + ": X-left (channels)";
    fh1_mw_xr = new TH1F(Name1, Name2, 1000, 1,4096);
    Name1 =  fNameDet + "_XR";
    Name2 = fNameDet + ": X-right (channels)";
    fh1_mw_xl = new TH1F(Name1, Name2, 1000, 1,4096);
    Name1 =  fNameDet + "_YU";
    Name2 = fNameDet + ": Y-up (channels)";
    fh1_mw_yu = new TH1F(Name1, Name2, 1000, 1,4096);
    Name1 =  fNameDet + "_YD";
    Name2 = fNameDet + ": Y-down (channels)";
    fh1_mw_yd = new TH1F(Name1, Name2, 1000, 1,4096);
    Name1 =  fNameDet + "_XSUM";
    Name2 = fNameDet + ": Sum XL+XR (channels)";
    fh1_mw_xsum = new TH1F(Name1, Name2, 800,5,8005);
    Name1 =  fNameDet + "_YSUM";
    Name2 = fNameDet + ": Sum YU+YD (channels)";
    fh1_mw_ysum = new TH1F(Name1, Name2, 800,5,8005);

    // MW: Hit data
    Name1 =  fNameDet + "_X";
    Name2 = fNameDet + ": X [mm]";
    fh1_mw_x = new TH1F(Name1, Name2, 201,-100.5,+100.5);
    Name1 =  fNameDet + "_Y";
    Name2 = fNameDet + ": Y [mm]";
    fh1_mw_y = new TH1F(Name1, Name2, 201,-100.5,+100.5);
    Name1 =  fNameDet + "_XY";
    Name2 = fNameDet + ": X vs Y in [mm]";
    fh2_mw_xy = new TH2F(Name1, Name2, 201,-100.5,+100.5, 201,-100.5,+100.5);


    // MAIN FOLDER
    TFolder* mainfolMW = new TFolder(fNameDet, fNameDet + " info");
    mainfolMW->Add(fh1_mw_a);
    mainfolMW->Add(fh1_mw_xr);
    mainfolMW->Add(fh1_mw_xl);
    mainfolMW->Add(fh1_mw_yu);
    mainfolMW->Add(fh1_mw_yd);
    mainfolMW->Add(fh1_mw_xsum);
    mainfolMW->Add(fh1_mw_ysum);
    mainfolMW->Add(fh1_mw_x);
    mainfolMW->Add(fh1_mw_y);
    mainfolMW->Add(fh2_mw_xy);
    run->AddObject(mainfolMW);

    // Register command to reset histograms
    //run->GetHttpServer()->RegisterCommand("Reset_" + fNameDet + "_HIST",
    //                                      Form("/Objects/%s/->Reset_Histo()", GetName()));

    return kSUCCESS;
}

void FrsMWOnlineSpectra::Reset_Histo()
{
    LOG(INFO) << "Frs" + fNameDet + "OnlineSpectra::Reset_Histo";
    // Map data
    fh1_mw_a->Reset();
    fh1_mw_xr->Reset();
    fh1_mw_xl->Reset();
    fh1_mw_yu->Reset();
    fh1_mw_yd->Reset();
    fh1_mw_xsum->Reset();
    fh1_mw_ysum->Reset();
    // Cal data
    fh1_mw_x->Reset();
    fh1_mw_y->Reset();
    fh2_mw_xy->Reset();
}

void FrsMWOnlineSpectra::Exec(Option_t* option)
{
    FairRootManager* mgr = FairRootManager::Instance();
    if (NULL == mgr)
        LOG(FATAL) << "Frs" + fNameDet + "OnlineSpectra::Exec FairRootManager not found";

    // Fill Mapped data
    if (fMapItemsMw && fMapItemsMw->GetEntriesFast())
    {
        Int_t nHits = fMapItemsMw->GetEntriesFast();
        Int_t an=0,xl=0,xr=0,yu=0,yd=0;
        for (Int_t ihit = 0; ihit < nHits; ihit++)
        {
            R3BMwMappedData* hit = (R3BMwMappedData*)fMapItemsMw->At(ihit);
            if (!hit)
                continue;
            an=hit->GetAn();
            fh1_mw_a->Fill(an);
            xr=hit->GetXr();
            fh1_mw_xr->Fill(xr);
            xl=hit->GetXl();
            fh1_mw_xl->Fill(xl);
            yu=hit->GetYu();
            fh1_mw_yu->Fill(yu);
            yd=hit->GetYd();
            fh1_mw_yd->Fill(yd);
            // Control sum for x and y
            fh1_mw_xsum->Fill(1000 + (xl - an) + (xr - an));
            fh1_mw_ysum->Fill(1000 + (yu - an) + (yd - an));
        }

    }

    // Fill hit mw data
    if (fHitItemsMw && fHitItemsMw->GetEntriesFast())
    {
        Int_t nHits = fHitItemsMw->GetEntriesFast();
        // std::cout << nHits << std::endl;
        for (Int_t ihit = 0; ihit < nHits; ihit++)
        {
            R3BMwHitData* hit = (R3BMwHitData*)fHitItemsMw->At(ihit);
            if (!hit)
                continue;
            if( TString(fDetectorNames[hit->GetDetId()]).CompareTo(fNameDet)==0 ){
             // std::cout << hit->GetDetId() <<" " <<hit->GetX() << std::endl;
             //std::cout << fDetectorNames[hit->GetDetId()] <<" " <<fNameDet << std::endl;
             fh1_mw_x->Fill(hit->GetX());
             fh1_mw_y->Fill(hit->GetY());
             fh2_mw_xy->Fill(hit->GetX(), hit->GetY());
            }
        }
    }

    fNEvents += 1;
}

void FrsMWOnlineSpectra::FinishEvent()
{
    if (fMapItemsMw)
    {
        fMapItemsMw->Clear();
    }
}

void FrsMWOnlineSpectra::FinishTask()
{
    if (fMapItemsMw)
    {
        fh1_mw_a->Write();
        fh1_mw_xr->Write();
        fh1_mw_xl->Write();
        fh1_mw_yu->Write();
        fh1_mw_yd->Write();
        fh1_mw_xsum->Write();
        fh1_mw_ysum->Write();
        fh1_mw_x->Write();
        fh1_mw_y->Write();
        fh2_mw_xy->Write();
    }

}

ClassImp(FrsMWOnlineSpectra)

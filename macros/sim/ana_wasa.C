//-------------------------------------------------------------------------
//    joseluis.rodriguez.sanchez@usc.es
//    Universidad de Santiago de Compostela & GSI
//-------------------------------------------------------------------------
//
//	Check resutls
//
//	General Usage:
//
//      root -l ana_wasa.C
//
//--------------------------------------------------------------------------

#include "TCanvas.h"
#include "TH1F.h"
#include "TH2F.h"

#include "TClonesArray.h"
#include "TMath.h"
#include "TRandom.h"
#include <array>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>

void ana_wasa() {

  TStopwatch timer;
  timer.Start();

  // ROOT ENVIRONMENT
  gROOT->SetStyle("Plain");
  gStyle->SetOptStat(1);
  gStyle->SetOptFit(1111);

  // INPUT FILE
  char inputfile[255] = "sim.root";
  TFile *file1 = TFile::Open(inputfile);
  // READING TREE
  TTree *tree = (TTree *)file1->Get("evt");

  // ENTRIES  -------------------------------------------------------------------------
  Float_t nevents = tree->GetEntries();
  std::cout << "Events: " << nevents << std::endl;

  // MCTrack data   ----------------------------------------------------------------
  TClonesArray *trackDataCA = new TClonesArray("R3BMCTrack", 10);
  TBranch *branchTrackData = tree->GetBranch("MCTrack");
  branchTrackData->SetAddress(&trackDataCA);

  // ToF Barrel data   ----------------------------------------------------------------
  TClonesArray *tofDataCA = new TClonesArray("WASATofPoint", 10);
  TBranch *branchTofData = tree->GetBranch("WasaTofPoint");
  branchTofData->SetAddress(&tofDataCA);

  // MDC data   ----------------------------------------------------------------
  TClonesArray *mdcDataCA = new TClonesArray("WASAMdcPoint", 10);
  TBranch *branchMdcData = tree->GetBranch("MdcPoint");
  branchMdcData->SetAddress(&mdcDataCA);

  // Histograms         ---------------------------------------------------------------
  TH2F *fh2_P_Energy = new TH2F("P:Energy_loss", "", 600, -2, 2, 600, 0.0001, 0.045);
  TH2F *fh2_P_ang = new TH2F("P:ang", "", 176*3, 2, 178, 300*4., 0., 3.);
  TVector3 mom, momt;

  Double_t eelos=0.09;
  Double_t emom=0.015;

  // LOOP IN THE EVENTS ---------------------------------------------------------------
  for (Int_t i = 0; i < nevents; i++) {
    if (i % 100000 == 0)
      std::cout << "Event:" << i << std::endl;

    trackDataCA->Clear();
    tofDataCA->Clear();
    mdcDataCA->Clear();

    tree->GetEntry(i);

    if (tofDataCA->GetEntries() > 0 && mdcDataCA->GetEntries() > 3) {

      R3BMCTrack **TrackData = new R3BMCTrack *[trackDataCA->GetEntries()];

      Int_t nHits = tofDataCA->GetEntries();
      WASATofPoint **Data = new WASATofPoint *[nHits];
      int track=0, ID=0;
/*      bool ok=false;
      for (Int_t j = 0; j < nHits; j++) {
        Data[j] = (WASATofPoint *)(tofDataCA->At(j));
        track = Data[j]->GetTrackID();
        TrackData[track] = (R3BMCTrack*)trackDataCA->At(track);
        //ID= (int)TrackData[track]->GetPdgCode()/10000;
        //if(ID==100055)ok=true;
          //cout <<Data[j]->GetPid() <<" "<< ID << endl;
        
      }

      track=0; ID=0;
      if(ok)
*/
      for (Int_t j = 0; j < nHits; j++) {
        Data[j] = (WASATofPoint *)(tofDataCA->At(j));
        track = Data[j]->GetTrackID();
        TrackData[track] = (R3BMCTrack*)trackDataCA->At(track);
        ID = TrackData[track]->GetMotherId();
        momt.SetXYZ(TrackData[track]->GetPx(),TrackData[track]->GetPy(),TrackData[track]->GetPz());
       if(ID==-1){
        if((Data[j]->GetPid()==211 || Data[j]->GetPid()==2212)){
          Data[j]->Momentum(mom);
          if(Data[j]->GetPid()==211 && mom.Mag()>0.05)fh2_P_ang->Fill(momt.Theta()*TMath::RadToDeg()+gRandom->Gaus(0.,0.5),mom.Mag()+gRandom->Gaus(0.,mom.Mag()*emom));
          //cout <<Data[j]->GetPid() <<" "<< mom.Mag()<<" "<< TrackData[track]->GetPdgCode() << endl;
          if(Data[j]->GetPid()==2212 && mom.Mag()>0.233)fh2_P_Energy->Fill(mom.Mag(),Data[j]->GetEnergyLoss()+gRandom->Gaus(0.,Data[j]->GetEnergyLoss()*eelos));
          if(Data[j]->GetPid()==211 && mom.Mag()>0.05)fh2_P_Energy->Fill(mom.Mag(),Data[j]->GetEnergyLoss()+gRandom->Gaus(0.,Data[j]->GetEnergyLoss()*eelos));
          if(Data[j]->GetPid()==211 && mom.Mag()>0.05)fh2_P_Energy->Fill(-mom.Mag(),Data[j]->GetEnergyLoss()+gRandom->Gaus(0.,Data[j]->GetEnergyLoss()*eelos));
        }else if(Data[j]->GetPid()==-211 && mom.Mag()>0.05){
          //cout <<Data[j]->GetPid() <<" "<< mom.Mag() << endl;
          Data[j]->Momentum(mom);
          fh2_P_ang->Fill(momt.Theta()*TMath::RadToDeg()+gRandom->Gaus(0.,0.5),mom.Mag()+gRandom->Gaus(0.,mom.Mag()*emom));
          fh2_P_Energy->Fill(mom.Mag()+gRandom->Gaus(0.,mom.Mag()*emom),Data[j]->GetEnergyLoss()+gRandom->Gaus(0.,Data[j]->GetEnergyLoss()*eelos));
          fh2_P_Energy->Fill(-mom.Mag()+gRandom->Gaus(0.,mom.Mag()*emom),Data[j]->GetEnergyLoss()+gRandom->Gaus(0.,Data[j]->GetEnergyLoss()*eelos));
        }
       }
      }
      if (TrackData)
        delete[] TrackData;
      if (Data)
        delete[] Data;

    }

  }

  TCanvas *c0 = new TCanvas("c0");
  fh2_P_Energy->Draw("col");

  TCanvas *c1 = new TCanvas("c1");
  fh2_P_ang->Draw("col");

  // End  -----------------------------------------------------------------------------
  timer.Stop();
  Double_t rtime = timer.RealTime();
  Double_t ctime = timer.CpuTime();
  Float_t cpuUsage = ctime / rtime;
  cout << "CPU used: " << cpuUsage << "\n" << endl;
  cout << "Real time " << rtime/60. << " min, CPU time " << ctime/60. << "min" << endl;
  cout << "Macro finished successfully." << endl;
}

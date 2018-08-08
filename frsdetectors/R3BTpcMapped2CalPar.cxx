// -------------------------------------------------------------------------
// -----         R3BTpcMapped2CalPar source file                       -----
// -----             Created 29/07/18  by J.L. Rodriguez-Sanchez       -----
// -------------------------------------------------------------------------
#include "R3BTpcMappedData.h"
#include "R3BTpcMapped2CalPar.h"
#include "R3BEventHeader.h"
#include "R3BTpcCalPar.h"

#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRuntimeDb.h"
#include "FairLogger.h"
#include "TGeoManager.h"

#include "TClonesArray.h"
#include "TObjArray.h"
#include "TRandom.h"
#include "TSpectrum.h"
#include "TH1F.h"
#include "TF1.h"
#include "TGraph.h"
#include "TMath.h"
#include "TVector3.h"
#include "TGeoMatrix.h"

#include <iostream>
#include <stdlib.h>

using namespace std;

//R3BTpcMapped2CalPar: Default Constructor --------------------------
R3BTpcMapped2CalPar::R3BTpcMapped2CalPar() :
  FairTask("TPC calibration",1),
  fTpc_Par(NULL),
  fTpcMappedDataCA(NULL),
  fNumDets(6),
  fNumAnodesX(2),
  fNumAnodesY(4),
  fMinStatistics(0),
  fMapHistos_left(0),
  fMapHistos_right(0),
  fMapHistos_bins(0),
  fDeltaX(0),
  fDeltaY(0),
  fOutputFile(NULL) {
  fLim_Csum_Max = new TArrayF;
  fLim_Csum_Min = new TArrayF;
  fLim_Csum_Max->Set(fNumDets*4);//4lines*Nbdetectors
  fLim_Csum_Min->Set(fNumDets*4);
  for(Int_t i=0;i<fNumDets*4;i++){
     fLim_Csum_Max->AddAt(2000,i);
     fLim_Csum_Min->AddAt(1300,i);
  }
  
}

//R3BTpcMapped2CalPar: Standard Constructor --------------------------
R3BTpcMapped2CalPar::R3BTpcMapped2CalPar(const char* name, Int_t iVerbose) :
  FairTask(name, iVerbose),
  fTpc_Par(NULL),
  fTpcMappedDataCA(NULL),
  fNumDets(6),
  fNumAnodesX(2),
  fNumAnodesY(4),
  fMinStatistics(0),
  fMapHistos_left(0),
  fMapHistos_right(0),
  fMapHistos_bins(0),
  fDeltaX(0),
  fDeltaY(0),
  fOutputFile(NULL) {
  fLim_Csum_Max = new TArrayF;
  fLim_Csum_Min = new TArrayF;
  fLim_Csum_Max->Set(fNumDets*4);//4lines*Nbdetectors
  fLim_Csum_Min->Set(fNumDets*4);
  for(Int_t i=0;i<fNumDets*4;i++){
     fLim_Csum_Max->AddAt(2000,i);
     fLim_Csum_Min->AddAt(1300,i);
  }
  
}

//R3BTpcMapped2CalPar: Destructor ----------------------------------------
R3BTpcMapped2CalPar::~R3BTpcMapped2CalPar() {
  
}

// -----   Public method Init   --------------------------------------------
InitStatus R3BTpcMapped2CalPar::Init() {

  LOG(INFO) << "R3BTpcMapped2CalPar: Init" << FairLogger::endl;

  char name[100];

  fh_Map_csum = new TH1F*[fNumAnodesY*fNumDets];
  for(Int_t d=0;d<fNumDets;d++){
   for(Int_t i=0;i<fNumAnodesY;i++){
    sprintf(name,"fh_Map_csum_%i_%i",d,i);
    fh_Map_csum[fNumAnodesY*d+i] = new TH1F(name,name,fMapHistos_bins,fMapHistos_left,fMapHistos_right);
   }
  }
  fh_Map_dt_y = new TH1F*[fNumAnodesY*fNumDets];
  for(Int_t i=0;i<fNumAnodesY*fNumDets;i++){
    sprintf(name,"fh_Map_dt_y_%i",i+1);
    fh_Map_dt_y[i] = new TH1F(name,name,fMapHistos_bins,fMapHistos_left,fMapHistos_right);
  }
  fh_Map_dt_x = new TH1F*[fNumAnodesX*fNumDets];
  for(Int_t i=0;i<fNumAnodesX*fNumDets;i++){
    sprintf(name,"fh_Map_dt_x_%i",i+1);
    fh_Map_dt_x[i] = new TH1F(name,name,fMapHistos_bins,fMapHistos_left,fMapHistos_right);
  }

  FairRootManager* rootManager = FairRootManager::Instance();
  if (!rootManager) { return kFATAL;}
  
  fTpcMappedDataCA = (TClonesArray*)rootManager->GetObject("TpcMappedData");
  if (!fTpcMappedDataCA) { return kFATAL;}
  
  FairRuntimeDb* rtdb = FairRuntimeDb::instance();
  if (!rtdb) { return kFATAL;}
  
  fTpc_Par=(R3BTpcCalPar*)rtdb->getContainer("tpcCalPar");
  if (!fTpc_Par) {
    LOG(ERROR)<<"R3BTpcMapped2CalPar::Init() Couldn't get handle on tpcCalPar container"<<FairLogger::endl;
    return kFATAL;
  }
  
  return kSUCCESS;
}

// -----   Public method ReInit   --------------------------------------------
InitStatus R3BTpcMapped2CalPar::ReInit() {
  
  return kSUCCESS;
}

// -----   Public method Exec   --------------------------------------------
void R3BTpcMapped2CalPar::Exec(Option_t* opt) {
  
  Int_t nHits = fTpcMappedDataCA->GetEntries();
  if(!nHits) return;

  R3BTpcMappedData* MapHit;
  Int_t detId;
  TArrayI* fTpcdt;
  TArrayI* fTpclt;
  TArrayI* fTpcrt;
  
  for(Int_t i = 0; i < nHits; i++) {
    MapHit = (R3BTpcMappedData*)(fTpcMappedDataCA->At(i));
    detId = MapHit->GetDetectorId();
    fTpcdt = new TArrayI(*(MapHit->GetTpcdt()));
    fTpcrt = new TArrayI(*(MapHit->GetTpcrt()));
    fTpclt = new TArrayI(*(MapHit->GetTpclt()));
    
   //std::cout << fTpcdt->GetAt(0) <<" "<< fTpcdt->GetAt(1)<<" "<< fTpcdt->GetAt(2)<<" "<< fTpcdt->GetAt(3) << std::endl;
   //std::cout << fTpclt->GetAt(0) <<" "<< fTpclt->GetAt(1) << std::endl;
   //std::cout << fTpcrt->GetAt(0) <<" "<< fTpcrt->GetAt(1) << std::endl;

    //Init control sum for TPCs
    for (int j=0;j<fNumAnodesY;j++){
     tpc_csum[j] =0.;
     b_tpc_csum[j] = kFALSE;
    }

    for(int j=0;j<fNumAnodesY;j++){
      // calculate control sums
      if(j<2){ 
          tpc_csum[j] = abs( fTpclt->GetAt(0)+fTpcrt->GetAt(0) -2*fTpcdt->GetAt(j));
      }else{ 
          tpc_csum[j] = abs( fTpclt->GetAt(1)+fTpcrt->GetAt(1) -2*fTpcdt->GetAt(j));
      }
      fh_Map_csum[fNumAnodesY*detId+j]->Fill(tpc_csum[j]);

      if(tpc_csum[j]>fLim_Csum_Min->GetAt(detId*4+j) && tpc_csum[j]<fLim_Csum_Max->GetAt(detId*4+j))
         b_tpc_csum[j] = kTRUE;


      if((fTpclt->GetAt(0)==0 && fTpcrt->GetAt(0)==0 && j<2) || 
         (fTpclt->GetAt(1)==0 && fTpcrt->GetAt(1)==0 && j>1)){
        b_tpc_csum[j]=kFALSE;
      }
      
      //if(fTpclt->GetAt(1)==0 && fTpcrt->GetAt(1)==0 && j>1)
      	//		{b_tpc_csum[j]=kFALSE;} 

      if (b_tpc_csum[j]){
         fh_Map_dt_y[j+fNumAnodesY*detId]->Fill(fTpcdt->GetAt(j));
      }

    }//j<4

    if (b_tpc_csum[0] || b_tpc_csum[1]){
      fh_Map_dt_x[fNumAnodesX*detId]->Fill(fTpclt->GetAt(0)-fTpcrt->GetAt(0));
    }
    if (b_tpc_csum[2] || b_tpc_csum[3]){
      fh_Map_dt_x[1+fNumAnodesX*detId]->Fill(fTpclt->GetAt(1)-fTpcrt->GetAt(1));
    }
  }

}

// ---- Public method Reset   --------------------------------------------------
void R3BTpcMapped2CalPar::Reset() {
  
}

void R3BTpcMapped2CalPar::FinishEvent() {
}

// ---- Public method Finish   --------------------------------------------------
void R3BTpcMapped2CalPar::FinishTask() {
  //Set Csum parameters -------------------------------
  fTpc_Par->GetTpcCsumMaxParams()->Set(4*fNumDets);
  fTpc_Par->GetTpcCsumMinParams()->Set(4*fNumDets);
  for(Int_t d=0;d<fNumDets;d++){
   for(Int_t j=0;j<4;j++){
    fTpc_Par->SetTpcCsumMaxParams(fLim_Csum_Max->GetAt(d*4+j),d*4+j);
    fTpc_Par->SetTpcCsumMinParams(fLim_Csum_Min->GetAt(d*4+j),d*4+j);
   }
  }
  fTpc_Par->setChanged();

  //Set Cal parameters --------------------------------
  SearchCalParXY();

  //Set histograms in the root file
  for(Int_t i=0;i<fNumAnodesY*fNumDets;i++)
  fh_Map_csum[i]->Write();
  for(Int_t i=0;i<fNumAnodesY*fNumDets;i++)
  fh_Map_dt_y[i]->Write();
  for(Int_t i=0;i<fNumAnodesX*fNumDets;i++)
  fh_Map_dt_x[i]->Write();

  //fTpc_Par->printParams();

}

//------------------
void R3BTpcMapped2CalPar::SearchCalParXY(){

  LOG(INFO) << "R3BTpcMapped2CalPar: Search calibration parameters" << FairLogger::endl;

  Int_t numPars =2;// by default number of parameters=2
  fTpc_Par->SetNumDets(fNumDets);

  Int_t fNumAnodesTotal=fNumAnodesX+fNumAnodesY;
  fTpc_Par->SetNumDT(fNumAnodesTotal);
  fTpc_Par->SetNumParametersFit(numPars);
  fTpc_Par->GetTpcCalParams()->Set(numPars*fNumAnodesTotal*fNumDets);


  int fNumPeaks=5;

  for(Int_t d=0;d<fNumDets;d++){

   for (Int_t i=0;i<fNumAnodesTotal;i++){
    
    TSpectrum *ss= new TSpectrum(fNumPeaks); 
    Int_t nfound=0;

    // Fit of DT in the Y direction
    if(i<fNumAnodesY){
    if (fh_Map_dt_y[i+d*fNumAnodesY]->GetEntries()>fMinStatistics){
      //Sigma=1 is better than other values!
      nfound = ss->Search(fh_Map_dt_y[i+d*fNumAnodesY],1,"goff",0.000001);

      //Int_t idx[nfound];

      Double_t *xpeaks = ss->GetPositionX();
     // TMath::Sort(nfound, xpeaks, idx, kTRUE);

      //Calibrated Spectrum
      Double_t X[nfound];
      Double_t Y[nfound];

      if(nfound<2)
      LOG(ERROR)<<"R3BTpccMapped2CalPar::SearchY() Couldn't get the sufficient parameters:"<<nfound<<"<2"<<FairLogger::endl;
      

     // LOG(INFO)<<"nfound "<<nfound<<FairLogger::endl;

      for (Int_t j=0;j<nfound;j++){
	X[j]=xpeaks[j];
	Y[j]=fDeltaY*j-fDeltaY;
        //std::cout << X[j] << " " << Y[j] << std::endl;
      }


      TF1 * f1 = new TF1 ("f1", "[0]+[1]*x", fMapHistos_left, fMapHistos_right);
      TGraph* graph = new TGraph (nfound, X, Y);
      graph->Fit("f1","QR");//Quiet mode (minimum printing)

      if(nfound>1){
      for(Int_t h=0; h<numPars;h++)
	fTpc_Par->SetTpcCalParams(f1->GetParameter(h),numPars*i+h+d*numPars*fNumAnodesTotal);
      }else{
	fTpc_Par->SetTpcCalParams(0,numPars*i+d*numPars*fNumAnodesTotal);
	fTpc_Par->SetTpcCalParams(1,numPars*i+d*numPars*fNumAnodesTotal+1);
        LOG(INFO)<<"R3BTpccMapped2CalPar::SearchY() default parameters: a0=0 and a1=1"<<FairLogger::endl;
     }


    }else {
      fTpc_Par->SetTpcCalParams(0,numPars*i+d*numPars*fNumAnodesTotal);//dead anode
      fTpc_Par->SetTpcCalParams(0,numPars*i+d*numPars*fNumAnodesTotal+1);
      LOG(WARNING)<<"R3BTpcMapped2CalPar: Histogram NO Fitted, detector: " << d+1 << ", anode: "<< i+1 <<FairLogger::endl;
    }
    }else{//if DT_Y
     
    // Fit of DT in the X direction
    if (fh_Map_dt_x[i-4+d*fNumAnodesX]->GetEntries()>fMinStatistics){
      //Sigma=1 is better than other values!
      nfound = ss->Search(fh_Map_dt_x[i-4+d*fNumAnodesX],1,"goff",0.00001);

      Int_t idx[nfound];

      Double_t *xpeaks = ss->GetPositionX();
      TMath::Sort(nfound, xpeaks, idx, kTRUE);

      //Calibrated Spectrum
      Double_t X[nfound];
      Double_t Y[nfound];

      if(nfound<2)
      LOG(ERROR)<<"R3BTpccMapped2CalPar::SearchX() Couldn't get the sufficient parameters:"<<nfound<<"<2"<<FairLogger::endl;
      
      for (Int_t j=0;j<nfound;j++){
	X[j]=xpeaks[idx[j]];
	Y[j]=fDeltaX*j-fDeltaX;
        //std::cout << X[j] << " " << Y[j] << std::endl;
      }



      TF1 * f1 = new TF1 ("f1", "[0]+[1]*x", fMapHistos_left, fMapHistos_right);
      TGraph* graph = new TGraph (nfound, X, Y);
      graph->Fit("f1","Q");//Quiet mode (minimum printing)



      if(nfound>1){
      for(Int_t h=0; h<numPars;h++)
	fTpc_Par->SetTpcCalParams(f1->GetParameter(h),numPars*i+h+d*numPars*fNumAnodesTotal);
      }else{
	fTpc_Par->SetTpcCalParams(0,numPars*i+d*numPars*fNumAnodesTotal);
	fTpc_Par->SetTpcCalParams(1,numPars*i+d*numPars*fNumAnodesTotal+1);
        LOG(INFO)<<"R3BTpccMapped2CalPar::SearchX() default parameters: a0=0 and a1=1"<<FairLogger::endl;
     }

    }else {

      fTpc_Par->SetTpcCalParams(0,numPars*i+d*numPars*fNumAnodesTotal);//dead anode

      fTpc_Par->SetTpcCalParams(0,numPars*i+d*numPars*fNumAnodesTotal+1);

      LOG(WARNING)<<"R3BTpcMapped2CalPar: Histogram NO Fitted, detector: " << d+1 << ", anode: "<< i+1 <<FairLogger::endl;
    }

    }

   }
  }
  
  fTpc_Par->setChanged();
  return;

}

ClassImp(R3BTpcMapped2CalPar)

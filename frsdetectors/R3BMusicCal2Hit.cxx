// ----------------------------------------------------------------------
// -----         R3BMusicCal2Hit source file                        -----
// -----             Created 22/07/18  by J.L. Rodriguez-Sanchez    -----
// ----------------------------------------------------------------------

//ROOT headers
#include "TClonesArray.h"
#include "TMath.h"
#include "TRandom.h"

//Fair headers
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRuntimeDb.h"
#include "FairLogger.h"

#include <iomanip>

//Music headers
#include "R3BMusicHitData.h"
#include "R3BMusicCalData.h"
#include "R3BMusicCal2Hit.h"
#include "R3BMusicHitPar.h"

//R3BMusicCal2Hit: Default Constructor --------------------------
R3BMusicCal2Hit::R3BMusicCal2Hit() : 
  FairTask("R3B Music Calibrator",1),
  NumDets(0),
  NumAnodes(8),
  NumParams(0),
  MaxSigma(200),
  CalParams(NULL),
  fCal_Par(NULL),
  fMusicHitDataCA(NULL),
  fMusicCalDataCA(NULL),
  fOnline(kFALSE)
{
}

//R3BMusicCal2HitPar: Standard Constructor --------------------------
R3BMusicCal2Hit::R3BMusicCal2Hit(const char* name, Int_t iVerbose) :
  FairTask(name, iVerbose),
  NumDets(0),
  NumAnodes(8),
  NumParams(0),
  MaxSigma(200),
  CalParams(NULL),
  fCal_Par(NULL),
  fMusicHitDataCA(NULL),
  fMusicCalDataCA(NULL),
  fOnline(kFALSE)
{  
}

//Virtual R3BMusicCal2Hit: Destructor
R3BMusicCal2Hit::~R3BMusicCal2Hit()
{
  LOG(INFO) << "R3BMusicCal2Hit: Delete instance" ;
  if(fMusicHitDataCA) delete fMusicHitDataCA;
  if(fMusicCalDataCA) delete fMusicCalDataCA;
}


void R3BMusicCal2Hit::SetParContainers() {
  
  //Parameter Container
  //Reading musicCalPar from FairRuntimeDb
  FairRuntimeDb* rtdb = FairRuntimeDb::instance();
  if (!rtdb) { 
    LOG(ERROR)<<"FairRuntimeDb not opened!";
  }
  
  fCal_Par=(R3BMusicHitPar*)rtdb->getContainer("musicHitPar");
  if (!fCal_Par) {
    LOG(ERROR)<<"R3BMusicCal2HitPar::Init() Couldn't get handle on musicCalPar container";
  }
  else{
    LOG(INFO)<<"R3BMusicCal2HitPar:: musicCalPar container open";
  }
}


void R3BMusicCal2Hit::SetParameter(){
  
  //--- Parameter Container ---
  NumDets=fCal_Par->GetNumDets();//Number of Detectors
  NumParams=fCal_Par->GetNumParametersFit();//Number of Parameters

  LOG(INFO)<<"R3BMusicCal2Hit: Nb detectors: "<< NumDets ;
  LOG(INFO)<<"R3BMusicCal2Hit: Nb parameters from pedestal fit: "<< NumParams ;
  
  CalParams= new TArrayF();
  Int_t array_size = NumDets*NumParams;
  CalParams->Set(array_size);	
  CalParams=fCal_Par->GetDetectorHitParams();//Array with the Cal parameters

  //Parameters detector
  for(Int_t d = 0; d < NumDets; d++){
  LOG(INFO)<<"R3BMusicCal2Hit Nb detector: " <<d+1<< " Params "<< CalParams->GetAt(d*NumParams) <<" : "<< CalParams->GetAt(d*NumParams+1) ;
  }
}

// -----   Public method Init   --------------------------------------------
InitStatus R3BMusicCal2Hit::Init()
{
  LOG(INFO) << "R3BMusicCal2Hit: Init" ;

  //INPUT DATA
  FairRootManager* rootManager = FairRootManager::Instance();
  if (!rootManager) { return kFATAL;}
  
  fMusicCalDataCA = (TClonesArray*)rootManager->GetObject("MusicCalData");
  if (!fMusicCalDataCA) { return kFATAL;}
   
  //OUTPUT DATA
  fMusicHitDataCA = new TClonesArray("R3BMusicHitData",10);
  if(!fOnline){
  rootManager->Register("MusicHitData", "MUSIC Hit", fMusicHitDataCA, kTRUE);
  }else{
  rootManager->Register("MusicHitData", "MUSIC Hit", fMusicHitDataCA, kFALSE);
  }  
  
  SetParameter();
  return kSUCCESS;
}

// -----   Public method ReInit   ----------------------------------------------
InitStatus R3BMusicCal2Hit::ReInit()
{
  SetParContainers();
  return kSUCCESS;
}

// -----   Public method Execution   --------------------------------------------
void R3BMusicCal2Hit::Exec(Option_t* option)
{
  //Reset entries in output arrays, local arrays
  Reset();
  
  if (!fCal_Par) {
    LOG(ERROR)<<"NO Container Parameter!!";
  }  
 
  Int_t nHits = fMusicCalDataCA->GetEntries();
  if(!nHits) return;
  
  //R3BMusicCalData* CalDat;
  R3BMusicCalData** CalDat = new R3BMusicCalData*[nHits];

  Int_t detId, anodeId;
  Double_t energyperanode[5][8];//max 5 detectors and 8 anodes
  Int_t nbdet=0;

  for(Int_t i = 0; i < 5; i++)
  for(Int_t j = 0; j < 8; j++)energyperanode[i][j]=0;
  
  for(Int_t i = 0; i < nHits; i++) {
    CalDat[i] = (R3BMusicCalData*)(fMusicCalDataCA->At(i));
    detId = CalDat[i]->GetDetectorId();
    anodeId = CalDat[i]->GetAnodeId();
    
    energyperanode[detId][anodeId] = CalDat[i]->GetEnergy();
    nbdet=detId;
  }

  Double_t a0,a1;

  // calculate truncated dE from 8 anodes, Munich MUSIC 
  for(Int_t i = 0; i <= NumDets; i++) {
    
     Float_t r1 = sqrt(energyperanode[i][0]*energyperanode[i][1]);
     Float_t r2 = sqrt(energyperanode[i][2]*energyperanode[i][3]);
     Float_t r3 = sqrt(energyperanode[i][4]*energyperanode[i][5]);
     Float_t r4 = sqrt(energyperanode[i][6]*energyperanode[i][7]);

     if ( (r1 > 0) && (r2 > 0) && (r3 > 0) && (r4 > 0) ) {
      a0=CalParams->GetAt(i*NumParams);
      a1=CalParams->GetAt(i*NumParams+1);
      AddHitData(i,a0 + a1*sqrt(sqrt( sqrt( r1 * r2 ) * sqrt( r3 * r4 ) )));
     }  
  }


  if(CalDat) delete CalDat;
  return;
}

// -----   Protected method Finish   --------------------------------------------
void R3BMusicCal2Hit::Finish()
{
  
}

// -----   Public method Reset   ------------------------------------------------
void R3BMusicCal2Hit::Reset()
{
  LOG(DEBUG) << "Clearing MusicHitData Structure" ;
  if(fMusicHitDataCA)fMusicHitDataCA->Clear();
}


// -----   Private method AddHitData  --------------------------------------------
R3BMusicHitData* R3BMusicCal2Hit::AddHitData(Int_t detid, Double_t charge)
{
  //It fills the R3BMusicHitData
  TClonesArray& clref = *fMusicHitDataCA;
  Int_t size = clref.GetEntriesFast();
  return new(clref[size]) R3BMusicHitData(detid,charge);
}

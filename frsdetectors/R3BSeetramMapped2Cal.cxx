// ----------------------------------------------------------------------
// -----         R3BSeetramMapped2Cal source file                   -----
// -----             Created 10/08/18  by J.L. Rodriguez-Sanchez    -----
// ----------------------------------------------------------------------

//ROOT headers
#include "TClonesArray.h"
#include "TMath.h"

//Fair headers
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRuntimeDb.h"
#include "FairLogger.h"
#include <iomanip>

//Seetram and frs headers
#include "R3BSeetramCalData.h"
#include "R3BFrsMappedData.h"
#include "R3BSeetramMapped2Cal.h"
#include "R3BSeetramCalPar.h"

//R3BSeetramMapped2Cal: Default Constructor --------------------------
R3BSeetramMapped2Cal::R3BSeetramMapped2Cal() : 
  FairTask("R3B Seetram Calibrator",1),
  NumParams(0),
  fclock1seg(0),
  fseecounts(0),
  firstclock1seg(0),
  firstEvt(kTRUE),
  CalParams(NULL),
  fCal_Par(NULL),
  fFrsMappedDataCA(NULL),
  fSeetramCalDataCA(NULL),
  fOnline(kFALSE)
{
}

//R3BSeetramMapped2CalPar: Standard Constructor --------------------------
R3BSeetramMapped2Cal::R3BSeetramMapped2Cal(const char* name, Int_t iVerbose) :
  FairTask(name, iVerbose),
  NumParams(0),
  fclock1seg(0),
  fseecounts(0),
  firstclock1seg(0),
  firstEvt(kTRUE),
  CalParams(NULL),
  fCal_Par(NULL),
  fFrsMappedDataCA(NULL),
  fSeetramCalDataCA(NULL),
  fOnline(kFALSE)
{  
}

//Virtual R3BSeetramMapped2Cal: Destructor
R3BSeetramMapped2Cal::~R3BSeetramMapped2Cal()
{
  LOG(INFO) << "R3BSeetramMapped2Cal: Delete instance" << FairLogger::endl;
}


void R3BSeetramMapped2Cal::SetParContainers() {
  
  //Parameter Container
  //Reading seetramCalPar from FairRuntimeDb
  FairRuntimeDb* rtdb = FairRuntimeDb::instance();
  if (!rtdb) { 
    LOG(ERROR)<<"FairRuntimeDb not opened!"<<FairLogger::endl;
  }
  
  fCal_Par=(R3BSeetramCalPar*)rtdb->getContainer("seetramCalPar");
  if (!fCal_Par) {
    LOG(ERROR)<<"R3BSeetramMapped2CalPar::Init() Couldn't get handle on seetramCalPar container"<<FairLogger::endl;
  }
  else{
    LOG(INFO)<<"R3BSeetramMapped2CalPar:: seetramCalPar container open"<<FairLogger::endl;
  }
}


void R3BSeetramMapped2Cal::SetParameter(){
  
  //--- Parameter Container ---
  NumParams=fCal_Par->GetNumParametersFit();//Number of Parameters

  LOG(INFO)<<"R3BSeetramMapped2Cal: Nb parameters for calibration: "<< NumParams <<FairLogger::endl;
  
  CalParams= new TArrayF();
  Int_t array_size = NumParams;
  CalParams->Set(array_size);	
  CalParams=fCal_Par->GetSeetramCalParams();//Array with the Cal parameters
/*
  //Count the number of dead anodes per Music detector
  for(Int_t d = 0; d < NumDets; d++){
  Int_t numdeadanodes=0;
  for(Int_t i = 0; i < NumAnodes; i++)if(CalParams->GetAt(NumParams*i+1+NumAnodes*d*NumParams)==-1)numdeadanodes++;
  LOG(INFO)<<"R3BSeetramMapped2Cal: Nb of dead anodes in MUSIC " <<d+1<< ": "<< numdeadanodes <<FairLogger::endl;
  }
*/
}

// -----   Public method Init   --------------------------------------------
InitStatus R3BSeetramMapped2Cal::Init()
{
  LOG(INFO) << "R3BSeetramMapped2Cal: Init" << FairLogger::endl;

  //INPUT DATA
  FairRootManager* rootManager = FairRootManager::Instance();
  if (!rootManager) { return kFATAL;}
  
  fFrsMappedDataCA = (TClonesArray*)rootManager->GetObject("FrsMappedData");
  if (!fFrsMappedDataCA) { return kFATAL;}
   
  //OUTPUT DATA
  //Calibrated data
  fSeetramCalDataCA = new TClonesArray("R3BSeetramCalData",10);
  if(!fOnline){
  rootManager->Register("SeetramCalData", "Seetram Cal", fSeetramCalDataCA, kTRUE);
  }else{
  rootManager->Register("SeetramCalData", "Seetram Cal", fSeetramCalDataCA, kFALSE);
  } 

  SetParameter();
  return kSUCCESS;
}

// -----   Public method ReInit   ----------------------------------------------
InitStatus R3BSeetramMapped2Cal::ReInit()
{
  SetParContainers();
  return kSUCCESS;
}

// -----   Public method Execution   --------------------------------------------
void R3BSeetramMapped2Cal::Exec(Option_t* option)
{
  
  //Reset entries in output arrays, local arrays
  Reset();
  
  if (!fCal_Par) {
    LOG(ERROR)<<"NO Container for Seetram detector!!"<<FairLogger::endl;
  }  
 
  

  //Reading the Input -- Mapped Data --
  Int_t nHits = fFrsMappedDataCA->GetEntries();
  //if(nHits==0)LOG(WARNING) << "R3BSeetramMapped2Cal: nHits=" <<nHits<<FairLogger::endl;
  if(!nHits) return;
  
  R3BFrsMappedData** mappedData = new R3BFrsMappedData*[nHits];

  //fseecounts = 0;
  //firstEvt = kTRUE;

  for(Int_t i = 0; i < nHits; i++) {
    mappedData[i] = (R3BFrsMappedData*)(fFrsMappedDataCA->At(i));
   
   if(firstEvt){ 
     firstEvt = kFALSE;
     fseecounts=0;
     fclock1seg = mappedData[i]->GetClock1Hz(); 
     fseecounter = mappedData[i]->GetSeetramNew();
     firstclock1seg = fclock1seg;
   }

   if(mappedData[i]->GetClock1Hz()<fclock1seg){
     firstclock1seg=-1*(fclock1seg-firstclock1seg)+mappedData[i]->GetClock1Hz();
     fclock1seg=mappedData[i]->GetClock1Hz();
     fseecounter=mappedData[i]->GetSeetramNew();
   }

   if(mappedData[i]->GetClock1Hz()==fclock1seg){
     fseecounts = fseecounts + (mappedData[i]->GetSeetramNew()-fseecounter);
     fseecounter = mappedData[i]->GetSeetramNew();
   }else{
     //fseecounts=fseecounts;
     //std::cout << fclock1seg-firstclock1seg << " "<< fseecounts  << std::endl;
     AddCalData(fseecounts, fclock1seg-firstclock1seg);
     fclock1seg=mappedData[i]->GetClock1Hz();
     fseecounts=0;
     fseecounts = fseecounts + (mappedData[i]->GetSeetramNew()-fseecounter);
     fseecounter = mappedData[i]->GetSeetramNew();
   }

  }

/*  Int_t detId;
  Int_t anodeId;
  Double_t energy;
  Double_t pedestal=0.;
  Double_t sigma=0.;

  for(Int_t i = 0; i < nHits; i++) {
    mappedData[i] = (R3BMusicMappedData*)(fMusicMappedDataCA->At(i));
    detId   = mappedData[i]->GetDetectorId();
    anodeId = mappedData[i]->GetAnodeId();

    pedestal=CalParams->GetAt(NumParams*anodeId+1+detId*NumAnodes*NumParams);
    //sigma=CalParams->GetAt(NumParams*anodeId+2+detId*NumAnodes*NumParams);

   // std::cout << detId << " " << anodeId<<" "<< mappedData[i]->GetEnergy()<< " " << pedestal << std::endl;

    energy  = mappedData[i]->GetEnergy()-pedestal;

    if(pedestal!=-1)
    AddCalData(detId,anodeId,energy);
  }
  */
  if(mappedData) delete mappedData;
  return;
}

// -----   Protected method Finish   --------------------------------------------
void R3BSeetramMapped2Cal::Finish()
{
  
}

// -----   Public method Reset   ------------------------------------------------
void R3BSeetramMapped2Cal::Reset()
{
  LOG(DEBUG) << "Clearing SeetramCalData Structure" << FairLogger::endl;
  if(fSeetramCalDataCA)fSeetramCalDataCA->Clear();
}


// -----   Private method AddCalData  --------------------------------------------
R3BSeetramCalData* R3BSeetramMapped2Cal::AddCalData(Int_t Seecounts, Int_t clock1seg)
{
  //It fills the R3BSeetramCalData
  TClonesArray& clref = *fSeetramCalDataCA;
  Int_t size = clref.GetEntriesFast();
  return new(clref[size]) R3BSeetramCalData(Seecounts,clock1seg);
}

ClassImp(R3BSeetramMapped2Cal)

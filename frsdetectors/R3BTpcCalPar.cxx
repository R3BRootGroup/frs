// ------------------------------------------------------------------
// -----         R3BTpcCalPar source file                       -----
// -----         Created 29/07/18  by J.L. Rodriguez-Sanchez    -----
// ------------------------------------------------------------------

#include "R3BTpcCalPar.h"

#include "FairLogger.h"
#include "FairParamList.h"

#include "TString.h"
#include "TMath.h"
#include "TArrayF.h"

#include <iostream>

using std::cout;
using std::endl;

// ---- Standard Constructor ---------------------------------------------------
R3BTpcCalPar::R3BTpcCalPar(const char* name,
					       const char* title,
					       const char* context)
  : FairParGenericSet(name,title,context) {
  fNumDets=4;
  fNumDT=6;//4dt_y + 2dt_x
  fNumParamsFit=2;
  fTpcCalParams= new TArrayF(24);//4*4dty + 4*2dtx
  fTpcCsumMinParams= new TArrayF(16);//4lines*4dect
  fTpcCsumMaxParams= new TArrayF(16);//4lines*4dect
}

// ----  Destructor ------------------------------------------------------------
R3BTpcCalPar::~R3BTpcCalPar() {
  clear();
  delete fTpcCalParams;
  delete fTpcCsumMaxParams;
  delete fTpcCsumMinParams;
}

// ----  Method clear ----------------------------------------------------------
void R3BTpcCalPar::clear() {
  status=kFALSE;
  resetInputVersions();
}

// ----  Method putParams ------------------------------------------------------
void R3BTpcCalPar::putParams(FairParamList* list) {
  LOG(INFO) <<"R3BTpcCalPar::putParams() called" <<FairLogger::endl;
  if (!list){ return; }
  
  Int_t array_size = fNumDets*fNumParamsFit*fNumDT;
  LOG(INFO) <<"Array Size: "<<array_size <<FairLogger::endl;
  
  fTpcCalParams->Set(array_size);

  Int_t array_sizecsum = fNumDets*4;
  fTpcCsumMaxParams->Set(array_sizecsum);
  fTpcCsumMinParams->Set(array_sizecsum);
  
  list->add("tpcDetNumberPar", fNumDets);
  list->add("tpcSectionNumberPar", fNumDT);
  list->add("tpcSectionParamsFitPar", fNumParamsFit);
  list->add("tpcCsumMaxPar", *fTpcCsumMaxParams);
  list->add("tpcCsumMinPar", *fTpcCsumMinParams);
  list->add("tpcCalPar", *fTpcCalParams);
}


// ----  Method getParams ------------------------------------------------------
Bool_t R3BTpcCalPar::getParams(FairParamList* list) {
  LOG(INFO) <<"R3BTpcCalPar::getParams() called" <<FairLogger::endl;
  if (!list){ return kFALSE;}

  if (!list->fill("tpcDetNumberPar", &fNumDets) ) { 
    return kFALSE; 
  }  

  if (!list->fill("tpcSectionNumberPar", &fNumDT) ) { 
    return kFALSE; 
  }
  
  if (!list->fill("tpcSectionParamsFitPar", &fNumParamsFit) ) { 
    return kFALSE; 
  }

  fTpcCsumMaxParams->Set(fNumDets*4);
  if (!(list->fill("tpcCsumMaxPar",fTpcCsumMaxParams))){
    LOG(INFO)<< "---Could not initialize tpcCsumMaxPar"<<FairLogger::endl;
    return kFALSE;
  }
  fTpcCsumMinParams->Set(fNumDets*4);
  if (!(list->fill("tpcCsumMinPar",fTpcCsumMinParams))){
    LOG(INFO)<< "---Could not initialize tpcCsumMinPar"<<FairLogger::endl;
    return kFALSE;
  }
  
  Int_t array_size = fNumDets*fNumParamsFit*fNumDT;
  LOG(INFO) <<"Array Size: "<<array_size <<FairLogger::endl;
  fTpcCalParams->Set(array_size);
  
  if (!(list->fill("tpcCalPar",fTpcCalParams))){
    LOG(INFO)<< "---Could not initialize tpcCalPar"<<FairLogger::endl;
    return kFALSE;
  }
  
  return kTRUE;
}

// ----  Method printParams ----------------------------------------------------
void R3BTpcCalPar::printParams() {
  LOG(INFO) << "R3BTpcCalPar: tpc Parameters for limits csum: "<<FairLogger::endl;	
  for(Int_t d=0;d<fNumDets;d++) {
   std::cout << "TPC detector number: " <<d<< std::endl;
   for(Int_t i=0;i<4;i++) { 
    std::cout << "CsumParam(min,max) = ("<<fTpcCsumMinParams->GetAt(d*4+i) <<","<<fTpcCsumMaxParams->GetAt(d*4+i)<<")" <<std::endl;
   }
  }

  LOG(INFO) << "R3BTpcCalPar: tpc anode Parameters: "<<FairLogger::endl;
  for(Int_t d=0;d<fNumDets;d++) {
    std::cout << "TPC detector number: " << d << std::endl;
   for(Int_t i=0;i<fNumDT;i++) {      
    std::cout << "Section number: " << i << std::endl;
    for(Int_t j=0;j<fNumParamsFit;j++) {
      std::cout << "FitParam("<<j<<") = "<<fTpcCalParams->GetAt(d*fNumParamsFit*fNumDT+i*fNumParamsFit+j) << std::endl;
    }
   }
  }
}



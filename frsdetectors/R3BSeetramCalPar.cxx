// ------------------------------------------------------------------
// -----             R3BSeetramCalPar source file               -----
// -----         Created 15/07/18  by J.L. Rodriguez-Sanchez    -----
// ------------------------------------------------------------------

#include "R3BSeetramCalPar.h"

#include "FairLogger.h"
#include "FairParamList.h"

#include "TString.h"
#include "TMath.h"
#include "TArrayF.h"

#include <iostream>

using std::cout;
using std::endl;

// ---- Standard Constructor ---------------------------------------------------
R3BSeetramCalPar::R3BSeetramCalPar(const char* name,
					       const char* title,
					       const char* context)
  : FairParGenericSet(name,title,context) {
  fSeetramCalParams= new TArrayF(2);
  fNumParamsFit=2;
}

// ----  Destructor ------------------------------------------------------------
R3BSeetramCalPar::~R3BSeetramCalPar() {
  clear();
  //delete fStripCalParams;
}

// ----  Method clear ----------------------------------------------------------
void R3BSeetramCalPar::clear() {
  status=kFALSE;
  resetInputVersions();
}

// ----  Method putParams ------------------------------------------------------
void R3BSeetramCalPar::putParams(FairParamList* list) {
  LOG(INFO) <<"R3BSeetramCalPar::putParams() called";
  if (!list){ return; }
  
  Int_t array_size = fNumParamsFit;
  LOG(INFO) <<"Array Size: "<<array_size;
 /*
  fStripCalParams->Set(array_size);
  
  list->add("amsStripCalPar", *fStripCalParams);
  list->add("amsDetNumberPar", fNumDets);
  list->add("amsStripNumberPar", fNumStrips);
  list->add("amsStripSNumberPar", fNumStripsS);
  list->add("amsStripKNumberPar", fNumStripsK);
*/
  list->add("SeetramFitPar", fNumParamsFit);
}


// ----  Method getParams ------------------------------------------------------
Bool_t R3BSeetramCalPar::getParams(FairParamList* list) {
  LOG(INFO) <<"R3BSeetramCalPar::getParams() called";
  if (!list){ return kFALSE;}
/*
  if (!list->fill("amsDetNumberPar", &fNumDets) ) { 
    return kFALSE; 
  }  

  if (!list->fill("amsStripNumberPar", &fNumStrips) ) { 
    return kFALSE; 
  }

  if (!list->fill("amsStripSNumberPar", &fNumStripsS) ) { 
    return kFALSE; 
  }

  if (!list->fill("amsStripKNumberPar", &fNumStripsK) ) { 
    return kFALSE; 
  }
  */
  if (!list->fill("SeetramFitPar", &fNumParamsFit) ) { 
    return kFALSE; 
  }
  /*
  Int_t array_size = fNumDets*fNumStrips*fNumParamsFit;
  LOG(INFO) <<"Array Size: "<<array_size;
  fStripCalParams->Set(array_size);
  
  if (!(list->fill("amsStripCalPar",fStripCalParams))){
    LOG(INFO)<< "---Could not initialize amsStripCalPar";
    return kFALSE;
  }
  */
  return kTRUE;
}

// ----  Method printParams ----------------------------------------------------
void R3BSeetramCalPar::printParams() {	
  LOG(INFO) << "R3BSeetramCalPar: seetram Parameters: ";
/*  Int_t array_size = fNumDets*fNumStrips*fNumParamsFit;
  
  for(Int_t d=0;d<fNumDets;d++) {
    cout << "AMS detector number: " << d << endl;
   for(Int_t i=0;i<fNumStrips;i++) {      
    cout << "AMS Strip number: " << i << endl;
    for(Int_t j=0;j<fNumParamsFit;j++) {
      cout << "FitParam("<<j<<") = "<<fStripCalParams->GetAt(d*fNumParamsFit*fNumStrips+i*fNumParamsFit+j) << endl;
    }
   }
  }

*/
}



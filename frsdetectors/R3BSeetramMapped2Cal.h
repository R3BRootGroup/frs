// ----------------------------------------------------------------------
// -----                                                            -----
// -----                     R3BSeetramMapped2Cal                   -----
// -----             Created 10/08/18  by J.L. Rodriguez-Sanchez    -----
// ----------------------------------------------------------------------

#ifndef R3BSeetramMapped2Cal_H
#define R3BSeetramMapped2Cal_H

#include "FairTask.h"
#include "TH1F.h"
#include "R3BSeetramCalData.h"
#include "R3BFrsMappedData.h"


class TClonesArray;
class R3BSeetramCalPar;

class R3BSeetramMapped2Cal : public FairTask {
  
 public:
  /** Default constructor **/
  R3BSeetramMapped2Cal();

  /** Standard constructor **/
  R3BSeetramMapped2Cal(const char* name, Int_t iVerbose=1);
  
  /** Destructor **/
  virtual ~R3BSeetramMapped2Cal();
  
  /** Virtual method Exec **/
  virtual void Exec(Option_t* option);
  
  /** Virtual method Reset **/
  virtual void Reset();
  
  virtual void SetParContainers();
  
  //Fair specific
  /** Virtual method Init **/
  virtual InitStatus Init();
  
  /** Virtual method ReInit **/
  virtual InitStatus ReInit();
  
  /** Virtual method Finish **/
  virtual void Finish();

  /** Accessor to select online mode **/
  void SetOnline(Bool_t option){fOnline=option;}  
  
 private:
  
  void SetParameter();

  Int_t NumParams;

  //clocks
  Int_t fclock1hz;
  Int_t fclock10hz;
  Int_t fclock100khz;
  Int_t firstclock1hz;
  Int_t firstclock10hz;
  Int_t firstclock100khz;

  //Triggers
  Int_t faceptrigcounts;
  Int_t faceptrigcounter;
  Int_t ffreetrigcounts;
  Int_t ffreetrigcounter;

  //seetram
  Int_t fseecounts;
  Int_t fseecounter;

  //IC
  Int_t ficcounts;
  Int_t ficcounter;

  //sci00
  Int_t fsci00counts;
  Int_t fsci00counter;

  //sci01
  Int_t fsci01counts;
  Int_t fsci01counter;

  //sci02
  Int_t fsci02counts;
  Int_t fsci02counter;

  //dummy
  Int_t fdumcounts;
  Int_t fdumcounter;

  //sci21
  Int_t fsci21counts;
  Int_t fsci21counter;

  //sci41
  Int_t fsci41counts;
  Int_t fsci41counter;

  Bool_t firstEvt;

  TArrayF* CalParams;

  Bool_t fOnline;//Don't store data for online
  
  R3BSeetramCalPar* fCal_Par;       /**< Parameter container. >*/ 
  TClonesArray* fFrsMappedDataCA;   /**< Array with FRS Mapped- input data. >*/
  TClonesArray* fSeetramCalDataCA;  /**< Array with Seetram Cal- output data. >*/
  
  /** Private method AddCalData **/
  //** Adds a SeetramCalData to the CalCollection
  R3BSeetramCalData* AddCalData(Int_t acctrigger, Int_t freetrigger, Int_t Seecounts, Int_t IcCounts, Int_t DumCounts, Int_t Sci00Counts, Int_t Sci01Counts, Int_t Sci02Counts, Int_t clock1seg);

 public:
  //Class definition
  ClassDef(R3BSeetramMapped2Cal, 1)
    };

#endif

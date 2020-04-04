// --------------------------------------------------------------
// -----                                                    -----
// -----                   FrsMusicReader                   -----
// -----     Created 14/03/20  by J.L. Rodriguez-Sanchez    -----
// -----        A reader of FRS-MUSIC data with UCESB       -----
// --------------------------------------------------------------

#ifndef FrsMusicReader_H
#define FrsMusicReader_H

#include "R3BReader.h"

class TClonesArray;
class FairLogger;

struct EXT_STR_h101_FRSMUSIC_t;
typedef struct EXT_STR_h101_FRSMUSIC_t EXT_STR_h101_FRSMUSIC;
typedef struct EXT_STR_h101_FRSMUSIC_onion_t EXT_STR_h101_FRSMUSIC_onion;

class FrsMusicReader : public R3BReader
{
  public:
    /** Standard constructor **/
    FrsMusicReader(EXT_STR_h101_FRSMUSIC*, UInt_t);

    /** Destructor **/
    virtual ~FrsMusicReader();

    /** Method Init **/
    Bool_t Init(ext_data_struct_info*);

    /** Data reader **/
    Bool_t Read();

    /** Virtual method Reset **/
    void Reset();

    /** Accessor to select the number of detectors **/
    void SetNbDet(Int_t ndet) { fNbDet = ndet; }

    /** Accessor to select online mode **/
    void SetOnline(Bool_t option) { fOnline = option; }

  private:
    /* An event counter */
    UInt_t fNEvent;
    /* Number of detectors */
    Int_t fNbDet;
    /* Reader specific data structure from ucesb */
    EXT_STR_h101_FRSMUSIC* fData;
    /* Data offset */
    UInt_t fOffset;
    /* FairLogger */
    FairLogger* fLogger;
    // Don't store data for online
    Bool_t fOnline;
    // Output array
    TClonesArray* fArray;

  public:
    ClassDef(FrsMusicReader, 0);
};

#endif

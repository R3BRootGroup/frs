#ifndef FrsTpcReader_H
#define FrsTpcReader_H

#include "R3BReader.h"
#include "TFile.h"
#include "TTree.h"

class TClonesArray;
class FairLogger;
class TLeaf;

struct EXT_STR_h101_TPC_t;
typedef struct EXT_STR_h101_TPC_t EXT_STR_h101_TPC;
// class ext_data_struct_info;

/**
 * A reader of FRS data with UCESB.
 * Receives mapped raw data and converts it to FAIRRoot objects.
 * @author J.L. Rodriguez
 * @since March 9th, 2020
 */
class FrsTpcReader : public R3BReader
{
  public:
    /**
     * Standard constructor.
     * Creates instance of the reader. To be called in the steering macro.
     * @param Pointer to a full C structure generated by the Ucesb unpacker.
     */
    FrsTpcReader(EXT_STR_h101_TPC*, UInt_t);
    ~FrsTpcReader();

    Bool_t Init(ext_data_struct_info*);
    Bool_t Read();
    void Reset();

    /** Accessor to select online mode **/
    void SetOnline(Bool_t option) { fOnline = option; }

  private:
    /* An event counter */
    unsigned int fNEvent;
    /* Reader specific data structure from ucesb */
    EXT_STR_h101_TPC* fData;
    /* Data offset */
    UInt_t fOffset;
    /* FairLogger */
    FairLogger* fLogger;

    Bool_t fOnline; // Don't store data for online

    TClonesArray* fArray;   // Output array for tpc detectors.

    Int_t tpc_ae[4], tpc_le[2], tpc_re[2], tpc_dt[4], tpc_lt[2], tpc_rt[2];

  public:
    ClassDef(FrsTpcReader, 0);
};

#endif

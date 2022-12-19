#ifndef R3BFrsReaderNov19_H
#define R3BFrsReaderNov19_H

#include "R3BReader.h"
#include "TFile.h"
#include "TTree.h"

class TClonesArray;
class FairLogger;
class TLeaf;
class R3BEventHeader;

struct EXT_STR_h101_FRS_t;
typedef struct EXT_STR_h101_FRS_t EXT_STR_h101_FRS;
// class ext_data_struct_info;

/**
 * A reader of FRS data with UCESB.
 * Receives mapped raw data and converts it to FAIRRoot objects.
 * @author J.L. Rodriguez
 * @since Nov 16th, 2019
 */
class R3BFrsReaderNov19 : public R3BReader
{
  public:
    /**
     * Standard constructor.
     * Creates instance of the reader. To be called in the steering macro.
     * @param Pointer to a full C structure generated by the Ucesb unpacker.
     */
    R3BFrsReaderNov19(EXT_STR_h101_FRS*, UInt_t);
    ~R3BFrsReaderNov19();

    Bool_t Init(ext_data_struct_info*);
    Bool_t Read();
    void Reset();

    /** Accessor to select online mode **/
    void SetOnline(Bool_t option) { fOnline = option; }

  private:
    /* An event counter */
    unsigned int fNEvent;
    /* Reader specific data structure from ucesb */
    EXT_STR_h101_FRS* fData;
    /* Data offset */
    UInt_t fOffset;
    /* FairLogger */
    FairLogger* fLogger;
    /* A pointer to the R3BEventHeader structure */
    R3BEventHeader* fEventHeader;

    Bool_t fOnline; // Don't store data for online

    TClonesArray* fArray;      // Output array for frs scin and scalers.
    TClonesArray* fArrayMusic; // Output array for music detectors.
    TClonesArray* fArrayTpc;   // Output array for tpc detectors.
    TClonesArray* fArraySpill; // Output array for spill.

    TClonesArray* fArrayMW11; // Output array for mw detectors.
    TClonesArray* fArrayMW21;
    TClonesArray* fArrayMW22;
    TClonesArray* fArrayMW31;
    TClonesArray* fArrayMW51;
    TClonesArray* fArrayMW71;
    TClonesArray* fArrayMW81;
    TClonesArray* fArrayMW82;

    int unpack_vme0[21][32];
    int unpack_vme1[21][32];
    float by_pos_TPC1, anal_de_cor2;

    TBranch* b_theData_unpack_vme0; //!
    TBranch* b_theData_unpack_vme1; //!

    TFile* fRootFile;
    TTree* fTreeFile;

    Int_t tpc_ae[4], tpc_le[2], tpc_re[2], tpc_dt[4], tpc_lt[2], tpc_rt[2];

  public:
    ClassDef(R3BFrsReaderNov19, 0);
};

#endif

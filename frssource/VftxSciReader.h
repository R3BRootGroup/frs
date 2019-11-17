#ifndef VftxSciReader_H
#define VftxSciReader_H

#include "R3BReader.h"
#include "TClonesArray.h"

struct EXT_STR_h101_frssci_t;
typedef struct EXT_STR_h101_frssci_t EXT_STR_h101_frssci;
class FairLogger;

class VftxSciReader : public R3BReader
{
  public:
    VftxSciReader(EXT_STR_h101_frssci*, UInt_t);
    ~VftxSciReader();

    Bool_t Init(ext_data_struct_info*);
    Bool_t Read();
    void Reset();

    /** Accessor to select online mode **/
    void SetOnline(Bool_t option) { fOnline = option; }

  private:
    /* Reader specific data structure from ucesb */
    EXT_STR_h101_frssci* fData;
    /* Data offset */
    UInt_t fOffset;
    // Don't store data for online
    Bool_t fOnline;
    /* the structs of type VftxSciMapped Item */
    TClonesArray* fArray; /**< Output array. */
    UInt_t fNumEntries;

  public:
    ClassDef(VftxSciReader, 0);
};

#endif

#ifndef R3BWasaReader_H
#define R3BWasaReader_H

#include "R3BReader.h"

class TClonesArray;
class FairLogger;

struct EXT_STR_h101_WASA_t;
typedef struct EXT_STR_h101_WASA_t EXT_STR_h101_WASA;

/**
 * A reader of WASA data with UCESB.
 * Receives mapped raw data and converts it to R3BRoot objects.
 * @author J.L. Rodriguez
 * @since September 23, 2018
 */
class R3BWasaReader : public R3BReader
{
  public:
    /**
     * Standard constructor.
     * Creates instance of the reader. To be called in the steering macro.
     * @param Pointer to a full C structure generated by the Ucesb unpacker.
     */
    R3BWasaReader(EXT_STR_h101_WASA*, UInt_t);
    ~R3BWasaReader();

    Bool_t Init(ext_data_struct_info*);
    Bool_t Read();
    void Reset();

    /** Accessor to select online mode **/
    void SetOnline(Bool_t option) { fOnline = option; }

  private:
    /* An event counter */
    unsigned int fNEvent;
    /* Reader specific data structure from ucesb */
    EXT_STR_h101_WASA* fData;
    /* Data offset */
    UInt_t fOffset;
    /* FairLogger */
    FairLogger* fLogger;

    Bool_t fOnline;   // Don't store data for online

    TClonesArray* fArrayMdcWasa;   // Output array for mdc detector.

  public:
    ClassDef(R3BWasaReader, 0);
};

#endif

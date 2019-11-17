#ifndef VftxSciMappedData_H
#define VftxSciMappedData_H

#include "TObject.h"

class VftxSciMappedData : public TObject
{
  public:
    // Default Constructor
    VftxSciMappedData();

    // Standard Constructor
    VftxSciMappedData(UShort_t detector, UShort_t pmt, UInt_t tc, UInt_t tf);

    // Destructor
    virtual ~VftxSciMappedData() {}

    // Getters
    inline const UShort_t& GetDetector() const { return fDetector; }
    inline const UShort_t& GetPmt() const { return fPmt; }
    inline const UInt_t& GetTimeCoarse() const { return fTimeCoarse; }
    inline const UInt_t& GetTimeFine() const { return fTimeFine; }

  private:
    UShort_t fDetector;
    UShort_t fPmt;      
    UInt_t fTimeCoarse;
    UInt_t fTimeFine;

  public:
    ClassDef(VftxSciMappedData, 1)
};

#endif

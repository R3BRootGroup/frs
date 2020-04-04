#ifndef FRSSCITCALITEM_H
#define FRSSCITCALITEM_H

#include "TObject.h"

class FrsSciTcalData : public TObject
{
  public:
    // Default Constructor
    FrsSciTcalData();

    // Standard Constructor
    FrsSciTcalData(UShort_t detector, UShort_t pmt, Double_t t);

    // Destructor
    virtual ~FrsSciTcalData() {}

    // Getters
    inline const UShort_t& GetDetector() const { return fDetector; }
    inline const UShort_t& GetPmt() const { return fPmt; }
    inline const Double_t& GetRawTimeNs() const { return fRawTimeNs; }

  private:
    UShort_t fDetector; // 1..n
    UShort_t fPmt;      // 1..3
    Double_t fRawTimeNs;

  public:
    ClassDef(FrsSciTcalData, 1)
};

#endif

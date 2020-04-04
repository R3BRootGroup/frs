#ifndef FRSSCISINGLETCALITEM_H
#define FRSSCISINGLETCALITEM_H

#include "TObject.h"
#include "FairLogger.h"

class FrsSciSingleTcalData : public TObject
{
  public:
    // Default Constructor
    FrsSciSingleTcalData();

    // Destructor
    virtual ~FrsSciSingleTcalData() {}

    // Getters
    inline const Double_t& GetRawTimeNs(UShort_t det) const { return fRawTimeNs[det-1]; }
    inline const Double_t& GetRawPosNs(UShort_t det)  const { return fRawPosNs[det-1]; }
    inline const Double_t& GetRawTofNs(UShort_t rank) const { return fRawTofNs[rank];}

    // Modifiers
    void SetRawTimeNs(UShort_t det, Double_t time)  {fRawTimeNs[det-1]=time;}
    void SetRawPosNs(UShort_t det, Double_t pos)    {fRawPosNs[det-1]=pos;}
    void SetMultPerDet(UShort_t det, UShort_t m)    {fMultPerDet[det-1]=m;}
    void SetRawTofNs(UShort_t rank, Double_t tof)   {fRawTofNs[rank]=tof;} 
    void SetMultPerToF(UShort_t rank, UShort_t m)    {fMultPerDet[rank]=m;} 

  private:
    Double_t fRawTimeNs[2];           // 0.5*(Tleft + Tright)
    Double_t fRawPosNs[2];            // Tleft - Tright
    UShort_t fMultPerDet[2];        // number of hits with the proper pos 

    Double_t fRawTofNs[1];
    UShort_t fMultPerTof[1];              // number of hits with the proper tof 

  public:
    ClassDef(FrsSciSingleTcalData, 2)
};

#endif

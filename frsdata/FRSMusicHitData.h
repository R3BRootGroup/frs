// ---------------------------------------------------------------------------
// -----                                                                 -----
// -----                      FRSMusicHitData                            -----
// -----                  Created 12/05/2018 by J.L. Rodriguez           -----
// -----                                                                 -----
// ---------------------------------------------------------------------------

#ifndef FRSMusicHitData_H
#define FRSMusicHitData_H
#include "TObject.h"

class FRSMusicHitData : public TObject
{

  public:
    // Default Constructor
    FRSMusicHitData();

    /** Standard Constructor
     *@param detId       Detector unique identifier
     *@param charge      Total energy deposited in the detector in units of Z
     **/
    FRSMusicHitData(Int_t detId, Double_t charge);

    // Destructor
    ~FRSMusicHitData() {}

    // Getters
    inline const Int_t& GetDetectorId() const { return fDetId; }
    inline const Double_t& GetZ() const { return fCharge; }

  protected:
    Int_t fDetId;     // detector unique identifiers
    Double_t fCharge; // total energy in units of Z

  public:
    ClassDef(FRSMusicHitData, 1)
};

#endif

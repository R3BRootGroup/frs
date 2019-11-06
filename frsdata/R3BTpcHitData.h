// ---------------------------------------------------------------------------
// -----                                                                 -----
// -----                      R3BTpcHitData                              -----
// -----                  Created 29/07/2018 by J.L. Rodriguez           -----
// -----                                                                 -----
// ---------------------------------------------------------------------------

#ifndef R3BTpcHitData_H
#define R3BTpcHitData_H
#include "TObject.h"

class R3BTpcHitData : public TObject
{

  public:
    // Default Constructor
    R3BTpcHitData();

    /** Standard Constructor
     *@param detId      Detector unique identifier
     *@param x          Position X in [mm]
     *@param y          Position X in [mm]
     **/
    R3BTpcHitData(Int_t detId, Double_t x, Double_t y);

    // Destructor
    ~R3BTpcHitData() {}

    // Getters
    inline const Int_t& GetDetectorId() const { return fDetId; }
    inline const Double_t& GetX() const { return fX; }
    inline const Double_t& GetY() const { return fY; }

  protected:
    Int_t fDetId;
    Double_t fX, fY; // Position X and Y in [mm]

  public:
    ClassDef(R3BTpcHitData, 1)
};

#endif

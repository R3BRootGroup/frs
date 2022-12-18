// ---------------------------------------------------------------------------
// -----                                                                 -----
// -----                      R3BMwHitData                               -----
// -----                  Created 27/03/2019 by J.L. Rodriguez           -----
// -----                                                                 -----
// ---------------------------------------------------------------------------

#ifndef R3BMwHitData_H
#define R3BMwHitData_H
#include "TObject.h"

class R3BMwHitData : public TObject
{

  public:
    // Default Constructor
    R3BMwHitData();

    /** Standard Constructor
     *@param detId      Detector unique identifier
     *@param x          Position X in [mm]
     *@param y          Position X in [mm]
     **/
    R3BMwHitData(Int_t detId, Double_t x, Double_t y);

    // Destructor
    ~R3BMwHitData() {}

    // Getters
    inline const Int_t GetDetId() const { return fDetId; }
    inline const Double_t GetX() const { return fX; }
    inline const Double_t GetY() const { return fY; }

  protected:
    Int_t fDetId;
    Double_t fX, fY;   // Position X and Y in [mm]

  public:
    ClassDef(R3BMwHitData, 1)
};

#endif

// ---------------------------------------------------------------------------
// -----                                                                 -----
// -----                      R3BTpcCalData                              -----
// -----                  Created 29/07/2018 by J.L. Rodriguez           -----
// -----                                                                 -----
// ---------------------------------------------------------------------------

#ifndef R3BTpcCalData_H
#define R3BTpcCalData_H
#include "TObject.h"

class R3BTpcCalData : public TObject
{

  public:
    // Default Constructor
    R3BTpcCalData();

    /** Standard Constructor
     *@param detId       Detector unique identifier
     *@param xyId        Orientation unique identifier
     *@param secId       Section unique identifier
     *@param pos         Position in mm
     *@param controlpar  Control parameter for TPCs (csum and deltaX)
     **/
    R3BTpcCalData(Int_t detId, Int_t xyId, Int_t secId, Double_t position, Double_t controlpar);

    // Destructor
    ~R3BTpcCalData() {}

    // Getters
    inline const Int_t& GetDetectorId() const { return fDetId; }
    inline const Int_t& GetSecId() const { return fSecId; }
    inline const Int_t& GetXYId() const { return fXYId; }
    inline const Double_t& GetPosition() const { return fPos; }
    inline const Double_t& GetControlPar() const { return fControlPar; }

  protected:
    Int_t fDetId, fXYId, fSecId; // detector, orientation and section unique identifiers
    Double_t fPos, fControlPar;  // Position in [mm] and control parameter

  public:
    ClassDef(R3BTpcCalData, 1)
};

#endif

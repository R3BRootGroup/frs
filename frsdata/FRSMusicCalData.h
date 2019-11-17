// ---------------------------------------------------------------------------
// -----                                                                 -----
// -----                      FRSMusicCalData                            -----
// -----                  Created 12/05/2018 by J.L. Rodriguez           -----
// -----                                                                 -----
// ---------------------------------------------------------------------------

#ifndef FRSMusicCalData_H
#define FRSMusicCalData_H
#include "TObject.h"

class FRSMusicCalData : public TObject
{

  public:
    // Default Constructor
    FRSMusicCalData();

    /** Standard Constructor
     *@param detId       Detector unique identifier
     *@param anodeId     Anode unique identifier
     *@param energy      Total energy deposited in the anode
     **/
    FRSMusicCalData(Int_t detId, Int_t anodeId, Int_t energy);

    // Destructor
    ~FRSMusicCalData() {}

    // Getters
    inline const Int_t& GetDetectorId() const { return fDetId; }
    inline const Int_t& GetAnodeId() const { return fAnodeId; }
    inline const Int_t& GetEnergy() const { return fEnergy; }

  protected:
    Int_t fDetId, fAnodeId; // detector and anode unique identifiers
    Int_t fEnergy;          // total energy in the anode

  public:
    ClassDef(FRSMusicCalData, 1)
};

#endif

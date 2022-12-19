// ---------------------------------------------------------------------------
// -----                                                                 -----
// -----                      FRSMusicMappedData                         -----
// -----                  Created 12/05/2018 by J.L. Rodriguez           -----
// -----                                                                 -----
// ---------------------------------------------------------------------------

#ifndef FRSMusicMappedData_H
#define FRSMusicMappedData_H
#include "TObject.h"

class FRSMusicMappedData : public TObject
{

  public:
    // Default Constructor
    FRSMusicMappedData();

    /** Standard Constructor
     *@param detId       Detector unique identifier
     *@param anodeId     Anode unique identifier
     *@param energy      Total energy deposited in the anode
     **/
    FRSMusicMappedData(Int_t detId, Int_t anodeId, Int_t energy);

    // Destructor
    ~FRSMusicMappedData() {}

    // Getters
    inline const Int_t& GetDetectorId() const { return fDetId; }
    inline const Int_t& GetAnodeId() const { return fAnodeId; }
    inline const Int_t& GetEnergy() const { return fEnergy; }

  protected:
    Int_t fDetId, fAnodeId; // detector and anode unique identifiers
    Int_t fEnergy;          // total energy in the anode

  public:
    ClassDef(FRSMusicMappedData, 1)
};

#endif

// ---------------------------------------------------------------------------
// -----                                                                 -----
// -----                      R3BMdcMappedData                           -----
// -----                  Created 23/09/2018 by J.L. Rodriguez           -----
// -----                                                                 -----
// ---------------------------------------------------------------------------

#ifndef R3BMdcMappedData_H
#define R3BMdcMappedData_H
#include "TObject.h"

class R3BMdcMappedData : public TObject
{

  public:
    // Default Constructor
    R3BMdcMappedData();

    /** Standard Constructor
     *@param anodeId     Anode unique identifier
     *@param energy      Total energy deposited in the anode
     **/
    R3BMdcMappedData(Int_t anodeId, Int_t energy);

    // Destructor
    ~R3BMdcMappedData() {}

    // Getters
    inline const Int_t& GetAnodeId() const { return fAnodeId; }
    inline const Int_t& GetEnergy() const { return fEnergy; }

  protected:
    Int_t fAnodeId;   // anode unique identifiers
    Int_t fEnergy;    // total energy in the anode

  public:
    ClassDef(R3BMdcMappedData, 1)
};

#endif

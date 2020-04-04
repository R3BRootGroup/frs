#ifndef __FrsTcalContFact_H__
#define __FrsTcalContFact_H__

#include "FairContFact.h"

// --- ------------------------------------- --- //
// --- Factory for tcal parameter containers --- //
// --- ------------------------------------- --- //

class FairContainer;

class FrsTcalContFact : public FairContFact
{
  private:
    void setAllContainers();

  public:
    FrsTcalContFact();
    ~FrsTcalContFact() {}
    FairParSet* createContainer(FairContainer*);
    void activateParIo(FairParIo* io);
    ClassDef(FrsTcalContFact, 1)
};

#endif // FRSTCALCONTFACT_H

#ifndef R3BFrsContFact_H
#define R3BFrsContFact_H

#include "FairContFact.h"

class FairContainer;

class R3BFrsContFact : public FairContFact {
private:
  void setAllContainers();
public:
  R3BFrsContFact();
  ~R3BFrsContFact() {}
  FairParSet* createContainer(FairContainer*);
  void  activateParIo(FairParIo* io);
  ClassDef( R3BFrsContFact,0) // Factory for all FRS parameter containers
};

#endif  /* !R3BFrsContFact_H */

// ----------------------------------------------------------------------
// -----          R3BFrsContFact source file                        -----
// -----             Created 22/09/18  by J.L. Rodriguez-Sanchez    -----
// ----------------------------------------------------------------------
//
//  R3BFrsContFact
//
//  Factory for the parameter containers in libR3BFrs
//

#include "R3BFrsContFact.h"

#include "FairLogger.h"
#include "FairParAsciiFileIo.h"
#include "FairParRootFileIo.h"
#include "FairRuntimeDb.h"

//#include "R3BSeetramCalPar.h"
#include "R3BFrsAnaPar.h"
#include "FRSMusicCalPar.h"
#include "FRSMusicHitPar.h"
#include "R3BTpcCalPar.h"

#include "TClass.h"

static R3BFrsContFact gR3BFrsContFact;

R3BFrsContFact::R3BFrsContFact()
{
    // Constructor (called when the library is loaded)
    fName = "R3BFrsContFact";
    fTitle = "Factory for parameter containers in libR3BFrs";
    setAllContainers();
    FairRuntimeDb::instance()->addContFactory(this);
}

void R3BFrsContFact::setAllContainers()
{
    /** Creates the Container objects with all accepted contexts and adds them to
     *  the list of containers for the STS library.*/

    FairContainer* p1 = new FairContainer("seetramCalPar", "FRS Parameters", "FrsCalParContext");
    p1->addContext("FrsCalParContext");

    containers->Add(p1);

    FairContainer* p2 = new FairContainer("frsmusicCalPar", "FRS MUSIC Parameters", "FRSMusicCalParContext");
    p2->addContext("FRSMusicCalParContext");

    containers->Add(p2);

    FairContainer* p3 = new FairContainer("frsmusicHitPar", "FRS MUSIC Hit Parameters", "FRSMUSICHitParContext");
    p3->addContext("FRSMUSICHitParContext");

    containers->Add(p3);

    FairContainer* p4 = new FairContainer("tpcCalPar", "TPC Parameters", "TPCCalParContext");
    p4->addContext("TPCCalParContext");

    containers->Add(p4);

    FairContainer* p5 = new FairContainer("frsAnaPar", "FRS S2-S4 Parameters", "FRSANAParContext");
    p5->addContext("FRSANAParContext");

    containers->Add(p5);
}

FairParSet* R3BFrsContFact::createContainer(FairContainer* c)
{
    /** Trals the constructor of the corresponding parameter container.
     * For an actual context, which is not an empty string and not the default context
     * of this container, the name is concatinated with the context. */

    const char* name = c->GetName();
    LOG(INFO) << "R3BFrsContFact: Create container name: " << name;
    FairParSet* p = 0;
    if (strcmp(name, "seetramCalPar") == 0)
    {
        // p=new R3BSeetramCalPar(c->getConcatName().Data(),c->GetTitle(),c->getContext());
    }

    if (strcmp(name, "frsmusicCalPar") == 0)
    {
        p = new FRSMusicCalPar(c->getConcatName().Data(), c->GetTitle(), c->getContext());
    }

    if (strcmp(name, "tpcCalPar") == 0)
    {
        p = new R3BTpcCalPar(c->getConcatName().Data(), c->GetTitle(), c->getContext());
    }

    if (strcmp(name, "frsmusicHitPar") == 0)
    {
        p = new FRSMusicHitPar(c->getConcatName().Data(), c->GetTitle(), c->getContext());
    }

    if (strcmp(name, "frsAnaPar") == 0)
    {
        p = new R3BFrsAnaPar(c->getConcatName().Data(), c->GetTitle(), c->getContext());
    }

    return p;

    // return NULL;
}

void R3BFrsContFact::activateParIo(FairParIo* io)
{
    // activates the input/output class for the parameters
    // needed by the Sts
}

ClassImp(R3BFrsContFact)

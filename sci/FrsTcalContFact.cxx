// ----------------------------------------------------------------------
// -----          R3BFrsContFact source file                        -----
// -----             Created 09/03/20  by J.L. Rodriguez-Sanchez    -----
// ----------------------------------------------------------------------
//
//  R3BFrsContFact
//
//  Factory for the parameter containers in libFrsTcal
//

#include "FrsTcalContFact.h"

#include "FairLogger.h"
#include "FairParAsciiFileIo.h"
#include "FairParRootFileIo.h"
#include "FairRuntimeDb.h"

#include "FrsSciTcalPar.h"
#include "FrsSciRawPosPar.h"
#include "FrsSciRawTofPar.h"

#include "TClass.h"

static FrsTcalContFact gFrsTcalContFact;

FrsTcalContFact::FrsTcalContFact()
{
    // Constructor (called when the library is loaded)
    fName = "FrsTcalContFact";
    fTitle = "Factory for Tcal parameter containers in libFrsTcal";
    setAllContainers();
    LOG(INFO) << "Enter in the FrsTcalContFact constructor";
    FairRuntimeDb::instance()->addContFactory(this);
}

void FrsTcalContFact::setAllContainers()
{
    /** Creates the Container objects with all accepted contexts and adds them to
     *  the list of containers for the STS library.*/

    // --- for scintillators at S2 and S4 --- //
    FairContainer* p1 = new FairContainer("FrsSciTcalPar", "FrsSciTcal Parameters", "FrsSciTcalParContext");
    p1->addContext("FrsSciTcalParContext");
    containers->Add(p1);

    FairContainer* p2 = new FairContainer("FrsSciRawPosPar", "FrsSciRawPos Parameters", "FrsSciRawPosParContext");
    p2->addContext("FrsSciRawPosParContext");
    containers->Add(p2);
 
    FairContainer* p3 = new FairContainer("FrsSciRawTofPar", "FrsSciRawTof Parameters", "FrsSciRawTofParContext");
    p3->addContext("FrsSciRawTofParContext");
    containers->Add(p3);

}

FairParSet* FrsTcalContFact::createContainer(FairContainer* c)
{
    /** Trals the constructor of the corresponding parameter container.
     * For an actual context, which is not an empty string and not the default context
     * of this container, the name is concatinated with the context. */

    const char* name = c->GetName();
    LOG(INFO) << "FrsTcalContFact: Create container name: " << name;
    FairParSet* p = 0;

    if (strcmp(name, "FrsSciTcalPar") == 0)
    {
        p = new FrsSciTcalPar(c->getConcatName().Data(), c->GetTitle(), c->getContext());
    }
    if (strcmp(name, "FrsSciRawPosPar") == 0)
    {
        p = new FrsSciRawPosPar(c->getConcatName().Data(), c->GetTitle(), c->getContext());
    }
    if (strcmp(name, "FrsSciRawTofPar") == 0)
    {
        p = new FrsSciRawTofPar(c->getConcatName().Data(), c->GetTitle(), c->getContext());
    }
    return p;
}

void FrsTcalContFact::activateParIo(FairParIo* io)
{
    // activates the input/output class for the parameters
    // needed by the Sts
}

ClassImp(FrsTcalContFact)

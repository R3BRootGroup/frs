//*-- AUTHOR : Jose Luis
//*-- Created : 30/09/2018

#include "WASAGeoTofPar.h"

#include "FairParamList.h"
#include "TObjArray.h"

#include <iomanip>
#include <iostream>

ClassImp(WASAGeoTofPar)

    WASAGeoTofPar::WASAGeoTofPar(const char* name, const char* title, const char* context)
    : FairParGenericSet(name, title, context)
{

    fGeoSensNodes = new TObjArray();
    fGeoPassNodes = new TObjArray();
}

WASAGeoTofPar::~WASAGeoTofPar(void) {}

void WASAGeoTofPar::clear(void)
{
    if (fGeoSensNodes)
        delete fGeoSensNodes;
    if (fGeoPassNodes)
        delete fGeoPassNodes;
}

void WASAGeoTofPar::putParams(FairParamList* l)
{
    if (!l)
        return;
    l->addObject("FairGeoNodes Sensitive List", fGeoSensNodes);
    l->addObject("FairGeoNodes Passive List", fGeoPassNodes);
}

Bool_t WASAGeoTofPar::getParams(FairParamList* l)
{
    if (!l)
        return kFALSE;
    if (!l->fillObject("FairGeoNodes Sensitive List", fGeoSensNodes))
        return kFALSE;
    if (!l->fillObject("FairGeoNodes Passive List", fGeoPassNodes))
        return kFALSE;

    return kTRUE;
}

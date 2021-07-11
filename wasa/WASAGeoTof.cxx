
/////////////////////////////////////////////////////////////
// WASAGeoTof
//
// Class for geometry of R3BCAL
//
/////////////////////////////////////////////////////////////
#include "WASAGeoTof.h"
#include "FairGeoNode.h"
#include "FairLogger.h"

WASAGeoTof::WASAGeoTof()
{
    // Constructor
    fName = "sts";
    maxSectors = 0;
    maxModules = 99;
}

const char* WASAGeoTof::getModuleName(Int_t m)
{
    // Returns the module name of sts number m
    if (m < 0)
    {
        LOG(ERROR) << "WASAGeoTof::getModuleName:: Module number " << m << " not known!";
        return "";
    }
    if (m < 9)
        sprintf(modName, "calstation0%i", m + 1);
    else
        sprintf(modName, "calstation%i", m + 1);
    return modName;
}

const char* WASAGeoTof::getEleName(Int_t m)
{
    // Returns the element name of sts number m
    sprintf(eleName, "cal%i", m + 1);
    return eleName;
}

ClassImp(WASAGeoTof)

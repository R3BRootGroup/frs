#ifndef WASAGeoTof_H
#define WASAGeoTof_H

#include "FairGeoSet.h"

class WASAGeoTof : public FairGeoSet
{
  protected:
    char modName[30]; // name of module
    char eleName[20]; // substring for elements in module
  public:
    WASAGeoTof();
    ~WASAGeoTof() {}
    const char* getModuleName(Int_t);
    const char* getEleName(Int_t);
    inline Int_t getModNumInMod(const TString&);
    ClassDef(WASAGeoTof, 0) // Class for STS
};

inline Int_t WASAGeoTof::getModNumInMod(const TString& name)
{
    // returns the module index from module name
    return (Int_t)(name[3] - '0') - 1;
}

#endif /* !WASAGeoTof_H */

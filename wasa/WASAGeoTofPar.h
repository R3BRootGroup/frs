#ifndef WASAGeoTofPAR_H
#define WASAGeoTofPAR_H

#include "FairParGenericSet.h"
#include "TH1F.h"

class WASAGeoTofPar : public FairParGenericSet
{
  public:
    TObjArray* fGeoSensNodes; // List of FairGeoNodes for sensitive volumes
    TObjArray* fGeoPassNodes; // List of FairGeoNodes for sensitive volumes

    WASAGeoTofPar(const char* name = "WASAGeoTofPar",
                  const char* title = "Tof Geometry Parameters",
                  const char* context = "TestDefaultContext");
    ~WASAGeoTofPar(void);
    void clear(void);
    void putParams(FairParamList*);
    Bool_t getParams(FairParamList*);
    TObjArray* GetGeoSensitiveNodes() { return fGeoSensNodes; }
    TObjArray* GetGeoPassiveNodes() { return fGeoPassNodes; }

    ClassDef(WASAGeoTofPar, 1)
};

#endif /* !WASAGeoTofPAR_H */

// -------------------------------------------------------------------------
// -----                    FRSWasaFieldMap source file                -----
// -----                Created 30/09/18  by J.L. Rodriguez-Sanchez    -----
// -------------------------------------------------------------------------

#ifndef FRSWasaFieldMap_H
#define FRSWasaFieldMap_H 1


#include "FairField.h"
#include "R3BFieldPar.h"
#include "TRotation.h"
#include "TVector3.h"

class FRSWasaFieldMap : public FairField {


public:


  /** Default constructor **/
  FRSWasaFieldMap();


  /** Standard constructor
   ** @param name       Name of field map
   **/
  FRSWasaFieldMap(const char* mapName);


  /** Destructor **/
  virtual ~FRSWasaFieldMap();


  /** Initialisation (read map from file) **/
  virtual void Init();


  /** Get the field components at a certain point 
   ** @param x,y,z     Point coordinates (local) [cm]
   ** @value Bx,By,Bz  Field components [kG]
   **/
  virtual Double_t GetBx(Double_t x, Double_t y, Double_t z);
  virtual Double_t GetBy(Double_t x, Double_t y, Double_t z);
  virtual Double_t GetBz(Double_t x, Double_t y, Double_t z);


  /** Determine whether a point is inside the field map
   ** @param x,y,z              Point coordinates (local) [cm]
   ** @value kTRUE if inside map, else kFALSE
   **/
  virtual Bool_t IsInside(Double_t x, Double_t y, Double_t z);


  /** Set the position of the field centre **/
  virtual void SetPosition(Double_t x, Double_t y, Double_t z);


  /** Set the magnetic field  **/
  virtual void SetField(Double_t Bx, Double_t By, Double_t Bz);


  /** Set limits  **/
  virtual void SetRmax(Double_t Rmax) { fRmax = Rmax; } 
  virtual void SetRmin(Double_t Rmin) { fRmin = Rmin; }
  virtual void SetZmax(Double_t Zmax) { fZmax = Zmax; }
  virtual void SetZmin(Double_t Zmin) { fZmin = Zmin; }


  /** Set a global field scaling factor **/
  virtual void SetScale(Double_t factor) { fScale = factor; }


  /** Accessors to field parameters in local coordinate system **/
  Double_t GetRmax()  const { return fRmax; } 
  Double_t GetRmin()  const { return fRmin; }
  Double_t GetZmin()  const { return fZmin; }
  Double_t GetZmax()  const { return fZmax; }


  /** Accessor to field centre position in global system **/
  Double_t GetPositionX() const { return fPosX; }
  Double_t GetPositionY() const { return fPosY; }
  Double_t GetPositionZ() const { return fPosZ; }


  /** Accessor to global scaling factor  **/
  Double_t GetScale() const { return fScale; }


  /** Accessors to the field value  **/
  Double_t GetBx() const { return fBx; }
  Double_t GetBy() const { return fBy; }
  Double_t GetBz() const { return fBz; }

  /** Screen output **/
  virtual void Print(Option_t *option="") const;
	

	
 protected:


  /** Reset the field parameters and data **/
  void Reset();


  /** Global scaling factor (w.r.t. map on file) **/
  Double_t fScale;             


  /** Field centre position in global coordinates  **/
  Double_t fPosX, fPosY, fPosZ;


  /** Field limits in local coordinate system **/
  Double_t fRmin, fRmax;
  Double_t fZmin, fZmax;

  /** Field values  **/
  Double_t fBx, fBy, fBz; 


  /** local transformation
  **/
  TRotation* gRot;    //!
  TVector3* gTrans;   //!


 ClassDef(FRSWasaFieldMap,1)

};


#endif

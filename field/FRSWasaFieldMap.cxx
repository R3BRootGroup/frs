// -------------------------------------------------------------------------
// -----                    FRSWasaFieldMap source file                -----
// -----                Created 30/09/18  by J.L. Rodriguez-Sanchez    -----
// -------------------------------------------------------------------------

#include "FRSWasaFieldMap.h"

#include "TMath.h"

#include <fstream>
#include <iomanip>
#include <iostream>

using std::cerr;
using std::cout;
using std::endl;
using std::flush;
using std::right;
using std::setw;
using std::showpoint;

// -------------   Default constructor  ----------------------------------
FRSWasaFieldMap::FRSWasaFieldMap()
    : FairField("WASAFieldMap")
{
    fRmin = fRmax = 0.;
    fZmin = fZmax = 0.;
    fScale = 1.;
    fBx = fBy = fBz = 0.;
    fPosX = fPosY = fPosZ = 0.;
}
// ------------------------------------------------------------------------

// -------------   Standard constructor   ---------------------------------
FRSWasaFieldMap::FRSWasaFieldMap(const char* mapName)
    : FairField(mapName)
{
    fRmin = fRmax = 0.;
    fZmin = fZmax = 0.;
    fScale = 1.;
    fBx = fBy = fBz = 0.;
    fPosX = fPosY = fPosZ = 0.;
}

// ------------   Destructor   --------------------------------------------
FRSWasaFieldMap::~FRSWasaFieldMap() {}
// ------------------------------------------------------------------------

// -----------   Intialisation   ------------------------------------------
void FRSWasaFieldMap::Init()
{
    LOG(info) << "FRSWasaFieldMap: Init";
    fPosX = 0.0;
    fPosY = 0.0;
    fPosZ = 0.0;
    gTrans = new TVector3(-fPosX, -fPosY, -fPosZ);
}
// ------------------------------------------------------------------------

// -----------   Get x component of the field   ---------------------------
Double_t FRSWasaFieldMap::GetBx(Double_t x, Double_t y, Double_t z)
{

    // transform to local coordinates
    // local to global
    TVector3 localPoint(x, y, z);

    localPoint = localPoint + (*gTrans);

    if (IsInside(localPoint.X(), localPoint.Y(), localPoint.Z()))
    {
        // std::cout << fBx << std::endl;
        return fBx;
    }

    return 0.;
}
// ------------------------------------------------------------------------

// -----------   Get y component of the field   ---------------------------
Double_t FRSWasaFieldMap::GetBy(Double_t x, Double_t y, Double_t z)
{

    // transform to local coordinates
    // local to global
    TVector3 localPoint(x, y, z);

    localPoint = localPoint + (*gTrans);

    if (IsInside(localPoint.X(), localPoint.Y(), localPoint.Z()))
    {
        // std::cout << fBy << std::endl;
        return fBy;
    }

    return 0.;
}
// ------------------------------------------------------------------------

// -----------   Get z component of the field   ---------------------------
Double_t FRSWasaFieldMap::GetBz(Double_t x, Double_t y, Double_t z)
{

    // transform to local coordinates
    // local to global
    TVector3 localPoint(x, y, z);

    localPoint = localPoint + (*gTrans);

    if (IsInside(localPoint.X(), localPoint.Y(), localPoint.Z()))
    {
        // std::cout << fBz << std::endl;
        return fBz;
    }

    return 0.;
}
// ------------------------------------------------------------------------

// -----------   Check whether a point is inside the map   ----------------
Bool_t FRSWasaFieldMap::IsInside(Double_t x, Double_t y, Double_t z)
{
    Double_t rl = TMath::Sqrt(x * x + y * y);

    // ---  Check for being outside the map range
    if (rl >= fRmin && rl <= fRmax && z >= fZmin && z <= fZmax)
    {
        return kTRUE;
    }

    return kFALSE;
}
// ------------------------------------------------------------------------

// -----  Set the position of the field centre in global coordinates  -----
void FRSWasaFieldMap::SetPosition(Double_t x, Double_t y, Double_t z)
{
    fPosX = x;
    fPosY = y;
    fPosZ = z;
}
// ------------------------------------------------------------------------

// -----  Set the field  -----
void FRSWasaFieldMap::SetField(Double_t Bx, Double_t By, Double_t Bz)
{
    fBx = Bx;
    fBy = By;
    fBz = Bz;
}
// ------------------------------------------------------------------------

// ---------   Screen output   --------------------------------------------
void FRSWasaFieldMap::Print(Option_t* option) const
{
    cout << "======================================================" << endl;
    cout << "----  " << fTitle << " : " << fName << endl;
    cout << "----" << endl;
    cout << "----  Field type    : constant" << endl;
    cout << "----" << endl;
    cout << "----  Field regions : " << endl;
    cout << "----        r = " << setw(4) << fRmin << " to " << setw(4) << fRmax << " cm" << endl;
    cout << "----        z = " << setw(4) << fZmin << " to " << setw(4) << fZmax << " cm" << endl;
    cout << "---- Position = " << setw(4) << fPosX << " " << setw(4) << fPosY << " " << setw(4) << fPosZ << " cm"
         << endl;
    cout.precision(4);
    cout << "----  B = ( " << fBx << ", " << fBy << ", " << fBz << " ) kG" << endl;
    cout << "======================================================" << endl;
}
// ------------------------------------------------------------------------

// ---------    Reset parameters and data (private)  ----------------------
void FRSWasaFieldMap::Reset()
{
    fRmin = fRmax = 0.;
    fZmin = fZmax = 0.;
    fScale = 1.;
    fBx = fBy = fBz = 0.;
}
// ------------------------------------------------------------------------

ClassImp(FRSWasaFieldMap)

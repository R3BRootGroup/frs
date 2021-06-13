#include "WASAMdc.h"
#include "FairGeoInterface.h"
#include "FairGeoLoader.h"
#include "FairGeoNode.h"
#include "FairGeoRootBuilder.h"
#include "FairRootManager.h"
#include "FairRun.h"
#include "FairRuntimeDb.h"
#include "FairVolume.h"
#include "R3BMCStack.h"
#include "TClonesArray.h"
#include "TGeoArb8.h"
#include "TGeoBBox.h"
#include "TGeoBoolNode.h"
#include "TGeoCompositeShape.h"
#include "TGeoCone.h"
#include "TGeoMCGeometry.h"
#include "TGeoManager.h"
#include "TGeoMaterial.h"
#include "TGeoMatrix.h"
#include "TGeoMedium.h"
#include "TGeoPara.h"
#include "TGeoPgon.h"
#include "TGeoShapeAssembly.h"
#include "TGeoSphere.h"
#include "TGeoTube.h"
#include "TObjArray.h"
#include "TParticle.h"
#include "TVirtualMC.h"
#include "WASAMdcPoint.h"
#include <stdlib.h>

WASAMdc::WASAMdc()
    : WASAMdc("")
{
}

WASAMdc::WASAMdc(const TString& geoFile, const TGeoTranslation& trans, const TGeoRotation& rot)
    : WASAMdc(geoFile, { trans, rot })
{
}

WASAMdc::WASAMdc(const TString& geoFile, const TGeoCombiTrans& combi)
    : R3BDetector("WASAMdc", kTRA, geoFile, combi)
    , fTraCollection(new TClonesArray("WASAMdcPoint"))
    , fPosIndex(0)
    , kGeoSaved(kFALSE)
    , flGeoPar(new TList())
{
    flGeoPar->SetName(GetName());
    ResetParameters();
}

WASAMdc::~WASAMdc()
{
    if (flGeoPar)
    {
        delete flGeoPar;
    }
    if (fTraCollection)
    {
        fTraCollection->Delete();
        delete fTraCollection;
    }
}

void WASAMdc::Initialize()
{
    FairDetector::Initialize();

    LOG(INFO) << "WASAMdc: initialisation";
    // LOG(DEBUG) << "WASAMdc: Sens. Vol. (McId) " << gMC->VolId("TraLog") ;

    Char_t buffer[126];
    for (Int_t i = 0; i < 9; i++)
    {
        sprintf(buffer, "ME0%i", i + 1);
        LOG(DEBUG) << "-I- R3BRpc: Layer   : " << i << " connected to (McId) ---> " << buffer << "  "
                   << gMC->VolId(buffer);
        fLayer[i] = gMC->VolId(buffer);
    }
    for (Int_t i = 9; i < 17; i++)
    {
        sprintf(buffer, "ME%i", i + 1);
        LOG(DEBUG) << "-I- R3BRpc: Layer   : " << i << " connected to (McId) ---> " << buffer << "  "
                   << gMC->VolId(buffer);
        fLayer[i] = gMC->VolId(buffer);
    }
}

void WASAMdc::SetSpecialPhysicsCuts() { LOG(INFO) << "-I- WASAMdc: Adding customized Physics cut ... "; }

// -----   Public method ProcessHits  --------------------------------------
Bool_t WASAMdc::ProcessHits(FairVolume* vol)
{
    if (gMC->IsTrackEntering())
    {
        fELoss = 0.;
        fTime = gMC->TrackTime() * 1.0e09;
        fLength = gMC->TrackLength();
        gMC->TrackPosition(fPosIn);
        gMC->TrackMomentum(fMomIn);
    }

    // Sum energy loss for all steps in the active volume
    fELoss += gMC->Edep();

    // Set additional parameters at exit of active volume. Create WASAMdcPoint.
    if (gMC->IsTrackExiting() || gMC->IsTrackStop() || gMC->IsTrackDisappeared())
    {

        Int_t cp1 = -1;
        Int_t volId1 = -1;
        volId1 = gMC->CurrentVolID(cp1);

        fTrackID = gMC->GetStack()->GetCurrentTrackNumber();
        fVolumeID = GetLayerType(volId1);
        fDetCopyID = vol->getCopyNo();
        gMC->TrackPosition(fPosOut);
        gMC->TrackMomentum(fMomOut);
        if (fELoss == 0.)
            return kFALSE;

 /*       if (gMC->IsTrackExiting())
        {
            const Double_t* oldpos;
            const Double_t* olddirection;
            Double_t newpos[3];
            Double_t newdirection[3];
            Double_t safety;

            gGeoManager->FindNode(fPosOut.X(), fPosOut.Y(), fPosOut.Z());
            oldpos = gGeoManager->GetCurrentPoint();
            olddirection = gGeoManager->GetCurrentDirection();

            for (Int_t i = 0; i < 3; i++)
            {
                newdirection[i] = -1 * olddirection[i];
            }

            gGeoManager->SetCurrentDirection(newdirection);
            //   TGeoNode *bla = gGeoManager->FindNextBoundary(2);
            safety = gGeoManager->GetSafeDistance();

            gGeoManager->SetCurrentDirection(-newdirection[0], -newdirection[1], -newdirection[2]);

            for (Int_t i = 0; i < 3; i++)
            {
                newpos[i] = oldpos[i] - (3 * safety * olddirection[i]);
            }

            fPosOut.SetX(newpos[0]);
            fPosOut.SetY(newpos[1]);
            fPosOut.SetZ(newpos[2]);
        }
*/
        AddHit(fTrackID,
               fVolumeID,
               fDetCopyID,
               TVector3(fPosIn.X(), fPosIn.Y(), fPosIn.Z()),
               TVector3(fPosOut.X(), fPosOut.Y(), fPosOut.Z()),
               TVector3(fMomIn.Px(), fMomIn.Py(), fMomIn.Pz()),
               TVector3(fMomOut.Px(), fMomOut.Py(), fMomOut.Pz()),
               fTime,
               fLength,
               fELoss);

        // Increment number of TraPoints for this track
        R3BStack* stack = (R3BStack*)gMC->GetStack();
        stack->AddPoint(kTRA);

        ResetParameters();
    }

    return kTRUE;
}

// -----   Public method EndOfEvent   -----------------------------------------
void WASAMdc::BeginEvent() {}

// -----   Public method EndOfEvent   -----------------------------------------
void WASAMdc::EndOfEvent()
{
    if (fVerboseLevel)
        Print();
    fTraCollection->Clear();

    ResetParameters();
}
// ----------------------------------------------------------------------------

// -----   Public method Register   -------------------------------------------
void WASAMdc::Register() { FairRootManager::Instance()->Register("MdcPoint", GetName(), fTraCollection, kTRUE); }
// ----------------------------------------------------------------------------

// -----   Public method GetCollection   --------------------------------------
TClonesArray* WASAMdc::GetCollection(Int_t iColl) const
{
    if (iColl == 0)
        return fTraCollection;
    else
        return NULL;
}
// ----------------------------------------------------------------------------

// -----   Public method Print   ----------------------------------------------
void WASAMdc::Print(Option_t* option) const
{
    Int_t nHits = fTraCollection->GetEntriesFast();
    LOG(INFO) << "WASAMdc: " << nHits << " points registered in this event";
}
// ----------------------------------------------------------------------------

// -----   Public method Reset   ----------------------------------------------
void WASAMdc::Reset()
{
    fTraCollection->Clear();
    ResetParameters();
}
// ----------------------------------------------------------------------------

// -----   Public method CopyClones   -----------------------------------------
void WASAMdc::CopyClones(TClonesArray* cl1, TClonesArray* cl2, Int_t offset)
{
    Int_t nEntries = cl1->GetEntriesFast();
    LOG(INFO) << "WASAMdc: " << nEntries << " entries to add";
    TClonesArray& clref = *cl2;
    WASAMdcPoint* oldpoint = NULL;
    for (Int_t i = 0; i < nEntries; i++)
    {
        oldpoint = (WASAMdcPoint*)cl1->At(i);
        Int_t index = oldpoint->GetTrackID() + offset;
        oldpoint->SetTrackID(index);
        new (clref[fPosIndex]) WASAMdcPoint(*oldpoint);
        fPosIndex++;
    }
    LOG(INFO) << "WASAMdc: " << cl2->GetEntriesFast() << " merged entries";
}

// -----   Private method AddHit   --------------------------------------------
WASAMdcPoint* WASAMdc::AddHit(Int_t trackID,
                              Int_t detID,
                              Int_t detCopyID, // added by Marc
                              TVector3 posIn,
                              TVector3 posOut,
                              TVector3 momIn,
                              TVector3 momOut,
                              Double_t time,
                              Double_t length,
                              Double_t eLoss)
{
    TClonesArray& clref = *fTraCollection;
    Int_t size = clref.GetEntriesFast();
    if (fVerboseLevel > 1)
        LOG(INFO) << "WASAMdc: Adding Point at (" << posIn.X() << ", " << posIn.Y() << ", " << posIn.Z()
                  << ") cm,  detector " << detID << ", track " << trackID << ", energy loss " << eLoss * 1e06 << " keV";
    return new (clref[size]) WASAMdcPoint(trackID, detID, detCopyID, posIn, posOut, momIn, momOut, time, length, eLoss);
}

Bool_t WASAMdc::CheckIfSensitive(std::string name)
{
    if (TString(name).Contains("ME"))
    {
        return kTRUE;
    }
    return kFALSE;
}

ClassImp(WASAMdc)

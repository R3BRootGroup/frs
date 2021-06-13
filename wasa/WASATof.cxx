// -------------------------------------------------------------------------
// -----                      WASATof file                             -----
// -----                  Created 30/09/18 by J.L. Rodriguez           -----
// -------------------------------------------------------------------------

#include "WASATof.h"
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
#include "TGeoMCGeometry.h"
#include "TGeoManager.h"
#include "TObjArray.h"
#include "TParticle.h"
#include "TVirtualMC.h"
#include "WASAGeoTof.h"
#include "WASAGeoTofPar.h"
#include "WASATofPoint.h"
#include <stdlib.h>

WASATof::WASATof()
    : WASATof("")
{
}

WASATof::WASATof(const TString& geoFile, const TGeoTranslation& trans, const TGeoRotation& rot)
    : WASATof(geoFile, { trans, rot })
{
}

WASATof::WASATof(const TString& geoFile, const TGeoCombiTrans& combi)
    : R3BDetector("kTofPoint", kTOF, geoFile, combi)
    , fTofCollection(new TClonesArray("WASATofPoint"))
    , fPosIndex(0)
    , kGeoSaved(kFALSE)
    , flGeoPar(new TList())
{
    flGeoPar->SetName(GetName());
    ResetParameters();
}

WASATof::~WASATof()
{
    if (flGeoPar)
    {
        delete flGeoPar;
    }
    if (fTofCollection)
    {
        fTofCollection->Delete();
        delete fTofCollection;
    }
}

void WASATof::Initialize()
{
    FairDetector::Initialize();
    LOG(INFO) << "WASATof: initialisation";
    //LOG(DEBUG) << "WASATof: Sci. Vol. (McId) " << gMC->VolId("WASATOFLog");
}

void WASATof::SetSpecialPhysicsCuts()
{
    LOG(INFO) << "WASATof: Adding customized Physics cut ... ";
}

// -----   Public method ProcessHits  --------------------------------------
Bool_t WASATof::ProcessHits(FairVolume* vol)
{
    // Simple Det PLane
    if (gMC->IsTrackEntering())
    {
        fELoss = 0.;
        fTime_in = gMC->TrackTime() * 1.0e09;
        fLength_in = gMC->TrackLength();
        gMC->TrackPosition(fPosIn);
        gMC->TrackMomentum(fMomIn);
    }

    // Sum energy loss for all steps in the active volume
    fELoss += gMC->Edep();

    // Set additional parameters at exit of active volume. Create WASATofPoint.
    if (gMC->IsTrackExiting() || gMC->IsTrackStop() || gMC->IsTrackDisappeared())
    {
        fTrackID = gMC->GetStack()->GetCurrentTrackNumber();
        fVolumeID = vol->getMCid();
        fDetCopyID = vol->getCopyNo();
        gMC->TrackPosition(fPosOut);
        gMC->TrackMomentum(fMomOut);
        if (fELoss == 0.)
          return kFALSE;

        fTime_out = gMC->TrackTime() * 1.0e09; // also in case particle is stopped in detector, or decays...
        fLength_out = gMC->TrackLength();
        fTime = (fTime_out + fTime_in) / 2.;
        fLength = (fLength_out + fLength_in) / 2.;

        if (gMC->IsTrackExiting())
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

        AddHit(fTrackID,
               fVolumeID,
               fDetCopyID,
               TVector3(fPosIn.X(), fPosIn.Y(), fPosIn.Z()),
               TVector3(fPosOut.X(), fPosOut.Y(), fPosOut.Z()),
               TVector3(fMomIn.Px(), fMomIn.Py(), fMomIn.Pz()),
               TVector3(fMomOut.Px(), fMomOut.Py(), fMomOut.Pz()),
               fTime,
               fLength,
               fELoss,
               gMC->TrackPid());

        // Increment number of TofPoints for this track
        R3BStack* stack = (R3BStack*)gMC->GetStack();
        stack->AddPoint(kTOF);

        ResetParameters();
    }

    return kTRUE;
}

// -----   Public method BeginEvent   -----------------------------------------
void WASATof::BeginEvent() {}

// -----   Public method EndOfEvent   -----------------------------------------
void WASATof::EndOfEvent()
{
    if (fVerboseLevel)
        Print();
    fTofCollection->Clear();

    ResetParameters();
}
// ----------------------------------------------------------------------------

// -----   Public method Register   -------------------------------------------
void WASATof::Register() { FairRootManager::Instance()->Register("WasaTofPoint", GetName(), fTofCollection, kTRUE); }
// ----------------------------------------------------------------------------

// -----   Public method GetCollection   --------------------------------------
TClonesArray* WASATof::GetCollection(Int_t iColl) const
{
    if (iColl == 0)
        return fTofCollection;
    else
        return NULL;
}
// ----------------------------------------------------------------------------

// -----   Public method Print   ----------------------------------------------
void WASATof::Print(Option_t* option) const
{
    Int_t nHits = fTofCollection->GetEntriesFast();
    LOG(INFO) << "WASATof: " << nHits << " points registered in this event";
}
// ----------------------------------------------------------------------------

// -----   Public method Reset   ----------------------------------------------
void WASATof::Reset()
{
    fTofCollection->Clear();
    ResetParameters();
}
// ----------------------------------------------------------------------------

// -----   Public method CopyClones   -----------------------------------------
void WASATof::CopyClones(TClonesArray* cl1, TClonesArray* cl2, Int_t offset)
{
    Int_t nEntries = cl1->GetEntriesFast();
    LOG(INFO) << "WASATof: " << nEntries << " entries to add";
    TClonesArray& clref = *cl2;
    WASATofPoint* oldpoint = NULL;
    for (Int_t i = 0; i < nEntries; i++)
    {
        oldpoint = (WASATofPoint*)cl1->At(i);
        Int_t index = oldpoint->GetTrackID() + offset;
        oldpoint->SetTrackID(index);
        new (clref[fPosIndex]) WASATofPoint(*oldpoint);
        fPosIndex++;
    }
    LOG(INFO) << "WASATof: " << cl2->GetEntriesFast() << " merged entries";
}

// -----   Private method AddHit   --------------------------------------------
WASATofPoint* WASATof::AddHit(Int_t trackID,
                              Int_t detID,
                              Int_t CopyID,
                              TVector3 posIn,
                              TVector3 posOut,
                              TVector3 momIn,
                              TVector3 momOut,
                              Double_t time,
                              Double_t length,
                              Double_t eLoss,
                              Int_t pdgcode)
{
    TClonesArray& clref = *fTofCollection;
    Int_t size = clref.GetEntriesFast();
    if (fVerboseLevel > 1)
        LOG(INFO) << "WASATof: Adding Point at (" << posIn.X() << ", " << posIn.Y() << ", " << posIn.Z()
                  << ") cm,  detector " << detID << ", copy " << CopyID << ", track " << trackID << ", energy loss "
                  << eLoss * 1e06 << " keV";
    return new (clref[size]) WASATofPoint(trackID, detID, CopyID, posIn, posOut, momIn, momOut, time, length, eLoss,
                                         pdgcode);
}

Bool_t WASATof::CheckIfSensitive(std::string name)
{
    if (TString(name).Contains("WASATOFLog"))
    {
        //LOG(INFO) << "Found Wasa-ToF geometry from ROOT file: " << name;
        return kTRUE;
    }
    return kFALSE;
}

ClassImp(WASATof)

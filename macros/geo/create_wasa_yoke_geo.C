//
//   ----- General Macro for WASA simulation
//
//         Author: Jose Luis <joseluis.rodriguez.sanchez@usc.es>
//
//         Last Update: 25/05/19 (Jose Luis)
//
//         Comments:
//   

#include <iomanip>
#include <iostream>
#include "TGeoManager.h"
#include "TMath.h"

#include "geometryVolume.C"

// Create Matrix Unity
TGeoRotation *fGlobalRot = new TGeoRotation();

// Create a null translation
TGeoTranslation *fGlobalTrans = new TGeoTranslation();
TGeoRotation *fRefRot = NULL;

TGeoManager*  gGeoMan = NULL;

Double_t fThetaX = 0.;
Double_t fThetaY = 0.;
Double_t fThetaZ = 0.;
Double_t fPhi   = 0.;
Double_t fTheta = 0.;
Double_t fPsi   = 0.;
Double_t fX = 0.;
Double_t fY = 0.;
Double_t fZ = 0.;
Bool_t fLocalTrans = kFALSE;

TGeoCombiTrans* GetGlobalPosition(TGeoCombiTrans *fRef);

void create_wasa_yoke_geo(const char* geoTag="wasayoke")
{
// --------------------------------------------------------------------------
// Configurable geometry for the WASA Detectors.
// Use this macro to create root files with the different configurations 
// and positions/angles of the detectors.
//
// Execute macro:  root -l
//                 .L create_wasa_yoke_geo.C
//                 create_wasa_yoke_geo("v0")
// --------------------------------------------------------------------------

  fGlobalTrans->SetTranslation(0.0,0.0,0.0);

  // -------   Load media from media file   -----------------------------------
  FairGeoLoader*    geoLoad = new FairGeoLoader("TGeo","FairGeoLoader");
  FairGeoInterface* geoFace = geoLoad->getGeoInterface();
  TString geoPath = gSystem->Getenv("VMCWORKDIR");
  TString medFile = geoPath + "/geometry/media_r3b.geo";
  geoFace->setMediaFile(medFile);
  geoFace->readMedia();
  gGeoMan = gGeoManager;
  // --------------------------------------------------------------------------



  // -------   Geometry file name (output)   ----------------------------------
  TString geoFileName = geoPath + "/frs/geometry/wasa_yoke_";
  geoFileName = geoFileName + geoTag + ".geo.root";
  // --------------------------------------------------------------------------

  // -----------------   Get and create the required media    -----------------
  FairGeoMedia*   geoMedia = geoFace->getMedia();
  FairGeoBuilder* geoBuild = geoLoad->getGeoBuilder();

  FairGeoMedium* mAir      = geoMedia->getMedium("Air");
  if ( ! mAir ) Fatal("Main", "FairMedium Air not found");
  geoBuild->createMedium(mAir);
  TGeoMedium* pMedAir = gGeoMan->GetMedium("Air");
  if ( ! pMedAir ) Fatal("Main", "Medium Air not found");

  FairGeoMedium* mVac      = geoMedia->getMedium("vacuum");
  if ( ! mVac ) Fatal("Main", "FairMedium vacuum not found");
  geoBuild->createMedium(mVac);
  TGeoMedium* pMedVac = gGeoMan->GetMedium("vacuum");
  if ( ! pMedVac ) Fatal("Main", "Medium vacuum not found");
  
  FairGeoMedium* mSi      = geoMedia->getMedium("silicon");
  if ( ! mSi ) Fatal("Main", "FairMedium silicon not found");
  geoBuild->createMedium(mSi);
  TGeoMedium* pMedSi = gGeoMan->GetMedium("silicon");
  if ( ! pMedSi ) Fatal("Main", "Medium silicon not found");

  FairGeoMedium* mCopper      = geoMedia->getMedium("copper");
  if ( ! mCopper ) Fatal("Main", "FairMedium copper not found");
  geoBuild->createMedium(mCopper);
  TGeoMedium* pMedCu = gGeoMan->GetMedium("copper");
  if ( ! pMedCu ) Fatal("Main", "Medium copper not found");
  
  FairGeoMedium* mAl      = geoMedia->getMedium("aluminium");
  if ( ! mAl ) Fatal("Main", "FairMedium aluminium not found");
  geoBuild->createMedium(mAl);
  TGeoMedium* pMedAl = gGeoMan->GetMedium("aluminium");
  if ( ! pMedAl ) Fatal("Main", "Medium aluminium not found");

  FairGeoMedium* mFe      = geoMedia->getMedium("iron");
  if ( ! mFe ) Fatal("Main", "FairMedium iron not found");
  geoBuild->createMedium(mFe);
  TGeoMedium* pMedFe = gGeoMan->GetMedium("iron");
  if ( ! pMedFe ) Fatal("Main", "Medium iron not found");

  FairGeoMedium* mSci      = geoMedia->getMedium("plasticForTOF");
  if ( ! mSci ) Fatal("Main", "FairMedium Sci not found");
  geoBuild->createMedium(mSci);
  TGeoMedium* pMedSci = gGeoMan->GetMedium("plasticForTOF");
  if ( ! pMedSci ) Fatal("Main", "Medium Sci not found");


  // --------------------------------------------------------------------------



  // --------------   Create geometry and top volume  -------------------------
  gGeoMan = (TGeoManager*)gROOT->FindObject("FAIRGeom");
  gGeoMan->SetName("WASAYOKEgeom");
  TGeoVolume* top = new TGeoVolumeAssembly("TOP");
  gGeoMan->SetTopVolume(top);
  // --------------------------------------------------------------------------



	// Fill Chamber: Vacuum or Air. Needed still: an external call interface for choosing which.
	TGeoMedium * pMedFill=pMedVac;
  //pMedFill = new TGeoMedium("Fill_Air", numed,pMat2, par);
  //pMedFill = (TGeoMedium*) pMedAir->Clone();
  //pMedFill->SetName("Fill_Air");
//  pMedFill = (TGeoMedium*) pMedVac->Clone();
//  pMedFill->SetName("Fill_Vacuum");
  

	// out-of-file geometry definition
	Double_t dx,dy,dz;
	Double_t rmin, rmax, rmin1, rmax1, rmin2, rmax2;
	Double_t thx, phx, thy, phy, thz, phz;
	Double_t  phi1, phi2;
	Double_t tx,ty,tz;
  
	TGeoRotation * zeroRot = new TGeoRotation; //zero rotation
	TGeoCombiTrans * tZero = new TGeoCombiTrans("tZero", 0., 0., 0., zeroRot);
	tZero->RegisterYourself();

  //-------------------------------------------------------------------
  
  // Shape: World type: TGeoBBox
  TGeoVolume* pWorld = gGeoManager->GetTopVolume();
  pWorld->SetVisLeaves(kFALSE);


  /************ Assembling everything together ****************/
  TGeoVolume *WasaYoke = new TGeoVolumeAssembly("YOKE_WASA"); 

  // Solenoid
  TGeoVolume* INNER_ = gGeoManager->MakeTube("INNER", pMedVac, 0., 31.5, 27.75);
  /*
  TGeoVolume* SOL_ = gGeoManager->MakeTube("SOL", med2, 24.5, 31.5, 27.75);
  TGeoVolume* SOC0 = gGeoManager->MakeTube("SOC0", med34, 3.9, 4.1, 2.5);
  SOC0->SetLineColor(kSpring-2);
  TGeoVolume* SOC1 = gGeoManager->MakeTube("SOC1", med35, 3.9, 4.1, 12);
  SOC1->SetLineColor(kSpring-2);
*/
  // Yoke
  TGeoVolume* IRC_ = gGeoManager->MakePcon("IRC", pMedFe, 0, 360, 14);
  //((TGeoPcon*)IRC_->GetShape())->DefineSection(0, -61.8, 9, 37);
  //((TGeoPcon*)IRC_->GetShape())->DefineSection(1, -51.8, 9, 59.5);
  ((TGeoPcon*)IRC_->GetShape())->DefineSection(0, -61.8, 33., 37);
  ((TGeoPcon*)IRC_->GetShape())->DefineSection(1, -51.8, 33., 59.5);
  ((TGeoPcon*)IRC_->GetShape())->DefineSection(2, -51.8, 37, 59.5);
  ((TGeoPcon*)IRC_->GetShape())->DefineSection(3, -42, 52.5, 68);
  ((TGeoPcon*)IRC_->GetShape())->DefineSection(4, -35.5, 60, 70);
  ((TGeoPcon*)IRC_->GetShape())->DefineSection(5, -20, 66, 76);
  ((TGeoPcon*)IRC_->GetShape())->DefineSection(6, 25, 66, 76);
  ((TGeoPcon*)IRC_->GetShape())->DefineSection(7, 41, 63, 73.5);
  ((TGeoPcon*)IRC_->GetShape())->DefineSection(8, 47.5, 57, 72.5);
  ((TGeoPcon*)IRC_->GetShape())->DefineSection(9, 55.5, 47.5, 64.5);
  ((TGeoPcon*)IRC_->GetShape())->DefineSection(10, 57.5, 40, 62.5);
  ((TGeoPcon*)IRC_->GetShape())->DefineSection(11, 57.5, 19.5, 62.5);
  ((TGeoPcon*)IRC_->GetShape())->DefineSection(12, 59.5, 19.5, 60.5);
  ((TGeoPcon*)IRC_->GetShape())->DefineSection(13, 70.5, 23, 47);
  IRC_->SetLineColor(kBlue);

  TGeoRotation* rot255 = new TGeoRotation("rot255", 90, 0, 90, 90, 0, 0);
  WasaYoke->AddNode(IRC_, 1, rot255);

  TGeoRotation *rotg = new TGeoRotation();
  rotg->RotateX(0.);
  rotg->RotateY(0.);
  rotg->RotateZ(0.);
  dx=tx=0.0;
  dy=ty=0.0;
  dz=tz=0.0;
  
  TGeoCombiTrans *t0 = new TGeoCombiTrans(tx,ty,tz,rotg);
  pWorld->AddNode(WasaYoke, 1, GetGlobalPosition(t0));
   
  // ---------------   Finish   -----------------------------------------------
  gGeoMan->CloseGeometry();
  gGeoMan->CheckOverlaps(0.001);
  gGeoMan->PrintOverlaps();
  gGeoMan->Test();

  TFile* geoFile = new TFile(geoFileName, "RECREATE");
  top->Write();
  geoFile->Close();

  std::cout << "Creating geometry: "<<geoFileName<< std::endl;

  // --------------------------------------------------------------------------
}



TGeoCombiTrans* GetGlobalPosition(TGeoCombiTrans *fRef)
{
  if (fLocalTrans == kTRUE ) {
    
    if ( ( fThetaX == 0 )  && ( fThetaY==0 )  && ( fThetaZ == 0 )
	 &&
	 ( fX == 0 ) && ( fY == 0 ) && ( fZ == 0 )
	 )  return fRef;
    
    
    // X axis
    Double_t xAxis[3] = { 1. , 0. , 0. };
    Double_t yAxis[3] = { 0. , 1. , 0. };
    Double_t zAxis[3] = { 0. , 0. , 1. };
    // Reference Rotation
    fRefRot = fRef->GetRotation();
    
    if (fRefRot) {
      Double_t mX[3] = {0.,0.,0.};
      Double_t mY[3] = {0.,0.,0.};
      Double_t mZ[3] = {0.,0.,0.};
      
      fRefRot->LocalToMasterVect(xAxis,mX);
      fRefRot->LocalToMasterVect(yAxis,mY);
      fRefRot->LocalToMasterVect(zAxis,mZ);
      
      Double_t a[4]={ mX[0],mX[1],mX[2], fThetaX };
      Double_t b[4]={ mY[0],mY[1],mY[2], fThetaY };
      Double_t c[4]={ mZ[0],mZ[1],mZ[2], fThetaZ };
      
      ROOT::Math::AxisAngle aX(a,a+4);
      ROOT::Math::AxisAngle aY(b,b+4);
      ROOT::Math::AxisAngle aZ(c,c+4);
      
      ROOT::Math::Rotation3D fMatX( aX );
      ROOT::Math::Rotation3D fMatY( aY );
      ROOT::Math::Rotation3D fMatZ( aZ );
      
      ROOT::Math::Rotation3D  fRotXYZ = (fMatZ * (fMatY * fMatX));
      
      //cout << fRotXYZ << endl;
      
      Double_t fRotable[9]={0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};
      fRotXYZ.GetComponents(
			    fRotable[0],fRotable[3],fRotable[6],
			    fRotable[1],fRotable[4],fRotable[7],
			    fRotable[2],fRotable[5],fRotable[8]
			    );
      TGeoRotation *pRot = new TGeoRotation();
      pRot->SetMatrix(fRotable);
      TGeoCombiTrans *pTmp = new TGeoCombiTrans(*fGlobalTrans,*pRot);
      
      // ne peut pas etre applique ici
      // il faut differencier trans et rot dans la multi.
      TGeoRotation rot_id;
      rot_id.SetAngles(0.0,0.0,0.0);
      
      TGeoCombiTrans c1;
      c1.SetRotation(rot_id);
      const Double_t *t = pTmp->GetTranslation();
      c1.SetTranslation(t[0],t[1],t[2]);
      
      TGeoCombiTrans c2;
      c2.SetRotation(rot_id);
      const Double_t *tt = fRefRot->GetTranslation();
      c2.SetTranslation(tt[0],tt[1],tt[2]);
      
      TGeoCombiTrans cc = c1 * c2 ;
      
      TGeoCombiTrans c3;
      c3.SetRotation(pTmp->GetRotation());
      TGeoCombiTrans c4;
      c4.SetRotation(fRefRot);
      
      TGeoCombiTrans ccc = c3 * c4;
      
      TGeoCombiTrans pGlobal;
      pGlobal.SetRotation(ccc.GetRotation());
      const Double_t *allt = cc.GetTranslation();
      pGlobal.SetTranslation(allt[0],allt[1],allt[2]);
      
      return  ( new TGeoCombiTrans( pGlobal ) );
      
    }else{
      
      cout << "-E- R3BDetector::GetGlobalPosition() \
	      No. Ref. Transformation defined ! " << endl;
      cout << "-E- R3BDetector::GetGlobalPosition() \
	      cannot create Local Transformation " << endl;
      return NULL;
    } //! fRefRot
    
  } else {
    // Lab Transf.
    if ( ( fPhi == 0 )  && ( fTheta==0 )  && ( fPsi == 0 )
	 &&
	 ( fX == 0 ) && ( fY == 0 ) && ( fZ == 0 )
	 )  return fRef;
    
    
    return ( new TGeoCombiTrans(*fGlobalTrans,*fGlobalRot) );
    
  }
}


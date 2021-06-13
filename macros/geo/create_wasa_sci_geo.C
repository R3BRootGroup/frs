//
//   ----- General Macro for WASA simulation
//
//         Author: Jose Luis <joseluis.rodriguez.sanchez@usc.es>
//
//         Last Update: 25/09/18 (Jose Luis)
//
//         Comments:
//

#include "TGeoManager.h"
#include "TMath.h"
#include <iomanip>
#include <iostream>

#include "geometryVolume.C"

// Create Matrix Unity
TGeoRotation* fGlobalRot = new TGeoRotation();

// Create a null translation
TGeoTranslation* fGlobalTrans = new TGeoTranslation();
TGeoRotation* fRefRot = NULL;

TGeoManager* gGeoMan = NULL;

Double_t fThetaX = 0.;
Double_t fThetaY = 0.;
Double_t fThetaZ = 0.;
Double_t fPhi = 0.;
Double_t fTheta = 0.;
Double_t fPsi = 0.;
Double_t fX = 0.;
Double_t fY = 0.;
Double_t fZ = 0.;
Bool_t fLocalTrans = kFALSE;

TGeoCombiTrans* GetGlobalPosition(TGeoCombiTrans* fRef);

void create_wasa_sci_geo(const char* geoTag = "v2020")
{
    // --------------------------------------------------------------------------
    // Configurable geometry for the WASA Detectors.
    // Use this macro to create root files with the different configurations
    // and positions/angles of the detectors.
    //
    // Execute macro:  root -l
    //                 .L create_wasa_geo.C
    //                 create_wasa_geo("v0")
    // --------------------------------------------------------------------------

    fGlobalTrans->SetTranslation(0.0, 0.0, 0.0);

    // -------   Load media from media file   -----------------------------------
    FairGeoLoader* geoLoad = new FairGeoLoader("TGeo", "FairGeoLoader");
    FairGeoInterface* geoFace = geoLoad->getGeoInterface();
    TString geoPath = gSystem->Getenv("VMCWORKDIR");
    TString medFile = geoPath + "/geometry/media_r3b.geo";
    geoFace->setMediaFile(medFile);
    geoFace->readMedia();
    gGeoMan = gGeoManager;
    // --------------------------------------------------------------------------

    // -------   Geometry file name (output)   ----------------------------------
    TString geoFileName = geoPath + "/frs/geometry/wasa_sci_";
    geoFileName = geoFileName + geoTag + ".geo.root";
    // --------------------------------------------------------------------------

    // -----------------   Get and create the required media    -----------------
    FairGeoMedia* geoMedia = geoFace->getMedia();
    FairGeoBuilder* geoBuild = geoLoad->getGeoBuilder();

    FairGeoMedium* mAir = geoMedia->getMedium("Air");
    if (!mAir)
        Fatal("Main", "FairMedium Air not found");
    geoBuild->createMedium(mAir);
    TGeoMedium* pMedAir = gGeoMan->GetMedium("Air");
    if (!pMedAir)
        Fatal("Main", "Medium Air not found");

    FairGeoMedium* mVac = geoMedia->getMedium("vacuum");
    if (!mVac)
        Fatal("Main", "FairMedium vacuum not found");
    geoBuild->createMedium(mVac);
    TGeoMedium* pMedVac = gGeoMan->GetMedium("vacuum");
    if (!pMedVac)
        Fatal("Main", "Medium vacuum not found");

    FairGeoMedium* mSi = geoMedia->getMedium("silicon");
    if (!mSi)
        Fatal("Main", "FairMedium silicon not found");
    geoBuild->createMedium(mSi);
    TGeoMedium* pMedSi = gGeoMan->GetMedium("silicon");
    if (!pMedSi)
        Fatal("Main", "Medium silicon not found");

    FairGeoMedium* mCopper = geoMedia->getMedium("copper");
    if (!mCopper)
        Fatal("Main", "FairMedium copper not found");
    geoBuild->createMedium(mCopper);
    TGeoMedium* pMedCu = gGeoMan->GetMedium("copper");
    if (!pMedCu)
        Fatal("Main", "Medium copper not found");

    FairGeoMedium* mAl = geoMedia->getMedium("aluminium");
    if (!mAl)
        Fatal("Main", "FairMedium aluminium not found");
    geoBuild->createMedium(mAl);
    TGeoMedium* pMedAl = gGeoMan->GetMedium("aluminium");
    if (!pMedAl)
        Fatal("Main", "Medium aluminium not found");

    FairGeoMedium* mFe = geoMedia->getMedium("iron");
    if (!mFe)
        Fatal("Main", "FairMedium iron not found");
    geoBuild->createMedium(mFe);
    TGeoMedium* pMedFe = gGeoMan->GetMedium("iron");
    if (!pMedFe)
        Fatal("Main", "Medium iron not found");

    FairGeoMedium* mSci = geoMedia->getMedium("plasticForTOF");
    if (!mSci)
        Fatal("Main", "FairMedium Sci not found");
    geoBuild->createMedium(mSci);
    TGeoMedium* pMedSci = gGeoMan->GetMedium("plasticForTOF");
    if (!pMedSci)
        Fatal("Main", "Medium Sci not found");

    // --------------------------------------------------------------------------

    // --------------   Create geometry and top volume  -------------------------
    gGeoMan = (TGeoManager*)gROOT->FindObject("FAIRGeom");
    gGeoMan->SetName("WASAgeom");
    TGeoVolume* top = new TGeoVolumeAssembly("TOP");
    gGeoMan->SetTopVolume(top);
    // --------------------------------------------------------------------------

    // Fill Chamber: Vacuum or Air. Needed still: an external call interface for choosing which.
    TGeoMedium* pMedFill = pMedVac;
    // pMedFill = new TGeoMedium("Fill_Air", numed,pMat2, par);
    // pMedFill = (TGeoMedium*) pMedAir->Clone();
    // pMedFill->SetName("Fill_Air");
    //  pMedFill = (TGeoMedium*) pMedVac->Clone();
    //  pMedFill->SetName("Fill_Vacuum");

    // out-of-file geometry definition
    Double_t dx, dy, dz;
    Double_t rmin, rmax, rmin1, rmax1, rmin2, rmax2;
    Double_t thx, phx, thy, phy, thz, phz;
    Double_t phi1, phi2;
    Double_t tx, ty, tz;

    TGeoRotation* zeroRot = new TGeoRotation; // zero rotation
    TGeoCombiTrans* tZero = new TGeoCombiTrans("tZero", 0., 0., 0., zeroRot);
    tZero->RegisterYourself();

    //-------------------------------------------------------------------

    // Shape: World type: TGeoBBox
    TGeoVolume* pWorld = gGeoManager->GetTopVolume();
    pWorld->SetVisLeaves(kFALSE);

    TGeoRotation* rot1077 = new TGeoRotation("rot1077", 180, 0, 90, 97.50001, 90, 7.500001);
    TGeoRotation* rot1078 = new TGeoRotation("rot1078", 180, 0, 90, 105, 90, 14.99996);
    TGeoRotation* rot1079 = new TGeoRotation("rot1079", 180, 0, 90, 112.5002, 90, 22.49997);
    TGeoRotation* rot1080 = new TGeoRotation("rot1080", 180, 0, 90, 119.9999, 90, 29.99998);
    TGeoRotation* rot1081 = new TGeoRotation("rot1081", 180, 0, 90, 127.5001, 90, 37.50006);
    TGeoRotation* rot1082 = new TGeoRotation("rot1082", 180, 0, 90, 135, 90, 45);
    TGeoRotation* rot1083 = new TGeoRotation("rot1083", 180, 0, 90, 142.5, 90, 52.49986);
    TGeoRotation* rot1084 = new TGeoRotation("rot1084", 180, 0, 90, 150.0001, 90, 60.00002);
    TGeoRotation* rot1085 = new TGeoRotation("rot1085", 180, 0, 90, 157.4999, 90, 67.50003);
    TGeoRotation* rot1086 = new TGeoRotation("rot1086", 180, 0, 90, 165, 90, 74.99993);
    TGeoRotation* rot1087 = new TGeoRotation("rot1087", 180, 0, 90, 172.4998, 90, 82.50002);
    TGeoRotation* rot1088 = new TGeoRotation("rot1088", 180, 0, 90, 180.0001, 90, 90);
    TGeoRotation* rot1089 = new TGeoRotation("rot1089", 180, 0, 90, 187.5, 90, 97.49998);
    TGeoRotation* rot1090 = new TGeoRotation("rot1090", 180, 0, 90, 195, 90, 105);
    TGeoRotation* rot1091 = new TGeoRotation("rot1091", 180, 0, 90, 202.5002, 90, 112.5);
    TGeoRotation* rot1092 = new TGeoRotation("rot1092", 180, 0, 90, 210, 90, 120);
    TGeoRotation* rot1093 = new TGeoRotation("rot1093", 180, 0, 90, 217.5001, 90, 127.5001);
    TGeoRotation* rot1094 = new TGeoRotation("rot1094", 180, 0, 90, 224.9999, 90, 135);
    TGeoRotation* rot1095 = new TGeoRotation("rot1095", 180, 0, 90, 232.5, 90, 142.4999);
    TGeoRotation* rot1096 = new TGeoRotation("rot1096", 180, 0, 90, 240, 90, 150);
    TGeoRotation* rot1097 = new TGeoRotation("rot1097", 180, 0, 90, 247.4999, 90, 157.4999);
    TGeoRotation* rot1098 = new TGeoRotation("rot1098", 180, 0, 90, 255, 90, 165);
    TGeoRotation* rot1099 = new TGeoRotation("rot1099", 180, 0, 90, 262.4999, 90, 172.5);
    TGeoRotation* rot1100 = new TGeoRotation("rot1100", 180, 0, 90, 270, 90, 180);
    TGeoRotation* rot1101 = new TGeoRotation("rot1101", 180, 0, 90, 277.5, 90, 187.5);
    TGeoRotation* rot1102 = new TGeoRotation("rot1102", 180, 0, 90, 285, 90, 195);
    TGeoRotation* rot1103 = new TGeoRotation("rot1103", 180, 0, 90, 292.5001, 90, 202.4999);
    TGeoRotation* rot1104 = new TGeoRotation("rot1104", 180, 0, 90, 299.9999, 90, 210.0001);
    TGeoRotation* rot1105 = new TGeoRotation("rot1105", 180, 0, 90, 307.5, 90, 217.5);
    TGeoRotation* rot1106 = new TGeoRotation("rot1106", 180, 0, 90, 315, 90, 225);
    TGeoRotation* rot1107 = new TGeoRotation("rot1107", 180, 0, 90, 322.4999, 90, 232.5);
    TGeoRotation* rot1108 = new TGeoRotation("rot1108", 180, 0, 90, 330.0001, 90, 240);
    TGeoRotation* rot1109 = new TGeoRotation("rot1109", 180, 0, 90, 337.4999, 90, 247.5);
    TGeoRotation* rot1110 = new TGeoRotation("rot1110", 180, 0, 90, 345.0002, 90, 255.0001);
    TGeoRotation* rot1111 = new TGeoRotation("rot1111", 180, 0, 90, 352.5, 90, 262.5);
    TGeoRotation* rot1112 = new TGeoRotation("rot1112", 180, 0, 90, 0, 90, 270);
    TGeoRotation* rot1113 = new TGeoRotation("rot1113", 180, 0, 90, 7.500048, 90, 277.5);
    TGeoRotation* rot1114 = new TGeoRotation("rot1114", 180, 0, 90, 14.99997, 90, 285.0001);
    TGeoRotation* rot1115 = new TGeoRotation("rot1115", 180, 0, 90, 22.50006, 90, 292.5);
    TGeoRotation* rot1116 = new TGeoRotation("rot1116", 180, 0, 90, 29.99994, 90, 300.0001);
    TGeoRotation* rot1117 = new TGeoRotation("rot1117", 180, 0, 90, 37.50002, 90, 307.5);
    TGeoRotation* rot1118 = new TGeoRotation("rot1118", 180, 0, 90, 45, 90, 315.0001);
    TGeoRotation* rot1119 = new TGeoRotation("rot1119", 180, 0, 90, 52.5001, 90, 322.5);
    TGeoRotation* rot1120 = new TGeoRotation("rot1120", 180, 0, 90, 60.00005, 90, 330.0001);
    TGeoRotation* rot1121 = new TGeoRotation("rot1121", 180, 0, 90, 67.50007, 90, 337.4999);
    TGeoRotation* rot1122 = new TGeoRotation("rot1122", 180, 0, 90, 75.00013, 90, 345);
    TGeoRotation* rot1123 = new TGeoRotation("rot1123", 180, 0, 90, 82.49995, 90, 352.5);
    TGeoRotation* rot1124 = new TGeoRotation("rot1124", 180, 0, 90, 90, 90, 0.1366038E-04);

    /************ Assembling efverything together ****************/
    TGeoVolume* WasaSci = new TGeoVolumeAssembly("SCI_WASA");

    // Plastic barrel
    TGeoVolume* PSCE = gGeoManager->MakeBox("WASATOFLog", pMedSci, 55.5 / 2., 3.8 / 2., 0.8 / 2.);
    PSCE->SetLineColor(4);

    WasaSci->AddNode(PSCE, 1, new TGeoCombiTrans(22.27613, 2.932708, 0., rot1077));
    WasaSci->AddNode(PSCE, 2, new TGeoCombiTrans(22.72984, 6.090441, 0., rot1078));
    WasaSci->AddNode(PSCE, 3, new TGeoCombiTrans(20.75805, 8.598266, 0., rot1079));
    WasaSci->AddNode(PSCE, 4, new TGeoCombiTrans(20.37901, 11.76583, 0., rot1080));
    WasaSci->AddNode(PSCE, 5, new TGeoCombiTrans(17.82534, 13.67787, 0., rot1081));
    WasaSci->AddNode(PSCE /*PSCE->GetVolume(5),*/, 6, new TGeoCombiTrans(16.63939, 16.63939, 0., rot1082));
    WasaSci->AddNode(PSCE /*PSCE->GetVolume(6),*/, 7, new TGeoCombiTrans(13.67787, 17.82534, 0., rot1083));
    WasaSci->AddNode(PSCE /*PSCE->GetVolume(7),*/, 8, new TGeoCombiTrans(11.76583, 20.37901, 0., rot1084));
    WasaSci->AddNode(PSCE /*PSCE->GetVolume(8),*/, 9, new TGeoCombiTrans(8.598266, 20.75805, 0., rot1085));
    WasaSci->AddNode(PSCE /*PSCE->GetVolume(9),*/, 10, new TGeoCombiTrans(6.090441, 22.72984, 0., rot1086));
    WasaSci->AddNode(PSCE /*PSCE->GetVolume(10)*/, 11, new TGeoCombiTrans(2.932709, 22.27613, 0., rot1087));
    WasaSci->AddNode(PSCE /*PSCE->GetVolume(12)*/, 12, new TGeoCombiTrans(0.1430511E-05, 23.53166, 0., rot1088));
    WasaSci->AddNode(PSCE /*PSCE->GetVolume(13)*/, 13, new TGeoCombiTrans(-2.932707, 22.27613, 0., rot1089));
    WasaSci->AddNode(PSCE /*PSCE->GetVolume(14)*/, 14, new TGeoCombiTrans(-6.090442, 22.72984, 0., rot1090));
    WasaSci->AddNode(PSCE /*PSCE->GetVolume(15)*/, 15, new TGeoCombiTrans(-8.598269, 20.75805, 0., rot1091));
    WasaSci->AddNode(PSCE /*PSCE->GetVolume(16)*/, 16, new TGeoCombiTrans(-11.76583, 20.37901, 0., rot1092));
    WasaSci->AddNode(PSCE /*PSCE->GetVolume(17)*/, 17, new TGeoCombiTrans(-13.67787, 17.82534, 0., rot1093));
    WasaSci->AddNode(PSCE /*PSCE->GetVolume(18)*/, 18, new TGeoCombiTrans(-16.63939, 16.63939, 0., rot1094));
    WasaSci->AddNode(PSCE /*PSCE->GetVolume(19)*/, 19, new TGeoCombiTrans(-17.82534, 13.67787, 0., rot1095));
    WasaSci->AddNode(PSCE /*PSCE->GetVolume(20)*/, 20, new TGeoCombiTrans(-20.37901, 11.76583, 0., rot1096));
    WasaSci->AddNode(PSCE /*PSCE->GetVolume(21)*/, 21, new TGeoCombiTrans(-20.75805, 8.598268, 0., rot1097));
    WasaSci->AddNode(PSCE /*PSCE->GetVolume(22)*/, 22, new TGeoCombiTrans(-22.72984, 6.090437, 0., rot1098));
    WasaSci->AddNode(PSCE /*PSCE->GetVolume(23)*/, 23, new TGeoCombiTrans(-22.27613, 2.93271, 0., rot1099));
    WasaSci->AddNode(PSCE /*PSCE->GetVolume(24)*/, 24, new TGeoCombiTrans(-23.53166, 0., 0., rot1100));
    WasaSci->AddNode(PSCE /*PSCE->GetVolume(25)*/, 25, new TGeoCombiTrans(-22.27613, -2.932705, 0., rot1101));
    WasaSci->AddNode(PSCE /*PSCE->GetVolume(26)*/, 26, new TGeoCombiTrans(-22.72984, -6.090443, 0., rot1102));
    WasaSci->AddNode(PSCE /*PSCE->GetVolume(27)*/, 27, new TGeoCombiTrans(-20.75805, -8.598267, 0., rot1103));
    WasaSci->AddNode(PSCE /*PSCE->GetVolume(28)*/, 28, new TGeoCombiTrans(-20.37901, -11.76583, 0., rot1104));
    WasaSci->AddNode(PSCE /*PSCE->GetVolume(29)*/, 29, new TGeoCombiTrans(-17.82534, -13.67787, 0., rot1105));
    WasaSci->AddNode(PSCE /*PSCE->GetVolume(30)*/, 30, new TGeoCombiTrans(-16.6394, -16.63939, 0., rot1106));
    WasaSci->AddNode(PSCE /*PSCE->GetVolume(31)*/, 31, new TGeoCombiTrans(-13.67786, -17.82534, 0., rot1107));
    WasaSci->AddNode(PSCE /*PSCE->GetVolume(32)*/, 32, new TGeoCombiTrans(-11.76583, -20.37901, 0., rot1108));
    WasaSci->AddNode(PSCE /*PSCE->GetVolume(33)*/, 33, new TGeoCombiTrans(-8.598265, -20.75805, 0., rot1109));
    WasaSci->AddNode(PSCE /*PSCE->GetVolume(34)*/, 34, new TGeoCombiTrans(-6.090433, -22.72984, 0., rot1110));
    WasaSci->AddNode(PSCE /*PSCE->GetVolume(35)*/, 35, new TGeoCombiTrans(-2.932707, -22.27613, 0., rot1111));
    WasaSci->AddNode(PSCE /*PSCE->GetVolume(37)*/, 36, new TGeoCombiTrans(0.6198883E-05, -23.53166, 0., rot1112));
    WasaSci->AddNode(PSCE /*PSCE->GetVolume(38)*/, 37, new TGeoCombiTrans(2.932709, -22.27613, 0., rot1113));
    WasaSci->AddNode(PSCE /*PSCE->GetVolume(39)*/, 38, new TGeoCombiTrans(6.090446, -22.72984, 0., rot1114));
    WasaSci->AddNode(PSCE /*PSCE->GetVolume(40)*/, 39, new TGeoCombiTrans(8.598266, -20.75805, 0., rot1115));
    WasaSci->AddNode(PSCE /*PSCE->GetVolume(41)*/, 40, new TGeoCombiTrans(11.76583, -20.37901, 0., rot1116));
    WasaSci->AddNode(PSCE /*PSCE->GetVolume(42)*/, 41, new TGeoCombiTrans(13.67786, -17.82534, 0., rot1117));
    WasaSci->AddNode(PSCE /*PSCE->GetVolume(43)*/, 42, new TGeoCombiTrans(16.6394, -16.63939, 0., rot1118));
    WasaSci->AddNode(PSCE /*PSCE->GetVolume(44)*/, 43, new TGeoCombiTrans(17.82535, -13.67786, 0., rot1119));
    WasaSci->AddNode(PSCE /*PSCE->GetVolume(45)*/, 44, new TGeoCombiTrans(20.37901, -11.76584, 0., rot1120));
    WasaSci->AddNode(PSCE /*PSCE->GetVolume(46)*/, 45, new TGeoCombiTrans(20.75805, -8.59827, 0., rot1121));
    WasaSci->AddNode(PSCE /*PSCE->GetVolume(47)*/, 46, new TGeoCombiTrans(22.72984, -6.090441, 0., rot1122));
    WasaSci->AddNode(PSCE /*PSCE->GetVolume(48)*/, 47, new TGeoCombiTrans(22.27613, -2.932703, 0., rot1123));
    WasaSci->AddNode(PSCE /*PSCE->GetVolume(49)*/, 48, new TGeoCombiTrans(23.53166, -0.1192093E-05, 0., rot1124));

    Double_t* fver = new Double_t[16];

    fver[0] = -2.6 / 2.;
    fver[1] = -0.4;

    fver[2] = -2.6 / 2.;
    fver[3] = 0.4;

    fver[4] = 2.6 / 2.;
    fver[5] = 0.4;

    fver[6] = 2.6 / 2.;
    fver[7] = -0.4;

    fver[8] = -0.75 / 2.;
    fver[9] = -0.4;

    fver[10] = -0.75 / 2.;
    fver[11] = 0.4;

    fver[12] = 0.75 / 2.;
    fver[13] = 0.4;

    fver[14] = 0.75 / 2.;
    fver[15] = -0.4;

    TGeoVolume* Alv = gGeoManager->MakeArb8("FWASATOFLog", pMedSci, 17.2 / 2., fver);
    Alv->SetLineColor(4);

    Char_t buffer[126];
    double x, y, ang;

    TGeoRotation* frot[48];
    double angstep = TMath::Pi() * 2. / 48.;
    double angstep2 = 180. * 2. / 48.;
    for (int p = 0; p < 48; p++)
    {

        sprintf(buffer, "t10_X%i", p + 1);
        ang = angstep * p;
        x = 13.4478 * cos(ang);
        y = 13.4478 * sin(ang);

        frot[p] = new TGeoRotation();
        frot[p]->RotateY(-90.);
        frot[p]->RotateX(90.0);
        frot[p]->RotateY(30.0);
        if (p > 0)
            frot[p]->RotateZ(angstep2 * p);
        WasaSci->AddNode(Alv, p + 1, new TGeoCombiTrans(buffer, x, y, 55. / 2. + 8.6 / 2. / 2. + 1., frot[p]));
    }

    Double_t* bver = new Double_t[16];

    bver[0] = -3.6 / 2.;
    bver[1] = 0.4;

    bver[2] = 3.6 / 2.;
    bver[3] = 0.4;

    bver[4] = 3.1 / 2.;
    bver[5] = -0.4;

    bver[6] = -3.1 / 2.;
    bver[7] = -0.4;

    bver[8] = -1.45 / 2.;
    bver[9] = 0.4;

    bver[10] = 1.45 / 2.;
    bver[11] = 0.4;

    bver[12] = 1.05 / 2.;
    bver[13] = -0.4;

    bver[14] = -1.05 / 2.;
    bver[15] = -0.4;

    TGeoVolume* bAlv = gGeoManager->MakeArb8("BWASATOFLog", pMedSci, 16. / 2., bver);
    bAlv->SetLineColor(4);

    TGeoRotation* brot[48];
    double bangstep = TMath::Pi() * 2. / 48.;
    double bangstep2 = 180. * 2. / 48.;
    double rb = 9.5 + 16. / 2.;
    for (int p = 0; p < 48; p++)
    {

        sprintf(buffer, "t20_X%i", p + 1);
        ang = bangstep * p;
        x = rb * cos(ang);
        y = rb * sin(ang);

        brot[p] = new TGeoRotation();
        if (p % 2 == 1)
            brot[p]->RotateZ(180.);
        brot[p]->RotateY(-90.);
        brot[p]->RotateX(90.0);
        if (p > 0)
            brot[p]->RotateZ(bangstep2 * p);
        WasaSci->AddNode(
            bAlv, p + 1, new TGeoCombiTrans(buffer, x, y, -1. * (55. / 2. + 8.6 / 2. / 2. - 0.8), brot[p]));
    }

    /*
        TGeoRotation* arot2 = new TGeoRotation();
        arot2->RotateX(90.0-30.);
        //arot2->RotateZ(-10.0);

      WasaSci->AddNode(Alv,1,new TGeoCombiTrans("t100", 0.0, 13.4478, 55./2.+8.6/2./2.+1., arot2));


        TGeoRotation* arot3 = new TGeoRotation();
        arot3->RotateX(90.0-30.);
        arot3->RotateZ(180.0);
        //arot3->RotateY(180.);

      WasaSci->AddNode(Alv,2,new TGeoCombiTrans("t101", 0., -13.4478, 55./2.+8.6/2./2.+1., arot3));


        TGeoRotation* arot4 = new TGeoRotation();
        arot4->RotateY(-90.);
        arot4->RotateX(90.0);
        arot4->RotateY(30.0);

      WasaSci->AddNode(Alv,3,new TGeoCombiTrans("t102", 13.4478, 0., 55./2.+8.6/2./2.+1., arot4));

        TGeoRotation* arot5 = new TGeoRotation();
        arot5->RotateY(90.);
        arot5->RotateX(90.0);
        arot5->RotateY(-30.0);

      WasaSci->AddNode(Alv,4,new TGeoCombiTrans("t102", -13.4478, 0., 55./2.+8.6/2./2.+1., arot5));

        TGeoRotation* arot6 = new TGeoRotation();
        arot6->RotateY(90.);
        arot6->RotateX(90.0);
        arot6->RotateY(-30.0);
        arot6->RotateZ(18.0);

      WasaSci->AddNode(Alv,5,new TGeoCombiTrans("t102", -13.4478+0.5, -3.3, 55./2.+8.6/2./2.+1., arot6));
    */

    TGeoRotation* rotg = new TGeoRotation();
    rotg->RotateX(0.);
    rotg->RotateY(0.);
    rotg->RotateZ(0.);
    dx = tx = 0.0;
    dy = ty = 0.0;
    dz = tz = 9.0;

    TGeoCombiTrans* t0 = new TGeoCombiTrans(tx, ty, tz, rotg);
    pWorld->AddNode(WasaSci, 1, GetGlobalPosition(t0));

    // ---------------   Finish   -----------------------------------------------
    gGeoMan->CloseGeometry();
    gGeoMan->CheckOverlaps(0.001);
    gGeoMan->PrintOverlaps();
    gGeoMan->Test();

    top->Draw("");

    // TView *view = gPad->GetView();
    // view->ShowAxis();

    TFile* geoFile = new TFile(geoFileName, "RECREATE");
    top->Write();
    geoFile->Close();

    std::cout << "Creating geometry: " << geoFileName << std::endl;

    // --------------------------------------------------------------------------
}

TGeoCombiTrans* GetGlobalPosition(TGeoCombiTrans* fRef)
{
    if (fLocalTrans == kTRUE)
    {

        if ((fThetaX == 0) && (fThetaY == 0) && (fThetaZ == 0) && (fX == 0) && (fY == 0) && (fZ == 0))
            return fRef;

        // X axis
        Double_t xAxis[3] = { 1., 0., 0. };
        Double_t yAxis[3] = { 0., 1., 0. };
        Double_t zAxis[3] = { 0., 0., 1. };
        // Reference Rotation
        fRefRot = fRef->GetRotation();

        if (fRefRot)
        {
            Double_t mX[3] = { 0., 0., 0. };
            Double_t mY[3] = { 0., 0., 0. };
            Double_t mZ[3] = { 0., 0., 0. };

            fRefRot->LocalToMasterVect(xAxis, mX);
            fRefRot->LocalToMasterVect(yAxis, mY);
            fRefRot->LocalToMasterVect(zAxis, mZ);

            Double_t a[4] = { mX[0], mX[1], mX[2], fThetaX };
            Double_t b[4] = { mY[0], mY[1], mY[2], fThetaY };
            Double_t c[4] = { mZ[0], mZ[1], mZ[2], fThetaZ };

            ROOT::Math::AxisAngle aX(a, a + 4);
            ROOT::Math::AxisAngle aY(b, b + 4);
            ROOT::Math::AxisAngle aZ(c, c + 4);

            ROOT::Math::Rotation3D fMatX(aX);
            ROOT::Math::Rotation3D fMatY(aY);
            ROOT::Math::Rotation3D fMatZ(aZ);

            ROOT::Math::Rotation3D fRotXYZ = (fMatZ * (fMatY * fMatX));

            // cout << fRotXYZ << endl;

            Double_t fRotable[9] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
            fRotXYZ.GetComponents(fRotable[0],
                                  fRotable[3],
                                  fRotable[6],
                                  fRotable[1],
                                  fRotable[4],
                                  fRotable[7],
                                  fRotable[2],
                                  fRotable[5],
                                  fRotable[8]);
            TGeoRotation* pRot = new TGeoRotation();
            pRot->SetMatrix(fRotable);
            TGeoCombiTrans* pTmp = new TGeoCombiTrans(*fGlobalTrans, *pRot);

            // ne peut pas etre applique ici
            // il faut differencier trans et rot dans la multi.
            TGeoRotation rot_id;
            rot_id.SetAngles(0.0, 0.0, 0.0);

            TGeoCombiTrans c1;
            c1.SetRotation(rot_id);
            const Double_t* t = pTmp->GetTranslation();
            c1.SetTranslation(t[0], t[1], t[2]);

            TGeoCombiTrans c2;
            c2.SetRotation(rot_id);
            const Double_t* tt = fRefRot->GetTranslation();
            c2.SetTranslation(tt[0], tt[1], tt[2]);

            TGeoCombiTrans cc = c1 * c2;

            TGeoCombiTrans c3;
            c3.SetRotation(pTmp->GetRotation());
            TGeoCombiTrans c4;
            c4.SetRotation(fRefRot);

            TGeoCombiTrans ccc = c3 * c4;

            TGeoCombiTrans pGlobal;
            pGlobal.SetRotation(ccc.GetRotation());
            const Double_t* allt = cc.GetTranslation();
            pGlobal.SetTranslation(allt[0], allt[1], allt[2]);

            return (new TGeoCombiTrans(pGlobal));
        }
        else
        {

            cout << "-E- R3BDetector::GetGlobalPosition() \
	      No. Ref. Transformation defined ! "
                 << endl;
            cout << "-E- R3BDetector::GetGlobalPosition() \
	      cannot create Local Transformation "
                 << endl;
            return NULL;
        } //! fRefRot
    }
    else
    {
        // Lab Transf.
        if ((fPhi == 0) && (fTheta == 0) && (fPsi == 0) && (fX == 0) && (fY == 0) && (fZ == 0))
            return fRef;

        return (new TGeoCombiTrans(*fGlobalTrans, *fGlobalRot));
    }
}

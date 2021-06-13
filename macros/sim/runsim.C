//
//   ----- General macro for WASA simulation
//
//         Author: Jose Luis <joseluis.rodriguez.sanchez@usc.es>
//
//         Last Update: 25/09/18 (Jose Luis)
//
//         Comments: root -l
//                   .L runsim.C
//                   runsim(nEvents)
//

void runsim(Int_t nEvents = 1)
{

    // -----   Timer   --------------------------------------------------------
    TStopwatch timer;
    timer.Start();
    // ------------------------------------------------------------------------

    // =========== Configuration area =============================

    TString OutFile = "sim.root"; // Output file for data
    TString ParFile = "par.root"; // Output file for params

    Bool_t fVis = false;        // Store tracks for visualization
    Bool_t fUserPList = false; // Use of R3B special physics list
    Bool_t fMagnet = true;     // Magnetic field definition

    TString fMC = "TGeant4";    // MonteCarlo engine: TGeant3, TGeant4, TFluka
    TString fGenerator = "box"; // Event generator type: box, gammas, r3b, ion, ascii
    TString fEventFile = "";    // Input event file in the case of ascii generator

    Int_t fFieldScale = 1; // Magnetic field scale factor

    // ----    Debug option   -------------------------------------------------
    gDebug = 0;

    // ---------------  Detector selection: true - false ----------------------
    Bool_t fTarget = false;      // Target
    TString fTargetType = "LiH"; // Target selection: LeadTarget, Para, Para45, LiH

    Bool_t fYoke = true; // Yoke wasa
    TString fYokeGeo = "wasa_yoke_v2020.geo.root";

    Bool_t fTracker = true; // Tracker
    TString fTrackerGeo = "wasa_v2020.geo.root";

    Bool_t fTof = true; // ToF Detector
    TString fTofGeo = "wasa_sci_v2020.geo.root";

    // ========= End of Configuration area =======================

    // ---- Stable part   -----------------------------------------------------
    TString dir = gSystem->Getenv("VMCWORKDIR");
    TString r3bdir = dir + "/macros/";
    r3bdir.ReplaceAll("//", "/");

    TString r3b_geomdir = dir + "/geometry/";
    gSystem->Setenv("GEOMPATH", r3b_geomdir.Data());
    r3b_geomdir.ReplaceAll("//", "/");

    TString r3b_confdir = dir + "/gconfig/";
    gSystem->Setenv("CONFIG_DIR", r3b_confdir.Data());
    r3b_confdir.ReplaceAll("//", "/");

    char str[1000];
    sprintf(str, "GEOMPATH=%s/frs/geometry", dir.Data());
    putenv(str);

    // -----   Create simulation run   ----------------------------------------
    FairRunSim* run = new FairRunSim();
    run->SetName(fMC);                           // Transport engine
    run->SetSink(new FairRootFileSink(OutFile)); // Output file

    //  R3B Special Physics List in G4 case
    if ((fUserPList) && (fMC.CompareTo("TGeant4") == 0))
    {
        run->SetUserConfig("g4Config.C");
        run->SetUserCuts("SetCuts.C");
    }

    // -----   Create media   -------------------------------------------------
    run->SetMaterials("media_r3b.geo"); // Materials

    // -----   Create R3B geometry --------------------------------------------

    // Cave definition
    FairModule* cave = new R3BCave("CAVE");
    cave->SetGeometryFileName("r3b_cave_vacuum.geo");
    run->AddModule(cave);

    // Yoke
    if (fYoke)
    {
        run->AddModule(new R3BTarget(fTargetType, fYokeGeo));
    }

    // Tracker
    if (fTracker)
    {
        run->AddModule(new WASAMdc(fTrackerGeo));
    }

    // Tof
    if (fTof)
    {
        run->AddModule(new WASATof(fTofGeo));
    }

    // -----   Create WASA magnetic field ----------------------------------------
    // If the Global Position of the Magnet is changed
    // the Field Map is also transformed accordingly
    if (fMagnet == 1)
    {
        FRSWasaFieldMap* magField = new FRSWasaFieldMap("FrsWasaFieldMap");
        // magField->SetScale(fFieldScale);
        magField->SetPosition(0., 0., 0.);
        magField->SetField(0., 0., 11.); // kGaus
        magField->SetRmax(30.);
        magField->SetZmax(25.);
        magField->SetZmin(-25.);
        run->SetField(magField);
    }

    // -----   Create PrimaryGenerator   --------------------------------------

    // 1 - Create the Main API class for the Generator
    FairPrimaryGenerator* primGen = new FairPrimaryGenerator();

    if (fGenerator.CompareTo("box") == 0)
    {
        // 2- Define the BOX generator
        Double_t pdgId = 2212; // proton beam
        Double_t theta1 = 0.; // polar angle distribution
        Double_t theta2 = 0.;
        Double_t momentum = 2.25; // 10 GeV/c
        FairBoxGenerator* boxGen = new FairBoxGenerator(pdgId, 1);
        boxGen->SetThetaRange(theta1, theta2);
        boxGen->SetPRange(momentum, momentum);
        boxGen->SetPhiRange(0., 0.);
        boxGen->SetXYZ(0.0, 0.0, -20.5);
        // add the box generator
        //primGen->AddGenerator(boxGen);

        FRSResonanceGenerator* resGen = new FRSResonanceGenerator();
        primGen->AddGenerator(resGen);

        // FairBoxGenerator* boxGen2 = new FairBoxGenerator(211, 1);
        // boxGen2->SetThetaRange (   theta1,   theta2);
        // boxGen2->SetPRange     (momentum,momentum*2.);
        // boxGen2->SetPhiRange   (0.,360.);
        // boxGen2->SetXYZ(0.0,0.0,.0);
        // add the box generator
        // primGen->AddGenerator(boxGen2);

        // 128-Sn fragment
         R3BIonGenerator* ionGen = new R3BIonGenerator(54, 124, 54, 1, 0., 0., 1.3);
         ionGen->SetSpotRadius(0., -37., 0.);
         //primGen->AddGenerator(ionGen);

        // R3BIonGenerator* ionGen = new R3BIonGenerator(2, 128, 50, 1, 0., 1.3, 0);
        // ionGen->SetSpotRadius(0.1, 0., 0.);
        //  primGen->AddGenerator(ionGen);
    }

    run->SetGenerator(primGen);

    //-------Set visualisation flag to true------------------------------------
    run->SetStoreTraj(fVis);

    FairLogger::GetLogger()->SetLogVerbosityLevel("LOW");

    // -----   Initialize simulation run   ------------------------------------
    run->Init();

    // -----   Runtime database   ---------------------------------------------
    FairRuntimeDb* rtdb = run->GetRuntimeDb();
    Bool_t kParameterMerged = kTRUE;
    FairParRootFileIo* parOut = new FairParRootFileIo(kParameterMerged);
    parOut->open(ParFile.Data());
    rtdb->setOutput(parOut);
    rtdb->saveOutput();
    rtdb->print();

    // -----   Start run   ----------------------------------------------------
    if (nEvents > 0)
        run->Run(nEvents);

    // -----   Finish   -------------------------------------------------------
    timer.Stop();
    Double_t rtime = timer.RealTime();
    Double_t ctime = timer.CpuTime();
    cout << endl << endl;
    cout << "Macro finished succesfully." << endl;
    cout << "Output file is " << OutFile << endl;
    cout << "Parameter file is " << ParFile << endl;
    cout << "Real time " << rtime << " s, CPU time " << ctime << "s" << endl << endl;
    // ------------------------------------------------------------------------

    cout << " Test passed" << endl;
    cout << " All ok " << endl;
}

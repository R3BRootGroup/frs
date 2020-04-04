/* Additional info:
 * Author: Jose Luis <joseluis.rodriguez.sanchez@usc.es>
 * @since December 2nd, 2019
 * */

typedef struct EXT_STR_h101_t {
  EXT_STR_h101_unpack_t unpack;
  EXT_STR_h101_frssci_onion_t vftx;
} EXT_STR_h101;

void vftx() {
  TStopwatch timer;
  timer.Start();
  
  //const Int_t nev = -1; /* number of events to read, -1 - until CTRL+C */
  const Int_t nev = -1; /* number of events to read, -1 - until CTRL+C */
  
  /* Create source using ucesb for input ------------------ */
  
  //TString filename = "--stream=lxg1266:8000";
  TString filename = "~/lmd/frs2020/s480_calibration1_109sn_2126.lmd";

  TString outputFileName = "data_vftx.root";

  // Calibration files ------------------------------------
  TString dir = gSystem->Getenv("VMCWORKDIR");
  // Parameters for FRS detectors
  TString frscaldir = dir + "/frs/macros/unpack/vftx/";
  TString frscalfilename = frscaldir + "sci_rawcal.par";
  frscalfilename.ReplaceAll("//", "/");

  TString ntuple_options = "RAW";
  TString ucesb_dir = getenv("UCESB_DIR");
  TString ucesb_path = ucesb_dir + "/../upexps/202003_s475/201911_eng2  --input-buffer=100Mi";
  ucesb_path.ReplaceAll("//","/");
  
  EXT_STR_h101 ucesb_struct;
  
  R3BUcesbSource* source = new R3BUcesbSource(filename, ntuple_options,
					      ucesb_path, &ucesb_struct, sizeof(ucesb_struct));
  source->SetMaxEvents(nev);
  

  /* Definition of reader --------------------------------- */
  R3BUnpackReader* unpackreader = new R3BUnpackReader((EXT_STR_h101_unpack*)&ucesb_struct.unpack,
					offsetof(EXT_STR_h101, unpack));


  VftxSciReader* unpackvftx= new VftxSciReader((EXT_STR_h101_frssci*)&ucesb_struct.vftx,
					     offsetof(EXT_STR_h101, vftx));


  /* Add readers ------------------------------------------ */
  source->AddReader(unpackreader);
  source->AddReader(unpackvftx);

  
  /* Create online run ------------------------------------ */
  FairRunOnline* run = new FairRunOnline(source);
  run->SetRunId(1);
  run->SetSink(new FairRootFileSink(outputFileName));       // Output file
  Int_t refresh = 1;
  Int_t port=8888;
  run->ActivateHttpServer(refresh, port);


  /* Runtime data base ------------------------------------ */
  FairRuntimeDb* rtdb = run->GetRuntimeDb();

  /* Load parameters   ------------------------------------ */ 
  FairParAsciiFileIo* parIo1 = new FairParAsciiFileIo(); // Ascii
  parIo1->open(frscalfilename, "in");
  rtdb->setFirstInput(parIo1);
  rtdb->print();

  /* Add analysis task ------------------------------------ */ 

  // --- Mapped 2 Tcal for FrsSci
  FrsSciMapped2Tcal* FrsSciMap2Tcal = new FrsSciMapped2Tcal();
  FrsSciMap2Tcal->SetOnline(false);
  run->AddTask(FrsSciMap2Tcal);

        // --- Tcal 2 SingleTcal for FrsSci
        FrsSciTcal2SingleTcal* FrsSciTcal2STcal = new FrsSciTcal2SingleTcal();
        FrsSciTcal2STcal->SetOnline(false);
        run->AddTask(FrsSciTcal2STcal);
        // --- SingleTcal 2 Hit for FrsSci
        //FrsSciSingleTCal2Hit* FrsSciSTcal2Hit = new FrsSciSingleTCal2Hit();
        //FrsSciSTcal2Hit->SetOnline(false);
        //SofSciSTcal2Hit->SetCalParams(675.,-1922.);//ToF calibration at Cave-C
        //run->AddTask(SofSciSTcal2Hit);


  /* Add online task ------------------------------------ */  
  R3BFrsOnlineSpectra* online= new R3BFrsOnlineSpectra();
  //run->AddTask(online);



  /* Initialize ------------------------------------------- */
  run->Init();
  FairLogger::GetLogger()->SetLogScreenLevel("INFO");
  //FairLogger::GetLogger()->SetLogScreenLevel("WARNING");
  //FairLogger::GetLogger()->SetLogScreenLevel("DEBUG");
  /* ------------------------------------------------------ */


  /* Run -------------------------------------------------- */
  run->Run((nev < 0) ? nev : 0, (nev < 0) ? 0 : nev);


  // -----   Finish   -------------------------------------------------------
  cout << endl << endl;
  // Extract the maximal used memory an add is as Dart measurement
  // This line is filtered by CTest and the value send to CDash
  FairSystemInfo sysInfo;
  Float_t maxMemory=sysInfo.GetMaxMemory();
  cout << "MaxMemory: ";
  cout << maxMemory<< endl;

  timer.Stop();
  Double_t rtime = timer.RealTime();
  Double_t ctime = timer.CpuTime();
  Float_t cpuUsage=ctime/rtime;
  cout << "CPU used: " << cpuUsage << endl;

  cout << endl;
  std::cout << "Output file is " << outputFileName << std::endl;
  cout << "Real time " << rtime << " s, CPU time " << ctime << "s" 
       << endl << endl;
  cout << "Macro finished successfully." << endl;
  //gApplication->Terminate();
}

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
  TString filename = "~/lmd/frsnov19/s2-s8-cal160_targ_0p9985_0036.lmd";

  TString outputFileName = "data_vftx.root";
  
  TString ntuple_options = "RAW";
  TString ucesb_dir = getenv("UCESB_DIR");
  
  TString ucesb_path = ucesb_dir + "/../upexps/frs_nov2019/frs_nov2019  --input-buffer=100Mi";
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
  /*FairParRootFileIo* parIo1 = new FairParRootFileIo();
  parIo1->open("FRS_Par.root","in");
  rtdb->setFirstInput(parIo1);
  rtdb->print();*/
  //FairParAsciiFileIo* parIo1 = new FairParAsciiFileIo();
  //parIo1->open("FRS_Par.par","in");
  //rtdb->setFirstInput(parIo1);


  /* Add analysis task ------------------------------------ */ 




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

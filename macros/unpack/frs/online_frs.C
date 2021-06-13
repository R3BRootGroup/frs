/* Additional info:
 * To generate the header file used for the UcesbSource (ext_h101.h), use:
 *
 * ./frs_april2019 --ntuple=RAW,id=h101_FRS,ext_h101_frs.h
 *
 * at $UCESB_DIR/upexps/frs_april2019
 *
 * Put this header file into the 'frs/frssource' directory and recompile.
 *
 * Author: Jose Luis <joseluis.rodriguez.sanchez@usc.es>
 * @since March 9th, 2020
 * */

typedef struct EXT_STR_h101_t {
  EXT_STR_h101_unpack_t unpack;
  EXT_STR_h101_WRMASTER_t wrm;
  EXT_STR_h101_FRSMUSIC_onion_t music;
  EXT_STR_h101_frssci_onion_t vftx;
  EXT_STR_h101_FRS_t frs;
  EXT_STR_h101_TPC_t tpc;
} EXT_STR_h101;

void online_frs() {
  TStopwatch timer;
  timer.Start();
  
  //const Int_t nev = -1; /* number of events to read, -1 - until CTRL+C */
  const Int_t nev = -1; /* number of events to read, -1 - until CTRL+C */
  
  /* Create source using ucesb for input ------------------ */
  
  //TString filename = "--stream=lxg1266:8000";
  //TString filename = "/home/joseluis/lmd/frsnov19/frag_0075.lmd";
  TString filename = "~/lmd/frs2020/s468_12_193W__0922.lmd";

  TString outputFileName = "data_frs_online.root";
  
  TString ntuple_options = "RAW";
  TString ucesb_dir = getenv("UCESB_DIR");
  
  //TString ucesb_path = ucesb_dir + "/../upexps/frs_april2019/frs_april2019  --input-buffer=100Mi";
  TString ucesb_path = ucesb_dir + "/../upexps/202003_s475/202003_s475  --input-buffer=100Mi --allow-errors";
  ucesb_path.ReplaceAll("//","/");
  
  EXT_STR_h101 ucesb_struct;
  
  R3BUcesbSource* source = new R3BUcesbSource(filename, ntuple_options,
					      ucesb_path, &ucesb_struct, sizeof(ucesb_struct));
  source->SetMaxEvents(nev);
  

  /* Definition of reader --------------------------------- */
  R3BUnpackReader* unpackreader = new R3BUnpackReader((EXT_STR_h101_unpack*)&ucesb_struct.unpack,
					offsetof(EXT_STR_h101, unpack));

  R3BWhiterabbitMasterReader* unpackWRM = new R3BWhiterabbitMasterReader((EXT_STR_h101_WRMASTER*)&ucesb_struct.wrm,
                                             offsetof(EXT_STR_h101, wrm), 0x100);

  R3BFrsReaderNov19* unpackfrs= new R3BFrsReaderNov19((EXT_STR_h101_FRS*)&ucesb_struct.frs,
					     offsetof(EXT_STR_h101, frs));

  FrsTpcReader* unpacktpc= new FrsTpcReader((EXT_STR_h101_TPC*)&ucesb_struct.tpc,
					     offsetof(EXT_STR_h101, tpc));

  VftxSciReader* unpackvftx= new VftxSciReader((EXT_STR_h101_frssci*)&ucesb_struct.vftx,
					     offsetof(EXT_STR_h101, vftx));

  FrsMusicReader* unpackmusic= new FrsMusicReader((EXT_STR_h101_FRSMUSIC*)&ucesb_struct.music,
					     offsetof(EXT_STR_h101, music));


  /* Add readers ------------------------------------------ */
  source->AddReader(unpackreader);
  unpackWRM->SetOnline(true);
  source->AddReader(unpackWRM);
  unpackfrs->SetOnline(true);
  source->AddReader(unpackfrs);
  //unpacktpc->SetOnline(true);
  source->AddReader(unpacktpc);
  unpackmusic->SetOnline(true);
  source->AddReader(unpackmusic);
  unpackvftx->SetOnline(true);
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
  FairParAsciiFileIo* parIo1 = new FairParAsciiFileIo();
  //parIo1->open("FRS_Par.par","in");
  parIo1->open("FRS_Par.par","in");
  rtdb->setFirstInput(parIo1);


  /* Add analysis task ------------------------------------ */ 
  //Spill
  FrsRatesSpill* Spill = new FrsRatesSpill();
  Spill->SetOnline(true);
  run->AddTask(Spill);
  //Seetram
  R3BSeetramMapped2Cal* SeeMap2Cal = new R3BSeetramMapped2Cal();
  SeeMap2Cal->SetOnline(true);
  run->AddTask(SeeMap2Cal);
  //MWPCs
  R3BMWMapped2Hit* MwMap2Hit = new R3BMWMapped2Hit();
  MwMap2Hit->SetOnline(true);
  run->AddTask(MwMap2Hit);
  //Musics
  FRSMusicMapped2Cal* MusMap2Cal = new FRSMusicMapped2Cal();
  MusMap2Cal->SetOnline(true);
  run->AddTask(MusMap2Cal);
  FRSMusicCal2Hit* MusCal2Hit = new FRSMusicCal2Hit();
  //MusCal2Hit->SetOnline(true);
  run->AddTask(MusCal2Hit);
  //Tpcs
  R3BTpcMapped2Cal* TpcMap2Cal = new R3BTpcMapped2Cal();
  //TpcMap2Cal->SetOnline(true);
  run->AddTask(TpcMap2Cal);
  R3BTpcCal2Hit* TpcCal2Hit = new R3BTpcCal2Hit();
  //TpcCal2Hit->SetOnline(true);
  run->AddTask(TpcCal2Hit);
  // Vftx
  // --- Mapped 2 Tcal for FrsSci
  FrsSciMapped2Tcal* FrsSciMap2Tcal = new FrsSciMapped2Tcal();
  //FrsSciMap2Tcal->SetOnline(true);
  run->AddTask(FrsSciMap2Tcal);
  // --- Tcal 2 SingleTcal for FrsSci
  FrsSciTcal2SingleTcal* FrsSciTcal2STcal = new FrsSciTcal2SingleTcal();
  //FrsSciTcal2STcal->SetOnline(true);
  run->AddTask(FrsSciTcal2STcal);
  //Analysis S4
  R3BFrsHit2AnaS4* AnaFrsS4 = new R3BFrsHit2AnaS4();
  //AnaFrsS4->SetOnline(true);
  //AnaFrsS4->SetOffsetAq(0.0268);
  AnaFrsS4->SetOffsetZ(0.);
  run->AddTask(AnaFrsS4);

  /* Add online task ------------------------------------ */
  FrsTpcOnlineSpectra* tpconline= new FrsTpcOnlineSpectra();
  run->AddTask(tpconline);
/*
  FrsMWOnlineSpectra* mw11online= new FrsMWOnlineSpectra("MW11OnlineSpectra",1,"MW11");
  run->AddTask(mw11online);

  FrsMWOnlineSpectra* mw21online= new FrsMWOnlineSpectra("MW21OnlineSpectra",1,"MW21");
  run->AddTask(mw21online);

  FrsMWOnlineSpectra* mw22online= new FrsMWOnlineSpectra("MW22OnlineSpectra",1,"MW22");
  run->AddTask(mw22online);

  FrsMWOnlineSpectra* mw31online= new FrsMWOnlineSpectra("MW31OnlineSpectra",1,"MW31");
  run->AddTask(mw31online);
*/
  FrsMusicOnlineSpectra* mus41online= new FrsMusicOnlineSpectra("Music41OnlineSpectra",1,"Music41");
  run->AddTask(mus41online);

  FrsMusicOnlineSpectra* mus42online= new FrsMusicOnlineSpectra("Music42OnlineSpectra",1,"Music42");
  run->AddTask(mus42online);

  R3BFrsOnlineSpectra* online= new R3BFrsOnlineSpectra();
  run->AddTask(online);


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

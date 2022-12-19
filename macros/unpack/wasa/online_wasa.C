/* Additional info:
 * To generate the header file used for the R3BUcesbSource (ext_h101.h), use:
 *
 * ./wasa --ntuple=RAW,id=h101_WASA,ext_h101_wasa.h
 *
 * at $UCESB_DIR/upexps/wasa
 *
 * Put this header file into the 'frs/frssource' directory and recompile.
 *
 * Author: Jose Luis <joseluis.rodriguez.sanchez@usc.es>
 * @since September 23, 2018
 * */

typedef struct EXT_STR_h101_t {
  EXT_STR_h101_unpack_t unpack;
  EXT_STR_h101_WASA_t wasa;
} EXT_STR_h101;

void online_wasa() {
  TStopwatch timer;
  timer.Start();
  
  //const Int_t nev = -1; /* number of events to read, -1 - until CTRL+C */
  const Int_t nev = -1; /* number of events to read, -1 - until CTRL+C */
  
  /* Create source using ucesb for input ------------------ */
  
  //TString filename = "--stream=lxg0898:6002";
  TString filename = "~/lmd/mdctest0075.lmd";
  
  TString outputFileName = "data_online.root";
  
  TString ntuple_options = "UNPACK:EVENTNO,UNPACK:TRIGGER,RAW";
  TString ucesb_dir = getenv("UCESB_DIR");
  
  TString ucesb_path = ucesb_dir + "/../upexps/wasa/swasa";
  
  EXT_STR_h101 ucesb_struct;
  
  R3BUcesbSource* source = new R3BUcesbSource(filename, ntuple_options,
					      ucesb_path, &ucesb_struct, sizeof(ucesb_struct));
  source->SetMaxEvents(nev);
  

  /* Definition of reader --------------------------------- */
  R3BUnpackReader* unpackreader = new R3BUnpackReader((EXT_STR_h101_unpack*)&ucesb_struct,
					offsetof(EXT_STR_h101, unpack));

  R3BWasaReader* unpackwasa= new R3BWasaReader((EXT_STR_h101_WASA*)&ucesb_struct.wasa,
					     offsetof(EXT_STR_h101, wasa));


  /* Add readers ------------------------------------------ */
  source->AddReader(unpackreader);
  unpackwasa->SetOnline(true);
  source->AddReader(unpackwasa);

  
  /* Create online run ------------------------------------ */
  FairRunOnline* run = new FairRunOnline(source);
  run->SetRunId(1);
  run->SetOutputFile(outputFileName);
  Int_t refresh = 1;
  Int_t port=8044;
  run->ActivateHttpServer(refresh, port);


  /* Runtime data base ------------------------------------ */
  FairRuntimeDb* rtdb = run->GetRuntimeDb();


  /* Load parameters   ------------------------------------ */ 
  /*FairParRootFileIo* parIo1 = new FairParRootFileIo();
  parIo1->open("FRS_Par.root","in");
  rtdb->setFirstInput(parIo1);
  rtdb->print();*/
/*
  FairParAsciiFileIo* parIo1 = new FairParAsciiFileIo();
  parIo1->open("FRS_Par.par","in");
  rtdb->setFirstInput(parIo1);
*/

  /* Add analysis task ------------------------------------ */ 
  //Seetram
/*
  R3BSeetramMapped2Cal* SeeMap2Cal = new R3BSeetramMapped2Cal();
  SeeMap2Cal->SetOnline(true);
  run->AddTask(SeeMap2Cal);
  //Musics
  R3BMusicMapped2Cal* MusMap2Cal = new R3BMusicMapped2Cal();
  MusMap2Cal->SetOnline(true);
  run->AddTask(MusMap2Cal);
  R3BMusicCal2Hit* MusCal2Hit = new R3BMusicCal2Hit();
  MusCal2Hit->SetOnline(true);
  run->AddTask(MusCal2Hit);
  //Tpcs
  R3BTpcMapped2Cal* TpcMap2Cal = new R3BTpcMapped2Cal();
  TpcMap2Cal->SetOnline(true);
  run->AddTask(TpcMap2Cal);
  R3BTpcCal2Hit* TpcCal2Hit = new R3BTpcCal2Hit();
  TpcCal2Hit->SetOnline(true);
  run->AddTask(TpcCal2Hit);
  //Analysis S4
  R3BFrsHit2AnaS4* AnaFrsS4 = new R3BFrsHit2AnaS4();
  AnaFrsS4->SetOnline(true);
  AnaFrsS4->SetOffsetAq(0.0268);
  AnaFrsS4->SetOffsetZ(0.);
  run->AddTask(AnaFrsS4);
*/

  /* Add online task ------------------------------------ */  
  R3BWasaOnlineSpectra* online= new R3BWasaOnlineSpectra();
  run->AddTask(online);


  /* Initialize ------------------------------------------- */
  run->Init();
  FairLogger::GetLogger()->SetLogScreenLevel("INFO");
  //FairLogger::GetLogger()->SetLogScreenLevel("warn");
  //FairLogger::GetLogger()->SetLogScreenLevel("DEBUG");
  /* ------------------------------------------------------ */


  /* Run -------------------------------------------------- */
  run->Run((nev < 0) ? nev : 0, (nev < 0) ? 0 : nev);


  /* Finish ----------------------------------------------- */
  timer.Stop();
  Double_t rtime = timer.RealTime();
  Double_t ctime = timer.CpuTime();
  std::cout << std::endl << std::endl;
  std::cout << "Macro finished succesfully." << std::endl;
  std::cout << "Output file is " << outputFileName << std::endl;
  std::cout << "Real time " << rtime << " s, CPU time " << ctime << " s"
            << std::endl << std::endl;
  //gApplication->Terminate();
}

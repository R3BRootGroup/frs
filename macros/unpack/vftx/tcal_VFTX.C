/* Additional info:
 * Author: Jose Luis <joseluis.rodriguez.sanchez@usc.es>
 * @since March 9th, 2020
 * */

typedef struct EXT_STR_h101_t {
  EXT_STR_h101_unpack_t unpack;
  EXT_STR_h101_frssci_onion_t vftx;
} EXT_STR_h101;

void tcal_VFTX()
{
  TStopwatch timer;
  timer.Start();

  const Int_t nev = -1; /* number of events to read, -1 - until CTRL+C */
  
  // Create input -----------------------------------------
  TString filename = "~/lmd/frs2020/s480_calibration1_109sn_2126.lmd";

  // Output file with parameters --------------------------
  TString outputFileNamePar = "tcal_VFTX.par";
    
  // Output file ------------------------------------------
  TString outputFileName = "tcal_data.root";

  /* Create source using ucesb for input ------------------ */
  // UCESB configuration ----------------------------------
  TString ntuple_options = "RAW";
  TString ucesb_dir = getenv("UCESB_DIR");  
  TString ucesb_path = ucesb_dir + "/../upexps/202003_s475/201911_eng2 --allow-errors  --input-buffer=100Mi";
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
  
  /* Runtime data base ------------------------------------ */
  FairRuntimeDb* rtdb = run->GetRuntimeDb();

  /* Calibrate SofSci ---------------------------------------- */
  FrsSciMapped2TcalPar* sciTcalibrator = new FrsSciMapped2TcalPar("FrsSciMapped2TcalPar");
  sciTcalibrator->SetNumDetectors(2); 
  sciTcalibrator->SetNumChannels(2);
  sciTcalibrator->SetMinStatistics(20000);
  run->AddTask(sciTcalibrator);
  
  /* Initialize ------------------------------------------- */
  run->Init();
  FairLogger::GetLogger()->SetLogScreenLevel("INFO");
  //FairLogger::GetLogger()->SetLogScreenLevel("WARNING");
  /* ------------------------------------------------------ */
  
  // Ascii file with the Calibration Parameters
  FairParAsciiFileIo* parOut = new FairParAsciiFileIo();
  parOut->open(outputFileNamePar,"out");
  rtdb->setOutput(parOut);
  
  /* Run -------------------------------------------------- */
  run->Run((nev < 0) ? nev : 0, (nev < 0) ? 0 : nev);
  rtdb->saveOutput();
  /* ------------------------------------------------------ */

  
  timer.Stop();
  Double_t rtime = timer.RealTime();
  Double_t ctime = timer.CpuTime();
  cout << endl << endl;
  cout << "Macro finished succesfully." << endl;
  cout << "Output file is " << outputFileName << endl;
  cout << "Real time " << rtime << " s, CPU time " << ctime << " s"
       << endl << endl;
}




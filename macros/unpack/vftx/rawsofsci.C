/* Additional info:
 * Author: Jose Luis <joseluis.rodriguez.sanchez@usc.es>
 * @since December 2nd, 2019
 * */

typedef struct EXT_STR_h101_t {
  EXT_STR_h101_unpack_t unpack;
  EXT_STR_h101_frssci_onion_t vftx;
} EXT_STR_h101;

void rawsofsci()
{
  TStopwatch timer;
  timer.Start();

  const Int_t nev = -1; /* number of events to read, -1 - until CTRL+C */

  // --- ----------------------------------- --- //
  // --- Create source using ucesb for input --- //
  // --- ----------------------------------- --- //
  TString filename = "~/lmd/frs2020/s480_calibration1_109sn_2126.lmd";
  
  // Output file ----------------------------------------------------
  TString outputFileName = "data_SciRawPosRawTof.root";
 
  // Calibration files ------------------------------------
  TString dir = gSystem->Getenv("VMCWORKDIR");
  // Parameters for FRS detectors
  TString frscaldir = dir + "/frs/macros/unpack/vftx/";
  TString frscalfilename = frscaldir + "tcal_VFTX.par";
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
  run->SetOutputFile(outputFileName);

  /* Runtime data base ------------------------------------ */
  FairRuntimeDb* rtdb = run->GetRuntimeDb();
 
  /* Load parameters   ------------------------------------ */
  FairParAsciiFileIo* parIo1 = new FairParAsciiFileIo();//Ascii
  parIo1->open(frscalfilename,"in");
  rtdb->setFirstInput(parIo1);
  rtdb->print();

  /* Add analysis task ------------------------------------ */ 
  // --- Mapped 2 Tcal for FrsSci
  FrsSciMapped2Tcal* FrsSciMap2Tcal = new FrsSciMapped2Tcal();
  FrsSciMap2Tcal->SetOnline(false);
  run->AddTask(FrsSciMap2Tcal);

  // === Tcal2RawPos for FrsSci === //
  FrsSciTcal2RawPosPar* sci_poscalibrator = new FrsSciTcal2RawPosPar("FrsSciTcal2RawPosPar");
  sci_poscalibrator->SetNumDetectors(2); 
  sci_poscalibrator->SetNumChannels(2);
  sci_poscalibrator->SetNumParsPerSignal(2);
  sci_poscalibrator->SetMinStatistics(1000);
  run->AddTask(sci_poscalibrator);

  // === Tcal2RawTof for FrsSci === //
  FrsSciTcal2RawTofPar* sci_tofcalibrator = new FrsSciTcal2RawTofPar("FrsSciTcal2RawTofPar");
  sci_tofcalibrator->SetFirstStaSci(1);
  //sci_tofcalibrator->SetFirstStoSci(2);
  //sci_tofcalibrator->SetNumSignals();
  sci_tofcalibrator->SetNumParsPerSignal(2);
  sci_tofcalibrator->SetMinStatistics(1000);
  run->AddTask(sci_tofcalibrator);

  // --- ---------- --- //
  // --- Initialize --- //
  // --- ---------- --- //
  run->Init();
  FairLogger::GetLogger()->SetLogScreenLevel("INFO");
  //FairLogger::GetLogger()->SetLogScreenLevel("WARNING");

  // --- ------------------------------------------- --- //
  // --- output parameters :                         --- //
  // ---  ascii file with the calibration parameters --- //
  // --- ------------------------------------------- --- //
  FairParAsciiFileIo* parOut = new FairParAsciiFileIo();
  TString outputFileNamePar = "out_sofsci.par";
  parOut->open(outputFileNamePar,"out");
  rtdb->setOutput(parOut);
  rtdb->print();

  // --- --- --- //
  // --- Run --- //
  // --- --- --- //
  run->Run((nev < 0) ? nev : 0, (nev < 0) ? 0 : nev);
  rtdb->saveOutput();

  // --- ------- --- //
  // --- Cleanup --- //
  // --- ------- --- //
  timer.Stop();
  Double_t rtime = timer.RealTime();
  Double_t ctime = timer.CpuTime();
  cout << endl << endl;
  cout << "Macro finished succesfully." << endl;
  cout << "Output file is " << outputFileName << endl;
  cout << "Real time " << rtime << " s, CPU time " << ctime << " s"
       << endl << endl;

}

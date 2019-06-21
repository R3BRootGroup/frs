/* Additional info:
 * To generate the header file used for the R3BUcesbSource (ext_h101.h), use:
 *
 * ./frs_jul2018 --ntuple=RAW,id=h101_FRS,ext_h101_frs.h
 *
 * at $UCESB_DIR/upexps/frs_jul2018
 *
 * Put this header file into the 'frs/frssource' directory and recompile.
 *
 * Author: Jose Luis <joseluis.rodriguez.sanchez@usc.es>
 * @since July 29, 2018
 * */

typedef struct EXT_STR_h101_t {
  EXT_STR_h101_unpack_t unpack;
  EXT_STR_h101_FRS_t frs;
} EXT_STR_h101;

void unpack_gsi2018_frs_mapped() {
  TStopwatch timer;
  timer.Start();
  
  //const Int_t nev = -1; /* number of events to read, -1 - until CTRL+C */
  const Int_t nev = -1; /* number of events to read, -1 - until CTRL+C */
  
  /* Create source using ucesb for input ------------------ */
  
  TString filename = "~/lmd/Ag107_1000AMeV_0011.lmd";
  TString outputFileName = "data_map_01.root";
  
  TString ntuple_options = "UNPACK:EVENTNO,UNPACK:TRIGGER,RAW";
  TString ucesb_dir = getenv("UCESB_DIR");
  
  TString ucesb_path = ucesb_dir + "/../upexps/frs_jul2018/frs_jul2018";
  
  EXT_STR_h101 ucesb_struct;
  
  R3BUcesbSource* source = new R3BUcesbSource(filename, ntuple_options,
					      ucesb_path, &ucesb_struct, sizeof(ucesb_struct));
  source->SetMaxEvents(nev);
  
  source->AddReader(new R3BUnpackReader((EXT_STR_h101_unpack*)&ucesb_struct,
					offsetof(EXT_STR_h101, unpack)));
  source->AddReader(new R3BFrsReader((EXT_STR_h101_FRS*)&ucesb_struct.frs,
					     offsetof(EXT_STR_h101, frs)));

  
  /* Create online run ------------------------------------ */
  FairRunOnline* run = new FairRunOnline(source);
  //run->SetRunId(1513078509);
  run->SetOutputFile(outputFileName);


  /* Initialize ------------------------------------------- */
  run->Init();
  FairLogger::GetLogger()->SetLogScreenLevel("INFO");
  //FairLogger::GetLogger()->SetLogScreenLevel("WARNING");
  //FairLogger::GetLogger()->SetLogScreenLevel("DEBUG");
  /* ------------------------------------------------------ */
  

  /* Runtime data base ------------------------------------ */
  FairRuntimeDb* rtdb = run->GetRuntimeDb();


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
  gApplication->Terminate();
}

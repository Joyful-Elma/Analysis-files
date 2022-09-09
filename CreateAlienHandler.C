AliAnalysisGrid* CreateAlienHandler()
{
  AliAnalysisAlien *plugin = new AliAnalysisAlien();
  // Set the run mode (can be "full", "test", "offline", "submit" or "terminate")
  plugin->SetRunMode("terminate");
 // plugin->SetMergeViaJDL(kTRUE);
  // Set versions of used packages

 plugin->SetAPIVersion("V1.1x");
  plugin->SetAliPhysicsVersion("vAN-20210503-1");
  //////////////////////
  // Analysis on grid //
  ////////////////////
  // Declare input data to be processed.
  // Method 1: Create automatically XML collections using alien 'find' command.
  // Define production directory LFN
 plugin->SetGridDataDir("/alice/sim/2020/LHC20a2");
        plugin->SetDataPattern("AOD209/*/AliAOD.root");
//   plugin->SetRunPrefix("000");
  plugin->SetNtestFiles(2);
  
    const char *runListName = "runList17.txt";
     if(!runListName) {
 	cout << "run list file name does not exist... stop now!" <<endl;
 	return NULL;
 	}
 	    ifstream runListFile;
 	    runListFile.open((char*)runListName);
 	    Int_t runNr;
 	    if (runListFile.is_open()) {
 	      while (kTRUE){
 		runListFile >> runNr;
 		if(runListFile.eof()) break;
 		cout<<runNr<<"\n";
 		plugin->AddRunNumber(runNr);
 	      }
 	}
 	  else {
 	      cout << "run list file "<<runListName<<" does not exist... stop now!" <<endl;
 	      return NULL;
 	}
   runListFile.close();

  plugin->SetGridWorkingDir("sim/epos");
  plugin->SetGridOutputDir("EPOS");
  
//   plugin->SetDefaultOutputs(kFALSE);
//   plugin->SetOutputFiles("MuonVsMultData.root@disk=2");
  
  // Optionally define the files to be archived.
//   TString outputArchive = "log_archive.zip:stdout,stderr";
//   plugin->SetOutputArchive(outputArchive.Data());
  
  plugin->SetOutputToRunNo();
  plugin->SetAnalysisSource("AliAnalysisTaskMuonVsMult.cxx");
  plugin->SetAdditionalLibs("AliAnalysisTaskMuonVsMult.h AliAnalysisTaskMuonVsMult.cxx libSTEERBase.so libESD.so libAOD.so libANALYSIS.so libOADB.so libANALYSISalice.so libCORRFW.so libGui.so libMinuit.so libProofPlayer.so libRAWDatabase.so libCDB.so libSTEER.so libMUONcore.so libMUONmapping.so libMUONgeometry.so libMUONcalib.so libMUONtrigger.so libMUONraw.so libMUONbase.so libMUONrec.so libMUONevaluation.so libPWGmuon.so" );
  
  // Optionally set a name for the generated analysis macro (default MyAnalysis.C)
   plugin->SetAnalysisMacro("AnalysisMuonVsMult.C");

  // Optionally add include paths
  plugin->SetSplitMaxInputFileNumber(100);
  
  // Optionally set executable file (default: analysis.sh)
  plugin->SetExecutable("MuonVsMult.sh");
  
  // Optionally set time to live (default 30000 sec)
  plugin->SetTTL(30000);
  
  // Optionally set input format (default xml-single)
  plugin->SetInputFormat("xml-single");
  
  // Optionally modify the name of the generated JDL (default analysis.jdl)
//   plugin->SetJDLName(Form("analysisMuonVsMult_%d.jdl",nRun));
  plugin->SetJDLName("analysisMuonVsMult.jdl");
  
  // Optionally modify job price (default 1)
  plugin->SetPrice(1);
  
//   plugin->SetUseSubmitPolicy(); //commentare se si vogliono sottomettere piu' run contemporaneamente
  
  // Optionally modify split mode (default 'se')    
  plugin->SetSplitMode("se");
  
  // Optionally add include paths
  plugin->AddIncludePath("-Wno-deprecated");
  plugin->AddIncludePath("-I$ROOTSYS/include");
  plugin->AddIncludePath("-I$ALICE_ROOT/include");
  plugin->AddIncludePath("-I$ALICE_PHYSICS/include");
  plugin->AddIncludePath("-I$ALICE_ROOT/MUON");
  plugin->AddIncludePath("-I$ALICE_ROOT/MUON/mapping");
  plugin->AddIncludePath("-I$ALICE_ROOT/STEER");
  
  return plugin;
}

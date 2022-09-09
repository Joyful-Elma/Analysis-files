{
  gSystem->Load("libANALYSIS");
  gSystem->Load("libANALYSISalice");
  gSystem->Load("libCORRFW");
  gSystem->Load("libPWGmuon");
  gSystem->Load("libPWGmuondep");
  
  gSystem->Load("liblhapdf");      // Parton density functions
  gSystem->Load("libEGPythia6");   // TGenerator interface
  gSystem->Load("libpythia6_4_25");     // Pythia 6.4
  gSystem->Load("libAliPythia6");  // ALICE specific implementations
//   gROOT->ProcessLine(".include $ROOTSYS/include");
//    gROOT->ProcessLine(".include  $ALICE_ROOT/include");
gSystem->SetIncludePath("-I. -I/include -I$ROOTSYS/include -I$ALICE_ROOT/MUON -I$ALICE_ROOT/include -I$ALICE_PHYSICS/include");
  //gSystem->Setenv("LHAPATH",".");
  
//AliMuonAccEffSubmitter a("GenParamCustomSingleForHF_2_40",kFALSE,"4.25");
AliMuonAccEffSubmitter a("GenParamCustomSingleForHF_2_40Pbp",kFALSE,"4.25");
a.TemplateFileList()->Add(new TObjString("loadLibs.C"));
a.UseOCDBSnapshots(kFALSE);
a.SetRemoteDir("/alice/cern.ch/user/j/jmdhluli/FONLL/NNPDF/LHC17q/muon_calo_pass1/MSL1");
a.ShouldOverwriteFiles(true);
a.SetCompactMode(1);
// a.SetPackages("VO_ALICE@AliPhysics::vAN-20180316-1","VO_ALICE@AliRoot::v5-09-24-1");
//a.SetAliPhysicsVersion("VO_ALICE@AliPhysics::vAN-20180316-1",);
a.SetAliPhysicsVersion("VO_ALICE@AliPhysics::v5-09-55b-01-1");
//a.MakeNofEventsPropToTriggerCount("CMSH7-S-NOPF-MUON",0.3); // muon high pT trigger for 2012
a.MakeNofEventsPropToTriggerCount("CMSL7-B-NOPF-MUFAST",0.15);
 //a.SetRunList(276508); //run from LHC17h, pp 13TeV muon_calo_pass2
//a.SetRunList(189596);
a.SetRunList("runList17q.txt");
a.SetMaxEventsPerChunk(10000);
//a.MakeNofEventsFixed(10);
a.Print();
//a.Run("test");
a.Run("full");
}

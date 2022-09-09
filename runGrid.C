// AliAnalysisTaskSE *AddTask(TString trigger = "CMSH7-S", Bool_t useMC = kFALSE);

void runGrid()
{
  // Load common libraries
  gSystem->Load("libCore.so");  
  gSystem->Load("libTree.so");
  gSystem->Load("libGeom.so");
  gSystem->Load("libVMC.so");
  gSystem->Load("libPhysics.so");
  gSystem->Load("libMinuit.so");
  gSystem->Load("libSTEERBase");
  gSystem->Load("libESD");
  gSystem->Load("libAOD");
  gSystem->Load("libANALYSIS");
  gSystem->Load("libANALYSISalice");
  gSystem->Load("libCORRFW");
  gSystem->Load("libPWGmuon");
  // Use AliRoot includes to compile our task
  gROOT->ProcessLine(".include $ROOTSYS/include");
   gROOT->ProcessLine(".include  $ALICE_ROOT/include");
gSystem->SetIncludePath("-I. -I/include -I$ROOTSYS/include -I$ALICE_ROOT/MUON -I$ALICE_ROOT/include -I$ALICE_PHYSICS/include");
  
  // Create and configure the alien handler plugin
  gROOT->LoadMacro("CreateAlienHandler.C");
  AliAnalysisGrid *alienHandler = CreateAlienHandler();  
  if (!alienHandler) return;

  // Create the analysis manager
  AliAnalysisManager *mgr = new AliAnalysisManager("MuonVsMult_task");

  // Connect plug-in to the analysis manager
  mgr->SetGridHandler(alienHandler);

 gROOT->LoadMacro("AliAnalysisTaskMuonVsMult.cxx++g");

  // input handler
  //--------------


  AliAODInputHandler *dataHandler = new AliAODInputHandler();
  dataHandler->SetCheckStatistics(kTRUE);
  mgr->SetInputEventHandler(dataHandler);
  
   AliMuonEventCuts *muonEventCuts = new AliMuonEventCuts("StandardMuonEventCuts","StandardMuonEventCuts");
  muonEventCuts->SetFilterMask(AliMuonEventCuts::kPhysicsSelected);
  
  AliMuonTrackCuts *muonTrackCuts = new AliMuonTrackCuts("StandardMuonTrackCuts","StandardMuonTrackCuts");

  muonTrackCuts->SetAllowDefaultParams(kTRUE);
  muonTrackCuts->SetFilterMask(AliMuonTrackCuts::kMuPdca);
  
  AliAnalysisTaskMuonVsMult *task = new AliAnalysisTaskMuonVsMult("AliAnalysisTaskMuonVsMult");
//   task->SetEventCuts(muonEventCuts);
  task->SetMuonCuts(muonTrackCuts);
  
  TString file = "MuonVsMultData.root";
  
  AliAnalysisDataContainer *coutput1 = mgr->CreateContainer("TTreeMuonVsMult", TTree::Class(),AliAnalysisManager::kOutputContainer,file.Data());
  AliAnalysisDataContainer *coutput2 = mgr->CreateContainer("HistoEvent",TH2I::Class(),AliAnalysisManager::kOutputContainer,file.Data());
  AliAnalysisDataContainer *coutput3 = mgr->CreateContainer("HistoMuons",TH2I::Class(),AliAnalysisManager::kOutputContainer,file.Data());
  
  mgr->AddTask(task);
  mgr->ConnectInput(task,0,mgr->GetCommonInputContainer());
  mgr->ConnectOutput(task,1,coutput1);
  mgr->ConnectOutput(task,2,coutput2);
  mgr->ConnectOutput(task,3,coutput3);
  
  
  // Enable debug printouts
  mgr->SetDebugLevel(0);


  if (!mgr->InitAnalysis())
    return;

  mgr->PrintStatus();
  // Start analysis
  mgr->StartAnalysis("grid"); // Use this for grid
  //mgr->StartAnalysis("proof"); // Use this for proof  

};


/*
AliAnalysisTaskSE *AddTask(TString trigger, Bool_t useMC){
  
  AliAnalysisManager *mgr = AliAnalysisManager::GetAnalysisManager();
  if (!mgr) {
    ::Error("AddtaskSingleMu", "No analysis manager to connect to.");
    return NULL;
  }
  
  //  my task
  //-------------------------
  TString naming = trigger;
  naming.ReplaceAll("-","_");
  AliAnalysisTaskPtCMSH *task = new AliAnalysisTaskPtCMSH(Form("%s_Task",naming.Data()));

  // specific setting for my task
  //-----------------------------

  // ***** track cuts settings ******
  Bool_t isMC = kFALSE;
  task->GetMuonTrackCuts()->SetFilterMask ( AliMuonTrackCuts::kMuEta |AliMuonTrackCuts::kMuThetaAbs | AliMuonTrackCuts::kMuPdca | AliMuonTrackCuts::kMuMatchHpt);
  task->GetMuonTrackCuts()->SetIsMC(useMC);
  task->GetMuonTrackCuts()->Print("mask");
  task->GetMuonTrackCuts()->SetPassName("muon_calo_pass2");
  task->GetMuonTrackCuts()->SetAllowDefaultParams(kTRUE);
  task->GetMuonTrackCuts()->ApplySharpPtCutInMatching(kTRUE);
  

  // ***** event cuts settings ******
  task->GetMuonEventCuts()->SetFilterMask ( AliMuonEventCuts::kPhysicsSelected | AliMuonEventCuts::kSelectedTrig | AliMuonEventCuts::kGoodVertex );
  task->GetMuonEventCuts()->SetVertexMinNContributors(1);
  task->GetMuonEventCuts()->SetVertexVzLimits(-10., 10.);
  task->GetMuonEventCuts()->SetTrigClassPatterns(trigger.Data(),"0MSH:13");


  mgr->AddTask(task);

  AliAnalysisDataContainer *cinput = mgr->GetCommonInputContainer();
  
  AliAnalysisDataContainer *coutput3 = mgr->CreateContainer(Form("chist_%s",naming.Data()), TList::Class(), AliAnalysisManager::kOutputContainer, Form("MSH_corr.root:%s",naming.Data()));
     

  mgr->ConnectInput(task, 0, cinput);
  
  mgr->ConnectOutput(task, 1, coutput3);
  
  return task;
}*/



#if !defined(__CINT__) || defined(__MAKECINT__)
#include "TString.h"

#include "AliAnalysisManager.h"
#include "AliAnalysisDataContainer.h"

#include "AliMuonTrackCuts.h"
#include "AliMuonEventCuts.h"
#include "AliAnalysisTaskMuonVsMult.h"
#endif 
 
AliAnalysisTaskMuonVsMult *AddTask(TString trigger = "CINT7-B-NOPF-MUFAST", Bool_t useMC = kFALSE){
  
  AliAnalysisManager *mgr = AliAnalysisManager::GetAnalysisManager();
  if (!mgr) {
    ::Error("AddtaskSingleMu", "No analysis manager to connect to.");
    return NULL;
  } 
 
  
   //  my task
  //-------------------------
  TString naming = trigger;
  naming.ReplaceAll("-","_");
  Bool_t IsMC = kFALSE;
  Bool_t ApplyPUCuts;
  Double_t MeanTrRef;
  AliAnalysisTaskMuonVsMult *task = new AliAnalysisTaskMuonVsMult("AliAnalysisTaskMuonVsMult",IsMC, ApplyPUCuts/*, MeanTrRef=0*/);
 
    
  task->GetMuonTrackCuts()->SetFilterMask (/* AliMuonTrackCuts::kMuEta |AliMuonTrackCuts::kMuThetaAbs |*/ AliMuonTrackCuts::kMuPdca /*| AliMuonTrackCuts::kMuMatchLpt*/);
  task->GetMuonTrackCuts()->SetIsMC(useMC);
  task->GetMuonTrackCuts()->Print("mask");
  task->GetMuonTrackCuts()->SetPassName("muon_calo_pass1");
  task->GetMuonTrackCuts()->SetAllowDefaultParams(kTRUE);
//   task->GetMuonTrackCuts()->ApplySharpPtCutInMatching(kTRUE);
  
    task->GetMuonEventCuts()->SetFilterMask ( AliMuonEventCuts::kPhysicsSelected | AliMuonEventCuts::kSelectedTrig | AliMuonEventCuts::kGoodVertex );
  task->GetMuonEventCuts()->SetVertexMinNContributors(1);
  task->GetMuonEventCuts()->SetVertexVzLimits(-10., 10.);
  task->GetMuonEventCuts()->SetTrigClassPatterns("CMSL7-B-NOPF-MUFAST","0MSL:20");
  
   mgr->AddTask(task);
  
   
  TString file = "MuonVsMultData1.root";
  
AliAnalysisDataContainer *coutput1 = mgr->CreateContainer(Form("fEventCounters_%s",naming.Data()),AliCounterCollection::Class(),AliAnalysisManager::kOutputContainer,file.Data()); 
AliAnalysisDataContainer *coutput2 = mgr->CreateContainer(Form("ListEvents_%s",naming.Data()),TList::Class(),AliAnalysisManager::kOutputContainer,file.Data()); 
AliAnalysisDataContainer *coutput3 = mgr->CreateContainer(Form("ListSPDtracklets_%s",naming.Data()),TList::Class(),AliAnalysisManager::kOutputContainer,file.Data());
AliAnalysisDataContainer *coutput4 = mgr->CreateContainer(Form("ListPhysics_%s",naming.Data()),TList::Class(),AliAnalysisManager::kOutputContainer,file.Data());

  
mgr->ConnectInput(task,0,mgr->GetCommonInputContainer());
mgr->ConnectOutput(task,1,coutput1);
mgr->ConnectOutput(task,2,coutput2);
mgr->ConnectOutput(task,3,coutput3);
mgr->ConnectOutput(task,4,coutput4);
   return task;
}

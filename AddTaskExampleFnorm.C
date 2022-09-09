#if !defined(__CINT__) || defined(__MAKECINT__)


#include "AliPhysicsSelectionTask.h"

#endif 
AliAnalysisTaskFNorm *AddTaskExampleFnorm()
{
  const char *name = "ExampleFnorm";
  AliAnalysisManager *aam = AliAnalysisManager::GetAnalysisManager();
  
 // AliPhysicsSelectionTask *physSelTask = AddTaskPhysicsSelection(kFALSE,kTRUE,0,kFALSE);
  
  AliAnalysisTaskFNorm *task = new AliAnalysisTaskFNorm(name);
  // --- get input and output managers
  AliAnalysisDataContainer *aadci = aam->GetCommonInputContainer();
  AliAnalysisDataContainer *aadco = aam->CreateContainer
    (
     Form("Fnorm\%s",name),
     TList::Class(),
     AliAnalysisManager::kOutputContainer,
     Form("FNorm16r.root")
     );
    
  // --- add task and connect input and output managers
  aam->AddTask(task);
  aam->ConnectInput(task,0,aadci);
  aam->ConnectOutput(task,1,aadco); // recall class constructor
  // --- return pointer to Task
  return task;
}

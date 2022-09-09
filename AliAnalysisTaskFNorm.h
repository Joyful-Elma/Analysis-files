
#ifndef AliAnalysisTaskFNorm_H
#define AliAnalysisTaskFNorm_H

#include "AliAnalysisTaskSE.h"

//class TH1D;
class TParticle ;
class TFile ;
class AliStack ;
class AliESDtrack;
class AliVParticle;
class TObjArray;
class AliAODEvent;
//class AliMuonTrackCuts;


class AliAnalysisTaskFNorm : public AliAnalysisTaskSE {
  public:

  AliAnalysisTaskFNorm();
  AliAnalysisTaskFNorm(const Char_t* name);
  AliAnalysisTaskFNorm& operator= (const AliAnalysisTaskFNorm& c);
  AliAnalysisTaskFNorm(const AliAnalysisTaskFNorm& c);
  virtual ~AliAnalysisTaskFNorm();

  // ANALYSIS FRAMEWORK STUFF to loop on data and fill output objects
  void UserExec(Option_t *option);
  void Terminate(Option_t *);
  void UserCreateOutputObjects();
  void SetAnalysisType(const char* type) {fkAnalysisType=type;}
  
 protected:
  
  const char* fkAnalysisType; //ESD or AOD based analysis
  TList *fTriggerList;  // output file
  
  
  ClassDef(AliAnalysisTaskFNorm,1);
};

#endif


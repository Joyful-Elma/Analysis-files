

// This code works for W/o physics selection

//#ifndef AliAnalysisTaskFNorm_CXX
//#define AliAnalysisTaskFNorm_CXX
#include <TCanvas.h>
#include <TF1.h>
#include <TH1.h>
#include <TLatex.h>
#include <TList.h>
#include <TStyle.h>
#include <TFileMergeInfo.h>
#include <TClassTable.h>
#include <TLorentzVector.h>
#include "AliAnalysisTaskFNorm.h"
#include "AliAnalysisTaskSE.h"
#include "AliAnalysisManager.h"
#include "AliTrackReference.h"
#include "AliESDEvent.h"
#include "AliESDMuonTrack.h"
#include "AliESD.h"
#include "AliVEvent.h"
#include "AliInputEventHandler.h"
#include "AliStack.h"
#include "AliLog.h"
#include "AliHeader.h"
#include "AliESDHeader.h"
#include "AliStack.h"
#include "TParticle.h"
#include "TLorentzVector.h"
#include "AliESDMuonTrack.h"
#include "AliESDInputHandler.h"
#include "AliAODEvent.h"
#include "AliAODHeader.h"
#include "AliAODHandler.h"
#include "AliAODInputHandler.h"
#include "TClonesArray.h"
#include "AliAODTrack.h"
#include "AliRunLoader.h"
#include "AliLoader.h"
#include "AliMUONHit.h"
#include "AliMUONVDigit.h"
#include "AliMUONRawCluster.h"
#include "AliMUONTrack.h"
ClassImp(AliAnalysisTaskFNorm)

//__________________________________________________________________________
AliAnalysisTaskFNorm::AliAnalysisTaskFNorm() :
  fkAnalysisType(0x0),
  fTriggerList(0)
  
{
}
//___________________________________________________________________________
AliAnalysisTaskFNorm::AliAnalysisTaskFNorm(const Char_t* name) :
  AliAnalysisTaskSE(name),
  fkAnalysisType(0x0),
  fTriggerList(0)
  
{
  //
  // Constructor. Initialization of Inputs and Outputs
  //
  Info("AliAnalysisTaskFNorm","Calling Constructor");
  
  DefineOutput(1,TList::Class());
  
}

//___________________________________________________________________________
AliAnalysisTaskFNorm& AliAnalysisTaskFNorm::operator=(const AliAnalysisTaskFNorm& c)
{
  //
  // Assignment operator
  //
  if (this!=&c) {
    AliAnalysisTaskSE::operator=(c) ;
  }
  return *this;
}

//___________________________________________________________________________
AliAnalysisTaskFNorm::AliAnalysisTaskFNorm(const AliAnalysisTaskFNorm& c) :
  AliAnalysisTaskSE(c),
  fkAnalysisType(c.fkAnalysisType),
  fTriggerList(c.fTriggerList)
  
  
 {
  //
  // Copy Constructor										
  //
}

//___________________________________________________________________________
AliAnalysisTaskFNorm::~AliAnalysisTaskFNorm() {
  //
  //destructor
  //
  Info("~AliAnalysisTaskFNorm","Calling Destructor");

  if (fTriggerList){
    delete fTriggerList;
    fTriggerList = 0;
  }
  
  
}

//___________________________________________________________________________
void AliAnalysisTaskFNorm::UserCreateOutputObjects(){
 
 // output objects creation	 

 fTriggerList = new TList();
 fTriggerList->SetOwner();
 
 TH1D *hNumberEvents = new TH1D("hNumberEvents","hNumberMuonEvents;N_{events}",100,0.,10.);
 TH1D *hNumberCMSH7 = new TH1D("hNumberCMSH7","hNumberCMSH7;N_{#mu events}",100,0.,10.);
 TH1D *hNumberCMSL7 = new TH1D("hNumberCMSL7","hNumberCMSL7;N_{#mu events}",100,0.,10.);
 TH1D *hNumberCINT7 = new TH1D("hNumberCINT7","hNumberCINT7;N_{MB}",100,0.,10.);
 TH1D *hNumberC0TVX = new TH1D("hNumberC0TVX","hNumberC0TVX;N_{MB}",100,0.,10.);
 TH1D *hNumber0TVX = new TH1D("hNumber0TVX","hNumber0TVX;N_{MB}",100,0.,10.);
 TH1D *hNumber0MSH = new TH1D("hNumber0MSH","hNumber0MSH;N_{MB}",100,0.,10.);
 TH1D *hNumber0MSL = new TH1D("hNumber0MSL","hNumber0MSL;N_{MB}",100,0.,10.);
 TH1D *hNumberCINT7_0MSH   = new TH1D("hNumberCINT7_0MSH","hNumberCINT7_0MSH;N_{CINT7&0MSH}",100,0,10.);
 TH1D *hNumberCMSL7_0MSH   = new TH1D("hNumberCMSL7_0MSH","hNumberCMSL7_0MSH;N_{CMSL7&0MSH}",100,0,10.);
 TH1D *hNumberCINT7_0MSL   = new TH1D("hNumberCINT7_0MSL","hNumberCINT7_0MSL;N_{CINT7&0MSL}",100,0,10.);
 TH1D *hNumberCINT7_0TVX   = new TH1D("hNumberCINT7_0TVX","hNumberCINT7_0TVX;N_{CINT7&0MSH}",100,0,10.);
 
 TH1D *hNumberEventsperrun = new TH1D("hNumberEventsperrun","hNumberMuonEventsperrun",100,0.,100.);
 TH1D *hNumberCMSH7perrun = new TH1D("hNumberCMSH7perrun","hNumberCMSH7perrun",100,0.,100.);
 TH1D *hNumberCMSL7perrun = new TH1D("hNumberCMSL7perrun","hNumberCMSL7perrun",100,0.,100.);
 TH1D *hNumberCINT7perrun = new TH1D("hNumberCINT7perrun","hNumberCINT7perrun",100,0.,100.);
 TH1D *hNumberC0TVXperrun = new TH1D("hNumberC0TVXperrun","hNumberC0TVXperrun",100,0.,100.);
 TH1D *hNumber0TVXperrun = new TH1D("hNumber0TVXperrun","hNumber0TVXperrun",100,0.,100.);
 TH1D *hNumber0MSHperrun = new TH1D("hNumber0MSHperrun","hNumber0MSHperrun",100,0.,100.);
 TH1D *hNumber0MSLperrun = new TH1D("hNumber0MSLperrun","hNumber0MSLperrun",100,0.,100.);
 TH1D *hNumberCINT7_0MSHperrun   = new TH1D("hNumberCINT7_0MSHperrun","hNumberCINT7_0MSHperrun",100,0,100.);
 TH1D *hNumberCMSL7_0MSHperrun   = new TH1D("hNumberCMSL7_0MSHperrun","hNumberCMSL7_0MSHperrun",100,0,100.);
 TH1D *hNumberCINT7_0MSLperrun   = new TH1D("hNumberCINT7_0MSLperrun","hNumberCINT7_0MSLperrun",100,0,100.);
 TH1D *hNumberCINT7_0TVXperrun   = new TH1D("hNumberCINT7_0TVXperrun","hNumberCINT7_0TVXperrun",100,0,100.);
 
    
 TH1D *hNumberCMSH7_WPS = new TH1D("hNumberCMSH7_WPS","hNumberCMSH7_WPS;N_{#mu events}",100,0.,10.);
 TH1D *hNumberCMSL7_WPS = new TH1D("hNumberCMSL7_WPS","hNumberCMSL7_WPS;N_{#mu events}",100,0.,10.);
 TH1D *hNumberCINT7_WPS = new TH1D("hNumberCINT7_WPS","hNumberCINT7_WPS;N_{MB}",100,0.,10.);
 TH1D *hNumberC0TVX_WPS = new TH1D("hNumberC0TVX_WPS","hNumberC0TVX_WPS;N_{MB}",100,0.,10.);
 TH1D *hNumber0TVX_WPS = new TH1D("hNumber0TVX_WPS","hNumber0TVX_WPS;N_{MB}",100,0.,10.);
 TH1D *hNumber0MSH_WPS = new TH1D("hNumber0MSH_WPS","hNumber0MSH_WPS;N_{MB}",100,0.,10.);
 TH1D *hNumber0MSL_WPS = new TH1D("hNumber0MSL_WPS","hNumber0MSL_WPS;N_{MB}",100,0.,10.);
 TH1D *hNumberCINT7_0MSH_WPS   = new TH1D("hNumberCINT7_0MSH_WPS","hNumberCINT7_0MSH_WPS;N_{CINT7&0MSH}",100,0,10.);
 TH1D *hNumberCMSL7_0MSH_WPS   = new TH1D("hNumberCMSL7_0MSH_WPS","hNumberCMSL7_0MSH_WPS;N_{CMSL7&0MSH}",100,0,10.);
 TH1D *hNumberCINT7_0MSL_WPS   = new TH1D("hNumberCINT7_0MSL_WPS","hNumberCINT7_0MSL_WPS;N_{CINT7&0MSL}",100,0,10.);
 TH1D *hNumberCINT7_0TVX_WPS   = new TH1D("hNumberCINT7_0TVX_WPS","hNumberCINT7_0TVX_WPS;N_{CINT7&0MSH}",100,0,10.);
 
 
    
 TH1D *hNumberCMSH7_WPSperrun = new TH1D("hNumberCMSH7_WPSperrun","hNumberCMSH7_WPSperrun",100,0.,100.);
 TH1D *hNumberCMSL7_WPSperrun = new TH1D("hNumberCMSL7_WPSperrun","hNumberCMSL7_WPSperrun",100,0.,100.);
 TH1D *hNumberCINT7_WPSperrun = new TH1D("hNumberCINT7_WPSperrun","hNumberCINT7_WPSperrun",100,0.,100.);
 TH1D *hNumberC0TVX_WPSperrun = new TH1D("hNumberC0TVX_WPSperrun","hNumberC0TVX_WPSperrun",100,0.,100.);
 TH1D *hNumber0TVX_WPSperrun = new TH1D("hNumber0TVX_WPSperrun","hNumber0TVX_WPSperrun",100,0.,100.);
 TH1D *hNumber0MSH_WPSperrun = new TH1D("hNumber0MSH_WPSperrun","hNumber0MSH_WPSperrun",100,0.,100.);
 TH1D *hNumber0MSL_WPSperrun = new TH1D("hNumber0MSL_WPSperrun","hNumber0MSL_WPSperrun",100,0.,100.);
 TH1D *hNumberCINT7_0MSH_WPSperrun   = new TH1D("hNumberCINT7_0MSH_WPSperrun","hNumberCINT7_0MSH_WPSperrun",100,0,100.);
 TH1D *hNumberCMSL7_0MSH_WPSperrun   = new TH1D("hNumberCMSL7_0MSH_WPSperrun","hNumberCMSL7_0MSH_WPSperrun",100,0,100.);
 TH1D *hNumberCINT7_0MSL_WPSperrun   = new TH1D("hNumberCINT7_0MSL_WPSperrun","hNumberCINT7_0MSL_WPSperrun",100,0,100.);
 TH1D *hNumberCINT7_0TVX_WPSperrun   = new TH1D("hNumberCINT7_0TVX_WPSperrun","hNumberCINT7_0TVX_WPSperrun",100,0,100.);
    
 fTriggerList->Add(hNumberEvents);
 fTriggerList->Add(hNumberCMSH7);
 fTriggerList->Add(hNumberCMSL7);
 fTriggerList->Add(hNumberCINT7);
 fTriggerList->Add(hNumberC0TVX);
 fTriggerList->Add(hNumber0TVX);
 fTriggerList->Add(hNumber0MSH);
 fTriggerList->Add(hNumber0MSL);
 fTriggerList->Add(hNumberCINT7_0MSH);
 fTriggerList->Add(hNumberCMSL7_0MSH);
 fTriggerList->Add(hNumberCINT7_0MSL);
 fTriggerList->Add(hNumberCINT7_0TVX);
 
 fTriggerList->Add(hNumberEventsperrun);
 fTriggerList->Add(hNumberCMSH7perrun);
 fTriggerList->Add(hNumberCMSL7perrun);
 fTriggerList->Add(hNumberCINT7perrun);
 fTriggerList->Add(hNumberC0TVXperrun);
 fTriggerList->Add(hNumber0TVXperrun);
 fTriggerList->Add(hNumber0MSHperrun);
 fTriggerList->Add(hNumber0MSLperrun);
 fTriggerList->Add(hNumberCINT7_0MSHperrun);
 fTriggerList->Add(hNumberCMSL7_0MSHperrun);
 fTriggerList->Add(hNumberCINT7_0MSLperrun);
 fTriggerList->Add(hNumberCINT7_0TVXperrun);
 
fTriggerList->Add(hNumberCMSH7_WPS);
fTriggerList->Add(hNumberCMSL7_WPS);
fTriggerList->Add(hNumberCINT7_WPS);
fTriggerList->Add(hNumberC0TVX_WPS);
fTriggerList->Add(hNumber0TVX_WPS);
fTriggerList->Add(hNumber0MSH_WPS);
fTriggerList->Add(hNumber0MSL_WPS);
fTriggerList->Add(hNumberCINT7_0MSH_WPS);
fTriggerList->Add(hNumberCMSL7_0MSH_WPS);
fTriggerList->Add(hNumberCINT7_0MSL_WPS);
fTriggerList->Add(hNumberCINT7_0TVX_WPS);

fTriggerList->Add(hNumberCMSH7_WPSperrun);
fTriggerList->Add(hNumberCMSL7_WPSperrun);
fTriggerList->Add(hNumberCINT7_WPSperrun);
fTriggerList->Add(hNumberC0TVX_WPSperrun);
fTriggerList->Add(hNumber0TVX_WPSperrun);
fTriggerList->Add(hNumber0MSH_WPSperrun);
fTriggerList->Add(hNumber0MSL_WPSperrun);
fTriggerList->Add(hNumberCINT7_0MSH_WPSperrun);
fTriggerList->Add(hNumberCMSL7_0MSH_WPSperrun);
fTriggerList->Add(hNumberCINT7_0MSL_WPSperrun);
fTriggerList->Add(hNumberCINT7_0TVX_WPSperrun);

    
fTriggerList->ls();
  
 PostData(1,fTriggerList);
 
} 

//_________________________________________________
void AliAnalysisTaskFNorm::UserExec(Option_t *)
{
     Int_t Event=0;
     AliAODEvent *aod=0x0;
  
    aod = dynamic_cast<AliAODEvent*> (InputEvent());
    if ( ! aod ) {
      AliError("Cannot get AOD event");
      return;    
    }   
  
  
  Int_t runNr = aod->GetRunNumber();

    Event++;
    ((TH1D*)(fTriggerList->FindObject("hNumberEvents")))->Fill(Event);
    
    ((TH1D*)(fTriggerList->FindObject("hNumberEventsperrun")))->Fill(Form("%d",runNr),1);
  
   TString trigger = aod->GetFiredTriggerClasses();
   Int_t triggerClass = -1;
    
   //W/o Physics Selection
    //Trigger part
    Int_t TrigEventCINT7=0;
    Int_t TrigEventCMSL7=0;
    Int_t TrigEventCMSH7=0;
    Int_t TrigEventC0TVX=0;
    Int_t TrigEventCINT7_0MSL=0;
    Int_t TrigEventCINT7_0MSH=0;
    Int_t TrigEventCMSL7_0MSH=0;
    Int_t TrigEventCINT7_0TVX=0;
    
    Int_t TrigEventCINT7_WPS=0;
    Int_t TrigEventCMSL7_WPS=0;
    Int_t TrigEventCMSH7_WPS=0;
    Int_t TrigEventC0TVX_WPS=0;
    Int_t TrigEventCINT7_0MSL_WPS=0;
    Int_t TrigEventCINT7_0MSH_WPS=0;
    Int_t TrigEventCMSL7_0MSH_WPS=0;
    Int_t TrigEventCINT7_0TVX_WPS=0;
    
    //inputmask part
    Int_t nofMSH = 0;
    Int_t nofMSL = 0;
    Int_t nofTVX = 0;
    
    Int_t nofMSH_WPS = 0;
    Int_t nofMSL_WPS = 0;
    Int_t nofTVX_WPS = 0;
  
   UInt_t inpmask = aod->GetHeader()->GetL0TriggerInputs();
    
    // check if 0TVX is fired
    Int_t input0TVX = 3;
    Int_t is0TVXfired = (inpmask & (1<<(input0TVX-1)));
    
    // check if 0MSL is fired
    Int_t input0MSL = 20;
    Int_t is0MSLfired = (inpmask & (1<<(input0MSL-1)));
    
    // check if 0MSH is fired
    Int_t input0MSH = 21;
    Int_t is0MSHfired = (inpmask & (1<<(input0MSH-1)));
       
   //
  
  Bool_t isSelected = (((AliInputEventHandler*)(AliAnalysisManager::GetAnalysisManager()->GetInputEventHandler()))->IsEventSelected() & AliVEvent::kAny); // 

  Bool_t isSelected_MB = (((AliInputEventHandler*)(AliAnalysisManager::GetAnalysisManager()->GetInputEventHandler()))->IsEventSelected()& AliVEvent::kMB);
 
  Bool_t isSelected_MSL = (((AliInputEventHandler*)(AliAnalysisManager::GetAnalysisManager()->GetInputEventHandler()))->IsEventSelected()& AliVEvent::kMuonSingleLowPt7);
    
  Bool_t isSelected_MSH = (((AliInputEventHandler*)(AliAnalysisManager::GetAnalysisManager()->GetInputEventHandler()))->IsEventSelected()& AliVEvent::kMuonSingleHighPt7);
   
    if(is0TVXfired){
        nofTVX++;
        ((TH1D*)(fTriggerList->FindObject("hNumber0TVX")))->Fill(nofTVX);
        ((TH1D*)(fTriggerList->FindObject("hNumber0TVXperrun")))->Fill(Form("%d",runNr),1);
    }
    if(is0MSLfired){
        nofMSL++;
        ((TH1D*)(fTriggerList->FindObject("hNumber0MSL")))->Fill(nofMSL);
        ((TH1D*)(fTriggerList->FindObject("hNumber0MSLperrun")))->Fill(Form("%d",runNr),1);
    }
    
    if(is0MSHfired){
        nofMSH++;
        ((TH1D*)(fTriggerList->FindObject("hNumber0MSH")))->Fill(nofMSH);
        ((TH1D*)(fTriggerList->FindObject("hNumber0MSHperrun")))->Fill(Form("%d",runNr),1);
    }
    
    if ((trigger.Contains("CINT7-B-NOPF-MUFAST"))){
        TrigEventCINT7++;
        ((TH1D*)(fTriggerList->FindObject("hNumberCINT7")))->Fill(TrigEventCINT7);
        ((TH1D*)(fTriggerList->FindObject("hNumberCINT7perrun")))->Fill(Form("%d",runNr),1);
    }
    
    if ((trigger.Contains("C0TVX-B-NOPF-CENTNOTRD"))){
        TrigEventC0TVX++;
        ((TH1D*)(fTriggerList->FindObject("hNumberC0TVX")))->Fill(TrigEventC0TVX);
        ((TH1D*)(fTriggerList->FindObject("hNumberC0TVXperrun")))->Fill(Form("%d",runNr),1);
    }
    
    if ((trigger.Contains("CMSL7-B-NOPF-MUFAST"))){
        TrigEventCMSL7++;
        ((TH1D*)(fTriggerList->FindObject("hNumberCMSL7")))->Fill(TrigEventCMSL7);
        ((TH1D*)(fTriggerList->FindObject("hNumberCMSL7perrun")))->Fill(Form("%d",runNr),1);
    }
    
    if ((trigger.Contains("CMSH7-B-NOPF-MUFAST"))){
        TrigEventCMSH7++;
        ((TH1D*)(fTriggerList->FindObject("hNumberCMSH7")))->Fill(TrigEventCMSH7);
        ((TH1D*)(fTriggerList->FindObject("hNumberCMSH7perrun")))->Fill(Form("%d",runNr),1);
    }
    
    if ((trigger.Contains("CINT7-B-NOPF-MUFAST")) &&is0TVXfired){
        TrigEventCINT7_0TVX++;
        ((TH1D*)(fTriggerList->FindObject("hNumberCINT7_0TVX")))->Fill(TrigEventCINT7_0TVX);
        ((TH1D*)(fTriggerList->FindObject("hNumberCINT7_0TVXperrun")))->Fill(Form("%d",runNr),1);
    }
    
    if ((trigger.Contains("CINT7-B-NOPF-MUFAST")) &&is0MSLfired){
        TrigEventCINT7_0MSL++;
        ((TH1D*)(fTriggerList->FindObject("hNumberCINT7_0MSL")))->Fill(TrigEventCINT7_0MSL);
        ((TH1D*)(fTriggerList->FindObject("hNumberCINT7_0MSLperrun")))->Fill(Form("%d",runNr),1);
    }
    
    if ((trigger.Contains("CINT7-B-NOPF-MUFAST")) &&is0MSHfired){
        TrigEventCINT7_0MSH++;
        ((TH1D*)(fTriggerList->FindObject("hNumberCINT7_0MSH")))->Fill(TrigEventCINT7_0MSH);
        ((TH1D*)(fTriggerList->FindObject("hNumberCINT7_0MSHperrun")))->Fill(Form("%d",runNr),1);
    }
    
    if ((trigger.Contains("CMSL7-B-NOPF-MUFAST"))&&is0MSHfired){
        TrigEventCMSL7_0MSH++;
        ((TH1D*)(fTriggerList->FindObject("hNumberCMSL7_0MSH")))->Fill(TrigEventCMSL7_0MSH);
        ((TH1D*)(fTriggerList->FindObject("hNumberCMSL7_0MSHperrun")))->Fill(Form("%d",runNr),1);
    }

 //__________________________________________________________________________________________________________________
    
 //_________________________________________________*****  Physics Selection Applied *****__________________________
      if(is0TVXfired && isSelected){
          nofTVX_WPS++;
          ((TH1D*)(fTriggerList->FindObject("hNumber0TVX_WPS")))->Fill(nofTVX_WPS);
          ((TH1D*)(fTriggerList->FindObject("hNumber0TVX_WPSperrun")))->Fill(Form("%d",runNr),1);
      }
      if(is0MSLfired && isSelected){
          nofMSL_WPS++;
          ((TH1D*)(fTriggerList->FindObject("hNumber0MSL_WPS")))->Fill(nofMSL_WPS);
          ((TH1D*)(fTriggerList->FindObject("hNumber0MSL_WPSperrun")))->Fill(Form("%d",runNr),1);
      }
      
      if(is0MSHfired && isSelected){
          nofMSH_WPS++;
          ((TH1D*)(fTriggerList->FindObject("hNumber0MSH_WPS")))->Fill(nofMSH_WPS);
          ((TH1D*)(fTriggerList->FindObject("hNumber0MSH_WPSperrun")))->Fill(Form("%d",runNr),1);
      }
      
      if ((trigger.Contains("CINT7-B-NOPF-MUFAST") &&isSelected)){
          TrigEventCINT7_WPS++;
          ((TH1D*)(fTriggerList->FindObject("hNumberCINT7_WPS")))->Fill(TrigEventCINT7_WPS);
          ((TH1D*)(fTriggerList->FindObject("hNumberCINT7_WPSperrun")))->Fill(Form("%d",runNr),1);
          }
    
      if ((trigger.Contains("C0TVX-B-NOPF-CENTNOTRD")) &&isSelected){
        TrigEventC0TVX_WPS++;
        ((TH1D*)(fTriggerList->FindObject("hNumberC0TVX_WPS")))->Fill(TrigEventC0TVX_WPS);
      }
    
      if ((trigger.Contains("CMSL7-B-NOPF-MUFAST")) &&isSelected){
          TrigEventCMSL7_WPS++;
          ((TH1D*)(fTriggerList->FindObject("hNumberCMSL7_WPS")))->Fill(TrigEventCMSL7_WPS);
          ((TH1D*)(fTriggerList->FindObject("hNumberCMSL7_WPSperrun")))->Fill(Form("%d",runNr),1);
      }
      
      if ((trigger.Contains("CMSH7-B-NOPF-MUFAST")) &&isSelected){
          TrigEventCMSH7_WPS++;
          ((TH1D*)(fTriggerList->FindObject("hNumberCMSH7_WPS")))->Fill(TrigEventCMSH7_WPS);
          ((TH1D*)(fTriggerList->FindObject("hNumberCMSH7_WPSperrun")))->Fill(Form("%d",runNr),1);
          }
    
      if ((trigger.Contains("CINT7-B-NOPF-CENT"))&&isSelected &&is0TVXfired ){
          TrigEventCINT7_0TVX_WPS++;
          ((TH1D*)(fTriggerList->FindObject("hNumberCINT7_0TVX_WPS")))->Fill(TrigEventCINT7_0TVX_WPS);
          ((TH1D*)(fTriggerList->FindObject("hNumberCINT7_0TVX_WPS")))->Fill(Form("%d",runNr),1);
      }
      
      if ((trigger.Contains("CINT7-B-NOPF-MUFAST")) &&isSelected &&is0MSLfired){
          TrigEventCINT7_0MSL_WPS++;
          ((TH1D*)(fTriggerList->FindObject("hNumberCINT7_0MSL_WPS")))->Fill(TrigEventCINT7_0MSL_WPS);
          ((TH1D*)(fTriggerList->FindObject("hNumberCINT7_0MSL_WPSperrun")))->Fill(Form("%d",runNr),1);
      }
      
      if ((trigger.Contains("CINT7-B-NOPF-MUFAST")) &&isSelected &&is0MSHfired){
          TrigEventCINT7_0MSH_WPS++;
          ((TH1D*)(fTriggerList->FindObject("hNumberCINT7_0MSH_WPS")))->Fill(TrigEventCINT7_0MSH_WPS);
          ((TH1D*)(fTriggerList->FindObject("hNumberCINT7_0MSH_WPSperrun")))->Fill(Form("%d",runNr),1);
      }
      
      if ((trigger.Contains("CMSL7-B-NOPF-MUFAST")) &&isSelected &&is0MSHfired){
          TrigEventCMSL7_0MSH_WPS++;
          ((TH1D*)(fTriggerList->FindObject("hNumberCMSL7_0MSH_WPS")))->Fill(TrigEventCMSL7_0MSH_WPS);
          ((TH1D*)(fTriggerList->FindObject("hNumberCMSL7_0MSH_WPSperrun")))->Fill(Form("%d",runNr),1);
      }

 PostData(1,fTriggerList );
    
}//main loop
   
//________________________________________________________________________
void AliAnalysisTaskFNorm::Terminate(Option_t *)
{
  
  fTriggerList = dynamic_cast<TList*> (GetOutputData(1));
  if(!fTriggerList)
    cerr<<"TList corrupted "<<endl;
    
     
}


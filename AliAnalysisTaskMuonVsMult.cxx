/**************************************************************************
 * Copyright(c) 1998-1999, ALICE Experiment at CERN, All rights reserved. *
 *                                                                        *
 * Author: The ALICE Off-line Project.                                    *
 * Contributors are mentioned in the code where appropriate.              *
 *                                                                        *
 * Permission to use, copy, modify and distribute this software and its   *
 * documentation strictly for non-commercial purposes is hereby granted   *
 * without fee, provided that the above copyright notice appears in all   *
 * copies and that both the copyright notice and this permission notice   *
 * appear in the supporting documentation. The authors make no claims     *
 * about the suitability of this software for any purpose. It is          *
 * provided "as is" without express or implied warranty.                  *
 **************************************************************************/

//include root libraries
#include <TCanvas.h>
#include <TList.h>
#include <TH1.h>
#include <TH2.h>
#include <TH3.h>
#include <TProfile.h>
#include <TChain.h>
#include "TMath.h"
#include <TObjArray.h>
#include <TRandom3.h>
#include <THnSparse.h>
//include aliroot libraries
#include "AliLog.h"
#include "AliAnalysisManager.h"
#include "AliAODv0.h"
#include "AliVEvent.h"
#include "AliESDEvent.h"
#include "AliAODEvent.h"
#include "AliVVZERO.h"
#include "AliESDVZERO.h"
#include "AliAODVZERO.h"
#include "AliVVertex.h"
#include "AliESDVertex.h"
#include "AliAODVertex.h"
#include "AliAnalysisMuonUtility.h"
#include "AliAnalysisUtils.h"
#include "AliMuonTrackCuts.h"
#include "AliMuonEventCuts.h"
#include "AliOADBMuonTrackCutsParam.h"
#include "AliCentrality.h"
#include "AliVTrack.h"
#include "AliAODTrack.h"
#include "AliAODTracklets.h"
#include "AliAODHeader.h"
#include "AliESDMuonTrack.h"
#include "AliInputEventHandler.h"
#include "AliAnalysisManager.h"
#include "AliAODMCParticle.h"
#include "AliVertexingHFUtils.h"
#include "AliCounterCollection.h"
#include "AliTriggerAnalysis.h"
//include the class header file
#include "AliAnalysisTaskMuonVsMult.h"

#include "AliAODMCHeader.h"
#include "AliGenEventHeader.h"
#include "AliGenHijingEventHeader.h"
#include "AliGenDPMjetEventHeader.h"
#include "AliGenPythiaEventHeader.h"
#include "AliGenCocktailEventHeader.h"


ClassImp(AliAnalysisTaskMuonVsMult)

//====================================================================================================================================================================
AliAnalysisTaskMuonVsMult::AliAnalysisTaskMuonVsMult()
   : AliAnalysisTaskSE(),
    fUtils(0x0),
    fMuonTrackCuts(0x0),
    fMuonEventCuts(0x0),
    fTriggerAnalysis(0x0),
//    //
//    fRunCounters(0x0),
    fEventCounters(0x0),
    fTrackletsBin(0),
    fSTrackletsBin(0x0),
//    //
    hEventsPerRun(0x0),
    hEventsCounter(0x0),
    hMBEventsCounter(0x0),
    hSingleMu(0x0),
    hAcceptedMuons(0x0),
    hPtEta(0x0),
    hPtThetaAbs(0x0),
    hMatchTrigger(0x0),
    hPdca(0x0),
    // tracklets
    hTrackletsPerEvent(0x0),
    hTrackletsVsZVertex(0x0),
    hMeanTrackletsVsZVertex(0x0),
    hMBTrackletsVsZVertex(0x0),
    hMBMeanTrackletsVsZVertex(0x0),
    hMBTrackletsPerEvent(0x0),
    // vertexZ
    hVertexZ(0x0),
    hPrimaryVertexZ(0x0),
    hSigmaVertexZVsNContrib(0x0),
    hVertexZAccepted(0x0),
    hPrimaryVertexZAccepted(0x0),
    hSigmaVertexZNContribAccepted(0x0),
    hVertexZVsEta(0x0),
    hVertexZVsPhi(0x0),
    hMBVertexZ(0x0),
    hMBPrimaryVertexZ(0x0),
    hMBSigmaVertexZVsNContrib(0x0),
    hMBVertexZAccepted(0x0),
    hMBPrimaryVertexZAccepted(0x0),
    hMBSigmaVertexZNContribAccepted(0x0),
    hMBVertexZVsEta(0x0),
    //
    fSPDMeanTracklets(0x0),
    hReferenceProfile(0x0),
    // raw tracklets
    hRawTrackletsPerEvent(0x0),
    hRawTrackletsVsZVertex(0x0),
    hMBRawTrackletsVsZVertex(0x0),
    hMeanRawTrackletsVsZVertex(0x0),
    hMBMeanRawTrackletsVsZVertex(0x0),
    hMBRawTrackletsPerEvent(0x0),
    //
    hCorrectedVsRawTracklets(0x0),
    hMBCorrectedVsRawTracklets(0x0),
    hNcorrVsEta(0x0),
    hNrawVsEta(0x0),
    hMBNcorrVsEta(0x0),
    hMBNrawVsEta(0x0),
    ////
    listPhysics(0x0),
    listEvents(0x0),
    listSPDTracklets(0x0),
    //
    fMinEtaForTracklets(-3.8),
    fMaxEtaForTracklets(-1.7),

    fMinEtaForTracklets1(2.8),
    fMaxEtaForTracklets1(5.1),
//     fMeanTrRef(-1),
    fMinContrib(1),
    fMaxZRes(0.25),
    fIsMC(kFALSE),
    fPileUp(kFALSE),
    fMinEtaMuon(-4.),
    fMaxEtaMuon(-2.5),
    fRand(0x0),
    //
    fPDGmassJPsi1S(3.096916),
    fSigmaJpsi1S(0.07),
    //
    fNContribSpdPu(0),
    fDistanceSpdPu(0.),
    fPuMode(0)
    //fTriggerofEvent(0)
{
   // Dummy constructor ALWAYS needed for I/O.
}

//====================================================================================================================================================================
AliAnalysisTaskMuonVsMult::AliAnalysisTaskMuonVsMult(const char *name, const bool IsMC, const bool ApplyPUCuts/*, double MeanTrRef*/)
  : AliAnalysisTaskSE(name),
    fUtils(0x0),
    fTriggerAnalysis(new AliTriggerAnalysis("TriggerAnalysisPerso")),
    //
//    fRunCounters(0x0),
    fEventCounters(0x0),
    fTrackletsBin(0),
    fSTrackletsBin(0x0),
    //
    hEventsPerRun(0x0),
    hEventsCounter(0x0),
    hMBEventsCounter(0x0),
    hSingleMu(0x0),
   hAcceptedMuons(0x0),
   hPtEta(0x0),
   hPtThetaAbs(0x0),
   hMatchTrigger(0x0),
   hPdca(0x0),
    // tracklets
    hTrackletsPerEvent(0x0),
    hTrackletsVsZVertex(0x0),
    hMeanTrackletsVsZVertex(0x0),
    hMBTrackletsVsZVertex(0x0),
    hMBMeanTrackletsVsZVertex(0x0),
    hMBTrackletsPerEvent(0x0),
    // vertexZ
    hVertexZ(0x0),
    hPrimaryVertexZ(0x0),
    hSigmaVertexZVsNContrib(0x0),
    hVertexZAccepted(0x0),
    hPrimaryVertexZAccepted(0x0),
    hSigmaVertexZNContribAccepted(0x0),
    hVertexZVsEta(0x0),
    hVertexZVsPhi(0x0),
    hMBVertexZ(0x0),
    hMBPrimaryVertexZ(0x0),
    hMBSigmaVertexZVsNContrib(0x0),
    hMBVertexZAccepted(0x0),
    hMBPrimaryVertexZAccepted(0x0),
    hMBSigmaVertexZNContribAccepted(0x0),
    hMBVertexZVsEta(0x0),
    //
    fSPDMeanTracklets(0x0),
    hReferenceProfile(0x0),
    // raw tracklets
    hRawTrackletsPerEvent(0x0),
    hRawTrackletsVsZVertex(0x0),
    hMBRawTrackletsVsZVertex(0x0),
    hMeanRawTrackletsVsZVertex(0x0),
    hMBMeanRawTrackletsVsZVertex(0x0),
    hMBRawTrackletsPerEvent(0x0),
    //
    hCorrectedVsRawTracklets(0x0),
    hMBCorrectedVsRawTracklets(0x0),
    hNcorrVsEta(0x0),
    hNrawVsEta(0x0),
    hMBNcorrVsEta(0x0),
    hMBNrawVsEta(0x0),
    ////
    listPhysics(0x0),
    listEvents(0x0),
    listSPDTracklets(0x0),
    //
    fMuonEventCuts(new AliMuonEventCuts("stdEventCuts","stdEventCuts")),
    fMuonTrackCuts(new AliMuonTrackCuts("stdMuonCuts","stdMuonCuts")),
//     fMeanTrRef(MeanTrRef),
    fMinContrib(1),
    fMaxZRes(0.25),
    fMinEtaForTracklets(-3.8),
    fMaxEtaForTracklets(-1.7),

    fMinEtaForTracklets1(2.8),
    fMaxEtaForTracklets1(5.1),
    fIsMC(IsMC),
    fPileUp(ApplyPUCuts),
    fMinEtaMuon(-4.),
    fMaxEtaMuon(-2.5),
    fRand(0x0),
    //
    fPDGmassJPsi1S(3.096916),
    fSigmaJpsi1S(0.07),
    //
    fNContribSpdPu(0),
    fDistanceSpdPu(0.),
    fPuMode(-1)
    //fTriggerofEvent(triggerofevent)
{
  fUtils = new AliAnalysisUtils();
   // Input slot #0 works with a TChain - it is connected to the default input container
  DefineInput(0, TChain::Class());
  DefineOutput(1, AliCounterCollection::Class());
  DefineOutput(2, TList::Class());                                            // for output objarray
  DefineOutput(3, TList::Class());                                            // for output objarray
  DefineOutput(4, TList::Class()); 
 


}

//====================================================================================================================================================================
AliAnalysisTaskMuonVsMult::~AliAnalysisTaskMuonVsMult()
{
   // Destructor. Clean-up the output list, but not the histograms that are put inside
   // (the list is owner and will clean-up these histograms). Protect in PROOF case.
   if (!AliAnalysisManager::GetAnalysisManager()->IsProofMode()) {
       if (listPhysics) delete listPhysics;
       if (listEvents) delete listEvents;
       if (listSPDTracklets) delete listSPDTracklets;
       if (fEventCounters) delete fEventCounters;
   }

   if(fUtils) delete fUtils;
   delete fRand;
   delete fSPDMeanTracklets;

   delete fMuonTrackCuts;
   delete fMuonEventCuts;
   delete fTriggerAnalysis;
}

//====================================================================================================================================================================
void AliAnalysisTaskMuonVsMult::NotifyRun()
{
  /// Set run number for cuts
  fMuonTrackCuts->SetRun(fInputHandler);
}

//====================================================================================================================================================================
void AliAnalysisTaskMuonVsMult::UserCreateOutputObjects()
{
    listEvents = new TList();
    listEvents->SetOwner();

    listPhysics = new TList();
    listPhysics->SetOwner();

    listSPDTracklets = new TList();
    listSPDTracklets->SetOwner();

  //create event counters
  fEventCounters = new AliCounterCollection("eventCounters");
  fEventCounters->AddRubric("run",1000000);
  fEventCounters->AddRubric("trigger",1000000);
  fEventCounters->AddRubric("physsel", "yes/no");
  fEventCounters->AddRubric("isaccepted","yes/no");
  fEventCounters->AddRubric("ntracklets",1000000);
  fEventCounters->Init();

    Int_t pTNBins = 80;
    Float_t pTMinBin = 0.;
    Float_t pTMaxBin =80.;

    Int_t yNBins = 15;
    Float_t yMinBin = -4;
    Float_t yMaxBin = -2.5;

    Float_t nTrackMax = 350;
    float zmax = 20;
    float zNbins = 10*zmax; //200;
    float zcut = 10; 
 

    //definition of Events histograms
    Int_t runFirst =/* 266437 */265594;
    Int_t runLast = 267131 /* 266318i*/;
    Int_t nRuns = runLast-runFirst;

    hEventsPerRun = new TH1I("hEventsPerRun","Events per run", nRuns, runFirst, runLast);
    hEventsPerRun->SetStats(kTRUE);
    hEventsPerRun->GetYaxis()->SetTitle("Events");
    hEventsPerRun->Sumw2();
    listEvents->Add(hEventsPerRun);

    TString trigString = "CMSL7-B-NOPF-MUFAST";
    hEventsCounter = new TH1I("hEventsCounter","hEventsCounter CMSL",9,0,9);
    hEventsCounter->SetStats(kTRUE);
    hEventsCounter->Sumw2();
    TString counterLabel[] = { 
	    "All evts", 
	    trigString, 
	    trigString+" after PS", 
	    "IsPrimaryVertex", 
	    "IsSPDVertex", 
	    "nContrib(SPD) > 0", 
	    "#sigma_{z}^{SPD} < 0.25 cm", 
	    "|zVertex| < 10 cm",
        "Acc tracklet evnts"  
    };
    for(int i=0; i<9; i++){
        hEventsCounter->GetXaxis()->SetBinLabel(i+1, counterLabel[i].Data() );
    }
    listEvents->Add(hEventsCounter);

    trigString = "CINT7-B-NOPF-MUFAST";
    hMBEventsCounter = new TH1I("hMBEventsCounter","EventsCounter CINT7",9,0,9);
    hMBEventsCounter->SetStats(kTRUE);
    hMBEventsCounter->Sumw2();
    TString MBcounterLabel[] = { 
	    "All evts", 
	    trigString, 
	    trigString+" after PS", 
	    "IsPrimaryVertex", 
	    "IsSPDVertex", 
	    "nContrib(SPD) > 0", 
	    "#sigma_{z}^{SPD} < 0.25 cm", 
	    "|zVertex| < 10 cm",
        "Acc tracklet evnts"};
    for(int i=0; i<9; i++){
        hMBEventsCounter->GetXaxis()->SetBinLabel(i+1, MBcounterLabel[i].Data());
    }
    listEvents->Add(hMBEventsCounter);

//    //definition of Physics histograms
    
    //pt, eta, zv, mult, charge
  Int_t bins[kNvars] = {80,15,200,350,2};
  Double_t min[kNvars] = {0,-4,-10,0,-2};
  Double_t max[kNvars] = {80,-2.5,10,350,2};  
  
 hSingleMu = new THnSparseD("hn","hn",kNvars,bins,min,max);
 listPhysics->Add(hSingleMu);
 
 Float_t Nptbins =80;
 Float_t ptmin=0;
 Float_t ptmax=80;
 
   hAcceptedMuons= new TH1F("hAcceptedMuons","", Nptbins,ptmin, ptmax);
   AliAnalysisTaskMuonVsMult::SetHisto( hAcceptedMuons, "#it{p}_{T} (GeV/c)", "", listPhysics);

   hPtEta = new TH1F("hPtEta","", Nptbins, ptmin, ptmax);
   AliAnalysisTaskMuonVsMult::SetHisto( hPtEta, "#it{p}_{T} (GeV/c)", "", listPhysics);

   hPtThetaAbs= new TH1F("hPtThetaAbs","", Nptbins, ptmin, ptmax);
   AliAnalysisTaskMuonVsMult::SetHisto( hPtThetaAbs, "#it{p}_{T} (GeV/c)", "", listPhysics);
   
  hMatchTrigger= new TH1F("hMatchTrigger","", Nptbins, ptmin, ptmax);
   AliAnalysisTaskMuonVsMult::SetHisto( hMatchTrigger, "#it{p}_{T} (GeV/c)", "", listPhysics);
   
  hPdca= new TH1F("hPdca","", Nptbins, ptmin, ptmax);
   AliAnalysisTaskMuonVsMult::SetHisto( hPdca, "#it{p}_{T} (GeV/c)", "", listPhysics);

    // TRACKLETS histograms

   if(fSPDMeanTracklets){ 
	   hReferenceProfile = (TProfile*)fSPDMeanTracklets->Clone();
	   //hMeanTrackletsVsZVertex->SetName("hMeanTrackletsVsZVertex");
	   listSPDTracklets->Add(hReferenceProfile);
   }

   hTrackletsPerEvent = new TH1F("hTrackletsPerEvent","", nTrackMax, 0, nTrackMax);
   AliAnalysisTaskMuonVsMult::SetHisto( hTrackletsPerEvent, "N^{corr}", "", listSPDTracklets);

   hRawTrackletsPerEvent = new TH1F("hRawTrackletsPerEvent","N^{raw}",nTrackMax,0,nTrackMax);
   AliAnalysisTaskMuonVsMult::SetHisto( hRawTrackletsPerEvent, "N^{raw}", "", listSPDTracklets);


   hMeanTrackletsVsZVertex = new TProfile("hMeanTrackletsVsZVertex","",TMath::Nint(2*zcut/0.25),-zcut,zcut);
   AliAnalysisTaskMuonVsMult::SetHisto( hMeanTrackletsVsZVertex, "zVertex (cm)", "<N^{corr}>", listSPDTracklets);

   hMeanRawTrackletsVsZVertex = new TProfile("hMeanRawTrackletsVsZVertex","",TMath::Nint(2*zcut/0.25),-zcut,zcut);
   AliAnalysisTaskMuonVsMult::SetHisto( hMeanRawTrackletsVsZVertex, "zVertex (cm)", "<N^{raw}>", listSPDTracklets);

   hTrackletsVsZVertex = new TH2F("hTrackletsVsZVertex","", TMath::Nint(2*zcut/0.25),-zcut,zcut, nTrackMax, 0, nTrackMax);
   AliAnalysisTaskMuonVsMult::SetHisto( hTrackletsVsZVertex, "zVertex (cm)", "N^{corr}", listSPDTracklets);

   hRawTrackletsVsZVertex = new TH2F("hRawTrackletsVsZVertex", "", TMath::Nint(2*zcut/0.25),-zcut,zcut, nTrackMax, 0, nTrackMax);
   AliAnalysisTaskMuonVsMult::SetHisto( hRawTrackletsVsZVertex, "zVertex (cm)", "nTracklets^{raw}", listSPDTracklets);
   //listSPDTracklets->AddFirst(hRawTrackletsVsZVertex);

   fRand = new TRandom3(0);


   // MB histograms

   hMBRawTrackletsPerEvent = new TH1F("hMBRawTrackletsPerEvent","N^{raw}",nTrackMax,0,nTrackMax);
   AliAnalysisTaskMuonVsMult::SetHisto( hMBRawTrackletsPerEvent, "N^{raw}", "", listSPDTracklets);
   
   hMBTrackletsVsZVertex = new TH2F("hMBTrackletsVsZVertex","",zNbins,-zcut,zcut, nTrackMax, 0, nTrackMax);
   AliAnalysisTaskMuonVsMult::SetHisto( hMBTrackletsVsZVertex, "zVertex (cm)", "nTracklets^{corr}", listSPDTracklets);

   hMBRawTrackletsVsZVertex = new TH2F("hMBRawTrackletsVsZVertex","corrected N_tr vs zVertex (CINT)",zNbins,-zcut,zcut, nTrackMax, 0, nTrackMax);
   AliAnalysisTaskMuonVsMult::SetHisto(hMBRawTrackletsVsZVertex, "zVertex (cm)", "nTracklets^{raw}", listSPDTracklets);

   hCorrectedVsRawTracklets = new TH2F("hCorrectedVsRawTracklets", "N^{corr} - N^{raw}", nTrackMax, 0, nTrackMax, nTrackMax, 0, nTrackMax);
   AliAnalysisTaskMuonVsMult::SetHisto( hCorrectedVsRawTracklets, "N^{raw}", "N^{corr}", listSPDTracklets);

   hMBCorrectedVsRawTracklets = new TH2F("hMBCorrectedVsRawTracklets", "N^{corr} - N^{raw} (CINT)", nTrackMax, 0, nTrackMax, nTrackMax, 0, nTrackMax);
   AliAnalysisTaskMuonVsMult::SetHisto( hMBCorrectedVsRawTracklets, "N^{raw}", "N^{corr}", listSPDTracklets);

   hMBMeanTrackletsVsZVertex = new TProfile("hMBMeanTrackletsVsZVertex","",TMath::Nint(2*zcut/0.25),-zcut,zcut);
   hMBMeanTrackletsVsZVertex->GetXaxis()->SetTitle("zVertex (cm)");
   hMBMeanTrackletsVsZVertex->GetYaxis()->SetTitle("<N^{corr}>");
   listSPDTracklets->Add(hMBMeanTrackletsVsZVertex);

   hMBMeanRawTrackletsVsZVertex = new TProfile("hMBMeanRawTrackletsVsZVertex","",TMath::Nint(2*zcut/0.25),-zcut,zcut);
   hMBMeanRawTrackletsVsZVertex->GetXaxis()->SetTitle("zVertex (cm)");
   hMBMeanRawTrackletsVsZVertex->GetYaxis()->SetTitle("<N^{raw}>");
   listSPDTracklets->Add(hMBMeanRawTrackletsVsZVertex); 

   hMBTrackletsPerEvent = new TH1F("hMBTrackletsPerEvent","", nTrackMax, 0, nTrackMax);
   hMBTrackletsPerEvent->SetStats(kTRUE);
   hMBTrackletsPerEvent->GetXaxis()->SetTitle("nTracklets^{corr}");
   hMBTrackletsPerEvent->Sumw2();
   listSPDTracklets->Add(hMBTrackletsPerEvent);
    


//    float etaNbins = 300;
//    float etaMax = 3;
//    hEta = new TH1F("hEta","",etaNbins,-etaMax,etaMax);
//    AliAnalysisTaskMuonVsMult::SetHisto( hEta, "eta", "", listSPDTracklets);
// 
//    float phimin = 0;
//    float phimax = 2*TMath::Pi();
//    int phiNbins = TMath::Nint( (phimax-phimin)/0.1 );
//    hPhi = new TH1F( "hPhi", "", phiNbins, phimin, phimax);
//    AliAnalysisTaskMuonVsMult::SetHisto( hPhi, "phi", "", listSPDTracklets);
// 
   // Vertex QA
   float zdiff = 5;
   int nContribMax = 50;

    
   hVertexZ = new TH1F("hVertexZ","", zNbins, -zmax, zmax);
   AliAnalysisTaskMuonVsMult::SetHisto( hVertexZ, "zVertex (cm)", "", listSPDTracklets);
   
    hMBVertexZ = new TH1F("hMBVertexZ","", zNbins, -zmax, zmax);
   AliAnalysisTaskMuonVsMult::SetHisto( hMBVertexZ, "zVertex (cm)", "", listSPDTracklets);

   hPrimaryVertexZ = new TH1F("hPrimaryVertexZ", "",zNbins,-zmax,zmax);
   AliAnalysisTaskMuonVsMult::SetHisto( hPrimaryVertexZ, "zVertex^{p} (cm)","", listSPDTracklets);
   
   hMBPrimaryVertexZ = new TH1F("hMBPrimaryVertexZ", "",zNbins,-zmax,zmax);
   AliAnalysisTaskMuonVsMult::SetHisto( hPrimaryVertexZ, "zVertex^{p} (cm)","", listSPDTracklets);


   hSigmaVertexZVsNContrib = new TH2F("hSigmaVertexZVsNContrib","hSigmaVertexZVsNContrib before cut",nContribMax,0,nContribMax,1000,0,10);
   AliAnalysisTaskMuonVsMult::SetHisto(hSigmaVertexZVsNContrib, "n_{contrib}", "sigma_{z}^{SPD} (cm)", listSPDTracklets);

   hMBSigmaVertexZVsNContrib = new TH2F("hMBSigmaVertexZVsNContrib","hMBSigmaVertexZVsNContrib before cut",nContribMax,0,nContribMax,1000,0,10);
   AliAnalysisTaskMuonVsMult::SetHisto( hMBSigmaVertexZVsNContrib, "n_{contrib}", "sigma_{z}^{SPD} (cm)",listSPDTracklets);



    PostData(1,fEventCounters);
    PostData(2, listEvents);
    PostData(3, listSPDTracklets);
    PostData(4, listPhysics);


}

//=====================================================================================================================
void AliAnalysisTaskMuonVsMult::UserExec(Option_t *)
{
    AliAODEvent *aod = 0;
    //AliESDEvent *esd = 0;
    AliAODVertex* vertex = NULL;
    AliAODVertex* vertexSPD = NULL;
    AliVEvent* aodesd = NULL;

    Bool_t physSel = kFALSE;
    Bool_t physSelMB = kFALSE;
    Bool_t trigSel = kFALSE;
    Bool_t IsVertex = kTRUE;
    Bool_t IsPrimaryVertex = kTRUE;
    TString strFiredTriggers;

    Bool_t accept = kTRUE;
    
    
    
    //Check if the event is AOD or ESD
    if (AliAnalysisMuonUtility::IsAODEvent(InputEvent())){
        aod = static_cast<AliAODEvent *>(InputEvent());
        strFiredTriggers = aod->GetFiredTriggerClasses();
    }
    else{
        AliError("ERROR: Could not retrieve AOD event !!");
        return;
    }

    //return;
    
    aodesd = static_cast<AliVEvent *>(InputEvent());
    vertex = const_cast<AliAODVertex *>(aod->GetPrimaryVertex()); // gives primary vertex!!!
    vertexSPD = const_cast<AliAODVertex *>(aod->GetPrimaryVertexSPD()); //gives SPD vertex

    

    int runNumber = aod->GetRunNumber();
    if( !fIsMC ) hEventsPerRun->Fill(runNumber);
    hEventsCounter->Fill(0);
    
    if( !fIsMC ) hMBEventsCounter->Fill(0);


    UInt_t IsSelected = (((AliInputEventHandler*)(AliAnalysisManager::GetAnalysisManager()->GetInputEventHandler()))->IsEventSelected());

    // CINT7 triggered events
    if(strFiredTriggers.Contains( "CINT7-B-NOPF-MUFAST") ){
      
       trigSel = kTRUE;
       hMBEventsCounter->Fill(1);


     if ((IsSelected & AliVEvent::kINT7inMUON)) {
	     hMBEventsCounter->Fill(2);
	     physSelMB = kTRUE;
    }

   } // end of if CINT7
   // CMSL7 triggered events
   if( strFiredTriggers.Contains("CMSL7-B-NOPF-MUFAST") ){
       
       trigSel = kTRUE;
       hEventsCounter->Fill(1);

     if ((IsSelected & AliVEvent::kMuonSingleLowPt7) ) {
         physSel = kTRUE;
	 hEventsCounter->Fill(2);
        }

   } // end of if CMSL7

   
   
   int ncorr = -1; // this way if not accepted and thus no correction -> will be excluded from counting
//    TString selected = "";
//    selected = (IsSelected) ? "physsel:yes" : "physsel:no";
   //TString selectedMB = (physSelMB) ? "physselmb:yes" : "physselmb:no";
   TString isaccepted = "isaccepted:no";// ( accept ) ? "isaccepted:yes" : "isaccepted:no";
	
     

	// primary vertex - no cut on primary vertex
	int nContributorsPrimary = vertex->GetNContributors();
	double zVertexPrim = vertex->GetZ();	
	if( vertex && nContributorsPrimary >= fMinContrib ) IsPrimaryVertex = kTRUE;
	if( physSel ){
		
		hPrimaryVertexZ->Fill( zVertexPrim );
		if( IsPrimaryVertex ) hEventsCounter->Fill(3);

	}
	
	if( physSelMB ){
		
		hMBPrimaryVertexZ->Fill( zVertexPrim );
		if( IsPrimaryVertex ) hMBEventsCounter->Fill(3);

	}


	// SPD vertex
	double zVertex = vertexSPD->GetZ();
	int nContributors = vertexSPD->GetNContributors();
	double cov[6] = {0};
	
	// is SPD vertex reconstructed?
	if( !vertexSPD ){ // && nContributors > fMinContrib ) { 
		IsVertex = kFALSE;
		accept = kFALSE;  // dont accept if no vertex
	}
	
	if( physSel && accept ) {
		
		hVertexZ->Fill( zVertex );		// fill in SPD zVtx before any cuts
		hEventsCounter->Fill(4);
		
	}
	
	if( physSelMB && accept ) {
// 		
		hMBVertexZ->Fill( zVertex );		// fill in SPD zVtx before any cuts define this histo
		hMBEventsCounter->Fill(4);
// 		
	}

        // is it properly reconstructed
	if(  nContributors < fMinContrib ){
		IsVertex = kFALSE;
		accept = kFALSE;
		//return;
	}

	if(physSel && accept) hEventsCounter->Fill(5);
	if(physSelMB && accept) hMBEventsCounter->Fill(5);
	

	// sigmaZ SPD vertex
	vertexSPD->GetCovarianceMatrix(cov);
	double zRes = TMath::Sqrt(cov[5]);
	//printf("\nzRes = %.3f cm\n",zRes);
	
	if( physSel && accept )   hSigmaVertexZVsNContrib->Fill( nContributors, zRes);
	if( physSelMB && accept ) hMBSigmaVertexZVsNContrib->Fill( nContributors, zRes);

	if(  zRes > fMaxZRes ) accept = kFALSE;	

	if( physSel && accept ) {
		
		hEventsCounter->Fill(6);
	}
	if( physSelMB && accept ) {
		
		hMBEventsCounter->Fill(6);
	}

	if( TMath::Abs(zVertex)>10 ) accept = kFALSE;

	if( accept){
		if( physSel ) hEventsCounter->Fill(7);
		if( physSelMB ) hMBEventsCounter->Fill(7);

	
		if( physSel ) hEventsCounter->Fill(8);
		if( physSelMB ) hMBEventsCounter->Fill(8);
	}


// SPD analysis get tracklet counts
         AliAODTracklets *trackletsData = (AliAODTracklets*) aod->GetTracklets();
         int nSPDTracklets = trackletsData->GetNumberOfTracklets();
 	 int count1 = 0;
     int count2 = 0;
     int count = 0;
	 double correctedCount = 0;
	 int genSPDprimaries = 0;


   if( accept ){ //applied all vertex cuts

	   isaccepted = "isaccepted:yes";

     count1 = AliVertexingHFUtils::GetNumberOfTrackletsInEtaRange(aod, fMinEtaForTracklets, fMaxEtaForTracklets);
     count2 = AliVertexingHFUtils::GetNumberOfTrackletsInEtaRange(aod, fMinEtaForTracklets1, fMaxEtaForTracklets1);
     count = count1 + count2;
// 	 correctedCount = AliAnalysisTaskMuonVsMult::GetTrackletsMeanCorrection( zVertex, count, fMeanTrRef );

// 	    // Eta loop
//            for(Int_t iTr=0; iTr<nSPDTracklets; iTr++){
//           
//                Double_t theta=trackletsData->GetTheta(iTr);
//                Double_t eta=-TMath::Log(TMath::Tan(theta/2.));
// 	       Double_t phi = trackletsData->GetPhi(iTr);
// 
//                if( physSel ){
// 		     
// 		     hEta->Fill(eta);
// 		     hPhi->Fill(phi);
// 	     
// 
// 	       }
  
           
  
// 	  if(correctedCount<300 && correctedCount>-1) 
// 	  ncorr = correctedCount; 

	 if( physSelMB ){ // start with CINT7
	
// 		hMBTrackletsPerEvent->Fill(correctedCount);		
		hMBRawTrackletsPerEvent->Fill(count);

// 	        hMBTrackletsVsZVertex->Fill( zVertex, correctedCount );
		hMBRawTrackletsVsZVertex->Fill( zVertex, count );
// 		hMBCorrectedVsRawTracklets->Fill( count, correctedCount );

// 		hMBMeanTrackletsVsZVertex->Fill( zVertex, correctedCount );
		hMBMeanRawTrackletsVsZVertex->Fill( zVertex, count );
		//
	 } // end if( CINT7 )

	 if( physSel ){ //fill muon histos

// 		 hTrackletsPerEvent->Fill(correctedCount);
		 hRawTrackletsPerEvent->Fill(count);

// 		 hTrackletsVsZVertex->Fill( zVertex, correctedCount );
		 hRawTrackletsVsZVertex->Fill( zVertex, count );
// 		 hCorrectedVsRawTracklets->Fill( count, correctedCount );

// 		 hMeanTrackletsVsZVertex->Fill( zVertex, correctedCount );
		 hMeanRawTrackletsVsZVertex->Fill( zVertex, count );

	 }
       
   }// end if accept

   
   // HF Muon analysis 
   
       if( physSelMB){
    
    Double_t data[kNvars];
    
    for ( Int_t iTracks = 0; iTracks < aod->GetNumberOfTracks(); iTracks++ ) {
    AliAODTrack* track = dynamic_cast<AliAODTrack*>(aod->GetTrack(iTracks));
    if (!track) {
      printf("ERROR: Could not receive track %d\n", iTracks);
      continue;   
      
    }
//  cout << "**************************again ************************" << endl;
         if(!track->IsMuonTrack()) continue;
         
         hAcceptedMuons->Fill(track->Pt());
        
         if(track->Eta() <-4 || track->Eta() >-2.5) continue;
          
          hPtEta->Fill(track->Pt());         
          
          if(track->GetRAtAbsorberEnd()<17.6 || track->GetRAtAbsorberEnd()>89.5) continue;
        
          hPtThetaAbs->Fill(track->Pt());
          
          if(!(track->GetMatchTrigger()==0)) continue;

          std::cout << "matchpt="  << track->GetMatchTrigger() << std::endl;
          
          hMatchTrigger->Fill(track->Pt());
         
          if(!fMuonTrackCuts->IsSelected(track)) continue;
          
          hPdca->Fill(track->Pt());    
          
    data[kPt] 	= track->Pt();
    data[kEta] 	= track->Eta();
    data[kCharge] = track->Charge()/3;
    data[kMult] = count;
    data[kVz] = vertex->GetZ();
   
   
    hSingleMu->Fill(data);
    
    
   }  

   
 } 
 
    PostData(1,fEventCounters);
    PostData(2, listEvents);
    PostData(3, listSPDTracklets);
    PostData(4, listPhysics);
 
 
 
}

//====================================================================================================================================================================
void AliAnalysisTaskMuonVsMult::Terminate(Option_t *)
{


    fEventCounters = dynamic_cast<AliCounterCollection *>(GetOutputData(1));
    if (!fEventCounters) { AliError("Could not retrieve AliCounterCollection* fEventCounters"); return; }

    listEvents = dynamic_cast<TList *>(GetOutputData(2));
    if (!listEvents) { AliError("Could not retrieve TList* listEvents"); return; }

    listSPDTracklets = dynamic_cast<TList *>(GetOutputData(3));
    if (!listSPDTracklets) { AliError("Could not retrieve TList* listSPDTracklets"); return; }

    listPhysics = dynamic_cast<TList *>(GetOutputData(4));
    if (!listPhysics) { AliError("Could not retrieve TList* listPhysics"); return; }


}
//________________________________________________________________________
// Bool_t AliAnalysisTaskMuonVsMult::IsAcceptedMuon(const TObject *obj){
// 
//     const AliVParticle* muonTrack = static_cast<const AliVParticle*> ( obj );
// 
//     Bool_t isMuon = AliAnalysisMuonUtility::IsMuonTrack(muonTrack);
//     if ( ! isMuon ) return kFALSE;
// 
//     if(!(AliAnalysisMuonUtility::MatchApt(muonTrack))) return kFALSE;
// 
//     return kTRUE;
// 
// }
//________________________________________________________________________
void AliAnalysisTaskMuonVsMult::SetHisto( TH1* h0, TString titleXaxis, TString titleYaxis, TList* list, int idx){

	h0->Sumw2();
	h0->SetStats(kTRUE);
	h0->GetXaxis()->SetTitle( titleXaxis );
	h0->GetYaxis()->SetTitle( titleYaxis );

	if(idx<0) list->AddLast(h0);
	else list->AddAt(h0,idx);

}
//________________________________________________________________________
void AliAnalysisTaskMuonVsMult::SetHisto( TH2* h0, TString titleXaxis, TString titleYaxis, TList* list, int idx){

	h0->Sumw2();
	h0->SetStats(kTRUE);
	h0->GetXaxis()->SetTitle( titleXaxis );
	h0->GetYaxis()->SetTitle( titleYaxis );

	if(idx<0) list->AddLast(h0);
	else list->AddAt(h0,idx);

}
//________________________________________________________________________
// void AliAnalysisTaskMuonVsMult::FillEta(AliAODTracklets *trackletsData, Double_t zvert){
// 
// 	int nSPDTracklets = trackletsData->GetNumberOfTracklets();
// 	if( nSPDTracklets<fMinContrib ) return;
// 
//    for(Int_t iTr=0; iTr<nSPDTracklets; iTr++){
//           
//            Double_t theta=trackletsData->GetTheta(iTr);
//            Double_t eta=-TMath::Log(TMath::Tan(theta/2.));
// 
//            hEta->Fill(eta);
// 
// 	   UInt_t IsSelected = (((AliInputEventHandler*)(AliAnalysisManager::GetAnalysisManager()->GetInputEventHandler()))->IsEventSelected());
// 	   if( IsSelected & AliVEvent::kINT7inMUON ) hMBVertexZVsEta->Fill( zvert , eta );
// 	   if( IsSelected & AliVEvent::kMuonSingleLowPt7 ) hVertexZVsEta->Fill( zvert , eta );
// 
//           
//     }   
// }

//________________________________________________________________________
Double_t AliAnalysisTaskMuonVsMult::GetTrackletsMeanCorrection(Double_t zvert, Int_t nTracklets, double nMeanTrackletsRef ) /*const*/
{
    Double_t correctedNtr = 0;
    TProfile* h(0x0); 

  if ( !fSPDMeanTracklets )
  {
    AliFatal("ERROR: No tracklets mean correction");
    return 0;
  }
  else{   

    h = (TProfile*)fSPDMeanTracklets->Clone();
    if(!h){
	    AliError("ERROR: TProfile didn't get loaded properly or was not set");
	    return 0;
    }
    AliInfo("\n Loaded fSPDMeanTracklets.\n");
  
    Double_t nMeanTrackletsZ = h->GetBinContent( h->FindBin(zvert) );

    Double_t deltaN = 0;
    if( nMeanTrackletsZ<=0 ) correctedNtr = -1000;
    else{
	  
	    Double_t meanPoiss = nTracklets* (nMeanTrackletsRef/nMeanTrackletsZ - 1);
	    deltaN = fRand->PoissonD( TMath::Abs(meanPoiss) );

	    correctedNtr = nTracklets + ( meanPoiss>0 ? 1 : -1)* deltaN;
    
    }

    delete h;

    if(correctedNtr<0) correctedNtr=0;

   return correctedNtr;
 
  } 

}

/*
 *simple HF muon Analysis task
 *
 */
 // last edit 2015-11-30
#ifndef ANALYSISTASKMULTIPLICITY_H
#define ANALYSISTASKMULTIPLICITY_H

class TH1F;
class TH2F;
class TH3F;
class TProfile;
class TList;
class TObjArray;
class TArrayF;
class TRandom3;

class AliAnalysisManager;
class AliVEvent;
class AliCounterCollection;
class AliMuonTrackCuts;
class AliMuonEventCuts;
class AliAnalysisUtils;
class AliTriggerAnalysis;

#ifndef ALIANALYSISTASKSE_H
#include "AliAnalysisTaskSE.h"
#endif

class AliAnalysisTaskMuonVsMult : public AliAnalysisTaskSE {
public:
    AliAnalysisTaskMuonVsMult();
    //AliAnalysisTaskMuonVsMult(const char *name, AliMuonTrackCuts* cuts, const bool IsMC, double MeanTrRef);
    AliAnalysisTaskMuonVsMult(const char *name,  const bool IsMC, const bool ApplyPUCuts/*, double MeanTrRef*/);
  /*  AliAnalysisTaskMuonVsMult(const char *name, const AliMuonTrackCuts& cuts, TProfile* spdMeanCorrection, const bool IsMC);
*/
    virtual ~AliAnalysisTaskMuonVsMult();
    virtual void     NotifyRun();
    virtual void     UserCreateOutputObjects();
    virtual void     UserExec(Option_t *option);
    virtual void     Terminate(Option_t *);

    void SetProfile( TProfile* tp ){ fSPDMeanTracklets = tp; }
//     Bool_t IsAcceptedMuon(const TObject *obj);
//     TLorentzVector MuonTrackToLorentzVector(const TObject *obj);
    void SetHisto( TH1* h0, TString titleXaxis, TString titleYaxis, TList* list, int idx = -1);
    void SetHisto( TH2* h0, TString titleXaxis, TString titleYaxis, TList* list, int idx = -1);
//     Int_t GetGeneratedInEtaRange( TClonesArray* arrayMC, Double_t mineta, Double_t maxeta );
//     void FillEta(AliAODTracklets *trackletsData, Double_t zvert);
//     void AnalyseGenerated( TClonesArray* array);
    Double_t GetTrackletsMeanCorrection(Double_t zvert, Int_t nTracklets, double nMeanTrackletsRef=20); /*const*/

//     TList* BuildListOfTrigger(const TObjArray*);
//     TList* BuildListOfTracklets(int nCorrectedTracklets);

    /// Get track cuts
    AliMuonTrackCuts* GetMuonTrackCuts() { return fMuonTrackCuts; }
    /// Get event cuts
    AliMuonEventCuts* GetMuonEventCuts() { return fMuonEventCuts; }

    AliMuonTrackCuts *fMuonTrackCuts;  
    AliMuonEventCuts *fMuonEventCuts; 
    // set SPD pile up cut
    void SetSPDPileUpCut( Int_t ncontr = 0, Double_t dist = 0. ){ fNContribSpdPu = ncontr; fDistanceSpdPu = dist; }
    // get trigger analysis
    AliTriggerAnalysis* GetTriggerAnalysis() { return fTriggerAnalysis; }

    // pile-up cuts added by hand
//     Bool_t IsSPDClusterVsTrackletBG(const AliVEvent* event, TString trigger, Int_t fillHists=1);
    void SetPileUpMode( Int_t pumode = -1 ){ fPuMode = pumode; }
    //void SetBeamConfig( Int_t beamconfig ){}
    ////**************************************** 
    // PILE-UP MODE - controls applied pile-up cuts
    // -1 = no pile-up cut (default)
    //  0 = V0PF
    //  1 = +SPD (default MultiBins)
    //  2 = +TrackletsVsClusters
    ////****************************************
//    void SetPileUpCuts( TString spucuts = "" ){ fSPileUpCuts = spucuts };

//protected:



private:

 enum{ // EventCounterHsitogram bins
	 kAllEvents,
	 kTrigger,//kCMUL7Trig,
	 kTriggerPhysSel,//kCMUL7PhysSel,
	 kIsPileUpV0PF,
	 kIsPileUpSPD,
	 kIsPileUpV0OnOff,
	 kIsPileUpSPDOnOff,
	 kIsPileUpZDCTime,
	 kIsPileUpV0VsSPD,
	 kIsSPDBG,
//	 kCustomPhysSel,
	 kPrimaryVertex,
	 kVertex,
	 kVertexContrib, 
	 kSigmaVertexZ,
         kVertexCut,
         //
	 kAcceptedTrackletsEvt,
	 kIsDimuon,
	 kRapidityCut,
	 kJpsisMultLeft,
	 kLastCounterBin
 };

 //enum VertexQAHisto {};

    
    AliAnalysisUtils *fUtils; //!
    AliTriggerAnalysis *fTriggerAnalysis;

//  AliCounterCollection *fRunCounters;//! run counters
  AliCounterCollection *fEventCounters;//! event counters
  TArrayI fTrackletsBin; //ntracklets range for event counters
  TObjArray *fSTrackletsBin; //array of ntracklets bins


  //  UInt_t fTriggerofEvent;// = 0;
//     Double_t fMeanTrRef;
    Int_t fMinContrib;
    Double_t fMaxZRes;
    Double_t fMinEtaForTracklets;
    Double_t fMaxEtaForTracklets;
    Double_t fMinEtaForTracklets1;
    Double_t fMaxEtaForTracklets1;
    Double_t fMinEtaMuon;
    Double_t fMaxEtaMuon;
    Bool_t fIsMC;
    Bool_t fPileUp;
    TRandom3 *fRand;
    Float_t fPDGmassJPsi1S;
    Float_t fSigmaJpsi1S;
    //
    Int_t fNContribSpdPu;
    Double_t fDistanceSpdPu;
    Int_t fPuMode;

    //declaration of the events histograms
    TH1I *hEventsPerRun; //!
    TH1I *hEventsCounter; //!
    TH1I* hMBEventsCounter; //!

    //declaration of the physics histograms
    THnSparse *hSingleMu;
    TH1F *hAcceptedMuons;
    TH1F *hPtEta;
    TH1F *hPtThetaAbs;
    TH1F *hMatchTrigger;
    TH1F *hPdca;    
    

    // tracklets
    TH1F *hTrackletsPerEvent;		//!
    TH1F* hRawTrackletsPerEvent;	//!
    TH1F* hMBTrackletsPerEvent;		//!
    TH1F* hMBRawTrackletsPerEvent;	//!
    //
   
    TH2F* hNcorrVsEta;			//!
    TH2F* hNrawVsEta;			//!
    TH2F* hMBNcorrVsEta;			//!
    TH2F* hMBNrawVsEta;			//!
    TH2F* hVertexZVsEta;		//!
    TH2F* hVertexZVsPhi;		//!
    TH2F* hMBVertexZVsEta;		//!
    // Vertex QA
    TH1F* hVertexZ;			//!
    TH1F* hPrimaryVertexZ;		//!
    TH1F* hVertexZAccepted;		//!
    TH2F* hSigmaVertexZVsNContrib;	//!
    TH1F* hPrimaryVertexZAccepted;	//!
    TH2F* hSigmaVertexZNContribAccepted; //!
    //
    TH1F* hMBVertexZ;			//!
    TH1F* hMBPrimaryVertexZ;		//!
    TH2F* hMBSigmaVertexZVsNContrib;	//!
    TH1F* hMBVertexZAccepted;		//!
    TH1F* hMBPrimaryVertexZAccepted;	//!
    TH2F* hMBSigmaVertexZNContribAccepted; //!
    //
    TProfile* hReferenceProfile;
    TProfile* hMeanTrackletsVsZVertex;	
    TProfile* hMBMeanTrackletsVsZVertex;	
    TProfile* hMeanRawTrackletsVsZVertex;	
    TProfile* hMBMeanRawTrackletsVsZVertex;
    TH2F* hTrackletsVsZVertex;		//!
    TH2F* hMBTrackletsVsZVertex;	//!
    TProfile* fSPDMeanTracklets; 
    TH2F* hRawTrackletsVsZVertex;		//!
    TH2F* hCorrectedVsRawTracklets;	//!
    TH2F* hMBRawTrackletsVsZVertex; //!
    TH2F* hMBCorrectedVsRawTracklets;	//!
  
  enum{kPt,kEta,kVz,kMult,kCharge,kNvars};
  enum listList{ 
	    kDefaultContainer,
	    kListEvents, 
	    kListSPDTracklets,
	    kListPhysics,
    };

    TList* listPhysics;                
    TList* listEvents;              
    TList* listSPDTracklets;		

    ClassDef(AliAnalysisTaskMuonVsMult,1);
};

#endif

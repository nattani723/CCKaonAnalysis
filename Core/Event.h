#ifndef _Event2_h_
#define _Event2_h_

#include <vector>

#include "TVector3.h"

#include "SimParticle.h"
#include "RecoParticle.h"

using std::vector;
using std::string;

struct Event {

	bool IsData=false;
	UInt_t EventID;
	Int_t run;
	Int_t subrun;
	Int_t event;
	Int_t fileID;
	double Weight=1.0;

        // Flags applying to the entire event
  Bool_t EventIsSignal = false;
  Bool_t EventIsSignal_NuMuP = false;
  Bool_t EventIsSignal_PiPPi0 = false;
  Bool_t EventHasKaonPScatter = false;
  Bool_t EventHasHyperon = false;
  Bool_t EventHasKaon = false;
  Bool_t EventHasKaonP = false;
  Bool_t EventHasKaonP_NuMuP = false;
  Bool_t EventHasKaonP_PiPPi0 = false;
  Bool_t EventHasKaonM = false;
  Bool_t EventHasKaon0 = false;

        // Flags for each MCTruth
        vector<string> Mode;
        vector<string> CCNC;
        Int_t NMCTruths;
        Int_t NMCTruthsInTPC;
        vector<bool> InActiveTPC;
        vector<bool> IsHyperon;
  vector<bool> IsKaon;
  vector<bool> IsKaonP;
  vector<bool> IsKaonP_NuMuP;
  vector<bool> IsKaonP_PiPPi0;
  vector<bool> IsKaonP_2PiPPiM;
  vector<bool> IsKaonP_ENuE;
  vector<bool> IsKaonP_2PiNPiP;
  vector<bool> IsKaonP_Others;
  vector<bool> IsKaonM;
  vector<bool> IsKaon0;
  vector<bool> IsAssociatedKaonP;
  vector<bool> IsSignal;
  vector<bool> IsSignal_NuMuP;
  vector<bool> IsSignal_PiPPi0;
  Bool_t GoodReco;
  Bool_t GoodReco_NuMuP;
  Bool_t GoodReco_PiPPi0;
  Bool_t GoodPrimaryReco;
  Bool_t GoodRecoAsShower;

        vector<TVector3> TruePrimaryVertex;

	//true variables
	std::vector<SimParticle> Neutrino;
	std::vector<SimParticle> Lepton;
	std::vector<SimParticle> PrimaryHyperon;
  std::vector<SimParticle> PrimaryNucleon;
  std::vector<SimParticle> PrimaryPion;
  std::vector<SimParticle> PrimaryKaon;
  std::vector<SimParticle> PrimaryKaonP;
  std::vector<SimParticle> PrimaryKaonM;
  std::vector<SimParticle> PrimaryNucleus;
  std::vector<SimParticle> HyperonDecay;
  std::vector<SimParticle> KaonPDecay;
  std::vector<SimParticle> KaonPDecay_NuMuP;
  std::vector<SimParticle> KaonPDecay_PiPPi0;
  std::vector<SimParticle> KaonMDecay;
  std::vector<SimParticle> Kaon0Decay;
  std::vector<SimParticle> NeutralKaonDecayK0SL;

        vector<TVector3> DecayVertex;

	TVector3 RecoPrimaryVertex;
  Bool_t PassNuCCInclusiveFilter;
	Int_t NPrimaryDaughters;
	Int_t NPrimaryTrackDaughters;
	Int_t NPrimaryShowerDaughters;
  Int_t NOtherTracks;
  Int_t NOtherRebuiltTracks;
  Int_t NOtherShowers;

	std::vector<RecoParticle> TrackPrimaryDaughters;
	std::vector<RecoParticle> ShowerPrimaryDaughters;
  std::vector<RecoParticle> TrackOthers;
  std::vector<RecoParticle> TrackRebuiltOthers;
  std::vector<RecoParticle> ShowerOthers;

	int TrueMuonIndex;
	int TrueKaonIndex;
	int TrueDecayMuonIndex;
	int TrueDecayPionIndex;

	// Muon, proton and pion candidates
	RecoParticle MuonCandidate;
	RecoParticle KaonCandidate;
	RecoParticle DecayMuonCandidate;
	RecoParticle DecayPionCandidate;

	Float_t SelectorBDTScore;
	Float_t AnalysisBDTScore;
    
        vector<string> SysDials;
        vector<vector<double>> SysWeights;
  //vector<vector<vector<double>>> SysWeights;

        void Print(){ std::cout << run << "  " << subrun << "  " << event << std::endl; }

};

#endif

#ifndef _EventAssembler2_h_
#define _EventAssembler2_h_

#include <vector>

#include "TFile.h"
#include "TTree.h"
#include "TLorentzVector.h"
#include "TVector3.h"

#include "SimParticle.h"
#include "RecoParticle.h"
#include "Event.h"

using std::vector;
using std::string;

///////////////////////////////////////////////////////////////////////////////////////////////

class EventAssembler {

   private:

      // Input file and event tree
      TFile * f_in=nullptr;
      TTree * t_in;

      TTree *t_meta;
      Double_t POT;

      // Number of events (entries in event tree)
      int nEvents;

      TString DataDir;

   public:

      EventAssembler();
      EventAssembler(bool loadweights);

      // Setters and getters
      void SetFile(string infilename,string sampletype);
      void Close();

      Event GetEvent(int i);
      Long64_t GetNEvents();
      double GetPOT();		

   private:

      std::string SampleType;
      const bool LoadWeights;

      // General Info
      Bool_t          IsData;
      UInt_t          EventID;
      Int_t           run;
      Int_t           subrun;
      Int_t           event;
      Double_t        Weight;

      // Event flags
      vector<string>* Mode=0;
      vector<string>* CCNC=0;
      Int_t NMCTruths;
      Int_t NMCTruthsInTPC;
      vector<bool>* InActiveTPC=0;
      vector<bool>* IsHyperon=0;
      vector<bool>* IsKaon=0;
      vector<bool>* IsKaonP=0;
      vector<bool>* IsKaonP_NuMuP=0;
      vector<bool>* IsKaonP_PiPPi0=0;
      vector<bool>* IsKaonP_2PiPPiM=0;
      vector<bool>* IsKaonP_ENuE=0;
      vector<bool>* IsKaonP_2PiNPiP=0;
      vector<bool>* IsKaonP_Others=0;
      vector<bool>* IsKaonM=0;
      vector<bool>* IsKaon0=0;
      vector<bool>* IsAssociatedKaonP=0;
      vector<bool>* IsSignal=0;
      vector<bool>* IsSignal_NuMuP=0;
      vector<bool>* IsSignal_PiPPi0=0;

      Bool_t GoodReco;
      Bool_t GoodReco_NuMuP;
      Bool_t GoodReco_PiPPi0;
      Bool_t GoodPrimaryReco;
      Bool_t GoodRecoAsShower;
      Bool_t EventHasKaonPScatter;
      Bool_t EventHasHyperon;
      Bool_t EventHasKaon;
      Bool_t EventHasKaonP;
      Bool_t EventHasKaonP_NuMuP;
      Bool_t EventHasKaonP_PiPPi0;
      Bool_t EventHasKaonM;
      Bool_t EventHasKaon0;

      // Truth variables
      std::vector<SimParticle>* Neutrino=0;
      std::vector<SimParticle>* Lepton=0;
      std::vector<SimParticle>* PrimaryHyperon=0;

      std::vector<SimParticle>* PrimaryNucleon=0;
      std::vector<SimParticle>* PrimaryPion=0;
      std::vector<SimParticle>* PrimaryKaon=0;
      std::vector<SimParticle>* PrimaryKaonP=0;
      std::vector<SimParticle>* PrimaryKaonM=0;
      std::vector<SimParticle>* PrimaryNucleus=0;
      std::vector<SimParticle>* HyperonDecay=0;
      std::vector<SimParticle>* KaonPDecay=0;
      std::vector<SimParticle>* KaonPDecay_NuMuP=0;
      std::vector<SimParticle>* KaonPDecay_PiPPi0=0;
      std::vector<SimParticle>* KaonMDecay=0;
      std::vector<SimParticle>* Kaon0Decay=0;
      std::vector<SimParticle>* NeutralKaonDecayK0SL=0;

      vector<double>  *TruePrimaryVertex_X=0;
      vector<double>  *TruePrimaryVertex_Y=0;
      vector<double>  *TruePrimaryVertex_Z=0;
      vector<double>  *DecayVertex_X=0;
      vector<double>  *DecayVertex_Y=0;
      vector<double>  *DecayVertex_Z=0;

      // Reco variables
      Bool_t PassNuCCInclusiveFilter;
      Int_t NPrimaryDaughters;
      Int_t NPrimaryTrackDaughters;
      Int_t NPrimaryShowerDaughters;
      Int_t NOtherTracks;
      Int_t NOtherRebuiltTracks;
      Int_t NOtherShowers;

      TVector3* RecoPrimaryVertex=0;
      std::vector<RecoParticle>* TracklikePrimaryDaughters=0;
      std::vector<RecoParticle>* ShowerlikePrimaryDaughters=0;
      std::vector<RecoParticle>* TrackOthers=0;
      std::vector<RecoParticle>* TrackRebuiltOthers=0;
      std::vector<RecoParticle>* ShowerOthers=0;

      // Systematics
      vector<string>* SysDials=0;
      vector<vector<vector<double>>>* SysWeights=0;
};

///////////////////////////////////////////////////////////////////////////////////////////////

#endif

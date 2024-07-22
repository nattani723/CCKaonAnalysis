R__LOAD_LIBRARY($HYP_TOP/lib/libHyperon.so)
R__LOAD_LIBRARY($HYP_TOP/lib/libParticleDict.so)

#include "SelectionManager.h"
#include "EventAssembler.h"
#include "Cut.h"
#include "SelectionParameters.h"

#include "TEfficiency.h"
#include "DrawEfficiencyPlot.h"

#include "Parameters.h"
#include "SampleSets_Example.h"

   // Generates efficiency curves for every stage of the selection
   // against a variety of different variables to monitor any
   // phase space dependence in the selection

   void PhaseSpaceTest(){

      BuildTunes();

      std::string label = "SignalPhaseSpace";

      const double POT = 1e21; // POT to scale samples to
      const int Mode = kFHC;

      SelectionParameters P = P_FHC_K_NOBDT_TEST;

      // Setup selection manager. Set POT to scale sample to
      EventAssembler E;
      SelectionManager M(P);
      M.SetPOT(POT);
      //M.ImportBDTWeights(P.p_BDTCutBDT_WeightsDir);

      /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

      // All Cuts //

      TH1D *h_Q2_All = new TH1D("h_Q2_All","",60,0,3.0);
      TH1D *h_SelectedQ2_All = new TH1D("h_SelectedQ2_All","",60,0,3.0);
      TEfficiency* Efficiency_Q2_All = new TEfficiency("Q2_eff_All",";True Q^{2} (GeV^{2});Selected/All",60,0,3.0);

      TH1D *h_NuE_All = new TH1D("h_TrueNuE_All","",20,0,4.0);
      TH1D *h_SelectedNuE_All = new TH1D("h_SelectedNuE_All","",20,0,4.0);
      TEfficiency* Efficiency_NuE_All = new TEfficiency("NuE_eff_All",";True E_{#nu} (GeV);Selected/All",20,0,4.0);

      TH1D *h_MuonKE_All = new TH1D("h_MuonKE_All","",60,0,3.0);
      TH1D *h_SelectedMuonKE_All = new TH1D("h_SelectedMuonKE_All","",60,0,3.0);
      TEfficiency* Efficiency_MuonKE_All = new TEfficiency("MuonKE_eff_All",";True Muon KE (GeV);Selected/All",60,0,3.0);

      TH1D *h_MuonTrueTheta_All = new TH1D("h_MuonTrueTheta_All","",60,0,3.1415);
      TH1D *h_SelectedMuonTrueTheta_All = new TH1D("h_SelectedMuonTrueTheta_All","",60,0,3.1415);
      TEfficiency* Efficiency_MuonTrueTheta_All = new TEfficiency("MuonTrueTheta_eff_All",";Muon True #theta;Selected/All",60,0,3.1415);

      TH1D *h_MuonDetectorTheta_All = new TH1D("h_TrueMuonDetectorTheta_All","",60,0,3.1415);
      TH1D *h_SelectedMuonDetectorTheta_All = new TH1D("h_SelectedMuonDetectorTheta_All","",60,0,3.1415);
      TEfficiency* Efficiency_MuonDetectorTheta_All = new TEfficiency("MuonDetectorTheta_eff",";Muon Detector #theta;Selected/All",60,0,3.1415);

      TH1D *h_MuonDetectorPhi_All = new TH1D("h_TrueMuonDetectorPhi_All","",60,-3.1415,3.1415);
      TH1D *h_SelectedMuonDetectorPhi_All = new TH1D("h_SelectedMuonDetectorPhi_All","",60,-3.1415,3.1415);
      TEfficiency* Efficiency_MuonDetectorPhi_All = new TEfficiency("MuonDetectorPhi_eff_All",";Muon Detector #theta;Selected/All",60,-3.1415,3.1415);

      TH1D *h_MuonBeamTheta_All = new TH1D("h_TrueMuonBeamTheta_All","",60,0,3.1415);
      TH1D *h_SelectedMuonBeamTheta_All = new TH1D("h_SelectedMuonBeamTheta_All","",60,0,3.1415);
      TEfficiency* Efficiency_MuonBeamTheta_All = new TEfficiency("MuonBeamTheta_eff_All",";Muon Beam #theta;Selected/All",60,0,3.1415);

      TH1D *h_MuonBeamPhi_All = new TH1D("h_TrueMuonBeamPhi_All","",60,-3.1415,3.1415);
      TH1D *h_SelectedMuonBeamPhi_All = new TH1D("h_SelectedMuonBeamPhi_All","",60,-3.1415,3.1415);
      TEfficiency* Efficiency_MuonBeamPhi_All = new TEfficiency("MuonBeamPhi_eff_All",";Muon Beam #theta;Selected/All",60,-3.1415,3.1415);

      TH1D *h_KaonMomentum_All = new TH1D("h_TrueKaonMomentum_All","",25,0.0,2.5);
      TH1D *h_SelectedKaonMomentum_All = new TH1D("h_SelectedKaonMomentum_All","",25,0.0,2.5);
      TEfficiency* Efficiency_KaonMomentum_All = new TEfficiency("KaonMomentum_eff_All",";True K^{+} Momentum (GeV/c);Selected/All",25,0.0,2.5);

      TH1D *h_DecayMuonMomentum_All = new TH1D("h_TrueDecayMuonMomentum_All","",60,0.3,1.5);
      TH1D *h_SelectedDecayMuonMomentum_All = new TH1D("h_SelectedDecayMuonMomentum_All","",60,0.3,1.5);
      TEfficiency* Efficiency_DecayMuonMomentum_All = new TEfficiency("DecayMuonMomentum_eff_All",";True  Decay #mu^{+} Momentum (GeV/c);Selected/All",60,0.3,1.5);

      TH1D *h_DecayPionMomentum_All = new TH1D("h_TrueDecayPionMomentum_All","",60,0.1,0.8);
      TH1D *h_SelectedDecayPionMomentum_All = new TH1D("h_SelectedDecayPionMomentum_All","",60,0.1,0.8);
      TEfficiency* Efficiency_DecayPionMomentum_All = new TEfficiency("DecayPionMomentum_eff_All",";True Decay #pi^{+} Momentum (GeV/c);Selected/All",60,0.1,0.8);

      TH1D *h_All = new TH1D("h_All","",1,0,1.0);
      TH1D *h_Selected_All = new TH1D("h_Selected_All","",1,0,1.0);
      TEfficiency* Efficiency_All = new TEfficiency("eff_All",";;Selected/All",1,0,1.0);


      // Fiducial Volume Cut //

      TH1D *h_Q2_FV = new TH1D("h_Q2_FV","",60,0,3.0);
      TH1D *h_SelectedQ2_FV = new TH1D("h_SelectedQ2_FV","",60,0,3.0);
      TEfficiency* Efficiency_Q2_FV = new TEfficiency("Q2_eff_FV",";True Q^{2} (GeV^{2});Selected/All",60,0,3.0);

      TH1D *h_NuE_FV = new TH1D("h_TrueNuE_FV","",60,0,4.0);
      TH1D *h_SelectedNuE_FV = new TH1D("h_SelectedNuE_FV","",60,0,4.0);
      TEfficiency* Efficiency_NuE_FV = new TEfficiency("NuE_eff_FV",";True E_{#nu} (GeV);Selected/All",60,0,4.0);

      TH1D *h_MuonKE_FV = new TH1D("h_MuonKE_FV","",60,0,3.0);
      TH1D *h_SelectedMuonKE_FV = new TH1D("h_SelectedMuonKE_FV","",60,0,3.0);
      TEfficiency* Efficiency_MuonKE_FV = new TEfficiency("MuonKE_eff_FV",";True Muon KE (GeV);Selected/All",60,0,3.0);

      TH1D *h_MuonTrueTheta_FV = new TH1D("h_MuonTrueTheta_FV","",60,0,3.1415);
      TH1D *h_SelectedMuonTrueTheta_FV = new TH1D("h_SelectedMuonTrueTheta_FV","",60,0,3.1415);
      TEfficiency* Efficiency_MuonTrueTheta_FV = new TEfficiency("MuonTrueTheta_eff_FV",";Muon True #theta;Selected/All",60,0,3.1415);

      TH1D *h_MuonDetectorTheta_FV = new TH1D("h_TrueMuonDetectorTheta_FV","",60,0,3.1415);
      TH1D *h_SelectedMuonDetectorTheta_FV = new TH1D("h_SelectedMuonDetectorTheta_FV","",60,0,3.1415);
      TEfficiency* Efficiency_MuonDetectorTheta_FV = new TEfficiency("MuonDetectorTheta_eff_FV",";Muon Detector #theta;Selected/All",60,0,3.1415);

      TH1D *h_MuonDetectorPhi_FV = new TH1D("h_TrueMuonDetectorPhi_FV","",60,-3.1415,3.1415);
      TH1D *h_SelectedMuonDetectorPhi_FV = new TH1D("h_SelectedMuonDetectorPhi_FV","",60,-3.1415,3.1415);
      TEfficiency* Efficiency_MuonDetectorPhi_FV = new TEfficiency("MuonDetectorPhi_eff_FV",";Muon Detector #theta;Selected/All",60,-3.1415,3.1415);

      TH1D *h_MuonBeamTheta_FV = new TH1D("h_TrueMuonBeamTheta_FV","",60,0,3.1415);
      TH1D *h_SelectedMuonBeamTheta_FV = new TH1D("h_SelectedMuonBeamTheta_FV","",60,0,3.1415);
      TEfficiency* Efficiency_MuonBeamTheta_FV = new TEfficiency("MuonBeamTheta_eff_FV",";Muon Beam #theta;Selected/All",60,0,3.1415);

      TH1D *h_MuonBeamPhi_FV = new TH1D("h_TrueMuonBeamPhi_FV","",60,-3.1415,3.1415);
      TH1D *h_SelectedMuonBeamPhi_FV = new TH1D("h_SelectedMuonBeamPhi_FV","",60,-3.1415,3.1415);
      TEfficiency* Efficiency_MuonBeamPhi_FV = new TEfficiency("MuonBeamPhi_eff_FV",";Muon Beam #theta;Selected/All",60,-3.1415,3.1415);

      TH1D *h_KaonMomentum_FV = new TH1D("h_TrueKaonMomentum_FV","",60,0.0,2.0);
      TH1D *h_SelectedKaonMomentum_FV = new TH1D("h_SelectedKaonMomentum_FV","",60,0.0,2.0);
      TEfficiency* Efficiency_KaonMomentum_FV = new TEfficiency("KaonMomentum_eff_FV",";True K^{+} Momentum (GeV/c);Selected/All",60,0.0,2.0);

      TH1D *h_DecayMuonMomentum_FV = new TH1D("h_TrueDecayMuonMomentum_FV","",60,0.3,1.5);
      TH1D *h_SelectedDecayMuonMomentum_FV = new TH1D("h_SelectedDecayMuonMomentum_FV","",60,0.3,1.5);
      TEfficiency* Efficiency_DecayMuonMomentum_FV = new TEfficiency("DecayMuonMomentum_eff_FV",";True Decay Proton Momentum (GeV/c);Selected/All",60,0.3,1.5);

      TH1D *h_DecayPionMomentum_FV = new TH1D("h_TrueDecayPionMomentum_FV","",60,0.1,0.8);
      TH1D *h_SelectedDecayPionMomentum_FV = new TH1D("h_SelectedDecayPionMomentum_FV","",60,0.1,0.8);
      TEfficiency* Efficiency_DecayPionMomentum_FV = new TEfficiency("DecayPionMomentum_eff_FV",";True Decay #pi^{+} Momentum (GeV/c);Selected/All",60,0.1,0.8);

      TH1D *h_FV = new TH1D("h_FV","",1,0,1.0);
      TH1D *h_Selected_FV = new TH1D("h_Selected_FV","",1,0,1.0);
      TEfficiency* Efficiency_FV = new TEfficiency("eff_FV",";;Selected/All",1,0,1.0);

      // NuCCFilter Cut //

      TH1D *h_Q2_NuCCFilter = new TH1D("h_Q2_NuCCFilter","",60,0,3.0);
      TH1D *h_SelectedQ2_NuCCFilter = new TH1D("h_SelectedQ2_NuCCFilter","",60,0,3.0);
      TEfficiency* Efficiency_Q2_NuCCFilter = new TEfficiency("Q2_eff_NuCCFilter",";True Q^{2} (GeV^{2});Selected/All",60,0,3.0);

      TH1D *h_NuE_NuCCFilter = new TH1D("h_TrueNuE_NuCCFilter","",60,0,4.0);
      TH1D *h_SelectedNuE_NuCCFilter = new TH1D("h_SelectedNuE_NuCCFilter","",60,0,4.0);
      TEfficiency* Efficiency_NuE_NuCCFilter = new TEfficiency("NuE_eff_NuCCFilter",";True E_{#nu} (GeV);Selected/All",60,0,4.0);

      TH1D *h_MuonKE_NuCCFilter = new TH1D("h_MuonKE_NuCCFilter","",60,0,3.0);
      TH1D *h_SelectedMuonKE_NuCCFilter = new TH1D("h_SelectedMuonKE_NuCCFilter","",60,0,3.0);
      TEfficiency* Efficiency_MuonKE_NuCCFilter = new TEfficiency("MuonKE_eff_NuCCFilter",";True Muon KE (GeV);Selected/All",60,0,3.0);

      TH1D *h_MuonTrueTheta_NuCCFilter = new TH1D("h_MuonTrueTheta_NuCCFilter","",60,0,3.1415);
      TH1D *h_SelectedMuonTrueTheta_NuCCFilter = new TH1D("h_SelectedMuonTrueTheta_NuCCFilter","",60,0,3.1415);
      TEfficiency* Efficiency_MuonTrueTheta_NuCCFilter = new TEfficiency("MuonTrueTheta_eff_NuCCFilter",";Muon True #theta;Selected/All",60,0,3.1415);

      TH1D *h_MuonDetectorTheta_NuCCFilter = new TH1D("h_TrueMuonDetectorTheta_NuCCFilter","",60,0,3.1415);
      TH1D *h_SelectedMuonDetectorTheta_NuCCFilter = new TH1D("h_SelectedMuonDetectorTheta_NuCCFilter","",60,0,3.1415);
      TEfficiency* Efficiency_MuonDetectorTheta_NuCCFilter = new TEfficiency("MuonDetectorTheta_eff_NuCCFilter",";Muon Detector #theta;Selected/All",60,0,3.1415);

      TH1D *h_MuonDetectorPhi_NuCCFilter = new TH1D("h_TrueMuonDetectorPhi_NuCCFilter","",60,-3.1415,3.1415);
      TH1D *h_SelectedMuonDetectorPhi_NuCCFilter = new TH1D("h_SelectedMuonDetectorPhi_NuCCFilter","",60,-3.1415,3.1415);
      TEfficiency* Efficiency_MuonDetectorPhi_NuCCFilter = new TEfficiency("MuonDetectorPhi_eff_NuCCFilter",";Muon Detector #theta;Selected/All",60,-3.1415,3.1415);

      TH1D *h_MuonBeamTheta_NuCCFilter = new TH1D("h_TrueMuonBeamTheta_NuCCFilter","",60,0,3.1415);
      TH1D *h_SelectedMuonBeamTheta_NuCCFilter = new TH1D("h_SelectedMuonBeamTheta_NuCCFilter","",60,0,3.1415);
      TEfficiency* Efficiency_MuonBeamTheta_NuCCFilter = new TEfficiency("MuonBeamTheta_eff_NuCCFilter",";Muon Beam #theta;Selected/All",60,0,3.1415);

      TH1D *h_MuonBeamPhi_NuCCFilter = new TH1D("h_TrueMuonBeamPhi_NuCCFilter","",60,-3.1415,3.1415);
      TH1D *h_SelectedMuonBeamPhi_NuCCFilter = new TH1D("h_SelectedMuonBeamPhi_NuCCFilter","",60,-3.1415,3.1415);
      TEfficiency* Efficiency_MuonBeamPhi_NuCCFilter = new TEfficiency("MuonBeamPhi_eff_NuCCFilter",";Muon Beam #theta;Selected/All",60,-3.1415,3.1415);

      TH1D *h_KaonMomentum_NuCCFilter = new TH1D("h_TrueKaonMomentum_NuCCFilter","",60,0.0,2.0);
      TH1D *h_SelectedKaonMomentum_NuCCFilter = new TH1D("h_SelectedKaonMomentum_NuCCFilter","",60,0.0,2.0);
      TEfficiency* Efficiency_KaonMomentum_NuCCFilter = new TEfficiency("KaonMomentum_eff_NuCCFilter",";True K^{+} Momentum (GeV/c);Selected/All",60,0.0,2.0);

      TH1D *h_DecayMuonMomentum_NuCCFilter = new TH1D("h_TrueDecayMuonMomentum_NuCCFilter","",60,0.3,1.5);
      TH1D *h_SelectedDecayMuonMomentum_NuCCFilter = new TH1D("h_SelectedDecayMuonMomentum_NuCCFilter","",60,0.3,1.5);
      TEfficiency* Efficiency_DecayMuonMomentum_NuCCFilter = new TEfficiency("DecayMuonMomentum_eff_NuCCFilter",";True Decay Proton Momentum (GeV/c);Selected/All",60,0.3,1.5);

      TH1D *h_DecayPionMomentum_NuCCFilter = new TH1D("h_TrueDecayPionMomentum_NuCCFilter","",60,0.1,0.8);
      TH1D *h_SelectedDecayPionMomentum_NuCCFilter = new TH1D("h_SelectedDecayPionMomentum_NuCCFilter","",60,0.1,0.8);
      TEfficiency* Efficiency_DecayPionMomentum_NuCCFilter = new TEfficiency("DecayPionMomentum_eff_NuCCFilter",";True Decay #pi^{+} Momentum (GeV/c);Selected/All",60,0.1,0.8);

      TH1D *h_NuCCFilter = new TH1D("h_NuCCFilter","",1,0,1.0);
      TH1D *h_Selected_NuCCFilter = new TH1D("h_Selected_NuCCFilter","",1,0,1.0);
      TEfficiency* Efficiency_NuCCFilter = new TEfficiency("eff_NuCCFilter",";;Selected/All",1,0,1.0);

      // Number of Daughter Track Cut //

      TH1D *h_Q2_NDaughterTrack = new TH1D("h_Q2_NDaughterTrack","",60,0,3.0);
      TH1D *h_SelectedQ2_NDaughterTrack = new TH1D("h_SelectedQ2_NDaughterTrack","",60,0,3.0);
      TEfficiency* Efficiency_Q2_NDaughterTrack = new TEfficiency("Q2_eff_NDaughterTrack",";True Q^{2} (GeV^{2});Selected/All",60,0,3.0);

      TH1D *h_NuE_NDaughterTrack = new TH1D("h_TrueNuE_NDaughterTrack","",60,0,4.0);
      TH1D *h_SelectedNuE_NDaughterTrack = new TH1D("h_SelectedNuE_NDaughterTrack","",60,0,4.0);
      TEfficiency* Efficiency_NuE_NDaughterTrack = new TEfficiency("NuE_eff_NDaughterTrack",";True E_{#nu} (GeV);Selected/All",60,0,4.0);

      TH1D *h_MuonKE_NDaughterTrack = new TH1D("h_MuonKE_NDaughterTrack","",60,0,3.0);
      TH1D *h_SelectedMuonKE_NDaughterTrack = new TH1D("h_SelectedMuonKE_NDaughterTrack","",60,0,3.0);
      TEfficiency* Efficiency_MuonKE_NDaughterTrack = new TEfficiency("MuonKE_eff_NDaughterTrack",";True Muon KE (GeV);Selected/All",60,0,3.0);

      TH1D *h_MuonTrueTheta_NDaughterTrack = new TH1D("h_MuonTrueTheta_NDaughterTrack","",60,0,3.1415);
      TH1D *h_SelectedMuonTrueTheta_NDaughterTrack = new TH1D("h_SelectedMuonTrueTheta_NDaughterTrack","",60,0,3.1415);
      TEfficiency* Efficiency_MuonTrueTheta_NDaughterTrack = new TEfficiency("MuonTrueTheta_eff_NDaughterTrack",";Muon True #theta;Selected/All",60,0,3.1415);

      TH1D *h_MuonDetectorTheta_NDaughterTrack = new TH1D("h_TrueMuonDetectorTheta_NDaughterTrack","",60,0,3.1415);
      TH1D *h_SelectedMuonDetectorTheta_NDaughterTrack = new TH1D("h_SelectedMuonDetectorTheta_NDaughterTrack","",60,0,3.1415);
      TEfficiency* Efficiency_MuonDetectorTheta_NDaughterTrack = new TEfficiency("MuonDetectorTheta_eff_NDaughterTrack",";Muon Detector #theta;Selected/All",60,0,3.1415);

      TH1D *h_MuonDetectorPhi_NDaughterTrack = new TH1D("h_TrueMuonDetectorPhi_NDaughterTrack","",60,-3.1415,3.1415);
      TH1D *h_SelectedMuonDetectorPhi_NDaughterTrack = new TH1D("h_SelectedMuonDetectorPhi_NDaughterTrack","",60,-3.1415,3.1415);
      TEfficiency* Efficiency_MuonDetectorPhi_NDaughterTrack = new TEfficiency("MuonDetectorPhi_eff_NDaughterTrack",";Muon Detector #theta;Selected/All",60,-3.1415,3.1415);

      TH1D *h_MuonBeamTheta_NDaughterTrack = new TH1D("h_TrueMuonBeamTheta_NDaughterTrack","",60,0,3.1415);
      TH1D *h_SelectedMuonBeamTheta_NDaughterTrack = new TH1D("h_SelectedMuonBeamTheta_NDaughterTrack","",60,0,3.1415);
      TEfficiency* Efficiency_MuonBeamTheta_NDaughterTrack = new TEfficiency("MuonBeamTheta_eff_NDaughterTrack",";Muon Beam #theta;Selected/All",60,0,3.1415);

      TH1D *h_MuonBeamPhi_NDaughterTrack = new TH1D("h_TrueMuonBeamPhi_NDaughterTrack","",60,-3.1415,3.1415);
      TH1D *h_SelectedMuonBeamPhi_NDaughterTrack = new TH1D("h_SelectedMuonBeamPhi_NDaughterTrack","",60,-3.1415,3.1415);
      TEfficiency* Efficiency_MuonBeamPhi_NDaughterTrack = new TEfficiency("MuonBeamPhi_eff_NDaughterTrack",";Muon Beam #theta;Selected/All",60,-3.1415,3.1415);

      TH1D *h_KaonMomentum_NDaughterTrack = new TH1D("h_TrueKaonMomentum_NDaughterTrack","",60,0.0,2.0);
      TH1D *h_SelectedKaonMomentum_NDaughterTrack = new TH1D("h_SelectedKaonMomentum_NDaughterTrack","",60,0.0,2.0);
      TEfficiency* Efficiency_KaonMomentum_NDaughterTrack = new TEfficiency("KaonMomentum_eff_NDaughterTrack",";True K^{+} Momentum (GeV/c);Selected/All",60,0.0,2.0);

      TH1D *h_DecayMuonMomentum_NDaughterTrack = new TH1D("h_TrueDecayMuonMomentum_NDaughterTrack","",60,0.3,1.5);
      TH1D *h_SelectedDecayMuonMomentum_NDaughterTrack = new TH1D("h_SelectedDecayMuonMomentum_NDaughterTrack","",60,0.3,1.5);
      TEfficiency* Efficiency_DecayMuonMomentum_NDaughterTrack = new TEfficiency("DecayMuonMomentum_eff_NDaughterTrack",";True Decay Proton Momentum (GeV/c);Selected/All",60,0.3,1.5);

      TH1D *h_DecayPionMomentum_NDaughterTrack = new TH1D("h_TrueDecayPionMomentum_NDaughterTrack","",60,0.1,0.8);
      TH1D *h_SelectedDecayPionMomentum_NDaughterTrack = new TH1D("h_SelectedDecayPionMomentum_NDaughterTrack","",60,0.1,0.8);
      TEfficiency* Efficiency_DecayPionMomentum_NDaughterTrack = new TEfficiency("DecayPionMomentum_eff_NDaughterTrack",";True Decay #pi^{+} Momentum (GeV/c);Selected/All",60,0.1,0.8);

      TH1D *h_NDaughterTrack = new TH1D("h_NDaughterTrack","",1,0,1.0);
      TH1D *h_Selected_NDaughterTrack = new TH1D("h_Selected_NDaughterTrack","",1,0,1.0);
      TEfficiency* Efficiency_NDaughterTrack = new TEfficiency("eff_NDaughterTrack",";;Selected/All",1,0,1.0);

      // Daughter Track Fiducial Volume Cut //

      TH1D *h_Q2_DaughterFV = new TH1D("h_Q2_DaughterFV","",60,0,3.0);
      TH1D *h_SelectedQ2_DaughterFV = new TH1D("h_SelectedQ2_DaughterFV","",60,0,3.0);
      TEfficiency* Efficiency_Q2_DaughterFV = new TEfficiency("Q2_eff_DaughterFV",";True Q^{2} (GeV^{2});Selected/All",60,0,3.0);

      TH1D *h_NuE_DaughterFV = new TH1D("h_TrueNuE_DaughterFV","",60,0,4.0);
      TH1D *h_SelectedNuE_DaughterFV = new TH1D("h_SelectedNuE_DaughterFV","",60,0,4.0);
      TEfficiency* Efficiency_NuE_DaughterFV = new TEfficiency("NuE_eff_DaughterFV",";True E_{#nu} (GeV);Selected/All",60,0,4.0);

      TH1D *h_MuonKE_DaughterFV = new TH1D("h_MuonKE_DaughterFV","",60,0,3.0);
      TH1D *h_SelectedMuonKE_DaughterFV = new TH1D("h_SelectedMuonKE_DaughterFV","",60,0,3.0);
      TEfficiency* Efficiency_MuonKE_DaughterFV = new TEfficiency("MuonKE_eff_DaughterFV",";True Muon KE (GeV);Selected/All",60,0,3.0);

      TH1D *h_MuonTrueTheta_DaughterFV = new TH1D("h_MuonTrueTheta_DaughterFV","",60,0,3.1415);
      TH1D *h_SelectedMuonTrueTheta_DaughterFV = new TH1D("h_SelectedMuonTrueTheta_DaughterFV","",60,0,3.1415);
      TEfficiency* Efficiency_MuonTrueTheta_DaughterFV = new TEfficiency("MuonTrueTheta_eff_DaughterFV",";Muon True #theta;Selected/All",60,0,3.1415);

      TH1D *h_MuonDetectorTheta_DaughterFV = new TH1D("h_TrueMuonDetectorTheta_DaughterFV","",60,0,3.1415);
      TH1D *h_SelectedMuonDetectorTheta_DaughterFV = new TH1D("h_SelectedMuonDetectorTheta_DaughterFV","",60,0,3.1415);
      TEfficiency* Efficiency_MuonDetectorTheta_DaughterFV = new TEfficiency("MuonDetectorTheta_eff_DaughterFV",";Muon Detector #theta;Selected/All",60,0,3.1415);

      TH1D *h_MuonDetectorPhi_DaughterFV = new TH1D("h_TrueMuonDetectorPhi_DaughterFV","",60,-3.1415,3.1415);
      TH1D *h_SelectedMuonDetectorPhi_DaughterFV = new TH1D("h_SelectedMuonDetectorPhi_DaughterFV","",60,-3.1415,3.1415);
      TEfficiency* Efficiency_MuonDetectorPhi_DaughterFV = new TEfficiency("MuonDetectorPhi_eff_DaughterFV",";Muon Detector #theta;Selected/All",60,-3.1415,3.1415);

      TH1D *h_MuonBeamTheta_DaughterFV = new TH1D("h_TrueMuonBeamTheta_DaughterFV","",60,0,3.1415);
      TH1D *h_SelectedMuonBeamTheta_DaughterFV = new TH1D("h_SelectedMuonBeamTheta_DaughterFV","",60,0,3.1415);
      TEfficiency* Efficiency_MuonBeamTheta_DaughterFV = new TEfficiency("MuonBeamTheta_eff_DaughterFV",";Muon Beam #theta;Selected/All",60,0,3.1415);

      TH1D *h_MuonBeamPhi_DaughterFV = new TH1D("h_TrueMuonBeamPhi_DaughterFV","",60,-3.1415,3.1415);
      TH1D *h_SelectedMuonBeamPhi_DaughterFV = new TH1D("h_SelectedMuonBeamPhi_DaughterFV","",60,-3.1415,3.1415);
      TEfficiency* Efficiency_MuonBeamPhi_DaughterFV = new TEfficiency("MuonBeamPhi_eff_DaughterFV",";Muon Beam #theta;Selected/All",60,-3.1415,3.1415);

      TH1D *h_KaonMomentum_DaughterFV = new TH1D("h_TrueKaonMomentum_DaughterFV","",20,0.0,2.0);
      TH1D *h_SelectedKaonMomentum_DaughterFV = new TH1D("h_SelectedKaonMomentum_DaughterFV","",20,0.0,2.0);
      TEfficiency* Efficiency_KaonMomentum_DaughterFV = new TEfficiency("KaonMomentum_eff_DaughterFV",";True K^{+} Momentum (GeV/c);Selected/All",20,0.0,2.0);

      TH1D *h_DecayMuonMomentum_DaughterFV = new TH1D("h_TrueDecayMuonMomentum_DaughterFV","",60,0.3,1.5);
      TH1D *h_SelectedDecayMuonMomentum_DaughterFV = new TH1D("h_SelectedDecayMuonMomentum_DaughterFV","",60,0.3,1.5);
      TEfficiency* Efficiency_DecayMuonMomentum_DaughterFV = new TEfficiency("DecayMuonMomentum_eff_DaughterFV",";True Decay Proton Momentum (GeV/c);Selected/All",60,0.3,1.5);

      TH1D *h_DecayPionMomentum_DaughterFV = new TH1D("h_TrueDecayPionMomentum_DaughterFV","",60,0.1,0.8);
      TH1D *h_SelectedDecayPionMomentum_DaughterFV = new TH1D("h_SelectedDecayPionMomentum_DaughterFV","",60,0.1,0.8);
      TEfficiency* Efficiency_DecayPionMomentum_DaughterFV = new TEfficiency("DecayPionMomentum_eff_DaughterFV",";True Decay #pi^{+} Momentum (GeV/c);Selected/All",60,0.1,0.8);

      TH1D *h_DaughterFV = new TH1D("h_DaughterFV","",1,0,1.0);
      TH1D *h_Selected_DaughterFV = new TH1D("h_Selected_DaughterFV","",1,0,1.0);
      TEfficiency* Efficiency_DaughterFV = new TEfficiency("eff_DaughterFV",";;Selected/All",1,0,1.0);

      // BDT Cut //
      /*
      TH1D *h_Q2_BDTCut = new TH1D("h_Q2_BDTCut","",60,0,3.0);
      TH1D *h_SelectedQ2_BDTCut = new TH1D("h_SelectedQ2_BDTCut","",60,0,3.0);
      TEfficiency* Efficiency_Q2_BDTCut = new TEfficiency("Q2_eff_BDTCut",";True Q^{2} (GeV^{2});Selected/All",60,0,3.0);

      TH1D *h_NuE_BDTCut = new TH1D("h_TrueNuE_BDTCut","",60,0,4.0);
      TH1D *h_SelectedNuE_BDTCut = new TH1D("h_SelectedNuE_BDTCut","",60,0,4.0);
      TEfficiency* Efficiency_NuE_BDTCut = new TEfficiency("NuE_eff_BDTCut",";True E_{#nu} (GeV);Selected/All",60,0,4.0);

      TH1D *h_MuonKE_BDTCut = new TH1D("h_MuonKE_BDTCut","",60,0,3.0);
      TH1D *h_SelectedMuonKE_BDTCut = new TH1D("h_SelectedMuonKE_BDTCut","",60,0,3.0);
      TEfficiency* Efficiency_MuonKE_BDTCut = new TEfficiency("MuonKE_eff_BDTCut",";True Muon KE (GeV);Selected/All",60,0,3.0);

      TH1D *h_MuonTrueTheta_BDTCut = new TH1D("h_MuonTrueTheta_BDTCut","",60,0,3.1415);
      TH1D *h_SelectedMuonTrueTheta_BDTCut = new TH1D("h_SelectedMuonTrueTheta_BDTCut","",60,0,3.1415);
      TEfficiency* Efficiency_MuonTrueTheta_BDTCut = new TEfficiency("MuonTrueTheta_eff_BDTCut",";Muon True #theta;Selected/All",60,0,3.1415);

      TH1D *h_MuonDetectorTheta_BDTCut = new TH1D("h_TrueMuonDetectorTheta_BDTCut","",60,0,3.1415);
      TH1D *h_SelectedMuonDetectorTheta_BDTCut = new TH1D("h_SelectedMuonDetectorTheta_BDTCut","",60,0,3.1415);
      TEfficiency* Efficiency_MuonDetectorTheta_BDTCut = new TEfficiency("MuonDetectorTheta_eff_BDTCut",";Muon Detector #theta;Selected/All",60,0,3.1415);

      TH1D *h_MuonDetectorPhi_BDTCut = new TH1D("h_TrueMuonDetectorPhi_BDTCut","",60,-3.1415,3.1415);
      TH1D *h_SelectedMuonDetectorPhi_BDTCut = new TH1D("h_SelectedMuonDetectorPhi_BDTCut","",60,-3.1415,3.1415);
      TEfficiency* Efficiency_MuonDetectorPhi_BDTCut = new TEfficiency("MuonDetectorPhi_eff_BDTCut",";Muon Detector #theta;Selected/All",60,-3.1415,3.1415);

      TH1D *h_MuonBeamTheta_BDTCut = new TH1D("h_TrueMuonBeamTheta_BDTCut","",60,0,3.1415);
      TH1D *h_SelectedMuonBeamTheta_BDTCut = new TH1D("h_SelectedMuonBeamTheta_BDTCut","",60,0,3.1415);
      TEfficiency* Efficiency_MuonBeamTheta_BDTCut = new TEfficiency("MuonBeamTheta_eff_BDTCut",";Muon Beam #theta;Selected/All",60,0,3.1415);

      TH1D *h_MuonBeamPhi_BDTCut = new TH1D("h_TrueMuonBeamPhi_BDTCut","",60,-3.1415,3.1415);
      TH1D *h_SelectedMuonBeamPhi_BDTCut = new TH1D("h_SelectedMuonBeamPhi_BDTCut","",60,-3.1415,3.1415);
      TEfficiency* Efficiency_MuonBeamPhi_BDTCut = new TEfficiency("MuonBeamPhi_eff_BDTCut",";Muon Beam #theta;Selected/All",60,-3.1415,3.1415);

      TH1D *h_KaonMomentum_BDTCut = new TH1D("h_TrueKaonMomentum_BDTCut","",60,0.0,2.0);
      TH1D *h_SelectedKaonMomentum_BDTCut = new TH1D("h_SelectedKaonMomentum_BDTCut","",60,0.0,2.0);
      TEfficiency* Efficiency_KaonMomentum_BDTCut = new TEfficiency("KaonMomentum_eff_BDTCut",";True K^{+} Momentum (GeV/c);Selected/All",60,0.0,2.0);

      TH1D *h_DecayMuonMomentum_BDTCut = new TH1D("h_TrueDecayMuonMomentum_BDTCut","",60,0.3,1.5);
      TH1D *h_SelectedDecayMuonMomentum_BDTCut = new TH1D("h_SelectedDecayMuonMomentum_BDTCut","",60,0.3,1.5);
      TEfficiency* Efficiency_DecayMuonMomentum_BDTCut = new TEfficiency("DecayMuonMomentum_eff_BDTCut",";True Decay Proton Momentum (GeV/c);Selected/All",60,0.3,1.5);

      TH1D *h_DecayPionMomentum_BDTCut = new TH1D("h_TrueDecayPionMomentum_BDTCut","",60,0.1,0.8);
      TH1D *h_SelectedDecayPionMomentum_BDTCut = new TH1D("h_SelectedDecayPionMomentum_BDTCut","",60,0.1,0.8);
      TEfficiency* Efficiency_DecayPionMomentum_BDTCut = new TEfficiency("DecayPionMomentum_eff_BDTCut",";True Decay #pi^{+} Momentum (GeV/c);Selected/All",60,0.1,0.8);

      TH1D *h_BDTCut = new TH1D("h_BDTCut","",1,0,1.0);
      TH1D *h_Selected_BDTCut = new TH1D("h_Selected_BDTCut","",1,0,1.0);
      TEfficiency* Efficiency_BDTCut = new TEfficiency("eff_BDTCut",";;Selected/All",1,0,1.0);

      // Daughter Track Length Cut //

      TH1D *h_Q2_DaughterTrackLength = new TH1D("h_Q2_DaughterTrackLength","",60,0,3.0);
      TH1D *h_SelectedQ2_DaughterTrackLength = new TH1D("h_SelectedQ2_DaughterTrackLength","",60,0,3.0);
      TEfficiency* Efficiency_Q2_DaughterTrackLength = new TEfficiency("Q2_eff_DaughterTrackLength",";True Q^{2} (GeV^{2});Selected/All",60,0,3.0);

      TH1D *h_NuE_DaughterTrackLength = new TH1D("h_TrueNuE_DaughterTrackLength","",60,0,4.0);
      TH1D *h_SelectedNuE_DaughterTrackLength = new TH1D("h_SelectedNuE_DaughterTrackLength","",60,0,4.0);
      TEfficiency* Efficiency_NuE_DaughterTrackLength = new TEfficiency("NuE_eff_DaughterTrackLength",";True E_{#nu} (GeV);Selected/All",60,0,4.0);

      TH1D *h_MuonKE_DaughterTrackLength = new TH1D("h_MuonKE_DaughterTrackLength","",60,0,3.0);
      TH1D *h_SelectedMuonKE_DaughterTrackLength = new TH1D("h_SelectedMuonKE_DaughterTrackLength","",60,0,3.0);
      TEfficiency* Efficiency_MuonKE_DaughterTrackLength = new TEfficiency("MuonKE_eff_DaughterTrackLength",";True Muon KE (GeV);Selected/All",60,0,3.0);

      TH1D *h_MuonTrueTheta_DaughterTrackLength = new TH1D("h_MuonTrueTheta_DaughterTrackLength","",60,0,3.1415);
      TH1D *h_SelectedMuonTrueTheta_DaughterTrackLength = new TH1D("h_SelectedMuonTrueTheta_DaughterTrackLength","",60,0,3.1415);
      TEfficiency* Efficiency_MuonTrueTheta_DaughterTrackLength = new TEfficiency("MuonTrueTheta_eff_DaughterTrackLength",";Muon True #theta;Selected/All",60,0,3.1415);

      TH1D *h_MuonDetectorTheta_DaughterTrackLength = new TH1D("h_TrueMuonDetectorTheta_DaughterTrackLength","",60,0,3.1415);
      TH1D *h_SelectedMuonDetectorTheta_DaughterTrackLength = new TH1D("h_SelectedMuonDetectorTheta_DaughterTrackLength","",60,0,3.1415);
      TEfficiency* Efficiency_MuonDetectorTheta_DaughterTrackLength = new TEfficiency("MuonDetectorTheta_eff_DaughterTrackLength",";Muon Detector #theta;Selected/All",60,0,3.1415);

      TH1D *h_MuonDetectorPhi_DaughterTrackLength = new TH1D("h_TrueMuonDetectorPhi_DaughterTrackLength","",60,-3.1415,3.1415);
      TH1D *h_SelectedMuonDetectorPhi_DaughterTrackLength = new TH1D("h_SelectedMuonDetectorPhi_DaughterTrackLength","",60,-3.1415,3.1415);
      TEfficiency* Efficiency_MuonDetectorPhi_DaughterTrackLength = new TEfficiency("MuonDetectorPhi_eff_DaughterTrackLength",";Muon Detector #theta;Selected/All",60,-3.1415,3.1415);

      TH1D *h_MuonBeamTheta_DaughterTrackLength = new TH1D("h_TrueMuonBeamTheta_DaughterTrackLength","",60,0,3.1415);
      TH1D *h_SelectedMuonBeamTheta_DaughterTrackLength = new TH1D("h_SelectedMuonBeamTheta_DaughterTrackLength","",60,0,3.1415);
      TEfficiency* Efficiency_MuonBeamTheta_DaughterTrackLength = new TEfficiency("MuonBeamTheta_eff_DaughterTrackLength",";Muon Beam #theta;Selected/All",60,0,3.1415);

      TH1D *h_MuonBeamPhi_DaughterTrackLength = new TH1D("h_TrueMuonBeamPhi_DaughterTrackLength","",60,-3.1415,3.1415);
      TH1D *h_SelectedMuonBeamPhi_DaughterTrackLength = new TH1D("h_SelectedMuonBeamPhi_DaughterTrackLength","",60,-3.1415,3.1415);
      TEfficiency* Efficiency_MuonBeamPhi_DaughterTrackLength = new TEfficiency("MuonBeamPhi_eff_DaughterTrackLength",";Muon Beam #theta;Selected/All",60,-3.1415,3.1415);

      TH1D *h_KaonMomentum_DaughterTrackLength = new TH1D("h_TrueKaonMomentum_DaughterTrackLength","",60,0.0,2.0);
      TH1D *h_SelectedKaonMomentum_DaughterTrackLength = new TH1D("h_SelectedKaonMomentum_DaughterTrackLength","",60,0.0,2.0);
      TEfficiency* Efficiency_KaonMomentum_DaughterTrackLength = new TEfficiency("KaonMomentum_eff_DaughterTrackLength",";True K^{+} Momentum (GeV/c);Selected/All",60,0.0,2.0);

      TH1D *h_DecayMuonMomentum_DaughterTrackLength = new TH1D("h_TrueDecayMuonMomentum_DaughterTrackLength","",60,0.3,1.5);
      TH1D *h_SelectedDecayMuonMomentum_DaughterTrackLength = new TH1D("h_SelectedDecayMuonMomentum_DaughterTrackLength","",60,0.3,1.5);
      TEfficiency* Efficiency_DecayMuonMomentum_DaughterTrackLength = new TEfficiency("DecayMuonMomentum_eff_DaughterTrackLength",";True Decay Proton Momentum (GeV/c);Selected/All",60,0.3,1.5);

      TH1D *h_DecayPionMomentum_DaughterTrackLength = new TH1D("h_TrueDecayPionMomentum_DaughterTrackLength","",60,0.1,0.8);
      TH1D *h_SelectedDecayPionMomentum_DaughterTrackLength = new TH1D("h_SelectedDecayPionMomentum_DaughterTrackLength","",60,0.1,0.8);
      TEfficiency* Efficiency_DecayPionMomentum_DaughterTrackLength = new TEfficiency("DecayPionMomentum_eff_DaughterTrackLength",";True Decay #pi^{+} Momentum (GeV/c);Selected/All",60,0.1,0.8);

      TH1D *h_DaughterTrackLength = new TH1D("h_DaughterTrackLength","",1,0,1.0);
      TH1D *h_Selected_DaughterTrackLength = new TH1D("h_Selected_DaughterTrackLength","",1,0,1.0);
      TEfficiency* Efficiency_DaughterTrackLength = new TEfficiency("eff_DaughterTrackLength",";;Selected/All",1,0,1.0);
      */

      TH1D *h_RecoKaonMomentum_NDaughterTrack = new TH1D("h_RecoKaonMomentum_NDaughterTrack","",60,0.0,2.0);
      TH1D *h_SelectedRecoKaonMomentum_NDaughterTrack = new TH1D("h_SelectedRecoKaonMomentum_NDaughterTrack","",60,0.0,2.0);
      TEfficiency* Efficiency_RecoKaonMomentum_NDaughterTrack = new TEfficiency("RecoKaonMomentum_eff_NDaughterTrack",";Reconstructed K^{+} Momentum (GeV/c);Selected/All",60,0.0,2.0);


      /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

      E.SetFile("/exp/uboone/data/users/taniuchi/ntuple_testarea/assok_KaonTrees.root", "KAON");
      M.AddSample("AssocKaon","AssocKaon",POT);//need to change

      M.UseFluxWeight(false);
      M.UseGenWeight(false);

      for(int i=0;i<E.GetNEvents();i++){
        
         if(i % 10000 == 0) std::cout << "Processing event " << i << "/" << E.GetNEvents() << std::endl;
        
         //get an event
         Event e = E.GetEvent(i);

         //update metadata
         M.AddEvent(e);
         M.SetSignal(e);

         if(!e.EventIsSignal) continue;
         //if(!e.EventHasKaonPScatter) continue;

         // Calculate Q2
         double Q2 = -1;

	 if (!(e.Neutrino.size() > 0 && e.Lepton.size() > 0)){
	   continue;
	   std::cout << "THIS EVENT DOES NOT HAVE NEUTRINO NOR LEPTON" << std::endl;
	 }

         TLorentzVector Nu4Momentum(e.Neutrino.at(0).Px,e.Neutrino.at(0).Py,e.Neutrino.at(0).Pz,e.Neutrino.at(0).E);
         TLorentzVector Muon4Momentum(e.Lepton.at(0).Px,e.Lepton.at(0).Py,e.Lepton.at(0).Pz,e.Lepton.at(0).E);

         Q2 = (-1)*(Nu4Momentum - Muon4Momentum)*(Nu4Momentum - Muon4Momentum);

         // Calculate NuE
         double NuE = -1;
         NuE = e.Neutrino.at(0).E;

         // Calculate Muon KE
         double MuonKE = -1;
         MuonKE = e.Lepton.at(0).KE;

         // Get the Neutrino's true direction
         TVector3 NuDirection(e.Neutrino.at(0).Px,e.Neutrino.at(0).Py,e.Neutrino.at(0).Pz);
         NuDirection *= 1.0/NuDirection.Mag();

         // Get the muon's true direction
         TVector3 MuonTrueDir(e.Lepton.at(0).Px,e.Lepton.at(0).Py,e.Lepton.at(0).Pz);

         double MuonTrueTheta = MuonTrueDir.Angle(NuDirection);
         double MuonDetectorTheta = MuonTrueDir.Theta();
         double MuonDetectorPhi = MuonTrueDir.Phi();

         TVector3 MuonTrueDirBeam = RotateToBeam(MuonTrueDir);

         double MuonBeamTheta = MuonTrueDirBeam.Theta();
         double MuonBeamPhi = MuonTrueDirBeam.Phi();
         double KaonMomentum = e.PrimaryKaonP.at(0).ModMomentum;
         double DecayMuonMomentum,DecayPionMomentum=-1.0;

	 if(e.KaonPDecay_NuMuP.size() == 2){
	   if(e.KaonPDecay_NuMuP.at(0).PDG == -13) DecayMuonMomentum = e.KaonPDecay_NuMuP.at(0).ModMomentum;
	   if(e.KaonPDecay_NuMuP.at(1).PDG == -13) DecayMuonMomentum = e.KaonPDecay_NuMuP.at(1).ModMomentum;
	 }
	 else if(e.KaonPDecay_PiPPi0.size() == 2){
	   if(e.KaonPDecay_PiPPi0.at(0).PDG == 211) DecayPionMomentum = e.KaonPDecay_PiPPi0.at(0).ModMomentum;
	   if(e.KaonPDecay_PiPPi0.at(1).PDG == 211) DecayPionMomentum = e.KaonPDecay_PiPPi0.at(1).ModMomentum;
	 }

         bool passed_FV=false, passed_NuCCFilter=false, passed_NDaughterTrack=false, passed_DaughterFV=false, passed_BDTCut=false, passed_All=false;
         //bool passed_DaughterTrackLength=false;

         passed_FV = M.FiducialVolumeCut(e);
         if(passed_FV) passed_NuCCFilter = M.NuCCInclusiveFilter(e);
         if(passed_NuCCFilter) passed_NDaughterTrack = M.DaughterTrackCut(e);
         if(passed_NDaughterTrack) passed_DaughterFV = M.DaughterFiducialVolumeCut(e);
         //if(passed_DaughterFV) passed_BDTCut = M.BDTCut(e);
         //if(passed_BDTCut) passed_DaughterTrackLength = M.DaughterTrackLengthCut(e);

	 passed_All = passed_DaughterFV;
         //passed_All = passed_AngleCut;

         // Entire Selection
         h_Q2_All->Fill(Q2,e.Weight);
         Efficiency_Q2_All->FillWeighted(passed_All,e.Weight,Q2);
         if(Q2 > 0 && passed_All) h_SelectedQ2_All->Fill(Q2,e.Weight);

         h_NuE_All->Fill(NuE,e.Weight); 
         Efficiency_NuE_All->FillWeighted(passed_All,e.Weight,NuE);
         if(NuE > 0 && passed_All)  h_SelectedNuE_All->Fill(NuE,e.Weight);

         h_MuonKE_All->Fill(MuonKE,e.Weight); 
         Efficiency_MuonKE_All->FillWeighted(passed_All,e.Weight,MuonKE);
         if(MuonKE > 0 && passed_All)  h_SelectedMuonKE_All->Fill(MuonKE,e.Weight);

         h_MuonTrueTheta_All->Fill(MuonTrueTheta,e.Weight); 
         Efficiency_MuonTrueTheta_All->FillWeighted(passed_All,e.Weight,MuonTrueTheta);
         if(passed_All)  h_SelectedMuonTrueTheta_All->Fill(MuonTrueTheta,e.Weight);

         h_MuonDetectorTheta_All->Fill(MuonDetectorTheta,e.Weight); 
         Efficiency_MuonDetectorTheta_All->FillWeighted(passed_All,e.Weight,MuonDetectorTheta);
         if(passed_All)  h_SelectedMuonDetectorTheta_All->Fill(MuonDetectorTheta,e.Weight);

         h_MuonDetectorPhi_All->Fill(MuonDetectorPhi,e.Weight); 
         Efficiency_MuonDetectorPhi_All->FillWeighted(passed_All,e.Weight,MuonDetectorPhi);
         if(passed_All)  h_SelectedMuonDetectorPhi_All->Fill(MuonDetectorPhi,e.Weight);

         h_MuonBeamTheta_All->Fill(MuonBeamTheta,e.Weight); 
         Efficiency_MuonBeamTheta_All->FillWeighted(passed_All,e.Weight,MuonBeamTheta);
         if(passed_All)  h_SelectedMuonBeamTheta_All->Fill(MuonBeamTheta,e.Weight);

         h_MuonBeamPhi_All->Fill(MuonBeamPhi,e.Weight); 
         Efficiency_MuonBeamPhi_All->FillWeighted(passed_All,e.Weight,MuonBeamPhi);
         if(passed_All)  h_SelectedMuonBeamPhi_All->Fill(MuonBeamPhi,e.Weight);

         h_KaonMomentum_All->Fill(KaonMomentum,e.Weight); 
         Efficiency_KaonMomentum_All->FillWeighted(passed_All,e.Weight,KaonMomentum);
         if(passed_All)  h_SelectedKaonMomentum_All->Fill(KaonMomentum,e.Weight);

         h_DecayMuonMomentum_All->Fill(DecayMuonMomentum,e.Weight); 
         Efficiency_DecayMuonMomentum_All->FillWeighted(passed_All,e.Weight,DecayMuonMomentum);
         if(passed_All)  h_SelectedDecayMuonMomentum_All->Fill(DecayMuonMomentum,e.Weight);

         h_DecayPionMomentum_All->Fill(DecayPionMomentum,e.Weight); 
         Efficiency_DecayPionMomentum_All->FillWeighted(passed_All,e.Weight,DecayPionMomentum);
         if(passed_All)  h_SelectedDecayPionMomentum_All->Fill(DecayPionMomentum,e.Weight);

         h_All->Fill(0.5,e.Weight);
         Efficiency_All->FillWeighted(passed_All,e.Weight,0.5);
         if(passed_All) h_Selected_All->Fill(0.5,e.Weight);

         // Fiducial Volume Cut
         h_Q2_FV->Fill(Q2,e.Weight);
         Efficiency_Q2_FV->FillWeighted(passed_FV,e.Weight,Q2);
         if(Q2 > 0 && passed_FV) h_SelectedQ2_FV->Fill(Q2,e.Weight);

         h_NuE_FV->Fill(NuE,e.Weight); 
         Efficiency_NuE_FV->FillWeighted(passed_FV,e.Weight,NuE);
         if(NuE > 0 && passed_FV)  h_SelectedNuE_FV->Fill(NuE,e.Weight);

         h_MuonKE_FV->Fill(MuonKE,e.Weight); 
         Efficiency_MuonKE_FV->FillWeighted(passed_FV,e.Weight,MuonKE);
         if(MuonKE > 0 && passed_FV)  h_SelectedMuonKE_FV->Fill(MuonKE,e.Weight);

         h_MuonTrueTheta_FV->Fill(MuonTrueTheta,e.Weight); 
         Efficiency_MuonTrueTheta_FV->FillWeighted(passed_FV,e.Weight,MuonTrueTheta);
         if(passed_FV)  h_SelectedMuonTrueTheta_FV->Fill(MuonTrueTheta,e.Weight);

         h_MuonDetectorTheta_FV->Fill(MuonDetectorTheta,e.Weight); 
         Efficiency_MuonDetectorTheta_FV->FillWeighted(passed_FV,e.Weight,MuonDetectorTheta);
         if(passed_FV)  h_SelectedMuonDetectorTheta_FV->Fill(MuonDetectorTheta,e.Weight);

         h_MuonDetectorPhi_FV->Fill(MuonDetectorPhi,e.Weight); 
         Efficiency_MuonDetectorPhi_FV->FillWeighted(passed_FV,e.Weight,MuonDetectorPhi);
         if(passed_FV)  h_SelectedMuonDetectorPhi_FV->Fill(MuonDetectorPhi,e.Weight);

         h_MuonBeamTheta_FV->Fill(MuonBeamTheta,e.Weight); 
         Efficiency_MuonBeamTheta_FV->FillWeighted(passed_FV,e.Weight,MuonBeamTheta);
         if(passed_FV)  h_SelectedMuonBeamTheta_FV->Fill(MuonBeamTheta,e.Weight);

         h_MuonBeamPhi_FV->Fill(MuonBeamPhi,e.Weight); 
         Efficiency_MuonBeamPhi_FV->FillWeighted(passed_FV,e.Weight,MuonBeamPhi);
         if(passed_FV)  h_SelectedMuonBeamPhi_FV->Fill(MuonBeamPhi,e.Weight);

         h_KaonMomentum_FV->Fill(KaonMomentum,e.Weight); 
         Efficiency_KaonMomentum_FV->FillWeighted(passed_FV,e.Weight,KaonMomentum);
         if(passed_FV)  h_SelectedKaonMomentum_FV->Fill(KaonMomentum,e.Weight);

         h_DecayMuonMomentum_FV->Fill(DecayMuonMomentum,e.Weight); 
         Efficiency_DecayMuonMomentum_FV->FillWeighted(passed_FV,e.Weight,DecayMuonMomentum);
         if(passed_FV)  h_SelectedDecayMuonMomentum_FV->Fill(DecayMuonMomentum,e.Weight);

         h_DecayPionMomentum_FV->Fill(DecayPionMomentum,e.Weight); 
         Efficiency_DecayPionMomentum_FV->FillWeighted(passed_FV,e.Weight,DecayPionMomentum);
         if(passed_FV)  h_SelectedDecayPionMomentum_FV->Fill(DecayPionMomentum,e.Weight);

         h_FV->Fill(0.5,e.Weight);
         Efficiency_FV->FillWeighted(passed_FV,e.Weight,0.5);
         if(passed_FV) h_Selected_FV->Fill(0.5,e.Weight);

         // Track Cut
         h_Q2_NuCCFilter->Fill(Q2,e.Weight);
         Efficiency_Q2_NuCCFilter->FillWeighted(passed_NuCCFilter,e.Weight,Q2);
         if(Q2 > 0 && passed_NuCCFilter) h_SelectedQ2_NuCCFilter->Fill(Q2,e.Weight);

         h_NuE_NuCCFilter->Fill(NuE,e.Weight); 
         Efficiency_NuE_NuCCFilter->FillWeighted(passed_NuCCFilter,e.Weight,NuE);
         if(NuE > 0 && passed_NuCCFilter)  h_SelectedNuE_NuCCFilter->Fill(NuE,e.Weight);

         h_MuonKE_NuCCFilter->Fill(MuonKE,e.Weight); 
         Efficiency_MuonKE_NuCCFilter->FillWeighted(passed_NuCCFilter,e.Weight,MuonKE);
         if(MuonKE > 0 && passed_NuCCFilter)  h_SelectedMuonKE_NuCCFilter->Fill(MuonKE,e.Weight);

         h_MuonTrueTheta_NuCCFilter->Fill(MuonTrueTheta,e.Weight); 
         Efficiency_MuonTrueTheta_NuCCFilter->FillWeighted(passed_NuCCFilter,e.Weight,MuonTrueTheta);
         if(passed_NuCCFilter)  h_SelectedMuonTrueTheta_NuCCFilter->Fill(MuonTrueTheta,e.Weight);

         h_MuonDetectorTheta_NuCCFilter->Fill(MuonDetectorTheta,e.Weight); 
         Efficiency_MuonDetectorTheta_NuCCFilter->FillWeighted(passed_NuCCFilter,e.Weight,MuonDetectorTheta);
         if(passed_NuCCFilter)  h_SelectedMuonDetectorTheta_NuCCFilter->Fill(MuonDetectorTheta,e.Weight);

         h_MuonDetectorPhi_NuCCFilter->Fill(MuonDetectorPhi,e.Weight); 
         Efficiency_MuonDetectorPhi_NuCCFilter->FillWeighted(passed_NuCCFilter,e.Weight,MuonDetectorPhi);
         if(passed_NuCCFilter)  h_SelectedMuonDetectorPhi_NuCCFilter->Fill(MuonDetectorPhi,e.Weight);

         h_MuonBeamTheta_NuCCFilter->Fill(MuonBeamTheta,e.Weight); 
         Efficiency_MuonBeamTheta_NuCCFilter->FillWeighted(passed_NuCCFilter,e.Weight,MuonBeamTheta);
         if(passed_NuCCFilter)  h_SelectedMuonBeamTheta_NuCCFilter->Fill(MuonBeamTheta,e.Weight);

         h_MuonBeamPhi_NuCCFilter->Fill(MuonBeamPhi,e.Weight); 
         Efficiency_MuonBeamPhi_NuCCFilter->FillWeighted(passed_NuCCFilter,e.Weight,MuonBeamPhi);
         if(passed_NuCCFilter)  h_SelectedMuonBeamPhi_NuCCFilter->Fill(MuonBeamPhi,e.Weight);

         h_KaonMomentum_NuCCFilter->Fill(KaonMomentum,e.Weight); 
         Efficiency_KaonMomentum_NuCCFilter->FillWeighted(passed_NuCCFilter,e.Weight,KaonMomentum);
         if(passed_NuCCFilter)  h_SelectedKaonMomentum_NuCCFilter->Fill(KaonMomentum,e.Weight);

         h_DecayMuonMomentum_NuCCFilter->Fill(DecayMuonMomentum,e.Weight); 
         Efficiency_DecayMuonMomentum_NuCCFilter->FillWeighted(passed_NuCCFilter,e.Weight,DecayMuonMomentum);
         if(passed_NuCCFilter)  h_SelectedDecayMuonMomentum_NuCCFilter->Fill(DecayMuonMomentum,e.Weight);

         h_DecayPionMomentum_NuCCFilter->Fill(DecayPionMomentum,e.Weight); 
         Efficiency_DecayPionMomentum_NuCCFilter->FillWeighted(passed_NuCCFilter,e.Weight,DecayPionMomentum);
         if(passed_NuCCFilter)  h_SelectedDecayPionMomentum_NuCCFilter->Fill(DecayPionMomentum,e.Weight);

         h_NuCCFilter->Fill(0.5,e.Weight);
         Efficiency_NuCCFilter->FillWeighted(passed_NuCCFilter,e.Weight,0.5);
         if(passed_NuCCFilter) h_Selected_NuCCFilter->Fill(0.5,e.Weight);

         // Shower Cut
         h_Q2_NDaughterTrack->Fill(Q2,e.Weight);
         Efficiency_Q2_NDaughterTrack->FillWeighted(passed_NDaughterTrack,e.Weight,Q2);
         if(Q2 > 0 && passed_NDaughterTrack) h_SelectedQ2_NDaughterTrack->Fill(Q2,e.Weight);

         h_NuE_NDaughterTrack->Fill(NuE,e.Weight); 
         Efficiency_NuE_NDaughterTrack->FillWeighted(passed_NDaughterTrack,e.Weight,NuE);
         if(NuE > 0 && passed_NDaughterTrack)  h_SelectedNuE_NDaughterTrack->Fill(NuE,e.Weight);

         h_MuonKE_NDaughterTrack->Fill(MuonKE,e.Weight); 
         Efficiency_MuonKE_NDaughterTrack->FillWeighted(passed_NDaughterTrack,e.Weight,MuonKE);
         if(MuonKE > 0 && passed_NDaughterTrack)  h_SelectedMuonKE_NDaughterTrack->Fill(MuonKE,e.Weight);

         h_MuonTrueTheta_NDaughterTrack->Fill(MuonTrueTheta,e.Weight); 
         Efficiency_MuonTrueTheta_NDaughterTrack->FillWeighted(passed_NDaughterTrack,e.Weight,MuonTrueTheta);
         if(passed_NDaughterTrack)  h_SelectedMuonTrueTheta_NDaughterTrack->Fill(MuonTrueTheta,e.Weight);

         h_MuonDetectorTheta_NDaughterTrack->Fill(MuonDetectorTheta,e.Weight); 
         Efficiency_MuonDetectorTheta_NDaughterTrack->FillWeighted(passed_NDaughterTrack,e.Weight,MuonDetectorTheta);
         if(passed_NDaughterTrack)  h_SelectedMuonDetectorTheta_NDaughterTrack->Fill(MuonDetectorTheta,e.Weight);

         h_MuonDetectorPhi_NDaughterTrack->Fill(MuonDetectorPhi,e.Weight); 
         Efficiency_MuonDetectorPhi_NDaughterTrack->FillWeighted(passed_NDaughterTrack,e.Weight,MuonDetectorPhi);
         if(passed_NDaughterTrack)  h_SelectedMuonDetectorPhi_NDaughterTrack->Fill(MuonDetectorPhi,e.Weight);

         h_MuonBeamTheta_NDaughterTrack->Fill(MuonBeamTheta,e.Weight); 
         Efficiency_MuonBeamTheta_NDaughterTrack->FillWeighted(passed_NDaughterTrack,e.Weight,MuonBeamTheta);
         if(passed_NDaughterTrack)  h_SelectedMuonBeamTheta_NDaughterTrack->Fill(MuonBeamTheta,e.Weight);

         h_MuonBeamPhi_NDaughterTrack->Fill(MuonBeamPhi,e.Weight); 
         Efficiency_MuonBeamPhi_NDaughterTrack->FillWeighted(passed_NDaughterTrack,e.Weight,MuonBeamPhi);
         if(passed_NDaughterTrack)  h_SelectedMuonBeamPhi_NDaughterTrack->Fill(MuonBeamPhi,e.Weight);

         h_KaonMomentum_NDaughterTrack->Fill(KaonMomentum,e.Weight); 
         Efficiency_KaonMomentum_NDaughterTrack->FillWeighted(passed_NDaughterTrack,e.Weight,KaonMomentum);
         if(passed_NDaughterTrack)  h_SelectedKaonMomentum_NDaughterTrack->Fill(KaonMomentum,e.Weight);

         h_DecayMuonMomentum_NDaughterTrack->Fill(DecayMuonMomentum,e.Weight); 
         Efficiency_DecayMuonMomentum_NDaughterTrack->FillWeighted(passed_NDaughterTrack,e.Weight,DecayMuonMomentum);
         if(passed_NDaughterTrack)  h_SelectedDecayMuonMomentum_NDaughterTrack->Fill(DecayMuonMomentum,e.Weight);

         h_DecayPionMomentum_NDaughterTrack->Fill(DecayPionMomentum,e.Weight); 
         Efficiency_DecayPionMomentum_NDaughterTrack->FillWeighted(passed_NDaughterTrack,e.Weight,DecayPionMomentum);
         if(passed_NDaughterTrack)  h_SelectedDecayPionMomentum_NDaughterTrack->Fill(DecayPionMomentum,e.Weight);

         h_NDaughterTrack->Fill(0.5,e.Weight);
         Efficiency_NDaughterTrack->FillWeighted(passed_NDaughterTrack,e.Weight,0.5);
         if(passed_NDaughterTrack) h_Selected_NDaughterTrack->Fill(0.5,e.Weight);

         // Muon ID
         h_Q2_DaughterFV->Fill(Q2,e.Weight);
         Efficiency_Q2_DaughterFV->FillWeighted(passed_DaughterFV,e.Weight,Q2);
         if(Q2 > 0 && passed_DaughterFV) h_SelectedQ2_DaughterFV->Fill(Q2,e.Weight);

         h_NuE_DaughterFV->Fill(NuE,e.Weight); 
         Efficiency_NuE_DaughterFV->FillWeighted(passed_DaughterFV,e.Weight,NuE);
         if(NuE > 0 && passed_DaughterFV)  h_SelectedNuE_DaughterFV->Fill(NuE,e.Weight);

         h_MuonKE_DaughterFV->Fill(MuonKE,e.Weight); 
         Efficiency_MuonKE_DaughterFV->FillWeighted(passed_DaughterFV,e.Weight,MuonKE);
         if(MuonKE > 0 && passed_DaughterFV)  h_SelectedMuonKE_DaughterFV->Fill(MuonKE,e.Weight);

         h_MuonTrueTheta_DaughterFV->Fill(MuonTrueTheta,e.Weight); 
         Efficiency_MuonTrueTheta_DaughterFV->FillWeighted(passed_DaughterFV,e.Weight,MuonTrueTheta);
         if(passed_DaughterFV)  h_SelectedMuonTrueTheta_DaughterFV->Fill(MuonTrueTheta,e.Weight);

         h_MuonDetectorTheta_DaughterFV->Fill(MuonDetectorTheta,e.Weight); 
         Efficiency_MuonDetectorTheta_DaughterFV->FillWeighted(passed_DaughterFV,e.Weight,MuonDetectorTheta);
         if(passed_DaughterFV)  h_SelectedMuonDetectorTheta_DaughterFV->Fill(MuonDetectorTheta,e.Weight);

         h_MuonDetectorPhi_DaughterFV->Fill(MuonDetectorPhi,e.Weight); 
         Efficiency_MuonDetectorPhi_DaughterFV->FillWeighted(passed_DaughterFV,e.Weight,MuonDetectorPhi);
         if(passed_DaughterFV)  h_SelectedMuonDetectorPhi_DaughterFV->Fill(MuonDetectorPhi,e.Weight);

         h_MuonBeamTheta_DaughterFV->Fill(MuonBeamTheta,e.Weight); 
         Efficiency_MuonBeamTheta_DaughterFV->FillWeighted(passed_DaughterFV,e.Weight,MuonBeamTheta);
         if(passed_DaughterFV)  h_SelectedMuonBeamTheta_DaughterFV->Fill(MuonBeamTheta,e.Weight);

         h_MuonBeamPhi_DaughterFV->Fill(MuonBeamPhi,e.Weight); 
         Efficiency_MuonBeamPhi_DaughterFV->FillWeighted(passed_DaughterFV,e.Weight,MuonBeamPhi);
         if(passed_DaughterFV)  h_SelectedMuonBeamPhi_DaughterFV->Fill(MuonBeamPhi,e.Weight);

         h_KaonMomentum_DaughterFV->Fill(KaonMomentum,e.Weight); 
         Efficiency_KaonMomentum_DaughterFV->FillWeighted(passed_DaughterFV,e.Weight,KaonMomentum);
         if(passed_DaughterFV)  h_SelectedKaonMomentum_DaughterFV->Fill(KaonMomentum,e.Weight);

         h_DecayMuonMomentum_DaughterFV->Fill(DecayMuonMomentum,e.Weight); 
         Efficiency_DecayMuonMomentum_DaughterFV->FillWeighted(passed_DaughterFV,e.Weight,DecayMuonMomentum);
         if(passed_DaughterFV)  h_SelectedDecayMuonMomentum_DaughterFV->Fill(DecayMuonMomentum,e.Weight);

         h_DecayPionMomentum_DaughterFV->Fill(DecayPionMomentum,e.Weight); 
         Efficiency_DecayPionMomentum_DaughterFV->FillWeighted(passed_DaughterFV,e.Weight,DecayPionMomentum);
         if(passed_DaughterFV)  h_SelectedDecayPionMomentum_DaughterFV->Fill(DecayPionMomentum,e.Weight);

         h_DaughterFV->Fill(0.5,e.Weight);
         Efficiency_DaughterFV->FillWeighted(passed_DaughterFV,e.Weight,0.5);
         if(passed_DaughterFV) h_Selected_DaughterFV->Fill(0.5,e.Weight);

	 /*
         // Decay Selector
         h_Q2_BDTCut->Fill(Q2,e.Weight);
         Efficiency_Q2_BDTCut->FillWeighted(passed_BDTCut,e.Weight,Q2);
         if(Q2 > 0 && passed_BDTCut) h_SelectedQ2_BDTCut->Fill(Q2,e.Weight);

         h_NuE_BDTCut->Fill(NuE,e.Weight); 
         Efficiency_NuE_BDTCut->FillWeighted(passed_BDTCut,e.Weight,NuE);
         if(NuE > 0 && passed_BDTCut)  h_SelectedNuE_BDTCut->Fill(NuE,e.Weight);

         h_MuonKE_BDTCut->Fill(MuonKE,e.Weight); 
         Efficiency_MuonKE_BDTCut->FillWeighted(passed_BDTCut,e.Weight,MuonKE);
         if(MuonKE > 0 && passed_BDTCut)  h_SelectedMuonKE_BDTCut->Fill(MuonKE,e.Weight);

         h_MuonTrueTheta_BDTCut->Fill(MuonTrueTheta,e.Weight); 
         Efficiency_MuonTrueTheta_BDTCut->FillWeighted(passed_BDTCut,e.Weight,MuonTrueTheta);
         if(passed_BDTCut)  h_SelectedMuonTrueTheta_BDTCut->Fill(MuonTrueTheta,e.Weight);

         h_MuonDetectorTheta_BDTCut->Fill(MuonDetectorTheta,e.Weight); 
         Efficiency_MuonDetectorTheta_BDTCut->FillWeighted(passed_BDTCut,e.Weight,MuonDetectorTheta);
         if(passed_BDTCut)  h_SelectedMuonDetectorTheta_BDTCut->Fill(MuonDetectorTheta,e.Weight);

         h_MuonDetectorPhi_BDTCut->Fill(MuonDetectorPhi,e.Weight); 
         Efficiency_MuonDetectorPhi_BDTCut->FillWeighted(passed_BDTCut,e.Weight,MuonDetectorPhi);
         if(passed_BDTCut)  h_SelectedMuonDetectorPhi_BDTCut->Fill(MuonDetectorPhi,e.Weight);

         h_MuonBeamTheta_BDTCut->Fill(MuonBeamTheta,e.Weight); 
         Efficiency_MuonBeamTheta_BDTCut->FillWeighted(passed_BDTCut,e.Weight,MuonBeamTheta);
         if(passed_BDTCut)  h_SelectedMuonBeamTheta_BDTCut->Fill(MuonBeamTheta,e.Weight);

         h_MuonBeamPhi_BDTCut->Fill(MuonBeamPhi,e.Weight); 
         Efficiency_MuonBeamPhi_BDTCut->FillWeighted(passed_BDTCut,e.Weight,MuonBeamPhi);
         if(passed_BDTCut)  h_SelectedMuonBeamPhi_BDTCut->Fill(MuonBeamPhi,e.Weight);

         h_KaonMomentum_BDTCut->Fill(KaonMomentum,e.Weight); 
         Efficiency_KaonMomentum_BDTCut->FillWeighted(passed_BDTCut,e.Weight,KaonMomentum);
         if(passed_BDTCut)  h_SelectedKaonMomentum_BDTCut->Fill(KaonMomentum,e.Weight);

         h_DecayMuonMomentum_BDTCut->Fill(DecayMuonMomentum,e.Weight); 
         Efficiency_DecayMuonMomentum_BDTCut->FillWeighted(passed_BDTCut,e.Weight,DecayMuonMomentum);
         if(passed_BDTCut)  h_SelectedDecayMuonMomentum_BDTCut->Fill(DecayMuonMomentum,e.Weight);

         h_DecayPionMomentum_BDTCut->Fill(DecayPionMomentum,e.Weight); 
         Efficiency_DecayPionMomentum_BDTCut->FillWeighted(passed_BDTCut,e.Weight,DecayPionMomentum);
         if(passed_BDTCut)  h_SelectedDecayPionMomentum_BDTCut->Fill(DecayPionMomentum,e.Weight);

         h_BDTCut->Fill(0.5,e.Weight);
         Efficiency_BDTCut->FillWeighted(passed_BDTCut,e.Weight,0.5);
         if(passed_BDTCut) h_Selected_BDTCut->Fill(0.5,e.Weight);

         // Connectedness
         h_Q2_DaughterTrackLength->Fill(Q2,e.Weight);
         Efficiency_Q2_DaughterTrackLength->FillWeighted(passed_DaughterTrackLength,e.Weight,Q2);
         if(Q2 > 0 && passed_DaughterTrackLength) h_SelectedQ2_DaughterTrackLength->Fill(Q2,e.Weight);

         h_NuE_DaughterTrackLength->Fill(NuE,e.Weight); 
         Efficiency_NuE_DaughterTrackLength->FillWeighted(passed_DaughterTrackLength,e.Weight,NuE);
         if(NuE > 0 && passed_DaughterTrackLength)  h_SelectedNuE_DaughterTrackLength->Fill(NuE,e.Weight);

         h_MuonKE_DaughterTrackLength->Fill(MuonKE,e.Weight); 
         Efficiency_MuonKE_DaughterTrackLength->FillWeighted(passed_DaughterTrackLength,e.Weight,MuonKE);
         if(MuonKE > 0 && passed_DaughterTrackLength)  h_SelectedMuonKE_DaughterTrackLength->Fill(MuonKE,e.Weight);

         h_MuonTrueTheta_DaughterTrackLength->Fill(MuonTrueTheta,e.Weight); 
         Efficiency_MuonTrueTheta_DaughterTrackLength->FillWeighted(passed_DaughterTrackLength,e.Weight,MuonTrueTheta);
         if(passed_DaughterTrackLength)  h_SelectedMuonTrueTheta_DaughterTrackLength->Fill(MuonTrueTheta,e.Weight);

         h_MuonDetectorTheta_DaughterTrackLength->Fill(MuonDetectorTheta,e.Weight); 
         Efficiency_MuonDetectorTheta_DaughterTrackLength->FillWeighted(passed_DaughterTrackLength,e.Weight,MuonDetectorTheta);
         if(passed_DaughterTrackLength)  h_SelectedMuonDetectorTheta_DaughterTrackLength->Fill(MuonDetectorTheta,e.Weight);

         h_MuonDetectorPhi_DaughterTrackLength->Fill(MuonDetectorPhi,e.Weight); 
         Efficiency_MuonDetectorPhi_DaughterTrackLength->FillWeighted(passed_DaughterTrackLength,e.Weight,MuonDetectorPhi);
         if(passed_DaughterTrackLength)  h_SelectedMuonDetectorPhi_DaughterTrackLength->Fill(MuonDetectorPhi,e.Weight);

         h_MuonBeamTheta_DaughterTrackLength->Fill(MuonBeamTheta,e.Weight); 
         Efficiency_MuonBeamTheta_DaughterTrackLength->FillWeighted(passed_DaughterTrackLength,e.Weight,MuonBeamTheta);
         if(passed_DaughterTrackLength)  h_SelectedMuonBeamTheta_DaughterTrackLength->Fill(MuonBeamTheta,e.Weight);

         h_MuonBeamPhi_DaughterTrackLength->Fill(MuonBeamPhi,e.Weight); 
         Efficiency_MuonBeamPhi_DaughterTrackLength->FillWeighted(passed_DaughterTrackLength,e.Weight,MuonBeamPhi);
         if(passed_DaughterTrackLength)  h_SelectedMuonBeamPhi_DaughterTrackLength->Fill(MuonBeamPhi,e.Weight);

         h_KaonMomentum_DaughterTrackLength->Fill(KaonMomentum,e.Weight); 
         Efficiency_KaonMomentum_DaughterTrackLength->FillWeighted(passed_DaughterTrackLength,e.Weight,KaonMomentum);
         if(passed_DaughterTrackLength)  h_SelectedKaonMomentum_DaughterTrackLength->Fill(KaonMomentum,e.Weight);

         h_DecayMuonMomentum_DaughterTrackLength->Fill(DecayMuonMomentum,e.Weight); 
         Efficiency_DecayMuonMomentum_DaughterTrackLength->FillWeighted(passed_DaughterTrackLength,e.Weight,DecayMuonMomentum);
         if(passed_DaughterTrackLength)  h_SelectedDecayMuonMomentum_DaughterTrackLength->Fill(DecayMuonMomentum,e.Weight);

         h_DecayPionMomentum_DaughterTrackLength->Fill(DecayPionMomentum,e.Weight); 
         Efficiency_DecayPionMomentum_DaughterTrackLength->FillWeighted(passed_DaughterTrackLength,e.Weight,DecayPionMomentum);
         if(passed_DaughterTrackLength)  h_SelectedDecayPionMomentum_DaughterTrackLength->Fill(DecayPionMomentum,e.Weight);

         h_DaughterTrackLength->Fill(0.5,e.Weight);
         Efficiency_DaughterTrackLength->FillWeighted(passed_DaughterTrackLength,e.Weight,0.5);
         if(passed_DaughterTrackLength) h_Selected_DaughterTrackLength->Fill(0.5,e.Weight);
	 */

	 for (const auto& pair : M.VectorPair) {
	   RecoParticle PrimaryKaonTrack = pair.first;
	   double RecoKaonMomentum = PrimaryKaonTrack.KaonMomentum;
	   
	   h_RecoKaonMomentum_NDaughterTrack->Fill(RecoKaonMomentum,e.Weight); 
	   Efficiency_RecoKaonMomentum_NDaughterTrack->FillWeighted(passed_All,e.Weight,RecoKaonMomentum);
	   if(passed_All)  h_SelectedRecoKaonMomentum_NDaughterTrack->Fill(RecoKaonMomentum,e.Weight);

	 }

      }

      //close the event assembler
      E.Close();

      
      // Entire Selection
      std::cout << "h_Q2_All->GetEntries(): " << h_Q2_All->GetEntries() << ", h_SelectedQ2_All->GetEntries(): "<< h_SelectedQ2_All->GetEntries()  << std::endl;
      DrawEfficiencyPlot(h_Q2_All,h_SelectedQ2_All,Efficiency_Q2_All,";True Q^{2} (GeV^{2},Mode,POT);Events",label + "_Q2_All",Mode,POT);
      DrawEfficiencyPlot(h_NuE_All,h_SelectedNuE_All,Efficiency_NuE_All,";True E_{#nu} (GeV,Mode,POT);Events",label + "_NuE_All",Mode,POT);
      DrawEfficiencyPlot(h_MuonKE_All,h_SelectedMuonKE_All,Efficiency_MuonKE_All,";True Muon E_{k} (GeV,Mode,POT);Events",label + "_MuonKE_All",Mode,POT);
      DrawEfficiencyPlot(h_MuonTrueTheta_All,h_SelectedMuonTrueTheta_All,Efficiency_MuonTrueTheta_All,";True Muon #theta;Events",label + "_MuonTrueTheta_All",Mode,POT);
      DrawEfficiencyPlot(h_MuonDetectorTheta_All,h_SelectedMuonDetectorTheta_All,Efficiency_MuonDetectorTheta_All,";Detector Muon #theta;Events",label + "_MuonDetectorTheta_All",Mode,POT);
      DrawEfficiencyPlot(h_MuonDetectorPhi_All,h_SelectedMuonDetectorPhi_All,Efficiency_MuonDetectorPhi_All,";Detector Muon #phi;Events",label + "_MuonDetectorPhi_All",Mode,POT);
      DrawEfficiencyPlot(h_MuonBeamTheta_All,h_SelectedMuonBeamTheta_All,Efficiency_MuonBeamTheta_All,";Beam Muon #theta;Events",label + "_MuonBeamTheta_All",Mode,POT);
      DrawEfficiencyPlot(h_MuonBeamPhi_All,h_SelectedMuonBeamPhi_All,Efficiency_MuonBeamPhi_All,";Beam Muon #phi;Events",label + "_MuonBeamPhi_All",Mode,POT);
      DrawEfficiencyPlot(h_KaonMomentum_All,h_SelectedKaonMomentum_All,Efficiency_KaonMomentum_All,";True K^{+} Momentum (GeV/c,Mode,POT);Events",label + "_KaonMomentum_All",Mode,POT);
      DrawEfficiencyPlot(h_DecayMuonMomentum_All,h_SelectedDecayMuonMomentum_All,Efficiency_DecayMuonMomentum_All,";True Decay Proton Momentum (GeV/c,Mode,POT);Events",label + "_DecayMuonMomentum_All",Mode,POT);
      DrawEfficiencyPlot(h_DecayPionMomentum_All,h_SelectedDecayPionMomentum_All,Efficiency_DecayPionMomentum_All,";True Decay #pi^{+} Momentum (GeV/c,Mode,POT);Events",label + "_DecayPionMomentum_All",Mode,POT);
      DrawEfficiencyPlot(h_All,h_Selected_All,Efficiency_All,";;Events",label + "_All",Mode,POT);

      // Fiducial Volume Cut
      DrawEfficiencyPlot(h_Q2_FV,h_SelectedQ2_FV,Efficiency_Q2_FV,";True Q^{2} (GeV^{2},Mode,POT);Events",label + "_Q2_FV",Mode,POT);
      DrawEfficiencyPlot(h_NuE_FV,h_SelectedNuE_FV,Efficiency_NuE_FV,";True E_{#nu} (GeV,Mode,POT);Events",label + "_NuE_FV",Mode,POT);
      DrawEfficiencyPlot(h_MuonKE_FV,h_SelectedMuonKE_FV,Efficiency_MuonKE_FV,";True Muon E_{k} (GeV,Mode,POT);Events",label + "_MuonKE_FV",Mode,POT);
      DrawEfficiencyPlot(h_MuonTrueTheta_FV,h_SelectedMuonTrueTheta_FV,Efficiency_MuonTrueTheta_FV,";True Muon #theta;Events",label + "_MuonTrueTheta_FV",Mode,POT);
      DrawEfficiencyPlot(h_MuonDetectorTheta_FV,h_SelectedMuonDetectorTheta_FV,Efficiency_MuonDetectorTheta_FV,";Detector Muon #theta;Events",label + "_MuonDetectorTheta_FV",Mode,POT);
      DrawEfficiencyPlot(h_MuonDetectorPhi_FV,h_SelectedMuonDetectorPhi_FV,Efficiency_MuonDetectorPhi_FV,";Detector Muon #phi;Events",label + "_MuonDetectorPhi_FV",Mode,POT);
      DrawEfficiencyPlot(h_MuonBeamTheta_FV,h_SelectedMuonBeamTheta_FV,Efficiency_MuonBeamTheta_FV,";Beam Muon #theta;Events",label + "_MuonBeamTheta_FV",Mode,POT);
      DrawEfficiencyPlot(h_MuonBeamPhi_FV,h_SelectedMuonBeamPhi_FV,Efficiency_MuonBeamPhi_FV,";Beam Muon #phi;Events",label + "_MuonBeamPhi_FV",Mode,POT);
      DrawEfficiencyPlot(h_KaonMomentum_FV,h_SelectedKaonMomentum_FV,Efficiency_KaonMomentum_FV,";True K^{+} Momentum (GeV/c,Mode,POT);Events",label + "_KaonMomentum_FV",Mode,POT);
      DrawEfficiencyPlot(h_DecayMuonMomentum_FV,h_SelectedDecayMuonMomentum_FV,Efficiency_DecayMuonMomentum_FV,";True Decay Proton Momentum (GeV/c,Mode,POT);Events",label + "_DecayMuonMomentum_FV",Mode,POT);
      DrawEfficiencyPlot(h_DecayPionMomentum_FV,h_SelectedDecayPionMomentum_FV,Efficiency_DecayPionMomentum_FV,";True Decay #pi^{+} Momentum (GeV/c,Mode,POT);Events",label + "_DecayPionMomentum_FV",Mode,POT);
      DrawEfficiencyPlot(h_FV,h_Selected_FV,Efficiency_FV,";;Events",label + "_FV",Mode,POT);


      // Track Cut
      DrawEfficiencyPlot(h_Q2_NuCCFilter,h_SelectedQ2_NuCCFilter,Efficiency_Q2_NuCCFilter,";True Q^{2} (GeV^{2},Mode,POT);Events",label + "_Q2_NuCCFilter",Mode,POT);
      DrawEfficiencyPlot(h_NuE_NuCCFilter,h_SelectedNuE_NuCCFilter,Efficiency_NuE_NuCCFilter,";True E_{#nu} (GeV,Mode,POT);Events",label + "_NuE_NuCCFilter",Mode,POT);
      DrawEfficiencyPlot(h_MuonKE_NuCCFilter,h_SelectedMuonKE_NuCCFilter,Efficiency_MuonKE_NuCCFilter,";True Muon E_{k} (GeV,Mode,POT);Events",label + "_MuonKE_NuCCFilter",Mode,POT);
      DrawEfficiencyPlot(h_MuonTrueTheta_NuCCFilter,h_SelectedMuonTrueTheta_NuCCFilter,Efficiency_MuonTrueTheta_NuCCFilter,";True Muon #theta;Events",label + "_MuonTrueTheta_NuCCFilter",Mode,POT);
      DrawEfficiencyPlot(h_MuonDetectorTheta_NuCCFilter,h_SelectedMuonDetectorTheta_NuCCFilter,Efficiency_MuonDetectorTheta_NuCCFilter,";Detector Muon #theta;Events",label + "_MuonDetectorTheta_NuCCFilter",Mode,POT);
      DrawEfficiencyPlot(h_MuonDetectorPhi_NuCCFilter,h_SelectedMuonDetectorPhi_NuCCFilter,Efficiency_MuonDetectorPhi_NuCCFilter,";Detector Muon #phi;Events",label + "_MuonDetectorPhi_NuCCFilter",Mode,POT);
      DrawEfficiencyPlot(h_MuonBeamTheta_NuCCFilter,h_SelectedMuonBeamTheta_NuCCFilter,Efficiency_MuonBeamTheta_NuCCFilter,";Beam Muon #theta;Events",label + "_MuonBeamTheta_NuCCFilter",Mode,POT);
      DrawEfficiencyPlot(h_MuonBeamPhi_NuCCFilter,h_SelectedMuonBeamPhi_NuCCFilter,Efficiency_MuonBeamPhi_NuCCFilter,";Beam Muon #phi;Events",label + "_MuonBeamPhi_NuCCFilter",Mode,POT);
      DrawEfficiencyPlot(h_KaonMomentum_NuCCFilter,h_SelectedKaonMomentum_NuCCFilter,Efficiency_KaonMomentum_NuCCFilter,";True K^{+} Momentum (GeV/c,Mode,POT);Events",label + "_KaonMomentum_NuCCFilter",Mode,POT);
      DrawEfficiencyPlot(h_DecayMuonMomentum_NuCCFilter,h_SelectedDecayMuonMomentum_NuCCFilter,Efficiency_DecayMuonMomentum_NuCCFilter,";True Decay Proton Momentum (GeV/c,Mode,POT);Events",label + "_DecayMuonMomentum_NuCCFilter",Mode,POT);
      DrawEfficiencyPlot(h_DecayPionMomentum_NuCCFilter,h_SelectedDecayPionMomentum_NuCCFilter,Efficiency_DecayPionMomentum_NuCCFilter,";True Decay #pi^{+} Momentum (GeV/c,Mode,POT);Events",label + "_DecayPionMomentum_NuCCFilter",Mode,POT);
      DrawEfficiencyPlot(h_NuCCFilter,h_Selected_NuCCFilter,Efficiency_NuCCFilter,";;Events",label + "_NuCCFilter",Mode,POT);

      // Shower Cut
      DrawEfficiencyPlot(h_Q2_NDaughterTrack,h_SelectedQ2_NDaughterTrack,Efficiency_Q2_NDaughterTrack,";True Q^{2} (GeV^{2},Mode,POT);Events",label + "_Q2_NDaughterTrack",Mode,POT);
      DrawEfficiencyPlot(h_NuE_NDaughterTrack,h_SelectedNuE_NDaughterTrack,Efficiency_NuE_NDaughterTrack,";True E_{#nu} (GeV,Mode,POT);Events",label + "_NuE_NDaughterTrack",Mode,POT);
      DrawEfficiencyPlot(h_MuonKE_NDaughterTrack,h_SelectedMuonKE_NDaughterTrack,Efficiency_MuonKE_NDaughterTrack,";True Muon E_{k} (GeV,Mode,POT);Events",label + "_MuonKE_NDaughterTrack",Mode,POT);
      DrawEfficiencyPlot(h_MuonTrueTheta_NDaughterTrack,h_SelectedMuonTrueTheta_NDaughterTrack,Efficiency_MuonTrueTheta_NDaughterTrack,";True Muon #theta;Events",label + "_MuonTrueTheta_NDaughterTrack",Mode,POT);
      DrawEfficiencyPlot(h_MuonDetectorTheta_NDaughterTrack,h_SelectedMuonDetectorTheta_NDaughterTrack,Efficiency_MuonDetectorTheta_NDaughterTrack,";Detector Muon #theta;Events",label + "_MuonDetectorTheta_NDaughterTrack",Mode,POT);
      DrawEfficiencyPlot(h_MuonDetectorPhi_NDaughterTrack,h_SelectedMuonDetectorPhi_NDaughterTrack,Efficiency_MuonDetectorPhi_NDaughterTrack,";Detector Muon #phi;Events",label + "_MuonDetectorPhi_NDaughterTrack",Mode,POT);
      DrawEfficiencyPlot(h_MuonBeamTheta_NDaughterTrack,h_SelectedMuonBeamTheta_NDaughterTrack,Efficiency_MuonBeamTheta_NDaughterTrack,";Beam Muon #theta;Events",label + "_MuonBeamTheta_NDaughterTrack",Mode,POT);
      DrawEfficiencyPlot(h_MuonBeamPhi_NDaughterTrack,h_SelectedMuonBeamPhi_NDaughterTrack,Efficiency_MuonBeamPhi_NDaughterTrack,";Beam Muon #phi;Events",label + "_MuonBeamPhi_NDaughterTrack",Mode,POT);
      DrawEfficiencyPlot(h_KaonMomentum_NDaughterTrack,h_SelectedKaonMomentum_NDaughterTrack,Efficiency_KaonMomentum_NDaughterTrack,";True K^{+} Momentum (GeV/c,Mode,POT);Events",label + "_KaonMomentum_NDaughterTrack",Mode,POT);
      DrawEfficiencyPlot(h_DecayMuonMomentum_NDaughterTrack,h_SelectedDecayMuonMomentum_NDaughterTrack,Efficiency_DecayMuonMomentum_NDaughterTrack,";True Decay Proton Momentum (GeV/c,Mode,POT);Events",label + "_DecayMuonMomentum_NDaughterTrack",Mode,POT);
      DrawEfficiencyPlot(h_DecayPionMomentum_NDaughterTrack,h_SelectedDecayPionMomentum_NDaughterTrack,Efficiency_DecayPionMomentum_NDaughterTrack,";True Decay #pi^{+} Momentum (GeV/c,Mode,POT);Events",label + "_DecayPionMomentum_NDaughterTrack",Mode,POT);
      DrawEfficiencyPlot(h_NDaughterTrack,h_Selected_NDaughterTrack,Efficiency_NDaughterTrack,";;Events",label + "_NDaughterTrack",Mode,POT);

      // Muon ID
      DrawEfficiencyPlot(h_Q2_DaughterFV,h_SelectedQ2_DaughterFV,Efficiency_Q2_DaughterFV,";True Q^{2} (GeV^{2},Mode,POT);Events",label + "_Q2_DaughterFV",Mode,POT);
      DrawEfficiencyPlot(h_NuE_DaughterFV,h_SelectedNuE_DaughterFV,Efficiency_NuE_DaughterFV,";True E_{#nu} (GeV,Mode,POT);Events",label + "_NuE_DaughterFV",Mode,POT);
      DrawEfficiencyPlot(h_MuonKE_DaughterFV,h_SelectedMuonKE_DaughterFV,Efficiency_MuonKE_DaughterFV,";True Muon E_{k} (GeV,Mode,POT);Events",label + "_MuonKE_DaughterFV",Mode,POT);
      DrawEfficiencyPlot(h_MuonTrueTheta_DaughterFV,h_SelectedMuonTrueTheta_DaughterFV,Efficiency_MuonTrueTheta_DaughterFV,";True Muon #theta;Events",label + "_MuonTrueTheta_DaughterFV",Mode,POT);
      DrawEfficiencyPlot(h_MuonDetectorTheta_DaughterFV,h_SelectedMuonDetectorTheta_DaughterFV,Efficiency_MuonDetectorTheta_DaughterFV,";Detector Muon #theta;Events",label + "_MuonDetectorTheta_DaughterFV",Mode,POT);
      DrawEfficiencyPlot(h_MuonDetectorPhi_DaughterFV,h_SelectedMuonDetectorPhi_DaughterFV,Efficiency_MuonDetectorPhi_DaughterFV,";Detector Muon #phi;Events",label + "_MuonDetectorPhi_DaughterFV",Mode,POT);
      DrawEfficiencyPlot(h_MuonBeamTheta_DaughterFV,h_SelectedMuonBeamTheta_DaughterFV,Efficiency_MuonBeamTheta_DaughterFV,";Beam Muon #theta;Events",label + "_MuonBeamTheta_DaughterFV",Mode,POT);
      DrawEfficiencyPlot(h_MuonBeamPhi_DaughterFV,h_SelectedMuonBeamPhi_DaughterFV,Efficiency_MuonBeamPhi_DaughterFV,";Beam Muon #phi;Events",label + "_MuonBeamPhi_DaughterFV",Mode,POT);
      DrawEfficiencyPlot(h_KaonMomentum_DaughterFV,h_SelectedKaonMomentum_DaughterFV,Efficiency_KaonMomentum_DaughterFV,";True K^{+} Momentum (GeV/c,Mode,POT);Events",label + "_KaonMomentum_DaughterFV",Mode,POT);
      DrawEfficiencyPlot(h_DecayMuonMomentum_DaughterFV,h_SelectedDecayMuonMomentum_DaughterFV,Efficiency_DecayMuonMomentum_DaughterFV,";True Decay Proton Momentum (GeV/c,Mode,POT);Events",label + "_DecayMuonMomentum_DaughterFV",Mode,POT);
      DrawEfficiencyPlot(h_DecayPionMomentum_DaughterFV,h_SelectedDecayPionMomentum_DaughterFV,Efficiency_DecayPionMomentum_DaughterFV,";True Decay #pi^{+} Momentum (GeV/c,Mode,POT);Events",label + "_DecayPionMomentum_DaughterFV",Mode,POT);
      DrawEfficiencyPlot(h_DaughterFV,h_Selected_DaughterFV,Efficiency_DaughterFV,";;Events",label + "_DaughterFV",Mode,POT);
      

      /*
      // Track Selector BDT
      DrawEfficiencyPlot(h_Q2_BDTCut,h_SelectedQ2_BDTCut,Efficiency_Q2_BDTCut,";True Q^{2} (GeV^{2},Mode,POT);Events",label + "_Q2_BDTCut",Mode,POT);
      DrawEfficiencyPlot(h_NuE_BDTCut,h_SelectedNuE_BDTCut,Efficiency_NuE_BDTCut,";True E_{#nu} (GeV,Mode,POT);Events",label + "_NuE_BDTCut",Mode,POT);
      DrawEfficiencyPlot(h_MuonKE_BDTCut,h_SelectedMuonKE_BDTCut,Efficiency_MuonKE_BDTCut,";True Muon E_{k} (GeV,Mode,POT);Events",label + "_MuonKE_BDTCut",Mode,POT);
      DrawEfficiencyPlot(h_MuonTrueTheta_BDTCut,h_SelectedMuonTrueTheta_BDTCut,Efficiency_MuonTrueTheta_BDTCut,";True Muon #theta;Events",label + "_MuonTrueTheta_BDTCut",Mode,POT);
      DrawEfficiencyPlot(h_MuonDetectorTheta_BDTCut,h_SelectedMuonDetectorTheta_BDTCut,Efficiency_MuonDetectorTheta_BDTCut,";Detector Muon #theta;Events",label + "_MuonDetectorTheta_BDTCut",Mode,POT);
      DrawEfficiencyPlot(h_MuonDetectorPhi_BDTCut,h_SelectedMuonDetectorPhi_BDTCut,Efficiency_MuonDetectorPhi_BDTCut,";Detector Muon #phi;Events",label + "_MuonDetectorPhi_BDTCut",Mode,POT);
      DrawEfficiencyPlot(h_MuonBeamTheta_BDTCut,h_SelectedMuonBeamTheta_BDTCut,Efficiency_MuonBeamTheta_BDTCut,";Beam Muon #theta;Events",label + "_MuonBeamTheta_BDTCut",Mode,POT);
      DrawEfficiencyPlot(h_MuonBeamPhi_BDTCut,h_SelectedMuonBeamPhi_BDTCut,Efficiency_MuonBeamPhi_BDTCut,";Beam Muon #phi;Events",label + "_MuonBeamPhi_BDTCut",Mode,POT);
      DrawEfficiencyPlot(h_KaonMomentum_BDTCut,h_SelectedKaonMomentum_BDTCut,Efficiency_KaonMomentum_BDTCut,";True K^{+} Momentum (GeV/c,Mode,POT);Events",label + "_KaonMomentum_BDTCut",Mode,POT);
      DrawEfficiencyPlot(h_DecayMuonMomentum_BDTCut,h_SelectedDecayMuonMomentum_BDTCut,Efficiency_DecayMuonMomentum_BDTCut,";True Decay Proton Momentum (GeV/c,Mode,POT);Events",label + "_DecayMuonMomentum_BDTCut",Mode,POT);
      DrawEfficiencyPlot(h_DecayPionMomentum_BDTCut,h_SelectedDecayPionMomentum_BDTCut,Efficiency_DecayPionMomentum_BDTCut,";True Decay #pi^{+} Momentum (GeV/c,Mode,POT);Events",label + "_DecayPionMomentum_BDTCut",Mode,POT);
      DrawEfficiencyPlot(h_BDTCut,h_Selected_BDTCut,Efficiency_BDTCut,";;Events",label + "_BDTCut",Mode,POT);


      // CT
      DrawEfficiencyPlot(h_Q2_DaughterTrackLength,h_SelectedQ2_DaughterTrackLength,Efficiency_Q2_DaughterTrackLength,";True Q^{2} (GeV^{2},Mode,POT);Events",label + "_Q2_DaughterTrackLength",Mode,POT);
      DrawEfficiencyPlot(h_NuE_DaughterTrackLength,h_SelectedNuE_DaughterTrackLength,Efficiency_NuE_DaughterTrackLength,";True E_{#nu} (GeV,Mode,POT);Events",label + "_NuE_DaughterTrackLength",Mode,POT);
      DrawEfficiencyPlot(h_MuonKE_DaughterTrackLength,h_SelectedMuonKE_DaughterTrackLength,Efficiency_MuonKE_DaughterTrackLength,";True Muon E_{k} (GeV,Mode,POT);Events",label + "_MuonKE_DaughterTrackLength",Mode,POT);
      DrawEfficiencyPlot(h_MuonTrueTheta_DaughterTrackLength,h_SelectedMuonTrueTheta_DaughterTrackLength,Efficiency_MuonTrueTheta_DaughterTrackLength,";True Muon #theta;Events",label + "_MuonTrueTheta_DaughterTrackLength",Mode,POT);
      DrawEfficiencyPlot(h_MuonDetectorTheta_DaughterTrackLength,h_SelectedMuonDetectorTheta_DaughterTrackLength,Efficiency_MuonDetectorTheta_DaughterTrackLength,";Detector Muon #theta;Events",label + "_MuonDetectorTheta_DaughterTrackLength",Mode,POT);
      DrawEfficiencyPlot(h_MuonDetectorPhi_DaughterTrackLength,h_SelectedMuonDetectorPhi_DaughterTrackLength,Efficiency_MuonDetectorPhi_DaughterTrackLength,";Detector Muon #phi;Events",label + "_MuonDetectorPhi_DaughterTrackLength",Mode,POT);
      DrawEfficiencyPlot(h_MuonBeamTheta_DaughterTrackLength,h_SelectedMuonBeamTheta_DaughterTrackLength,Efficiency_MuonBeamTheta_DaughterTrackLength,";Beam Muon #theta;Events",label + "_MuonBeamTheta_DaughterTrackLength",Mode,POT);
      DrawEfficiencyPlot(h_MuonBeamPhi_DaughterTrackLength,h_SelectedMuonBeamPhi_DaughterTrackLength,Efficiency_MuonBeamPhi_DaughterTrackLength,";Beam Muon #phi;Events",label + "_MuonBeamPhi_DaughterTrackLength",Mode,POT);
      DrawEfficiencyPlot(h_KaonMomentum_DaughterTrackLength,h_SelectedKaonMomentum_DaughterTrackLength,Efficiency_KaonMomentum_DaughterTrackLength,";True K^{+} Momentum (GeV/c,Mode,POT);Events",label + "_KaonMomentum_DaughterTrackLength",Mode,POT);
      DrawEfficiencyPlot(h_DecayMuonMomentum_DaughterTrackLength,h_SelectedDecayMuonMomentum_DaughterTrackLength,Efficiency_DecayMuonMomentum_DaughterTrackLength,";True Decay Proton Momentum (GeV/c,Mode,POT);Events",label + "_DecayMuonMomentum_DaughterTrackLength",Mode,POT);
      DrawEfficiencyPlot(h_DecayPionMomentum_DaughterTrackLength,h_SelectedDecayPionMomentum_DaughterTrackLength,Efficiency_DecayPionMomentum_DaughterTrackLength,";True Decay #pi^{+} Momentum (GeV/c,Mode,POT);Events",label + "_DecayPionMomentum_DaughterTrackLength",Mode,POT);
      DrawEfficiencyPlot(h_DaughterTrackLength,h_Selected_DaughterTrackLength,Efficiency_DaughterTrackLength,";;Events",label + "_DaughterTrackLength",Mode,POT);
      */

      DrawEfficiencyPlot(h_RecoKaonMomentum_NDaughterTrack,h_SelectedRecoKaonMomentum_NDaughterTrack,Efficiency_RecoKaonMomentum_NDaughterTrack,";Reconstructed K^{+} Momentum (GeV/c,Mode,POT);Events",label + "_RecoKaonMomentum_NDaughterTrack",Mode,POT);


   }


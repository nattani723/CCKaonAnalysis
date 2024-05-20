#ifndef _BDTManager_h_
#define _BDTManager_h_

#include "Event.h"
#include "TFile.h"
#include "TTree.h"
#include "TVector3.h"
#include "RecoParticle.h"
#include "Misc.h"

#include "TMVA/Tools.h"
#include "TMVA/Reader.h"

// Track selector BDT class. Has two modes, training
// and testing. Training for filling the trees train
// new BDT tunes. Testing to use them in the selection

class BDTManager {

   public:

      BDTManager();
      BDTManager(std::string Mode);
      ~BDTManager();

      void FillTree(const Event &e, const RecoParticle &PrimaryKaonTrackParticle, const RecoParticle &DaughterTrackParticle);
      void WriteTrainingTrees();    

   private:

      enum e_Algs{kLD,kBDT,kBDTG,kKNN,kLikelihood,kMLPBNN,kAlgMAX};
      const std::vector<std::string> Algs_str = {"LD","BDT","BDTG","KNN","Likelihood","MLPBNN"};
      std::string Alg = "BDT";

      std::string fMode;

      bool SetVariables(RecoParticle PrimaryKaonTrackParticle, RecoParticle DaughterTrackParticle);

      // Training trees

      void SetupTrainingTrees();    

      TFile *f_Trees;
      TTree *t_Signal=nullptr;
      TTree *t_Background=nullptr;

      // Variables
      Float_t v_PrimaryTrack_Chi2_Kaon_3Plane;
      Float_t v_PrimaryTrack_Chi2_Proton_3Plane;
      Float_t v_PrimaryTrack_Chi2_Pion_3Plane;
      Float_t v_PrimaryTrack_Chi2_Muon_3Plane;
      Float_t v_DaughterTrack_Chi2_Kaon_3Plane;
      Float_t v_DaughterTrack_Chi2_Proton_3Plane;
      Float_t v_DaughterTrack_Chi2_Pion_3Plane;
      Float_t v_DaughterTrack_Chi2_Muon_3Plane;
      Float_t v_PrimaryTrack_LLR_PID;
      Float_t v_PrimaryTrack_LLR_PID_Kaon;
      Float_t v_DaughterTrack_LLR_PID;
      Float_t v_DaughterTrack_LLR_PID_Kaon;
      Float_t v_DaughterTrackLength;
      Float_t v_PrimaryTrack_dEdX;
      Float_t v_DaughterTrack_dEdX;


      const std::pair<double,double> separation_limits = { 0 , 20 };
      const std::pair<double,double> pid_limits = { -10 , 10 };
      const std::pair<double,double> trkscore_limits = { 0 , 1.0 };
      const std::pair<double,double> dEdX_limits = { 0.0 , 20 };
      const std::pair<double,double> LLR_limits = { -1.0 , 1.0 };

      // Importing BDT and using in selection
      std::string fWeightsDir;
      TMVA::Reader *reader=nullptr;

   public:

      void SetupBDT(std::string WeightsDir="",std::string alg="BDT");
      void SetAlg(std::string alg);
      double GetScore(RecoParticle DecayProtonCandidate,RecoParticle DecayPionCandidate);
      double CalculateScore(Event &e);

};

#endif

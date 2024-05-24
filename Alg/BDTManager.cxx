#ifndef _BDTManager_cxx_
#define _BDTManager_cxx_

#include "BDTManager.h"

///////////////////////////////////////////////////////////////////////////////////////////////

BDTManager::BDTManager(){

   fMode = "Test";

}

///////////////////////////////////////////////////////////////////////////////////////////////

BDTManager::BDTManager(std::string Mode){

   fMode = Mode;
   if(fMode == "Train") SetupTrainingTrees();

}

///////////////////////////////////////////////////////////////////////////////////////////////

BDTManager::~BDTManager(){

   if(fMode == "Train"){
      f_Trees->Close();
      delete f_Trees;
   }
   else if(fMode == "Test"){
      if(reader != nullptr)  delete reader;
   }

}

///////////////////////////////////////////////////////////////////////////////////////////////

void BDTManager::WriteTrainingTrees(){

   std::cout << "Entries in Signal tree = " << t_Signal->GetEntries() << std::endl;
   std::cout << "Entries in Background tree = " << t_Background->GetEntries() << std::endl;

   f_Trees->cd();

   t_Signal->Write("SignalTree");
   t_Background->Write("BackgroundTree");

}   

///////////////////////////////////////////////////////////////////////////////////////////////

void BDTManager::SetupTrainingTrees(){

   system("mkdir -p SelectorMVA");

   f_Trees = TFile::Open( "SelectorMVA/Trees.root" , "RECREATE" );
   t_Signal = new TTree("t_SelectorMVA_Signal","Signal");
   t_Background = new TTree("t_SelectorMVA_Background","Background");

   t_Signal->Branch("PrimaryTrack_Chi2_Kaon_3Plane",&v_PrimaryTrack_Chi2_Kaon_3Plane);
   t_Signal->Branch("PrimaryTrack_Chi2_Proton_3Plane",&v_PrimaryTrack_Chi2_Proton_3Plane);
   t_Signal->Branch("PrimaryTrack_Chi2_Muon_3Plane",&v_PrimaryTrack_Chi2_Muon_3Plane);
   t_Signal->Branch("PrimaryTrack_Chi2_Pion_3Plane",&v_PrimaryTrack_Chi2_Pion_3Plane);
   t_Signal->Branch("DaughterTrack_Chi2_Kaon_3Plane",&v_DaughterTrack_Chi2_Kaon_3Plane);
   t_Signal->Branch("DaughterTrack_Chi2_Proton_3Plane",&v_DaughterTrack_Chi2_Proton_3Plane);
   t_Signal->Branch("DaughterTrack_Chi2_Muon_3Plane",&v_DaughterTrack_Chi2_Muon_3Plane);
   t_Signal->Branch("DaughterTrack_Chi2_Pion_3Plane",&v_DaughterTrack_Chi2_Pion_3Plane);
   t_Signal->Branch("PrimaryTrack_LLR_PID",&v_PrimaryTrack_LLR_PID);
   t_Signal->Branch("PrimaryTrack_LLR_PID_Kaon",&v_PrimaryTrack_LLR_PID_Kaon);
   t_Signal->Branch("PrimaryTrack_dEdX",&v_PrimaryTrack_dEdX);
   t_Signal->Branch("DaughterTrack_LLR_PID",&v_DaughterTrack_LLR_PID);
   t_Signal->Branch("DaughterTrack_LLR_PID_Kaon",&v_DaughterTrack_LLR_PID_Kaon);
   t_Signal->Branch("DaughterTrack_dEdX",&v_DaughterTrack_dEdX);
   t_Signal->Branch("DaughterTrackLength",&v_DaughterTrackLength);

   t_Background->Branch("PrimaryTrack_Chi2_Kaon_3Plane",&v_PrimaryTrack_Chi2_Kaon_3Plane);
   t_Background->Branch("PrimaryTrack_Chi2_Proton_3Plane",&v_PrimaryTrack_Chi2_Proton_3Plane);
   t_Background->Branch("PrimaryTrack_Chi2_Muon_3Plane",&v_PrimaryTrack_Chi2_Muon_3Plane);
   t_Background->Branch("PrimaryTrack_Chi2_Pion_3Plane",&v_PrimaryTrack_Chi2_Pion_3Plane);
   t_Background->Branch("DaughterTrack_Chi2_Kaon_3Plane",&v_DaughterTrack_Chi2_Kaon_3Plane);
   t_Background->Branch("DaughterTrack_Chi2_Proton_3Plane",&v_DaughterTrack_Chi2_Proton_3Plane);
   t_Background->Branch("DaughterTrack_Chi2_Muon_3Plane",&v_DaughterTrack_Chi2_Muon_3Plane);
   t_Background->Branch("DaughterTrack_Chi2_Pion_3Plane",&v_DaughterTrack_Chi2_Pion_3Plane);
   t_Background->Branch("PrimaryTrack_LLR_PID",&v_PrimaryTrack_LLR_PID);
   t_Background->Branch("PrimaryTrack_LLR_PID_Kaon",&v_PrimaryTrack_LLR_PID_Kaon);
   t_Background->Branch("PrimaryTrack_dEdX",&v_PrimaryTrack_dEdX);
   t_Background->Branch("DaughterTrack_LLR_PID",&v_DaughterTrack_LLR_PID);
   t_Background->Branch("DaughterTrack_LLR_PID_Kaon",&v_DaughterTrack_LLR_PID_Kaon);
   t_Background->Branch("DaughterTrack_dEdX",&v_DaughterTrack_dEdX);

}

///////////////////////////////////////////////////////////////////////////////////////////////

void BDTManager::FillTree(const Event &e, const RecoParticle &PrimaryKaonTrackParticle, const RecoParticle &DaughterTrackParticle){

   // Check in the right running mode first
   assert(fMode == "Train");

   // Only train this alg on events with real reconstructed decays
   if(!e.GoodReco) return;

   if( t_Signal == nullptr || t_Background == nullptr ){ std::cout << "Trees not setup, exiting" << std::endl; return; }

   if(!SetVariables(PrimaryKaonTrackParticle, DaughterTrackParticle)) return;

   //if(e.GoodReco && PrimaryKaonTrackParticle.TrackTruePDG == 321 && (DaughterTrackParticle.TrackTruePDG == -13 || DaughterTrackParticle.TrackTruePDG == 211) ) t_Signal->Fill();
   if(e.GoodReco && PrimaryKaonTrackParticle.Index == e.TrueKaonIndex && ( DaughterTrackParticle.Index == e.TrueDecayMuonIndex ||  DaughterTrackParticle.Index == e.TrueDecayPionIndex ))
     t_Signal->Fill();
   else t_Background->Fill();

}

///////////////////////////////////////////////////////////////////////////////////////////////

bool BDTManager::SetVariables(const RecoParticle &PrimaryKaonTrackParticle, const RecoParticle &DaughterTrackParticle){

   // Catch default dEdX fills
  /*
   if(PrimaryKaonTrackParticle.MeandEdX_ThreePlane < 0 || DaughterTrackParticle.MeandEdX_ThreePlane < 0) return false;
   if(std::isnan(PrimaryKaonTrackParticle.MeandEdX_ThreePlane) || std::isnan(DaughterTrackParticle.MeandEdX_ThreePlane)) return false;
  */

   v_PrimaryTrack_dEdX = Limit(PrimaryKaonTrackParticle.MeandEdX_ThreePlane,dEdX_limits);
   v_DaughterTrack_dEdX = Limit(DaughterTrackParticle.MeandEdX_ThreePlane,dEdX_limits);

   v_PrimaryTrack_Chi2_Kaon_3Plane = PrimaryKaonTrackParticle.Track_Chi2_Kaon_3Plane;
   v_PrimaryTrack_Chi2_Proton_3Plane = PrimaryKaonTrackParticle.Track_Chi2_Proton_3Plane;
   v_PrimaryTrack_Chi2_Muon_3Plane = PrimaryKaonTrackParticle.Track_Chi2_Muon_3Plane;
   v_PrimaryTrack_Chi2_Pion_3Plane = PrimaryKaonTrackParticle.Track_Chi2_Pion_3Plane;

   v_DaughterTrack_Chi2_Kaon_3Plane = DaughterTrackParticle.Track_Chi2_Kaon_3Plane;
   v_DaughterTrack_Chi2_Proton_3Plane = DaughterTrackParticle.Track_Chi2_Proton_3Plane;
   v_DaughterTrack_Chi2_Muon_3Plane = DaughterTrackParticle.Track_Chi2_Muon_3Plane;
   v_DaughterTrack_Chi2_Pion_3Plane = DaughterTrackParticle.Track_Chi2_Pion_3Plane;

   v_PrimaryTrack_LLR_PID = PrimaryKaonTrackParticle.Track_LLR_PID;
   v_PrimaryTrack_LLR_PID_Kaon = PrimaryKaonTrackParticle.Track_LLR_PID_Kaon;
   v_DaughterTrack_LLR_PID = DaughterTrackParticle.Track_LLR_PID;
   v_DaughterTrack_LLR_PID_Kaon = DaughterTrackParticle.Track_LLR_PID_Kaon;

   v_DaughterTrackLength = DaughterTrackParticle.TrackLength;

   return true;

}

///////////////////////////////////////////////////////////////////////////////////////////////

void BDTManager::SetupBDT(std::string WeightsDir,std::string alg){

   assert(fMode == "Test");

   if(WeightsDir == ""){ 
      std::cout << "No weights directory given, assuming default location" << std::endl;
      fWeightsDir = "/home/lar/cthorpe/uboone/HyperonSelection/TMVA/SelectorMVA/v1/dataset/weights";
   }
   else fWeightsDir = WeightsDir;  


   TMVA::Tools::Instance();
   reader = new TMVA::Reader( "!Color:!Silent" );

   reader->AddVariable("PrimaryTrack_Chi2_Kaon_3Plane",&v_PrimaryTrack_Chi2_Kaon_3Plane);
   reader->AddVariable("PrimaryTrack_Chi2_Proton_3Plane",&v_PrimaryTrack_Chi2_Proton_3Plane);
   reader->AddVariable("PrimaryTrack_Chi2_Muon_3Plane",&v_PrimaryTrack_Chi2_Muon_3Plane);
   reader->AddVariable("PrimaryTrack_Chi2_Pion_3Plane",&v_PrimaryTrack_Chi2_Pion_3Plane);
   reader->AddVariable("DaughterTrack_Chi2_Kaon_3Plane",&v_DaughterTrack_Chi2_Kaon_3Plane);
   reader->AddVariable("DaughterTrack_Chi2_Proton_3Plane",&v_DaughterTrack_Chi2_Proton_3Plane);
   reader->AddVariable("DaughterTrack_Chi2_Muon_3Plane",&v_DaughterTrack_Chi2_Muon_3Plane);
   reader->AddVariable("DaughterTrack_Chi2_Pion_3Plane",&v_DaughterTrack_Chi2_Pion_3Plane);
   reader->AddVariable("PrimaryTrack_LLR_PID",&v_PrimaryTrack_LLR_PID);
   reader->AddVariable("PrimaryTrack_LLR_PID_Kaon",&v_PrimaryTrack_LLR_PID_Kaon);
   reader->AddVariable("DaughterTrack_LLR_PID",&v_DaughterTrack_LLR_PID);
   reader->AddVariable("DaughterTrack_LLR_PID_Kaon",&v_DaughterTrack_LLR_PID_Kaon);
   reader->AddVariable("DaughterTrackLength",&v_DaughterTrackLength);

   std::map<std::string,int> Use;
   for(size_t i_a=0;i_a<Algs_str.size();i_a++)
      Use[Algs_str.at(i_a)] = 1;

   TString prefix = "TMVAClassification";

   for (std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) {
      if (it->second) {
         TString methodName = TString(it->first) + TString(" method");
         TString weightfile = fWeightsDir + "/" + prefix + TString("_") + TString(it->first) + TString(".weights.xml");
         std::cout << "Opening weight file " << weightfile << std::endl; 
         reader->BookMVA( methodName, weightfile );
      }
   }

}

///////////////////////////////////////////////////////////////////////////////////////////////

void BDTManager::SetAlg(std::string alg){

   bool found_alg = false;
   for(size_t i_a=0;i_a<Algs_str.size();i_a++)
      if(alg == Algs_str.at(i_a)) found_alg = true;

   if(!found_alg) throw std::invalid_argument("BDTManager: Classifier " + alg + " not found, exiting");

   Alg = alg;

}

///////////////////////////////////////////////////////////////////////////////////////////////

double BDTManager::CalculateScore(Event &e){
  
  //if(!SetVariables(e)) return -1.0;

  double score = reader->EvaluateMVA("BDT method");

  e.BDTScore = score;

  return score;
}


///////////////////////////////////////////////////////////////////////////////////////////////

double BDTManager::CalculateScore(Event &e, const RecoParticle &PrimaryKaonTrackParticle, const RecoParticle &DaughterTrackParticle){
  
  if(!SetVariables(PrimaryKaonTrackParticle, DaughterTrackParticle)) return -1.0;

  double score = reader->EvaluateMVA("BDT method");

  e.BDTScore = score;

  return score;
}


///////////////////////////////////////////////////////////////////////////////////////////////

#endif

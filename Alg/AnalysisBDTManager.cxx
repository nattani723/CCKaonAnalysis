#ifndef _AnalysisBDTManager_cxx_
#define _AnalysisBDTManager_cxx_

#include "AnalysisBDTManager.h"

///////////////////////////////////////////////////////////////////////////////////////////////

AnalysisBDTManager::AnalysisBDTManager() :
   Fitter()
{

   fMode = "Test";

}

///////////////////////////////////////////////////////////////////////////////////////////////

AnalysisBDTManager::AnalysisBDTManager(std::string Mode) :
   Fitter()
{

   fMode = Mode;
   if(fMode == "Train") SetupTrainingTrees();    

}

///////////////////////////////////////////////////////////////////////////////////////////////

AnalysisBDTManager::~AnalysisBDTManager(){

   if(fMode == "Train"){

      f_Trees->Close();

      delete f_Trees;

   }

   else if(fMode == "Test"){

      if(reader != nullptr)  delete reader;

   }

}


///////////////////////////////////////////////////////////////////////////////////////////////

void AnalysisBDTManager::WriteTrainingTrees(){

   std::cout << "Entries in Signal tree = " << t_Signal->GetEntries() << std::endl;
   std::cout << "Entries in Background tree = " << t_Background->GetEntries() << std::endl;

   f_Trees->cd();

   t_Signal->Write("SignalTree");
   t_Background->Write("BackgroundTree");

}   

///////////////////////////////////////////////////////////////////////////////////////////////

void AnalysisBDTManager::SetupTrainingTrees(){

   system("mkdir -p AnalysisMVA");

   f_Trees = TFile::Open( "AnalysisMVA/Trees.root" , "RECREATE" );
   t_Signal = new TTree("t_AnalysisMVA_Signal","Signal Pairings");
   t_Background = new TTree("t_AnalysisMVA_Background","Background Pairings");

   t_Signal->Branch("W",&v_w);
   t_Signal->Branch("Gap",&v_gap);
   t_Signal->Branch("BDT_Score",&v_bdt_score);
   t_Signal->Branch("Lambda_Angle",&v_lambda_angle);
   t_Signal->Branch("Lambda_V_Crossing_Dist",&v_lambda_V_crossing_dist);
   t_Signal->Branch("Weight",&v_weight);

   t_Background->Branch("W",&v_w);
   t_Background->Branch("Gap",&v_gap);
   t_Background->Branch("BDT_Score",&v_bdt_score);
   t_Background->Branch("Lambda_Angle",&v_lambda_angle);
   t_Background->Branch("Lambda_V_Crossing_Dist",&v_lambda_V_crossing_dist);
   t_Background->Branch("Weight",&v_weight);

}

///////////////////////////////////////////////////////////////////////////////////////////////

void AnalysisBDTManager::FillTree(const Event &e){

   // Check in the right running mode first
   assert(fMode == "Train");

   if(!SetVariables(e)) return;

    if(e.EventIsSignal) t_Signal->Fill();
   else t_Background->Fill();

}

///////////////////////////////////////////////////////////////////////////////////////////////

bool AnalysisBDTManager::SetVariables(const Event &e){

  //SecondaryVertex V = Fitter.MakeVertex(e.DecayProtonCandidate,e.DecayPionCandidate);
   SecondaryVertex V = Fitter.MakeVertex(e.DecayPionCandidate,e.DecayPionCandidate);

   // Reject if fit failed
   //if(!V.fitStatus) return false;

   TVector3 gap_vector = V.Vertex - e.RecoPrimaryVertex;

   //TLorentzVector lambda4momentum = ProtonPion4Momentum(e.DecayProtonCandidate,e.DecayPionCandidate);
   TLorentzVector lambda4momentum = ProtonPion4Momentum(e.DecayPionCandidate,e.DecayPionCandidate);
   TVector3 lambdadirection(lambda4momentum.X(),lambda4momentum.Y(),lambda4momentum.Z());

   lambdadirection *= 1.0/lambdadirection.Mag();

   //v_w = ProtonPionInvariantMass(e.DecayProtonCandidate,e.DecayPionCandidate);
   v_w = ProtonPionInvariantMass(e.DecayPionCandidate,e.DecayPionCandidate);
   v_gap = gap_vector.Mag();   
   v_bdt_score = e.SelectorBDTScore; 
   v_lambda_angle = (180/3.142)*lambdadirection.Angle(gap_vector);
   v_lambda_V_crossing_dist = V.CrossingDist;
   v_weight = e.Weight;

   return true;

}

///////////////////////////////////////////////////////////////////////////////////////////////

void AnalysisBDTManager::SetupAnalysisBDT(std::string WeightsDir){

   assert(fMode == "Test");

   if(WeightsDir == ""){ 
      std::cout << "No weights directory given, assuming default location" << std::endl;
      fWeightsDir = "/home/lar/cthorpe/uboone/HyperonSelection/TMVA/AnalysisMVA/v1/dataset/weights";
   }
   else fWeightsDir = WeightsDir;  

   TMVA::Tools::Instance();
   reader = new TMVA::Reader( "!Color:!Silent" );

   reader->AddVariable("W",&v_w);
   //reader->AddVariable("Gap",&v_gap);
   reader->AddVariable("BDT_Score",&v_bdt_score);
   reader->AddVariable("Lambda_Angle",&v_lambda_angle);
   //reader->AddVariable("Lambda_V_Crossing_Dist",&v_lambda_V_crossing_dist);

   std::map<std::string,int> Use;
   Use["BDT"] = 1;
   Use["BDTG"] = 1;

   TString prefix = "TMVAClassification";

   for (std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) {
      if (it->second) {
         TString methodName = TString(it->first) + TString(" method");
         TString weightfile = fWeightsDir + "/" + prefix + TString("_") + TString(it->first) + TString(".weights.xml");
         reader->BookMVA( methodName, weightfile );
      }
   }

}

///////////////////////////////////////////////////////////////////////////////////////////////

double AnalysisBDTManager::CalculateScore(Event &e){

   if(!SetVariables(e)) return -1.0;

   double score = reader->EvaluateMVA("BDT method");

   e.AnalysisBDTScore = score;

   return score;

}

///////////////////////////////////////////////////////////////////////////////////////////////

void AnalysisBDTManager::SetPull(double Pull){

   Fitter.SetPull(Pull);

}

#endif

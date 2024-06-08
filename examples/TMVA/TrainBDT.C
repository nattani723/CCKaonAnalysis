#include "TChain.h"
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TObjString.h"
#include "TSystem.h"
#include "TROOT.h"

#include "TMVA/Factory.h"
#include "TMVA/DataLoader.h"
#include "TMVA/Tools.h"
#include "TMVA/TMVAGui.h"

void TrainBDT(){

   //get input trees

   TFile *f_in = TFile::Open("MVA/Trees.root");

   //set output file
   TString outfileName( "TMVA.root" );
   TFile* outputFile = TFile::Open( outfileName, "RECREATE" );


   //grab the trees

   TTree* t_Signal;
   TTree* t_Background;

   f_in->GetObject("SignalTree",t_Signal);
   f_in->GetObject("BackgroundTree",t_Background);

   int nSignal = t_Signal->GetEntries();
   int nBackground = t_Background->GetEntries();

   std::cout << "Training Analyser BDT with " << nSignal << " signal and " << nBackground << " background" << std::endl;

   std::map<std::string,int> Use;
   Use["BDT"] = 1;

   TMVA::Tools::Instance();

   //setup factory
   TMVA::Factory *factory = new TMVA::Factory( "TMVAClassification", outputFile,
         "!V:!Silent:Color:DrawProgressBar:Transformations=I;D;P;G,D:AnalysisType=Classification" );


   TMVA::DataLoader *dataloader=new TMVA::DataLoader("dataset");

   dataloader->AddVariable("PrimaryTrack_Chi2_Kaon_3Plane", "Primary Track Chi2 Score under Kaon Hypothesis", 'F');
   dataloader->AddVariable("PrimaryTrack_Chi2_Proton_3Plane", "Primary Track Chi2 Score under Proton Hypothesis", 'F');
   dataloader->AddVariable("PrimaryTrack_Chi2_Muon_3Plane", "Primary Track Chi2 Score under Muon Hypothesis", 'F');
   dataloader->AddVariable("PrimaryTrack_Chi2_Pion_3Plane", "Primary Track Chi2 Score under Pion Hypothesis", 'F');
   dataloader->AddVariable("DaughterTrack_Chi2_Kaon_3Plane", "Daughter Track Chi2 Score under Kaon Hypothesis", 'F');
   dataloader->AddVariable("DaughterTrack_Chi2_Proton_3Plane", "Daughter Track Chi2 Score under Proton Hypothesis", 'F');
   dataloader->AddVariable("DaughterTrack_Chi2_Muon_3Plane", "Daughter Track Chi2 Score under Muon Hypothesis", 'F');
   dataloader->AddVariable("DaughterTrack_Chi2_Pion_3Plane", "Daughter Track Chi2 Score under Pion Hypothesis", 'F');
   /*
   dataloader->AddVariable("PrimaryTrack_Chi2_Kaon_Plane2", "Primary Track Chi2 Score under Kaon Hypothesis", 'F');
   dataloader->AddVariable("PrimaryTrack_Chi2_Proton_Plane2", "Primary Track Chi2 Score under Proton Hypothesis", 'F');
   dataloader->AddVariable("PrimaryTrack_Chi2_Muon_Plane2", "Primary Track Chi2 Score under Muon Hypothesis", 'F');
   dataloader->AddVariable("PrimaryTrack_Chi2_Pion_Plane2", "Primary Track Chi2 Score under Pion Hypothesis", 'F');
   dataloader->AddVariable("DaughterTrack_Chi2_Kaon_Plane2", "Daughter Track Chi2 Score under Kaon Hypothesis", 'F');
   dataloader->AddVariable("DaughterTrack_Chi2_Proton_Plane2", "Daughter Track Chi2 Score under Proton Hypothesis", 'F');
   dataloader->AddVariable("DaughterTrack_Chi2_Muon_Plane2", "Daughter Track Chi2 Score under Muon Hypothesis", 'F');
   dataloader->AddVariable("DaughterTrack_Chi2_Pion_Plane2", "Daughter Track Chi2 Score under Pion Hypothesis", 'F');
   */
   
   dataloader->AddVariable("PrimaryTrack_LLR_PID","Primary Track LLR PID Score",'F');
   dataloader->AddVariable("PrimaryTrack_LLR_PID_Kaon","Primary Track Kaon LLR PID Score",'F');
   dataloader->AddVariable("DaughterTrack_LLR_PID","Daughter Track LLR PID Score",'F');
   dataloader->AddVariable("DaughterTrack_LLR_PID_Kaon","Daughter Track Kaon LLR PID Score",'F');
   dataloader->AddVariable("DaughterTrackLength","Daughter Track Length",'F');
   /*
   dataloader->AddVariable("PrimaryTrack_Bragg_PID_Kaon","Primary Track Bragg PID Kaon",'F');
   dataloader->AddVariable("DaughterTrack_Bragg_PID_Kaon","Daughter Track Bragg PID Kaon",'F');
   dataloader->AddVariable("PrimaryTrack_dEdX","Primary Track Mean dEdX",'F');
   dataloader->AddVariable("DaughterTrack_dEdX","Daughter Track Mean dEdX",'F');
   */

   dataloader->AddSignalTree( t_Signal , 1.0 );
   dataloader->AddBackgroundTree( t_Background , 1.0 );

   TCut mycuts = "";
   TCut mycutb = "";

   TString Setup = "nTrain_Signal=" + std::to_string(nSignal/2) + ":nTrain_Background=" + std::to_string(nBackground/2) + ":SplitMode=Random:NormMode=NumEvents:!V";
   dataloader->PrepareTrainingAndTestTree(mycuts,mycutb,Setup);


   if(Use["BDT"]) factory->BookMethod( dataloader, TMVA::Types::kBDT, "BDT", "!H:!V:NTrees=300:MinNodeSize=4%:MaxDepth=10:BoostType=AdaBoost:AdaBoostBeta=0.65:UseBaggedBoost:BaggedSampleFraction=0.16:SeparationType=CrossEntropy:nCuts=10:DoBoostMonitor=true:UseRandomisedTrees=True:UseNvars=13");
   //"!H:!V:NTrees=850:MinNodeSize=2.5%:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20" );

   factory->TrainAllMethods();
   factory->TestAllMethods();
   factory->EvaluateAllMethods();

   outputFile->Close();

   std::cout << "==> Wrote root file: " << outputFile->GetName() << std::endl;
   std::cout << "==> TMVAClassification is done!" << std::endl;


   delete factory;
   delete dataloader;


   //launch GUI
   if (!gROOT->IsBatch()) TMVA::TMVAGui( outfileName );


}

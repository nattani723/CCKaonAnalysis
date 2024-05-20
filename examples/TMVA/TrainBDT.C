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

void TrainAnalysisBDT(){

   TFile *f_Signal = TFile::Open("AnalysisMVA/Trees_Signal.root");
   TFile *f_Background = TFile::Open("AnalysisMVA/Trees_Background.root");

   //set output file
   TString outfileName( "TMVA.root" );
   TFile* outputFile = TFile::Open( outfileName, "RECREATE" );

   //grab the trees

   TTree* t_Signal;
   TTree* t_Background;

   f_Signal->GetObject("SignalTree",t_Signal);
   f_Background->GetObject("BackgroundTree",t_Background);

   int nSignal = t_Signal->GetEntries();
   int nBackground = t_Background->GetEntries();

   std::cout << "Training Analyser BDT with " << nSignal << " signal and " << nBackground << " background" << std::endl;

   std::map<std::string,int> Use;
   Use["BDT"] = 1;
   Use["BDTG"] = 1;
   Use["MLPBNN"] = 1;

   TMVA::Tools::Instance();

   //setup factory
   TMVA::Factory *factory = new TMVA::Factory( "TMVAClassification", outputFile,
         "!V:!Silent:Color:DrawProgressBar:Transformations=I;D;P;G,D:AnalysisType=Classification" );

   TMVA::DataLoader *dataloader=new TMVA::DataLoader("dataset");

   dataloader->AddVariable("W","W (Reco'd)","GeV",'F');
   dataloader->AddVariable("BDT_Score","BDT Score",' ');
   dataloader->AddVariable("Lambda_Angle","Lambda Angle",' ');

   dataloader->SetBackgroundWeightExpression( "Weight" );

   dataloader->AddSignalTree( t_Signal , 1.0 );
   dataloader->AddBackgroundTree( t_Background , 1.0 );

   TCut mycuts = "";
   TCut mycutb = "";

   TString Setup = "nTrain_Signal=" + std::to_string(nSignal/2) + ":nTrain_Background=" + std::to_string(nBackground/2) + ":SplitMode=Random:NormMode=NumEvents:!V";

   dataloader->PrepareTrainingAndTestTree(mycuts,mycutb,Setup);

   if(Use["BDT"]) factory->BookMethod( dataloader, TMVA::Types::kBDT, "BDT","!H:!V:NTrees=1000:MinNodeSize=2.5%:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20" );
   if(Use["BDTG"]) factory->BookMethod( dataloader, TMVA::Types::kBDT, "BDTG","!H:!V:NTrees=1000:MinNodeSize=2.5%:BoostType=Grad:Shrinkage=0.10:UseBaggedBoost:BaggedSampleFraction=0.5:nCuts=20:MaxDepth=2" );
   if (Use["MLPBNN"]) factory->BookMethod( dataloader, TMVA::Types::kMLP, "MLPBNN", "H:!V:NeuronType=tanh:VarTransform=N:NCycles=60:HiddenLayers=N+5:TestRate=5:TrainingMethod=BFGS:UseRegulator" ); // BFGS training with bayesian regulators

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




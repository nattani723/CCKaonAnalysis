
#include <cstdlib>
#include <iostream>
#include <map>
#include <string>

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

int TMVAClassification_template_addspec( TString myMethodList = "" )
{

  int nthreads = 6;
  ROOT::EnableImplicitMT(nthreads);

   //---------------------------------------------------------------
   // This loads the library
   TMVA::Tools::Instance();

   // Default MVA methods to be trained + tested
   std::map<std::string,int> Use;

   // Cut optimisation
   Use["Cuts"]            = 1;
   Use["CutsD"]           = 1;
   Use["CutsPCA"]         = 0;
   Use["CutsGA"]          = 0;
   Use["CutsSA"]          = 0;
   //
   // 1-dimensional likelihood ("naive Bayes estimator")
   Use["Likelihood"]      = 1;
   Use["LikelihoodD"]     = 0; // the "D" extension indicates decorrelated input variables (see option strings)
   Use["LikelihoodPCA"]   = 1; // the "PCA" extension indicates PCA-transformed input variables (see option strings)
   Use["LikelihoodKDE"]   = 0;
   Use["LikelihoodMIX"]   = 0;
   //
   // Mutidimensional likelihood and Nearest-Neighbour methods
   Use["PDERS"]           = 1;
   Use["PDERSD"]          = 0;
   Use["PDERSPCA"]        = 0;
   Use["PDEFoam"]         = 1;
   Use["PDEFoamBoost"]    = 0; // uses generalised MVA method boosting
   Use["KNN"]             = 1; // k-nearest neighbour method
   //
   // Linear Discriminant Analysis
   Use["LD"]              = 1; // Linear Discriminant identical to Fisher
   Use["Fisher"]          = 0;
   Use["FisherG"]         = 0;
   Use["BoostedFisher"]   = 0; // uses generalised MVA method boosting
   Use["HMatrix"]         = 0;
   //
   // Function Discriminant analysis
   Use["FDA_GA"]          = 1; // minimisation of user-defined function using Genetics Algorithm
   Use["FDA_SA"]          = 0;
   Use["FDA_MC"]          = 0;
   Use["FDA_MT"]          = 0;
   Use["FDA_GAMT"]        = 0;
   Use["FDA_MCMT"]        = 0;
   //
   // Neural Networks (all are feed-forward Multilayer Perceptrons)
   Use["MLP"]             = 0; // Recommended ANN
   Use["MLPBFGS"]         = 0; // Recommended ANN with optional training method
   Use["MLPBNN"]          = 1; // Recommended ANN with BFGS training method and bayesian regulator
   Use["CFMlpANN"]        = 0; // Depreciated ANN from ALEPH
   Use["TMlpANN"]         = 0; // ROOT's own ANN   
#ifdef R__HAS_TMVAGPU
   Use["DNN_GPU"]         = 1; // CUDA-accelerated DNN training.
#else
   Use["DNN_GPU"]         = 0;
#endif

#ifdef R__HAS_TMVACPU
   Use["DNN_CPU"]         = 1; // Multi-core accelerated DNN.
#else
   Use["DNN_CPU"]         = 0;
#endif
   //
   // Support Vector Machine
   Use["SVM"]             = 1;
   //
   // Boosted Decision Trees
   Use["BDT"]             = 1; // uses Adaptive Boost
   Use["BDTG"]            = 0; // uses Gradient Boost
   Use["BDTB"]            = 0; // uses Bagging
   Use["BDTD"]            = 0; // decorrelation + Adaptive Boost
   Use["BDTF"]            = 0; // allow usage of fisher discriminant for node splitting
   //
   // Friedman's RuleFit method, ie, an optimised series of cuts ("rules")
   Use["RuleFit"]         = 1;
   // ---------------------------------------------------------------
   
   std::cout << std::endl;
   std::cout << "==> Start TMVAClassification" << std::endl;

   // Select methods (don't look at this code - not of interest)
   if (myMethodList != "") {
      for (std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) it->second = 0;

      std::vector<TString> mlist = TMVA::gTools().SplitString( myMethodList, ',' );
      for (UInt_t i=0; i<mlist.size(); i++) {
         std::string regMethod(mlist[i]);

         if (Use.find(regMethod) == Use.end()) {
            std::cout << "Method \"" << regMethod << "\" not known in TMVA under this name. Choose among the following:" << std::endl;
            for (std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) std::cout << it->first << " ";
            std::cout << std::endl;
            return 1;
         }
         Use[regMethod] = 1;
      }
   }
   
   // --------------------------------------------------------------------------------------------------

   (TMVA::gConfig().GetVariablePlotting()).fNbinsMVAoutput = 50;
   (TMVA::gConfig().GetVariablePlotting()).fNbins1D = 100;
   // Here the preparation phase begins

   // Read training and test data
   // (it is also possible to use ASCII format as input -> see TMVA Users Guide)
   TFile *input(0);

   TString fname = "/exp/uboone/data/users/taniuchi/taniuchi/pandora_alg/ana/cck_numi_train_34.root";

      
   //TString fname = "/uboone/app/users/taniuchi/KaonAna/KaonAnlysis/Ana/track_tuple/5Dec.root";
   //TString fname = "/uboone/data/users/taniuchi/pandora_alg/ana/cck_numi_train_34.root";
   //TString fname = "/uboone/app/users/taniuchi/KaonAna/KaonAnlysis/Ana/track_tuple/15Aug_numi_run1_fhc.root";
   //TString fname = "/uboone/app/users/taniuchi/KaonAna/KaonAnlysis/Ana/track_tuple/root_files/nuccfilter_numi_cck_tracktuple.root";
   //TString fname = "/uboone/app/users/taniuchi/KaonAna/KaonAnlysis/Ana/track_tuple/root_files/nuccfilter_numi_mc_w_cck_tracktuple.root";
   //TString fname = "/uboone/app/users/taniuchi/KaonAna/KaonAnlysis/Ana/track_tuple/root_files/mip_numi_mc_w_cck_tracktuple.root";
   //TString fname = "/uboone/data/users/taniuchi/bnb_kaon/root_files/cck_sample/CCKaonAnalyzer_cckplus.root";
   
   TString ver = "notrklength_BDT2_w_5Dec_sample_all9_replot_test"; // tag of the training
   //TString ver = "nuccfilter_3pl_wo_MIP_wo_nhits_test"; // tag of the training
  
   
   input = TFile::Open( fname ); // check if file in local directory exists
   if (!input) {
      std::cout << "ERROR: could not open data file" << std::endl;
      exit(1);
   }
   std::cout << "--- TMVAClassification       : Using input file: " << input->GetName() << std::endl;


   TTree *inputTree = (TTree*)input->Get("CCKaonTracks");
   //TString outfileName( "TMVA.root" );
   TString outfileName( "TMVA_" + ver + ".root" );
   TFile* outputFile = TFile::Open( outfileName, "RECREATE" );

   //TCut signalCut = "reco_track_true_pdg==321";
   //TCut signalCut = "(true_nu_pdg==14 && true_nu_ccnc==0 && reco_track_true_pdg==321 && (reco_track_daughter_true_pdg==-13 || reco_track_daughter_true_pdg==211))"; // definition of your signal
   TCut signalCut = "(reco_track_true_pdg==321 && (reco_track_daughter_true_pdg==-13 || reco_track_daughter_true_pdg==211))"; // definition of your signal
   //TCut signalCut = "(reco_track_true_pdg==321 && (reco_track_daughter_true_pdg==-13 || reco_track_daughter_true_pdg==211)) && reco_track_vtx_inTPC==1 && reco_track_end_inTPC==1 && reco_track_daughter_vtx_inTPC==1 && reco_track_daughter_end_inTPC==1";
   TCut backgrCut = !signalCut;

   
   TMVA::Factory *factory = new TMVA::Factory( "TMVAClassification", outputFile,
                                               "!V:!Silent:Color:DrawProgressBar:AnalysisType=Classification" );                                               	
   //TMVA::Factory *factory = new TMVA::Factory( "TMVAClassification", outputFile,
   //                                            "!V:!Silent:Color:DrawProgressBar:Transformations=I;D;P;G,D:AnalysisType=Classification" );
   
   TMVA::DataLoader *dataloader=new TMVA::DataLoader("dataset_" + ver );
   
   dataloader->SetInputTrees( inputTree, signalCut, backgrCut );
   //dataloader->PrepareTrainingAndTestTree(signalCut, backgrCut, "SplitMode=Random");



   //////// variables to train the model

   dataloader->AddSpectator("reco_track_true_pdg");
   dataloader->AddSpectator("reco_track_daughter_true_pdg");
   dataloader->AddSpectator("true_nu_energy");
   dataloader->AddSpectator("true_nu_ccnc");
   dataloader->AddSpectator("true_nu_mode");
   dataloader->AddSpectator("true_lepton_pdg");

   dataloader->AddSpectator("true_nkaons");
   dataloader->AddSpectator("true_kaon_length");
   dataloader->AddSpectator("true_kaon_p");
   dataloader->AddSpectator("true_kaon_ke");
   dataloader->AddSpectator("true_kaon_theta");
   dataloader->AddSpectator("true_kaon_costheta");
   dataloader->AddSpectator("true_kaon_phi");

   dataloader->AddSpectator("reco_ccmu_true_pdg");


   dataloader->AddSpectator("true_nu_pdg");
   dataloader->AddSpectator("true_nu_vtx_inCCInclusiveTPC");
   dataloader->AddSpectator("true_kaon_end_inCCInclusiveTPC");
   dataloader->AddSpectator("true_kaon_daughter_end_in5cmTPC");

   dataloader->AddSpectator("run");
   dataloader->AddSpectator("subrun");
   dataloader->AddSpectator("eventnum");
   
   //dataloader->AddSpectator("reco_track_kin0");
   //dataloader->AddSpectator("reco_track_kin1");
   //dataloader->AddSpectator("reco_track_kin2");
   dataloader->AddSpectator("reco_track_theta");
   dataloader->AddSpectator("reco_track_phi");
   dataloader->AddSpectator("true_kaon_daughter_length");

   dataloader->AddSpectator("reco_track_chi2ka_pl2");
   dataloader->AddSpectator("reco_track_chi2pr_pl2");
   dataloader->AddSpectator("reco_track_chi2pi_pl2");
   dataloader->AddSpectator("reco_track_chi2mu_pl2");

   dataloader->AddSpectator("reco_track_daughter_chi2ka_pl2");
   dataloader->AddSpectator("reco_track_daughter_chi2pr_pl2");
   dataloader->AddSpectator("reco_track_daughter_chi2pi_pl2");
   dataloader->AddSpectator("reco_track_daughter_chi2mu_pl2"); 

   dataloader->AddSpectator("true_kaon_end_process");
 
   /*
   dataloader->AddSpectator("reco_nu_cc_filter");
   dataloader->AddSpectator("reco_nu_vtx_inCCInclusiveTPC");
   dataloader->AddSpectator("reco_track_end_inCCInclusiveTPC");
   dataloader->AddSpectator("reco_track_ndaughters");
   dataloader->AddSpectator("reco_track_daughter_vtx_in5cmTPC");
   dataloader->AddSpectator("reco_track_daughter_end_in5cmTPC");
   dataloader->AddSpectator("reco_track_end_inCCInclusiveTPC");
   */

   /*
   dataloader->AddVariable("reco_track_chi2ka_pl0");
   dataloader->AddVariable("reco_track_chi2pr_pl0");
   dataloader->AddVariable("reco_track_chi2pi_pl0");
   dataloader->AddVariable("reco_track_chi2mu_pl0");
   
   dataloader->AddVariable("reco_track_chi2ka_pl1");
   dataloader->AddVariable("reco_track_chi2pr_pl1");
   dataloader->AddVariable("reco_track_chi2pi_pl1");
   dataloader->AddVariable("reco_track_chi2mu_pl1");
   
   dataloader->AddVariable("reco_track_chi2ka_pl2");
   dataloader->AddVariable("reco_track_chi2pr_pl2");
   dataloader->AddVariable("reco_track_chi2pi_pl2");
   dataloader->AddVariable("reco_track_chi2mu_pl2");

        
   dataloader->AddVariable("reco_track_daughter_chi2ka_pl0");
   dataloader->AddVariable("reco_track_daughter_chi2pr_pl0");
   dataloader->AddVariable("reco_track_daughter_chi2pi_pl0");
   dataloader->AddVariable("reco_track_daughter_chi2mu_pl0"); 
   
   dataloader->AddVariable("reco_track_daughter_chi2ka_pl1");
   dataloader->AddVariable("reco_track_daughter_chi2pr_pl1");
   dataloader->AddVariable("reco_track_daughter_chi2pi_pl1");
   dataloader->AddVariable("reco_track_daughter_chi2mu_pl1"); 
   
   dataloader->AddVariable("reco_track_daughter_chi2ka_pl2");
   dataloader->AddVariable("reco_track_daughter_chi2pr_pl2");
   dataloader->AddVariable("reco_track_daughter_chi2pi_pl2");
   dataloader->AddVariable("reco_track_daughter_chi2mu_pl2"); 
  */ 
   

   /*
   dataloader->AddVariable("reco_track_chi2ka_pl2");
   dataloader->AddVariable("reco_track_chi2pr_pl2");
   dataloader->AddVariable("reco_track_chi2pi_pl2");
   dataloader->AddVariable("reco_track_chi2mu_pl2");

   dataloader->AddVariable("reco_track_daughter_chi2ka_pl2");
   dataloader->AddVariable("reco_track_daughter_chi2pr_pl2");
   dataloader->AddVariable("reco_track_daughter_chi2pi_pl2");
   dataloader->AddVariable("reco_track_daughter_chi2mu_pl2"); 
   */   
   
  
   dataloader->AddVariable("reco_track_chi2ka_3pl");
   dataloader->AddVariable("reco_track_chi2pr_3pl");
   dataloader->AddVariable("reco_track_chi2pi_3pl");
   dataloader->AddVariable("reco_track_chi2mu_3pl");

   dataloader->AddVariable("reco_track_daughter_chi2ka_3pl");
   dataloader->AddVariable("reco_track_daughter_chi2pr_3pl");
   dataloader->AddVariable("reco_track_daughter_chi2pi_3pl");
   dataloader->AddVariable("reco_track_daughter_chi2mu_3pl");


   dataloader->AddVariable("reco_track_llrpid_3pl");
   dataloader->AddVariable("reco_track_llrpid_k_3pl");
   dataloader->AddVariable("reco_track_daughter_llrpid_3pl");
   dataloader->AddVariable("reco_track_daughter_llrpid_k_3pl");
   
   
   //dataloader->AddVariable("reco_track_distance");
   //dataloader->AddVariable("reco_track_vtx_distance");

   //dataloader->AddVariable("reco_track_theta");
   //dataloader->AddVariable("reco_track_phi");
   
   dataloader->AddVariable("reco_track_daughter_length");

   
   /*
   dataloader->AddVariable("reco_track_length");
   dataloader->AddVariable("reco_track_daughter_vtx_distance");
   dataloader->AddVariable("reco_track_daughter_distance");
   */

   //dataloader->AddVariable("reco_track_daughter_theta");
   //dataloader->AddVariable("reco_track_daughter_phi");
 
  //dataloader->AddVariable("reco_track_daughter_theta");//
   //dataloader->AddVariable("reco_track_daughter_phi");//

   
   //dataloader->AddVariable("reco_track_log_bragg_peak");
   /*
   dataloader->AddVariable("reco_track_Bragg_fwd_ka_pl0");
   dataloader->AddVariable("reco_track_Bragg_fwd_pr_pl0");
   dataloader->AddVariable("reco_track_Bragg_fwd_pi_pl0");
   dataloader->AddVariable("reco_track_Bragg_fwd_mu_pl0");
   dataloader->AddVariable("reco_track_Bragg_fwd_ka_pl1");
   dataloader->AddVariable("reco_track_Bragg_fwd_pr_pl1");
   dataloader->AddVariable("reco_track_Bragg_fwd_pi_pl1");
   dataloader->AddVariable("reco_track_Bragg_fwd_mu_pl1");
   dataloader->AddVariable("reco_track_Bragg_fwd_ka_pl2");
   dataloader->AddVariable("reco_track_Bragg_fwd_pr_pl2");
   dataloader->AddVariable("reco_track_Bragg_fwd_pi_pl2");
   dataloader->AddVariable("reco_track_Bragg_fwd_mu_pl2");
   */
   /*
   dataloader->AddVariable("reco_track_MIP_pl0"); 
   dataloader->AddVariable("reco_track_MIP_pl1"); 
   dataloader->AddVariable("reco_track_MIP_pl2"); 
   */
   /*
   dataloader->AddVariable("reco_track_nhits0");
   dataloader->AddVariable("reco_track_nhits1");
   dataloader->AddVariable("reco_track_nhits2");
   */

   //dataloader->PrepareTrainingAndTestTree("","nTrain_Signal=0:nTest_Signal=0:nTrain_Background=0:nTest_Background=0");
   dataloader->PrepareTrainingAndTestTree("","nTrain_Signal=0:nTest_Signal=0:nTrain_Background=0:nTest_Background=0:SplitMode=Random");

   //  dataloader->PrepareTrainingAndTestTree( "",
   //                                       "nTrain_Signal=1000:nTrain_Background=1000:SplitMode=Random:NormMode=NumEvents:!V" );


   // ### Book MVA methods
   //
   // Please lookup the various method configuration options in the corresponding cxx files, eg:
   // src/MethoCuts.cxx, etc, or here: http://tmva.sourceforge.net/optionRef.html
   // it is possible to preset ranges in the option string in which the cut optimisation should be done:
   // "...:CutRangeMin[2]=-1:CutRangeMax[2]=1"...", where [2] is the third input variable

   // Cut optimisation
   if (Use["Cuts"])
      factory->BookMethod( dataloader, TMVA::Types::kCuts, "Cuts",
                           "!H:!V:FitMethod=MC:EffSel:SampleSize=100000:VarProp=FSmart" );
   
   if (Use["CutsD"])
      factory->BookMethod( dataloader, TMVA::Types::kCuts, "CutsD",
                           "!H:!V:FitMethod=MC:EffSel:SampleSize=200000:VarProp=FSmart:VarTransform=Decorrelate" );

   if (Use["CutsPCA"])
      factory->BookMethod( dataloader, TMVA::Types::kCuts, "CutsPCA",
                           "!H:!V:FitMethod=MC:EffSel:SampleSize=200000:VarProp=FSmart:VarTransform=PCA" );

   if (Use["CutsGA"])
      factory->BookMethod( dataloader, TMVA::Types::kCuts, "CutsGA",
                           "H:!V:FitMethod=GA:CutRangeMin[0]=-10:CutRangeMax[0]=10:VarProp[1]=FMax:EffSel:Steps=30:Cycles=3:PopSize=400:SC_steps=10:SC_rate=5:SC_factor=0.95" );

   if (Use["CutsSA"])
      factory->BookMethod( dataloader, TMVA::Types::kCuts, "CutsSA",
                           "!H:!V:FitMethod=SA:EffSel:MaxCalls=150000:KernelTemp=IncAdaptive:InitialTemp=1e+6:MinTemp=1e-6:Eps=1e-10:UseDefaultScale" );

   // Likelihood ("naive Bayes estimator")
   if (Use["Likelihood"])
      factory->BookMethod( dataloader, TMVA::Types::kLikelihood, "Likelihood",
                           "H:!V:TransformOutput:PDFInterpol=Spline2:NSmoothSig[0]=20:NSmoothBkg[0]=20:NSmoothBkg[1]=10:NSmooth=1:NAvEvtPerBin=50" );

   // Decorrelated likelihood
   if (Use["LikelihoodD"])
      factory->BookMethod( dataloader, TMVA::Types::kLikelihood, "LikelihoodD",
                           "H:!V:TransformOutput:PDFInterpol=Spline2:NSmoothSig[0]=20:NSmoothBkg[0]=20:NSmooth=5:NAvEvtPerBin=50:VarTransform=Decorrelate" );

   // PCA-transformed likelihood
   if (Use["LikelihoodPCA"])
      factory->BookMethod( dataloader, TMVA::Types::kLikelihood, "LikelihoodPCA",
                           "!H:!V:!TransformOutput:PDFInterpol=Spline2:NSmoothSig[0]=20:NSmoothBkg[0]=20:NSmooth=5:NAvEvtPerBin=50:VarTransform=PCA" );

   // Use a kernel density estimator to approximate the PDFs
   if (Use["LikelihoodKDE"])
      factory->BookMethod( dataloader, TMVA::Types::kLikelihood, "LikelihoodKDE",
                           "!H:!V:!TransformOutput:PDFInterpol=KDE:KDEtype=Gauss:KDEiter=Adaptive:KDEFineFactor=0.2:KDEborder=None:Nbins=300" );

   // Use a variable-dependent mix of splines and kernel density estimator
   if (Use["LikelihoodMIX"])
      factory->BookMethod( dataloader, TMVA::Types::kLikelihood, "LikelihoodMIX",
                           "!H:!V:!TransformOutput:PDFInterpolSig[0]=KDE:PDFInterpolBkg[0]=KDE:PDFInterpolSig[1]=KDE:PDFInterpolBkg[1]=KDE:PDFInterpolSig[2]=KDE:PDFInterpolBkg[2]=KDE:PDFInterpolSig[3]=KDE:PDFInterpolBkg[3]=KDE:KDEtype=Gauss:KDEiter=Nonadaptive:KDEborder=None:NAvEvtPerBin=200" );

   // Test the multi-dimensional probability density estimator
   // here are the options strings for the MinMax and RMS methods, respectively:
   //
   //      "!H:!V:VolumeRangeMode=MinMax:DeltaFrac=0.2:KernelEstimator=Gauss:GaussSigma=0.3" );
   //      "!H:!V:VolumeRangeMode=RMS:DeltaFrac=3:KernelEstimator=Gauss:GaussSigma=0.3" );
   if (Use["PDERS"])
      factory->BookMethod( dataloader, TMVA::Types::kPDERS, "PDERS",
                           "!H:!V:NormTree=T:VolumeRangeMode=Adaptive:KernelEstimator=Gauss:GaussSigma=0.3:NEventsMin=400:NEventsMax=40000" );

   if (Use["PDERSD"])
      factory->BookMethod( dataloader, TMVA::Types::kPDERS, "PDERSD",
                           "!H:!V:VolumeRangeMode=Adaptive:KernelEstimator=Gauss:GaussSigma=0.5:NEventsMin=800:NEventsMax=40000:VarTransform=Decorrelate" );

   if (Use["PDERSPCA"])
      factory->BookMethod( dataloader, TMVA::Types::kPDERS, "PDERSPCA",
                           "!H:!V:VolumeRangeMode=Adaptive:KernelEstimator=Gauss:GaussSigma=0.3:NEventsMin=400:NEventsMax=40000:VarTransform=PCA" );

   // Multi-dimensional likelihood estimator using self-adapting phase-space binning
   if (Use["PDEFoam"])
      factory->BookMethod( dataloader, TMVA::Types::kPDEFoam, "PDEFoam",
                           "!H:!V:SigBgSeparate=F:TailCut=0.001:VolFrac=0.0666:nActiveCells=500:nSampl=2000:nBin=5:Nmin=100:Kernel=None:Compress=T" );

   if (Use["PDEFoamBoost"])
      factory->BookMethod( dataloader, TMVA::Types::kPDEFoam, "PDEFoamBoost",
                           "!H:!V:Boost_Num=30:Boost_Transform=linear:SigBgSeparate=F:MaxDepth=4:UseYesNoCell=T:DTLogic=MisClassificationError:FillFoamWithOrigWeights=F:TailCut=0:nActiveCells=500:nBin=20:Nmin=400:Kernel=None:Compress=T" );

   // K-Nearest Neighbour classifier (KNN)
   if (Use["KNN"])
      factory->BookMethod( dataloader, TMVA::Types::kKNN, "KNN",
                           "H:nkNN=100:ScaleFrac=0.8:SigmaFact=1.0:Kernel=Gaus:UseKernel=F:UseWeight=T:!Trim" );

   // H-Matrix (chi2-squared) method
   if (Use["HMatrix"])
      factory->BookMethod( dataloader, TMVA::Types::kHMatrix, "HMatrix", "!H:!V:VarTransform=None" );

   // Linear discriminant (same as Fisher discriminant)
   //if (Use["LD"])
   //   factory->BookMethod( dataloader, TMVA::Types::kLD, "LD", "H:!V:VarTransform=None:CreateMVAPdfs:PDFInterpolMVAPdf=Spline2:NbinsMVAPdf=50:NsmoothMVAPdf=10" );

   // Fisher discriminant (same as LD)
   if (Use["Fisher"])
      factory->BookMethod( dataloader, TMVA::Types::kFisher, "Fisher", "H:!V:Fisher:VarTransform=None:CreateMVAPdfs:PDFInterpolMVAPdf=Spline2:NbinsMVAPdf=50:NsmoothMVAPdf=10" );

   // Fisher with Gauss-transformed input variables
   if (Use["FisherG"])
      factory->BookMethod( dataloader, TMVA::Types::kFisher, "FisherG", "H:!V:VarTransform=Gauss" );

   // Composite classifier: ensemble (tree) of boosted Fisher classifiers
   if (Use["BoostedFisher"])
      factory->BookMethod( dataloader, TMVA::Types::kFisher, "BoostedFisher",
                           "H:!V:Boost_Num=20:Boost_Transform=log:Boost_Type=AdaBoost:Boost_AdaBoostBeta=0.2:!Boost_DetailedMonitoring" );

   // Function discrimination analysis (FDA) -- test of various fitters - the recommended one is Minuit (or GA or SA)
   if (Use["FDA_MC"])
      factory->BookMethod( dataloader, TMVA::Types::kFDA, "FDA_MC",
                           "H:!V:Formula=(0)+(1)*x0+(2)*x1+(3)*x2+(4)*x3:ParRanges=(-1,1);(-10,10);(-10,10);(-10,10);(-10,10):FitMethod=MC:SampleSize=100000:Sigma=0.1" );

   if (Use["FDA_GA"]) // can also use Simulated Annealing (SA) algorithm (see Cuts_SA options])
      factory->BookMethod( dataloader, TMVA::Types::kFDA, "FDA_GA",
                           "H:!V:Formula=(0)+(1)*x0+(2)*x1+(3)*x2+(4)*x3:ParRanges=(-1,1);(-10,10);(-10,10);(-10,10);(-10,10):FitMethod=GA:PopSize=100:Cycles=2:Steps=5:Trim=True:SaveBestGen=1" );

   if (Use["FDA_SA"]) // can also use Simulated Annealing (SA) algorithm (see Cuts_SA options])
      factory->BookMethod( dataloader, TMVA::Types::kFDA, "FDA_SA",
                           "H:!V:Formula=(0)+(1)*x0+(2)*x1+(3)*x2+(4)*x3:ParRanges=(-1,1);(-10,10);(-10,10);(-10,10);(-10,10):FitMethod=SA:MaxCalls=15000:KernelTemp=IncAdaptive:InitialTemp=1e+6:MinTemp=1e-6:Eps=1e-10:UseDefaultScale" );

   if (Use["FDA_MT"])
      factory->BookMethod( dataloader, TMVA::Types::kFDA, "FDA_MT",
                           "H:!V:Formula=(0)+(1)*x0+(2)*x1+(3)*x2+(4)*x3:ParRanges=(-1,1);(-10,10);(-10,10);(-10,10);(-10,10):FitMethod=MINUIT:ErrorLevel=1:PrintLevel=-1:FitStrategy=2:UseImprove:UseMinos:SetBatch" );

   if (Use["FDA_GAMT"])
      factory->BookMethod( dataloader, TMVA::Types::kFDA, "FDA_GAMT",
                           "H:!V:Formula=(0)+(1)*x0+(2)*x1+(3)*x2+(4)*x3:ParRanges=(-1,1);(-10,10);(-10,10);(-10,10);(-10,10):FitMethod=GA:Converger=MINUIT:ErrorLevel=1:PrintLevel=-1:FitStrategy=0:!UseImprove:!UseMinos:SetBatch:Cycles=1:PopSize=5:Steps=5:Trim" );

   if (Use["FDA_MCMT"])
      factory->BookMethod( dataloader, TMVA::Types::kFDA, "FDA_MCMT",
                           "H:!V:Formula=(0)+(1)*x0+(2)*x1+(3)*x2+(4)*x3:ParRanges=(-1,1);(-10,10);(-10,10);(-10,10);(-10,10):FitMethod=MC:Converger=MINUIT:ErrorLevel=1:PrintLevel=-1:FitStrategy=0:!UseImprove:!UseMinos:SetBatch:SampleSize=20" );

   // TMVA ANN: MLP (recommended ANN) -- all ANNs in TMVA are Multilayer Perceptrons
   if (Use["MLP"])
      factory->BookMethod( dataloader, TMVA::Types::kMLP, "MLP", "H:!V:NeuronType=tanh:VarTransform=N:NCycles=500:HiddenLayers=N+15:TestRate=6:!UseRegulator:LearningRate=0.02:TrainingMethod=BP" );

   if (Use["MLPBFGS"])
      factory->BookMethod( dataloader, TMVA::Types::kMLP, "MLPBFGS", "H:!V:NeuronType=tanh:VarTransform=N:NCycles=300:HiddenLayers=N+1,N:TestRate=5:TrainingMethod=BFGS:!UseRegulator" );

   if (Use["MLPBNN"])
      factory->BookMethod( dataloader, TMVA::Types::kMLP, "MLPBNN", "H:!V:NeuronType=tanh:VarTransform=N:NCycles=60:HiddenLayers=N+5:TestRate=5:TrainingMethod=BFGS:UseRegulator" ); // BFGS training with bayesian regulators

   // Multi-architecture DNN implementation.
   if (Use["DNN_CPU"] or Use["DNN_GPU"]) {
      // General layout.
      TString layoutString ("Layout=TANH|128,TANH|128,TANH|128,LINEAR");

      // Training strategies.
      TString training0("LearningRate=1e-2,Momentum=0.9,Repetitions=1,"
                        "ConvergenceSteps=30,BatchSize=256,TestRepetitions=10,"
                        "WeightDecay=1e-4,Regularization=None,"
                        "DropConfig=0.0+0.5+0.5+0.5, Multithreading=True");
      TString training1("LearningRate=1e-2,Momentum=0.9,Repetitions=1,"
                        "ConvergenceSteps=20,BatchSize=256,TestRepetitions=10,"
                        "WeightDecay=1e-4,Regularization=L2,"
                        "DropConfig=0.0+0.0+0.0+0.0, Multithreading=True");
      TString training2("LearningRate=1e-3,Momentum=0.0,Repetitions=1,"
                        "ConvergenceSteps=20,BatchSize=256,TestRepetitions=10,"
                        "WeightDecay=1e-4,Regularization=L2,"
                        "DropConfig=0.0+0.0+0.0+0.0, Multithreading=True");
      TString trainingStrategyString ("TrainingStrategy=");
      trainingStrategyString += training0 + "|" + training1 + "|" + training2;

      // General Options.
      TString dnnOptions ("!H:V:ErrorStrategy=CROSSENTROPY:VarTransform=N:"
                          "WeightInitialization=XAVIERUNIFORM");
      dnnOptions.Append (":"); dnnOptions.Append (layoutString);
      dnnOptions.Append (":"); dnnOptions.Append (trainingStrategyString);

      // Cuda implementation.
      if (Use["DNN_GPU"]) {
	TString gpuOptions = dnnOptions + ":Architecture=GPU";//kDL
	factory->BookMethod(dataloader, TMVA::Types::kDNN, "DNN_GPU", gpuOptions);
      }
      // Multi-core CPU implementation.
      if (Use["DNN_CPU"]) {
	TString cpuOptions = dnnOptions + ":Architecture=CPU";//kDL
	factory->BookMethod(dataloader, TMVA::Types::kDNN, "DNN_CPU", cpuOptions);
      }
   }

   // CF(Clermont-Ferrand)ANN
   if (Use["CFMlpANN"])
      factory->BookMethod( dataloader, TMVA::Types::kCFMlpANN, "CFMlpANN", "!H:!V:NCycles=200:HiddenLayers=N+1,N"  ); // n_cycles:#nodes:#nodes:...

   // Tmlp(Root)ANN
   if (Use["TMlpANN"])
      factory->BookMethod( dataloader, TMVA::Types::kTMlpANN, "TMlpANN", "!H:!V:NCycles=200:HiddenLayers=N+1,N,N,:LearningMethod=BFGS:ValidationFraction=0.1"  ); // n_cycles:#nodes:#nodes:...

   // Support Vector Machine
   if (Use["SVM"])
      factory->BookMethod( dataloader, TMVA::Types::kSVM, "SVM", "Gamma=0.25:Tol=0.7:VarTransform=Norm" );

   // Boosted Decision Trees
   if (Use["BDTG"]) //{// Gradient Boost
     // auto mm = 
      factory->BookMethod( dataloader, TMVA::Types::kBDT, "BDTG",
			   "!H:!V:NTrees=50:MinNodeSize=5%:MaxDepth=3:BoostType=Grad:Shrinkage=0.15:UseBaggedGrad=true:BaggedSampleFraction=0.10:SeparationType=GiniIndex:nCuts=50:DoBoostMonitor=true:UseRandomisedTrees=True:UseNvars=13");


			   //"!H:!V:NTrees=10:MinNodeSize=5%:MaxDepth=4:BoostType=Grad:Shrinkage=0.45:UseBaggedGrad=true:SeparationType=GiniIndex:nCuts=50:UseRandomisedTrees=True:DoBoostMonitor=true:UseNvars=16");
   //			   "!H:!V:NTrees=30:MinNodeSize=3%:BoostType=Grad:Shrinkage=0.45:UseBaggedGrad=true:MaxDepth=3:nCuts=5000:UseRandomisedTrees=True:DoBoostMonitor=true");
			   //"!H:!V:NTrees=50:MinNodeSize=10%:BoostType=Grad:Shrinkage=0.45:UseBaggedBoost=true:MaxDepth=2:nCuts=20:UseRandomisedTrees=True:UseNvars=16:VarTransform=D,D,D:SigToBkgFraction=0.1:DoBoostMonitor=true");
			   //"!H:!V:NTrees=50:MinNodeSize=10%:BoostType=Grad:Shrinkage=0.45:UseBaggedBoost=true:MaxDepth=3:nCuts=60000:UseRandomisedTrees=True:UseNvars=21:SeparationType=GiniIndex:VarTransform=D,D,D,N:SigToBkgFraction=0.1:DoBoostMonitor=true");
			   //"!H:!V:NTrees=20:MinNodeSize=10%:BoostType=Grad:Shrinkage=0.45:UseBaggedBoost=true:MaxDepth=3:nCuts=30:UseRandomisedTrees=True:UseNvars=16:SeparationType=GiniIndex:VarTransform=D,D,D,N:SigToBkgFraction=0.1:DoBoostMonitor=true");
   

////////////////////////////////// 

   if (Use["BDT"])  // Adaptive Boost
     //  factory->BookMethod( dataloader, TMVA::Types::kBDT, "BDT");
   factory->BookMethod( dataloader, TMVA::Types::kBDT, "BDT", 

			//"!H:!V:NTrees=445:MinNodeSize=3%:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.62:UseBaggedBoost:BaggedSampleFraction=0.14:SeparationType=CrossEntropy:nCuts=95:DoBoostMonitor=true:UseRandomisedTrees=True:UseNvars=13"); 
			//"!H:!V:NTrees=325:MinNodeSize=4%:MaxDepth=4:BoostType=AdaBoost:AdaBoostBeta=0.60:UseBaggedBoost:BaggedSampleFraction=0.12:SeparationType=CrossEntropy:nCuts=5:DoBoostMonitor=true:UseRandomisedTrees=True:UseNvars=13");

			//"!H:!V:NTrees=500:MinNodeSize=2%:MaxDepth=10:BoostType=AdaBoost:AdaBoostBeta=0.60:UseBaggedBoost:BaggedSampleFraction=0.12:SeparationType=CrossEntropy:nCuts=5:DoBoostMonitor=true:UseRandomisedTrees=True:UseNvars=13");
			//"!H:!V:NTrees=500:MinNodeSize=2%:MaxDepth=10:BoostType=AdaBoost:AdaBoostBeta=0.65:UseBaggedBoost:BaggedSampleFraction=0.10:SeparationType=CrossEntropy:nCuts=10:DoBoostMonitor=true:UseRandomisedTrees=True:UseNvars=13");max: 0.10614, sample5
			//"!H:!V:NTrees=500:MinNodeSize=3%:MaxDepth=10:BoostType=AdaBoost:AdaBoostBeta=0.60:UseBaggedBoost:BaggedSampleFraction=0.10:SeparationType=CrossEntropy:nCuts=10:DoBoostMonitor=true:UseRandomisedTrees=True:UseNvars=13");
			//"!H:!V:NTrees=400:MinNodeSize=5%:MaxDepth=5:BoostType=AdaBoost:AdaBoostBeta=0.50:UseBaggedBoost:BaggedSampleFraction=0.14:SeparationType=CrossEntropy:nCuts=10:DoBoostMonitor=true:UseRandomisedTrees=True:UseNvars=13"); max: 0.111184 sample6
			//"!H:!V:NTrees=400:MinNodeSize=5%:MaxDepth=5:BoostType=AdaBoost:AdaBoostBeta=0.60:UseBaggedBoost:BaggedSampleFraction=0.14:SeparationType=CrossEntropy:nCuts=10:DoBoostMonitor=true:UseRandomisedTrees=True:UseNvars=13"); max: 0.116599 at 129 eff: 0.126316 pur: 0.923077 sample7 (max: 0.10614 at 129 eff: 0.115789 pur: 0.916667)
			//"!H:!V:NTrees=400:MinNodeSize=4%:MaxDepth=10:BoostType=AdaBoost:AdaBoostBeta=0.65:UseBaggedBoost:BaggedSampleFraction=0.14:SeparationType=CrossEntropy:nCuts=10:DoBoostMonitor=true:UseRandomisedTrees=True:UseNvars=13"); max: 0.10614 at 129 eff: 0.115789 pur: 0.916667 sample8
			"!H:!V:NTrees=300:MinNodeSize=4%:MaxDepth=10:BoostType=AdaBoost:AdaBoostBeta=0.65:UseBaggedBoost:BaggedSampleFraction=0.16:SeparationType=CrossEntropy:nCuts=10:DoBoostMonitor=true:UseRandomisedTrees=True:UseNvars=13"); //max: 0.116599 at 129 eff: 0.126316 pur: 0.923077 sample9
			//"!H:!V:NTrees=300:MinNodeSize=4%:MaxDepth=10:BoostType=AdaBoost:AdaBoostBeta=0.65:UseBaggedBoost:BaggedSampleFraction=0.16:SeparationType=CrossEntropy:nCuts=10:DoBoostMonitor=true:UseRandomisedTrees=True:UseNvars=13");//sample10
			//"!H:!V:NTrees=300:MinNodeSize=5%:MaxDepth=20:BoostType=AdaBoost:AdaBoostBeta=0.60:UseBaggedBoost:BaggedSampleFraction=0.15:SeparationType=CrossEntropy:nCuts=30:DoBoostMonitor=true:UseRandomisedTrees=True:UseNvars=13"); 



// set the parameters for BDT training

//////////////////////////////////


   if (Use["BDTB"]) // Bagging
      factory->BookMethod( dataloader, TMVA::Types::kBDT, "BDTB","!H:!V:NTrees=300:MinNodeSize=2%:BoostType=Bagging:Shrinkage=0.1:UseBaggedBoost=True:MaxDepth=5:UseRandomisedTrees=True:UseNvars=16:SeparationType=GiniIndex:nCuts=50:BaggedSampleFraction=0.2" );

   if (Use["BDTD"]) // Decorrelation + Adaptive Boost
      factory->BookMethod( dataloader, TMVA::Types::kBDT, "BDTD",
			   //"!H:!V:NTrees=300:MinNodeSize=5%:MaxDepth=10:BoostType=AdaBoost:AdaBoostBeta=0.50:UseBaggedBoost:BaggedSampleFraction=0.10:SeparationType=CrossEntropy:nCuts=50:DoBoostMonitor=true:UseRandomisedTrees=True:UseNvars=16:VarTransform=Decorrelate");
			   //"!H:!V:NTrees=350:MinNodeSize=4%:MaxDepth=4:BoostType=AdaBoost:AdaBoostBeta=0.35:UseBaggedBoost:BaggedSampleFraction=0.10:SeparationType=CrossEntropy:nCuts=15:DoBoostMonitor=true:UseRandomisedTrees=True:UseNvars=16");
			   
			   
			   "!H:!V:NTrees=400:MinNodeSize=4%:MaxDepth=5:BoostType=AdaBoost:AdaBoostBeta=0.25:UseBaggedBoost:BaggedSampleFraction=0.08:SeparationType=CrossEntropy:nCuts=5:DoBoostMonitor=true:UseRandomisedTrees=True:UseNvars=16:VarTransform=Decorrelate");

   //"!H:!V:NTrees=470:MinNodeSize=5%:MaxDepth=5:BoostType=AdaBoost:AdaBoostBeta=0.50:UseBaggedBoost:BaggedSampleFraction=0.12:SeparationType=CrossEntropy:nCuts=5:DoBoostMonitor=true:UseRandomisedTrees=True:UseNvars=16"); max: 0.0413565 at 131 eff: 0.0537634 pur: 0.769231

   //"!H:!V:NTrees=20:MinNodeSize=5%:MaxDepth=5:BoostType=AdaBoost:SeparationType=GiniIndex:nCuts=200:VarTransform=Decorrelate" );

   if (Use["BDTF"])  // Allow Using Fisher discriminant in node splitting for (strong) linearly correlated variables
      factory->BookMethod( dataloader, TMVA::Types::kBDT, "BDTF",
                           //"!H:!V:NTrees=300:MinNodeSize=4%:UseFisherCuts:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.20:SeparationType=GiniIndex:nCuts=500" );
			   //"!H:!V:NTrees=330:MinNodeSize=5%:MaxDepth=5:BoostType=AdaBoost:AdaBoostBeta=0.50:UseBaggedBoost:BaggedSampleFraction=0.14:SeparationType=CrossEntropy:nCuts=16:DoBoostMonitor=true:UseRandomisedTrees=True:UseNvars=16");
			   //"!H:!V:NTrees=700:MinNodeSize=5%:UseFisherCuts:MaxDepth=5:BoostType=AdaBoost:AdaBoostBeta=0.45:UseBaggedBoost:BaggedSampleFraction=0.15:SeparationType=CrossEntropy:nCuts=5:DoBoostMonitor=true:UseRandomisedTrees=True:UseNvars=16");

"!H:!V:NTrees=400:MinNodeSize=5%:UseFisherCuts:MaxDepth=5:BoostType=AdaBoost:AdaBoostBeta=0.50:UseBaggedBoost:BaggedSampleFraction=0.14:SeparationType=CrossEntropy:nCuts=5:DoBoostMonitor=true:UseRandomisedTrees=True:UseNvars=16");


   /**/
   // RuleFit -- TMVA implementation of Friedman's method
   //if (Use["RuleFit"])
   //   factory->BookMethod( dataloader, TMVA::Types::kRuleFit, "RuleFit",
   //                        "H:!V:RuleFitModule=RFTMVA:Model=ModRuleLinear:MinImp=0.001:RuleMinDist=0.001:NTrees=20:fEventsMin=0.01:fEventsMax=0.5:GDTau=-1.0:GDTauPrec=0.01:GDStep=0.01:GDNSteps=10000:GDErrScale=1.02" );

   // For an example of the category classifier usage, see: TMVAClassificationCategory
   //
   // --------------------------------------------------------------------------------------------------
   //  Now you can optimize the setting (configuration) of the MVAs using the set of training events
   // STILL EXPERIMENTAL and only implemented for BDT's !
   //
   //     factory->OptimizeAllMethods("SigEffAtBkg0.01","Scan");
   //     factory->OptimizeAllMethods("ROCIntegral","FitGA");
   //
   // --------------------------------------------------------------------------------------------------

   // Now you can tell the factory to train, test, and evaluate the MVAs
   //
   // Train MVAs using the set of training events
   factory->TrainAllMethods();
   
   // Evaluate all MVAs using the set of test events
   factory->TestAllMethods();

   // Evaluate and compare performance of all configured MVAs
   factory->EvaluateAllMethods();

   // --------------------------------------------------------------

   // Save the output
   outputFile->Close();

   std::cout << "==> Wrote root file: " << outputFile->GetName() << std::endl;
   std::cout << "==> TMVAClassification is done!" << std::endl;

   delete factory;
   delete dataloader;
   // Launch the GUI for the root macros
   if (!gROOT->IsBatch()) TMVA::TMVAGui( outfileName );

   return 0;
   
}

int main( int argc, char** argv )
{
   // Select methods (don't look at this code - not of interest)
   TString methodList;
   for (int i=1; i<argc; i++) {
      TString regMethod(argv[i]);
      if(regMethod=="-b" || regMethod=="--batch") continue;
      if (!methodList.IsNull()) methodList += TString(",");
      methodList += regMethod;
   }
   return TMVAClassification_template_addspec(methodList);
}

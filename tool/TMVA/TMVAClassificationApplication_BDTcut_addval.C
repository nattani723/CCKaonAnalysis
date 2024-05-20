/// \file
/// \ingroup tutorial_tmva
/// \notebook -nodraw
/// This macro provides a simple example on how to use the trained classifiers
/// within an analysis module
/// - Project   : TMVA - a Root-integrated toolkit for multivariate data analysis
/// - Package   : TMVA
/// - Exectuable: TMVAClassificationApplication
///
/// \macro_output
/// \macro_code
/// \author Andreas Hoecker

#include <cstdlib>
#include <vector>
#include <iostream>
#include <map>
#include <string>

#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TSystem.h"
#include "TROOT.h"
#include "TStopwatch.h"

#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#include "TMVA/MethodCuts.h"

using namespace TMVA;

void TMVAClassificationApplication_BDTcut_addval( TString myMethodList = "" )
{
  
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
  Use["DNN_CPU"] = 0;         // CUDA-accelerated DNN training.
  Use["DNN_GPU"] = 0;         // Multi-core accelerated DNN.
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
  Use["Plugin"]          = 0;
  Use["Category"]        = 0;
  Use["SVM_Gauss"]       = 0;
  Use["SVM_Poly"]        = 0;
  Use["SVM_Lin"]         = 0;
  
  std::cout << std::endl;
  std::cout << "==> Start TMVAClassificationApplication" << std::endl;
  
  // Select methods (don't look at this code - not of interest)
  if (myMethodList != "") {
    for (std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) it->second = 0;
    
    std::vector<TString> mlist = gTools().SplitString( myMethodList, ',' );
    for (UInt_t i=0; i<mlist.size(); i++) {
      std::string regMethod(mlist[i]);
      
      if (Use.find(regMethod) == Use.end()) {
	std::cout << "Method \"" << regMethod
		  << "\" not known in TMVA under this name. Choose among the following:" << std::endl;
	for (std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) {
	  std::cout << it->first << " ";
	}
	std::cout << std::endl;
	return;
      }
      Use[regMethod] = 1;
    }
  }
  
  // --------------------------------------------------------------------------------------------------
  
  // Create the Reader object
  
  //TMVA::Reader *reader = new TMVA::Reader( "!Color:!Silent" );
  TMVA::Reader *reader = new TMVA::Reader( "V" );
  
  // Create a set of variables and declare them to the reader
  // - the variable names MUST corresponds in name and type to those given in the weight file(s) used
  /*
    Float_t var1, var2;
    Float_t var3, var4;
    reader->AddVariable( "myvar1 := var1+var2", &var1 );
    reader->AddVariable( "myvar2 := var1-var2", &var2 );
    reader->AddVariable( "var3",                &var3 );
    reader->AddVariable( "var4",                &var4 );
  */

  Int_t BDTcut=0;
  Float_t reco_track_chi2ka_pl0, reco_track_chi2pr_pl0, reco_track_chi2pi_pl0, reco_track_chi2mu_pl0;
  Float_t reco_track_chi2ka_pl1, reco_track_chi2pr_pl1, reco_track_chi2pi_pl1, reco_track_chi2mu_pl1;
  Float_t reco_track_chi2ka_pl2, reco_track_chi2pr_pl2, reco_track_chi2pi_pl2, reco_track_chi2mu_pl2;
  Float_t reco_track_chi2ka_3pl, reco_track_chi2pr_3pl, reco_track_chi2pi_3pl, reco_track_chi2mu_3pl;
  Float_t reco_track_daughter_chi2ka_pl0, reco_track_daughter_chi2pr_pl0, reco_track_daughter_chi2pi_pl0, reco_track_daughter_chi2mu_pl0;
  Float_t reco_track_daughter_chi2ka_pl1, reco_track_daughter_chi2pr_pl1, reco_track_daughter_chi2pi_pl1, reco_track_daughter_chi2mu_pl1;
  Float_t reco_track_daughter_chi2ka_pl2, reco_track_daughter_chi2pr_pl2, reco_track_daughter_chi2pi_pl2, reco_track_daughter_chi2mu_pl2;
  Float_t reco_track_daughter_chi2ka_3pl, reco_track_daughter_chi2pr_3pl, reco_track_daughter_chi2pi_3pl, reco_track_daughter_chi2mu_3pl;
  Float_t reco_track_llrpid_3pl, reco_track_llrpid_k_3pl, reco_track_daughter_llrpid_3pl, reco_track_daughter_llrpid_k_3pl;
  Float_t reco_track_length, reco_track_daughter_length, reco_track_daughter_distance, reco_track_daughter_vtx_distance;
  Float_t reco_track_theta, reco_track_phi, reco_track_daughter_theta, reco_track_daughter_phi, reco_track_distance, reco_track_vtx_distance;
  
  /*
  reader->AddVariable("reco_track_chi2ka_pl0", &reco_track_chi2ka_pl0);
  reader->AddVariable("reco_track_chi2pr_pl0", &reco_track_chi2pr_pl0);
  reader->AddVariable("reco_track_chi2pi_pl0", &reco_track_chi2pi_pl0);
  reader->AddVariable("reco_track_chi2mu_pl0", &reco_track_chi2mu_pl0);

  reader->AddVariable("reco_track_chi2ka_pl1", &reco_track_chi2ka_pl1);
  reader->AddVariable("reco_track_chi2pr_pl1", &reco_track_chi2pr_pl1);
  reader->AddVariable("reco_track_chi2pi_pl1", &reco_track_chi2pi_pl1);
  reader->AddVariable("reco_track_chi2mu_pl1", &reco_track_chi2mu_pl1);

  reader->AddVariable("reco_track_daughter_chi2ka_pl0", &reco_track_daughter_chi2ka_pl0);
  reader->AddVariable("reco_track_daughter_chi2pr_pl0", &reco_track_daughter_chi2pr_pl0);
  reader->AddVariable("reco_track_daughter_chi2pi_pl0", &reco_track_daughter_chi2pi_pl0);
  reader->AddVariable("reco_track_daughter_chi2mu_pl0", &reco_track_daughter_chi2mu_pl0);

  reader->AddVariable("reco_track_daughter_chi2ka_pl1", &reco_track_daughter_chi2ka_pl1);
  reader->AddVariable("reco_track_daughter_chi2pr_pl1", &reco_track_daughter_chi2pr_pl1);
  reader->AddVariable("reco_track_daughter_chi2pi_pl1", &reco_track_daughter_chi2pi_pl1);
  reader->AddVariable("reco_track_daughter_chi2mu_pl1", &reco_track_daughter_chi2mu_pl1);
  */

  /*
  reader->AddVariable("reco_track_chi2ka_pl2", &reco_track_chi2ka_pl2);
  reader->AddVariable("reco_track_chi2pr_pl2", &reco_track_chi2pr_pl2);
  reader->AddVariable("reco_track_chi2pi_pl2", &reco_track_chi2pi_pl2);
  reader->AddVariable("reco_track_chi2mu_pl2", &reco_track_chi2mu_pl2);

  reader->AddVariable("reco_track_daughter_chi2ka_pl2", &reco_track_daughter_chi2ka_pl2);
  reader->AddVariable("reco_track_daughter_chi2pr_pl2", &reco_track_daughter_chi2pr_pl2);
  reader->AddVariable("reco_track_daughter_chi2pi_pl2", &reco_track_daughter_chi2pi_pl2);
  reader->AddVariable("reco_track_daughter_chi2mu_pl2", &reco_track_daughter_chi2mu_pl2);
  */

  
  reader->AddVariable("reco_track_chi2ka_3pl", &reco_track_chi2ka_3pl);
  reader->AddVariable("reco_track_chi2pr_3pl", &reco_track_chi2pr_3pl);
  reader->AddVariable("reco_track_chi2pi_3pl", &reco_track_chi2pi_3pl);
  reader->AddVariable("reco_track_chi2mu_3pl", &reco_track_chi2mu_3pl);

  reader->AddVariable("reco_track_daughter_chi2ka_3pl", &reco_track_daughter_chi2ka_3pl);
  reader->AddVariable("reco_track_daughter_chi2pr_3pl", &reco_track_daughter_chi2pr_3pl);
  reader->AddVariable("reco_track_daughter_chi2pi_3pl", &reco_track_daughter_chi2pi_3pl);
  reader->AddVariable("reco_track_daughter_chi2mu_3pl", &reco_track_daughter_chi2mu_3pl);
    
  reader->AddVariable("reco_track_llrpid_3pl", &reco_track_llrpid_3pl);
  reader->AddVariable("reco_track_llrpid_k_3pl", &reco_track_llrpid_k_3pl);
  reader->AddVariable("reco_track_daughter_llrpid_3pl", &reco_track_daughter_llrpid_3pl);
  reader->AddVariable("reco_track_daughter_llrpid_k_3pl", &reco_track_daughter_llrpid_k_3pl);
  
  //reader->AddVariable("reco_track_distance", &reco_track_distance);
  //reader->AddVariable("reco_track_vtx_distance", &reco_track_vtx_distance);

  //reader->AddVariable("reco_track_theta", &reco_track_theta);
  //reader->AddVariable("reco_track_phi", &reco_track_phi);

  reader->AddVariable("reco_track_daughter_length", &reco_track_daughter_length);

  
  //reader->AddVariable("reco_track_length", &reco_track_length);
  //reader->AddVariable("reco_track_daughter_vtx_distance", &reco_track_daughter_vtx_distance);
  //reader->AddVariable("reco_track_daughter_distance", &reco_track_daughter_distance);
  
  //reader->AddVariable("reco_track_daughter_theta", &reco_track_daughter_theta);
  //reader->AddVariable("reco_track_daughter_phi", &reco_track_daughter_phi);
  
  
  Float_t reco_track_true_pdg, reco_track_daughter_true_pdg, true_nu_energy, true_nu_ccnc, true_nu_mode, true_lepton_pdg, reco_ccmu_true_pdg;
  Float_t true_nkaons, true_kaon_length, true_kaon_p, true_kaon_ke, true_kaon_theta, true_kaon_costheta, true_kaon_phi;
  Float_t true_nu_pdg, true_nu_vtx_inCCInclusiveTPC, true_kaon_end_inCCInclusiveTPC, true_kaon_daughter_end_in5cmTPC, run, subrun, eventnum, true_kaon_end_process;
  Float_t reco_track_kin0, reco_track_kin1, reco_track_kin2,  true_kaon_daughter_length;// reco_track_chi2ka_pl2, reco_track_chi2pr_pl2, reco_track_chi2pi_pl2, reco_track_chi2mu_pl2, reco_track_daughter_chi2ka_pl2, reco_track_daughter_chi2pr_pl2, reco_track_daughter_chi2pi_pl2, reco_track_daughter_chi2mu_pl2;

  
  reader->AddSpectator("reco_track_true_pdg", &reco_track_true_pdg);
  reader->AddSpectator("reco_track_daughter_true_pdg", &reco_track_daughter_true_pdg);
  reader->AddSpectator("true_nu_energy", &true_nu_energy);
  reader->AddSpectator("true_nu_ccnc", &true_nu_ccnc);
  reader->AddSpectator("true_nu_mode", &true_nu_mode);
  reader->AddSpectator("true_lepton_pdg", &true_lepton_pdg);
  reader->AddSpectator("true_nkaons", &true_nkaons);
  reader->AddSpectator("true_kaon_length", &true_kaon_length);
  reader->AddSpectator("true_kaon_p", &true_kaon_p);
  reader->AddSpectator("true_kaon_ke", &true_kaon_ke);
  reader->AddSpectator("true_kaon_theta", &true_kaon_theta);
  reader->AddSpectator("true_kaon_costheta", &true_kaon_costheta);
  reader->AddSpectator("true_kaon_phi", &true_kaon_phi);
  reader->AddSpectator("reco_ccmu_true_pdg", &reco_ccmu_true_pdg);
  
  
  reader->AddSpectator("true_nu_pdg", &true_nu_pdg);
  reader->AddSpectator("true_nu_vtx_inCCInclusiveTPC", &true_nu_vtx_inCCInclusiveTPC);
  reader->AddSpectator("true_kaon_end_inCCInclusiveTPC", &true_kaon_end_inCCInclusiveTPC);
  reader->AddSpectator("true_kaon_daughter_end_in5cmTPC", &true_kaon_daughter_end_in5cmTPC);
  
  reader->AddSpectator("run", &run);
  reader->AddSpectator("subrun", &subrun);
  reader->AddSpectator("eventnum", &eventnum);
  
  //reader->AddSpectator("reco_track_kin0", &reco_track_kin0);
  //reader->AddSpectator("reco_track_kin1", &reco_track_kin1);
  //reader->AddSpectator("reco_track_kin2", &reco_track_kin2);
  reader->AddSpectator("reco_track_theta", &reco_track_theta);
  reader->AddSpectator("reco_track_phi", &reco_track_phi);
  reader->AddSpectator("true_kaon_daughter_length", &true_kaon_daughter_length);

  reader->AddSpectator("reco_track_chi2ka_pl2", &reco_track_chi2ka_pl2);
  reader->AddSpectator("reco_track_chi2pr_pl2", &reco_track_chi2pr_pl2);
  reader->AddSpectator("reco_track_chi2pi_pl2", &reco_track_chi2pi_pl2);
  reader->AddSpectator("reco_track_chi2mu_pl2", &reco_track_chi2mu_pl2);

  reader->AddSpectator("reco_track_daughter_chi2ka_pl2", &reco_track_daughter_chi2ka_pl2);
  reader->AddSpectator("reco_track_daughter_chi2pr_pl2", &reco_track_daughter_chi2pr_pl2);
  reader->AddSpectator("reco_track_daughter_chi2pi_pl2", &reco_track_daughter_chi2pi_pl2);
  reader->AddSpectator("reco_track_daughter_chi2mu_pl2", &reco_track_daughter_chi2mu_pl2);

  //reader->AddSpectator("true_kaon_end_process", &true_kaon_end_process);
  /*
  reader->AddSpectator("reco_nu_cc_filter", &reco_nu_cc_filter);  
  reader->AddSpectator("reco_nu_vtx_inCCInclusiveTPC", &reco_nu_vtx_inCCInclusiveTPC);  
  reader->AddSpectator("reco_track_end_inCCInclusiveTPC", &reco_track_end_inCCInclusiveTPC);  
  reader->AddSpectator("reco_track_ndaughters", &reco_track_ndaughters);  
  reader->AddSpectator("reco_track_daughter_vtx_in5cmTPC", &reco_track_daughter_vtx_in5cmTPC);  
  reader->AddSpectator("reco_track_daughter_end_in5cmTPC", &reco_track_daughter_end_in5cmTPC);  
  reader->AddSpectator("reco_track_end_inCCInclusiveTPC", &reco_track_end_inCCInclusiveTPC);  
  */

  // Book the MVA methods
  
  //TString dir    = "/uboone/app/users/taniuchi/KaonAna/KaonAnlysis/Ana/TMVA/15Aug/dataset_all_pl2_BDT_ntree350_ncut15_depth4_beta40_frac10_node4_Gini/weights/";
  TString dir    = "/uboone/app/users/taniuchi/KaonAna/KaonAnlysis/Ana/TMVA/rebuildTrack/dataset_notrklength_BDT2_w_5Dec_sample_all9/weights/";
  TString prefix = "TMVAClassification";
  
  //TString methodName;
  // Book method(s)
  for (std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) {
    if (it->second) {
      //methodName = TString(it->first) + TString(" method");
      TString methodName = TString(it->first) + TString(" method");
      TString weightfile = dir + prefix + TString("_") + TString(it->first) + TString(".weights.xml");
      reader->BookMVA( methodName, weightfile );
      cout << methodName << endl;
      cout << weightfile << endl;
    }
  }
  
  // Book output histograms
  UInt_t nbin = 100;
  TH1F *histLk(0);
  TH1F *histLkD(0);
  TH1F *histLkPCA(0);
  TH1F *histLkKDE(0);
  TH1F *histLkMIX(0);
  TH1F *histPD(0);
  TH1F *histPDD(0);
  TH1F *histPDPCA(0);
  TH1F *histPDEFoam(0);
  TH1F *histPDEFoamErr(0);
  TH1F *histPDEFoamSig(0);
  TH1F *histKNN(0);
  TH1F *histHm(0);
  TH1F *histFi(0);
  TH1F *histFiG(0);
  TH1F *histFiB(0);
  TH1F *histLD(0);
  TH1F *histNn(0);
  TH1F *histNnbfgs(0);
  TH1F *histNnbnn(0);
  TH1F *histNnC(0);
  TH1F *histNnT(0);
  TH1F *histBdt(0);
  TH1F *histBdtG(0);
  TH1F *histBdtB(0);
  TH1F *histBdtD(0);
  TH1F *histBdtF(0);
  TH1F *histRf(0);
  TH1F *histSVMG(0);
  TH1F *histSVMP(0);
  TH1F *histSVML(0);
  TH1F *histFDAMT(0);
  TH1F *histFDAGA(0);
  TH1F *histCat(0);
  TH1F *histPBdt(0);
  TH1F *histDnnGpu(0);
  TH1F *histDnnCpu(0);
  
  if (Use["Likelihood"])    histLk      = new TH1F( "MVA_Likelihood",    "MVA_Likelihood",    nbin, -1, 1 );
  if (Use["LikelihoodD"])   histLkD     = new TH1F( "MVA_LikelihoodD",   "MVA_LikelihoodD",   nbin, -1, 0.9999 );
  if (Use["LikelihoodPCA"]) histLkPCA   = new TH1F( "MVA_LikelihoodPCA", "MVA_LikelihoodPCA", nbin, -1, 1 );
  if (Use["LikelihoodKDE"]) histLkKDE   = new TH1F( "MVA_LikelihoodKDE", "MVA_LikelihoodKDE", nbin,  -0.00001, 0.99999 );
  if (Use["LikelihoodMIX"]) histLkMIX   = new TH1F( "MVA_LikelihoodMIX", "MVA_LikelihoodMIX", nbin,  0, 1 );
  if (Use["PDERS"])         histPD      = new TH1F( "MVA_PDERS",         "MVA_PDERS",         nbin,  0, 1 );
  if (Use["PDERSD"])        histPDD     = new TH1F( "MVA_PDERSD",        "MVA_PDERSD",        nbin,  0, 1 );
  if (Use["PDERSPCA"])      histPDPCA   = new TH1F( "MVA_PDERSPCA",      "MVA_PDERSPCA",      nbin,  0, 1 );
  if (Use["KNN"])           histKNN     = new TH1F( "MVA_KNN",           "MVA_KNN",           nbin,  0, 1 );
  if (Use["HMatrix"])       histHm      = new TH1F( "MVA_HMatrix",       "MVA_HMatrix",       nbin, -0.95, 1.55 );
  if (Use["Fisher"])        histFi      = new TH1F( "MVA_Fisher",        "MVA_Fisher",        nbin, -4, 4 );
  if (Use["FisherG"])       histFiG     = new TH1F( "MVA_FisherG",       "MVA_FisherG",       nbin, -1, 1 );
  if (Use["BoostedFisher"]) histFiB     = new TH1F( "MVA_BoostedFisher", "MVA_BoostedFisher", nbin, -2, 2 );
  if (Use["LD"])            histLD      = new TH1F( "MVA_LD",            "MVA_LD",            nbin, -2, 2 );
  if (Use["MLP"])           histNn      = new TH1F( "MVA_MLP",           "MVA_MLP",           nbin, -1.25, 1.5 );
  if (Use["MLPBFGS"])       histNnbfgs  = new TH1F( "MVA_MLPBFGS",       "MVA_MLPBFGS",       nbin, -1.25, 1.5 );
  if (Use["MLPBNN"])        histNnbnn   = new TH1F( "MVA_MLPBNN",        "MVA_MLPBNN",        nbin, -1.25, 1.5 );
  if (Use["CFMlpANN"])      histNnC     = new TH1F( "MVA_CFMlpANN",      "MVA_CFMlpANN",      nbin,  0, 1 );
  if (Use["TMlpANN"])       histNnT     = new TH1F( "MVA_TMlpANN",       "MVA_TMlpANN",       nbin, -1.3, 1.3 );
  if (Use["DNN_GPU"]) histDnnGpu = new TH1F("MVA_DNN_GPU", "MVA_DNN_GPU", nbin, -0.1, 1.1);
  if (Use["DNN_CPU"]) histDnnCpu = new TH1F("MVA_DNN_CPU", "MVA_DNN_CPU", nbin, -0.1, 1.1);
  if (Use["BDT"])           histBdt     = new TH1F( "MVA_BDT",           "MVA_BDT",           nbin, -0.8, 0.8 );
  if (Use["BDTG"])          histBdtG    = new TH1F( "MVA_BDTG",          "MVA_BDTG",          nbin, -1.0, 1.0 );
  if (Use["BDTB"])          histBdtB    = new TH1F( "MVA_BDTB",          "MVA_BDTB",          nbin, -1.0, 1.0 );
  if (Use["BDTD"])          histBdtD    = new TH1F( "MVA_BDTD",          "MVA_BDTD",          nbin, -0.8, 0.8 );
  if (Use["BDTF"])          histBdtF    = new TH1F( "MVA_BDTF",          "MVA_BDTF",          nbin, -1.0, 1.0 );
  if (Use["RuleFit"])       histRf      = new TH1F( "MVA_RuleFit",       "MVA_RuleFit",       nbin, -2.0, 2.0 );
  if (Use["SVM_Gauss"])     histSVMG    = new TH1F( "MVA_SVM_Gauss",     "MVA_SVM_Gauss",     nbin,  0.0, 1.0 );
  if (Use["SVM_Poly"])      histSVMP    = new TH1F( "MVA_SVM_Poly",      "MVA_SVM_Poly",      nbin,  0.0, 1.0 );
  if (Use["SVM_Lin"])       histSVML    = new TH1F( "MVA_SVM_Lin",       "MVA_SVM_Lin",       nbin,  0.0, 1.0 );
  if (Use["FDA_MT"])        histFDAMT   = new TH1F( "MVA_FDA_MT",        "MVA_FDA_MT",        nbin, -2.0, 3.0 );
  if (Use["FDA_GA"])        histFDAGA   = new TH1F( "MVA_FDA_GA",        "MVA_FDA_GA",        nbin, -2.0, 3.0 );
  if (Use["Category"])      histCat     = new TH1F( "MVA_Category",      "MVA_Category",      nbin, -2., 2. );
  if (Use["Plugin"])        histPBdt    = new TH1F( "MVA_PBDT",          "MVA_BDT",           nbin, -0.8, 0.8 );


  //add new histos
  TH1F * BDT_track_ka = new TH1F("BDT_track_ka", "; BDT Response; Number of Events", 100, -1, 1);
  TH1F * BDT_track_pr = new TH1F("BDT_track_pr", "; BDT Response; Number of Events", 100, -1, 1);
  TH1F * BDT_track_pi = new TH1F("BDT_track_pi", "; BDT Response; Number of Events", 100, -1, 1);
  TH1F * BDT_track_mu = new TH1F("BDT_track_mu", "; BDT Response; Number of Events", 100, -1, 1);
  TH1F * BDT_track_ot = new TH1F("BDT_track_ot", "; BDT Response; Number of Events", 100, -1, 1);
  TH1F * BDT_daughter_ka = new TH1F("BDT_daughter_ka", "; BDT Response; Number of Events", 100, -1, 1);
  TH1F * BDT_daughter_pr = new TH1F("BDT_daughter_pr", "; BDT Response; Number of Events", 100, -1, 1);
  TH1F * BDT_daughter_pi = new TH1F("BDT_daughter_pi", "; BDT Response; Number of Events", 100, -1, 1);
  TH1F * BDT_daughter_mu = new TH1F("BDT_daughter_mu", "; BDT Response; Number of Events", 100, -1, 1);
  TH1F * BDT_daughter_ot = new TH1F("BDT_daughter_ot", "; BDT Response; Number of Events", 100, -1, 1);
  TH1F * h_sig = new TH1F("h_sig", "; BDT signal; Number of Events", 100, -1, 1);
  TH1F * h_bg = new TH1F("h_bg", "; BDT background; Number of Events", 100, -1, 1);

  TLegend * l = new TLegend(0.75,0.65,0.95,0.95);
  l->AddEntry(BDT_track_ka, "True K^{+}"  , "f");
  l->AddEntry(BDT_track_pr, "True p" , "f");
  l->AddEntry(BDT_track_pi, "True #pi^{+}"   , "f");
  l->AddEntry(BDT_track_mu, "True #mu^{-}"   , "f");
  l->AddEntry(BDT_track_ot, "Others"   , "f");

  TLegend * l_d = new TLegend(0.75,0.65,0.95,0.95);
  l_d->AddEntry(BDT_daughter_pr, "True p" , "f");
  l_d->AddEntry(BDT_daughter_pi, "True #pi^{+}"   , "f");
  l_d->AddEntry(BDT_daughter_mu, "True #mu^{+}"   , "f");
  l_d->AddEntry(BDT_daughter_ot, "Others"   , "f");

  TLegend * l_sn = new TLegend(0.75,0.65,0.95,0.95);
  l_sn->AddEntry(h_sig, "Signal" , "f");
  l_sn->AddEntry(h_bg, "Background" , "f");

  BDT_track_ka->SetFillColor(kBlue);
  BDT_track_pr->SetFillColor(kRed);
  BDT_track_pi->SetFillColor(kGreen+1);
  BDT_track_mu->SetFillColor(kViolet);
  BDT_track_ot->SetFillColor(kOrange+1);

  BDT_daughter_ka->SetFillColor(kBlue);
  BDT_daughter_pr->SetFillColor(kRed);
  BDT_daughter_pi->SetFillColor(kGreen+1);
  BDT_daughter_mu->SetFillColor(kAzure+10);
  BDT_daughter_ot->SetFillColor(kOrange+1);

  h_sig->SetFillColor(kRed);
  h_bg->SetFillColor(kBlue);

  THStack * s_trk = new THStack("BDT_track", "");
  THStack * s_dau = new THStack("BDT_daughter", "");
  THStack * s_sn = new THStack("BDT_SN", "");

  
  // PDEFoam also returns per-event error, fill in histogram, and also fill significance
  if (Use["PDEFoam"]) {
    histPDEFoam    = new TH1F( "MVA_PDEFoam",       "MVA_PDEFoam",              nbin,  0, 1 );
    histPDEFoamErr = new TH1F( "MVA_PDEFoamErr",    "MVA_PDEFoam error",        nbin,  0, 1 );
    histPDEFoamSig = new TH1F( "MVA_PDEFoamSig",    "MVA_PDEFoam significance", nbin,  0, 10 );
  }

  // Book example histogram for probability (the other methods are done similarly)
  TH1F *probHistFi(0), *rarityHistFi(0);
  if (Use["Fisher"]) {
    probHistFi   = new TH1F( "MVA_Fisher_Proba",  "MVA_Fisher_Proba",  nbin, 0, 1 );
    rarityHistFi = new TH1F( "MVA_Fisher_Rarity", "MVA_Fisher_Rarity", nbin, 0, 1 );
  }
  
  // Prepare input tree (this must be replaced by your data source)
  // in this example, there is a toy tree with signal and one with background events
  // we'll later on use only the "signal" events for the test in this example.
  //
  TFile *input(0);
  //TString fname = "/uboone/app/users/taniuchi/KaonAna/plots/precut/test.root";
  TString fname = "/uboone/data/users/taniuchi/pandora_alg/ana/singlek_prod_2.root";
  //TString fname = "/uboone/data/users/taniuchi/pandora_alg/ana/cck_numi_test_012_old.root";
  //TString fname = "/uboone/app/users/taniuchi/KaonAna/KaonAnlysis/Ana/track_tuple/make_assok_events_numi_fhc_run1_POT_41E22.root";
  //TString fname = "/uboone/app/users/taniuchi/KaonAna/KaonAnlysis/Ana/track_tuple/make_singlek_events_numi_fhc_run1_POT_18E23.root";
  //TString fname = "/uboone/app/users/taniuchi/KaonAna/KaonAnlysis/Ana/track_tuple/15Aug_numi_run1_fhc.root";
  //TString fname = "/uboone/app/users/taniuchi/KaonAna/KaonAnlysis/Ana/track_tuple/ana_numi_noprecut.root";
  if (!gSystem->AccessPathName( fname )) {
    input = TFile::Open( fname ); // check if file in local directory exists
  }
  else {
    TFile::SetCacheFileDir(".");
    input = TFile::Open("http://root.cern.ch/files/tmva_class_example.root", "CACHEREAD"); // if not: download from ROOT server
  }
  if (!input) {
    std::cout << "ERROR: could not open data file" << std::endl;
    exit(1);
  }
  std::cout << "--- TMVAClassificationApp    : Using input file: " << input->GetName() << std::endl;
  
  
  TString output_pdf_bdt = "BDT_response.pdf"; 
  TCanvas * c = new TCanvas("c", "c", 800, 600); 
  c->SetFillStyle(4000);
  c->Print(Form("%s[", output_pdf_bdt.Data()));
  

  // Event loop
  
  // Prepare the event tree
  // - Here the variable names have to corresponds to your tree
  // - You can use the same variables as above which is slightly faster,
  //   but of course you can use different ones and copy the values inside the event loop
  //
  Int_t reco_track_true_pdgR;
  Float_t reco_track_daughter_true_pdgR, true_kaon_keR;
  Int_t           eventnumR;
  Int_t           runR;
  Int_t           subrunR;
  Int_t           true_nu_pdgR;
  Int_t           true_nu_modeR;
  Int_t           true_nu_ccncR;
  Int_t         true_lepton_pdgR;
  Int_t true_kaon_end_processR;
  Float_t true_kaon_thetaR, true_kaon_costhetaR, true_kaon_phiR, true_kaon_lengthR;
  Float_t reco_track_thetaR, reco_track_costhetaR, reco_track_phiR, reco_track_daughter_thetaR, reco_track_daughter_phiR, reco_track_lengthR;
  Int_t true_nu_vtx_inCCInclusiveTPCR, true_kaon_end_inCCInclusiveTPCR, true_kaon_daughter_end_in5cmTPCR;  
  Bool_t reco_nu_cc_filter, reco_nu_vtx_inCCInclusiveTPC, reco_track_end_inCCInclusiveTPC,  reco_track_daughter_vtx_in5cmTPC, reco_track_daughter_end_in5cmTPC;
  Float_t reco_track_ndaughters;


  std::cout << "--- Select signal sample" << std::endl;
  TTree* theTree = (TTree*)input->Get("CCKaonTracks");

  theTree->SetBranchAddress( "reco_track_chi2ka_pl2", &reco_track_chi2ka_pl2 );
  theTree->SetBranchAddress( "reco_track_chi2pr_pl2", &reco_track_chi2pr_pl2 );
  theTree->SetBranchAddress( "reco_track_chi2pi_pl2", &reco_track_chi2pi_pl2 );
  theTree->SetBranchAddress( "reco_track_chi2mu_pl2", &reco_track_chi2mu_pl2 );
  theTree->SetBranchAddress( "reco_track_daughter_chi2ka_pl2", &reco_track_daughter_chi2ka_pl2 );
  theTree->SetBranchAddress( "reco_track_daughter_chi2pr_pl2", &reco_track_daughter_chi2pr_pl2 );
  theTree->SetBranchAddress( "reco_track_daughter_chi2pi_pl2", &reco_track_daughter_chi2pi_pl2 );
  theTree->SetBranchAddress( "reco_track_daughter_chi2mu_pl2", &reco_track_daughter_chi2mu_pl2 );

  theTree->SetBranchAddress( "reco_track_chi2ka_3pl", &reco_track_chi2ka_3pl );
  theTree->SetBranchAddress( "reco_track_chi2pr_3pl", &reco_track_chi2pr_3pl );
  theTree->SetBranchAddress( "reco_track_chi2pi_3pl", &reco_track_chi2pi_3pl );
  theTree->SetBranchAddress( "reco_track_chi2mu_3pl", &reco_track_chi2mu_3pl );
  theTree->SetBranchAddress( "reco_track_daughter_chi2ka_3pl", &reco_track_daughter_chi2ka_3pl );
  theTree->SetBranchAddress( "reco_track_daughter_chi2pr_3pl", &reco_track_daughter_chi2pr_3pl );
  theTree->SetBranchAddress( "reco_track_daughter_chi2pi_3pl", &reco_track_daughter_chi2pi_3pl );
  theTree->SetBranchAddress( "reco_track_daughter_chi2mu_3pl", &reco_track_daughter_chi2mu_3pl );

  theTree->SetBranchAddress( "reco_track_llrpid_3pl", &reco_track_llrpid_3pl );
  theTree->SetBranchAddress( "reco_track_llrpid_k_3pl", &reco_track_llrpid_k_3pl );
  theTree->SetBranchAddress( "reco_track_daughter_llrpid_3pl", &reco_track_daughter_llrpid_3pl );
  theTree->SetBranchAddress( "reco_track_daughter_llrpid_k_3pl", &reco_track_daughter_llrpid_k_3pl );
  theTree->SetBranchAddress( "reco_track_length", &reco_track_length );
  theTree->SetBranchAddress( "reco_track_daughter_length", &reco_track_daughter_length );
  theTree->SetBranchAddress( "reco_track_daughter_distance", &reco_track_daughter_distance );
  theTree->SetBranchAddress( "reco_track_daughter_vtx_distance", &reco_track_daughter_vtx_distance );

  theTree->SetBranchAddress( "reco_track_true_pdg", &reco_track_true_pdgR );
  theTree->SetBranchAddress( "reco_track_daughter_true_pdg", &reco_track_daughter_true_pdgR );
  theTree->SetBranchAddress( "reco_track_theta", &reco_track_thetaR );
  theTree->SetBranchAddress( "reco_track_costheta", &reco_track_costhetaR );
  theTree->SetBranchAddress( "reco_track_phi", &reco_track_phiR );
  theTree->SetBranchAddress( "reco_track_daughter_theta", &reco_track_daughter_thetaR );
  theTree->SetBranchAddress( "reco_track_daughter_phi", &reco_track_daughter_phiR );

  theTree->SetBranchAddress( "eventnum", &eventnumR);  
  theTree->SetBranchAddress( "run", &runR);  
  theTree->SetBranchAddress( "subrun", &subrunR);
  theTree->SetBranchAddress( "true_nu_pdg", &true_nu_pdgR);  
  theTree->SetBranchAddress( "true_nu_mode", &true_nu_modeR);  
  theTree->SetBranchAddress( "true_lepton_pdg", &true_lepton_pdgR);  
  theTree->SetBranchAddress( "true_nu_ccnc", &true_nu_ccncR);
  theTree->SetBranchAddress( "true_kaon_ke", &true_kaon_keR);  
  theTree->SetBranchAddress( "true_kaon_end_process", &true_kaon_end_processR);  

  theTree->SetBranchAddress( "true_kaon_theta", &true_kaon_thetaR);  
  theTree->SetBranchAddress( "true_kaon_costheta", &true_kaon_costhetaR);  
  theTree->SetBranchAddress( "true_kaon_phi", &true_kaon_phiR);  
  theTree->SetBranchAddress( "true_kaon_daughter_end_in5cmTPC", &true_kaon_daughter_end_in5cmTPCR);  
  theTree->SetBranchAddress( "true_kaon_end_inCCInclusiveTPC", &true_kaon_end_inCCInclusiveTPCR);  
  theTree->SetBranchAddress( "true_nu_vtx_inCCInclusiveTPC", &true_nu_vtx_inCCInclusiveTPCR);
  theTree->SetBranchAddress( "true_kaon_length", &true_kaon_lengthR);  

  theTree->SetBranchAddress("reco_nu_cc_filter", &reco_nu_cc_filter);
  theTree->SetBranchAddress("reco_nu_vtx_inCCInclusiveTPC", &reco_nu_vtx_inCCInclusiveTPC);
  theTree->SetBranchAddress("reco_track_end_inCCInclusiveTPC", &reco_track_end_inCCInclusiveTPC);
  theTree->SetBranchAddress("reco_track_ndaughters", &reco_track_ndaughters);
  theTree->SetBranchAddress("reco_track_daughter_vtx_in5cmTPC", &reco_track_daughter_vtx_in5cmTPC);
  theTree->SetBranchAddress("reco_track_daughter_end_in5cmTPC", &reco_track_daughter_end_in5cmTPC);
  //theTree->SetBranchAddress("", &);

  TH1F * h_BDT_ka = new TH1F("BDT_ka", "; BDT Response; Efficiency", 200, -1, 1);
  TH1F * h_BDT_all = new TH1F("BDT_all", "; BDT Response; Efficiency", 200, -1, 1);
  TH1F * h_eff_left = new TH1F("BDT_track_ka1", "; BDT Response; Efficiency", 200, -1, 1);
  TH1F * h_pur_left = new TH1F("BDT_track_ka2", "; BDT Response; Purity", 200, -1, 1);
  TH1F * h_etp_left = new TH1F("BDT_track_ka3", "; BDT Response; Efficiency * Purity", 200, -1, 1);
  TH1F * h_eff_right = new TH1F("BDT_track_k4a", "; BDT Response; Efficiency", 200, -1, 1);
  TH1F * h_pur_right = new TH1F("BDT_track_k56a", "; BDT Response; Purity", 200, -1, 1);
  TH1F * h_etp_right = new TH1F("BDT_track_ka6", "; BDT Response; Efficiency * Purity", 200, -1, 1);
  gStyle->SetOptStat(0);


  // Efficiency calculator for cut method
  Int_t    nSelCutsGA = 0;
  Double_t effS       = 0.7;
  
  std::vector<Float_t> vecVar(16); // vector for EvaluateMVA tests
  
  std::cout << "--- Processing: " << theTree->GetEntries() << " events" << std::endl;
  TStopwatch sw;
  sw.Start();
  for (Long64_t ievt=0; ievt<theTree->GetEntries();ievt++) {
    
    //if (ievt%1000 == 0) std::cout << "--- ... Processing event: " << ievt << std::endl;
    
    theTree->GetEntry(ievt);

    /*    
    reco_track_chi2ka_pl2R = reco_track_chi2ka_pl2;
    reco_track_chi2pr_pl2R = reco_track_chi2pr_pl2;
    reco_track_chi2pi_pl2R = reco_track_chi2pi_pl2;
    reco_track_chi2mu_pl2R = reco_track_chi2mu_pl2;
    reco_track_daughter_chi2ka_pl2R = reco_track_daughter_chi2ka_pl2;
    reco_track_daughter_chi2pr_pl2R = reco_track_daughter_chi2pr_pl2;
    reco_track_daughter_chi2pi_pl2R = reco_track_daughter_chi2pi_pl2;
    reco_track_daughter_chi2mu_pl2R = reco_track_daughter_chi2mu_pl2;
    reco_track_llrpid_3plR = reco_track_llrpid_3pl;
    reco_track_llrpid_k_3plR = reco_track_llrpid_k_3pl;
    reco_track_daughter_llrpid_3plR = reco_track_daughter_llrpid_3pl;
    reco_track_daughter_llrpid_k_3plR = reco_track_daughter_llrpid_k_3pl;
    reco_track_lengthR = reco_track_length;
    reco_track_daughter_lengthR = reco_track_daughter_length;
    reco_track_daughter_distanceR = reco_track_daughter_distance;
    reco_track_daughter_vtx_distanceR = reco_track_daughter_vtx_distance;
    */
    //cout << reco_track_true_pdgR << endl;
    //cout << reco_track_daughter_true_pdgR << endl;
    
    
    // Return the MVA outputs and fill into histograms
    
    if (Use["CutsGA"]) {
      // Cuts is a special case: give the desired signal efficienciy
      Bool_t passed = reader->EvaluateMVA( "CutsGA method", effS );
      if (passed) nSelCutsGA++;
    }

    if (Use["Likelihood"   ])   histLk     ->Fill( reader->EvaluateMVA( "Likelihood method"    ) );
    if (Use["LikelihoodD"  ])   histLkD    ->Fill( reader->EvaluateMVA( "LikelihoodD method"   ) );
    if (Use["LikelihoodPCA"])   histLkPCA  ->Fill( reader->EvaluateMVA( "LikelihoodPCA method" ) );
    if (Use["LikelihoodKDE"])   histLkKDE  ->Fill( reader->EvaluateMVA( "LikelihoodKDE method" ) );
    if (Use["LikelihoodMIX"])   histLkMIX  ->Fill( reader->EvaluateMVA( "LikelihoodMIX method" ) );
    if (Use["PDERS"        ])   histPD     ->Fill( reader->EvaluateMVA( "PDERS method"         ) );
    if (Use["PDERSD"       ])   histPDD    ->Fill( reader->EvaluateMVA( "PDERSD method"        ) );
    if (Use["PDERSPCA"     ])   histPDPCA  ->Fill( reader->EvaluateMVA( "PDERSPCA method"      ) );
    if (Use["KNN"          ])   histKNN    ->Fill( reader->EvaluateMVA( "KNN method"           ) );
    if (Use["HMatrix"      ])   histHm     ->Fill( reader->EvaluateMVA( "HMatrix method"       ) );
    if (Use["Fisher"       ])   histFi     ->Fill( reader->EvaluateMVA( "Fisher method"        ) );
    if (Use["FisherG"      ])   histFiG    ->Fill( reader->EvaluateMVA( "FisherG method"       ) );
    if (Use["BoostedFisher"])   histFiB    ->Fill( reader->EvaluateMVA( "BoostedFisher method" ) );
    if (Use["LD"           ])   histLD     ->Fill( reader->EvaluateMVA( "LD method"            ) );
    if (Use["MLP"          ])   histNn     ->Fill( reader->EvaluateMVA( "MLP method"           ) );
    if (Use["MLPBFGS"      ])   histNnbfgs ->Fill( reader->EvaluateMVA( "MLPBFGS method"       ) );
    if (Use["MLPBNN"       ])   histNnbnn  ->Fill( reader->EvaluateMVA( "MLPBNN method"        ) );
    if (Use["CFMlpANN"     ])   histNnC    ->Fill( reader->EvaluateMVA( "CFMlpANN method"      ) );
    if (Use["TMlpANN"      ])   histNnT    ->Fill( reader->EvaluateMVA( "TMlpANN method"       ) );
    if (Use["DNN_GPU"      ])   histDnnGpu ->Fill( reader->EvaluateMVA( "DNN_GPU method"       ) );
    if (Use["DNN_CPU"      ])   histDnnCpu ->Fill( reader->EvaluateMVA( "DNN_CPU method"       ) );
    //if (Use["BDT"          ])   histBdt    ->Fill( mvaValue );

    if (Use["BDT"          ]){
      histBdt    ->Fill( reader->EvaluateMVA( "BDT method"           ) );

      //if(true_nu_vtx_inCCInclusiveTPCR==1 && true_kaon_end_inCCInclusiveTPCR==1 && true_kaon_daughter_end_in5cmTPCR==1) h_BDT_all->Fill( reader->EvaluateMVA("BDT method") );
      //if(true_nu_vtx_inCCInclusiveTPCR==1) 
      h_BDT_all->Fill( reader->EvaluateMVA("BDT method") );

      //if(reco_track_true_pdgR==321 && (reco_track_daughter_true_pdgR==-13 || reco_track_daughter_true_pdgR==211)){
      //if(true_nu_pdgR==14 && true_nu_ccncR==0 && true_kaon_keR>=0){
      if(true_nu_pdgR==14 && true_nu_ccncR==0 && true_kaon_keR>=0 && true_nu_vtx_inCCInclusiveTPCR==1 && true_kaon_end_inCCInclusiveTPCR==1 && true_kaon_daughter_end_in5cmTPCR==1 && reco_track_true_pdgR==321){
      //if(reco_track_true_pdgR==321 && (reco_track_daughter_true_pdgR==-13 || reco_track_daughter_true_pdgR==211) && true_nu_vtx_inCCInclusiveTPCR==1 && true_kaon_end_inCCInclusiveTPCR==1 && true_kaon_daughter_end_in5cmTPCR==1 && reco_track_true_pdgR==321){

      //if(true_nu_pdgR==14 && true_nu_ccncR==0 && true_kaon_keR>=0 && true_nu_vtx_inCCInclusiveTPCR==1 && true_kaon_end_inCCInclusiveTPCR==1 && true_kaon_daughter_end_in5cmTPCR==1){
      //if(true_nu_pdgR==14 && true_nu_ccncR==0 && true_kaon_keR>=0){
	h_BDT_ka->Fill( reader->EvaluateMVA("BDT method") );
	/*
	if(reader->EvaluateMVA("BDT method")<0){
	  cout << reader->EvaluateMVA("BDT method") << endl;
	  cout << "track: " << reco_track_true_pdgR << ", daughter: " << reco_track_daughter_true_pdgR << endl;
	  cout << "true_nu_pdg: " << true_nu_pdgR << ", true_nu_mode: " << true_nu_modeR << ", true_nu_ccnc: " << true_nu_ccncR << ", true_kaon_ke: " << true_kaon_keR << endl;
	  cout << " " << endl;
	  }
	*/
      }
      
      //if(reco_track_true_pdgR==321 && (reco_track_daughter_true_pdgR==-13 || reco_track_daughter_true_pdgR==211)) h_sig->Fill( reader->EvaluateMVA("BDT method") );
      //if(true_nu_pdgR==14 && true_nu_ccncR==0 && true_kaon_keR>=0) h_sig->Fill( reader->EvaluateMVA("BDT method") );
      //else h_bg->Fill( reader->EvaluateMVA("BDT method") );

      //if(true_nu_pdgR==14 && true_nu_ccncR==0 && true_kaon_keR>=0) h_sig->Fill( reader->EvaluateMVA("BDT method") );
      //if(true_nu_pdgR==14 && true_nu_ccncR==0 && true_kaon_keR>=0 && true_nu_vtx_inCCInclusiveTPCR==1 && true_kaon_end_inCCInclusiveTPCR==1 && true_kaon_daughter_end_in5cmTPCR==1 && reco_track_true_pdgR==321) h_sig->Fill( reader->EvaluateMVA("BDT method") ); 
      if(true_nu_pdgR==14 && (true_kaon_end_processR == 0 || true_kaon_end_processR == 1) && true_nu_ccncR==0 && true_kaon_keR>=0 && true_nu_vtx_inCCInclusiveTPCR==1 && true_kaon_end_inCCInclusiveTPCR==1 && true_kaon_daughter_end_in5cmTPCR==1 && reco_track_true_pdgR==321) h_sig->Fill( reader->EvaluateMVA("BDT method") );
      //if(true_nu_pdgR==14 && true_nu_ccncR==0 && true_kaon_keR>=0 && true_nu_vtx_inCCInclusiveTPCR==1 && true_kaon_end_inCCInclusiveTPCR==1 && true_kaon_daughter_end_in5cmTPCR==1 && reco_track_true_pdgR==321) h_sig->Fill( reader->EvaluateMVA("BDT method") ); 
      //if((reco_track_daughter_true_pdgR==211 || reco_track_daughter_true_pdgR==-13) && reco_track_true_pdgR==321) h_sig->Fill( reader->EvaluateMVA("BDT method") ); 
      //if(reco_track_daughter_chi2ka_pl2<14 && reco_track_daughter_chi2pr_pl2>5) h_sig->Fill( reader->EvaluateMVA("BDT method") ); 
      else h_bg->Fill( reader->EvaluateMVA("BDT method") );

      if(reco_track_true_pdgR==321) BDT_track_ka->Fill( reader->EvaluateMVA("BDT method") );
      else if(reco_track_true_pdgR==13) BDT_track_mu->Fill( reader->EvaluateMVA("BDT method") );
      else if(reco_track_true_pdgR==211) BDT_track_pi->Fill( reader->EvaluateMVA("BDT method") );
      else if(reco_track_true_pdgR==2212) BDT_track_pr->Fill( reader->EvaluateMVA("BDT method") );
      else BDT_track_ot->Fill( reader->EvaluateMVA("BDT method") );

      if(reco_track_daughter_true_pdgR==-13) BDT_daughter_mu->Fill( reader->EvaluateMVA("BDT method") );
      else if(reco_track_daughter_true_pdgR==211) BDT_daughter_pi->Fill( reader->EvaluateMVA("BDT method") );
      else if(reco_track_daughter_true_pdgR==2212) BDT_daughter_pr->Fill( reader->EvaluateMVA("BDT method") );
      else BDT_daughter_ot->Fill( reader->EvaluateMVA("BDT method") );

      
      //if(reader->EvaluateMVA("BDT method")>0.21){
      if(true_nu_pdgR==14 && true_nu_ccncR==0 && true_kaon_keR>=0 && true_nu_vtx_inCCInclusiveTPCR==1 && true_kaon_end_inCCInclusiveTPCR==1 && true_kaon_daughter_end_in5cmTPCR==1 && ( true_kaon_end_processR == 0 || true_kaon_end_processR == 1 ) && reader->EvaluateMVA("BDT method")>=0.28){

      //if(reader->EvaluateMVA("BDT method")<=0.28 && reco_track_true_pdgR==321){
      //if(true_nu_pdgR==14 && true_nu_ccncR==0 && true_kaon_keR>=0 && reco_track_true_pdgR==321){
      //cout << "true_kaon_end_process: " << true_kaon_end_processR << endl;
      //if(true_nu_pdgR==14 && true_nu_ccncR==0 && true_kaon_keR>=0 && true_nu_vtx_inCCInclusiveTPCR==1 && true_kaon_end_inCCInclusiveTPCR==1 && true_kaon_daughter_end_in5cmTPCR==1 && ( true_kaon_end_processR == 0 || true_kaon_end_processR == 1 ) && reader->EvaluateMVA("BDT method")<=0.28){

      //if(reco_track_chi2ka_pl2<15 && reco_track_chi2pr_pl2>5 && reco_track_daughter_chi2pr_pl2>60 && reco_track_daughter_length>40 && reco_track_daughter_vtx_in5cmTPC==1 && reco_track_daughter_end_in5cmTPC==1){
      //if(reco_track_chi2ka_pl2<15 && reco_track_chi2pr_pl2>7 && reco_track_daughter_chi2pr_pl2>60 && reco_track_daughter_length>40 &&reco_nu_vtx_inCCInclusiveTPC==1 &&  reco_track_end_inCCInclusiveTPC==1 && reco_track_daughter_end_in5cmTPC==1){
      //if(reco_track_chi2ka_3pl<15 && reco_track_chi2pr_3pl>14 && reco_track_daughter_chi2pr_3pl>95 && reco_track_daughter_length>40 &&reco_nu_vtx_inCCInclusiveTPC==1 &&  reco_track_end_inCCInclusiveTPC==1 && reco_track_daughter_end_in5cmTPC==1){
      //if(reco_track_chi2ka_pl2<15 && reco_track_chi2pr_pl2>5 && reco_track_daughter_chi2pr_pl2>60 && reco_track_daughter_length>40){
      //if(reco_track_llrpid_k_3pl>-0.1 && reco_track_daughter_chi2pr_pl2>60 && reco_track_daughter_length>40 &&reco_nu_vtx_inCCInclusiveTPC==1 &&  reco_track_end_inCCInclusiveTPC==1 && reco_track_daughter_end_in5cmTPC==1){
	//if(true_nu_vtx_inCCInclusiveTPCR==1 && true_kaon_end_inCCInclusiveTPCR==1 && true_kaon_daughter_end_in5cmTPCR==1){

      //if(reco_track_chi2ka_pl2<10 && reco_track_chi2pr_pl2>8 && reco_track_daughter_chi2pr_pl2>60 && reco_track_daughter_length>40 &&reco_nu_vtx_inCCInclusiveTPC==1 &&  reco_track_end_inCCInclusiveTPC==1 && reco_track_daughter_end_in5cmTPC==1){

	/*
      if(
	 (runR==6521 && subrunR==32   && eventnumR==1610 ) ||
	 (runR==6766 && subrunR==91   && eventnumR==4591 ) ||
	 (runR==6776 && subrunR==206  && eventnumR==10345) ||
	 (runR==7006 && subrunR==453  && eventnumR==22669) ||
	 (runR==6752 && subrunR==100  && eventnumR==5036 ) 
	 ){
	*/

	  cout << "track: " << reco_track_true_pdgR << ", daughter: " << reco_track_daughter_true_pdgR << endl;
	  cout << "BDT: " << reader->EvaluateMVA("BDT method") << ", run: " << runR << ", subrun: " << subrunR << ", event: " << eventnumR << ", true_nu_pdg: " << true_nu_pdgR << ", true_nu_mode: " << true_nu_modeR << ", true_lepton_pdg: " << true_lepton_pdgR << endl;
	  cout << "true_nu_pdg: " << true_nu_pdgR << ", true_nu_ccnc: " << true_nu_ccncR << ", true_kaon_ke" << true_kaon_keR << ", true_nu_vtx_inCCInclusiveTPC: " << true_nu_vtx_inCCInclusiveTPCR << ", true_kaon_daughter_end_in5cmTPC: " << true_kaon_daughter_end_in5cmTPCR << ", true_kaon_daughter_end_in5cmTPC: " << true_kaon_daughter_end_in5cmTPCR << endl;
	  cout << "true_kaon_length: " << true_kaon_lengthR << ", reco_track_length: " << reco_track_length << endl;
	  //cout << "true_kaon_E: " << true_kaon_keR << ", reco_track_E: " << reco_track_ke << endl;
	  
	  BDTcut++;
	  cout << " " << endl;
	  cout << BDTcut << endl;
	  //}
	  //}  
      }
    }


    
    if (Use["BDTD"          ]){
      histBdtD    ->Fill( reader->EvaluateMVA( "BDTD method"           ) );

      h_BDT_all->Fill( reader->EvaluateMVA("BDTD method") );
      //if(reco_track_true_pdgR==321 && (reco_track_daughter_true_pdgR==-13 || reco_track_daughter_true_pdgR==211)) 
      if(true_nu_pdgR==14 && true_nu_ccncR==0 && true_kaon_keR>=0 && true_nu_vtx_inCCInclusiveTPCR==1 && true_kaon_end_inCCInclusiveTPCR==1 && true_kaon_daughter_end_in5cmTPCR==1 && reco_track_true_pdgR==321) h_BDT_ka->Fill( reader->EvaluateMVA("BDTD method") );


      //if(reco_track_true_pdgR==321 && (reco_track_daughter_true_pdgR==-13 || reco_track_daughter_true_pdgR==211)) h_sig->Fill( reader->EvaluateMVA("BDT method") );
      if(true_nu_pdgR==14 && true_nu_ccncR==0 && true_kaon_keR>=0 && true_nu_vtx_inCCInclusiveTPCR==1 && true_kaon_end_inCCInclusiveTPCR==1 && true_kaon_daughter_end_in5cmTPCR==1 && reco_track_true_pdgR==321) h_sig->Fill( reader->EvaluateMVA("BDTD method") );
      else h_bg->Fill( reader->EvaluateMVA("BDTD method") );

      if(reco_track_true_pdgR==321) BDT_track_ka->Fill( reader->EvaluateMVA("BDTD method") );
      else if(reco_track_true_pdgR==13) BDT_track_mu->Fill( reader->EvaluateMVA("BDTD method") );
      else if(reco_track_true_pdgR==211) BDT_track_pi->Fill( reader->EvaluateMVA("BDTD method") );
      else if(reco_track_true_pdgR==2212) BDT_track_pr->Fill( reader->EvaluateMVA("BDTD method") );
      else BDT_track_ot->Fill( reader->EvaluateMVA("BDTD method") );

      if(reco_track_daughter_true_pdgR==-13) BDT_daughter_mu->Fill( reader->EvaluateMVA("BDTD method") );
      else if(reco_track_daughter_true_pdgR==211) BDT_daughter_pi->Fill( reader->EvaluateMVA("BDTD method") );
      else if(reco_track_daughter_true_pdgR==2212) BDT_daughter_pr->Fill( reader->EvaluateMVA("BDTD method") );
      else BDT_daughter_ot->Fill( reader->EvaluateMVA("BDTD method") );
      
    }
 

   if (Use["BDTF"          ]){
      histBdtF    ->Fill( reader->EvaluateMVA( "BDTF method"           ) );

      h_BDT_all->Fill( reader->EvaluateMVA("BDTF method") );
      //if(reco_track_true_pdgR==321 && (reco_track_daughter_true_pdgR==-13 || reco_track_daughter_true_pdgR==211)) 
      if(true_nu_pdgR==14 && true_nu_ccncR==0 && true_kaon_keR>=0 && true_nu_vtx_inCCInclusiveTPCR==1 && true_kaon_end_inCCInclusiveTPCR==1 && true_kaon_daughter_end_in5cmTPCR==1 && reco_track_true_pdgR==321) h_BDT_ka->Fill( reader->EvaluateMVA("BDTF method") );


      //if(reco_track_true_pdgR==321 && (reco_track_daughter_true_pdgR==-13 || reco_track_daughter_true_pdgR==211)) h_sig->Fill( reader->EvaluateMVA("BDT method") );
      //if(true_nu_pdgR==14 && true_nu_ccncR==0 && true_kaon_keR>=0 && true_nu_vtx_inCCInclusiveTPCR==1 && true_kaon_end_inCCInclusiveTPCR==1 && true_kaon_daughter_end_in5cmTPCR==1 && reco_track_true_pdgR==321) h_sig->Fill( reader->EvaluateMVA("BDTF method") );
      if(true_nu_pdgR==14 && true_nu_ccncR==0 && (reco_track_daughter_true_pdgR==-13 || reco_track_daughter_true_pdgR==211) && true_kaon_keR>=0 && true_nu_vtx_inCCInclusiveTPCR==1 && true_kaon_end_inCCInclusiveTPCR==1 && true_kaon_daughter_end_in5cmTPCR==1 && reco_track_true_pdgR==321) h_sig->Fill( reader->EvaluateMVA("BDTF method") );
      else h_bg->Fill( reader->EvaluateMVA("BDTF method") );

      if(reco_track_true_pdgR==321) BDT_track_ka->Fill( reader->EvaluateMVA("BDTF method") );
      else if(reco_track_true_pdgR==13) BDT_track_mu->Fill( reader->EvaluateMVA("BDTF method") );
      else if(reco_track_true_pdgR==211) BDT_track_pi->Fill( reader->EvaluateMVA("BDTF method") );
      else if(reco_track_true_pdgR==2212) BDT_track_pr->Fill( reader->EvaluateMVA("BDTF method") );
      else BDT_track_ot->Fill( reader->EvaluateMVA("BDTF method") );

      if(reco_track_daughter_true_pdgR==-13) BDT_daughter_mu->Fill( reader->EvaluateMVA("BDTF method") );
      else if(reco_track_daughter_true_pdgR==211) BDT_daughter_pi->Fill( reader->EvaluateMVA("BDTF method") );
      else if(reco_track_daughter_true_pdgR==2212) BDT_daughter_pr->Fill( reader->EvaluateMVA("BDTF method") );
      else BDT_daughter_ot->Fill( reader->EvaluateMVA("BDTF method") );
      
    }
    

    if (Use["BDTG"         ])   histBdtG   ->Fill( reader->EvaluateMVA( "BDTG method"          ) );
    if (Use["BDTB"         ])   histBdtB   ->Fill( reader->EvaluateMVA( "BDTB method"          ) );
    //if (Use["BDTD"         ])   histBdtD   ->Fill( reader->EvaluateMVA( "BDTD method"          ) );
    //if (Use["BDTF"         ])   histBdtF   ->Fill( reader->EvaluateMVA( "BDTF method"          ) );
    if (Use["RuleFit"      ])   histRf     ->Fill( reader->EvaluateMVA( "RuleFit method"       ) );
    if (Use["SVM_Gauss"    ])   histSVMG   ->Fill( reader->EvaluateMVA( "SVM_Gauss method"     ) );
    if (Use["SVM_Poly"     ])   histSVMP   ->Fill( reader->EvaluateMVA( "SVM_Poly method"      ) );
    if (Use["SVM_Lin"      ])   histSVML   ->Fill( reader->EvaluateMVA( "SVM_Lin method"       ) );
    if (Use["FDA_MT"       ])   histFDAMT  ->Fill( reader->EvaluateMVA( "FDA_MT method"        ) );
    if (Use["FDA_GA"       ])   histFDAGA  ->Fill( reader->EvaluateMVA( "FDA_GA method"        ) );
    if (Use["Category"     ])   histCat    ->Fill( reader->EvaluateMVA( "Category method"      ) );
    if (Use["Plugin"       ])   histPBdt   ->Fill( reader->EvaluateMVA( "P_BDT method"         ) );
    
    // Retrieve also per-event error
    if (Use["PDEFoam"]) {
      Double_t val = reader->EvaluateMVA( "PDEFoam method" );
      Double_t err = reader->GetMVAError();
      histPDEFoam   ->Fill( val );
      histPDEFoamErr->Fill( err );
      if (err>1.e-50) histPDEFoamSig->Fill( val/err );
    }
    
    // Retrieve probability instead of MVA output
    if (Use["Fisher"])   {
      probHistFi  ->Fill( reader->GetProba ( "Fisher method" ) );
      rarityHistFi->Fill( reader->GetRarity( "Fisher method" ) );
    }

  }
  
  // Get elapsed time
  sw.Stop();
  std::cout << "--- End of event loop: "; sw.Print();
  
  // Get efficiency for cuts classifier
  if (Use["CutsGA"]) std::cout << "--- Efficiency for CutsGA method: " << double(nSelCutsGA)/theTree->GetEntries()
			       << " (for a required signal efficiency of " << effS << ")" << std::endl;
  
  if (Use["CutsGA"]) {
    
    // test: retrieve cuts for particular signal efficiency
    // CINT ignores dynamic_casts so we have to use a cuts-secific Reader function to acces the pointer
    TMVA::MethodCuts* mcuts = reader->FindCutsMVA( "CutsGA method" ) ;
    
    if (mcuts) {
      std::vector<Double_t> cutsMin;
      std::vector<Double_t> cutsMax;
      mcuts->GetCuts( 0.7, cutsMin, cutsMax );
      std::cout << "--- -------------------------------------------------------------" << std::endl;
      std::cout << "--- Retrieve cut values for signal efficiency of 0.7 from Reader" << std::endl;
      for (UInt_t ivar=0; ivar<cutsMin.size(); ivar++) {
	std::cout << "... Cut: "
		  << cutsMin[ivar]
		  << " < \""
		  << mcuts->GetInputVar(ivar)
		  << "\" <= "
		  << cutsMax[ivar] << std::endl;
      }
      std::cout << "--- -------------------------------------------------------------" << std::endl;
    }
  }


  h_eff_left->Reset();
  h_pur_left->Reset();
  h_etp_left->Reset();
  h_eff_right->Reset();
  h_pur_right->Reset();
  h_etp_right->Reset();

  h_eff_left->SetLineColor(kRed);
  h_pur_left->SetLineColor(kBlue);
  h_etp_left->SetLineColor(kBlack);
  h_eff_right->SetLineColor(kRed);
  h_pur_right->SetLineColor(kBlue);
  h_etp_right->SetLineColor(kBlack);

  int last_bin = 200;

  double den = h_BDT_ka->Integral(1,last_bin+1);
  //cout << "den: " << den << endl;
  //den = 95;//odd 30+31 //even 19+15
  den = 4705;//odd 30+31 //even 19+15
  for (int bin=1; bin<=last_bin+1; bin++) {
    double sig_left = h_BDT_ka->Integral(1,bin);
    double all_left = h_BDT_all->Integral(1,bin);
    double eff_left = den>0 ? sig_left/den : 0;
    double pur_left = all_left>0 ? sig_left/all_left : 0;
    double sig_right = h_BDT_ka->Integral(bin,last_bin+1);
    double all_right = h_BDT_all->Integral(bin,last_bin+1);
    double eff_right = den>0 ? sig_right/den : 0;
    double pur_right = all_right>0 ? sig_right/all_right : 0;
    h_eff_left->SetBinContent(bin,eff_left);
    h_pur_left->SetBinContent(bin,pur_left);
    h_etp_left->SetBinContent(bin,eff_left*pur_left);
    h_eff_right->SetBinContent(bin,eff_right);
    h_pur_right->SetBinContent(bin,pur_right);
    h_etp_right->SetBinContent(bin,eff_right*pur_right);
  }

  
  // Write histograms
  
  TFile *target  = new TFile( "TMVApp.root","RECREATE" );
  if (Use["Likelihood"   ])   histLk     ->Write();
  if (Use["LikelihoodD"  ])   histLkD    ->Write();
  if (Use["LikelihoodPCA"])   histLkPCA  ->Write();
  if (Use["LikelihoodKDE"])   histLkKDE  ->Write();
  if (Use["LikelihoodMIX"])   histLkMIX  ->Write();
  if (Use["PDERS"        ])   histPD     ->Write();
  if (Use["PDERSD"       ])   histPDD    ->Write();
  if (Use["PDERSPCA"     ])   histPDPCA  ->Write();
  if (Use["KNN"          ])   histKNN    ->Write();
  if (Use["HMatrix"      ])   histHm     ->Write();
  if (Use["Fisher"       ])   histFi     ->Write();
  if (Use["FisherG"      ])   histFiG    ->Write();
  if (Use["BoostedFisher"])   histFiB    ->Write();
  if (Use["LD"           ])   histLD     ->Write();
  if (Use["MLP"          ])   histNn     ->Write();
  if (Use["MLPBFGS"      ])   histNnbfgs ->Write();
  if (Use["MLPBNN"       ])   histNnbnn  ->Write();
  if (Use["CFMlpANN"     ])   histNnC    ->Write();
  if (Use["TMlpANN"      ])   histNnT    ->Write();
  if (Use["DNN_GPU"]) histDnnGpu->Write();
  if (Use["DNN_CPU"]) histDnnCpu->Write();
  if (Use["BDT"          ])   histBdt    ->Write();
  if (Use["BDTG"         ])   histBdtG   ->Write();
  if (Use["BDTB"         ])   histBdtB   ->Write();
  if (Use["BDTD"         ])   histBdtD   ->Write();
  if (Use["BDTF"         ])   histBdtF   ->Write();
  if (Use["RuleFit"      ])   histRf     ->Write();
  if (Use["SVM_Gauss"    ])   histSVMG   ->Write();
  if (Use["SVM_Poly"     ])   histSVMP   ->Write();
  if (Use["SVM_Lin"      ])   histSVML   ->Write();
  if (Use["FDA_MT"       ])   histFDAMT  ->Write();
  if (Use["FDA_GA"       ])   histFDAGA  ->Write();
  if (Use["Category"     ])   histCat    ->Write();
  if (Use["Plugin"       ])   histPBdt   ->Write();
  
  // Write also error and significance histos
  if (Use["PDEFoam"]) { histPDEFoam->Write(); histPDEFoamErr->Write(); histPDEFoamSig->Write(); }
  
  // Write also probability hists
  if (Use["Fisher"]) { if (probHistFi != 0) probHistFi->Write(); if (rarityHistFi != 0) rarityHistFi->Write(); }

  //save histograms
  s_trk->Add(BDT_track_ka);
  s_trk->Add(BDT_track_pr);
  s_trk->Add(BDT_track_pi);
  s_trk->Add(BDT_track_mu);
  s_trk->Add(BDT_track_ot);

  s_dau->Add(BDT_daughter_pr);
  s_dau->Add(BDT_daughter_pi);
  s_dau->Add(BDT_daughter_mu);
  s_dau->Add(BDT_daughter_ot);

  s_sn->Add(h_sig);
  s_sn->Add(h_bg);

  target->cd();
  s_trk->Write();
  l->Write();

  target->cd();
  s_dau->Write();
  l_d->Write();

  target->cd();
  s_sn->Write();
  l_sn->Write();

  target->cd();
  h_sig->Write();

  target->cd();
  h_bg->Write();

  target->Close();

  c->SetLogy();
  s_trk->Draw();
  l->Draw(); 
  c->Print(output_pdf_bdt);

  s_dau->Draw();
  l_d->Draw(); 
  c->Print(output_pdf_bdt);

  s_sn->Draw();
  l_sn->Draw(); 
  c->Print(output_pdf_bdt);

  h_sig->SetFillColor(kBlack);

  s_trk->Draw();
  h_sig->Draw("same");
  l->AddEntry(h_sig, "True CCK^{+} in FV" , "f");
  l->Draw(); 
  c->Print(output_pdf_bdt);

  s_dau->Draw();
  h_sig->Draw("same");
  l_d->AddEntry(h_sig, "True CCK^{+} in FV" , "f");
  l_d->Draw(); 
  c->Print(output_pdf_bdt);

  TCanvas * c_left = new TCanvas();
  c_left->SetLogy();
  //h_eff_left->SetMinimum(0);
  h_eff_left->SetMaximum(1);
  h_eff_left->Draw("C");
  h_pur_left->Draw("C""same");
  h_etp_left->Draw("C""same");
  TLegend * l_left = new TLegend(0.65,0.7,0.85,0.85);
  l_left->AddEntry(h_eff_left,"Efficiency","l");
  l_left->AddEntry(h_pur_left,"Purity","l");
  l_left->AddEntry(h_etp_left,"Eff. #times Pur.","l");
  l_left->Draw();
  c_left->Print(output_pdf_bdt);

  TCanvas * c_right = new TCanvas();
  c_right->SetLogy();
  //h_eff_right->SetMinimum(0);
  h_eff_right->SetMaximum(2);
  h_eff_right->Draw("C");
  h_pur_right->Draw("C""same");
  h_etp_right->Draw("C""same");
  TLegend * l_right = new TLegend(0.15,0.7,0.30,0.85);
  l_right->AddEntry(h_eff_right,"Efficiency","l");
  l_right->AddEntry(h_pur_right,"Purity","l");
  l_right->AddEntry(h_etp_right,"Eff. #times Pur.","l");
  l_right->Draw();
  c_right->Print(output_pdf_bdt);


  cout << "cut at 0.29: " << h_etp_right->GetBinContent(129) << " " << h_eff_right->GetBinContent(129) << " " << h_pur_right->GetBinContent(129) << endl;

  cout << "max: " << h_etp_right->GetMaximum() << " at " << h_etp_right->GetMaximumBin() << " eff: " <<  h_eff_right->GetBinContent(h_etp_right->GetMaximumBin()) << " pur: " << h_pur_right->GetBinContent(h_etp_right->GetMaximumBin()) << endl;
  cout << " " << endl;

  c->Print(Form("%s]", output_pdf_bdt.Data())); 

  std::cout << "--- Created root file: \"TMVApp.root\" containing the MVA output histograms" << std::endl;
  
  delete reader;
  
  std::cout << "==> TMVAClassificationApplication is done!" << std::endl << std::endl;
}

int main( int argc, char** argv )
{
  TString methodList;
  for (int i=1; i<argc; i++) {
    TString regMethod(argv[i]);
    if(regMethod=="-b" || regMethod=="--batch") continue;
    if (!methodList.IsNull()) methodList += TString(",");
    methodList += regMethod;
  }
  TMVAClassificationApplication_BDTcut_addval(methodList);
  return 0;
}

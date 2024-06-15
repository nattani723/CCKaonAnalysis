#include "RebuildTrackHist.h"

void Initialise()
{
  gStyle->SetCanvasColor(0);
  gStyle->SetFrameFillColor(0);
  gStyle->SetFrameLineColor(1);
  gStyle->SetFrameBorderMode(0);
  gStyle->SetPadBorderMode(0);
  gStyle->SetCanvasBorderMode(0);
  gStyle->SetStatColor(0);
  gStyle->SetTitleFillColor(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetPalette(1);
  gStyle->SetOptStat(0);
  gStyle->SetOptFit(112);
  gStyle->SetFillStyle(4000);
  gStyle->SetLineWidth(3);

  nentry=0;
  reco_true_length_mu=0;
  reco_true_length_pi=0;
  reco_old_true_length_mu=0;
  reco_old_true_length_pi=0;
}

void RebuildTrackHist()
{
  //RebuildTrackHist("/exp/uboone/app/users/taniuchi/KaonAna/KaonAnlysis/Ana/track_tuple/refine_debug_2.root", "test2.pdf", "3pl");
  //RebuildTrackHist("/exp/uboone/data/users/taniuchi/taniuchi/pandora_alg/ana_old/scan_fhc_run1_assok_match_roi20_debug6_max15_initial101_lsdis15_spineall_nospine_discon075_daughter40_lscon_ls_open23_peak3_min5_closest8_final50_prod_tracktuple.root", "test2.pdf", "3pl", "All", true);
  //RebuildTrackHist("/exp/uboone/app/users/taniuchi/51_pandora/CCKaonAnalysis/tool/track_tuple/rootfile/core.root", "core.pdf", "3pl", "All", true);
  //RebuildTrackHist("/exp/uboone/app/users/taniuchi/51_pandora/CCKaonAnalysis/tool/track_tuple/rootfile/assok_refined_KrecoAlg_track_test.root", "test.pdf", "3pl", "All", true);

  //RebuildTrackHist("/exp/uboone/data/users/taniuchi/taniuchi/pandora_alg/ana/assok_rerunPID_tracktuple_test.root",  "Plots/assocK_all.pdf", "3pl", "All", true);
  //RebuildTrackHist("/exp/uboone/data/users/taniuchi/taniuchi/pandora_alg/ana/assok_rerunPID_tracktuple_test.root",  "Plots/assocK_IsK.pdf", "3pl", "IsK", true);
  //RebuildTrackHist("/exp/uboone/data/users/taniuchi/taniuchi/pandora_alg/ana/assok_rerunPID_tracktuple_test.root",  "Plots/assocK_NotK.pdf", "3pl", "NotK", true);

  //RebuildTrackHist("/exp/uboone/data/users/taniuchi/taniuchi/pandora_alg/ana/singlek_rerunPID_tracktuple.root",  "Plots/singleK_all.pdf", "3pl", "All", true);
  //RebuildTrackHist("/exp/uboone/data/users/taniuchi/taniuchi/pandora_alg/ana/singlek_rerunPID_tracktuple.root",  "Plots/singleK_IsK.pdf", "3pl", "IsK", true);
  //RebuildTrackHist("/exp/uboone/data/users/taniuchi/taniuchi/pandora_alg/ana/singlek_rerunPID_tracktuple.root",  "Plots/singleK_NotK.pdf", "3pl", "NotK", true);

  //RebuildTrackHist("cck.list",  "Plots/CCK_all.pdf", "3pl", "All", true);
  //RebuildTrackHist("cck.list",  "Plots/CCK_IsK.pdf", "3pl", "IsK", true);
  //RebuildTrackHist("cck.list",  "Plots/CCK_NotK.pdf", "3pl", "NotK", true);

  //RebuildTrackHist("numi.list",  "Plots/NuMI_all.pdf", "3pl", "All", true);
  //RebuildTrackHist("numi.list",  "Plots/NuMI_IsK.pdf", "3pl", "IsK", true);
  RebuildTrackHist("numi.list",  "Plots/NuMI_NotK.pdf", "3pl", "NotK", true);

}

void RebuildTrackHist(TString input_name, TString output_name, TString pl, TString mode, bool IsHybrid)
{
  TGaxis::SetMaxDigits(3);
  gErrorIgnoreLevel = kWarning;

  TChain *chain_TMVA = new TChain("dataset_tree325_node4_depth4_beta60_frac12_ncut5_addspec/TestTree");
  TChain *chain_Standard = new TChain("CCKaonTracks");

  if (input_name.EndsWith(".root")) {
    // Determine which chain to add to based on file name
    if (input_name.Contains("TMVA")) {
      chain_TMVA->Add(input_name);
    } else {
      chain_Standard->Add(input_name);
    }
  } else if (input_name.EndsWith(".list")) {
    std::ifstream listFile(input_name.Data());
    std::string line;
    while (std::getline(listFile, line)) {
      if (!line.empty()) {
	if (line.find("TMVA") != std::string::npos) {
	  chain_TMVA->Add(line.c_str());
	} else {
	  chain_Standard->Add(line.c_str());
	}
      }
    }
  } else {
    std::cout << "Unsupported file type or path. Exiting." << std::endl;
    return;
  }

  TFile * f = new TFile(input_name);

  Initialise;

  TCanvas * c = new TCanvas("c", "c", 800, 600);
  c->SetFillStyle(4000);
  gStyle->SetOptStat(0);
  c->Print(Form("%s[", output_name.Data()));

  //c->Print(Form("%s[", output_name.Data()));

  // Determine which chain to use based on some criteria, e.g., number of entries or priority
  TChain* activeChain = (chain_TMVA->GetEntries() > 0) ? chain_TMVA : chain_Standard;
  //GeneratePlots(pl, mode, IsHybrid, c, output_name, activeChain);
  GeneratePlots(f, pl, mode, IsHybrid, c, output_name, activeChain);
  
  c->Print(Form("%s]", output_name.Data()));
  //c->Print(Form("%s]", output_name.Data()));

}

void GeneratePlots(TFile *f, TString pl, TString mode, bool IsHybrid, TCanvas* &c, TString output_name, TChain *chain)
{

  if (!chain || chain->GetEntries() == 0) {
    std::cout << "No entries in the chain or chain is null." << std::endl;
    return;
  }

  TTree * t = chain;
  //TTree * t;
  //t = chain;

  LoadTree(f, pl, t);
  SetHistos();
  SetHistosStyle();

  cout << "nentry: " << nentry << endl;
  for(int ientry=0; ientry<nentry; ++ientry){

    t->GetEntry(ientry);
    //if( fname.Contains("7Nov") || (fname.Contains("TMVA") && BDT>0.32)){
    FillPrimaryTrack();
    
    //if(reco_track_daughter_true_pdg==211 && std::abs(reco_track_daughter_length-true_dau_pip_length)<0.2*true_dau_pip_length))
    //add true track length 


    if(mode=="All"){	  
      FillOldTrackLength();
      if(IsHybrid) FillHybridTrackLength();
      else FillRebuiltTrackLength();
    }
    else if(mode=="IsK"){
      if(reco_track_true_pdg==321){
	FillOldTrackLength();
	if(IsHybrid) FillHybridTrackLength();
	else FillRebuiltTrackLength();
      }
    }
    else if(mode=="NotK"){
      if(reco_track_true_pdg!=321){
	FillOldTrackLength();
	if(IsHybrid) FillHybridTrackLength();
	else FillRebuiltTrackLength();
	
      }
    }
    
    if(pl=="pl2") FillPl2PID();
    else if(pl=="3pl") Fill3PlPID();
    
  }

  AddStackHistos();
  AddLegend();  
  DrawHistos(c, output_name);

  cout << "n0: " << n0 << ", " << "n1: " << n1 << ", " << "n2: " << n2 << ", " << "n3: " << n3 << ", " << "n4: " << n4 << ", " << "n5: " << n5 << endl;

  cout << "h_track_dau_ln_pr: " << h_track_dau_ln_pr->GetEntries() << endl;
  cout << "h_track_dau_ln_pi: " << h_track_dau_ln_pi->GetEntries() << endl;
  cout << "h_track_dau_ln_mu: " << h_track_dau_ln_mu->GetEntries() << endl;
  cout << "h_track_dau_ln_sh: " << h_track_dau_ln_sh->GetEntries() << endl;
  cout << "h_track_dau_ln_ot: " << h_track_dau_ln_ot->GetEntries() << endl;
  cout << endl;

  cout << "h_track_dau_ln_pr_hy: " << h_track_dau_ln_pr_hy->GetEntries() << endl;
  cout << "h_track_dau_ln_pi_hy: " << h_track_dau_ln_pi_hy->GetEntries() << endl;
  cout << "h_track_dau_ln_mu_hy: " << h_track_dau_ln_mu_hy->GetEntries() << endl;
  cout << "h_track_dau_ln_sh_hy: " << h_track_dau_ln_sh_hy->GetEntries() << endl;
  cout << "h_track_dau_ln_ot_hy: " << h_track_dau_ln_ot_hy->GetEntries() << endl;
  cout << endl;

  cout << "h_track_dau_old_ln_pr: " << h_track_dau_old_ln_pr->GetEntries() << endl;
  cout << "h_track_dau_old_ln_pi: " << h_track_dau_old_ln_pi->GetEntries() << endl;
  cout << "h_track_dau_old_ln_mu: " << h_track_dau_old_ln_mu->GetEntries() << endl;
  cout << "h_track_dau_old_ln_sh: " << h_track_dau_old_ln_sh->GetEntries() << endl;
  cout << "h_track_dau_old_ln_ot: " << h_track_dau_old_ln_ot->GetEntries() << endl;
  cout << endl;

  cout << "reco_old_true_length_mu: " << reco_old_true_length_mu << endl;
  cout << "reco_old_true_length_pi: " << reco_old_true_length_pi << endl;
  cout << "reco_true_length_mu: " << reco_true_length_mu << endl;
  cout << "reco_true_length_pi: " << reco_true_length_pi << endl;
  cout << "reco_true_length_mu_hy: " << reco_true_length_mu_hy << endl;
  cout << "reco_true_length_pi_hy: " << reco_true_length_pi_hy << endl;


  delete h_track_chi2ka_ka;
  delete h_track_chi2ka_pr;
  delete h_track_chi2ka_pi;
  delete h_track_chi2ka_mu;
  delete h_track_chi2ka_ot;
  delete h_track_chi2pr_ka;
  delete h_track_chi2pr_pr;
  delete h_track_chi2pr_pi;
  delete h_track_chi2pr_mu;
  delete h_track_chi2pr_ot;
  delete s_chi2ka;
  delete s_chi2pr;
}


void LoadTree(TFile *f, TString pl, TTree* &t){

  TString fname(f->GetName());


  /*
  //TTree * t;
  if(fname.Contains("TMVA")){
    t = (TTree*) f->Get("dataset_tree325_node4_depth4_beta60_frac12_ncut5_addspec/TestTree");
  }else{
    t = (TTree*) f->Get("CCKaonTracks");
  }
  */
  nentry = t->GetEntries();


  t->SetBranchAddress("true_nu_pdg", &true_nu_pdg);
  t->SetBranchAddress("true_nu_ccnc", &true_nu_ccnc);
  t->SetBranchAddress("true_kaon_ke", &true_kaon_ke);
  t->SetBranchAddress("true_kaon_end_process", &true_kaon_end_process);   
  t->SetBranchAddress("true_nu_vtx_inCCInclusiveTPC", &true_nu_vtx_inCCInclusiveTPC);
  t->SetBranchAddress("true_kaon_end_inCCInclusiveTPC", &true_kaon_end_inCCInclusiveTPC);
  t->SetBranchAddress("true_kaon_daughter_end_in5cmTPC", &true_kaon_daughter_end_in5cmTPC);
  t->SetBranchAddress("true_dau_pip_length", &true_dau_pip_length);
  t->SetBranchAddress("true_dau_muon_length", &true_dau_muon_length);

  t->SetBranchAddress("reco_track_true_pdg", &reco_track_true_pdg);
  t->SetBranchAddress("reco_track_daughter_true_pdg", &reco_track_daughter_true_pdg);
  t->SetBranchAddress("reco_track_daughter_old_true_pdg", &reco_track_daughter_old_true_pdg);
  if(fname.Contains("TMVA")) t->SetBranchAddress("BDT", &BDT);
  
  t->SetBranchAddress("reco_track_length", &reco_track_length);
  t->SetBranchAddress("reco_track_distance", &reco_track_distance);
  t->SetBranchAddress("reco_track_daughter_length", &reco_track_daughter_length);
  t->SetBranchAddress("reco_track_daughter_old_length", &reco_track_daughter_old_length);
  t->SetBranchAddress("reco_track_daughter_distance", &reco_track_daughter_distance);
  t->SetBranchAddress("reco_track_daughter_vtx_distance", &reco_track_daughter_vtx_distance);
  t->SetBranchAddress("true_kaon_length", &true_kaon_length);

  t->SetBranchAddress("reco_track_Bragg_fwd_ka_pl2", &reco_track_Bragg_fwd_ka_pl2);
  t->SetBranchAddress("reco_track_Bragg_fwd_pr_pl2", &reco_track_Bragg_fwd_pr_pl2);
  t->SetBranchAddress("reco_track_Bragg_fwd_pi_pl2", &reco_track_Bragg_fwd_pi_pl2);
  t->SetBranchAddress("reco_track_Bragg_fwd_mu_pl2", &reco_track_Bragg_fwd_mu_pl2);

  if(pl=="pl2"){
    //if(trdau.Contains("tra")){
      t->SetBranchAddress("reco_track_chi2ka_pl2", &reco_track_chi2ka_pl2);
      t->SetBranchAddress("reco_track_chi2pr_pl2", &reco_track_chi2pr_pl2);
      t->SetBranchAddress("reco_track_chi2pi_pl2", &reco_track_chi2pi_pl2);
      t->SetBranchAddress("reco_track_chi2mu_pl2", &reco_track_chi2mu_pl2);
      t->SetBranchAddress("reco_track_llrpid_3pl", &reco_track_llrpid_3pl);
      t->SetBranchAddress("reco_track_llrpid_k_3pl", &reco_track_llrpid_k_3pl);
      //}else{
      t->SetBranchAddress("reco_track_daughter_chi2ka_pl2", &reco_track_daughter_chi2ka_pl2);
      t->SetBranchAddress("reco_track_daughter_chi2pr_pl2", &reco_track_daughter_chi2pr_pl2);
      t->SetBranchAddress("reco_track_daughter_chi2pi_pl2", &reco_track_daughter_chi2pi_pl2);
      t->SetBranchAddress("reco_track_daughter_chi2mu_pl2", &reco_track_daughter_chi2mu_pl2);
      t->SetBranchAddress("reco_track_daughter_llrpid_3pl", &reco_track_daughter_llrpid_3pl);
      t->SetBranchAddress("reco_track_daughter_llrpid_k_3pl", &reco_track_daughter_llrpid_k_3pl);
      //}
  }

  if(pl=="3pl"){
    //if(trdau.Contains("tra")){
      t->SetBranchAddress("reco_track_chi2ka_3pl", &reco_track_chi2ka_3pl);
      t->SetBranchAddress("reco_track_chi2pr_3pl", &reco_track_chi2pr_3pl);
      t->SetBranchAddress("reco_track_chi2pi_3pl", &reco_track_chi2pi_3pl);
      t->SetBranchAddress("reco_track_chi2mu_3pl", &reco_track_chi2mu_3pl);
      t->SetBranchAddress("reco_track_llrpid_3pl", &reco_track_llrpid_3pl);
      t->SetBranchAddress("reco_track_llrpid_k_3pl", &reco_track_llrpid_k_3pl);
      //}else{
      t->SetBranchAddress("reco_track_daughter_chi2ka_3pl", &reco_track_daughter_chi2ka_3pl);
      t->SetBranchAddress("reco_track_daughter_chi2pr_3pl", &reco_track_daughter_chi2pr_3pl);
      t->SetBranchAddress("reco_track_daughter_chi2pi_3pl", &reco_track_daughter_chi2pi_3pl);
      t->SetBranchAddress("reco_track_daughter_chi2mu_3pl", &reco_track_daughter_chi2mu_3pl);
      t->SetBranchAddress("reco_track_daughter_llrpid_3pl", &reco_track_daughter_llrpid_3pl);
      t->SetBranchAddress("reco_track_daughter_llrpid_k_3pl", &reco_track_daughter_llrpid_k_3pl);

      t->SetBranchAddress("reco_track_daughter_old_chi2ka_3pl", &reco_track_daughter_old_chi2ka_3pl);
      t->SetBranchAddress("reco_track_daughter_old_chi2pr_3pl", &reco_track_daughter_old_chi2pr_3pl);
      t->SetBranchAddress("reco_track_daughter_old_chi2pi_3pl", &reco_track_daughter_old_chi2pi_3pl);
      t->SetBranchAddress("reco_track_daughter_old_chi2mu_3pl", &reco_track_daughter_old_chi2mu_3pl);
      t->SetBranchAddress("reco_track_daughter_old_llrpid_3pl", &reco_track_daughter_old_llrpid_3pl);
      t->SetBranchAddress("reco_track_daughter_old_llrpid_k_3pl", &reco_track_daughter_old_llrpid_k_3pl);
      //}
  }

}

//void Draw(TFile *f, TString var, double scale, int dencut, bool print)
void SetHistos(){

  h_track_chi2ka_ka = new TH1D("BDT_track_kaka", "; BDT Response; Number of Events", 50, 0, 100);
  h_track_chi2ka_pr = new TH1D("BDT_track_kapr", "; BDT Response; Number of Events", 50, 0, 100);
  h_track_chi2ka_pi = new TH1D("BDT_track_kapi", "; BDT Response; Number of Events", 50, 0, 100);
  h_track_chi2ka_mu = new TH1D("BDT_track_kamu", "; BDT Response; Number of Events", 50, 0, 100);
  h_track_chi2ka_ot = new TH1D("BDT_track_kaot", "; BDT Response; Number of Events", 50, 0, 100);

  h_track_chi2pr_ka = new TH1D("BDT_track_prka", "; BDT Response; Number of Events", 50, 0, 100);
  h_track_chi2pr_pr = new TH1D("BDT_track_prpr", "; BDT Response; Number of Events", 50, 0, 100);
  h_track_chi2pr_pi = new TH1D("BDT_track_prpi", "; BDT Response; Number of Events", 50, 0, 100);
  h_track_chi2pr_mu = new TH1D("BDT_track_prmu", "; BDT Response; Number of Events", 50, 0, 100);
  h_track_chi2pr_ot = new TH1D("BDT_track_prot", "; BDT Response; Number of Events", 50, 0, 100);

  h_track_llr_ka = new TH1D("BDT_track_llrka", "; BDT Response; Number of Events", 50, -1, 1);
  h_track_llr_pr = new TH1D("BDT_track_llrpr", "; BDT Response; Number of Events", 50, -1, 1);
  h_track_llr_pi = new TH1D("BDT_track_llrpi", "; BDT Response; Number of Events", 50, -1, 1);
  h_track_llr_mu = new TH1D("BDT_track_llrmu", "; BDT Response; Number of Events", 50, -1, 1);
  h_track_llr_ot = new TH1D("BDT_track_llrot", "; BDT Response; Number of Events", 50, -1, 1);

  h_track_llrka_ka = new TH1D("BDT_track_llrkaka", "; BDT Response; Number of Events", 50, -1, 1);
  h_track_llrka_pr = new TH1D("BDT_track_llrkapr", "; BDT Response; Number of Events", 50, -1, 1);
  h_track_llrka_pi = new TH1D("BDT_track_llrkapi", "; BDT Response; Number of Events", 50, -1, 1);
  h_track_llrka_mu = new TH1D("BDT_track_llrkamu", "; BDT Response; Number of Events", 50, -1, 1);
  h_track_llrka_ot = new TH1D("BDT_track_llrkaot", "; BDT Response; Number of Events", 50, -1, 1);

  h_track_dau_llr_pr = new TH1D("BDT_track_dau_llapr", "; BDT Response; Number of Events", 50, -1, 1);
  h_track_dau_llr_pi = new TH1D("BDT_track_dau_llrpi", "; BDT Response; Number of Events", 50, -1, 1);
  h_track_dau_llr_mu = new TH1D("BDT_track_dau_llrmu", "; BDT Response; Number of Events", 50, -1, 1);
  h_track_dau_llr_sh = new TH1D("BDT_track_dau_llrsh", "; BDT Response; Number of Events", 50, -1, 1);
  h_track_dau_llr_ot = new TH1D("BDT_track_dau_llrot", "; BDT Response; Number of Events", 50, -1, 1);

  h_track_dau_llrka_pr = new TH1D("BDT_track_dau_llapr", "; BDT Response; Number of Events", 50, -1, 1);
  h_track_dau_llrka_pi = new TH1D("BDT_track_dau_llrpi", "; BDT Response; Number of Events", 50, -1, 1);
  h_track_dau_llrka_mu = new TH1D("BDT_track_dau_llrmu", "; BDT Response; Number of Events", 50, -1, 1);
  h_track_dau_llrka_sh = new TH1D("BDT_track_dau_llrsh", "; BDT Response; Number of Events", 50, -1, 1);
  h_track_dau_llrka_ot = new TH1D("BDT_track_dau_llrot", "; BDT Response; Number of Events", 50, -1, 1);

  
  h_track_dau_chi2pr_pr = new TH1D("BDT_track_dau_prpr", "; BDT Response; Number of Events", 50, 0, 150);
  h_track_dau_chi2pr_pi = new TH1D("BDT_track_dau_prpi", "; BDT Response; Number of Events", 50, 0, 150);
  h_track_dau_chi2pr_mu = new TH1D("BDT_track_dau_prmu", "; BDT Response; Number of Events", 50, 0, 150);
  h_track_dau_chi2pr_sh = new TH1D("BDT_track_dau_prsh", "; BDT Response; Number of Events", 50, 0, 150);
  h_track_dau_chi2pr_ot = new TH1D("BDT_track_dau_prot", "; BDT Response; Number of Events", 50, 0, 150);

  h_track_dau_chi2pi_pr = new TH1D("BDT_track_dau_prpr", "; BDT Response; Number of Events", 50, 0, 100);
  h_track_dau_chi2pi_pi = new TH1D("BDT_track_dau_prpi", "; BDT Response; Number of Events", 50, 0, 100);
  h_track_dau_chi2pi_mu = new TH1D("BDT_track_dau_prmu", "; BDT Response; Number of Events", 50, 0, 100);
  h_track_dau_chi2pi_sh = new TH1D("BDT_track_dau_prsh", "; BDT Response; Number of Events", 50, 0, 100);
  h_track_dau_chi2pi_ot = new TH1D("BDT_track_dau_prot", "; BDT Response; Number of Events", 50, 0, 100);

  h_track_dau_chi2mu_pr = new TH1D("BDT_track_dau_mupr", "; BDT Response; Number of Events", 50, 0, 100);
  h_track_dau_chi2mu_pi = new TH1D("BDT_track_dau_mupi", "; BDT Response; Number of Events", 50, 0, 100);
  h_track_dau_chi2mu_mu = new TH1D("BDT_track_dau_mumu", "; BDT Response; Number of Events", 50, 0, 100);
  h_track_dau_chi2mu_sh = new TH1D("BDT_track_dau_mush", "; BDT Response; Number of Events", 50, 0, 100);
  h_track_dau_chi2mu_ot = new TH1D("BDT_track_dau_muot", "; BDT Response; Number of Events", 50, 0, 100);
  

  h_track_dau_ln_pr = new TH1D("track_dau_ln_pr", "; BDT Response; Number of Events", 50, 0, 100);
  h_track_dau_ln_pi = new TH1D("track_dau_ln_pi", "; BDT Response; Number of Events", 50, 0, 100);
  h_track_dau_ln_mu = new TH1D("track_dau_ln_mu", "; BDT Response; Number of Events", 50, 0, 100);
  h_track_dau_ln_sh = new TH1D("track_dau_ln_sh", "; BDT Response; Number of Events", 50, 0, 100);
  h_track_dau_ln_ot = new TH1D("track_dau_ln_ot", "; BDT Response; Number of Events", 50, 0, 100);

  h_track_dau_ln_pr_hy = new TH1D("track_dau_ln_pr_hy", "; BDT Response; Number of Events", 50, 0, 100);
  h_track_dau_ln_pi_hy = new TH1D("track_dau_ln_pi_hy", "; BDT Response; Number of Events", 50, 0, 100);
  h_track_dau_ln_mu_hy = new TH1D("track_dau_ln_mu_hy", "; BDT Response; Number of Events", 50, 0, 100);
  h_track_dau_ln_sh_hy = new TH1D("track_dau_ln_sh_hy", "; BDT Response; Number of Events", 50, 0, 100);
  h_track_dau_ln_ot_hy = new TH1D("track_dau_ln_ot_hy", "; BDT Response; Number of Events", 50, 0, 100);

  //

  h_track_dau_old_llr_pr = new TH1D("BDT_track_dau_old_llapr", "; BDT Response; Number of Events", 50, -1, 1);
  h_track_dau_old_llr_pi = new TH1D("BDT_track_dau_old_llrpi", "; BDT Response; Number of Events", 50, -1, 1);
  h_track_dau_old_llr_mu = new TH1D("BDT_track_dau_old_llrmu", "; BDT Response; Number of Events", 50, -1, 1);
  h_track_dau_old_llr_sh = new TH1D("BDT_track_dau_old_llrsh", "; BDT Response; Number of Events", 50, -1, 1);
  h_track_dau_old_llr_ot = new TH1D("BDT_track_dau_old_llrot", "; BDT Response; Number of Events", 50, -1, 1);

  h_track_dau_old_llrka_pr = new TH1D("BDT_track_dau_old_llapr", "; BDT Response; Number of Events", 50, -1, 1);
  h_track_dau_old_llrka_pi = new TH1D("BDT_track_dau_old_llrpi", "; BDT Response; Number of Events", 50, -1, 1);
  h_track_dau_old_llrka_mu = new TH1D("BDT_track_dau_old_llrmu", "; BDT Response; Number of Events", 50, -1, 1);
  h_track_dau_old_llrka_sh = new TH1D("BDT_track_dau_old_llrsh", "; BDT Response; Number of Events", 50, -1, 1);
  h_track_dau_old_llrka_ot = new TH1D("BDT_track_dau_old_llrot", "; BDT Response; Number of Events", 50, -1, 1);

  
  h_track_dau_old_chi2pr_pr = new TH1D("BDT_track_dau_old_prpr", "; BDT Response; Number of Events", 50, 0, 150);
  h_track_dau_old_chi2pr_pi = new TH1D("BDT_track_dau_old_prpi", "; BDT Response; Number of Events", 50, 0, 150);
  h_track_dau_old_chi2pr_mu = new TH1D("BDT_track_dau_old_prmu", "; BDT Response; Number of Events", 50, 0, 150);
  h_track_dau_old_chi2pr_sh = new TH1D("BDT_track_dau_old_prsh", "; BDT Response; Number of Events", 50, 0, 150);
  h_track_dau_old_chi2pr_ot = new TH1D("BDT_track_dau_old_prot", "; BDT Response; Number of Events", 50, 0, 150);

  h_track_dau_old_chi2pi_pr = new TH1D("BDT_track_dau_old_prpr", "; BDT Response; Number of Events", 50, 0, 100);
  h_track_dau_old_chi2pi_pi = new TH1D("BDT_track_dau_old_prpi", "; BDT Response; Number of Events", 50, 0, 100);
  h_track_dau_old_chi2pi_mu = new TH1D("BDT_track_dau_old_prmu", "; BDT Response; Number of Events", 50, 0, 100);
  h_track_dau_old_chi2pi_sh = new TH1D("BDT_track_dau_old_prsh", "; BDT Response; Number of Events", 50, 0, 100);
  h_track_dau_old_chi2pi_ot = new TH1D("BDT_track_dau_old_prot", "; BDT Response; Number of Events", 50, 0, 100);

  h_track_dau_old_chi2mu_pr = new TH1D("BDT_track_dau_old_mupr", "; BDT Response; Number of Events", 50, 0, 100);
  h_track_dau_old_chi2mu_pi = new TH1D("BDT_track_dau_old_mupi", "; BDT Response; Number of Events", 50, 0, 100);
  h_track_dau_old_chi2mu_mu = new TH1D("BDT_track_dau_old_mumu", "; BDT Response; Number of Events", 50, 0, 100);
  h_track_dau_old_chi2mu_sh = new TH1D("BDT_track_dau_old_mush", "; BDT Response; Number of Events", 50, 0, 100);
  h_track_dau_old_chi2mu_ot = new TH1D("BDT_track_dau_old_muot", "; BDT Response; Number of Events", 50, 0, 100);
  

  h_track_dau_old_ln_pr = new TH1D("track_dau_old_ln_pr", "; BDT Response; Number of Events", 50, 0, 100);
  h_track_dau_old_ln_pi = new TH1D("track_dau_old_ln_pi", "; BDT Response; Number of Events", 50, 0, 100);
  h_track_dau_old_ln_mu = new TH1D("track_dau_old_ln_mu", "; BDT Response; Number of Events", 50, 0, 100);
  h_track_dau_old_ln_sh = new TH1D("track_dau_old_ln_sh", "; BDT Response; Number of Events", 50, 0, 100);
  h_track_dau_old_ln_ot = new TH1D("track_dau_old_ln_ot", "; BDT Response; Number of Events", 50, 0, 100);


  h_truek_trkln_chi2ka = new TH2D("h_truek_trkln_chi2ka", "Track length vs #chi^{2}_{K};  #chi^{2}_{K}; Track length", 50, 0 , 50, 50, 0, 100);

  h_reco_track_length = new TH1D("h_reco_track_length", "; reco_track_length; Number of Events", 50, 0, 50);
  h_reco_track_daughter_distance = new TH1D("h_reco_track_daughter_distance", "; reco_track_daughter_distance; Number of Events", 50, 0, 50);
  h_reco_track_daughter_vtx_distance = new TH1D(" h_reco_track_daughter_vtx_distance", ";  reco_track_daughter_vtx_distance; Number of Events", 50, 0, 50);

  /*
  THStack * s_chi2ka = new THStack();
  THStack * s_chi2pr = new THStack();
  THStack * s_llr = new THStack();
  THStack * s_llrka = new THStack();

  THStack * s_llr_dau = new THStack();
  THStack * s_llrka_dau = new THStack();
  THStack * s_chi2pr_dau = new THStack();
  THStack * s_chi2pi_dau = new THStack();
  THStack * s_chi2mu_dau = new THStack();
  THStack * s_trkln_dau = new THStack();

  THStack * s_llr_dau_old = new THStack();
  THStack * s_llrka_dau_old = new THStack();
  THStack * s_chi2pr_dau_old = new THStack();
  THStack * s_chi2pi_dau_old = new THStack();
  THStack * s_chi2mu_dau_old = new THStack();
  THStack * s_trkln_dau_old = new THStack();

  THStack * s_braggka = new THStack();
  THStack * s_braggpr = new THStack();
  THStack * s_braggpi = new THStack();
  THStack * s_braggmu = new THStack();
  */

}

void SetHistosStyle(){
  
  h_track_chi2ka_ka->SetLineColor(kBlue);
  h_track_chi2ka_pr->SetLineColor(kRed);
  h_track_chi2ka_pi->SetLineColor(TColor::GetColorDark(kGreen));
  h_track_chi2ka_mu->SetLineColor(kViolet);
  h_track_chi2ka_ot->SetLineColor(kOrange+1);

  h_track_chi2pr_ka->SetLineColor(kBlue);
  h_track_chi2pr_pr->SetLineColor(kRed);
  h_track_chi2pr_pi->SetLineColor(TColor::GetColorDark(kGreen));
  h_track_chi2pr_mu->SetLineColor(kViolet);
  h_track_chi2pr_ot->SetLineColor(kOrange+1);

  h_track_llr_ka->SetLineColor(kBlue);
  h_track_llr_pr->SetLineColor(kRed);
  h_track_llr_pi->SetLineColor(TColor::GetColorDark(kGreen));
  h_track_llr_mu->SetLineColor(kViolet);
  h_track_llr_ot->SetLineColor(kOrange+1);

  h_track_llrka_ka->SetLineColor(kBlue);
  h_track_llrka_pr->SetLineColor(kRed);
  h_track_llrka_pi->SetLineColor(TColor::GetColorDark(kGreen));
  h_track_llrka_mu->SetLineColor(kViolet);
  h_track_llrka_ot->SetLineColor(kOrange+1);

  h_track_dau_llr_pr->SetLineColor(kRed);
  h_track_dau_llr_pi->SetLineColor(TColor::GetColorDark(kGreen));
  h_track_dau_llr_mu->SetLineColor(kCyan);
  h_track_dau_llr_sh->SetLineColor(kMagenta);
  h_track_dau_llr_ot->SetLineColor(kOrange+1);

  h_track_dau_llrka_pr->SetLineColor(kRed);
  h_track_dau_llrka_pi->SetLineColor(TColor::GetColorDark(kGreen));
  h_track_dau_llrka_mu->SetLineColor(kCyan);
  h_track_dau_llrka_sh->SetLineColor(kMagenta);
  h_track_dau_llrka_ot->SetLineColor(kOrange+1);

  h_track_dau_chi2pr_pr->SetLineColor(kRed);
  h_track_dau_chi2pr_pi->SetLineColor(TColor::GetColorDark(kGreen));
  h_track_dau_chi2pr_mu->SetLineColor(kCyan);
  h_track_dau_chi2pr_sh->SetLineColor(kMagenta);
  h_track_dau_chi2pr_ot->SetLineColor(kOrange+1);

  h_track_dau_chi2pi_pr->SetLineColor(kRed);
  h_track_dau_chi2pi_pi->SetLineColor(TColor::GetColorDark(kGreen));
  h_track_dau_chi2pi_mu->SetLineColor(kCyan);
  h_track_dau_chi2pi_sh->SetLineColor(kMagenta);
  h_track_dau_chi2pi_ot->SetLineColor(kOrange+1);

  h_track_dau_chi2mu_pr->SetLineColor(kRed);
  h_track_dau_chi2mu_pi->SetLineColor(TColor::GetColorDark(kGreen));
  h_track_dau_chi2mu_mu->SetLineColor(kCyan);
  h_track_dau_chi2mu_sh->SetLineColor(kMagenta);
  h_track_dau_chi2mu_ot->SetLineColor(kOrange+1);

  h_track_dau_ln_pr->SetLineColor(kRed);
  h_track_dau_ln_pi->SetLineColor(TColor::GetColorDark(kGreen));
  h_track_dau_ln_mu->SetLineColor(kCyan);
  h_track_dau_ln_sh->SetLineColor(kMagenta);
  h_track_dau_ln_ot->SetLineColor(kBlack);
  h_track_dau_ln_pr->SetLineWidth(2);
  h_track_dau_ln_pi->SetLineWidth(3);
  h_track_dau_ln_mu->SetLineWidth(3);
  h_track_dau_ln_sh->SetLineWidth(2);
  h_track_dau_ln_ot->SetLineWidth(2);
  h_track_dau_ln_pi->SetFillColorAlpha(TColor::GetColorDark(kGreen), 0.5);
  h_track_dau_ln_mu->SetFillColorAlpha(kCyan, 0.3);

  h_track_dau_ln_pr_hy->SetLineColor(kRed);
  h_track_dau_ln_pi_hy->SetLineColor(TColor::GetColorDark(kGreen));
  h_track_dau_ln_mu_hy->SetLineColor(kCyan);
  h_track_dau_ln_sh_hy->SetLineColor(kMagenta);
  h_track_dau_ln_ot_hy->SetLineColor(kBlack);
  h_track_dau_ln_pr_hy->SetLineWidth(2);
  h_track_dau_ln_pi_hy->SetLineWidth(3);
  h_track_dau_ln_mu_hy->SetLineWidth(3);
  h_track_dau_ln_sh_hy->SetLineWidth(2);
  h_track_dau_ln_ot_hy->SetLineWidth(2);
  h_track_dau_ln_pi_hy->SetFillColorAlpha(TColor::GetColorDark(kGreen), 0.5);
  h_track_dau_ln_mu_hy->SetFillColorAlpha(kCyan, 0.3);

  //h_track_dau_ln_pr->SetFillColor(kRed);
  //h_track_dau_ln_sh->SetFillColor(kMagenta);
  //h_track_dau_ln_ot->SetFillColor(kBlack);
  //h_track_dau_ln_pi->SetFillStyle(3003);
  //h_track_dau_ln_mu->SetFillStyle(3004);
  //h_track_dau_ln_ot->SetFillStyle(3005);

  h_track_dau_old_llr_pr->SetLineColor(kRed);
  h_track_dau_old_llr_pi->SetLineColor(TColor::GetColorDark(kGreen));
  h_track_dau_old_llr_mu->SetLineColor(kCyan);
  h_track_dau_old_llr_sh->SetLineColor(kMagenta);
  h_track_dau_old_llr_ot->SetLineColor(kOrange+1);

  h_track_dau_old_llrka_pr->SetLineColor(kRed);
  h_track_dau_old_llrka_pi->SetLineColor(TColor::GetColorDark(kGreen));
  h_track_dau_old_llrka_mu->SetLineColor(kCyan);
  h_track_dau_old_llrka_sh->SetLineColor(kMagenta);
  h_track_dau_old_llrka_ot->SetLineColor(kOrange+1);

  h_track_dau_old_chi2pr_pr->SetLineColor(kRed);
  h_track_dau_old_chi2pr_pi->SetLineColor(TColor::GetColorDark(kGreen));
  h_track_dau_old_chi2pr_mu->SetLineColor(kCyan);
  h_track_dau_old_chi2pr_sh->SetLineColor(kMagenta);
  h_track_dau_old_chi2pr_ot->SetLineColor(kOrange+1);

  h_track_dau_old_chi2pi_pr->SetLineColor(kRed);
  h_track_dau_old_chi2pi_pi->SetLineColor(TColor::GetColorDark(kGreen));
  h_track_dau_old_chi2pi_mu->SetLineColor(kCyan);
  h_track_dau_old_chi2pi_sh->SetLineColor(kMagenta);
  h_track_dau_old_chi2pi_ot->SetLineColor(kOrange+1);

  h_track_dau_old_chi2mu_pr->SetLineColor(kRed);
  h_track_dau_old_chi2mu_pi->SetLineColor(TColor::GetColorDark(kGreen));
  h_track_dau_old_chi2mu_mu->SetLineColor(kCyan);
  h_track_dau_old_chi2mu_sh->SetLineColor(kMagenta);
  h_track_dau_old_chi2mu_ot->SetLineColor(kOrange+1);

  h_track_dau_old_ln_pr->SetLineColor(kRed);
  h_track_dau_old_ln_pi->SetLineColor(TColor::GetColorDark(kGreen));
  h_track_dau_old_ln_mu->SetLineColor(kCyan);
  h_track_dau_old_ln_sh->SetLineColor(kMagenta);
  h_track_dau_old_ln_ot->SetLineColor(kBlack);
  h_track_dau_old_ln_pr->SetLineWidth(2);
  h_track_dau_old_ln_pi->SetLineWidth(3);
  h_track_dau_old_ln_mu->SetLineWidth(3);
  h_track_dau_old_ln_sh->SetLineWidth(2);
  h_track_dau_old_ln_ot->SetLineWidth(2);
  h_track_dau_old_ln_pi->SetFillColorAlpha(TColor::GetColorDark(kGreen), 0.5);
  h_track_dau_old_ln_mu->SetFillColorAlpha(kCyan, 0.3);

  /*
  h_reco_track_Bragg_fwd_ka_pl2_ka->SetLineColor(kBlue);
  h_reco_track_Bragg_fwd_ka_pl2_pr->SetLineColor(kRed);
  h_reco_track_Bragg_fwd_ka_pl2_pi->SetLineColor(TColor::GetColorDark(kGreen));
  h_reco_track_Bragg_fwd_ka_pl2_mu->SetLineColor(kViolet);
  h_reco_track_Bragg_fwd_ka_pl2_ot->SetLineColor(kOrange+1);

  h_reco_track_Bragg_fwd_pr_pl2_ka->SetLineColor(kBlue);
  h_reco_track_Bragg_fwd_pr_pl2_pr->SetLineColor(kRed);
  h_reco_track_Bragg_fwd_pr_pl2_pi->SetLineColor(TColor::GetColorDark(kGreen));
  h_reco_track_Bragg_fwd_pr_pl2_mu->SetLineColor(kViolet);
  h_reco_track_Bragg_fwd_pr_pl2_ot->SetLineColor(kOrange+1);

  h_reco_track_Bragg_fwd_pi_pl2_ka->SetLineColor(kBlue);
  h_reco_track_Bragg_fwd_pi_pl2_pr->SetLineColor(kRed);
  h_reco_track_Bragg_fwd_pi_pl2_pi->SetLineColor(TColor::GetColorDark(kGreen));
  h_reco_track_Bragg_fwd_pi_pl2_mu->SetLineColor(kViolet);
  h_reco_track_Bragg_fwd_pi_pl2_ot->SetLineColor(kOrange+1);

  h_reco_track_Bragg_fwd_mu_pl2_ka->SetLineColor(kBlue);
  h_reco_track_Bragg_fwd_mu_pl2_pr->SetLineColor(kRed);
  h_reco_track_Bragg_fwd_mu_pl2_pi->SetLineColor(TColor::GetColorDark(kGreen));
  h_reco_track_Bragg_fwd_mu_pl2_mu->SetLineColor(kViolet);
  h_reco_track_Bragg_fwd_mu_pl2_ot->SetLineColor(kOrange+1);
  
  h_reco_track_Bragg_fwd_ka_pl2_ka->SetLineWidth(3);
  h_reco_track_Bragg_fwd_ka_pl2_pr->SetLineWidth(3);
  h_reco_track_Bragg_fwd_ka_pl2_pi->SetLineWidth(3);
  h_reco_track_Bragg_fwd_ka_pl2_mu->SetLineWidth(3);
  h_reco_track_Bragg_fwd_ka_pl2_ot->SetLineWidth(3);

  h_reco_track_Bragg_fwd_pr_pl2_ka->SetLineWidth(3);
  h_reco_track_Bragg_fwd_pr_pl2_pr->SetLineWidth(3);
  h_reco_track_Bragg_fwd_pr_pl2_pi->SetLineWidth(3);
  h_reco_track_Bragg_fwd_pr_pl2_mu->SetLineWidth(3);
  h_reco_track_Bragg_fwd_pr_pl2_ot->SetLineWidth(3);

  h_reco_track_Bragg_fwd_pi_pl2_ka->SetLineWidth(3);
  h_reco_track_Bragg_fwd_pi_pl2_pr->SetLineWidth(3);
  h_reco_track_Bragg_fwd_pi_pl2_pi->SetLineWidth(3);
  h_reco_track_Bragg_fwd_pi_pl2_mu->SetLineWidth(3);
  h_reco_track_Bragg_fwd_pi_pl2_ot->SetLineWidth(3);

  h_reco_track_Bragg_fwd_mu_pl2_ka->SetLineWidth(3);
  h_reco_track_Bragg_fwd_mu_pl2_pr->SetLineWidth(3);
  h_reco_track_Bragg_fwd_mu_pl2_pi->SetLineWidth(3);
  h_reco_track_Bragg_fwd_mu_pl2_mu->SetLineWidth(3);
  h_reco_track_Bragg_fwd_mu_pl2_ot->SetLineWidth(3);
  */

}


void FillHybridTrackLength(){
  
  /*
  if(reco_track_daughter_true_pdg==211){
    cout << "reco_track_daughter_length: " << reco_track_daughter_length << endl;
    cout << "reco_track_daughter_old_true_pdg: " << reco_track_daughter_old_true_pdg << ", reco_track_daughter_old_length: " << reco_track_daughter_old_length << endl;
  }
  */

  if(reco_track_daughter_old_length>50 && reco_track_daughter_old_length<75){
    if(reco_track_daughter_old_true_pdg==2212)
      h_track_dau_ln_pr_hy->Fill(reco_track_daughter_old_length);
    else if(reco_track_daughter_old_true_pdg==-13)
      h_track_dau_ln_mu_hy->Fill(reco_track_daughter_old_length);
    else if(reco_track_daughter_old_true_pdg==211)
      h_track_dau_ln_pi_hy->Fill(reco_track_daughter_old_length);  
    else if(reco_track_daughter_old_true_pdg==11 || reco_track_daughter_old_true_pdg==-11 || reco_track_daughter_old_true_pdg==22)
      h_track_dau_ln_sh_hy->Fill(reco_track_daughter_old_length);
    else if(reco_track_daughter_old_true_pdg!=-9999)
      h_track_dau_ln_ot_hy->Fill(reco_track_daughter_old_length);

    if(reco_track_true_pdg==321 && (reco_track_daughter_old_true_pdg==211 && std::abs(reco_track_daughter_old_length-true_dau_pip_length)<0.2*true_dau_pip_length)) reco_true_length_pi_hy++;
    if(reco_track_true_pdg==321 && (reco_track_daughter_old_true_pdg==-13 && std::abs(reco_track_daughter_old_length-true_dau_muon_length)<0.2*true_dau_muon_length)) reco_true_length_mu_hy++;

  }
  else if(reco_track_daughter_length>25 && reco_track_daughter_length<75){
    //else{
    
    if(reco_track_true_pdg==321 && (reco_track_daughter_true_pdg==211 && std::abs(reco_track_daughter_length-true_dau_pip_length)<0.2*true_dau_pip_length)) reco_true_length_pi_hy++;
    if(reco_track_true_pdg==321 && (reco_track_daughter_true_pdg==-13 && std::abs(reco_track_daughter_length-true_dau_muon_length)<0.2*true_dau_muon_length)) reco_true_length_mu_hy++;

    if(reco_track_daughter_true_pdg==2212){
      h_track_dau_ln_pr_hy->Fill(reco_track_daughter_length);
      //h_track_dis_ln_pr->Fill(reco_track_distance);
      //h_track_dau_dis_ln_pr->Fill(reco_track_daughter_distance);
      h_track_dau_llr_pr->Fill(reco_track_daughter_llrpid_3pl);
      h_track_dau_llrka_pr->Fill(reco_track_daughter_llrpid_k_3pl);
    }
    //else if(reco_track_daughter_true_pdg==-13){
    else if( (reco_track_daughter_true_pdg==-13 || reco_track_daughter_true_pdg==13) ){
      h_track_dau_ln_mu_hy->Fill(reco_track_daughter_length);
      //h_track_dis_ln_mu->Fill(reco_track_distance);
      //h_track_dau_dis_ln_mu->Fill(reco_track_daughter_distance);
      h_track_dau_llr_mu->Fill(reco_track_daughter_llrpid_3pl);
      h_track_dau_llrka_mu->Fill(reco_track_daughter_llrpid_k_3pl);
    }
    else if(reco_track_daughter_true_pdg==211){
      h_track_dau_ln_pi_hy->Fill(reco_track_daughter_length);
      //h_track_dis_ln_pi->Fill(reco_track_distance);
      //h_track_dau_dis_ln_pi->Fill(reco_track_daughter_distance);
      h_track_dau_llr_pi->Fill(reco_track_daughter_llrpid_3pl);
      h_track_dau_llrka_pi->Fill(reco_track_daughter_llrpid_k_3pl);
    }
    else if(reco_track_daughter_true_pdg==11 || reco_track_daughter_true_pdg==-11 || reco_track_daughter_true_pdg==22){
      h_track_dau_ln_sh_hy->Fill(reco_track_daughter_length);
      h_track_dau_llr_sh->Fill(reco_track_daughter_llrpid_3pl);
      h_track_dau_llrka_sh->Fill(reco_track_daughter_llrpid_k_3pl);
    }
    else if(reco_track_daughter_true_pdg!=-9999){
      h_track_dau_ln_ot_hy->Fill(reco_track_daughter_length);
      //h_track_dis_ln_ot->Fill(reco_track_distance);
      //h_track_dau_dis_ln_ot->Fill(reco_track_daughter_distance);
      h_track_dau_llr_ot->Fill(reco_track_daughter_llrpid_3pl);
      h_track_dau_llrka_ot->Fill(reco_track_daughter_llrpid_k_3pl);
    }
  }
  
    if(reco_track_true_pdg==321 && (reco_track_daughter_true_pdg==211 && std::abs(reco_track_daughter_length-true_dau_pip_length)<0.2*true_dau_pip_length)) reco_true_length_pi++;
    if(reco_track_true_pdg==321 && (reco_track_daughter_true_pdg==-13 && std::abs(reco_track_daughter_length-true_dau_muon_length)<0.2*true_dau_muon_length)) reco_true_length_mu++;

    if(reco_track_daughter_length>25 && reco_track_daughter_length<75){
  if(reco_track_daughter_true_pdg==2212){
    h_track_dau_ln_pr->Fill(reco_track_daughter_length);
    h_track_dau_llr_pr->Fill(reco_track_daughter_llrpid_3pl);
    h_track_dau_llrka_pr->Fill(reco_track_daughter_llrpid_k_3pl);
  }
  else if(reco_track_daughter_true_pdg==-13){
    h_track_dau_ln_mu->Fill(reco_track_daughter_length);
    h_track_dau_llr_mu->Fill(reco_track_daughter_llrpid_3pl);
    h_track_dau_llrka_mu->Fill(reco_track_daughter_llrpid_k_3pl);
  }
  else if(reco_track_daughter_true_pdg==211){
    h_track_dau_ln_pi->Fill(reco_track_daughter_length);
    h_track_dau_llr_pi->Fill(reco_track_daughter_llrpid_3pl);
    h_track_dau_llrka_pi->Fill(reco_track_daughter_llrpid_k_3pl);
  }
  else if(reco_track_daughter_true_pdg==11 || reco_track_daughter_true_pdg==-11 || reco_track_daughter_true_pdg==22){
    h_track_dau_ln_sh->Fill(reco_track_daughter_length);
    h_track_dau_llr_sh->Fill(reco_track_daughter_llrpid_3pl);
    h_track_dau_llrka_sh->Fill(reco_track_daughter_llrpid_k_3pl);	  
  }
  else if(reco_track_daughter_true_pdg!=-9999){
    h_track_dau_ln_ot->Fill(reco_track_daughter_length);
    h_track_dau_llr_ot->Fill(reco_track_daughter_llrpid_3pl);
    h_track_dau_llrka_ot->Fill(reco_track_daughter_llrpid_k_3pl);
  }
  }

}


void FillOldTrackLength(){

  if(reco_track_daughter_old_length>25 && reco_track_daughter_old_length<75){
  if(reco_track_daughter_old_true_pdg==2212){
    h_track_dau_old_ln_pr->Fill(reco_track_daughter_old_length);
    h_track_dau_old_llr_pr->Fill(reco_track_daughter_old_llrpid_3pl);
    h_track_dau_old_llrka_pr->Fill(reco_track_daughter_old_llrpid_k_3pl);
  }
  else if(reco_track_daughter_old_true_pdg==-13){
    h_track_dau_old_ln_mu->Fill(reco_track_daughter_old_length);
    h_track_dau_old_llr_mu->Fill(reco_track_daughter_old_llrpid_3pl);
    h_track_dau_old_llrka_mu->Fill(reco_track_daughter_old_llrpid_k_3pl);
	}
  else if(reco_track_daughter_old_true_pdg==211){
    h_track_dau_old_ln_pi->Fill(reco_track_daughter_old_length);
    h_track_dau_old_llr_pi->Fill(reco_track_daughter_old_llrpid_3pl);
    h_track_dau_old_llrka_pi->Fill(reco_track_daughter_old_llrpid_k_3pl);
  }
  else if(reco_track_daughter_old_true_pdg==11 || reco_track_daughter_old_true_pdg==-11 || reco_track_daughter_old_true_pdg==22){
    h_track_dau_old_ln_sh->Fill(reco_track_daughter_old_length);
    h_track_dau_old_llr_sh->Fill(reco_track_daughter_old_llrpid_3pl);
    h_track_dau_old_llrka_sh->Fill(reco_track_daughter_old_llrpid_k_3pl);	  
  }
  else if(reco_track_daughter_old_true_pdg!=-9999){
    h_track_dau_old_ln_ot->Fill(reco_track_daughter_old_length);
    h_track_dau_old_llr_ot->Fill(reco_track_daughter_old_llrpid_3pl);
    h_track_dau_old_llrka_ot->Fill(reco_track_daughter_old_llrpid_k_3pl);
  }
  }

  if(reco_track_true_pdg==321 && (reco_track_daughter_old_true_pdg==211 && std::abs(reco_track_daughter_old_length-true_dau_pip_length)<0.2*true_dau_pip_length)) reco_old_true_length_pi++;
  if(reco_track_true_pdg==321 && (reco_track_daughter_old_true_pdg==-13 && std::abs(reco_track_daughter_old_length-true_dau_muon_length)<0.2*true_dau_muon_length)) reco_old_true_length_mu++;

  
}

void FillRebuiltTrackLength(){

    if(reco_track_true_pdg==321 && (reco_track_daughter_true_pdg==211 && std::abs(reco_track_daughter_length-true_dau_pip_length)<0.2*true_dau_pip_length)) reco_true_length_pi++;
    if(reco_track_true_pdg==321 && (reco_track_daughter_true_pdg==-13 && std::abs(reco_track_daughter_length-true_dau_muon_length)<0.2*true_dau_muon_length)) reco_true_length_mu++;

  if(reco_track_daughter_true_pdg==2212){
    h_track_dau_ln_pr->Fill(reco_track_daughter_length);
    h_track_dau_llr_pr->Fill(reco_track_daughter_llrpid_3pl);
    h_track_dau_llrka_pr->Fill(reco_track_daughter_llrpid_k_3pl);
  }
  else if(reco_track_daughter_true_pdg==-13){
    h_track_dau_ln_mu->Fill(reco_track_daughter_length);
    h_track_dau_llr_mu->Fill(reco_track_daughter_llrpid_3pl);
    h_track_dau_llrka_mu->Fill(reco_track_daughter_llrpid_k_3pl);
  }
  else if(reco_track_daughter_true_pdg==211){
    h_track_dau_ln_pi->Fill(reco_track_daughter_length);
    h_track_dau_llr_pi->Fill(reco_track_daughter_llrpid_3pl);
    h_track_dau_llrka_pi->Fill(reco_track_daughter_llrpid_k_3pl);
  }
  else if(reco_track_daughter_true_pdg==11 || reco_track_daughter_true_pdg==-11 || reco_track_daughter_true_pdg==22){
    h_track_dau_ln_sh->Fill(reco_track_daughter_length);
    h_track_dau_llr_sh->Fill(reco_track_daughter_llrpid_3pl);
    h_track_dau_llrka_sh->Fill(reco_track_daughter_llrpid_k_3pl);	  
  }
  else if(reco_track_daughter_true_pdg!=-9999){
    h_track_dau_ln_ot->Fill(reco_track_daughter_length);
    h_track_dau_llr_ot->Fill(reco_track_daughter_llrpid_3pl);
    h_track_dau_llrka_ot->Fill(reco_track_daughter_llrpid_k_3pl);
  }
  
}


	void FillPl2PID(){

	if(reco_track_true_pdg==321){
	  h_track_chi2ka_ka->Fill(reco_track_chi2ka_pl2);
	  h_track_chi2pr_ka->Fill(reco_track_chi2pr_pl2);
	}
	else if(reco_track_true_pdg==13){
	  h_track_chi2ka_mu->Fill(reco_track_chi2ka_pl2);
	  h_track_chi2pr_mu->Fill(reco_track_chi2pr_pl2);
	}
	else if(reco_track_true_pdg==211){
	  h_track_chi2ka_pi->Fill(reco_track_chi2ka_pl2);
	  h_track_chi2pr_pi->Fill(reco_track_chi2pr_pl2);
	}
	else if(reco_track_true_pdg==2212){
	  h_track_chi2ka_pr->Fill(reco_track_chi2ka_pl2);
	  h_track_chi2pr_pr->Fill(reco_track_chi2pr_pl2);
	}
	else{
	  h_track_chi2ka_ot->Fill(reco_track_chi2ka_pl2);
	  h_track_chi2pr_ot->Fill(reco_track_chi2pr_pl2);
	}

	if(reco_track_daughter_true_pdg==2212){
	  h_track_dau_chi2pr_pr->Fill(reco_track_daughter_chi2pr_pl2);
	  h_track_dau_chi2pi_pr->Fill(reco_track_daughter_chi2pi_pl2);
	  h_track_dau_chi2mu_pr->Fill(reco_track_daughter_chi2mu_pl2);
	}
	else if(reco_track_daughter_true_pdg==-13){
	  h_track_dau_chi2pr_mu->Fill(reco_track_daughter_chi2pr_pl2);
	  h_track_dau_chi2pi_mu->Fill(reco_track_daughter_chi2pi_pl2);
	  h_track_dau_chi2mu_mu->Fill(reco_track_daughter_chi2mu_pl2);
	}
	else if(reco_track_daughter_true_pdg==211){
	  h_track_dau_chi2pr_pi->Fill(reco_track_daughter_chi2pr_pl2);
	  h_track_dau_chi2pi_pi->Fill(reco_track_daughter_chi2pi_pl2);
	  h_track_dau_chi2mu_pi->Fill(reco_track_daughter_chi2mu_pl2);
	}
	else if(reco_track_daughter_true_pdg==11 || reco_track_daughter_true_pdg==-11 || reco_track_daughter_true_pdg==22 ){
	  h_track_dau_chi2pr_sh->Fill(reco_track_daughter_chi2pr_pl2);
	  h_track_dau_chi2pi_sh->Fill(reco_track_daughter_chi2pi_pl2);
	  h_track_dau_chi2mu_sh->Fill(reco_track_daughter_chi2mu_pl2);
	}
	else{
	  h_track_dau_chi2pr_ot->Fill(reco_track_daughter_chi2pr_pl2);
	  h_track_dau_chi2pi_ot->Fill(reco_track_daughter_chi2pi_pl2);
	  h_track_dau_chi2mu_ot->Fill(reco_track_daughter_chi2mu_pl2);
	}

	if(reco_track_daughter_old_true_pdg==2212){
	  h_track_dau_old_chi2pr_pr->Fill(reco_track_daughter_old_chi2pr_pl2);
	  h_track_dau_old_chi2pi_pr->Fill(reco_track_daughter_old_chi2pi_pl2);
	  h_track_dau_old_chi2mu_pr->Fill(reco_track_daughter_old_chi2mu_pl2);
	}
	else if(reco_track_daughter_old_true_pdg==-13){
	  h_track_dau_old_chi2pr_mu->Fill(reco_track_daughter_old_chi2pr_pl2);
	  h_track_dau_old_chi2pi_mu->Fill(reco_track_daughter_old_chi2pi_pl2);
	  h_track_dau_old_chi2mu_mu->Fill(reco_track_daughter_old_chi2mu_pl2);
	}
	else if(reco_track_daughter_old_true_pdg==211){
	  h_track_dau_old_chi2pr_pi->Fill(reco_track_daughter_old_chi2pr_pl2);
	  h_track_dau_old_chi2pi_pi->Fill(reco_track_daughter_old_chi2pi_pl2);
	  h_track_dau_old_chi2mu_pi->Fill(reco_track_daughter_old_chi2mu_pl2);
	}
	else if(reco_track_daughter_old_true_pdg==11 || reco_track_daughter_old_true_pdg==-11 || reco_track_daughter_old_true_pdg==22 ){
	  h_track_dau_old_chi2pr_sh->Fill(reco_track_daughter_old_chi2pr_pl2);
	  h_track_dau_old_chi2pi_sh->Fill(reco_track_daughter_old_chi2pi_pl2);
	  h_track_dau_old_chi2mu_sh->Fill(reco_track_daughter_old_chi2mu_pl2);
	}
	else{
	  h_track_dau_old_chi2pr_ot->Fill(reco_track_daughter_old_chi2pr_pl2);
	  h_track_dau_old_chi2pi_ot->Fill(reco_track_daughter_old_chi2pi_pl2);
	  h_track_dau_old_chi2mu_ot->Fill(reco_track_daughter_old_chi2mu_pl2);
	}

	}

	void Fill3PlPID(){
	if(reco_track_true_pdg==321){
	  h_track_chi2ka_ka->Fill(reco_track_chi2ka_3pl);
	  h_track_chi2pr_ka->Fill(reco_track_chi2pr_3pl);
	}
	else if(reco_track_true_pdg==13){
	  h_track_chi2ka_mu->Fill(reco_track_chi2ka_3pl);
	  h_track_chi2pr_mu->Fill(reco_track_chi2pr_3pl);
	}
	else if(reco_track_true_pdg==211){
	  h_track_chi2ka_pi->Fill(reco_track_chi2ka_3pl);
	  h_track_chi2pr_pi->Fill(reco_track_chi2pr_3pl);
	}
	else if(reco_track_true_pdg==2212){
	  h_track_chi2ka_pr->Fill(reco_track_chi2ka_3pl);
	  h_track_chi2pr_pr->Fill(reco_track_chi2pr_3pl);
	}
	else{
	  h_track_chi2ka_ot->Fill(reco_track_chi2ka_3pl);
	  h_track_chi2pr_ot->Fill(reco_track_chi2pr_3pl);
	}


	if(reco_track_daughter_true_pdg==2212){
	  h_track_dau_chi2pr_pr->Fill(reco_track_daughter_chi2pr_3pl);
	  h_track_dau_chi2pi_pr->Fill(reco_track_daughter_chi2pi_3pl);
	  h_track_dau_chi2mu_pr->Fill(reco_track_daughter_chi2mu_3pl);
	}
	else if(reco_track_daughter_true_pdg==-13){
	  h_track_dau_chi2pr_mu->Fill(reco_track_daughter_chi2pr_3pl);
	  h_track_dau_chi2pi_mu->Fill(reco_track_daughter_chi2pi_3pl);
	  h_track_dau_chi2mu_mu->Fill(reco_track_daughter_chi2mu_3pl);
	}
	else if(reco_track_daughter_true_pdg==211){
	  h_track_dau_chi2pr_pi->Fill(reco_track_daughter_chi2pr_3pl);
	  h_track_dau_chi2pi_pi->Fill(reco_track_daughter_chi2pi_3pl);
	  h_track_dau_chi2mu_pi->Fill(reco_track_daughter_chi2mu_3pl);
	}
	else if(reco_track_daughter_true_pdg==11 || reco_track_daughter_true_pdg==-11 || reco_track_daughter_true_pdg==22 ){
	  h_track_dau_chi2pr_sh->Fill(reco_track_daughter_chi2pr_3pl);
	  h_track_dau_chi2pi_sh->Fill(reco_track_daughter_chi2pi_3pl);
	  h_track_dau_chi2mu_sh->Fill(reco_track_daughter_chi2mu_3pl);
	}
	else{
	  h_track_dau_chi2pr_ot->Fill(reco_track_daughter_chi2pr_3pl);
	  h_track_dau_chi2pi_ot->Fill(reco_track_daughter_chi2pi_3pl);
	  h_track_dau_chi2mu_ot->Fill(reco_track_daughter_chi2mu_3pl);
	}

	if(reco_track_daughter_old_true_pdg==2212){
	  h_track_dau_old_chi2pr_pr->Fill(reco_track_daughter_old_chi2pr_3pl);
	  h_track_dau_old_chi2pi_pr->Fill(reco_track_daughter_old_chi2pi_3pl);
	  h_track_dau_old_chi2mu_pr->Fill(reco_track_daughter_old_chi2mu_3pl);
	}
	else if(reco_track_daughter_old_true_pdg==-13){
	  h_track_dau_old_chi2pr_mu->Fill(reco_track_daughter_old_chi2pr_3pl);
	  h_track_dau_old_chi2pi_mu->Fill(reco_track_daughter_old_chi2pi_3pl);
	  h_track_dau_old_chi2mu_mu->Fill(reco_track_daughter_old_chi2mu_3pl);
	}
	else if(reco_track_daughter_old_true_pdg==211){
	  h_track_dau_old_chi2pr_pi->Fill(reco_track_daughter_old_chi2pr_3pl);
	  h_track_dau_old_chi2pi_pi->Fill(reco_track_daughter_old_chi2pi_3pl);
	  h_track_dau_old_chi2mu_pi->Fill(reco_track_daughter_old_chi2mu_3pl);
	}
	else if(reco_track_daughter_old_true_pdg==11 || reco_track_daughter_old_true_pdg==-11 || reco_track_daughter_old_true_pdg==22 ){
	  h_track_dau_old_chi2pr_sh->Fill(reco_track_daughter_old_chi2pr_3pl);
	  h_track_dau_old_chi2pi_sh->Fill(reco_track_daughter_old_chi2pi_3pl);
	  h_track_dau_old_chi2mu_sh->Fill(reco_track_daughter_old_chi2mu_3pl);
	}
	else{
	  h_track_dau_old_chi2pr_ot->Fill(reco_track_daughter_old_chi2pr_3pl);
	  h_track_dau_old_chi2pi_ot->Fill(reco_track_daughter_old_chi2pi_3pl);
	  h_track_dau_old_chi2mu_ot->Fill(reco_track_daughter_old_chi2mu_3pl);
	}

	}

void FillPrimaryTrack(){

    if(reco_track_true_pdg==321){
      h_track_llr_ka->Fill(reco_track_llrpid_3pl);
      h_track_llrka_ka->Fill(reco_track_llrpid_k_3pl);
    }
    else if(reco_track_true_pdg==13){
      h_track_llr_mu->Fill(reco_track_llrpid_3pl); 
      h_track_llrka_mu->Fill(reco_track_llrpid_k_3pl);
    }
    else if(reco_track_true_pdg==211){
      h_track_llr_pi->Fill(reco_track_llrpid_3pl);
      h_track_llrka_pi->Fill(reco_track_llrpid_k_3pl);
    }
    else if(reco_track_true_pdg==2212){
      h_track_llr_pr->Fill(reco_track_llrpid_3pl);
      h_track_llrka_pr->Fill(reco_track_llrpid_k_3pl);
    }
    else{
      h_track_llr_ot->Fill(reco_track_llrpid_3pl); 
      h_track_llrka_ot->Fill(reco_track_llrpid_k_3pl);
    }
    
    h_reco_track_length->Fill(reco_track_length);
    h_reco_track_daughter_distance->Fill(reco_track_daughter_distance);
    h_reco_track_daughter_vtx_distance->Fill(reco_track_daughter_vtx_distance);
    
    if(true_kaon_end_process == 0) n0++; 
    if(true_kaon_end_process == 1) n1++;
    if(true_kaon_end_process == 2) n2++;
    if(true_kaon_end_process == 3) n3++;
    if(true_kaon_end_process == 4) n4++;
    if(true_kaon_end_process == 5) n5++; 
    
}

void AddStackHistos(){

  s_chi2ka->Add(h_track_chi2ka_ka);
  s_chi2ka->Add(h_track_chi2ka_pr);
  s_chi2ka->Add(h_track_chi2ka_pi);
  s_chi2ka->Add(h_track_chi2ka_mu);
  s_chi2ka->Add(h_track_chi2ka_ot);
  
  s_chi2pr->Add(h_track_chi2pr_ka);
  s_chi2pr->Add(h_track_chi2pr_pr);
  s_chi2pr->Add(h_track_chi2pr_pi);
  s_chi2pr->Add(h_track_chi2pr_mu);
  s_chi2pr->Add(h_track_chi2pr_ot);

  s_llr->Add(h_track_llr_pr);
  s_llr->Add(h_track_llr_ka);
  s_llr->Add(h_track_llr_ot);
  s_llr->Add(h_track_llr_mu);
  s_llr->Add(h_track_llr_pi);
  /*
  s_llr->Add(h_track_llr_ka);
  s_llr->Add(h_track_llr_pr);
  s_llr->Add(h_track_llr_pi);
  s_llr->Add(h_track_llr_mu);
  s_llr->Add(h_track_llr_ot);
  */
  s_llrka->Add(h_track_llrka_ka);
  s_llrka->Add(h_track_llrka_pr);
  s_llrka->Add(h_track_llrka_pi);
  s_llrka->Add(h_track_llrka_mu);
  s_llrka->Add(h_track_llrka_ot);

  s_llr_dau->Add(h_track_dau_llr_pr);
  s_llr_dau->Add(h_track_dau_llr_mu);
  s_llr_dau->Add(h_track_dau_llr_pi);
  s_llr_dau->Add(h_track_dau_llr_sh);
  s_llr_dau->Add(h_track_dau_llr_ot);

  s_llrka_dau->Add(h_track_dau_llrka_pr);
  s_llrka_dau->Add(h_track_dau_llrka_mu);
  s_llrka_dau->Add(h_track_dau_llrka_pi);
  s_llrka_dau->Add(h_track_dau_llrka_sh);
  s_llrka_dau->Add(h_track_dau_llrka_ot);

  s_chi2pr_dau->Add(h_track_dau_chi2pr_pr);
  s_chi2pr_dau->Add(h_track_dau_chi2pr_mu);
  s_chi2pr_dau->Add(h_track_dau_chi2pr_pi);
  s_chi2pr_dau->Add(h_track_dau_chi2pr_sh);
  s_chi2pr_dau->Add(h_track_dau_chi2pr_ot);

  s_chi2pi_dau->Add(h_track_dau_chi2pi_pr);
  s_chi2pi_dau->Add(h_track_dau_chi2pi_mu);
  s_chi2pi_dau->Add(h_track_dau_chi2pi_pi);
  s_chi2pi_dau->Add(h_track_dau_chi2pi_sh);
  s_chi2pi_dau->Add(h_track_dau_chi2pi_ot);

  s_chi2mu_dau->Add(h_track_dau_chi2mu_pr);
  s_chi2mu_dau->Add(h_track_dau_chi2mu_mu);
  s_chi2mu_dau->Add(h_track_dau_chi2mu_pi);
  s_chi2mu_dau->Add(h_track_dau_chi2mu_sh);
  s_chi2mu_dau->Add(h_track_dau_chi2mu_ot);


  s_trkln_dau->Add(h_track_dau_ln_pi);
  s_trkln_dau->Add(h_track_dau_ln_mu);
  s_trkln_dau->Add(h_track_dau_ln_sh);
  s_trkln_dau->Add(h_track_dau_ln_pr);
  s_trkln_dau->Add(h_track_dau_ln_ot);

  s_trkln_dau_hy->Add(h_track_dau_ln_pi_hy);
  s_trkln_dau_hy->Add(h_track_dau_ln_mu_hy);
  s_trkln_dau_hy->Add(h_track_dau_ln_sh_hy);
  s_trkln_dau_hy->Add(h_track_dau_ln_pr_hy);
  s_trkln_dau_hy->Add(h_track_dau_ln_ot_hy);


  s_llr_dau_old->Add(h_track_dau_old_llr_pr);
  s_llr_dau_old->Add(h_track_dau_old_llr_mu);
  s_llr_dau_old->Add(h_track_dau_old_llr_pi);
  s_llr_dau_old->Add(h_track_dau_old_llr_sh);
  s_llr_dau_old->Add(h_track_dau_old_llr_ot);

  s_llrka_dau_old->Add(h_track_dau_old_llrka_pr);
  s_llrka_dau_old->Add(h_track_dau_old_llrka_mu);
  s_llrka_dau_old->Add(h_track_dau_old_llrka_pi);
  s_llrka_dau_old->Add(h_track_dau_old_llrka_sh);
  s_llrka_dau_old->Add(h_track_dau_old_llrka_ot);

  s_chi2pr_dau_old->Add(h_track_dau_old_chi2pr_pr);
  s_chi2pr_dau_old->Add(h_track_dau_old_chi2pr_mu);
  s_chi2pr_dau_old->Add(h_track_dau_old_chi2pr_pi);
  s_chi2pr_dau_old->Add(h_track_dau_old_chi2pr_sh);
  s_chi2pr_dau_old->Add(h_track_dau_old_chi2pr_ot);

  s_chi2pi_dau_old->Add(h_track_dau_old_chi2pi_pr);
  s_chi2pi_dau_old->Add(h_track_dau_old_chi2pi_mu);
  s_chi2pi_dau_old->Add(h_track_dau_old_chi2pi_pi);
  s_chi2pi_dau_old->Add(h_track_dau_old_chi2pi_sh);
  s_chi2pi_dau_old->Add(h_track_dau_old_chi2pi_ot);

  s_chi2mu_dau_old->Add(h_track_dau_old_chi2mu_pr);
  s_chi2mu_dau_old->Add(h_track_dau_old_chi2mu_mu);
  s_chi2mu_dau_old->Add(h_track_dau_old_chi2mu_pi);
  s_chi2mu_dau_old->Add(h_track_dau_old_chi2mu_sh);
  s_chi2mu_dau_old->Add(h_track_dau_old_chi2mu_ot);


  s_trkln_dau_old->Add(h_track_dau_old_ln_pi);
  s_trkln_dau_old->Add(h_track_dau_old_ln_mu);
  s_trkln_dau_old->Add(h_track_dau_old_ln_sh);
  s_trkln_dau_old->Add(h_track_dau_old_ln_pr);
  s_trkln_dau_old->Add(h_track_dau_old_ln_ot);


}

void AddLegend(){
  l_ka = new TLegend(0.75,0.65,0.95,0.95);
  l_ka->AddEntry(h_track_chi2ka_ka, "True K^{+}"  , "f");
  l_ka->AddEntry(h_track_chi2ka_pr, "True p" , "f");
  l_ka->AddEntry(h_track_chi2ka_pi, "True #pi^{+}"   , "f");
  l_ka->AddEntry(h_track_chi2ka_mu, "True #mu^{-}"   , "f");
  l_ka->AddEntry(h_track_chi2ka_ot, "Others"   , "f");

  l_pr = new TLegend(0.75,0.65,0.95,0.95);
  l_pr->AddEntry(h_track_chi2pr_ka, "True K^{+}"  , "f");
  l_pr->AddEntry(h_track_chi2pr_pr, "True p" , "f");
  l_pr->AddEntry(h_track_chi2pr_pi, "True #pi^{+}"   , "f");
  l_pr->AddEntry(h_track_chi2pr_mu, "True #mu^{-}"   , "f");
  l_pr->AddEntry(h_track_chi2pr_ot, "Others"   , "f");

  l_pr_dau = new TLegend(0.75,0.65,0.95,0.95);
  l_pr_dau->AddEntry(h_track_dau_chi2pr_pr, "True p" , "f");
  l_pr_dau->AddEntry(h_track_dau_chi2pr_pi, "True #pi^{+}"   , "f");
  l_pr_dau->AddEntry(h_track_dau_chi2pr_mu, "True #mu^{+}"   , "f");
  l_pr_dau->AddEntry(h_track_dau_chi2pr_sh, "True shower"   , "f");
  l_pr_dau->AddEntry(h_track_dau_chi2pr_ot, "Others"   , "f");

  /*
  l_pr_dau_ln = new TLegend(0.75,0.65,0.95,0.95);
  l_pr_dau_ln->AddEntry(h_track_dau_ln_pr, "True p" , "f");
  l_pr_dau_ln->AddEntry(h_track_dau_ln_pi, "True #pi^{+}"   , "f");
  l_pr_dau_ln->AddEntry(h_track_dau_ln_mu, "True #mu^{+}"   , "f");
  l_pr_dau_ln->AddEntry(h_track_dau_ln_sh, "True shower"   , "f");
  l_pr_dau_ln->AddEntry(h_track_dau_ln_ot, "Others"   , "f");
  */
  l_pr_dau_ln = new TLegend(0.65,0.55,0.85,0.85);
  l_pr_dau_ln->SetBorderSize(0);
  l_pr_dau_ln->AddEntry(h_track_dau_ln_mu, "True #mu^{+}"   , "f");
  l_pr_dau_ln->AddEntry(h_track_dau_ln_pi, "True #pi^{+}"   , "f");
  l_pr_dau_ln->AddEntry(h_track_dau_ln_pr, "True p" , "l");
  l_pr_dau_ln->AddEntry(h_track_dau_ln_sh, "True shower"   , "l");
  l_pr_dau_ln->AddEntry(h_track_dau_ln_ot, "Others"   , "l");

  l_pr_dau2 = new TLegend(0.15,0.58,0.35,0.88);
  l_pr_dau2->AddEntry(h_track_dau_chi2pr_pr, "True p" , "f");
  l_pr_dau2->AddEntry(h_track_dau_chi2pr_pi, "True #pi^{+}"   , "f");
  l_pr_dau2->AddEntry(h_track_dau_chi2pr_mu, "True #mu^{+}"   , "f");
  l_pr_dau2->AddEntry(h_track_dau_chi2pr_sh, "True shower"   , "f");
  l_pr_dau2->AddEntry(h_track_dau_chi2pr_ot, "Others"   , "f");

  h_reco_track_daughter_vtx_distance->SetLineColor(kRed);
  h_reco_track_daughter_distance->SetLineColor(kBlue);
  h_reco_track_length->SetLineColor(kBlack);

}

void DrawHistos(TCanvas* &c,TString output_name){
  
  /*
  h_reco_track_daughter_vtx_distance->Draw();
  h_reco_track_daughter_distance->Draw("same");
  h_reco_track_length->Draw("same");
  c->Print(output_name);
  

  //s_chi2ka->Draw();
  s_chi2ka->Draw("nostack");
  l_pr->Draw();
  c->Print(output_name);
  
  //s_chi2pr->Draw();
  s_chi2pr->Draw("nostack");
  l_pr->Draw();
  c->Print(output_name);
  
  //s_llr->Draw();
  s_llr->Draw("nostack");
  l_pr->Draw();
  c->Print(output_name);
  
  //s_llrka->Draw();
  s_llrka->Draw("nostack");
  l_pr->Draw();
  c->Print(output_name);
  
  //s_chi2pr_dau->Draw();
  s_chi2pr_dau->Draw("nostack");
  //l_pr_dau->Draw();
  c->Print(output_name);
  
  //s_chi2pi_dau->Draw();
  s_chi2pi_dau->Draw("nostack");
  //l_pr_dau->Draw();
  c->Print(output_name);
  
  //s_chi2mu_dau->Draw();
  s_chi2mu_dau->Draw("nostack");
  //l_pr_dau->Draw();
  c->Print(output_name);
  
  //s_llr_dau->Draw();
  s_llr_dau->Draw("nostack");
  l_pr_dau2->Draw();
  c->Print(output_name);
  
  //s_llrka_dau->Draw();
  s_llrka_dau->Draw("nostack");
  l_pr_dau2->Draw();
  c->Print(output_name);
  */
  
  //s_trkln_dau->Draw();
// Usage example:
  int maximum = GetMaxBinContentFromStack(s_trkln_dau_hy);
  maximum *= 1.05;

  s_trkln_dau->SetMaximum(maximum);
  s_trkln_dau->Draw("nostack");
  l_pr_dau_ln->Draw();
  c->Print(output_name);
  
  //s_trkln_dau->Draw();
  s_trkln_dau_hy->SetMaximum(maximum);
  s_trkln_dau_hy->Draw("nostack");
  l_pr_dau_ln->Draw();
  c->Print(output_name);
  
  /*
  //s_chi2pr_dau_old->Draw();
  s_chi2pr_dau_old->Draw("nostack");
  //l_pr_dau->Draw();
  c->Print(output_name);
  
  //s_chi2pi_dau_old->Draw();
  s_chi2pi_dau_old->Draw("nostack");
  //l_pr_dau->Draw();
  c->Print(output_name);
  
  //s_chi2mu_dau_old->Draw();
  s_chi2mu_dau_old->Draw("nostack");
  //l_pr_dau->Draw();
  c->Print(output_name);
  
  //s_llr_dau_old->Draw();
  s_llr_dau_old->Draw("nostack");
  l_pr_dau2->Draw();
  c->Print(output_name);
  
  //s_llrka_dau_old->Draw();
  s_llrka_dau_old->Draw("nostack");
  l_pr_dau2->Draw();
  c->Print(output_name);
  */
  
  //s_trkln_dau_old->Draw();
  s_trkln_dau_old->SetMaximum(maximum); 
  s_trkln_dau_old->Draw("nostack");
  l_pr_dau_ln->Draw();
  c->Print(output_name);
  
  
}

double GetMaxBinContentFromStack(THStack *stack) {
  double maxBinContent = 0;

  // THStack::GetHists returns a TList of histograms
  TList* histList = stack->GetHists();
  if (!histList) return maxBinContent; // Return 0 if no histograms

  TIter next(histList);
  TH1* hist;
  while ((hist = (TH1*)next())) {
    // Get the maximum content of the current histogram
    double currentMax = hist->GetBinContent(hist->GetMaximumBin());
    if (currentMax > maxBinContent) {
      maxBinContent = currentMax;
    }
  }

  return maxBinContent;
}

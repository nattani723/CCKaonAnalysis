#include <iostream>
#include <TH2D.h>
#include <TFile.h>
#include <TROOT.h>
#include <TChain.h>
#include <TTree.h>
#include <TVectorT.h>
#include <vector>
#include <iostream>
#include <stdio.h>
#include <string.h>


void Initialise();
void GeneratePlots(TFile *f, TString pl, TCanvas* &c, TString output_name);
void DrawChi2(TFile *f, TString pr, TString pr2, TString pl, TString trdau, TCanvas* &c, TString output_name);
void RebuildTrackHist(TString input_name, TString output_name, TString pl);



// Cuts
TString output_pdf_trk = "chi2_trk.pdf";
TString output_pdf_dau = "chi2_dau.pdf";;
int n0 = 0;
int n1 = 0;
int n2 = 0;
int n3 = 0;
int n4 = 0;
//int n5 = 0;
double n5=0;


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
}

void RebuildTrackHist()
{
  //RebuildTrackHist("/exp/uboone/app/users/taniuchi/KaonAna/KaonAnlysis/Ana/track_tuple/refine_debug_2.root", "test2.pdf", "3pl");
  RebuildTrackHist("/exp/uboone/app/users/taniuchi/51_pandora/tool/track_tuple/rootfile/refine_debug_2.root", "test.pdf", "3pl");

}

void RebuildTrackHist(TString input_name, TString output_name, TString pl)
{
  TGaxis::SetMaxDigits(3);
  gErrorIgnoreLevel = kWarning;

  //output from PreCutHistos
  //TFile * f = new TFile("/uboone/app/users/taniuchi/KaonAna/KaonAnlysis/Ana/TMVA/Jun28/TMVA_all_pl2.root");
  TFile * f = new TFile(input_name);

  Initialise;

  TCanvas * c = new TCanvas("c", "c", 800, 600);
  c->SetFillStyle(4000);
  gStyle->SetOptStat(0);
  c->Print(Form("%s[", output_name.Data()));
  //c->Print(Form("%s[", output_name.Data()));

  GeneratePlots(f, pl, c, output_name);
  
  c->Print(Form("%s]", output_name.Data()));
  //c->Print(Form("%s]", output_name.Data()));

}

void GeneratePlots(TFile *f, TString pl, TCanvas* &c, TString output_name)
{
  DrawChi2(f, "ka", "pr", pl, "track", c, output_name);
}

//void Draw(TFile *f, TString var, double scale, int dencut, bool print)
void DrawChi2(TFile *f, TString pr, TString pr2, TString pl, TString trdau, TCanvas* &c, TString output_name)
{
  TString fname(f->GetName());

  TTree * t;
  if(fname.Contains("TMVA")){
    t = (TTree*) f->Get("dataset_tree325_node4_depth4_beta60_frac12_ncut5_addspec/TestTree");
  }else{
    t = (TTree*) f->Get("CCKaonTracks");
  }

  int nentry = t->GetEntries();

  Float_t true_dau_pip_length;
  Float_t true_dau_muon_length;

  Float_t reco_track_daughter_old_length;
  Float_t reco_track_daughter_old_chi2ka_pl2;
  Float_t reco_track_daughter_old_chi2pr_pl2;
  Float_t reco_track_daughter_old_chi2pi_pl2;
  Float_t reco_track_daughter_old_chi2mu_pl2;
  Float_t reco_track_daughter_old_llrpid_pl2;
  Float_t reco_track_daughter_old_chi2ka_3pl;
  Float_t reco_track_daughter_old_chi2pr_3pl;
  Float_t reco_track_daughter_old_chi2pi_3pl;
  Float_t reco_track_daughter_old_chi2mu_3pl;
  Float_t reco_track_daughter_old_llrpid_3pl;
  Float_t reco_track_daughter_old_llrpid_k_3pl;
  Float_t reco_track_daughter_old_Bragg_fwd_ka_pl2;
  Float_t reco_track_daughter_old_Bragg_fwd_pr_pl2;
  Float_t reco_track_daughter_old_Bragg_fwd_pi_pl2;
  Float_t reco_track_daughter_old_Bragg_fwd_mu_pl2;

  Float_t reco_track_length;
  Float_t reco_track_distance;
  Float_t reco_track_daughter_length;
  Float_t reco_track_daughter_distance;
  Float_t reco_track_daughter_vtx_distance;
  Float_t reco_track_chi2ka_pl2;
  Float_t reco_track_chi2pr_pl2;
  Float_t reco_track_chi2pi_pl2;
  Float_t reco_track_chi2mu_pl2;
  Float_t reco_track_llrpid_pl2;
  Float_t reco_track_daughter_chi2ka_pl2;
  Float_t reco_track_daughter_chi2pr_pl2;
  Float_t reco_track_daughter_chi2pi_pl2;
  Float_t reco_track_daughter_chi2mu_pl2;
  Float_t reco_track_daughter_llrpid_pl2;
  Float_t reco_track_chi2ka_3pl;
  Float_t reco_track_chi2pr_3pl;
  Float_t reco_track_chi2pi_3pl;
  Float_t reco_track_chi2mu_3pl;
  Float_t reco_track_llrpid_3pl;
  Float_t reco_track_llrpid_k_3pl;
  Float_t reco_track_daughter_chi2ka_3pl;
  Float_t reco_track_daughter_chi2pr_3pl;
  Float_t reco_track_daughter_chi2pi_3pl;
  Float_t reco_track_daughter_chi2mu_3pl;
  Float_t reco_track_daughter_llrpid_3pl;
  Float_t reco_track_daughter_llrpid_k_3pl;
  Float_t reco_track_Bragg_fwd_ka_pl2;
  Float_t reco_track_Bragg_fwd_pr_pl2;
  Float_t reco_track_Bragg_fwd_pi_pl2;
  Float_t reco_track_Bragg_fwd_mu_pl2;

  
  //Int_t reco_track_true_pdg;
  Float_t reco_track_daughter_true_pdg;
  Float_t reco_track_daughter_old_true_pdg;
  Float_t BDT;
  Float_t true_kaon_ke;
  Float_t true_kaon_length;
  Int_t true_kaon_end_process;

  Int_t true_nu_pdg, true_nu_ccnc, true_nu_vtx_inCCInclusiveTPC, true_kaon_end_inCCInclusiveTPC, true_kaon_daughter_end_in5cmTPC, reco_track_true_pdg;
  //Float_t true_nu_pdg, true_nu_ccnc, true_nu_vtx_inCCInclusiveTPC, true_kaon_end_inCCInclusiveTPC, true_kaon_daughter_end_in5cmTPC, reco_track_true_pdg;

  /*
  if(fname.Contains("TMVA")){
    cout << "aa" << endl;
    Float_t true_nu_pdg, true_nu_ccnc, true_kaon_ke, true_nu_vtx_inCCInclusiveTPC, true_kaon_end_inCCInclusiveTPC, true_kaon_daughter_end_in5cmTPC, reco_track_true_pdg;
  }else if(fname.Contains("7Nov")){
    cout << "bb" << endl;
    Int_t true_nu_pdg, true_nu_ccnc, true_nu_vtx_inCCInclusiveTPC, true_kaon_end_inCCInclusiveTPC, true_kaon_daughter_end_in5cmTPC, reco_track_true_pdg;
  }
  */


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

  /*
  TH2D * h_chi2_trk_pr_ka = new TH2D("h_chi2_trk_pr_ka", "Track #chi^{2}_{P} vs #chi^{2}_{K};  #chi^{2}_{P}; #chi^{2}_{K}", 100, 0 , 50, 100, 0, 50);
  TH2D * h_chi2_trk_pr_ka_bg = new TH2D("h_chi2_trk_pr_ka_bg", "Track #chi^{2}_{P} vs #chi^{2}_{K};  #chi^{2}_{P}; #chi^{2}_{K}", 100, 0 , 50, 100, 0, 50);
  TH2D * h_chi2_trk_pr_ka_sig = new TH2D("h_chi2_trk_pr_ka_sig", "Track #chi^{2}_{P} vs #chi^{2}_{K};  #chi^{2}_{P}; #chi^{2}_{K}", 100, 0 , 50, 100, 0, 50);
  TH2D * h_chi2_trk_pi_ka = new TH2D("h_chi2_trk_pi_ka", "Track #chi^{2}_{#pi} vs #chi^{2}_{K}; #chi^{2}_{#pi}; #chi^{2}_{K}", 100, 0 , 100, 100, 0, 100);
  TH2D * h_chi2_trk_mu_ka = new TH2D("h_chi2_trk_mu_ka", "Track #chi^{2}_{#mu} vs #chi^{2}_{K}; #chi^{2}_{#mu}, #chi^{2}_{K}", 100, 0 , 100, 100, 0, 100);

  TH2D * h_chi2_dau_pr_mu = new TH2D("h_chi2_dau_pr_mu", "Daughter #chi^{2}_{P} vs #chi^{2}_{#mu}; #chi^{2}_{P}; #chi^{2}_{#mu}",100, 0 , 100, 100, 0, 100);
  TH2D * h_chi2_dau_pi_mu = new TH2D("h_chi2_trk_pi_mu", "Daughter #chi^{2}_{#pi} vs #chi^{2}_{#mu}; #chi^{2}_{#pi}; #chi^{2}_{#mu}", 100, 0 , 100, 100, 0, 100);
  TH2D * h_chi2_dau_ka_mu = new TH2D("h_chi2_trk_ka_mu", "Daughter #chi^{2}_{K} vs #chi^{2}_{#mu}; #chi^{2}_{K}; #chi^{2}_{#mu}", 100, 0 , 100, 100, 0, 50);
  TH2D * h_chi2_dau_pr_pi = new TH2D("h_chi2_dau_pr_pi", "Daughter #chi^{2}_{P} vs #chi^{2}_{#pi}; #chi^{2}_{P}; #chi^{2}_{#pi}", 100, 0 , 100, 100, 0, 100);
  TH2D * h_chi2_dau_mu_pi = new TH2D("h_chi2_trk_mu_pi", "Daughter #chi^{2}_{#mu} vs #chi^{2}_{#pi}; #chi^{2}_{#mu}; #chi^{2}_{#pi}", 100, 0 , 100, 100, 0, 100);
  TH2D * h_chi2_dau_ka_pi = new TH2D("h_chi2_trk_ka_pi", "Daughter #chi^{2}_{K} vs #chi^{2}_{#pi}; #chi^{2}_{K}; #chi^{2}_{#pi}", 100, 0 , 100, 100, 0, 100);
  */

  TH1D * h_track_chi2ka_ka = new TH1D("BDT_track_kaka", "; BDT Response; Number of Events", 50, 0, 100);
  TH1D * h_track_chi2ka_pr = new TH1D("BDT_track_kapr", "; BDT Response; Number of Events", 50, 0, 100);
  TH1D * h_track_chi2ka_pi = new TH1D("BDT_track_kapi", "; BDT Response; Number of Events", 50, 0, 100);
  TH1D * h_track_chi2ka_mu = new TH1D("BDT_track_kamu", "; BDT Response; Number of Events", 50, 0, 100);
  TH1D * h_track_chi2ka_ot = new TH1D("BDT_track_kaot", "; BDT Response; Number of Events", 50, 0, 100);

  TH1D * h_track_chi2pr_ka = new TH1D("BDT_track_prka", "; BDT Response; Number of Events", 50, 0, 100);
  TH1D * h_track_chi2pr_pr = new TH1D("BDT_track_prpr", "; BDT Response; Number of Events", 50, 0, 100);
  TH1D * h_track_chi2pr_pi = new TH1D("BDT_track_prpi", "; BDT Response; Number of Events", 50, 0, 100);
  TH1D * h_track_chi2pr_mu = new TH1D("BDT_track_prmu", "; BDT Response; Number of Events", 50, 0, 100);
  TH1D * h_track_chi2pr_ot = new TH1D("BDT_track_prot", "; BDT Response; Number of Events", 50, 0, 100);

  TH1D * h_track_llr_ka = new TH1D("BDT_track_llrka", "; BDT Response; Number of Events", 50, -1, 1);
  TH1D * h_track_llr_pr = new TH1D("BDT_track_llrpr", "; BDT Response; Number of Events", 50, -1, 1);
  TH1D * h_track_llr_pi = new TH1D("BDT_track_llrpi", "; BDT Response; Number of Events", 50, -1, 1);
  TH1D * h_track_llr_mu = new TH1D("BDT_track_llrmu", "; BDT Response; Number of Events", 50, -1, 1);
  TH1D * h_track_llr_ot = new TH1D("BDT_track_llrot", "; BDT Response; Number of Events", 50, -1, 1);

  TH1D * h_track_llrka_ka = new TH1D("BDT_track_llrkaka", "; BDT Response; Number of Events", 50, -1, 1);
  TH1D * h_track_llrka_pr = new TH1D("BDT_track_llrkapr", "; BDT Response; Number of Events", 50, -1, 1);
  TH1D * h_track_llrka_pi = new TH1D("BDT_track_llrkapi", "; BDT Response; Number of Events", 50, -1, 1);
  TH1D * h_track_llrka_mu = new TH1D("BDT_track_llrkamu", "; BDT Response; Number of Events", 50, -1, 1);
  TH1D * h_track_llrka_ot = new TH1D("BDT_track_llrkaot", "; BDT Response; Number of Events", 50, -1, 1);

  //

  TH1D * h_track_dau_llr_pr = new TH1D("BDT_track_dau_llapr", "; BDT Response; Number of Events", 50, -1, 1);
  TH1D * h_track_dau_llr_pi = new TH1D("BDT_track_dau_llrpi", "; BDT Response; Number of Events", 50, -1, 1);
  TH1D * h_track_dau_llr_mu = new TH1D("BDT_track_dau_llrmu", "; BDT Response; Number of Events", 50, -1, 1);
  TH1D * h_track_dau_llr_sh = new TH1D("BDT_track_dau_llrsh", "; BDT Response; Number of Events", 50, -1, 1);
  TH1D * h_track_dau_llr_ot = new TH1D("BDT_track_dau_llrot", "; BDT Response; Number of Events", 50, -1, 1);

  TH1D * h_track_dau_llrka_pr = new TH1D("BDT_track_dau_llapr", "; BDT Response; Number of Events", 50, -1, 1);
  TH1D * h_track_dau_llrka_pi = new TH1D("BDT_track_dau_llrpi", "; BDT Response; Number of Events", 50, -1, 1);
  TH1D * h_track_dau_llrka_mu = new TH1D("BDT_track_dau_llrmu", "; BDT Response; Number of Events", 50, -1, 1);
  TH1D * h_track_dau_llrka_sh = new TH1D("BDT_track_dau_llrsh", "; BDT Response; Number of Events", 50, -1, 1);
  TH1D * h_track_dau_llrka_ot = new TH1D("BDT_track_dau_llrot", "; BDT Response; Number of Events", 50, -1, 1);

  TH1D * h_track_dau_chi2pr_pr = new TH1D("BDT_track_dau_prpr", "; BDT Response; Number of Events", 50, 0, 150);
  TH1D * h_track_dau_chi2pr_pi = new TH1D("BDT_track_dau_prpi", "; BDT Response; Number of Events", 50, 0, 150);
  TH1D * h_track_dau_chi2pr_mu = new TH1D("BDT_track_dau_prmu", "; BDT Response; Number of Events", 50, 0, 150);
  TH1D * h_track_dau_chi2pr_sh = new TH1D("BDT_track_dau_prsh", "; BDT Response; Number of Events", 50, 0, 150);
  TH1D * h_track_dau_chi2pr_ot = new TH1D("BDT_track_dau_prot", "; BDT Response; Number of Events", 50, 0, 150);

  TH1D * h_track_dau_chi2pi_pr = new TH1D("BDT_track_dau_prpr", "; BDT Response; Number of Events", 50, 0, 100);
  TH1D * h_track_dau_chi2pi_pi = new TH1D("BDT_track_dau_prpi", "; BDT Response; Number of Events", 50, 0, 100);
  TH1D * h_track_dau_chi2pi_mu = new TH1D("BDT_track_dau_prmu", "; BDT Response; Number of Events", 50, 0, 100);
  TH1D * h_track_dau_chi2pi_sh = new TH1D("BDT_track_dau_prsh", "; BDT Response; Number of Events", 50, 0, 100);
  TH1D * h_track_dau_chi2pi_ot = new TH1D("BDT_track_dau_prot", "; BDT Response; Number of Events", 50, 0, 100);

  TH1D * h_track_dau_chi2mu_pr = new TH1D("BDT_track_dau_mupr", "; BDT Response; Number of Events", 50, 0, 100);
  TH1D * h_track_dau_chi2mu_pi = new TH1D("BDT_track_dau_mupi", "; BDT Response; Number of Events", 50, 0, 100);
  TH1D * h_track_dau_chi2mu_mu = new TH1D("BDT_track_dau_mumu", "; BDT Response; Number of Events", 50, 0, 100);
  TH1D * h_track_dau_chi2mu_sh = new TH1D("BDT_track_dau_mush", "; BDT Response; Number of Events", 50, 0, 100);
  TH1D * h_track_dau_chi2mu_ot = new TH1D("BDT_track_dau_muot", "; BDT Response; Number of Events", 50, 0, 100);

  TH1D * h_track_dau_ln_pr = new TH1D("track_dau_ln_pr", "; BDT Response; Number of Events", 50, 0, 100);
  TH1D * h_track_dau_ln_pi = new TH1D("track_dau_ln_pi", "; BDT Response; Number of Events", 50, 0, 100);
  TH1D * h_track_dau_ln_mu = new TH1D("track_dau_ln_mu", "; BDT Response; Number of Events", 50, 0, 100);
  TH1D * h_track_dau_ln_sh = new TH1D("track_dau_ln_sh", "; BDT Response; Number of Events", 50, 0, 100);
  TH1D * h_track_dau_ln_ot = new TH1D("track_dau_ln_ot", "; BDT Response; Number of Events", 50, 0, 100);

  //

  TH1D * h_track_dau_old_llr_pr = new TH1D("BDT_track_dau_old_llapr", "; BDT Response; Number of Events", 50, -1, 1);
  TH1D * h_track_dau_old_llr_pi = new TH1D("BDT_track_dau_old_llrpi", "; BDT Response; Number of Events", 50, -1, 1);
  TH1D * h_track_dau_old_llr_mu = new TH1D("BDT_track_dau_old_llrmu", "; BDT Response; Number of Events", 50, -1, 1);
  TH1D * h_track_dau_old_llr_sh = new TH1D("BDT_track_dau_old_llrsh", "; BDT Response; Number of Events", 50, -1, 1);
  TH1D * h_track_dau_old_llr_ot = new TH1D("BDT_track_dau_old_llrot", "; BDT Response; Number of Events", 50, -1, 1);

  TH1D * h_track_dau_old_llrka_pr = new TH1D("BDT_track_dau_old_llapr", "; BDT Response; Number of Events", 50, -1, 1);
  TH1D * h_track_dau_old_llrka_pi = new TH1D("BDT_track_dau_old_llrpi", "; BDT Response; Number of Events", 50, -1, 1);
  TH1D * h_track_dau_old_llrka_mu = new TH1D("BDT_track_dau_old_llrmu", "; BDT Response; Number of Events", 50, -1, 1);
  TH1D * h_track_dau_old_llrka_sh = new TH1D("BDT_track_dau_old_llrsh", "; BDT Response; Number of Events", 50, -1, 1);
  TH1D * h_track_dau_old_llrka_ot = new TH1D("BDT_track_dau_old_llrot", "; BDT Response; Number of Events", 50, -1, 1);

  TH1D * h_track_dau_old_chi2pr_pr = new TH1D("BDT_track_dau_old_prpr", "; BDT Response; Number of Events", 50, 0, 150);
  TH1D * h_track_dau_old_chi2pr_pi = new TH1D("BDT_track_dau_old_prpi", "; BDT Response; Number of Events", 50, 0, 150);
  TH1D * h_track_dau_old_chi2pr_mu = new TH1D("BDT_track_dau_old_prmu", "; BDT Response; Number of Events", 50, 0, 150);
  TH1D * h_track_dau_old_chi2pr_sh = new TH1D("BDT_track_dau_old_prsh", "; BDT Response; Number of Events", 50, 0, 150);
  TH1D * h_track_dau_old_chi2pr_ot = new TH1D("BDT_track_dau_old_prot", "; BDT Response; Number of Events", 50, 0, 150);

  TH1D * h_track_dau_old_chi2pi_pr = new TH1D("BDT_track_dau_old_prpr", "; BDT Response; Number of Events", 50, 0, 100);
  TH1D * h_track_dau_old_chi2pi_pi = new TH1D("BDT_track_dau_old_prpi", "; BDT Response; Number of Events", 50, 0, 100);
  TH1D * h_track_dau_old_chi2pi_mu = new TH1D("BDT_track_dau_old_prmu", "; BDT Response; Number of Events", 50, 0, 100);
  TH1D * h_track_dau_old_chi2pi_sh = new TH1D("BDT_track_dau_old_prsh", "; BDT Response; Number of Events", 50, 0, 100);
  TH1D * h_track_dau_old_chi2pi_ot = new TH1D("BDT_track_dau_old_prot", "; BDT Response; Number of Events", 50, 0, 100);

  TH1D * h_track_dau_old_chi2mu_pr = new TH1D("BDT_track_dau_old_mupr", "; BDT Response; Number of Events", 50, 0, 100);
  TH1D * h_track_dau_old_chi2mu_pi = new TH1D("BDT_track_dau_old_mupi", "; BDT Response; Number of Events", 50, 0, 100);
  TH1D * h_track_dau_old_chi2mu_mu = new TH1D("BDT_track_dau_old_mumu", "; BDT Response; Number of Events", 50, 0, 100);
  TH1D * h_track_dau_old_chi2mu_sh = new TH1D("BDT_track_dau_old_mush", "; BDT Response; Number of Events", 50, 0, 100);
  TH1D * h_track_dau_old_chi2mu_ot = new TH1D("BDT_track_dau_old_muot", "; BDT Response; Number of Events", 50, 0, 100);

  TH1D * h_track_dau_old_ln_pr = new TH1D("track_dau_old_ln_pr", "; BDT Response; Number of Events", 50, 0, 100);
  TH1D * h_track_dau_old_ln_pi = new TH1D("track_dau_old_ln_pi", "; BDT Response; Number of Events", 50, 0, 100);
  TH1D * h_track_dau_old_ln_mu = new TH1D("track_dau_old_ln_mu", "; BDT Response; Number of Events", 50, 0, 100);
  TH1D * h_track_dau_old_ln_sh = new TH1D("track_dau_old_ln_sh", "; BDT Response; Number of Events", 50, 0, 100);
  TH1D * h_track_dau_old_ln_ot = new TH1D("track_dau_old_ln_ot", "; BDT Response; Number of Events", 50, 0, 100);



  /*
  TH1D * h_track_dau_dis_ln_pr = new TH1D("track_dau_dis_ln_pr", "; BDT Response; Number of Events", 50, 0, 10);
  TH1D * h_track_dau_dis_ln_pi = new TH1D("track_dau_dis_ln_pi", "; BDT Response; Number of Events", 50, 0, 10);
  TH1D * h_track_dau_dis_ln_mu = new TH1D("track_dau_dis_ln_mu", "; BDT Response; Number of Events", 50, 0, 10);
  TH1D * h_track_dau_dis_ln_sh = new TH1D("track_dau_dis_ln_sh", "; BDT Response; Number of Events", 50, 0, 10);
  TH1D * h_track_dau_dis_ln_ot = new TH1D("track_dau_dis_ln_ot", "; BDT Response; Number of Events", 50, 0, 10);

  TH1D * h_track_dis_ln_pr = new TH1D("track_dau_dis_ln_pr", "; BDT Response; Number of Events", 50, 0, 10);
  TH1D * h_track_dis_ln_pi = new TH1D("track_dau_dis_ln_pi", "; BDT Response; Number of Events", 50, 0, 10);
  TH1D * h_track_dis_ln_mu = new TH1D("track_dau_dis_ln_mu", "; BDT Response; Number of Events", 50, 0, 10);
  TH1D * h_track_dis_ln_ot = new TH1D("track_dau_dis_ln_ot", "; BDT Response; Number of Events", 50, 0, 10);
  */

  TH1D * h_reco_track_Bragg_fwd_ka_pl2_ka = new TH1D("reco_track_Bragg_fwd_ka_pl2_ka", "; ;", 50, -1, 1);
  TH1D * h_reco_track_Bragg_fwd_ka_pl2_pr = new TH1D("reco_track_Bragg_fwd_ka_pl2_pr", "; ;", 50, -1, 1);
  TH1D * h_reco_track_Bragg_fwd_ka_pl2_pi = new TH1D("reco_track_Bragg_fwd_ka_pl2_pi", "; ;", 50, -1, 1);
  TH1D * h_reco_track_Bragg_fwd_ka_pl2_mu = new TH1D("reco_track_Bragg_fwd_ka_pl2_mu", "; ;", 50, -1, 1);
  TH1D * h_reco_track_Bragg_fwd_ka_pl2_ot = new TH1D("reco_track_Bragg_fwd_ka_pl2_ot", "; ;", 50, -1, 1);

  TH1D * h_reco_track_Bragg_fwd_pr_pl2_ka = new TH1D("reco_track_Bragg_fwd_pr_pl2_ka", "; ;", 50, -1, 1);
  TH1D * h_reco_track_Bragg_fwd_pr_pl2_pr = new TH1D("reco_track_Bragg_fwd_pr_pl2_pr", "; ;", 50, -1, 1);
  TH1D * h_reco_track_Bragg_fwd_pr_pl2_pi = new TH1D("reco_track_Bragg_fwd_pr_pl2_pi", "; ;", 50, -1, 1);
  TH1D * h_reco_track_Bragg_fwd_pr_pl2_mu = new TH1D("reco_track_Bragg_fwd_pr_pl2_mu", "; ;", 50, -1, 1);
  TH1D * h_reco_track_Bragg_fwd_pr_pl2_ot = new TH1D("reco_track_Bragg_fwd_pr_pl2_ot", "; ;", 50, -1, 1);

  TH1D * h_reco_track_Bragg_fwd_pi_pl2_ka = new TH1D("reco_track_Bragg_fwd_pi_pl2_ka", "; ;", 50, -1, 1);
  TH1D * h_reco_track_Bragg_fwd_pi_pl2_pr = new TH1D("reco_track_Bragg_fwd_pi_pl2_pr", "; ;", 50, -1, 1);
  TH1D * h_reco_track_Bragg_fwd_pi_pl2_pi = new TH1D("reco_track_Bragg_fwd_pi_pl2_pi", "; ;", 50, -1, 1);
  TH1D * h_reco_track_Bragg_fwd_pi_pl2_mu = new TH1D("reco_track_Bragg_fwd_pi_pl2_mu", "; ;", 50, -1, 1);
  TH1D * h_reco_track_Bragg_fwd_pi_pl2_ot = new TH1D("reco_track_Bragg_fwd_pi_pl2_ot", "; ;", 50, -1, 1);

  TH1D * h_reco_track_Bragg_fwd_mu_pl2_ka = new TH1D("reco_track_Bragg_fwd_mu_pl2_ka", "; ;", 50, -1, 1);
  TH1D * h_reco_track_Bragg_fwd_mu_pl2_pr = new TH1D("reco_track_Bragg_fwd_mu_pl2_pr", "; ;", 50, -1, 1);
  TH1D * h_reco_track_Bragg_fwd_mu_pl2_pi = new TH1D("reco_track_Bragg_fwd_mu_pl2_pi", "; ;", 50, -1, 1);
  TH1D * h_reco_track_Bragg_fwd_mu_pl2_mu = new TH1D("reco_track_Bragg_fwd_mu_pl2_mu", "; ;", 50, -1, 1);
  TH1D * h_reco_track_Bragg_fwd_mu_pl2_ot = new TH1D("reco_track_Bragg_fwd_mu_pl2_ot", "; ;", 50, -1, 1);

  /*
  TH1D * h_track_chi2ka_ka_sig = new TH1D("BDT_track_kaka_sig", "; BDT Response; Number of Events", 100, 0, 100);
  TH1D * h_track_chi2ka_pr_sig = new TH1D("BDT_track_kapr_sig", "; BDT Response; Number of Events", 100, 0, 100);
  TH1D * h_track_chi2ka_pi_sig = new TH1D("BDT_track_kapi_sig", "; BDT Response; Number of Events", 100, 0, 100);
  TH1D * h_track_chi2ka_mu_sig = new TH1D("BDT_track_kamu_sig", "; BDT Response; Number of Events", 100, 0, 100);
  TH1D * h_track_chi2ka_ot_sig = new TH1D("BDT_track_kaot_sig", "; BDT Response; Number of Events", 100, 0, 100);

  TH1D * h_track_chi2pr_ka_sig = new TH1D("BDT_track_prka_sig", "; BDT Response; Number of Events", 100, 0, 100);
  TH1D * h_track_chi2pr_pr_sig = new TH1D("BDT_track_prpr_sig", "; BDT Response; Number of Events", 100, 0, 100);
  TH1D * h_track_chi2pr_pi_sig = new TH1D("BDT_track_prpi_sig", "; BDT Response; Number of Events", 100, 0, 100);
  TH1D * h_track_chi2pr_mu_sig = new TH1D("BDT_track_prmu_sig", "; BDT Response; Number of Events", 100, 0, 100);
  TH1D * h_track_chi2pr_ot_sig = new TH1D("BDT_track_prot_sig", "; BDT Response; Number of Events", 100, 0, 100);

  TH1D * h_track_chi2ka_ka_bg = new TH1D("BDT_track_kaka_bg", "; BDT Response; Number of Events", 100, 0, 100);
  TH1D * h_track_chi2ka_pr_bg = new TH1D("BDT_track_kapr_bg", "; BDT Response; Number of Events", 100, 0, 100);
  TH1D * h_track_chi2ka_pi_bg = new TH1D("BDT_track_kapi_bg", "; BDT Response; Number of Events", 100, 0, 100);
  TH1D * h_track_chi2ka_mu_bg = new TH1D("BDT_track_kamu_bg", "; BDT Response; Number of Events", 100, 0, 100);
  TH1D * h_track_chi2ka_ot_bg = new TH1D("BDT_track_kaot_bg", "; BDT Response; Number of Events", 100, 0, 100);

  TH1D * h_track_chi2pr_ka_bg = new TH1D("BDT_track_prka_bg", "; BDT Response; Number of Events", 100, 0, 100);
  TH1D * h_track_chi2pr_pr_bg = new TH1D("BDT_track_prpr_bg", "; BDT Response; Number of Events", 100, 0, 100);
  TH1D * h_track_chi2pr_pi_bg = new TH1D("BDT_track_prpi_bg", "; BDT Response; Number of Events", 100, 0, 100);
  TH1D * h_track_chi2pr_mu_bg = new TH1D("BDT_track_prmu_bg", "; BDT Response; Number of Events", 100, 0, 100);
  TH1D * h_track_chi2pr_o_bgt = new TH1D("BDT_track_prot_bg", "; BDT Response; Number of Events", 100, 0, 100);
  */

  TH2D * h_truek_trkln_chi2ka = new TH2D("h_truek_trkln_chi2ka", "Track length vs #chi^{2}_{K};  #chi^{2}_{K}; Track length", 50, 0 , 50, 50, 0, 100);

  TH1D * h_reco_track_length = new TH1D("h_reco_track_length", "; reco_track_length; Number of Events", 50, 0, 50);
  TH1D * h_reco_track_daughter_distance = new TH1D("h_reco_track_daughter_distance", "; reco_track_daughter_distance; Number of Events", 50, 0, 50);
  TH1D * h_reco_track_daughter_vtx_distance = new TH1D(" h_reco_track_daughter_vtx_distance", ";  reco_track_daughter_vtx_distance; Number of Events", 50, 0, 50);

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
  h_track_dau_old_ln_pr->SetLineColor(kRed);
  h_track_dau_old_ln_pi->SetLineColor(TColor::GetColorDark(kGreen));
  h_track_dau_old_ln_mu->SetLineColor(kCyan);
  h_track_dau_old_ln_sh->SetLineColor(kMagenta);
  h_track_dau_old_ln_ot->SetLineColor(kOrange+1);
  */

  /*
  h_track_dau_ln_pr->SetFillColor(kRed);
  h_track_dau_ln_pi->SetFillColor(TColor::GetColorDark(kGreen));
  h_track_dau_ln_mu->SetFillColor(kCyan);
  h_track_dau_ln_sh->SetFillColor(kMagenta);
  h_track_dau_ln_ot->SetFillColor(kOrange+1);

  h_track_dau_old_ln_pr->SetFillColor(kRed);
  h_track_dau_old_ln_pi->SetFillColor(TColor::GetColorDark(kGreen));
  h_track_dau_old_ln_mu->SetFillColor(kCyan);
  h_track_dau_old_ln_sh->SetFillColor(kMagenta);
  h_track_dau_old_ln_ot->SetFillColor(kOrange+1);
  */

  /*
  h_track_dis_ln_pr->SetLineColor(kRed);
  h_track_dis_ln_pi->SetLineColor(TColor::GetColorDark(kGreen));
  h_track_dis_ln_mu->SetLineColor(kCyan);
  h_track_dis_ln_sh->SetLineColor(kMagenta);
  h_track_dis_ln_ot->SetLineColor(kOrange+1);

  h_track_dau_dis_ln_pr->SetLineColor(kRed);
  h_track_dau_dis_ln_pi->SetLineColor(TColor::GetColorDark(kGreen));
  h_track_dau_dis_ln_mu->SetLineColor(kCyan);
  h_track_dau_dis_ln_sh->SetLineColor(kMagenta);
  h_track_dau_dis_ln_ot->SetLineColor(kOrange+1);
  */

  /*
  h_reco_track_Bragg_fwd_ka_pl2_ka->SetFillColor(kBlue);
  h_reco_track_Bragg_fwd_ka_pl2_pr->SetFillColor(kRed);
  h_reco_track_Bragg_fwd_ka_pl2_pi->SetFillColor(TColor::GetColorDark(kGreen));
  h_reco_track_Bragg_fwd_ka_pl2_mu->SetFillColor(kViolet);
  h_reco_track_Bragg_fwd_ka_pl2_ot->SetFillColor(kOrange+1);

  h_reco_track_Bragg_fwd_pr_pl2_ka->SetFillColor(kBlue);
  h_reco_track_Bragg_fwd_pr_pl2_pr->SetFillColor(kRed);
  h_reco_track_Bragg_fwd_pr_pl2_pi->SetFillColor(TColor::GetColorDark(kGreen));
  h_reco_track_Bragg_fwd_pr_pl2_mu->SetFillColor(kViolet);
  h_reco_track_Bragg_fwd_pr_pl2_ot->SetFillColor(kOrange+1);

  h_reco_track_Bragg_fwd_pi_pl2_ka->SetFillColor(kBlue);
  h_reco_track_Bragg_fwd_pi_pl2_pr->SetFillColor(kRed);
  h_reco_track_Bragg_fwd_pi_pl2_pi->SetFillColor(TColor::GetColorDark(kGreen));
  h_reco_track_Bragg_fwd_pi_pl2_mu->SetFillColor(kViolet);
  h_reco_track_Bragg_fwd_pi_pl2_ot->SetFillColor(kOrange+1);

  h_reco_track_Bragg_fwd_mu_pl2_ka->SetFillColor(kBlue);
  h_reco_track_Bragg_fwd_mu_pl2_pr->SetFillColor(kRed);
  h_reco_track_Bragg_fwd_mu_pl2_pi->SetFillColor(TColor::GetColorDark(kGreen));
  h_reco_track_Bragg_fwd_mu_pl2_mu->SetFillColor(kViolet);
  h_reco_track_Bragg_fwd_mu_pl2_ot->SetFillColor(kOrange+1);
  */

  
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

  //THStack * s_trkdis = new THStack();
  //THStack * s_daudis = new THStack();
  THStack * s_braggka = new THStack();
  THStack * s_braggpr = new THStack();
  THStack * s_braggpi = new THStack();
  THStack * s_braggmu = new THStack();

  for(int ientry=0; ientry<nentry; ++ientry){
  //for(int ientry=0; ientry<9526; ++ientry){
    t->GetEntry(ientry);
    //if( fname.Contains("7Nov") || (fname.Contains("TMVA") && BDT>0.32)){

	if(reco_track_true_pdg==321){
	  h_track_llr_ka->Fill(reco_track_llrpid_3pl);
	  h_track_llrka_ka->Fill(reco_track_llrpid_k_3pl);
	  h_reco_track_Bragg_fwd_ka_pl2_ka->Fill(reco_track_Bragg_fwd_ka_pl2);
	  h_reco_track_Bragg_fwd_pr_pl2_ka->Fill(reco_track_Bragg_fwd_pr_pl2);
	  h_reco_track_Bragg_fwd_pi_pl2_ka->Fill(reco_track_Bragg_fwd_pi_pl2);
	  h_reco_track_Bragg_fwd_mu_pl2_ka->Fill(reco_track_Bragg_fwd_mu_pl2);
	}
	else if(reco_track_true_pdg==13){
	  h_track_llr_mu->Fill(reco_track_llrpid_3pl); 
	  h_track_llrka_mu->Fill(reco_track_llrpid_k_3pl);
	  h_reco_track_Bragg_fwd_ka_pl2_mu->Fill(reco_track_Bragg_fwd_ka_pl2);
	  h_reco_track_Bragg_fwd_pr_pl2_mu->Fill(reco_track_Bragg_fwd_pr_pl2);
	  h_reco_track_Bragg_fwd_pi_pl2_mu->Fill(reco_track_Bragg_fwd_pi_pl2);
	  h_reco_track_Bragg_fwd_mu_pl2_mu->Fill(reco_track_Bragg_fwd_mu_pl2);
	}
	else if(reco_track_true_pdg==211){
	  h_track_llr_pi->Fill(reco_track_llrpid_3pl);
	  h_track_llrka_pi->Fill(reco_track_llrpid_k_3pl);
	  h_reco_track_Bragg_fwd_ka_pl2_pi->Fill(reco_track_Bragg_fwd_ka_pl2);
	  h_reco_track_Bragg_fwd_pr_pl2_pi->Fill(reco_track_Bragg_fwd_pr_pl2);
	  h_reco_track_Bragg_fwd_pi_pl2_pi->Fill(reco_track_Bragg_fwd_pi_pl2);
	  h_reco_track_Bragg_fwd_mu_pl2_pi->Fill(reco_track_Bragg_fwd_mu_pl2);
	}
	else if(reco_track_true_pdg==2212){
	  h_track_llr_pr->Fill(reco_track_llrpid_3pl);
	  h_track_llrka_pr->Fill(reco_track_llrpid_k_3pl);
	  h_reco_track_Bragg_fwd_ka_pl2_pr->Fill(reco_track_Bragg_fwd_ka_pl2);
	  h_reco_track_Bragg_fwd_pr_pl2_pr->Fill(reco_track_Bragg_fwd_pr_pl2);
	  h_reco_track_Bragg_fwd_pi_pl2_pr->Fill(reco_track_Bragg_fwd_pi_pl2);
	  h_reco_track_Bragg_fwd_mu_pl2_pr->Fill(reco_track_Bragg_fwd_mu_pl2);
	}
	else{
	  h_track_llr_ot->Fill(reco_track_llrpid_3pl); 
	  h_track_llrka_ot->Fill(reco_track_llrpid_k_3pl);
	  h_reco_track_Bragg_fwd_ka_pl2_ot->Fill(reco_track_Bragg_fwd_ka_pl2);
	  h_reco_track_Bragg_fwd_pr_pl2_ot->Fill(reco_track_Bragg_fwd_pr_pl2);
	  h_reco_track_Bragg_fwd_pi_pl2_ot->Fill(reco_track_Bragg_fwd_pi_pl2);
	  h_reco_track_Bragg_fwd_mu_pl2_ot->Fill(reco_track_Bragg_fwd_mu_pl2);
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
	//if(true_kaon_end_process>=0) n5/reco_ntracks++;

	if( (reco_track_true_pdg==321 || reco_track_true_pdg==321 ) && ( reco_track_daughter_length>0 || reco_track_daughter_old_length>40)){
	//if( (reco_track_true_pdg==321 || reco_track_true_pdg!=321 ) ){

	//if( reco_track_true_pdg!=321 && (reco_track_daughter_length>25 || reco_track_daughter_old_length>40) ){
	//if(reco_track_true_pdg==321 && reco_track_daughter_length>25){
	//if(reco_track_true_pdg==321 && 
	//((reco_track_daughter_true_pdg==211 && std::abs(reco_track_daughter_length-true_dau_pip_length)<0.2*true_dau_pip_length)
	//|| (reco_track_daughter_true_pdg==-13 && std::abs(reco_track_daughter_length-true_dau_muon_length)<0.2*true_dau_muon_length)) ){
 	//if(reco_track_true_pdg==321 && ( (reco_track_daughter_length>25 && reco_track_daughter_old_length<40 )|| reco_track_daughter_old_length>40)){

	  //if(reco_track_daughter_llrpid_3pl<0) continue;
	  //if(reco_track_daughter_llrpid_k_3pl<0) continue;

	//if(reco_track_true_pdg!=321 && ( (reco_track_daughter_length>25 && reco_track_daughter_old_length<40 )|| reco_track_daughter_old_length>40)){
	  //if(reco_track_daughter_true_pdg==211) cout << reco_track_daughter_length << endl;

	  /*
	if(reco_track_true_pdg==321 && 
	    ((reco_track_daughter_true_pdg==211 && std::abs(reco_track_daughter_length-true_dau_pip_length)<0.2*true_dau_pip_length)
	     || (reco_track_daughter_old_length<40 && reco_track_daughter_true_pdg==-13 && std::abs(reco_track_daughter_length-true_dau_muon_length)<0.2*true_dau_muon_length)
	     || (reco_track_daughter_old_length>40 && reco_track_daughter_old_true_pdg==-13 && std::abs(reco_track_daughter_old_length-true_dau_muon_length)<0.2*true_dau_muon_length)) ){
	  */
	  
	//if(reco_track_daughter_old_length>50 && reco_track_daughter_true_pdg!=211){
	    


	  
	  if(reco_track_daughter_old_length>40){
	    if(reco_track_daughter_old_true_pdg==2212) h_track_dau_ln_pr->Fill(reco_track_daughter_old_length);
	    else if(reco_track_daughter_old_true_pdg==-13)  h_track_dau_ln_mu->Fill(reco_track_daughter_old_length);
	    else if(reco_track_daughter_old_true_pdg==211) h_track_dau_ln_pi->Fill(reco_track_daughter_old_length);  
	    else if(reco_track_daughter_old_true_pdg==11 || reco_track_daughter_old_true_pdg==-11 || reco_track_daughter_old_true_pdg==22) h_track_dau_ln_sh->Fill(reco_track_daughter_old_length);
	    else if(reco_track_daughter_old_true_pdg!=-9999) h_track_dau_ln_ot->Fill(reco_track_daughter_old_length);
	  }
	  else if(reco_track_daughter_old_length<40){
	  

	  
	  //else if(reco_track_daughter_length>25 && reco_track_daughter_old_length<40){
	
  
	  if(reco_track_true_pdg==321 && (reco_track_daughter_true_pdg!=-13 && reco_track_daughter_true_pdg!=211) ){
	  //if(reco_track_true_pdg==321 && (reco_track_daughter_true_pdg==22||reco_track_daughter_true_pdg==-11||reco_track_daughter_true_pdg==11) ){
	    /*
	    if(true_kaon_end_process == 0) n0++;
	    if(true_kaon_end_process == 1) n1++;
	    if(true_kaon_end_process == 2) n2++;
	    if(true_kaon_end_process == 3) n3++;
	    if(true_kaon_end_process == 4) n4++;
	    if(true_kaon_end_process == 5) n5++;
	    */
	    //cout << true_kaon_end_process << endl;
	  }
	  //if(reco_track_true_pdg==321){
	  /*
	  if(reco_track_true_pdg!=321 && (true_kaon_end_process==1 && true_kaon_end_process!=0)  ){
	    if(reco_track_daughter_true_pdg!=2212 && reco_track_daughter_true_pdg!=-13 && reco_track_daughter_true_pdg!=-11 && reco_track_daughter_true_pdg!=11 && reco_track_daughter_true_pdg!=211 && reco_track_daughter_true_pdg!=22 && reco_track_daughter_true_pdg!=-9999 ) cout << reco_track_daughter_true_pdg << endl;
	  }
	  */
	  /*
	  if(reco_track_true_pdg!=321){
	    if(reco_track_true_pdg!=2212 && reco_track_true_pdg!=13 && reco_track_true_pdg!=211) cout << reco_track_true_pdg << endl;
	  }
	  */

	if(reco_track_daughter_true_pdg==2212){
	  h_track_dau_ln_pr->Fill(reco_track_daughter_length);
	  //h_track_dis_ln_pr->Fill(reco_track_distance);
	  //h_track_dau_dis_ln_pr->Fill(reco_track_daughter_distance);
	  h_track_dau_llr_pr->Fill(reco_track_daughter_llrpid_3pl);
	  h_track_dau_llrka_pr->Fill(reco_track_daughter_llrpid_k_3pl);
	}
	//else if(reco_track_daughter_true_pdg==-13){
	else if( (reco_track_daughter_true_pdg==-13 || reco_track_daughter_true_pdg==13) ){
	  h_track_dau_ln_mu->Fill(reco_track_daughter_length);
	  //h_track_dis_ln_mu->Fill(reco_track_distance);
	  //h_track_dau_dis_ln_mu->Fill(reco_track_daughter_distance);
	  h_track_dau_llr_mu->Fill(reco_track_daughter_llrpid_3pl);
	  h_track_dau_llrka_mu->Fill(reco_track_daughter_llrpid_k_3pl);
	}
	else if(reco_track_daughter_true_pdg==211){
	  h_track_dau_ln_pi->Fill(reco_track_daughter_length);
	  //h_track_dis_ln_pi->Fill(reco_track_distance);
	  //h_track_dau_dis_ln_pi->Fill(reco_track_daughter_distance);
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
	  //h_track_dis_ln_ot->Fill(reco_track_distance);
	  //h_track_dau_dis_ln_ot->Fill(reco_track_daughter_distance);
	  h_track_dau_llr_ot->Fill(reco_track_daughter_llrpid_3pl);
	  h_track_dau_llrka_ot->Fill(reco_track_daughter_llrpid_k_3pl);
	}
	}

	  }

	if( (reco_track_true_pdg==321 || reco_track_true_pdg==321) && reco_track_daughter_old_length>0){
	//if(reco_track_true_pdg!=321 && reco_track_daughter_old_length>0){
	//if(reco_track_true_pdg!=321 && reco_track_daughter_old_length>25){
	//if(reco_track_true_pdg!=321 && reco_track_daughter_old_length>25){

	//if(reco_track_true_pdg==321 && reco_track_daughter_old_length>25 &&reco_track_daughter_old_true_pdg==211 ) cout << reco_track_daughter_old_length << endl;
	/*    
	  if(reco_track_true_pdg==321 && reco_track_daughter_old_length>25 &&
	  ((reco_track_daughter_old_true_pdg==211 && std::abs(reco_track_daughter_old_length-true_dau_pip_length)<0.2*true_dau_pip_length)
	  || (reco_track_daughter_old_true_pdg==-13 && std::abs(reco_track_daughter_old_length-true_dau_muon_length)<0.2*true_dau_muon_length)) ){
	*/

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


      if(pl=="pl2"){

	/*
	h_chi2_trk_pr_ka->Fill(reco_track_chi2pr_pl2, reco_track_chi2ka_pl2);

	if(true_nu_pdg==14 && true_nu_ccnc==0 && true_kaon_ke>=0 && true_nu_vtx_inCCInclusiveTPC==1 && true_kaon_end_inCCInclusiveTPC==1 && true_kaon_daughter_end_in5cmTPC==1 && reco_track_true_pdg==321){
	  h_chi2_trk_pr_ka_sig->Fill(reco_track_chi2pr_pl2, reco_track_chi2ka_pl2);
	}
	else h_chi2_trk_pr_ka_bg->Fill(reco_track_chi2pr_pl2, reco_track_chi2ka_pl2);

	h_truek_trkln_chi2ka->Fill(reco_track_chi2ka_pl2, true_kaon_length);
	*/
	/*
	h_chi2_trk_pi_ka->Fill(reco_track_chi2pi_pl2, reco_track_chi2ka_pl2);
	h_chi2_trk_mu_ka->Fill(reco_track_chi2mu_pl2, reco_track_chi2ka_pl2);
	
	h_chi2_dau_pr_mu->Fill(reco_track_daughter_chi2pr_pl2, reco_track_daughter_chi2mu_pl2);
	h_chi2_dau_pi_mu->Fill(reco_track_daughter_chi2pi_pl2, reco_track_daughter_chi2mu_pl2);
	h_chi2_dau_ka_mu->Fill(reco_track_daughter_chi2ka_pl2, reco_track_daughter_chi2mu_pl2);
	h_chi2_dau_pr_pi->Fill(reco_track_daughter_chi2pr_pl2, reco_track_daughter_chi2ka_pl2);
	h_chi2_dau_mu_pi->Fill(reco_track_daughter_chi2mu_pl2, reco_track_daughter_chi2ka_pl2);
	h_chi2_dau_ka_pi->Fill(reco_track_daughter_chi2ka_pl2, reco_track_daughter_chi2ka_pl2);
	*/
	
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


      }else{
	/*
	h_chi2_trk_pr_ka->Fill(reco_track_chi2pr_3pl, reco_track_chi2ka_3pl);

	if(true_nu_pdg==14 && true_nu_ccnc==0 && true_kaon_ke>=0 && true_nu_vtx_inCCInclusiveTPC==1 && true_kaon_end_inCCInclusiveTPC==1 && true_kaon_daughter_end_in5cmTPC==1 && reco_track_true_pdg==321){
	  h_chi2_trk_pr_ka_sig->Fill(reco_track_chi2pr_3pl, reco_track_chi2ka_3pl);
	}
	else h_chi2_trk_pr_ka_bg->Fill(reco_track_chi2pr_3pl, reco_track_chi2ka_3pl);

	h_truek_trkln_chi2ka->Fill(reco_track_chi2ka_3pl, true_kaon_length);
	*/
	/*
	h_chi2_trk_pr_ka->Fill(reco_track_daughter_chi2pr_3pl, reco_track_daughter_chi2ka_3pl);
	h_chi2_trk_pi_ka->Fill(reco_track_daughter_chi2pi_3pl, reco_track_daughter_chi2ka_3pl);
	h_chi2_trk_mu_ka->Fill(reco_track_daughter_chi2mu_3pl, reco_track_daughter_chi2ka_3pl);
	
	h_chi2_dau_pr_mu->Fill(reco_track_daughter_chi2pr_3pl, reco_track_daughter_chi2mu_3pl);
	h_chi2_dau_pi_mu->Fill(reco_track_daughter_chi2pi_3pl, reco_track_daughter_chi2mu_3pl);
	h_chi2_dau_ka_mu->Fill(reco_track_daughter_chi2ka_3pl, reco_track_daughter_chi2mu_3pl);
	h_chi2_dau_pr_pi->Fill(reco_track_daughter_chi2pr_3pl, reco_track_daughter_chi2ka_3pl);
	h_chi2_dau_mu_pi->Fill(reco_track_daughter_chi2mu_3pl, reco_track_daughter_chi2ka_3pl);
	h_chi2_dau_ka_pi->Fill(reco_track_daughter_chi2ka_3pl, reco_track_daughter_chi2ka_3pl);
	*/	
	
	//cout << reco_track_true_pdg << endl;

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
      //}
  }

  s_braggka->Add(h_reco_track_Bragg_fwd_ka_pl2_pr);
  s_braggka->Add(h_reco_track_Bragg_fwd_ka_pl2_ot);
  s_braggka->Add(h_reco_track_Bragg_fwd_ka_pl2_ka);

  s_braggka->Add(h_reco_track_Bragg_fwd_ka_pl2_mu);
  s_braggka->Add(h_reco_track_Bragg_fwd_ka_pl2_pi);


  s_braggpr->Add(h_reco_track_Bragg_fwd_pr_pl2_pr);
  s_braggpr->Add(h_reco_track_Bragg_fwd_pr_pl2_ot);
  s_braggpr->Add(h_reco_track_Bragg_fwd_pr_pl2_ka);
  s_braggpr->Add(h_reco_track_Bragg_fwd_pr_pl2_mu);
  s_braggpr->Add(h_reco_track_Bragg_fwd_pr_pl2_pi);

  s_braggpi->Add(h_reco_track_Bragg_fwd_pi_pl2_pr);
  s_braggpi->Add(h_reco_track_Bragg_fwd_pi_pl2_ot);
  s_braggpi->Add(h_reco_track_Bragg_fwd_pi_pl2_ka);
  s_braggpi->Add(h_reco_track_Bragg_fwd_pi_pl2_mu);
  s_braggpi->Add(h_reco_track_Bragg_fwd_pi_pl2_pi);

  s_braggmu->Add(h_reco_track_Bragg_fwd_mu_pl2_pr);
  s_braggmu->Add(h_reco_track_Bragg_fwd_mu_pl2_ot);
  s_braggmu->Add(h_reco_track_Bragg_fwd_mu_pl2_ka);
  s_braggmu->Add(h_reco_track_Bragg_fwd_mu_pl2_mu);
  s_braggmu->Add(h_reco_track_Bragg_fwd_mu_pl2_pi);


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


  /*
  s_trkln_dau->Add(h_track_dau_ln_mu);
  s_trkln_dau->Add(h_track_dau_ln_pr);
  s_trkln_dau->Add(h_track_dau_ln_pi);
  s_trkln_dau->Add(h_track_dau_ln_sh);
  s_trkln_dau->Add(h_track_dau_ln_ot);

  s_daudis->Add(h_track_dau_dis_ln_mu);
  s_daudis->Add(h_track_dau_dis_ln_pr);
  s_daudis->Add(h_track_dau_dis_ln_pi);
  s_daudis->Add(h_track_dau_dis_ln_ot);

  s_trkdis->Add(h_track_dis_ln_mu);
  s_trkdis->Add(h_track_dis_ln_pr);
  s_trkdis->Add(h_track_dis_ln_pi);
  s_trkdis->Add(h_track_dis_ln_ot);
  */

  TLegend * l_ka = new TLegend(0.75,0.65,0.95,0.95);
  l_ka->AddEntry(h_track_chi2ka_ka, "True K^{+}"  , "f");
  l_ka->AddEntry(h_track_chi2ka_pr, "True p" , "f");
  l_ka->AddEntry(h_track_chi2ka_pi, "True #pi^{+}"   , "f");
  l_ka->AddEntry(h_track_chi2ka_mu, "True #mu^{-}"   , "f");
  l_ka->AddEntry(h_track_chi2ka_ot, "Others"   , "f");

  TLegend * l_pr = new TLegend(0.75,0.65,0.95,0.95);
  l_pr->AddEntry(h_track_chi2pr_ka, "True K^{+}"  , "f");
  l_pr->AddEntry(h_track_chi2pr_pr, "True p" , "f");
  l_pr->AddEntry(h_track_chi2pr_pi, "True #pi^{+}"   , "f");
  l_pr->AddEntry(h_track_chi2pr_mu, "True #mu^{-}"   , "f");
  l_pr->AddEntry(h_track_chi2pr_ot, "Others"   , "f");

  TLegend * l_pr_dau = new TLegend(0.75,0.65,0.95,0.95);
  l_pr_dau->AddEntry(h_track_dau_chi2pr_pr, "True p" , "f");
  l_pr_dau->AddEntry(h_track_dau_chi2pr_pi, "True #pi^{+}"   , "f");
  l_pr_dau->AddEntry(h_track_dau_chi2pr_mu, "True #mu^{+}"   , "f");
  l_pr_dau->AddEntry(h_track_dau_chi2pr_sh, "True shower"   , "f");
  l_pr_dau->AddEntry(h_track_dau_chi2pr_ot, "Others"   , "f");

  TLegend * l_pr_dau_ln = new TLegend(0.75,0.65,0.95,0.95);
  l_pr_dau_ln->AddEntry(h_track_dau_ln_pr, "True p" , "f");
  l_pr_dau_ln->AddEntry(h_track_dau_ln_pi, "True #pi^{+}"   , "f");
  l_pr_dau_ln->AddEntry(h_track_dau_ln_mu, "True #mu^{+}"   , "f");
  l_pr_dau_ln->AddEntry(h_track_dau_ln_sh, "True shower"   , "f");
  l_pr_dau_ln->AddEntry(h_track_dau_ln_ot, "Others"   , "f");

  TLegend * l_pr_dau2 = new TLegend(0.15,0.58,0.35,0.88);
  l_pr_dau2->AddEntry(h_track_dau_chi2pr_pr, "True p" , "f");
  l_pr_dau2->AddEntry(h_track_dau_chi2pr_pi, "True #pi^{+}"   , "f");
  l_pr_dau2->AddEntry(h_track_dau_chi2pr_mu, "True #mu^{+}"   , "f");
  l_pr_dau2->AddEntry(h_track_dau_chi2pr_sh, "True shower"   , "f");
  l_pr_dau2->AddEntry(h_track_dau_chi2pr_ot, "Others"   , "f");

  h_reco_track_daughter_vtx_distance->SetLineColor(kRed);
  h_reco_track_daughter_distance->SetLineColor(kBlue);
  h_reco_track_length->SetLineColor(kBlack);


  if(trdau.Contains("tra")){
    /*
    h_chi2_trk_pr_ka->Draw("colz");
    c->Print(output_name);

    h_chi2_trk_pr_ka_sig->Draw("colz");
    c->Print(output_name);

    h_chi2_trk_pr_ka_bg->Draw("colz");
    c->Print(output_name);

    h_truek_trkln_chi2ka->Draw("colz");
    c->Print(output_name);
    */
    /*
    h_chi2_trk_pi_ka->Draw("colz");
    c->Print(output_pdf_trk);
    h_chi2_trk_mu_ka->Draw("colz");
    c->Print(output_pdf_trk);
    */

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

    //s_trkln_dau->Draw();
    s_trkln_dau->SetMaximum(200.);
    s_trkln_dau_old->SetMaximum(200.); 
    s_trkln_dau->Draw("nostack");
    l_pr_dau_ln->Draw();
    c->Print(output_name);

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

    //s_trkln_dau_old->Draw();
    s_trkln_dau_old->Draw("nostack");
    l_pr_dau_ln->Draw();
    c->Print(output_name);


    /*
    s_trkdis->Draw();
    l_pr_dau->Draw();
    c->Print(output_name);

    s_daudis->Draw();
    l_pr_dau->Draw();
    c->Print(output_name);
    */

    //s_braggka->Draw();
    s_braggka->Draw("nostack");
    l_pr->Draw();
    c->Print(output_name);

    //s_braggpr->Draw();
    s_braggpr->Draw("nostack");
    l_pr->Draw();
    c->Print(output_name);

    //s_braggpi->Draw();
    s_braggpi->Draw("nostack");
    l_pr->Draw();
    c->Print(output_name);

    //s_braggmu->Draw();
    s_braggmu->Draw("nostack");
    l_pr->Draw();
    c->Print(output_name);

  }
  else if(trdau.Contains("dau")){
    /*
    h_chi2_dau_pr_mu->Draw("colz");
    c->Print(output_pdf_dau);
    h_chi2_dau_pi_mu->Draw("colz");
    c->Print(output_pdf_dau);
    h_chi2_dau_ka_mu->Draw("colz");
    c->Print(output_pdf_dau);
    h_chi2_dau_pr_pi->Draw("colz");
    c->Print(output_pdf_dau);
    h_chi2_dau_pr_pi->Draw("colz");
    c->Print(output_pdf_dau);
    h_chi2_dau_mu_pi->Draw("colz");
    c->Print(output_pdf_dau);
    h_chi2_dau_ka_pi->Draw("colz");
    c->Print(output_pdf_dau);
    */
  }
  else{
    cout << "No output pdf file found" << endl;
  }

  cout << "n0: " << n0 << ", " << "n1: " << n1 << ", " << "n2: " << n2 << ", " << "n3: " << n3 << ", " << "n4: " << n4 << ", " << "n5: " << n5 << endl;

  cout << "h_track_dau_ln_pr: " << h_track_dau_ln_pr->GetEntries() << endl;
  cout << "h_track_dau_ln_pi: " << h_track_dau_ln_pi->GetEntries() << endl;
  cout << "h_track_dau_ln_mu: " << h_track_dau_ln_mu->GetEntries() << endl;
  cout << "h_track_dau_ln_sh: " << h_track_dau_ln_sh->GetEntries() << endl;
  cout << "h_track_dau_ln_ot: " << h_track_dau_ln_ot->GetEntries() << endl;

  cout << "h_track_dau_old_ln_pr: " << h_track_dau_old_ln_pr->GetEntries() << endl;
  cout << "h_track_dau_old_ln_pi: " << h_track_dau_old_ln_pi->GetEntries() << endl;
  cout << "h_track_dau_old_ln_mu: " << h_track_dau_old_ln_mu->GetEntries() << endl;
  cout << "h_track_dau_old_ln_sh: " << h_track_dau_old_ln_sh->GetEntries() << endl;
  cout << "h_track_dau_old_ln_ot: " << h_track_dau_old_ln_ot->GetEntries() << endl;



  /*
  delete h_chi2_trk_pr_ka;
  delete h_chi2_trk_pi_ka;
  delete h_chi2_trk_mu_ka;
  delete h_chi2_dau_pr_mu;
  delete h_chi2_dau_pi_mu;
  delete h_chi2_dau_ka_mu;
  delete h_chi2_dau_pr_pi;
  delete h_chi2_dau_ka_pi;
  delete h_chi2_dau_mu_pi;
  */
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


#include <iostream>
#include <TH2D.h>
#include <TFile.h>
#include <TROOT.h>
#include <TChain.h>
#include <TTree.h>
#include <TVectorT.h>
#include <TChain.h>
#include <vector>
#include <iostream>
#include <stdio.h>
#include <string.h>

void Initialise();
//void GeneratePlots(TFile *f, TString pl, TCanvas* &c, TString output_name);
void GeneratePlots(TFile *f, TString pl, TString mode, bool IsHybrid, TCanvas* &c, TString output_name, TChain *chain);
//void DrawChi2(TFile *f, TString pr, TString pr2, TString pl, TString trdau, TCanvas* &c, TString output_name);
void RebuildTrackHist(TString input_name, TString output_name, TString pl, TString mode, bool IsHybrid);
void LoadTree(TFile *f, TString pl, TTree* &t);
void SetHistos();
void SetHistosStyle();
void FillHybridTrackLength();
void FillRebuiltTrackLength(); 
void FillOldTrackLength();
void FillPl2PID();
void Fill3PlPID();
void FillPrimaryTrack();
void AddStackHistos();
void AddLegend();
void DrawHistos(TCanvas* &c,TString output_name);
double GetMaxBinContentFromStack(THStack *stack);

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

int nentry=0;
int reco_true_length_mu;
int reco_true_length_pi;
int reco_true_length_mu_hy;
int reco_true_length_pi_hy;
int reco_old_true_length_mu;
int reco_old_true_length_pi;

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

  Float_t reco_track_daughter_true_pdg;
  Float_t reco_track_daughter_old_true_pdg;
  Float_t BDT;
  Float_t true_kaon_ke;
  Float_t true_kaon_length;
  Int_t true_kaon_end_process;

  Int_t true_nu_pdg, true_nu_ccnc, true_nu_vtx_inCCInclusiveTPC, true_kaon_end_inCCInclusiveTPC, true_kaon_daughter_end_in5cmTPC, reco_track_true_pdg;


TH1D * h_track_chi2ka_ka;
TH1D * h_track_chi2ka_pr;
TH1D * h_track_chi2ka_pi;
TH1D * h_track_chi2ka_mu;
TH1D * h_track_chi2ka_ot;
TH1D * h_track_chi2pr_ka;
TH1D * h_track_chi2pr_pr;
TH1D * h_track_chi2pr_pi;
TH1D * h_track_chi2pr_mu;
TH1D * h_track_chi2pr_ot;
TH1D * h_track_llr_ka;
TH1D * h_track_llr_pr;
TH1D * h_track_llr_pi;
TH1D * h_track_llr_mu;
TH1D * h_track_llr_ot;
TH1D * h_track_llrka_ka;
TH1D * h_track_llrka_pr;
TH1D * h_track_llrka_pi;
TH1D * h_track_llrka_mu;
TH1D * h_track_llrka_ot;

TH1D * h_track_dau_llr_sh;
TH1D * h_track_dau_llr_pr;
TH1D * h_track_dau_llr_pi;
TH1D * h_track_dau_llr_mu;
TH1D * h_track_dau_llr_ot;
TH1D * h_track_dau_llrka_sh;
TH1D * h_track_dau_llrka_pr;
TH1D * h_track_dau_llrka_pi;
TH1D * h_track_dau_llrka_mu;
TH1D * h_track_dau_llrka_ot;
TH1D * h_track_dau_chi2pr_pr;
TH1D * h_track_dau_chi2pr_pi;
TH1D * h_track_dau_chi2pr_mu;
TH1D * h_track_dau_chi2pr_sh;
TH1D * h_track_dau_chi2pr_ot;
TH1D * h_track_dau_chi2pi_pr;
TH1D * h_track_dau_chi2pi_pi;
TH1D * h_track_dau_chi2pi_mu;
TH1D * h_track_dau_chi2pi_sh;
TH1D * h_track_dau_chi2pi_ot;
TH1D * h_track_dau_chi2mu_pr;
TH1D * h_track_dau_chi2mu_pi;
TH1D * h_track_dau_chi2mu_mu;
TH1D * h_track_dau_chi2mu_sh;
TH1D * h_track_dau_chi2mu_ot;
TH1D * h_track_dau_ln_pr;
TH1D * h_track_dau_ln_pi;
TH1D * h_track_dau_ln_mu;
TH1D * h_track_dau_ln_sh;
TH1D * h_track_dau_ln_ot;

TH1D * h_track_dau_ln_pr_hy;
TH1D * h_track_dau_ln_pi_hy;
TH1D * h_track_dau_ln_mu_hy;
TH1D * h_track_dau_ln_sh_hy;
TH1D * h_track_dau_ln_ot_hy;

TH1D * h_track_dau_old_llr_sh;
TH1D * h_track_dau_old_llr_pr;
TH1D * h_track_dau_old_llr_pi;
TH1D * h_track_dau_old_llr_mu;
TH1D * h_track_dau_old_llr_ot;
TH1D * h_track_dau_old_llrka_sh;
TH1D * h_track_dau_old_llrka_pr;
TH1D * h_track_dau_old_llrka_pi;
TH1D * h_track_dau_old_llrka_mu;
TH1D * h_track_dau_old_llrka_ot;
TH1D * h_track_dau_old_chi2pr_pr;
TH1D * h_track_dau_old_chi2pr_pi;
TH1D * h_track_dau_old_chi2pr_mu;
TH1D * h_track_dau_old_chi2pr_sh;
TH1D * h_track_dau_old_chi2pr_ot;
TH1D * h_track_dau_old_chi2pi_pr;
TH1D * h_track_dau_old_chi2pi_pi;
TH1D * h_track_dau_old_chi2pi_mu;
TH1D * h_track_dau_old_chi2pi_sh;
TH1D * h_track_dau_old_chi2pi_ot;
TH1D * h_track_dau_old_chi2mu_pr;
TH1D * h_track_dau_old_chi2mu_pi;
TH1D * h_track_dau_old_chi2mu_mu;
TH1D * h_track_dau_old_chi2mu_sh;
TH1D * h_track_dau_old_chi2mu_ot;
TH1D * h_track_dau_old_ln_pr;
TH1D * h_track_dau_old_ln_pi;
TH1D * h_track_dau_old_ln_mu;
TH1D * h_track_dau_old_ln_sh;
TH1D * h_track_dau_old_ln_ot;

TH2D * h_truek_trkln_chi2ka;
TH1D * h_reco_track_length;
TH1D * h_reco_track_daughter_distance;
TH1D * h_reco_track_daughter_vtx_distance;

  THStack * s_chi2ka = new THStack();
  THStack * s_chi2pr = new THStack();
  THStack * s_llr = new THStack();
  THStack * s_llrka = new THStack();

  THStack * s_llr_dau = new THStack();
  THStack * s_llrka_dau = new THStack();
  THStack * s_chi2pr_dau = new THStack();
  THStack * s_chi2pi_dau = new THStack();
  THStack * s_chi2mu_dau = new THStack();
//THStack * s_trkln_dau = new THStack();

  THStack * s_llr_dau_old = new THStack();
  THStack * s_llrka_dau_old = new THStack();
  THStack * s_chi2pr_dau_old = new THStack();
  THStack * s_chi2pi_dau_old = new THStack();
  THStack * s_chi2mu_dau_old = new THStack();
//THStack * s_trkln_dau_old = new THStack();

THStack * s_trkln_dau = new THStack("s_trkln_dau", ";Daughter Track Length (cm);Event (a.u.)");
THStack * s_trkln_dau_hy = new THStack("s_trkln_dau_hy", ";Daughter Track Length (cm);Event (a.u.)");
THStack * s_trkln_dau_old = new THStack("s_trkln_dau)old", ";Daughter Track Length (cm);Event (a.u.)");


/*
  THStack * s_braggka = new THStack();
  THStack * s_braggpr = new THStack();
  THStack * s_braggpi = new THStack();
  THStack * s_braggmu = new THStack();
*/

TLegend * l_ka;
TLegend * l_pr;
TLegend * l_pr_dau;
TLegend * l_pr_dau_ln;
TLegend * l_pr_dau2;

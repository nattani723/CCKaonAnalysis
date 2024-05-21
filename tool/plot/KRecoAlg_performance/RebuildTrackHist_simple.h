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
//void GeneratePlots(TFile *f, TString pl, TCanvas* &c, TString output_name);
void GeneratePlots(TFile *f, TString pl, TString mode, bool IsHybrid, TCanvas* &c, TString output_name);
//void DrawChi2(TFile *f, TString pr, TString pr2, TString pl, TString trdau, TCanvas* &c, TString output_name);
void RebuildTrackHist(TString input_name, TString output_name, TString pl, TString mode, bool IsHybrid);
void LoadTree(TFile *f, TString pl, TTree* &t);
void SetHistos();
void SetHistosStyle();
void FillHybridTrackLength();
void FillRebuildTrackLength(); 
void FillTrackLength(); 
void FillOldTrackLength();
void FillPl2PID();
void Fill3PlPID();
void FillPrimaryTrack();
void AddStackHistos();
void AddLegend();
void DrawHistos(TCanvas* &c,TString output_name);

// Cuts
TString output_pdf_trk = "chi2_trk.pdf";
TString output_pdf_dau = "chi2_dau.pdf";;

int nentry=0;
int reco_true_length_mu;
int reco_true_length_pi;
int reco_old_true_length_mu;
int reco_old_true_length_pi;

  Float_t true_dau_pip_length;
  Float_t true_dau_muon_length;

  Float_t reco_track_daughter_old_length;
  Float_t reco_track_length;
  Float_t reco_track_distance;
  Float_t reco_track_daughter_length;
  Float_t reco_track_daughter_distance;
  Float_t reco_track_daughter_vtx_distance;

  Float_t reco_track_daughter_true_pdg;
  Float_t reco_track_daughter_old_true_pdg;
  Float_t BDT;
  Float_t true_kaon_ke;
  Float_t true_kaon_length;
  Int_t true_kaon_end_process;

  Int_t true_nu_pdg, true_nu_ccnc, true_nu_vtx_inCCInclusiveTPC, true_kaon_end_inCCInclusiveTPC, true_kaon_daughter_end_in5cmTPC, reco_track_true_pdg;

Int_t n_recoRebDauTracks;
Float_t rebdautrack_length, rebdautracktrue_length, rebdautracktruedir_length, rebdautrack_pdg;
Float_t best_peak_x, best_peak_y, best_peak_z, best_peak_x_true, best_peak_y_true, best_peak_z_true;

TVector3 true_dau_dir;
TVector3 cheat_dir;
TVector3 reco_dir;
/*
TVector3 true_dau_muon_dir;
TVector3 true_dau_pip_dir;
TVector3 cheat_pip_dir;
TVector3 cheat_muon_dir;
TVector3 reco_muon_dir;
TVector3 reco_pip_dir;
*/

loat_t true_dau_muon_end_x, true_dau_muon_end_y, true_dau_muon_end_z, true_dau_muon_start_x, true_dau_muon_start_y, true_dau_muon_start_z, true_dau_pip_end_x, true_dau_pip_end_y, true_dau_pip_end_z, true_dau_pip_start_x, true_dau_pip_start_y, true_dau_pip_start_z, true_dau_muon_theta, true_dau_muon_phi, true_dau_pip_theta, true_dau_pip_phi;

TH1D * h_track_dau_ln_pr;
TH1D * h_track_dau_ln_pi;
TH1D * h_track_dau_ln_mu;
TH1D * h_track_dau_ln_sh;
TH1D * h_track_dau_ln_ot;

TH1D * h_track_dau_old_ln_pr;
TH1D * h_track_dau_old_ln_pi;
TH1D * h_track_dau_old_ln_mu;
TH1D * h_track_dau_old_ln_sh;
TH1D * h_track_dau_old_ln_ot;

//rebdau
TH1D * h_track_rebdau_ln_pr;
TH1D * h_track_rebdau_ln_pi;
TH1D * h_track_rebdau_ln_mu;
TH1D * h_track_rebdau_ln_sh;
TH1D * h_track_rebdau_ln_ot;

TH1D * h_track_rebdau_cheat_ln_pr;
TH1D * h_track_rebdau_cheat_ln_pi;
TH1D * h_track_rebdau_cheat_ln_mu;
TH1D * h_track_rebdau_cheat_ln_sh;
TH1D * h_track_rebdau_cheat_ln_ot;

TH1D * h_track_rebdau_cheat_dir_ln_pr;
TH1D * h_track_rebdau_cheat_dir_ln_pi;
TH1D * h_track_rebdau_cheat_dir_ln_mu;
TH1D * h_track_rebdau_cheat_dir_ln_sh;
TH1D * h_track_rebdau_cheat_dir_ln_ot;

TH1D * h_peak_dir_pr;
TH1D * h_peak_dir_pi;
TH1D * h_peak_dir_mu;
TH1D * h_peak_dir_sh;
TH1D * h_peak_dir_ot;

TH1D * h_peak_dir_cheat_pr;
TH1D * h_peak_dir_cheat_pi;
TH1D * h_peak_dir_cheat_mu;
TH1D * h_peak_dir_cheat_sh;
TH1D * h_peak_dir_cheat_ot;

TH2D * h_truek_trkln_chi2ka;
TH1D * h_reco_track_length;
TH1D * h_reco_track_daughter_distance;
TH1D * h_reco_track_daughter_vtx_distance;

  THStack * s_trkln_dau = new THStack();
  THStack * s_trkln_dau_old = new THStack();
THStack * s_trkln_rebdau = new THStack();
THStack * s_trkln_rebdau_cheat = new THStack();
THStack * s_trkln_rebdau_cheat_dir = new THStack();
THStack * s_peak_dir = new THStack();
THStack * s_peak_dir_cheat = new THStack();

/*
  THStack * s_braggka = new THStack();
  THStack * s_braggpr = new THStack();
  THStack * s_braggpi = new THStack();
  THStack * s_braggmu = new THStack();
*/

TLegend * l_pr_dau_ln;


//how to store PDG

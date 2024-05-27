//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sun Jan 10 23:24:45 2021 by ROOT version 6.12/06
// from TTree Event/Event Tree from Reco
// found on file: /nashome/a/arturo/uboone/uboonedata/uboonecode_v08_00_00_32/CCKaonFilter/cckaonfilter_ana_cck_v7.root
//////////////////////////////////////////////////////////

#ifndef Event_h
#define Event_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class Event {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           event;
   Int_t           run;
   Int_t           subrun;
   Float_t         event_weight;
   Float_t         true_nu_energy;
   Int_t           true_nu_pdg;
   Int_t           true_nu_mode;
   Int_t           true_nu_ccnc;
   Float_t         true_nu_vtx_x;
   Float_t         true_nu_vtx_y;
   Float_t         true_nu_vtx_z;
   Bool_t          true_nu_vtx_inTPC;
   Bool_t          true_nu_vtx_in5cmTPC;
   Bool_t          true_nu_vtx_inCCInclusiveTPC;
   Int_t           true_lepton_pdg;
   Float_t         true_lepton_p;
   Float_t         true_lepton_ke;
   Float_t         true_lepton_theta;
   Float_t         true_lepton_costheta;
   Float_t         true_lepton_phi;
   Int_t           true_nkaons;
   Int_t           true_nhyperons;
   Float_t         true_kaon_length;
   Float_t         true_kaon_p;
   Float_t         true_kaon_ke;
   Float_t         true_kaon_theta;
   Float_t         true_kaon_costheta;
   Float_t         true_kaon_phi;
   Float_t         true_kaon_ccmuon_angle;
   Float_t         true_kaon_ccmuon_cosangle;
   Int_t           true_kaon_end_process;
   Float_t         true_kaon_end_ke;
   Float_t         true_kaon_end_x;
   Float_t         true_kaon_end_y;
   Float_t         true_kaon_end_z;
   Bool_t          true_kaon_end_inTPC;
   Bool_t          true_kaon_end_in5cmTPC;
   Bool_t          true_kaon_end_inCCInclusiveTPC;
   Int_t           true_kaon_ndaughters;
   Int_t           true_kaon_ndaughters_decay;
   Int_t           true_kaon_ndaughters_inelastic;
   Int_t           true_kaon_ndecmup;
   Int_t           true_kaon_ndecpip;
   Int_t           true_kaon_ninekap;
   Int_t           true_kaon_ninepip;
   Int_t           true_kaon_ninepro;
   Float_t         true_kaon_daughter_length;
   Float_t         true_kaon_daughter_p;
   Float_t         true_kaon_daughter_ke;
   Float_t         true_kaon_daughter_theta;
   Float_t         true_kaon_daughter_costheta;
   Float_t         true_kaon_daughter_angle;
   Float_t         true_kaon_daughter_cosangle;
   Int_t           true_kaon_daughter_pdg;
   Float_t         true_kaon_daughter_end_x;
   Float_t         true_kaon_daughter_end_y;
   Float_t         true_kaon_daughter_end_z;
   Bool_t          true_kaon_daughter_end_inTPC;
   Bool_t          true_kaon_daughter_end_in5cmTPC;
   Bool_t          true_kaon_daughter_end_inCCInclusiveTPC;
   Bool_t          reco_nu_cc_filter;
   Bool_t          PFP_have_nuslice;;
   Float_t         reco_nu_vtx_x;
   Float_t         reco_nu_vtx_y;
   Float_t         reco_nu_vtx_z;
   Bool_t          reco_nu_vtx_inTPC;
   Bool_t          reco_nu_vtx_in5cmTPC;
   Bool_t          reco_nu_vtx_inCCInclusiveTPC;
   Int_t           reco_nu_ndaughters;
   Float_t         reco_ccmu_vtx_x;
   Float_t         reco_ccmu_vtx_y;
   Float_t         reco_ccmu_vtx_z;
   Bool_t          reco_ccmu_vtx_inTPC;
   Bool_t          reco_ccmu_vtx_in5cmTPC;
   Bool_t          reco_ccmu_vtx_inCCInclusiveTPC;
   Int_t           reco_ccmu_true_pdg;
   Int_t           reco_ccmu_true_origin;
   Bool_t          reco_ccmu_true_primary;
   Bool_t          reco_ccmu_true_end_inTPC;
   Bool_t          reco_ccmu_true_end_in5cmTPC;
   Bool_t          reco_ccmu_true_end_inCCInclusiveTPC;
   Float_t         reco_ccmu_true_length;
   Int_t           reco_ntracks;
   Float_t true_dau_pip_length;
   Float_t true_dau_muon_length;

   Float_t         reco_track_end_x[20];
   Float_t         reco_track_end_y[20];
   Float_t         reco_track_end_z[20];

Int_t n_recoRebDauTracks[20];
Float_t rebdautrack_length[20][10], rebdautracktrue_length[20], rebdautracktruedir_length[20], rebdautrack_pdg[20][10];
Float_t best_peak_x[20][10], best_peak_y[20][10], best_peak_z[20][10], best_peak_x_true[20], best_peak_y_true[20], best_peak_z_true[20];
 Float_t true_dau_muon_end_x;
Float_t true_dau_muon_end_y, true_dau_muon_end_z, true_dau_muon_start_x, true_dau_muon_start_y, true_dau_muon_start_z, true_dau_pip_end_x, true_dau_pip_end_y, true_dau_pip_end_z, true_dau_pip_start_x, true_dau_pip_start_y, true_dau_pip_start_z, true_dau_muon_theta, true_dau_muon_phi, true_dau_pip_theta, true_dau_pip_phi;


   Float_t         reco_track_distance[20];
   Int_t           reco_track_nhits0[20];
   Int_t           reco_track_nhits1[20];
   Int_t           reco_track_nhits2[20];
   Float_t         reco_track_length[20];
   Float_t         reco_track_theta[20];
   Float_t         reco_track_phi[20];
   Bool_t          reco_track_dir[20];
   Float_t         reco_track_chi2ka_pl0[20];
   Float_t         reco_track_chi2pr_pl0[20];
   Float_t         reco_track_chi2pi_pl0[20];
   Float_t         reco_track_chi2mu_pl0[20];
   Float_t         reco_track_chi2ka_pl1[20];
   Float_t         reco_track_chi2pr_pl1[20];
   Float_t         reco_track_chi2pi_pl1[20];
   Float_t         reco_track_chi2mu_pl1[20];
   Float_t         reco_track_chi2ka_pl2[20];
   Float_t         reco_track_chi2pr_pl2[20];
   Float_t         reco_track_chi2pi_pl2[20];
   Float_t         reco_track_chi2mu_pl2[20];
   Float_t         reco_track_chi2ka_3pl[20];
   Float_t         reco_track_chi2pr_3pl[20];
   Float_t         reco_track_chi2pi_3pl[20];
   Float_t         reco_track_chi2mu_3pl[20];
   Float_t         reco_track_likepr_3pl[20];
   Float_t         reco_track_llrpid_3pl[20];
   Float_t         reco_track_llrpid_k_3pl[20];
   Float_t         reco_track_Bragg_fwd_ka_pl0[20];
   Float_t         reco_track_Bragg_fwd_pr_pl0[20];
   Float_t         reco_track_Bragg_fwd_pi_pl0[20];
   Float_t         reco_track_Bragg_fwd_mu_pl0[20];
   Float_t         reco_track_Bragg_fwd_ka_pl1[20];
   Float_t         reco_track_Bragg_fwd_pr_pl1[20];
   Float_t         reco_track_Bragg_fwd_pi_pl1[20];
   Float_t         reco_track_Bragg_fwd_mu_pl1[20];
   Float_t         reco_track_Bragg_fwd_ka_pl2[20];
   Float_t         reco_track_Bragg_fwd_pr_pl2[20];
   Float_t         reco_track_Bragg_fwd_pi_pl2[20];
   Float_t         reco_track_Bragg_fwd_mu_pl2[20];
   //Float_t         reco_track_vtx_distance[20];

   Float_t         true_length[10];
   Float_t         true_p[10];
   Float_t         true_ke[10];
   Float_t         true_theta[10];
   Float_t         true_costheta[10];
   Float_t         true_phi[10];

   Float_t         reco_track_MIP_pl0[20];
   Float_t         reco_track_MIP_pl1[20];
   Float_t         reco_track_MIP_pl2[20];
   Float_t         reco_track_daughter_MIP_pl0[20][20];
   Float_t         reco_track_daughter_MIP_pl1[20][20];
   Float_t         reco_track_daughter_MIP_pl2[20][20];
   Bool_t          reco_track_vtx_inTPC[20];
   Bool_t          reco_track_vtx_in5cmTPC[20];
   Bool_t          reco_track_vtx_inCCInclusiveTPC[20];
   Bool_t          reco_track_end_inTPC[20];
   Bool_t          reco_track_end_in5cmTPC[20];
   Bool_t          reco_track_end_inCCInclusiveTPC[20];
   Int_t           reco_track_true_pdg[20];
   Int_t           reco_track_true_origin[20];
   Bool_t          reco_track_true_primary[20];
   Bool_t          reco_track_true_end_inTPC[20];
   Bool_t          reco_track_true_end_in5cmTPC[20];
   Bool_t          reco_track_true_end_inCCInclusiveTPC[20];
   Float_t         reco_track_true_length[20];
   Int_t           reco_track_ndaughters[20];
   Float_t         reco_track_daughter_distance[20][20];
   Float_t         reco_track_daughter_vtx_distance[20][20];
   Int_t           reco_track_daughter_nhits0[20][20];
   Int_t           reco_track_daughter_nhits1[20][20];
   Int_t           reco_track_daughter_nhits2[20][20];
   Float_t         reco_track_daughter_length[20][20];
   Float_t         reco_track_daughter_theta[20][20];
   Float_t         reco_track_daughter_phi[20][20];
   Float_t         reco_track_daughter_chi2ka_pl0[20][20];
   Float_t         reco_track_daughter_chi2pr_pl0[20][20];
   Float_t         reco_track_daughter_chi2pi_pl0[20][20];
   Float_t         reco_track_daughter_chi2mu_pl0[20][20];
   Float_t         reco_track_daughter_chi2ka_pl1[20][20];
   Float_t         reco_track_daughter_chi2pr_pl1[20][20];
   Float_t         reco_track_daughter_chi2pi_pl1[20][20];
   Float_t         reco_track_daughter_chi2mu_pl1[20][20];
   Float_t         reco_track_daughter_chi2ka_pl2[20][20];
   Float_t         reco_track_daughter_chi2pr_pl2[20][20];
   Float_t         reco_track_daughter_chi2pi_pl2[20][20];
   Float_t         reco_track_daughter_chi2mu_pl2[20][20];
   Float_t         reco_track_daughter_chi2ka_3pl[20][20];
   Float_t         reco_track_daughter_chi2pr_3pl[20][20];
   Float_t         reco_track_daughter_chi2pi_3pl[20][20];
   Float_t         reco_track_daughter_chi2mu_3pl[20][20];
   Float_t         reco_track_daughter_likepr_3pl[20][20];
   Float_t         reco_track_daughter_llrpid_3pl[20][20];
   Float_t         reco_track_daughter_llrpid_k_3pl[20][20];
   Float_t         reco_angle_track_daughter[20][20];
   Bool_t          reco_track_daughter_vtx_inTPC[20][20];
   Bool_t          reco_track_daughter_vtx_in5cmTPC[20][20];
   Bool_t          reco_track_daughter_vtx_inCCInclusiveTPC[20][20];
   Bool_t          reco_track_daughter_end_inTPC[20][20];
   Bool_t          reco_track_daughter_end_in5cmTPC[20][20];
   Bool_t          reco_track_daughter_end_inCCInclusiveTPC[20][20];
   Int_t           reco_track_daughter_true_pdg[20][20];
   Int_t           reco_track_daughter_true_origin[20][20];
   Bool_t          reco_track_daughter_true_primary[20][20];
   Bool_t          reco_track_daughter_true_end_inTPC[20][20];
   Bool_t          reco_track_daughter_true_end_in5cmTPC[20][20];
   Bool_t          reco_track_daughter_true_end_inCCInclusiveTPC[20][20];
   Float_t         reco_track_daughter_true_length[20][20];
   Int_t           reco_track_daughter_true_mother[20][20];
   Int_t           k_can_trkid;
   Int_t           mu_can_trkid;
   Float_t         k_mu_can_dis;
   Float_t         k_mu_open_angle;
   Float_t         k_vtx_dis;
   Int_t           cut_1;
   Int_t           cut_2;
   Int_t           cut_3;
   Int_t           cut_4;
   Int_t           cut_5;
   Int_t           cut_6;
   Int_t           cut_7;
   Int_t           cut_8;
   Int_t           cut_9;
   Int_t           cut_10;
   Int_t           cut_11;
   Int_t           cut_12;
   Int_t           cut_13;

   Float_t reco_track_kin0[20];
   Float_t reco_track_kin1[20];
   Float_t reco_track_kin2[20];

   Float_t reco_track_P_vtx[20];
   Float_t reco_track_P_str[20];
   Float_t reco_track_P_end[20];

   Int_t           reco_track_ndaughters_old[20];
   Float_t         reco_track_daughter_old_distance[20][20];
   Float_t         reco_track_daughter_old_length[20][20];
   Float_t         reco_track_daughter_old_theta[20][20];
   Float_t         reco_track_daughter_old_phi[20][20];
   Float_t         reco_track_daughter_old_chi2ka_pl0[20][20];
   Float_t         reco_track_daughter_old_chi2pr_pl0[20][20];
   Float_t         reco_track_daughter_old_chi2pi_pl0[20][20];
   Float_t         reco_track_daughter_old_chi2mu_pl0[20][20];
   Float_t         reco_track_daughter_old_chi2ka_pl1[20][20];
   Float_t         reco_track_daughter_old_chi2pr_pl1[20][20];
   Float_t         reco_track_daughter_old_chi2pi_pl1[20][20];
   Float_t         reco_track_daughter_old_chi2mu_pl1[20][20];
   Float_t         reco_track_daughter_old_chi2ka_pl2[20][20];
   Float_t         reco_track_daughter_old_chi2pr_pl2[20][20];
   Float_t         reco_track_daughter_old_chi2pi_pl2[20][20];
   Float_t         reco_track_daughter_old_chi2mu_pl2[20][20];
   Float_t         reco_track_daughter_old_chi2ka_3pl[20][20];
   Float_t         reco_track_daughter_old_chi2pr_3pl[20][20];
   Float_t         reco_track_daughter_old_chi2pi_3pl[20][20];
   Float_t         reco_track_daughter_old_chi2mu_3pl[20][20];
   Float_t         reco_track_daughter_old_likepr_3pl[20][20];
   Float_t         reco_track_daughter_old_llrpid_3pl[20][20];
   Float_t         reco_track_daughter_old_llrpid_k_3pl[20][20];
   Bool_t          reco_track_daughter_old_vtx_inTPC[20][20];
   Bool_t          reco_track_daughter_old_vtx_in5cmTPC[20][20];
   Bool_t          reco_track_daughter_old_vtx_inCCInclusiveTPC[20][20];
   Bool_t          reco_track_daughter_old_end_inTPC[20][20];
   Bool_t          reco_track_daughter_old_end_in5cmTPC[20][20];
   Bool_t          reco_track_daughter_old_end_inCCInclusiveTPC[20][20];
   Int_t           reco_track_daughter_old_true_pdg[20][20];


   // List of branches
   TBranch        *b_event;   //!
   TBranch        *b_run;   //!
   TBranch        *b_surbrun;   //!
   TBranch        *b_event_weight;   //!
   TBranch        *b_true_nu_energy;   //!
   TBranch        *b_true_nu_pdg;   //!
   TBranch        *b_true_nu_mode;   //!
   TBranch        *b_true_nu_ccnc;   //!
   TBranch        *b_true_nu_vtx_x;   //!
   TBranch        *b_true_nu_vtx_y;   //!
   TBranch        *b_true_nu_vtx_z;   //!
   TBranch        *b_true_nu_vtx_inTPC;   //!
   TBranch        *b_true_nu_vtx_in5cmTPC;   //!
   TBranch        *b_true_nu_vtx_inCCInclusiveTPC;   //!
   TBranch        *b_true_lepton_pdg;   //!
   TBranch        *b_true_lepton_p;   //!
   TBranch        *b_true_lepton_ke;   //!
   TBranch        *b_true_lepton_theta;   //!
   TBranch        *b_true_lepton_costheta;   //!
   TBranch        *b_true_lepton_phi;   //!
   TBranch        *b_true_nkaons;   //!
   TBranch        *b_true_nhyperons;   //!
   TBranch        *b_true_kaon_length;   //!
   TBranch        *b_true_kaon_p;   //!
   TBranch        *b_true_kaon_ke;   //!
   TBranch        *b_true_kaon_theta;   //!
   TBranch        *b_true_kaon_costheta;   //!
   TBranch        *b_true_kaon_phi;   //!

  TBranch        *b_true_dau_muon_end_x;
   TBranch        *b_true_dau_muon_end_y;
   TBranch        *b_true_dau_muon_end_z;
   TBranch        *b_true_dau_muon_start_x;
   TBranch        *b_true_dau_muon_start_y;
   TBranch        *b_true_dau_muon_start_z;
   TBranch        *b_true_dau_pip_end_x;
   TBranch        *b_true_dau_pip_end_y;
   TBranch        *b_true_dau_pip_end_z;
   TBranch        *b_true_dau_pip_start_x;
   TBranch        *b_true_dau_pip_start_y;
   TBranch        *b_true_dau_pip_start_z;
   TBranch        *b_true_dau_muon_phi;
   TBranch        *b_true_dau_muon_theta;
   TBranch        *b_true_dau_pip_phi;
   TBranch        *b_true_dau_pip_theta;


   TBranch        *b_true_length;   //!
   TBranch        *b_true_p;   //!
   TBranch        *b_true_ke;   //!
   TBranch        *b_true_theta;   //!
   TBranch        *b_true_phi;   //!

   TBranch        *b_true_kaon_ccmuon_angle;   //!
   TBranch        *b_true_kaon_ccmuon_cosangle;   //!
   TBranch        *b_true_kaon_end_process;   //!
   TBranch        *b_true_kaon_end_ke;   //!
   TBranch        *b_true_kaon_end_x;   //!
   TBranch        *b_true_kaon_end_y;   //!
   TBranch        *b_true_kaon_end_z;   //!
   TBranch        *b_reco_track_end_x;
   TBranch        *b_reco_track_end_y;
   TBranch        *b_reco_track_end_z;
   TBranch        *b_true_kaon_end_inTPC;   //!
   TBranch        *b_true_kaon_end_in5cmTPC;   //!
   TBranch        *b_true_kaon_end_inCCInclusiveTPC;   //!
   TBranch        *b_true_kaon_ndaughters;   //!
   TBranch        *b_true_kaon_ndaughters_decay;   //!
   TBranch        *b_true_kaon_ndaughters_inelastic;   //!
   TBranch        *b_true_kaon_ndecmup;   //!
   TBranch        *b_true_kaon_ndecpip;   //!
   TBranch        *b_true_kaon_ninekap;   //!
   TBranch        *b_true_kaon_ninepip;   //!
   TBranch        *b_true_kaon_ninepro;   //!
   TBranch        *b_true_kaon_daughter_length;   //!
   TBranch        *b_true_kaon_daughter_p;   //!
   TBranch        *b_true_kaon_daughter_ke;   //!
   TBranch        *b_true_kaon_daughter_theta;   //!
   TBranch        *b_true_kaon_daughter_costheta;   //!
   TBranch        *b_true_kaon_daughter_angle;   //!
   TBranch        *b_true_kaon_daughter_cosangle;   //!
   TBranch        *b_true_kaon_daughter_pdg;   //!
   TBranch        *b_true_kaon_daughter_end_x;   //!
   TBranch        *b_true_kaon_daughter_end_y;   //!
   TBranch        *b_true_kaon_daughter_end_z;   //!
   TBranch        *b_true_kaon_daughter_endInTPC;   //!
   TBranch        *b_true_kaon_daughter_end_in5cmTPC;   //!
   TBranch        *b_true_kaon_daughter_end_inCCInclusiveTPC;   //!
   TBranch        *b_reco_nu_cc_filter;   //!
   TBranch        *b_PFP_have_nuslice;   //!
   TBranch        *b_reco_nu_vtx_x;   //!
   TBranch        *b_reco_nu_vtx_y;   //!
   TBranch        *b_reco_nu_vtx_z;   //!
   TBranch        *b_reco_nu_vtx_inTPC;   //!
   TBranch        *b_reco_nu_vtx_in5cmTPC;   //!
   TBranch        *b_reco_nu_vtx_inCCInclusiveTPC;   //!
   TBranch        *b_reco_nu_ndaughters;   //!
   TBranch        *b_reco_ccmu_vtx_x;   //!
   TBranch        *b_reco_ccmu_vtx_y;   //!
   TBranch        *b_reco_ccmu_vtx_z;   //!
   TBranch        *b_reco_ccmu_vtx_inTPC;   //!
   TBranch        *b_reco_ccmu_vtx_in5cmTPC;   //!
   TBranch        *b_reco_ccmu_vtx_inCCInclusiveTPC;   //!
   TBranch        *b_reco_ccmu_true_pdg;   //!
   TBranch        *b_reco_ccmu_true_origin;   //!
   TBranch        *b_reco_ccmu_true_primary;   //!
   TBranch        *b_reco_ccmu_true_end_inTPC;   //!
   TBranch        *b_reco_ccmu_true_end_in5cmTPC;   //!
   TBranch        *b_reco_ccmu_true_end_inCCInclusiveTPC;   //!
   TBranch        *b_reco_ccmu_true_length;   //!
   TBranch        *b_reco_ntracks;   //!

   TBranch        *b_true_dau_muon_length;
   TBranch        *b_true_dau_pip_length;

   TBranch        *b_n_recoRebDauTracks;
   TBranch        *b_rebdautrack_length;
   TBranch        *b_rebdautracktrue_length;
   TBranch        *b_rebdautracktruedir_length;
   TBranch        *b_rebdautrack_pdg;
   TBranch        *b_best_peak_x;
   TBranch        *b_best_peak_y;
   TBranch        *b_best_peak_z;
   TBranch        *b_best_peak_x_true;
   TBranch        *b_best_peak_y_true;
   TBranch        *b_best_peak_z_true;
 
   TBranch        *b_reco_track_distance;   //!
   TBranch        *b_reco_track_nhits0;   //!
   TBranch        *b_reco_track_nhits1;   //!
   TBranch        *b_reco_track_nhits2;   //!
   TBranch        *b_reco_track_length;   //!
   TBranch        *b_reco_track_theta;   //!
   TBranch        *b_reco_track_phi;   //!
   TBranch        *b_reco_track_dir;   //!
   TBranch        *b_reco_track_chi2ka_pl0;   //!
   TBranch        *b_reco_track_chi2pr_pl0;   //!
   TBranch        *b_reco_track_chi2pi_pl0;   //!
   TBranch        *b_reco_track_chi2mu_pl0;   //!
   TBranch        *b_reco_track_chi2ka_pl1;   //!
   TBranch        *b_reco_track_chi2pr_pl1;   //!
   TBranch        *b_reco_track_chi2pi_pl1;   //!
   TBranch        *b_reco_track_chi2mu_pl1;   //!
   TBranch        *b_reco_track_chi2ka_pl2;   //!
   TBranch        *b_reco_track_chi2pr_pl2;   //!
   TBranch        *b_reco_track_chi2pi_pl2;   //!
   TBranch        *b_reco_track_chi2mu_pl2;   //!
   TBranch        *b_reco_track_chi2ka_3pl;   //!
   TBranch        *b_reco_track_chi2pr_3pl;   //!
   TBranch        *b_reco_track_chi2pi_3pl;   //!
   TBranch        *b_reco_track_chi2mu_3pl;   //!
   TBranch        *b_reco_track_likepr_3pl;   //!
   TBranch        *b_reco_track_llrpid_3pl;   //!
   TBranch        *b_reco_track_llrpid_k_3pl;   //!
   TBranch        *b_reco_track_Bragg_fwd_ka_pl0;
   TBranch        *b_reco_track_Bragg_fwd_pr_pl0;
   TBranch        *b_reco_track_Bragg_fwd_pi_pl0;
   TBranch        *b_reco_track_Bragg_fwd_mu_pl0;
   TBranch        *b_reco_track_Bragg_fwd_ka_pl1;
   TBranch        *b_reco_track_Bragg_fwd_pr_pl1;
   TBranch        *b_reco_track_Bragg_fwd_pi_pl1;
   TBranch        *b_reco_track_Bragg_fwd_mu_pl1;
   TBranch        *b_reco_track_Bragg_fwd_ka_pl2;
   TBranch        *b_reco_track_Bragg_fwd_pr_pl2;
   TBranch        *b_reco_track_Bragg_fwd_pi_pl2;
   TBranch        *b_reco_track_Bragg_fwd_mu_pl2;
   TBranch        *b_reco_track_MIP_pl0;   //!
   TBranch        *b_reco_track_MIP_pl1;   //!
   TBranch        *b_reco_track_MIP_pl2;   //!
   //TBranch        *b_reco_track_vtx_distance;   //!
   TBranch        *b_reco_track_daughter_MIP_pl0;   //!
   TBranch        *b_reco_track_daughter_MIP_pl1;   //!
   TBranch        *b_reco_track_daughter_MIP_pl2;   //!
   TBranch        *b_reco_track_vtx_inTPC;   //!
   TBranch        *b_reco_track_vtx_in5cmTPC;   //!
   TBranch        *b_reco_track_vtx_inCCInclusiveTPC;   //!
   TBranch        *b_reco_track_end_inTPC;   //!
   TBranch        *b_reco_track_end_in5cmTPC;   //!
   TBranch        *b_reco_track_end_inCCInclusiveTPC;   //!
   TBranch        *b_reco_track_true_pdg;   //!
   TBranch        *b_reco_track_true_origin;   //!
   TBranch        *b_reco_track_true_primary;   //!
   TBranch        *b_reco_track_true_end_inTPC;   //!
   TBranch        *b_reco_track_true_end_in5cmTPC;   //!
   TBranch        *b_reco_track_true_end_inCCInclusiveTPC;   //!
   TBranch        *b_reco_track_true_length;   //!
   TBranch        *b_reco_track_ndaughters;   //!
   TBranch        *b_reco_track_daughter_distance;   //!
   TBranch        *b_reco_track_daughter_vtx_distance;   //!
   TBranch        *b_reco_track_daughter_nhits0;   //!
   TBranch        *b_reco_track_daughter_nhits1;   //!
   TBranch        *b_reco_track_daughter_nhits2;   //!
   TBranch        *b_reco_track_daughter_length;   //!
   TBranch        *b_reco_track_daughter_theta;   //!
   TBranch        *b_reco_track_daughter_phi;   //!
   TBranch        *b_reco_track_daughter_chi2ka_pl0;   //!
   TBranch        *b_reco_track_daughter_chi2pr_pl0;   //!
   TBranch        *b_reco_track_daughter_chi2pi_pl0;   //!
   TBranch        *b_reco_track_daughter_chi2mu_pl0;   //!
   TBranch        *b_reco_track_daughter_chi2ka_pl1;   //!
   TBranch        *b_reco_track_daughter_chi2pr_pl1;   //!
   TBranch        *b_reco_track_daughter_chi2pi_pl1;   //!
   TBranch        *b_reco_track_daughter_chi2mu_pl1;   //!
   TBranch        *b_reco_track_daughter_chi2ka_pl2;   //!
   TBranch        *b_reco_track_daughter_chi2pr_pl2;   //!
   TBranch        *b_reco_track_daughter_chi2pi_pl2;   //!
   TBranch        *b_reco_track_daughter_chi2mu_pl2;   //!
   TBranch        *b_reco_track_daughter_chi2ka_3pl;   //!
   TBranch        *b_reco_track_daughter_chi2pr_3pl;   //!
   TBranch        *b_reco_track_daughter_chi2pi_3pl;   //!
   TBranch        *b_reco_track_daughter_chi2mu_3pl;   //!
   TBranch        *b_reco_track_daughter_likepr_3pl;   //!
   TBranch        *b_reco_track_daughter_llrpid_3pl;   //!
   TBranch        *b_reco_track_daughter_llrpid_k_3pl;   //!
   TBranch        *b_reco_angle_track_daughter;   //!
   TBranch        *b_reco_track_daughter_vtx_inTPC;   //!
   TBranch        *b_reco_track_daughter_vtx_in5cmTPC;   //!
   TBranch        *b_reco_track_daughter_vtx_inCCInclusiveTPC;   //!
   TBranch        *b_reco_track_daughter_end_inTPC;   //!
   TBranch        *b_reco_track_daughter_end_in5cmTPC;   //!
   TBranch        *b_reco_track_daughter_end_inCCInclusiveTPC;   //!
   TBranch        *b_reco_track_daughter_true_pdg;   //!
   TBranch        *b_reco_track_daughter_true_origin;   //!
   TBranch        *b_reco_track_daughter_true_primary;   //!
   TBranch        *b_reco_track_daughter_true_end_inTPC;   //!
   TBranch        *b_reco_track_daughter_true_end_in5cmTPC;   //!
   TBranch        *b_reco_track_daughter_true_end_inCCInclusiveTPC;   //!
   TBranch        *b_reco_track_daughter_true_length;   //!
   TBranch        *b_reco_track_daughter_true_mother;   //!
   TBranch        *b_k_can_trkid;   //!
   TBranch        *b_mu_can_trkid;   //!
   TBranch        *b_k_mu_can_dis;   //!
   TBranch        *b_k_mu_open_angle;   //!
   TBranch        *b_k_vtx_dis;   //!
   TBranch        *b_cut_1;   //!
   TBranch        *b_cut_2;   //!
   TBranch        *b_cut_3;   //!
   TBranch        *b_cut_4;   //!
   TBranch        *b_cut_5;   //!
   TBranch        *b_cut_6;   //!
   TBranch        *b_cut_7;   //!
   TBranch        *b_cut_8;   //!
   TBranch        *b_cut_9;   //!
   TBranch        *b_cut_10;   //!
   TBranch        *b_cut_11;   //!
   TBranch        *b_cut_12;   //!
   TBranch        *b_cut_13;   //!

   TBranch *b_reco_track_kin0;
   TBranch *b_reco_track_kin1;
   TBranch *b_reco_track_kin2;

   TBranch *b_reco_track_P_vtx;
   TBranch *b_reco_track_P_str;
   TBranch *b_reco_track_P_end;

   TBranch        *b_reco_track_ndaughters_old;   //!
   TBranch        *b_reco_track_daughter_old_distance;   //!
   TBranch        *b_reco_track_daughter_old_length;   //!
   TBranch        *b_reco_track_daughter_old_theta;   //!
   TBranch        *b_reco_track_daughter_old_phi;   //!
   TBranch        *b_reco_track_daughter_old_chi2ka_pl0;   //!
   TBranch        *b_reco_track_daughter_old_chi2pr_pl0;   //!
   TBranch        *b_reco_track_daughter_old_chi2pi_pl0;   //!
   TBranch        *b_reco_track_daughter_old_chi2mu_pl0;   //!
   TBranch        *b_reco_track_daughter_old_chi2ka_pl1;   //!
   TBranch        *b_reco_track_daughter_old_chi2pr_pl1;   //!
   TBranch        *b_reco_track_daughter_old_chi2pi_pl1;   //!
   TBranch        *b_reco_track_daughter_old_chi2mu_pl1;   //!
   TBranch        *b_reco_track_daughter_old_chi2ka_pl2;   //!
   TBranch        *b_reco_track_daughter_old_chi2pr_pl2;   //!
   TBranch        *b_reco_track_daughter_old_chi2pi_pl2;   //!
   TBranch        *b_reco_track_daughter_old_chi2mu_pl2;   //!
   TBranch        *b_reco_track_daughter_old_chi2ka_3pl;   //!
   TBranch        *b_reco_track_daughter_old_chi2pr_3pl;   //!
   TBranch        *b_reco_track_daughter_old_chi2pi_3pl;   //!
   TBranch        *b_reco_track_daughter_old_chi2mu_3pl;   //!
   TBranch        *b_reco_track_daughter_old_likepr_3pl;   //!
   TBranch        *b_reco_track_daughter_old_llrpid_3pl;   //!
   TBranch        *b_reco_track_daughter_old_llrpid_k_3pl;   //!
   TBranch        *b_reco_track_daughter_old_vtx_inTPC;   //!
   TBranch        *b_reco_track_daughter_old_vtx_in5cmTPC;   //!
   TBranch        *b_reco_track_daughter_old_vtx_inCCInclusiveTPC;   //!
   TBranch        *b_reco_track_daughter_old_end_inTPC;   //!
   TBranch        *b_reco_track_daughter_old_end_in5cmTPC;   //!
   TBranch        *b_reco_track_daughter_old_end_inCCInclusiveTPC;   //!
   TBranch        *b_reco_track_daughter_old_true_pdg;


   Event(TTree *tree=0);
   virtual ~Event();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef Event_cxx
Event::Event(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/nashome/a/arturo/uboone/uboonedata/uboonecode_v08_00_00_32/CCKaonFilter/cckaonfilter_ana_cck_v7.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("/nashome/a/arturo/uboone/uboonedata/uboonecode_v08_00_00_32/CCKaonFilter/cckaonfilter_ana_cck_v7.root");
      }
      TDirectory * dir = (TDirectory*)f->Get("/nashome/a/arturo/uboone/uboonedata/uboonecode_v08_00_00_32/CCKaonFilter/cckaonfilter_ana_cck_v7.root:/CCKaonAnalyzer");
      dir->GetObject("Event",tree);

   }
   Init(tree);
}

Event::~Event()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t Event::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t Event::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void Event::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("event", &event, &b_event);
   fChain->SetBranchAddress("run", &run, &b_run);
   fChain->SetBranchAddress("subrun", &subrun, &b_surbrun);
   //fChain->SetBranchAddress("event_weight", &event_weight, &b_event_weight);
   fChain->SetBranchAddress("true_nu_energy", &true_nu_energy, &b_true_nu_energy);
   fChain->SetBranchAddress("true_nu_pdg", &true_nu_pdg, &b_true_nu_pdg);
   fChain->SetBranchAddress("true_nu_mode", &true_nu_mode, &b_true_nu_mode);
   fChain->SetBranchAddress("true_nu_ccnc", &true_nu_ccnc, &b_true_nu_ccnc);
   fChain->SetBranchAddress("true_nu_vtx_x", &true_nu_vtx_x, &b_true_nu_vtx_x);
   fChain->SetBranchAddress("true_nu_vtx_y", &true_nu_vtx_y, &b_true_nu_vtx_y);
   fChain->SetBranchAddress("true_nu_vtx_z", &true_nu_vtx_z, &b_true_nu_vtx_z);
   fChain->SetBranchAddress("true_nu_vtx_inTPC", &true_nu_vtx_inTPC, &b_true_nu_vtx_inTPC);
   fChain->SetBranchAddress("true_nu_vtx_in5cmTPC", &true_nu_vtx_in5cmTPC, &b_true_nu_vtx_in5cmTPC);
   fChain->SetBranchAddress("true_nu_vtx_inCCInclusiveTPC", &true_nu_vtx_inCCInclusiveTPC, &b_true_nu_vtx_inCCInclusiveTPC);
   fChain->SetBranchAddress("true_dau_muon_end_x", &true_dau_muon_end_x, &b_true_dau_muon_end_x);
   //fChain->SetBranchStatus("true_dau_muon_end_x", 1);
   fChain->SetBranchAddress("true_dau_muon_end_y", &true_dau_muon_end_y, &b_true_dau_muon_end_y);
   fChain->SetBranchAddress("true_dau_muon_end_z", &true_dau_muon_end_z, &b_true_dau_muon_end_z);
   fChain->SetBranchAddress("true_dau_muon_start_x", &true_dau_muon_start_x, &b_true_dau_muon_start_x);
   fChain->SetBranchAddress("true_dau_muon_start_y", &true_dau_muon_start_y, &b_true_dau_muon_start_y);
   fChain->SetBranchAddress("true_dau_muon_start_z", &true_dau_muon_start_z, &b_true_dau_muon_start_z);
   fChain->SetBranchAddress("true_dau_pip_end_x", &true_dau_pip_end_x, &b_true_dau_pip_end_x);
   fChain->SetBranchAddress("true_dau_pip_end_y", &true_dau_pip_end_y, &b_true_dau_pip_end_y);
   fChain->SetBranchAddress("true_dau_pip_end_z", &true_dau_pip_end_z, &b_true_dau_pip_end_z);
   fChain->SetBranchAddress("true_dau_pip_start_x", &true_dau_pip_start_x, &b_true_dau_pip_start_x);
   fChain->SetBranchAddress("true_dau_pip_start_y", &true_dau_pip_start_y, &b_true_dau_pip_start_y);
   fChain->SetBranchAddress("true_dau_pip_start_z", &true_dau_pip_start_z, &b_true_dau_pip_start_z);
   fChain->SetBranchAddress("true_dau_muon_theta", &true_dau_muon_theta, &b_true_dau_muon_theta);
   fChain->SetBranchAddress("true_dau_muon_phi", &true_dau_muon_phi, &b_true_dau_muon_phi);
   fChain->SetBranchAddress("true_dau_pip_theta", &true_dau_pip_theta, &b_true_dau_pip_theta);
   fChain->SetBranchAddress("true_dau_pip_phi", &true_dau_pip_phi, &b_true_dau_pip_phi);

   fChain->SetBranchAddress("true_lepton_pdg", &true_lepton_pdg, &b_true_lepton_pdg);
   fChain->SetBranchAddress("true_lepton_p", &true_lepton_p, &b_true_lepton_p);
   fChain->SetBranchAddress("true_lepton_ke", &true_lepton_ke, &b_true_lepton_ke);
   fChain->SetBranchAddress("true_lepton_theta", &true_lepton_theta, &b_true_lepton_theta);
   fChain->SetBranchAddress("true_lepton_costheta", &true_lepton_costheta, &b_true_lepton_costheta);
   fChain->SetBranchAddress("true_lepton_phi", &true_lepton_phi, &b_true_lepton_phi);
   fChain->SetBranchAddress("true_nkaons", &true_nkaons, &b_true_nkaons);
   fChain->SetBranchAddress("true_nhyperons", &true_nhyperons, &b_true_nhyperons);
   fChain->SetBranchAddress("true_kaon_length", &true_kaon_length, &b_true_kaon_length);
   fChain->SetBranchAddress("true_kaon_p", &true_kaon_p, &b_true_kaon_p);
   fChain->SetBranchAddress("true_kaon_ke", &true_kaon_ke, &b_true_kaon_ke);
   fChain->SetBranchAddress("true_kaon_theta", &true_kaon_theta, &b_true_kaon_theta);
   fChain->SetBranchAddress("true_kaon_costheta", &true_kaon_costheta, &b_true_kaon_costheta);
   fChain->SetBranchAddress("true_kaon_phi", &true_kaon_phi, &b_true_kaon_phi);
   fChain->SetBranchAddress("true_kaon_ccmuon_angle", &true_kaon_ccmuon_angle, &b_true_kaon_ccmuon_angle);
   fChain->SetBranchAddress("true_kaon_ccmuon_cosangle", &true_kaon_ccmuon_cosangle, &b_true_kaon_ccmuon_cosangle);
   fChain->SetBranchAddress("true_kaon_end_process", &true_kaon_end_process, &b_true_kaon_end_process);
   fChain->SetBranchAddress("true_kaon_end_ke", &true_kaon_end_ke, &b_true_kaon_end_ke);
   fChain->SetBranchAddress("true_kaon_end_x", &true_kaon_end_x, &b_true_kaon_end_x);
   fChain->SetBranchAddress("true_kaon_end_y", &true_kaon_end_y, &b_true_kaon_end_y);
   fChain->SetBranchAddress("true_kaon_end_z", &true_kaon_end_z, &b_true_kaon_end_z);
   fChain->SetBranchAddress("reco_track_end_x", &reco_track_end_x, &b_reco_track_end_x);
   fChain->SetBranchAddress("reco_track_end_y", &reco_track_end_y, &b_reco_track_end_y);
   fChain->SetBranchAddress("reco_track_end_z", &reco_track_end_z, &b_reco_track_end_z);
   fChain->SetBranchAddress("true_kaon_end_inTPC", &true_kaon_end_inTPC, &b_true_kaon_end_inTPC);
   fChain->SetBranchAddress("true_kaon_end_in5cmTPC", &true_kaon_end_in5cmTPC, &b_true_kaon_end_in5cmTPC);
   fChain->SetBranchAddress("true_kaon_end_inCCInclusiveTPC", &true_kaon_end_inCCInclusiveTPC, &b_true_kaon_end_inCCInclusiveTPC);
   fChain->SetBranchAddress("true_kaon_ndaughters", &true_kaon_ndaughters, &b_true_kaon_ndaughters);
   fChain->SetBranchAddress("true_kaon_ndaughters_decay", &true_kaon_ndaughters_decay, &b_true_kaon_ndaughters_decay);
   fChain->SetBranchAddress("true_kaon_ndaughters_inelastic", &true_kaon_ndaughters_inelastic, &b_true_kaon_ndaughters_inelastic);
   fChain->SetBranchAddress("true_kaon_ndecmup", &true_kaon_ndecmup, &b_true_kaon_ndecmup);
   fChain->SetBranchAddress("true_kaon_ndecpip", &true_kaon_ndecpip, &b_true_kaon_ndecpip);
   fChain->SetBranchAddress("true_kaon_ninekap", &true_kaon_ninekap, &b_true_kaon_ninekap);
   fChain->SetBranchAddress("true_kaon_ninepip", &true_kaon_ninepip, &b_true_kaon_ninepip);
   fChain->SetBranchAddress("true_kaon_ninepro", &true_kaon_ninepro, &b_true_kaon_ninepro);
   fChain->SetBranchAddress("true_kaon_daughter_length", &true_kaon_daughter_length, &b_true_kaon_daughter_length);
   fChain->SetBranchAddress("true_kaon_daughter_p", &true_kaon_daughter_p, &b_true_kaon_daughter_p);
   fChain->SetBranchAddress("true_kaon_daughter_ke", &true_kaon_daughter_ke, &b_true_kaon_daughter_ke);
   fChain->SetBranchAddress("true_kaon_daughter_theta", &true_kaon_daughter_theta, &b_true_kaon_daughter_theta);
   fChain->SetBranchAddress("true_kaon_daughter_costheta", &true_kaon_daughter_costheta, &b_true_kaon_daughter_costheta);
   fChain->SetBranchAddress("true_kaon_daughter_angle", &true_kaon_daughter_angle, &b_true_kaon_daughter_angle);
   fChain->SetBranchAddress("true_kaon_daughter_cosangle", &true_kaon_daughter_cosangle, &b_true_kaon_daughter_cosangle);
   fChain->SetBranchAddress("true_kaon_daughter_pdg", &true_kaon_daughter_pdg, &b_true_kaon_daughter_pdg);
   fChain->SetBranchAddress("true_kaon_daughter_end_x", &true_kaon_daughter_end_x, &b_true_kaon_daughter_end_x);
   fChain->SetBranchAddress("true_kaon_daughter_end_y", &true_kaon_daughter_end_y, &b_true_kaon_daughter_end_y);
   fChain->SetBranchAddress("true_kaon_daughter_end_z", &true_kaon_daughter_end_z, &b_true_kaon_daughter_end_z);
   fChain->SetBranchAddress("true_kaon_daughter_end_inTPC", &true_kaon_daughter_end_inTPC, &b_true_kaon_daughter_endInTPC);
   fChain->SetBranchAddress("true_kaon_daughter_end_in5cmTPC", &true_kaon_daughter_end_in5cmTPC, &b_true_kaon_daughter_end_in5cmTPC);
   fChain->SetBranchAddress("true_kaon_daughter_end_inCCInclusiveTPC", &true_kaon_daughter_end_inCCInclusiveTPC, &b_true_kaon_daughter_end_inCCInclusiveTPC);

   fChain->SetBranchAddress("true_length", &true_length, &b_true_length);
   fChain->SetBranchAddress("true_p", &true_p, &b_true_p);
   fChain->SetBranchAddress("true_ke", &true_ke, &b_true_ke);
   fChain->SetBranchAddress("true_theta", &true_theta, &b_true_theta);
   fChain->SetBranchAddress("true_phi", &true_phi, &b_true_phi);

   fChain->SetBranchAddress("reco_nu_cc_filter", &reco_nu_cc_filter, &b_reco_nu_cc_filter);
   fChain->SetBranchAddress("PFP_have_nuslice", &PFP_have_nuslice, &b_PFP_have_nuslice);
   fChain->SetBranchAddress("reco_nu_vtx_x", &reco_nu_vtx_x, &b_reco_nu_vtx_x);
   fChain->SetBranchAddress("reco_nu_vtx_y", &reco_nu_vtx_y, &b_reco_nu_vtx_y);
   fChain->SetBranchAddress("reco_nu_vtx_z", &reco_nu_vtx_z, &b_reco_nu_vtx_z);
   fChain->SetBranchAddress("reco_nu_vtx_inTPC", &reco_nu_vtx_inTPC, &b_reco_nu_vtx_inTPC);
   fChain->SetBranchAddress("reco_nu_vtx_in5cmTPC", &reco_nu_vtx_in5cmTPC, &b_reco_nu_vtx_in5cmTPC);
   fChain->SetBranchAddress("reco_nu_vtx_inCCInclusiveTPC", &reco_nu_vtx_inCCInclusiveTPC, &b_reco_nu_vtx_inCCInclusiveTPC);
   fChain->SetBranchAddress("reco_nu_ndaughters", &reco_nu_ndaughters, &b_reco_nu_ndaughters);
   fChain->SetBranchAddress("reco_ccmu_vtx_x", &reco_ccmu_vtx_x, &b_reco_ccmu_vtx_x);
   fChain->SetBranchAddress("reco_ccmu_vtx_y", &reco_ccmu_vtx_y, &b_reco_ccmu_vtx_y);
   fChain->SetBranchAddress("reco_ccmu_vtx_z", &reco_ccmu_vtx_z, &b_reco_ccmu_vtx_z);
   fChain->SetBranchAddress("reco_ccmu_vtx_inTPC", &reco_ccmu_vtx_inTPC, &b_reco_ccmu_vtx_inTPC);
   fChain->SetBranchAddress("reco_ccmu_vtx_in5cmTPC", &reco_ccmu_vtx_in5cmTPC, &b_reco_ccmu_vtx_in5cmTPC);
   fChain->SetBranchAddress("reco_ccmu_vtx_inCCInclusiveTPC", &reco_ccmu_vtx_inCCInclusiveTPC, &b_reco_ccmu_vtx_inCCInclusiveTPC);
   fChain->SetBranchAddress("reco_ccmu_true_pdg", &reco_ccmu_true_pdg, &b_reco_ccmu_true_pdg);
   fChain->SetBranchAddress("reco_ccmu_true_origin", &reco_ccmu_true_origin, &b_reco_ccmu_true_origin);
   fChain->SetBranchAddress("reco_ccmu_true_primary", &reco_ccmu_true_primary, &b_reco_ccmu_true_primary);
   fChain->SetBranchAddress("reco_ccmu_true_end_inTPC", &reco_ccmu_true_end_inTPC, &b_reco_ccmu_true_end_inTPC);
   fChain->SetBranchAddress("reco_ccmu_true_end_in5cmTPC", &reco_ccmu_true_end_in5cmTPC, &b_reco_ccmu_true_end_in5cmTPC);
   fChain->SetBranchAddress("reco_ccmu_true_end_inCCInclusiveTPC", &reco_ccmu_true_end_inCCInclusiveTPC, &b_reco_ccmu_true_end_inCCInclusiveTPC);
   fChain->SetBranchAddress("reco_ccmu_true_length", &reco_ccmu_true_length, &b_reco_ccmu_true_length);
   fChain->SetBranchAddress("reco_ntracks", &reco_ntracks, &b_reco_ntracks);

   fChain->SetBranchAddress("true_dau_pip_length", &true_dau_pip_length, &b_true_dau_pip_length);
   fChain->SetBranchAddress("true_dau_muon_length", &true_dau_muon_length, &b_true_dau_muon_length);

   fChain->SetBranchAddress("n_recoRebDauTracks", n_recoRebDauTracks, &b_n_recoRebDauTracks);
   fChain->SetBranchAddress("rebdautrack_length", rebdautrack_length, &b_rebdautrack_length);
   fChain->SetBranchAddress("rebdautracktrue_length", &rebdautracktrue_length, &b_rebdautracktrue_length);
   fChain->SetBranchAddress("rebdautracktruedir_length", &rebdautracktruedir_length, &b_rebdautracktruedir_length);
   fChain->SetBranchAddress("rebdautrack_pdg", &rebdautrack_pdg, &b_rebdautrack_pdg);
   fChain->SetBranchAddress("best_peak_x", &best_peak_x, &b_best_peak_x);
   fChain->SetBranchAddress("best_peak_y", &best_peak_y, &b_best_peak_y);
   fChain->SetBranchAddress("best_peak_z", &best_peak_z, &b_best_peak_z);
   fChain->SetBranchAddress("best_peak_x_true", &best_peak_x_true, &b_best_peak_x_true);
   fChain->SetBranchAddress("best_peak_y_true", &best_peak_y_true, &b_best_peak_y_true);
   fChain->SetBranchAddress("best_peak_z_true", &best_peak_z_true, &b_best_peak_z_true);

   fChain->SetBranchAddress("reco_track_distance", reco_track_distance, &b_reco_track_distance);
   fChain->SetBranchAddress("reco_track_nhits0", reco_track_nhits0, &b_reco_track_nhits0);
   fChain->SetBranchAddress("reco_track_nhits1", reco_track_nhits1, &b_reco_track_nhits1);
   fChain->SetBranchAddress("reco_track_nhits2", reco_track_nhits2, &b_reco_track_nhits2);
   fChain->SetBranchAddress("reco_track_length", reco_track_length, &b_reco_track_length);
   fChain->SetBranchAddress("reco_track_theta", reco_track_theta, &b_reco_track_theta);
   fChain->SetBranchAddress("reco_track_phi", reco_track_phi, &b_reco_track_phi);
   fChain->SetBranchAddress("reco_track_dir", reco_track_dir, &b_reco_track_dir);
   fChain->SetBranchAddress("reco_track_chi2ka_pl0", reco_track_chi2ka_pl0, &b_reco_track_chi2ka_pl0);
   fChain->SetBranchAddress("reco_track_chi2pr_pl0", reco_track_chi2pr_pl0, &b_reco_track_chi2pr_pl0);
   fChain->SetBranchAddress("reco_track_chi2pi_pl0", reco_track_chi2pi_pl0, &b_reco_track_chi2pi_pl0);
   fChain->SetBranchAddress("reco_track_chi2mu_pl0", reco_track_chi2mu_pl0, &b_reco_track_chi2mu_pl0);
   fChain->SetBranchAddress("reco_track_chi2ka_pl1", reco_track_chi2ka_pl1, &b_reco_track_chi2ka_pl1);
   fChain->SetBranchAddress("reco_track_chi2pr_pl1", reco_track_chi2pr_pl1, &b_reco_track_chi2pr_pl1);
   fChain->SetBranchAddress("reco_track_chi2pi_pl1", reco_track_chi2pi_pl1, &b_reco_track_chi2pi_pl1);
   fChain->SetBranchAddress("reco_track_chi2mu_pl1", reco_track_chi2mu_pl1, &b_reco_track_chi2mu_pl1);
   fChain->SetBranchAddress("reco_track_chi2ka_pl2", reco_track_chi2ka_pl2, &b_reco_track_chi2ka_pl2);
   fChain->SetBranchAddress("reco_track_chi2pr_pl2", reco_track_chi2pr_pl2, &b_reco_track_chi2pr_pl2);
   fChain->SetBranchAddress("reco_track_chi2pi_pl2", reco_track_chi2pi_pl2, &b_reco_track_chi2pi_pl2);
   fChain->SetBranchAddress("reco_track_chi2mu_pl2", reco_track_chi2mu_pl2, &b_reco_track_chi2mu_pl2);
   fChain->SetBranchAddress("reco_track_chi2ka_3pl", reco_track_chi2ka_3pl, &b_reco_track_chi2ka_3pl);
   fChain->SetBranchAddress("reco_track_chi2pr_3pl", reco_track_chi2pr_3pl, &b_reco_track_chi2pr_3pl);
   fChain->SetBranchAddress("reco_track_chi2pi_3pl", reco_track_chi2pi_3pl, &b_reco_track_chi2pi_3pl);
   fChain->SetBranchAddress("reco_track_chi2mu_3pl", reco_track_chi2mu_3pl, &b_reco_track_chi2mu_3pl);
   fChain->SetBranchAddress("reco_track_likepr_3pl", reco_track_likepr_3pl, &b_reco_track_likepr_3pl);
   fChain->SetBranchAddress("reco_track_llrpid_3pl", reco_track_llrpid_3pl, &b_reco_track_llrpid_3pl);
   fChain->SetBranchAddress("reco_track_llrpid_k_3pl", reco_track_llrpid_k_3pl, &b_reco_track_llrpid_k_3pl);
   fChain->SetBranchAddress("reco_track_Bragg_fwd_ka_pl0", reco_track_Bragg_fwd_ka_pl0, &b_reco_track_Bragg_fwd_ka_pl0);
   fChain->SetBranchAddress("reco_track_Bragg_fwd_pr_pl0", reco_track_Bragg_fwd_pr_pl0, &b_reco_track_Bragg_fwd_pr_pl0);
   fChain->SetBranchAddress("reco_track_Bragg_fwd_pi_pl0", reco_track_Bragg_fwd_pi_pl0, &b_reco_track_Bragg_fwd_pi_pl0);
   fChain->SetBranchAddress("reco_track_Bragg_fwd_mu_pl0", reco_track_Bragg_fwd_mu_pl0, &b_reco_track_Bragg_fwd_mu_pl0);
   fChain->SetBranchAddress("reco_track_Bragg_fwd_ka_pl1", reco_track_Bragg_fwd_ka_pl1, &b_reco_track_Bragg_fwd_ka_pl1);
   fChain->SetBranchAddress("reco_track_Bragg_fwd_pr_pl1", reco_track_Bragg_fwd_pr_pl1, &b_reco_track_Bragg_fwd_pr_pl1);
   fChain->SetBranchAddress("reco_track_Bragg_fwd_pi_pl1", reco_track_Bragg_fwd_pi_pl1, &b_reco_track_Bragg_fwd_pi_pl1);
   fChain->SetBranchAddress("reco_track_Bragg_fwd_mu_pl1", reco_track_Bragg_fwd_mu_pl1, &b_reco_track_Bragg_fwd_mu_pl1);
   fChain->SetBranchAddress("reco_track_Bragg_fwd_ka_pl2", reco_track_Bragg_fwd_ka_pl2, &b_reco_track_Bragg_fwd_ka_pl2);
   fChain->SetBranchAddress("reco_track_Bragg_fwd_pr_pl2", reco_track_Bragg_fwd_pr_pl2, &b_reco_track_Bragg_fwd_pr_pl2);
   fChain->SetBranchAddress("reco_track_Bragg_fwd_pi_pl2", reco_track_Bragg_fwd_pi_pl2, &b_reco_track_Bragg_fwd_pi_pl2);
   fChain->SetBranchAddress("reco_track_Bragg_fwd_mu_pl2", reco_track_Bragg_fwd_mu_pl2, &b_reco_track_Bragg_fwd_mu_pl2);
   fChain->SetBranchAddress("reco_track_MIP_pl0", reco_track_MIP_pl0, &b_reco_track_MIP_pl0);
   fChain->SetBranchAddress("reco_track_MIP_pl1", reco_track_MIP_pl1, &b_reco_track_MIP_pl1);
   fChain->SetBranchAddress("reco_track_MIP_pl2", reco_track_MIP_pl2, &b_reco_track_MIP_pl2);
   //fChain->SetBranchAddress("reco_track_vtx_distance", reco_track_vtx_distance, &b_reco_track_vtx_distance);
   fChain->SetBranchAddress("reco_track_daughter_MIP_pl0", reco_track_daughter_MIP_pl0, &b_reco_track_daughter_MIP_pl0);
   fChain->SetBranchAddress("reco_track_daughter_MIP_pl1", reco_track_daughter_MIP_pl1, &b_reco_track_daughter_MIP_pl1);
   fChain->SetBranchAddress("reco_track_daughter_MIP_pl2", reco_track_daughter_MIP_pl2, &b_reco_track_daughter_MIP_pl2);
   fChain->SetBranchAddress("reco_track_vtx_inTPC", reco_track_vtx_inTPC, &b_reco_track_vtx_inTPC);
   fChain->SetBranchAddress("reco_track_vtx_in5cmTPC", reco_track_vtx_in5cmTPC, &b_reco_track_vtx_in5cmTPC);
   fChain->SetBranchAddress("reco_track_vtx_inCCInclusiveTPC", reco_track_vtx_inCCInclusiveTPC, &b_reco_track_vtx_inCCInclusiveTPC);
   fChain->SetBranchAddress("reco_track_end_inTPC", reco_track_end_inTPC, &b_reco_track_end_inTPC);
   fChain->SetBranchAddress("reco_track_end_in5cmTPC", reco_track_end_in5cmTPC, &b_reco_track_end_in5cmTPC);
   fChain->SetBranchAddress("reco_track_end_inCCInclusiveTPC", reco_track_end_inCCInclusiveTPC, &b_reco_track_end_inCCInclusiveTPC);
   fChain->SetBranchAddress("reco_track_true_pdg", reco_track_true_pdg, &b_reco_track_true_pdg);
   fChain->SetBranchAddress("reco_track_true_origin", reco_track_true_origin, &b_reco_track_true_origin);
   fChain->SetBranchAddress("reco_track_true_primary", reco_track_true_primary, &b_reco_track_true_primary);
   fChain->SetBranchAddress("reco_track_true_end_inTPC", reco_track_true_end_inTPC, &b_reco_track_true_end_inTPC);
   fChain->SetBranchAddress("reco_track_true_end_in5cmTPC", reco_track_true_end_in5cmTPC, &b_reco_track_true_end_in5cmTPC);
   fChain->SetBranchAddress("reco_track_true_end_inCCInclusiveTPC", reco_track_true_end_inCCInclusiveTPC, &b_reco_track_true_end_inCCInclusiveTPC);
   fChain->SetBranchAddress("reco_track_true_length", reco_track_true_length, &b_reco_track_true_length);
   fChain->SetBranchAddress("reco_track_ndaughters", reco_track_ndaughters, &b_reco_track_ndaughters);
   fChain->SetBranchAddress("reco_track_daughter_distance", reco_track_daughter_distance, &b_reco_track_daughter_distance);
   fChain->SetBranchAddress("reco_track_daughter_vtx_distance", reco_track_daughter_vtx_distance, &b_reco_track_daughter_vtx_distance);
   fChain->SetBranchAddress("reco_track_daughter_nhits0", reco_track_daughter_nhits0, &b_reco_track_daughter_nhits0);
   fChain->SetBranchAddress("reco_track_daughter_nhits1", reco_track_daughter_nhits1, &b_reco_track_daughter_nhits1);
   fChain->SetBranchAddress("reco_track_daughter_nhits2", reco_track_daughter_nhits2, &b_reco_track_daughter_nhits2);
   fChain->SetBranchAddress("reco_track_daughter_length", reco_track_daughter_length, &b_reco_track_daughter_length);
   fChain->SetBranchAddress("reco_track_daughter_theta", reco_track_daughter_theta, &b_reco_track_daughter_theta);
   fChain->SetBranchAddress("reco_track_daughter_phi", reco_track_daughter_phi, &b_reco_track_daughter_phi);
   fChain->SetBranchAddress("reco_track_daughter_chi2ka_pl0", reco_track_daughter_chi2ka_pl0, &b_reco_track_daughter_chi2ka_pl0);
   fChain->SetBranchAddress("reco_track_daughter_chi2pr_pl0", reco_track_daughter_chi2pr_pl0, &b_reco_track_daughter_chi2pr_pl0);
   fChain->SetBranchAddress("reco_track_daughter_chi2pi_pl0", reco_track_daughter_chi2pi_pl0, &b_reco_track_daughter_chi2pi_pl0);
   fChain->SetBranchAddress("reco_track_daughter_chi2mu_pl0", reco_track_daughter_chi2mu_pl0, &b_reco_track_daughter_chi2mu_pl0);
   fChain->SetBranchAddress("reco_track_daughter_chi2ka_pl1", reco_track_daughter_chi2ka_pl1, &b_reco_track_daughter_chi2ka_pl1);
   fChain->SetBranchAddress("reco_track_daughter_chi2pr_pl1", reco_track_daughter_chi2pr_pl1, &b_reco_track_daughter_chi2pr_pl1);
   fChain->SetBranchAddress("reco_track_daughter_chi2pi_pl1", reco_track_daughter_chi2pi_pl1, &b_reco_track_daughter_chi2pi_pl1);
   fChain->SetBranchAddress("reco_track_daughter_chi2mu_pl1", reco_track_daughter_chi2mu_pl1, &b_reco_track_daughter_chi2mu_pl1);
   fChain->SetBranchAddress("reco_track_daughter_chi2ka_pl2", reco_track_daughter_chi2ka_pl2, &b_reco_track_daughter_chi2ka_pl2);
   fChain->SetBranchAddress("reco_track_daughter_chi2pr_pl2", reco_track_daughter_chi2pr_pl2, &b_reco_track_daughter_chi2pr_pl2);
   fChain->SetBranchAddress("reco_track_daughter_chi2pi_pl2", reco_track_daughter_chi2pi_pl2, &b_reco_track_daughter_chi2pi_pl2);
   fChain->SetBranchAddress("reco_track_daughter_chi2mu_pl2", reco_track_daughter_chi2mu_pl2, &b_reco_track_daughter_chi2mu_pl2);
   fChain->SetBranchAddress("reco_track_daughter_chi2ka_3pl", reco_track_daughter_chi2ka_3pl, &b_reco_track_daughter_chi2ka_3pl);
   fChain->SetBranchAddress("reco_track_daughter_chi2pr_3pl", reco_track_daughter_chi2pr_3pl, &b_reco_track_daughter_chi2pr_3pl);
   fChain->SetBranchAddress("reco_track_daughter_chi2pi_3pl", reco_track_daughter_chi2pi_3pl, &b_reco_track_daughter_chi2pi_3pl);
   fChain->SetBranchAddress("reco_track_daughter_chi2mu_3pl", reco_track_daughter_chi2mu_3pl, &b_reco_track_daughter_chi2mu_3pl);
   fChain->SetBranchAddress("reco_track_daughter_likepr_3pl", reco_track_daughter_likepr_3pl, &b_reco_track_daughter_likepr_3pl);
   fChain->SetBranchAddress("reco_track_daughter_llrpid_3pl", reco_track_daughter_llrpid_3pl, &b_reco_track_daughter_llrpid_3pl);
   fChain->SetBranchAddress("reco_track_daughter_llrpid_k_3pl", reco_track_daughter_llrpid_k_3pl, &b_reco_track_daughter_llrpid_k_3pl);
   fChain->SetBranchAddress("reco_angle_track_daughter", reco_angle_track_daughter, &b_reco_angle_track_daughter);
   fChain->SetBranchAddress("reco_track_daughter_vtx_inTPC", reco_track_daughter_vtx_inTPC, &b_reco_track_daughter_vtx_inTPC);
   fChain->SetBranchAddress("reco_track_daughter_vtx_in5cmTPC", reco_track_daughter_vtx_in5cmTPC, &b_reco_track_daughter_vtx_in5cmTPC);
   fChain->SetBranchAddress("reco_track_daughter_vtx_inCCInclusiveTPC", reco_track_daughter_vtx_inCCInclusiveTPC, &b_reco_track_daughter_vtx_inCCInclusiveTPC);
   fChain->SetBranchAddress("reco_track_daughter_end_inTPC", reco_track_daughter_end_inTPC, &b_reco_track_daughter_end_inTPC);
   fChain->SetBranchAddress("reco_track_daughter_end_in5cmTPC", reco_track_daughter_end_in5cmTPC, &b_reco_track_daughter_end_in5cmTPC);
   fChain->SetBranchAddress("reco_track_daughter_end_inCCInclusiveTPC", reco_track_daughter_end_inCCInclusiveTPC, &b_reco_track_daughter_end_inCCInclusiveTPC);
   fChain->SetBranchAddress("reco_track_daughter_true_pdg", reco_track_daughter_true_pdg, &b_reco_track_daughter_true_pdg);
   fChain->SetBranchAddress("reco_track_daughter_true_origin", reco_track_daughter_true_origin, &b_reco_track_daughter_true_origin);
   fChain->SetBranchAddress("reco_track_daughter_true_primary", reco_track_daughter_true_primary, &b_reco_track_daughter_true_primary);
   fChain->SetBranchAddress("reco_track_daughter_true_end_inTPC", reco_track_daughter_true_end_inTPC, &b_reco_track_daughter_true_end_inTPC);
   fChain->SetBranchAddress("reco_track_daughter_true_end_in5cmTPC", reco_track_daughter_true_end_in5cmTPC, &b_reco_track_daughter_true_end_in5cmTPC);
   fChain->SetBranchAddress("reco_track_daughter_true_end_inCCInclusiveTPC", reco_track_daughter_true_end_inCCInclusiveTPC, &b_reco_track_daughter_true_end_inCCInclusiveTPC);
   fChain->SetBranchAddress("reco_track_daughter_true_length", reco_track_daughter_true_length, &b_reco_track_daughter_true_length);
   fChain->SetBranchAddress("reco_track_daughter_true_mother", reco_track_daughter_true_mother, &b_reco_track_daughter_true_mother);
   fChain->SetBranchAddress("k_can_trkid", &k_can_trkid, &b_k_can_trkid);
   fChain->SetBranchAddress("mu_can_trkid", &mu_can_trkid, &b_mu_can_trkid);
   fChain->SetBranchAddress("k_mu_can_dis", &k_mu_can_dis, &b_k_mu_can_dis);
   fChain->SetBranchAddress("k_mu_open_angle", &k_mu_open_angle, &b_k_mu_open_angle);
   fChain->SetBranchAddress("k_vtx_dis", &k_vtx_dis, &b_k_vtx_dis);
   fChain->SetBranchAddress("cut_1", &cut_1, &b_cut_1);
   fChain->SetBranchAddress("cut_2", &cut_2, &b_cut_2);
   fChain->SetBranchAddress("cut_3", &cut_3, &b_cut_3);
   fChain->SetBranchAddress("cut_4", &cut_4, &b_cut_4);
   fChain->SetBranchAddress("cut_5", &cut_5, &b_cut_5);
   fChain->SetBranchAddress("cut_6", &cut_6, &b_cut_6);
   fChain->SetBranchAddress("cut_7", &cut_7, &b_cut_7);
   fChain->SetBranchAddress("cut_8", &cut_8, &b_cut_8);
   fChain->SetBranchAddress("cut_9", &cut_9, &b_cut_9);
   fChain->SetBranchAddress("cut_10", &cut_10, &b_cut_10);
   fChain->SetBranchAddress("cut_11", &cut_11, &b_cut_11);
   fChain->SetBranchAddress("cut_12", &cut_12, &b_cut_12);
   fChain->SetBranchAddress("cut_13", &cut_13, &b_cut_13);

   fChain->SetBranchAddress("reco_track_kin0", &reco_track_kin0, &b_reco_track_kin0);
   fChain->SetBranchAddress("reco_track_kin1", &reco_track_kin1, &b_reco_track_kin1);
   fChain->SetBranchAddress("reco_track_kin2", &reco_track_kin2, &b_reco_track_kin2);

   fChain->SetBranchAddress("reco_track_P_vtx", &reco_track_P_vtx, &b_reco_track_P_vtx);
   fChain->SetBranchAddress("reco_track_P_str", &reco_track_P_str, &b_reco_track_P_str);
   fChain->SetBranchAddress("reco_track_P_end", &reco_track_P_end, &b_reco_track_P_end);

   fChain->SetBranchAddress("reco_track_ndaughters_old", reco_track_ndaughters_old, &b_reco_track_ndaughters_old);
   fChain->SetBranchAddress("reco_track_daughter_old_distance", reco_track_daughter_old_distance, &b_reco_track_daughter_old_distance);
   fChain->SetBranchAddress("reco_track_daughter_old_length", reco_track_daughter_old_length, &b_reco_track_daughter_old_length);
   fChain->SetBranchAddress("reco_track_daughter_old_theta", reco_track_daughter_old_theta, &b_reco_track_daughter_old_theta);
   fChain->SetBranchAddress("reco_track_daughter_old_phi", reco_track_daughter_old_phi, &b_reco_track_daughter_old_phi);
   fChain->SetBranchAddress("reco_track_daughter_old_chi2ka_pl0", reco_track_daughter_old_chi2ka_pl0, &b_reco_track_daughter_old_chi2ka_pl0);
   fChain->SetBranchAddress("reco_track_daughter_old_chi2pr_pl0", reco_track_daughter_old_chi2pr_pl0, &b_reco_track_daughter_old_chi2pr_pl0);
   fChain->SetBranchAddress("reco_track_daughter_old_chi2pi_pl0", reco_track_daughter_old_chi2pi_pl0, &b_reco_track_daughter_old_chi2pi_pl0);
   fChain->SetBranchAddress("reco_track_daughter_old_chi2mu_pl0", reco_track_daughter_old_chi2mu_pl0, &b_reco_track_daughter_old_chi2mu_pl0);
   fChain->SetBranchAddress("reco_track_daughter_old_chi2ka_pl1", reco_track_daughter_old_chi2ka_pl1, &b_reco_track_daughter_old_chi2ka_pl1);
   fChain->SetBranchAddress("reco_track_daughter_old_chi2pr_pl1", reco_track_daughter_old_chi2pr_pl1, &b_reco_track_daughter_old_chi2pr_pl1);
   fChain->SetBranchAddress("reco_track_daughter_old_chi2pi_pl1", reco_track_daughter_old_chi2pi_pl1, &b_reco_track_daughter_old_chi2pi_pl1);
   fChain->SetBranchAddress("reco_track_daughter_old_chi2mu_pl1", reco_track_daughter_old_chi2mu_pl1, &b_reco_track_daughter_old_chi2mu_pl1);
   fChain->SetBranchAddress("reco_track_daughter_old_chi2ka_pl2", reco_track_daughter_old_chi2ka_pl2, &b_reco_track_daughter_old_chi2ka_pl2);
   fChain->SetBranchAddress("reco_track_daughter_old_chi2pr_pl2", reco_track_daughter_old_chi2pr_pl2, &b_reco_track_daughter_old_chi2pr_pl2);
   fChain->SetBranchAddress("reco_track_daughter_old_chi2pi_pl2", reco_track_daughter_old_chi2pi_pl2, &b_reco_track_daughter_old_chi2pi_pl2);
   fChain->SetBranchAddress("reco_track_daughter_old_chi2mu_pl2", reco_track_daughter_old_chi2mu_pl2, &b_reco_track_daughter_old_chi2mu_pl2);
   fChain->SetBranchAddress("reco_track_daughter_old_chi2ka_3pl", reco_track_daughter_old_chi2ka_3pl, &b_reco_track_daughter_old_chi2ka_3pl);
   fChain->SetBranchAddress("reco_track_daughter_old_chi2pr_3pl", reco_track_daughter_old_chi2pr_3pl, &b_reco_track_daughter_old_chi2pr_3pl);
   fChain->SetBranchAddress("reco_track_daughter_old_chi2pi_3pl", reco_track_daughter_old_chi2pi_3pl, &b_reco_track_daughter_old_chi2pi_3pl);
   fChain->SetBranchAddress("reco_track_daughter_old_chi2mu_3pl", reco_track_daughter_old_chi2mu_3pl, &b_reco_track_daughter_old_chi2mu_3pl);
   fChain->SetBranchAddress("reco_track_daughter_old_likepr_3pl", reco_track_daughter_old_likepr_3pl, &b_reco_track_daughter_old_likepr_3pl);
   fChain->SetBranchAddress("reco_track_daughter_old_llrpid_3pl", reco_track_daughter_old_llrpid_3pl, &b_reco_track_daughter_old_llrpid_3pl);
   fChain->SetBranchAddress("reco_track_daughter_old_llrpid_k_3pl", reco_track_daughter_old_llrpid_k_3pl, &b_reco_track_daughter_old_llrpid_k_3pl);
   fChain->SetBranchAddress("reco_track_daughter_old_vtx_inTPC", reco_track_daughter_old_vtx_inTPC, &b_reco_track_daughter_old_vtx_inTPC);
   fChain->SetBranchAddress("reco_track_daughter_old_vtx_in5cmTPC", reco_track_daughter_old_vtx_in5cmTPC, &b_reco_track_daughter_old_vtx_in5cmTPC);
   fChain->SetBranchAddress("reco_track_daughter_old_vtx_inCCInclusiveTPC", reco_track_daughter_old_vtx_inCCInclusiveTPC, &b_reco_track_daughter_old_vtx_inCCInclusiveTPC);
   fChain->SetBranchAddress("reco_track_daughter_old_end_inTPC", reco_track_daughter_old_end_inTPC, &b_reco_track_daughter_old_end_inTPC);
   fChain->SetBranchAddress("reco_track_daughter_old_end_in5cmTPC", reco_track_daughter_old_end_in5cmTPC, &b_reco_track_daughter_old_end_in5cmTPC);
   fChain->SetBranchAddress("reco_track_daughter_old_end_inCCInclusiveTPC", reco_track_daughter_old_end_inCCInclusiveTPC, &b_reco_track_daughter_old_end_inCCInclusiveTPC);

   fChain->SetBranchAddress("reco_track_daughter_old_true_pdg", reco_track_daughter_old_true_pdg, &b_reco_track_daughter_old_true_pdg);



   Notify();
}

Bool_t Event::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void Event::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t Event::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef Event_cxx

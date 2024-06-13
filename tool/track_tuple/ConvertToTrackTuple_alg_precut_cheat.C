#define Event_cxx
#define plotcck_cxx
//#include "plotcck.h"
#include "Event.h"

#include "TH1.h"
#include "TStopwatch.h"

#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

void Event::Loop() {};
//void plotcck::Loop(){};
void ConvertToTrackTuple_alg_precut_cheat(TString input_name, TString output_name);
//void precuts(TString s);
//vector <int> evt;


void ConvertToTrackTuple_alg_precut_cheat()
{

  TStopwatch clock;

  ConvertToTrackTuple_alg_precut_cheat("/exp/uboone/data/users/taniuchi/taniuchi/pandora_alg/ana/assok_refined_KrecoAlg_parameter8_debug.root", "/exp/uboone/data/users/taniuchi/taniuchi/pandora_alg/ana/assok_tracktuple_debug_test.root");
  //ConvertToTrackTuple_alg_precut_cheat("/exp/uboone/data/users/taniuchi/taniuchi/pandora_alg/ana/singlek_refined_KrecoAlg_parameter8.root", "/exp/uboone/data/users/taniuchi/taniuchi/pandora_alg/ana/singlek_tracktuple.root");
  //ConvertToTrackTuple_alg_precut_cheat("/exp/uboone/data/users/taniuchi/taniuchi/pandora_alg/ana/numi_sample0_refined_KrecoAlg_parameter8.root", "/exp/uboone/data/users/taniuchi/taniuchi/pandora_alg/ana/numi_sample0_tracktuple.root");
  //ConvertToTrackTuple_alg_precut_cheat("/exp/uboone/data/users/taniuchi/taniuchi/pandora_alg/ana/numi_sample1_refined_KrecoAlg_parameter8.root", "/exp/uboone/data/users/taniuchi/taniuchi/pandora_alg/ana/numi_sample1_tracktuple.root");
  //ConvertToTrackTuple_alg_precut_cheat("/exp/uboone/data/users/taniuchi/taniuchi/pandora_alg/ana/numi_sample2_refined_KrecoAlg_parameter8.root", "/exp/uboone/data/users/taniuchi/taniuchi/pandora_alg/ana/numi_sample2_tracktuple.root");

  //ConvertToTrackTuple_alg_precut_cheat("/exp/uboone/data/users/taniuchi/taniuchi/pandora_alg/ana/assok_refined_KrecoAlg_parameter8.root", "/exp/uboone/data/users/taniuchi/taniuchi/pandora_alg/ana/assok_tracktuple.root");
  //ConvertToTrackTuple_alg_precut_cheat("/exp/uboone/data/users/taniuchi/recoalg_testarea/assok_refined_KrecoAlg_debug_test3.root", "rootfile/test.root");
  //ConvertToTrackTuple_alg_precut_cheat("/exp/uboone/data/users/taniuchi/recoalg_testarea/assok_refined_KrecoAlg_debug_test5_debug.root", "rootfile/assok_refined_KrecoAlg_track_debug5_debugtest.root");
  //ConvertToTrackTuple_alg_precut_cheat("/exp/uboone/data/users/taniuchi/recoalg_testarea/CCKaonAnalyzer_debug.root", "rootfile/assok_refined_KrecoAlg_track.root");


  cout << "Real time " << clock.RealTime() << " s" << endl << endl;

}


void ConvertToTrackTuple_alg_precut_cheat(TString input_name, TString output_name)
{

  // Input files
  //TChain * t = new TChain("CCKaonAnalyzer/Event");
  TChain * t = new TChain("CCKaonAnalyzerRebuild/Event");

  cout << "Input " << input_name << endl;

  //if root file                                                                                                                                                                                                                                 
  if (input_name.Contains(".root")) {
    t->Add(input_name);
  }
  //if list file                                                                                                                                                                                                                                 
  else if (input_name.Contains(".list")) {
    ifstream file_list(input_name.Data());
    while (file_list.good()) {
      string line;
      getline(file_list,line);
      if (!file_list.eof()) t->Add(line.c_str());
    }
  }
  else {
    cout << "unknown input" << endl;
    return;
  }

  // Output file
  TFile * outfile = new TFile(output_name, "recreate");
  TTree * outtree = new TTree("CCKaonTracks","CCKaonTracks");

  Int_t   true_kaon_ndaughters = -1;
  Int_t   true_kaon_end_process = -1;

  Int_t   reco_track_nhits0 = 0;
  Int_t   reco_track_nhits1 = 0;
  Int_t   reco_track_nhits2 = 0;
  
  Float_t reco_track_distance = -9999;
  //Float_t reco_track_vtx_distance = -9999;
  Float_t reco_track_length = -9999;
  Float_t reco_track_theta = -9999;
  Float_t reco_track_phi = -9999;

  Float_t reco_track_chi2ka_pl0 = -9999;
  Float_t reco_track_chi2pr_pl0 = -9999;
  Float_t reco_track_chi2pi_pl0 = -9999;
  Float_t reco_track_chi2mu_pl0 = -9999;
  
  Float_t reco_track_chi2ka_pl1 = -9999;
  Float_t reco_track_chi2pr_pl1 = -9999;
  Float_t reco_track_chi2pi_pl1 = -9999;
  Float_t reco_track_chi2mu_pl1 = -9999;
  
  Float_t reco_track_chi2ka_pl2 = -9999;
  Float_t reco_track_chi2pr_pl2 = -9999;
  Float_t reco_track_chi2pi_pl2 = -9999;
  Float_t reco_track_chi2mu_pl2 = -9999;  
     
  Float_t reco_track_chi2ka_3pl = -9999;
  Float_t reco_track_chi2pr_3pl = -9999;
  Float_t reco_track_chi2pi_3pl = -9999;
  Float_t reco_track_chi2mu_3pl = -9999;
  
  Float_t reco_track_llrpid_3pl = -9999;  
  Float_t reco_track_llrpid_k_3pl = -9999;  
  Int_t   reco_track_true_pdg = -9999;
  
  Bool_t  reco_track_vtx_inTPC = 0;
  Bool_t  reco_track_vtx_in5cmTPC = 0;
  Bool_t  reco_track_vtx_inCCInclusiveTPC = 0;
  Bool_t  reco_track_end_inTPC = 0;
  Bool_t  reco_track_end_in5cmTPC = 0;
  Bool_t  reco_track_end_inCCInclusiveTPC = 0;
  
  Bool_t  reco_track_true_end_inTPC = 0;
  Bool_t  reco_track_true_end_in5cmTPC = 0;
  Bool_t  reco_track_true_end_inCCInclusiveTPC = 0;
  
  
  Float_t reco_track_ndaughters_old = 0;  
  Float_t reco_track_daughter_old_distance = -9999;
  Float_t reco_track_daughter_old_true_pdg = -9999;
  Float_t reco_track_daughter_old_length = -9999;
  Float_t reco_track_daughter_old_theta = -9999;
  Float_t reco_track_daughter_old_phi = -9999;
  Float_t reco_track_daughter_old_chi2ka_pl0 = -9999;
  Float_t reco_track_daughter_old_chi2pr_pl0 = -9999;
  Float_t reco_track_daughter_old_chi2pi_pl0 = -9999;
  Float_t reco_track_daughter_old_chi2mu_pl0 = -9999;
  
  Float_t reco_track_daughter_old_chi2ka_pl1 = -9999;
  Float_t reco_track_daughter_old_chi2pr_pl1 = -9999;
  Float_t reco_track_daughter_old_chi2pi_pl1 = -9999;
  Float_t reco_track_daughter_old_chi2mu_pl1 = -9999;
  
  Float_t reco_track_daughter_old_chi2ka_pl2 = -9999;
  Float_t reco_track_daughter_old_chi2pr_pl2 = -9999;
  Float_t reco_track_daughter_old_chi2pi_pl2 = -9999;
  Float_t reco_track_daughter_old_chi2mu_pl2 = -9999;
  
  Float_t reco_track_daughter_old_chi2ka_3pl = -9999;
  Float_t reco_track_daughter_old_chi2pr_3pl = -9999;
  Float_t reco_track_daughter_old_chi2pi_3pl = -9999;
  Float_t reco_track_daughter_old_chi2mu_3pl = -9999;  
  Float_t reco_track_daughter_old_llrpid_3pl = -9999;
  Float_t reco_track_daughter_old_llrpid_k_3pl = -9999;
  
  Bool_t  reco_track_daughter_old_vtx_inTPC = 0;
  Bool_t  reco_track_daughter_old_vtx_in5cmTPC = 0;
  Bool_t  reco_track_daughter_old_vtx_inCCInclusiveTPC = 0;
  Bool_t  reco_track_daughter_old_end_inTPC = 0;
  Bool_t  reco_track_daughter_old_end_in5cmTPC = 0;
  Bool_t  reco_track_daughter_old_end_inCCInclusiveTPC = 0;


  Float_t reco_track_ndaughters = 0;  
  Float_t reco_track_daughter_length = -9999;
  Float_t reco_track_daughter_distance = -9999;
  Float_t reco_track_daughter_vtx_distance = -9999;
  Float_t reco_track_daughter_theta = -9999;
  Float_t reco_track_daughter_phi = -9999;
  
  Float_t reco_track_daughter_chi2ka_pl0 = -9999;
  Float_t reco_track_daughter_chi2pr_pl0 = -9999;
  Float_t reco_track_daughter_chi2pi_pl0 = -9999;
  Float_t reco_track_daughter_chi2mu_pl0 = -9999;
  
  Float_t reco_track_daughter_chi2ka_pl1 = -9999;
  Float_t reco_track_daughter_chi2pr_pl1 = -9999;
  Float_t reco_track_daughter_chi2pi_pl1 = -9999;
  Float_t reco_track_daughter_chi2mu_pl1 = -9999;
  
  Float_t reco_track_daughter_chi2ka_pl2 = -9999;
  Float_t reco_track_daughter_chi2pr_pl2 = -9999;
  Float_t reco_track_daughter_chi2pi_pl2 = -9999;
  Float_t reco_track_daughter_chi2mu_pl2 = -9999;
  
  Float_t reco_track_daughter_chi2ka_3pl = -9999;
  Float_t reco_track_daughter_chi2pr_3pl = -9999;
  Float_t reco_track_daughter_chi2pi_3pl = -9999;
  Float_t reco_track_daughter_chi2mu_3pl = -9999;
  
  Float_t reco_track_daughter_llrpid_3pl = -9999;
  Float_t reco_track_daughter_llrpid_k_3pl = -9999;
  Float_t reco_track_daughter_true_pdg = -9999;
  
  Bool_t  reco_track_daughter_vtx_inTPC = 0;
  Bool_t  reco_track_daughter_vtx_in5cmTPC = 0;
  Bool_t  reco_track_daughter_vtx_inCCInclusiveTPC = 0;
  Bool_t  reco_track_daughter_end_inTPC = 0;
  Bool_t  reco_track_daughter_end_in5cmTPC = 0;
  Bool_t  reco_track_daughter_end_inCCInclusiveTPC = 0;
  
  Bool_t  reco_track_daughter_true_end_inTPC = 0;
  Bool_t  reco_track_daughter_true_end_in5cmTPC = 0;
  Bool_t  reco_track_daughter_true_end_inCCInclusiveTPC = 0;
  //Bool+y

  Float_t reco_track_Bragg_fwd_ka_pl0 = -9999;
  Float_t reco_track_Bragg_fwd_pr_pl0 = -9999;
  Float_t reco_track_Bragg_fwd_pi_pl0 = -9999;
  Float_t reco_track_Bragg_fwd_mu_pl0 = -9999;
  Float_t reco_track_Bragg_fwd_ka_pl1 = -9999;
  Float_t reco_track_Bragg_fwd_pr_pl1 = -9999;
  Float_t reco_track_Bragg_fwd_pi_pl1 = -9999;
  Float_t reco_track_Bragg_fwd_mu_pl1 = -9999;
  Float_t reco_track_Bragg_fwd_ka_pl2 = -9999;
  Float_t reco_track_Bragg_fwd_pr_pl2 = -9999;
  Float_t reco_track_Bragg_fwd_pi_pl2 = -9999;
  Float_t reco_track_Bragg_fwd_mu_pl2 = -9999;
  Float_t reco_track_MIP_pl0 = -9999;
  Float_t reco_track_MIP_pl1 = -9999;
  Float_t reco_track_MIP_pl2 = -9999;
   
  Float_t reco_track_braggLLH = -9999;
   
  Float_t reco_angle_track_daughter = -9999;
  Float_t reco_track_log_bragg_peak = -9999;
  
  Float_t reco_nu_ndaughters = -9999;
  
  Float_t reco_track_delta_dEdx_pl0 = -9999;
  Float_t reco_track_delta_dEdx_pl1 = -9999;
  Float_t reco_track_delta_dEdx_pl2 = -9999;


  Float_t         true_nu_energy = -9999;
  Float_t         true_kaon_p = -9999;
  Float_t         true_kaon_ke = -9999;
  Float_t         true_kaon_theta = -9999;
  Float_t         true_kaon_costheta = -9999;
  Float_t         true_kaon_phi = -9999;
  Float_t         true_kaon_length = -9999;
  Float_t         true_kaon_daughter_length = -9999;

  Float_t true_dau_pip_length = -9999;
  Float_t true_dau_muon_length = -9999;

  Int_t         true_nu_ccnc = -9999;
  Int_t         true_nu_pdg = -9999;
  Int_t         true_nu_mode = -9999;
  Int_t         true_lepton_pdg = -9999;
  Int_t         true_nkaons = -9999;
  Int_t         true_nhyperons = -9999;
  //Int_t         true_kaon_ndaughters = -9999;
  Int_t         true_kaon_ndaughters_inelastic = -9999;
  Int_t         reco_ccmu_true_pdg = -9999;
  Int_t         eventnum = -9999;
  Int_t         run = -9999;
  Int_t         subrun = -9999;

  Int_t true_kaon_daughter_end_in5cmTPC = -9999;
  Int_t true_kaon_end_inCCInclusiveTPC = -9999;
  Int_t true_nu_vtx_inCCInclusiveTPC = -9999;

  Float_t reco_track_kin0 = -9999;
  Float_t reco_track_kin1 = -9999;
  Float_t reco_track_kin2 = -9999;

  Float_t reco_track_P_vtx = -9999;  // track.VertexMomentum
  Float_t reco_track_P_str = -9999;  // track.StartMomentum()
  Float_t reco_track_P_end = -9999;  // track.EndMomentum();

  Int_t n_true_k=0;
  //Int_t           reco_track_true_pdg = -9999;
  //Int_t           reco_track_daughter_true_pdg = -9999;

  Int_t n_recoRebDauTracks = -9999;
  Float_t rebdautrack_length = -9999; 
  Float_t rebdautracktrue_length = -9999; 
  Float_t rebdautracktruedir_length = -9999; 
  Float_t rebdautrack_pdg = -9999; 
  Float_t best_peak_x = -9999; 
  Float_t best_peak_y = -9999; 
  Float_t best_peak_z = -9999; 
  Float_t best_peak_x_true = -9999; 
  Float_t best_peak_y_true = -9999; 
  Float_t best_peak_z_true = -9999; 
  Float_t true_dau_muon_end_x = -9999; 
  Float_t true_dau_muon_end_y = -9999; 
  Float_t true_dau_muon_end_z = -9999; 
  Float_t true_dau_muon_start_x = -9999; 
  Float_t true_dau_muon_start_y = -9999;
  Float_t true_dau_muon_start_z = -9999; 
  Float_t true_dau_pip_end_x = -9999; 
  Float_t true_dau_pip_end_y = -9999; 
  Float_t true_dau_pip_end_z = -9999; 
  Float_t true_dau_pip_start_x = -9999; 
  Float_t true_dau_pip_start_y = -9999;
  Float_t true_dau_pip_start_z = -9999; 
  Float_t true_dau_muon_theta = -9999; 
  Float_t true_dau_muon_phi = -9999; 
  Float_t true_dau_pip_theta = -9999;
  Float_t true_dau_pip_phi = -9999; 
  Float_t reco_track_end_x = -9999;
  Float_t reco_track_end_y = -9999;
  Float_t reco_track_end_z = -9999;
  Float_t true_kaon_end_x = -9999;
  Float_t true_kaon_end_y = -9999;
  Float_t true_kaon_end_z = -9999;

outtree->Branch("n_recoRebDauTracks",&n_recoRebDauTracks,"n_recoRebDauTracks/I");
 outtree->Branch("rebdautrack_length",&rebdautrack_length,"rebdautrack_length/F");
 outtree->Branch("rebdautracktrue_length",&rebdautracktrue_length,"rebdautracktrue_length/F");
 outtree->Branch("rebdautracktruedir_length",&rebdautracktruedir_length,"rebdautracktruedir_length/F");
 outtree->Branch("best_peak_x",&best_peak_x,"best_peak_x/F");
 outtree->Branch("best_peak_y",&best_peak_y,"best_peak_y/F");
 outtree->Branch("best_peak_z",&best_peak_z,"best_peak_z/F");
 outtree->Branch("best_peak_x_true",&best_peak_x_true,"best_peak_x_true/F");
 outtree->Branch("best_peak_y_true",&best_peak_y_true,"best_peak_y_true/F");
 outtree->Branch("best_peak_z_true",&best_peak_z_true,"best_peak_z_true/F");
 outtree->Branch("true_dau_muon_end_x",&true_dau_muon_end_x,"true_dau_muon_end_x/F");
 outtree->Branch("true_dau_muon_end_y",&true_dau_muon_end_y,"true_dau_muon_end_y/F");
 outtree->Branch("true_dau_muon_end_z",&true_dau_muon_end_z,"true_dau_muon_end_z/F");
 outtree->Branch("true_dau_muon_start_x",&true_dau_muon_start_x,"true_dau_muon_start_x/F");
 outtree->Branch("true_dau_muon_start_y",&true_dau_muon_start_y,"true_dau_muon_start_y/F");
 outtree->Branch("true_dau_muon_start_z",&true_dau_muon_start_z,"true_dau_muon_start_z/F");
 outtree->Branch("true_dau_pip_end_x",&true_dau_pip_end_x,"true_dau_pip_end_x/F");
 outtree->Branch("true_dau_pip_end_y",&true_dau_pip_end_y,"true_dau_pip_end_y/F");
 outtree->Branch("true_dau_pip_end_z",&true_dau_pip_end_z,"true_dau_pip_end_z/F");
 outtree->Branch("true_dau_pip_start_x",&true_dau_pip_start_x,"true_dau_pip_start_x/F");
 outtree->Branch("true_dau_pip_start_y",&true_dau_pip_start_y,"true_dau_pip_start_y/F");
 outtree->Branch("true_dau_pip_start_z",&true_dau_pip_start_z,"true_dau_pip_start_z/F");
 outtree->Branch("true_dau_muon_theta",&true_dau_muon_theta,"true_dau_muon_theta/F");
 outtree->Branch("true_dau_muon_phi",&true_dau_muon_phi,"true_dau_muon_phi/F");
 outtree->Branch("true_dau_pip_theta",&true_dau_pip_theta,"true_dau_pip_theta/F");
 outtree->Branch("true_dau_pip_phi",&true_dau_pip_phi,"true_dau_pip_phi/F");
 outtree->Branch("true_kaon_end_x",&true_kaon_end_x,"true_kaon_end_x/F");
 outtree->Branch("true_kaon_end_y",&true_kaon_end_y,"true_kaon_end_y/F");
 outtree->Branch("true_kaon_end_z",&true_kaon_end_z,"true_kaon_end_z/F");
 outtree->Branch("reco_track_end_x",&reco_track_end_x,"reco_track_end_x/F");
 outtree->Branch("reco_track_end_y",&reco_track_end_y,"reco_track_end_y/F");
 outtree->Branch("reco_track_end_z",&reco_track_end_z,"reco_track_end_z/F");
 outtree->Branch("rebdautrack_pdg",&rebdautrack_pdg,"rebdautrack_pdg/F");

  outtree->Branch("true_nu_energy",&true_nu_energy,"true_nu_energy/F");
  outtree->Branch("true_kaon_p",&true_kaon_p,"true_kaon_p/F");
  outtree->Branch("true_kaon_ke",&true_kaon_ke,"true_kaon_ke/F");
  outtree->Branch("true_kaon_theta",&true_kaon_theta,"true_kaon_theta/F");
  outtree->Branch("true_kaon_costheta",&true_kaon_costheta,"true_kaon_costheta/F");
  outtree->Branch("true_kaon_phi",&true_kaon_phi,"true_kaon_phi/F");
  outtree->Branch("true_kaon_length",&true_kaon_length,"true_kaon_length/F");
  outtree->Branch("true_kaon_daughter_length",&true_kaon_daughter_length,"true_kaon_daughter_length/F");

  outtree->Branch("true_dau_pip_length",&true_dau_pip_length,"true_dau_pip_length/F"); 
  outtree->Branch("true_dau_muon_length",&true_dau_muon_length,"true_dau_muon_length/F"); 

  outtree->Branch("eventnum", &eventnum, "eventnum/I"); 
  outtree->Branch("run", &run, "run/I"); 
  outtree->Branch("subrun", &subrun, "subrun/I"); 
  outtree->Branch("true_nu_pdg", &true_nu_pdg, "true_nu_pdg/I"); 
  outtree->Branch("true_nu_ccnc", &true_nu_ccnc, "true_nu_ccnc/I"); 
  outtree->Branch("true_nu_mode", &true_nu_mode, "true_nu_mode/I"); 
  outtree->Branch("true_lepton_pdg", &true_lepton_pdg, "true_lepton_pdg/I"); 
  outtree->Branch("true_nkaons", &true_nkaons, "true_nkaons/I"); 
  outtree->Branch("true_nhyperons", &true_nhyperons, "true_nhyperons/I"); 
  outtree->Branch("true_kaon_ndaughters_inelastic", &true_kaon_ndaughters_inelastic, "true_kaon_ndaughters_inelastic/I");
  outtree->Branch("reco_ccmu_true_pdg", &reco_ccmu_true_pdg, "reco_ccmu_true_pdg/I"); 

  //outtree->Branch("reco_track_true_pdg",&reco_track_true_pdg,"reco_track_true_pdg/I");
  //outtree->Branch("reco_track_daughter_true_pdg",&reco_track_daughter_true_pdg,"reco_track_daughter_true_pdg/I");

  outtree->Branch("true_kaon_end_inCCInclusiveTPC",&true_kaon_end_inCCInclusiveTPC,"true_kaon_end_inCCInclusiveTPC/I");
  outtree->Branch("true_nu_vtx_inCCInclusiveTPC",&true_nu_vtx_inCCInclusiveTPC,"true_nu_vtx_inCCInclusiveTPC/I");
  outtree->Branch("true_kaon_daughter_end_in5cmTPC",&true_kaon_daughter_end_in5cmTPC,"true_kaon_daughter_end_in5cmTPC/I");
  
  outtree->Branch("true_kaon_end_process",&true_kaon_end_process,"true_kaon_end_process/I");
  outtree->Branch("reco_track_nhits0",&reco_track_nhits0,"reco_track_nhits0/I");
  outtree->Branch("reco_track_nhits1",&reco_track_nhits1,"reco_track_nhits1/I");
  outtree->Branch("reco_track_nhits2",&reco_track_nhits2,"reco_track_nhits2/I");

  outtree->Branch("reco_track_distance",&reco_track_distance,"reco_track_distance/F");
  //outtree->Branch("reco_track_vtx_distance",&reco_track_vtx_distance,"reco_track_vtx_distance/F");
  outtree->Branch("reco_track_length",&reco_track_length,"reco_track_length/F");
  outtree->Branch("reco_track_theta",&reco_track_theta,"reco_track_theta/F");
  outtree->Branch("reco_track_phi",&reco_track_phi,"reco_track_phi/F");
  
  outtree->Branch("reco_track_log_bragg_peak",&reco_track_log_bragg_peak,"reco_track_log_bragg_peak/F");
  outtree->Branch("reco_track_Bragg_fwd_ka_pl0",&reco_track_Bragg_fwd_ka_pl0,"reco_track_Bragg_fwd_ka_pl0/F");  
  outtree->Branch("reco_track_Bragg_fwd_pr_pl0",&reco_track_Bragg_fwd_pr_pl0,"reco_track_Bragg_fwd_pr_pl0/F");  
  outtree->Branch("reco_track_Bragg_fwd_pi_pl0",&reco_track_Bragg_fwd_pi_pl0,"reco_track_Bragg_fwd_pi_pl0/F");  
  outtree->Branch("reco_track_Bragg_fwd_mu_pl0",&reco_track_Bragg_fwd_mu_pl0,"reco_track_Bragg_fwd_mu_pl0/F");  
  outtree->Branch("reco_track_Bragg_fwd_ka_pl1",&reco_track_Bragg_fwd_ka_pl1,"reco_track_Bragg_fwd_ka_pl1/F");  
  outtree->Branch("reco_track_Bragg_fwd_pr_pl1",&reco_track_Bragg_fwd_pr_pl1,"reco_track_Bragg_fwd_pr_pl1/F");  
  outtree->Branch("reco_track_Bragg_fwd_pi_pl1",&reco_track_Bragg_fwd_pi_pl1,"reco_track_Bragg_fwd_pi_pl1/F");  
  outtree->Branch("reco_track_Bragg_fwd_mu_pl1",&reco_track_Bragg_fwd_mu_pl1,"reco_track_Bragg_fwd_mu_pl1/F");  
  outtree->Branch("reco_track_Bragg_fwd_ka_pl2",&reco_track_Bragg_fwd_ka_pl2,"reco_track_Bragg_fwd_ka_pl2/F");  
  outtree->Branch("reco_track_Bragg_fwd_pr_pl2",&reco_track_Bragg_fwd_pr_pl2,"reco_track_Bragg_fwd_pr_pl2/F");  
  outtree->Branch("reco_track_Bragg_fwd_pi_pl2",&reco_track_Bragg_fwd_pi_pl2,"reco_track_Bragg_fwd_pi_pl2/F");  
  outtree->Branch("reco_track_Bragg_fwd_mu_pl2",&reco_track_Bragg_fwd_mu_pl2,"reco_track_Bragg_fwd_mu_pl2/F");  

  outtree->Branch("reco_track_MIP_pl0",&reco_track_MIP_pl0,"reco_track_MIP_pl0/F");
  outtree->Branch("reco_track_MIP_pl1",&reco_track_MIP_pl0,"reco_track_MIP_pl1/F");
  outtree->Branch("reco_track_MIP_pl2",&reco_track_MIP_pl0,"reco_track_MIP_pl2/F");
  
  outtree->Branch("reco_track_chi2ka_pl0",&reco_track_chi2ka_pl0,"reco_track_chi2ka_pl0/F");
  outtree->Branch("reco_track_chi2pr_pl0",&reco_track_chi2pr_pl0,"reco_track_chi2pr_pl0/F");
  outtree->Branch("reco_track_chi2pi_pl0",&reco_track_chi2pi_pl0,"reco_track_chi2pi_pl0/F");
  outtree->Branch("reco_track_chi2mu_pl0",&reco_track_chi2mu_pl0,"reco_track_chi2mu_pl0/F");
  
  outtree->Branch("reco_track_chi2ka_pl1",&reco_track_chi2ka_pl1,"reco_track_chi2ka_pl1/F");
  outtree->Branch("reco_track_chi2pr_pl1",&reco_track_chi2pr_pl1,"reco_track_chi2pr_pl1/F");
  outtree->Branch("reco_track_chi2pi_pl1",&reco_track_chi2pi_pl1,"reco_track_chi2pi_pl1/F");
  outtree->Branch("reco_track_chi2mu_pl1",&reco_track_chi2mu_pl1,"reco_track_chi2mu_pl1/F");
  
  outtree->Branch("reco_track_chi2ka_pl2",&reco_track_chi2ka_pl2,"reco_track_chi2ka_pl2/F");
  outtree->Branch("reco_track_chi2pr_pl2",&reco_track_chi2pr_pl2,"reco_track_chi2pr_pl2/F");
  outtree->Branch("reco_track_chi2pi_pl2",&reco_track_chi2pi_pl2,"reco_track_chi2pi_pl2/F");
  outtree->Branch("reco_track_chi2mu_pl2",&reco_track_chi2mu_pl2,"reco_track_chi2mu_pl2/F");
  
  
  outtree->Branch("reco_track_chi2ka_3pl",&reco_track_chi2ka_3pl,"reco_track_chi2ka_3pl/F");
  outtree->Branch("reco_track_chi2pr_3pl",&reco_track_chi2pr_3pl,"reco_track_chi2pr_3pl/F");
  outtree->Branch("reco_track_chi2pi_3pl",&reco_track_chi2pi_3pl,"reco_track_chi2pi_3pl/F");
  outtree->Branch("reco_track_chi2mu_3pl",&reco_track_chi2mu_3pl,"reco_track_chi2mu_3pl/F");
 

  outtree->Branch("reco_track_delta_dEdx_pl0",&reco_track_delta_dEdx_pl0,"reco_track_delta_dEdx_pl0/F");
  outtree->Branch("reco_track_delta_dEdx_pl1",&reco_track_delta_dEdx_pl1,"reco_track_delta_dEdx_pl1/F");
  outtree->Branch("reco_track_delta_dEdx_pl2",&reco_track_delta_dEdx_pl2,"reco_track_delta_dEdx_pl2/F");

  outtree->Branch("reco_track_llrpid_3pl",&reco_track_llrpid_3pl,"reco_track_llrpid_3pl/F");
  outtree->Branch("reco_track_llrpid_k_3pl",&reco_track_llrpid_k_3pl,"reco_track_llrpid_k_3pl/F");
  outtree->Branch("reco_track_true_pdg",&reco_track_true_pdg,"reco_track_true_pdg/I");
  
  outtree->Branch("reco_track_vtx_inTPC",&reco_track_vtx_inTPC,"reco_track_vtx_inTPC/O");
  outtree->Branch("reco_track_vtx_in5cmTPC",&reco_track_vtx_in5cmTPC,"reco_track_vtx_in5cmTPC/O");
  outtree->Branch("reco_track_vtx_inCCInclusiveTPC",&reco_track_vtx_inCCInclusiveTPC,"reco_track_vtx_inCCInclusiveTPC/O");
  outtree->Branch("reco_track_end_inTPC",&reco_track_end_inTPC,"reco_track_end_inTPC/O");
  outtree->Branch("reco_track_end_in5cmTPC",&reco_track_end_in5cmTPC,"reco_track_end_in5cmTPC/O");
  outtree->Branch("reco_track_end_inCCInclusiveTPC",&reco_track_end_inCCInclusiveTPC,"reco_track_end_inCCInclusiveTPC/O");
  
  outtree->Branch("reco_track_true_end_inTPC",&reco_track_true_end_inTPC,"reco_track_true_end_inTPC/O");
  outtree->Branch("reco_track_true_end_in5cmTPC",&reco_track_true_end_in5cmTPC,"reco_track_true_end_in5cmTPC/O");
  outtree->Branch("reco_track_true_end_inCCInclusiveTPC",&reco_track_true_end_inCCInclusiveTPC,"reco_track_true_end_inCCInclusiveTPC/O");


  outtree->Branch("reco_track_ndaughters",&reco_track_ndaughters,"reco_track_ndaughters/F");    
  outtree->Branch("reco_track_daughter_length",&reco_track_daughter_length,"reco_track_daughter_length/F");
  outtree->Branch("reco_track_daughter_distance",&reco_track_daughter_distance,"reco_track_daughter_distance/F");
  outtree->Branch("reco_track_daughter_vtx_distance",&reco_track_daughter_vtx_distance,"reco_track_daughter_vtx_distance/F");
  outtree->Branch("reco_track_daughter_theta",&reco_track_daughter_theta,"reco_track_daughter_theta/F");
  outtree->Branch("reco_track_daughter_phi",&reco_track_daughter_phi,"reco_track_daughter_phi/F");  
  outtree->Branch("reco_angle_track_daughter",&reco_angle_track_daughter,"reco_angle_track_daughter/F");
  
  outtree->Branch("reco_track_daughter_chi2ka_pl0",&reco_track_daughter_chi2ka_pl0,"reco_track_daughter_chi2ka_pl0/F");
  outtree->Branch("reco_track_daughter_chi2pr_pl0",&reco_track_daughter_chi2pr_pl0,"reco_track_daughter_chi2pr_pl0/F");
  outtree->Branch("reco_track_daughter_chi2pi_pl0",&reco_track_daughter_chi2pi_pl0,"reco_track_daughter_chi2pi_pl0/F");
  outtree->Branch("reco_track_daughter_chi2mu_pl0",&reco_track_daughter_chi2mu_pl0,"reco_track_daughter_chi2mu_pl0/F");
  
  outtree->Branch("reco_track_daughter_chi2ka_pl1",&reco_track_daughter_chi2ka_pl1,"reco_track_daughter_chi2ka_pl1/F");
  outtree->Branch("reco_track_daughter_chi2pr_pl1",&reco_track_daughter_chi2pr_pl1,"reco_track_daughter_chi2pr_pl1/F");
  outtree->Branch("reco_track_daughter_chi2pi_pl1",&reco_track_daughter_chi2pi_pl1,"reco_track_daughter_chi2pi_pl1/F");
  outtree->Branch("reco_track_daughter_chi2mu_pl1",&reco_track_daughter_chi2mu_pl1,"reco_track_daughter_chi2mu_pl1/F");
  
  outtree->Branch("reco_track_daughter_chi2ka_pl2",&reco_track_daughter_chi2ka_pl2,"reco_track_daughter_chi2ka_pl2/F");
  outtree->Branch("reco_track_daughter_chi2pr_pl2",&reco_track_daughter_chi2pr_pl2,"reco_track_daughter_chi2pr_pl2/F");
  outtree->Branch("reco_track_daughter_chi2pi_pl2",&reco_track_daughter_chi2pi_pl2,"reco_track_daughter_chi2pi_pl2/F");
  outtree->Branch("reco_track_daughter_chi2mu_pl2",&reco_track_daughter_chi2mu_pl2,"reco_track_daughter_chi2mu_pl2/F");
  
  outtree->Branch("reco_track_daughter_chi2ka_3pl",&reco_track_daughter_chi2ka_3pl,"reco_track_daughter_chi2ka_3pl/F");
  outtree->Branch("reco_track_daughter_chi2pr_3pl",&reco_track_daughter_chi2pr_3pl,"reco_track_daughter_chi2pr_3pl/F");
  outtree->Branch("reco_track_daughter_chi2pi_3pl",&reco_track_daughter_chi2pi_3pl,"reco_track_daughter_chi2pi_3pl/F");
  outtree->Branch("reco_track_daughter_chi2mu_3pl",&reco_track_daughter_chi2mu_3pl,"reco_track_daughter_chi2mu_3pl/F");

  outtree->Branch("reco_track_daughter_llrpid_3pl",&reco_track_daughter_llrpid_3pl,"reco_track_daughter_llrpid_3pl/F");  
  outtree->Branch("reco_track_daughter_llrpid_k_3pl",&reco_track_daughter_llrpid_k_3pl,"reco_track_daughter_llrpid_k_3pl/F");  
  outtree->Branch("reco_track_daughter_true_pdg",&reco_track_daughter_true_pdg,"reco_track_daughter_true_pdg/F");  
  outtree->Branch("reco_track_daughter_vtx_inTPC",&reco_track_daughter_vtx_inTPC,"reco_track_daughter_vtx_inTPC/O");
  outtree->Branch("reco_track_daughter_vtx_in5cmTPC",&reco_track_daughter_vtx_in5cmTPC,"reco_track_daughter_vtx_in5cmTPC/O");
  outtree->Branch("reco_track_daughter_vtx_inCCInclusiveTPC",&reco_track_daughter_vtx_inCCInclusiveTPC,"reco_track_daughter_vtx_inCCInclusiveTPC/O");
  outtree->Branch("reco_track_daughter_end_inTPC",&reco_track_daughter_end_inTPC,"reco_track_daughter_end_inTPC/O");
  outtree->Branch("reco_track_daughter_end_in5cmTPC",&reco_track_daughter_end_in5cmTPC,"reco_track_daughter_end_in5cmTPC/O");
  outtree->Branch("reco_track_daughter_end_inCCInclusiveTPC",&reco_track_daughter_end_inCCInclusiveTPC,"reco_track_daughter_end_inCCInclusiveTPC/O");
  
  outtree->Branch("reco_track_daughter_true_end_inTPC",&reco_track_daughter_true_end_inTPC,"reco_track_daughter_true_end_inTPC/O");
  outtree->Branch("reco_track_daughter_true_end_in5cmTPC",&reco_track_daughter_true_end_in5cmTPC,"reco_track_daughter_true_end_in5cmTPC/O");
  outtree->Branch("reco_track_daughter_true_end_inCCInclusiveTPC",&reco_track_daughter_true_end_inCCInclusiveTPC,"reco_track_daughter_true_end_inCCInclusiveTPC/O");

  outtree->Branch("reco_track_kin0",&reco_track_kin0,"reco_track_kin0/F");
  outtree->Branch("reco_track_kin1",&reco_track_kin1,"reco_track_kin1/F");
  outtree->Branch("reco_track_kin2",&reco_track_kin2,"reco_track_kin2/F");

  outtree->Branch("reco_track_P_vtx",&reco_track_P_vtx,"reco_track_P_vtx/F");
  outtree->Branch("reco_track_P_str",&reco_track_P_str,"reco_track_P_str/F");
  outtree->Branch("reco_track_P_end",&reco_track_P_end,"reco_track_P_end/F");

  
  outtree->Branch("reco_track_ndaughters_old",&reco_track_ndaughters_old,"reco_track_ndaughters_old/F");    
  outtree->Branch("reco_track_daughter_old_length",&reco_track_daughter_old_length,"reco_track_daughter_old_length/F");
  outtree->Branch("reco_track_daughter_old_distance",&reco_track_daughter_old_distance,"reco_track_daughter_old_distance/F");
  outtree->Branch("reco_track_daughter_old_theta",&reco_track_daughter_old_theta,"reco_track_daughter_old_theta/F");
  outtree->Branch("reco_track_daughter_old_phi",&reco_track_daughter_old_phi,"reco_track_daughter_old_phi/F");  

  outtree->Branch("reco_track_daughter_old_chi2ka_pl0",&reco_track_daughter_old_chi2ka_pl0,"reco_track_daughter_old_chi2ka_pl0/F");
  outtree->Branch("reco_track_daughter_old_chi2pr_pl0",&reco_track_daughter_old_chi2pr_pl0,"reco_track_daughter_old_chi2pr_pl0/F");
  outtree->Branch("reco_track_daughter_old_chi2pi_pl0",&reco_track_daughter_old_chi2pi_pl0,"reco_track_daughter_old_chi2pi_pl0/F");
  outtree->Branch("reco_track_daughter_old_chi2mu_pl0",&reco_track_daughter_old_chi2mu_pl0,"reco_track_daughter_old_chi2mu_pl0/F");
  
  outtree->Branch("reco_track_daughter_old_chi2ka_pl1",&reco_track_daughter_old_chi2ka_pl1,"reco_track_daughter_old_chi2ka_pl1/F");
  outtree->Branch("reco_track_daughter_old_chi2pr_pl1",&reco_track_daughter_old_chi2pr_pl1,"reco_track_daughter_old_chi2pr_pl1/F");
  outtree->Branch("reco_track_daughter_old_chi2pi_pl1",&reco_track_daughter_old_chi2pi_pl1,"reco_track_daughter_old_chi2pi_pl1/F");
  outtree->Branch("reco_track_daughter_old_chi2mu_pl1",&reco_track_daughter_old_chi2mu_pl1,"reco_track_daughter_old_chi2mu_pl1/F");
  
  outtree->Branch("reco_track_daughter_old_chi2ka_pl2",&reco_track_daughter_old_chi2ka_pl2,"reco_track_daughter_old_chi2ka_pl2/F");
  outtree->Branch("reco_track_daughter_old_chi2pr_pl2",&reco_track_daughter_old_chi2pr_pl2,"reco_track_daughter_old_chi2pr_pl2/F");
  outtree->Branch("reco_track_daughter_old_chi2pi_pl2",&reco_track_daughter_old_chi2pi_pl2,"reco_track_daughter_old_chi2pi_pl2/F");
  outtree->Branch("reco_track_daughter_old_chi2mu_pl2",&reco_track_daughter_old_chi2mu_pl2,"reco_track_daughter_old_chi2mu_pl2/F");
  
  outtree->Branch("reco_track_daughter_old_chi2ka_3pl",&reco_track_daughter_old_chi2ka_3pl,"reco_track_daughter_old_chi2ka_3pl/F");
  outtree->Branch("reco_track_daughter_old_chi2pr_3pl",&reco_track_daughter_old_chi2pr_3pl,"reco_track_daughter_old_chi2pr_3pl/F");
  outtree->Branch("reco_track_daughter_old_chi2pi_3pl",&reco_track_daughter_old_chi2pi_3pl,"reco_track_daughter_old_chi2pi_3pl/F");
  outtree->Branch("reco_track_daughter_old_chi2mu_3pl",&reco_track_daughter_old_chi2mu_3pl,"reco_track_daughter_old_chi2mu_3pl/F");

  outtree->Branch("reco_track_daughter_old_llrpid_3pl",&reco_track_daughter_old_llrpid_3pl,"reco_track_daughter_old_llrpid_3pl/F");  
  outtree->Branch("reco_track_daughter_old_llrpid_k_3pl",&reco_track_daughter_old_llrpid_k_3pl,"reco_track_daughter_old_llrpid_k_3pl/F");  
  outtree->Branch("reco_track_daughter_old_true_pdg",&reco_track_daughter_old_true_pdg,"reco_track_daughter_old_true_pdg/F");  
  outtree->Branch("reco_track_daughter_old_vtx_inTPC",&reco_track_daughter_old_vtx_inTPC,"reco_track_daughter_old_vtx_inTPC/O");
  outtree->Branch("reco_track_daughter_old_vtx_in5cmTPC",&reco_track_daughter_old_vtx_in5cmTPC,"reco_track_daughter_old_vtx_in5cmTPC/O");
  outtree->Branch("reco_track_daughter_old_vtx_inCCInclusiveTPC",&reco_track_daughter_old_vtx_inCCInclusiveTPC,"reco_track_daughter_old_vtx_inCCInclusiveTPC/O");
  outtree->Branch("reco_track_daughter_old_end_inTPC",&reco_track_daughter_old_end_inTPC,"reco_track_daughter_old_end_inTPC/O");
  outtree->Branch("reco_track_daughter_old_end_in5cmTPC",&reco_track_daughter_old_end_in5cmTPC,"reco_track_daughter_old_end_in5cmTPC/O");
  outtree->Branch("reco_track_daughter_old_end_inCCInclusiveTPC",&reco_track_daughter_old_end_inCCInclusiveTPC,"reco_track_daughter_old_end_inCCInclusiveTPC/O");
  


  // Loop over tree
  Long64_t nentries = t->GetEntries();
  cout << "Tree entries " << nentries << endl;

  Event event(t);
  //plotcck event(t);

  //for(Long64_t ev = 0; ev < evt.size(); ev++){

  Int_t true_cut1 = 0;
  Int_t true_cut2 = 0;
  Int_t true_cut3 = 0;

  //event.GetEntry(evt[ev]);
  //for (Long64_t jentry=0; jentry<1000; jentry++) {
  for (Long64_t jentry=0; jentry<nentries; jentry++) {

   
    event.GetEntry(jentry);
    if(nentries>=10){
      if (jentry%int(nentries/10.) == 0) {
	cout << int(100.*jentry/nentries) << " %" << endl;
      }
    }
    //cout << "true_nu_energy: " << event.true_nu_energy << endl;
    //cout << "true_dau_muon_end_x: " << event.true_dau_muon_end_x << endl; 

    //if(true_dau_muon_end_x>0) cout << "true_dau_muon_end_x: " << event.true_dau_muon_end_x << ", true_dau_muon_start_x: " <<  event.true_dau_muon_start_x  << endl;  

    //FHC: 23 October 2015 - 2 May 2016 | run.sub 0 - 6748.22
    //RHC: 29 June 2016 - 29 July 2016 | run.sub 6748.22 - 7001
    //remove RHC runs
    /*
    if(event.run >= 6748 && event.run <= 7001){
      if(!(event.run == 6748 && event.subrun <= 21)) continue;
      //else continue;
    }
    */
    

    if(event.true_nu_pdg==14 && event.true_nu_ccnc==0 && (event.true_kaon_end_process==0 || event.true_kaon_end_process==1)  && event.true_kaon_ke>=0 && event.true_nu_vtx_inCCInclusiveTPC==true && event.true_kaon_end_inCCInclusiveTPC==true && event.true_kaon_daughter_end_in5cmTPC==true) n_true_k++;
    //if(event.true_kaon_end_process>=0) n_true_k++;
    //if(jentry%2 == 1) continue;

    if (event.reco_nu_vtx_inCCInclusiveTPC==false) continue;
    if (event.reco_nu_cc_filter==false) continue;    
    
    if(event.true_nu_pdg==14 && event.true_nu_ccnc==0 && event.true_kaon_ke>=0 && event.true_nu_vtx_inCCInclusiveTPC==true){
      true_cut1++;
      if(event.true_kaon_end_inCCInclusiveTPC==true){
	true_cut2++;
	if(event.true_kaon_daughter_end_in5cmTPC==true){
	  true_cut3++;
	}
      }    
    }
    

    //if(event.run==5025 || event.subrun==134 || event.event==6738) cout << "num_tracks: " << event.reco_ntracks << endl;

    std::cout << "event.run: " << event.run << ", event.subrun: " << event.subrun << ", event.event: " << event.event << std::endl;

    // Loop over tracks 
    //cout << "event.reco_ntracks: " << event.reco_ntracks << endl;
    for (int itrk=0;itrk<event.reco_ntracks;itrk++) {
    //for (int itrk=0;itrk<10;itrk++) {

      //if(event.run==5025 || event.subrun==134 || event.event==6738){
      /*
	if(event.true_nu_pdg==14 && event.true_nu_ccnc==0 && event.true_kaon_ke>=0 && event.true_nu_vtx_inCCInclusiveTPC==true){
	  cout << "num_tracks: " << event.reco_ntracks << endl;
	  cout << itrk << "-th track pdg: " << event.reco_track_true_pdg[itrk] << endl;
	}
*/
	//}

      //if(event.reco_track_end_inCCInclusiveTPC[itrk]==false) continue;

      //cout << "event.n_recoRebDauTracks[itrk]: " << event.n_recoRebDauTracks[itrk] << endl;

      n_recoRebDauTracks = event.n_recoRebDauTracks[itrk];
      rebdautracktrue_length = event.rebdautracktrue_length[itrk];
      rebdautracktruedir_length = event.rebdautracktruedir_length[itrk];
      best_peak_x_true = event.best_peak_x_true[itrk];
      best_peak_y_true = event.best_peak_y_true[itrk];
      best_peak_z_true = event.best_peak_z_true[itrk];


      double max_dau_length = -1;
      int max_dau_length_index = -1;

      //if(event.rebdautrack_length[itrk][idau]!=-9999) 
      //if(n_recoRebDauTracks<=0) continue;
      for (int idau=0;idau<event.n_recoRebDauTracks[itrk];idau++) {

	//cout << "reco_track_true_pdg: " << reco_track_true_pdg << endl;
	//cout << "itrk: " << itrk << ", idau: " << idau <<  ", event.rebdautrack_length[itrk][idau]: " << event.rebdautrack_length[itrk][idau] << endl;

	if(event.rebdautrack_length[itrk][idau]>max_dau_length){
	  max_dau_length = event.rebdautrack_length[itrk][idau];
	  max_dau_length_index = idau;
	}
      }

	if(max_dau_length_index>=0){
	  rebdautrack_length = max_dau_length;
	  rebdautrack_pdg = event.rebdautrack_pdg[itrk][max_dau_length_index];
	  best_peak_x = event.best_peak_x[itrk][max_dau_length_index];
	  best_peak_y = event.best_peak_y[itrk][max_dau_length_index];
	  best_peak_z = event.best_peak_z[itrk][max_dau_length_index];
      }
	
	reco_track_daughter_length = event.reco_track_daughter_length[itrk][0];
	reco_track_daughter_distance = event.reco_track_daughter_distance[itrk][0];
	reco_track_daughter_vtx_distance = event.reco_track_daughter_vtx_distance[itrk][0];
	reco_track_daughter_theta = event.reco_track_daughter_theta[itrk][0];
	reco_track_daughter_phi = event.reco_track_daughter_phi[itrk][0];
	
	reco_angle_track_daughter = event.reco_angle_track_daughter[itrk][0];
	
	reco_track_daughter_chi2ka_pl0 = event.reco_track_daughter_chi2ka_pl0[itrk][0];
	reco_track_daughter_chi2pr_pl0 = event.reco_track_daughter_chi2pr_pl0[itrk][0];
	reco_track_daughter_chi2pi_pl0 = event.reco_track_daughter_chi2pi_pl0[itrk][0];
	reco_track_daughter_chi2mu_pl0 = event.reco_track_daughter_chi2mu_pl0[itrk][0];
	
	reco_track_daughter_chi2ka_pl1 = event.reco_track_daughter_chi2ka_pl1[itrk][0];
	reco_track_daughter_chi2pr_pl1 = event.reco_track_daughter_chi2pr_pl1[itrk][0];
	reco_track_daughter_chi2pi_pl1 = event.reco_track_daughter_chi2pi_pl1[itrk][0];
	reco_track_daughter_chi2mu_pl1 = event.reco_track_daughter_chi2mu_pl1[itrk][0];
	
	reco_track_daughter_chi2ka_pl2 = event.reco_track_daughter_chi2ka_pl2[itrk][0];
	reco_track_daughter_chi2pr_pl2 = event.reco_track_daughter_chi2pr_pl2[itrk][0];
	reco_track_daughter_chi2pi_pl2 = event.reco_track_daughter_chi2pi_pl2[itrk][0];
	reco_track_daughter_chi2mu_pl2 = event.reco_track_daughter_chi2mu_pl2[itrk][0];
	
	reco_track_daughter_chi2ka_3pl = event.reco_track_daughter_chi2ka_3pl[itrk][0];
	reco_track_daughter_chi2pr_3pl = event.reco_track_daughter_chi2pr_3pl[itrk][0];
	reco_track_daughter_chi2pi_3pl = event.reco_track_daughter_chi2pi_3pl[itrk][0];
	reco_track_daughter_chi2mu_3pl = event.reco_track_daughter_chi2mu_3pl[itrk][0];
	
	reco_track_daughter_llrpid_3pl = event.reco_track_daughter_llrpid_3pl[itrk][0];      
	reco_track_daughter_llrpid_k_3pl = event.reco_track_daughter_llrpid_k_3pl[itrk][0];      
	reco_track_daughter_true_pdg = event.reco_track_daughter_true_pdg[itrk][0];
	//if(event.reco_track_true_pdg[itrk]==321) cout << "reco_track_daughter_true_pdg: " << reco_track_daughter_true_pdg << ", length: " << reco_track_daughter_length << endl;
	
	reco_track_daughter_vtx_inTPC = event.reco_track_daughter_vtx_inTPC[itrk][0];
	reco_track_daughter_vtx_in5cmTPC = event.reco_track_daughter_vtx_in5cmTPC[itrk][0];
	reco_track_daughter_vtx_inCCInclusiveTPC = event.reco_track_daughter_vtx_inCCInclusiveTPC[itrk][0];
	reco_track_daughter_end_inTPC = event.reco_track_daughter_end_inTPC[itrk][0];
	reco_track_daughter_end_in5cmTPC = event.reco_track_daughter_end_in5cmTPC[itrk][0];
	reco_track_daughter_end_inCCInclusiveTPC = event.reco_track_daughter_end_inCCInclusiveTPC[itrk][0];
 
      //}
      
      //if(reco_track_daughter_end_in5cmTPC == false) continue;
      //if(reco_track_daughter_length<0) continue;


      /*
      if(event.reco_track_true_pdg[itrk]==321 && ( event.reco_track_daughter_true_pdg[itrk][0]==-13 || event.reco_track_daughter_true_pdg[itrk][0]==211)  && event.reco_nu_vtx_inCCInclusiveTPC==true){
	true_cut1++;
	if(event.reco_track_end_inCCInclusiveTPC[itrk]==true){
	  true_cut2++;
	  if(reco_track_daughter_end_in5cmTPC==true){
	    true_cut3++;
	  }
	}    
      }
      */

      //if (event.reco_track_end_inCCInclusiveTPC[itrk]==false) continue;
      //if (event.reco_track_ndaughters[itrk] != 1) continue;
      //if (event.reco_track_daughter_end_in5cmTPC[itrk][0]==false) continue;

      /*
      if(
	 (event.run==7006 && event.subrun==70 && event.event==3528)
	 || (event.run==5025 || event.subrun==134 || event.event==6738)
	 )
	{
      */
	  //}

      //if (event.reco_track_true_pdg[itrk] == -9999) continue;
      //if (event.reco_track_true_pdg[itrk] != 321) continue;
      //if (event.reco_track_vtx_inTPC[itrk]==false) continue;

      //if (event.reco_track_daughter_vtx_inTPC[itrk][0]==false) continue;
      //if (event.reco_track_daughter_true_pdg[itrk][0] == -9999) continue;
      //if (event.reco_track_daughter_true_pdg[itrk][0] != -13 && event.reco_track_daughter_true_pdg[itrk][0] != 211) continue;
      
      true_nu_energy = event.true_nu_energy;
      true_kaon_length = event.true_kaon_length;
      true_kaon_daughter_length = event.true_kaon_daughter_length;
      true_kaon_p = event.true_kaon_p;
      true_kaon_ke = event.true_kaon_ke;
      true_kaon_theta = event.true_kaon_theta;
      true_kaon_costheta = event.true_kaon_costheta;
      true_kaon_phi = event.true_kaon_phi;

      true_dau_pip_length = event.true_dau_pip_length;
      true_dau_muon_length = event.true_dau_muon_length;

      eventnum = event.event;
      run = event.run;
      subrun = event.subrun;
      true_nu_pdg = event.true_nu_pdg;
      true_nu_ccnc = event.true_nu_ccnc;
      true_nu_mode = event.true_nu_mode;
      true_lepton_pdg = event.true_lepton_pdg;
      true_nkaons = event.true_nkaons;
      true_nhyperons = event.true_nhyperons;
      reco_ccmu_true_pdg = event.reco_ccmu_true_pdg;

      true_kaon_end_process  = event.true_kaon_end_process;

      true_kaon_end_x = event.true_kaon_end_x;
      true_kaon_end_y = event.true_kaon_end_y;
      true_kaon_end_z = event.true_kaon_end_z;
      //cout << "true_dau_muon_end_x: " << event.true_dau_muon_end_x << endl;
      true_dau_muon_end_x = event.true_dau_muon_end_x;
      true_dau_muon_end_y = event.true_dau_muon_end_y;
      true_dau_muon_end_z = event.true_dau_muon_end_z;
      true_dau_muon_start_x = event.true_dau_muon_start_x;
      true_dau_muon_start_y = event.true_dau_muon_start_y;
      true_dau_muon_start_z = event.true_dau_muon_start_z;
      true_dau_pip_end_x = event.true_dau_pip_end_x;
      true_dau_pip_end_y = event.true_dau_pip_end_y;
      true_dau_pip_end_z = event.true_dau_pip_end_z;
      true_dau_pip_start_x = event.true_dau_pip_start_x;
      true_dau_pip_start_y = event.true_dau_pip_start_y;
      true_dau_pip_start_z = event.true_dau_pip_start_z;
      true_dau_muon_theta = event.true_dau_muon_theta;
      true_dau_muon_phi = event.true_dau_muon_phi;
      true_dau_pip_theta = event.true_dau_pip_theta;
      true_dau_pip_phi = event.true_dau_pip_phi;

      reco_track_nhits0 = event.reco_track_nhits0[itrk];
      reco_track_nhits1 = event.reco_track_nhits1[itrk];
      reco_track_nhits2 = event.reco_track_nhits2[itrk];
      
      reco_track_distance = event.reco_track_distance[itrk];
      //reco_track_vtx_distance = event.reco_track_vtx_distance[itrk];
      reco_track_length = event.reco_track_length[itrk];
      reco_track_theta = event.reco_track_theta[itrk];
      reco_track_phi = event.reco_track_phi[itrk];

      reco_track_end_x = event.reco_track_end_x[itrk];
      reco_track_end_y = event.reco_track_end_y[itrk];
      reco_track_end_z = event.reco_track_end_z[itrk];
      
      reco_track_log_bragg_peak = log(event.reco_track_MIP_pl2[itrk]/event.reco_track_Bragg_fwd_pr_pl2[itrk]);
      reco_track_Bragg_fwd_ka_pl0 = event.reco_track_Bragg_fwd_ka_pl0[itrk];
      reco_track_Bragg_fwd_pr_pl0 = event.reco_track_Bragg_fwd_pr_pl0[itrk];
      reco_track_Bragg_fwd_pi_pl0 = event.reco_track_Bragg_fwd_pi_pl0[itrk];
      reco_track_Bragg_fwd_mu_pl0 = event.reco_track_Bragg_fwd_mu_pl0[itrk];
      reco_track_Bragg_fwd_ka_pl1 = event.reco_track_Bragg_fwd_ka_pl1[itrk];
      reco_track_Bragg_fwd_pr_pl1 = event.reco_track_Bragg_fwd_pr_pl1[itrk];
      reco_track_Bragg_fwd_pi_pl1 = event.reco_track_Bragg_fwd_pi_pl1[itrk];
      reco_track_Bragg_fwd_mu_pl1 = event.reco_track_Bragg_fwd_mu_pl1[itrk];
      reco_track_Bragg_fwd_ka_pl2 = event.reco_track_Bragg_fwd_ka_pl2[itrk];
      reco_track_Bragg_fwd_pr_pl2 = event.reco_track_Bragg_fwd_pr_pl2[itrk];
      reco_track_Bragg_fwd_pi_pl2 = event.reco_track_Bragg_fwd_pi_pl2[itrk];
      reco_track_Bragg_fwd_mu_pl2 = event.reco_track_Bragg_fwd_mu_pl2[itrk];
      
      reco_track_MIP_pl0 = event.reco_track_MIP_pl0[itrk];
      reco_track_MIP_pl1 = event.reco_track_MIP_pl1[itrk];
      reco_track_MIP_pl2 = event.reco_track_MIP_pl2[itrk];
      
      reco_track_chi2ka_pl0 = event.reco_track_chi2ka_pl0[itrk];
      reco_track_chi2pr_pl0 = event.reco_track_chi2pr_pl0[itrk];
      reco_track_chi2pi_pl0 = event.reco_track_chi2pi_pl0[itrk];
      reco_track_chi2mu_pl0 = event.reco_track_chi2mu_pl0[itrk];
      
      reco_track_chi2ka_pl1 = event.reco_track_chi2ka_pl1[itrk];
      reco_track_chi2pr_pl1 = event.reco_track_chi2pr_pl1[itrk];
      reco_track_chi2pi_pl1 = event.reco_track_chi2pi_pl1[itrk];
      reco_track_chi2mu_pl1 = event.reco_track_chi2mu_pl1[itrk];
      
      reco_track_chi2ka_pl2 = event.reco_track_chi2ka_pl2[itrk];
      reco_track_chi2pr_pl2 = event.reco_track_chi2pr_pl2[itrk];
      reco_track_chi2pi_pl2 = event.reco_track_chi2pi_pl2[itrk];
      reco_track_chi2mu_pl2 = event.reco_track_chi2mu_pl2[itrk];
      
      reco_track_chi2ka_3pl = event.reco_track_chi2ka_3pl[itrk];
      reco_track_chi2pr_3pl = event.reco_track_chi2pr_3pl[itrk];
      reco_track_chi2pi_3pl = event.reco_track_chi2pi_3pl[itrk];
      reco_track_chi2mu_3pl = event.reco_track_chi2mu_3pl[itrk];
      
      reco_track_llrpid_3pl = event.reco_track_llrpid_3pl[itrk];
      reco_track_llrpid_k_3pl = event.reco_track_llrpid_k_3pl[itrk];
      reco_track_true_pdg = event.reco_track_true_pdg[itrk];
      //cout << "reco_track_true_pdg: " << reco_track_true_pdg << endl;
      
      true_nu_vtx_inCCInclusiveTPC = event.true_nu_vtx_inCCInclusiveTPC;
      true_kaon_end_inCCInclusiveTPC = event.true_kaon_end_inCCInclusiveTPC;
      true_kaon_daughter_end_in5cmTPC = event.true_kaon_daughter_end_in5cmTPC;

      reco_track_vtx_inTPC = event.reco_track_vtx_inTPC[itrk];
      reco_track_vtx_in5cmTPC = event.reco_track_vtx_in5cmTPC[itrk];
      reco_track_vtx_inCCInclusiveTPC = event.reco_track_vtx_inCCInclusiveTPC[itrk];
      reco_track_end_inTPC = event.reco_track_end_inTPC[itrk];
      reco_track_end_in5cmTPC = event.reco_track_end_in5cmTPC[itrk];
      reco_track_end_inCCInclusiveTPC = event.reco_track_end_inCCInclusiveTPC[itrk];
      reco_track_ndaughters = event.reco_track_ndaughters[itrk];
      //reco_track_ndaughters_old = event.reco_track_ndaughters_old[itrk];
	

    

      reco_track_kin0 = event.reco_track_kin0[itrk];
      reco_track_kin1 = event.reco_track_kin1[itrk];
      reco_track_kin2 = event.reco_track_kin2[itrk];

      reco_track_P_vtx = event.reco_track_P_vtx[itrk];
      reco_track_P_str = event.reco_track_P_str[itrk];
      reco_track_P_end = event.reco_track_P_end[itrk];


      outtree->Fill();

      // Reset track-level variables after filling the tree
      reco_track_ndaughters = -1;
      reco_track_daughter_length = -9999;
      reco_track_daughter_distance = -9999;
      reco_track_daughter_vtx_distance = -9999;
      reco_track_daughter_theta = -9999;
      reco_track_daughter_phi = -9999;
      reco_track_daughter_chi2ka_pl0 = -9999;
      reco_track_daughter_chi2pr_pl0 = -9999;
      reco_track_daughter_chi2pi_pl0 = -9999;
      reco_track_daughter_chi2mu_pl0 = -9999;
      reco_track_daughter_chi2ka_pl1 = -9999;
      reco_track_daughter_chi2pr_pl1 = -9999;
      reco_track_daughter_chi2pi_pl1 = -9999;
      reco_track_daughter_chi2mu_pl1 = -9999;
      reco_track_daughter_chi2ka_pl2 = -9999;
      reco_track_daughter_chi2pr_pl2 = -9999;
      reco_track_daughter_chi2pi_pl2 = -9999;
      reco_track_daughter_chi2mu_pl2 = -9999;
      reco_track_daughter_chi2ka_3pl = -9999;
      reco_track_daughter_chi2pr_3pl = -9999;
      reco_track_daughter_chi2pi_3pl = -9999;
      reco_track_daughter_chi2mu_3pl = -9999;
      reco_track_daughter_llrpid_3pl = -9999;
      reco_track_daughter_llrpid_k_3pl = -9999;
      reco_track_daughter_true_pdg = -9999;
      reco_track_daughter_vtx_inTPC = false;
      reco_track_daughter_vtx_in5cmTPC = false;
      reco_track_daughter_vtx_inCCInclusiveTPC = false;
      reco_track_daughter_end_inTPC = false;
      reco_track_daughter_end_in5cmTPC = false;
      reco_track_daughter_end_inCCInclusiveTPC = false;

    }//end loop over tracks

    // Reset event-level variables after each event is fully processed
    true_nu_energy = -9999;
    true_kaon_length = -9999;
    true_kaon_daughter_length = -9999;
    true_kaon_p = -9999;
    true_kaon_ke = -9999;
    true_kaon_theta = -9999;
    true_kaon_costheta = -9999;
    true_kaon_phi = -9999;
    true_dau_pip_length = -9999;
    true_dau_muon_length = -9999;
    true_nu_ccnc = -9999;
    true_nu_pdg = -9999;
    true_nu_mode = -9999;
    true_lepton_pdg = -9999;
    true_nkaons = -9999;
    true_nhyperons = -9999;
    true_kaon_end_process = -9999;
    true_kaon_ndaughters_inelastic = -9999;
    reco_ccmu_true_pdg = -9999;
    eventnum = -9999;
    run = -9999;
    subrun = -9999;

  }//tree loop

  cout << true_cut1 << " " << true_cut2 << " " << true_cut3 << endl;

  outfile->Write();
  outfile->Close();
  delete outfile;
  cout << "n_true_k: " << n_true_k << endl;
  cout << "process end" << endl;
}



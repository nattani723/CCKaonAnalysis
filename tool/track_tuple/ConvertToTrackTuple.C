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
void ConvertToTrackTuple(TString input_name, TString output_name);
//void precuts(TString s);
//vector <int> evt;


void ConvertToTrackTuple()
{

  TStopwatch clock;
  //ConvertToTrackTuple("/uboone/app/users/taniuchi/KaonAna/bnb_kaon/root_files/cck_sample/CCKaonAnalyzer_cckplus.root","test.root");
  //ConvertToTrackTuple("/uboone/app/users/taniuchi/KaonAna/numi_kaon/root_files/CCKaonAnalyzer_fullmc.root","root_files/nuccfilter_numi_mc_tracktuple.root");
  //ConvertToTrackTuple("/uboone/app/users/taniuchi/KaonAna/numi_kaon/cckMC/fhc_run1/root_files/numi_cck_fhc_run1.root","root_files/nuccfilter_numi_cck_tracktuple.root");
  //ConvertToTrackTuple("/uboone/app/users/taniuchi/KaonAna/numi_kaon/root_files/CCKaonAnalyzer_fullmc.root","root_files/mip_numi_mc_tracktuple.root");
  //ConvertToTrackTuple("/uboone/app/users/taniuchi/KaonAna/numi_kaon/cckMC/fhc_run1/root_files/numi_cck_fhc_run1.root","root_files/mip_numi_cck_tracktuple.root");
  //ConvertToTrackTuple("/uboone/data/users/taniuchi/numi_kaon/root_files/ana/ana_numi_mc.root","root_files/nuccfilter_numi_mc_tracktuple.root");
  //ConvertToTrackTuple("/uboone/data/users/taniuchi/numi_kaon/root_files/ana/ana_numi_cck_fhc_run1_pt1_pt2.root","root_files/nuccfilter_numi_cck_tracktuple.root");
  //ConvertToTrackTuple("/uboone/data/users/taniuchi/numi_kaon/root_files/ana/ana_numi_mc.root","root_files/mip_numi_mc_tracktuple.root");
  //ConvertToTrackTuple("/uboone/data/users/taniuchi/numi_kaon/root_files/ana/ana_numi_cck_fhc_run1_pt1_pt2.root","root_files/mip_numi_cck_tracktuple.root");
  //  ConvertToTrackTuple(Form("%s",s.c_str()),"tracks_cck_sig.root");

  /*
  ConvertToTrackTuple("uboone/data/users/taniuchi/numi_kaon/ana/numi_mc/ana_numi_mc.root","root_files/mip_numi_mc_tracktuple.root");
  ConvertToTrackTuple("/uboone/data/users/taniuchi/numi_kaon/ana/numi_cck/ana_numi_cck_fhc_run1.root","root_files/mip_numi_cck_tracktuple.root");
  ConvertToTrackTuple("/uboone/data/users/taniuchi/numi_kaon/ana/ana_numi_mc_w_cck_fhc_run1.root","root_files/mip_numi_mc_w_cck_tracktuple.root");
  
  ConvertToTrackTuple("uboone/data/users/taniuchi/numi_kaon/ana/numi_mc/ana_numi_mc.root","root_files/nuccfilter_numi_mc_tracktuple.root");
  ConvertToTrackTuple("/uboone/data/users/taniuchi/numi_kaon/ana/numi_cck/ana_numi_cck_fhc_run1.root","root_files/nuccfilter_numi_cck_tracktuple.root");
  ConvertToTrackTuple("/uboone/data/users/taniuchi/numi_kaon/ana/ana_numi_mc_w_cck_fhc_run1.root","root_files/nuccfilter_numi_mc_w_cck_tracktuple.root");
  */

  //ConvertToTrackTuple("/uboone/data/users/taniuchi/numi_kaon/ana/numi_cck/15Aug2022/ana_numi_mc.root","15Aug_numi_run1_fhc_test.root");

  //ConvertToTrackTuple("/uboone/data/users/taniuchi/numi_kaon/ana/numi_mc/prodgenie_numi_uboone_overlay_fhc_mcc9_run1_v28_sample2_half2.root","track_numi_sample2_half_performance.root");
  //ConvertToTrackTuple("/uboone/data/users/taniuchi/numi_kaon/ana/numi_cck/7Nov2022/numi_fhc_run1_w_cck_v2.root","11Nov2.root");
  //ConvertToTrackTuple("numi_fhc_run1_w_cck_v3_5Dec.root","5Dec.root");

  //ConvertToTrackTuple("/uboone/data/users/taniuchi/numi_kaon/ana/numi_cck/27Jul2022/numi_fhc_run1_w_cck.root","test.root");

  //ConvertToTrackTuple("/uboone/data/users/taniuchi/numi_kaon/ana/numi_cck/numi_fhc_run1_cck.root","7Nov_1.root");
  //ConvertToTrackTuple("/uboone/data/users/taniuchi/numi_kaon/ana/numi_cck/15Aug2022/numi_fhc_run1_w_cck.root","15Aug_test.root");
  //ConvertToTrackTuple("/uboone/data/users/taniuchi/numi_kaon/ana/numi_cck/numi_w_cck_numi_fhc_run1.root","Jun29.root");

  //ConvertToTrackTuple("/uboone/app/users/taniuchi/KaonAna/ana/run1_FHC/ana_fhc_run1_sample0_trueinfo.root", "test.root");

  //ConvertToTrackTuple("/uboone/app/users/taniuchi/KaonSystematics/xml/detvar/ana/taniuchi_make_assok_events_numi_fhc_run1_detvar_g4_reco1_reco2_reco2_CV_reco2.root","make_assok_events_numi_fhc_run1_POT_41E22.root");
  //ConvertToTrackTuple("/uboone/app/users/taniuchi/KaonSystematics/xml/detvar/ana/taniuchi_make_singlek_events_numi_fhc_run1_detvar_g4_reco1_reco2_reco2_CV_reco2.root","make_singlek_events_numi_fhc_run1_POT_18E23.root");

  //ConvertToTrackTuple("/uboone/app/users/taniuchi/KaonSystematics/xml/detvar/ana/taniuchi_make_assok_events_numi_fhc_run1_detvar_g4_reco1_reco2_reco2_CV_reco2.root","make_assok_events_numi_fhc_run1_POT_41E22_no_precut.root");
  //ConvertToTrackTuple("/uboone/app/users/taniuchi/KaonSystematics/xml/detvar/ana/taniuchi_make_singlek_events_numi_fhc_run1_detvar_g4_reco1_reco2_reco2_CV_reco2.root","make_singlek_events_numi_fhc_run1_POT_18E23_no_precut.root");

  //ConvertToTrackTuple("/uboone/data/users/taniuchi/pandora_alg/ana/assok.root", "/uboone/data/users/taniuchi/pandora_alg/ana/assok_tracktuple.root");
  //ConvertToTrackTuple("/uboone/data/users/taniuchi/pandora_alg/ana/prod_2nd.root", "/uboone/data/users/taniuchi/pandora_alg/ana/prod_2nd_tracktuple.root");
  //ConvertToTrackTuple("/uboone/data/users/taniuchi/pandora_alg/ana/scan_fhc_run1_assok_match_roi30_openPI23_grow5_fit100_thres2_twofit.root", "/uboone/data/users/taniuchi/pandora_alg/ana/scan_fhc_run1_assok_match_roi30_openPI23_grow5_fit100_thres2_twofit_tracktuple.root");
  //ConvertToTrackTuple("/uboone/data/users/taniuchi/pandora_alg/ana/scan_fhc_run1_assok_match_roi30_openPI23_grow50_fit100_thres2_twofit_prod_misc.root", "/uboone/data/users/taniuchi/pandora_alg/ana/scan_fhc_run1_assok_match_roi30_openPI23_grow50_fit100_thres2_twofit_prod_misc_tracktuple.root");

  //ConvertToTrackTuple("/uboone/data/users/taniuchi/pandora_alg/ana/scan_fhc_run1_assok_match_roi30_debug_max10_initial2_discut_prod.root", "/uboone/data/users/taniuchi/pandora_alg/ana/scan_fhc_run1_assok_match_roi30_debug_max10_initial2_discut_prod_tracktuple.root");
  /*
  ConvertToTrackTuple("/uboone/data/users/taniuchi/pandora_alg/ana/scan_fhc_run1_assok_match_roi30_debug_max25_initial5_discut_prod.root", "/uboone/data/users/taniuchi/pandora_alg/ana/scan_fhc_run1_assok_match_roi30_debug_max25_initial5_discut_prod_tracktuple.root");
  ConvertToTrackTuple("/uboone/data/users/taniuchi/pandora_alg/ana/scan_fhc_run1_assok_match_roi30_debug_max25_initial5_lsdis_prod.root", "/uboone/data/users/taniuchi/pandora_alg/ana/scan_fhc_run1_assok_match_roi30_debug_max25_initial5_lsdis_prod_tracktuple.root");
  ConvertToTrackTuple("/uboone/data/users/taniuchi/pandora_alg/ana/scan_fhc_run1_assok_match_roi30_debug_max25_initial5_lscon_prod.root", "/uboone/data/users/taniuchi/pandora_alg/ana/scan_fhc_run1_assok_match_roi30_debug_max25_initial5_lscon_prod_tracktuple.root");
  */
  //ConvertToTrackTuple("/uboone/data/users/taniuchi/pandora_alg/ana/scan_fhc_run1_assok_match_roi30_debug3_prod.root", "/uboone/data/users/taniuchi/pandora_alg/ana/scan_fhc_run1_assok_match_roi30_debug3_prod_tracktuple.root");
  //ConvertToTrackTuple("/uboone/data/users/taniuchi/pandora_alg/ana/scan_fhc_run1_assok_match_roi30_debug3_max25_initial7_lsdis3_spineall_nospine_discon5_daughter50_prod.root", "/uboone/data/users/taniuchi/pandora_alg/ana/scan_fhc_run1_assok_match_roi30_debug3_max25_initial7_lsdis3_spineall_nospine_discon5_daughter50_prod_tracktuple.root");
  //ConvertToTrackTuple("/uboone/data/users/taniuchi/pandora_alg/ana/scan_fhc_run1_assok_match_roi30_debug3_max25_initial7_spineall_noprp_nospine_prod.root", "/uboone/data/users/taniuchi/pandora_alg/ana/scan_fhc_run1_assok_match_roi30_debug3_max25_initial7_spineall_noprp_nospine_prod_tracktuple.root");
  ConvertToTrackTuple("/uboone/data/users/taniuchi/pandora_alg/ana/scan_fhc_run1_assok_match_roi20_debug4_max25_initial14_lsdis3_spineall_nospine_discon5_daughter30_prod.root", "/uboone/data/users/taniuchi/pandora_alg/ana/scan_fhc_run1_assok_match_roi20_debug4_max25_initial14_lsdis3_spineall_nospine_discon5_daughter30_prod_tracktuple.root");

  cout << "Real time " << clock.RealTime() << " s" << endl << endl;

}


void ConvertToTrackTuple(TString input_name, TString output_name)
{

  // Input files
  TChain * t = new TChain("CCKaonAnalyzer/Event");
  //TChain * t = new TChain("CCKaonAnalyzerRebuild/Event");

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
  //Int_t true_kaon_ndaughters_decay = -1;
  Int_t   true_kaon_end_process = -1;

  Int_t   reco_track_nhits0 = 0;
  Int_t   reco_track_nhits1 = 0;
  Int_t   reco_track_nhits2 = 0;
  
  Float_t reco_track_distance = -9999;
  Float_t reco_track_vtx_distance = -9999;
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
  
  Bool_t  reco_track_true_vtx_inTPC = 0;
  Bool_t  reco_track_true_vtx_in5cmTPC = 0;
  Bool_t  reco_track_true_vtx_inCCInclusiveTPC = 0;
  Bool_t  reco_track_true_end_inTPC = 0;
  Bool_t  reco_track_true_end_in5cmTPC = 0;
  Bool_t  reco_track_true_end_inCCInclusiveTPC = 0;
  
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
  
  Bool_t  reco_track_daughter_true_vtx_inTPC = 0;
  Bool_t  reco_track_daughter_true_vtx_in5cmTPC = 0;
  Bool_t  reco_track_daughter_true_vtx_inCCInclusiveTPC = 0;
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

  //Int_t           reco_track_true_pdg = -9999;
  //Int_t           reco_track_daughter_true_pdg = -9999;


  outtree->Branch("true_nu_energy",&true_nu_energy,"true_nu_energy/F");
  outtree->Branch("true_kaon_p",&true_kaon_p,"true_kaon_p/F");
  outtree->Branch("true_kaon_ke",&true_kaon_ke,"true_kaon_ke/F");
  outtree->Branch("true_kaon_theta",&true_kaon_theta,"true_kaon_theta/F");
  outtree->Branch("true_kaon_costheta",&true_kaon_costheta,"true_kaon_costheta/F");
  outtree->Branch("true_kaon_phi",&true_kaon_phi,"true_kaon_phi/F");
  outtree->Branch("true_kaon_length",&true_kaon_length,"true_kaon_length/F");
  outtree->Branch("true_kaon_daughter_length",&true_kaon_daughter_length,"true_kaon_daughter_length/F");


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
  outtree->Branch("reco_track_vtx_distance",&reco_track_vtx_distance,"reco_track_vtx_distance/F");
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
  
  outtree->Branch("reco_track_true_vtx_inTPC",&reco_track_true_vtx_inTPC,"reco_track_true_vtx_inTPC/O");
  outtree->Branch("reco_track_true_vtx_in5cmTPC",&reco_track_true_vtx_in5cmTPC,"reco_track_true_vtx_in5cmTPC/O");
  outtree->Branch("reco_track_true_vtx_inCCInclusiveTPC",&reco_track_true_vtx_inCCInclusiveTPC,"reco_track_true_vtx_inCCInclusiveTPC/O");
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
  
  outtree->Branch("reco_track_daughter_true_vtx_inTPC",&reco_track_daughter_true_vtx_inTPC,"reco_track_daughter_true_vtx_inTPC/O");
  outtree->Branch("reco_track_daughter_true_vtx_in5cmTPC",&reco_track_daughter_true_vtx_in5cmTPC,"reco_track_daughter_true_vtx_in5cmTPC/O");
  outtree->Branch("reco_track_daughter_true_vtx_inCCInclusiveTPC",&reco_track_daughter_true_vtx_inCCInclusiveTPC,"reco_track_daughter_true_vtx_inCCInclusiveTPC/O");
  outtree->Branch("reco_track_daughter_true_end_inTPC",&reco_track_daughter_true_end_inTPC,"reco_track_daughter_true_end_inTPC/O");
  outtree->Branch("reco_track_daughter_true_end_in5cmTPC",&reco_track_daughter_true_end_in5cmTPC,"reco_track_daughter_true_end_in5cmTPC/O");
  outtree->Branch("reco_track_daughter_true_end_inCCInclusiveTPC",&reco_track_daughter_true_end_inCCInclusiveTPC,"reco_track_daughter_true_end_inCCInclusiveTPC/O");

  outtree->Branch("reco_track_kin0",&reco_track_kin0,"reco_track_kin0/F");
  outtree->Branch("reco_track_kin1",&reco_track_kin1,"reco_track_kin1/F");
  outtree->Branch("reco_track_kin2",&reco_track_kin2,"reco_track_kin2/F");

  outtree->Branch("reco_track_P_vtx",&reco_track_P_vtx,"reco_track_P_vtx/F");
  outtree->Branch("reco_track_P_str",&reco_track_P_str,"reco_track_P_str/F");
  outtree->Branch("reco_track_P_end",&reco_track_P_end,"reco_track_P_end/F");



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
  for (Long64_t jentry=0; jentry<nentries; jentry++) {
   
    event.GetEntry(jentry);
    if(nentries>=10){
      if (jentry%int(nentries/10.) == 0) {
	cout << int(100.*jentry/nentries) << " %" << endl;
      }
    }


    //if (event.reco_nu_cc_filter==false) continue;    
    //if (event.reco_nu_vtx_inCCInclusiveTPC==false) continue;

    /*
    if(event.true_nu_pdg==14 && event.true_nu_ccnc==0 && event.true_kaon_ke>=0 && event.true_nu_vtx_inCCInclusiveTPC==true){
      true_cut1++;
      if(event.true_kaon_end_inCCInclusiveTPC==true){
	true_cut2++;
	if(event.true_kaon_daughter_end_in5cmTPC==true){
	  true_cut3++;
	}
      }    
    }
    */

    //if(event.run==5025 || event.subrun==134 || event.event==6738) cout << "num_tracks: " << event.reco_ntracks << endl;

    // Loop over tracks 
    for (int itrk=0;itrk<event.reco_ntracks;itrk++) {

      //if(event.run==5025 || event.subrun==134 || event.event==6738){
      /*
	if(event.true_nu_pdg==14 && event.true_nu_ccnc==0 && event.true_kaon_ke>=0 && event.true_nu_vtx_inCCInclusiveTPC==true){
	  cout << "num_tracks: " << event.reco_ntracks << endl;
	  cout << itrk << "-th track pdg: " << event.reco_track_true_pdg[itrk] << endl;
	}
*/
	//}

      /*
      if(event.reco_track_true_pdg[itrk]==321 && ( event.reco_track_daughter_true_pdg[itrk][0]==-13 || event.reco_track_daughter_true_pdg[itrk][0]==211)  && event.true_nu_vtx_inCCInclusiveTPC==true){
	true_cut1++;
	if(event.true_kaon_end_inCCInclusiveTPC==true){
	  true_cut2++;
	  if(event.true_kaon_daughter_end_in5cmTPC==true){
	    true_cut3++;
	  }
	}    
      }
      */
      /*
      if(event.reco_track_true_pdg[itrk]==321 && ( event.reco_track_daughter_true_pdg[itrk][0]==-13 || event.reco_track_daughter_true_pdg[itrk][0]==211)  && event.reco_nu_vtx_inCCInclusiveTPC==true){
	true_cut1++;
	if(event.reco_track_end_inCCInclusiveTPC[itrk]==true){
	  true_cut2++;
	  if(event.reco_track_ndaughters[itrk]==1 && event.reco_track_daughter_end_in5cmTPC[itrk][0]==true){
	    true_cut3++;
	  }
	}    
      }
      */

      /*
      if(event.reco_track_nhits2[itrk]>0){
	if(event.reco_track_MIP_pl2[itrk]>0.06) continue;
      }else{
	if(event.reco_track_nhits0[itrk]>event.reco_track_nhits1[itrk]){
	  if(event.reco_track_MIP_pl0[itrk]>0.06) continue;
	}
	else if(event.reco_track_MIP_pl1[itrk]>0.06) continue;
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
	if(event.true_nu_pdg==14 && event.true_nu_ccnc==0 && event.true_kaon_ke>=0 && event.true_nu_vtx_inCCInclusiveTPC==true && event.true_kaon_end_inCCInclusiveTPC==1 && event.true_kaon_daughter_end_in5cmTPC==1 && event.reco_track_kin2[itrk]<1 && event.reco_track_true_pdg[itrk]==321){
	  cout << "num_tracks: " << event.reco_ntracks << ", true kaon ke" << event.true_kaon_ke << endl;
	  cout << itrk << "-th track pdg: " << event.reco_track_true_pdg[itrk] << endl;
	  cout << "reco energy: " << event.reco_track_kin2[itrk] << " " << event.reco_track_kin0[itrk] << " " << event.reco_track_kin1[itrk] <<endl;
	  cout << "reco track length: " << event.reco_track_length[itrk] <<endl;
	  }
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
      reco_track_nhits0 = event.reco_track_nhits0[itrk];
      reco_track_nhits1 = event.reco_track_nhits1[itrk];
      reco_track_nhits2 = event.reco_track_nhits2[itrk];
      
      reco_track_distance = event.reco_track_distance[itrk];
      reco_track_vtx_distance = event.reco_track_vtx_distance[itrk];
      reco_track_length = event.reco_track_length[itrk];
      reco_track_theta = event.reco_track_theta[itrk];
      reco_track_phi = event.reco_track_phi[itrk];
      
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
      
      reco_track_daughter_vtx_inTPC = event.reco_track_daughter_vtx_inTPC[itrk][0];
      reco_track_daughter_vtx_in5cmTPC = event.reco_track_daughter_vtx_in5cmTPC[itrk][0];
      reco_track_daughter_vtx_inCCInclusiveTPC = event.reco_track_daughter_vtx_inCCInclusiveTPC[itrk][0];
      reco_track_daughter_end_inTPC = event.reco_track_daughter_end_inTPC[itrk][0];
      reco_track_daughter_end_in5cmTPC = event.reco_track_daughter_end_in5cmTPC[itrk][0];
      reco_track_daughter_end_inCCInclusiveTPC = event.reco_track_daughter_end_inCCInclusiveTPC[itrk][0];

      reco_track_kin0 = event.reco_track_kin0[itrk];
      reco_track_kin1 = event.reco_track_kin1[itrk];
      reco_track_kin2 = event.reco_track_kin2[itrk];

      reco_track_P_vtx = event.reco_track_P_vtx[itrk];
      reco_track_P_str = event.reco_track_P_str[itrk];
      reco_track_P_end = event.reco_track_P_end[itrk];


      
      outtree->Fill();

    }//end loop over tracks

  }//tree loop

  cout << true_cut1 << " " << true_cut2 << " " << true_cut3 << endl;

  outfile->Write();
  outfile->Close();
  delete outfile;
  cout << "process end" << endl;
}

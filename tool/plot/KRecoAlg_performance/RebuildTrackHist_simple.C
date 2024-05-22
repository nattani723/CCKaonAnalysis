#include "RebuildTrackHist_simple.h"

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

void RebuildTrackHist_simple()
{
  //RebuildTrackHist("/exp/uboone/app/users/taniuchi/KaonAna/KaonAnlysis/Ana/track_tuple/refine_debug_2.root", "test2.pdf", "3pl");
  //RebuildTrackHist("/uboone/data/users/taniuchi/pandora_alg/ana/scan_fhc_run1_assok_match_roi20_debug6_max15_initial101_lsdis15_spineall_nospine_discon075_daughter40_lscon_ls_open23_peak3_min5_closest8_final50_prod_tracktuple.root", "test2.pdf", "3pl", "All", true);
  RebuildTrackHist_simple("/exp/uboone/app/users/taniuchi/51_pandora//CCKaonAnalysis/tool/track_tuple/rootfile/test.root", "a.pdf", "3pl", "IsK", true);

}

void RebuildTrackHist_simple(TString input_name, TString output_name, TString pl, TString mode, bool IsHybrid)
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

  GeneratePlots(f, pl, mode, IsHybrid, c, output_name);
  
  c->Print(Form("%s]", output_name.Data()));
  //c->Print(Form("%s]", output_name.Data()));

}

void GeneratePlots(TFile *f, TString pl, TString mode, bool IsHybrid, TCanvas* &c, TString output_name)
{

  TTree * t;

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

    if(reco_track_true_pdg!=321) continue;
    FillTrackLength();
    FillRebuildTrackLength();
    
  }

  AddStackHistos();
  AddLegend();  
  DrawHistos(c, output_name);

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

  cout << "reco_old_true_length_mu: " << reco_old_true_length_mu << endl;
  cout << "reco_old_true_length_pi: " << reco_old_true_length_pi << endl;
  cout << "reco_true_length_mu: " << reco_true_length_mu << endl;
  cout << "reco_true_length_pi: " << reco_true_length_pi << endl;

}


void LoadTree(TFile *f, TString pl, TTree * &t){

  TString fname(f->GetName());

  //TTree * t;
  if(fname.Contains("TMVA")){
    t = (TTree*) f->Get("dataset_tree325_node4_depth4_beta60_frac12_ncut5_addspec/TestTree");
  }else{
    t = (TTree*) f->Get("CCKaonTracks");
  }

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

  t->SetBranchAddress("n_recoRebDauTracks", &n_recoRebDauTracks);
  t->SetBranchAddress("rebdautrack_length", &rebdautrack_length);
  t->SetBranchAddress("rebdautracktrue_length", &rebdautracktrue_length);
  t->SetBranchAddress("rebdautracktruedir_length", &rebdautracktruedir_length);
  t->SetBranchAddress("rebdautrack_pdg", &rebdautrack_pdg);
  t->SetBranchAddress("best_peak_x", &best_peak_x);
  t->SetBranchAddress("best_peak_y", &best_peak_y);
  t->SetBranchAddress("best_peak_z", &best_peak_z);
  t->SetBranchAddress("best_peak_x_true", &best_peak_x_true);
  t->SetBranchAddress("best_peak_y_true", &best_peak_y_true);
  t->SetBranchAddress("best_peak_z_true", &best_peak_z_true);
  t->SetBranchAddress("true_dau_muon_end_x", &true_dau_muon_end_x);
  t->SetBranchAddress("true_dau_muon_end_y", &true_dau_muon_end_y);
  t->SetBranchAddress("true_dau_muon_end_z", &true_dau_muon_end_z);
  t->SetBranchAddress("true_dau_muon_start_x", &true_dau_muon_start_x);
  t->SetBranchAddress("true_dau_muon_start_y", &true_dau_muon_start_y);
  t->SetBranchAddress("true_dau_muon_start_z", &true_dau_muon_start_z);
  t->SetBranchAddress("true_dau_pip_end_x", &true_dau_pip_end_x);
  t->SetBranchAddress("true_dau_pip_end_y", &true_dau_pip_end_y);
  t->SetBranchAddress("true_dau_pip_end_z", &true_dau_pip_end_z);
  t->SetBranchAddress("true_dau_pip_start_x", &true_dau_pip_start_x);
  t->SetBranchAddress("true_dau_pip_start_y", &true_dau_pip_start_y);
  t->SetBranchAddress("true_dau_pip_start_z", &true_dau_pip_start_z);
  t->SetBranchAddress("true_dau_muon_theta", &true_dau_muon_theta);
  t->SetBranchAddress("true_dau_muon_phi", &true_dau_muon_phi);
  t->SetBranchAddress("true_dau_pip_theta", &true_dau_pip_theta);
  t->SetBranchAddress("true_dau_pip_phi", &true_dau_pip_phi);
  //t->SetBranchAddress("", &);
  //t->SetBranchAddress("", &);
  //t->SetBranchAddress("", &);
  
}

//void Draw(TFile *f, TString var, double scale, int dencut, bool print)
void SetHistos(){
  

  h_track_dau_ln_pr = new TH1D("track_dau_ln_pr", "; BDT Response; Number of Events", 50, 0, 100);
  h_track_dau_ln_pi = new TH1D("track_dau_ln_pi", "; BDT Response; Number of Events", 50, 0, 100);
  h_track_dau_ln_mu = new TH1D("track_dau_ln_mu", "; BDT Response; Number of Events", 50, 0, 100);
  h_track_dau_ln_sh = new TH1D("track_dau_ln_sh", "; BDT Response; Number of Events", 50, 0, 100);
  h_track_dau_ln_ot = new TH1D("track_dau_ln_ot", "; BDT Response; Number of Events", 50, 0, 100);
  

  h_track_dau_old_ln_pr = new TH1D("track_dau_old_ln_pr", "; BDT Response; Number of Events", 50, 0, 100);
  h_track_dau_old_ln_pi = new TH1D("track_dau_old_ln_pi", "; BDT Response; Number of Events", 50, 0, 100);
  h_track_dau_old_ln_mu = new TH1D("track_dau_old_ln_mu", "; BDT Response; Number of Events", 50, 0, 100);
  h_track_dau_old_ln_sh = new TH1D("track_dau_old_ln_sh", "; BDT Response; Number of Events", 50, 0, 100);
  h_track_dau_old_ln_ot = new TH1D("track_dau_old_ln_ot", "; BDT Response; Number of Events", 50, 0, 100);

  h_track_rebdau_ln_pr = new TH1D("track_rebdau_ln_pr", "; BDT Response; Number of Events", 50, 0, 100);
  h_track_rebdau_ln_pi = new TH1D("track_rebdau_ln_pi", "; BDT Response; Number of Events", 50, 0, 100);
  h_track_rebdau_ln_mu = new TH1D("track_rebdau_ln_mu", "; BDT Response; Number of Events", 50, 0, 100);
  h_track_rebdau_ln_sh = new TH1D("track_rebdau_ln_sh", "; BDT Response; Number of Events", 50, 0, 100);
  h_track_rebdau_ln_ot = new TH1D("track_rebdau_ln_ot", "; BDT Response; Number of Events", 50, 0, 100);

  h_track_rebdau_cheat_ln_pr = new TH1D("track_rebdau_cheat_ln_pr", "; BDT Response; Number of Events", 50, 0, 100);
  h_track_rebdau_cheat_ln_pi = new TH1D("track_rebdau_cheat_ln_pi", "; BDT Response; Number of Events", 50, 0, 100);
  h_track_rebdau_cheat_ln_mu = new TH1D("track_rebdau_cheat_ln_mu", "; BDT Response; Number of Events", 50, 0, 100);
  h_track_rebdau_cheat_ln_sh = new TH1D("track_rebdau_cheat_ln_sh", "; BDT Response; Number of Events", 50, 0, 100);
  h_track_rebdau_cheat_ln_ot = new TH1D("track_rebdau_cheat_ln_ot", "; BDT Response; Number of Events", 50, 0, 100);

  h_track_rebdau_cheat_dir_ln_pr = new TH1D("track_rebdau_cheat_dir_ln_pr", "; BDT Response; Number of Events", 50, 0, 100);
  h_track_rebdau_cheat_dir_ln_pi = new TH1D("track_rebdau_cheat_dir_ln_pi", "; BDT Response; Number of Events", 50, 0, 100);
  h_track_rebdau_cheat_dir_ln_mu = new TH1D("track_rebdau_cheat_dir_ln_mu", "; BDT Response; Number of Events", 50, 0, 100);
  h_track_rebdau_cheat_dir_ln_sh = new TH1D("track_rebdau_cheat_dir_ln_sh", "; BDT Response; Number of Events", 50, 0, 100);
  h_track_rebdau_cheat_dir_ln_ot = new TH1D("track_rebdau_cheat_dir_ln_ot", "; BDT Response; Number of Events", 50, 0, 100);


  h_peak_dir_pr = new TH1D("peak_dir_pr", "; true_pip_pin_theta; Number of Events", 30, 0, 3.14);
  h_peak_dir_pi = new TH1D("peak_dir_pi", "; true_pip_pin_theta; Number of Events", 30, 0, 3.14);
  h_peak_dir_mu = new TH1D("peak_dir_mu", "; true_pip_pin_theta; Number of Events", 30, 0, 3.14);
  h_peak_dir_sh = new TH1D("peak_dir_sh", "; true_pip_pin_theta; Number of Events", 30, 0, 3.14);
  h_peak_dir_ot = new TH1D("peak_dir_ot", "; true_pip_pin_theta; Number of Events", 30, 0, 3.14);

  h_peak_dir_cheat_pr = new TH1D("peak_dir_cheat_pr", "; true_pip_pin_theta; Number of Events", 30, 0, 3.14);
  h_peak_dir_cheat_pi = new TH1D("peak_dir_cheat_pi", "; true_pip_pin_theta; Number of Events", 30, 0, 3.14);
  h_peak_dir_cheat_mu = new TH1D("peak_dir_cheat_mu", "; true_pip_pin_theta; Number of Events", 30, 0, 3.14);
  h_peak_dir_cheat_sh = new TH1D("peak_dir_cheat_sh", "; true_pip_pin_theta; Number of Events", 30, 0, 3.14);
  h_peak_dir_cheat_ot = new TH1D("peak_dir_cheat_ot", "; true_pip_pin_theta; Number of Events", 30, 0, 3.14);


  h_truek_trkln_chi2ka = new TH2D("h_truek_trkln_chi2ka", "Track length vs #chi^{2}_{K};  #chi^{2}_{K}; Track length", 50, 0 , 50, 50, 0, 100);

  h_reco_track_length = new TH1D("h_reco_track_length", "; reco_track_length; Number of Events", 50, 0, 50);
  h_reco_track_daughter_distance = new TH1D("h_reco_track_daughter_distance", "; reco_track_daughter_distance; Number of Events", 50, 0, 50);
  h_reco_track_daughter_vtx_distance = new TH1D(" h_reco_track_daughter_vtx_distance", ";  reco_track_daughter_vtx_distance; Number of Events", 50, 0, 50);


}

void SetHistosStyle(){
  
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

  h_track_rebdau_ln_pr->SetLineColor(kRed);
  h_track_rebdau_ln_pi->SetLineColor(TColor::GetColorDark(kGreen));
  h_track_rebdau_ln_mu->SetLineColor(kCyan); 
  h_track_rebdau_ln_sh->SetLineColor(kMagenta);
  h_track_rebdau_ln_ot->SetLineColor(kBlack);
  h_track_rebdau_ln_pr->SetLineWidth(2); 
  h_track_rebdau_ln_pi->SetLineWidth(3);
  h_track_rebdau_ln_mu->SetLineWidth(3);
  h_track_rebdau_ln_sh->SetLineWidth(2);
  h_track_rebdau_ln_ot->SetLineWidth(2);
  h_track_rebdau_ln_pi->SetFillColorAlpha(TColor::GetColorDark(kGreen), 0.5);
  h_track_rebdau_ln_mu->SetFillColorAlpha(kCyan, 0.3);

  h_track_rebdau_cheat_ln_pr->SetLineColor(kRed);
  h_track_rebdau_cheat_ln_pi->SetLineColor(TColor::GetColorDark(kGreen));
  h_track_rebdau_cheat_ln_mu->SetLineColor(kCyan); 
  h_track_rebdau_cheat_ln_sh->SetLineColor(kMagenta);
  h_track_rebdau_cheat_ln_ot->SetLineColor(kBlack);
  h_track_rebdau_cheat_ln_pr->SetLineWidth(2); 
  h_track_rebdau_cheat_ln_pi->SetLineWidth(3);
  h_track_rebdau_cheat_ln_mu->SetLineWidth(3);
  h_track_rebdau_cheat_ln_sh->SetLineWidth(2);
  h_track_rebdau_cheat_ln_ot->SetLineWidth(2);
  h_track_rebdau_cheat_ln_pi->SetFillColorAlpha(TColor::GetColorDark(kGreen), 0.5);
  h_track_rebdau_cheat_ln_mu->SetFillColorAlpha(kCyan, 0.3);

  h_track_rebdau_cheat_dir_ln_pr->SetLineColor(kRed);
  h_track_rebdau_cheat_dir_ln_pi->SetLineColor(TColor::GetColorDark(kGreen));
  h_track_rebdau_cheat_dir_ln_mu->SetLineColor(kCyan); 
  h_track_rebdau_cheat_dir_ln_sh->SetLineColor(kMagenta);
  h_track_rebdau_cheat_dir_ln_ot->SetLineColor(kBlack);
  h_track_rebdau_cheat_dir_ln_pr->SetLineWidth(2); 
  h_track_rebdau_cheat_dir_ln_pi->SetLineWidth(3);
  h_track_rebdau_cheat_dir_ln_mu->SetLineWidth(3);
  h_track_rebdau_cheat_dir_ln_sh->SetLineWidth(2);
  h_track_rebdau_cheat_dir_ln_ot->SetLineWidth(2);
  h_track_rebdau_cheat_dir_ln_pi->SetFillColorAlpha(TColor::GetColorDark(kGreen), 0.5);
  h_track_rebdau_cheat_dir_ln_mu->SetFillColorAlpha(kCyan, 0.3);

  h_peak_dir_pr->SetLineColor(kRed);
  h_peak_dir_pi->SetLineColor(TColor::GetColorDark(kGreen));
  h_peak_dir_mu->SetLineColor(kCyan); 
  h_peak_dir_sh->SetLineColor(kMagenta);
  h_peak_dir_ot->SetLineColor(kBlack);
  h_peak_dir_pr->SetLineWidth(2); 
  h_peak_dir_pi->SetLineWidth(3);
  h_peak_dir_mu->SetLineWidth(3);
  h_peak_dir_sh->SetLineWidth(2);
  h_peak_dir_ot->SetLineWidth(2);
  h_peak_dir_pi->SetFillColorAlpha(TColor::GetColorDark(kGreen), 0.5);
  h_peak_dir_mu->SetFillColorAlpha(kCyan, 0.3);

  h_peak_dir_cheat_pr->SetLineColor(kRed);
  h_peak_dir_cheat_pi->SetLineColor(TColor::GetColorDark(kGreen));
  h_peak_dir_cheat_mu->SetLineColor(kCyan); 
  h_peak_dir_cheat_sh->SetLineColor(kMagenta);
  h_peak_dir_cheat_ot->SetLineColor(kBlack);
  h_peak_dir_cheat_pr->SetLineWidth(2); 
  h_peak_dir_cheat_pi->SetLineWidth(3);
  h_peak_dir_cheat_mu->SetLineWidth(3);
  h_peak_dir_cheat_sh->SetLineWidth(2);
  h_peak_dir_cheat_ot->SetLineWidth(2);
  h_peak_dir_cheat_pi->SetFillColorAlpha(TColor::GetColorDark(kGreen), 0.5);
  h_peak_dir_cheat_mu->SetFillColorAlpha(kCyan, 0.3);

  /*
  ->SetLineColor(kRed);
  ->SetLineColor(TColor::GetColorDark(kGreen));
  ->SetLineColor(kCyan); 
  ->SetLineColor(kMagenta);
  ->SetLineColor(kBlack);
  ->SetLineWidth(2); 
  ->SetLineWidth(3);
  ->SetLineWidth(3);
  ->SetLineWidth(2);
  ->SetLineWidth(2);
  ->SetFillColorAlpha(TColor::GetColorDark(kGreen), 0.5);
  ->SetFillColorAlpha(kCyan, 0.3);
  */
}


void FillHybridTrackLength(){
  
  if(reco_track_daughter_old_length>40){
    if(reco_track_daughter_old_true_pdg==2212)
      h_track_dau_ln_pr->Fill(reco_track_daughter_old_length);
    else if(reco_track_daughter_old_true_pdg==-13)
      h_track_dau_ln_mu->Fill(reco_track_daughter_old_length);
    else if(reco_track_daughter_old_true_pdg==211)
      h_track_dau_ln_pi->Fill(reco_track_daughter_old_length);  
    else if(reco_track_daughter_old_true_pdg==11 || reco_track_daughter_old_true_pdg==-11 || reco_track_daughter_old_true_pdg==22)
      h_track_dau_ln_sh->Fill(reco_track_daughter_old_length);
    else if(reco_track_daughter_old_true_pdg!=-9999)
      h_track_dau_ln_ot->Fill(reco_track_daughter_old_length);

    if(reco_track_true_pdg==321 && (reco_track_daughter_old_true_pdg==211 && std::abs(reco_track_daughter_old_length-true_dau_pip_length)<0.2*true_dau_pip_length)) reco_true_length_pi++;
    if(reco_track_true_pdg==321 && (reco_track_daughter_old_true_pdg==-13 && std::abs(reco_track_daughter_old_length-true_dau_muon_length)<0.2*true_dau_muon_length)) reco_true_length_mu++;

  }
  else if(reco_track_daughter_old_length<40){
    
    if(reco_track_true_pdg==321 && (reco_track_daughter_true_pdg==211 && std::abs(reco_track_daughter_length-true_dau_pip_length)<0.2*true_dau_pip_length)) reco_true_length_pi++;
    if(reco_track_true_pdg==321 && (reco_track_daughter_true_pdg==-13 && std::abs(reco_track_daughter_length-true_dau_muon_length)<0.2*true_dau_muon_length)) reco_true_length_mu++;

    if(reco_track_daughter_true_pdg==2212){
      h_track_dau_ln_pr->Fill(reco_track_daughter_length);
    }
    //else if(reco_track_daughter_true_pdg==-13){
    else if( (reco_track_daughter_true_pdg==-13 || reco_track_daughter_true_pdg==13) ){
      h_track_dau_ln_mu->Fill(reco_track_daughter_length);
    }
    else if(reco_track_daughter_true_pdg==211){
      h_track_dau_ln_pi->Fill(reco_track_daughter_length);
    }
    else if(reco_track_daughter_true_pdg==11 || reco_track_daughter_true_pdg==-11 || reco_track_daughter_true_pdg==22){
      h_track_dau_ln_sh->Fill(reco_track_daughter_length);
    }
    else if(reco_track_daughter_true_pdg!=-9999){
      h_track_dau_ln_ot->Fill(reco_track_daughter_length);
    }
  }
  
}


void FillOldTrackLength(){

  if(reco_track_daughter_old_true_pdg==2212){
    h_track_dau_old_ln_pr->Fill(reco_track_daughter_old_length);
  }
  else if(reco_track_daughter_old_true_pdg==-13){
    h_track_dau_old_ln_mu->Fill(reco_track_daughter_old_length);
  }
  else if(reco_track_daughter_old_true_pdg==211){
    h_track_dau_old_ln_pi->Fill(reco_track_daughter_old_length);
  }
  else if(reco_track_daughter_old_true_pdg==11 || reco_track_daughter_old_true_pdg==-11 || reco_track_daughter_old_true_pdg==22){
    h_track_dau_old_ln_sh->Fill(reco_track_daughter_old_length);
  }
  else if(reco_track_daughter_old_true_pdg!=-9999){
    h_track_dau_old_ln_ot->Fill(reco_track_daughter_old_length);
  }

  if(reco_track_true_pdg==321 && (reco_track_daughter_old_true_pdg==211 && std::abs(reco_track_daughter_old_length-true_dau_pip_length)<0.2*true_dau_pip_length)) reco_old_true_length_pi++;
  if(reco_track_true_pdg==321 && (reco_track_daughter_old_true_pdg==-13 && std::abs(reco_track_daughter_old_length-true_dau_muon_length)<0.2*true_dau_muon_length)) reco_old_true_length_mu++;

  
}

void FillRebuildTrackLength(){ 

  //cout << "rebdautrack_pdg: " << rebdautrack_pdg << endl;
  //cout << "rebdautrack_length: " << rebdautrack_length << endl;

  if(true_kaon_end_process==0){
    Double_t true_dau_muon_dir_x = true_dau_muon_end_x - true_dau_muon_start_x;
    Double_t true_dau_muon_dir_y = true_dau_muon_end_y - true_dau_muon_start_y;
    Double_t true_dau_muon_dir_z = true_dau_muon_end_z - true_dau_muon_start_z;
    //true_dau_muon_dir.SetXYZ(true_dau_muon_dir_x, true_dau_muon_dir_y, true_dau_muon_dir_z);
    true_dau_dir.SetMagThetaPhi(1, true_dau_muon_theta, true_dau_muon_phi);
    cheat_dir.SetXYZ(best_peak_x_true, best_peak_y_true, best_peak_z_true);
    reco_dir.SetXYZ(best_peak_x, best_peak_y, best_peak_z);
    //cout << "true_dau_muon_dirx: " << true_dau_muon_dir_x << " " << true_dau_muon_dir_y << " " << true_dau_muon_dir_z << endl;
    //cout << "best_peak_x, y, z: " << best_peak_x << " " << best_peak_y << " " << best_peak_z << endl;
    //cout << "best_peak_x_true, y, z: " << best_peak_x_true << " " << best_peak_y_true << " " << best_peak_z_true <<endl;
  }
  if(true_kaon_end_process==1){
    Double_t true_dau_pip_dir_x = true_dau_pip_end_x - true_dau_pip_start_x;
    Double_t true_dau_pip_dir_y = true_dau_pip_end_y - true_dau_pip_start_y;
    Double_t true_dau_pip_dir_z = true_dau_pip_end_z - true_dau_pip_start_z;
    true_dau_dir.SetXYZ(true_dau_pip_dir_x, true_dau_pip_dir_y, true_dau_pip_dir_z);
    //true_dau_pip_dir.SetMagThetaPhi(1, event.true_dau_pip_theta, event.true_dau_pip_phi);
    cheat_dir.SetXYZ(best_peak_x_true, best_peak_y_true, best_peak_z_true);
    reco_dir.SetXYZ(best_peak_x, best_peak_y, best_peak_z);
  }


  if(true_kaon_end_process==0 || true_kaon_end_process==1){
    //cout << "true_dau_dir.Angle(reco_dir): " << true_dau_dir.Angle(reco_dir) << endl;
    //cout << "true_dau_dir.Angle(cheat_dir): " << true_dau_dir.Angle(cheat_dir) << endl;
  }

  if(rebdautrack_pdg==2212){
    h_track_rebdau_ln_pr->Fill(rebdautrack_length);
    h_track_rebdau_cheat_ln_pr->Fill(rebdautracktrue_length);
    h_track_rebdau_cheat_dir_ln_pr->Fill(rebdautracktruedir_length);

    if(true_kaon_end_process==0 || true_kaon_end_process==1) { 
      h_peak_dir_pr->Fill(true_dau_dir.Angle(reco_dir));
      h_peak_dir_cheat_pr->Fill(true_dau_dir.Angle(cheat_dir));
    }
  }
  else if(rebdautrack_pdg==-13){
    h_track_rebdau_ln_mu->Fill(rebdautrack_length);
    h_track_rebdau_cheat_ln_mu->Fill(rebdautracktrue_length);
    h_track_rebdau_cheat_dir_ln_mu->Fill(rebdautracktruedir_length);

    if(true_kaon_end_process==0 || true_kaon_end_process==1) { 
      h_peak_dir_mu->Fill(true_dau_dir.Angle(reco_dir));
      h_peak_dir_cheat_mu->Fill(true_dau_dir.Angle(cheat_dir));
    }
  }
  else if(rebdautrack_pdg==211){
    h_track_rebdau_ln_pi->Fill(rebdautrack_length);
    h_track_rebdau_cheat_ln_pi->Fill(rebdautracktrue_length);
    h_track_rebdau_cheat_dir_ln_pi->Fill(rebdautracktruedir_length);

    if(true_kaon_end_process==0 || true_kaon_end_process==1) { 
      h_peak_dir_pi->Fill(true_dau_dir.Angle(reco_dir));
      h_peak_dir_cheat_pi->Fill(true_dau_dir.Angle(cheat_dir));
    }
  }
  else if(rebdautrack_pdg==22 || rebdautrack_pdg==11 || rebdautrack_pdg==-11 || rebdautrack_pdg==111){
    h_track_rebdau_ln_sh->Fill(rebdautrack_length);
    h_track_rebdau_cheat_ln_sh->Fill(rebdautracktrue_length);
    h_track_rebdau_cheat_dir_ln_sh->Fill(rebdautracktruedir_length);

    if(true_kaon_end_process==0 || true_kaon_end_process==1) { 
      h_peak_dir_sh->Fill(true_dau_dir.Angle(reco_dir));
      h_peak_dir_cheat_sh->Fill(true_dau_dir.Angle(cheat_dir));
    }
  }
  else{
    h_track_rebdau_ln_ot->Fill(rebdautrack_length);
    h_track_rebdau_cheat_ln_ot->Fill(rebdautracktrue_length);
    h_track_rebdau_cheat_dir_ln_ot->Fill(rebdautracktruedir_length);

    if(true_kaon_end_process==0 || true_kaon_end_process==1) { 
      h_peak_dir_ot->Fill(true_dau_dir.Angle(reco_dir));
      h_peak_dir_cheat_ot->Fill(true_dau_dir.Angle(cheat_dir));
    }
  }

}

void FillTrackLength(){//need to update module

    if(reco_track_true_pdg==321 && (reco_track_daughter_true_pdg==211 && std::abs(reco_track_daughter_length-true_dau_pip_length)<0.2*true_dau_pip_length)) reco_true_length_pi++;
    if(reco_track_true_pdg==321 && (reco_track_daughter_true_pdg==-13 && std::abs(reco_track_daughter_length-true_dau_muon_length)<0.2*true_dau_muon_length)) reco_true_length_mu++;

  if(reco_track_daughter_true_pdg==2212){
    h_track_dau_ln_pr->Fill(reco_track_daughter_length);
  }
  else if(reco_track_daughter_true_pdg==-13){
    h_track_dau_ln_mu->Fill(reco_track_daughter_length);
  }
  else if(reco_track_daughter_true_pdg==211){
    h_track_dau_ln_pi->Fill(reco_track_daughter_length);
  }
  else if(reco_track_daughter_true_pdg==11 || reco_track_daughter_true_pdg==-11 || reco_track_daughter_true_pdg==22){
    h_track_dau_ln_sh->Fill(reco_track_daughter_length);
  }
  else if(reco_track_daughter_true_pdg!=-9999){
    h_track_dau_ln_ot->Fill(reco_track_daughter_length);
  }
  
}


void FillPrimaryTrack(){

    if(reco_track_true_pdg==321){
    }
    else if(reco_track_true_pdg==13){
    }
    else if(reco_track_true_pdg==211){
    }
    else if(reco_track_true_pdg==2212){
    }
    else{
    }
    
    h_reco_track_length->Fill(reco_track_length);
    h_reco_track_daughter_distance->Fill(reco_track_daughter_distance);
    h_reco_track_daughter_vtx_distance->Fill(reco_track_daughter_vtx_distance);
    
}

void AddStackHistos(){


  s_trkln_dau->Add(h_track_dau_ln_pi);
  s_trkln_dau->Add(h_track_dau_ln_mu);
  s_trkln_dau->Add(h_track_dau_ln_sh);
  s_trkln_dau->Add(h_track_dau_ln_pr);
  s_trkln_dau->Add(h_track_dau_ln_ot);

  s_trkln_dau_old->Add(h_track_dau_old_ln_pi);
  s_trkln_dau_old->Add(h_track_dau_old_ln_mu);
  s_trkln_dau_old->Add(h_track_dau_old_ln_sh);
  s_trkln_dau_old->Add(h_track_dau_old_ln_pr);
  s_trkln_dau_old->Add(h_track_dau_old_ln_ot);


  s_trkln_rebdau->Add(h_track_rebdau_ln_pr);
  s_trkln_rebdau->Add(h_track_rebdau_ln_pi);
  s_trkln_rebdau->Add(h_track_rebdau_ln_mu);
  s_trkln_rebdau->Add(h_track_rebdau_ln_sh);
  s_trkln_rebdau->Add(h_track_rebdau_ln_ot);

  s_trkln_rebdau_cheat->Add(h_track_rebdau_cheat_ln_pr);
  s_trkln_rebdau_cheat->Add(h_track_rebdau_cheat_ln_pi);
  s_trkln_rebdau_cheat->Add(h_track_rebdau_cheat_ln_mu);
  s_trkln_rebdau_cheat->Add(h_track_rebdau_cheat_ln_sh);
  s_trkln_rebdau_cheat->Add(h_track_rebdau_cheat_ln_ot);

  s_trkln_rebdau_cheat_dir->Add(h_track_rebdau_cheat_dir_ln_pr);
  s_trkln_rebdau_cheat_dir->Add(h_track_rebdau_cheat_dir_ln_pi);
  s_trkln_rebdau_cheat_dir->Add(h_track_rebdau_cheat_dir_ln_mu);
  s_trkln_rebdau_cheat_dir->Add(h_track_rebdau_cheat_dir_ln_sh);
  s_trkln_rebdau_cheat_dir->Add(h_track_rebdau_cheat_dir_ln_ot);

  s_peak_dir->Add(h_peak_dir_pr);
  s_peak_dir->Add(h_peak_dir_pi);
  s_peak_dir->Add(h_peak_dir_mu);
  s_peak_dir->Add(h_peak_dir_sh);
  s_peak_dir->Add(h_peak_dir_ot);

  s_peak_dir_cheat->Add(h_peak_dir_cheat_pr);
  s_peak_dir_cheat->Add(h_peak_dir_cheat_pi);
  s_peak_dir_cheat->Add(h_peak_dir_cheat_mu);
  s_peak_dir_cheat->Add(h_peak_dir_cheat_sh);
  s_peak_dir_cheat->Add(h_peak_dir_cheat_ot);

}

void AddLegend(){
  /*
  l_ka = new TLegend(0.75,0.65,0.95,0.95);
  l_ka->AddEntry(h_track_chi2ka_ka, "True K^{+}"  , "f");
  l_ka->AddEntry(h_track_chi2ka_pr, "True p" , "f");
  l_ka->AddEntry(h_track_chi2ka_pi, "True #pi^{+}"   , "f");
  l_ka->AddEntry(h_track_chi2ka_mu, "True #mu^{-}"   , "f");
  l_ka->AddEntry(h_track_chi2ka_ot, "Others"   , "f");
  */

  l_pr_dau_ln = new TLegend(0.75,0.65,0.95,0.95);
  l_pr_dau_ln->AddEntry(h_track_dau_ln_pr, "True p" , "f");
  l_pr_dau_ln->AddEntry(h_track_dau_ln_pi, "True #pi^{+}"   , "f");
  l_pr_dau_ln->AddEntry(h_track_dau_ln_mu, "True #mu^{+}"   , "f");
  l_pr_dau_ln->AddEntry(h_track_dau_ln_sh, "True shower"   , "f");
  l_pr_dau_ln->AddEntry(h_track_dau_ln_ot, "Others"   , "f");

  h_reco_track_daughter_vtx_distance->SetLineColor(kRed);
  h_reco_track_daughter_distance->SetLineColor(kBlue);
  h_reco_track_length->SetLineColor(kBlack);

}

void DrawHistos(TCanvas* &c,TString output_name){
  
  h_reco_track_daughter_vtx_distance->Draw();
  h_reco_track_daughter_distance->Draw("same");
  h_reco_track_length->Draw("same");
  c->Print(output_name);
  
  s_trkln_dau->SetMaximum(200.);
  s_trkln_dau_old->SetMaximum(200.); 
  s_trkln_dau->Draw("nostack");
  l_pr_dau_ln->Draw();
  c->Print(output_name);
  
  s_trkln_dau_old->Draw("nostack");
  l_pr_dau_ln->Draw();
  c->Print(output_name);

  s_trkln_rebdau->Draw("nostack");
  l_pr_dau_ln->Draw();
  c->Print(output_name);

  s_trkln_rebdau_cheat->Draw("nostack");
  l_pr_dau_ln->Draw();
  c->Print(output_name);

  s_trkln_rebdau_cheat_dir->Draw("nostack");
  l_pr_dau_ln->Draw();
  c->Print(output_name);

  s_peak_dir->Draw("nostack");
  l_pr_dau_ln->Draw();
  c->Print(output_name);

  s_peak_dir_cheat->Draw("nostack");
  l_pr_dau_ln->Draw();
  c->Print(output_name);


  
}

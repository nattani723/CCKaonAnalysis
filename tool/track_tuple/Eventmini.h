//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sun Jan 10 23:24:45 2021 by ROOT version 6.12/06
// from TTree Event/Event Tree from Reco
// found on file: /nashome/a/arturo/uboone/uboonedata/uboonecode_v08_00_00_32/CCKaonFilter/cckaonfilter_ana_cck_v7.root
//////////////////////////////////////////////////////////

#ifndef Eventmini_h
#define Eventmini_h

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
   Float_t         reco_nu_vtx_x;
   Float_t         reco_nu_vtx_y;
   Float_t         reco_nu_vtx_z;
   Bool_t          reco_nu_vtx_inTPC;
   Bool_t          reco_nu_vtx_in5cmTPC;
   Bool_t          reco_nu_vtx_inCCInclusiveTPC;
   Int_t           reco_nu_ndaughters;
   Int_t           reco_ntracks;

   Float_t         reco_track_end_x[20];
   Float_t         reco_track_end_y[20];
   Float_t         reco_track_end_z[20];

   Int_t           n_recoRebDauTracks[20];
   Float_t         rebdautrack_length[20][10];
   Float_t         rebdautrack_pdg[20][10];
   Float_t         best_peak_x[20][10];
   Float_t         best_peak_y[20][10];
   Float_t         best_peak_z[20][10];

   /*
   Float_t         rebdautracktrue_length[20];
   Float_t         rebdautracktruedir_length[20];
   Float_t         best_peak_x_true[20];
   Float_t         best_peak_y_true[20];
   Float_t         best_peak_z_true[20];
   */

   Float_t         true_dau_muon_end_x;
   Float_t         true_dau_muon_end_y;
   Float_t         true_dau_muon_end_z;
   Float_t         true_dau_muon_start_x;
   Float_t         true_dau_muon_start_y;
   Float_t         true_dau_muon_start_z;
   Float_t         true_dau_pip_end_x;
   Float_t         true_dau_pip_end_y;
   Float_t         true_dau_pip_end_z;
   Float_t         true_dau_pip_start_x;
   Float_t         true_dau_pip_start_y;
   Float_t         true_dau_pip_start_z;
   Float_t         true_dau_muon_theta;
   Float_t         true_dau_muon_phi;
   Float_t         true_dau_pip_theta;
   Float_t         true_dau_pip_phi;



   // List of branches
   TBranch        *b_event;
   TBranch        *b_run;
   TBranch        *b_surbrun;

   TBranch        *b_true_nu_energy;
   TBranch        *b_true_nu_pdg;
   TBranch        *b_true_nu_mode;
   TBranch        *b_true_nu_ccnc;
   TBranch        *b_true_nu_vtx_x;
   TBranch        *b_true_nu_vtx_y;
   TBranch        *b_true_nu_vtx_z;
   TBranch        *b_true_nu_vtx_inTPC;
   TBranch        *b_true_nu_vtx_in5cmTPC;
   TBranch        *b_true_nu_vtx_inCCInclusiveTPC;

   TBranch        *b_true_lepton_pdg;
   TBranch        *b_true_lepton_p;
   TBranch        *b_true_lepton_ke;
   TBranch        *b_true_lepton_theta;
   TBranch        *b_true_lepton_costheta;
   TBranch        *b_true_lepton_phi;

   TBranch        *b_true_nkaons;   //!
   TBranch        *b_true_kaon_length;   //!
   TBranch        *b_true_kaon_p;   //!
   TBranch        *b_true_kaon_ke;   //!
   TBranch        *b_true_kaon_theta;   //!
   TBranch        *b_true_kaon_costheta;   //!
   TBranch        *b_true_kaon_phi;   //!
   TBranch        *b_true_kaon_ccmuon_angle;   //!
   TBranch        *b_true_kaon_ccmuon_cosangle;   //!
   TBranch        *b_true_kaon_end_process;   //!
   TBranch        *b_true_kaon_end_ke;   //!
   TBranch        *b_true_kaon_end_x;   //!
   TBranch        *b_true_kaon_end_y;   //!
   TBranch        *b_true_kaon_end_z;   //!
   TBranch        *b_true_kaon_end_inTPC;   //!
   TBranch        *b_true_kaon_end_in5cmTPC;   //!
   TBranch        *b_true_kaon_end_inCCInclusiveTPC;   //!
   TBranch        *b_true_kaon_ndaughters;   //!
   TBranch        *b_true_kaon_ndaughters_decay;   //!
   TBranch        *b_true_kaon_ndaughters_inelastic;   //!

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
   TBranch        *b_reco_nu_vtx_x;   //!
   TBranch        *b_reco_nu_vtx_y;   //!
   TBranch        *b_reco_nu_vtx_z;   //!
   TBranch        *b_reco_nu_vtx_inTPC;   //!
   TBranch        *b_reco_nu_vtx_in5cmTPC;   //!
   TBranch        *b_reco_nu_vtx_inCCInclusiveTPC;   //!
   TBranch        *b_reco_nu_ndaughters;   //!
   TBranch        *b_reco_ntracks;   //!

   TBranch        *b_reco_track_end_x;
   TBranch        *b_reco_track_end_y;
   TBranch        *b_reco_track_end_z;

   TBranch        *b_n_recoRebDauTracks;
   TBranch        *b_rebdautrack_length;
   TBranch        *b_rebdautrack_pdg;
   TBranch        *b_best_peak_x;
   TBranch        *b_best_peak_y;
   TBranch        *b_best_peak_z;

   /*
   TBranch        *b_rebdautracktrue_length;
   TBranch        *b_rebdautracktruedir_length;
   TBranch        *b_best_peak_x_true;
   TBranch        *b_best_peak_y_true;
   TBranch        *b_best_peak_z_true;
   */
   
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

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("event", &event, &b_event);
   fChain->SetBranchAddress("run", &run, &b_run);
   fChain->SetBranchAddress("subrun", &subrun, &b_surbrun);

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

   fChain->SetBranchAddress("true_lepton_pdg", &true_lepton_pdg, &b_true_lepton_pdg);
   fChain->SetBranchAddress("true_lepton_p", &true_lepton_p, &b_true_lepton_p);
   fChain->SetBranchAddress("true_lepton_ke", &true_lepton_ke, &b_true_lepton_ke);
   fChain->SetBranchAddress("true_lepton_theta", &true_lepton_theta, &b_true_lepton_theta);
   fChain->SetBranchAddress("true_lepton_costheta", &true_lepton_costheta, &b_true_lepton_costheta);
   fChain->SetBranchAddress("true_lepton_phi", &true_lepton_phi, &b_true_lepton_phi);

   fChain->SetBranchAddress("true_nkaons", &true_nkaons, &b_true_nkaons);
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
   fChain->SetBranchAddress("true_kaon_end_inTPC", &true_kaon_end_inTPC, &b_true_kaon_end_inTPC);
   fChain->SetBranchAddress("true_kaon_end_in5cmTPC", &true_kaon_end_in5cmTPC, &b_true_kaon_end_in5cmTPC);
   fChain->SetBranchAddress("true_kaon_end_inCCInclusiveTPC", &true_kaon_end_inCCInclusiveTPC, &b_true_kaon_end_inCCInclusiveTPC);
   fChain->SetBranchAddress("true_kaon_ndaughters", &true_kaon_ndaughters, &b_true_kaon_ndaughters);
   fChain->SetBranchAddress("true_kaon_ndaughters_decay", &true_kaon_ndaughters_decay, &b_true_kaon_ndaughters_decay);
   fChain->SetBranchAddress("true_kaon_ndaughters_inelastic", &true_kaon_ndaughters_inelastic, &b_true_kaon_ndaughters_inelastic);

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

   
   fChain->SetBranchAddress("reco_nu_cc_filter", &reco_nu_cc_filter, &b_reco_nu_cc_filter);
   fChain->SetBranchAddress("reco_nu_vtx_x", &reco_nu_vtx_x, &b_reco_nu_vtx_x);
   fChain->SetBranchAddress("reco_nu_vtx_y", &reco_nu_vtx_y, &b_reco_nu_vtx_y);
   fChain->SetBranchAddress("reco_nu_vtx_z", &reco_nu_vtx_z, &b_reco_nu_vtx_z);
   fChain->SetBranchAddress("reco_nu_vtx_inTPC", &reco_nu_vtx_inTPC, &b_reco_nu_vtx_inTPC);
   fChain->SetBranchAddress("reco_nu_vtx_in5cmTPC", &reco_nu_vtx_in5cmTPC, &b_reco_nu_vtx_in5cmTPC);
   fChain->SetBranchAddress("reco_nu_vtx_inCCInclusiveTPC", &reco_nu_vtx_inCCInclusiveTPC, &b_reco_nu_vtx_inCCInclusiveTPC);
   fChain->SetBranchAddress("reco_nu_ndaughters", &reco_nu_ndaughters, &b_reco_nu_ndaughters);
   fChain->SetBranchAddress("reco_ntracks", &reco_ntracks, &b_reco_ntracks);

   fChain->SetBranchAddress("reco_track_end_x", &reco_track_end_x, &b_reco_track_end_x);
   fChain->SetBranchAddress("reco_track_end_y", &reco_track_end_y, &b_reco_track_end_y);
   fChain->SetBranchAddress("reco_track_end_z", &reco_track_end_z, &b_reco_track_end_z);

   fChain->SetBranchAddress("n_recoRebDauTracks", &n_recoRebDauTracks, &b_n_recoRebDauTracks);
   fChain->SetBranchAddress("rebdautrack_length", &rebdautrack_length, &b_rebdautrack_length);
   fChain->SetBranchAddress("rebdautrack_pdg", &rebdautrack_pdg, &b_rebdautrack_pdg);
   fChain->SetBranchAddress("best_peak_x", &best_peak_x, &b_best_peak_x);
   fChain->SetBranchAddress("best_peak_y", &best_peak_y, &b_best_peak_y);
   fChain->SetBranchAddress("best_peak_z", &best_peak_z, &b_best_peak_z);

   /*
   fChain->SetBranchAddress("rebdautracktrue_length", &rebdautracktrue_length, &b_rebdautracktrue_length);
   fChain->SetBranchAddress("rebdautracktruedir_length", &rebdautracktruedir_length, &b_rebdautracktruedir_length);

   fChain->SetBranchAddress("best_peak_x_true", &best_peak_x_true, &b_best_peak_x_true);
   fChain->SetBranchAddress("best_peak_y_true", &best_peak_y_true, &b_best_peak_y_true);
   fChain->SetBranchAddress("best_peak_z_true", &best_peak_z_true, &b_best_peak_z_true);
   */

   fChain->SetBranchAddress("true_dau_muon_end_x", &true_dau_muon_end_x, &b_true_dau_muon_end_x);
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

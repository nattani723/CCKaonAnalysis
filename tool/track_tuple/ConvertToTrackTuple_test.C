#define Event_cxx
#define plotcck_cxx
//#include "plotcck.h"
#include "Eventmini.h"

#include "TH1.h"
#include "TStopwatch.h"

#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

void Event::Loop() {};
//void plotcck::Loop(){};
void ConvertToTrackTuple_test(TString input_name, TString output_name);
//void precuts(TString s);
//vector <int> evt;


void ConvertToTrackTuple_test()
{

  TStopwatch clock;

  ConvertToTrackTuple_test("/exp/uboone/data/users/taniuchi/recoalg_testarea/assok_refined_KrecoAlg_debug_test3.root", "rootfile/test.root");

}


void ConvertToTrackTuple_test(TString input_name, TString output_name)
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

  Int_t         eventnum = -9999;
  Int_t         run = -9999;
  Int_t         subrun = -9999;
  Float_t true_dau_muon_end_x = -9999;
  Float_t true_dau_muon_start_x = -9999;


  outtree->Branch("eventnum", &eventnum, "eventnum/I"); 
  outtree->Branch("run", &run, "run/I"); 
  outtree->Branch("subrun", &subrun, "subrun/I"); 
  outtree->Branch("true_dau_muon_start_x",&true_dau_muon_start_x,"true_dau_muon_start_x/F");
  outtree->Branch("true_dau_muon_end_x",&true_dau_muon_end_x,"true_dau_muon_end_x/F");


  // Loop over tree
  Long64_t nentries = t->GetEntries();
  t->Draw("true_dau_muon_end_x");
  cout << "Tree entries " << nentries << endl;

  Event event(t);

  for (Long64_t jentry=0; jentry<100; jentry++){
    
    event.GetEntry(jentry);
    if(nentries>=10){
      if (jentry%int(nentries/10.) == 0) {
	cout << int(100.*jentry/nentries) << " %" << endl;
      }
    }

    cout << "true_dau_muon_end_x: " << event.true_dau_muon_end_x << endl; 
    cout << "true_dau_muon_start_x: " << event.true_dau_muon_start_x << endl; 

      eventnum = event.event;
      run = event.run;
      subrun = event.subrun;

      true_dau_muon_end_x = event.true_dau_muon_end_x;
      true_dau_muon_start_x = event.true_dau_muon_start_x;

      outtree->Fill();

  }//tree loop


  outfile->Write();
  outfile->Close();
  delete outfile;

}



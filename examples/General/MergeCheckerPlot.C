R__LOAD_LIBRARY($HYP_TOP/lib/libHyperon.so)
R__LOAD_LIBRARY($HYP_TOP/lib/libParticleDict.so)

#include "SelectionManager.h"
#include "EventAssembler.h"
#include "Cut.h"
#include "SelectionParameters.h"

#include "Parameters.h"
#include "SampleSets_Example.h"


int PDGToBin(int pdg) {
  switch (pdg) {
  case 321: return 1;  // K+
  case -13: return 2; // mu+
  case 211: return 3; // pi+
  case 2212: return 4; // proton
  case 11:  // e-
  case -11: // e+
  case 22:  return 5; // gamma (shower)
  default: return 6;  // Others
  }
}

std::string PDGLabel(int bin) {
  switch (bin) {
  case 1: return "K^{+}";
  case 2: return "#mu^{+}";
  case 3: return "#pi^{+}";
  case 4: return "proton";
  case 5: return "shower";
  case 6: return "Others";
  default: return "Invalid";
  }
}

// Initialize histograms in a map
void InitializeHistograms(std::map<std::string, TH1D*>& histograms) {
  std::vector<std::string> types = {"daughter", "rebdaughter", "shower"};
  for (const auto& type : types) {
    std::string name = "h_" + type;
    std::string title = ";" + type + " Track PDG; a.u.";
    histograms[name] = new TH1D(name.c_str(), title.c_str(), 6, 0, 6);
    histograms[name]->SetStats(0);
    for (int bin = 1; bin <= 6; ++bin) {
      histograms[name]->GetXaxis()->SetBinLabel(bin, PDGLabel(bin).c_str());
    }
  }
}

void AnalyzeIndividualTrack(const TVector3& PrimaryTrackEnd, const RecoParticle& DaughterTrack, TH1D* histogram, double maxDistance, int& nentry) {
  
  TVector3 DaughterTrackStart(DaughterTrack.X, DaughterTrack.Y, DaughterTrack.Z);
  if ((PrimaryTrackEnd - DaughterTrackStart).Mag() > maxDistance) return;

  //Fill straight forward
  /*
  int bin1 = PDGToBin(DaughterTrack.MergePDG_1st) - 1;
  if(DaughterTrack.MergePDG_1st!=-1) histogram->Fill(bin1);
  
  if (DaughterTrack.MergeEnergyPurity_2nd > 0.1) {
    int bin2 = PDGToBin(DaughterTrack.MergePDG_2nd) - 1;
    if(DaughterTrack.MergePDG_2nd!=-1) histogram->Fill(bin2);
  }

  if (DaughterTrack.MergeEnergyPurity_3rd > 0.1) {
    int bin3 = PDGToBin(DaughterTrack.MergePDG_3rd) - 1;
    if(DaughterTrack.MergePDG_3rd!=-1) histogram->Fill(bin3);
  }
  */

  ++nentry;

  int bin1 = PDGToBin(DaughterTrack.MergePDG_1st) - 1;
  if(DaughterTrack.MergePDG_1st!=-1) histogram->Fill(bin1, DaughterTrack.MergeEnergyPurity_1st);

  int bin2 = PDGToBin(DaughterTrack.MergePDG_2nd) - 1;
  if(DaughterTrack.MergePDG_2nd!=-1) histogram->Fill(bin2, DaughterTrack.MergeEnergyPurity_2nd);

  int bin3 = PDGToBin(DaughterTrack.MergePDG_3rd) - 1;
  if(DaughterTrack.MergePDG_3rd!=-1) histogram->Fill(bin3, DaughterTrack.MergeEnergyPurity_3rd);
  
}

void AnalyzeTracks(const Event& e, std::map<std::string, TH1D*>& histograms, int* nentry) {
  for (size_t i_tr = 0; i_tr < e.TrackPrimaryDaughters.size(); i_tr++) {
    RecoParticle PrimaryTrack = e.TrackPrimaryDaughters[i_tr];
    if (PrimaryTrack.TrackTruePDG != 321) continue; // Only interested in tracks with PDG == 321
    TVector3 PrimaryTrackEnd(PrimaryTrack.TrackEndX, PrimaryTrack.TrackEndY, PrimaryTrack.TrackEndZ);

    // Analyze daughter tracks
    for (size_t i_tr_dau = 0; i_tr_dau < e.TrackOthers.size(); i_tr_dau++) {
      AnalyzeIndividualTrack(PrimaryTrackEnd, e.TrackOthers[i_tr_dau], histograms["h_daughter"], 10, nentry[0]);
    }

    // Analyze shower daughters
    for (size_t i_sh = 0; i_sh < e.ShowerOthers.size(); i_sh++) {
      AnalyzeIndividualTrack(PrimaryTrackEnd, e.ShowerOthers[i_sh], histograms["h_shower"], 20, nentry[1]);
    }

    // Analyze rebuilt daughter tracks
    for (size_t i_tr_dau = 0; i_tr_dau < e.TrackRebuiltOthers.size(); i_tr_dau++) {
      AnalyzeIndividualTrack(PrimaryTrackEnd, e.TrackRebuiltOthers[i_tr_dau], histograms["h_rebdaughter"], 10, nentry[2]);
    }
  }

  int i=0;
  for(auto& pair : histograms){
    TH1D* hist = pair.second;
    hist->Scale(100/nentry[i]);
    i++;
  }

}

void PlotHistograms(const std::map<std::string, TH1D*>& histograms) {
  TCanvas* c = new TCanvas("c", "Canvas for Drawing Histograms", 800, 600);
  c->cd();

  for (const auto& entry : histograms) {
    TH1D* h = entry.second;  // Get the histogram pointer
    if (!h) continue;  // Skip if histogram pointer is null

    // Set histogram visual styles
    h->SetStats(0);  // Turn off the statistics box
    h->GetXaxis()->SetTitleFont(62);
    h->GetYaxis()->SetTitleFont(62);
    h->GetXaxis()->SetLabelFont(62);
    h->GetYaxis()->SetLabelFont(62);
    h->GetXaxis()->SetLabelSize(0.04);
    h->GetYaxis()->SetLabelSize(0.04);
    h->GetXaxis()->SetTitleOffset(1.0);
    h->GetYaxis()->SetTitleOffset(1.5);

    // Setting custom bin labels if required
    h->GetXaxis()->SetBinLabel(1, "K^{+}");
    h->GetXaxis()->SetBinLabel(2, "#mu^{+}");
    h->GetXaxis()->SetBinLabel(3, "#pi^{+}");
    h->GetXaxis()->SetBinLabel(4, "proton");
    h->GetXaxis()->SetBinLabel(5, "shower");
    h->GetXaxis()->SetBinLabel(6, "Others");

    // Draw the histogram
    h->Draw("HIST");

    // Update the canvas to reflect changes
    c->Modified();
    c->Update();

    // Save the canvas as a PDF or an image file
    std::string filename = "Plots/" + entry.first + ".pdf";
    c->Print(filename.c_str());

    // Optionally clear the canvas for the next histogram
    c->Clear();
  }

  // Clean up: Delete the canvas to free memory
  delete c;
}


void PlotHistograms(std::map<std::string, TH1D*>& histograms) {
  TCanvas* c1 = new TCanvas("c1", "Canvas for Drawing Histograms", 800, 600);
  for (const auto& hist : histograms) {
    c1->cd();
    hist.second->Draw();
    c1->Update();
    std::string filename = "Plots/" + hist.first + ".pdf";
    c1->Print(filename.c_str());
  }
  delete c1;
}

void MergeCheckerPlot(){
  
  double POT = 1.0e21; // POT to scale samples to
  std::map<std::string, TH1D*> histograms;
  int nentry[3] = {0,0,0};

  BuildTunes();
  SelectionParameters P = P_FHC_K_NOBDT_TEST;
  
  SampleNames.push_back("AssocKaon"); 
  SampleTypes.push_back("AssocKaon"); 
  SampleFiles.push_back("/exp/uboone/data/users/taniuchi/taniuchi/pandora_alg/ana/assok_refined_KrecoAlg_parameter8_ntuple.root");
  //SampleFiles.push_back("/exp/uboone/data/users/taniuchi/test/KaonTrees.root");
  //SampleFiles.push_back("/exp/uboone/data/users/taniuchi/ntuple_testarea/assok_KaonTrees.root");
  
  EventAssembler E;
  SelectionManager M(P);
  M.SetPOT(POT);

  InitializeHistograms(histograms);
  
  // Sample Loop
  for(size_t i_s=0;i_s<SampleNames.size();i_s++){
    
    E.SetFile(SampleFiles.at(i_s), "KAON");//2nd parameter is dummy
    
    if( SampleTypes.at(i_s) == "AssocKaon") M.AddSample("AssocKaon","AssocKaon",POT);
    //if(SampleTypes.at(i_s) != "EXT" && SampleTypes.at(i_s) != "Data") M.AddSample(SampleNames.at(i_s),SampleTypes.at(i_s),E.GetPOT());
    else if(SampleTypes.at(i_s) == "Data") M.AddSample(SampleNames.at(i_s),SampleTypes.at(i_s),Data_POT);
    else if(SampleTypes.at(i_s) == "EXT") M.AddSample(SampleNames.at(i_s),SampleTypes.at(i_s),EXT_POT);
    
    M.UseFluxWeight(false);
    M.UseGenWeight(false);
    
    // Event Loop
    for(int i=0;i<E.GetNEvents();i++){

      if(i % 10000 == 0) std::cout << i << "/" << E.GetNEvents() << std::endl;
      
      Event e = E.GetEvent(i);
      
      M.SetSignal(e);
      M.AddEvent(e);

      //if(!e.EventIsSignal_NuMuP) continue;
      if(!e.EventIsSignal_PiPPi0) continue;
      
      if(!M.FiducialVolumeCut(e)) continue;
      if(!M.NuCCInclusiveFilter(e)) continue;
      //if(!M.DaughterTrackCut(e)) continue;
      //if(!M.DaughterFiducialVolumeCut(e)) continue;
      //if(!M.DaughterTrackLengthCut(e)) continue;
      
      if(!(e.Neutrino.size() > 0 && e.Lepton.size() > 0)) continue;
      if(e.PrimaryKaonP.size()<=0) continue;
      if(e.EventIsSignal==false) continue;

      AnalyzeTracks(e, histograms, nentry);
      
    }
    E.Close();
  }

  PlotHistograms(histograms);

}



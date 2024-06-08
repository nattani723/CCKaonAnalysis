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

void AnalyzeIndividualTrack(const TVector3& PrimaryTrackEnd, const RecoParticle& DaughterTrack, TH1D* histogram, double maxDistance) {
  
  TVector3 DaughterTrackStart(DaughterTrack.X, DaughterTrack.Y, DaughterTrack.Z);
  if ((PrimaryTrackEnd - DaughterTrackStart).Mag() > maxDistance) return;

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
  
}

void AnalyzeTracks(const Event& e, std::map<std::string, TH1D*>& histograms) {
  for (size_t i_tr = 0; i_tr < e.TrackPrimaryDaughters.size(); i_tr++) {
    RecoParticle PrimaryTrack = e.TrackPrimaryDaughters[i_tr];
    if (PrimaryTrack.TrackTruePDG != 321) continue; // Only interested in tracks with PDG == 321
    TVector3 PrimaryTrackEnd(PrimaryTrack.TrackEndX, PrimaryTrack.TrackEndY, PrimaryTrack.TrackEndZ);

    // Analyze daughter tracks
    for (size_t i_tr_dau = 0; i_tr_dau < e.TrackOthers.size(); i_tr_dau++) {
      AnalyzeIndividualTrack(PrimaryTrackEnd, e.TrackOthers[i_tr_dau], histograms["h_daughter"], 10);
    }

    // Analyze shower daughters
    for (size_t i_sh = 0; i_sh < e.ShowerOthers.size(); i_sh++) {
      AnalyzeIndividualTrack(PrimaryTrackEnd, e.ShowerOthers[i_sh], histograms["h_shower"], 20);
    }

    // Analyze rebuilt daughter tracks
    for (size_t i_tr_dau = 0; i_tr_dau < e.TrackRebuiltOthers.size(); i_tr_dau++) {
      AnalyzeIndividualTrack(PrimaryTrackEnd, e.TrackRebuiltOthers[i_tr_dau], histograms["h_rebdaughter"], 10);
    }
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

  BuildTunes();
  SelectionParameters P = P_FHC_K_NOBDT_TEST;
  
  SampleNames.push_back("AssocKaon"); 
  SampleTypes.push_back("AssocKaon"); 
  SampleFiles.push_back("/exp/uboone/data/users/taniuchi/test/KaonTrees.root");
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
      
      if(!M.FiducialVolumeCut(e)) continue;
      if(!M.NuCCInclusiveFilter(e)) continue;
      //if(!M.DaughterTrackCut(e)) continue;
      //if(!M.DaughterFiducialVolumeCut(e)) continue;
      //if(!M.DaughterTrackLengthCut(e)) continue;
      
      if(!(e.Neutrino.size() > 0 && e.Lepton.size() > 0)) continue;
      if(e.PrimaryKaonP.size()<=0) continue;
      if(e.EventIsSignal==false) continue;

      AnalyzeTracks(e, histograms);

      /*
      for(size_t i_tr=0;i_tr<e.TrackPrimaryDaughters.size();i_tr++){

	RecoParticle PrimaryTrack = e.TrackPrimaryDaughters.at(i_tr);
	if(PrimaryTrack.TrackTruePDG != 321) continue;
	TVector3 PrimaryTrackEnd(PrimaryTrack.TrackEndX, PrimaryTrack.TrackEndY, PrimaryTrack.TrackEndZ);

	for(size_t i_tr_dau=0;i_tr_dau<e.TrackOthers.size();i_tr_dau++){ 

	  RecoParticle DaughterTrack = e.TrackOthers.at(i_tr_dau);
	  TVector3 DaughterTrackStart(DaughterTrack.X, DaughterTrack.Y, DaughterTrack.Z);

	  if((PrimaryTrackEnd - DaughterTrackStart).Mag()>10) continue;

	  //get merge info
	  int MergePDG_1st = DaughterTrack.MergePDG_1st;
	  int MergePDG_2nd = DaughterTrack.MergePDG_2nd;
	  int MergePDG_3rd = DaughterTrack.MergePDG_3rd;
	  double MergeEnergyPurity_1st = DaughterTrack.MergeEnergyPurity_1st;
	  double MergeEnergyPurity_2ns = DaughterTrack.MergeEnergyPurity_2nd;
	  double MergeEnergyPurity_3rd = DaughterTrack.MergeEnergyPurity_3rd;
	  double MergeHitPurity_1st = DaughterTrack.MergeHitPurity_1st;
	  double MergeHitPurity_2nd = DaughterTrack.MergeHitPurity_2nd;
	  double MergeHitPurity_3rd = DaughterTrack.MergeHitPurity_3rd;

	  int bin1 = PDGToBin(MergePDG_1st) - 1;
	  int bin2 = PDGToBin(MergePDG_2nd) - 1;
	  int bin3 = PDGToBin(MergePDG_3rd) - 1;

	  h_daughter->Fill(bin1);
	  if(MergeEnergyPurity_2nd>0.2) h_daughter->Fill(bin2);
	  if(MergeEnergyPurity_3rd>0.2) h_daughter->Fill(bin3);

	}

	for(size_t i_sh=0;i_sh<e.ShowerOthers.size();i_sh++){

	  RecoParticle DaughterShower = e.ShowerOthers.at(i_sh); 
	  TVector3 DaughterShowerStart(DaughterShower.X, DaughterShower.Y, DaughterShower.Z);
	  
	  if((PrimaryTrackEnd - DaughterShowerStart).Mag()>20) continue;

	  //get merge info
	  int MergePDG_1st = DaughterTrack.MergePDG_1st;
	  int MergePDG_2nd = DaughterTrack.MergePDG_2nd;
	  int MergePDG_3rd = DaughterTrack.MergePDG_3rd;
	  double MergeEnergyPurity_1st = DaughterTrack.MergeEnergyPurity_1st;
	  double MergeEnergyPurity_2nd = DaughterTrack.MergeEnergyPurity_2nd;
	  double MergeEnergyPurity_3rd = DaughterTrack.MergeEnergyPurity_3rd;
	  double MergeHitPurity_1st = DaughterTrack.MergeHitPurity_1st;
	  double MergeHitPurity_2nd = DaughterTrack.MergeHitPurity_2nd;
	  double MergeHitPurity_3rd = DaughterTrack.MergeHitPurity_3rd;

	  int bin1 = PDGToBin(MergePDG_1st) - 1;
	  int bin2 = PDGToBin(MergePDG_2nd) - 1;
	  int bin3 = PDGToBin(MergePDG_3rd) - 1;

	  h_shower->Fill(bin1);
	  if(MergeEnergyPurity_2nd>0.2) h_shower->Fill(bin2);
	  if(MergeEnergyPurity_3rd>0.2) h_shower->Fill(bin3);
	    
	}

	for(size_t i_tr_dau=0;i_tr_dau<e.TrackRebuiltOthers.size();i_tr_dau++){
	
	  RecoParticle DaughterTrack = e.TrackRebuiltOthers.at(i_tr_dau);
	  TVector3 DaughterTrackStart(DaughterTrack.X, DaughterTrack.Y, DaughterTrack.Z);

	  if((PrimaryTrackEnd - DaughterTrackStart).Mag()>10) continue;

	  //get merge info
	  int MergePDG_1st = DaughterTrack.MergePDG_1st;
	  int MergePDG_2nd = DaughterTrack.MergePDG_2nd;
	  int MergePDG_3rd = DaughterTrack.MergePDG_3rd;
	  double MergeEnergyPurity_1st = DaughterTrack.MergeEnergyPurity_1st;
	  double MergeEnergyPurity_2ns = DaughterTrack.MergeEnergyPurity_2nd;
	  double MergeEnergyPurity_3rd = DaughterTrack.MergeEnergyPurity_3rd;
	  double MergeHitPurity_1st = DaughterTrack.MergeHitPurity_1st;
	  double MergeHitPurity_2nd = DaughterTrack.MergeHitPurity_2nd;
	  double MergeHitPurity_3rd = DaughterTrack.MergeHitPurity_3rd;

	  int bin1 = PDGToBin(MergePDG_1st) - 1;
	  int bin2 = PDGToBin(MergePDG_2nd) - 1;
	  int bin3 = PDGToBin(MergePDG_3rd) - 1;

	  h_rebdaughter->Fill(bin1);
	  if(MergeEnergyPurity_2nd>0.2) h_rebdaughter->Fill(bin2);
	  if(MergeEnergyPurity_3rd>0.2) h_rebdaughter->Fill(bin3);
	  
	}

      }
      */
      
    }
    E.Close();
  }

  PlotHistograms(histograms);
  /*
  TCanvas* c1 = new TCanvas("c1", "Canvas for Drawing Histograms", 800, 600);
  c1->cd();

  h_track->GetXaxis()->SetLabelSize(0.04);
  h_track->GetYaxis()->SetLabelSize(0.04);
  h_track->GetXaxis()->SetLabelFont(62);
  h_track->GetYaxis()->SetLabelFont(62);
  h_track->GetXaxis()->SetTitleFont(62);
  h_track->GetYaxis()->SetTitleFont(62);
  h_track->GetXaxis()->SetTitleOffset(1.0);
  h_track->GetYaxis()->SetTitleOffset(1.5);
  h_track->GetXaxis()->SetLabelSize(0.04);
  h_track->GetYaxis()->SetLabelSize(0.04);

  h_track->GetXaxis()->SetBinLabel(1, "K^{+}");
  h_track->GetXaxis()->SetBinLabel(2, "#mu^{+}");
  h_track->GetXaxis()->SetBinLabel(3, "#pi^{+}");
  h_track->GetXaxis()->SetBinLabel(4, "proton");
  h_track->GetXaxis()->SetBinLabel(5, "shower");
  h_track->GetXaxis()->SetBinLabel(6, "Others");
  
  c1->Modified();
  c1->Update();
  c1->Print("Plots/MergeCheck_DaughterTrack.pdf");

  h_rebtrack->GetXaxis()->SetLabelSize(0.04);
  h_rebtrack->GetYaxis()->SetLabelSize(0.04);
  h_rebtrack->GetXaxis()->SetLabelFont(62);
  h_rebtrack->GetYaxis()->SetLabelFont(62);
  h_rebtrack->GetXaxis()->SetTitleFont(62);
  h_rebtrack->GetYaxis()->SetTitleFont(62);
  h_rebtrack->GetXaxis()->SetTitleOffset(1.0);
  h_rebtrack->GetYaxis()->SetTitleOffset(1.5);
  h_rebtrack->GetXaxis()->SetLabelSize(0.04);
  h_rebtrack->GetYaxis()->SetLabelSize(0.04);

  h_rebtrack->GetXaxis()->SetBinLabel(1, "K^{+}");
  h_rebtrack->GetXaxis()->SetBinLabel(2, "#mu^{+}");
  h_rebtrack->GetXaxis()->SetBinLabel(3, "#pi^{+}");
  h_rebtrack->GetXaxis()->SetBinLabel(4, "proton");
  h_rebtrack->GetXaxis()->SetBinLabel(5, "shower");
  h_rebtrack->GetXaxis()->SetBinLabel(6, "Others");
  
  c1->Modified();
  c1->Update();
  c1->Print("Plots/MergeCheck_DaughterTrack.pdf");

  //M.DrawHistograms(label);
  */
}



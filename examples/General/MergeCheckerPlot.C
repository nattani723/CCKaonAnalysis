R__LOAD_LIBRARY($HYP_TOP/lib/libHyperon.so)
R__LOAD_LIBRARY($HYP_TOP/lib/libParticleDict.so)


#include "SelectionManager.h"
#include "EventAssembler.h"
#include "Cut.h"
#include "SelectionParameters.h"
#include "Parameters.h"
#include "SampleSets_Example.h"

// Function prototypes
int PDGToBin(int pdg);
std::string PDGLabel(int bin);
void InitializeHistograms(std::map<std::string, TH1D*>& histograms);
void AnalyzeIndividualTrack(const TVector3& PrimaryTrackEnd, const RecoParticle& DaughterTrack, TH1D* histogram, double maxDistance, int& nentry);
void AnalyzeTracks(const Event& e, std::map<std::string, TH1D*>& histograms, int* nentry);
void PlotHistograms(const std::map<std::string, TH1D*>& histograms);
void HighlightBins(TH1D* hist, int bin, int color);
void MergeCheckerPlot();

// PDG to bin conversion
int PDGToBin(int pdg) {
  switch (pdg) {
  case 321: return 1;  // K+
  case -13: return 2; // mu+
  case 211: return 3; // pi+
  case 2212: return 4; // proton
  case 11:  // e-
  case -11: // e+
  case 22: return 5; // gamma (shower)
  default: return 6;  // Others
  }
}

// Bin to PDG label conversion
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
  std::vector<std::string> labels = {"Daughter Tracks", "Rebuild Daughter Tracks", "Showers"};
  //for (const auto& type : types) {
  for(int i=0; i<types.size(); i++){
    std::string name = "h_" + types[i];
    std::string title = ";Truth Match PDG of " + labels[i] + "; Energy Deposition [%]";
    histograms[name] = new TH1D(name.c_str(), title.c_str(), 6, 0, 6);
    histograms[name]->SetStats(0);
    for (int bin = 1; bin <= 6; ++bin) {
      histograms[name]->GetXaxis()->SetBinLabel(bin, PDGLabel(bin).c_str());
    }
  }
}

// Analyze individual track
void AnalyzeIndividualTrack(const TVector3& PrimaryTrackEnd, const RecoParticle& DaughterTrack, TH1D* histogram, double maxDistance, int& nentry) {
  if (!histogram) {
    std::cerr << "Error: Histogram pointer is null." << std::endl;
    return;
  }

  TVector3 DaughterTrackStart(DaughterTrack.X, DaughterTrack.Y, DaughterTrack.Z);
  if ((PrimaryTrackEnd - DaughterTrackStart).Mag() > maxDistance) return;

  ++nentry;

  int bin1 = PDGToBin(DaughterTrack.MergePDG_1st) - 1;
  if (DaughterTrack.MergePDG_1st != -1) histogram->Fill(bin1, DaughterTrack.MergeEnergyPurity_1st);

  int bin2 = PDGToBin(DaughterTrack.MergePDG_2nd) - 1;
  if (DaughterTrack.MergePDG_2nd != -1) histogram->Fill(bin2, DaughterTrack.MergeEnergyPurity_2nd);

  int bin3 = PDGToBin(DaughterTrack.MergePDG_3rd) - 1;
  if (DaughterTrack.MergePDG_3rd != -1) histogram->Fill(bin3, DaughterTrack.MergeEnergyPurity_3rd);
}

// Analyze tracks
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
}

// Function to highlight specific bins in a histogram
void HighlightBins(TH1D* hist, int bin, int color) {
  if (!hist) {
    std::cerr << "Error: Histogram pointer is null." << std::endl;
    return;
  }

  double xlow = hist->GetXaxis()->GetBinLowEdge(bin);
  double xhigh = hist->GetXaxis()->GetBinUpEdge(bin);
  //double ylow = hist->GetMinimum();
  double ylow = 0;
  double yhigh = hist->GetBinContent(bin);

  TBox* box = new TBox(xlow, ylow, xhigh, yhigh);
  box->SetFillColorAlpha(color,0.5);
  box->Draw("same");
}

// Plot histograms
void PlotHistograms(const std::map<std::string, TH1D*>& histograms) {
  TCanvas* c = new TCanvas("c", "Canvas for Drawing Histograms", 800, 600);
  c->cd();

  for (const auto& entry : histograms) {
    TH1D* h = entry.second;  // Get the histogram pointer
    if (!h) continue;  // Skip if histogram pointer is null

    // Set histogram visual styles
    h->SetStats(0);  // Turn off the statistics box
    h->SetLineColor(kBlack);
    h->SetLineWidth(3);
    h->GetXaxis()->SetTitleFont(62);
    h->GetYaxis()->SetTitleFont(62);
    h->GetXaxis()->SetLabelFont(62);
    h->GetYaxis()->SetLabelFont(62);
    h->GetXaxis()->SetLabelSize(0.04);
    h->GetYaxis()->SetLabelSize(0.04);
    h->GetXaxis()->SetTitleOffset(1.0);
    h->GetYaxis()->SetTitleOffset(1.5);
    h->SetMinimum(0.0);

    // Setting custom bin labels if required
    h->GetXaxis()->SetBinLabel(1, "K^{+}");
    h->GetXaxis()->SetBinLabel(2, "#mu^{+}");
    h->GetXaxis()->SetBinLabel(3, "#pi^{+}");
    h->GetXaxis()->SetBinLabel(4, "proton");
    h->GetXaxis()->SetBinLabel(5, "shower");
    h->GetXaxis()->SetBinLabel(6, "Others");

    // Draw the histogram
    h->Draw("HIST");

    // Highlight specific bins
    HighlightBins(h, 2, TColor::GetColorDark(kCyan));  // Highlight "mu+" bin
    HighlightBins(h, 3, TColor::GetColorDark(kGreen));  // Highlight "pi+" bin
    if (entry.first == "h_shower") HighlightBins(h, 5, kMagenta);  // Highlight "shower" bin

    // Update the canvas to reflect changes
    c->Modified();
    c->Update();

    // Save the canvas as a PDF or an image file
    //std::string filename = "Plots/CCK_" + entry.first + "_NuMuP.pdf";
    //std::string filename = "Plots/CCK_" + entry.first + "_PiPPi0.pdf";
    std::string filename = "Plots/CCK_" + entry.first + "_BothDCY.pdf";
    c->Print(filename.c_str());

    // Optionally clear the canvas for the next histogram
    c->Clear();
  }

  // Clean up: Delete the canvas to free memory
  delete c;
}

// Main function
void MergeCheckerPlot() {
  double POT = 1.0e21; // POT to scale samples to
  std::map<std::string, TH1D*> histograms;
  int nentry[3] = {0, 0, 0};

  BuildTunes();
  SelectionParameters P = P_FHC_K_NOBDT_TEST;

  SampleNames.push_back("AsoscKaon");
  SampleTypes.push_back("AssocKaon");
  SampleFiles.push_back("/exp/uboone/data/users/taniuchi/taniuchi/pandora_alg/ana/assok_refined_KrecoAlg_parameter10_ntuple.root");

  SampleNames.push_back("SingleKaon");
  SampleTypes.push_back("SingleKaon");
  SampleFiles.push_back("/exp/uboone/data/users/taniuchi/taniuchi/pandora_alg/ana/singlek_refined_KrecoAlg_parameter10_ntuple.root");
  //SampleFiles.push_back("/exp/uboone/data/users/taniuchi/taniuchi/pandora_alg/ana/cck_refined_KrecoAlg_parameter10_ntuple.root");
  //SampleFiles.push_back("/exp/uboone/data/users/taniuchi/test/KaonTrees.root");
  //SampleFiles.push_back("/exp/uboone/data/users/taniuchi/ntuple_testarea/assok_KaonTrees.root");

  EventAssembler E;
  SelectionManager M(P);
  M.SetPOT(POT);

  InitializeHistograms(histograms);

  // Sample Loop
  for (size_t i_s = 0; i_s < SampleNames.size(); i_s++) {
    E.SetFile(SampleFiles.at(i_s), "KAON"); // 2nd parameter is dummy

    if (SampleTypes.at(i_s) == "SingleKaon") M.AddSample("SingleKaon", "SingleKaon", POT);
    //if(SampleTypes.at(i_s) != "EXT" && SampleTypes.at(i_s) != "Data") M.AddSample(SampleNames.at(i_s),SampleTypes.at(i_s),E.GetPOT());
    else if (SampleTypes.at(i_s) == "Data") M.AddSample(SampleNames.at(i_s), SampleTypes.at(i_s), Data_POT);
    else if (SampleTypes.at(i_s) == "EXT") M.AddSample(SampleNames.at(i_s), SampleTypes.at(i_s), EXT_POT);

    M.UseFluxWeight(false);
    M.UseGenWeight(false);

    // Event Loop
    for (int i = 0; i < E.GetNEvents(); i++) {
      if (i % 10000 == 0) std::cout << i << "/" << E.GetNEvents() << std::endl;

      Event e = E.GetEvent(i);

      M.SetSignal(e);
      M.AddEvent(e);

      //if(!e.EventIsSignal_NuMuP) continue;
      //if (!e.EventIsSignal_PiPPi0) continue;
      if (!e.EventIsSignal_NuMuP && !e.EventIsSignal_PiPPi0) continue;

      if (!M.FiducialVolumeCut(e)) continue;
      if (!M.NuCCInclusiveFilter(e)) continue;
      if (!M.DaughterTrackCut(e)) continue;
      //if(!M.DaughterFiducialVolumeCut(e)) continue;
      //if(!M.DaughterTrackLengthCut(e)) continue;

      if (!(e.Neutrino.size() > 0 && e.Lepton.size() > 0)) continue;
      if (e.PrimaryKaonP.size() <= 0) continue;
      if (e.EventIsSignal == false) continue;

      AnalyzeTracks(e, histograms, nentry);
    }
    E.Close();
  }

  int i = 0;
  for (auto& pair : histograms) {
    TH1D* hist = pair.second;
    std::cout << "nentry[i]: " << nentry[i] << std::endl;
    if (nentry[i] > 0) { // Avoid division by zero
      //hist->Scale(100.0 / nentry[i]);
      hist->Scale(100.0 / hist->Integral(0,5));
    }
    i++;
  }

  PlotHistograms(histograms);
}

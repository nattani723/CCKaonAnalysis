#include <iostream>
#include <TH2D.h>
#include <TH1D.h>
#include <THStack.h>
#include <TFile.h>
#include <TROOT.h>
#include <TChain.h>
#include <TTree.h>
#include <TVectorT.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TGaxis.h>
#include <TLegend.h>
#include <vector>
#include <string>

void Initialise();

TString outputpdf = "BDT_overtrain_check.pdf";

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
}

void DrawOverlayHistograms(TFile* file, const std::string& variable, const std::string& label)
{
  TH1D *sigHist = (TH1D*) file->Get(("dataset/Method_BDT/BDT/" + variable + "__Signal").c_str());
  TH1D *bgHist = (TH1D*) file->Get(("dataset/Method_BDT/BDT/" + variable + "__Background").c_str());

  if (!sigHist || !bgHist) {
    std::cerr << "Histogram not found for variable: " << variable << std::endl;
    return;
  }

  TCanvas *c = new TCanvas("c", "c", 800, 600);
  c->SetFillStyle(4000);

  sigHist->SetLineColor(kBlue);
  sigHist->SetLineStyle(1);
  sigHist->SetLineWidth(2);

  bgHist->SetLineColor(kRed);
  bgHist->SetLineStyle(1);
  bgHist->SetLineWidth(2);

  THStack *hs = new THStack("hs","");
  hs->Add(sigHist, "HIST");
  hs->Add(bgHist, "HIST");

  double maximum = std::max(sigHist->GetMaximum(), bgHist->GetMaximum());
  hs->SetMaximum(maximum * 1.25);
  hs->SetMinimum(0);

  hs->Draw("nostack HIST");
  hs->GetXaxis()->SetTitle(label.c_str());
  hs->GetYaxis()->SetTitle("Events");

  TLegend *l = new TLegend(0.1, 0.8, 0.9, 0.99);
  l->AddEntry(sigHist, "Signal", "L");
  l->AddEntry(bgHist, "Background", "L");
  l->SetTextSize(0.04);
  l->SetNColumns(2);
  l->SetBorderSize(0);
  l->SetFillColor(0);
  c->SetTopMargin(0.2);
  l->Draw();

  c->Update();
  c->Print(outputpdf);
  delete c;
}

void DrawBDTHistograms(TFile* file)
{
  TH1D *BDT_Test_Signal = (TH1D*) file->Get("dataset/Method_BDT/BDT/MVA_BDT_S");
  TH1D *BDT_Train_Signal = (TH1D*) file->Get("dataset/Method_BDT/BDT/MVA_BDT_Train_S");
  TH1D *BDT_Test_BG = (TH1D*) file->Get("dataset/Method_BDT/BDT/MVA_BDT_B");
  TH1D *BDT_Train_BG = (TH1D*) file->Get("dataset/Method_BDT/BDT/MVA_BDT_Train_B");

  if (!BDT_Test_Signal || !BDT_Train_Signal || !BDT_Test_BG || !BDT_Train_BG) {
    std::cerr << "One or more BDT histograms not found." << std::endl;
    return;
  }

  BDT_Test_Signal->SetLineColor(kBlue);
  BDT_Test_Signal->SetLineStyle(1);
  BDT_Test_Signal->SetLineWidth(2);

  BDT_Train_Signal->SetLineColor(kCyan-7);
  BDT_Train_Signal->SetLineStyle(10);
  BDT_Train_Signal->SetLineWidth(2);

  BDT_Test_BG->SetLineColor(kRed);
  BDT_Test_BG->SetLineStyle(1);
  BDT_Test_BG->SetLineWidth(2);

  BDT_Train_BG->SetLineColor(kMagenta-4);
  BDT_Train_BG->SetLineStyle(10);
  BDT_Train_BG->SetLineWidth(2);

  TCanvas *c = new TCanvas("c", "c", 800, 600);
  c->SetFillStyle(4000);

  THStack *hs = new THStack("hs", "");
  hs->Add(BDT_Test_Signal, "HIST");
  hs->Add(BDT_Train_Signal, "HIST");
  hs->Add(BDT_Test_BG, "HIST");
  hs->Add(BDT_Train_BG, "HIST");

  double maximum = -1e10;
  maximum = std::max(maximum, BDT_Test_Signal->GetMaximum());
  maximum = std::max(maximum, BDT_Train_Signal->GetMaximum());
  maximum = std::max(maximum, BDT_Test_BG->GetMaximum());
  maximum = std::max(maximum, BDT_Train_BG->GetMaximum());

  hs->SetMaximum(maximum * 1.25);
  hs->SetMinimum(0);

  hs->Draw("nostack HIST");
  hs->GetXaxis()->SetTitle("BDT response score");
  hs->GetYaxis()->SetTitle("Events");

  TLegend *l = new TLegend(0.1, 0.8, 0.9, 0.99);
  l->AddEntry(BDT_Test_Signal, "Signal, Test", "L");
  l->AddEntry(BDT_Train_Signal, "Signal, Train", "L");
  l->AddEntry(BDT_Test_BG, "Background, Test", "L");
  l->AddEntry(BDT_Train_BG, "Background, Train", "L");
  l->SetNColumns(2);
  l->SetTextSize(0.04);
  l->SetBorderSize(0);
  l->SetFillColor(0);
  c->SetTopMargin(0.2);
  l->Draw();

  c->Update();
  c->Print(outputpdf);
  delete c;
}

void BDTCutPlots_plane()
{
  TGaxis::SetMaxDigits(3);
  gErrorIgnoreLevel = kWarning;

  TFile *f_mva = new TFile("/exp/uboone/app/users/taniuchi/51_pandora/CCKaonAnalysis/examples/TMVA/TMVA.root");

  Initialise();

  outputpdf = "BDT_overtrain_check.pdf";
  TString openPdf = outputpdf + "[";
  TString closePdf = outputpdf + "]";
  TCanvas *c = new TCanvas();
  c->Print(openPdf);
  delete c;

  std::vector<std::string> variables = {
    "PrimaryTrack_Chi2_Kaon_3Plane",
    "PrimaryTrack_Chi2_Proton_3Plane",
    "PrimaryTrack_Chi2_Muon_3Plane",
    "PrimaryTrack_Chi2_Pion_3Plane",
    "DaughterTrack_Chi2_Kaon_3Plane",
    "DaughterTrack_Chi2_Proton_3Plane",
    "DaughterTrack_Chi2_Muon_3Plane",
    "DaughterTrack_Chi2_Pion_3Plane",
    "PrimaryTrack_LLR_PID",
    "PrimaryTrack_LLR_PID_Kaon",
    "DaughterTrack_LLR_PID",
    "DaughterTrack_LLR_PID_Kaon",
    "DaughterTrackLength",
  };

  std::vector<std::string> labels = {
    "Primary Track Three Plane Kaon Hypothesis #Chi^{2} Score",
    "Primary Track Three Plane Proton Hypothesis #Chi^{2} Score",
    "Primary Track Three Plane Muon Hypothesis #Chi^{2} Score",
    "Primary Track Three Plane Pion Hypothesis #Chi^{2} Score",
    "Daughter Track Three Plane Kaon Hypothesis #Chi^{2} Score",
    "Daughter Track Three Plane Proton Hypothesis #Chi^{2} Score",
    "Daughter Track Three Plane Muon Hypothesis #Chi^{2} Score",
    "Daughter Track Three Plane Pion Hypothesis #Chi^{2} Score",
    "Primary Track Proton/Muon Separation LLR PID",
    "Primary Track Proton/Kaon Separation LLR PID",
    "Daughter Track Proton/Muon Separation LLR PID",
    "Daughter Track Proton/Kaon Separation LLR PID",
    "Daughter Track Length [cm]"
  };

  //for (const auto& variable : variables) {
  for(int i=0; i<variables.size(); i++){
    DrawOverlayHistograms(f_mva, variables.at(i), labels.at(i));
  }
    //}

  DrawBDTHistograms(f_mva);

  c = new TCanvas();
  c->Print(closePdf);
  delete c;

  f_mva->Close();
  delete f_mva;
}

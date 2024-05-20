#include <iostream>
#include <TH2D.h>
#include <TFile.h>
#include <TROOT.h>
#include <TChain.h>
#include <TTree.h>
#include <TVectorT.h>
#include <vector>
#include <iostream>
#include <stdio.h>
#include <string.h>


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


void BDTCutPlots_plane()
{
  TGaxis::SetMaxDigits(3);
  gErrorIgnoreLevel = kWarning;

  //output from PreCutHistos
  TFile * f_mva = new TFile("/uboone/app/users/taniuchi/KaonAna/KaonAnlysis/Ana/TMVA/Jun28/TMVA_all_pl2.root");

  Initialise;

  TCanvas * c = new TCanvas("c", "c", 800, 600);
  c->SetFillStyle(4000);
  //c->Print(Form("%s[", output_pdf_bdt_plane.Data()));
  
  TString fname(f_mva->GetName());

  /*
  TTree * t_mva_train;
  TTree * t_mva_tree;
  t_mva_train = (TTree*) f_mva->Get("dataset_all_pl2/TrainTree");
  t_mva_tree = (TTree*) f_mva->Get("dataset_all_pl2/TestTree");

  int nentry_train = t_mva_train->GetEntries();
  int nentry_tree = t_mva_tree->GetEntries();
  */

  //under dataset/Method_BDT/ we have TH1Ds MVA_BDT_S/MVA_BDT_B/MVA_BDT_Train_S/MVA_BDT_Train_B
  /*
  TH1D * BDT_Test_Signal;
  TH1D * BDT_Train_Signal;
  TH1D * BDT_Test_BG;
  TH1D * BDT_Train_BG;
  */

  TH1D * BDT_Test_Signal = (TH1D*) f_mva->Get("dataset/Method_BDT/MVA_BDT_S");
  TH1D * BDT_Train_Signal = (TH1D*) f_mva->Get("dataset/Method_BDT/MVA_BDT_Train_S");
  TH1D * BDT_Test_BG = (TH1D*) f_mva->Get("dataset/Method_BDT/MVA_BDT_B");
  TH1D * BDT_Train_BG = (TH1D*) f_mva->Get("dataset/Method_BDT/MVA_BDT_Train_B");

  BDT_Test_Signal->SetLineColor("kBlue");
  BDT_Test_Signal->SetLineStyle(1);
  BDT_Test_Signal->SetLineWidth(2);
  BDT_Test_Signal->Draw("E");

  BDT_Train_Signal->SetLineColor("kCyan-7");
  BDT_Train_Signal->SetLineStyle(10);
  BDT_Train_Signal->SetLineWidth(2);
  BDT_Train_Signal->Draw("E");

  BDT_Test_BG->SetLineColor("kRed");
  BDT_Test_BG->SetLineStyle(1);
  BDT_Test_BG->SetLineWidth(2);
  BDT_Test_BG->Draw("E");
  
  BDT_Train_BG->SetLineColor("kMagenta-4");
  BDT_Train_BG->SetLineStyle(10);
  BDT_Train_BG->SetLineWidth(2);
  BDT_Train_BG->Draw("E");

  gStyle->SetOptStat(0);

  THStack *hs = new THStack("hs",BDT_Test_Signal->GetTitle());
  hs->Add(BDT_Test_Signal,"HIST");
  hs->Add(BDT_Train_Signal,"HIST");
  hs->Add(BDT_Test_BG,"HIST");
  hs->Add(BDT_Train_BG,"HIST");

  //double maximum = GetHistMaxError(hs);
  
  double maximum = -1e10;

  for(int i_b=1;i_b<hs->GetNbinsX()+1;i_b++)
    if(hs->GetBinContent(i_b)+hs->GetBinError(i_b) > maximum)
      maximum = hs->GetBinContent(i_b)+hs->GetBinError(i_b);

  return maximum;
  
  hs->GetYaxis()->SetRangeUser(0.0,maximum*1.25);
  hs->SetStats(0);

  TLegend *l = new TLegend(0.1, 0.8, 0.9, 0.99);
  l->AddEntry(BDT_Test_Signal,"Signal, Test","F");
  l->AddEntry(BDT_Train_Signal,"Signal, Train","F");
  l->AddEntry(BDT_Test_BG,"Background, Test","F");
  l->AddEntry(BDT_Train_BG,"Backgroun, Train","F");
  l->SetNColumns(2);
  l->SetBorderSize(0);
  l->SetFillColor(0);
  c->SetTopMargin(0.2);

  hs->Draw("nostack");
  c->Update();
  hs->GetXaxis()->SetTitle("BDT response score");
  l->Draw();

  c->Print(outputpdf);

  //c->Print(Form("%s]", output_pdf_bdt_plane.Data()));
}

void DaughterBraggPIDKaon_ByDaugterPDG()
{
//=========Macro generated from canvas: c/c
//=========  (Mon Aug  5 10:52:00 2024) by ROOT version 6.16/00
   TCanvas *c = new TCanvas("c", "c",0,0,800,600);
   c->Range(0,0,1,1);
   c->SetFillColor(0);
   c->SetBorderMode(0);
   c->SetBorderSize(2);
   c->SetFrameBorderMode(0);
  
// ------------>Primitives in pad: p_legend
   TPad *p_legend = new TPad("p_legend", "p_legend",0,0.85,1,1);
   p_legend->Draw();
   p_legend->cd();
   p_legend->Range(0,0,1,1);
   p_legend->SetFillColor(0);
   p_legend->SetBorderMode(0);
   p_legend->SetBorderSize(2);
   p_legend->SetBottomMargin(0);
   p_legend->SetFrameBorderMode(0);
   
   TLegend *leg = new TLegend(0.1,0,0.9,1,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextFont(62);
   leg->SetTextSize(0.25);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("h_daughter_KaonP","CC K^{+}","l");
   entry->SetLineColor(8);
   entry->SetLineStyle(1);
   entry->SetLineWidth(2);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(62);
   entry=leg->AddEntry("h_daughter_Proton","proton","l");
   entry->SetLineColor(46);
   entry->SetLineStyle(1);
   entry->SetLineWidth(2);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(62);
   entry=leg->AddEntry("h_daughter_MuonP","#mu^{+}","l");
   entry->SetLineColor(2);
   entry->SetLineStyle(1);
   entry->SetLineWidth(2);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(62);
   entry=leg->AddEntry("h_daughter_MuonM","#mu^{-}","l");
   entry->SetLineColor(3);
   entry->SetLineStyle(1);
   entry->SetLineWidth(2);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(62);
   entry=leg->AddEntry("h_daughter_PionP","#pi^{+}","l");
   entry->SetLineColor(4);
   entry->SetLineStyle(1);
   entry->SetLineWidth(2);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(62);
   entry=leg->AddEntry("h_daughter_PionM","#pi^{-}","l");
   entry->SetLineColor(5);
   entry->SetLineStyle(1);
   entry->SetLineWidth(2);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(62);
   entry=leg->AddEntry("h_daughter_Shower","Shower","l");
   entry->SetLineColor(6);
   entry->SetLineStyle(1);
   entry->SetLineWidth(2);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(62);
   entry=leg->AddEntry("h_daughter_Other","Other","l");
   entry->SetLineColor(7);
   entry->SetLineStyle(1);
   entry->SetLineWidth(2);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(62);
   leg->Draw();
   p_legend->Modified();
   c->cd();
  
// ------------>Primitives in pad: p_plot
   TPad *p_plot = new TPad("p_plot", "p_plot",0,0,1,0.85);
   p_plot->Draw();
   p_plot->cd();
   p_plot->Range(-3.75,-2446.77,33.75,22020.93);
   p_plot->SetFillColor(0);
   p_plot->SetBorderMode(0);
   p_plot->SetBorderSize(2);
   p_plot->SetTopMargin(0.01);
   p_plot->SetFrameBorderMode(0);
   p_plot->SetFrameBorderMode(0);
   
   TH1D *h_daughter_KaonP__3 = new TH1D("h_daughter_KaonP__3","",30,0,30);
   h_daughter_KaonP__3->SetBinContent(0,19);
   h_daughter_KaonP__3->SetBinContent(1,793);
   h_daughter_KaonP__3->SetBinError(0,4.358899);
   h_daughter_KaonP__3->SetBinError(1,28.16026);
   h_daughter_KaonP__3->SetMinimum(0);
   h_daughter_KaonP__3->SetMaximum(21776.25);
   h_daughter_KaonP__3->SetEntries(812);
   h_daughter_KaonP__3->SetStats(0);
   h_daughter_KaonP__3->SetFillColor(8);
   h_daughter_KaonP__3->SetLineColor(8);
   h_daughter_KaonP__3->SetLineWidth(2);
   h_daughter_KaonP__3->GetXaxis()->SetTitle("Bragg PID K^{+}");
   h_daughter_KaonP__3->GetXaxis()->SetLabelFont(42);
   h_daughter_KaonP__3->GetXaxis()->SetLabelSize(0.045);
   h_daughter_KaonP__3->GetXaxis()->SetTitleSize(0.05);
   h_daughter_KaonP__3->GetXaxis()->SetTitleOffset(0.93);
   h_daughter_KaonP__3->GetYaxis()->SetTitle("Event");
   h_daughter_KaonP__3->GetYaxis()->SetLabelFont(42);
   h_daughter_KaonP__3->GetYaxis()->SetLabelSize(0.045);
   h_daughter_KaonP__3->GetYaxis()->SetTitleSize(0.05);
   h_daughter_KaonP__3->GetYaxis()->SetTitleOffset(1.06);
   h_daughter_KaonP__3->GetZaxis()->SetLabelFont(42);
   h_daughter_KaonP__3->GetZaxis()->SetLabelSize(0.035);
   h_daughter_KaonP__3->GetZaxis()->SetTitleSize(0.035);
   h_daughter_KaonP__3->GetZaxis()->SetTitleOffset(1);
   h_daughter_KaonP__3->GetZaxis()->SetTitleFont(42);
   h_daughter_KaonP__3->Draw("");
   
   THStack *hs = new THStack();
   hs->SetName("hs");
   hs->SetTitle("");
   
   TH1F *hs_stack_2 = new TH1F("hs_stack_2","",30,0,30);
   hs_stack_2->SetMinimum(0);
   hs_stack_2->SetMaximum(18292.05);
   hs_stack_2->SetDirectory(0);
   hs_stack_2->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   hs_stack_2->SetLineColor(ci);
   hs_stack_2->GetXaxis()->SetLabelFont(42);
   hs_stack_2->GetXaxis()->SetLabelSize(0.035);
   hs_stack_2->GetXaxis()->SetTitleSize(0.035);
   hs_stack_2->GetXaxis()->SetTitleOffset(1);
   hs_stack_2->GetXaxis()->SetTitleFont(42);
   hs_stack_2->GetYaxis()->SetLabelFont(42);
   hs_stack_2->GetYaxis()->SetLabelSize(0.035);
   hs_stack_2->GetYaxis()->SetTitleSize(0.035);
   hs_stack_2->GetYaxis()->SetTitleFont(42);
   hs_stack_2->GetZaxis()->SetLabelFont(42);
   hs_stack_2->GetZaxis()->SetLabelSize(0.035);
   hs_stack_2->GetZaxis()->SetTitleSize(0.035);
   hs_stack_2->GetZaxis()->SetTitleOffset(1);
   hs_stack_2->GetZaxis()->SetTitleFont(42);
   hs->SetHistogram(hs_stack_2);
   
   
   TH1D *h_daughter_KaonP_stack_1 = new TH1D("h_daughter_KaonP_stack_1","",30,0,30);
   h_daughter_KaonP_stack_1->SetBinContent(0,19);
   h_daughter_KaonP_stack_1->SetBinContent(1,793);
   h_daughter_KaonP_stack_1->SetBinError(0,4.358899);
   h_daughter_KaonP_stack_1->SetBinError(1,28.16026);
   h_daughter_KaonP_stack_1->SetMinimum(0);
   h_daughter_KaonP_stack_1->SetMaximum(21776.25);
   h_daughter_KaonP_stack_1->SetEntries(812);
   h_daughter_KaonP_stack_1->SetStats(0);
   h_daughter_KaonP_stack_1->SetFillColor(8);
   h_daughter_KaonP_stack_1->SetLineColor(8);
   h_daughter_KaonP_stack_1->SetLineWidth(2);
   h_daughter_KaonP_stack_1->GetXaxis()->SetTitle("Bragg PID K^{+}");
   h_daughter_KaonP_stack_1->GetXaxis()->SetLabelFont(42);
   h_daughter_KaonP_stack_1->GetXaxis()->SetLabelSize(0.045);
   h_daughter_KaonP_stack_1->GetXaxis()->SetTitleSize(0.05);
   h_daughter_KaonP_stack_1->GetXaxis()->SetTitleOffset(0.93);
   h_daughter_KaonP_stack_1->GetYaxis()->SetTitle("Event");
   h_daughter_KaonP_stack_1->GetYaxis()->SetLabelFont(42);
   h_daughter_KaonP_stack_1->GetYaxis()->SetLabelSize(0.045);
   h_daughter_KaonP_stack_1->GetYaxis()->SetTitleSize(0.05);
   h_daughter_KaonP_stack_1->GetYaxis()->SetTitleOffset(1.06);
   h_daughter_KaonP_stack_1->GetZaxis()->SetLabelFont(42);
   h_daughter_KaonP_stack_1->GetZaxis()->SetLabelSize(0.035);
   h_daughter_KaonP_stack_1->GetZaxis()->SetTitleSize(0.035);
   h_daughter_KaonP_stack_1->GetZaxis()->SetTitleOffset(1);
   h_daughter_KaonP_stack_1->GetZaxis()->SetTitleFont(42);
   hs->Add(h_daughter_KaonP_stack_1,"HIST");
   
   TH1D *h_daughter_Proton_stack_2 = new TH1D("h_daughter_Proton_stack_2","",30,0,30);
   h_daughter_Proton_stack_2->SetBinContent(0,106);
   h_daughter_Proton_stack_2->SetBinContent(1,5540);
   h_daughter_Proton_stack_2->SetBinError(0,10.29563);
   h_daughter_Proton_stack_2->SetBinError(1,74.43118);
   h_daughter_Proton_stack_2->SetEntries(5646);
   h_daughter_Proton_stack_2->SetStats(0);
   h_daughter_Proton_stack_2->SetFillColor(46);
   h_daughter_Proton_stack_2->SetLineColor(46);
   h_daughter_Proton_stack_2->SetLineWidth(2);
   h_daughter_Proton_stack_2->GetXaxis()->SetTitle("Bragg PID K^{+}");
   h_daughter_Proton_stack_2->GetXaxis()->SetLabelFont(42);
   h_daughter_Proton_stack_2->GetXaxis()->SetLabelSize(0.035);
   h_daughter_Proton_stack_2->GetXaxis()->SetTitleSize(0.035);
   h_daughter_Proton_stack_2->GetXaxis()->SetTitleOffset(1);
   h_daughter_Proton_stack_2->GetXaxis()->SetTitleFont(42);
   h_daughter_Proton_stack_2->GetYaxis()->SetTitle("Event");
   h_daughter_Proton_stack_2->GetYaxis()->SetLabelFont(42);
   h_daughter_Proton_stack_2->GetYaxis()->SetLabelSize(0.035);
   h_daughter_Proton_stack_2->GetYaxis()->SetTitleSize(0.035);
   h_daughter_Proton_stack_2->GetYaxis()->SetTitleFont(42);
   h_daughter_Proton_stack_2->GetZaxis()->SetLabelFont(42);
   h_daughter_Proton_stack_2->GetZaxis()->SetLabelSize(0.035);
   h_daughter_Proton_stack_2->GetZaxis()->SetTitleSize(0.035);
   h_daughter_Proton_stack_2->GetZaxis()->SetTitleOffset(1);
   h_daughter_Proton_stack_2->GetZaxis()->SetTitleFont(42);
   hs->Add(h_daughter_Proton_stack_2,"HIST");
   
   TH1D *h_daughter_MuonP_stack_3 = new TH1D("h_daughter_MuonP_stack_3","",30,0,30);
   h_daughter_MuonP_stack_3->SetBinContent(0,95);
   h_daughter_MuonP_stack_3->SetBinContent(1,5440);
   h_daughter_MuonP_stack_3->SetBinError(0,9.746794);
   h_daughter_MuonP_stack_3->SetBinError(1,73.75636);
   h_daughter_MuonP_stack_3->SetEntries(5535);
   h_daughter_MuonP_stack_3->SetStats(0);
   h_daughter_MuonP_stack_3->SetFillColor(2);
   h_daughter_MuonP_stack_3->SetLineColor(2);
   h_daughter_MuonP_stack_3->SetLineWidth(2);
   h_daughter_MuonP_stack_3->GetXaxis()->SetTitle("Bragg PID K^{+}");
   h_daughter_MuonP_stack_3->GetXaxis()->SetLabelFont(42);
   h_daughter_MuonP_stack_3->GetXaxis()->SetLabelSize(0.035);
   h_daughter_MuonP_stack_3->GetXaxis()->SetTitleSize(0.035);
   h_daughter_MuonP_stack_3->GetXaxis()->SetTitleOffset(1);
   h_daughter_MuonP_stack_3->GetXaxis()->SetTitleFont(42);
   h_daughter_MuonP_stack_3->GetYaxis()->SetTitle("Event");
   h_daughter_MuonP_stack_3->GetYaxis()->SetLabelFont(42);
   h_daughter_MuonP_stack_3->GetYaxis()->SetLabelSize(0.035);
   h_daughter_MuonP_stack_3->GetYaxis()->SetTitleSize(0.035);
   h_daughter_MuonP_stack_3->GetYaxis()->SetTitleFont(42);
   h_daughter_MuonP_stack_3->GetZaxis()->SetLabelFont(42);
   h_daughter_MuonP_stack_3->GetZaxis()->SetLabelSize(0.035);
   h_daughter_MuonP_stack_3->GetZaxis()->SetTitleSize(0.035);
   h_daughter_MuonP_stack_3->GetZaxis()->SetTitleOffset(1);
   h_daughter_MuonP_stack_3->GetZaxis()->SetTitleFont(42);
   hs->Add(h_daughter_MuonP_stack_3,"HIST");
   
   TH1D *h_daughter_MuonM_stack_4 = new TH1D("h_daughter_MuonM_stack_4","",30,0,30);
   h_daughter_MuonM_stack_4->SetBinContent(0,19);
   h_daughter_MuonM_stack_4->SetBinContent(1,325);
   h_daughter_MuonM_stack_4->SetBinError(0,4.358899);
   h_daughter_MuonM_stack_4->SetBinError(1,18.02776);
   h_daughter_MuonM_stack_4->SetEntries(344);
   h_daughter_MuonM_stack_4->SetStats(0);
   h_daughter_MuonM_stack_4->SetFillColor(3);
   h_daughter_MuonM_stack_4->SetLineColor(3);
   h_daughter_MuonM_stack_4->SetLineWidth(2);
   h_daughter_MuonM_stack_4->GetXaxis()->SetTitle("Bragg PID K^{+}");
   h_daughter_MuonM_stack_4->GetXaxis()->SetLabelFont(42);
   h_daughter_MuonM_stack_4->GetXaxis()->SetLabelSize(0.035);
   h_daughter_MuonM_stack_4->GetXaxis()->SetTitleSize(0.035);
   h_daughter_MuonM_stack_4->GetXaxis()->SetTitleOffset(1);
   h_daughter_MuonM_stack_4->GetXaxis()->SetTitleFont(42);
   h_daughter_MuonM_stack_4->GetYaxis()->SetTitle("Event");
   h_daughter_MuonM_stack_4->GetYaxis()->SetLabelFont(42);
   h_daughter_MuonM_stack_4->GetYaxis()->SetLabelSize(0.035);
   h_daughter_MuonM_stack_4->GetYaxis()->SetTitleSize(0.035);
   h_daughter_MuonM_stack_4->GetYaxis()->SetTitleFont(42);
   h_daughter_MuonM_stack_4->GetZaxis()->SetLabelFont(42);
   h_daughter_MuonM_stack_4->GetZaxis()->SetLabelSize(0.035);
   h_daughter_MuonM_stack_4->GetZaxis()->SetTitleSize(0.035);
   h_daughter_MuonM_stack_4->GetZaxis()->SetTitleOffset(1);
   h_daughter_MuonM_stack_4->GetZaxis()->SetTitleFont(42);
   hs->Add(h_daughter_MuonM_stack_4,"HIST");
   
   TH1D *h_daughter_PionP_stack_5 = new TH1D("h_daughter_PionP_stack_5","",30,0,30);
   h_daughter_PionP_stack_5->SetBinContent(0,59);
   h_daughter_PionP_stack_5->SetBinContent(1,2165);
   h_daughter_PionP_stack_5->SetBinError(0,7.681146);
   h_daughter_PionP_stack_5->SetBinError(1,46.52956);
   h_daughter_PionP_stack_5->SetEntries(2224);
   h_daughter_PionP_stack_5->SetStats(0);
   h_daughter_PionP_stack_5->SetFillColor(4);
   h_daughter_PionP_stack_5->SetLineColor(4);
   h_daughter_PionP_stack_5->SetLineWidth(2);
   h_daughter_PionP_stack_5->GetXaxis()->SetTitle("Bragg PID K^{+}");
   h_daughter_PionP_stack_5->GetXaxis()->SetLabelFont(42);
   h_daughter_PionP_stack_5->GetXaxis()->SetLabelSize(0.035);
   h_daughter_PionP_stack_5->GetXaxis()->SetTitleSize(0.035);
   h_daughter_PionP_stack_5->GetXaxis()->SetTitleOffset(1);
   h_daughter_PionP_stack_5->GetXaxis()->SetTitleFont(42);
   h_daughter_PionP_stack_5->GetYaxis()->SetTitle("Event");
   h_daughter_PionP_stack_5->GetYaxis()->SetLabelFont(42);
   h_daughter_PionP_stack_5->GetYaxis()->SetLabelSize(0.035);
   h_daughter_PionP_stack_5->GetYaxis()->SetTitleSize(0.035);
   h_daughter_PionP_stack_5->GetYaxis()->SetTitleFont(42);
   h_daughter_PionP_stack_5->GetZaxis()->SetLabelFont(42);
   h_daughter_PionP_stack_5->GetZaxis()->SetLabelSize(0.035);
   h_daughter_PionP_stack_5->GetZaxis()->SetTitleSize(0.035);
   h_daughter_PionP_stack_5->GetZaxis()->SetTitleOffset(1);
   h_daughter_PionP_stack_5->GetZaxis()->SetTitleFont(42);
   hs->Add(h_daughter_PionP_stack_5,"HIST");
   
   TH1D *h_daughter_PionM_stack_6 = new TH1D("h_daughter_PionM_stack_6","",30,0,30);
   h_daughter_PionM_stack_6->SetBinContent(0,30);
   h_daughter_PionM_stack_6->SetBinContent(1,1251);
   h_daughter_PionM_stack_6->SetBinError(0,5.477226);
   h_daughter_PionM_stack_6->SetBinError(1,35.36948);
   h_daughter_PionM_stack_6->SetEntries(1281);
   h_daughter_PionM_stack_6->SetStats(0);
   h_daughter_PionM_stack_6->SetFillColor(5);
   h_daughter_PionM_stack_6->SetLineColor(5);
   h_daughter_PionM_stack_6->SetLineWidth(2);
   h_daughter_PionM_stack_6->GetXaxis()->SetTitle("Bragg PID K^{+}");
   h_daughter_PionM_stack_6->GetXaxis()->SetLabelFont(42);
   h_daughter_PionM_stack_6->GetXaxis()->SetLabelSize(0.035);
   h_daughter_PionM_stack_6->GetXaxis()->SetTitleSize(0.035);
   h_daughter_PionM_stack_6->GetXaxis()->SetTitleOffset(1);
   h_daughter_PionM_stack_6->GetXaxis()->SetTitleFont(42);
   h_daughter_PionM_stack_6->GetYaxis()->SetTitle("Event");
   h_daughter_PionM_stack_6->GetYaxis()->SetLabelFont(42);
   h_daughter_PionM_stack_6->GetYaxis()->SetLabelSize(0.035);
   h_daughter_PionM_stack_6->GetYaxis()->SetTitleSize(0.035);
   h_daughter_PionM_stack_6->GetYaxis()->SetTitleFont(42);
   h_daughter_PionM_stack_6->GetZaxis()->SetLabelFont(42);
   h_daughter_PionM_stack_6->GetZaxis()->SetLabelSize(0.035);
   h_daughter_PionM_stack_6->GetZaxis()->SetTitleSize(0.035);
   h_daughter_PionM_stack_6->GetZaxis()->SetTitleOffset(1);
   h_daughter_PionM_stack_6->GetZaxis()->SetTitleFont(42);
   hs->Add(h_daughter_PionM_stack_6,"HIST");
   
   TH1D *h_daughter_Shower_stack_7 = new TH1D("h_daughter_Shower_stack_7","",30,0,30);
   h_daughter_Shower_stack_7->SetBinContent(0,137);
   h_daughter_Shower_stack_7->SetBinContent(1,1825);
   h_daughter_Shower_stack_7->SetBinError(0,11.7047);
   h_daughter_Shower_stack_7->SetBinError(1,42.72002);
   h_daughter_Shower_stack_7->SetEntries(1962);
   h_daughter_Shower_stack_7->SetStats(0);
   h_daughter_Shower_stack_7->SetFillColor(6);
   h_daughter_Shower_stack_7->SetLineColor(6);
   h_daughter_Shower_stack_7->SetLineWidth(2);
   h_daughter_Shower_stack_7->GetXaxis()->SetTitle("Bragg PID K^{+}");
   h_daughter_Shower_stack_7->GetXaxis()->SetLabelFont(42);
   h_daughter_Shower_stack_7->GetXaxis()->SetLabelSize(0.035);
   h_daughter_Shower_stack_7->GetXaxis()->SetTitleSize(0.035);
   h_daughter_Shower_stack_7->GetXaxis()->SetTitleOffset(1);
   h_daughter_Shower_stack_7->GetXaxis()->SetTitleFont(42);
   h_daughter_Shower_stack_7->GetYaxis()->SetTitle("Event");
   h_daughter_Shower_stack_7->GetYaxis()->SetLabelFont(42);
   h_daughter_Shower_stack_7->GetYaxis()->SetLabelSize(0.035);
   h_daughter_Shower_stack_7->GetYaxis()->SetTitleSize(0.035);
   h_daughter_Shower_stack_7->GetYaxis()->SetTitleFont(42);
   h_daughter_Shower_stack_7->GetZaxis()->SetLabelFont(42);
   h_daughter_Shower_stack_7->GetZaxis()->SetLabelSize(0.035);
   h_daughter_Shower_stack_7->GetZaxis()->SetTitleSize(0.035);
   h_daughter_Shower_stack_7->GetZaxis()->SetTitleOffset(1);
   h_daughter_Shower_stack_7->GetZaxis()->SetTitleFont(42);
   hs->Add(h_daughter_Shower_stack_7,"HIST");
   
   TH1D *h_daughter_Other_stack_8 = new TH1D("h_daughter_Other_stack_8","",30,0,30);
   h_daughter_Other_stack_8->SetBinContent(0,7);
   h_daughter_Other_stack_8->SetBinContent(1,82);
   h_daughter_Other_stack_8->SetBinError(0,2.645751);
   h_daughter_Other_stack_8->SetBinError(1,9.055385);
   h_daughter_Other_stack_8->SetEntries(89);
   h_daughter_Other_stack_8->SetStats(0);
   h_daughter_Other_stack_8->SetFillColor(7);
   h_daughter_Other_stack_8->SetLineColor(7);
   h_daughter_Other_stack_8->SetLineWidth(2);
   h_daughter_Other_stack_8->GetXaxis()->SetTitle("Bragg PID K^{+}");
   h_daughter_Other_stack_8->GetXaxis()->SetLabelFont(42);
   h_daughter_Other_stack_8->GetXaxis()->SetLabelSize(0.035);
   h_daughter_Other_stack_8->GetXaxis()->SetTitleSize(0.035);
   h_daughter_Other_stack_8->GetXaxis()->SetTitleOffset(1);
   h_daughter_Other_stack_8->GetXaxis()->SetTitleFont(42);
   h_daughter_Other_stack_8->GetYaxis()->SetTitle("Event");
   h_daughter_Other_stack_8->GetYaxis()->SetLabelFont(42);
   h_daughter_Other_stack_8->GetYaxis()->SetLabelSize(0.035);
   h_daughter_Other_stack_8->GetYaxis()->SetTitleSize(0.035);
   h_daughter_Other_stack_8->GetYaxis()->SetTitleFont(42);
   h_daughter_Other_stack_8->GetZaxis()->SetLabelFont(42);
   h_daughter_Other_stack_8->GetZaxis()->SetLabelSize(0.035);
   h_daughter_Other_stack_8->GetZaxis()->SetTitleSize(0.035);
   h_daughter_Other_stack_8->GetZaxis()->SetTitleOffset(1);
   h_daughter_Other_stack_8->GetZaxis()->SetTitleFont(42);
   hs->Add(h_daughter_Other_stack_8,"HIST");
   hs->Draw("hist,same");
   
   TH1D *h_daughter_KaonP_copy__4 = new TH1D("h_daughter_KaonP_copy__4","",30,0,30);
   h_daughter_KaonP_copy__4->SetBinContent(0,19);
   h_daughter_KaonP_copy__4->SetBinContent(1,793);
   h_daughter_KaonP_copy__4->SetBinError(0,4.358899);
   h_daughter_KaonP_copy__4->SetBinError(1,28.16026);
   h_daughter_KaonP_copy__4->SetMinimum(0);
   h_daughter_KaonP_copy__4->SetMaximum(21776.25);
   h_daughter_KaonP_copy__4->SetEntries(812);
   h_daughter_KaonP_copy__4->SetDirectory(0);
   h_daughter_KaonP_copy__4->SetStats(0);
   h_daughter_KaonP_copy__4->SetFillColor(8);
   h_daughter_KaonP_copy__4->SetLineColor(8);
   h_daughter_KaonP_copy__4->SetLineWidth(2);
   h_daughter_KaonP_copy__4->GetXaxis()->SetTitle("Bragg PID K^{+}");
   h_daughter_KaonP_copy__4->GetXaxis()->SetLabelFont(42);
   h_daughter_KaonP_copy__4->GetXaxis()->SetLabelSize(0.045);
   h_daughter_KaonP_copy__4->GetXaxis()->SetTitleSize(0.05);
   h_daughter_KaonP_copy__4->GetXaxis()->SetTitleOffset(0.93);
   h_daughter_KaonP_copy__4->GetYaxis()->SetTitle("Event");
   h_daughter_KaonP_copy__4->GetYaxis()->SetLabelFont(42);
   h_daughter_KaonP_copy__4->GetYaxis()->SetLabelSize(0.045);
   h_daughter_KaonP_copy__4->GetYaxis()->SetTitleSize(0.05);
   h_daughter_KaonP_copy__4->GetYaxis()->SetTitleOffset(1.06);
   h_daughter_KaonP_copy__4->GetZaxis()->SetLabelFont(42);
   h_daughter_KaonP_copy__4->GetZaxis()->SetLabelSize(0.035);
   h_daughter_KaonP_copy__4->GetZaxis()->SetTitleSize(0.035);
   h_daughter_KaonP_copy__4->GetZaxis()->SetTitleOffset(1);
   h_daughter_KaonP_copy__4->GetZaxis()->SetTitleFont(42);
   h_daughter_KaonP_copy__4->Draw("sameaxis");
   
   leg = new TLegend(0.54,0.815,0.885,0.9,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextAlign(32);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   entry=leg->AddEntry("NULL","NuMI FHC, 10.0 #times 10^{20} POT","h");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   leg->Draw();
   
   leg = new TLegend(0.45,0.9,0.89,0.985,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextAlign(32);
   leg->SetTextFont(62);
   leg->SetTextSize(0.05);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   entry=leg->AddEntry("NULL","MicroBooNE Simulation, Preliminary","h");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(62);
   leg->Draw();
   p_plot->Modified();
   c->cd();
   c->Modified();
   c->cd();
   c->SetSelected(c);
}

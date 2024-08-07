void PrimaryPDGDaughterPDG_BySigBGSignal()
{
//=========Macro generated from canvas: c/c
//=========  (Mon Aug  5 12:21:08 2024) by ROOT version 6.16/00
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
   
   TLegend *leg = new TLegend(0.45,0.9,0.89,0.985,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextAlign(32);
   leg->SetTextFont(62);
   leg->SetTextSize(0.05);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("NULL","MicroBooNE Simulation, Preliminary","h");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(62);
   leg->Draw();
   
   leg = new TLegend(0.1,0,0.9,1,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   leg->Draw();
   p_legend->Modified();
   c->cd();
  
// ------------>Primitives in pad: p_plot
   TPad *p_plot = new TPad("p_plot", "p_plot",0,0,1,0.85);
   p_plot->Draw();
   p_plot->cd();
   p_plot->Range(-0.7500001,-0.6741573,6.75,6.067416);
   p_plot->SetFillColor(0);
   p_plot->SetBorderMode(0);
   p_plot->SetBorderSize(2);
   p_plot->SetTopMargin(0.01);
   p_plot->SetFrameBorderMode(0);
   p_plot->SetFrameBorderMode(0);
   
   TH2D *h_Signal = new TH2D("h_Signal","",6,0,6,6,0,6);
   h_Signal->SetBinContent(17,4910);
   h_Signal->SetBinContent(25,968);
   h_Signal->SetEntries(5878);
   h_Signal->SetStats(0);
   h_Signal->SetContour(20);
   h_Signal->SetContourLevel(0,0);
   h_Signal->SetContourLevel(1,245.5);
   h_Signal->SetContourLevel(2,491);
   h_Signal->SetContourLevel(3,736.5);
   h_Signal->SetContourLevel(4,982);
   h_Signal->SetContourLevel(5,1227.5);
   h_Signal->SetContourLevel(6,1473);
   h_Signal->SetContourLevel(7,1718.5);
   h_Signal->SetContourLevel(8,1964);
   h_Signal->SetContourLevel(9,2209.5);
   h_Signal->SetContourLevel(10,2455);
   h_Signal->SetContourLevel(11,2700.5);
   h_Signal->SetContourLevel(12,2946);
   h_Signal->SetContourLevel(13,3191.5);
   h_Signal->SetContourLevel(14,3437);
   h_Signal->SetContourLevel(15,3682.5);
   h_Signal->SetContourLevel(16,3928);
   h_Signal->SetContourLevel(17,4173.5);
   h_Signal->SetContourLevel(18,4419);
   h_Signal->SetContourLevel(19,4664.5);
   
   TPaletteAxis *palette = new TPaletteAxis(6.0375,0,6.375,6,h_Signal);
   palette->SetLabelColor(1);
   palette->SetLabelFont(42);
   palette->SetLabelOffset(0.005);
   palette->SetLabelSize(0.035);
   palette->SetTitleOffset(1);
   palette->SetTitleSize(0.035);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#f9f90e");
   palette->SetFillColor(ci);
   palette->SetFillStyle(1001);
   h_Signal->GetListOfFunctions()->Add(palette,"br");

   ci = TColor::GetColor("#000099");
   h_Signal->SetLineColor(ci);
   h_Signal->GetXaxis()->SetTitle("Primary Track PDG");
   h_Signal->GetXaxis()->SetBinLabel(1,"K^{+}");
   h_Signal->GetXaxis()->SetBinLabel(2,"#mu^{+}");
   h_Signal->GetXaxis()->SetBinLabel(3,"#pi^{+}");
   h_Signal->GetXaxis()->SetBinLabel(4,"proton");
   h_Signal->GetXaxis()->SetBinLabel(5,"shower");
   h_Signal->GetXaxis()->SetBinLabel(6,"Others");
   h_Signal->GetXaxis()->SetLabelFont(42);
   h_Signal->GetXaxis()->SetLabelSize(0.035);
   h_Signal->GetXaxis()->SetTitleSize(0.035);
   h_Signal->GetXaxis()->SetTitleOffset(1);
   h_Signal->GetXaxis()->SetTitleFont(42);
   h_Signal->GetYaxis()->SetTitle("Daughter PDG");
   h_Signal->GetYaxis()->SetBinLabel(1,"K^{+}");
   h_Signal->GetYaxis()->SetBinLabel(2,"#mu^{+}");
   h_Signal->GetYaxis()->SetBinLabel(3,"#pi^{+}");
   h_Signal->GetYaxis()->SetBinLabel(4,"proton");
   h_Signal->GetYaxis()->SetBinLabel(5,"shower");
   h_Signal->GetYaxis()->SetBinLabel(6,"Others");
   h_Signal->GetYaxis()->SetLabelFont(42);
   h_Signal->GetYaxis()->SetLabelSize(0.035);
   h_Signal->GetYaxis()->SetTitleSize(0.035);
   h_Signal->GetYaxis()->SetTitleFont(42);
   h_Signal->GetZaxis()->SetLabelFont(42);
   h_Signal->GetZaxis()->SetLabelSize(0.035);
   h_Signal->GetZaxis()->SetTitleSize(0.035);
   h_Signal->GetZaxis()->SetTitleOffset(1);
   h_Signal->GetZaxis()->SetTitleFont(42);
   h_Signal->Draw("COLZ");
   
   TH2D *h_Signal_copy__1 = new TH2D("h_Signal_copy__1","",6,0,6,6,0,6);
   h_Signal_copy__1->SetBinContent(17,4910);
   h_Signal_copy__1->SetBinContent(25,968);
   h_Signal_copy__1->SetEntries(5878);
   h_Signal_copy__1->SetDirectory(0);
   h_Signal_copy__1->SetStats(0);

   ci = TColor::GetColor("#000099");
   h_Signal_copy__1->SetLineColor(ci);
   h_Signal_copy__1->GetXaxis()->SetTitle("Primary Track PDG");
   h_Signal_copy__1->GetXaxis()->SetBinLabel(1,"K^{+}");
   h_Signal_copy__1->GetXaxis()->SetBinLabel(2,"#mu^{+}");
   h_Signal_copy__1->GetXaxis()->SetBinLabel(3,"#pi^{+}");
   h_Signal_copy__1->GetXaxis()->SetBinLabel(4,"proton");
   h_Signal_copy__1->GetXaxis()->SetBinLabel(5,"shower");
   h_Signal_copy__1->GetXaxis()->SetBinLabel(6,"Others");
   h_Signal_copy__1->GetXaxis()->SetLabelFont(42);
   h_Signal_copy__1->GetXaxis()->SetLabelSize(0.035);
   h_Signal_copy__1->GetXaxis()->SetTitleSize(0.035);
   h_Signal_copy__1->GetXaxis()->SetTitleOffset(1);
   h_Signal_copy__1->GetXaxis()->SetTitleFont(42);
   h_Signal_copy__1->GetYaxis()->SetTitle("Daughter PDG");
   h_Signal_copy__1->GetYaxis()->SetBinLabel(1,"K^{+}");
   h_Signal_copy__1->GetYaxis()->SetBinLabel(2,"#mu^{+}");
   h_Signal_copy__1->GetYaxis()->SetBinLabel(3,"#pi^{+}");
   h_Signal_copy__1->GetYaxis()->SetBinLabel(4,"proton");
   h_Signal_copy__1->GetYaxis()->SetBinLabel(5,"shower");
   h_Signal_copy__1->GetYaxis()->SetBinLabel(6,"Others");
   h_Signal_copy__1->GetYaxis()->SetLabelFont(42);
   h_Signal_copy__1->GetYaxis()->SetLabelSize(0.035);
   h_Signal_copy__1->GetYaxis()->SetTitleSize(0.035);
   h_Signal_copy__1->GetYaxis()->SetTitleFont(42);
   h_Signal_copy__1->GetZaxis()->SetLabelFont(42);
   h_Signal_copy__1->GetZaxis()->SetLabelSize(0.035);
   h_Signal_copy__1->GetZaxis()->SetTitleSize(0.035);
   h_Signal_copy__1->GetZaxis()->SetTitleOffset(1);
   h_Signal_copy__1->GetZaxis()->SetTitleFont(42);
   h_Signal_copy__1->Draw("sameaxis");
   p_plot->Modified();
   c->cd();
   c->Modified();
   c->cd();
   c->SetSelected(c);
}

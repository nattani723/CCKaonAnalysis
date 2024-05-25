#ifndef _DrawEfficiencyPlot_h_
#define _DrawEfficiencyPlot_h_

#include "TFile.h"
#include "TH1D.h"
#include "Misc.h"
#include "TText.h"
#include "TLatex.h"
#include "TGraphAsymmErrors.h"
#include "TGaxis.h"
#include "FluxWeight2.h"
#include "TMatrixDSym.h"
#include "EventType.h"

using std::string;
using std::vector;

//const double _EPSILON_ = 1e-5;

//namespace HypPlot {

   bool DrawWatermark = true;

   // Single panel axis settings etc.

   const double Single_CanvasX = 800;
   const double Single_CanvasY = 600; 
   const double Single_PadSplit = 0.85; // Height at which to split the cavas into plot/legend

   const double Single_XaxisTitleSize = 0.05;
   const double Single_YaxisTitleSize = 0.05;
   const double Single_XaxisTitleOffset = 0.93;
   const double Single_YaxisTitleOffset = 1.06;
   const double Single_XaxisLabelSize = 0.045;
   const double Single_YaxisLabelSize = 0.045;

   const double Single_TextLabelSize = 0.09; // Label size if bin labels are used

   // Two panel axis settings etc.

   const double Dual_CanvasX = 800;
   const double Dual_CanvasY = 750; 
   const double Dual_PadSplitLow = 0.3; // Height at which to split the canvas between the ratio and the main plot
   const double Dual_PadSplitHigh = 0.9; // Height at which to split the canvas between the main plot and the legend

   const double Dual_MainXaxisTitleSize = 0;
   const double Dual_MainYaxisTitleSize = 0.065;
   const double Dual_MainXaxisTitleOffset = 0;
   const double Dual_MainYaxisTitleOffset = 0.8;
   const double Dual_MainXaxisLabelSize = 0;
   const double Dual_MainYaxisLabelSize = 0.05;

   const double Dual_RatioXaxisTitleSize = 0.12;
   const double Dual_RatioYaxisTitleSize = 0.12;
   const double Dual_RatioXaxisTitleOffset = 0.8;
   const double Dual_RatioYaxisTitleOffset = 0.43;
   const double Dual_RatioXaxisLabelSize = 0.1;
   const double Dual_RatioYaxisLabelSize = 0.1;

   const double Dual_TextLabelSize = 0.17; // Label size if bin labels are used

   // Matrix axis settings etc.

   const double Matrix_CanvasX = 800;
   const double Matrix_CanvasY = 600; 

   const double Matrix_XaxisTitleSize = 0.05;
   const double Matrix_YaxisTitleSize = 0.05;
   const double Matrix_XaxisTitleOffset = 0.93;
   const double Matrix_YaxisTitleOffset = 1.02;
   const double Matrix_XaxisLabelSize = 0.045;
   const double Matrix_YaxisLabelSize = 0.045;
   const double Matrix_ZaxisLabelSize = 0.045;

   const double Matrix_TextLabelSize = 0.07;

   const int GoodLineColors[13] = {1,2,8,4,6,38,46,43,30,9,7,14,3};

///////////////////////////////////////////////////////////////////////////////////////////////

void DontDrawWatermark(){

   DrawWatermark = false;

}

///////////////////////////////////////////////////////////////////////////////////////////////

// Get the maximum of a histogram including error bars

double GetHistMaxError(TH1D *h){

   double max = -1e10;

   for(int i_b=1;i_b<h->GetNbinsX()+1;i_b++)
      if(h->GetBinContent(i_b)+h->GetBinError(i_b) > max)
         max = h->GetBinContent(i_b)+h->GetBinError(i_b);

   return max;
}

///////////////////////////////////////////////////////////////////////////////////////////////

// Get the maximum of a histogram not including the errors

double GetHistMax(TH1D *h){

   double max = -1e10;

   for(int i_b=1;i_b<h->GetNbinsX()+1;i_b++)
      if(h->GetBinContent(i_b) > max)
         max = h->GetBinContent(i_b);

   return max;
}

///////////////////////////////////////////////////////////////////////////////////////////////

// Make a 2D histogram from a TMatrix object
// Uses h_example for the bin widths, axis titles etc.

TH2D* MakeHistogram(TMatrixD Mat,TH2D* h_example,string Name=""){

   TH2D* h_Mat = (TH2D*)h_example->Clone(("h_" + Name).c_str());
   const int nbins = h_Mat->GetNbinsX();

   for(int i=1;i<nbins+1;i++)
      for(int j=1;j<nbins+1;j++)
         h_Mat->SetBinContent(i,j,Mat[i-1][j-1]);

   return h_Mat; 
}

///////////////////////////////////////////////////////////////////////////////////////////////

// Make a TGraph object from a vector containing the x positions of data events in 
// some variable

TGraph* MakeDataGraph(std::vector<double> data_v){

   std::vector<Double_t> Y(data_v.size(),0.0); 

   TGraph* g = new TGraph(data_v.size(),&(data_v[0]),&(Y[0]));
   g->SetMarkerStyle(23);
   g->SetMarkerSize(3);

   return g;
}

///////////////////////////////////////////////////////////////////////////////////////////////

// Draw a stack of histograms of efficiency and #events passed selection
// If you anto to include systematic uncertainties in the MC, make sure they're already included
// in the error of h_errors
// Inputs:
// hist_v = the stack of histograms you want to draw
// h_errors = the total MC prediction with uncertainties
// captions = list of what should be added to the legend for each histogram
// plotdir = the directory to write the plots into
// label = label to be added the front of the plot
// mode = FHC/RHC/BNB
// run = 1,3 or 13 (for 1+3)
// POT = the POT used 
// signalscale = scaling for the signal
// hasdata = flag indicating if there is data in the stack of histograms
// colors = list of colors for the histograms
// binlabels = bin labels
// chi2ndof = chi2 and degrees of freedom if applicable
// data_v list of x positions of individual data events (used for signal box plots only)

 void DrawEfficiencyPlot(TH1D * h_All, TH1D * h_Selected, TEfficiency * Efficiency, string title, string label, int Mode, double POT)
 {

   std::string plotdir = "PhaseSpacePlots";

   const int nbins = h_All->GetNbinsX();

   // Setup the canvas
   TCanvas *c = new TCanvas("c","c",Single_CanvasX,Single_CanvasY);
   TPad *p_plot = new TPad("p_plot","p_plot",0,0,1,Single_PadSplit);
   TPad *p_legend = new TPad("p_legend","p_legend",0,Single_PadSplit,1,1);
   p_legend->SetBottomMargin(0);
   p_legend->SetTopMargin(0.1);
   p_plot->SetTopMargin(0.01);

   THStack *hs = new THStack("hs",title.c_str());

   // Create the empty legend
   TLegend *l = new TLegend(0.1,0.0,0.9,1.0);
   l->SetBorderSize(0);
   int ncols = 2;
   l->SetNColumns(ncols);

   //TH1D* h_Eff = (TH1D*)Efficiency->GetCopyPassedHisto();
   TH1D* h_Eff = (TH1D*)h_All->Clone("h_Eff");
   h_Eff->Reset(); 
   h_Eff->SetTitle("Efficiency");

   TH1D *h_PassedSignal = (TH1D*)Efficiency->GetPassedHistogram();
   TH1D *h_TotalSignal = (TH1D*)Efficiency->GetTotalHistogram();

   //std::cout << "h_TotalSignal: " << h_TotalSignal->GetNbinsX() << std::endl;
   
   for(int i_c=0; i_c<h_Eff->GetNbinsX()+1;i_c++){
     //std::cout << "Efficiency->GetEfficiency(i_c+1): " << Efficiency->GetEfficiency(i_c+1) << std::endl;
     //h_Eff->Fill(i_c, Efficiency->GetEfficiency(i_c+1));
     double eff = Efficiency->GetEfficiency(i_c+1);
     double eff_err_up = Efficiency->GetEfficiencyErrorUp(i_c+1);
     double eff_err_low = Efficiency->GetEfficiencyErrorLow(i_c+1);
     h_Eff->SetBinContent(i_c, eff);
     h_Eff->SetBinError(i_c, eff_err_up);
   }

   /*
   TH1D* h_Ratio = (TH1D*)h_Selected->Clone("h_Ratio");
   h_Ratio->Divide(h_All);
   h_Ratio->SetTitle("Selected/All");
   */

   TH1D *h_Ratio = (TH1D*)h_All->Clone("h_Ratio");
   h_Ratio->SetTitle("Selected/All");

   for (int i = 1; i <= h_All->GetNbinsX(); ++i) {
     double N = h_Selected->GetBinContent(i);
     double D = h_All->GetBinContent(i);
     double sigma_N = h_Selected->GetBinError(i);
     double sigma_D = h_All->GetBinError(i);

     if (D != 0) {  // To avoid division by zero
       double R = N / D;
       double sigma_R = R * sqrt((sigma_N / N) * (sigma_N / N) + (sigma_D / D) * (sigma_D / D));
       h_Ratio->SetBinContent(i, R);
       h_Ratio->SetBinError(i, sigma_R);
     } else {
       h_Ratio->SetBinContent(i, 0);
       h_Ratio->SetBinError(i, 0);
     }
   }

   h_All->SetLineColor(kBlack);
   h_All->SetLineWidth(2);

   h_Selected->SetLineColor(kBlue);
   h_Selected->SetLineWidth(2);

   h_Eff->SetLineColor(kRed);
   h_Eff->SetLineWidth(2);
   h_Eff->SetMarkerColor(kRed);
   h_Eff->SetMarkerStyle(20);
   //h_Eff->SetMarkerSize(2.0);

   h_Ratio->SetLineColor(kRed);
   h_Ratio->SetLineWidth(2);
   h_Ratio->SetMarkerColor(kRed);
   h_Ratio->SetMarkerStyle(20);
   //h_Ratio->SetMarkerSize(2.0);

   l->AddEntry(h_All,"All Events","l");
   l->AddEntry(h_Selected,"Selected Events","l");
   l->AddEntry(h_Eff,"Selected/All","l");
   l->SetTextSize(0.2);

   // Create the "MicroBooNE" watermark
   TLegend *l_Watermark = new TLegend(0.45,0.900,0.89,0.985);
   l_Watermark->SetBorderSize(0);
   l_Watermark->SetMargin(0.005);
   l_Watermark->SetTextAlign(32);
   l_Watermark->SetTextSize(0.05);
   l_Watermark->SetTextFont(62);
   l_Watermark->SetHeader("MicroBooNE Simulation, Preliminary","R");


   // Create the POT label
   //TLegend *l_POT = new TLegend(0.54,0.815,0.885,0.900);
   TLegend *l_POT,*l_POT2;
   if(DrawWatermark) l_POT = new TLegend(0.54,0.815,0.885,0.900);
   else l_POT = new TLegend(0.54,0.900,0.885,0.985);
   l_POT->SetBorderSize(0);
   l_POT->SetMargin(0.005);
   l_POT->SetTextAlign(32);
   if(DrawWatermark) l_POT2 = new TLegend(0.536,0.735,0.886,0.815,NULL,"brNDC");
   else l_POT2 = new TLegend(0.536,0.815,0.886,0.900,NULL,"brNDC");
   //TLegend *l_POT2 = new TLegend(0.54,0.735,0.89,0.815,NULL,"brNDC");
   l_POT2->SetBorderSize(0);
   l_POT2->SetMargin(0.005);
   l_POT2->SetTextAlign(32);


   if(Mode == kFHC) l_POT->SetHeader(("NuMI FHC, " + to_string_with_precision(POT/1e20,1) + " #times 10^{20} POT").c_str());
   else if(Mode == kRHC) l_POT->SetHeader(("NuMI RHC, " + to_string_with_precision(POT/1e20,1) + " #times 10^{20} POT").c_str());
   else if(Mode == kBNB) l_POT->SetHeader(("BNB, " + to_string_with_precision(POT/1e20,1) + " #times 10^{20} POT").c_str());

   /*
   if(mode.size() == 2 && mode.at(1) == kFHC) l_POT2->SetHeader(("NuMI FHC, " + to_string_with_precision(POT.at(1)/1e20,1) + " #times 10^{20} POT").c_str());
   else if(mode.size() == 2 && mode.at(1) == kRHC) l_POT2->SetHeader(("NuMI RHC, " + to_string_with_precision(POT.at(1)/1e20,1) + " #times 10^{20} POT").c_str());
   else if(mode.size() == 2 && mode.at(0) == kBNB && mode.at(1) == kBNB) l_POT->SetHeader(("BNB, " + to_string_with_precision(POT.at(0) + POT.at(1)/1e20,1) + " #times 10^{20} POT").c_str());
   */


   // Draw everything
   p_legend->Draw();
   p_legend->cd();
   l->Draw();
   c->cd();
   p_plot->Draw();
   p_plot->cd();

   h_All->SetTitle(title.c_str());
   hs->Add(h_All,"");
   hs->Add(h_Selected,"");
   hs->Draw("nostack, e");
   //gPad->Update();
   c->Modified();
   c->Update();

   Float_t rightmax = 1.1;
   //Float_t rightmax = 1.1 * h_Eff->GetMaximum();
   Float_t scale = gPad->GetUymax()/rightmax;
   h_Ratio->Scale(scale);
   h_Ratio->SetStats(0);
   h_Ratio->Draw("same, ep");

   //draw an axis on the right side
   TGaxis*axis = new TGaxis(gPad->GetUxmax(),gPad->GetUymin(),
                            gPad->GetUxmax(),gPad->GetUymax(),
                            0,rightmax,510,"+L");
   axis->SetLineColor(kRed);
   axis->SetLabelColor(kRed);
   axis->SetTitle("Selected/All");
   axis->SetTitleColor(kRed);
   axis->Draw();

   p_plot->RedrawAxis();

   // Draw the various legends, labels etc.
   l_POT->Draw();
   if(DrawWatermark) l_Watermark->Draw();


   c->cd();
   system(("mkdir -p " + plotdir).c_str());
   c->Print((plotdir + "/" + label + ".png").c_str());
   c->Print((plotdir + "/" + label + ".pdf").c_str());
   c->Print((plotdir + "/" + label + ".C").c_str());
   c->Clear();
   c->Close();

 }

 //};

#endif

R__LOAD_LIBRARY($HYP_TOP/lib/libHyperon.so)
R__LOAD_LIBRARY($HYP_TOP/lib/libParticleDict.so)

#include "TGraphAsymmErrors.h"

#include "SelectionManager.h"
#include "EventAssembler.h"
#include "Cut.h"
#include "SelectionParameters.h"
#include "Parameters.h"
#include "SampleSets_Example.h"

#include "BayesianPosteriorPDF.h"

   // Produces graph with efficiency, purity and S/sqrt(S+B)
   // for each step of the selection and prints lots of
   // performance metrics.

   void SelectionPerformance(){

      // Diables TEfficiency warnings
      gErrorIgnoreLevel = kWarning;

      double POT = 1.0e21; // POT to scale samples to

      BuildTunes();

      SelectionParameters P = P_FHC_K_NOBDT_TEST;

      SampleNames.push_back("AssocKaon"); 
      SampleTypes.push_back("AssocKaon"); 
      SampleFiles.push_back("/exp/uboone/data/users/taniuchi/ntuple_testarea/assok_KaonTrees.root");
//exp/uboone/app/users/taniuchi/51_pandora/srcs/ubana/ubana/CCKaonProduction/testarea/KaonTrees.root");

      SampleNames.push_back("GENIE Background"); 
      SampleTypes.push_back("Background");
      SampleFiles.push_back("/exp/uboone/data/users/taniuchi/ntuple_testarea/NuMI_sample0_KaonTrees_0_2894.root");

      bool hasdata=false;

      std::string label = "eff_BG_cuts";
      std::string plotdir = "Plots";

      EventAssembler E;
      SelectionManager M(P);
      M.SetPOT(POT);

      //M.ImportBDTWeights(P.p_BDT_WeightsDir);;

      TEfficiency* Eff = new TEfficiency("Eff","",5,-0.5,4.5);
      TEfficiency* Background_Acceptance = new TEfficiency("Background_Acceptance","",5,-0.5,4.5);

      TH1D* h_Eff = new TH1D("Eff_hist","",5,-0.5,4.5);
      TH1D* h_BG = new TH1D("BG_hist","",5,-0.5,4.5);
      TH1D* h_Data = new TH1D("Data_hist","",5,-0.5,4.5);

      // when you change the num of cuts, modify the eff nbin
      /*
      TEfficiency* Eff = new TEfficiency("Eff","",6,-0.5,5.5);
      TEfficiency* Background_Acceptance = new TEfficiency("Background_Acceptance","",6,-0.5,5.5);
      */

      Eff->SetConfidenceLevel(0.6827); // Set to 68.27% confidence level, typical for 1 sigma in physics
      Efficiency->SetStatisticOption(TEfficiency::kBUniform);
      Efficiency->SetPosteriorMode();
      Background_Acceptance->SetConfidenceLevel(0.6827);


      // Sample Loop
      for(size_t i_s=0;i_s<SampleNames.size();i_s++){

	E.SetFile(SampleFiles.at(i_s), "KAON");
	
	if( SampleTypes.at(i_s) == "AssocKaon") M.AddSample("AssocKaon","AssocKaon",POT);
	//if(SampleTypes.at(i_s) != "EXT" && SampleTypes.at(i_s) != "Data") M.AddSample(SampleNames.at(i_s),SampleTypes.at(i_s),E.GetPOT());
	else if(SampleTypes.at(i_s) == "Data") M.AddSample(SampleNames.at(i_s),SampleTypes.at(i_s),Data_POT);
	else if(SampleTypes.at(i_s) == "EXT") M.AddSample(SampleNames.at(i_s),SampleTypes.at(i_s),EXT_POT);

      	M.UseFluxWeight(false);
	M.UseGenWeight(false);

         // Event Loop
         for(int i=0;i<E.GetNEvents();i++){

            if(i % 10000 == 0) std::cout << "Processing event " << i << "/" << E.GetNEvents() << std::endl;

            Event e = E.GetEvent(i);
            M.SetSignal(e);                
            M.AddEvent(e);

            bool passed_FV=false, passed_NuCCFilter=false, passed_NDaughterTrack=false, passed_DaughterFV=false, passed_BDTCut=false;
            //bool passed_DaughterTrackLength=false;

            passed_FV = M.FiducialVolumeCut(e);
            if(passed_FV) passed_NuCCFilter = M.NuCCInclusiveFilter(e);
            if(passed_NuCCFilter) passed_NDaughterTrack = M.DaughterTrackCut(e);
            if(passed_NDaughterTrack) passed_DaughterFV = M.DaughterFiducialVolumeCut(e);
            //if(passed_DaughterFV) passed_BDTCut = M.BDTCut(e);
            //if(passed_BDTCut) passed_DaughterTrackLength = M.DaughterTrackLengthCut(e);


            if(e.EventIsSignal){
               Eff->FillWeighted(true,e.Weight,0);
               Eff->FillWeighted(passed_FV,e.Weight,1);
               Eff->FillWeighted(passed_NuCCFilter,e.Weight,2);
               Eff->FillWeighted(passed_NDaughterTrack,e.Weight,3);
               Eff->FillWeighted(passed_DaughterFV,e.Weight,4);
               //Eff->FillWeighted(passed_BDTCut,e.Weight,5);
               //Eff->FillWeighted(passed_DaughterTrackLength ,e.Weight,6);

            }
            else {
               Background_Acceptance->FillWeighted(true,e.Weight,0);
               Background_Acceptance->FillWeighted(passed_FV,e.Weight,1);
               Background_Acceptance->FillWeighted(passed_NuCCFilter,e.Weight,2);
               Background_Acceptance->FillWeighted(passed_NDaughterTrack,e.Weight,3);
               Background_Acceptance->FillWeighted(passed_DaughterFV,e.Weight,4);
               //Background_Acceptance->FillWeighted(passed_BDTCut,e.Weight,5);
               //Background_Acceptance->FillWeighted(passed_DaughterTrackLength ,e.Weight,6);
            }
         }
         E.Close();
      }

      /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

      std::cout << std::endl << std::endl << "Trying New Estimators" << std::endl;

      TCanvas *c2 = new TCanvas("c2","c2");

      TH1D *h_PassedSignal = (TH1D*)Eff->GetPassedHistogram();
      TH1D *h_TotalSignal = (TH1D*)Eff->GetTotalHistogram();
      TH1D *h_PassedBackground = (TH1D*)Background_Acceptance->GetPassedHistogram();
      TH1D *h_TotalBackground = (TH1D*)Background_Acceptance->GetTotalHistogram();

      Eff->SetStatisticOption(TEfficiency::kBUniform);
      Background_Acceptance->SetStatisticOption(TEfficiency::kBUniform);
      Background_Acceptance->SetPosteriorMode();

      for(int i_c=1;i_c<h_PassedSignal->GetNbinsX()+1;i_c++){
         std::cout << std::endl << "Cut Number " << i_c << std::endl;
         std::cout << "Total Signal = " << h_TotalSignal->GetBinContent(i_c) << "  Signal Passed = " << h_PassedSignal->GetBinContent(i_c) << std::endl;
         std::cout << "Total Background = " << h_TotalBackground->GetBinContent(i_c) << "  Background Passed = " << h_PassedBackground->GetBinContent(i_c) << std::endl;
         std::cout << "Signal Efficiency = " << Eff->GetEfficiency(i_c) << " + " << Eff->GetEfficiencyErrorUp(i_c) << " - " << Eff->GetEfficiencyErrorLow(i_c) << std::endl;
         std::cout << "Background Acceptance = " << Background_Acceptance->GetEfficiency(i_c) << " + " << Background_Acceptance->GetEfficiencyErrorUp(i_c) << " - " << Background_Acceptance->GetEfficiencyErrorLow(i_c) << std::endl;

         std::cout << "Selected Signal = " << h_TotalSignal->GetBinContent(i_c)*Eff->GetEfficiency(i_c)  << " + " << h_TotalSignal->GetBinContent(i_c)*Eff->GetEfficiencyErrorUp(i_c) << " - " << h_TotalSignal->GetBinContent(i_c)*Eff->GetEfficiencyErrorLow(i_c) << std::endl;
         std::cout << "Selected Background = " << h_TotalBackground->GetBinContent(i_c)*Background_Acceptance->GetEfficiency(i_c) << " + " << h_TotalBackground->GetBinContent(i_c)*Background_Acceptance->GetEfficiencyErrorUp(i_c) << " - " << h_TotalBackground->GetBinContent(i_c)*Background_Acceptance->GetEfficiencyErrorLow(i_c) << std::endl;
	 h_Eff->Fill(i_c-1, Eff->GetEfficiency(i_c));
	 h_BG->Fill(i_c-1, Background_Acceptance->GetEfficiency(i_c));
      }
      std::cout << std::endl << std::endl;

      gSystem->Exec("mkdir -p rootfiles");
      TFile *f_out = TFile::Open(("rootfiles/Expected_Events_" + label + ".root").c_str(),"RECREATE");

      TH1D *h_ExpectedSignal = PosteriorPDF(Eff,5,"Signal");//need to change nbin if you change selection criteria
      TH1D *h_ExpectedBackground = PosteriorPDF(Background_Acceptance,5,"Background");

      h_ExpectedSignal->Write();
      h_ExpectedBackground->Write();

      f_out->Close();

      // Your existing setup for histogram drawing
      TCanvas *c = new TCanvas("c","Canvas",600,600);
      c->cd();

      // Assuming h_Eff and h_BG are already created and configured
      h_Eff->SetLineWidth(2);
      h_Eff->SetLineColor(kBlue);
      h_Eff->SetStats(0);
      h_Eff->GetYaxis()->SetRangeUser(0.0,1.1); // Ensure the range includes all possible values
      h_Eff->GetYaxis()->SetTitle("Efficiency"); // Set y-axis label
      h_Eff->Draw("HIST");

      h_BG->SetLineWidth(2);
      h_BG->SetLineColor(kRed);
      h_BG->SetStats(0);
      h_BG->Draw("SAME,HIST");

      // Custom bin labels
      h_Eff->GetXaxis()->SetBinLabel(1, "cut1");
      h_Eff->GetXaxis()->SetBinLabel(2, "cut2");
      h_Eff->GetXaxis()->SetBinLabel(3, "cut3");
      h_Eff->GetXaxis()->SetBinLabel(4, "cut4");
      h_Eff->GetXaxis()->SetBinLabel(5, "cut5");

      // Ensure the axis labels are visible and not cut off
      //h_Eff->GetXaxis()->LabelsOption("v"); // Optionally rotate labels if needed
      h_Eff->GetXaxis()->SetLabelSize(0.06); // Adjust label size as necessary

      // Redraw histograms to apply label settings
      // Draw legends, canvas saving, etc., as before
      TLegend *l = new TLegend(0.5,0.5,0.7,0.7);
      l->SetBorderSize(0);
      l->SetFillColor(0);
      l->SetTextSize(0.03);
      l->AddEntry(h_Eff, "Efficiency", "l");
      l->AddEntry(h_BG, "Accepted Background", "l");
      if (hasdata) {
	h_Data->SetLineWidth(2);
	h_Data->SetLineColor(kBlack);
	h_Data->SetMarkerStyle(20);
	h_Data->SetMarkerColor(kBlack);
	l->AddEntry(h_Data, ("Data = " + to_string_with_precision(h_Data->Integral(), 1)).c_str(), "P");
	h_Data->Draw("E1 P SAME");
      }

      c->cd();

      l->Draw();
      h_Eff->Draw("SAME, HIST");
      h_BG->Draw("SAME,HIST");

      c->Modified();
      c->Update();

      // Save the plot
      system(("mkdir -p " + plotdir).c_str());
      c->Print((plotdir + "/" + label + ".png").c_str());
      c->Print((plotdir + "/" + label + ".pdf").c_str());


   }

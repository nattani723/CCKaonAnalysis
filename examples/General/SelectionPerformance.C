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
      SampleFiles.push_back("/exp/uboone/app/users/taniuchi/51_pandora/srcs/ubana/ubana/CCKaonProduction/testarea/KaonTrees.root");

      SampleNames.push_back("GENIE Background"); 
      SampleTypes.push_back("Background");
      SampleFiles.push_back("/exp/uboone/data/users/taniuchi/taniuchi/KaonTrees.root");

      std::string label = "test";

      EventAssembler E;
      SelectionManager M(P);
      M.SetPOT(POT);

      M.ImportBDTWeights(P.p_BDT_WeightsDir);;

      TEfficiency* Eff = new TEfficiency("Eff","",6,-0.5,5.5);
      TEfficiency* Background_Acceptance = new TEfficiency("Background_Acceptance","",6,-0.5,5.5);

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
            if(passed_DaughterFV) passed_BDTCut = M.BDTCut(e);
            //if(passed_BDTCut) passed_DaughterTrackLength = M.DaughterTrackLengthCut(e);


            if(e.EventIsSignal){
               Eff->FillWeighted(true,e.Weight,0);
               Eff->FillWeighted(passed_FV,e.Weight,1);
               Eff->FillWeighted(passed_NuCCFilter,e.Weight,2);
               Eff->FillWeighted(passed_NDaughterTrack,e.Weight,3);
               Eff->FillWeighted(passed_DaughterFV,e.Weight,4);
               Eff->FillWeighted(passed_BDTCut,e.Weight,5);
               //Eff->FillWeighted(passed_DaughterTrackLength ,e.Weight,6);
            }
            else {
               Background_Acceptance->FillWeighted(true,e.Weight,0);
               Background_Acceptance->FillWeighted(passed_FV,e.Weight,1);
               Background_Acceptance->FillWeighted(passed_NuCCFilter,e.Weight,2);
               Background_Acceptance->FillWeighted(passed_NDaughterTrack,e.Weight,3);
               Background_Acceptance->FillWeighted(passed_DaughterFV,e.Weight,4);
               Background_Acceptance->FillWeighted(passed_BDTCut,e.Weight,5);
               //Background_Acceptance->FillWeighted(passed_DaughterTrackLength ,e.Weight,6);
            }
         }
         E.Close();
      }

      /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

      std::cout << std::endl << std::endl << "Trying New Estimators" << std::endl;

      TCanvas *c2 = new TCanvas("c","c");

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
      }
      std::cout << std::endl << std::endl;

      gSystem->Exec("mkdir -p rootfiles");
      TFile *f_out = TFile::Open(("rootfiles/Expected_Events_" + label + ".root").c_str(),"RECREATE");

      TH1D *h_ExpectedSignal = PosteriorPDF(Eff,6,"Signal");
      TH1D *h_ExpectedBackground = PosteriorPDF(Background_Acceptance,6,"Background");

      h_ExpectedSignal->Write();
      h_ExpectedBackground->Write();  

      f_out->Close();

   }

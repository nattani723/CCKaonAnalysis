R__LOAD_LIBRARY($HYP_TOP/lib/libHyperon.so)
R__LOAD_LIBRARY($HYP_TOP/lib/libParticleDict.so)

#include "SelectionManager.h"
#include "EventAssembler.h"
#include "Cut.h"
#include "SelectionParameters.h"

#include "Parameters.h"
#include "SampleSets_Example.h"

   void BDTCutTest(){

  std::string label = "BDTScore";//select the name?
  double POT = 1.0e21; // POT to scale samples to
  
  BuildTunes();
  SelectionParameters P = P_FHC_K_NOBDT_TEST;
  
  SampleNames.push_back("AssocKaon"); 
  SampleTypes.push_back("AssocKaon"); 
  SampleFiles.push_back("/exp/uboone/data/users/taniuchi/taniuchi/pandora_alg/ana/assok_refined_KrecoAlg_parameter8_ntuple.root");
  
  /*
    SampleNames.push_back("GENIE Background"); 
    SampleTypes.push_back("Background");
    SampleFiles.push_back("/exp/uboone/data/users/taniuchi/taniuchi/KaonTrees.root");

    SampleNames.push_back("GENIE Background");
    SampleTypes.push_back("Background");
    SampleFiles.push_back("run1_FHC/analysisOutputFHC_Overlay_GENIE_Background_All.root");
    
    SampleNames.push_back("GENIE Hyperon");
    SampleTypes.push_back("Hyperon");
    SampleFiles.push_back("run1_FHC/analysisOutputFHC_Overlay_GENIE_Hyperon_All.root");
  */
  
  EventAssembler E;
  SelectionManager M(P);
  M.SetPOT(POT);
  M.ImportBDTWeights("/exp/uboone/app/users/taniuchi/51_pandora/CCKaonAnalysis/examples/TMVA/dataset/weights/");

  // Setup the histograms
  M.SetupHistograms(20,-1,1,";BDT Score;Events");
  M.SetupHistogramsEtoP();
  
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

      if(i % 10000 == 0) std::cout << i << "/" << E.GetNEvents() << std::endl;
      
      Event e = E.GetEvent(i);
      
      M.SetSignal(e);
      M.AddEvent(e);
      
      if(!M.FiducialVolumeCut(e)) continue;
      if(!M.NuCCInclusiveFilter(e)) continue;
      if(!M.DaughterTrackCut(e)) continue;
      if(!M.DaughterFiducialVolumeCut(e)) continue;

      for (const auto& pair : M.VectorPair) {
	RecoParticle PrimaryKaonTrackParticle = pair.first;
	RecoParticle DaughterTrackParticle = pair.second;
	M.BDTCut(e,PrimaryKaonTrackParticle,DaughterTrackParticle);
      
	double bdt = e.BDTScore;
	std::cout << "BDT: " << bdt << std::endl;
	
	M.FillHistograms(e,bdt);//add weight
	M.FillHistogramsEtoP(e,bdt,PrimaryKaonTrackParticle,DaughterTrackParticle,e.Weight);
      }      
      
    }
    E.Close();
  }

  M.FillEtoPCurve();
  M.PlotEtoPCurve();

  M.DrawHistograms(label);

  /*
  //we want to calculate efficiency and purity for BDT signal/BG
  //->this can be done by Hist_All
  //if(e.GoodReco && PrimaryKaonTrackParticle.Index == e.TrueKaonIndex && ( DaughterTrackParticle.Index == e.TrueDecayMuonIndex ||  DaughterTrackParticle.Index == e.TrueDecayPionIndex ))
  //stack histos for signal and various BG
  //->this can be done by M.DrawHistograms(label);

  nbin = Hist_BDT_All->GetNBinsX();
  double denominator = Hist_BDT_All->Integral(1,nbin+1);
  for (int bin=1; bin<=nbin+1; bin++) { 
    double signal = Hist_BDT_Signal->Integral(bin,nbin+1);
    double all = Hist_BDT_All->Integral(bin,nbin+1);
    double efficiency = denominator>0 ? signal/denominator : 0;
    double purity = all>0 ? signal/all : 0;
    Hist_Efficiency->SetBinContent(bin,efficiency);
    Hist_Purity->SetBinContent(bin,purity);
    Hist_EtoP->SetBinContent(bin, efficiency*purity);
  }


  TString output_pdf_bdtcut = "BDT_opt_cut.pdf";

  TCanvas * c = new TCanvas();
  c->SetFillStyle(4000); 

  Hist_Efficiency->SetMinimum(0);
  Hist_Efficiency->SetMaximum(1);
  Hist_Efficiency->Draw("C");
  Hist_Purity->Draw("C,SAME");
  Hist_EtoP->Draw("C,SAME");

  TLegend * legend = new TLegend(0.65,0.7,0.85,0.85); 
  legend->AddEntry(Hist_Efficiency,"Efficiency","l");
  legend->AddEntry(Hist_Purity,"Purity","l");
  legend->AddEntry(Hist_EtoP,"Eff. #times Pur.","l");
  legend->Draw();
  c->Print(output_pdf_bdtcut);
  */
}

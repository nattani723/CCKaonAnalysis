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

double GetVariableValue(const RecoParticle& particle, const std::string& variableName) {
  
  if (variableName == "TrackLength") {
    return particle.TrackLength;
  }
  else if (variableName == "LLRPID") {
    return particle.Track_LLR_PID;
  }
  else if (variableName == "LLRPIDKaon") {
    return particle.Track_LLR_PID_Kaon;
  }
  else if (variableName == "Chi2KaonPlane2") {
    return particle.Track_Chi2_Kaon_Plane2;
  }
  else if (variableName == "Chi2ProtonPlane2") {
    return particle.Track_Chi2_Proton_Plane2;
	  }
  else if (variableName == "Chi2MuonPlane2") {
    return particle.Track_Chi2_Muon_Plane2;
  }
  else if (variableName == "Chi2PionPlane2") {
    return particle.Track_Chi2_Pion_Plane2;
  }
  else if (variableName == "Chi2Kaon3Plane") {
    return particle.Track_Chi2_Kaon_3Plane;
  }
  else if (variableName == "Chi2Proton3Plane") {
    return particle.Track_Chi2_Proton_3Plane;
  }
  else if (variableName == "Chi2Muon3Plane") {
    return particle.Track_Chi2_Muon_3Plane;
  }
  else if (variableName == "Chi2Pion3Plane") {
    return particle.Track_Chi2_Pion_3Plane;
  }
  else if (variableName == "BraggPIDKaon") {
    return particle.Track_Bragg_PID_Kaon;
  }
  else if (variableName == "MeandEdX3Plane") {
    return particle.MeandEdX_ThreePlane;
  }
  else if (variableName == "PDG") {
    return particle.TrackTruePDG;
  }
  
  
  // Add more variables as needed
  else {
    std::cerr << "Variable name '" << variableName << "' not recognized." << std::endl;
    return -1; // Return an invalid value or handle this case appropriately
  }
}


void BDTXCheckPlotList(std::string label, bool IsHistosPDG, int nbinsX, double xlow, double xhigh, std::string title, bool IsPrimaryX, std::string variableNameX, int nbinsY = 0, double ylow = 0, double yhigh = 0, bool IsPrimaryY = true, std::string variableNameY = "defaultY") {

  std::string plotdir = "BDTXPlots";

  double POT = 1.0e21; // POT to scale samples to
  BuildTunes();
  SelectionParameters P = P_FHC_K_NOBDT_TEST;
  ImportSamples(sFHCRun1BDTTest);
    
  EventAssembler E;
  SelectionManager M(P);
  M.SetPOT(POT);

  if (IsHistosPDG) {
    M.SetupHistogramsPDG(nbinsX, xlow, xhigh, title);
  } else {
    M.Setup2DHistograms(nbinsX, xlow, xhigh, nbinsY, ylow, yhigh, title);
  }
  
  /*
  SampleNames.push_back("AssocKaon"); 
  SampleTypes.push_back("AssocKaon");
  SampleFiles.push_back("/exp/uboone/data/users/taniuchi/taniuchi/pandora_alg/ana/assok_refined_KrecoAlg_parameter8_ntuple.root");
  */
  
  //SampleNames.push_back("GENIE Background"); 
  //SampleTypes.push_back("Background");
  //SampleFiles.push_back("/exp/uboone/data/users/taniuchi/ntuple_testarea/NuMI_sample0_KaonTrees_0_2894.root");
  
  TEfficiency* Eff = new TEfficiency("Eff","",2,-0.5,1.5);
  TEfficiency* Background_Acceptance = new TEfficiency("Background_Acceptance","",2,-0.5,1.5); 

  
  // Sample Loop
  for(size_t i_s=0;i_s<SampleNames.size();i_s++){
    
    E.SetFile(SampleFiles.at(i_s), "KAON");

    if(SampleTypes.at(i_s) != "EXT" && SampleTypes.at(i_s) != "Data") M.AddSample(SampleNames.at(i_s),SampleTypes.at(i_s),POT); 
    /*
    if( SampleTypes.at(i_s) == "AssocKaon") M.AddSample("AssocKaon","AssocKaon",E.GetPOT());
    else if(SampleTypes.at(i_s) == "SingleKaonSig" || SampleTypes.at(i_s) == "SingleKaonBG") M.AddSample(SampleNames.at(i_s),SampleTypes.at(i_s),E.GetPOT()/5);
    else if(SampleTypes.at(i_s) != "EXT" && SampleTypes.at(i_s) != "Data") M.AddSample(SampleNames.at(i_s),SampleTypes.at(i_s),E.GetPOT());
    else if(SampleTypes.at(i_s) == "Data") M.AddSample(SampleNames.at(i_s),SampleTypes.at(i_s),Data_POT);
    else if(SampleTypes.at(i_s) == "EXT") M.AddSample(SampleNames.at(i_s),SampleTypes.at(i_s),EXT_POT);
    */
    
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
      //if(!M.DaughterTrackLengthCut(e)) continue;
      
      if (!(e.Neutrino.size() > 0 && e.Lepton.size() > 0)) continue;
      //if (M.GetDaughterTrackParticle().Length<=0 || !M.GetPrimaryKaonTrackParticle().Length<=0) continue;

      for (const auto& pair : M.VectorPair) {

	RecoParticle PrimaryKaonTrack = pair.first;
	RecoParticle DaughterTrack = pair.second;

	int PrimaryKaonTrackPDG = PrimaryKaonTrack.TrackTruePDG;
	int DaughterTrackPDG = DaughterTrack.TrackTruePDG;

	double valueToFillX=-9;
	double valueToFillY=-9;

	if (IsPrimaryX) valueToFillX = GetVariableValue(PrimaryKaonTrack, variableNameX);
	else valueToFillX = GetVariableValue(DaughterTrack, variableNameX);

	if (!IsHistosPDG) {
	  if (IsPrimaryY) valueToFillY = GetVariableValue(PrimaryKaonTrack, variableNameY);
	  else valueToFillY = GetVariableValue(DaughterTrack, variableNameY);
	}

	if(label == "PrimaryPDGDaughterPDG"){

	  //int xbin = PDGToBin(PrimaryKaonTrackPDG) - 1;
	  //int ybin = PDGToBin(DaughterTrackPDG) - 1;
	  int xbin = PDGToBin(valueToFillX) - 1;
	  int ybin = PDGToBin(valueToFillY) - 1;
	  //h->Fill(xbin, ybin);
	  
	  // Set bin labels
	  M.Fill2DHistograms(e,xbin,ybin,PrimaryKaonTrack,DaughterTrack);

	  /*
	  h->GetXaxis()->SetBinLabel(1, "K^{+}");
	  h->GetXaxis()->SetBinLabel(2, "#mu^{+}");
	  h->GetXaxis()->SetBinLabel(3, "#pi^{+}");
	  h->GetXaxis()->SetBinLabel(4, "proton");
	  h->GetXaxis()->SetBinLabel(5, "shower");
	  h->GetXaxis()->SetBinLabel(6, "Others");
	  
	  h->GetYaxis()->SetBinLabel(1, "K^{+}");
	  h->GetYaxis()->SetBinLabel(2, "#mu^{+}");
	  h->GetYaxis()->SetBinLabel(3, "#pi^{+}");
	  h->GetYaxis()->SetBinLabel(4, "proton");
	  h->GetYaxis()->SetBinLabel(5, "shower");
	  h->GetYaxis()->SetBinLabel(6, "Others");
	  */

	  continue;
	}

	if(IsHistosPDG) M.FillHistogramsPDG(e,valueToFillX,PrimaryKaonTrack,DaughterTrack);
	else M.Fill2DHistograms(e,valueToFillX,valueToFillY,PrimaryKaonTrack,DaughterTrack);

		
	//condition for passed
	bool passed_PrimaryMeandEdX = false;
	
	if(PrimaryKaonTrack.MeandEdX_ThreePlane<15) passed_PrimaryMeandEdX = true;
	
	if(e.EventIsSignal) Eff->FillWeighted(true,e.Weight,0);
	else Background_Acceptance->FillWeighted(true,e.Weight,0);  
	if(e.EventIsSignal) Eff->FillWeighted(passed_PrimaryMeandEdX,e.Weight,1);
	else Background_Acceptance->FillWeighted(passed_PrimaryMeandEdX,e.Weight,1);
       	

      }
    }

    E.Close();
  
  }

  TH1D *h_PassedSignal = (TH1D*)Eff->GetPassedHistogram();  
  TH1D *h_TotalSignal = (TH1D*)Eff->GetTotalHistogram(); 
  TH1D *h_PassedBackground = (TH1D*)Background_Acceptance->GetPassedHistogram();
  TH1D *h_TotalBackground = (TH1D*)Background_Acceptance->GetTotalHistogram(); 
  
  for(int i_c=1;i_c<h_PassedSignal->GetNbinsX()+1;i_c++){ 
    std::cout << "Total Signal = " << h_TotalSignal->GetBinContent(i_c) << "  Signal Passed = " << h_PassedSignal->GetBinContent(i_c) << std::endl;
    std::cout << "Total Background = " << h_TotalBackground->GetBinContent(i_c) << "  Background Passed = " << h_PassedBackground->GetBinContent(i_c) << std::endl;
    std::cout << "Efficiency = " << h_PassedSignal->GetBinContent(i_c)/h_TotalSignal->GetBinContent(i_c) << ", purity: " << h_PassedSignal->GetBinContent(i_c)/(h_PassedSignal->GetBinContent(i_c)+h_PassedBackground->GetBinContent(i_c)) << std::endl;
    
  }
    
  M.PlotDir=plotdir;

  if (IsHistosPDG) M.DrawHistogramsPDG(label);
  else if (label == "PrimaryPDGDaughterPDG") {
    std::vector<std::string> binlabels = {"K^{+}", "#mu^{+}", "#pi^{+}", "proton", "shower", "Others"};
    M.Draw2DHistograms(label, 1, 1, binlabels);
  }
  else M.Draw2DHistograms(label);

  /*
  TCanvas* c1 = new TCanvas("c1", "Canvas for Drawing Histograms", 800, 600);
  c1->cd();

  h->GetXaxis()->SetLabelSize(0.04);
  h->GetYaxis()->SetLabelSize(0.04);
  h->GetXaxis()->SetLabelFont(62);
  h->GetYaxis()->SetLabelFont(62);
  h->GetXaxis()->SetTitleFont(62);
  h->GetYaxis()->SetTitleFont(62);
  h->GetXaxis()->SetTitleOffset(1.0);
  h->GetYaxis()->SetTitleOffset(1.5);
  h->GetXaxis()->SetLabelSize(0.04);
  h->GetYaxis()->SetLabelSize(0.04);

  h->Draw("COLZ");
  c1->Modified();
  c1->Update();

  c1->Print("Plots/PrimaryDaughterPDGs.pdf");
  */  
}

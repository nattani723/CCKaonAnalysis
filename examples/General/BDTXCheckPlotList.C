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

void BDTXCheckPlotList(std::string label, bool IsHistosPDG, int nbinsX, double xlow, double xhigh, std::string title, int nbinsY = 0, double ylow = 0, double yhigh = 0) {

  double POT = 1.0e21; // POT to scale samples to
  BuildTunes();
  SelectionParameters P = P_FHC_K_NOBDT_TEST;
    
  EventAssembler E;
  SelectionManager M(P);
  M.SetPOT(POT);

  if (IsHistosPDG) {
    M.SetupHistogramsPDG(nbinsX, xlow, xhigh, title);
  } else {
    M.Setup2DHistograms(nbinsX, xlow, xhigh, nbinsY, ylow, yhigh, title);
  }
  
  SampleNames.push_back("AssocKaon"); 
  SampleTypes.push_back("AssocKaon"); 
  SampleFiles.push_back("/exp/uboone/data/users/taniuchi/ntuple_testarea/assok_KaonTrees.root");
  //SampleFiles.push_back("/exp/uboone/data/users/taniuchi/test/KaonTrees.root");
  
  //SampleNames.push_back("GENIE Background"); 
  //SampleTypes.push_back("Background");
  //SampleFiles.push_back("/exp/uboone/data/users/taniuchi/ntuple_testarea/NuMI_sample0_KaonTrees_0_2894.root");
  
  TEfficiency* Eff = new TEfficiency("Eff","",2,-0.5,1.5);
  TEfficiency* Background_Acceptance = new TEfficiency("Background_Acceptance","",2,-0.5,1.5); 

  // Setup the histograms
  //M.SetupHistogramsPDG(25,0.0,50,";#Chi_{K^{+}};Events");
  M.SetupHistogramsPDG(20,-1,1,";LLRPID p/#mu;Events");
  //M.SetupHistogramsPDG(30,0.0,30,";Three Plane Mean dE/dx;Events");
  //M.Setup2DHistograms(25,0,50,15,0,30,";#Chi_{p^{+}};#Chi_{K^{+}};");
  //M.Setup2DHistograms(30,0,150,12,0,60,";#Chi_{p^{+}};#Chi_{#mu^{+}};");

  
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
      //if(!M.DaughterTrackLengthCut(e)) continue;
      
      if (!(e.Neutrino.size() > 0 && e.Lepton.size() > 0)) continue;
      //if (M.GetDaughterTrackParticle().Length<=0 || !M.GetPrimaryKaonTrackParticle().Length<=0) continue;

      for (const auto& pair : M.VectorPair) {

	RecoParticle PrimaryKaonTrack = pair.first;
	RecoParticle DaughterTrack = pair.second;

	int PrimaryKaonTrackPDG = PrimaryKaonTrack.TrackTruePDG;
	int DaughterTrackPDG = DaughterTrack.TrackTruePDG;

	//RecoParticle PrimaryKaonTrack = M.GetPrimaryKaonTrackParticle();
	//RecoParticle DaughterTrack = M.GetDaughterTrackParticle();

      //if(DaughterTrack.TrackLength<=0 || PrimaryKaonTrack.TrackLength<=0) continue;

	double PrimaryTrackLength = PrimaryKaonTrack.TrackLength;
	double PrimaryTrackLLRPID = PrimaryKaonTrack.Track_LLR_PID;
	double PrimaryTrackLLRPIDKaon = PrimaryKaonTrack.Track_LLR_PID_Kaon;
	double PrimaryTrackChi2KaonPlane2 = PrimaryKaonTrack.Track_Chi2_Kaon_Plane2;
	double PrimaryTrackChi2ProtonPlane2 = PrimaryKaonTrack.Track_Chi2_Proton_Plane2;
	double PrimaryTrackChi2MuonPlane2 = PrimaryKaonTrack.Track_Chi2_Muon_Plane2;
	double PrimaryTrackChi2PionPlane2 = PrimaryKaonTrack.Track_Chi2_Pion_Plane2;
	double PrimaryTrackChi2Kaon3Plane = PrimaryKaonTrack.Track_Chi2_Kaon_3Plane;
	double PrimaryTrackChi2Proton3Plane = PrimaryKaonTrack.Track_Chi2_Proton_3Plane;
	double PrimaryTrackChi2Pion3Plane = PrimaryKaonTrack.Track_Chi2_Pion_3Plane;
	double PrimaryTrackChi2Muon3Plane = PrimaryKaonTrack.Track_Chi2_Muon_3Plane;
	double PrimaryTrackBraggPIDKaon = PrimaryKaonTrack.Track_Bragg_PID_Kaon;
	double PrimaryMeandEdX3Plane = PrimaryKaonTrack.MeandEdX_ThreePlane;
	
	double DaughterTrackLength = DaughterTrack.TrackLength;
	double DaughterTrackLLRPID = DaughterTrack.Track_LLR_PID;
	double DaughterTrackLLRPIDKaon = DaughterTrack.Track_LLR_PID_Kaon;
	double DaughterTrackChi2KaonPlane2 = DaughterTrack.Track_Chi2_Kaon_Plane2;
	double DaughterTrackChi2ProtonPlane2 = DaughterTrack.Track_Chi2_Proton_Plane2;
	double DaughterTrackChi2PionPlane2 = DaughterTrack.Track_Chi2_Pion_Plane2;
	double DaughterTrackChi2MuonPlane2 = DaughterTrack.Track_Chi2_Muon_Plane2;
	double DaughterTrackChi2Kaon3Plane = DaughterTrack.Track_Chi2_Kaon_3Plane;
	double DaughterTrackChi2Proton3Plane = DaughterTrack.Track_Chi2_Proton_3Plane;
	double DaughterTrackChi2Pion3Plane = DaughterTrack.Track_Chi2_Pion_3Plane;
	double DaughterTrackChi2Muon3Plane = DaughterTrack.Track_Chi2_Muon_3Plane;
	double DaughterTrackBraggPIDKaon = DaughterTrack.Track_Bragg_PID_Kaon;
	double DaughterMeandEdX3Plane = DaughterTrack.MeandEdX_ThreePlane;
	
	//if(PrimaryTrackChi2KaonPlane2>0 && PrimaryTrackChi2KaonPlane2<3) std::cout << PrimaryKaonTrack.TrackTruePDG << " " << PrimaryTrackChi2KaonPlane2 << std::endl;
	//if(PrimaryKaonTrack.TrackTruePDG == 321) std::cout << PrimaryTrackChi2KaonPlane2 << std::endl;
	//M.FillHistogramsPDG(e,PrimaryMeandEdX3Plane,PrimaryKaonTrack,DaughterTrack);

	//M.FillHistogramsPDG(e,PrimaryTrackChi2KaonPlane2,PrimaryKaonTrack,DaughterTrack);
	M.FillHistogramsPDG(e,PrimaryTrackLLRPID,PrimaryKaonTrack,DaughterTrack);
	//M.Fill2DHistograms(e,PrimaryTrackChi2Proton3Plane,PrimaryTrackChi2Kaon3Plane,PrimaryKaonTrack,DaughterTrack);

	//M.Fill2DHistograms(e,PrimaryTrackChi2ProtonPlane2,PrimaryTrackChi2KaonPlane2,PrimaryKaonTrack,DaughterTrack,1);
	//M.Fill2DHistograms(e,DaughterTrackChi2ProtonPlane2,DaughterTrackChi2MuonPlane2,PrimaryKaonTrack,DaughterTrack,1);
		
	//calculation for efficiency and purity
	//bool passed=false;
	//condition for passed
	
	
	bool passed_PrimaryMeandEdX = false;
	
	if(PrimaryMeandEdX3Plane<15) passed_PrimaryMeandEdX = true;
	
	if(e.EventIsSignal) Eff->FillWeighted(true,e.Weight,0);
	else Background_Acceptance->FillWeighted(true,e.Weight,0);  
	if(e.EventIsSignal) Eff->FillWeighted(passed_PrimaryMeandEdX,e.Weight,1);
	else Background_Acceptance->FillWeighted(passed_PrimaryMeandEdX,e.Weight,1);

	/*
	int xbin = PDGToBin(PrimaryKaonTrackPDG) - 1;
	int ybin = PDGToBin(DaughterTrackPDG) - 1;
	h->Fill(xbin, ybin);

	// Set bin labels
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
    
  if (IsHistosPDG) M.DrawHistogramsPDG(label);
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

R__LOAD_LIBRARY($HYP_TOP/lib/libHyperon.so)
R__LOAD_LIBRARY($HYP_TOP/lib/libParticleDict.so)

#include "SelectionManager.h"
#include "EventAssembler.h"
#include "Cut.h"
#include "SelectionParameters.h"

#include "Parameters.h"
#include "SampleSets_Example.h"

void BDTXCheck(){
  
  std::string label = "test";//select the name?
  double POT = 1.0e21; // POT to scale samples to

  BuildTunes();
  SelectionParameters P = P_FHC_K_NOBDT_TEST;
  
  SampleNames.push_back("AssocKaon"); 
  SampleTypes.push_back("AssocKaon"); 
  SampleFiles.push_back("/exp/uboone/data/users/taniuchi/ntuple_testarea/assok_KaonTrees.root");
  
  SampleNames.push_back("GENIE Background"); 
  SampleTypes.push_back("Background");
  SampleFiles.push_back("/exp/uboone/data/users/taniuchi/ntuple_testarea/NuMI_sample0_KaonTrees_0_2894.root");
  
  EventAssembler E;
  SelectionManager M(P);
  M.SetPOT(POT);

  TEfficiency* Eff = new TEfficiency("Eff","",2,-0.5,1.5);
  TEfficiency* Background_Acceptance = new TEfficiency("Background_Acceptance","",2,-0.5,1.5); 

  
  // Setup the histograms
  M.SetupHistogramsPDG(50,0.0,100,";#Chi_{K^{+}};Events");
  //M.SetupHistogramsPDG(30,0.0,30,";Three Plane Mean dE/dx;Events");
  //M.Setup2DHistograms(50,0,50,30,0,30,";#Chi_{p^{+}};#Chi_{K^{+}};");
  
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

      RecoParticle PrimaryKaonTrack = M.GetPrimaryKaonTrackParticle();
      RecoParticle DaughterTrack = M.GetDaughterTrackParticle();

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
      double DaughterTrackChi2Kaon3Plane = DaughterTrack.Track_Chi2_Kaon_3Plane;
      double DaughterTrackChi2Proton3Plane = DaughterTrack.Track_Chi2_Proton_3Plane;
      double DaughterTrackChi2Pion3Plane = DaughterTrack.Track_Chi2_Pion_3Plane;
      double DaughterTrackChi2Muon3Plane = DaughterTrack.Track_Chi2_Muon_3Plane;
      double DaughterTrackBraggPIDKaon = DaughterTrack.Track_Bragg_PID_Kaon;
      double DaughterMeandEdX3Plane = DaughterTrack.MeandEdX_ThreePlane;


      //M.FillHistogramsPDG(e,PrimaryMeandEdX3Plane);
      M.FillHistogramsPDG(e,PrimaryTrackChi2KaonPlane2);
      //M.Fill2DHistograms(e,PrimaryTrackChi2Proton3Plane,PrimaryTrackChi2Kaon3Plane);
      //M.Fill2DHistograms(e,PrimaryTrackChi2ProtonPlane2,PrimaryTrackChi2KaonPlane2);

      //calculation for efficiency and purity
      //bool passed=false;
      //condition for passed


      bool passed_PrimaryMeandEdX = false;

      if(PrimaryMeandEdX3Plane<15) passed_PrimaryMeandEdX = true;
      
      if(e.EventIsSignal) Eff->FillWeighted(true,e.Weight,0);
      else Background_Acceptance->FillWeighted(true,e.Weight,0);  
      if(e.EventIsSignal) Eff->FillWeighted(passed_PrimaryMeandEdX,e.Weight,1);
      else Background_Acceptance->FillWeighted(passed_PrimaryMeandEdX,e.Weight,1);  
          
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
    
  M.DrawHistogramsPDG(label);

  //M.Draw2DHistograms(label);
}

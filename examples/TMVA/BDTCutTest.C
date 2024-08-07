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
  SelectionParameters P = P_FHC_RUN1_BDT_TEST;
  //ImportSamples(sFHCRun1BDTTest);
  
  SampleNames.push_back("AssocKaon"); 
  SampleTypes.push_back("AssocKaonSig");
  SampleFiles.push_back("/exp/uboone/data/users/taniuchi/taniuchi/KaonNTuple/CV/run1/prodgenie_numi_nu_overlay_fhc_run1_CV_reco2_ReRunReco_ntuple.root");
  
  EventAssembler E(false,true);
  SelectionManager M(P);
  M.SetPOT(POT);
  M.ImportBDTWeights(P.p_BDT_WeightsDir);

  // Setup the histograms
  M.SetupHistograms(100,-1,1,";BDT Score;Events");
  M.SetupHistogramsEtoP();

  // Sample Loop
  for(size_t i_s=0;i_s<SampleNames.size();i_s++){
    
    E.SetFile(SampleFiles.at(i_s), "KAON");
    
    //if( SampleTypes.at(i_s) == "AssocKaon") M.AddSample("AssocKaon","AssocKaon",POT);
    if(SampleTypes.at(i_s) == "SingleKaonSig" || SampleTypes.at(i_s) == "SingleKaonBG") M.AddSample(SampleNames.at(i_s),SampleTypes.at(i_s),E.GetPOT()/5);
    else if(SampleTypes.at(i_s) != "EXT" && SampleTypes.at(i_s) != "Data") M.AddSample(SampleNames.at(i_s),SampleTypes.at(i_s),E.GetPOT());
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

      M.FillHistogramsEtoP(e,1,e.Weight,false);
      
      if(!M.FiducialVolumeCut(e)) continue;
      if(!M.NuCCInclusiveFilter(e)) continue;
      if(!M.DaughterTrackCut(e)) continue;
      if(!M.DaughterFiducialVolumeCut(e)) continue;

      bool passed_DaughterTrackLength=false, passed_BDTCut=false;

      double max_bdt=-999;

      for (const auto& pair : M.VectorPair) {

	RecoParticle PrimaryKaonTrackParticle = pair.first;
	RecoParticle DaughterTrackParticle = pair.second;

	double bdt = M.BDTScore(e,PrimaryKaonTrackParticle,DaughterTrackParticle);
	if(bdt>max_bdt) max_bdt = bdt;
	/*
	bool passed_BDTCut_pair = false;
	bool passed_DaughterTrackLength_pair = false;

	if(bdt >= cut_BDTscore) passed_BDTCut_pair = true;
	if(DaughterTrackParticle.TrackLength <= cut_TrackLength) passed_DaughterTrackLength_pair = true;

	if(passed_BDTCut==false && passed_BDTCut_pair==true) passed_BDTCut = true;
	if(passed_DaughterTrackLength==false && passed_DaughterTrackLength_pair==true) passed_DaughterTrackLength = true;
	*/
      }

      M.FillHistograms(e,max_bdt);//add weight
      M.FillHistogramsEtoP(e,max_bdt,e.Weight,true);

      /*
      if(e.EventIsSignal){	
      }
      else{
      }
      */

    }

    E.Close();
  }

  M.FillEtoPCurve();
  M.PlotEtoPCurve();

  M.DrawHistograms(label);

}

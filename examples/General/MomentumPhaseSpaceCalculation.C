R__LOAD_LIBRARY($HYP_TOP/lib/libHyperon.so)
R__LOAD_LIBRARY($HYP_TOP/lib/libParticleDict.so)

#include "SelectionManager.h"
#include "EventAssembler.h"
#include "Cut.h"
#include "SelectionParameters.h"

#include "Parameters.h"
#include "SampleSets_Example.h"
#include "DrawEfficiencyPlot.h"

   void MomentumPhaseSpaceCalculation(){

  std::string label = "KaonMomentum";//select the name?
      double POT = 1.0e21; // POT to scale samples to

      BuildTunes();
      SelectionParameters P = P_FHC_K_NOBDT_TEST;

      SampleNames.push_back("AssocKaon"); 
      SampleTypes.push_back("AssocKaon"); 
      SampleFiles.push_back("/exp/uboone/data/users/taniuchi/ntuple_testarea/assok_KaonTrees.root");

      EventAssembler E;
      SelectionManager M(P);
      M.SetPOT(POT);

      // Setup the histograms
      TH1D *h_KaonEndMom = new TH1D("h_KaonEndMom",";K^{+} End Momentum (GeV/c^2);Events",25,0.0,2.5);
      TH1D *h_Probability = new TH1D("h_Probability", "", 100,0.0,2.5);

      // Sample Loop
      for(size_t i_s=0;i_s<SampleNames.size();i_s++){

	E.SetFile(SampleFiles.at(i_s), "KAON");//2nd parameter is dummy

	if( SampleTypes.at(i_s) == "AssocKaon") M.AddSample("AssocKaon","AssocKaon",POT);
	if(SampleTypes.at(i_s) != "EXT" && SampleTypes.at(i_s) != "Data") M.AddSample(SampleNames.at(i_s),SampleTypes.at(i_s),E.GetPOT());
         else if(SampleTypes.at(i_s) == "Data") M.AddSample(SampleNames.at(i_s),SampleTypes.at(i_s),Data_POT);
         else if(SampleTypes.at(i_s) == "EXT") M.AddSample(SampleNames.at(i_s),SampleTypes.at(i_s),EXT_POT);
	
	M.UseFluxWeight(false);
	M.UseGenWeight(false);

         // Event Loop
         for(int i=0;i<E.GetNEvents();i++){

            if(i % 10000 == 0) std::cout << i << "/" << E.GetNEvents() << std::endl;

            Event e = E.GetEvent(i);
	    //std::cout << e.PrimaryKaonP.at(0).E << endl;

            M.SetSignal(e);
            M.AddEvent(e);

	    if(!e.EventIsSignal) continue;

	    if (!(e.Neutrino.size() > 0 && e.Lepton.size() > 0)){
	      continue;
	      std::cout << "THIS EVENT DOES NOT HAVE NEUTRINO NOR LEPTON" << std::endl;
	    }


	    //if(!M.FiducialVolumeCut(e)) continue;
	    //if(!M.NuCCInclusiveFilter(e)) continue;
	    //if(!M.DaughterTrackCut(e)) continue;
	    //if(!M.DaughterFiducialVolumeCut(e)) continue;
	    //if(!M.DaughterTrackLengthCut(e)) continue;
	    
	    //double NuE = e.Neutrino.at(0).E;

	    if(e.PrimaryKaonP.size()<=0) continue;
 	    double KaonMomentum = e.PrimaryKaonP.at(0).EndModMomentum;
	    h_KaonEndMom->Fill(KaonMomentum,e.Weight);

         }
         E.Close();

	    double x = 0;
	    double MK = 0.4937;
	    double MPi = 0.1396;
	    double PPi_thresh = 0.100;
	    double pCMS = 0.2051;
	    double E = sqrt(MPi*MPi + pCMS*pCMS);
	    //double ratio = x/MK;
	    double A,F;

	 for (int i = 1; i <= h_Probability->GetNbinsX(); i++) {
	   double x_centre = h_Probability->GetXaxis()->GetBinCenter(i);
	   double ratio = x_centre/MK;

	   A = (sqrt( MPi*MPi + PPi_thresh*PPi_thresh) - sqrt(1+ratio*ratio) * E)/( sqrt(1+ratio*ratio) * sqrt( 1 - 1/(1+ratio*ratio))*pCMS );	    
	   if(A<-1) F = 1;
	   else F = (1-A)/2;
	   h_Probability->SetBinContent(i,F);
	 }

      }
      DrawPhaseSpacePlot(h_KaonEndMom, h_Probability);
   }

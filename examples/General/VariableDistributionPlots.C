R__LOAD_LIBRARY($HYP_TOP/lib/libHyperon.so)
R__LOAD_LIBRARY($HYP_TOP/lib/libParticleDict.so)

#include "SelectionManager.h"
#include "EventAssembler.h"
#include "Cut.h"
#include "SelectionParameters.h"

#include "Parameters.h"
#include "SampleSets_Example.h"

   void VariableDistributionPlots(){

  std::string label = "KaonMomentum";//select the name?
      double POT = 1.0e21; // POT to scale samples to

      BuildTunes();
      SelectionParameters P = P_FHC_K_NOBDT_TEST;

      SampleNames.push_back("AssocKaon"); 
      SampleTypes.push_back("AssocKaon"); 
      SampleFiles.push_back("/exp/uboone/data/users/taniuchi/ntuple_testarea/assok_KaonTrees.root");

      SampleNames.push_back("GENIE Background"); 
      SampleTypes.push_back("Background");
      SampleFiles.push_back("/exp/uboone/data/users/taniuchi/ntuple_testarea/NuMI_sample0_KaonTrees_0_2894.root");

      /*
      SampleNames.push_back("GENIE Background");
      SampleTypes.push_back("Background");
      SampleFiles.push_back("run1_FHC/analysisOutputFHC_Overlay_GENIE_Background_All.root");

      SampleNames.push_back("GENIE Hyperon");
      SampleTypes.push_back("Hyperon");
      SampleFiles.push_back("run1_FHC/analysisOutputFHC_Overlay_GENIE_Hyperon_All.root");
      */

      EventAssembler E;
      SelectionManager M(P);
      M.ImportBDTWeights(P.p_BDT_WeightsDir);
      M.SetPOT(POT);

      // Setup the histograms
      //M.SetupHistograms(100,0.0,5.0,";Neutrino Energy (GeV);Events");
      //M.SetupHistograms(30,0.0,3.0,";K^{+} Energy (GeV);Events");
      M.SetupHistograms(25,0.0,2.5,";K^{+} Momentum (GeV/c^2);Events");
      //M.SetupHistograms(8,0.0,8.0,";Number of Tracks;Events");

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

	    //if(!M.FiducialVolumeCut(e)) continue;
	    //if(!M.NuCCInclusiveFilter(e)) continue;
	    //if(!M.DaughterTrackCut(e)) continue;
	    //if(!M.DaughterFiducialVolumeCut(e)) continue;
	    //if(!M.DaughterTrackLengthCut(e)) continue;
	    
	    //double NuE = e.Neutrino.at(0).E;

	    if(e.PrimaryKaonP.size()<=0) continue;
 	    double KaonMomentum = e.PrimaryKaonP.at(0).ModMomentum;
	    //double KaonE = e.PrimaryKaonP.at(0).E;
	    //double ntrk = e.NPrimaryTrackDaughters;
	    //double nottrk = e.NOtherTracks;

            //M.FillHistograms(e,E);
            //M.FillHistograms(e,ntrk);
            //M.FillHistograms(e,KaonE);
            M.FillHistograms(e,KaonMomentum);

         }
         E.Close();
      }
      M.DrawHistograms(label);
   }

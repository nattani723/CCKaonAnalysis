R__LOAD_LIBRARY($HYP_TOP/lib/libHyperon.so)
R__LOAD_LIBRARY($HYP_TOP/lib/libParticleDict.so)

#include "SelectionManager.h"
#include "EventAssembler.h"
#include "BDTManager.h"
#include "Cut.h"
#include "SelectionParameters.h"

#include "Parameters.h"
#include "SampleSets.h"

   // Fills the trees for the MVA training

   void FillTree(std::string Mode){

      BuildTunes();
      ImportSamples(sNuWroNoCosmic); //change

      // POT to scale samples to
      double POT = 1.0e21;

      // Set the parameters you want to use
      SelectionParameters P = P_FHC_K_NOBDT_TEST;

      SelectionManager M(P);
      M.SetPOT(POT);
      EventAssembler E;

      // Setup BDT Manager Object
      BDTManager BDTManager("Train");


      // Sample Loop
      for(size_t i_s=0;i_s<SampleNames.size();i_s++){
        
	E.SetFile(SampleFiles.at(i_s),"KAON");

	if( SampleTypes.at(i_s) == "AssocKaon") M.AddSample("AssocKaon","AssocKaon",POT);
         //if(SampleTypes.at(i_s) != "EXT" && SampleTypes.at(i_s) != "Data") M.AddSample(SampleNames.at(i_s),SampleTypes.at(i_s),E.GetPOT());
         else if(SampleTypes.at(i_s) == "Data") M.AddSample(SampleNames.at(i_s),SampleTypes.at(i_s),Data_POT);
         else if(SampleTypes.at(i_s) == "EXT") M.AddSample(SampleNames.at(i_s),SampleTypes.at(i_s),EXT_POT);

         // Event Loop
         for(int i=0;i<E.GetNEvents();i++){

            Event e = E.GetEvent(i);

            M.SetSignal(e);                
            M.AddEvent(e);

	    if(!M.FiducialVolumeCut(e)) continue;
	    if(!M.NuCCInclusiveFilter(e)) continue;
	    //if(!M.DaughterTrackCut(e)) continue;
	    //if(!M.DaughterFiducialVolumeCut(e)) continue;
	    //if(!M.DaughterTrackLengthCut(e)) continue;

	    RecoParticle DaughterTrackParticle = M.GetDaughterTrackParticle();
	    RecoParticle PrimaryKaonTrackParticle = M.GetPrimaryKaonTrackParticle();

            BDTManager.FillTree(e, PrimaryKaonTrackParticle, DaughterTrackParticle);

         }

         E.Close();

      }

      BDTManager.WriteTrainingTrees();

   }


// Put pre-defined sample sets in here.

enum settings { sNuWroFullFHCvsData , sNuWroFullFHC , sBDTTest};

std::vector<std::string> SampleNames,SampleTypes,SampleFiles,EventLists;

double EXT_POT=0.0;
double Data_POT=0.0;

int fhc_run_range[2];
int rhc_run_range[2];

std::string GoodRunList="";
std::vector<int> GoodRuns;

// Detector systematics
std::vector<std::string> Detvar_Names;
std::vector<std::vector<std::string>> SampleNames_Detvar,SampleTypes_Detvar,SampleFiles_Detvar,EventLists_Detvar;
std::vector<std::string> CommonRSLists_Detvar;
std::vector<std::vector<std::pair<int,int>>> CommonRSLists;

void ImportSamples(int Setting){

  if(Setting == sBDTTest){
    
    SampleNames = { "Associated K Overlay" };
    SampleTypes = { "AssocKaon" };
    SampleFiles = { "/exp/uboone/data/users/taniuchi/taniuchi/pandora_alg/ana/assok_refined_KrecoAlg_parameter10_ntuple.root" };

  }

   if(Setting == sNuWroFullFHCvsData){

      SampleNames = { "NuWro Overlay Backgroud" , "NuWro Overlay Hyperon" , "GENIE Dirt" , "EXT" , "Data" };
      SampleTypes = { "Background" , "Hyperon" , "Dirt" , "EXT" , "Data" };
      SampleFiles = { "analysisOutputFHC_Overlay_NuWro_Background_kmistry_numi_run1_fhc_nuwro.root" , "analysisOutputFHC_Overlay_NuWro_Hyperon_prod_numi_uboone_overlay_fhc_mcc9_run1_v51_nuwro_hyperon_nuwro_reco2_reco2.root" , "analysisOutputFHC_Overlay_GENIE_Dirt_prodgenie_numi_uboone_overlay_dirt_fhc_mcc9_run1_v28_sample0.root" , "analysisOutput_EXT_cthorpe_numi_uboone_run1_beamoff_offset1_mcc9_reco2_v08_00_00_28_sample0_sample1_all.root" , "analysisOutputFHC_Data_cthorpe_numi_uboone_run1_beamon_offset1_mcc9_reco2_v08_00_00_28_sample0_beam_good_may_2021.root" };

      EXT_POT = 1.0421e20; 
      Data_POT = 1.385e19;
   }


   if(Setting == sNuWroFullFHC){

      SampleNames = { "NuWro Overlay Backgroud" , "NuWro Overlay Hyperon" , "GENIE Dirt" , "EXT" };
      SampleTypes = { "Background" , "Hyperon" , "Dirt" , "EXT" };
      SampleFiles = { "analysisOutputFHC_Overlay_NuWro_Background_kmistry_numi_run1_fhc_nuwro.root" , "analysisOutputFHC_Overlay_NuWro_Hyperon_prod_numi_uboone_overlay_fhc_mcc9_run1_v51_nuwro_hyperon_nuwro_reco2_reco2.root" , "analysisOutputFHC_Overlay_GENIE_Dirt_prodgenie_numi_uboone_overlay_dirt_fhc_mcc9_run1_v28_sample0.root" , "analysisOutput_EXT_cthorpe_numi_uboone_run1_beamoff_offset1_mcc9_reco2_v08_00_00_28_sample0_sample1_all.root" };

      EXT_POT = 1.0421e20; 

      EventLists = { "FHC_Tune_325/analysisOutputFHC_Overlay_NuWro_Background_kmistry_numi_run1_fhc_nuwro.root_Selected.txt" , "FHC_Tune_325/analysisOutputFHC_Overlay_NuWro_Hyperon_prod_numi_uboone_overlay_fhc_mcc9_run1_v51_nuwro_hyperon_nuwro_reco2_reco2.root_Selected.txt" ,  "FHC_Tune_325/analysisOutputFHC_GENIE_Overlay_Dirt_prodgenie_numi_uboone_overlay_dirt_fhc_mcc9_run1_v28_sample1.root_Selected.txt" , "FHC_Tune_325/analysisOutput_EXT_cthorpe_numi_uboone_run1_beamoff_offset1_mcc9_reco2_v08_00_00_28_sample2_sample3_all.root_Selected.txt" };
   }

/*

  // To add a new sample set, use the following template:

  SampleNames = { "Your Sample Name 1" , "Your Sample Name 2" , ... }; // To track which is which.
  SampleTypes = { "Background" , "Hyperon" , ... }; // Use either Background, Hyperon, Dirt, EXT, Data.
  SampleFiles = { "Sample 1 Tree File" , "Sample 2 Tree File" , ... } // Location of corresponding ntuples in data/ dir. 

  // Whatever the POTs of your data and EXT are if used.
  EXT_POT = 1.000e20;
  Data_POT = 1.000e20;

  // The EventConnectedness repo contains the code that performs the connectedness test. This outputs
  // a list of events that passed for the samples you give it. Add those lists here to use that in the selection
  EventLists = { "Sample 1 Selected Events.txt" ,  "Sample 2 Selected Events.txt" , ...  };

*/

   if(GoodRunList != ""){
      std::ifstream input_GoodRunList(GoodRunList);
      while(!input_GoodRunList.eof()){
         int run;
         input_GoodRunList >> run;
          //std::cout << run << std::endl;
         GoodRuns.push_back(run);
      }
   }
}



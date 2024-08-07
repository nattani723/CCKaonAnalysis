#ifndef _Parameters_h_
#define _Parameters_h_

#include "SelectionParameters.h"

// Pre-defined settings for the selection
// To use - include this header and add:
// BuildTunes(); at the start of your code
// Then SelectionManager(P_FHC_325) etc. 

SelectionParameters P_FHC_K_NOBDT_TEST;
SelectionParameters P_FHC_RUN1_BDT_TEST;

void BuildTunes(){

/////////////////////
// FROZEN FHC TUNE //
/////////////////////

//test for runnning selection on my K

 P_FHC_K_NOBDT_TEST.Name = "FHC Kaon No BDT";
 P_FHC_K_NOBDT_TEST.p_RunPeriod = 1;
 /*
 P_FHC_K_NOBDT_TEST.p_FV = ;
 P_FHC_K_NOBDT_TEST.p_Padding = ;
 P_FHC_K_NOBDT_TEST.p_Minimum_MIP_Length = ;
 P_FHC_K_NOBDT_TEST.p_SecondaryTrackLengthCut = ;
 P_FHC_K_NOBDT_TEST.p_TertiaryTrackLengthCut = ;
 P_FHC_K_NOBDT_TEST.p_Max_Displacement = ;
 P_FHC_K_NOBDT_TEST.p_PID_Cut = ;
 P_FHC_K_NOBDT_TEST.p_Proton_PID_Cut = ;
 P_FHC_K_NOBDT_TEST.p_Pion_PID_Cut = ;
 P_FHC_K_NOBDT_TEST.p_Separation_Cut = ;
 P_FHC_K_NOBDT_TEST.p_SelectorBDT_WeightsDir = ;
 P_FHC_K_NOBDT_TEST.p_AnalysisBDT_WeightsDir = ;
 P_FHC_K_NOBDT_TEST.p_BDT_Cut = ;
 */
 P_FHC_K_NOBDT_TEST.p_BeamMode = kFHC;
 P_FHC_K_NOBDT_TEST.HasBeenSetup = true;


//test for runnning selection on my K

 P_FHC_RUN1_BDT_TEST.Name = "FHC Run1 BDT Test";
 P_FHC_RUN1_BDT_TEST.p_RunPeriod = 1;
 P_FHC_RUN1_BDT_TEST.p_BDT_WeightsDir = "/exp/uboone/app/users/taniuchi/51_pandora/CCKaonAnalysis/examples/TMVA/dataset_par7_notrkln_input/weights";
 P_FHC_RUN1_BDT_TEST.p_BDT_Cut = 0.3;
 P_FHC_RUN1_BDT_TEST.p_BeamMode = kFHC;
 P_FHC_RUN1_BDT_TEST.HasBeenSetup = true;

}

#endif

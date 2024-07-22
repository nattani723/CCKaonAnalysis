#ifndef _Parameters_h_
#define _Parameters_h_

#include "SelectionParameters.h"

// Pre-defined settings for the selection
// To use - include this header and add:
// BuildTunes(); at the start of your code
// Then SelectionManager(P_FHC_325) etc. 

SelectionParameters P_FHC_K_NOBDT_TEST;

void BuildTunes(){

/////////////////////
// FROZEN FHC TUNE //
/////////////////////

//FHC Tune 325
P_FHC_Tune_325.Name = "FHC Tune 325";
P_FHC_Tune_325.p_RunPeriod=1;
P_FHC_Tune_325.p_FV=FV::kWirecellPadded;
P_FHC_Tune_325.p_Padding=10;
P_FHC_Tune_325.p_Minimum_MIP_Length=10;
P_FHC_Tune_325.p_SecondaryTrackLengthCut=1000;
P_FHC_Tune_325.p_TertiaryTrackLengthCut=1000;
P_FHC_Tune_325.p_Max_Displacement=1;
P_FHC_Tune_325.p_PID_Cut=0.6;
P_FHC_Tune_325.p_Proton_PID_Cut = 0.1;
P_FHC_Tune_325.p_Pion_PID_Cut = -0.1;
P_FHC_Tune_325.p_Separation_Cut=3;
P_FHC_Tune_325.p_VertexPull=5;
P_FHC_Tune_325.p_SelectorBDT_WeightsDir="/home/lar/cthorpe/uboone/HyperonSelection/TMVA/SelectorMVA/Tunes/FHC_Tune_325/dataset/weights";
P_FHC_Tune_325.p_AnalysisBDT_WeightsDir="/home/lar/cthorpe/uboone/HyperonSelection/TMVA/AnalysisMVA/Tunes/FHC_Tune_325/dataset/weights";
P_FHC_Tune_325.p_BDT_Cut=0.15;
P_FHC_Tune_325.p_BeamMode = kFHC;
P_FHC_Tune_325.HasBeenSetup = true;

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
 //P_FHC_RUN1_BDT_TEST.p_BDT_WeightsDir = ;
 //P_FHC_RUN1_BDT_TEST.p_BDT_Cut = ;
 P_FHC_RUN1_BDT_TEST.p_BeamMode = kFHC;
 P_FHC_RUN1_BDT_TEST.HasBeenSetup = true;

}

#endif

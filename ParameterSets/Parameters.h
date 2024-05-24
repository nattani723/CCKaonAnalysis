#ifndef _Parameters_h_
#define _Parameters_h_

#include "SelectionParameters.h"

// Pre-defined settings for the selection
// To use - include this header and add:
// BuildTunes(); at the start of your code
// Then SelectionManager(P_FHC_325) etc. 

SelectionParameters P_FHC_Tune_325;
SelectionParameters P_RHC_Tune_397;
SelectionParameters P_FHC_Tune_test;
SelectionParameters P_FHC_Tune_test2;
SelectionParameters P_FHC_Tune_1000;

SelectionParameters P_FHC_Tune_325_Alt;
SelectionParameters P_FHC_Tune_326;

SelectionParameters P_FHC_Tune_325_NoBDT;
SelectionParameters P_RHC_Tune_397_NoBDT;

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

/////////////////////
// FROZEN RHC TUNE //
/////////////////////

// RHC Tune 397
P_RHC_Tune_397.Name = "RHC Tune 397";
P_RHC_Tune_397.p_RunPeriod=3;
P_RHC_Tune_397.p_FV=FV::kWirecellPadded;
P_RHC_Tune_397.p_Padding=10;
P_RHC_Tune_397.p_Minimum_MIP_Length=10;
P_RHC_Tune_397.p_SecondaryTrackLengthCut=1000;
P_RHC_Tune_397.p_TertiaryTrackLengthCut=1000;
P_RHC_Tune_397.p_Max_Displacement=1;
P_RHC_Tune_397.p_PID_Cut=0.6;
P_RHC_Tune_397.p_Proton_PID_Cut = 0.0;
P_RHC_Tune_397.p_Pion_PID_Cut = -0.1;
P_RHC_Tune_397.p_Separation_Cut=3;
P_RHC_Tune_397.p_VertexPull=5;
P_RHC_Tune_397.p_SelectorBDT_WeightsDir="/home/lar/cthorpe/uboone/HyperonSelection/TMVA/SelectorMVA/Tunes/RHC_Tune_397/dataset/weights";
P_RHC_Tune_397.p_AnalysisBDT_WeightsDir="/home/lar/cthorpe/uboone/HyperonSelection/TMVA/AnalysisMVA/Tunes/RHC_Tune_397/dataset/weights";
P_RHC_Tune_397.p_BDT_Cut=0.2;
P_RHC_Tune_397.p_BeamMode = kRHC;
P_RHC_Tune_397.HasBeenSetup = true;

/////////////////////

//FHC test tune
P_FHC_Tune_test.Name = "FHC Tune test";
P_FHC_Tune_test.p_RunPeriod=1;
P_FHC_Tune_test.p_FV=FV::kWirecellPadded;
P_FHC_Tune_test.p_Padding=0;
P_FHC_Tune_test.p_Minimum_MIP_Length=0;
P_FHC_Tune_test.p_SecondaryTrackLengthCut=1000;
P_FHC_Tune_test.p_TertiaryTrackLengthCut=1000;
P_FHC_Tune_test.p_Max_Displacement=1;
P_FHC_Tune_test.p_PID_Cut=0.3;
P_FHC_Tune_test.p_Proton_PID_Cut = 1.0;
P_FHC_Tune_test.p_Pion_PID_Cut = -1.0;
P_FHC_Tune_test.p_Separation_Cut=100;
P_FHC_Tune_test.p_VertexPull=5;
P_FHC_Tune_test.p_SelectorBDT_WeightsDir="/home/lar/cthorpe/uboone/HyperonSelection/TMVA/SelectorMVA/Tunes/FHC_Tune_test/dataset/weights";
P_FHC_Tune_test.p_AnalysisBDT_WeightsDir="/home/lar/cthorpe/uboone/HyperonSelection/TMVA/AnalysisMVA/Tunes/FHC_Tune_test/dataset/weights";
P_FHC_Tune_test.p_BDT_Cut=0.15;
P_FHC_Tune_test.p_BeamMode = kFHC;
P_FHC_Tune_test.HasBeenSetup = true;

//FHC test2 tune2
P_FHC_Tune_test2.Name = "FHC Tune test 2";
P_FHC_Tune_test2.p_RunPeriod=1;
P_FHC_Tune_test2.p_FV=FV::kWirecellPadded;
P_FHC_Tune_test2.p_Padding=10;
P_FHC_Tune_test2.p_Minimum_MIP_Length=10;
P_FHC_Tune_test2.p_SecondaryTrackLengthCut=1000;
P_FHC_Tune_test2.p_TertiaryTrackLengthCut=1000;
P_FHC_Tune_test2.p_Max_Displacement=1;
P_FHC_Tune_test2.p_PID_Cut=0.6;
P_FHC_Tune_test2.p_Proton_PID_Cut = 1.0;
P_FHC_Tune_test2.p_Pion_PID_Cut = -1.0;
P_FHC_Tune_test2.p_Separation_Cut=100;
P_FHC_Tune_test2.p_VertexPull=5;
P_FHC_Tune_test2.p_SelectorBDT_WeightsDir="/home/lar/cthorpe/uboone/HyperonSelection/TMVA/SelectorMVA/Tunes/FHC_Tune_test2/dataset/weights";
P_FHC_Tune_test2.p_AnalysisBDT_WeightsDir="/home/lar/cthorpe/uboone/HyperonSelection/TMVA/AnalysisMVA/Tunes/FHC_Tune_test2/dataset/weights";
P_FHC_Tune_test2.p_BDT_Cut=0.15;
P_FHC_Tune_test2.p_BeamMode = kFHC;
P_FHC_Tune_test2.HasBeenSetup = true;

//FHC Tune 1000
P_FHC_Tune_1000.Name = "FHC Tune 1000";
P_FHC_Tune_1000.p_RunPeriod=1;
P_FHC_Tune_1000.p_FV=FV::kWirecellPadded;
P_FHC_Tune_1000.p_Padding=5;
P_FHC_Tune_1000.p_Minimum_MIP_Length=5;
P_FHC_Tune_1000.p_SecondaryTrackLengthCut=1000;
P_FHC_Tune_1000.p_TertiaryTrackLengthCut=1000;
P_FHC_Tune_1000.p_Max_Displacement=1;
P_FHC_Tune_1000.p_PID_Cut=0.6;
P_FHC_Tune_1000.p_Proton_PID_Cut = 0.1;
P_FHC_Tune_1000.p_Pion_PID_Cut = 0.0;
P_FHC_Tune_1000.p_Separation_Cut=10;
P_FHC_Tune_1000.p_VertexPull=5;
P_FHC_Tune_1000.p_SelectorBDT_WeightsDir="/home/lar/cthorpe/uboone/HyperonSelection/TMVA/SelectorMVA/Tunes/FHC_Tune_1000/dataset/weights";
P_FHC_Tune_1000.p_AnalysisBDT_WeightsDir="/home/lar/cthorpe/uboone/HyperonSelection/TMVA/AnalysisMVA/Tunes/FHC_Tune_1000/dataset/weights";
P_FHC_Tune_1000.p_BDT_Cut=0.15;
P_FHC_Tune_1000.p_BeamMode = kFHC;
P_FHC_Tune_1000.HasBeenSetup = true;

//FHC Tune 325 without using selector BDT score in analysis BDT
P_FHC_Tune_325_Alt.Name = "FHC Tune 325 Alt";
P_FHC_Tune_325_Alt.p_RunPeriod=1;
P_FHC_Tune_325_Alt.p_FV=FV::kWirecellPadded;
P_FHC_Tune_325_Alt.p_Padding=10;
P_FHC_Tune_325_Alt.p_Minimum_MIP_Length=10;
P_FHC_Tune_325_Alt.p_SecondaryTrackLengthCut=1000;
P_FHC_Tune_325_Alt.p_TertiaryTrackLengthCut=1000;
P_FHC_Tune_325_Alt.p_Max_Displacement=1;
P_FHC_Tune_325_Alt.p_PID_Cut=0.6;
P_FHC_Tune_325_Alt.p_Proton_PID_Cut = 0.1;
P_FHC_Tune_325_Alt.p_Pion_PID_Cut = -0.1;
P_FHC_Tune_325_Alt.p_Separation_Cut=3;
P_FHC_Tune_325_Alt.p_VertexPull=5;
P_FHC_Tune_325_Alt.p_SelectorBDT_WeightsDir="/home/lar/cthorpe/uboone/HyperonSelection/TMVA/SelectorMVA/Tunes/FHC_Tune_325/dataset/weights";
P_FHC_Tune_325_Alt.p_AnalysisBDT_WeightsDir="/home/lar/cthorpe/uboone/HyperonSelection/TMVA/AnalysisMVA/Tunes/FHC_Tune_325_Alt/dataset/weights";
P_FHC_Tune_325_Alt.p_BDT_Cut=0.2;
P_FHC_Tune_325_Alt.p_BeamMode = kFHC;
P_FHC_Tune_325_Alt.HasBeenSetup = true;

//FHC Tune 326
P_FHC_Tune_326.Name = "FHC Tune 326";
P_FHC_Tune_326.p_RunPeriod=1;
P_FHC_Tune_326.p_FV=FV::kWirecellPadded;
P_FHC_Tune_326.p_Padding=10;
P_FHC_Tune_326.p_Minimum_MIP_Length=10;
P_FHC_Tune_326.p_SecondaryTrackLengthCut=1000;
P_FHC_Tune_326.p_TertiaryTrackLengthCut=1000;
P_FHC_Tune_326.p_Max_Displacement=1;
P_FHC_Tune_326.p_PID_Cut=0.6;
P_FHC_Tune_326.p_Proton_PID_Cut = 0.1;
P_FHC_Tune_326.p_Pion_PID_Cut = -0.1;
P_FHC_Tune_326.p_Separation_Cut=3;
P_FHC_Tune_326.p_VertexPull=5;
P_FHC_Tune_326.p_SelectorBDT_WeightsDir="/home/lar/cthorpe/uboone/HyperonSelection/TMVA/SelectorMVA/Tunes/FHC_Tune_326/dataset/weights";
P_FHC_Tune_326.p_AnalysisBDT_WeightsDir="/home/lar/cthorpe/uboone/HyperonSelection/TMVA/AnalysisMVA/Tunes/FHC_Tune_326/dataset/weights";
P_FHC_Tune_326.p_BDT_Cut=0.1;
P_FHC_Tune_326.p_BeamMode = kFHC;
P_FHC_Tune_326.HasBeenSetup = true;

//FHC Tune 325 No BDT
P_FHC_Tune_325_NoBDT.Name = "FHC Tune 325 NoBDT";
P_FHC_Tune_325_NoBDT.p_RunPeriod=1;
P_FHC_Tune_325_NoBDT.p_FV=FV::kWirecellPadded;
P_FHC_Tune_325_NoBDT.p_Padding=10;
P_FHC_Tune_325_NoBDT.p_Minimum_MIP_Length=10;
P_FHC_Tune_325_NoBDT.p_SecondaryTrackLengthCut=1000;
P_FHC_Tune_325_NoBDT.p_TertiaryTrackLengthCut=1000;
P_FHC_Tune_325_NoBDT.p_Max_Displacement=1;
P_FHC_Tune_325_NoBDT.p_PID_Cut=0.6;
P_FHC_Tune_325_NoBDT.p_Proton_PID_Cut = 0.1;
P_FHC_Tune_325_NoBDT.p_Pion_PID_Cut = -0.1;
P_FHC_Tune_325_NoBDT.p_Separation_Cut=3;
P_FHC_Tune_325_NoBDT.p_VertexPull=5;
P_FHC_Tune_325_NoBDT.p_SelectorBDT_WeightsDir="/home/lar/cthorpe/uboone/HyperonSelection/TMVA/SelectorMVA/Tunes/FHC_Tune_325/dataset/weights";
P_FHC_Tune_325_NoBDT.p_AnalysisBDT_WeightsDir="/home/lar/cthorpe/uboone/HyperonSelection/TMVA/AnalysisMVA/Tunes/FHC_Tune_325/dataset/weights";
P_FHC_Tune_325_NoBDT.p_BDT_Cut=0.15;
P_FHC_Tune_325_NoBDT.p_BeamMode = kFHC;
P_FHC_Tune_325_NoBDT.p_W_Min = 1.09;
P_FHC_Tune_325_NoBDT.p_W_Max = 1.14;
P_FHC_Tune_325_NoBDT.p_Alpha_Cut = 14;
P_FHC_Tune_325_NoBDT.HasBeenSetup = true;

// RHC Tune 397 No BDT
P_RHC_Tune_397_NoBDT.Name = "RHC Tune 397 NoBDT";
P_RHC_Tune_397_NoBDT.p_RunPeriod=3;
P_RHC_Tune_397_NoBDT.p_FV=FV::kWirecellPadded;
P_RHC_Tune_397_NoBDT.p_Padding=10;
P_RHC_Tune_397_NoBDT.p_Minimum_MIP_Length=10;
P_RHC_Tune_397_NoBDT.p_SecondaryTrackLengthCut=1000;
P_RHC_Tune_397_NoBDT.p_TertiaryTrackLengthCut=1000;
P_RHC_Tune_397_NoBDT.p_Max_Displacement=1;
P_RHC_Tune_397_NoBDT.p_PID_Cut=0.6;
P_RHC_Tune_397_NoBDT.p_Proton_PID_Cut = 0.0;
P_RHC_Tune_397_NoBDT.p_Pion_PID_Cut = -0.1;
P_RHC_Tune_397_NoBDT.p_Separation_Cut=3;
P_RHC_Tune_397_NoBDT.p_VertexPull=5;
P_RHC_Tune_397_NoBDT.p_SelectorBDT_WeightsDir="/home/lar/cthorpe/uboone/HyperonSelection/TMVA/SelectorMVA/Tunes/RHC_Tune_397/dataset/weights";
P_RHC_Tune_397_NoBDT.p_AnalysisBDT_WeightsDir="/home/lar/cthorpe/uboone/HyperonSelection/TMVA/AnalysisMVA/Tunes/RHC_Tune_397/dataset/weights";
P_RHC_Tune_397_NoBDT.p_BDT_Cut=0.2;
P_RHC_Tune_397_NoBDT.p_BeamMode = kRHC;
P_RHC_Tune_397_NoBDT.p_W_Min = 1.09;
P_RHC_Tune_397_NoBDT.p_W_Max = 1.14;
P_RHC_Tune_397_NoBDT.p_Alpha_Cut = 14;
P_RHC_Tune_397_NoBDT.HasBeenSetup = true;


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

}

#endif

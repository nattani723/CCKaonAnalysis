#ifndef _SelectionParameters_h_
#define _SelectionParameters_h_

struct SelectionParameters {

std::string Name;
bool HasBeenSetup = false;

// Preselection Parameters
int p_FV;
double p_Padding;

// Muon ID Parameters
double p_Minimum_MIP_Length;
double p_Max_Displacement;
double p_PID_Cut;

// Subleading Track Length Cut Parameters
double p_SecondaryTrackLengthCut;
double p_TertiaryTrackLengthCut;

// Selector BDT Input Parameters
double p_Proton_PID_Cut;
double p_Pion_PID_Cut;
double p_Separation_Cut;

// Vertex Fitter Parameters
double p_VertexPull=5.0;

double p_BDT_Cut;

double p_W_Max;
double p_W_Min;
double p_Alpha_Cut;

// Selector BDT Weights file
std::string p_BDT_WeightsDir="";
std::string p_SelectorBDT_WeightsDir="";

// Analysis BDT Weights file
std::string p_AnalysisBDT_WeightsDir="";

// Guard to stop tune changing
bool SelectionParametersAreSet=false;

int p_RunPeriod;
int p_BeamMode;

};

#endif

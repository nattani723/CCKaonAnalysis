#!/bin/bash

# Define a function to run a ROOT macro with specified parameters
run_root_macro() {
    local label=$1
    local isHistosPDG=$2
    local nbinsX=$3
    local xlow=$4
    local xhigh=$5
    local title=$6
    local isPrimaryX=$7
    local variableX=$8
    local nbinsY=${9:-0}
    local ylow=${10:-0}
    local yhigh=${11:-0}
    local isPrimaryY=${12:-false}
    local variableY=${13:-""}

    root -l -q -b "BDTXCheckPlotList.C(\"$label\", $isHistosPDG, $nbinsX, $xlow, $xhigh, \"$title\", $isPrimaryX, \"$variableX\", $nbinsY, $ylow, $yhigh, $isPrimaryY, \"$variableY\")"
}

# Call the function with different sets of parameters
#run_root_macro "PrimaryLength" true 25 0 100 ";Track Length (cm);Events" true "TrackLength" 
run_root_macro "DaughterLength" true 25 0 100 ";Track Length (cm);Events" false "TrackLength" 

#run_root_macro "PrimaryLLRPID" true 20 -1 1 ";LLRPID p/#mu;Events" true "LLRPID"
#run_root_macro "PrimaryLLRPIDKaon" true 20 -1 1 ";LLRPID p/K;Events" true "LLRPIDKaon" 
#run_root_macro "DaughterLLRPID" true 20 -1 1 ";LLRPID p/#mu;Events" false "LLRPID"
#run_root_macro "DaughterLLRPIDKaon" true 20 -1 1 ";LLRPID p/K;Events" false "LLRPIDKaon" 

#run_root_macro "PrimaryChi2KaonPl2" true 25 0 50 ";#Chi_{K^{+}};Events" true "Chi2KaonPlane2"
#run_root_macro "PrimaryChi2ProtonPl2" true 25 0 50 ";#Chi_{p};Events" true "Chi2ProtonPlane2"
#run_root_macro "PrimaryChi2MuonPl2" true 25 0 100 ";#Chi_{p};Events" true "Chi2MuonPlane2"
#run_root_macro "PrimaryChi2PionPl2" true 25 0 100 ";#Chi_{p};Events" true "Chi2PionPlane2"

#run_root_macro "DaughterChi2KaonPl2" true 25 0 50 ";#Chi_{K^{+}};Events" false "Chi2KaonPlane2"
#run_root_macro "DaughterChi2ProtonPl2" true 25 0 50 ";#Chi_{p};Events" false "Chi2ProtonPlane2"
#run_root_macro "DaughterChi2MuonPl2" true 25 0 100 ";#Chi_{p};Events" false "Chi2MuonPlane2"
#run_root_macro "DaughterChi2PionPl2" true 25 0 100 ";#Chi_{p};Events" false "Chi2PionPlane2"

#run_root_macro "PrimaryChi2Kaon3Pl" true 25 0 50 ";#Chi_{K^{+}};Events" true "Chi2Kaon3Plane"
#run_root_macro "PrimaryChi2Proton3Pl" true 25 0 50 ";#Chi_{p};Events" true "Chi2Proton3Plane"
#run_root_macro "PrimaryChi2Muon3Pl" true 25 0 100 ";#Chi_{p};Events" true "Chi2Muon3Plane"
#run_root_macro "PrimaryChi2Pion3Pl" true 25 0 100 ";#Chi_{p};Events" true "Chi2Pion3Plane"

#run_root_macro "DaughterChi2Kaon3Pl" true 25 0 50 ";#Chi_{K^{+}};Events" false "Chi2Kaon3Plane"
#run_root_macro "DaughterChi2Proton3Pl" true 25 0 50 ";#Chi_{p};Events" false "Chi2Proton3Plane"
#run_root_macro "DaughterChi2Muon3Pl" true 25 0 100 ";#Chi_{p};Events" false "Chi2Muon3Plane"
#run_root_macro "DaughterChi2Pion3Pl" true 25 0 100 ";#Chi_{p};Events" false "Chi2Pion3Plane"

#run_root_macro "PrimaryMeandEdX" true 30 0 30 ";Three Plane Mean dE/dx;Events" true "MeandEdX3Plane"
#run_root_macro "DaughterMeandEdX" true 30 0 30 ";Three Plane Mean dE/dx;Events" false "MeandEdX3Plane"

#run_root_macro "PrimaryBraggPIDKaon" true 30 0 30 ";Bragg PID K^{+};Event" true "BraggPIDKaon"
#run_root_macro "DaughterBraggPIDKaon" true 30 0 30 ";Bragg PID K^{+};Event" false "BraggPIDKaon"

#run_root_macro "PrimaryChi2KChi2Pr" false 25 0 50 ";#Chi_{p^{+}};#Chi_{K^{+}};" true "Chi2ProtonPlane2" 15 0 30 true "Chi2KaonPlane2"
#run_root_macro "DaughterChi2MuChi2Pr" false 30 0 150 ";#Chi_{p^{+}};#Chi_{#mu^{+}};" false "Chi2ProtonPlane2" 12 0 60 false "Chi2MuonPlane2"

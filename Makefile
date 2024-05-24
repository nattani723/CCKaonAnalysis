#!/bin/bash

CXX=g++
CFLAGS=`${ROOTSYS}/bin/root-config --cflags` -fPIC 
INC=-I${HYP_TOP}/Core  -I${HYP_TOP}/Alg

all: $(addprefix lib/, BDTManager.o CTTest.o FiducialVolume.o FluxWeight2.o Muon_ID.o\
	TrackLengthCutManager.o SelectorBDTManager.o AnalysisBDTManager.o StatisticsManager.o\
	EventListFilter.o ForwardFolder2.o GenG4WeightHandler2.o Reweighter.o\
	SecondaryVertexFitter.o SelectionManager.o EventAssembler.o MultiVariateRNG.o libParticleDict.rootmap\
	libParticleDict.so libHyperon.so) 

lib/libParticleDict.rootmap: Core/LinkDef.h
	rootcling -v4 -f ${HYP_TOP}/lib/ParticleDict.cxx  -rmf ${HYP_TOP}/lib/libParticleDict.rootmap -rml ${HYP_TOP}/lib/libParticleDict.so  ${HYP_TOP}/Core/LinkDef.h

lib/libParticleDict.so: lib/libParticleDict.rootmap	
	g++ -shared -fPIC -I${HYP_TOP}/Core -o ${HYP_TOP}/lib/libParticleDict.so ${HYP_TOP}/lib/ParticleDict.cxx `root-config --cflags --libs`

%.o: %.cxx
	g++ $(CFLAGS) -c $(INC)  $< -o $@

lib/BDTManager.o: Alg/BDTManager.cxx
	g++ $(CFLAGS) -c $(INC)  $< -o $@	

lib/AnalysisBDTManager.o: Alg/AnalysisBDTManager.cxx
	g++ $(CFLAGS) -c $(INC)  $< -o $@	

lib/CTTest.o: Alg/CTTest.cxx
	g++ $(CFLAGS) -c $(INC)  $< -o $@	

lib/FiducialVolume.o: Alg/FiducialVolume.cxx
	g++ $(CFLAGS) -c $(INC)  $< -o $@	

lib/FluxWeight2.o: Alg/FluxWeight2.cxx
	g++ $(CFLAGS) -c $(INC)  $< -o $@	

lib/Muon_ID.o: Alg/Muon_ID.cxx
	g++ $(CFLAGS) -c $(INC)  $< -o $@	
	
lib/TrackLengthCutManager.o: Alg/TrackLengthCutManager.cxx
	g++ $(CFLAGS) -c $(INC)  $< -o $@	

lib/SelectorBDTManager.o: Alg/SelectorBDTManager.cxx
	g++ $(CFLAGS) -c $(INC)  $< -o $@	

lib/EventListFilter.o: Alg/EventListFilter.cxx
	g++ $(CFLAGS) -c $(INC)  $< -o $@	

lib/ForwardFolder2.o: Alg/ForwardFolder2.cxx
	g++ $(CFLAGS) -c $(INC)  $< -o $@	

lib/GenG4WeightHandler2.o: Alg/GenG4WeightHandler2.cxx
	g++ $(CFLAGS) -c $(INC)  $< -o $@	

lib/SecondaryVertexFitter.o: Alg/SecondaryVertexFitter.cxx
	g++ $(CFLAGS) -c $(INC)  $< -o $@	

lib/SelectionManager.o: Core/SelectionManager.cxx Alg/PlottingFunctions.h Alg/FluxWeight2.h
	g++ $(CFLAGS) -c $(INC)  $< -o $@	

lib/EventAssembler.o: Core/EventAssembler.cxx
	g++ $(CFLAGS) -c $(INC)  $< -o $@	
	
lib/MultiVariateRNG.o: Alg/MultiVariateRNG.cxx
	g++ $(CFLAGS) -c $(INC)  $< -o $@	

lib/StatisticsManager.o: Alg/StatisticsManager.cxx Alg/BayesianPosteriorPDF.h
	g++ $(CFLAGS) -c $(INC)  $< -o $@	

lib/SidebandFitter.o: Alg/SidebandFitter.cxx
	g++ $(CFLAGS) -c $(INC)  $< -o $@	

lib/Reweighter.o: Alg/Reweighter.cxx
	g++ $(CFLAGS) -c $(INC)  $< -o $@	
	
lib/libHyperon.so: $(addprefix lib/, BDTManager.o AnalysisBDTManager.o CTTest.o FiducialVolume.o FluxWeight2.o Muon_ID.o TrackLengthCutManager.o SelectorBDTManager.o SecondaryVertexFitter.o EventListFilter.o ForwardFolder2.o GenG4WeightHandler2.o EventAssembler.o SelectionManager.o MultiVariateRNG.o StatisticsManager.o SidebandFitter.o Reweighter.o)
	g++ -shared `${ROOTSYS}/bin/root-config --libs` lib/FiducialVolume.o lib/FluxWeight2.o lib/Muon_ID.o lib/TrackLengthCutManager.o lib/SelectorBDTManager.o lib/SecondaryVertexFitter.o lib/AnalysisBDTManager.o lib/EventListFilter.o lib/ForwardFolder2.o lib/CTTest.o lib/GenG4WeightHandler2.o lib/EventAssembler.o lib/SelectionManager.o lib/MultiVariateRNG.o lib/StatisticsManager.o lib/SidebandFitter.o lib/Reweighter.o -o lib/libHyperon.so lib/BDTManager.o 

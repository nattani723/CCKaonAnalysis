#ifndef _SelectionManager_cxx_
#define _SelectionManager_cxx_

#include "SelectionManager.h"

///////////////////////////////////////////////////////////////////////////////////////////////

// Default constructor

SelectionManager::SelectionManager() : 
   a_FluxWeightCalc(0) ,
   a_GenG4WeightCalc() ,
   a_FiducialVolume(1,0.0) ,
   a_MuonID(-0.35,18.0,0.0) ,
   a_TrackLengthCutManager(1000.0,1000.0) , 
   a_BDTManager("Test") ,
   a_EventListFilter() ,
   a_SecondaryVertexFitter(5)
{
   std::cout << "Calling default constructor for SelectionManager" << std::endl;
   DeclareCuts();
}

///////////////////////////////////////////////////////////////////////////////////////////////

// Destructor

SelectionManager::~SelectionManager(){


}

///////////////////////////////////////////////////////////////////////////////////////////////

// Constructor that loads selection parameters

SelectionManager::SelectionManager(SelectionParameters p) :
   a_FluxWeightCalc(p.p_BeamMode) ,
   a_GenG4WeightCalc() ,
   a_FiducialVolume(p.p_FV,p.p_Padding) ,
   a_MuonID(p.p_PID_Cut,p.p_Minimum_MIP_Length,p.p_Max_Displacement) ,
   a_TrackLengthCutManager(p.p_SecondaryTrackLengthCut,p.p_SecondaryTrackLengthCut) ,
   a_BDTManager("Test") , 
   a_EventListFilter() ,
   a_SecondaryVertexFitter(p.p_VertexPull)
{
   std::cout << "Building SelectionManager" << std::endl;

   if(!p.HasBeenSetup)
      throw std::invalid_argument("SelectionManager: Selection parameters " + p.Name + " have not been loaded. Run BuildTunes() first");

   // Set the selection parameters
   TheParams = p;
   DeclareCuts();
}

///////////////////////////////////////////////////////////////////////////////////////////////

// Close selection manager

void SelectionManager::Close(){
   if(f_Hists != nullptr) f_Hists->Close();
}

///////////////////////////////////////////////////////////////////////////////////////////////

// Set the beam being used

void SelectionManager::SetBeamMode(int mode){

   assert(mode == kFHC || mode == kRHC || mode == kBNB);

   BeamMode = mode;
}

///////////////////////////////////////////////////////////////////////////////////////////////

// Return the selection parameters loaded

SelectionParameters SelectionManager::GetParams(){
   return TheParams;
}

///////////////////////////////////////////////////////////////////////////////////////////////

// Load a sample of events, specify name, type and POT. Can also load list of selected events
// if using the event list cut

void SelectionManager::AddSample(std::string Name,std::string Type,double SamplePOT,std::string EventList){

   std::cout << "Processing Sample " << Name << " of type " << Type << " and POT " << SamplePOT <<  std::endl;

   if(Type != "Data") thisSampleWeight = POT/SamplePOT;
   else thisSampleWeight = 1.0;

   thisSampleName = Name;
   thisSampleType = Type;

   if(thisSampleType != "Data" && thisSampleType != "EXT"){
     thisSampleGenerator = kGENIE; // we do not use NuWro for this analysis
     /*
      if (thisSampleName.find("GENIE") != std::string::npos) thisSampleGenerator = kGENIE;
      else if (thisSampleName.find("NuWro") != std::string::npos) thisSampleGenerator = kNuWro;      
      else thisSampleGenerator = -1;
     */
   }

   if(Type == "Data") fHasData = true;

   TString DataDir = getenv("DATA_DIR");         

   TString file = DataDir + TString("/EventLists/") +  TString(EventList);  

   if(EventList != ""){
      std::cout << "Adding event list " << EventList << std::endl;
      a_EventListFilter.SetList(file); 
   }
}

///////////////////////////////////////////////////////////////////////////////////////////////

// Load an event, normalise its weight using the POT of the current sample

void SelectionManager::AddEvent(Event &e){

   // Sample Orthogonality

  if( ( thisSampleType != "AssocKaon" && thisSampleType != "SingleKaon" )  &&   e.EventHasKaonP){ e.Weight = 0.0; return; }
  if( ( thisSampleType == "AssocKaon" || thisSampleType == "SingleKaon" )  &&  !e.EventHasKaonP){ e.Weight = 0.0; return; }

   // Set flux weight if setup
   if(thisSampleType != "Data" && thisSampleType != "EXT"){
      if(fUseFluxWeight) e.Weight *= a_FluxWeightCalc.GetFluxWeight(e);        
      if(fUseGenWeight) {
         a_GenG4WeightCalc.LoadEvent(e);
         e.Weight *= a_GenG4WeightCalc.GetCVWeight();
      }
   }

   if(thisSampleType != "Data") e.Weight *= thisSampleWeight;

   for(size_t i_c=0;i_c<Cuts.size();i_c++){

      Cuts[i_c].fTotalEvents += e.Weight;

      if(e.EventIsSignal) Cuts[i_c].fSignalEvents += e.Weight;
      if(e.GoodReco) Cuts[i_c].fGoodRecoEvents += e.Weight;
      if(e.EventIsSignal_NuMuP) Cuts[i_c].fSignalEvents_NuMuP += e.Weight;
      if(e.GoodReco_NuMuP) Cuts[i_c].fGoodRecoEvents_NuMuP += e.Weight;
      if(e.EventIsSignal) Cuts[i_c].fSignalEvents_PiPPi0 += e.Weight;
      if(e.GoodReco) Cuts[i_c].fGoodRecoEvents_PiPPi0 += e.Weight;

      Cuts[i_c].fTotalEventsVar += e.Weight*e.Weight;
      if(e.EventIsSignal) Cuts[i_c].fSignalEventsVar += e.Weight*e.Weight;
      if(e.GoodReco) Cuts[i_c].fGoodRecoEventsVar += e.Weight*e.Weight;
      if(e.EventIsSignal_NuMuP) Cuts[i_c].fSignalEventsVar_NuMuP += e.Weight*e.Weight;
      if(e.GoodReco_NuMuP) Cuts[i_c].fGoodRecoEventsVar_NuMuP += e.Weight*e.Weight;
      if(e.EventIsSignal_PiPPi0) Cuts[i_c].fSignalEventsVar_PiPPi0 += e.Weight*e.Weight;
      if(e.GoodReco_PiPPi0) Cuts[i_c].fGoodRecoEventsVar_PiPPi0 += e.Weight*e.Weight;

   }
}

///////////////////////////////////////////////////////////////////////////////////////////////

void SelectionManager::UseFluxWeight(bool usefluxweight){
   fUseFluxWeight = usefluxweight;
}

///////////////////////////////////////////////////////////////////////////////////////////////

void SelectionManager::UseGenWeight(bool usegenweight){
   fUseGenWeight = usegenweight;
} 

///////////////////////////////////////////////////////////////////////////////////////////////

// Apply the signal definition

void SelectionManager::SetSignal(Event &e){


   e.EventIsSignal = false;
   e.EventIsSignal_NuMuP = false;
   e.EventIsSignal_PiPPi0 = false;

   e.GoodReco = false;
   e.GoodReco_NuMuP = false;
   e.GoodReco_PiPPi0 = false;
   e.GoodPrimaryReco = false;
   e.GoodRecoAsShower = false;

   std::vector<bool> IsSignal_tmp = e.IsSignal;
   std::vector<bool> IsSignal_NuMuP_tmp = e.IsSignal_NuMuP;
   std::vector<bool> IsSignal_PiPPi0_tmp = e.IsSignal_PiPPi0;

   for(size_t i_tr=0;i_tr<e.NMCTruths;i_tr++){

      IsSignal_tmp.at(i_tr) = false;
      IsSignal_NuMuP_tmp.at(i_tr) = false;
      IsSignal_PiPPi0_tmp.at(i_tr) = false;

      e.InActiveTPC.at(i_tr) = a_FiducialVolume.InFiducialVolume_MCC9(e.TruePrimaryVertex.at(i_tr)); 

      if(e.IsSignal.at(i_tr) || e.IsSignal_NuMuP.at(i_tr) || e.IsSignal_PiPPi0.at(i_tr) ){

	//bool found_proton=false, found_pion=false;
	bool found_pion, found_muon;

         for(size_t i_d=0;i_d<e.KaonPDecay.size();i_d++){

	   //std::cout << "i_tr: " << i_tr << ", e.KaonPDecay.at(i_d).MCTruthIndex: " << e.KaonPDecay.at(i_d).MCTruthIndex << ", e.KaonPDecay.at(i_d).PDG: " << e.KaonPDecay.at(i_d).PDG << ", e.KaonPDecay.at(i_d).ModMomentum: " << e.KaonPDecay.at(i_d).ModMomentum << std::endl;
	   if(e.KaonPDecay.at(i_d).MCTruthIndex == i_tr && e.KaonPDecay.at(i_d).PDG == -13 && e.KaonPDecay.at(i_d).ModMomentum > 0.1) 
	     found_muon = true;

	   if(e.KaonPDecay.at(i_d).MCTruthIndex == i_tr && e.KaonPDecay.at(i_d).PDG == 211 && e.KaonPDecay.at(i_d).ModMomentum > 0.1)
	     found_pion = true;

         }

	 IsSignal_tmp.at(i_tr) = (found_muon || found_pion) && e.InActiveTPC.at(i_tr) && e.IsSignal.at(i_tr);
	 IsSignal_NuMuP_tmp.at(i_tr) = found_muon && e.InActiveTPC.at(i_tr) && e.IsSignal_NuMuP.at(i_tr);
	 IsSignal_PiPPi0_tmp.at(i_tr) = found_pion && e.InActiveTPC.at(i_tr) && e.IsSignal_PiPPi0.at(i_tr);

      }
      //std::cout << "e.IsSignal after assessment: " << IsSignal_tmp.at(i_tr) << std::endl; 

   }


   e.IsSignal = IsSignal_tmp;

   e.IsSignal_NuMuP = IsSignal_NuMuP_tmp;
   e.IsSignal_PiPPi0 = IsSignal_PiPPi0_tmp;

   e.EventIsSignal = std::find(e.IsSignal.begin(),e.IsSignal.end(), true) != e.IsSignal.end();
   e.EventIsSignal_NuMuP = std::find(e.IsSignal_NuMuP.begin(),e.IsSignal_NuMuP.end(), true) != e.IsSignal_NuMuP.end();
   e.EventIsSignal_PiPPi0 = std::find(e.IsSignal_PiPPi0.begin(),e.IsSignal_PiPPi0.end(), true) != e.IsSignal_PiPPi0.end();


   // Search the list of reco'd tracks for the proton and pion
   bool found_kaon=false, found_muon=false, found_decay_muon=false, found_decay_pion=false;

   if(!e.EventIsSignal) return;

   for(size_t i_tr=0;i_tr<e.TrackPrimaryDaughters.size();i_tr++){

      if(e.TrackPrimaryDaughters.at(i_tr).HasTruth && e.TrackPrimaryDaughters.at(i_tr).TrackTruePDG == 321 && e.TrackPrimaryDaughters.at(i_tr).TrackTrueOrigin == 1){ 
         found_kaon = true; 
         e.TrueKaonIndex = i_tr; 
      }

      /*
      if(e.TrackPrimaryDaughters.at(i_tr).HasTruth && e.TrackPrimaryDaughters.at(i_tr).TrackTruePDG == 13 && e.TrackPrimaryDaughters.at(i_tr).TrackTrueOrigin == 1){ 
         found_muon = true; 
         e.TrueMuonIndex = i_tr; 
      }

      
      if(e.TrackPrimaryDaughters.at(i_tr).HasTruth && e.TrackPrimaryDaughters.at(i_tr).TrackTruePDG == -13 && e.TrackPrimaryDaughters.at(i_tr).TrackTrueOrigin == 2){ 
         found_decay_muon = true; 
         e.TrueDecayMuonIndex = i_tr; 
      }

      if(e.TrackPrimaryDaughters.at(i_tr).HasTruth && e.TrackPrimaryDaughters.at(i_tr).TrackTruePDG == 211 && e.TrackPrimaryDaughters.at(i_tr).TrackTrueOrigin == 2){
         found_decay_pion = true;
         e.TrueDecayPionIndex = i_tr; 
      }
      */

   }

   for(size_t i_tr=0;i_tr<e.TrackOthers.size();i_tr++){ 

     if(e.TrackOthers.at(i_tr).HasTruth && e.TrackOthers.at(i_tr).TrackTruePDG == -13){
       found_decay_muon = true;
       e.TrueDecayMuonIndex = i_tr;
     }

     if(e.TrackOthers.at(i_tr).HasTruth && e.TrackOthers.at(i_tr).TrackTruePDG == 211){
       found_decay_pion = true;
       e.TrueDecayPionIndex = i_tr;
     }

   }

   for(size_t i_tr=0;i_tr<e.TrackRebuiltOthers.size();i_tr++){ 

     if(e.TrackRebuiltOthers.at(i_tr).HasTruth && e.TrackRebuiltOthers.at(i_tr).TrackTruePDG == -13){
       found_decay_muon = true;
       e.TrueDecayRebuiltMuonIndex = i_tr;
     }

     if(e.TrackOthers.at(i_tr).HasTruth && e.TrackOthers.at(i_tr).TrackTruePDG == 211){
       found_decay_pion = true;
       e.TrueDecayRebuiltPionIndex = i_tr;
     }

   }
   
   e.GoodReco = e.EventIsSignal && found_kaon && ( found_decay_muon || found_decay_pion );
   e.GoodReco_NuMuP = e.EventIsSignal && found_kaon && found_decay_muon;
   e.GoodReco_PiPPi0 = e.EventIsSignal && found_kaon && found_decay_pion;
   e.GoodPrimaryReco = e.EventIsSignal && found_kaon;

}

///////////////////////////////////////////////////////////////////////////////////////////////

// Load the list of cuts

void SelectionManager::DeclareCuts(){

   for(size_t i_c=0;i_c<CutTypes.size();i_c++){
      Cut c;
      c.fName = CutTypes.at(i_c);
      Cuts.push_back(c);
   }
}

///////////////////////////////////////////////////////////////////////////////////////////////

// Add an event to a cut

void SelectionManager::UpdateCut(const Event &e,bool Passed,std::string CutName){

   for(size_t i_c=0;i_c<Cuts.size();i_c++){

      if(Cuts.at(i_c).fName == CutName){

         Cuts[i_c].fEventsIn += e.Weight;

         if(e.EventIsSignal) Cuts[i_c].fSignalEventsIn += e.Weight;
         if(e.GoodReco) Cuts[i_c].fGoodRecoEventsIn += e.Weight;
         if(e.EventIsSignal_NuMuP) Cuts[i_c].fSignalEventsIn_NuMuP += e.Weight;
         if(e.GoodReco_NuMuP) Cuts[i_c].fGoodRecoEventsIn_NuMuP += e.Weight;
         if(e.EventIsSignal_PiPPi0) Cuts[i_c].fSignalEventsIn_PiPPi0 += e.Weight;
         if(e.GoodReco_PiPPi0) Cuts[i_c].fGoodRecoEventsIn_PiPPi0 += e.Weight;

         Cuts[i_c].fEventsInVar += e.Weight*e.Weight;
         if(e.EventIsSignal) Cuts[i_c].fSignalEventsInVar += e.Weight*e.Weight;
         if(e.GoodReco) Cuts[i_c].fGoodRecoEventsInVar += e.Weight*e.Weight;
         if(e.EventIsSignal_NuMuP) Cuts[i_c].fSignalEventsInVar_NuMuP += e.Weight*e.Weight;
         if(e.GoodReco_NuMuP) Cuts[i_c].fGoodRecoEventsInVar_NuMuP += e.Weight*e.Weight;
         if(e.EventIsSignal_PiPPi0) Cuts[i_c].fSignalEventsInVar_PiPPi0 += e.Weight*e.Weight;
         if(e.GoodReco_PiPPi0) Cuts[i_c].fGoodRecoEventsInVar_PiPPi0 += e.Weight*e.Weight;

         if(Passed){

            Cuts[i_c].fEventsOut += e.Weight;
            if(e.EventIsSignal) Cuts[i_c].fSignalEventsOut += e.Weight;
            if(e.GoodReco) Cuts[i_c].fGoodRecoEventsOut += e.Weight;
            if(e.EventIsSignal_NuMuP) Cuts[i_c].fSignalEventsOut_NuMuP += e.Weight;
            if(e.GoodReco_NuMuP) Cuts[i_c].fGoodRecoEventsOut_NuMuP += e.Weight;
            if(e.EventIsSignal) Cuts[i_c].fSignalEventsOut += e.Weight;
            if(e.GoodReco) Cuts[i_c].fGoodRecoEventsOut += e.Weight;

            Cuts[i_c].fEventsOutVar += e.Weight*e.Weight;
            if(e.EventIsSignal) Cuts[i_c].fSignalEventsOutVar += e.Weight*e.Weight;
            if(e.GoodReco) Cuts[i_c].fGoodRecoEventsOutVar += e.Weight*e.Weight;
            if(e.EventIsSignal_NuMuP) Cuts[i_c].fSignalEventsOutVar_NuMuP += e.Weight*e.Weight;
            if(e.GoodReco_NuMuP) Cuts[i_c].fGoodRecoEventsOutVar_NuMuP += e.Weight*e.Weight;
            if(e.EventIsSignal_PiPPi0) Cuts[i_c].fSignalEventsOutVar_PiPPi0 += e.Weight*e.Weight;
            if(e.GoodReco_PiPPi0) Cuts[i_c].fGoodRecoEventsOutVar_PiPPi0 += e.Weight*e.Weight;
 
        }       
      }
   }
}

///////////////////////////////////////////////////////////////////////////////////////////////

// Retrieve the results from a cut

Cut SelectionManager::GetCut(std::string CutName){

   for(size_t i_c=0;i_c<Cuts.size();i_c++)
      if(Cuts.at(i_c).fName == CutName) return Cuts.at(i_c);

   std::cout << "Cut " << CutName << " not found" << std::endl;

   Cut c;
   return c;
}

///////////////////////////////////////////////////////////////////////////////////////////////

// Reset the data in the cuts

void SelectionManager::Reset(){
   for(size_t i_c=0;i_c<Cuts.size();i_c++) Cuts[i_c].Reset();  
}

///////////////////////////////////////////////////////////////////////////////////////////////

// Load the track selector BDT weights

void SelectionManager::ImportBDTWeights(std::string WeightDir){

   std::cout << "SelectionManager: Importing BDT Weights from " << WeightDir << std::endl;
   a_BDTManager.SetupBDT(WeightDir);
}

/*
///////////////////////////////////////////////////////////////////////////////////////////////

// Load the analysis BDT weights

void SelectionManager::ImportAnalysisBDTWeights(std::string WeightDir){

   std::cout << "SelectionManager: Importing Analysis BDT Weights from " << WeightDir << std::endl;
   a_AnalysisBDTManager.SetupAnalysisBDT(WeightDir);

}
*/

///////////////////////////////////////////////////////////////////////////////////////////////

// Apply the fiducial volume cut

bool SelectionManager::FiducialVolumeCut(const Event &e){

   bool passed = a_FiducialVolume.InFiducialVolume_MCC9(e.RecoPrimaryVertex);

   UpdateCut(e,passed,"FV");

   return passed;
}

///////////////////////////////////////////////////////////////////////////////////////////////

// Apply the fiducial volume cut for daughter track

bool SelectionManager::DaughterFiducialVolumeCut(const Event &e){

  //RecoParticle DaughterTrackParticle = GetDaughterTrackParticle();
  TVector3 DaughterTrackEnd;

  //for (const auto& pair : VectorPair){

    DaughterTrackEnd.Clear();

    auto isOutsideFiducialVolume = [&](const std::pair<RecoParticle, RecoParticle>& pair) {
      DaughterTrackEnd.SetXYZ(pair.second.TrackEndX, pair.second.TrackEndY, pair.second.TrackEndZ);
      return !a_FiducialVolume.InFiducialVolume_5cm(DaughterTrackEnd);
    };

    VectorPair.erase(std::remove_if(VectorPair.begin(), VectorPair.end(), isOutsideFiducialVolume), VectorPair.end());

    /*
    RecoParticle DaughterTrackParticle = pair.second;
    DaughterTrackEnd.SetXYZ(DaughterTrackParticle.TrackEndX, DaughterTrackParticle.TrackEndY, DaughterTrackParticle.TrackEndZ);
 
    if(!a_FiducialVolume.InFiducialVolume_5cm(DaughterTrackEnd))
    */

    //}

    bool passed = VectorPair.size() > 0;
  //bool passed = a_FiducialVolume.InFiducialVolume_5cm(DaughterTrackEnd);

   UpdateCut(e,passed,"DaughterFV");

   return passed;
}

///////////////////////////////////////////////////////////////////////////////////////////////

// Apply NuCC Inclusive Filter

bool SelectionManager::NuCCInclusiveFilter(const Event &e){

	bool passed = e.PassNuCCInclusiveFilter;
	
	UpdateCut(e,passed,"NuCCInclusiveFilter");
	
	return passed;
}

///////////////////////////////////////////////////////////////////////////////////////////////

// Apply the three track cut

void SelectionManager::StorePrimaryDaughterTracksPair(const Event &e){

  RecoParticle PrimaryTrack;
  RecoParticle DaughterTrack;

  TVector3 PrimaryEnd;
  TVector3 DaughterStart;
  TVector3 PrimaryDaughterDistance;

  VectorPair.clear();

  for(size_t i_tr=0;i_tr<e.TrackPrimaryDaughters.size();i_tr++){

     PrimaryEnd.Clear();
     PrimaryTrack = e.TrackPrimaryDaughters.at(i_tr);
     PrimaryEnd.SetXYZ(PrimaryTrack.TrackEndX, PrimaryTrack.TrackEndY, PrimaryTrack.TrackEndZ);

     for(size_t i_tr_dau=0;i_tr_dau<e.TrackOthers.size();i_tr_dau++){
       
       DaughterStart.Clear();
       DaughterTrack = e.TrackOthers.at(i_tr_dau);
       DaughterStart.SetXYZ(DaughterTrack.TrackStartX, DaughterTrack.TrackStartY, DaughterTrack.TrackStartZ);

       PrimaryDaughterDistance = PrimaryEnd - DaughterStart;

       if( PrimaryDaughterDistance.Mag() < 10){
	 SetPrimaryKaonTrackParticle(&PrimaryTrack);
	 SetDaughterTrackParticle(&DaughterTrack);
       }
 
     }

     double maxLength=-1;
     int index=-1;
     RecoParticle DaughterTrackRebuilt;

     for(size_t i_tr_dau=0;i_tr_dau<e.TrackRebuiltOthers.size();i_tr_dau++){

       DaughterTrackRebuilt = e.TrackRebuiltOthers.at(i_tr_dau);
       if(DaughterTrackRebuilt.TrackLength>maxLength) index = i_tr_dau;

     }

     if(index>=0) DaughterTrackRebuilt = e.TrackRebuiltOthers.at(index); 

     if( DaughterTrackRebuilt.TrackLength>0 && (DaughterTrack.TrackLength<40. || DaughterTrack.TrackLength>65.) )
       SetDaughterTrackParticle(&DaughterTrackRebuilt);

     
     RecoParticle * PrimaryKaonTrackParticle = GetPrimaryKaonTrackParticle();
     RecoParticle * DaughterTrackParticle = GetDaughterTrackParticle();

     if(PrimaryKaonTrackParticle && DaughterTrackParticle){

       std::pair <RecoParticle, RecoParticle> PrimaryDaughterTracksPair = {*PrimaryKaonTrackParticle, *DaughterTrackParticle};
       VectorPair.push_back(PrimaryDaughterTracksPair);

     }

     SetPrimaryKaonTrackParticle(0);
     SetDaughterTrackParticle(0);

  }//TrackPrimaryDaughters loop

}

///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////

bool SelectionManager::DaughterTrackCut(const Event &e){

  StorePrimaryDaughterTracksPair(e);

  bool passed = VectorPair.size() > 0; 

   UpdateCut(e,passed,"DaughterTrack");

   return passed;
}

///////////////////////////////////////////////////////////////////////////////////////////////

// Select the muon candidate

bool SelectionManager::ChooseMuonCandidate(Event &e){

   int i_muon = a_MuonID.SelectCandidate(e.TrackPrimaryDaughters);

   if(i_muon == -1){
      UpdateCut(e,false,"MuonID");
      return false;
   }

   RecoParticle theMuonCandidate = e.TrackPrimaryDaughters.at(i_muon);
   e.MuonCandidate = theMuonCandidate;
   e.TrackPrimaryDaughters.erase(e.TrackPrimaryDaughters.begin()+i_muon);

   UpdateCut(e,true,"MuonID");

   return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////

// Apply the secondary track length cut

bool SelectionManager::DaughterTrackLengthCut(const Event &e){

  RecoParticle * DaughterTrackParticle = GetDaughterTrackParticle();
  bool passed = DaughterTrackParticle->TrackLength > 20.f;

   UpdateCut(e,passed,"DaughterTrackLength");

   return passed;
}


///////////////////////////////////////////////////////////////////////////////////////////////

// Calculate decay analysis BDT score and apply cut. This also stores BDT score for each Event.

bool SelectionManager::BDTCut(Event &e){

   bool passed = a_BDTManager.CalculateScore(e) > TheParams.p_BDT_Cut; 

   UpdateCut(e,passed,"BDT");

   return passed;
}

///////////////////////////////////////////////////////////////////////////////////////////////

// Select events in the list already loaded

bool SelectionManager::EventListCut(const Event &e){

   bool passed = a_EventListFilter.EventPassed(e.run,e.subrun,e.event); 

   UpdateCut(e,passed,"Connectedness");

   return passed;
}

///////////////////////////////////////////////////////////////////////////////////////////////


// Setup histograms, vector with bin boundaries and string containing axis titles (same format
// as Root TH1 titles).

void SelectionManager::SetupHistograms(std::vector<double> boundaries,std::string title){

   if(boundaries.size() < 2)
      throw std::invalid_argument("Require at least 2 bin boundaries"); 

   fTitle = title;
   fHistNBins = boundaries.size()-1;
   fHistLow = boundaries.front();
   fHistHigh = boundaries.back();
   fHistBoundaries = boundaries;

   const int arr_n = boundaries.size();
   Double_t arr_boundaries[arr_n];
   for(size_t i=0;i<arr_n;i++) arr_boundaries[i] = boundaries.at(i);

   for(size_t i_proc=0;i_proc<EventType::Procs.size();i_proc++){
      std::string histname = "h_" + EventType::Procs.at(i_proc);
      Hists_ByProc[EventType::Procs.at(i_proc)] = new TH1D(histname.c_str(),fTitle.c_str(),fHistNBins,arr_boundaries);
   }

   for(size_t i_type=0;i_type<EventType::Types.size();i_type++){
      std::string histname = "h_ByType_" + EventType::Types.at(i_type);
      Hists_ByType[EventType::Types.at(i_type)] = new TH1D(histname.c_str(),fTitle.c_str(),fHistNBins,arr_boundaries);
   }

   for(size_t i_type=0;i_type<EventType::Types2.size();i_type++){
      std::string histname = "h_ByType2_" + EventType::Types2.at(i_type);
      Hists_ByType2[EventType::Types2.at(i_type)] = new TH1D(histname.c_str(),fTitle.c_str(),fHistNBins,arr_boundaries);
   }

   Hist_All = new TH1D("All",fTitle.c_str(),fHistNBins,arr_boundaries);
   Hist_Data = new TH1D("Data",fTitle.c_str(),fHistNBins,arr_boundaries);
}

///////////////////////////////////////////////////////////////////////////////////////////////

// Setup histograms. Give bin boundaries and number of bins. String containing axis titles 
// (same format as Root TH1 titles).

void SelectionManager::SetupHistograms(int n,double low,double high,std::string title){

   fTitle = title;
   fHistNBins = n;
   fHistLow = low;
   fHistHigh = high;

   for(size_t i_proc=0;i_proc<EventType::Procs.size();i_proc++){
      std::string histname = "h_" + EventType::Procs.at(i_proc);
      Hists_ByProc[EventType::Procs.at(i_proc)] = new TH1D(histname.c_str(),fTitle.c_str(),n,low,high);
   }

   for(size_t i_type=0;i_type<EventType::Types.size();i_type++){
      std::string histname = "h_ByType_" + EventType::Types.at(i_type);
      Hists_ByType[EventType::Types.at(i_type)] = new TH1D(histname.c_str(),fTitle.c_str(),n,low,high);
   }

   for(size_t i_type=0;i_type<EventType::Types2.size();i_type++){
      std::string histname = "h_ByType2_" + EventType::Types2.at(i_type);
      Hists_ByType2[EventType::Types2.at(i_type)] = new TH1D(histname.c_str(),fTitle.c_str(),n,low,high);
   }

   Hist_All = new TH1D("All",fTitle.c_str(),n,low,high);
   Hist_Data = new TH1D("Data",fTitle.c_str(),n,low,high);

   double width = (high-low)/n;
   for(int i=0;i<n+1;i++) fHistBoundaries.push_back(low+width*i); 
}

///////////////////////////////////////////////////////////////////////////////////////////////

void SelectionManager::SetupHistogramsEtoP(){

   Hist_BDT_Signal = new TH1D("BDT_Signal",fTitle.c_str(),fHistNBins,fHistLow,fHistHigh);
   Hist_BDT_All = new TH1D("BDT_All",fTitle.c_str(),fHistNBins,fHistLow,fHistHigh);
   Hist_Efficiency = new TH1D("BDT_Efficiency",fTitle.c_str(),fHistNBins,fHistLow,fHistHigh);
   Hist_Purity = new TH1D("BDT_Purity",fTitle.c_str(),fHistNBins,fHistLow,fHistHigh);
   Hist_EtoP = new TH1D("BDT_EtoP",fTitle.c_str(),fHistNBins,fHistLow,fHistHigh);

}

///////////////////////////////////////////////////////////////////////////////////////////////

// Setup histograms. Give bin boundaries and number of bins. String containing axis titles 
// (same format as Root TH1 titles).

void SelectionManager::SetupHistogramsPDG(int n,double low,double high,std::string title){

   fTitle = title;
   fHistNBins = n;
   fHistLow = low;
   fHistHigh = high;

   for(size_t i_pdg=0;i_pdg<EventType::PDGs.size();i_pdg++){
      std::string histname_primary = "h_primary_" + EventType::PDGs.at(i_pdg);
      std::string histname_daughter = "h_daughter_" + EventType::PDGs.at(i_pdg);
      Hists_ByPrimaryPDG[EventType::PDGs.at(i_pdg)] = new TH1D(histname_primary.c_str(),fTitle.c_str(),n,low,high);
      Hists_ByDaughterPDG[EventType::PDGs.at(i_pdg)] = new TH1D(histname_daughter.c_str(),fTitle.c_str(),n,low,high);
   }

   Hist_All = new TH1D("All",fTitle.c_str(),n,low,high);
   Hist_Data = new TH1D("Data",fTitle.c_str(),n,low,high);

   double width = (high-low)/n;
   for(int i=0;i<n+1;i++) fHistBoundaries.push_back(low+width*i); 
}


///////////////////////////////////////////////////////////////////////////////////////////////

// Setup histograms. Give bin boundaries and number of bins. String containing axis titles 
// (same format as Root TH2 titles).

void SelectionManager::Setup2DHistograms(int n_x, double low_x, double high_x, int n_y, double low_y, double high_y, std::string title){

   fTitle = title;
   fHist2DNXBins = n_x;
   fHist2DNYBins = n_y;
   fHist2DLowX = low_x;
   fHist2DLowX = low_x;

   for(size_t i_h=0;i_h<EventType::SigBG.size();i_h++){
      std::string histname = "h_" + EventType::SigBG.at(i_h);
      Hists2D_BySigBG[EventType::SigBG.at(i_h)] = new TH2D(histname.c_str(), fTitle.c_str(), n_x, low_x, high_x, n_y, low_y, high_y);
   }

   double width_x = (high_x-low_x)/n_x;
   double width_y = (high_y-low_y)/n_y;
   for(int i=0;i<n_x+1;i++) fHist2DBoundariesX.push_back(low_x+width_x*i);
   for(int i=0;i<n_y+1;i++) fHist2DBoundariesY.push_back(low_y+width_y*i); 
}

///////////////////////////////////////////////////////////////////////////////////////////////

// Setup histograms, vector with bin boundaries and string containing axis titles (same format
// as Root TH2 titles).

void SelectionManager::Setup2DHistograms(std::vector<double> boundariesx, std::vector<double> boundariesy, std::string title){

   if(boundariesx.size() < 2 || boundariesy.size() < 2)
      throw std::invalid_argument("Require at least 2 bin boundaries"); 

   fTitle = title;
   fHist2DNXBins = boundariesx.size()-1;
   fHist2DNYBins = boundariesy.size()-1;
   fHist2DLowX = boundariesx.front();
   fHist2DLowX = boundariesy.front();
   fHist2DHighX = boundariesx.back();
   fHist2DHighY = boundariesy.back();
   fHist2DBoundariesX = boundariesx;
   fHist2DBoundariesY = boundariesy;
	
   const int arr_n_x = boundariesx.size();
   const int arr_n_y = boundariesy.size();
   Double_t arr_boundaries_x[arr_n_x];
   Double_t arr_boundaries_y[arr_n_y];
	
   for(size_t i=0;i<arr_n_x;i++) arr_boundaries_x[i] = boundariesx.at(i);

   for(size_t i_h=0;i_h<EventType::SigBG.size();i_h++){
      std::string histname = "h_" + EventType::SigBG.at(i_h);
      Hists2D_BySigBG[EventType::SigBG.at(i_h)] = new TH2D(histname.c_str(), fTitle.c_str(), fHist2DNXBins, arr_boundaries_x, fHist2DNYBins, arr_boundaries_y);
   }

}

///////////////////////////////////////////////////////////////////////////////////////////////

// Setup histograms for a systematic. Give the type (multisim, single unisim or dual unisim),
// the number of universes and name

void SelectionManager::AddSystematic(int systype,int universes,std::string name){

   std::cout << "Setting up systematic " << name << " with " << universes << " universes" << std::endl;

   const int arr_n = fHistBoundaries.size();
   Double_t arr_boundaries[arr_n];
   for(size_t i=0;i<arr_n;i++) arr_boundaries[i] = fHistBoundaries.at(i);

   if(systype == kMultisim){
      for(size_t i_type=0;i_type<EventType::Types.size();i_type++){
         Multisim_Sys_Hists[EventType::Types.at(i_type)][name].resize(universes);
         for(size_t i=0;i<universes;i++) 
            Multisim_Sys_Hists[EventType::Types.at(i_type)][name].at(i) = new TH1D(("h_" + EventType::Types.at(i_type) + "_" + name + "_u_" + std::to_string(i)).c_str(),fTitle.c_str(),fHistNBins,arr_boundaries);
      }
      for(size_t i_type=0;i_type<EventType::Types2.size();i_type++){
         if(std::find(EventType::Types.begin(),EventType::Types.end(),EventType::Types2.at(i_type)) != EventType::Types.end()) continue;
         Multisim_Sys_Hists[EventType::Types2.at(i_type)][name].resize(universes);
         for(size_t i=0;i<universes;i++) 
            Multisim_Sys_Hists[EventType::Types2.at(i_type)][name].at(i) = new TH1D(("h_" + EventType::Types2.at(i_type) + "_" + name + "_u_" + std::to_string(i)).c_str(),fTitle.c_str(),fHistNBins,arr_boundaries);
      }
      Multisim_Sys_Hists_All[name].resize(universes);
      for(size_t i=0;i<universes;i++) 
         Multisim_Sys_Hists_All[name].at(i) = new TH1D(("h_All_" + name + "_u_" + std::to_string(i)).c_str(),fTitle.c_str(),fHistNBins,arr_boundaries);
   }
   else if(systype == kSingleUnisim){
      for(size_t i_type=0;i_type<EventType::Types.size();i_type++){
         SingleUnisim_Sys_Hists[EventType::Types.at(i_type)][name].resize(1);
         for(size_t i=0;i<1;i++)
            SingleUnisim_Sys_Hists[EventType::Types.at(i_type)][name][i] = new TH1D(("h_" + EventType::Types.at(i_type) + "_" + name + "_u_" + std::to_string(i)).c_str(),fTitle.c_str(),fHistNBins,arr_boundaries);
      }
      for(size_t i_type=0;i_type<EventType::Types2.size();i_type++){
         if(std::find(EventType::Types.begin(),EventType::Types.end(),EventType::Types2.at(i_type)) != EventType::Types.end()) continue;
         SingleUnisim_Sys_Hists[EventType::Types2.at(i_type)][name].resize(1);
         for(size_t i=0;i<1;i++)
            SingleUnisim_Sys_Hists[EventType::Types2.at(i_type)][name][i] = new TH1D(("h_" + EventType::Types2.at(i_type) + "_" + name + "_u_" + std::to_string(i)).c_str(),fTitle.c_str(),fHistNBins,arr_boundaries);
      }
      SingleUnisim_Sys_Hists_All[name].resize(1);
      for(size_t i=0;i<1;i++) 
         SingleUnisim_Sys_Hists_All[name].at(i) = new TH1D(("h_All_" + name + "_u_" + std::to_string(i)).c_str(),fTitle.c_str(),fHistNBins,arr_boundaries);
   }
   else if(systype == kDualUnisim){
      for(size_t i_type=0;i_type<EventType::Types.size();i_type++){
         DualUnisim_Sys_Hists[EventType::Types.at(i_type)][name].resize(2);
         for(size_t i=0;i<2;i++) 
            DualUnisim_Sys_Hists[EventType::Types.at(i_type)][name].at(i) = new TH1D(("h_" + EventType::Types.at(i_type) + "_" + name + "_u_" + std::to_string(i)).c_str(),fTitle.c_str(),fHistNBins,arr_boundaries);
      }
      for(size_t i_type=0;i_type<EventType::Types2.size();i_type++){
         if(std::find(EventType::Types.begin(),EventType::Types.end(),EventType::Types2.at(i_type)) != EventType::Types.end()) continue;
         DualUnisim_Sys_Hists[EventType::Types2.at(i_type)][name].resize(2);
         for(size_t i=0;i<2;i++) 
            DualUnisim_Sys_Hists[EventType::Types2.at(i_type)][name].at(i) = new TH1D(("h_" + EventType::Types2.at(i_type) + "_" + name + "_u_" + std::to_string(i)).c_str(),fTitle.c_str(),fHistNBins,arr_boundaries);
      }
      DualUnisim_Sys_Hists_All[name].resize(2);
      for(size_t i=0;i<2;i++) 
         DualUnisim_Sys_Hists_All[name].at(i) = new TH1D(("h_All_" + name + "_u_" + std::to_string(i)).c_str(),fTitle.c_str(),fHistNBins,arr_boundaries);
   }
}

///////////////////////////////////////////////////////////////////////////////////////////////
/*
// Get the event category 

std::string SelectionManager::GetType(Event e){

std::string mode;
if(thisSampleType == "Data") mode = "Data";
else if(thisSampleType == "EXT") mode = "EXT";
else if(thisSampleType == "Dirt") mode = "Dirt";
else if(e.EventIsSignal) mode = "Signal";
else if(e.Mode.at(0) == "HYP") mode = "OtherHYP";
else mode = "OtherNu";

return mode;
}

///////////////////////////////////////////////////////////////////////////////////////////////

// Get the event category using different labelling convention

std::string SelectionManager::GetType2(Event e){

std::string mode;

if(thisSampleType == "Data") return "Data";
else if(thisSampleType == "EXT") return "EXT";
else if (thisSampleType == "Dirt") return "Dirt";

bool islambdacharged =  std::find(e.IsLambdaCharged.begin(),e.IsLambdaCharged.end(), true) != e.IsLambdaCharged.end();
//bool ishyperon = e.Hyperon.size(); 

if(e.EventIsSignal) return "DirectLambda";
else if(e.Mode.at(0) == "HYP") return "DirectHYP"; 
else if(e.Mode.at(0) == "RES" && islambdacharged) return "RESLambda";
else if(e.Mode.at(0) == "RES" && e.Hyperon.size()) return "RESHYP"; 
else if(e.Mode.at(0) == "DIS" && islambdacharged) return "DISLambda";
else if(e.Mode.at(0) == "DIS" && e.Hyperon.size()) return "DISHYP"; 
else if(e.EventHasNeutronScatter) return "Neutron";
else return "Other";

return mode;
}
*/
///////////////////////////////////////////////////////////////////////////////////////////////

// Fill the histograms

void SelectionManager::FillHistograms(const Event &e,double variable,double weight){

   std::string mode,mode2,proc;

   mode = EventType::GetType(e);
   mode2 = EventType::GetType2(e);
   proc = EventType::GetProc(e);

   if(mode != "Data"){
      Hist_All->Fill(variable,weight*e.Weight);
      Hists_ByType[mode]->Fill(variable,weight*e.Weight);
      Hists_ByType2[mode2]->Fill(variable,weight*e.Weight);
      Hists_ByProc[proc]->Fill(1,1);
   }
   else Hist_Data->Fill(variable,weight*e.Weight);
}

///////////////////////////////////////////////////////////////////////////////////////////////                                                                                                                 
// Fill the histograms for EtP calculation

void SelectionManager::FillHistogramsEtoP(const Event &e,double variable,RecoParticle PrimaryKaonTrackParticle, RecoParticle DaughterTrackParticle,double weight){

  std::string mode = EventType::GetType(e);
  if(mode == "Data") return;

  //RecoParticle DaughterTrackParticle = GetDaughterTrackParticle();
  //RecoParticle PrimaryKaonTrackParticle = GetPrimaryKaonTrackParticle();
      
  Hist_BDT_All->Fill(variable,weight*e.Weight);
  
  if(e.GoodReco && PrimaryKaonTrackParticle.Index == e.TrueKaonIndex && ( DaughterTrackParticle.Index == e.TrueDecayMuonIndex ||  DaughterTrackParticle.Index == e.TrueDecayPionIndex ))
    Hist_BDT_Signal->Fill(variable,weight*e.Weight);


  FillEtoPCurve();
  PlotEtoPCurve();
  /*
    Hist_Efficiency_Left->Fill(variable,weight*e.Weight);
    Hist_Purity_Left->Fill(variable,weight*e.Weight);
    Hist_EtoP_Left->Fill(variable,weight*e.Weight);
    Hist_Efficiency_Right->Fill(variable,weight*e.Weight);
    Hist_Purity_Right->Fill(variable,weight*e.Weight);
    Hist_EtoP_Right->Fill(variable,weight*e.Weight);
  */
  
}

///////////////////////////////////////////////////////////////////////////////////////////////

void SelectionManager::FillEtoPCurve(){

  int nbin = Hist_BDT_All->GetNbinsX();
  double denominator = Hist_BDT_All->Integral(1,nbin+1);
  for (int bin=1; bin<=nbin+1; bin++) {
    double signal = Hist_BDT_Signal->Integral(bin,nbin+1);
    double all = Hist_BDT_All->Integral(bin,nbin+1);
    double efficiency = denominator>0 ? signal/denominator : 0;
    double purity = all>0 ? signal/all : 0;
    Hist_Efficiency->SetBinContent(bin,efficiency);
    Hist_Purity->SetBinContent(bin,purity);
    Hist_EtoP->SetBinContent(bin, efficiency*purity);
  }

  int binmax = Hist_EtoP->GetMaximumBin();
  std::cout << "Cut at " << Hist_EtoP->GetXaxis()->GetBinCenter(binmax) << " gives " << std::endl;
  std::cout << "Efficiency of " << Hist_Efficiency->GetBinContent(binmax) << std::endl;
  std::cout << "Purity of " << Hist_Purity->GetBinContent(binmax) << std::endl;
  std::cout << "E*P of " << Hist_EtoP->GetBinContent(binmax) << std::endl;

}

///////////////////////////////////////////////////////////////////////////////////////////////                                                                                                                 
void SelectionManager::PlotEtoPCurve(){

  TString output_pdf_bdtcut = "BDT_opt_cut.pdf";

  TCanvas * c = new TCanvas();
  c->SetFillStyle(4000);

  Hist_Efficiency->SetMinimum(0);
  Hist_Efficiency->SetMaximum(1);
  Hist_Efficiency->Draw("C");
  Hist_Purity->Draw("C,SAME");
  Hist_EtoP->Draw("C,SAME");

  TLegend * legend = new TLegend(0.65,0.7,0.85,0.85);
  legend->AddEntry(Hist_Efficiency,"Efficiency","l");
  legend->AddEntry(Hist_Purity,"Purity","l");
  legend->AddEntry(Hist_EtoP,"Eff. #times Pur.","l");
  legend->Draw();
  c->Print(output_pdf_bdtcut);

}

///////////////////////////////////////////////////////////////////////////////////////////////

// Fill the 2D histograms

void SelectionManager::Fill2DHistograms(const Event &e,double variable_x,double variable_y,RecoParticle PrimaryKaonTrackParticle, RecoParticle DaughterTrackParticle,double weight){

  std::string mode, sigbg;

  //RecoParticle PrimaryKaonTrackParticle = GetPrimaryKaonTrackParticle();
  //RecoParticle DaughterTrackParticle = GetDaughterTrackParticle();
  
  mode = EventType::GetType(e);
  //sigbg = EventType::GetSigBG(e);
  sigbg = EventType::GetSigBG(PrimaryKaonTrackParticle, DaughterTrackParticle);
  if(mode == "Data") return;
  Hists2D_BySigBG[sigbg]->Fill(variable_x,variable_y,weight*e.Weight);

}

///////////////////////////////////////////////////////////////////////////////////////////////

// Fill the histograms wrt true match PDG

void SelectionManager::FillHistogramsPDG(const Event &e,double variable,RecoParticle PrimaryKaonTrackParticle, RecoParticle DaughterTrackParticle,double weight){

   std::string mode, primarypdg, daughterpdg;
	
   //RecoParticle PrimaryKaonTrackParticle = GetPrimaryKaonTrackParticle();
   //RecoParticle DaughterTrackParticle = GetDaughterTrackParticle();
   
   mode = EventType::GetType(e);
   primarypdg = EventType::GetPDG(PrimaryKaonTrackParticle);
   daughterpdg = EventType::GetPDG(DaughterTrackParticle);
   
   if(mode == "Data") return;
   Hist_All->Fill(variable,weight*e.Weight);
   Hists_ByPrimaryPDG[primarypdg]->Fill(variable,weight*e.Weight);
   Hists_ByDaughterPDG[daughterpdg]->Fill(variable,weight*e.Weight);

}

///////////////////////////////////////////////////////////////////////////////////////////////

// Fill systematics histogram for a single universe with a single weight

void SelectionManager::FillHistogramsSys(const Event &e,double variable,std::string name,int universe,double weight){

   if(e.Mode.at(0) == "Data") return;

   if(std::isnan(e.Weight) || std::isnan(weight) || std::isinf(e.Weight) || std::isinf(weight)){
      //std::cout << "Nan weight detected for dial " << name << "  event " << e.run << " " << e.subrun << " " << e.event << " skipping" << std::endl;
      return;
   }

   std::string mode = EventType::GetType(e);
   std::string mode2 = EventType::GetType2(e);
   bool fill2 = std::find(EventType::Types.begin(),EventType::Types.end(),mode2) == EventType::Types.end();

   if (Multisim_Sys_Hists[mode].find(name) != Multisim_Sys_Hists[mode].end()){
      Multisim_Sys_Hists[mode][name].at(universe)->Fill(variable,weight*e.Weight);
      if(fill2) Multisim_Sys_Hists[mode2][name].at(universe)->Fill(variable,weight*e.Weight);
      Multisim_Sys_Hists_All[name].at(universe)->Fill(variable,weight*e.Weight);
      return;
   }
   else if (SingleUnisim_Sys_Hists[mode].find(name) != SingleUnisim_Sys_Hists[mode].end()){
      SingleUnisim_Sys_Hists[mode][name].at(universe)->Fill(variable,weight*e.Weight);
      if(fill2) SingleUnisim_Sys_Hists[mode2][name].at(universe)->Fill(variable,weight*e.Weight);
      SingleUnisim_Sys_Hists_All[name].at(universe)->Fill(variable,weight*e.Weight);
      return;
   }
   else if (DualUnisim_Sys_Hists[mode].find(name) != DualUnisim_Sys_Hists[mode].end()){
      DualUnisim_Sys_Hists[mode][name].at(universe)->Fill(variable,weight*e.Weight);
      if(fill2) DualUnisim_Sys_Hists[mode2][name].at(universe)->Fill(variable,weight*e.Weight);
      DualUnisim_Sys_Hists_All[name].at(universe)->Fill(variable,weight*e.Weight);
      return;
   }

}

///////////////////////////////////////////////////////////////////////////////////////////////

// Fill systematics histogram for all universes. Supply vector containing weights for different
// universes

void SelectionManager::FillHistogramsSys(const Event &e,double variable,std::string name,std::vector<double> weights){

   for(size_t i=0;i<weights.size();i++)
      FillHistogramsSys(e,variable,name,i,weights.at(i)); 

}

///////////////////////////////////////////////////////////////////////////////////////////////

// Draw the histograms

void SelectionManager::DrawHistograms(std::string label,double Scale,double SignalScale){

   OpenHistFile(label);

   system(("mkdir -p " + PlotDir).c_str());

   // Create weight sums
   for(size_t i_proc=0;i_proc<EventType::Procs.size();i_proc++){
      Hists_ByProc[EventType::Procs.at(i_proc)]->Scale(Scale);
      Hists_ByProc[EventType::Procs.at(i_proc)]->Sumw2();
   }
   for(size_t i_type=0;i_type<EventType::Types.size();i_type++){
      Hists_ByType[EventType::Types.at(i_type)]->Scale(Scale);
      Hists_ByType[EventType::Types.at(i_type)]->Sumw2();
   }
   for(size_t i_type=0;i_type<EventType::Types2.size();i_type++){
      Hists_ByType2[EventType::Types2.at(i_type)]->Scale(Scale);
      Hists_ByType2[EventType::Types2.at(i_type)]->Sumw2();
   }

   Hist_All->Sumw2();   

   Hists_ByProc["Signal"]->Scale(SignalScale);
   Hists_ByType["Signal"]->Scale(SignalScale);
   Hists_ByType2["CCKP"]->Scale(SignalScale);

   TH1D* h_errors = (TH1D*)Hist_All->Clone("h_errors");

   std::vector<TH1D*> Hists_ByType_v;
   std::vector<TH1D*> Hists_ByType2_v;
   std::vector<TH1D*> Hists_ByProc_v;
   for(size_t i_t=0;i_t<EventType::Types.size();i_t++) 
      Hists_ByType_v.push_back(Hists_ByType[EventType::Types.at(i_t)]); 
   for(size_t i_t=0;i_t<EventType::Types2.size();i_t++) 
      Hists_ByType2_v.push_back(Hists_ByType2[EventType::Types2.at(i_t)]); 
   for(size_t i_t=0;i_t<EventType::Procs.size();i_t++) 
      Hists_ByProc_v.push_back(Hists_ByProc[EventType::Procs.at(i_t)]); 

   HypPlot::DrawHistogram(Hists_ByType_v,h_errors,Hist_Data,EventType::Captions,PlotDir,label+"_ByType",{BeamMode},{Run},{POT},SignalScale,fHasData,EventType::Colors,BinLabels,std::make_pair(0,0));
   HypPlot::DrawHistogram(Hists_ByType2_v,h_errors,Hist_Data,EventType::Captions2,PlotDir,label+"_ByType2",{BeamMode},{Run},{POT},SignalScale,fHasData,EventType::Colors2,BinLabels,std::make_pair(0,0));
   HypPlot::DrawHistogram(Hists_ByProc_v,h_errors,Hist_Data,EventType::Captions3,PlotDir,label+"_ByProc",{BeamMode},{Run},{POT},SignalScale,fHasData,EventType::Colors3,BinLabels,std::make_pair(0,0));

   std::map<std::string,TH1D*>::iterator it;
   for (it = Hists_ByType.begin(); it != Hists_ByType.end(); it++)
      it->second->Write(it->first.c_str());
   for (it = Hists_ByType2.begin(); it != Hists_ByType2.end(); it++){
      if(/*it->first == "Data" || it->first == "All" || */it->first == "EXT" || it->first == "Dirt") continue;
      it->second->Write(it->first.c_str());
   }

   Hist_All->Write("All");
   Hist_Data->Write("Data");
   h_errors->Write("ErrorBand");
}

///////////////////////////////////////////////////////////////////////////////////////////////

// Draw the 2D histograms

void SelectionManager::Draw2DHistograms(std::string label,double Scale,double SignalScale){

   OpenHistFile(label);

   system(("mkdir -p " + PlotDir).c_str());

   //Hists2D_BySigBG["Signal"]->Scale(SignalScale);

   std::vector<TH2D*> Hists2D_BySigBG_v;

   for(size_t i_t=0;i_t<EventType::SigBG.size();i_t++){
      Hists2D_BySigBG_v.push_back(Hists2D_BySigBG[EventType::SigBG.at(i_t)]); 
      //std::cout << Hists2D_BySigBG[EventType::SigBG.at(i_t)]->GetEntries() << std::endl;
   }

   HypPlot::Draw2DHistogram(Hists2D_BySigBG_v,EventType::Captions,PlotDir,label+"_BySigBG",{BeamMode},{Run},{POT},SignalScale);
   
   std::map<std::string,TH2D*>::iterator it;
   for (it = Hists2D_BySigBG.begin(); it != Hists2D_BySigBG.end(); it++)
      it->second->Write(it->first.c_str());
	
}

///////////////////////////////////////////////////////////////////////////////////////////////

// Draw the histograms wrt truth match PDG

void SelectionManager::DrawHistogramsPDG(std::string label,double Scale,double SignalScale){

   OpenHistFile(label);

   system(("mkdir -p " + PlotDir).c_str());

   // Create weight sums
   for(size_t i_pdg=0;i_pdg<EventType::PDGs.size();i_pdg++){
      Hists_ByPrimaryPDG[EventType::PDGs.at(i_pdg)]->Scale(Scale);
      Hists_ByDaughterPDG[EventType::PDGs.at(i_pdg)]->Sumw2();
   }
   
   Hist_All->Sumw2(); 
   TH1D* h_errors = (TH1D*)Hist_All->Clone("h_errors");	
   
   Hists_ByPrimaryPDG["KaonP"]->Scale(SignalScale);
   Hists_ByDaughterPDG["MuonP"]->Scale(SignalScale);
   
   std::vector<TH1D*> Hists_ByPrimaryPDG_v;
   std::vector<TH1D*> Hists_ByDaughterPDG_v;
   
   for(size_t i_pdg=0;i_pdg<EventType::PDGs.size();i_pdg++) 
      Hists_ByPrimaryPDG_v.push_back(Hists_ByPrimaryPDG[EventType::PDGs.at(i_pdg)]); 

   for(size_t i_pdg=0;i_pdg<EventType::PDGs.size();i_pdg++) 
      Hists_ByDaughterPDG_v.push_back(Hists_ByDaughterPDG[EventType::PDGs.at(i_pdg)]); 

   HypPlot::DrawHistogramNoStack(Hists_ByPrimaryPDG_v,h_errors,Hist_Data,EventType::PDGs,PlotDir,label+"_ByPrimaryPDG",{BeamMode},{Run},{POT},SignalScale,fHasData,EventType::Colors3,BinLabels,std::make_pair(0,0));
   HypPlot::DrawHistogramNoStack(Hists_ByDaughterPDG_v,h_errors,Hist_Data,EventType::PDGs,PlotDir,label+"_ByDaugterPDG",{BeamMode},{Run},{POT},SignalScale,fHasData,EventType::Colors3,BinLabels,std::make_pair(0,0));
 
   std::map<std::string,TH1D*>::iterator it;
   for (it = Hists_ByPrimaryPDG.begin(); it != Hists_ByPrimaryPDG.end(); it++)
      it->second->Write(it->first.c_str());
   for (it = Hists_ByDaughterPDG.begin(); it != Hists_ByDaughterPDG.end(); it++)
      it->second->Write(it->first.c_str());
   

//Hist_All->Write("All");
   //Hist_Data->Write("Data");
   //h_errors->Write("ErrorBand");
}

///////////////////////////////////////////////////////////////////////////////////////////////

// Draw the systematics histograms

void SelectionManager::DrawHistogramsSys(std::string label,std::string name,std::string type){

   std::cout << "Drawing systematic histograms for dial " << name << " and event type " << type << std::endl;

   system(("mkdir -p " + PlotDir).c_str());
   system(("mkdir -p " + RootfileDir).c_str());

   // Select which histograms to draw
   int systype=-1;
   std::vector<TH1D*> ToDraw;

   if(type == "All"){
      if(Multisim_Sys_Hists_All.find(name) != Multisim_Sys_Hists_All.end()){
         ToDraw = Multisim_Sys_Hists_All[name];
         systype = kMultisim;
      }
      else if(SingleUnisim_Sys_Hists_All.find(name) != SingleUnisim_Sys_Hists_All.end()){
         ToDraw = SingleUnisim_Sys_Hists_All[name];
         systype = kSingleUnisim;
      }
      else if(DualUnisim_Sys_Hists_All.find(name) != DualUnisim_Sys_Hists_All.end()){
         ToDraw = DualUnisim_Sys_Hists_All[name];
         systype = kDualUnisim;
      }
   }
   else if (Multisim_Sys_Hists[type].find(name) != Multisim_Sys_Hists[type].end()){
      ToDraw = Multisim_Sys_Hists[type][name]; 
      systype = kMultisim;
   }
   else if (SingleUnisim_Sys_Hists[type].find(name) != SingleUnisim_Sys_Hists[type].end()){
      ToDraw = SingleUnisim_Sys_Hists[type][name];
      systype = kSingleUnisim;
   }
   else if (DualUnisim_Sys_Hists[type].find(name) != DualUnisim_Sys_Hists[type].end()){
      ToDraw = DualUnisim_Sys_Hists[type][name];
      systype = kDualUnisim;
   }

   if(!ToDraw.size()){
      std::cout << "Can't find systematic name=" << name << " type=" << type << std::endl;
      return;
   }

   TH1D* h_CV = nullptr;
   if(type == "All") h_CV = Hist_All;
   else if(std::find(EventType::Types.begin(),EventType::Types.end(),type) != EventType::Types.end()) h_CV = Hists_ByType[type];
   else if(std::find(EventType::Types2.begin(),EventType::Types2.end(),type) != EventType::Types2.end()) h_CV = Hists_ByType2[type];   
   else throw std::invalid_argument("Trying to draw systematics histograms for unknown event type " + type + ", exiting");  

   HypPlot::DrawHistogramSys(ToDraw,h_CV,PlotDir,label,type,name,{BeamMode},{Run},{POT},BinLabels);

   // Write everything to file
   if(!f_Hists->GetDirectory(name.c_str()))
      f_Hists->mkdir(name.c_str()); 
   f_Hists->GetDirectory(name.c_str())->cd();
   for(size_t i=0;i<ToDraw.size();i++){
      ToDraw.at(i)->SetDirectory(new TDirectory(name.c_str(),name.c_str()));      
      ToDraw.at(i)->Write();
   }
   f_Hists->cd();

}

///////////////////////////////////////////////////////////////////////////////////////////////

// Get the covariace matrix for systematic dial

TMatrixD SelectionManager::GetCovarianceMatrix(std::string label,std::string name,std::string type){

   system(("mkdir -p " + PlotDir).c_str());

   int systype=-1;

   std::cout << "Getting Covariance Matrix for " << name << std::endl;

   OpenHistFile(label);

   std::vector<TH1D*> ToUse;

   if(type == "All"){
      if(Multisim_Sys_Hists_All.find(name) != Multisim_Sys_Hists_All.end()){
         ToUse = Multisim_Sys_Hists_All[name];
         systype = kMultisim;
      }
      else if(SingleUnisim_Sys_Hists_All.find(name) != SingleUnisim_Sys_Hists_All.end()){
         ToUse = SingleUnisim_Sys_Hists_All[name];
         systype = kSingleUnisim;
      }
      else if(DualUnisim_Sys_Hists_All.find(name) != DualUnisim_Sys_Hists_All.end()){
         ToUse = DualUnisim_Sys_Hists_All[name];
         systype = kDualUnisim;
      }
   }
   else if(Multisim_Sys_Hists[type].find(name) != Multisim_Sys_Hists[type].end()){
      ToUse = Multisim_Sys_Hists[type][name];
      systype = kMultisim;
   }
   else if(SingleUnisim_Sys_Hists[type].find(name) != SingleUnisim_Sys_Hists[type].end()){
      ToUse = SingleUnisim_Sys_Hists[type][name];
      systype = kSingleUnisim;
   }
   else if(DualUnisim_Sys_Hists[type].find(name) != DualUnisim_Sys_Hists[type].end()){
      ToUse = DualUnisim_Sys_Hists[type][name];
      systype = kDualUnisim;
   }

   TH1D* h_CV = nullptr;
   if(type == "All") h_CV = Hist_All;
   else if(std::find(EventType::Types.begin(),EventType::Types.end(),type) != EventType::Types.end()) h_CV = Hists_ByType[type];
   else if(std::find(EventType::Types2.begin(),EventType::Types2.end(),type) != EventType::Types2.end()) h_CV = Hists_ByType2[type];   
   else throw std::invalid_argument("Trying to calculate covariance matrix for unknown event type " + type + ", exiting");  

   const int arr_n = fHistBoundaries.size();
   Double_t arr_boundaries[arr_n];
   for(size_t i=0;i<arr_n;i++) arr_boundaries[i] = fHistBoundaries.at(i);

   std::string title = ";" + std::string(Hist_All->GetXaxis()->GetTitle()) + ";" + std::string(Hist_All->GetXaxis()->GetTitle());

   TMatrixD Cov(fHistNBins,fHistNBins);
   TH2D *h_Cov = new TH2D("h_Cov",title.c_str(),fHistNBins,arr_boundaries,fHistNBins,arr_boundaries);

   TMatrixD frac_Cov(fHistNBins,fHistNBins);
   TH2D *h_frac_Cov = new TH2D("h_frac_Cov",title.c_str(),fHistNBins,arr_boundaries,fHistNBins,arr_boundaries);

   if(BinLabels.size()){
      for(int i=1;i<fHistNBins+1;i++){
         h_Cov->GetXaxis()->SetBinLabel(i,BinLabels.at(i-1).c_str());
         h_Cov->GetYaxis()->SetBinLabel(i,BinLabels.at(i-1).c_str());
         h_frac_Cov->GetXaxis()->SetBinLabel(i,BinLabels.at(i-1).c_str());
         h_frac_Cov->GetYaxis()->SetBinLabel(i,BinLabels.at(i-1).c_str());
      }

      h_Cov->GetXaxis()->SetLabelSize(0.07);
      h_Cov->GetYaxis()->SetLabelSize(0.07);
      h_frac_Cov->GetXaxis()->SetLabelSize(0.07);
      h_frac_Cov->GetYaxis()->SetLabelSize(0.07);
   }

   for(int i_b=1;i_b<fHistNBins+1;i_b++){
      for(int j_b=1;j_b<fHistNBins+1;j_b++){

         if(!(h_CV->GetBinContent(i_b) > 0 && h_CV->GetBinContent(j_b) > 0)) continue;

         Cov[i_b-1][j_b-1] = 0.0;        
         frac_Cov[i_b-1][j_b-1] = 0.0; 

         double Cov_ij = 0.0;
         double Mean_i = 0.0;
         double Mean_j = 0.0;

         if(systype == kMultisim){
            for(size_t i_u=0;i_u<ToUse.size();i_u++) Mean_i += ToUse.at(i_u)->GetBinContent(i_b)/ToUse.size();
            for(size_t i_u=0;i_u<ToUse.size();i_u++) Mean_j += ToUse.at(i_u)->GetBinContent(j_b)/ToUse.size();
            for(size_t i_u=0;i_u<ToUse.size();i_u++) Cov_ij += (ToUse.at(i_u)->GetBinContent(i_b) - Mean_i)*(ToUse.at(i_u)->GetBinContent(j_b) - Mean_j)/(ToUse.size()-1);
         }
         if(systype == kSingleUnisim){
            Mean_i = h_CV->GetBinContent(i_b);
            Mean_j = h_CV->GetBinContent(j_b);
            Cov_ij = (ToUse.at(0)->GetBinContent(i_b) - Mean_i)*(ToUse.at(0)->GetBinContent(j_b) - Mean_j);
         } 
         if(systype == kDualUnisim){
            Mean_i = h_CV->GetBinContent(i_b);
            Mean_j = h_CV->GetBinContent(j_b);
            Cov_ij = (ToUse.at(1)->GetBinContent(i_b) - ToUse.at(0)->GetBinContent(i_b))*(ToUse.at(1)->GetBinContent(j_b) - ToUse.at(0)->GetBinContent(j_b))/4;
         } 
         frac_Cov[i_b-1][j_b-1] = Cov_ij/Mean_i/Mean_j; 
         Cov[i_b-1][j_b-1] = Cov_ij;
         h_Cov->SetBinContent(i_b,j_b,Cov_ij);
         h_frac_Cov->SetBinContent(i_b,j_b,Cov_ij/Mean_i/Mean_j);
      }
   }

   std::string plottitle = label + "_CovMatrix_Sys_" + type + "_" + name;
   HypPlot::DrawMatrix(h_Cov,h_Cov,plottitle,PlotDir,BinLabels.size(),fUseText);

   plottitle = label + "_FCovMatrix_Sys_" + type + "_" + name;
   HypPlot::DrawMatrix(h_frac_Cov,h_frac_Cov,plottitle,PlotDir,BinLabels.size(),fUseText);

   h_Cov->Write(("Cov_" + type + "_" + name).c_str());
   h_frac_Cov->Write(("FCov_" + type + "_" + name).c_str());

   return Cov;
}

///////////////////////////////////////////////////////////////////////////////////////////////

// Get the predicted number of events in a bin for a given event category

double SelectionManager::GetPrediction(int bin,std::string type){

   if(type=="" || type == "All") return Hist_All->GetBinContent(bin);
   else if(type == "Data") return Hist_Data->GetBinContent(bin);
   else if(Hists_ByType.find(type) != Hists_ByType.end()) return Hists_ByType[type]->GetBinContent(bin);
   else if(Hists_ByProc.find(type) != Hists_ByProc.end()) return Hists_ByProc[type]->GetBinContent(bin);

   std::cout << "Type/Proc " << type << " not found, returning -1" << std::endl;
   return -1;
}

///////////////////////////////////////////////////////////////////////////////////////////////

      RecoParticle * SelectionManager::GetDaughterTrackParticle(){
	return DaughterTrackParticle_;
      }

///////////////////////////////////////////////////////////////////////////////////////////////

      RecoParticle * SelectionManager::SetDaughterTrackParticle(RecoParticle * DaughterTrackParticle){
	DaughterTrackParticle_ = DaughterTrackParticle;
	return DaughterTrackParticle_;
      }

///////////////////////////////////////////////////////////////////////////////////////////////

      RecoParticle * SelectionManager::GetPrimaryKaonTrackParticle(){
	return PrimaryKaonTrackParticle_;
      }

///////////////////////////////////////////////////////////////////////////////////////////////

      RecoParticle * SelectionManager::SetPrimaryKaonTrackParticle(RecoParticle * PrimaryKaonTrackParticle){
	PrimaryKaonTrackParticle_ = PrimaryKaonTrackParticle;
	return PrimaryKaonTrackParticle_;
      }

///////////////////////////////////////////////////////////////////////////////////////////////
      RecoParticle * SelectionManager::GetCCMuTrackParticle(){
	return CCMuTrackParticle_;
      }

///////////////////////////////////////////////////////////////////////////////////////////////

      RecoParticle * SelectionManager::SetCCMuTrackParticle(RecoParticle * CCMuTrackParticle){
	CCMuTrackParticle_ = CCMuTrackParticle;
	return CCMuTrackParticle_;
      }

///////////////////////////////////////////////////////////////////////////////////////////////

TH1D* SelectionManager::GetHist_All(){
  return Hist_All;
}

///////////////////////////////////////////////////////////////////////////////////////////////

// Reopen the file containing the histograms

void SelectionManager::OpenHistFile(std::string label){

   if(f_Hists == nullptr){
      system(("mkdir -p " +  RootfileDir).c_str());
      f_Hists = TFile::Open((RootfileDir + label + "_Histograms.root").c_str(),"RECREATE");
   }
}

///////////////////////////////////////////////////////////////////////////////////////////////

// Set the labels on the bins

void SelectionManager::SetBinLabels(std::vector<std::string> binlabels){

   if(binlabels.size() != fHistNBins) 
      throw std::invalid_argument("Set of bin labels does not match number of bins!"); 

   BinLabels = binlabels;
}

///////////////////////////////////////////////////////////////////////////////////////////////

// Divide bins by bin widths

void SelectionManager::WidthScaleHistograms(){

   std::map<std::string,TH1D*>::iterator it1;

   for (it1=Hists_ByType.begin();it1!=Hists_ByType.end();it1++){
      for(size_t i_b=1;i_b<it1->second->GetNbinsX()+1;i_b++){        
         it1->second->SetBinContent(i_b,it1->second->GetBinContent(i_b)/it1->second->GetBinWidth(i_b));
         it1->second->SetBinError(i_b,it1->second->GetBinError(i_b)/it1->second->GetBinWidth(i_b));
      }
   }

   for (it1=Hists_ByType2.begin();it1!=Hists_ByType2.end();it1++){
      for(size_t i_b=1;i_b<it1->second->GetNbinsX()+1;i_b++){        
         it1->second->SetBinContent(i_b,it1->second->GetBinContent(i_b)/it1->second->GetBinWidth(i_b));
         it1->second->SetBinError(i_b,it1->second->GetBinError(i_b)/it1->second->GetBinWidth(i_b));
      }
   }

   for (it1=Hists_ByProc.begin();it1!=Hists_ByProc.end();it1++){
      for(size_t i_b=1;i_b<it1->second->GetNbinsX()+1;i_b++){
         it1->second->SetBinContent(i_b,it1->second->GetBinContent(i_b)/it1->second->GetBinWidth(i_b));
         it1->second->SetBinError(i_b,it1->second->GetBinError(i_b)/it1->second->GetBinWidth(i_b));
      }
   }

   std::map<std::string,std::map<std::string,std::vector<TH1D*>>>::iterator it2;

   for (it2=Multisim_Sys_Hists.begin();it2!=Multisim_Sys_Hists.end();it2++){
      std::map<std::string,std::vector<TH1D*>>::iterator it22;
      for (it22=it2->second.begin();it22!=it2->second.end();it22++){
         for(size_t i=0;i<it22->second.size();i++){
            for(size_t i_b=1;i_b<it22->second.at(i)->GetNbinsX()+1;i_b++){        
               it22->second.at(i)->SetBinContent(i_b,it22->second.at(i)->GetBinContent(i_b)/it22->second.at(i)->GetBinWidth(i_b));
               it22->second.at(i)->SetBinError(i_b,it22->second.at(i)->GetBinError(i_b)/it22->second.at(i)->GetBinWidth(i_b));
            }
         }
      }
   }

   for (it2=SingleUnisim_Sys_Hists.begin();it2!=SingleUnisim_Sys_Hists.end();it2++){
      std::map<std::string,std::vector<TH1D*>>::iterator it22;
      for (it22=it2->second.begin();it22!=it2->second.end();it22++){
         for(size_t i=0;i<it22->second.size();i++){
            for(size_t i_b=1;i_b<it22->second.at(i)->GetNbinsX()+1;i_b++){        
               it22->second.at(i)->SetBinContent(i_b,it22->second.at(i)->GetBinContent(i_b)/it22->second.at(i)->GetBinWidth(i_b));
               it22->second.at(i)->SetBinError(i_b,it22->second.at(i)->GetBinError(i_b)/it22->second.at(i)->GetBinWidth(i_b));
            }
         }
      }
   }

   for (it2=DualUnisim_Sys_Hists.begin();it2!=DualUnisim_Sys_Hists.end();it2++){
      std::map<std::string,std::vector<TH1D*>>::iterator it22;
      for (it22=it2->second.begin();it22!=it2->second.end();it22++){
         for(size_t i=0;i<it22->second.size();i++){
            for(size_t i_b=1;i_b<it22->second.at(i)->GetNbinsX()+1;i_b++){        
               it22->second.at(i)->SetBinContent(i_b,it22->second.at(i)->GetBinContent(i_b)/it22->second.at(i)->GetBinWidth(i_b));
               it22->second.at(i)->SetBinError(i_b,it22->second.at(i)->GetBinError(i_b)/it22->second.at(i)->GetBinWidth(i_b));
            }
         }
      }
   }

   for(size_t i_b=1;i_b<Hist_Data->GetNbinsX()+1;i_b++) Hist_Data->SetBinContent(i_b,Hist_Data->GetBinContent(i_b)/Hist_Data->GetBinWidth(i_b));
   for(size_t i_b=1;i_b<Hist_All->GetNbinsX()+1;i_b++) Hist_All->SetBinContent(i_b,Hist_All->GetBinContent(i_b)/Hist_All->GetBinWidth(i_b));


}

///////////////////////////////////////////////////////////////////////////////////////////////

// Retrieve the vector containing bin boundaries

std::vector<double> SelectionManager::GetBinBoundaries(){
   return fHistBoundaries; 
}

///////////////////////////////////////////////////////////////////////////////////////////////

#endif

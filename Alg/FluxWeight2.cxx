#ifndef _FluxWeight_cxx_
#define _FluxWeight_cxx_

#include "FluxWeight2.h"

///////////////////////////////////////////////////////////////////////////////////////////////

FluxWeighter::FluxWeighter(int mode){

   FLUX_DIR = std::string(std::getenv("HYP_TOP")) + "Fluxes/";

   // Presently only have weights for run 1 and 3
   if(mode != kFHC && mode != kRHC && mode != kBNB)
      throw std::invalid_argument( "Requesting flux weights for unknown beam mode " + mode );      

   //fRunPeriod = RunPeriod;
   fMode = mode;

   if(mode == kBNB) return;

   /*
   if(fMode == kFHC){ fRunMode = "fhc"; fRunModeCaps = "FHC"; }
   else { fRunMode = "rhc"; fRunModeCaps = "RHC"; }

   if (fMode == kFHC)
      f_flux = TFile::Open((FLUX_DIR + "output_uboone_fhc_run0_merged.root").c_str(), "READ");
   else
      f_flux = TFile::Open((FLUX_DIR + "output_uboone_rhc_run0_merged.root").c_str(), "READ");               
   */

   std::string filePath;
   if(fMode == kFHC) {
     filePath = FLUX_DIR + "output_uboone_fhc_run0_merged.root";
     fRunMode = "fhc";
     fRunModeCaps = "FHC";
   } else {
     filePath = FLUX_DIR + "output_uboone_rhc_run0_merged.root";
     fRunMode = "rhc";
     fRunModeCaps = "RHC";
   }
   
   // Only proceed if the file exists, otherwise skip all operations involving the file
   if(!gSystem->AccessPathName(filePath.c_str())) {
     f_flux = TFile::Open(filePath.c_str(), "READ");
     if (f_flux && !f_flux->IsZombie()) {
       // Process histograms only if the file is opened successfully
       hist_ratio.resize(k_FLAV_MAX);
       hist_ratio_uw.resize(k_FLAV_MAX);
       hist_CV.resize(k_FLAV_MAX);

       // Get the flux histograms
       for (unsigned int f = 0; f < flav_str.size(); f++) {
	 hist_ratio.at(f) = dynamic_cast<TH2D*>(f_flux->Get(Form("%s/Detsmear/%s_CV_AV_TPC_2D", flav_str.at(f).c_str(), flav_str.at(f).c_str())));
	 hist_ratio_uw.at(f) = dynamic_cast<TH2D*>(f_flux->Get(Form("%s/Detsmear/%s_unweighted_AV_TPC_2D", flav_str.at(f).c_str(), flav_str.at(f).c_str())));
	 if (hist_ratio.at(f) && hist_ratio_uw.at(f)) {
	   hist_ratio.at(f)->SetDirectory(0);
	   hist_ratio_uw.at(f)->SetDirectory(0);
	   hist_ratio.at(f)->Divide(hist_ratio_uw.at(f));
	 }
       }
     } else {
       std::cerr << "Failed to open flux file or it is a zombie: " << filePath << std::endl;
     }
   } else {
     std::cerr << "Skipping operations as flux file does not exist: " << filePath << std::endl;
   }

   /*
   hist_ratio.resize(k_FLAV_MAX);
   hist_ratio_uw.resize(k_FLAV_MAX);
   hist_CV.resize(k_FLAV_MAX);

   // Get the flux histograms
   for (unsigned int f = 0; f < flav_str.size(); f++){
      hist_ratio.at(f)      = (TH2D*) f_flux->Get(Form("%s/Detsmear/%s_CV_AV_TPC_2D", flav_str.at(f).c_str(), flav_str.at(f).c_str()));
      hist_ratio_uw.at(f)   = (TH2D*) f_flux->Get(Form("%s/Detsmear/%s_unweighted_AV_TPC_2D", flav_str.at(f).c_str(), flav_str.at(f).c_str()));
      hist_CV.at(f) = *(TH2D*) f_flux->Get(Form("%s/Detsmear/%s_CV_AV_TPC_2D", flav_str.at(f).c_str(), flav_str.at(f).c_str()));      
      hist_ratio.at(f)->SetDirectory(0);
      hist_ratio_uw.at(f)->SetDirectory(0);

      // Take the ratio
      hist_ratio.at(f)->Divide(hist_ratio_uw.at(f));
   }
   */
   
}

///////////////////////////////////////////////////////////////////////////////////////////////

double FluxWeighter::GetFluxWeight(double nu_e,double nu_angle,int nu_pdg,std::string dial,int univ){

   if(fMode == kBNB) return 1.0;
 
   if(dial != "" && dial != "Flux_HP" && std::find(Beamline_Dials.begin(),Beamline_Dials.end(),dial) == Beamline_Dials.end())
      throw std::invalid_argument("Requesting flux weights for unknown systematic dial " + dial);      
  
   // If getting beamline weights
   std::pair<int,int> beamline_univ_p;
   int beamline_univ;
   if(dial != "" && dial != "Flux_HP"){
      beamline_univ_p = GetBeamlineUniv(dial);
      if(univ == 0) beamline_univ = beamline_univ_p.first;
      else if(univ == 1) beamline_univ = beamline_univ_p.second;
      else throw std::invalid_argument("Requesting flux universe other than 0 or 1 for beamline dial " + dial); 
   }    

   float weight = 1.0;

   double xbin{1.0},ybin{1.0};

   if (nu_pdg == 14) {
      xbin =  hist_ratio.at(k_numu)->GetXaxis()->FindBin(nu_e);
      ybin =  hist_ratio.at(k_numu)->GetYaxis()->FindBin(nu_angle);

      if(dial == "")  weight = hist_ratio.at(k_numu)->GetBinContent(xbin, ybin);
      else if(dial == "Flux_HP") weight = hist_sys_ratio.at(k_numu).at(univ)->GetBinContent(xbin, ybin);
      else weight = hist_beamline_vars_ratio.at(k_numu).at(beamline_univ)->GetBinContent(xbin, ybin);
   }
   if (nu_pdg == -14) {
      xbin =  hist_ratio.at(k_numubar)->GetXaxis()->FindBin(nu_e);
      ybin = hist_ratio.at(k_numubar)->GetYaxis()->FindBin(nu_angle);

      if(dial == "")  weight = hist_ratio.at(k_numubar)->GetBinContent(xbin, ybin);
      else if(dial == "Flux_HP") weight = hist_sys_ratio.at(k_numubar).at(univ)->GetBinContent(xbin, ybin);
      else weight = hist_beamline_vars_ratio.at(k_numubar).at(beamline_univ)->GetBinContent(xbin, ybin);
   }
   if (nu_pdg == 12) {
      xbin = hist_ratio.at(k_nue)->GetXaxis()->FindBin(nu_e);
      ybin = hist_ratio.at(k_nue)->GetYaxis()->FindBin(nu_angle);

      if(dial == "")  weight = hist_ratio.at(k_nue)->GetBinContent(xbin, ybin);
      else if(dial == "Flux_HP") weight = hist_sys_ratio.at(k_nue).at(univ)->GetBinContent(xbin, ybin);
      else weight = hist_beamline_vars_ratio.at(k_nue).at(beamline_univ)->GetBinContent(xbin, ybin);
   }
   if (nu_pdg == -12) {
      xbin = hist_ratio.at(k_nuebar)->GetXaxis()->FindBin(nu_e);
      ybin = hist_ratio.at(k_nuebar)->GetYaxis()->FindBin(nu_angle);

      if(dial == "")  weight = hist_ratio.at(k_nuebar)->GetBinContent(xbin, ybin);
      else if(dial == "Flux_HP") weight = hist_sys_ratio.at(k_nuebar).at(univ)->GetBinContent(xbin, ybin);
      else weight = hist_beamline_vars_ratio.at(k_nuebar).at(beamline_univ)->GetBinContent(xbin, ybin);
   }

   // Add some catches to remove unphysical weights
   if (std::isinf(weight)) weight = 1.0; 
   if (std::isnan(weight) == 1) weight = 1.0;
   if (weight > 100) weight = 1.0;

   return  weight;
}

//////////////////////////////////////////////////////////////////////////////////////////////

double FluxWeighter::GetFluxWeight(const Event &e){

   if(!e.Neutrino.size()) return 1.0;

   double weight = 1.0;

   // Get weight for each neutrino and multiply together
   for(size_t i_n=0;i_n<e.Neutrino.size();i_n++){
      double nu_e = e.Neutrino.at(i_n).E;
      double nu_angle = GetNuMIAngle(e.Neutrino.at(i_n).Px,e.Neutrino.at(i_n).Py,e.Neutrino.at(i_n).Pz);
      int nu_pdg = e.Neutrino.at(i_n).PDG;
      weight *= GetFluxWeight(nu_e,nu_angle,nu_pdg);
   }

   return weight;
}

//////////////////////////////////////////////////////////////////////////////////////////////

double FluxWeighter::GetFluxWeightCV(const Event &e){

  double weight = 1.0;
  weight *= e.PPFX_CV;

  return weight;

}

///////////////////////////////////////////////////////////////////////////////////////////////

FluxWeighter::~FluxWeighter(){

   if(f_flux != nullptr){
      f_flux->Close();
      delete f_flux;       
   }

   hist_ratio.clear();
   hist_ratio_uw.clear(); 
}

///////////////////////////////////////////////////////////////////////////////////////////////

void FluxWeighter::PrepareHPUniv(){

   std::cout << "Loading flux hadron production histograms" << std::endl;

   hist_sys_ratio.resize(flav_str.size());

   for (unsigned int f = 0; f < flav_str.size(); f++)
      hist_sys_ratio.at(f).resize(Flux_HP_Universes);

   for (unsigned int f = 0; f < flav_str.size(); f++){
      for(size_t i_univ=0;i_univ<Flux_HP_Universes;i_univ++){
         hist_sys_ratio.at(f).at(i_univ) = (TH2D*) f_flux->Get(Form("%s/Multisims/%s_ppfx_ms_UBPPFX_Uni_%s_AV_TPC_2D", flav_str.at(f).c_str(), flav_str.at(f).c_str(),std::to_string(i_univ).c_str()));
         hist_sys_ratio.at(f).at(i_univ)->Divide(hist_ratio_uw.at(f));
      }
   }
}

///////////////////////////////////////////////////////////////////////////////////////////////

void FluxWeighter::PrepareBeamlineUniv(){

   std::cout << "Loading flux beamline histograms" << std::endl;

   //f_beamline_vars.resize(Beamline_Universes);  
   f_beamline_vars = TFile::Open((FLUX_DIR + "NuMI_Beamline_Variations_to_CV_Ratios.root").c_str());
   hist_beamline_vars_ratio.resize(flav_str.size());

   for (unsigned int f = 0; f < flav_str.size(); f++){       
      hist_beamline_vars_ratio.at(f).resize(Beamline_Universes);  
      for(unsigned int bv=0;bv<Beamline_Universes;bv++){
         std::string histname = "EnergyTheta2D/ratio_run" + std::to_string(bv+1) + "_" + fRunModeCaps + "_" + flav_str.at(f) + "_CV_AV_TPC_2D"; 
         hist_beamline_vars_ratio.at(f).at(bv) = (TH2D*) f_beamline_vars->Get(histname.c_str());
      }
   }
}

///////////////////////////////////////////////////////////////////////////////////////////////

std::pair<int,int> FluxWeighter::GetBeamlineUniv(std::string dial){

   int i_dial = -1;
   for(size_t i=0;i<bMAX;i++)
      if(Beamline_Dials.at(i) == dial){
         i_dial = i;
         break;
      }

   if(i_dial == -1)
      throw std::invalid_argument("Unrecognised beamline dial " + dial);

   return {2*i_dial,2*i_dial+1};
}

///////////////////////////////////////////////////////////////////////////////////////////////

std::vector<double> FluxWeighter::GetSysWeightV(double nu_e,double nu_angle,int nu_pdg,std::string dial){

   std::vector<double> weights;
   if(dial == "Flux_HP") for(size_t i_univ=0;i_univ<Flux_HP_Universes;i_univ++) weights.push_back(GetFluxWeight(nu_e,nu_angle,nu_pdg,"Flux_HP",i_univ));
   else if(std::find(Beamline_Dials.begin(),Beamline_Dials.end(),dial) != Beamline_Dials.end()) 
      weights = {GetFluxWeight(nu_e,nu_angle,nu_pdg,dial,0),GetFluxWeight(nu_e,nu_angle,nu_pdg,dial,1)};  
   else throw std::invalid_argument("Requesting flux weights for unknown systematic dial " + dial);      
 
   return weights;
}

///////////////////////////////////////////////////////////////////////////////////////////////

std::vector<double> FluxWeighter::GetSysWeightV(const Event &e,std::string dial){

   std::vector<double> weights;
   if(dial == "Flux_HP") for(size_t i_univ=0;i_univ<Flux_HP_Universes;i_univ++) weights.push_back(1.0);
   else if(std::find(Beamline_Dials.begin(),Beamline_Dials.end(),dial) != Beamline_Dials.end()) weights = {1.0,1.0};
   else throw std::invalid_argument("Requesting flux weights for unknown systematic dial " + dial);      

   // If no neutrinos simulated, return vector of 1's
   if(!e.Neutrino.size()) return weights;
   
   for(size_t i_tr=0;i_tr<e.Neutrino.size();i_tr++){ 
      double nu_e = e.Neutrino.at(0).E;
      double nu_angle = GetNuMIAngle(e.Neutrino.at(0).Px,e.Neutrino.at(0).Py,e.Neutrino.at(0).Pz);
      int nu_pdg = e.Neutrino.at(0).PDG;
      std::vector<double> weights_thistruth = GetSysWeightV(nu_e,nu_angle,nu_pdg,dial);
      for(size_t i_w=0;i_w<weights.size();i_w++) weights.at(i_w) *= weights_thistruth.at(i_w); 
   }

   // If getting weights for hadron production, divide out the CV weight
   if(dial == "Flux_HP"){        
      double cv_weight = GetFluxWeight(e);
      for(size_t i_w=0;i_w<weights.size();i_w++) weights.at(i_w) /= cv_weight;
   }        
   
   return weights;
}

///////////////////////////////////////////////////////////////////////////////////////////////

#endif

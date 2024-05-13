#ifndef _FluxWeight2_h_
#define _FluxWeight2_h_

#include <iostream>
#include <map>

#include "TFile.h"
#include "TMatrixD.h"
#include "TH2D.h"
#include "TSystem.h"

#include "Event.h"
#include "Misc.h"

enum modes{kFHC,kRHC,kBNB};

const int Flux_HP_Universes = 600;
const int Beamline_Universes = 20;

const std::vector<std::string> Beamline_Dials = {"HC","H1X","H1Y","BSS","H2X","H2Y","HW","BSX","BSY","TPZ"};
const std::vector<std::string> Beamline_Captions = {"Horn Current","Horn 1 X","Horn 1 Y","Beam Spot Size","Horn 2 X","Horn 2 Y","Horn Water","Beam Spot X","Beam Spot Y","Target Pos. Z"};
enum Beamline_Dials_enum {bHC,bH1X,bH1Y,bBSS,bH2X,bH2Y,bHW,bBSX,bBSY,bTPZ,bPOT,bMAX};

///////////////////////////////////////////////////////////////////////////////////////

// Flux weight manager

class FluxWeighter {

   public:

      enum flav { k_numu, k_numubar, k_nue, k_nuebar, k_FLAV_MAX };
      std::vector<std::string> flav_str = {"numu","numubar","nue","nuebar"};       

      FluxWeighter(int mode);
      ~FluxWeighter();

      void PrepareHPUniv();
      void PrepareBeamlineUniv();

      // dial="" gives CV universe
      double GetFluxWeight(double nu_e,double nu_angle,int nu_pdg,std::string dial="",int univ=-1); 
      double GetFluxWeight(const Event &e);

      std::vector<double> GetSysWeightV(double nu_e,double nu_angle,int nu_pdg,std::string dial=""); 
      std::vector<double> GetSysWeightV(const Event &e,std::string dial);

   private:

      std::string FLUX_DIR;

      int fMode;
      std::string fRunMode;
      std::string fRunModeCaps;

      TFile *f_flux=nullptr;
      std::vector<TH2D*> hist_ratio;
      std::vector<TH2D*> hist_ratio_uw;       

      std::vector<TH2D> hist_CV;

      std::vector<std::vector<TH2D*>> hist_sys_ratio;

      TFile *f_beamline_vars; 
      std::vector<std::vector<TH2D*>> hist_beamline_vars_ratio;

      std::pair<int,int> GetBeamlineUniv(std::string dial);
};

///////////////////////////////////////////////////////////////////////////////////////

// Function to calculate the integrated flux in different universes

inline std::map<int,double> GetIntegratedFlux(int mode, int CV_HP_Beamline,double POT){

   assert(mode == kFHC || mode == kRHC);

   std::string BeamModeCaps = mode == kFHC ? "FHC" : "RHC";
   std::string BeamMode = mode == kFHC ? "fhc" : "rhc";

   // Get the flux histograms
   std::string FLUX_DIR = std::string(std::getenv("HYP_TOP")) + "Fluxes/";
   TFile *f_flux = TFile::Open((FLUX_DIR + "output_uboone_" + BeamMode + "_run0_merged.root").c_str());

   TH1D *h_numubar_flux;

   f_flux->GetObject("numubar/Detsmear/numubar_CV_AV_TPC",h_numubar_flux);

   for(int i=1;i<h_numubar_flux->GetNbinsX()+1;i++) h_numubar_flux->SetBinContent(i,h_numubar_flux->GetBinContent(i)/h_numubar_flux->GetBinWidth(i));

   h_numubar_flux->Scale(POT);

   std::map<int,double> univ_flux;

   if(CV_HP_Beamline == 0){
      univ_flux[0] =  h_numubar_flux->Integral("width")/100/100;
   }
   else if(CV_HP_Beamline == 1){
      // Calculate in HP universes
      std::vector<TH1D*> h_numubar_flux_HP(600);
      for(int i=0;i<600;i++){
         f_flux->GetObject(("numubar/Multisims/numubar_ppfx_ms_UBPPFX_Uni_" + std::to_string(i) + "_AV_TPC").c_str(),h_numubar_flux_HP[i]);
         for(int i_b=1;i_b<h_numubar_flux_HP[i]->GetNbinsX()+1;i_b++) h_numubar_flux_HP[i]->SetBinContent(i_b,h_numubar_flux_HP[i]->GetBinContent(i_b)/h_numubar_flux_HP[i]->GetBinWidth(i_b));
         h_numubar_flux_HP[i]->Scale(POT);
         univ_flux[i] = h_numubar_flux_HP[i]->Integral("width")/100/100;
      }
   }
   else {
      // Calculate in beamline geometry universes
      TFile *f_Beamline = TFile::Open((FLUX_DIR + "NuMI_Beamline_Variations_to_CV_Ratios.root").c_str());
      std::vector<TH1D*> h_numubar_flux_Beamline(Beamline_Universes);
      std::vector<TH1D*> h_numubar_ratio_Beamline(Beamline_Universes);       
      for(int i=0;i<Beamline_Universes;i++){
         f_Beamline->GetObject(("EnergyVarBin/ratio_run" + std::to_string(i+1) + "_" + BeamModeCaps + "_numubar_CV_AV_TPC").c_str(),h_numubar_ratio_Beamline[i]);           
         h_numubar_flux_Beamline[i] = (TH1D*)h_numubar_flux->Clone(("h_numubar_flux_Beamline_" + std::to_string(i)).c_str());
         for(int i_b=1;i_b<h_numubar_flux->GetNbinsX()+1;i_b++) h_numubar_flux_Beamline.at(i)->SetBinContent(i_b,h_numubar_flux->GetBinContent(i_b)*h_numubar_ratio_Beamline.at(i)->GetBinContent(i_b));
         univ_flux[i] = h_numubar_flux_Beamline[i]->Integral("width")/100/100;
      }  
   }
   return univ_flux;
}

///////////////////////////////////////////////////////////////////////////////////////

// Function to calculate the integrated flux in different universes

inline std::vector<double> GetIntegratedFlux2(int mode,double POT,std::string dial="CV"){

   assert(mode == kFHC || mode == kRHC);

   std::string BeamModeCaps = mode == kFHC ? "FHC" : "RHC";
   std::string BeamMode = mode == kFHC ? "fhc" : "rhc";

   // Get the flux histograms
   std::string FLUX_DIR = std::string(std::getenv("HYP_TOP")) + "Fluxes/";
   TFile *f_flux = TFile::Open((FLUX_DIR + "output_uboone_" + BeamMode + "_run0_merged.root").c_str());

   TH1D *h_numubar_flux;

   f_flux->GetObject("numubar/Detsmear/numubar_CV_AV_TPC",h_numubar_flux);

   for(int i=1;i<h_numubar_flux->GetNbinsX()+1;i++) h_numubar_flux->SetBinContent(i,h_numubar_flux->GetBinContent(i)/h_numubar_flux->GetBinWidth(i));

   h_numubar_flux->Scale(POT);

   std::vector<double> univ_flux;

   if(dial == "CV"){
      univ_flux.resize(1);
      univ_flux.at(0) = h_numubar_flux->Integral("width")/100/100;
   }
   else if(dial == "Flux_HP"){
      univ_flux.resize(Flux_HP_Universes);
      std::vector<TH1D*> h_numubar_flux_HP(Flux_HP_Universes);
      for(int i=0;i<Flux_HP_Universes;i++){
         f_flux->GetObject(("numubar/Multisims/numubar_ppfx_ms_UBPPFX_Uni_" + std::to_string(i) + "_AV_TPC").c_str(),h_numubar_flux_HP[i]);
         for(int i_b=1;i_b<h_numubar_flux_HP[i]->GetNbinsX()+1;i_b++) h_numubar_flux_HP[i]->SetBinContent(i_b,h_numubar_flux_HP[i]->GetBinContent(i_b)/h_numubar_flux_HP[i]->GetBinWidth(i_b));
         h_numubar_flux_HP[i]->Scale(POT);
         univ_flux[i] = h_numubar_flux_HP[i]->Integral("width")/100/100;
      }
   }
   else {

      TFile *f_Beamline = TFile::Open((FLUX_DIR + "NuMI_Beamline_Variations_to_CV_Ratios.root").c_str());
      std::vector<TH1D*> h_numubar_flux_Beamline(2,nullptr);
      std::vector<TH1D*> h_numubar_ratio_Beamline(2,nullptr);
      univ_flux.resize(2);

      int dial_pos = -1;
      for(size_t i_d=0;i_d<Beamline_Dials.size();i_d++)
         if(dial == Beamline_Dials.at(i_d))
            dial_pos = i_d;

      if(dial_pos == -1) throw std::invalid_argument("Trying to get integrated fluxes for unrecognised dial " + dial + " exiting");

      int univ_up = 2*dial_pos;
      int univ_down = 2*dial_pos + 1;

      f_Beamline->GetObject(("EnergyVarBin/ratio_run" + std::to_string(univ_up+1) + "_" + BeamModeCaps + "_numubar_CV_AV_TPC").c_str(),h_numubar_ratio_Beamline[0]);
      f_Beamline->GetObject(("EnergyVarBin/ratio_run" + std::to_string(univ_down+1) + "_" + BeamModeCaps + "_numubar_CV_AV_TPC").c_str(),h_numubar_ratio_Beamline[1]);      
 
      if(h_numubar_ratio_Beamline[0] == nullptr) std::cout << "EnergyVarBin/ratio_run" + std::to_string(univ_up+1) + "_" + BeamModeCaps + "_numubar_CV_AV_TPC" << " not found" << std::endl;
      if(h_numubar_ratio_Beamline[1] == nullptr) std::cout << "EnergyVarBin/ratio_run" + std::to_string(univ_down+1) + "_" + BeamModeCaps + "_numubar_CV_AV_TPC" << " not found" << std::endl;

      h_numubar_flux_Beamline[0] = (TH1D*)h_numubar_flux->Clone(("h_numubar_flux_Beamline_" + std::to_string(univ_up)).c_str());
      h_numubar_flux_Beamline[1] = (TH1D*)h_numubar_flux->Clone(("h_numubar_flux_Beamline_" + std::to_string(univ_down)).c_str());

      for(int i_b=1;i_b<h_numubar_flux->GetNbinsX()+1;i_b++){
         h_numubar_flux_Beamline.at(0)->SetBinContent(i_b,h_numubar_flux->GetBinContent(i_b)*h_numubar_ratio_Beamline.at(0)->GetBinContent(i_b));
         h_numubar_flux_Beamline.at(1)->SetBinContent(i_b,h_numubar_flux->GetBinContent(i_b)*h_numubar_ratio_Beamline.at(1)->GetBinContent(i_b));
      }
      univ_flux[0] = h_numubar_flux_Beamline[0]->Integral("width")/100/100;
      univ_flux[1] = h_numubar_flux_Beamline[1]->Integral("width")/100/100;
   }

   return univ_flux;
}

///////////////////////////////////////////////////////////////////////////////////////

#endif

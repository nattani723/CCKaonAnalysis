#ifndef _SelectionManager_h_
#define _SelectionManager_h_

#include "TFile.h"
#include "TTree.h"
#include "TLorentzVector.h"
#include "TVector3.h"
#include "TH1D.h"
#include "THStack.h"
#include "TCanvas.h"
#include "TMVA/Reader.h"
#include "TLegend.h"
#include "TPad.h"
#include "TGraph.h"
#include <TROOT.h>
#include <TStyle.h>
#include "TMatrix.h"

// Local includes
#include "FluxWeight2.h"
#include "GenG4WeightHandler2.h"
#include "FiducialVolume.h"
#include "Muon_ID.h"
#include "TrackLengthCutManager.h"
#include "SelectionParameters.h"
#include "Event.h"
#include "RecoParticle.h"
#include "SimParticle.h"
#include "Cut.h"
#include "Misc.h"
#include "SelectorBDTManager.h"
#include "AnalysisBDTManager.h"
#include "BDTManager.h"
#include "PlottingFunctions.h"
#include "EventListFilter.h"
#include "SystematicsHeader.h"
#include "EventType.h"

enum Generators {kGENIE,kNuWro};

class SelectionManager {

   // General variables/functions //

   public:

      // Constructors/Destructors
      SelectionManager();
      ~SelectionManager();
      SelectionManager(SelectionParameters p);

      void Close();

      // Start processing a sample
      void AddSample(std::string Name,std::string Type,double SamplePOT,std::string EventList="");

      // Increment metadata
      void AddEvent(Event &e);  
      void SetSignal(Event &e);

      // Set POT
      void SetPOT(double pot){ POT = pot; }

      // Beam Mode
      int BeamMode = kFHC;
      int Run = 1;
      void SetBeamMode(int mode);
      void SetRun(int run){ Run = run; }

      void ImportBDTWeights(std::string WeightDir="");
      //void ImportSelectorBDTWeights(std::string WeightDir="");
      //void ImportAnalysisBDTWeights(std::string WeightDir="");

      SelectionParameters GetParams();

   private: 

      // Stores the parameters controlling the selection
      SelectionParameters TheParams;
      RecoParticle DaughterTrackParticle_;
      RecoParticle CCMuTrackParticle_;
      RecoParticle PrimaryKaonTrackParticle_;
      //int test=0;

      // POT to scale samples to
      double POT;

      // List of allowed sample types
      const std::vector<std::string> SampleTypes = { "AssociatedKaon" , "SingleKaon", "Background" , "Dirt" , "EXT" , "Data" };

      // Parameters of current sample being processed
      double thisSampleWeight;
      std::string thisSampleName;
      std::string thisSampleType;
      int thisSampleGenerator;

      // Flux and Generator/G4 weight calculators
      FluxWeighter a_FluxWeightCalc;
      GenG4WeightHandler a_GenG4WeightCalc;

      // Selection Algs
      FV::FiducialVolume a_FiducialVolume;
      MuonID a_MuonID;
      TrackLengthCutManager a_TrackLengthCutManager;
      BDTManager a_BDTManager;
      //SelectorBDTManager a_SelectorBDTManager;
      //AnalysisBDTManager a_AnalysisBDTManager;
      EventListFilter a_EventListFilter;
      SecondaryVertexFitter a_SecondaryVertexFitter;

      // Misc settings/methods //
   private:

      bool fUseFluxWeight = true;
      bool fUseGenWeight = true;

   public:

      void UseFluxWeight(bool usefluxweight);
      void UseGenWeight(bool usegenweight); 

   private:

      // Cut Data Management //
      //const std::vector<std::string> CutTypes = { "FV" , "Tracks" , "Showers" , "MuonID" , "SubleadingTracks" , "DecaySelector" , "DecayAnalysis" , "Connectedness" , "InvariantMass" , "AlphaAngle" };
      const std::vector<std::string> CutTypes = { "FV" , "NuCCInclusiveFilter" , "DaughterTrack" , "DaughterFV" , "DaughterTrackLength" , "BDT" };
      void DeclareCuts();
      std::vector<Cut> Cuts;
      void UpdateCut(const Event &e,bool Passed,std::string CutName);

   public:

      Cut GetCut(std::string CutName);
      void Reset();

      // Cut Functions //

   public:

      bool FiducialVolumeCut(const Event &e);
      bool NuCCInclusiveFilter(const Event &e);
      bool ChooseMuonCandidate(Event &e);
      bool DaughterTrackCut(const Event &e);
      bool DaughterFiducialVolumeCut(const Event &e);
      bool DaughterTrackLengthCut(const Event &e, const RecoParticle &DaughterTrackParticle);
      bool BDTCut(Event &e);
      bool BDTCut(Event &e, const RecoParticle &PrimaryKaonTrackParticle, const RecoParticle &DaughterTrackParticle);
      double BDTScore(Event &e, const RecoParticle &PrimaryKaonTrackParticle, const RecoParticle &DaughterTrackParticle);
      bool EventListCut(const Event &e);

      void StorePrimaryDaughterTracksPair(const Event &e);
      bool IsWithinDistance(const TVector3& end1, const TVector3& start2, double maxDistance);

      // Histogram Functions //

   private:

      std::string fTitle;
      int fHistNBins;
      int fHist2DNXBins;
      int fHist2DNYBins;
      double fHistLow;
      double fHistHigh;
      double fHist2DLowX;
      double fHist2DHighX;
      double fHist2DLowY;
      double fHist2DHighY;
      std::vector<double> fHistBoundaries;
      std::vector<double> fHist2DBoundariesX;
      std::vector<double> fHist2DBoundariesY;

      bool fHasData=false;
      bool fUseText=false;

      TH1D * Hist_Data=nullptr;
      TH1D * Hist_All=nullptr;
      TH1D * Hist_BDT_Signal=nullptr;
      TH1D * Hist_BDT_Signal_All=nullptr;
      TH1D * Hist_BDT_All=nullptr;
      TH1D * Hist_Efficiency=nullptr;
      TH1D * Hist_Purity=nullptr;
      TH1D * Hist_EtoP=nullptr;
      TH1D * Hist2D_BDT_Signal=nullptr;
      TH1D * Hist2D_BDT_Signal_All=nullptr;
      TH1D * Hist2D_BDT_All=nullptr;
      TH1D * Hist2D_Efficiency=nullptr;
      TH1D * Hist2D_Purity=nullptr;
      TH1D * Hist2D_EtoP=nullptr;

      std::map<std::string,TH1D*> Hists_ByProc;
      std::map<std::string,TH1D*> Hists_ByType;
      std::map<std::string,TH1D*> Hists_ByType2;
      std::map<std::string,TH1D*> Hists_ByPrimaryPDG;
      std::map<std::string,TH1D*> Hists_ByDaughterPDG;
      std::map<std::string,TH2D*> Hists2D_BySigBG;

      std::map<std::string,std::vector<TH1D*>> Multisim_Sys_Hists_All;
      std::map<std::string,std::vector<TH1D*>> SingleUnisim_Sys_Hists_All;
      std::map<std::string,std::vector<TH1D*>> DualUnisim_Sys_Hists_All;
      std::map<std::string,std::map<std::string,std::vector<TH1D*>>> Multisim_Sys_Hists; // histogram in different multisim universes
      std::map<std::string,std::map<std::string,std::vector<TH1D*>>> SingleUnisim_Sys_Hists; // histogram in different single univese unisims
      std::map<std::string,std::map<std::string,std::vector<TH1D*>>> DualUnisim_Sys_Hists;  // histogram in different two universe multisims

      TFile *f_Hists = nullptr;
      void OpenHistFile(std::string label="Hists");

      std::vector<std::string> BinLabels;

   public:

      void AddSystematic(int systype,int universes,std::string name);
      void FillHistogramsSys(const Event &e,double variable,std::string name,std::vector<double> weights);
      void FillHistogramsSys(const Event &e,double variable,std::string name,int universe,double weight);
      void DrawHistogramsSys(std::string label,std::string name,std::string type="All");
      TMatrixD GetCovarianceMatrix(std::string label,std::string name,std::string type="All");

      void SetupHistograms(int n,double low,double high,std::string title="");
      void SetupHistograms(std::vector<double> boundaries,std::string title="");
      void SetupHistogramsEtoP();
      void SetupHistogramsEtoPTwoBox(int nx,double lowx,double highx,int ny,double lowy,double highy);
      void SetupHistogramsPDG(int n,double low,double high,std::string title="");
      void Setup2DHistograms(int n_x, double low_x, double high_x, int n_y, double low_y, double high_y, std::string title);
      void Setup2DHistograms(std::vector<double> boundariesx, std::vector<double> boundariesy, std::string title="");
      void FillHistograms(const Event &e,double variable,double weight=1.0);
      void FillHistogramsEtoP(const Event &e,double variable,RecoParticle PrimaryKaonTrackParticle, RecoParticle DaughterTrackParticle,double weight=1.0);
      void FillHistogramsEtoP(const Event &e,double variable,double weight=1.0,bool withPreCut=false);
      void FillHistogramsEtoPTwoBox(const Event &e,double variable1,double variable2,double weight=1.0,bool withPreCut=false);
      void Fill2DHistograms(const Event &e,double variable_x,double variable_y,double weight=1.0);
      void Fill2DHistograms(const Event &e,double variable_x,double variable_y,RecoParticle PrimaryKaonTrackParticle, RecoParticle DaughterTrackParticle,double weight=1.0);
      void FillHistogramsPDG(const Event &e,double variable,RecoParticle PrimaryKaonTrackParticle, RecoParticle DaughterTrackParticle,double weight=1.0);
      void DrawHistograms(std::string label="Hists",double Scale=1.0,double SignalScale=1.0);
      void Draw2DHistograms(std::string label="Hists",double Scale=1.0,double SignalScale=1.0,std::vector<std::string> binlabels={});
      void DrawHistogramsPDG(std::string label="Hists",double Scale=1.0,double SignalScale=1.0);

      void FillEtoPCurve();
      void PlotEtoPCurve();

      double GetPrediction(int bin,std::string type="");

      RecoParticle GetDaughterTrackParticle();
      void SetDaughterTrackParticle(RecoParticle DaughterTrackParticle);
      RecoParticle GetPrimaryKaonTrackParticle();
      void SetPrimaryKaonTrackParticle(RecoParticle PrimaryKaonTrackParticle);
      RecoParticle GetCCMuTrackParticle();
      void SetCCMuTrackParticle(RecoParticle CCMu);
      std::vector<std::pair<RecoParticle,RecoParticle>> VectorPair;

      TH1D* GetHist_All();

      std::string PlotDir="Plots/";
      std::string RootfileDir="rootfiles/";

      void SetBinLabels(std::vector<std::string> binlabels);
      std::vector<double> GetBinBoundaries();

      void WidthScaleHistograms();

      void UseText(){ fUseText = true; }
};

#endif

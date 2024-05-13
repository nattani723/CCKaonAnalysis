#ifndef _FiducialVolume_h_
#define _FiducialVolume_h_

#include "TVector3.h"


namespace FV {

   enum FV_Versions{ kOldFV , kWholeTPC , kWirecell , kWholeTPCPadded , kWirecellPadded };

   // Edges of TPC
   const double TPCxmin = -1.55;
   const double TPCxmax = 254.8;
   const double TPCymin = -115.53;
   const double TPCymax = 117.47;
   const double TPCzmin = 0.1;
   const double TPCzmax = 1036.9;

   //dead region to be cut - used in all FV versions
   const double deadzmin = 675.1;
   const double deadzmax = 775.1;

   // Fiducial volume class //

   class FiducialVolume {

      private:

     const double FVxmin = 0.0;
     const double FVxmax = 256.35;
     const double FVymin = -115.53;
     const double FVymax = 117.47;
     const double FVzmin = 0.1;
     const double FVzmax = 1036.9;

     const double FVxmin_5cm = 5.0;
     const double FVxmax_5cm = 251.35;
     const double FVymin_5cm = -110.53;
     const double FVymax_5cm = 112.47;
     const double FVzmin_5cm = 5.1;
     const double FVzmax_5cm = 1031.9;

     const double FVxmin_CCInclusive = 0.0;
     const double FVxmax_CCInclusive = 246.35;
     const double FVymin_CCInclusive = -105.53;
     const double FVymax_CCInclusive = 107.47;
     const double FVzmin_CCInclusive = 10.1;
     const double FVzmax_CCInclusive = 986.8;

         // MCC8 Inclusive FV
         const double FV_v1_xmin = 12.0;
         const double FV_v1_xmax = 256.35 - 12.0;
         const double FV_v1_ymin = -115.53 + 35;
         const double FV_v1_ymax = 117.47 - 35;
         const double FV_v1_zmin = 0.1 + 25;
         const double FV_v1_zmax = 1036.9 - 85;

         // Wirecell FV
         const double YX_TOP_y1_array     = 116;
         const double YX_TOP_x1_array[11] = {0, 150.00, 132.56, 122.86, 119.46, 114.22, 110.90, 115.85, 113.48, 126.36, 144.21};
         const double YX_TOP_y2_array[11] = {0, 110.00, 108.14, 106.77, 105.30, 103.40, 102.18, 101.76, 102.27, 102.75, 105.10};
         const double YX_TOP_x2_array = 256;

         const double YX_BOT_y1_array     = -115;
         const double YX_BOT_x1_array[11] = {0, 115.71, 98.05, 92.42, 91.14, 92.25, 85.38, 78.19, 74.46, 78.86, 108.90};
         const double YX_BOT_y2_array[11] = {0, -101.72, -99.46, -99.51, -100.43, -99.55, -98.56, -98.00, -98.30, -99.32, -104.20};
         const double YX_BOT_x2_array = 256;

         /// ZX view has Y dependence: Y sub-range from -116 to 116cm per 24cm
         const double ZX_Up_z1_array = 0;
         const double ZX_Up_x1_array = 120;
         const double ZX_Up_z2_array = 11;
         const double ZX_Up_x2_array = 256;

         const double ZX_Dw_z1_array     = 1037;
         const double ZX_Dw_x1_array[11] = {0, 120.00, 115.24, 108.50, 110.67, 120.90, 126.43, 140.51, 157.15, 120.00, 120.00};
         const double ZX_Dw_z2_array[11] = {0, 1029.00, 1029.12, 1027.21, 1026.01, 1024.91, 1025.27, 1025.32, 1027.61, 1026.00, 1026.00};
         const double ZX_Dw_x2_array     = 256;

         std::vector<double> boundary_xy_x, boundary_xy_y;
         std::vector<double> boundary_xz_x, boundary_xz_z;

         std::vector<std::vector<double>> boundary_xy_x_array, boundary_xy_y_array;
         std::vector<std::vector<double>> boundary_xz_x_array, boundary_xz_z_array;

         const double m_anode = 0;
         const double boundary_dis_cut = 3;
         const double m_top = 117;
         const double m_bottom = -116;
         const double m_upstream = 0;
         const double m_downstream = 1037;

      public:

         FiducialVolume();
         FiducialVolume(int FV);
         FiducialVolume(int FV,double Padding);

         bool InFiducialVolume(TVector3 Position);

      private:

         double fPadding = 0.0;
         int fVersion = 1;           

         void SetupWirecellFV();
         int pnpoly(std::vector<double>& vertx, std::vector<double>& verty, double testx, double testy);

	 bool InFiducialVolume_5cm(TVector3 Position);
	 bool InFiducialVolume_MCC9(TVector3 Position);
	 bool InFiducialVolume_CCInclusive(TVector3 Position);
         bool InFiducialVolume_OldFV(TVector3 Position);
         bool InFiducialVolume_WholeTPCPadded(TVector3 Position);
         bool InFiducialVolume_Wirecell(TVector3 Position);
         bool InFiducialVolume_WirecellPadded(TVector3 Position);

   };

}

#endif

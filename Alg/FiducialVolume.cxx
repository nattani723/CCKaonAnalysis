#ifndef _FiducialVolume_cxx_
#define _FiducialVolume_cxx_

#include "FiducialVolume.h"

using namespace FV;

///////////////////////////////////////////////////////////////////////////////////////////////

FiducialVolume::FiducialVolume(){

   fVersion = 1;

}

///////////////////////////////////////////////////////////////////////////////////////////////

FiducialVolume::FiducialVolume(int FV){

   fVersion = FV;

   if(fVersion == kWirecell || fVersion == kWirecellPadded) SetupWirecellFV();

}

///////////////////////////////////////////////////////////////////////////////////////////////

FiducialVolume::FiducialVolume(int FV,double Padding){

   fVersion = FV;

   if(fVersion == kWirecell || fVersion == kWirecellPadded) SetupWirecellFV();

   fPadding = Padding;

}

///////////////////////////////////////////////////////////////////////////////////////////////

void FiducialVolume::SetupWirecellFV(){
   for(int idx=0; idx<=9; idx++) {

      boundary_xy_x_array.push_back({0,0,0,0,0,0});                               boundary_xy_y_array.push_back({0,0,0,0,0,0});
      boundary_xz_x_array.push_back({0,0,0,0,0,0});                               boundary_xz_z_array.push_back({0,0,0,0,0,0});

      boundary_xy_x_array[idx][0] = m_anode              + boundary_dis_cut;      boundary_xy_y_array[idx][0] = m_bottom             + boundary_dis_cut;
      boundary_xy_x_array[idx][1] = YX_BOT_x1_array[idx] - boundary_dis_cut;      boundary_xy_y_array[idx][1] = YX_BOT_y1_array      + boundary_dis_cut;
      boundary_xy_x_array[idx][2] = YX_BOT_x2_array      - boundary_dis_cut;      boundary_xy_y_array[idx][2] = YX_BOT_y2_array[idx] + boundary_dis_cut;
      boundary_xy_x_array[idx][3] = YX_TOP_x2_array      - boundary_dis_cut;      boundary_xy_y_array[idx][3] = YX_TOP_y2_array[idx] - boundary_dis_cut;
      boundary_xy_x_array[idx][4] = YX_TOP_x1_array[idx] - boundary_dis_cut;      boundary_xy_y_array[idx][4] = YX_TOP_y1_array      - boundary_dis_cut;
      boundary_xy_x_array[idx][5] = m_anode              + boundary_dis_cut;      boundary_xy_y_array[idx][5] = m_top                - boundary_dis_cut;

      boundary_xz_x_array[idx][0] = m_anode             + boundary_dis_cut;       boundary_xz_z_array[idx][0] = m_upstream          + boundary_dis_cut+1;
      boundary_xz_x_array[idx][1] = ZX_Up_x1_array      - boundary_dis_cut;       boundary_xz_z_array[idx][1] = ZX_Up_z1_array      + boundary_dis_cut+1;
      boundary_xz_x_array[idx][2] = ZX_Up_x2_array      - boundary_dis_cut;       boundary_xz_z_array[idx][2] = ZX_Up_z2_array      + boundary_dis_cut+1;
      boundary_xz_x_array[idx][3] = ZX_Dw_x2_array      - boundary_dis_cut;       boundary_xz_z_array[idx][3] = ZX_Dw_z2_array[idx] - boundary_dis_cut-1;
      boundary_xz_x_array[idx][4] = ZX_Dw_x1_array[idx] - boundary_dis_cut;       boundary_xz_z_array[idx][4] = ZX_Dw_z1_array      - boundary_dis_cut-1;
      boundary_xz_x_array[idx][5] = m_anode             + boundary_dis_cut;       boundary_xz_z_array[idx][5] = m_downstream        - boundary_dis_cut-1;



   }
}

///////////////////////////////////////////////////////////////////////////////////////////////

int FiducialVolume::pnpoly(std::vector<double>& vertx, std::vector<double>& verty, double testx, double testy){
   int i, j, c = 0;
   for (i = 0, j = int(vertx.size())-1; i < int(vertx.size()); j = i++) {
      if ( ((verty[i]>testy) != (verty[j]>testy)) &&
            (testx < (vertx[j]-vertx[i]) * (testy-verty[i]) / (verty[j]-verty[i]) + vertx[i]) )
         c = !c;
   }
   return c;
}


///////////////////////////////////////////////////////////////////////////////////////////////

bool FiducialVolume::InFiducialVolume(TVector3 Position){

   switch (fVersion){

      case kOldFV: 
         return InFiducialVolume_OldFV(Position);

      case kWholeTPC:
      case kWholeTPCPadded:
         return InFiducialVolume_WholeTPCPadded(Position);

      case kWirecell:
         return InFiducialVolume_Wirecell(Position);

      case kWirecellPadded:
         return InFiducialVolume_WirecellPadded(Position);

      default:
         return false;

   }

}

///////////////////////////////////////////////////////////////////////////////////////////////

bool FiducialVolume::InFiducialVolume_MCC9(TVector3 Position){

   if(Position.X() > FVxmax || Position.X() < FVxmin) return false;

   if(Position.Y() > FVymax || Position.Y() < FVymin) return false;

   if(Position.Z() > FVzmax || Position.Z() < FVzmin) return false;

   if(Position.Z() < deadzmax && Position.Z() > deadzmin) return false;

   return true;

}

///////////////////////////////////////////////////////////////////////////////////////////////

bool FiducialVolume::InFiducialVolume_5cm(TVector3 Position){

   if(Position.X() > FVxmax_5cm || Position.X() < FVxmin_5cm) return false;

   if(Position.Y() > FVymax_5cm || Position.Y() < FVymin_5cm) return false;

   if(Position.Z() > FVzmax_5cm || Position.Z() < FVzmin_5cm) return false;

   if(Position.Z() < deadzmax && Position.Z() > deadzmin) return false;

   return true;

}

///////////////////////////////////////////////////////////////////////////////////////////////

bool FiducialVolume::InFiducialVolume_CCInclusive(TVector3 Position){

   if(Position.X() > FVxmax_CCInclusive || Position.X() < FVxmin_CCInclusive) return false;

   if(Position.Y() > FVymax_CCInclusive || Position.Y() < FVymin_CCInclusive) return false;

   if(Position.Z() > FVzmax_CCInclusive || Position.Z() < FVzmin_CCInclusive) return false;

   if(Position.Z() < deadzmax && Position.Z() > deadzmin) return false;

   return true;

}

///////////////////////////////////////////////////////////////////////////////////////////////

bool FiducialVolume::InFiducialVolume_OldFV(TVector3 Position){

   if(Position.X() > FV_v1_xmax || Position.X() < FV_v1_xmin) return false;

   if(Position.Y() > FV_v1_ymax || Position.Y() < FV_v1_ymin) return false;

   if(Position.Z() > FV_v1_zmax || Position.Z() < FV_v1_zmin) return false;

   if(Position.Z() < deadzmax && Position.Z() > deadzmin) return false;

   return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////

bool FiducialVolume::InFiducialVolume_WholeTPCPadded(TVector3 Position){

   if(Position.X() > TPCxmax - fPadding || Position.X() < TPCxmin + fPadding) return false;

   if(Position.Y() > TPCymax - fPadding || Position.Y() < TPCymin + fPadding) return false;

   if(Position.Z() > TPCzmax - fPadding || Position.Z() < TPCzmin + fPadding) return false;

   if(Position.Z() < deadzmax && Position.Z() > deadzmin) return false;

   return true;

}

///////////////////////////////////////////////////////////////////////////////////////////////

bool FiducialVolume::InFiducialVolume_Wirecell(TVector3 Position){

   // Don't include things outside the TPC
   if(Position.Z() > 1000 || Position.Z() < 0) return false;
   // Cut dead z region
   if(Position.Z() < deadzmax && Position.Z() > deadzmin) return false;


   int c1=0;
   int c2=0;
   int index_y = floor((Position.Y()+116)/24);
   int index_z = floor(Position.Z()/100);
   if(index_y<0){index_y=0;} else if(index_y>9){index_y=9;}
   if(index_z<0){index_z=0;} else if(index_z>9){index_z=9;}

   c1 = pnpoly(boundary_xy_x_array[index_z], boundary_xy_y_array[index_z], Position.X(), Position.Y());
   c2 = pnpoly(boundary_xz_x_array[index_y], boundary_xz_z_array[index_y], Position.X(), Position.Z());


   return c1 && c2; 

}

///////////////////////////////////////////////////////////////////////////////////////////////

bool FiducialVolume::InFiducialVolume_WirecellPadded(TVector3 Position){

   return InFiducialVolume_Wirecell(Position) && InFiducialVolume_WholeTPCPadded(Position);
}

///////////////////////////////////////////////////////////////////////////////////////////////

#endif

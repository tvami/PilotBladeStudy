#include "custom_can_macro.C"

void plotting() {
  gStyle->SetOptStat(1100);
  gStyle->SetOptTitle(1);
  TFile *f; TCanvas *c; TTree* t; TPaveStats *st;
  //TArrow *arr; TGaxis* axis;
  bool save = 0;
  std::string save_dir = "/data/vami/projects/pilotBlade/ppProcessing/Results/";
  const char* format = ".eps";
//_________________________________________________________________________________________________
  //data/vami/projects/PilotBlade/Workin/CMSSW_7_5_0_pre1/src/
  f = TFile::Open("./nTuplePilotBlade_test.root");
  t2 = (TTree*)f->Get("clustTree");
//_________________________________________________________________________________________________

// ClustTree nTuple
  
  // RZ Cluster plot
  hrzcl = new TH2D("RZ","Cluster positions on FPIX -Z side (R-Z plane);Z [cm];R [cm]", 110,-65.0,-30.0,20,0.0,20.0);
  c = custom_can_(hrzcl, "PilotBlade_3RZ_Clusters", 0,0, 650,500, 65,20, 45,60, 33, -50.0,18.0);
  hrzcl->Draw();
  t2->SetMarkerColor(kBlue);
  t2->Draw("sqrt((clusters.glx*clusters.glx)+(clusters.gly*clusters.gly)):clusters.glz", "(clusters.type!=2&&(module.blade==4||module.blade==5||module.blade==16||module.blade==17))||module_on.disk==-3", "SAME");
  t2->SetMarkerColor(kRed);
  t2->Draw("sqrt((clusters.glx*clusters.glx)+(clusters.gly*clusters.gly)):clusters.glz", "clusters.type==2||module_on.disk==-3", "SAME");
  gPad->Update(); 
  hrzcl->GetYaxis()->SetRangeUser(0,20);
  hrzcl->SetLineWidth(2);
  draw_lat_(-47, 20.5, "Cluster positions on FPIX -Z side (R-Z plane)", 1, 0.04, 0.0, 21);
  draw_lat_(-62, 16.0, "Pilot blades", 1, 0.04, 90.0, 21);
  draw_lat_(-52, 16.0, "Disk -2", 1, 0.04, 90.0, 21);
  draw_lat_(-39, 16.0, "Disk -1", 1, 0.04, 90.0, 21);
  prelim_sim_lat_(-50,60,18,18.5, 0);
  gPad->Update(); 
  if (save) c->SaveAs((save_dir+std::string(c->GetName())+format).c_str());


  // XY Cluster plot
  hxycl = new TH2D("glXY","Cluster positions on FPIX -Z side (transverse plane);X [cm];Y [cm]", 36,-18.0,18.0,36,-18.0,18.0);
  c = custom_can_(hxycl, "PilotBlade_2XY_Clusters", 0,0, 500,500, 65,20, 45,60, 33, -50.0,18.0);
  hxycl->Draw();
  t2->SetMarkerColor(kBlue);
  //t2->Draw("clusters.gly:clusters.glx>>(640, -16,16, 640, -16,16)", "module.side=1","SAME");
  t2->Draw("clusters.gly:clusters.glx>>(640, -16,16, 640, -16,16)", "module_on.disk==-2","SAME");
  t2->SetMarkerColor(kRed);
  t2->Draw("clusters.gly:clusters.glx", "module_on.disk==-3", "SAME");
  gPad->Update(); 
  hxycl->SetLineWidth(2);
  draw_lat_(-1, 19.5, "Cluster positions on FPIX -Z side (transverse plane)", 1, 0.04, 0.0, 21);
  prelim_sim_lat_(-6,15.5,15.2,15.8, 0);
  gPad->Update(); 
  if (save) c->SaveAs((save_dir+std::string(c->GetName())+format).c_str());

  // RZ Cluster plot COLZ occupancy
  hrzclCOLZ = new TH2D("RZCOLZ","Cluster occupancy on FPIX -Z side (R-Z plane);Z [cm];R [cm]", 2000,-65.0,-30.0,2000,0.0,20.0);
  c = custom_can_(hrzclCOLZ, "PilotBlade_4RZ_Clusters_COLZ", 0,0, 650,500, 65,100, 45,60, 33, -50.0,18.0);
  hrzclCOLZ->Draw();
  t2->Draw("sqrt((clusters.glx*clusters.glx)+(clusters.gly*clusters.gly)):clusters.glz>>RZCOLZ", "(clusters.type!=2&&module_on.side==1&&(module.blade==4||module.blade==5||module.blade==16||module.blade==17))||module_on.disk==-3", "COLZ");
  gPad->Update(); 
  hrzclCOLZ->GetYaxis()->SetRangeUser(0,20);
  hrzclCOLZ->SetLineWidth(2);
  draw_lat_(-47, 20.5, "Cluster occupancy on FPIX -Z side (R-Z plane)", 1, 0.04, 0.0, 21);
  draw_lat_(-62, 16.0, "Pilot blades", 1, 0.04, 90.0, 21);
  draw_lat_(-52, 16.0, "Disk -2", 1, 0.04, 90.0, 21);
  draw_lat_(-39, 16.0, "Disk -1", 1, 0.04, 90.0, 21);
  prelim_sim_lat_(-50,60,18.5,18.5, 0);
  gPad->Update(); 
  if (save) c->SaveAs((save_dir+std::string(c->GetName())+format).c_str());
   

//____________________________________________________________________________
  // trajTree nTuple
  f = TFile::Open("/data/vami/projects/pilotBlade/ppProcessing/Results/nTuplePB2900_v2.root");
  t = (TTree*)f->Get("trajTree");
//______________________________________________________________________________
 
  // PB Cluster Charge Distribution
  h = new TH1D("PBClustDistribution","Normalized cluster charge distribution (Pilot Blade); Cluster charge [ke];Clusters/1 ke", 200,0,200);
  c = custom_can_(h, "PilotBlade_5ClusterCharge", 1,1, 500,500, 100,20, 45,60, 33, 0.99,0.99);
  h->Draw();
  t->Draw("traj.norm_charge>>PBClustDistribution", "module_on.disk==-3", "SAME");
  gPad->Update();
  h->GetXaxis()->SetRangeUser(0.1,80);
  h->GetYaxis()->SetRangeUser(0,600);
  h->SetLineColor(1);
  h->SetLineWidth(2);
  prelim_sim_lat_(30,70, 0,500, 0, 0.04);
  gPad->Update(); 
  if (save) c->SaveAs((save_dir+std::string(c->GetName())+format).c_str());

 // FPIX Cluster Charge Distribution
  hfpix = new TH1D("FPixClustDistribution","Normalized cluster charge distribution (Forward disk -2); Cluster charge [ke];Clusters/1 ke", 200,0,200);
  c = custom_can_(hfpix, "FPix_5ClusterCharge", 1,1, 500,500, 100,20, 45,60, 33, 0.99,0.99);
  hfpix->Draw();
  t->Draw("traj.norm_charge>>FPixClustDistribution", "module_on.disk==-2", "SAME");
  gPad->Update();
  hfpix->GetXaxis()->SetRangeUser(0.1,80);
  hfpix->GetYaxis()->SetRangeUser(0,1200);
  hfpix->SetLineColor(1);
  hfpix->SetLineWidth(2);
  prelim_sim_lat_(30,70, 0,500, 0, 0.04);
  gPad->Update(); 
  if (save) c->SaveAs((save_dir+std::string(c->GetName())+format).c_str());
  
  // RZ RecHit plot
  hrz = new TH2D("RZ","Tracking hits on the FPIX -Z side (R-Z plane);Z [cm];R [cm]", 110,-65.0,-30.0,40,0.0,20);
  c = custom_can_(hrz, "PilotBlade_7RZ_RecHit", 0,0, 650,500, 65,20, 45,60, 33, -50.0,18.0);
  hrz->Draw();
  t->SetMarkerColor(kBlue);
  t->Draw("sqrt((traj.glx*traj.glx)+(traj.gly*traj.gly)):traj.glz", "type==0&&(module.blade==4||module.blade==5||module.blade==16||module.blade==17)", "SAME");
  t->SetMarkerColor(kRed);
  t->SetMarkerStyle(8);
  t->SetMarkerSize(0.25);
  t->Draw("sqrt((traj.glx*traj.glx)+(traj.gly*traj.gly)):traj.glz", "type==2&&module_on.disk==-3", "SAME");
  gPad->Update(); 
  hrz->GetYaxis()->SetRangeUser(0,20);
  hrz->SetLineWidth(2);
  draw_lat_(-47, 20.5, "Tracking hits on the FPIX -Z side (R-Z plane)", 1, 0.04, 0.0, 21);
  draw_lat_(-51.5, 1.0, "Pilot blades are only spectator in tracking", 1, 0.04, 0.0, 21);
  draw_lat_(-62, 16.0, "Pilot blades", 1, 0.04, 90.0, 20);
  draw_lat_(-52, 16.0, "Disk -2", 1, 0.04, 90.0, 20);
  draw_lat_(-39, 16.0, "Disk -1", 1, 0.04, 90.0, 20);
  prelim_sim_lat_(-50,60,18.5,18.5, 0);
  gPad->Update(); 
  if (save) c->SaveAs((save_dir+std::string(c->GetName())+format).c_str());

  // XY RecHit plot
  hxy = new TH2D("glXY","Tracking hits on the FPIX -Z side (transverse plane);X [cm];Y [cm]", 36,-18.0,18.0,36,-18.0,18.0);
  c = custom_can_(hxy, "PilotBlade_6XY_RecHit", 0,0, 500,500, 65,20, 45,60, 33, -50.0,18.0);
  hxy->Draw();
  t->SetMarkerColor(kBlue);
  t->Draw("traj.gly:traj.glx>>(640, -16,16, 640, -16,16)", "module.side=1&&traj.type==0","SAME");
  t->SetMarkerColor(kRed);
  t->SetMarkerStyle(8);
  t->SetMarkerSize(0.25);
  t->Draw("traj.gly:traj.glx", "module_on.disk==-3&&traj.dx_cl!=-9999.0&&(traj.dx_cl<0.01||traj.dy_cl<0.01)", "SAME");
  gPad->Update(); 
  hxy->SetLineWidth(2);
  draw_lat_(-1, 19.5, "Tracking hits on the FPIX -Z side (transverse plane)", 1, 0.04, 0.0, 21);
  prelim_sim_lat_(-6,15.5,15.2,15.8, 0);
  gPad->Update(); 
  if (save) c->SaveAs((save_dir+std::string(c->GetName())+format).c_str());
  
 /* 
  // dx residual
  hx = new TH1D("res_dx","Track hit residual on pixel pilot blade (azimuthal direction);Residual #DeltaX [cm]", 100,-0.099,0.099);
  c = custom_can_(hx, "PilotBlade_8ResidualDX", 1,1, 500,500, 40,20, 45,60, 33, 0.99,0.99);
  t->Draw("traj.dx_cl_corr[0]>>res_dx", "module.disk==3&&side==1&&onEdge==0&&type==2&&abs(traj.alpha)<1.24&&abs(traj.alpha)>1.21");
  gPad->Update();
  //hx->SetStats(1);  
  //st = (TPaveStats*)hx->FindObject("stats"); 
  //st->SetX1NDC(0.70); st->SetX2NDC(0.96); st->SetY1NDC(0.812); st->SetY2NDC(0.92);
  hx->GetYaxis()->SetRangeUser(0.1,135);
  hx->SetLineWidth(2);
  draw_lat_(0.06, 115, "RMS = 0.01038", 1, 0.04, 0.0, 21);
  prelim_sim_lat_(-0.08,0, 110,125, 0);
  gPad->Update(); if (save) c->SaveAs((save_dir+std::string(c->GetName())+format).c_str());
 
  // dy residual
  hy = new TH1D("res_dy","Track hit residual on pixel pilot blade (radial direction);Residual #DeltaY [cm]", 100,-0.099,0.099);
  c = custom_can_(hy, "PilotBlade_9ResidualDY", 1,1, 500,500, 40,20, 45,60, 33, 0.99,0.99);
  t->Draw("traj.dy_cl_corr[0]>>res_dy", "module.disk==3&&side==1&&onEdge==0&&type==2");
  gPad->Update();
  //hy->SetStats(1); 
  //st = (TPaveStats*)hy->FindObject("stats"); 
  //st->SetX1NDC(0.70); st->SetX2NDC(0.96); st->SetY1NDC(0.812); st->SetY2NDC(0.92);
  hy->GetYaxis()->SetRangeUser(0.1,190);
  hy->SetLineWidth(2);
  draw_lat_(0.06, 160, "RMS = 0.01729", 1, 0.04, 0.0, 21);
  prelim_sim_lat_(-0.08,0, 160,175, 0);
  gPad->Update(); if (save) c->SaveAs((save_dir+std::string(c->GetName())+format).c_str());
  */
/*
 TH2* h, std::string canname, int gx = 0, int gy = 0,
                     int histosize_x = 500, int histosize_y = 500,
                     int mar_left = 80, int mar_right = 120, int mar_top = 20, int mar_bottom = 60,
                     int title_align = 33, float title_x = 1.0, float title_y = 1.0,
                     std::string draw="COLZ", bool norm=false, bool log=false
                     
  void prelim_lat_(double xmin, double xmax, double ymin, double ymax, bool in, double scale = -1) {

*/

}

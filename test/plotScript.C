//   Usage: 
//   .L plotScript.C
//   digis();

#include "TROOT.h"
#include "TCanvas.h"
#include "TChain.h"
#include "TChainElement.h"
#include "TFile.h"
#include "TTree.h"
#include "TBrowser.h"
#include "TH2.h"
#include "TRandom.h"
#include "TProfile.h"
#include "TLegend.h"
#include <iostream>
#include <sys/stat.h>
#include <vector>
#include <stdlib.h>

#include "plotScript.h"
#include "/data/vami/.scripts.d/custom_can_macro.C"

bool FileExists(char* filename) 
{
    struct stat fileInfo;
    return stat(filename, &fileInfo) == 0;
}

int delay(uint run, const uint ls) {
  int delay=-9999;

  if (run==271056) {
    if (ls<58)  { delay=37; return delay; }
    if (ls<81)  { delay=12; return delay; }
    if (ls<110) { delay=-25; return delay;} // Get back to this point
    if (ls<223) { delay=49; return delay; }
    if (ls<263) { delay=37; return delay; }
    if (ls<306) { delay=25; return delay; }
  } 
  if (run==271084 || run==271087) { 
    delay=12; return delay; 
  } 
  if (run==271136 || run==271142 || run==271143 || run==271144 || run==271151) {
    delay=12; return delay;
  }
  if (run==271153 || run==271155 || run==271161 || run==271167 || run==271168) {
    delay=12; return delay;
  }
  if (run==271169 || run==271170 || run==271176 || run==271177) {
    delay=12; return delay;
  }
  if (run==271188) { 
    delay=49; return delay; 
  } 
  if (run==271191) {
    if (ls<55)  { delay=62; return delay; }
    if (ls<110) { delay=74; return delay; }
    else 	{ delay=87; return delay; }
  } 
  if (run==271192) { 
    delay=87; return delay; 
  } 
  if (run==271193) {
    if (ls<44)  { delay=47; return delay; }
    if (ls<92)  { delay=45; return delay; }
    else        { delay=43; return delay; }
  } 
  if (run==271195) {
    if (ls<47)  { delay=43; return delay; }
    if (ls<95)  { delay=41; return delay; }
    if (ls<134) { delay=39; return delay; }
    if (ls<186) { delay=85; return delay; }
    else 	{ delay=83; return delay; }
  }
  if (run==271196) {
    if (ls<37)	{ delay=79; return delay; }
    if (ls<88)  { delay=77; return delay; }
    if (ls<127) { delay=70; return delay; }
    if (ls<168) { delay=68; return delay; }
    if (ls<204) { delay=66; return delay; }
    else 	{ delay=64; return delay; }
  }
  if (run==271197) {
    if (ls<5)	{ delay=49; return delay; } // this is not the same as in the Elog (there it is 64) 
    else 	{ delay=60; return delay; }
  }
  if (run==271214) {
    if (ls<51)	{ delay=58; return delay; }
    else 	{ delay=56; return delay; }
  }
  if (run==271215 || run==271216 || run==271221 || run==271224 || run==271230) {
    delay=54; return delay;
  }
  if (run==271234 || run==271244 || run==271245 || run==271248 || run==271250) {
    delay=49; return delay;
  }
  if (run==271253 || run==271254 || run==271269 || run==271280 || run==271291) {
    delay=49; return delay;
  }
  if (run==271304) {
    if (ls<72) { delay=49; return delay; }
    else       { delay=54; return delay; }
  }
  if (run==271306) {
    if (ls<98)  { delay=54; return delay; }
    if (ls<118) { delay=52; return delay; }
    else        { delay=49; return delay; }
  }
  if (run==271307) {
    delay=52; // according to the elog this is 49
    return delay;
  }
  if (run==271310) {
    if (ls<12) { delay=52; return delay; }
    else       { delay=49; return delay; }
  }
  if (run==272008 || run==272009 || run==272010 || run==272011) {
    delay=90; return delay;
  }
  if (run==272012 || run==272013 || run==272014) {
    delay=92; return delay;
  }
  if (run==272021) {
    if (ls<6)   { delay=92; return delay;}
    if (ls<17)  { delay=94; return delay; }
    if (ls<28)  { delay=96; return delay; }
    if (ls<38)  { delay=98; return delay; }
    if (ls<48)  { delay=100; return delay;}
    if (ls<58)  { delay=102; return delay;}
    if (ls<69)  { delay=104; return delay;}
    if (ls<80)  { delay=106; return delay;}
    if (ls<90)  { delay=108; return delay;}
    if (ls<100) { delay=110; return delay;}
    if (ls<110) { delay=112; return delay;}
    if (ls<122) { delay=114; return delay;}
    else        { delay=62; return delay; }
  }
  if (run==272022) {
   delay=62; return delay;
  }
  return delay;
}



std::string name(int detid) {
  if (detid==344130820) return std::string("FPix_BmI_D3_BLD3_PNL1_PLQ1");
  if (detid==344131844) return std::string("FPix_BmI_D3_BLD2_PNL1_PLQ1");
  if (detid==344132868) return std::string("FPix_BmO_D3_BLD10_PNL1_PLQ1");
  if (detid==344133892) return std::string("FPix_BmO_D3_BLD11_PNL1_PLQ1");
  if (detid==344131076) return std::string("FPix_BmI_D3_BLD3_PNL2_PLQ1");
  if (detid==344132100) return std::string("FPix_BmI_D3_BLD2_PNL2_PLQ1");
  if (detid==344133124) return std::string("FPix_BmO_D3_BLD10_PNL2_PLQ1");
  if (detid==344134148) return std::string("FPix_BmO_D3_BLD11_PNL2_PLQ1");
  return std::string("");
}


void digis()
{
  //gStyle->SetOptStat(1100);
  gStyle->SetOptStat(111111111);
  gStyle->SetOptTitle(1);
  bool save = 1;
  std::string save_dir = "./";
  const char* format = ".png";
  bool select49=false;

  int _detids[] = { 344130820, 344131844, 344132868, 344133892, 344131076, 344132100, 344133124, 344134148 };
  std::vector<int> detids(_detids, _detids + sizeof(_detids) / sizeof(int) );

  std::map<int,int> idx;
  for (size_t i=0; i<detids.size(); i++) {
    idx[detids[i]]=i;
    cout << "define detector id " << detids[i] << " as " << idx[detids[i]]<<std::endl;
  }
  

  TChain* filechain = new TChain("filechain");
  filechain->Add("/data/vami/projects/pilotBlade/pp2016Processing/CMSSW_8_0_5/src/0DataProc/crab/BP/Ntuple/crab_PilotBlade_data_Ntuplizer_pp_BP_good_RunsApril23_v1/results/nTuplePilotBlade_All_1.root");

  // Create the histograms
  std::vector<std::vector<TH1*> > hists;

  std::vector<TH1F *> PBADCDist;
  std::vector<TH2F *> PBDigisMod;
  std::vector<TProfile *> PBDigiVsLS;
  
  // ---------------------- Clusters ---------------------- 
  
  std::vector<TH1F *> PBClusterCharge;
  std::vector<TH1F *> PBClusterSize;
  std::vector<TH2F *> PBClustersMod;
  std::vector<TProfile *> PBClusterChargeVsLS;
  std::vector<TProfile *> PBClusterSizeVsLS;
  std::vector<TProfile *> PBClustersVsLS;

  std::vector<TProfile *> PBClusterChargeVsDel;
  std::vector<TProfile *> PBClusterSizeVsDel;
  std::vector<TProfile *> PBClustersVsDel;


  for (size_t imod=0; imod<detids.size(); imod++) {

    std::vector<TH1*> vh;
    TH1 *h;

    // ---------------------- Digis ---------------------- 
    PBADCDist.push_back((TH1F*)(h=new TH1F(Form("PBADCDist_%d", detids[imod]), Form("ADC Distribution in %s ;ADC;Yield", name(detids[imod]).c_str()), 50,0.,250.))); vh.push_back(h);
    PBDigisMod.push_back((TH2F*)(h=new TH2F(Form("PBDigisMod_%d", detids[imod]), Form("Pixels in %s ;columns [pixels];rows [pixels]", name(detids[imod]).c_str()),      416,0,416.0,      160,0,160.0))); vh.push_back(h);
    PBDigiVsLS.push_back((TProfile*)(h=new TProfile(Form("PBDigiVsLS_%d", detids[imod]),  Form("Avg num of pixels per event vs LumiSection in %s;LumiSection;Avg num of pixels", name(detids[imod]).c_str()), 5900, 0, 5900, 0, 100))); vh.push_back(h);

    // ---------------------- Clusters ---------------------- 
    
    PBClusterCharge.push_back((TH1F*)(h=new TH1F(Form("PBClusterCharge_%d", detids[imod]),  Form("Clusters Charge Distribution in  %s;Cluster charge [ke];Yield", name(detids[imod]).c_str()), 150,0,150))); vh.push_back(h);
    PBClusterSize.push_back((TH1F*)(h=new TH1F(Form("PBClusterSize_%d", detids[imod]), Form( "Clusters Size Distribution in %s;Cluster size [pixel];Yield", name(detids[imod]).c_str()), 10,0,10))); vh.push_back(h);
    PBClustersMod.push_back((TH2F*)(h=new TH2F(Form("PBClustersMod_%d", detids[imod]), Form("Clusters in %s;x;y", name(detids[imod]).c_str()),      416,0,416,      160,0,160.0))); vh.push_back(h);
    PBClusterChargeVsLS.push_back((TProfile*)(h=new TProfile(Form("PBClusterChargeVsLS_%d", detids[imod]),  Form("Avg cluster charge vs LumiSection in %s;LumiSection;Avg cluster charge", name(detids[imod]).c_str()), 5900, 0, 5900, 0, 150))); vh.push_back(h);
    PBClusterSizeVsLS.push_back((TProfile*)(h=new TProfile(Form("PBClusterSizeVsLS_%d", detids[imod]),  Form("Avg cluster size vs LumiSection in %s;LumiSection;Avg cluster size", name(detids[imod]).c_str()), 5900, 0, 5900, 0, 15))); vh.push_back(h);
    PBClustersVsLS.push_back((TProfile*)(h=new TProfile(Form("PBClustersVsLS_%d", detids[imod]),  Form("Avg num of clusters per event vs LumiSection in %s;LumiSection;Avg num of clusters", name(detids[imod]).c_str()), 5900, 0, 5900, 0, 100))); vh.push_back(h);

    PBClusterChargeVsDel.push_back((TProfile*)(h=new TProfile(Form("PBClusterChargeVsDel_%d", detids[imod]),  Form("Avg cluster charge vs Delay in %s;Delay;Avg cluster charge", name(detids[imod]).c_str()), 130, -30, 100, 0, 150))); vh.push_back(h);
    PBClusterSizeVsDel.push_back((TProfile*)(h=new TProfile(Form("PBClusterSizeVsDel_%d", detids[imod]),  Form("Avg cluster size vs Delay in %s;Delay;Avg cluster size", name(detids[imod]).c_str()), 130, -30, 100, 0, 15))); vh.push_back(h);
    PBClustersVsDel.push_back((TProfile*)(h=new TProfile(Form("PBClustersVsDel_%d", detids[imod]),  Form("Avg num of clusters per event vs Delay in %s;Delay;Avg num of clusters", name(detids[imod]).c_str()), 130, -30, 100, 0, 100))); vh.push_back(h);
    
    hists.push_back(vh);
  }

  for (size_t i=0; i<hists.size(); i++) {
    for (size_t j=0; j<hists[i].size(); j++) {
      std::cout<<hists[i][j]->GetName()<< " : "<<hists[i][j]->GetTitle()<<std::endl;
      hists[i][j]->SetMarkerColor(i==7 ? 46 : i+1);
      hists[i][j]->SetMarkerStyle(hists[i][j]->GetDimension()==1 ? 20 : 1);
      hists[i][j]->SetLineColor(i==7 ? 46 : i+1);
      hists[i][j]->SetLineWidth(2);
    }
    std::cout<<std::endl;
  }


// -------------------------------------------- 
  DigiData digi;
  ModuleData module_on;
  EventData evt;
  ClustData clusters;


  TObjArray* fileElements = filechain->GetListOfFiles();
  TIter next(fileElements);
  TChainElement* chEl=0;
  while (( chEl=(TChainElement*)next() )) {
    TFile f(chEl->GetTitle());
    std::cout << "Opening "<<chEl->GetTitle()<<std::endl;

// ---------------------- Digis ---------------------- 
    TTree* digiTree = (TTree*)f.Get("digiTree");
    digiTree->GetBranch("digi")->SetAddress(&digi);
    digiTree->GetBranch("module_on")->SetAddress(&module_on);
    digiTree->GetBranch("event")->SetAddress(&evt);

    std::vector<int> currentEvent(detids.size(), -1);
    std::vector<int> digiCounter(detids.size(), 0);

    for (Long64_t i=0, ndigi=digiTree->GetEntries(); i<ndigi; ++i) {
      digiTree->GetEntry(i);
      if (select49 && delay(evt.run, evt.ls)!=49) continue;

      int run=evt.run-271056;
      if (run>28) run-=100;
      Int_t ls=(evt.ls/10)+run*100;      
      int imod = idx[module_on.rawid];

      if(module_on.disk==-3) {
	PBADCDist[imod]->Fill(digi.adc);
        PBDigisMod[imod]->Fill(digi.col,digi.row);

	if (evt.evt!=currentEvent[imod]) {
	  if (currentEvent[imod]!=-1) PBDigiVsLS[imod]->Fill(ls, digiCounter[imod]);
	  currentEvent[imod]=evt.evt;
	  digiCounter[imod]=0;
	}
	++digiCounter[imod];
      }
    }

// ---------------------- Clusters ---------------------- 
    TTree* clustTree = (TTree*)f.Get("clustTree");
    
    clustTree->GetBranch("clust")->SetAddress(&clusters);
    clustTree->GetBranch("module_on")->SetAddress(&module_on);
    clustTree->GetBranch("event")->SetAddress(&evt);

    for (size_t i=0; i<currentEvent.size(); i++) currentEvent[i]=-1;
    std::vector<int> clusterCounter(detids.size(), 0);

    for (Long64_t i=0, nclust=clustTree->GetEntries(); i<nclust; ++i) {
      clustTree->GetEntry(i);
      if (select49 && delay(evt.run, evt.ls)!=49) continue;

      int run=evt.run-271056;
      if (run>28) run-=100;
      Int_t ls=(evt.ls/10)+run*100;      
      int imod = idx[module_on.rawid];

      if(module_on.disk==-3) {
	PBClusterCharge[imod]->Fill(clusters.charge);
	PBClusterSize[imod]->Fill(clusters.size);
        PBClustersMod[imod]->Fill(clusters.y,clusters.x);   
        PBClusterChargeVsLS[imod]->Fill(ls,clusters.charge);
        PBClusterSizeVsLS[imod]->Fill(ls,clusters.size);
        PBClusterChargeVsDel[imod]->Fill(delay(evt.run, evt.ls),clusters.charge);
        PBClusterSizeVsDel[imod]->Fill(delay(evt.run, evt.ls),clusters.size);

	if (evt.evt!=currentEvent[imod]) {
	  if (currentEvent[imod]!=-1) {
	    PBClustersVsLS[imod]->Fill(ls, clusterCounter[imod]);
	    PBClustersVsDel[imod]->Fill(delay(evt.run, evt.ls), clusterCounter[imod]);
	  }
	  currentEvent[imod]=evt.evt;
	  clusterCounter[imod]=0;
	}
	++clusterCounter[imod];
      }
    }

// -------------------------------------------- 
  } // End of loop on files

  
  // Create the canvas and save

  std::vector<double> maxis(hists[0].size(), FLT_MIN);
  std::vector<double> minis(hists[0].size(), FLT_MAX);

  for (size_t j=0; j<hists[0].size(); j++) {
    for (size_t i=0; i<hists.size(); i++) {
      if (hists[i][j]->GetEntries()==0) continue;
      TCanvas *c = new TCanvas(Form("%d_%d", int(i), int(j)), Form("%d_%d", int(i), int(j)), 600, 600);
      hists[i][j]->Draw();
      gPad->Update();
      if (save) c->SaveAs(Form("%s%s%s", save_dir.c_str(), hists[i][j]->GetName(),format));

      if (hists[i][j]->GetBinContent(hists[i][j]->GetMaximumBin()) > maxis[j]) maxis[j]=hists[i][j]->GetBinContent(hists[i][j]->GetMaximumBin());
      if (hists[i][j]->GetBinContent(hists[i][j]->GetMinimumBin()) < minis[j]) minis[j]=hists[i][j]->GetBinContent(hists[i][j]->GetMinimumBin());
    }
    std::cout<<"Plots like "<<hists[0][j]->GetName()<<" have overall minimums of "<<minis[j]<<" and maximum of "<<maxis[j]<<std::endl;
  }

  for (size_t j=0; j<hists[0].size(); j++) {
    std::string n=Form("%s", hists[0][j]->GetName());
    n.erase(n.find_last_of("_"));
    std::cout<<n<<std::endl;
    std::string t=Form("%s", hists[0][j]->GetTitle());
    t.erase(t.find_last_of(" in ")-6);
    std::cout<<t<<std::endl;

    TCanvas *c = new TCanvas(n.c_str(), t.c_str(), 600, 600);
    c->Draw();
    if (hists[0][j]->GetDimension()==1) hists[0][j]->SetAxisRange(minis[j], maxis[j]*1.1, "Y");
    TH1 *h = (TH1*) hists[0][j]->Clone("h");
    h->SetTitle(t.c_str());
    h->Draw();
    TLegend *l = new TLegend(0.55, 0.15, 0.89, 0.30, "Modules");
    l->SetLineColor(0);
    for (size_t i=1; i<hists.size(); i++) {
      if (hists[i][j]->GetEntries()==0) continue;
      hists[i][j]->Draw("SAME");
      l->AddEntry(hists[i][j], name(detids[i]).c_str());
      std::cout<<name(detids[i]).c_str()<<std::endl;
      gPad->Update();
    }
    l->Draw();
    if (save) c->SaveAs(Form("%sAll_%s%s", save_dir.c_str(), hists[0][j]->GetName(), format));
  }


//   TCanvas *c1, *c2, *c3, *c4, *c5, *c6, *c7, *c8, *c9, *c10;

//   new TCanvas("c0002"); 
//   for (size_t i=0; i<detids.size(); i++) PBADCDist[i]->Draw(i==0? "" :"SAME");

//   c1 = custom_can_(PBDigisMod[0], "PBDigisMapModAll", 0,0,     840,340, 80,100,     60,60,   13,0.1, 0.95);
//   for (size_t i=0; i<detids.size(); i++) PBDigisMod[i]->Draw(i==0? "" :"SAME");
//   //prelim_lat_(350,400,170,180, 2);
//   gPad->Update(); 
//   if (save) c1->SaveAs((save_dir+std::string(c1->GetName())+format).c_str());
  
//   c2 = custom_can_(PBDigiVsLS[0], "PBDigiVsLS", 0,0,     450,450, 80,80,     60,60,   13,0.1, 0.95);
//   for (size_t i=0; i<detids.size(); i++) PBDigiVsLS[i]->Draw(i==0? "" :"SAME");
//   //prelim_lat_(230,280,150,160, 2);
//   gPad->Update(); 
//   if (save) c2->SaveAs((save_dir+std::string(c2->GetName())+format).c_str());
  
//   new TCanvas("c3"); for (size_t i=0; i<detids.size(); i++) PBClusterCharge[i]->Draw(i==0? "" :"SAME");
//   new TCanvas("c4"); for (size_t i=0; i<detids.size(); i++) PBClusterSize[i]->Draw(i==0? "" :"SAME");
//   new TCanvas("c5"); for (size_t i=0; i<detids.size(); i++) PBClustersMod[i]->Draw(i==0? "" :"SAME");
//   new TCanvas("c6"); for (size_t i=0; i<detids.size(); i++) PBClusterChargeVsLS[i]->Draw(i==0? "" :"SAME");
//   new TCanvas("c7"); for (size_t i=0; i<detids.size(); i++) PBClusterSizeVsLS[i]->Draw(i==0? "" :"SAME");

//   c8 = custom_can_(PBClustersVsLS[0], "PBClustersVsLS", 0,0,     450,450, 80,80,     60,60,   13,0.1, 0.95);
//   for (size_t i=0; i<detids.size(); i++) PBClustersVsLS[i]->Draw(i==0? "" :"SAME");
//   prelim_lat_(230,280,150,160, 2);
//   gPad->Update(); 
//   if (save) c8->SaveAs((save_dir+std::string(c8->GetName())+format).c_str());

}

void plotScript() {
   digis();
}

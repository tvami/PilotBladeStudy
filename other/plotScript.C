//   Usage: 
//   .L plotScript.C
//   digis();
//   clusters();
//   rechits();

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
//#include "/data/vami/.scripts.d/custom_can_macro.C"

bool FileExists(char* filename) 
{
    struct stat fileInfo;
    return stat(filename, &fileInfo) == 0;
}


int delay(uint run, const uint ls) {
  int delay=-9999;
  //2016-04-23
  if (run==271056) {
    if (ls<58)  { delay=37; return delay; }
    if (ls<81)  { delay=12; return delay; }
    if (ls<110) { delay=-25; return delay;} // Get back to this point
    if (ls<223) { delay=49; return delay; }
    if (ls<263) { delay=37; return delay; }
    if (ls<306) { delay=25; return delay; }
  } 
  if (run==271084 || run==271087) { 
    delay=49; return delay; 
  } 
  //2016-04-24
  if (run==271136 || run==271142 || run==271143 || run==271144 || run==271151) {
    delay=49; return delay;
  }
  if (run==271153 || run==271155 || run==271161 || run==271167 || run==271168) {
    delay=49; return delay;
  }
  if (run==271169 || run==271170 || run==271176 || run==271177 || run==271188) {
    delay=49; return delay;
  }
  if (run==271191) {
    if (ls<55)  { delay=62; return delay; }
    if (ls<110) { delay=74; return delay; }
    else 	{ delay=87; return delay; }
  } 
  if (run==271192) {
    if (ls<46)  { delay=87; return delay; } 
    else        { delay=47; return delay; }
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
    if (ls<222) { delay=83; return delay; }
    else 	{ delay=79; return delay; }
  }
  if (run==271196) {
    if (ls<37)	{ delay=79; return delay; }
    if (ls<88)  { delay=77; return delay; }
    if (ls<127) { delay=70; return delay; }
    if (ls<168) { delay=68; return delay; }
    if (ls<204) { delay=66; return delay; }
    if (ls<238) { delay=64; return delay; }
    else 	{ delay=60; return delay; }
  }
  if (run==271197) {
    if (ls<5)	{ delay=49; return delay; }
    if (ls<38)	{ delay=60; return delay; }
    else 	{ delay=58; return delay; }
  }
  if (run==271214) {
    if (ls<51)	{ delay=58; return delay; }
    if (ls<94)	{ delay=56; return delay; }
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
  //2016-04-25
  if (run==271304) {
    if (ls<72) { delay=49; return delay; }
    else       { delay=54; return delay; }
  }
  if (run==271306) {
    if (ls<98)  { delay=54; return delay; }
    else 	{ delay=52; return delay; }
  }
  if (run==271307) {
  	//did not manage to be reconfigured, just 52ns.
    		  delay=52; return delay;
  }
  //if (run==271310) {
  //  if (ls<12) { delay=52; return delay; }
  //  else       { delay=49; return delay; }
  //}
  //2016-04-29
  if (run==272008 || run==272010 || run==272011) {
    delay=90; return delay;
  }
  if (run==272012 || run==272013 || run==272014) {
    delay=92; return delay;
  }
  if (run==272021) {
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
    else	{ delay=114; return delay;}
  }
  if (run==272022) {
   delay=62; return delay;
  }
  
  // CRAFT from here
  //if (run>272022) {
  // if (run<272000) { // need to check
  //    delay=90; return delay;
  //  }
  //  if (run<272150) {
  //    delay=62; return delay;
  // }
  //}
  // Timing Scan2
  if (run==274000 || run==274002 || run==274004 || run==274007 || run==274008 || run==274036 || run==274044 || run==274046 || run==274047 || run==274048 || run==274049 || run==274050 || run==274052 || run==274057 || run==274062 || run==274064 || run==274076 || run==274077) { 
    delay=62; return delay; }

  if (run==274079 || run==274080 || run==274081 || run==274083 || run==274086 || run==274087 || run==274088 || run==274089 || run==274090 || run==274091 || run==274093 || run==274094 || run==274096) { 
    delay=52; return delay; }

  if (run==274102 || run==274103 || run==274104 || run==274105 || run==274106 || run==274107) { 
    delay=45; return delay; }

  if (run==274108 || run==274113 || run==274114 || run==274115 || run==274122 || run==274123 || run==274132 || run==274133 || run==274134 || run==274135 
|| run==274138 || run==274139 || run==274141 || run==274142 || run==274146 || run==274147 || run==274148 || run==274149 || run==274150 || run==274151 || run==274152 
|| run==274154 || run==274155 || run==274156 || run==274157) { 
    delay=70; return delay; }

  if (run==274159 || run==274192 || run==274195 || run==274196 || run==274246 || run==274247 || run==274248 || run==274256 || run==274263 || run==274264 
|| run==274266 || run==274268 || run==274270 || run==274274 || run==274275 || run==274276 || run==274280 || run==274281 || run==274289 || run==274290 || run==274294 
|| run==274295 || run==274300 || run==274305 || run==274306 || run==274309 || run==274311 || run==274313 || run==274317 || run==274320 || run==274324 || run==274337 
|| run==274344 || run==274345 || run==274346 || run==274347 || run==274349 || run==274356 || run==274363 || run==274366 || run==274367 || run==274368 || run==274369 
|| run==274372 || run==274373 || run==274374 || run==274377 || run==274378 || run==274379 || run==274380 || run==274381 || run==274382 || run==274384 || run==274385) { 
    delay=82; return delay; }

  if (run==274386 || run==274387) { 
    delay=45; return delay; }

  if (run==274391 || run==274392 || run==274393 || run==274394 || run==274396 || run==274398 || run==274401 || run==274402 || run==274414 || run==274415 || run==274417 || run==274418 || run==274419 || run==274420 || run==274421) { 
    delay=50; return delay; }

  if (run==274422) { 
    delay=56; return delay; }

  if (run==274424 || run==274425 || run==274430 || run==274433 || run==274436 || run==274437 || run==274438 || run==274439) { 
    delay=60; return delay; }

  if (run==274440) { 
    delay=60; return delay; }
  if (run==274441 || run==274442) { 
    delay=65; return delay; }
  if (run==274443 || run==274444) { 
    delay=70; return delay; }
  

  if (run==274445 || run==274446 || run==274448 || run==274449 || run==274450 || run==274452 || run==274455 || run==274463 || run==274468 || run==274469 || run==274470 || run==274471 || run==274495 || run==274503 || run==274505 || run==274506 || run==274507 || run==274508 || run==274510 || run==274512 || run==274516 || run==274517 || run==274569 || run==274718 || run==274720 || run==274722 || run==274724 || run==274726 || run==274728 || run==274733 || run==274743 || run==274744 || run==274746 || run==274748 || run==274749 || run==274758 || run==274771 || run==274774 || run==274775 || run==274776 || run==274777 || run==274778 || run==274779 || run==274780 || run==274781 || run==274783 || run==274784 || run==274785 || run==274799 || run==274802 || run==274804 || run==274806 || run==274810 || run==274813 || run==274814 || run==274815 || run==274817 || run==274850 || run==274856 || run==274861 || run==274864 || run==274866 || run==274868 || run==274869 || run==274873 || run==274875 || run==274877 || run==274878 || run==274879 || run==274880 || run==274881 || run==274883 || run==274885 || run==274887 || run==274888 || run==274939 || run==274940 || run==274941 || run==274942 || run==274943 || run==274944 || run==274945 || run==274947 || run==274948 || run==274950 || run==274951 || run==274953 || run==274954) { 
    delay=40; return delay; }

  if (run==279071 || run==279072 || run==279073) { 
    delay=49; return delay; }
// WBC=163. Globaldelay25=24ns

  if (run==279853 || run==279854 || run==279855 || run==279856 || run==279857 || run==279858 || run==279859 || run==279860 || run==279861 || run==279862 || run==279864) { 
    delay=124; return delay; }
// this above is not true.... the truth is: WBC moved 3 BX for BmI module and 4 BX for BmO modules.

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
  // Disk2
  if (detid==344081668) return std::string("FPix_BmO_D2_BLD11_PNL1_MOD1");
  if (detid==344081672) return std::string("FPix_BmO_D2_BLD11_PNL1_MOD2");
  if (detid==344081676) return std::string("FPix_BmO_D2_BLD11_PNL1_MOD3");
  if (detid==344081680) return std::string("FPix_BmO_D2_BLD11_PNL1_MOD4");
  
  if (detid==1) return std::string("FPix_BmO_D2_BLD10+11");
  return std::string("");
}

void digis(bool saveAll, std::string save_dir, const char* format, TChain* filechain)
{
 
  bool saveDigis = 0;
  if (saveAll) saveDigis = 1;
  Int_t selectDelay=-9999;
  Long64_t reduceFraction=0;
  Int_t skipFiles=0;

  int _detids[] = { 344132868, 344134148, 344131076, 344132100, 344130820, 1 };
  //int _detids[] = { 344130820, 344131844, 344132868, 344133892, 344131076, 344132100, 344133124, 344134148 };
  std::vector<int> detids(_detids, _detids + sizeof(_detids) / sizeof(int) );

  std::map<int,int> idx_map;
  for (size_t i=0; i<detids.size(); i++) {
    idx_map[detids[i]]=i;
    cout << "define detector id " << detids[i] << " as " << idx_map[detids[i]]<<std::endl;
  }
  const std::map<int,int>& idx = idx_map;
  
// Create the histograms
  std::vector<std::vector<TH1*> > hists;

  std::vector<TH1F *> PBADCDist;
  std::vector<TH2F *> PBDigisMod;
  //std::vector<TProfile *> PBDigiVsLS;
  
 
  for (size_t imod=0; imod<detids.size(); imod++) {

    std::vector<TH1*> vh;
    TH1 *h;

    PBADCDist.push_back((TH1F*)(h=new TH1F(Form("PBADCDist_%d", detids[imod]), Form("ADC Distribution in %s ;ADC;Yield", name(detids[imod]).c_str()), 50,0.,250.))); vh.push_back(h);
    PBDigisMod.push_back((TH2F*)(h=new TH2F(Form("PBDigisMod_%d", detids[imod]), Form("Pixels in %s ;columns [pixels];rows [pixels]", name(detids[imod]).c_str()),      416,0,416.0,      160,0,160.0))); vh.push_back(h);
    //PBDigiVsLS.push_back((TProfile*)(h=new TProfile(Form("PBDigiVsLS_%d", detids[imod]),  Form("Avg num of pixels per event vs LumiSection in %s;LumiSection;Avg num of pixels", name(detids[imod]).c_str()), 150, 0, 150, 0, 100))); vh.push_back(h);
    
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

  DigiData digi;
  ModuleData module_on;
  EventData evt;
  ClustData clusters;
  TrajMeasData traj;

  TObjArray* fileElements = filechain->GetListOfFiles();
  TIter next(fileElements);
  TChainElement* chEl=0;
  Int_t fileCounter=0;
  
  while (( chEl=(TChainElement*)next() )) {
    fileCounter++;
    if ((skipFiles!=0) && (fileCounter%skipFiles!=0)) continue;
    TFile f(chEl->GetTitle());
    std::cout << "Opening "<<chEl->GetTitle()<<std::endl;

// ---------------------- Digis ---------------------- 

    TTree* digiTree = (TTree*)f.Get("digiTree");
    digiTree->GetBranch("digi")->SetAddress(&digi);
    digiTree->GetBranch("module_on")->SetAddress(&module_on);
    digiTree->GetBranch("event")->SetAddress(&evt);

    std::vector<int> currentEvent(detids.size(), -1);
    std::vector<std::pair<int,int> > currentRunLs;
    for (size_t ii=0; ii<currentEvent.size(); ii++) currentRunLs.push_back(std::make_pair(-1, -1));
    std::vector<int> digiCounter(detids.size(), 0);

    for (Long64_t i=0, ndigi=digiTree->GetEntries(); i<ndigi; ++i) {
      if (reduceFraction!=0 && i%reduceFraction!=0) continue;
      digiTree->GetEntry(i);
      int del=delay(evt.run, evt.ls);
      if (del==-9999) continue; 
      if (selectDelay!=-9999 && del!=selectDelay) continue;

      if (module_on.disk!=-3 && !(module_on.disk==-2 && (module_on.blade==-10 || module_on.blade==-11)) ) continue;

      //int run=evt.run-271056;
      //if (run>28) run-=100;
      //Int_t ls=(evt.ls/10)+run*100;

      int rawid=module_on.rawid;
      if (module_on.disk==-2) rawid=1;
      
      std::map<int,int>::const_iterator it_idx=idx.find(rawid);
      if (it_idx==idx.end()) continue;
      int imod = it_idx->second;

      PBADCDist[imod]->Fill(digi.adc);
      PBDigisMod[imod]->Fill(digi.col,digi.row);

      //if (evt.evt!=currentEvent[imod]) {
	//	if (currentEvent[imod]!=-1) PBDigiVsLS[imod]->Fill(ls, digiCounter[imod]);
	//	currentEvent[imod]=evt.evt;
	//	digiCounter[imod]=0;
    // }
      ++digiCounter[imod];
    }

    // ---------------------- Events ---------------------- 
    TTree* eventTree = (TTree*)f.Get("eventTree");
    eventTree->GetBranch("event")->SetAddress(&evt_);

    for (Long64_t i=0; i<eventTree->GetEntries(); i++) {
      if (reduceFraction!=0 && i%reduceFraction!=0) continue;
      eventTree->GetEntry(i);
      int del=delay(evt.run, evt.ls);
      if (del==-9999) continue; 
      if (selectDelay!=-9999 && del!=selectDelay) continue;
    }

    
// -------------------------------------------- 
  } // End of loop on files
  
  // Create the canvas and save

  for (size_t j=0; j<hists[0].size(); j++) { // loop on plots
    for (size_t i=0; i<hists.size(); i++) { // loop on modules
      if (hists[i][j]->GetEntries()==0) continue;
      TCanvas *c = new TCanvas(Form("c%d_%d", int(i), int(j)), Form("%d_%d", int(i), int(j)), 600, 600);
      hists[i][j]->Draw();
      gPad->Update();
      if (saveDigis) {
	c->SaveAs(Form("%s%s%s", save_dir.c_str(), hists[i][j]->GetName(),format));
	c->SaveAs(Form("%s%s%s", save_dir.c_str(), hists[i][j]->GetName(),".C"));
      }
    }
  }

  std::vector<double> maxis(hists[0].size(), FLT_MIN);
  std::vector<double> minis(hists[0].size(), FLT_MAX);

  for (size_t j=0; j<hists[0].size(); j++) { // loop on plots
    for (size_t i=0; i<hists.size(); i++) { // loop on modules
      if (detids[i]<300000000) continue;
      if (hists[i][j]->GetEntries()==0) continue;
      if (hists[i][j]->GetBinContent(hists[i][j]->GetMaximumBin()) > maxis[j]) maxis[j]=hists[i][j]->GetBinContent(hists[i][j]->GetMaximumBin());
      if (hists[i][j]->GetBinContent(hists[i][j]->GetMinimumBin()) < minis[j]) minis[j]=hists[i][j]->GetBinContent(hists[i][j]->GetMinimumBin());
    }
    std::cout<<"Plots like "<<hists[0][j]->GetName()<<" have overall minimums of "<<minis[j]<<" and maximum of "<<maxis[j]<<std::endl;
  }

  for (size_t j=0; j<hists[0].size(); j++) { // loop on plots
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
    h->Reset();
    h->SetTitle(t.c_str());
    h->Draw();
    //TLegend *l = new TLegend(0.55, 0.15, 0.89, 0.30, "Modules");
    TLegend *l = new TLegend(0.15, 0.70, 0.49, 0.85, "Modules");
    l->SetLineColor(0);
    for (size_t i=0; i<hists.size(); i++) { // loop on modules
      if (detids[i]<300000000) continue;
      if (hists[i][j]->GetEntries()==0) continue;
      if (hists[0][j]->GetDimension()==1) {
	hists[i][j]->Draw("SAMEP");
      } else hists[i][j]->Draw("SAME");
      l->AddEntry(hists[i][j], name(detids[i]).c_str());
      std::cout<<name(detids[i]).c_str()<<std::endl;
      gPad->Update();
    }
    l->Draw();
    if (saveDigis) {
	c->SaveAs(Form("%s%s%s", save_dir.c_str(), hists[0][j]->GetName(),format));
	c->SaveAs(Form("%s%s%s", save_dir.c_str(), hists[0][j]->GetName(),".C"));
    }
  }
}
// ---------------------------------------------------------------------------
// -----------------------------Clusters--------------------------------------
// ---------------------------------------------------------------------------
void clusters(bool saveAll, std::string save_dir, const char* format, TChain* filechain)
{
  bool saveClusters = 0;
  if (saveAll) saveClusters = 1;
  Int_t selectDelay=-9999;
  Long64_t reduceFraction=0;
  Int_t skipFiles=0;

  int _detids[] = { 344132868, 344134148, 344131076, 344132100, 344130820, 1 };
  //int _detids[] = { 344130820, 344131844, 344132868, 344133892, 344131076, 344132100, 344133124, 344134148 };
  std::vector<int> detids(_detids, _detids + sizeof(_detids) / sizeof(int) );

  std::map<int,int> idx_map;
  for (size_t i=0; i<detids.size(); i++) {
    idx_map[detids[i]]=i;
    cout << "define detector id " << detids[i] << " as " << idx_map[detids[i]]<<std::endl;
  }
  const std::map<int,int>& idx = idx_map;
  
// Create the histograms
  std::vector<std::vector<TH1*> > hists;

  std::vector<TH1F *> PBClusterCharge;
  std::vector<TH1F *> PBClusterSize;
  std::vector<TH2F *> PBClustersMod;
  std::vector<TH2F *> PBClustersGlobal;

  //std::vector<TProfile *> PBClusterChargeVsLS;
  //std::vector<TProfile *> PBClusterSizeVsLS;
  //std::vector<TProfile *> PBClustersVsLS;

  std::vector<TProfile *> PBClusterChargeVsDel;
  std::vector<TProfile *> PBClusterSizeVsDel;
  std::vector<TProfile *> PBClustersVsDel;

  std::vector<TH1F *> PBClustersVsDel_num;
  std::vector<TH1F *> PBClustersVsDel_den;

  std::vector<TH1F *> PBClusterFEDErrVsDel;
  std::vector<TH1F *> PBClusterFEDErrType;
  std::vector<TH1F *> PBClusterFEDErrTypePerEvent;
  
 
  for (size_t imod=0; imod<detids.size(); imod++) {

    std::vector<TH1*> vh;
    TH1 *h;

    PBClusterCharge.push_back((TH1F*)(h=new TH1F(Form("PBClusterCharge_%d", detids[imod]),  Form("Clusters Charge Distribution in  %s;Cluster charge [ke];Yield", name(detids[imod]).c_str()), 150,0,150))); vh.push_back(h);
    PBClusterSize.push_back((TH1F*)(h=new TH1F(Form("PBClusterSize_%d", detids[imod]), Form( "Clusters Size Distribution in %s;Cluster size [pixel];Yield", name(detids[imod]).c_str()), 10,0,10))); vh.push_back(h);
    PBClustersMod.push_back((TH2F*)(h=new TH2F(Form("PBClustersMod_%d", detids[imod]), Form("Clusters in %s;x;y", name(detids[imod]).c_str()),      416,0,416,      160,0,160.0))); vh.push_back(h);
    PBClustersGlobal.push_back((TH2F*)(h=new TH2F(Form("PBClustersGlobal_%d", detids[imod]), Form("Clusters in %s;x;y", name(detids[imod]).c_str()), 3200,-16,16, 3200,-16,16))); vh.push_back(h);

    //PBClusterChargeVsLS.push_back((TProfile*)(h=new TProfile(Form("PBClusterChargeVsLS_%d", detids[imod]),  Form("Avg cluster charge vs LumiSection in %s;LumiSection;Avg cluster charge", name(detids[imod]).c_str()), 5900, 0, 5900, 0, 150))); vh.push_back(h);
    //PBClusterSizeVsLS.push_back((TProfile*)(h=new TProfile(Form("PBClusterSizeVsLS_%d", detids[imod]),  Form("Avg cluster size vs LumiSection in %s;LumiSection;Avg cluster size", name(detids[imod]).c_str()), 5900, 0, 5900, 0, 15))); vh.push_back(h);
    //PBClustersVsLS.push_back((TProfile*)(h=new TProfile(Form("PBClustersVsLS_%d", detids[imod]),  Form("Avg num of clusters per event vs LumiSection in %s;LumiSection;Avg num of clusters", name(detids[imod]).c_str()), 5900, 0, 5900, 0, 100))); vh.push_back(h);

    PBClusterChargeVsDel.push_back((TProfile*)(h=new TProfile(Form("PBClusterChargeVsDel_%d", detids[imod]),  Form("Avg cluster charge vs Delay in %s;Delay;Avg cluster charge", name(detids[imod]).c_str()), 150, -30, 120, 0, 150))); vh.push_back(h);
    PBClusterSizeVsDel.push_back((TProfile*)(h=new TProfile(Form("PBClusterSizeVsDel_%d", detids[imod]),  Form("Avg cluster size vs Delay in %s;Delay;Avg cluster size", name(detids[imod]).c_str()), 150, -30, 120, 0, 15))); vh.push_back(h);
    PBClustersVsDel.push_back((TProfile*)(h=new TProfile(Form("PBClustersVsDel_%d", detids[imod]),  Form("Avg num of clusters per event vs Delay in %s;Delay;Avg num of clusters", name(detids[imod]).c_str()), 150, -30, 120, 0, 100))); vh.push_back(h);

    PBClustersVsDel_num.push_back((TH1F*)(h=new TH1F(Form("PBClustersVsDel_num_%d", detids[imod]),  Form("Avg num of clusters per event vs Delay in %s;Delay;Avg num of clusters", name(detids[imod]).c_str()), 150, -30, 120))); vh.push_back(h);
    PBClustersVsDel_den.push_back((TH1F*)(h=new TH1F(Form("PBClustersVsDel_den_%d", detids[imod]),  Form("Total number of events vs Delay in %s;Delay;num of events", name(detids[imod]).c_str()), 150, -30, 120))); vh.push_back(h);

    PBClusterFEDErrVsDel.push_back((TH1F*)(h=new TH1F(Form("PBClusterFEDErrVsDel_%d", detids[imod]),  Form("Fraction of clusters with FED error vs Delay in %s;Delay;Clusters with FED err", name(detids[imod]).c_str()), 150, -30, 120))); vh.push_back(h);
    PBClusterFEDErrType.push_back((TH1F*)(h=new TH1F(Form("PBClusterFEDErrType_%d", detids[imod]),  Form("Fraction of clusters with FED error vs Error type in %s;Error type;Cluster fraction", name(detids[imod]).c_str()), 16, 24.5, 40.5))); vh.push_back(h);    
    PBClusterFEDErrTypePerEvent.push_back((TH1F*)(h=new TH1F(Form("PBClusterFEDErrTypePerEvent_%d", detids[imod]),  Form("Fraction of events with FED error vs Error type in %s;Error type;Event fraction", name(detids[imod]).c_str()), 16, 24.5, 40.5))); vh.push_back(h);    
    
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

  DigiData digi;
  ModuleData module_on;
  EventData evt;
  ClustData clusters;
  TrajMeasData traj;
  
  int eventNumber = 0;

  TObjArray* fileElements = filechain->GetListOfFiles();
  TIter next(fileElements);
  TChainElement* chEl=0;
  Int_t fileCounter=0;
  
  while (( chEl=(TChainElement*)next() )) {
    fileCounter++;
    if ((skipFiles!=0) && (fileCounter%skipFiles!=0)) continue;
    TFile f(chEl->GetTitle());
    TTree* clustTree = (TTree*)f.Get("clustTree");
    clustTree->GetBranch("clust")->SetAddress(&clusters);
    clustTree->GetBranch("module_on")->SetAddress(&module_on);
    clustTree->GetBranch("event")->SetAddress(&evt);

    std::vector<int> currentEvent(detids.size(), -1);
    std::vector<std::pair<int,int> > currentRunLs;
    for (size_t ii=0; ii<currentEvent.size(); ii++) currentRunLs.push_back(std::make_pair(-1, -1));
    for (size_t i=0; i<currentEvent.size(); i++) currentEvent[i]=-1;
    std::vector<int> clusterCounter(detids.size(), 0);
    for (Long64_t i=0, nclust=clustTree->GetEntries(); i<nclust; ++i) {
      if (reduceFraction!=0 && i%reduceFraction!=0) continue;
      clustTree->GetEntry(i);
      int del=delay(evt.run, evt.ls);
      if (del==-9999) continue; 
      if (selectDelay!=-9999 && del!=selectDelay) continue;

      //if (evt.run>=272008) continue;

      if (module_on.disk!=-3 && !(module_on.disk==-2 && (module_on.blade==-10 || module_on.blade==-11)) ) continue;
      int run=evt.run-271056;
      if (run>28) run-=100;
      Int_t ls=(evt.ls/10)+run*100;

      int rawid=module_on.rawid;
      if (module_on.disk==-2) rawid=1;
      
      std::map<int,int>::const_iterator it_idx=idx.find(rawid);
      if (it_idx==idx.end()) continue;
      int imod = it_idx->second;
      // if we want the disk2 modules before the PB then include:
      // if((module_on.disk==-3) || (module_on.disk==-2 && module_on.blade==-11) ) {
      PBClusterCharge[imod]->Fill(clusters.charge);
      PBClusterSize[imod]->Fill(clusters.size);
      PBClustersMod[imod]->Fill(clusters.y,clusters.x);   
      //PBClusterChargeVsLS[imod]->Fill(ls,clusters.charge);
      //PBClusterSizeVsLS[imod]->Fill(ls,clusters.size);
      PBClusterChargeVsDel[imod]->Fill(delay(evt.run, evt.ls),clusters.charge);
      PBClusterSizeVsDel[imod]->Fill(delay(evt.run, evt.ls),clusters.size);
      PBClustersGlobal[imod]->Fill(clusters.glx, clusters.gly);
      if (module_on.federr!=0) {
	PBClusterFEDErrVsDel[imod]->Fill(delay(evt.run, evt.ls));
	PBClusterFEDErrType[imod]->Fill(module_on.federr);
	PBClusterFEDErrTypePerEvent[imod]->Fill(module_on.federr);
      }
      if (evt.evt!=currentEvent[imod]) {
		if (currentEvent[imod]!=-1) {
		  std::map<int,int>::const_iterator it_idx=idx.find(1);
		  if (it_idx!=idx.end() && clusterCounter[it_idx->second]>0) { // If there was hit in FPix Disk 2 in the event
			for (size_t ii=0; ii<currentEvent.size(); ii++) {
			  //PBClustersVsLS[ii]->Fill(currentRunLs[ii].second, clusterCounter[ii]);
			  PBClustersVsDel[ii]->Fill(delay(currentRunLs[ii].first, currentRunLs[ii].second), clusterCounter[ii]); // counts the clusters for 0-suppressed TProfile
			  if (ii!=it_idx->second) PBClustersVsDel_num[ii]->Fill(delay(currentRunLs[ii].first, currentRunLs[ii].second), clusterCounter[ii]/clusterCounter[it_idx->second]); // counts fraction of clusters in PB w.r.t FPix, to be divided by all events with FPix clusters
			  else PBClustersVsDel_num[ii]->Fill(delay(currentRunLs[ii].first, currentRunLs[ii].second), 1); // all events with FPix clusters
			  //printf("run %d (%d), ls %d (%d), evt %d (%d), %s, num of clu %d, num of ref clu %d\n", currentRunLs[ii].first, evt.run, currentRunLs[ii].second, evt.ls, currentEvent[ii], evt.evt, name(_detids[ii]).c_str(), clusterCounter[ii], clusterCounter[it_idx->second]);
			}
		  }
		}
		for (size_t ii=0; ii<currentEvent.size(); ii++) {
		  currentEvent[ii]=evt.evt;
	      currentRunLs[ii].first=evt.run;
	      currentRunLs[ii].second=evt.ls;
	      clusterCounter[ii]=0;
		}
      }
      ++clusterCounter[imod];  
    }

    // ---------------------- Events ---------------------- 
    TTree* eventTree = (TTree*)f.Get("eventTree");
    eventTree->GetBranch("event")->SetAddress(&evt_);
    eventNumber = eventTree->GetEntries();
    for (Long64_t i=0; i<eventTree->GetEntries(); i++) {
      if (reduceFraction!=0 && i%reduceFraction!=0) continue;
      eventTree->GetEntry(i);
      int del=delay(evt.run, evt.ls);
      if (del==-9999) continue; 
      if (selectDelay!=-9999 && del!=selectDelay) continue;

      //if (evt.run>=272008) continue;

      for (size_t imod=0; imod<detids.size(); imod++) {
	PBClustersVsDel_den[imod]->Fill(delay(evt_.run, evt_.ls));
      }
    }


// -------------------------------------------- 
  } // End of loop on files

   // Compute averages / efficiencies
  {
    std::map<int,int>::const_iterator it_idx=idx.find(1);
    for (size_t imod=0; imod<detids.size(); imod++) {
      if (it_idx!=idx.end() && imod!=it_idx->second) PBClustersVsDel_num[imod]->Divide(PBClustersVsDel_num[it_idx->second]); //average ratio of PB clusters to FPix clusters in events with FPix clusters
      //PBHitEffVsDel_num[imod]->Divide(PBHitEffVsDel_den[imod]);
      
      PBClusterFEDErrVsDel[imod]->Scale(1./PBClusterCharge[imod]->GetEntries());
      PBClusterFEDErrType[imod]->Scale(1./PBClusterCharge[imod]->GetEntries());
      PBClusterFEDErrTypePerEvent[imod]->Scale(1./eventNumber);
      
    }
    if (it_idx!=idx.end()) PBClustersVsDel_num[it_idx->second]->Divide(PBClustersVsDel_den[it_idx->second]); // fraction of events with FPix clusters in all events
  }
  // Create the canvas and save

  for (size_t j=0; j<hists[0].size(); j++) { // loop on plots
    for (size_t i=0; i<hists.size(); i++) { // loop on modules
      if (hists[i][j]->GetEntries()==0) continue;
      TCanvas *c = new TCanvas(Form("c%d_%d", int(i), int(j)), Form("%d_%d", int(i), int(j)), 600, 600);
      hists[i][j]->Draw();
      gPad->Update();
      if (saveClusters) {
	c->SaveAs(Form("%s%s%s", save_dir.c_str(), hists[i][j]->GetName(),format));
	c->SaveAs(Form("%s%s%s", save_dir.c_str(), hists[i][j]->GetName(),".C"));
      }
    }
  }

  std::vector<double> maxis(hists[0].size(), FLT_MIN);
  std::vector<double> minis(hists[0].size(), FLT_MAX);

  for (size_t j=0; j<hists[0].size(); j++) { // loop on plots
    for (size_t i=0; i<hists.size(); i++) { // loop on modules
      if (detids[i]<300000000) continue;
      if (hists[i][j]->GetEntries()==0) continue;
      if (hists[i][j]->GetBinContent(hists[i][j]->GetMaximumBin()) > maxis[j]) maxis[j]=hists[i][j]->GetBinContent(hists[i][j]->GetMaximumBin());
      if (hists[i][j]->GetBinContent(hists[i][j]->GetMinimumBin()) < minis[j]) minis[j]=hists[i][j]->GetBinContent(hists[i][j]->GetMinimumBin());
    }
    std::cout<<"Plots like "<<hists[0][j]->GetName()<<" have overall minimums of "<<minis[j]<<" and maximum of "<<maxis[j]<<std::endl;
  }

  for (size_t j=0; j<hists[0].size(); j++) { // loop on plots
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
    h->Reset();
    h->SetTitle(t.c_str());
    h->Draw();
    //TLegend *l = new TLegend(0.55, 0.15, 0.89, 0.30, "Modules");
    TLegend *l = new TLegend(0.15, 0.70, 0.49, 0.85, "Modules");
    l->SetLineColor(0);
    for (size_t i=0; i<hists.size(); i++) { // loop on modules
      if (detids[i]<300000000) continue;
      if (hists[i][j]->GetEntries()==0) continue;
      if (hists[0][j]->GetDimension()==1) {
	hists[i][j]->Draw("SAMEP");
      } else hists[i][j]->Draw("SAME");
      l->AddEntry(hists[i][j], name(detids[i]).c_str());
      std::cout<<name(detids[i]).c_str()<<std::endl;
      gPad->Update();
    }
    l->Draw();
    if (saveClusters) {
      //c->SaveAs(Form("%sAll_%s%s", save_dir.c_str(), hists[0][j]->GetName(), format));
      //c->SaveAs(Form("%sAll_%s%s", save_dir.c_str(), hists[0][j]->GetName(), ".C"));
	  c->SaveAs(Form("%sAll_%s%s", save_dir.c_str(), n.c_str(), format));
      c->SaveAs(Form("%sAll_%s%s", save_dir.c_str(), n.c_str(), ".C"));
    }
  }
}
// ---------------------------------------------------------------------------
// -----------------------------Rechits---------------------------------------
// ---------------------------------------------------------------------------

void rechits(bool saveAll, std::string save_dir, const char* format, TChain* filechain)
{
  bool saveRecHits = 0;
  if (saveAll) saveRecHits = 1;
  Int_t selectDelay=-9999;
  Long64_t reduceFraction=0;
  Int_t skipFiles=0;

  int _detids[] = { 344132868, 344134148, 344131076, 344132100, 344130820, 1 };
  //int _detids[] = { 344130820, 344131844, 344132868, 344133892, 344131076, 344132100, 344133124, 344134148 };
  std::vector<int> detids(_detids, _detids + sizeof(_detids) / sizeof(int) );

  std::map<int,int> idx_map;
  for (size_t i=0; i<detids.size(); i++) {
    idx_map[detids[i]]=i;
    cout << "define detector id " << detids[i] << " as " << idx_map[detids[i]]<<std::endl;
  }
  const std::map<int,int>& idx = idx_map;
  
  // Create the histograms
  std::vector<std::vector<TH1*> > hists;

  std::vector<TH2F *> PBHitsGlobal;
  std::vector<TH1F *> PBHitCluDx;
  std::vector<TH1F *> PBHitCluDy;

  std::vector<TH1F *> PBHitEffVsDel_num;
  std::vector<TH1F *> PBHitEffVsDel_den;

  std::vector<TH1F *> PBClustersVsDel_num;
  std::vector<TH1F *> PBClustersVsDel_den;
 
  for (size_t imod=0; imod<detids.size(); imod++) {

    std::vector<TH1*> vh;
    TH1 *h;

    PBHitsGlobal.push_back((TH2F*)(h=new TH2F(Form("PBHitsGlobal_%d", detids[imod]), Form("RecHits in %s;x;y", name(detids[imod]).c_str()), 3200,-16,16, 3200,-16,16))); vh.push_back(h);
    PBHitCluDx.push_back((TH1F*)(h=new TH1F(Form("PBHitCluDx_%d", detids[imod]),  Form("Rechit to nearest cluster distance in %s;dx [cm];Yield", name(detids[imod]).c_str()), 400,-2,2))); vh.push_back(h);
    PBHitCluDy.push_back((TH1F*)(h=new TH1F(Form("PBHitCluDy_%d", detids[imod]),  Form("Rechit to nearest cluster distance in %s;dy [cm];Yield", name(detids[imod]).c_str()), 1000,-7,3))); vh.push_back(h);
    
    PBHitEffVsDel_num.push_back((TH1F*)(h=new TH1F(Form("PBHitEffVsDel_num_%d", detids[imod]),  Form("RecHit efficiency vs Delay in %s;Delay;Efficiency", name(detids[imod]).c_str()), 150, -30, 120))); vh.push_back(h);
    PBHitEffVsDel_den.push_back((TH1F*)(h=new TH1F(Form("PBHitEffVsDel_den_%d", detids[imod]),  Form("Num of RecHits vs Delay in %s;Delay;Num of hits", name(detids[imod]).c_str()), 150, -30, 120))); vh.push_back(h);
    //PBClustersVsDel_num.push_back((TH1F*)(h=new TH1F(Form("PBClustersVsDel_num_%d", detids[imod]),  Form("Avg num of clusters per event vs Delay in %s;Delay;Avg num of clusters", name(detids[imod]).c_str()), 150, -30, 120))); vh.push_back(h);
    //PBClustersVsDel_den.push_back((TH1F*)(h=new TH1F(Form("PBClustersVsDel_den_%d", detids[imod]),  Form("Total number of events vs Delay in %s;Delay;num of events", name(detids[imod]).c_str()), 150, -30, 120))); vh.push_back(h);
    
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

  DigiData digi;
  ModuleData module_on;
  EventData evt;
  ClustData clusters;
  TrajMeasData traj;

  TObjArray* fileElements = filechain->GetListOfFiles();
  TIter next(fileElements);
  TChainElement* chEl=0;
  Int_t fileCounter=0;
  
  while (( chEl=(TChainElement*)next() )) {
    fileCounter++;
    if ((skipFiles!=0) && (fileCounter%skipFiles!=0)) continue;
    TFile f(chEl->GetTitle());
    TTree* clustTree = (TTree*)f.Get("clustTree");
    TTree* trajTree = (TTree*)f.Get("trajTree");

    trajTree->GetBranch("traj")->SetAddress(&traj);
    trajTree->GetBranch("module_on")->SetAddress(&module_on);
    trajTree->GetBranch("event")->SetAddress(&evt);

    for (Long64_t i=0, ntraj=trajTree->GetEntries(); i<ntraj; ++i) {
      if (reduceFraction!=0 && i%reduceFraction!=0) continue;
      trajTree->GetEntry(i);
      int del=delay(evt.run, evt.ls);
      if (del==-9999) continue; 
      if (selectDelay!=-9999 && del!=selectDelay) continue;


      //if (evt.run>=272008) continue;

      if (module_on.disk!=-3 && !(module_on.disk==-2 && (module_on.blade==-10 || module_on.blade==-11)) ) continue;
      int rawid=module_on.rawid;
      if (module_on.disk==-2) rawid=1;
      
      std::map<int,int>::const_iterator it_idx=idx.find(rawid);
      if (it_idx==idx.end()) continue;
      if (traj.onEdge==1&&traj.type!=102) continue;
      int imod = it_idx->second;

      // Correction to cluster positions  344132868, 344134148, 344131076, 344132100, 344130820
	  //if (traj.type==102) continue;
      float dx_cl = traj.dx_cl;
      float dy_cl = traj.dy_cl;

//        if (module_on.rawid==344132868) {
// 	 	dx_cl+=0.0908;
// 	 	dy_cl+=0.8332;	
//        } else if (module_on.rawid==344134148) {
// 		//dx_cl = -traj.dx_cl - traj.lx*2+0.07385;
// 	 	dx_cl+=0.0537;
// 	 	dy_cl+=0.9192;	
//        } else if (module_on.rawid==344131076) {
// 	 	dx_cl+=0.0486;
// 	 	dy_cl-=0.1885;
//        } 


      if (evt.federrs_size==0 && module_on.federr==0) {
	PBHitEffVsDel_den[imod]->Fill(delay(evt.run, evt.ls));
	if (fabs(dx_cl)<0.05 && fabs(dy_cl)<0.05) PBHitEffVsDel_num[imod]->Fill(delay(evt.run, evt.ls));
	PBHitsGlobal[imod]->Fill(traj.glx, traj.gly);
	PBHitCluDx[imod]->Fill(dx_cl);
	PBHitCluDy[imod]->Fill(dy_cl);
      }

    }

    // ---------------------- Events ---------------------- 
    TTree* eventTree = (TTree*)f.Get("eventTree");
    eventTree->GetBranch("event")->SetAddress(&evt_);

    for (Long64_t i=0; i<eventTree->GetEntries(); i++) {
      if (reduceFraction!=0 && i%reduceFraction!=0) continue;
      eventTree->GetEntry(i);
      int del=delay(evt.run, evt.ls);
      if (del==-9999) continue; 
      if (selectDelay!=-9999 && del!=selectDelay) continue;
    }


// -------------------------------------------- 
  } // End of loop on files

   // Compute averages / efficiencies
  {
    std::map<int,int>::const_iterator it_idx=idx.find(1);
    for (size_t imod=0; imod<detids.size(); imod++) {
      //if (it_idx!=idx.end() && imod!=it_idx->second) PBClustersVsDel_num[imod]->Divide(PBClustersVsDel_num[it_idx->second]); //average ratio of PB clusters to FPix clusters in events with FPix clusters
      PBHitEffVsDel_num[imod]->Divide(PBHitEffVsDel_den[imod]);
    }
    //if (it_idx!=idx.end()) PBClustersVsDel_num[it_idx->second]->Divide(PBClustersVsDel_den[it_idx->second]); // fraction of events with FPix clusters in all events
  }
  // Create the canvas and save

  for (size_t j=0; j<hists[0].size(); j++) { // loop on plots
    for (size_t i=0; i<hists.size(); i++) { // loop on modules
      if (hists[i][j]->GetEntries()==0) continue;
      TCanvas *c = new TCanvas(Form("c%d_%d", int(i), int(j)), Form("%d_%d", int(i), int(j)), 600, 600);
      hists[i][j]->Draw();
      gPad->Update();
      if (saveRecHits) {
		c->SaveAs(Form("%s%s%s", save_dir.c_str(), hists[i][j]->GetName(),format));
		c->SaveAs(Form("%s%s%s", save_dir.c_str(), hists[i][j]->GetName(),".C"));
      }
    }
  }

  std::vector<double> maxis(hists[0].size(), FLT_MIN);
  std::vector<double> minis(hists[0].size(), FLT_MAX);

  for (size_t j=0; j<hists[0].size(); j++) { // loop on plots
    for (size_t i=0; i<hists.size(); i++) { // loop on modules
      if (detids[i]<300000000) continue;
      if (hists[i][j]->GetEntries()==0) continue;
      if (hists[i][j]->GetBinContent(hists[i][j]->GetMaximumBin()) > maxis[j]) maxis[j]=hists[i][j]->GetBinContent(hists[i][j]->GetMaximumBin());
      if (hists[i][j]->GetBinContent(hists[i][j]->GetMinimumBin()) < minis[j]) minis[j]=hists[i][j]->GetBinContent(hists[i][j]->GetMinimumBin());
    }
    std::cout<<"Plots like "<<hists[0][j]->GetName()<<" have overall minimums of "<<minis[j]<<" and maximum of "<<maxis[j]<<std::endl;
  }

  for (size_t j=0; j<hists[0].size(); j++) { // loop on plots
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
    h->Reset();
    h->SetTitle(t.c_str());
    h->Draw();
    //TLegend *l = new TLegend(0.55, 0.15, 0.89, 0.30, "Modules");
    TLegend *l = new TLegend(0.15, 0.70, 0.49, 0.85, "Modules");
    l->SetLineColor(0);
    for (size_t i=0; i<hists.size(); i++) { // loop on modules
      if (detids[i]<300000000) continue;
      if (hists[i][j]->GetEntries()==0) continue;
      if (hists[0][j]->GetDimension()==1) {
	hists[i][j]->Draw("SAMEP");
      } else hists[i][j]->Draw("SAME");
      l->AddEntry(hists[i][j], name(detids[i]).c_str());
      std::cout<<name(detids[i]).c_str()<<std::endl;
      gPad->Update();
    }
    l->Draw();
    if (saveRecHits) {
      c->SaveAs(Form("%sAll_%s%s", save_dir.c_str(), n.c_str(), format));
      c->SaveAs(Form("%sAll_%s%s", save_dir.c_str(), n.c_str(), ".C"));
    }
  }
}


void plotScript() {
  gStyle->SetOptStat(1100);
  //gStyle->SetOptStat(111111111);
  gStyle->SetOptTitle(1);
  bool saveAll = true;
  std::string save_dir = "./";
  const char* format = ".png";

  TChain* filechain = new TChain("filechain");
  filechain->Add("/data/vami/projects/pilotBlade/pp2016ReProcessing_v3/CMSSW_8_0_8/src/crab/Ntuple/August_Runs279853-279865/NoFiducialNoAlignment/crab_PilotBlade_data_Ntuplizer_pp_August_Runs279853-279865_v1/results/*.root");

  //digis(saveAll, save_dir, format, filechain);
  //clusters(saveAll, save_dir, format, filechain);
  rechits(saveAll, save_dir, format, filechain);
}

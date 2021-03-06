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
  if (run==274000) { 
    delay=62; return delay; }
  if (run==274002) { 
    delay=62; return delay; }
  if (run==274004) { 
    delay=62; return delay; }
  if (run==274007) { 
    delay=62; return delay; }
  if (run==274008) { 
    delay=62; return delay; }
  if (run==274036) { 
    delay=62; return delay; }
  if (run==274044) { 
    delay=62; return delay; }
  if (run==274046) { 
    delay=62; return delay; }
  if (run==274047) { 
    delay=62; return delay; }
  if (run==274048) { 
    delay=62; return delay; }
  if (run==274049) { 
    delay=62; return delay; }
  if (run==274050) { 
    delay=62; return delay; }
  if (run==274052) { 
    delay=62; return delay; }
  if (run==274057) { 
    delay=62; return delay; }
  if (run==274062) { 
    delay=62; return delay; }
  if (run==274064) { 
    delay=62; return delay; }
  if (run==274076) { 
    delay=62; return delay; }
  if (run==274077) { 
    delay=62; return delay; }
  if (run==274079) { 
    delay=52; return delay; }
  if (run==274080) { 
    delay=52; return delay; }
  if (run==274081) { 
    delay=52; return delay; }
  if (run==274083) { 
    delay=52; return delay; }
  if (run==274086) { 
    delay=52; return delay; }
  if (run==274087) { 
    delay=52; return delay; }
  if (run==274088) { 
    delay=52; return delay; }
  if (run==274089) { 
    delay=52; return delay; }
  if (run==274090) { 
    delay=52; return delay; }
  if (run==274091) { 
    delay=52; return delay; }
  if (run==274093) { 
    delay=52; return delay; }
  if (run==274094) { 
    delay=52; return delay; }
  if (run==274096) { 
    delay=52; return delay; }
  if (run==274102) { 
    delay=45; return delay; }
  if (run==274103) { 
    delay=45; return delay; }
  if (run==274104) { 
    delay=45; return delay; }
  if (run==274105) { 
    delay=45; return delay; }
  if (run==274106) { 
    delay=45; return delay; }
  if (run==274107) { 
    delay=45; return delay; }
  if (run==274108) { 
    delay=70; return delay; }
  if (run==274113) { 
    delay=70; return delay; }
  if (run==274114) { 
    delay=70; return delay; }
  if (run==274115) { 
    delay=70; return delay; }
  if (run==274122) { 
    delay=70; return delay; }
  if (run==274123) { 
    delay=70; return delay; }
  if (run==274132) { 
    delay=70; return delay; }
  if (run==274133) { 
    delay=70; return delay; }
  if (run==274134) { 
    delay=70; return delay; }
  if (run==274135) { 
    delay=70; return delay; }
  if (run==274138) { 
    delay=70; return delay; }
  if (run==274139) { 
    delay=70; return delay; }
  if (run==274141) { 
    delay=70; return delay; }
  if (run==274142) { 
    delay=70; return delay; }
  if (run==274146) { 
    delay=70; return delay; }
  if (run==274147) { 
    delay=70; return delay; }
  if (run==274148) { 
    delay=70; return delay; }
  if (run==274149) { 
    delay=70; return delay; }
  if (run==274150) { 
    delay=70; return delay; }
  if (run==274151) { 
    delay=70; return delay; }
  if (run==274152) { 
    delay=70; return delay; }
  if (run==274154) { 
    delay=70; return delay; }
  if (run==274155) { 
    delay=70; return delay; }
  if (run==274156) { 
    delay=70; return delay; }
  if (run==274157) { 
    delay=70; return delay; }
  if (run==274159) { 
    delay=82; return delay; }
  if (run==274192) { 
    delay=82; return delay; }
  if (run==274195) { 
    delay=82; return delay; }
  if (run==274196) { 
    delay=82; return delay; }
  if (run==274246) { 
    delay=82; return delay; }
  if (run==274247) { 
    delay=82; return delay; }
  if (run==274248) { 
    delay=82; return delay; }
  if (run==274256) { 
    delay=82; return delay; }
  if (run==274263) { 
    delay=82; return delay; }
  if (run==274264) { 
    delay=82; return delay; }
  if (run==274266) { 
    delay=82; return delay; }
  if (run==274268) { 
    delay=82; return delay; }
  if (run==274270) { 
    delay=82; return delay; }
  if (run==274274) { 
    delay=82; return delay; }
  if (run==274275) { 
    delay=82; return delay; }
  if (run==274276) { 
    delay=82; return delay; }
  if (run==274280) { 
    delay=82; return delay; }
  if (run==274281) { 
    delay=82; return delay; }
  if (run==274289) { 
    delay=82; return delay; }
  if (run==274290) { 
    delay=82; return delay; }
  if (run==274294) { 
    delay=82; return delay; }
  if (run==274295) { 
    delay=82; return delay; }
  if (run==274300) { 
    delay=82; return delay; }
  if (run==274305) { 
    delay=82; return delay; }
  if (run==274306) { 
    delay=82; return delay; }
  if (run==274309) { 
    delay=82; return delay; }
  if (run==274311) { 
    delay=82; return delay; }
  if (run==274313) { 
    delay=82; return delay; }
  if (run==274317) { 
    delay=82; return delay; }
  if (run==274320) { 
    delay=82; return delay; }
  if (run==274324) { 
    delay=82; return delay; }
  if (run==274337) { 
    delay=82; return delay; }
  if (run==274344) { 
    delay=82; return delay; }
  if (run==274345) { 
    delay=82; return delay; }
  if (run==274346) { 
    delay=82; return delay; }
  if (run==274347) { 
    delay=82; return delay; }
  if (run==274349) { 
    delay=82; return delay; }
  if (run==274356) { 
    delay=82; return delay; }
  if (run==274363) { 
    delay=82; return delay; }
  if (run==274366) { 
    delay=82; return delay; }
  if (run==274367) { 
    delay=82; return delay; }
  if (run==274368) { 
    delay=82; return delay; }
  if (run==274369) { 
    delay=82; return delay; }
  if (run==274372) { 
    delay=82; return delay; }
  if (run==274373) { 
    delay=82; return delay; }
  if (run==274374) { 
    delay=82; return delay; }
  if (run==274377) { 
    delay=82; return delay; }
  if (run==274378) { 
    delay=82; return delay; }
  if (run==274379) { 
    delay=82; return delay; }
  if (run==274380) { 
    delay=82; return delay; }
  if (run==274381) { 
    delay=82; return delay; }
  if (run==274382) { 
    delay=82; return delay; }
  if (run==274384) { 
    delay=82; return delay; }
  if (run==274385) { 
    delay=82; return delay; }
  if (run==274386) { 
    delay=45; return delay; }
  if (run==274387) { 
    delay=45; return delay; }
  if (run==274391) { 
    delay=50; return delay; }
  if (run==274392) { 
    delay=50; return delay; }
  if (run==274393) { 
    delay=50; return delay; }
  if (run==274394) { 
    delay=50; return delay; }
  if (run==274396) { 
    delay=50; return delay; }
  if (run==274398) { 
    delay=50; return delay; }
  if (run==274401) { 
    delay=50; return delay; }
  if (run==274402) { 
    delay=50; return delay; }
  if (run==274414) { 
    delay=50; return delay; }
  if (run==274415) { 
    delay=50; return delay; }
  if (run==274417) { 
    delay=50; return delay; }
  if (run==274418) { 
    delay=50; return delay; }
  if (run==274419) { 
    delay=50; return delay; }
  if (run==274420) { 
    delay=50; return delay; }
  if (run==274421) { 
    delay=50; return delay; }
  if (run==274422) { 
    delay=56; return delay; }
  if (run==274424) { 
    delay=60; return delay; }
  if (run==274425) { 
    delay=60; return delay; }
  if (run==274430) { 
    delay=60; return delay; }
  if (run==274433) { 
    delay=60; return delay; }
  if (run==274436) { 
    delay=60; return delay; }
  if (run==274437) { 
    delay=60; return delay; }
  if (run==274438) { 
    delay=60; return delay; }
  if (run==274439) { 
    delay=60; return delay; }
  if (run==274440) { 
    delay=60; return delay; }
  if (run==274441) { 
    delay=65; return delay; }
  if (run==274442) { 
    delay=65; return delay; }
  if (run==274443) { 
    delay=70; return delay; }
  if (run==274444) { 
    delay=70; return delay; }
  if (run==274445) { 
    delay=40; return delay; }
  if (run==274446) { 
    delay=40; return delay; }
  if (run==274448) { 
    delay=40; return delay; }
  if (run==274449) { 
    delay=40; return delay; }
  if (run==274450) { 
    delay=40; return delay; }
  if (run==274452) { 
    delay=40; return delay; }
  if (run==274455) { 
    delay=40; return delay; }
  if (run==274463) { 
    delay=40; return delay; }
  if (run==274468) { 
    delay=40; return delay; }
  if (run==274469) { 
    delay=40; return delay; }
  if (run==274470) { 
    delay=40; return delay; }
  if (run==274471) { 
    delay=40; return delay; }
  if (run==274495) { 
    delay=40; return delay; }
  if (run==274503) { 
    delay=40; return delay; }
  if (run==274505) { 
    delay=40; return delay; }
  if (run==274506) { 
    delay=40; return delay; }
  if (run==274507) { 
    delay=40; return delay; }
  if (run==274508) { 
    delay=40; return delay; }
  if (run==274510) { 
    delay=40; return delay; }
  if (run==274512) { 
    delay=40; return delay; }
  if (run==274516) { 
    delay=40; return delay; }
  if (run==274517) { 
    delay=40; return delay; }
  if (run==274569) { 
    delay=40; return delay; }
  if (run==274718) { 
    delay=40; return delay; }
  if (run==274720) { 
    delay=40; return delay; }
  if (run==274722) { 
    delay=40; return delay; }
  if (run==274724) { 
    delay=40; return delay; }
  if (run==274726) { 
    delay=40; return delay; }
  if (run==274728) { 
    delay=40; return delay; }
  if (run==274733) { 
    delay=40; return delay; }
  if (run==274743) { 
    delay=40; return delay; }
  if (run==274744) { 
    delay=40; return delay; }
  if (run==274746) { 
    delay=40; return delay; }
  if (run==274748) { 
    delay=40; return delay; }
  if (run==274749) { 
    delay=40; return delay; }
  if (run==274758) { 
    delay=40; return delay; }
  if (run==274771) { 
    delay=40; return delay; }
  if (run==274774) { 
    delay=40; return delay; }
  if (run==274775) { 
    delay=40; return delay; }
  if (run==274776) { 
    delay=40; return delay; }
  if (run==274777) { 
    delay=40; return delay; }
  if (run==274778) { 
    delay=40; return delay; }
  if (run==274779) { 
    delay=40; return delay; }
  if (run==274780) { 
    delay=40; return delay; }
  if (run==274781) { 
    delay=40; return delay; }
  if (run==274783) { 
    delay=40; return delay; }
  if (run==274784) { 
    delay=40; return delay; }
  if (run==274785) { 
    delay=40; return delay; }
  if (run==274799) { 
    delay=40; return delay; }
  if (run==274802) { 
    delay=40; return delay; }
  if (run==274804) { 
    delay=40; return delay; }
  if (run==274806) { 
    delay=40; return delay; }
  if (run==274810) { 
    delay=40; return delay; }
  if (run==274813) { 
    delay=40; return delay; }
  if (run==274814) { 
    delay=40; return delay; }
  if (run==274815) { 
    delay=40; return delay; }
  if (run==274817) { 
    delay=40; return delay; }
  if (run==274850) { 
    delay=40; return delay; }
  if (run==274856) { 
    delay=40; return delay; }
  if (run==274861) { 
    delay=40; return delay; }
  if (run==274864) { 
    delay=40; return delay; }
  if (run==274866) { 
    delay=40; return delay; }
  if (run==274868) { 
    delay=40; return delay; }
  if (run==274869) { 
    delay=40; return delay; }
  if (run==274873) { 
    delay=40; return delay; }
  if (run==274875) { 
    delay=40; return delay; }
  if (run==274877) { 
    delay=40; return delay; }
  if (run==274878) { 
    delay=40; return delay; }
  if (run==274879) { 
    delay=40; return delay; }
  if (run==274880) { 
    delay=40; return delay; }
  if (run==274881) { 
    delay=40; return delay; }
  if (run==274883) { 
    delay=40; return delay; }
  if (run==274885) { 
    delay=40; return delay; }
  if (run==274887) { 
    delay=40; return delay; }
  if (run==274888) { 
    delay=40; return delay; }
  if (run==274939) { 
    delay=40; return delay; }
  if (run==274940) { 
    delay=40; return delay; }
  if (run==274941) { 
    delay=40; return delay; }
  if (run==274942) { 
    delay=40; return delay; }
  if (run==274943) { 
    delay=40; return delay; }
  if (run==274944) { 
    delay=40; return delay; }
  if (run==274945) { 
    delay=40; return delay; }
  if (run==274947) { 
    delay=40; return delay; }
  if (run==274948) { 
    delay=40; return delay; }
  if (run==274950) { 
    delay=40; return delay; }
  if (run==274951) { 
    delay=40; return delay; }
  if (run==274953) { 
    delay=40; return delay; }
  if (run==274954) { 
    delay=40; return delay; }

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
  filechain->Add("/data/vami/projects/pilotBlade/pp2016Processing/Ntuple/April23/*.root");
  filechain->Add("/data/vami/projects/pilotBlade/pp2016Processing/Ntuple/April24/*.root");
  filechain->Add("/data/vami/projects/pilotBlade/pp2016Processing/Ntuple/April25/*.root");
  // 38T from here
  filechain->Add("/data/vami/projects/pilotBlade/pp2016Processing/Ntuple/April29/*.root");
  
 
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

    PBClusterChargeVsDel.push_back((TProfile*)(h=new TProfile(Form("PBClusterChargeVsDel_%d", detids[imod]),  Form("Avg cluster charge vs Delay in %s;Delay;Avg cluster charge", name(detids[imod]).c_str()), 150, -30, 120, 0, 150))); vh.push_back(h);
    PBClusterSizeVsDel.push_back((TProfile*)(h=new TProfile(Form("PBClusterSizeVsDel_%d", detids[imod]),  Form("Avg cluster size vs Delay in %s;Delay;Avg cluster size", name(detids[imod]).c_str()), 150, -30, 120, 0, 15))); vh.push_back(h);
    PBClustersVsDel.push_back((TProfile*)(h=new TProfile(Form("PBClustersVsDel_%d", detids[imod]),  Form("Avg num of clusters per event vs Delay in %s;Delay;Avg num of clusters", name(detids[imod]).c_str()), 150, -30, 120, 0, 100))); vh.push_back(h);
    
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
      // if we want the disk2 modules before the PB then include:
      // if((module_on.disk==-3) || (module_on.disk==-2 && module_on.blade==-11) ) {
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
    for (size_t i=0; i<hists.size(); i++) {
      if (hists[i][j]->GetEntries()==0) continue;
      hists[i][j]->Draw("SAME");
      l->AddEntry(hists[i][j], name(detids[i]).c_str());
      std::cout<<name(detids[i]).c_str()<<std::endl;
      gPad->Update();
    }
    l->Draw();
    if (save) c->SaveAs(Form("%sAll_%s%s", save_dir.c_str(), hists[0][j]->GetName(), format));
  }
}

void plotScript() {
   digis();
}

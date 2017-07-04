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

#include "PilotHistoMaker.h"
#include "/data/vami/projects/pilotBlade/PilotHistoMakerDelays.h"
//#include "PilotHistoMakerDelays.h"

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
// ---------------------------------------------------------------------------
// -----------------------------Digis---------------------------------------
// ---------------------------------------------------------------------------
void digis(bool saveAll, std::string save_dir, const char* format, TChain* filechain)
{
    
    bool saveDigis = 0;
    if (saveAll) saveDigis = 1;
    Int_t selectDelay=-9999;
    Long64_t reduceFraction=0;
    Int_t skipFiles=0;
    bool COLZ=true;
    
    int _detids[] = { 344132868, 344134148, 344131076, 344132100, 344130820, 1, 344131844 };
    //int _detids[] = { 344130820, 344131844, 344132868, 344133892, 344131076, 344132100, 344133124, 344134148, 1 };
    std::vector<int> detids(_detids, _detids + sizeof(_detids) / sizeof(int) );
    
    std::map<int,int> idx_map;
    for (size_t i=0; i<detids.size(); i++) {
        idx_map[detids[i]]=i;
        std::cout << "define detector id " << detids[i] << " as " << idx_map[detids[i]]<<std::endl;
    }
    const std::map<int,int>& idx = idx_map;
    
    // Create the histograms
    std::vector<std::vector<TH1*> > hists;
    
    std::vector<TH1F *> PBADCDist;
    std::vector<TH2F *> PBDigisMod;
    
    for (size_t imod=0; imod<detids.size(); imod++) {
        
        std::vector<TH1*> vh;
        TH1 *h;
        
        PBADCDist.push_back((TH1F*)(h=new TH1F(Form("PBADCDist_%d", detids[imod]), Form("ADC Distribution in %s ;ADC;Yield", name(detids[imod]).c_str()), 50,0.,250.))); vh.push_back(h);
        
        if (COLZ==true) {
          PBDigisMod.push_back((TH2F*)(h=new TH2F(Form("PBDigisMod_COLZ_%d", detids[imod]), Form("Pixels in %s ;columns [pixels];rows [pixels]", name(detids[imod]).c_str()),   416,0,416.0,   160,0,160.0))); vh.push_back(h);        
        } else {
          PBDigisMod.push_back((TH2F*)(h=new TH2F(Form("PBDigisMod_%d", detids[imod]), Form("Pixels in %s ;columns [pixels];rows [pixels]", name(detids[imod]).c_str()),   416,0,416.0,   160,0,160.0))); vh.push_back(h);
          }

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
            if (del==-9999) {
                std::cout << "Run " << evt.run << " LS " << evt.ls << "has no delay set up -- exiting" << std::endl; 
                continue; 
            }
            if (selectDelay!=-9999 && del!=selectDelay) continue;
            if (module_on.disk!=-3 && !(module_on.disk==-2 && (module_on.blade==-10 || module_on.blade==-11)) ) continue;
            
            int rawid=module_on.rawid;
            if (module_on.disk==-2) rawid=1;
            
            std::map<int,int>::const_iterator it_idx=idx.find(rawid);
            if (it_idx==idx.end()) continue;
            int imod = it_idx->second;
            
            PBADCDist[imod]->Fill(digi.adc);
            PBDigisMod[imod]->Fill(digi.col,digi.row);
            
            ++digiCounter[imod];
        }
        
        // ---------------------- Events ---------------------- 
        TTree* eventTree = (TTree*)f.Get("eventTree");
        eventTree->GetBranch("event")->SetAddress(&evt_);
        
        for (Long64_t i=0; i<eventTree->GetEntries(); i++) {
            if (reduceFraction!=0 && i%reduceFraction!=0) continue;
            eventTree->GetEntry(i);
            int del=delay(evt.run, evt.ls);
            if (del==-9999) {
                std::cout << "Run " << evt.run << " LS " << evt.ls << "has no delay set up -- exiting" << std::endl; 
                continue; 
            }
            if (selectDelay!=-9999 && del!=selectDelay) continue;
        }
        
        
        // -------------------------------------------- 
    } // End of loop on files
    
    // Create the canvas and save
    
    for (size_t j=0; j<hists[0].size(); j++) { // loop on plots
        for (size_t i=0; i<hists.size(); i++) { // loop on modules
            if (hists[i][j]->GetEntries()==0) continue;
            TCanvas *c = new TCanvas(Form("c%d_%d", int(i), int(j)), Form("%d_%d", int(i), int(j)), 600, 600);
            COLZ==true ? hists[i][j]->Draw("COLZ") : hists[i][j]->Draw();
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
// -----------------------------Clusters---------------------------------------
// ---------------------------------------------------------------------------
void clusters(bool saveAll, std::string save_dir, const char* format, TChain* filechain)
{
    bool saveClusters = 0;
    if (saveAll) saveClusters = 1;
    Int_t selectDelay=-9999;
    Long64_t reduceFraction=0;
    Int_t skipFiles=0;
    bool COLZ=false;
    
    int _detids[] = { 344132868, 344134148, 344131076, 344132100, 344130820, 1, 344131844 };
    //int _detids[] = { 344130820, 344131844, 344132868, 344133892, 344131076, 344132100, 344133124, 344134148, 1 };
    std::vector<int> detids(_detids, _detids + sizeof(_detids) / sizeof(int) );
    
    std::map<int,int> idx_map;
    for (size_t i=0; i<detids.size(); i++) {
        idx_map[detids[i]]=i;
        std::cout << "define detector id " << detids[i] << " as " << idx_map[detids[i]]<<std::endl;
    }
    const std::map<int,int>& idx = idx_map;
    
    // Create the histograms
    std::vector<std::vector<TH1*> > hists;
    
    std::vector<TH1F *> PBClusterCharge;
    std::vector<TH1F *> PBClusterSize;
    std::vector<TH2F *> PBClustersMod;
    std::vector<TH2F *> PBClustersGlobal;
    
    std::vector<TProfile *> PBClusterChargeVsDel;
    std::vector<TProfile *> PBClusterSizeVsDel;
    std::vector<TProfile *> PBClustersVsDel;
    
    std::vector<TH1F *> PBClustersVsDel_num;
    std::vector<TH1F *> PBClustersVsDel_den;
    
    std::vector<TH1F *> PBClusterFEDErrVsDel;
    std::vector<TH1F *> PBClusterFEDErrType;
    std::vector<TH1F *> PBClusterFEDErrTypePerEvent;
    
    
    for (uint imod=0; imod<detids.size(); imod++) {
        
        std::vector<TH1*> vh;
        TH1 *h;
        
        PBClusterCharge.push_back((TH1F*)(h=new TH1F(Form("PBClusterCharge_%d", detids[imod]),  Form("Clusters Charge Distribution in  %s;Cluster charge [ke];Yield", name(detids[imod]).c_str()), 150,0,150))); vh.push_back(h);
        PBClusterSize.push_back((TH1F*)(h=new TH1F(Form("PBClusterSize_%d", detids[imod]), Form( "Clusters Size Distribution in %s;Cluster size [pixel];Yield", name(detids[imod]).c_str()), 10,0,10))); vh.push_back(h);
        if (COLZ==true) {
            PBClustersMod.push_back((TH2F*)(h=new TH2F(Form("PBClustersMod_COLZ_%d", detids[imod]), Form("Cluster occupancy in %s;Columns [pixel];Rows [pixel]", name(detids[imod]).c_str()),   416,0,416,   160,0,160.0))); vh.push_back(h);
            PBClustersGlobal.push_back((TH2F*)(h=new TH2F(Form("PBClustersGlobal_COLZ_%d", detids[imod]), Form("Cluster occupancy in %s;CMS Global X;CMS Global Y", name(detids[imod]).c_str()), 3200,-16,16, 3200,-16,16))); vh.push_back(h);
        } else {
            PBClustersMod.push_back((TH2F*)(h=new TH2F(Form("PBClustersMod_%d", detids[imod]), Form("Clusters in %s;Columns [pixel];Rows [pixel]", name(detids[imod]).c_str()),   416,0,416,   160,0,160.0))); vh.push_back(h);
            PBClustersGlobal.push_back((TH2F*)(h=new TH2F(Form("PBClustersGlobal_%d", detids[imod]), Form("Clusters in %s;CMS Global X;CMS Global Y", name(detids[imod]).c_str()), 3200,-16,16, 3200,-16,16))); vh.push_back(h);
        }

        PBClusterChargeVsDel.push_back((TProfile*)(h=new TProfile(Form("PBClusterChargeVsDel_%d", detids[imod]),  Form("Avg cluster charge vs Delay in %s;Delay;Avg cluster charge", name(detids[imod]).c_str()), 150,0, 150, 0, 150))); vh.push_back(h);
        PBClusterSizeVsDel.push_back((TProfile*)(h=new TProfile(Form("PBClusterSizeVsDel_%d", detids[imod]),  Form("Avg cluster size vs Delay in %s;Delay;Avg cluster size", name(detids[imod]).c_str()), 150,0, 150, 0, 15))); vh.push_back(h);
        PBClustersVsDel.push_back((TProfile*)(h=new TProfile(Form("PBClustersVsDel_%d", detids[imod]),  Form("Avg num of clusters per event vs Delay in %s;Delay;Avg num of clusters", name(detids[imod]).c_str()), 150,0, 150, 0, 100))); vh.push_back(h);
        
        PBClustersVsDel_num.push_back((TH1F*)(h=new TH1F(Form("PBClusterAvgNumVsDel_%d", detids[imod]),  Form("Avg num of clusters per event vs Delay in %s;Delay;Avg num of clusters", name(detids[imod]).c_str()), 150,0, 150))); vh.push_back(h);
        PBClustersVsDel_den.push_back((TH1F*)(h=new TH1F(Form("PBCEventNumberVsDel_%d", detids[imod]),  Form("Total number of events vs Delay in %s;Delay;num of events", name(detids[imod]).c_str()), 150,0, 150))); vh.push_back(h);
        
        PBClusterFEDErrVsDel.push_back((TH1F*)(h=new TH1F(Form("PBClusterFEDErrVsDel_%d", detids[imod]),  Form("Fraction of clusters with FED error vs Delay in %s;Delay;Clusters with FED err", name(detids[imod]).c_str()), 150,0, 150))); vh.push_back(h);
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
        std::cout << "Opening "<<chEl->GetTitle()<<std::endl;
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
            //if (evt.run!=284036) continue;
            if (del==-9999) {
                std::cout << "Run " << evt.run << " LS " << evt.ls << "has no delay set up -- exiting" << std::endl; 
                continue; 
            }
            if (selectDelay!=-9999 && del!=selectDelay) continue;
            
            if (module_on.disk!=-3 && !(module_on.disk==-2 && (module_on.blade==-10 || module_on.blade==-11)) ) continue;
            size_t rawid=module_on.rawid;
            if (module_on.disk==-2) rawid=1;
            
            std::map<int,int>::const_iterator it_idx=idx.find(rawid);
            if (it_idx==idx.end()) continue;
            int imod = it_idx->second;
            // if we want the disk2 modules before the PB then include:
            if((module_on.disk==-3) || (module_on.disk==-2 && module_on.blade==-11) ) {
                PBClusterCharge[imod]->Fill(clusters.charge);
                PBClusterSize[imod]->Fill(clusters.size);
                PBClustersMod[imod]->Fill(clusters.y,clusters.x);   
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
        }
        
        // ---------------------- Events ---------------------- 
        TTree* eventTree = (TTree*)f.Get("eventTree");
        eventTree->GetBranch("event")->SetAddress(&evt_);
        eventNumber = eventTree->GetEntries();
        for (Long64_t i=0; i<eventTree->GetEntries(); i++) {
            if (reduceFraction!=0 && i%reduceFraction!=0) continue;
            eventTree->GetEntry(i);
            int del=delay(evt.run, evt.ls);
            if (del==-9999) {
                std::cout << "Run " << evt.run << " LS " << evt.ls << "has no delay set up -- exiting" << std::endl; 
                continue; 
            }
            if (selectDelay!=-9999 && del!=selectDelay) continue;
            
            for (uint imod=0; imod<detids.size(); imod++) {
                PBClustersVsDel_den[imod]->Fill(delay(evt_.run, evt_.ls));
            }
        }
        
        
        // -------------------------------------------- 
    } // End of loop on files
    
    // Compute averages / efficiencies
    {
        std::map<int,int>::const_iterator it_idx=idx.find(1);
        for (uint imod=0; imod<detids.size(); imod++) {
            //if (it_idx!=idx.end() && imod!=it_idx->second) PBClustersVsDel_num[imod]->Divide(PBClustersVsDel_num[it_idx->second]); //average ratio of PB clusters to FPix clusters in events with FPix clusters
            
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
            COLZ==true ? hists[i][j]->Draw("COLZ") : hists[i][j]->Draw();
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
	bool COLZ=true;
    
    int _detids[] = { 344132868, 344134148, 344131076, 344132100, 344130820, 1, 344131844 };
    //int _detids[] = { 344130820, 344131844, 344132868, 344133892, 344131076, 344132100, 344133124, 344134148 };
    std::vector<int> detids(_detids, _detids + sizeof(_detids) / sizeof(int) );
    
    std::map<int,int> idx_map;
    for (size_t i=0; i<detids.size(); i++) {
        idx_map[detids[i]]=i;
        std::cout << "define detector id " << detids[i] << " as " << idx_map[detids[i]]<<std::endl;
    }
    const std::map<int,int>& idx = idx_map;
    
    // Create the histograms
    std::vector<std::vector<TH1*> > hists;
    
    std::vector<TH2F *> PBHitsGlobal;
	std::vector<TH2F *> PBHitsMod;

    std::vector<TH1F *> PBHitCluDx;
    std::vector<TH1F *> PBHitCluDy;
    std::vector<TH2F *> PBHitCluXDx;
    std::vector<TH2F *> PBHitCluYDy;
    //std::vector<TH2F *> PBHitCluXDy;
    //std::vector<TH2F *> PBHitCluYDx;
   
    std::vector<TH1F *> PBHitEffVsDel_num;
    std::vector<TH1F *> PBHitEffVsDel_den;
    
    std::vector<TH1F *> PBClustersVsDel_num;
    std::vector<TH1F *> PBClustersVsDel_den;
    
    for (size_t imod=0; imod<detids.size(); imod++) {
        
        std::vector<TH1*> vh;
        TH1 *h;
        


        PBHitCluDx.push_back((TH1F*)(h=new TH1F(Form("PBHitCluDx_%d", detids[imod]),  Form("Rechit to nearest cluster distance in %s;Residual dx [cm];Yield", name(detids[imod]).c_str()), 50,-0.1,0.1))); vh.push_back(h);
        PBHitCluDy.push_back((TH1F*)(h=new TH1F(Form("PBHitCluDy_%d", detids[imod]),  Form("Rechit to nearest cluster distance in %s;Residual dy [cm];Yield", name(detids[imod]).c_str()), 50,-0.1,0.1))); vh.push_back(h);
		if (COLZ==true) {
			PBHitsGlobal.push_back((TH2F*)(h=new TH2F(Form("PBHitsGlobal_COLZ_%d", detids[imod]), Form("RecHits in %s;CMS Global X;CMS Global Y", name(detids[imod]).c_str()), 3200,-16,16, 3200,-16,16))); 
                        vh.push_back(h);
			PBHitsMod.push_back((TH2F*)(h=new TH2F(Form("PBHitsMod_COLZ_%d", detids[imod]), Form("Hits in %s;Columns (y) [cm];Rows (x) [cm]", name(detids[imod]).c_str()),   416,-4.0,4.0,   160,-1.0,1.0))); 
                        vh.push_back(h);

                        PBHitCluXDx.push_back((TH2F*)(h=new TH2F(Form("PBHitCluXDx_COLZ_%d", detids[imod]),  Form("Inactive rechit position (x) and the x residual %s;Rows (x) [cm];dx [cm]", name(detids[imod]).c_str()), 300,-1.0,1.0, 150,-1.0,1.0)));
                        vh.push_back(h);
			PBHitCluYDy.push_back((TH2F*)(h=new TH2F(Form("PBHitCluYDy_COLZ_%d", detids[imod]),  Form("Inactive rechit position (y) and the y residual %s;Columns (y) [cm];dy [cm]", name(detids[imod]).c_str()), 300,2.0,4.0,  150,-1.0,1.0)));
                        vh.push_back(h);
		} else {
        	PBHitsGlobal.push_back((TH2F*)(h=new TH2F(Form("PBHitsGlobal_%d", detids[imod]), Form("RecHits in %s;CMS Global X;CMS Global Y", name(detids[imod]).c_str()), 3200,-16,16, 3200,-16,16))); vh.push_back(h);
        	PBHitsMod.push_back((TH2F*)(h=new TH2F(Form("PBHitsMod_%d", detids[imod]), Form("Hits in %s;Columns [cm];Rows [cm]", name(detids[imod]).c_str()),   416,-4.0,4.0,   160,-1.0,1.0))); vh.push_back(h);

		    PBHitCluXDx.push_back((TH2F*)(h=new TH2F(Form("PBHitCluXDx_%d", detids[imod]),  Form("Inactive rechit position (x) and the x residual %s;Rows [cm];dx [cm]", name(detids[imod]).c_str()), 416,-7.0,7.0, 200,-7.0,7.0)));
                    vh.push_back(h);
		    PBHitCluYDy.push_back((TH2F*)(h=new TH2F(Form("PBHitCluYDy_%d", detids[imod]),  Form("Inactive rechit position (y) and the y residual %s;Columns [cm];dy [cm]", name(detids[imod]).c_str()), 160,-7.0,7.0,  200,-7.0,7.0)));
                    vh.push_back(h);
		}
        
        PBHitEffVsDel_num.push_back((TH1F*)(h=new TH1F(Form("PBHitEffVsDel_2mm_%d", detids[imod]),  Form("RecHit efficiency vs Delay in %s;Delay;Efficiency", name(detids[imod]).c_str()), 150, 0, 150))); 
        vh.push_back(h);
        PBHitEffVsDel_den.push_back((TH1F*)(h=new TH1F(Form("PBHitNumberVsDel_%d", detids[imod]),  Form("Num of RecHits vs Delay in %s;Delay;Num of hits", name(detids[imod]).c_str()), 150,0, 150))); 
        vh.push_back(h);
        PBClustersVsDel_num.push_back((TH1F*)(h=new TH1F(Form("PBClustersVsDel_num_%d", detids[imod]),  Form("Avg num of clusters per event vs Delay in %s;Delay;Avg num of clusters", name(detids[imod]).c_str()), 150,0, 150))); 
        vh.push_back(h);
        PBClustersVsDel_den.push_back((TH1F*)(h=new TH1F(Form("PBNumberOfEventsVsDel_den_%d", detids[imod]),  Form("Total number of events vs Delay in %s;Delay;num of events", name(detids[imod]).c_str()), 150,0, 150))); 
        vh.push_back(h);
        
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
    TrackData trk;
    
    TObjArray* fileElements = filechain->GetListOfFiles();
    TIter next(fileElements);
    TChainElement* chEl=0;
    Int_t fileCounter=0;
    
    while (( chEl=(TChainElement*)next() )) {
        fileCounter++;
        if ((skipFiles!=0) && (fileCounter%skipFiles!=0)) continue;
        TFile f(chEl->GetTitle());
        std::cout << "Opening "<<chEl->GetTitle()<<std::endl;
        //TTree* clustTree = (TTree*)f.Get("clustTree");
        TTree* trajTree = (TTree*)f.Get("trajTree");
        
        trajTree->GetBranch("traj")->SetAddress(&traj);
        trajTree->GetBranch("module_on")->SetAddress(&module_on);
        trajTree->GetBranch("event")->SetAddress(&evt);
        trajTree->GetBranch("track")->SetAddress(&trk);
        
        //if (trk.highPurity==0) continue;
        
        for (Long64_t i=0, ntraj=trajTree->GetEntries(); i<ntraj; ++i) {
            if (reduceFraction!=0 && i%reduceFraction!=0) continue;
            trajTree->GetEntry(i);
            //if (evt.run!=284036) continue;
            int del=delay(evt.run, evt.ls);
            if (del==-9999) {
                std::cout << "Run " << evt.run << " LS " << evt.ls << "has no delay set up -- exiting" << std::endl; 
                continue; 
            }
            if (selectDelay!=-9999 && del!=selectDelay) continue;
            
            if (module_on.disk!=-3 && !(module_on.disk==-2 && (module_on.blade==-10 || module_on.blade==-11)) ) continue;
            int rawid=module_on.rawid;
            if (module_on.disk==-2) rawid=1;
            
            std::map<int,int>::const_iterator it_idx=idx.find(rawid);
            if (it_idx==idx.end()) continue;
            if (traj.type!=102) continue;
            int imod = it_idx->second;


            // Correction to cluster positions  344132868, 344134148, 344131076, 344132100, 344130820
            float dx_cl = traj.dx_cl;
            float dy_cl = traj.dy_cl;
            
            //     if (module_on.rawid==344132868) {
            //    dx_cl+=0.0908;
            //    dy_cl+=0.8332; 
            //     } else if (module_on.rawid==344134148) {
            //   //dx_cl = -traj.dx_cl - traj.lx*2+0.07385;
            //    dx_cl+=0.0537;
            //    dy_cl+=0.9192; 
            //     } else if (module_on.rawid==344131076) {
            //    dx_cl+=0.0486;
            //    dy_cl-=0.1885;
            //     } 
            
            
            if (evt.federrs_size==0 && module_on.federr==0) {
                PBHitEffVsDel_den[imod]->Fill(delay(evt.run, evt.ls));
                if (fabs(dx_cl)<0.2 && fabs(dy_cl)<0.2) {
					PBHitEffVsDel_num[imod]->Fill(delay(evt.run, evt.ls));
				}
                PBHitsGlobal[imod]->Fill(traj.glx, traj.gly);
            	PBHitsMod[imod]->Fill(traj.ly,traj.lx);   
                PBHitCluDx[imod]->Fill(dx_cl);
                PBHitCluDy[imod]->Fill(dy_cl);
		PBHitCluXDx[imod]->Fill(traj.lx,traj.dx_cl);
                PBHitCluYDy[imod]->Fill(traj.ly,traj.dy_cl);
                //PBHitCluXDy[imod]->Fill(traj.lx,traj.dy_cl);
		//PBHitCluYDx[imod]->Fill(traj.ly,traj.dx_cl);
            }
            
        }
        
        // ---------------------- Events ---------------------- 
        TTree* eventTree = (TTree*)f.Get("eventTree");
        eventTree->GetBranch("event")->SetAddress(&evt_);
        
        for (Long64_t i=0; i<eventTree->GetEntries(); i++) {
            if (reduceFraction!=0 && i%reduceFraction!=0) continue;
            eventTree->GetEntry(i);
            int del=delay(evt.run, evt.ls);
            if (del==-9999) {
                std::cout << "Run " << evt.run << " LS " << evt.ls << "has no delay set up -- exiting" << std::endl; 
                continue; 
            }
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
        if (it_idx!=idx.end()) PBClustersVsDel_num[it_idx->second]->Divide(PBClustersVsDel_den[it_idx->second]); // fraction of events with FPix clusters in all events
    }
    // Create the canvas and save
    
    for (size_t j=0; j<hists[0].size(); j++) { // loop on plots
        for (size_t i=0; i<hists.size(); i++) { // loop on modules
            if (hists[i][j]->GetEntries()==0) continue;
            TCanvas *c = new TCanvas(Form("c%d_%d", int(i), int(j)), Form("%d_%d", int(i), int(j)), 600, 600);

			COLZ==true ? hists[i][j]->Draw("COLZ") : hists[i][j]->Draw();
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



int main(int argc, char* argv[]) {
    
    //   gStyle->SetOptStat(1100);
    //   gStyle->SetOptTitle(1);
    bool saveAll = true;
    std::string save_dir = "./";
    const char* format = ".png";
    
    TChain* filechain = new TChain("filechain");
    filechain->Add("/data/gridout/vami/2016pA/Runs286520/BestROCs_Margin20/ROC5/*.root");
    //filechain->Add("/data/vami/projects/pilotBlade/uTCA-data/GlobalRuns/CMSSW_8_0_20_patch1/src/0crab/3Ntuple/Runs283834-283835/crab_PilotBlade_data_Ntuplizer_pp_Runs283834-283835_CMSSW8020_ZeroBias_Fidu3_v2/results/*.root");
    //filechain->Add("/data/vami/projects/0RootFiles/2016H/PB-Ntuples/Runs283834-283835_Express/nTuplePilotBlade_All_1.root");
    
    //digis(saveAll, "./digis/", format, filechain);
    //clusters(saveAll, "./clusters/", format, filechain);
    rechits(saveAll, "./rechits/", format, filechain);
}

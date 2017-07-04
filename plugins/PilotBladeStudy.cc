#include "PilotBladeStudy.h"

using namespace std;
using namespace edm;
using namespace reco;

// ------------------------- Constructor & Destructor  ------------------------
PilotBladeStudy::PilotBladeStudy(edm::ParameterSet const& iConfig) : iConfig_(iConfig) {
  eventTree_= NULL;
  runTree_  = NULL;
  digiTree_ = NULL;
  clustTree_= NULL;
  trackTree_= NULL;
  trajTree_ = NULL;
  outfile_  = NULL;
  
  usePixelCPE_=false;
  cosmicsCase_=false;
  
  BSToken_                  = consumes< reco::BeamSpot >(edm::InputTag("offlineBeamSpot"));
  condInRunBlockToken_      = mayConsume< edm::ConditionsInRunBlock, InRun >(edm::InputTag("conditionsInEdm"));
  condInLumiBlockToken_     = mayConsume< edm::ConditionsInLumiBlock, InLumi >(edm::InputTag("conditionsInEdm"));
  
  if (iConfig_.exists("triggerTag")) {
    triggerTag_=iConfig_.getParameter<edm::InputTag>("triggerTag");
    std::cout<<"NON-DEFAULT PARAMETER: triggerTag= "<<triggerTag_<<std::endl;
  } else triggerTag_=edm::InputTag("TriggerResults","", "HLT");
  triggerResultsToken_=consumes<edm::TriggerResults>(triggerTag_);
  
  siPixelDigisToken_        = consumes< edm::DetSetVector<PixelDigi> >(edm::InputTag("siPixelDigis"));
  PBDigisToken_             = consumes< edm::DetSetVector<PixelDigi> >(edm::InputTag("PBDigis"));
  siPixelClustersToken_     = consumes< edmNew::DetSetVector<SiPixelCluster> >(edm::InputTag("siPixelClusters"));
  PBClustersToken_          = consumes< edmNew::DetSetVector<SiPixelCluster> >(edm::InputTag("PBClusters"));
  std::string trajTrackCollectionInput = iConfig.getParameter<std::string>("trajectoryInput");
  trajTrackCollToken_	    = consumes<TrajTrackAssociationCollection>(edm::InputTag(trajTrackCollectionInput));
  
  trackingErrorToken_	    = consumes< edm::EDCollection<DetId> >(edm::InputTag("siPixelDigis"));
  SiPixelRawDataErrorToken_ = consumes< edm::DetSetVector<SiPixelRawDataError> >(edm::InputTag("PBDigis"));
  userErrorToken_	    = consumes< edm::EDCollection<DetId> >(edm::InputTag("siPixelDigis", "UserErrorModules"));

  detIdFromFED40_[1]=344133892; // BmO_D3_BLD11_PNL1
  detIdFromFED40_[2]=344133892; // BmO_D3_BLD11_PNL1
  detIdFromFED40_[3]=344134148; // BmO_D3_BLD11_PNL2
  detIdFromFED40_[4]=344134148; // BmO_D3_BLD11_PNL2
  detIdFromFED40_[7]=344132868; // BmO_D3_BLD10_PNL1
  detIdFromFED40_[8]=344132868; // BmO_D3_BLD10_PNL1
  detIdFromFED40_[9]=344133124; // BmO_D3_BLD10_PNL2
  detIdFromFED40_[10]=344133124; // BmO_D3_BLD10_PNL2
  detIdFromFED40_[25]=344131844; // BmI_D3_BLD2_PNL1
  detIdFromFED40_[26]=344131844; // BmI_D3_BLD2_PNL1
  detIdFromFED40_[27]=344132100; // BmI_D3_BLD2_PNL2
  detIdFromFED40_[28]=344132100; // BmI_D3_BLD2_PNL2
  detIdFromFED40_[31]=344130820; // BmI_D3_BLD3_PNL1
  detIdFromFED40_[32]=344130820; // BmI_D3_BLD3_PNL1
  detIdFromFED40_[33]=344131076; // BmI_D3_BLD3_PNL2
  detIdFromFED40_[34]=344131076; // BmI_D3_BLD3_PNL2

  if (iConfig_.exists("PositionCorrections")) {
    Parameters positionCorrections = iConfig_.getUntrackedParameter<Parameters>("PositionCorrections");
    for(Parameters::iterator it = positionCorrections.begin(); it != positionCorrections.end(); ++it) {
      unsigned int id=(unsigned int)it->getParameter<unsigned int>("id");
      float dx=(float)it->getParameter<double>("dx");
      float dy=(float)it->getParameter<double>("dy");
      posCorr_[id]=PositionCorrection(dx, dy);
    }
  }

  for (std::map<unsigned int,PositionCorrection>::iterator it=posCorr_.begin(); it!=posCorr_.end(); it++) {
    std::cout<<"Correcting position for "<<it->first<<" with ("<<it->second.dx<<", "<<it->second.dy<<")"<<std::endl;
  }


  if (iConfig_.exists("FiducialRegions")) {
    Parameters fiducialRegions = iConfig_.getUntrackedParameter<Parameters>("FiducialRegions");
    for(Parameters::iterator it = fiducialRegions.begin(); it != fiducialRegions.end(); ++it) {
      unsigned int id=(unsigned int)it->getParameter<unsigned int>("id");
      float marginX=(float)it->getParameter<double>("marginX");
      float marginY=(float)it->getParameter<double>("marginY");
      std::vector<int> rocX = it->getParameter<std::vector<int> > ("rocX");
      std::vector<int> rocY = it->getParameter<std::vector<int> > ("rocY");
      if (rocX.size()!=rocY.size()) {
	std::cout<<"***ERROR: Skipping detId. Number of ROC X indices is not equal to Y for det Id "<<id<<std::endl;
	continue;
      }
      std::vector<FiducialRegion> rocs;
      for (size_t i=0; i<rocX.size(); i++) rocs.push_back(FiducialRegion(rocX[i], rocY[i], marginX, marginY));
      fidReg_[id]=rocs;
    }
  }

  for (std::map<unsigned int,std::vector<FiducialRegion> >::iterator it=fidReg_.begin(); it!=fidReg_.end(); it++) {
    std::cout<<"Fiducial regions in detID "<<it->first<< " are in ROCs" << std::endl;
    for (size_t i=0; i<it->second.size(); i++) std::cout<< it->second[i].print() <<std::endl;
  }

}

PilotBladeStudy::~PilotBladeStudy() { }

// ------------------------------ beginJob ------------------------------------
void PilotBladeStudy::beginJob() {
  
  std::string fileName="test.root";
  if (iConfig_.exists("fileName")) {  
    fileName=iConfig_.getParameter<std::string>("fileName");
  }
  
  if (iConfig_.exists("usePixelCPE")) {
    usePixelCPE_=iConfig_.getParameter<bool>("usePixelCPE");
    std::cout<<"Pixel Cluster Parameter Estimator (CPE) is used "<<std::endl;
  }
  
  if (iConfig_.exists("cosmicsCase")) {
    cosmicsCase_=iConfig_.getParameter<bool>("cosmicsCase");
    if (cosmicsCase_) std::cout<<"This is a Cosmics run: " <<std::endl;
  }
  
  if (iConfig_.exists("triggerTag")) {
    triggerTag_=iConfig_.getParameter<edm::InputTag>("triggerTag");
    std::cout<<"NON-DEFAULT PARAMETER: triggerTag= "<<triggerTag_<<std::endl;
  } else {
    triggerTag_=edm::InputTag("TriggerResults","", "HLT");
  }
  
  if (iConfig_.exists("triggerNames")) {
    triggerNames_=iConfig_.getParameter<std::vector<std::string> >("triggerNames");
    std::cout<<"NON-DEFAULT PARAMETER: triggerNames= ";
    for (size_t i=0; i<triggerNames_.size(); i++) std::cout<<triggerNames_[i]<<" ";
    std::cout<<std::endl;
  }
  
  outfile_ = new TFile(fileName.c_str(), "RECREATE");
  
  EventData         evt_;
  Digi		    digi_;
  Cluster           clust;
  TrackData 	    track_; // TODO this should be without the _ shouldn't it?
  TrajMeasurement   trajmeas;

  // Setting up the Branch-es
  eventTree_ = new TTree("eventTree", "The event");
  eventTree_->Branch("event", &evt_, evt_.list.data());
  
  runTree_ = new TTree("runTree", "The run");
  runTree_->Branch("run", &run_, run_.list.data());

  digiTree_ = new TTree("digiTree", "The digis");
  digiTree_->Branch("event",        &evt_, 		evt_.list.data());
  digiTree_->Branch("digi", 	    &digi_, 		digi_.list.data());
  digiTree_->Branch("module",       &digi_.mod, 	digi_.mod.list.data());
  digiTree_->Branch("module_on",    &digi_.mod_on, 	digi_.mod_on.list.data());
  
  clustTree_ = new TTree("clustTree", "The clusters");
  clustTree_->Branch("event",       &evt_,		evt_.list.data());
  clustTree_->Branch("clust",       &clust,		clust.list.data());
  clustTree_->Branch("module",      &clust.mod,		clust.mod.list.data());
  clustTree_->Branch("module_on",   &clust.mod_on,	clust.mod_on.list.data());

  trackTree_ = new TTree("trackTree", "The tracks");
  trackTree_->Branch("event", 	    &evt_, 		evt_.list.data());
  trackTree_->Branch("track",       &track_, 		track_.list.data());
  
  trajTree_ = new TTree("trajTree", "The trajectory measurements in the event");
  trajTree_->Branch("event",        &evt_,              evt_.list.data());
  trajTree_->Branch("track",        &trajmeas.trk,      trajmeas.trk.list.data());
  trajTree_->Branch("traj",         &trajmeas,          trajmeas.list.data());
  trajTree_->Branch("clust",        &trajmeas.clu,      trajmeas.clu.list.data());
//   trajTree_->Branch("clust_pixX",   &trajmeas.clu.pixX, "pixX[size]/F");
//   trajTree_->Branch("clust_pixY",   &trajmeas.clu.pixY, "pixY[size]/F");
  trajTree_->Branch("module",       &trajmeas.mod,      trajmeas.mod.list.data());
  trajTree_->Branch("module_on",    &trajmeas.mod_on,   trajmeas.mod_on.list.data());
}

// ------------------------------ endJob --------------------------------------
void PilotBladeStudy::endJob() {
  outfile_->Write();
  outfile_->Close();
  delete outfile_;
}

// ------------------------------ beginRun ------------------------------------
void PilotBladeStudy::beginRun(edm::Run const& iRun, edm::EventSetup const& iSetup){
//   run_.init();
//   run_.run = iRun.run();
//   
//   // ConditionsInRunBlock for fill number
//   edm::Handle<edm::ConditionsInRunBlock> condInRunBlock;
//   iRun.getByToken(condInRunBlockToken_, condInRunBlock);
//   
//   if (condInRunBlock.isValid()) {
//      run_.fill = condInRunBlock->lhcFillNumber;
//   } else if (run_.run==1) {
//    run_.fill = 0;
//   } else {
//     std::cout<<"No condInRunBlock info is available\n";
//     return;
//   }
//   std::cout<<"Begin Run: "<<evt_.run<<" in Fill: "<<evt_.fill<<std::endl;
}

// ------------------------------ endRun -------------------------------------
void PilotBladeStudy::endRun(edm::Run const& iRun, edm::EventSetup const& iSetup){
//   // ConditionsInRunBlock
//   edm::Handle<edm::ConditionsInRunBlock> condInRunBlock;
//   iRun.getByToken(condInRunBlockToken_, condInRunBlock);
//   if (!condInRunBlock.isValid()) {
//     std::cout<<"CondInRunBlock info is NOT available" << std::endl;
//   } else {
//     run_.fill = condInRunBlock->lhcFillNumber;
//     run_.run = iRun.run();
//     std::cout<<"End Run: "<<run_.run<<" in Fill: "<<run_.fill<<std::endl;
//   }
//   runTree_->Fill();
}

// -------------------------------- analyze -----------------------------------
void PilotBladeStudy::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup) {
  bool DEBUG = false;
  if (DEBUG) std::cout << "Processing the event " << std::endl;
  
  init_all();
  
  // ----------------------- Read event info -----------------------
  evt_.fill = run_.fill;
  evt_.run  = iEvent.id().run();
  evt_.ls   = iEvent.luminosityBlock();
  evt_.orb  = iEvent.orbitNumber();
  evt_.bx   = iEvent.bunchCrossing();
  evt_.evt  = iEvent.id().event();
  
  edm::Handle<edm::TriggerResults> triggerResults;
  iEvent.getByToken(triggerResultsToken_, triggerResults);
  if (triggerResults.isValid()) {
    evt_.trig=0;
    const edm::TriggerNames& triggerNames = iEvent.triggerNames(*triggerResults);
    for (size_t itrig=0; itrig<triggerNames.size(); itrig++) {
      std::string sname=triggerNames.triggerNames()[itrig];
      for (size_t k=0; k<triggerNames_.size(); k++) {
	if (sname.find(triggerNames_[k])) continue;
	if (triggerResults->accept(itrig)==0) continue;
	evt_.trig|=(1<<k);
      }
    }
  }
  // ----------------------- Read Extra Infos -----------------------
  readExtraInfos();
  evt_.wbc=wbc[iEvent.id().run()];
  evt_.delay=delay[iEvent.id().run()];

  // ----------------------- Read FED errors -----------------------
  std::map<uint32_t, int> federrors;
  readFEDErrors(iEvent, iSetup, SiPixelRawDataErrorToken_, trackingErrorToken_, federrors);
  
  for (std::map<uint32_t, int>::iterator it=federrors.begin(); it!=federrors.end(); it++) printf("DetId %d -- FED error %d\n", it->first, it->second);

  // ----------------------- Analyze digis -----------------------
  analyzeDigis(iEvent, iSetup, siPixelDigisToken_, federrors, 0, cosmicsCase_);
  analyzeDigis(iEvent, iSetup, PBDigisToken_, federrors, 0, cosmicsCase_);
  
  // ----------------------- Analyze clusters ----------------------
  
  analyzeClusters(iEvent, iSetup, siPixelClustersToken_, federrors, 0, cosmicsCase_); 
  analyzeClusters(iEvent, iSetup, PBClustersToken_, federrors, 0, cosmicsCase_);
  
  // ------------------------ Analyze tracks -----------------------
  analyzeTracks(iEvent, iSetup, trajTrackCollToken_, federrors, 0, cosmicsCase_); 
  
  // --------------------- Analyze trajectories --------------------
  analyzeTrajs(iEvent, iSetup, trajTrackCollToken_, federrors, 0, cosmicsCase_); 
  std::cout << "Number of Hits: "
  	    << nPixelHit << " Pixel hit and " << nStripHit
  	    << " Strip hit in the events so far. " << std::endl;
  
  // ---------------------------------------------------------------
    
  // ---------------------- Filling the trees ----------------------
  eventTree_->SetBranchAddress("event", &evt_);
  eventTree_->Fill();

  // Fill the digiTree
  Digi dig;
  digiTree_->SetBranchAddress("event", &evt_);
  digiTree_->SetBranchAddress("digi", &dig);
  digiTree_->SetBranchAddress("module", &dig.mod);
  digiTree_->SetBranchAddress("module_on", &dig.mod_on);
  for (size_t i=0; i<digis_.size(); i++) {
    dig = digis_[i];
    digiTree_->Fill();
  }
  // TODO: this should be like the clustTree

  // Fill the clustTree_
  clustTree_->SetBranchAddress("event", &evt_);
  for (size_t i=0; i<clust_.size(); i++) {
    clustTree_->SetBranchAddress("clust", &clust_[i]);
    clustTree_->SetBranchAddress("module", &clust_[i].mod);
    clustTree_->SetBranchAddress("module_on", &clust_[i].mod_on);
    clustTree_->Fill();
  }
 
  // Fill the trackTree
  TrackData trk;
  trackTree_->SetBranchAddress("event", &evt_);
  trackTree_->SetBranchAddress("track", &trk);
  for (size_t i=0; i<tracks_.size(); i++) {
    trk = tracks_[i];
    trackTree_->Fill();
  }
  // TODO: this should be like the clustTree
  
  TrajMeasurement traj;
  trajTree_->SetBranchAddress("event",      &evt_);
  trajTree_->SetBranchAddress("traj",       &traj);
  trajTree_->SetBranchAddress("module",     &traj.mod);
  trajTree_->SetBranchAddress("module_on",  &traj.mod_on);
  trajTree_->SetBranchAddress("clust",      &traj.clu);
//   trajTree_->SetBranchAddress("clust_pixX", &traj.clu.pixX);
//   trajTree_->SetBranchAddress("clust_pixY", &traj.clu.pixY);
  trajTree_->SetBranchAddress("track",      &traj.trk);
  for (size_t itrk=0; itrk<trajmeas_.size(); itrk++) {
    for (size_t i=0; i<trajmeas_[itrk].size(); i++) {
      float minD=10000.;
      for (size_t jtrk=0; jtrk<trajmeas_.size(); jtrk++) {
	for (size_t j=0; j<trajmeas_[jtrk].size(); j++) {
	  if (jtrk==itrk && j==i) continue;
	  float dx_hit=fabs(trajmeas_[itrk][i].lx-trajmeas_[jtrk][j].lx);
	  float dy_hit=fabs(trajmeas_[itrk][i].ly-trajmeas_[jtrk][j].ly);
	  float D=sqrt(dx_hit*dx_hit+dy_hit*dy_hit);
	  if (D<minD) {
	    minD=D;
	  }
	}
      }
      trajmeas_[itrk][i].d_hit = minD;
      traj = trajmeas_[itrk][i];
      traj.nPixelHit = nPixelHit;
      traj.nStripHit = nStripHit;
      traj.nPBHit    = nPBHit;
      traj.trk = tracks_[itrk];
      trajTree_->Fill();
    }
  }
  // ------------------------ end of filling the trees ------------------------
}
// ----------------------------- end of analyzer ------------------------------

// ------------------------------ Used functions ------------------------------

// ------------------------------- getModuleData ------------------------------
PilotBladeStudy::ModuleData PilotBladeStudy::getModuleData
(uint32_t rawId, const std::map<uint32_t, int>& federrors, std::string scheme) {

  ModuleData offline;
  ModuleData online;

  offline.rawid = online.rawid = rawId;
  int subDetId = DetId(offline.rawid).subdetId();
  
  std::map<uint32_t, int>::const_iterator federrors_it = federrors.find(offline.rawid);
  offline.federr = online.federr = (federrors_it!=federrors.end()) ? federrors_it->second : 0;

  
  // BPIX detector
  if (subDetId == PixelSubdetector::PixelBarrel) {
    PXBDetId pxbid=PXBDetId(offline.rawid);
    offline.det=online.det=0;
    offline.layer=online.layer=pxbid.layer();
    offline.ladder=pxbid.ladder();
    offline.module=pxbid.module();
    offline.half=0;
  if (offline.layer==1) {
    if (offline.ladder==5||offline.ladder==6||offline.ladder==15||offline.ladder==16) {
      offline.half=1;
    }
    offline.outer=offline.ladder%2;
  } else if (offline.layer==2) {
    if (offline.ladder==8||offline.ladder==9||offline.ladder==24||offline.ladder==25) {
    offline.half=1;
  }
  offline.outer=1-offline.ladder%2;
  } else if (offline.layer==3) {
    if (offline.ladder==11||offline.ladder==12||offline.ladder==33||offline.ladder==34) {
      offline.half=1;
    }
    offline.outer=offline.ladder%2;
  }
 
  if (scheme.find("on")==std::string::npos) return offline;
 
  if (offline.layer==1) {
    if (offline.ladder<=5 && offline.ladder>=1)online.ladder = 6-offline.ladder;
    else if (offline.ladder<=15 && offline.ladder>=6)online.ladder = 5-offline.ladder;
    else if (offline.ladder<=20 && offline.ladder>=16) online.ladder = 26-offline.ladder;
  } else if (offline.layer==2) {
    if (offline.ladder<=8 && offline.ladder>=1)online.ladder = 9-offline.ladder;
    else if (offline.ladder<=24 && offline.ladder>=9)online.ladder = 8-offline.ladder;
    else if (offline.ladder<=32 && offline.ladder>=25) online.ladder = 41-offline.ladder;
  } if (offline.layer==3) {
    if (offline.ladder<=11 && offline.ladder>=1) online.ladder = 12-offline.ladder;
    else if (offline.ladder<=33 && offline.ladder>=12) online.ladder = 11-offline.ladder;
    else if (offline.ladder<=44 && offline.ladder>=34) online.ladder = 56-offline.ladder;
  }
 
  if (offline.module>=1 && offline.module<=4)online.module = offline.module-5;
  else if (offline.module>=4 && offline.module<=8)online.module = offline.module-4;
 
  online.shl=online.shell_num();
  online.half=offline.half;
  online.outer=offline.outer;
 
  std::map<std::string, std::string>::const_iterator it;
  std::ostringstream sector;
  sector << "BPix_" << online.shell() << "_SEC";
 
  return online;
  }

  // FPIX detector
  if (subDetId == PixelSubdetector::PixelEndcap) {
    PXFDetId pxfid = PXFDetId(offline.rawid);
    if (pxfid.disk()!= 3) {
      offline.det = online.det=1;
      offline.side= online.side = pxfid.side();
      offline.disk= pxfid.disk();
      offline.blade= pxfid.blade();
      offline.panel= online.panel= pxfid.panel();
      offline.module = online.module = pxfid.module(); // not checked

      if (scheme.find("on")==std::string::npos) return offline;

      online.disk=offline.disk*(offline.side*2-3);

      if (offline.blade<=6 && offline.blade>=1)online.blade = 7-offline.blade;
      else if (offline.blade<=18 && offline.blade>=7)online.blade = 6-offline.blade;
      else if (offline.blade<=24 && offline.blade>=19)online.blade = 31-offline.blade;

      online.shl=online.shell_num();

      std::map<std::string, std::string>::const_iterator it;
      std::ostringstream disk;
      disk << "FPix_" << online.shell() << "_D" << abs(online.disk);
      std::ostringstream panel;
      panel << disk.str() << "_BLD" << abs(online.blade) << "_PNL" << online.panel;

      return online;
    } 
   // Pilot Blade
    else {
      offline.det= online.det= 1;
      offline.disk = pxfid.disk();
      offline.side = online.side = pxfid.side();
      online.disk = offline.disk*(offline.side*2-3);
      offline.blade= pxfid.blade();
      offline.panel= online.panel= pxfid.panel();
      offline.module = online.module = pxfid.module();

      if (scheme.find("on")==std::string::npos) return offline;
      return online;
    }
  }
  return offline;
}
// ---------------------------- end of getModuleData --------------------------

// ------------------------------ readFEDErrors -------------------------------
void PilotBladeStudy::readFEDErrors(const edm::Event& iEvent, 
                                    const edm::EventSetup& iSetup, 
				    edm::EDGetTokenT< edm::DetSetVector<SiPixelRawDataError> > RawDataErrorToken_,
				    edm::EDGetTokenT< edm::EDCollection<DetId> > trackingErrorToken_,
				    std::map<uint32_t, int>& federrors ){  
  bool DEBUG = false;
  int federr[16];
  for (int i=0; i<16; i++) federr[i]=0;
  
  edm::Handle<edm::DetSetVector<SiPixelRawDataError> >  siPixelRawDataErrorCollectionHandle;
  iEvent.getByToken(RawDataErrorToken_, siPixelRawDataErrorCollectionHandle); 
  
  if (siPixelRawDataErrorCollectionHandle.isValid()) {
    if (DEBUG) std::cout << "siPixelRawDataErrorCollectionHandle is valid" << std::endl;
    
    const edm::DetSetVector<SiPixelRawDataError>& siPixelRawDataErrorCollection = *siPixelRawDataErrorCollectionHandle;
    edm::DetSetVector<SiPixelRawDataError>::const_iterator itPixelErrorSet = siPixelRawDataErrorCollection.begin();

    for (; itPixelErrorSet!=siPixelRawDataErrorCollection.end(); itPixelErrorSet++) {
      edm::DetSet<SiPixelRawDataError>::const_iterator itPixelError=itPixelErrorSet->begin();
      for(; itPixelError!=itPixelErrorSet->end(); ++itPixelError) {
        if (DEBUG) { 
          std::cout << "FED ID: " << itPixelError->getFedId() << std::endl;
          std::cout << "Word32: " << itPixelError->getWord32() << std::endl;
          std::cout << "Word64: " << itPixelError->getWord64() << std::endl;
          std::cout << "Type: " << itPixelError->getType() << std::endl;
          std::cout << "Error message: " << itPixelError->getMessage() << std::endl;
	  std::cout << "detId" << itPixelErrorSet->detId() << std::endl;
        }
	int type = itPixelError->getType();
	if (type>24&&type<=40) federr[type-25]++;
	else std::cout<<"ERROR: Found new FED error with not recognised Error type: "<<type<<std::endl;
        if (itPixelErrorSet->detId()!=0xffffffff) {
          DetId detId(itPixelErrorSet->detId());
          federrors.insert(std::pair<uint32_t,int>(detId.rawId(), type));
	}
      }
    }
    for (int i=0; i<16; i++) {
      if (federr[i]!=0) {
        evt_.federrs[evt_.federrs_size][0]=federr[i];
        evt_.federrs[evt_.federrs_size][1]=i+25;
        evt_.federrs_size++;
      }
    }
  }
  
  // Run this if siPixelRawDataErrorCollection is not available (eg in RECO)
  if (!siPixelRawDataErrorCollectionHandle.isValid()) {
    
    if (DEBUG) std::cout << "siPixelRawDataErrorCollectionHandle is *NOT* valid" << std::endl;
    // Tracking Error list
    edm::Handle<edm::EDCollection<DetId> > TrackingErrorDetIdCollectionHandle;
    iEvent.getByToken(trackingErrorToken_, TrackingErrorDetIdCollectionHandle);
    
    if (TrackingErrorDetIdCollectionHandle.isValid()) {
      const edm::EDCollection<DetId>& TrackingErrorDetIdCollection = *TrackingErrorDetIdCollectionHandle;
      for (size_t i=0; i<TrackingErrorDetIdCollection.size(); i++) {
        federrors.insert(std::pair<uint32_t,int>(TrackingErrorDetIdCollection[i].rawId(), 29));
        federr[4]++;
      }
    }
    
    // User Error List (Overflow only by default)
    edm::Handle<edm::EDCollection<DetId> > UserErrorDetIdCollectionHandle;
    iEvent.getByToken(userErrorToken_, UserErrorDetIdCollectionHandle);
    
    if (UserErrorDetIdCollectionHandle.isValid()) {
      const edm::EDCollection<DetId>& UserErrorDetIdCollection = *UserErrorDetIdCollectionHandle;
      for (size_t i=0; i<UserErrorDetIdCollection.size(); i++) {
        federrors.insert(std::pair<uint32_t,int>(UserErrorDetIdCollection[i].rawId(), 40));
        federr[15]++;
      }
    }
    for (int i=0; i<16; i++) {
      if (federr[i]!=0) {
        evt_.federrs[evt_.federrs_size][0]=federr[i];
        evt_.federrs[evt_.federrs_size][1]=i+25;
        evt_.federrs_size++;
      }
    }
  } 
}
// ---------------------------- end of readFEDErrors --------------------------

// ------------------------------ analyzeDigis -----------------------------

void PilotBladeStudy::analyzeDigis(const edm::Event& iEvent, 
                                         const edm::EventSetup& iSetup,  
                                         edm::EDGetTokenT< edm::DetSetVector<PixelDigi> > digiColl,
					 std::map<uint32_t, int> federrors,
					 int verbosity,
					 bool cosmicsCase
                                     ) {
  
  edm::Handle<edm::DetSetVector<PixelDigi> > digiCollectionHandle;
  iEvent.getByToken(digiColl, digiCollectionHandle);
  
  if (!digiCollectionHandle.isValid()) {
    if (verbosity>1) std::cout<< "The digiCollectionHandle is invalid" << std::endl;
  } else {
    const edm::DetSetVector<PixelDigi>& digiCollection = *digiCollectionHandle;
    edm::DetSetVector<PixelDigi>::const_iterator itDigiSet =  digiCollection.begin();
	if (verbosity>2) std::cout << "Looping on the itDigiSet, it's size is " << digiCollection.size() << std::endl;
    for (; itDigiSet!=digiCollection.end(); itDigiSet++) {
      DetId detId(itDigiSet->detId());
      unsigned int subDetId=detId.subdetId();

      ModuleData module = getModuleData(detId.rawId(), federrors);
      ModuleData module_on = getModuleData(detId.rawId(), federrors, "online");

      if (verbosity>2) std::cout << "Looping on the digi sets " << std::endl;
      if (cosmicsCase==true && verbosity)  std::cout << "This is a Cosmics case -- we save everything" << std::endl;
      if (subDetId!=PixelSubdetector::PixelEndcap && subDetId!=PixelSubdetector::PixelBarrel && cosmicsCase==false) {
        if (verbosity>1) std::cout << "Not a pixel digi -- skipping the event" << std::endl;
        continue;
      }
      // Take only the FPIX- pixel digis
      //if ((subDetId!=PixelSubdetector::PixelEndcap || module_on.disk>0) && cosmicsCase==false) {
      //  if (verbosity>1) std::cout << "Not a FPIX -Z digi -- skipping it" << std::endl;
      //continue;
      //}
      
      if (module_on.disk==-3 && (verbosity)) std::cout << "Pilot Blade digi: " << std::endl;
      edm::DetSet<PixelDigi>::const_iterator itDigi=itDigiSet->begin();
      for(; itDigi!=itDigiSet->end(); ++itDigi) {
        Digi digi;
        digi.i=itDigi-itDigiSet->begin();
        digi.row=itDigi->row();
        digi.col=itDigi->column();
        digi.adc=itDigi->adc();
        digi.mod=module;
        digi.mod_on=module_on;
        digis_.push_back(digi);
        if (verbosity) {
          std::cout<<"\t#"<<digi.i<<" adc: "<<digi.adc<<" at col:"<<digi.col<<", row:"<<digi.row<<")";
          std::cout<<std::endl;
        }
      }
    } // end of the loop on digis
  } // end of the validity check
}
// ---------------------------- end of analyzeDigis --------------------------

// ------------------------------ analyzeClusters -----------------------------

void PilotBladeStudy::analyzeClusters(const edm::Event& iEvent, 
                                         const edm::EventSetup& iSetup,  
                                         edm::EDGetTokenT< edmNew::DetSetVector<SiPixelCluster> > clusterColl,
                                         std::map<uint32_t, int> federrors,
					 int verbosity,
					 bool cosmicsCase
                                     ) {
  bool DEBUGClusters = false;
  if (verbosity) DEBUGClusters = true;
  std::map<unsigned int, int> nclu_mod;
  
  // Get the handle for clusters
  edm::Handle<edmNew::DetSetVector<SiPixelCluster> > clusterCollectionHandle;
  iEvent.getByToken(clusterColl, clusterCollectionHandle);
  
  if (!clusterCollectionHandle.isValid()) {
     if (verbosity>1) std::cout<< "The clusterCollectionHandle is invalid" << std::endl;
  } else {
    // Create a itarator that loops on the cluster set collection
    const edmNew::DetSetVector<SiPixelCluster>& clusterCollection = *clusterCollectionHandle;
    edmNew::DetSetVector<SiPixelCluster>::const_iterator itClusterSet =  clusterCollection.begin();
    
    // Get the geometry of the tracker for converting the LocalPoint to a GlobalPoint
    edm::ESHandle<TrackerGeometry> tracker;
    iSetup.get<TrackerDigiGeometryRecord>().get(tracker);    
    const TrackerGeometry *tkgeom = &(*tracker);


    // Choose the CPE Estimator that will be used to estimate the LocalPoint of the cluster
    edm::ESHandle<PixelClusterParameterEstimator> cpEstimator;
    iSetup.get<TkPixelCPERecord>().get("PixelCPEGeneric", cpEstimator);
    if (!cpEstimator.isValid()) {
      std::cout << "The cpEstimator is not valid!" << std::endl;
    }
    const PixelClusterParameterEstimator &cpe(*cpEstimator);

    // Start looping on the cluster sets
    for (; itClusterSet != clusterCollection.end(); itClusterSet++) {
      DetId detId(itClusterSet->id());
      unsigned int subDetId=detId.subdetId();
      const PixelGeomDetUnit *pixdet = (const PixelGeomDetUnit*) tkgeom->idToDetUnit(detId);         
      
      ModuleData module = getModuleData(detId.rawId(), federrors);
      ModuleData module_on = getModuleData(detId.rawId(), federrors, "online");

      if (DEBUGClusters) std::cout << "Looping on the cluster sets ";
      
      // Take only pixel clusters. If this is a cosmicsCase then we save everything
      if (subDetId!=PixelSubdetector::PixelEndcap && subDetId!=PixelSubdetector::PixelBarrel
	&& cosmicsCase==false) {
        std::cout << "Not a pixel cluster" << std::endl;
        continue;
      }
      
      // Take only the FPIX- pixel clusters
      //if ((subDetId!=PixelSubdetector::PixelEndcap || module_on.disk>0) && cosmicsCase==false) {
	//if (verbosity>1) std::cout << "Not a FPIX -Z cluster -- skipping it" << std::endl;
      // continue;
      //}

      // Create a itarator that loops on the clusters which are in the set
      edmNew::DetSet<SiPixelCluster>::const_iterator itCluster=itClusterSet->begin();
      for(; itCluster!=itClusterSet->end(); ++itCluster) {
        if (DEBUGClusters) std::cout << "Looping on the clusters in the set" << std::endl;
	
	// Get the LocalPoint from PixelClusterParameterEstimator
	const Surface& surface = tracker->idToDet(detId)->surface();
	LocalPoint lp(-9999., -9999., -9999.);
	if (usePixelCPE_) {
	  PixelClusterParameterEstimator::ReturnType params = cpe.getParameters(*itCluster,*pixdet);
	  lp = std::get<0>(params);
	  if (DEBUGClusters) std::cout << "PixelClusterParameterEstimator: " << lp << std::endl;
	}
	
        Cluster clust;	
	GlobalPoint gp = surface.toGlobal(lp);
	
        clust.x=itCluster->x();
        clust.y=itCluster->y();
        clust.lx=lp.x();
	clust.ly=lp.y();
        clust.glx = gp.x();
        clust.gly = gp.y();
        clust.glz = gp.z();
	
	clust.size=itCluster->size();
        clust.charge=itCluster->charge()/1000.0;
        
        clust.mod    = module;
        clust.mod_on = module_on;
	
	if (!nclu_mod.count(detId.rawId())) nclu_mod[detId.rawId()] = 0;
	nclu_mod[detId.rawId()]++;
	clust.nclu_mod = nclu_mod[detId.rawId()];
        clust_.push_back(clust);
      }
    } // loop on cluster sets
  }
}
// --------------------------- end of analyzeClusters -------------------------

// ------------------------------ analyzeTracks -----------------------------
void PilotBladeStudy::analyzeTracks(const edm::Event& iEvent, 
                                         const edm::EventSetup& iSetup,  
                                         edm::EDGetTokenT< TrajTrackAssociationCollection > trackColl,
                                         std::map<uint32_t, int> federrors,
					 int verbosity,
					 bool cosmicsCase
                                     ) {
  bool DEBUGTracks = false;
  if (verbosity) DEBUGTracks = true;
  
  edm::Handle<TrajTrackAssociationCollection> trajTrackCollectionHandle;
  iEvent.getByToken(trackColl, trajTrackCollectionHandle);
  
  if (!trajTrackCollectionHandle.isValid()) {
    if (verbosity>1) std::cout << "trajTrackCollectionHandle is not valid, exiting the loop" << std::endl;
  } else {
    if (DEBUGTracks) std::cout << " Run " << evt_.run << " Event " << evt_.evt;
    if (DEBUGTracks) std::cout << " Number of tracks = " << trajTrackCollectionHandle->size() << std::endl;
    
    TrajTrackAssociationCollection::const_iterator itTrajTrack=trajTrackCollectionHandle->begin();
    for (;itTrajTrack!=trajTrackCollectionHandle->end(); itTrajTrack++) {
      const Trajectory& traj  = *itTrajTrack->key;
      const Track&      track = *itTrajTrack->val;
      
      TrackData track_;
      track_.nPixelHit = 0;
      track_.nStripHit = 0;
      track_.pt  = track.pt();
      track_.dxy = track.dxy();
      track_.dz  = track.dz();
      track_.eta = track.eta();
      track_.phi = track.phi();
      track_.highPurity= (track.quality(reco::TrackBase::highPurity)) ? 1 : 0;
	  
      
      std::vector<TrajectoryMeasurement> trajMeasurements = traj.measurements();
      std::vector<TrajectoryMeasurement>::const_iterator itTraj;
      for(itTraj=trajMeasurements.begin(); itTraj!=trajMeasurements.end(); ++itTraj) {
	TransientTrackingRecHit::ConstRecHitPointer recHit = itTraj->recHit();

	if(recHit->geographicalId().det() != DetId::Tracker) continue;
	uint subDetId = recHit->geographicalId().subdetId();
      
	if (recHit->isValid()) {
	  if      (subDetId == PixelSubdetector::PixelBarrel) track_.nPixelHit++;
	  else if (subDetId == PixelSubdetector::PixelEndcap) track_.nPixelHit++;
	  else if (subDetId == StripSubdetector::TIB) track_.nStripHit++;
	  else if (subDetId == StripSubdetector::TOB) track_.nStripHit++;
	  else if (subDetId == StripSubdetector::TID) track_.nStripHit++;
	  else if (subDetId == StripSubdetector::TEC) track_.nStripHit++;
	}
      }
      tracks_.push_back(track_);
    }
  }
}
// --------------------------- end of analyzeTracks -------------------------

// ------------------------------ analyzeTrajs -----------------------------
void PilotBladeStudy::analyzeTrajs(const edm::Event& iEvent, 
                                         const edm::EventSetup& iSetup,  
                                         edm::EDGetTokenT< TrajTrackAssociationCollection > trackColl,
                                         std::map<uint32_t, int> federrors,
					 int verbosity,
					 bool cosmicsCase
                                     ) {
  bool DEBUGTrajs = false;
  if (verbosity) DEBUGTrajs = true;
  
  edm::Handle<TrajTrackAssociationCollection> trajTrackCollectionHandle;
  iEvent.getByToken(trackColl, trajTrackCollectionHandle);
  
  if (!trajTrackCollectionHandle.isValid()) {
    if (verbosity>1) std::cout << "trajTrackCollectionHandle is not valid, exiting the loop" << std::endl;
  } else if ((trajTrackCollectionHandle->size())!=0){
    if (DEBUGTrajs) std::cout << "Number of tracks = " << trajTrackCollectionHandle->size() << std::endl;

     // --------------------- loop on the trajTrackCollection ----------------------
    TrajTrackAssociationCollection::const_iterator itTrajTrack=trajTrackCollectionHandle->begin();
    for (;itTrajTrack!=trajTrackCollectionHandle->end(); itTrajTrack++) {
      const Trajectory& traj  = *itTrajTrack->key;
          
      TrajectoryStateCombiner trajStateComb;
      
      // ----------------------- loop on the trajMeasurements -----------------------

      std::vector<TrajectoryMeasurement> trajMeasurements = traj.measurements();
      std::vector<TrajectoryMeasurement>::const_iterator itTraj;
      std::vector<TrajMeasurement> trajmeas; 
      
      for(itTraj=trajMeasurements.begin(); itTraj!=trajMeasurements.end(); ++itTraj) {
	
	TransientTrackingRecHit::ConstRecHitPointer recHit = itTraj->recHit();
	
	// Cutting on which trajectories we process
	if(recHit->geographicalId().det() != DetId::Tracker) continue;

	uint subDetId = recHit->geographicalId().subdetId();
	if (verbosity>1) std::cout << "detector ID: " << subDetId << std::endl;
		
	if      (subDetId == PixelSubdetector::PixelBarrel) nPixelHit++;
	else if (subDetId == PixelSubdetector::PixelEndcap) nPixelHit++;
	else if (subDetId == StripSubdetector::TIB) nStripHit++;
	else if (subDetId == StripSubdetector::TOB) nStripHit++;
	else if (subDetId == StripSubdetector::TID) nStripHit++;
	else if (subDetId == StripSubdetector::TEC) nStripHit++;

	if( (subDetId == 3 || subDetId == 4 || subDetId == 5 ||subDetId == 6) && cosmicsCase == false) {
          if (verbosity>2) std::cout << " Hit found on the Strip detector " << std::endl;
          continue;
        }

	TrajMeasurement meas;
                
        meas.mod    = getModuleData(recHit->geographicalId().rawId(), federrors);
        meas.mod_on = getModuleData(recHit->geographicalId().rawId(), federrors, "online");
		
	// Hit type codes: valid = 0, missing = 1, inactive = 2
	meas.type=NOVAL_I;
	if 	(recHit->getType() == TrackingRecHit::valid) 	meas.type=0;
        else if (recHit->getType() == TrackingRecHit::missing) 	meas.type=1;
        else if (recHit->getType() == TrackingRecHit::inactive) meas.type=2;
	
	TrajectoryStateOnSurface predTrajState=trajStateComb(itTraj->forwardPredictedState(),
                                                               itTraj->backwardPredictedState());       
	
	meas.lx=predTrajState.localPosition().x();
        meas.ly=predTrajState.localPosition().y();
	meas.lx_err=predTrajState.localError().positionError().xx();
        meas.ly_err=predTrajState.localError().positionError().yy();

	std::map<unsigned int,std::vector<FiducialRegion> >::iterator it_mod=fidReg_.find(recHit->geographicalId().rawId());
	if (it_mod!=fidReg_.end()) {
	  int rocx=meas.getROCx();
	  int rocy=meas.getROCy();
	  for (size_t i=0; i<it_mod->second.size(); i++) {
	    if (rocx==it_mod->second[i].rocX && rocy==it_mod->second[i].rocY) {
	      if (meas.isWithinROCFiducial(it_mod->second[i].marginX, it_mod->second[i].marginY)) meas.type+=100;
	    }
	  }
	}

        meas.glx=predTrajState.globalPosition().x();
        meas.gly=predTrajState.globalPosition().y();
        meas.glz=predTrajState.globalPosition().z();
	
        meas.onEdge=1;
        if (fabs(meas.lx)<0.55 && fabs(meas.ly)<3.0) {
          meas.onEdge=0;         
        }
        
        LocalTrajectoryParameters predTrajParam= predTrajState.localParameters();
        LocalVector dir = predTrajParam.momentum()/predTrajParam.momentum().mag();
        meas.alpha = atan2(dir.z(), dir.x());
        meas.beta = atan2(dir.z(), dir.y());
	
	// If Pilot Blade
        if (meas.mod.disk == 3) {
	  if (DEBUGTrajs) {
	      std::cout << "***************************\n** PilotBlade hit found! **"<< std::endl;
	      std::cout << "***************************" << std::endl;
	  }
	  nPBHit++;
	  
	  // Finding the closest cluster and filling it's properties
	  ClustData PBCluOnTrack;
          std::cout << " Finding the closest Pilot Blade cluster " << std::endl;
	  findClosestClusters(iEvent, iSetup, recHit->geographicalId().rawId(),
			      meas.lx, meas.ly, meas.dx_cl, meas.dy_cl, 
                              PBClustersToken_, PBCluOnTrack);
	  meas.clu = PBCluOnTrack;
	  std::cout << " Position of the Pilot Blade RecHit (lx,ly): " 
		    << meas.lx << "," << meas.ly << std::endl;
	  std::cout << " Dx distance of the closest Pilot Blade cluster: " << meas.dx_cl << std::endl;
	  std::cout << " Dy distance of the closest Pilot Blade cluster: " << meas.dy_cl << std::endl;
	  if (meas.dx_cl != NOVAL_F) {
	    meas.d_cl = sqrt(meas.dx_cl*meas.dx_cl+meas.dy_cl*meas.dy_cl);
	  } else {
	    meas.d_cl = NOVAL_F;
	  }
	}
	trajmeas.push_back(meas);         
      }
      trajmeas_.push_back(trajmeas);
    }
  }
}
// --------------------------- end of analyzeTrajs -------------------------


// ---------------------------- findClosestClusters ---------------------------
void PilotBladeStudy::findClosestClusters(
	      const edm::Event& iEvent, 
	      const edm::EventSetup& iSetup, uint32_t rawId, 
	      float lx, float ly, float& dx_cl, float& dy_cl, 
	      edm::EDGetTokenT< edmNew::DetSetVector<SiPixelCluster> > clusterColl,
	      ClustData& clu) {
  
  bool DEBUGfindClust = false;
  
  // Choose the CPE Estimator that will be used to estimate the LocalPoint of the nearest cluster
  edm::ESHandle<PixelClusterParameterEstimator> cpEstimator;
  iSetup.get<TkPixelCPERecord>().get("PixelCPEGeneric", cpEstimator);
  if (!cpEstimator.isValid()) {
    std::cout << "The cpEstimator is not valid!" << std::endl;
  }
  const PixelClusterParameterEstimator &cpe(*cpEstimator);
  
  // Get the geometry of the tracker for converting the LocalPoint to a GlobalPoint
  edm::ESHandle<TrackerGeometry> tracker;
  iSetup.get<TrackerDigiGeometryRecord>().get(tracker);
  if (!tracker.isValid()) {
    std::cout << "The tracker record is not valid!" << std::endl;
    return;
  }
  const TrackerGeometry *tkgeom = &(*tracker);
  
  // Get the handle for clusters
  edm::Handle<edmNew::DetSetVector<SiPixelCluster> > clusterCollectionHandle;
  iEvent.getByToken(clusterColl, clusterCollectionHandle);
  
  if (!clusterCollectionHandle.isValid()) {
    std::cout << "The clusterCollectionHandle is not valid!" << std::endl;
    return;
  }
  // Create a itarator that loops on the cluster set collection
  const edmNew::DetSetVector<SiPixelCluster>& clusterCollection= *clusterCollectionHandle;
  edmNew::DetSetVector<SiPixelCluster>::const_iterator itClusterSet = clusterCollection.begin();
  
  // Start looping on the cluster sets
  for ( ; itClusterSet!=clusterCollection.end(); itClusterSet++) {
    
    float minD=10000.;
    DetId detId(itClusterSet->id());
    unsigned int subDetId=detId.subdetId();
    const PixelGeomDetUnit *pixdet = (const PixelGeomDetUnit*) tkgeom->idToDetUnit(detId);
    
    if (detId.rawId()!=rawId) {
      if (DEBUGfindClust) std::cout << " Wrong rawId " << std::endl;
      continue;
    }
    
    if (subDetId!=PixelSubdetector::PixelBarrel &&  subDetId!=PixelSubdetector::PixelEndcap) {
      std::cout << " Not a pixel cluster!" << std::endl; 
      continue;
    }
    
    edmNew::DetSet<SiPixelCluster>::const_iterator itCluster=itClusterSet->begin();
    edmNew::DetSet<SiPixelCluster>::const_iterator itClosestCluster=itClusterSet->begin();
    
    for(; itCluster!=itClusterSet->end(); ++itCluster) {
      LocalPoint lp(itCluster->x(), itCluster->y(), 0.);
      
      if (usePixelCPE_) {
	PixelClusterParameterEstimator::ReturnType params = cpe.getParameters(*itCluster,*pixdet);
	lp = std::get<0>(params);
	if (DEBUGfindClust) std::cout << "PixelClusterParameterEstimator: " << lp << std::endl;
      }
      
      float lpx=lp.x();
      float lpy=lp.y();
      std::map<unsigned int,PositionCorrection>::const_iterator itCorr=posCorr_.find(detId.rawId());
      if (itCorr!=posCorr_.end()) {
	lpx+=itCorr->second.dx;
	lpy+=itCorr->second.dy;
      }

      float D = sqrt((lpx-lx)*(lpx-lx)+(lpy-ly)*(lpy-ly));
      if (DEBUGfindClust) std::cout << "Value of the D: " << D << std::endl; 
      if (D<minD) {
	minD=D;
	dx_cl=lpx;
	dy_cl=lpy;
	itClosestCluster = itCluster;
      } 
    } // loop on cluster sets
    
    if (minD<9999.) {
      dx_cl=dx_cl-lx;
      dy_cl=dy_cl-ly;
    }
    
    if (minD<9999.) {
       clu.charge=(itClosestCluster)->charge()/1000.0;
       clu.size=(itClosestCluster)->size();
//       clu.edge=NOVAL_F;
//       clu.sizeX=(itClosestCluster)->sizeX();
//       clu.sizeY=(itClosestCluster)->sizeY();
      clu.x=(itClosestCluster)->x();
      clu.y=(itClosestCluster)->y();
//       for (int i=0; i<(itClosestCluster)->size() && i<1000; i++) {
// 	clu.adc[i]=float((itClosestCluster)->pixelADC()[i])/1000.0;
// 	clu.pixX[i]=(((itClosestCluster)->pixels())[i]).x;
// 	clu.pixY[i]=(((itClosestCluster)->pixels())[i]).y;
    }
  }
}
// ------------------------ end of findClosestClusters ------------------------
 
// ----------------------------- readExtraInfos -------------------------------
  
void PilotBladeStudy::readExtraInfos(){
  wbc.insert(std::pair<size_t,int>(265352,167)); 
  delay.insert(std::pair<size_t,int>(269807,24));
}
// ------------------------ end of readExtraInfos ------------------------

// Other useful things
/*
  DetID == 344130820 || DetID == 344131844 || DetID == 344132868 
  || DetID == 344133892 || DetID == 344131076 || DetID == 344132100 
  || DetID == 344133124 || DetID == 344134148 )
*/
DEFINE_FWK_MODULE(PilotBladeStudy);

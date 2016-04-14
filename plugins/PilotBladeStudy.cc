#include "PilotBladeStudy.h"

using namespace std;
using namespace edm;
using namespace reco;

// ------------------------- Constructor & Destructor  ------------------------
PilotBladeStudy::PilotBladeStudy(edm::ParameterSet const& iConfig) : iConfig_(iConfig) {
  eventTree_= NULL;
  runTree_  = NULL;
  digiTree_ = NULL;
  outfile_  = NULL;
  
  BSToken_                  = consumes<reco::BeamSpot>(edm::InputTag("offlineBeamSpot"));
  condInRunBlockToken_      = mayConsume<edm::ConditionsInRunBlock, InRun >(edm::InputTag("conditionsInEdm"));
  condInLumiBlockToken_     = mayConsume<edm::ConditionsInLumiBlock, InLumi >(edm::InputTag("conditionsInEdm"));
  
  siPixelDigisToken_        = consumes<edm::DetSetVector<PixelDigi> >(edm::InputTag("siPixelDigis"));
  PBDigisToken_             = consumes<edm::DetSetVector<PixelDigi> >(edm::InputTag("PBDigis"));
  
  trackingErrorToken_	    = consumes<edm::EDCollection<DetId> >(edm::InputTag("siPixelDigis"));
  SiPixelRawDataErrorToken_ = consumes< edm::DetSetVector<SiPixelRawDataError> >(edm::InputTag("siPixelDigis"));
  userErrorToken_	    = consumes<edm::EDCollection<DetId> >(edm::InputTag("siPixelDigis", "UserErrorModules"));
}

PilotBladeStudy::~PilotBladeStudy() { }

// ------------------------------ beginJob ------------------------------------
void PilotBladeStudy::beginJob() {
  
  std::string fileName="test.root";
  if (iConfig_.exists("fileName")) {  
    fileName=iConfig_.getParameter<std::string>("fileName");
  }
  
  outfile_ = new TFile(fileName.c_str(), "RECREATE");
  
  EventData         evt_;
  Digi		    digi;
  
  eventTree_ = new TTree("eventTree", "The event");
  eventTree_->Branch("event", &evt_, evt_.list.data());
  
  runTree_ = new TTree("runTree", "The run");
  runTree_->Branch("run", &run_, run_.list.data());

  digiTree_ = new TTree("digiTree", "Pixel digis");
  digiTree_->Branch("event", &evt_, evt_.list.data());
  digiTree_->Branch("digi", &digi, digi.list.data());
  digiTree_->Branch("module", &digi.mod, digi.mod.list.data());
  digiTree_->Branch("module_on", &digi.mod_on, digi.mod_on.list.data());
}

// ------------------------------ endJob --------------------------------------
void PilotBladeStudy::endJob() {
  outfile_->Write();
  outfile_->Close();
  delete outfile_;
}

// ------------------------------ beginRun ------------------------------------
void PilotBladeStudy::beginRun(edm::Run const& iRun, edm::EventSetup const& iSetup){
  run_.init();
  run_.run = iRun.run();
  
  // ConditionsInRunBlock for fill number
  edm::Handle<edm::ConditionsInRunBlock> condInRunBlock;
  iRun.getByToken(condInRunBlockToken_, condInRunBlock);
  if (condInRunBlock.isValid()) {
     run_.fill = condInRunBlock->lhcFillNumber;
  } else if (run_.run==1) {
   run_.fill = 0;
  } else {
    std::cout<<"** ERROR (beginRun): no condInRunBlock info is available\n";
    return;
  }
  std::cout<<"Begin Run: "<<evt_.run<<" in Fill: "<<evt_.fill<<std::endl;
}

// ------------------------------ endRun -------------------------------------
void PilotBladeStudy::endRun(edm::Run const& iRun, edm::EventSetup const& iSetup){
  // ConditionsInRunBlock
  edm::Handle<edm::ConditionsInRunBlock> condInRunBlock;
  iRun.getByToken(condInRunBlockToken_, condInRunBlock);
  if (!condInRunBlock.isValid()) {
    std::cout<<" CondInRunBlock info is NOT available" << std::endl;
  } else {
    run_.fill = condInRunBlock->lhcFillNumber;
    run_.run = iRun.run();
    std::cout<<"End Run: "<<run_.run<<" in Fill: "<<run_.fill<<std::endl;
  }
  runTree_->Fill();
}

// -------------------------------- analyze -----------------------------------
void PilotBladeStudy::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup) {
  bool DEBUG = false;
  bool cosmicsCase = false;
  if (DEBUG) std::cout << "Processing the event " << std::endl;
  
  init_all();
  
  // ----------------------- Read event info -----------------------
  evt_.fill = run_.fill;
  evt_.run  = iEvent.id().run();
  evt_.ls   = iEvent.luminosityBlock();
  evt_.orb  = iEvent.orbitNumber();
  evt_.bx   = iEvent.bunchCrossing();
  evt_.evt  = iEvent.id().event();
  evt_.wbc  = wbc[iEvent.id().run()];

  // ----------------------- Read FED errors -----------------------
  std::map<uint32_t, int> federrors;
  ReadFEDErrors(iEvent, iSetup, SiPixelRawDataErrorToken_, trackingErrorToken_, federrors);
  
  // ----------------------- Analyze digis -----------------------
  analyzeDigis(iEvent, iSetup, siPixelDigisToken_, federrors, 0, cosmicsCase=true);
  analyzeDigis(iEvent, iSetup, PBDigisToken_, federrors, 1, cosmicsCase=true);
    
  // ---------------------- Filling the trees ----------------------
  eventTree_->SetBranchAddress("event", &evt_);
  eventTree_->Fill();

  // fill the digiTree
  Digi dig;
  digiTree_->SetBranchAddress("event", &evt_);
  digiTree_->SetBranchAddress("digi", &dig);
  digiTree_->SetBranchAddress("module", &dig.mod);
  digiTree_->SetBranchAddress("module_on", &dig.mod_on);
  for (size_t i=0; i<digis_.size(); i++) {
    dig = digis_[i];
    digiTree_->Fill();
  }
  
}//end of analyzer

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

// ------------------------------ ReadFEDErrors -------------------------------
void PilotBladeStudy::ReadFEDErrors(const edm::Event& iEvent, 
                                    const edm::EventSetup& iSetup, 
				    edm::EDGetTokenT< edm::DetSetVector<SiPixelRawDataError> > RawDataErrorToken_,
				    edm::EDGetTokenT< edm::EDCollection<DetId> > trackingErrorToken_,
				    std::map<uint32_t, int> federrors ){  
  bool DEBUG = false;
  int federr[16];
  for (int i=0; i<16; i++) federr[i]=0;
  //assert(evt_.federrs_size==0);
  
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
        }
        if (itPixelErrorSet->detId()!=0xffffffff) {
          DetId detId(itPixelErrorSet->detId());
          int type = itPixelError->getType();
          federrors.insert(std::pair<uint32_t,int>(detId.rawId(), type));
          if (type>24&&type<=40) federr[type-25]++;
          else std::cout<<"ERROR: Found new FED error with not recognised Error type: "<<type<<std::endl;
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
    
    std::cout << "siPixelRawDataErrorCollectionHandle is *NOT* valid" << std::endl;
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
// ---------------------------- end of ReadFEDErrors --------------------------

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
    std::cout<< "The digiCollectionHandle is invalid" << std::endl;
  } else {
    const edm::DetSetVector<PixelDigi>& digiCollection = *digiCollectionHandle;
    edm::DetSetVector<PixelDigi>::const_iterator itDigiSet =  digiCollection.begin();

    for (; itDigiSet!=digiCollection.end(); itDigiSet++) {
      DetId detId(itDigiSet->detId());
      unsigned int subDetId=detId.subdetId();

      ModuleData module = getModuleData(detId.rawId(), federrors);
      ModuleData module_on = getModuleData(detId.rawId(), federrors, "online");

      if (verbosity) std::cout << "Looping on the digi sets " << std::endl;
      if (cosmicsCase==true && verbosity)  std::cout << "This is a Cosmics case -- we save everything" << std::endl;
      if (subDetId!=PixelSubdetector::PixelEndcap && subDetId!=PixelSubdetector::PixelBarrel && cosmicsCase==false) {
        std::cout << "Not a pixel digi -- skipping the event" << std::endl;
        continue;
      }
      // Take only the FPIX pixel digis
      if (subDetId!=PixelSubdetector::PixelEndcap && cosmicsCase==false) {
        std::cout << "Not a FPIX digi -- skipping the event" << std::endl;
        continue;
      }
      
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

// Other useful things
/*
  DetID == 344130820 || DetID == 344131844 || DetID == 344132868 
  || DetID == 344133892 || DetID == 344131076 || DetID == 344132100 
  || DetID == 344133124 || DetID == 344134148 )
*/
DEFINE_FWK_MODULE(PilotBladeStudy);

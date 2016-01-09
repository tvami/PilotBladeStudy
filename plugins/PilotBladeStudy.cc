#include "PilotBladeStudy.h"
#include "DataFormats/Math/interface/deltaPhi.h"

using namespace std;
using namespace edm;
using namespace reco;

// ------------------------- Constructor & Destructor  ------------------------
PilotBladeStudy::PilotBladeStudy(edm::ParameterSet const& iConfig) : iConfig_(iConfig) {
  eventTree_=NULL;
  trajTree_=NULL;
  clustTree_=NULL;
  outfile_=NULL;
  
  isNewLS_ = false; 
  usePixelCPE_=false;
  
  //tokens
  tok_BS_           = consumes<reco::BeamSpot>(edm::InputTag("offlineBeamSpot"));
  tok_siPixelDigis_ = consumes< edm::DetSetVector<SiPixelRawDataError> >(edm::InputTag("siPixelDigis"));
  tok_siPixelClusters_ = consumes< edmNew::DetSetVector<SiPixelCluster> >(edm::InputTag("siPixelClusters"));
  tok_PBClusters_ = consumes< edmNew::DetSetVector<SiPixelCluster> >(edm::InputTag("PBClusters"));
  tok_Refitter_ = consumes< edm::AssociationMap<edm::OneToOne<std::vector<Trajectory>,std::vector<reco::Track>,unsigned short> > >(edm::InputTag("Refitter"));
//   tok_conditionsInEdm_ = consumes<edm::ConditionsInRunBlock>(edm::InputTag("conditionsInEdm")); // several errors using this

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
  
  outfile_ = new TFile(fileName.c_str(), "RECREATE");
  std::cout<<"Output file created: "<<outfile_->GetName()<<std::endl;
  
  EventData         evt_;
  Cluster           clust;
  TrajMeasurement   trajmeas;
  
  eventTree_ = new TTree("eventTree", "The event");
  eventTree_->Branch("event",     &evt_,            evt_.list.data());
  
  clustTree_ = new TTree("clustTree", "Pixel clusters in the event");
  clustTree_->Branch("event",       &evt_,            evt_.list.data());
  clustTree_->Branch("clusters",    &clust,           clust.list.data());
  clustTree_->Branch("clust_pixX",  &clust.pixX,      "pixX[size]/F");
  clustTree_->Branch("clust_pixY",  &clust.pixY,      "pixY[size]/F");
  clustTree_->Branch("module",      &clust.mod,       clust.mod.list.data());
  clustTree_->Branch("module_on",   &clust.mod_on,    clust.mod_on.list.data());

  
  trajTree_ = new TTree("trajTree", "The trajectory measurements in the event");
  trajTree_->Branch("event",        &evt_,              evt_.list.data());
  trajTree_->Branch("track",        &trajmeas.trk,      trajmeas.trk.list.data());
  trajTree_->Branch("traj",         &trajmeas,          trajmeas.list.data());
  trajTree_->Branch("clust",        &trajmeas.clu,      trajmeas.clu.list.data());
  trajTree_->Branch("clust_pixX",   &trajmeas.clu.pixX, "pixX[size]/F");
  trajTree_->Branch("clust_pixY",   &trajmeas.clu.pixY, "pixY[size]/F");
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
  evt_.init();
  evt_.run = iRun.run();
  
  // ConditionsInRunBlock for fill number
  edm::Handle<edm::ConditionsInRunBlock> condInRunBlock;
  iRun.getByLabel("conditionsInEdm", condInRunBlock);
  if (condInRunBlock.isValid()) {
    evt_.fill = condInRunBlock->lhcFillNumber;
  } else if (evt_.run==1) {
    evt_.fill = 0;
  } else {
    std::cout<<"No condInRunBlock info is available" << std::endl;
    return;
  }
  std::cout<<"Begin Run: "<<evt_.run<<" in Fill: "<<evt_.fill<<std::endl;
}

// ------------------------------ endRun -------------------------------------
void PilotBladeStudy::endRun(edm::Run const& iRun, edm::EventSetup const& iSetup){
  // ConditionsInRunBlock
  edm::Handle<edm::ConditionsInRunBlock> condInRunBlock;
  iRun.getByLabel("conditionsInEdm", condInRunBlock);
  if (!condInRunBlock.isValid()) {
    std::cout<<" CondInRunBlock info is NOT available" << std::endl;
  } else {
    evt_.fill = condInRunBlock->lhcFillNumber;
    evt_.run = iRun.run();
    std::cout << " End Run: " << evt_.run << " in Fill: " << evt_.fill << std::endl;
  }
  eventTree_->Fill();
}

// ------------------------ beginLuminosityBlock ------------------------------
void PilotBladeStudy::beginLuminosityBlock(edm::LuminosityBlock const& iLumi, edm::EventSetup const& iSetup){
  isNewLS_ = true;
}

// -------------------------- endLuminosityBlock ------------------------------
void PilotBladeStudy::endLuminosityBlock(edm::LuminosityBlock const& iLumi, edm::EventSetup const& iSetup){
  
  edm::Handle<LumiSummary> lumi;
  iLumi.getByLabel("lumiProducer", lumi);
  if (!lumi.isValid()) {
    std::cout<<" LumiSummary info is NOT available " << std::endl;
    evt_.init();
  } else {
    evt_.init(); // temporal values deleted, now we fill it for real
    evt_.intlumi=lumi->intgRecLumi();
    evt_.instlumi=lumi->avgInsDelLumi();
  }
  
  // ConditionsInLumiBlock
  edm::Handle<edm::ConditionsInLumiBlock> cond;
  iLumi.getByLabel("conditionsInEdm", cond);
  if (!cond.isValid()) {
    std::cout<<"ConditionsInLumiBlock info is NOT available" << std::endl;
    return;
  }
  
  evt_.run=iLumi.run();
  evt_.ls=iLumi.luminosityBlock();
  
  std::cout << "New lumi block: Run " << evt_.run << " LS = " << evt_.ls;
  std::cout << " inst lumi " << evt_.instlumi 
      << " int lumi " << evt_.intlumi<<std::endl;
  
  //eventTree_->Fill();
  evt_.init();
}

// -------------------------------- analyze -----------------------------------
void PilotBladeStudy::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup) {
  bool DEBUG = false;
  if (DEBUG) std::cout << "Processing the event " << std::endl;
  //beginLuminosityBlock
  if (isNewLS_== true) {
    evt_.run = iEvent.id().run();
    std::cout << "Run number: " << evt_.run << std::endl;
    evt_.ls=iEvent.luminosityBlock();
    isNewLS_=false;
  } else {
    assert(evt_.run == int(iEvent.id().run()));
    assert(evt_.ls == int(iEvent.luminosityBlock()));
  }
  
  init_all();
  
  // Read event info
  evt_.run=iEvent.id().run();
  evt_.evt=iEvent.id().event();
  evt_.ls=iEvent.luminosityBlock();
  
  // Read track info
  edm::Handle<TrajTrackAssociationCollection> trajTrackCollectionHandle;
  std::string trajTrackCollectionInput = iConfig_.getParameter<std::string>("trajectoryInput");
  iEvent.getByLabel(trajTrackCollectionInput, trajTrackCollectionHandle);
  
  Surface::GlobalPoint origin = Surface::GlobalPoint(0,0,0);

  edm::ESHandle<TrackerGeometry> tracker;
  iSetup.get<TrackerDigiGeometryRecord>().get(tracker);    

  
  // Read FED error info
  
  std::map<uint32_t, int> federrors;
  int federr[16];
  for (int i=0; i<16; i++) federr[i]=0;
  assert(evt_.federrs_size==0);
  
  edm::Handle<edm::DetSetVector<SiPixelRawDataError> >  siPixelRawDataErrorCollectionHandle;
  
//   iEvent.getByLabel("siPixelDigis", siPixelRawDataErrorCollectionHandle);  // change to getByToken
   iEvent.getByToken(tok_siPixelDigis_, siPixelRawDataErrorCollectionHandle); // Tav return
  
  if (siPixelRawDataErrorCollectionHandle.isValid()) {
    if (DEBUG) std::cout << "siPixelRawDataErrorCollectionHandle is valid" << std::endl;
    
    const edm::DetSetVector<SiPixelRawDataError>& siPixelRawDataErrorCollection = *siPixelRawDataErrorCollectionHandle;
    edm::DetSetVector<SiPixelRawDataError>::const_iterator itPixelErrorSet = siPixelRawDataErrorCollection.begin();

    for (; itPixelErrorSet!=siPixelRawDataErrorCollection.end(); itPixelErrorSet++) {
      if (DEBUG) std::cout << "Looping on siPixelRawDataErrorCollection" << std::endl;
      edm::DetSet<SiPixelRawDataError>::const_iterator itPixelError=itPixelErrorSet->begin();
      if (DEBUG) std::cout << "Before the loop on the error set" << std::endl;
      for(; itPixelError!=itPixelErrorSet->end(); ++itPixelError) {
        if (DEBUG) std::cout << "Looping on the error set" << std::endl;
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
    
    std::cout << "siPixelRawDataErrorCollectionHandle is not valid" << std::endl;
    // Tracking Error list
    edm::Handle<edm::EDCollection<DetId> > TrackingErrorDetIdCollectionHandle;
//     iEvent.getByLabel("siPixelDigis", TrackingErrorDetIdCollectionHandle); //Tav tokens vissza
    iEvent.getByToken(tok_siPixelDigis_, TrackingErrorDetIdCollectionHandle);
    
    if (TrackingErrorDetIdCollectionHandle.isValid()) {
      const edm::EDCollection<DetId>& TrackingErrorDetIdCollection = *TrackingErrorDetIdCollectionHandle;
      for (size_t i=0; i<TrackingErrorDetIdCollection.size(); i++) {
        federrors.insert(std::pair<uint32_t,int>(TrackingErrorDetIdCollection[i].rawId(), 29));
        federr[4]++;
      }
    }
    
    // User Error List (Overflow only by default)
    edm::Handle<edm::EDCollection<DetId> > UserErrorDetIdCollectionHandle;
//  iEvent.getByLabel("siPixelDigis", "UserErrorModules", UserErrorDetIdCollectionHandle); //Tav tokens
/*    iEvent.getByToken(tok_siPixelDigis_, "UserErrorModules", UserErrorDetIdCollectionHandle);  */  
    iEvent.getByToken(tok_siPixelDigis_, UserErrorDetIdCollectionHandle);  
    
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
  
  if (DEBUG) std::cout<<"DONE: Reading FEDError info\n";
  
  // Analyze clusters
  
  std::map<unsigned int, int> nclu_mod;
  std::map<unsigned int, int> npix_mod;
  std::map<unsigned long int, int> nclu_roc;
  std::map<unsigned long int, int> npix_roc;

//   analyzeClusters(iEvent, iSetup, "siPixelClusters", federrors);
//   analyzeClusters(iEvent, iSetup, "PBClusters", federrors);
  analyzeClusters(iEvent, iSetup, tok_siPixelClusters_, federrors); //Tav tokes
  analyzeClusters(iEvent, iSetup, tok_PBClusters_, federrors); //Tav tokens

  // ----------------------- start of filling the clusTree -----------------------
  eventTree_->SetBranchAddress("event", &evt_);
  eventTree_->Fill();
  
//  Cluster cluster;
//   clustTree_->SetBranchAddress("clusters", &cluster);
//   clustTree_->SetBranchAddress("module", &cluster.mod);
//   clustTree_->SetBranchAddress("clust_pix", &cluster.pix);
//   clustTree_->SetBranchAddress("module_on", &cluster.mod_on);
//   
//   for (size_t i=0; i<clust_.size(); i++) {
//     cluster = clust_[i];
//     clustTree_->Fill();
//   }
  
  clustTree_->SetBranchAddress("event", &evt_);
  for (size_t i=0; i<clust_.size(); i++) {
    clustTree_->SetBranchAddress("clusters", &clust_[i]);
    clustTree_->SetBranchAddress("clust_pixX", &clust_[i].pixX);
    clustTree_->SetBranchAddress("clust_pixY", &clust_[i].pixY);
    clustTree_->SetBranchAddress("module", &clust_[i].mod);
    clustTree_->SetBranchAddress("module_on", &clust_[i].mod_on);
    clustTree_->Fill();
  }

  // Process tracks
  if (trajTrackCollectionHandle.isValid()) {
    evt_.ntracks = trajTrackCollectionHandle->size();
    
    // --------------------- loop on the trajTrackCollection ----------------------
    TrajTrackAssociationCollection::const_iterator 
      itTrajTrack=trajTrackCollectionHandle->begin();
    
    for (;itTrajTrack!=trajTrackCollectionHandle->end(); itTrajTrack++) {
      const Trajectory& traj  = *itTrajTrack->key;
      const Track&      track = *itTrajTrack->val;
      
      TrackData track_;
      std::vector<TrajMeasurement> trajmeas; 
      track_.pt=track.pt();
      track_.ndof=track.ndof();
      track_.chi2=track.chi2();
      track_.eta=track.eta();
      track_.phi=track.phi();
      
      if (!track.quality(reco::TrackBase::highPurity)) continue;
      std::vector<TrajectoryMeasurement> trajMeasurements = traj.measurements();
      TrajectoryStateCombiner trajStateComb;
      
      // ----------------------- loop on the trajMeasurements -----------------------
      for(std::vector<TrajectoryMeasurement>::const_iterator itTraj = trajMeasurements.begin(); 
      itTraj != trajMeasurements.end(); itTraj++) {
        TrajMeasurement meas;
        
        TransientTrackingRecHit::ConstRecHitPointer recHit = itTraj->recHit();
        if(recHit->geographicalId().det() != DetId::Tracker) continue;
        
        unsigned int DetID    = recHit->geographicalId();
        unsigned int SubDetID = recHit->geographicalId().subdetId();

        const Surface& surface = tracker->idToDet(recHit->geographicalId())->surface();

        meas.mod    = getModuleData(recHit->geographicalId().rawId(), federrors);
        meas.mod_on = getModuleData(recHit->geographicalId().rawId(), federrors, "online");
        // Hit type codes: valid = 0, missing = 1, inactive = 2
        
        if (recHit->getType() == TrackingRecHit::valid) {
           meas.type=0;
         } else if (recHit->getType() == TrackingRecHit::missing) {
           meas.type=1;
         } else if (recHit->getType() == TrackingRecHit::inactive) {
           meas.type=2;
         }
         
        //Strip detector
        if(SubDetID == 3 || SubDetID == 4 || SubDetID == 5 ||SubDetID == 6 ) {
          //std::cout << " Hit found on the Strip detector" << std::endl;
          continue;
        }
        //Pixel Forward detector or Pixel Barrel detector
        else if ( SubDetID == PixelSubdetector::PixelEndcap || SubDetID == PixelSubdetector::PixelBarrel ) {
          //std::cout << " Hit found on the FPIX detector" << std::endl;
          nHits++;
          TrajectoryStateOnSurface predTrajState=trajStateComb(itTraj->forwardPredictedState(),
                                                               itTraj->backwardPredictedState());                                                 
          meas.lx=predTrajState.localPosition().x();
          meas.ly=predTrajState.localPosition().y();
          meas.glx=predTrajState.globalPosition().x();
          meas.gly=predTrajState.globalPosition().y();
          meas.glz=predTrajState.globalPosition().z();
          
          meas.lx_err=predTrajState.localError().positionError().xx();
          meas.ly_err=predTrajState.localError().positionError().yy();
          
          meas.onEdge=1;
          if (fabs(meas.lx)<0.55 && fabs(meas.ly)<3.0) {
            meas.onEdge=0;         
          }
          
          LocalTrajectoryParameters predTrajParam= predTrajState.localParameters();
          LocalVector dir = predTrajParam.momentum()/predTrajParam.momentum().mag();
          meas.alpha = atan2(dir.z(), dir.x());
          meas.beta = atan2(dir.z(), dir.y());
            
          // If Pilot Blade
          if (meas.mod.disk == 3 && meas.mod.side == 1) {
	    if (DEBUG) {
	      std::cout << "***************************\n** PilotBlade hit found! **"<< std::endl;
	      std::cout << "***************************" << std::endl;
	    }
            nPBHits++;
            
      ClustData clu1;
            findClosestClusters(iEvent, iSetup, recHit->geographicalId().rawId(),
        meas.lx, meas.ly, meas.dx_cl, meas.dy_cl, 
                                tok_PBClusters_, clu1
            );
            
      ClustData clu2;
            findClosestClusters(iEvent, iSetup, recHit->geographicalId().rawId(),
                                (meas.lx-0.003301), (meas.ly+0.001494), meas.dx_cl_corr, meas.dy_cl_corr, 
                                tok_PBClusters_, clu2
            );
            
      // Read associated cluster parameters
      if (DEBUG) std::cout << "Read associated cluster parameters" << std::endl;
      
      meas.clu=clu1;
      if (meas.clu.charge!=NOVAL_F) {
        meas.norm_charge = meas.clu.charge*
        sqrt(1.0/(1.0/pow(tan(meas.alpha),2)+1.0/pow(tan(meas.beta),2)+1.0));
      }

      for (size_t i=0; i<2; i++) {
        //std::cout << "PilotBlade dx_cl: " << meas.dx_cl[i] << std::endl;
        //std::cout << "PilotBlade dy_cl: " << meas.dy_cl[i] << std::endl;
        //std::cout << "PB FPIX meas.dx_cl_corr[0]: " << meas.dx_cl_corr[i] << std::endl;
        //std::cout << "PB FPIX meas.dy_cl_corr[0]: " << meas.dy_cl_corr[i] << std::endl;
        if (meas.dx_cl[i]!=NOVAL_F) {
          meas.d_cl[i]=sqrt(meas.dx_cl[i]*meas.dx_cl[i]+meas.dy_cl[i]*meas.dy_cl[i]);
        } else {
          meas.d_cl[i]=NOVAL_F;
        //std::cout << "d_cl[0]==NOVAL_F" << std::endl;
        } 
      }
          } else {
      if (1) { // choose cluster found by us to FPix hits, or the ones tracking has associated
        ClustData clu;
        findClosestClusters(iEvent, iSetup, recHit->geographicalId().rawId(),
          meas.lx, meas.ly, meas.dx_cl, meas.dy_cl, tok_siPixelClusters_, clu);
        meas.clu=clu;
        
        for (size_t i=0; i<2; i++) {
          //std::cout << "Non-PB FPIX meas.dx_cl[i]: " << meas.dx_cl[i] << std::endl;
          if (meas.dx_cl[i]!=NOVAL_F) {
            meas.d_cl[i] = sqrt(meas.dx_cl[i]*meas.dx_cl[i]+meas.dy_cl[i]*meas.dy_cl[i]);
          } else {
            meas.d_cl[i]=NOVAL_F;
          }
        }
      } else {
        if (recHit->isValid() && recHit->hit()!=0) {
          const SiPixelRecHit *hit=(const SiPixelRecHit*)recHit->hit();
          SiPixelRecHit::ClusterRef const& clust=hit->cluster();
          if (clust.isNonnull()) {
            meas.clu.charge=(*clust).charge()/1000.0;
            meas.clu.size=(*clust).size();
            meas.clu.edge=hit->isOnEdge() ? 1 : 0;
            meas.clu.sizeX=(*clust).sizeX();
            meas.clu.sizeY=(*clust).sizeY();
            meas.clu.x=(*clust).x();
            meas.clu.y=(*clust).y();
            for (int i=0; i<(*clust).size() && i<1000; i++) {
              meas.clu.adc[i]=float((*clust).pixelADC()[i])/1000.0;
              meas.clu.pixX[i]=(((*clust).pixels())[i]).x;
              meas.clu.pixY[i]=(((*clust).pixels())[i]).y;
            }
          }
          
          meas.dx_cl[0]=meas.lx-hit->localPosition().x();
          meas.dy_cl[0]=meas.ly-hit->localPosition().y();
          
          meas.d_cl[0] = sqrt(meas.dx_cl[0]*meas.dx_cl[0]+meas.dy_cl[0]*meas.dy_cl[0]);
        } else {
          meas.d_cl[0]=NOVAL_F;
        }
      }

      if (meas.d_cl[0]!=NOVAL_F) {
        LocalPoint lpmod(0.,0.,0.), lxdir(1.,0.,0.), lydir(0.,1.,0.);
        GlobalPoint gpmod = surface.toGlobal(lpmod);
        GlobalPoint glxdir = surface.toGlobal(lxdir);
        GlobalPoint glydir = surface.toGlobal(lydir);
        
        meas.dx_cl[0] *= (glxdir.perp() - gpmod.perp() >= 0 ? 1. : -1.);
        meas.dy_cl[0] *= (deltaPhi(glydir.phi(),gpmod.phi()) >= 0. ? 1. : -1.);

      }
      
      if (meas.clu.charge!=NOVAL_F) {
        meas.norm_charge = meas.clu.charge*
    sqrt(1.0/(1.0/pow(tan(meas.alpha),2)+1.0/pow(tan(meas.beta),2)+1.0));
      }
      
          } //if FPix not PB
          
          trajmeas.push_back(meas);                              
        } else {
          std::cout << " Nor BIX, nor FPIX, nor Strip, DetID: " << DetID << std::endl;
        }        
      }
      // ------------------- end of loop on the trajMeasurements --------------------
      tracks_.push_back(track_);
      trajmeas_.push_back(trajmeas);
    }
    // ------------------- end of loop on the trajTrackCollection -------------------
  } else {
    std::cout << " There is no valid trajTrackCollectionHandle" << std::endl;
    return;
  }//end of the IF: (trajTrackCollectionHandle.isValid())
  
  std::cout << "Number of PB Hits: " << nPBHits << " out of " 
      << nHits << " in the events so far. "<<std::endl;
  
  // ----------------------- start of filling the trajTree -----------------------
  eventTree_->SetBranchAddress("event", &evt_);
  eventTree_->Fill();
  
  TrajMeasurement traj;
  trajTree_->SetBranchAddress("event",      &evt_);
  trajTree_->SetBranchAddress("traj",       &traj);
  trajTree_->SetBranchAddress("module",     &traj.mod);
  trajTree_->SetBranchAddress("module_on",  &traj.mod_on);
  trajTree_->SetBranchAddress("clust",      &traj.clu);
  trajTree_->SetBranchAddress("clust_pixX", &traj.clu.pixX);
  trajTree_->SetBranchAddress("clust_pixY", &traj.clu.pixY);
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
      trajmeas_[itrk][i].hit_near = minD;
      
      // Module/ROC Occupancies
      trajmeas_[itrk][i].nclu_mod = (nclu_mod.count(trajmeas_[itrk][i].mod_on.rawid)) ?
        nclu_mod[trajmeas_[itrk][i].mod_on.rawid] : 0;
      trajmeas_[itrk][i].npix_mod = (npix_mod.count(trajmeas_[itrk][i].mod_on.rawid)) ?
        npix_mod[trajmeas_[itrk][i].mod_on.rawid] : 0;
      
      int RocID = get_RocID_from_local_coords(trajmeas_[itrk][i].lx, trajmeas_[itrk][i].ly, trajmeas_[itrk][i].mod_on);
      if (RocID!=NOVAL_I) {
        unsigned long int modroc = trajmeas_[itrk][i].mod_on.rawid * 100 + RocID;
        trajmeas_[itrk][i].nclu_roc = (nclu_roc.count(modroc)) ? nclu_roc[modroc] : 0;
        trajmeas_[itrk][i].npix_roc = (npix_roc.count(modroc)) ? npix_roc[modroc] : 0;
      } else { // Hit is outside module boundaries
        trajmeas_[itrk][i].nclu_roc = NOVAL_I;
        trajmeas_[itrk][i].npix_roc = NOVAL_I;
      }
      
      traj = trajmeas_[itrk][i];
      trajTree_->Fill();
    }
  }  
  // ----------------------- end of filling the trajTree ------------------------
}//end of analyzer

// ------------------------------ other functions -----------------------------

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

// ---------------------------- findClosestClusters ---------------------------
void PilotBladeStudy::findClosestClusters(
  const edm::Event& iEvent, 
  const edm::EventSetup& iSetup, uint32_t rawId, 
  float lx, float ly, float* dx_cl, float* dy_cl, edm::EDGetTokenT< edmNew::DetSetVector<SiPixelCluster> > clusterColl,
  ClustData& clu) {
  bool DEBUG = false;
  for (size_t i=0; i<1; i++) dx_cl[i]=dy_cl[i]=NOVAL_F;
  
  edm::ESHandle<PixelClusterParameterEstimator> cpEstimator;
  iSetup.get<TkPixelCPERecord>().get("PixelCPEGeneric", cpEstimator);
  if (!cpEstimator.isValid()) {
    std::cout << "The cpEstimator is not valid!" << std::endl;
    //return itClosestCluster.begin();
  }
  const PixelClusterParameterEstimator &cpe(*cpEstimator);
  
  edm::ESHandle<TrackerGeometry> tracker;
  iSetup.get<TrackerDigiGeometryRecord>().get(tracker);
  if (!tracker.isValid()) {
    std::cout << "The tracker record is not valid!" << std::endl;
    return;
  }
  const TrackerGeometry *tkgeom = &(*tracker);
  
  edm::Handle<edmNew::DetSetVector<SiPixelCluster> > clusterCollectionHandle;
  // clusterColl string is given as an input
  // could be siPixelClusters or PBClusters
//   iEvent.getByLabel(clusterColl, clusterCollectionHandle); //Tav tokens
  iEvent.getByToken(clusterColl, clusterCollectionHandle); //Tav tokens
  
  if (!clusterCollectionHandle.isValid()) {
    std::cout << "The clusterCollectionHandle is not valid!" << std::endl;
    return;
  } else {
    //std::cout << "The clusterCollectionHandle we use is " 
    //    << clusterColl << std::endl;
  }
  
  const edmNew::DetSetVector<SiPixelCluster>& clusterCollection= *clusterCollectionHandle;
  edmNew::DetSetVector<SiPixelCluster>::const_iterator itClusterSet = clusterCollection.begin();
  
  float minD[2];
  minD[0]=minD[1]=10000.;
  
  for ( ; itClusterSet!=clusterCollection.end(); itClusterSet++) {
    
    DetId detId(itClusterSet->id());
    if (DEBUG) {
      std::cout << " Cluster rawId: " << detId.rawId();
      std::cout << "?= RecHit rawId: " << rawId << std::endl;
    }
    if (detId.rawId()!=rawId) {
      if (DEBUG) std::cout << " Wrong rawId " << std::endl;
      continue;
    }
    
    unsigned int subDetId=detId.subdetId();
    if (subDetId!=PixelSubdetector::PixelBarrel &&
  subDetId!=PixelSubdetector::PixelEndcap) {
      std::cout << "ERROR: not a pixel cluster!!!" << std::endl; 
      continue;
    }
    
    const PixelGeomDetUnit *pixdet = (const PixelGeomDetUnit*) tkgeom->idToDetUnit(detId);
    edmNew::DetSet<SiPixelCluster>::const_iterator itCluster=itClusterSet->begin();
    edmNew::DetSet<SiPixelCluster>::const_iterator itClosestCluster=itClusterSet->begin();
    
    for(; itCluster!=itClusterSet->end(); ++itCluster) {
      LocalPoint lp(itCluster->x(), itCluster->y(), 0.);
      
      if (usePixelCPE_) {
  PixelClusterParameterEstimator::ReturnType params = cpe.getParameters(*itCluster,*pixdet);
  lp = std::get<0>(params);
  if (DEBUG) std::cout << "PixelClusterParameterEstimator: " << lp << std::endl;
      } 
      
      float D = sqrt((lp.x()-lx)*(lp.x()-lx)+(lp.y()-ly)*(lp.y()-ly));
      if (DEBUG) std::cout << "Value of the D: " << D << std::endl; 
      if (D<minD[0]) {
  minD[1]=minD[0];
  dx_cl[1]=dx_cl[0];
  dy_cl[1]=dy_cl[0];
  minD[0]=D;
  dx_cl[0]=lp.x();
  dy_cl[0]=lp.y();
  itClosestCluster = itCluster;
      } else if (D<minD[1]) {
  minD[1]=D;
  dx_cl[1]=lp.x();
  dy_cl[1]=lp.y();
  
      }
    } // loop on cluster sets
    
    for (size_t i=0; i<2; i++) {
      if (minD[i]<9999.) {
  dx_cl[i]=dx_cl[i]-lx;
  dy_cl[i]=dy_cl[i]-ly;
      }
    }
    
    if (minD[0]<9999.) {
      clu.charge=(itClosestCluster)->charge()/1000.0;
      clu.size=(itClosestCluster)->size();
      clu.edge=NOVAL_F;
      clu.sizeX=(itClosestCluster)->sizeX();
      clu.sizeY=(itClosestCluster)->sizeY();
      clu.x=(itClosestCluster)->x();
      clu.y=(itClosestCluster)->y();
      for (int i=0; i<(itClosestCluster)->size() && i<1000; i++) {
  clu.adc[i]=float((itClosestCluster)->pixelADC()[i])/1000.0;
  clu.pixX[i]=(((itClosestCluster)->pixels())[i]).x;
  clu.pixY[i]=(((itClosestCluster)->pixels())[i]).y;
      }
    }
    
  }


}
// ------------------------ end of findClosestClusters ------------------------ 

// ------------------------------ analyzeClusters -----------------------------

// void PilotBladeStudy::analyzeClusters(const edm::Event& iEvent, 
//                                          const edm::EventSetup& iSetup,  
//                                          std::string clusterColl,
//                                          std::map<uint32_t, int> federrors
//                                      ) {
void PilotBladeStudy::analyzeClusters(const edm::Event& iEvent, 
                                         const edm::EventSetup& iSetup,  
                                         edm::EDGetTokenT< edmNew::DetSetVector<SiPixelCluster> > clusterColl,
                                         std::map<uint32_t, int> federrors
                                     ) {
  bool DEBUG = false;
  
  for (size_t i=0; i<4; i++) evt_.nclu[i]=evt_.npix[i]=0;
  std::map<unsigned int, int> nclu_mod;
  std::map<unsigned int, int> npix_mod;
  std::map<unsigned long int, int> nclu_roc;
  std::map<unsigned long int, int> npix_roc;

  edm::Handle<edmNew::DetSetVector<SiPixelCluster> > clusterCollectionHandle;
//   iEvent.getByLabel(clusterColl, clusterCollectionHandle); //Tav tokens
  iEvent.getByToken(clusterColl, clusterCollectionHandle);
  
  if (clusterCollectionHandle.isValid()) {
    const edmNew::DetSetVector<SiPixelCluster>& clusterCollection = *clusterCollectionHandle;
    edmNew::DetSetVector<SiPixelCluster>::const_iterator itClusterSet =  clusterCollection.begin();

    edm::ESHandle<TrackerGeometry> tracker;
    iSetup.get<TrackerDigiGeometryRecord>().get(tracker);    
    const TrackerGeometry *tkgeom = &(*tracker);

    edm::ESHandle<PixelClusterParameterEstimator> cpEstimator;
    iSetup.get<TkPixelCPERecord>().get("PixelCPEGeneric", cpEstimator);
    if (!cpEstimator.isValid()) {
      std::cout << "The cpEstimator is not valid!" << std::endl;
      //return itClosestCluster.begin();
    }
    const PixelClusterParameterEstimator &cpe(*cpEstimator);

    for (; clusterCollectionHandle.isValid() && itClusterSet != clusterCollection.end();
          itClusterSet++) {
            DetId detId(itClusterSet->id());
      unsigned int subDetId=detId.subdetId();
         
            if (DEBUG) std::cout << "Looping on the cluster sets ";
      // Take only pixel clusters
      if (subDetId!=PixelSubdetector::PixelEndcap && subDetId!=PixelSubdetector::PixelBarrel) {
              std::cout << "Not a pixel cluster";
              continue;
      }
      
      const PixelGeomDetUnit *pixdet = (const PixelGeomDetUnit*) tkgeom->idToDetUnit(detId);
      edmNew::DetSet<SiPixelCluster>::const_iterator itCluster=itClusterSet->begin();

      for(; itCluster!=itClusterSet->end(); ++itCluster) {
        if (DEBUG) std::cout << "Looping on the clusters in the set " << std::endl;
                
        const Surface& surface = tracker->idToDet(detId)->surface();

        LocalPoint lp(-9999., -9999., -9999.);
        PixelClusterParameterEstimator::ReturnType params = cpe.getParameters(*itCluster,*pixdet);
        lp = std::get<0>(params);
        LocalPoint lp1(1.0,0.0,0.0);
        LocalPoint lp2(0.0,1.0,0.0);
        LocalPoint lp3(1.0,0.0,1.0);
        GlobalPoint gp = surface.toGlobal(lp);
        //GlobalPoint gp1 = surface.toGlobal(lp1);
        //std::cout << "GlobalPoint" << gp << std::endl;
        
        Cluster clust;
        clust.x=itCluster->x();
        clust.y=itCluster->y();
        clust.glx = gp.x();
        clust.gly = gp.y();
        clust.glz = gp.z();
        clust.sizeX=itCluster->sizeX();
        clust.sizeY=itCluster->sizeY();
        clust.i=itCluster-itClusterSet->begin();
        clust.size=itCluster->size();
        clust.charge=itCluster->charge()/1000.0;

        for (int i=0; i<itCluster->size() && i<1000; i++) {
          clust.adc[i]=float(itCluster->pixelADC()[i])/1000.0;
          clust.pixX[i]=((itCluster->pixels())[i]).x;
          clust.pixY[i]=((itCluster->pixels())[i]).y;
        }
        
        clust.mod    = getModuleData(detId.rawId(), federrors);
        clust.mod_on = getModuleData(detId.rawId(), federrors, "online");
        
        // Layer Occupancy
        if (clust.mod_on.det!=NOVAL_I) {
          evt_.nclu[(1-clust.mod_on.det)*clust.mod_on.layer]++;
          evt_.npix[(1-clust.mod_on.det)*clust.mod_on.layer]+=itCluster->size();
        }
        // Module Occupancy
        if (!nclu_mod.count(clust.mod_on.rawid)) nclu_mod[clust.mod_on.rawid] = 0;
        if (!npix_mod.count(clust.mod_on.rawid)) npix_mod[clust.mod_on.rawid] = 0;
        nclu_mod[clust.mod_on.rawid]++;
        npix_mod[clust.mod_on.rawid]+=itCluster->size();
        // Roc Occupancy
        int RocID = get_RocID_from_cluster_coords(clust.x, clust.y, clust.mod_on);
        unsigned long int modroc = clust.mod_on.rawid * 100 + RocID;
        if (!nclu_roc.count(modroc)) nclu_roc[modroc] = 0;
        if (!npix_roc.count(modroc)) npix_roc[modroc] = 0;
        nclu_roc[modroc]++;
        npix_roc[modroc]+=itCluster->size();
        



        if (DEBUG) std::cout<<"\t#"<<clust.i<<" charge: "<<clust.charge<<" size: "<<clust.size<<std::endl;

        clust_.push_back(clust);
      }
    } // loop on cluster sets
  } else {
    std::cout<< "The clusterCollectionHandle is invalid" << std::endl;
  }
}

int PilotBladeStudy::get_RocID_from_cluster_coords(const float& x, const float& y, const PilotBladeStudy::ModuleData& mod_on) {
  if (x!=NOVAL_F&&y!=NOVAL_F) {
    if (mod_on.det==0) {
      int ny = (int)(y / 52.0);
      int roc = (mod_on.half) ? ((mod_on.module<0)*8+ny) : ((mod_on.module>0) ? ((x>80.0) ? ny : 15-ny) : ((x>80.0) ? 8+ny : 7-ny));
      return roc;
    } else if (mod_on.det==1) {
      int nrocly = mod_on.module + mod_on.panel;
      int rocy = (int)(y/52.0);
      int roc = ((mod_on.panel==2 && x<80.0)
                 || (mod_on.panel==1 && (mod_on.module==1||mod_on.module==4))
                 || (mod_on.panel==1 && (mod_on.module==2||mod_on.module==3) && x>80.0 )) ? rocy
        : 2*nrocly -1 - rocy;
      return roc;
    } else return NOVAL_I;
  } else return NOVAL_I;
}

int PilotBladeStudy::get_RocID_from_local_coords(const float& lx, const float& ly, const PilotBladeStudy::ModuleData& mod_on) {
  if (lx!=NOVAL_F&&ly!=NOVAL_F) {
    if (mod_on.det==0) {
      if (fabs(ly)<3.24&&((mod_on.half==0&&fabs(lx)<0.8164)||(mod_on.half==1&&fabs(lx)<0.4082))) {
        int ny = (int)(ly / 0.81 + 4);
        int roc = (mod_on.half) ? ((mod_on.module<0)*8+ny) : ((mod_on.module>0) ? ((lx>0.0) ? ny : 15-ny) : ((lx>0.0) ? 8+ny : 7-ny));
        return roc;
      } else return NOVAL_I;
    } else if (mod_on.det==1) {
      int nrocly = mod_on.module + mod_on.panel;
      if (fabs(ly)<(nrocly*0.405) && ( ( !(mod_on.panel==1&&(mod_on.module==1||mod_on.module==4)) && fabs(lx)<0.8164 ) || (fabs(lx)<0.4082) )) {
        int rocy = (int)((ly+(nrocly%2)*0.405)/0.81+nrocly/2);
        int roc = ((mod_on.panel==2 && lx<0.0)
                   || (mod_on.panel==1 && (mod_on.module==1||mod_on.module==4))
                   || (mod_on.panel==1 && (mod_on.module==2||mod_on.module==3) && lx>0.0 )) ? rocy
          : 2*nrocly -1 - rocy;
        return roc;
      } else return NOVAL_I;
    } else return NOVAL_I;
  } else return NOVAL_I;
}


// Other useful things
/*
  DetID == 344130820 || DetID == 344131844 || DetID == 344132868 
  || DetID == 344133892 || DetID == 344131076 || DetID == 344132100 
  || DetID == 344133124 || DetID == 344134148 )
*/
DEFINE_FWK_MODULE(PilotBladeStudy);


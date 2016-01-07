# Source: /local/reps/CMSSW/CMSSW/Configuration/Applications/python/ConfigBuilder.py,v 
# with command line options: MinBias_13TeV_cfi.py -s RAW2DIGI,L1Reco,RECO --mc --conditions auto:run2_mc 
# --pileup=NoPileUp --magField 38T_PostLS1 --customise SLHCUpgradeSimulations/Configuration/postLS1Customs.customisePostLS1 -n 10 --no_exec
# Author: Tamas Almos Vami (Tav)
# Year: 2015
# Description: RAW data reconstructor for Pilot Blade containing data (using the optional importable PilotBladeSetup_cfi)

import FWCore.ParameterSet.Config as cms
process = cms.Process('RECO')

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('SimGeneral.MixingModule.mixNoPU_cfi')
process.load('Configuration.Geometry.GeometrySimDB_cff')
process.load('Configuration.Geometry.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_PostLS1_cff')
#process.load('Configuration.StandardSequences.RawToDigi_cff')
#process.load('Configuration.StandardSequences.RawToDigi_Data_cff')
process.load('Configuration.StandardSequences.RawToDigi_Repacked_cff') # HeavyIon setup
process.load('Configuration.StandardSequences.L1Reco_cff')
#process.load('Configuration.StandardSequences.Reconstruction_cff')
process.load('Configuration.StandardSequences.ReconstructionHeavyIons_cff') # HeavyIon setup
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')

PB = cms.bool(True)
Analyzers = cms.bool(False)

if PB:
  process.load('DPGAnalysis.PilotBladeStudy.PilotBladeSetup_cfi')
#endif

if Analyzers:
  process.load('DPGAnalysis.PilotBladeStudy.Analyzers_cfi')
#endif

# ------------------- Input ----------------------------
nEvents = 'test'
process.maxEvents = cms.untracked.PSet(
  input = cms.untracked.int32(15)
)

'''
# List of input files
from PoolSource_PB_MC_RAW import *
InputFiles = FileNames
process.source = cms.Source("PoolSource",
  #fileNames = InputFiles,
  secondaryFileNames = cms.untracked.vstring()
)
'''
process.source = cms.Source("PoolSource",
  fileNames = cms.untracked.vstring('file:/data/vami/projects/pilotBlade/0Data/RAW/00D1886C-4DA5-E511-A856-02163E01419D.root'),
  #fileNames = cms.untracked.vstring( '/store/hidata/HIRun2015/HIFlowCorr/RAW/v1/000/263/742/00000/00D1886C-4DA5-E511-A856-02163E01419D.root' ),
  secondaryFileNames = cms.untracked.vstring()
)

process.options = cms.untracked.PSet(
  #SkipEvent = cms.untracked.vstring('ProductNotFound')
)

#----------------Production Info------------------------
process.configurationMetadata = cms.untracked.PSet(
  annotation = cms.untracked.string('PilotBlade_HIFlowCorr.py nevts:10'),
  name = cms.untracked.string('Applications'),
  version = cms.untracked.string('$Revision: 1.19 $')
)
#-------------------------------------------------------

# ------------------- Output ---------------------------
process.RECOSIMoutput = cms.OutputModule("PoolOutputModule",
  dataset = cms.untracked.PSet(
    dataTier = cms.untracked.string(''),
    filterName = cms.untracked.string('')
  ),
  eventAutoFlushCompressedSize = cms.untracked.int32(5242880),
  fileName = cms.untracked.string('PilotBlade_HIFlowCorr_RAWtoRECO_'+nEvents+'.root'),
  outputCommands = cms.untracked.vstring(
    'drop *',
    #'keep *_*ixel*_*_*',
    #'keep *_*PB*_*_*',
    #'keep *_*racks*_*_*',
    'keep *_PBClusters_*_*',
    'keep *_siPixelClusters_*_*',
    'keep *_hiGeneralTracks_*_*',
    'keep *_generalTracks_*_*',
    'keep *_lumiProducer_*_*',
    'keep *_*iStripClusters*_*_*',
    'keep *_*eamSpot*_*_*',
    'keep *_*onditionsInEdm*_*_*',
    'keep *awDataError*_*_*_*',
  ),
  splitLevel = cms.untracked.int32(0)
)
#-------------------------------------------------------

# --------------------- GlobalTag ----------------------
from Configuration.AlCa.GlobalTag_condDBv2 import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, '75X_dataRun2_Prompt_v2', '')
#process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:run2_data', '')

# --------------------- Reconstruction --------------------
#Standard Pixel Digis
# standard CablingMap does not contain PB FEDs --> no siPixelDigis
process.siPixelDigis.UsePilotBlade = cms.bool(False)
process.siPixelDigis.InputLabel = cms.InputTag("rawDataRepacker") #for HI reco anyway del this row
process.siPixelDigis.CablingMapLabel =  cms.string("")
process.siPixelDigis.UseQualityInfo = cms.bool(True)

if PB :
  #Pilot Blade Digis
  process.PBDigis = cms.EDProducer("SiPixelRawToDigi",
    InputLabel = cms.InputTag("rawDataRepacker"),
    CablingMapLabel =  cms.string("pilotBlade"),
    UsePhase1 = cms.bool(False),
    UsePilotBlade = cms.bool(True),
    UseQualityInfo = cms.bool(False),
    IncludeErrors = cms.bool(True),
  )
  '''
  process.PBDigis = process.siPixelDigis.clone()
  process.PBDigis.UsePilotBlade = cms.bool(True)
  process.PBDigis.UsePhase1 = cms.bool(False)
  process.PBDigis.IncludeErrors = cms.bool(True)
  process.PBDigis.InputLabel = cms.InputTag("rawDataRepacker") #tav
  process.PBDigis.CablingMapLabel =  cms.string("pilotBlade")
  process.PBDigis.UseQualityInfo = cms.bool(False)
  '''
  #Pilot Blade Clusters
  from CondTools.SiPixel.SiPixelGainCalibrationService_cfi import *
  process.PBClusters = cms.EDProducer("SiPixelClusterProducer",
    SiPixelGainCalibrationServiceParameters,
    src = cms.InputTag("PBDigis"),
    ChannelThreshold = cms.int32(1000),
    MissCalibrate = cms.untracked.bool(False), # should be True #Tav
    SplitClusters = cms.bool(False),
    VCaltoElectronGain = cms.int32(65),
    VCaltoElectronOffset = cms.int32(-414),                          
    payloadType = cms.string('Offline'),
    #payloadType = cms.string('HLT'),
    SeedThreshold = cms.int32(1000),
    ClusterThreshold = cms.double(4000.0),
    maxNumberOfClusters = cms.int32(-1),
  )

  #Pilot Blade RecHits
  process.PBRecHits = cms.EDProducer("SiPixelRecHitConverter",
    src = cms.InputTag("PBClusters"),
    CPE = cms.string('PixelCPEGeneric'),
    VerboseLevel = cms.untracked.int32(0),
  )
# endif

#-------------------------------------------------------

#--------------------- EndPath -------------------------
process.raw2digi_step = cms.Path(process.RawToDigi)
process.L1Reco_step = cms.Path(process.L1Reco)
#process.reconstruction_step = cms.Path(process.reconstruction)
process.reconstruction_step = cms.Path(process.reconstructionHeavyIons)


# If you want to reconstruct the Pilot Blade then set PB in line 24 to True,
# if it is False then uncomment line 387-388 and only the Phase0 will be reconstructed. 
# If you want analyzers set line 25 to True; if false uncomment lines in the schedule
if PB :
  process.PBDigi_step = cms.Path(process.PBDigis)
  process.pilotBladeReco_step = cms.Path(
    process.PBClusters*
    process.PBRecHits
  )
# endif

process.endjob_step = cms.EndPath(process.endOfProcess)
process.RECOSIMoutput_step = cms.EndPath(process.RECOSIMoutput)

# Schedule definition
process.schedule = cms.Schedule(
  #standard part
  process.raw2digi_step,
  process.L1Reco_step,
  process.reconstruction_step,
  #process.analyze_step,
  
  #PilotBlade part
  process.PBDigi_step,
  process.pilotBladeReco_step,
  #process.analyzePB_step,
  
  #end part
  process.endjob_step,
  process.RECOSIMoutput_step
)

# customisation of the process
from SLHCUpgradeSimulations.Configuration.postLS1Customs import customisePostLS1 
process = customisePostLS1(process)

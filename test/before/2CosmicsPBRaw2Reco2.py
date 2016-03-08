# Auto generated configuration file
# using: 
# Revision: 1.19 
# Source: /local/reps/CMSSW/CMSSW/Configuration/Applications/python/ConfigBuilder.py,v 
# with command line options: --python_filename CosmicsPBRaw2Reco.py --conditions auto:run2_data --scenario cosmics --customise Configuration/DataProcessing/RecoTLR.customiseCosmicDataRun2 --step RAW2DIGI,RECO --datatier RECO --eventcontent RECO -n 100 --no_exec
import FWCore.ParameterSet.Config as cms

process = cms.Process('RECO')

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContentCosmics_cff')
process.load('SimGeneral.MixingModule.mixCosmics_cfi')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_cff')
process.load('Configuration.StandardSequences.RawToDigi_Data_cff')
process.load('Configuration.StandardSequences.ReconstructionCosmics_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
#process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')

PB = cms.bool(True)

if PB:
  process.load('DPGAnalysis.PilotBladeStudy.PilotBladeSetup_cfi')
#endif

nEvents = 'test100event'

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(100)
)

# Input source
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring('file:9445DE86-21DB-E511-A9AA-02163E01357D.root'),
      #'file:BC2DA80D-3EDB-E511-A86A-02163E0145C7.root'),
    secondaryFileNames = cms.untracked.vstring()
)

process.options = cms.untracked.PSet(

)

# Production Info
process.configurationMetadata = cms.untracked.PSet(
    annotation = cms.untracked.string('python_filename nevts:100'),
    name = cms.untracked.string('Applications'),
    version = cms.untracked.string('$Revision: 1.19 $')
)

# Output definition

process.RECOoutput = cms.OutputModule("PoolOutputModule",
    dataset = cms.untracked.PSet(
        dataTier = cms.untracked.string('RECO'),
        filterName = cms.untracked.string('')
    ),
    eventAutoFlushCompressedSize = cms.untracked.int32(5242880),
    fileName = cms.untracked.string('cosmics_PB_RAW2RECO_'+nEvents+'.root'),
    #outputCommands = process.RECOEventContent.outputCommands,
    outputCommands = cms.untracked.vstring(
    'drop *',
    'keep *_*lumi*_*_*',
    'keep *_*eamSpot*_*_*',
    'keep *_*cond*_*_*',
    'keep *_*ixel*_*_*',
    'keep *_*PB*_*_*',
    'keep *_*racks*_*_*',
    'keep *_*iStripClusters*_*_*',
    'keep *awDataError*_*_*_*',
  ),
    splitLevel = cms.untracked.int32(0)
)

# Additional output definition

# Other statements
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:run2_data', '')

# --------------------- Reconstruction --------------------
#Standard Pixel Digis
# standard CablingMap does not contain PB FEDs --> no siPixelDigis
process.siPixelDigis.UsePilotBlade = cms.bool(False)
process.siPixelDigis.CablingMapLabel =  cms.string("")
process.siPixelDigis.UseQualityInfo = cms.bool(True)

if PB :
  #Pilot Blade Digis
  process.PBDigis = cms.EDProducer("SiPixelRawToDigi",
    InputLabel = cms.InputTag("rawDataCollector"),
    CablingMapLabel =  cms.string("pilotBlade"),
    UsePhase1 = cms.bool(False),
    UsePilotBlade = cms.bool(True),
    UseQualityInfo = cms.bool(False),
    IncludeErrors = cms.bool(True),
  )
  
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

# Path and EndPath definitions
process.raw2digi_step = cms.Path(process.RawToDigi)
process.reconstruction_step = cms.Path(process.reconstructionCosmics)

if PB :
  process.PBDigi_step = cms.Path(process.PBDigis)
  process.pilotBladeReco_step = cms.Path(
    process.PBClusters*
    process.PBRecHits
  )
# endif

process.endjob_step = cms.EndPath(process.endOfProcess)
process.RECOoutput_step = cms.EndPath(process.RECOoutput)

# Schedule definition
process.schedule = cms.Schedule(
  process.raw2digi_step,
  process.reconstruction_step,
  #PilotBlade part
  process.PBDigi_step,
  process.pilotBladeReco_step,
  # Endjob
  process.endjob_step,
  process.RECOoutput_step
)

# customisation of the process.
from Configuration.DataProcessing.RecoTLR import customiseCosmicDataRun2 
process = customiseCosmicDataRun2(process)

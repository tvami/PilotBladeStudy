# Auto generated configuration file
# using: 
# Revision: 1.19 
# Source: /local/reps/CMSSW/CMSSW/Configuration/Applications/python/ConfigBuilder.py,v 
# with command line options: 2CosmicsRaw2Reco.py --data --conditions 80X_dataRun2_Prompt_v3 --scenario cosmics --era Run2_25ns --step RAW2DIGI,L1Reco,RECO --datatier RECO --eventcontent RECO -n 100 --no_exec --filein root://xrootd.unl.edu//store/data/Commissioning2016/Cosmics/RAW/v1/000/266/136/00000/2E176E62-A0E4-E511-B5B9-02163E011F1C.root
import FWCore.ParameterSet.Config as cms

from Configuration.StandardSequences.Eras import eras

process = cms.Process('RECO',eras.Run2_25ns)

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContentCosmics_cff')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff')
process.load('Configuration.StandardSequences.RawToDigi_Data_cff')
process.load('Configuration.StandardSequences.L1Reco_cff')
process.load('L1Trigger.Configuration.L1Reco_cff')
process.load('Configuration.StandardSequences.ReconstructionCosmics_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

PB = cms.bool(True)

if PB:
  process.load('DPGAnalysis.PilotBladeStudy.PilotBladeSetup_cfi')
#endif

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(1000)
)

# Input source
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring('root://xrootd.unl.edu//store/data/Commissioning2016/Cosmics/RAW/v1/000/266/136/00000/2E176E62-A0E4-E511-B5B9-02163E011F1C.root'),
    secondaryFileNames = cms.untracked.vstring()
)

process.options = cms.untracked.PSet(

)

# Production Info
process.configurationMetadata = cms.untracked.PSet(
    annotation = cms.untracked.string('2CosmicsRaw2Reco.py nevts:100'),
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
    fileName = cms.untracked.string('2Cosmics_Raw2Reco_PilotBlade.root'),
    #outputCommands = process.RECOEventContent.outputCommands,
    outputCommands = cms.untracked.vstring(
    'drop *',
    'keep *_*lumi*_*_*',
    'keep *_*eamSpot*_*_*',
    'keep *_*onditions*_*_*',
    'keep *_*ixel*_*_*',
    'keep *_*PB*_*_*',
    'keep *_*racks*_*_*',
    'keep *_*iStripClusters*_*_*',
    'keep *awDataError*_*_*_*',
    ),
    splitLevel = cms.untracked.int32(0)
)
#-------------------------------------------------------

# Additional output definition

# Other statements
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, '80X_dataRun2_Prompt_v3', '')

# --------------------- Reconstruction --------------------
#Standard Pixel Digis
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
# endif
#-------------------------------------------------------

# Path and EndPath definitions
process.raw2digi_step = cms.Path(process.RawToDigi)
process.L1Reco_step = cms.Path(process.L1Reco)
process.conditionsInEdm_step = cms.Path(process.conditionsInEdm)
process.reconstruction_step = cms.Path(process.reconstructionCosmics)

if PB :
  process.PBDigi_step = cms.Path(process.PBDigis)
  process.pilotBladeReco_step = cms.Path(
    process.PBClusters*
    process.PBRecHits
  )
# endif

process.endjob_step = cms.EndPath(process.endOfProcess)
process.output_step = cms.EndPath(process.RECOoutput)

# Schedule definition
process.schedule = cms.Schedule(
  #standard part
  process.raw2digi_step,
  process.L1Reco_step,
  process.conditionsInEdm_step,
  process.reconstruction_step,
  
  #PilotBlade part
  process.PBDigi_step,
  process.pilotBladeReco_step,
  
  #end part
  process.endjob_step,
  process.output_step
)


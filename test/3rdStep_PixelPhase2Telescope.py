import FWCore.ParameterSet.Config as cms

from Configuration.StandardSequences.Eras import eras

process = cms.Process('Analysis',eras.Run2_2017)

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
#for the Pilot Blade reconstruction include the line below
process.load('DPGAnalysis.PilotBladeStudy.PilotBladeSetup_cfi')

# ------------------- Input ----------------------------
nEvents =  'All'

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring('file:./RAW2DIGI_L1Reco_RECO.root'),
    #eventsToProcess = cms.untracked.VEventRange('269794:286802','269807:198295'),
    secondaryFileNames = cms.untracked.vstring()
)

process.options = cms.untracked.PSet(
)
#-------------------------------------------------------

#----------------Production Info------------------------
process.configurationMetadata = cms.untracked.PSet(
    annotation = cms.untracked.string('Ntuplizer.py nevts:100'),
    name = cms.untracked.string('Applications'),
    version = cms.untracked.string('$Revision: 1.19 $')
)
#-------------------------------------------------------

## ------------------- Output ---------------------------
# we do not save the output from the standard sequance 
# only the output of the NTuplizer (PilotBladeStudy)
#-------------------------------------------------------

# --------------------- GlobalTag ----------------------
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:phase1_2017_realistic', '')


#---------------------- Refitter -----------------------
process.load("RecoTracker.TrackProducer.TrackRefitters_cff")
process.Refitter = process.TrackRefitterP5.clone()
process.Refitter.src = 'generalTracks'
process.Refitter.TrajectoryInEvent = True
#-------------------------------------------------------

#------------------- PilotBladeStudy -------------------
process.PilotBladeStudy = cms.EDAnalyzer("PilotBladeStudy",
  trajectoryInput = cms.string('Refitter'),
  fileName = cms.string('nTuple'+nEvents+'.root'),
  usePixelCPE= cms.bool(True),
  cosmicsCase = cms.bool(False),
  triggerNames=cms.vstring(
        "HLT_ZeroBias",
        "HLT_Physics",
        "HLT_Random",
        "HLT_MinBias"
        )
)
#-------------------------------------------------------

#--------------------- EndPath -------------------------
process.endjob_step = cms.EndPath(process.endOfProcess)

process.Refitter_step = cms.Path(
  process.MeasurementTrackerEvent*
  process.Refitter
)

process.PilotBladeStudy_step = cms.Path(process.PilotBladeStudy)

#--------------------- Schedule ------------------------
process.schedule = cms.Schedule(
  process.Refitter_step,
  process.PilotBladeStudy_step,	
)
#-------------------------------------------------------

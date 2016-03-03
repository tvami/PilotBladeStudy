# Source: /local/reps/CMSSW/CMSSW/Configuration/Applications/python/ConfigBuilder.py,v 
# with command line options: MinBias_13TeV_cfi.py -s RAW2DIGI,L1Reco,RECO --mc --conditions auto:run2_mc --pileup=NoPileUp --magField 38T_PostLS1 
# --customise SLHCUpgradeSimulations/Configuration/postLS1Customs.customisePostLS1 -n 10 --no_exec
# Author: Tamas Almos Vami
# Year: 2015
# Description: RECO data NTuplizer for Pilot Blade containing data

import FWCore.ParameterSet.Config as cms

process = cms.Process('Analysis')

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContentCosmics_cff')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
#for the Pilot Blade reconstruction include the line below
process.load('DPGAnalysis.PilotBladeStudy.PilotBladeSetup_cfi')


# ------------------- Input ----------------------------
nEvents =  'test'

process.maxEvents = cms.untracked.PSet(
  input = cms.untracked.int32(-1)
)

'''
# List of input files
from PoolSource_PB_ppData_RECO import *
InputFiles = FileNames
process.source = cms.Source("PoolSource",
  fileNames = InputFiles,
  secondaryFileNames = cms.untracked.vstring()
)
'''
process.source = cms.Source("PoolSource",
  fileNames = cms.untracked.vstring('file:2CosmicsPBRaw2Reco2_py_RAW2DIGI_L1Reco_RECO.root'),
  #fileNames = cms.untracked.vstring('file:/data/vami/projects/pilotBlade/ppProcessing/PilotBlade_HIFlowCorr_RAWtoRECO_Run263742_1k.root'), #1k input
  secondaryFileNames = cms.untracked.vstring()
)

process.options = cms.untracked.PSet(
)
#-------------------------------------------------------

#----------------Production Info------------------------
process.configurationMetadata = cms.untracked.PSet(
  annotation = cms.untracked.string('PilotBladeNtuplizer.py nevts:10'),
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
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:run2_data', '')
#process.GlobalTag = GlobalTag(process.GlobalTag, '75X_dataRun2_Prompt_v2', '')
#-------------------------------------------------------

#---------------------- Refitter -----------------------
process.load("RecoTracker.TrackProducer.TrackRefitters_cff")
process.Refitter = process.TrackRefitterP5.clone()
#process.Refitter = process.TrackRefitter.clone()

#process.Refitter.src = 'ctfWithMaterialTracksP5'
#process.Refitter.src = 'ctfWithMaterialTracksCosmics' # kinda kizarva
#process.Refitter.src = 'regionalCosmicTracks'
process.Refitter.src = '' 
'''
cosmictrackfinderP5
ctfWithMaterialTracksP5LHCNavigation, globalBeamHaloMuonEndCapslOnly, globalCosmicMuons
process.Refitter.src = 'cosmicMuons' # makes a crash: Invalid DetID: no GeomDet associated
process.Refitter.src = 'beamhaloTracks' # ntrack=0
process.Refitter.src = 'ckfInOutTracksFromConversions'  # ntrack=0
process.Refitter.src = 'ckfOutInTracksFromConversions' # ntrack=0
process.Refitter.src = 'cosmicMuonsEndCapsOnly' # ntrack=0
process.Refitter.src = 'cosmicMuonsNoRPC' # makes a crash: Invalid DetID: no GeomDet 
process.Refitter.src = 'cosmicMuons1Leg' # makes a crash: Invalid DetID: no GeomDet 
process.Refitter.src = 'standAloneMuons' # makes a crash: Invalid DetID: no GeomDet 
process.Refitter.src = 'cosmicMuons1Leg' # makes a crash: Invalid DetID: no GeomDet 
'''

process.Refitter.TrajectoryInEvent = True
#-------------------------------------------------------

#------------------- PilotBladeStudy -------------------
process.PilotBladeStudy = cms.EDAnalyzer("PilotBladeStudy",
  trajectoryInput = cms.string('Refitter'),
  fileName = cms.string('nTuplePilotBlade_'+nEvents+'.root'),
  usePixelCPE= cms.bool(True),
)
#-------------------------------------------------------

#--------------------- EndPath -------------------------
process.Refitter_step = cms.Path(
  process.MeasurementTrackerEvent*
  process.Refitter
)

process.PilotBladeStudy_step = cms.Path(process.PilotBladeStudy)
#-------------------------------------------------------

#--------------------- Schedule ------------------------
process.schedule = cms.Schedule(
  process.Refitter_step,
  process.PilotBladeStudy_step,	
)

# customisation of the process
from SLHCUpgradeSimulations.Configuration.postLS1Customs import customisePostLS1 
process = customisePostLS1(process)
#-------------------------------------------------------

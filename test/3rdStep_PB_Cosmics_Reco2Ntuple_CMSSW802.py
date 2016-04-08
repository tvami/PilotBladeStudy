# Auto generated configuration file
# using: 
# Revision: 1.19 
# Source: /local/reps/CMSSW/CMSSW/Configuration/Applications/python/ConfigBuilder.py,v 
# with command line options: 2CosmicsRaw2Reco.py --data --conditions 80X_dataRun2_Prompt_v1 --scenario cosmics --era Run2_25ns --step RAW2DIGI,L1Reco,RECO --datatier RECO --eventcontent RECO -n 100 --no_exec --filein root://xrootd.unl.edu//store/data/Commissioning2016/Cosmics/RAW/v1/000/265/368/00000/BC2DA80D-3EDB-E511-A86A-02163E0145C7.root
import FWCore.ParameterSet.Config as cms

from Configuration.StandardSequences.Eras import eras

process = cms.Process('Analysis',eras.Run2_25ns)

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
nEvents =  '2016CRUZET_All'

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
      'file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RECOs/Cosmics_Raw2Reco_PilotBlade_WBC165.root',
      'file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RECOs/Cosmics_Raw2Reco_PilotBlade_WBC166.root',
      'file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RECOs/Cosmics_Raw2Reco_PilotBlade_WBC167.root',
      'file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RECOs/Cosmics_Raw2Reco_PilotBlade_WBC168.root',
      'file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RECOs/Cosmics_Raw2Reco_PilotBlade_WBC169.root',
      'file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RECOs/Cosmics_Raw2Reco_PilotBlade_March21.root',
      'file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RECOs/Cosmics_Raw2Reco_PilotBlade_March22.root',
      'file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RECOs/Cosmics_Raw2Reco_PilotBlade_March23.root',
                        
      ),                
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
process.GlobalTag = GlobalTag(process.GlobalTag, '80X_dataRun2_Prompt_v1', '')

#---------------------- Refitter -----------------------
process.load("RecoTracker.TrackProducer.TrackRefitters_cff")
process.Refitter = process.TrackRefitterP5.clone()
process.Refitter.src = 'ctfWithMaterialTracksP5'
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

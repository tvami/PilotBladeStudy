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
	'file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RECOs/April14/2Cosmics_Raw2Reco_PilotBlade_1.root',
	'file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RECOs/April14/2Cosmics_Raw2Reco_PilotBlade_2.root',
	'file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RECOs/April14/2Cosmics_Raw2Reco_PilotBlade_3.root',
	'file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RECOs/April14/2Cosmics_Raw2Reco_PilotBlade_4.root',
	'file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RECOs/April14/2Cosmics_Raw2Reco_PilotBlade_5.root',
	'file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RECOs/April14/2Cosmics_Raw2Reco_PilotBlade_6.root',
	'file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RECOs/April14/2Cosmics_Raw2Reco_PilotBlade_7.root',
	'file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RECOs/April14/2Cosmics_Raw2Reco_PilotBlade_8.root',
	'file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RECOs/April14/2Cosmics_Raw2Reco_PilotBlade_9.root',
	#'file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RECOs/April14/2Cosmics_Raw2Reco_PilotBlade_10.root',
	'file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RECOs/April14/2Cosmics_Raw2Reco_PilotBlade_11.root',
	'file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RECOs/April14/2Cosmics_Raw2Reco_PilotBlade_12.root',
	'file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RECOs/April14/2Cosmics_Raw2Reco_PilotBlade_13.root',
	'file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RECOs/April14/2Cosmics_Raw2Reco_PilotBlade_14.root',
	'file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RECOs/April14/2Cosmics_Raw2Reco_PilotBlade_15.root',
	'file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RECOs/April14/2Cosmics_Raw2Reco_PilotBlade_16.root',
	'file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RECOs/April14/2Cosmics_Raw2Reco_PilotBlade_17.root',
	'file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RECOs/April14/2Cosmics_Raw2Reco_PilotBlade_18.root',
	'file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RECOs/April14/2Cosmics_Raw2Reco_PilotBlade_19.root',
	'file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RECOs/April14/2Cosmics_Raw2Reco_PilotBlade_20.root',
	'file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RECOs/April14/2Cosmics_Raw2Reco_PilotBlade_21.root',
	'file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RECOs/April14/2Cosmics_Raw2Reco_PilotBlade_22.root',
	'file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RECOs/April14/2Cosmics_Raw2Reco_PilotBlade_23.root',
	'file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RECOs/April14/2Cosmics_Raw2Reco_PilotBlade_24.root',
	'file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RECOs/April14/2Cosmics_Raw2Reco_PilotBlade_25.root',
	'file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RECOs/April14/2Cosmics_Raw2Reco_PilotBlade_26.root',
	'file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RECOs/April14/2Cosmics_Raw2Reco_PilotBlade_27.root',
	'file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RECOs/April14/2Cosmics_Raw2Reco_PilotBlade_28.root',
	'file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RECOs/April14/2Cosmics_Raw2Reco_PilotBlade_29.root',
	'file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RECOs/April14/2Cosmics_Raw2Reco_PilotBlade_30.root',
	'file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RECOs/April14/2Cosmics_Raw2Reco_PilotBlade_31.root',
	'file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RECOs/April14/2Cosmics_Raw2Reco_PilotBlade_32.root',
	'file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RECOs/April14/2Cosmics_Raw2Reco_PilotBlade_33.root',
	'file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RECOs/April14/2Cosmics_Raw2Reco_PilotBlade_34.root',
	'file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RECOs/April14/2Cosmics_Raw2Reco_PilotBlade_35.root',
	'file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RECOs/April14/2Cosmics_Raw2Reco_PilotBlade_36.root',
	'file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RECOs/April14/2Cosmics_Raw2Reco_PilotBlade_37.root',
	'file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RECOs/April14/2Cosmics_Raw2Reco_PilotBlade_38.root',
	'file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RECOs/April14/2Cosmics_Raw2Reco_PilotBlade_39.root',
	'file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RECOs/April14/2Cosmics_Raw2Reco_PilotBlade_40.root',
	'file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RECOs/April14/2Cosmics_Raw2Reco_PilotBlade_41.root',
	'file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RECOs/April14/2Cosmics_Raw2Reco_PilotBlade_42.root',
	'file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RECOs/April14/2Cosmics_Raw2Reco_PilotBlade_43.root',
	'file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RECOs/April14/2Cosmics_Raw2Reco_PilotBlade_44.root',
	'file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RECOs/April14/2Cosmics_Raw2Reco_PilotBlade_45.root',
	'file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RECOs/April14/2Cosmics_Raw2Reco_PilotBlade_46.root',
	'file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RECOs/April14/2Cosmics_Raw2Reco_PilotBlade_47.root',
	'file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RECOs/April14/2Cosmics_Raw2Reco_PilotBlade_48.root',
	'file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RECOs/April14/2Cosmics_Raw2Reco_PilotBlade_49.root',
	'file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RECOs/April14/2Cosmics_Raw2Reco_PilotBlade_50.root',
	'file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RECOs/April14/2Cosmics_Raw2Reco_PilotBlade_51.root',
	'file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RECOs/April14/2Cosmics_Raw2Reco_PilotBlade_52.root',
	'file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RECOs/April14/2Cosmics_Raw2Reco_PilotBlade_53.root',
	'file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RECOs/April14/2Cosmics_Raw2Reco_PilotBlade_54.root',
	'file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RECOs/April14/2Cosmics_Raw2Reco_PilotBlade_55.root',
	'file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RECOs/April14/2Cosmics_Raw2Reco_PilotBlade_56.root',
	'file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RECOs/April14/2Cosmics_Raw2Reco_PilotBlade_57.root',
	'file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RECOs/April14/2Cosmics_Raw2Reco_PilotBlade_58.root',
	'file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RECOs/April14/2Cosmics_Raw2Reco_PilotBlade_59.root',
	'file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RECOs/April14/2Cosmics_Raw2Reco_PilotBlade_60.root',
	'file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RECOs/April14/2Cosmics_Raw2Reco_PilotBlade_61.root',
	'file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RECOs/April14/2Cosmics_Raw2Reco_PilotBlade_62.root',
	'file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RECOs/April14/2Cosmics_Raw2Reco_PilotBlade_63.root',
	'file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RECOs/April14/2Cosmics_Raw2Reco_PilotBlade_64.root',
	'file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RECOs/April14/2Cosmics_Raw2Reco_PilotBlade_65.root',
	'file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RECOs/April14/2Cosmics_Raw2Reco_PilotBlade_66.root',
	'file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RECOs/April14/2Cosmics_Raw2Reco_PilotBlade_67.root',
	'file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RECOs/April14/2Cosmics_Raw2Reco_PilotBlade_68.root',
	'file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RECOs/April14/2Cosmics_Raw2Reco_PilotBlade_69.root',
	'file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RECOs/April14/2Cosmics_Raw2Reco_PilotBlade_70.root',
	'file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RECOs/April14/2Cosmics_Raw2Reco_PilotBlade_71.root',
	'file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RECOs/April14/2Cosmics_Raw2Reco_PilotBlade_72.root',
	'file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RECOs/April14/2Cosmics_Raw2Reco_PilotBlade_73.root',
	'file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RECOs/April14/2Cosmics_Raw2Reco_PilotBlade_74.root',
	'file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RECOs/April14/2Cosmics_Raw2Reco_PilotBlade_75.root',
	'file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RECOs/April14/2Cosmics_Raw2Reco_PilotBlade_76.root',
	'file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RECOs/April14/2Cosmics_Raw2Reco_PilotBlade_77.root',
	'file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RECOs/April14/2Cosmics_Raw2Reco_PilotBlade_78.root',
	'file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RECOs/April14/2Cosmics_Raw2Reco_PilotBlade_79.root',
	'file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RECOs/April14/2Cosmics_Raw2Reco_PilotBlade_80.root',
	'file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RECOs/April14/2Cosmics_Raw2Reco_PilotBlade_81.root',
	'file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RECOs/April14/2Cosmics_Raw2Reco_PilotBlade_82.root',
	'file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RECOs/April14/2Cosmics_Raw2Reco_PilotBlade_83.root',
	'file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RECOs/April14/2Cosmics_Raw2Reco_PilotBlade_84.root',
	'file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RECOs/April14/2Cosmics_Raw2Reco_PilotBlade_85.root',
	'file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RECOs/April14/2Cosmics_Raw2Reco_PilotBlade_86.root',
	'file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RECOs/April14/2Cosmics_Raw2Reco_PilotBlade_87.root',
	'file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RECOs/April14/2Cosmics_Raw2Reco_PilotBlade_88.root',
	'file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RECOs/April14/2Cosmics_Raw2Reco_PilotBlade_89.root',
	'file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RECOs/April14/2Cosmics_Raw2Reco_PilotBlade_90.root',
	'file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RECOs/April14/2Cosmics_Raw2Reco_PilotBlade_91.root',
	'file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RECOs/April14/2Cosmics_Raw2Reco_PilotBlade_92.root',
	'file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RECOs/April14/2Cosmics_Raw2Reco_PilotBlade_93.root',
	'file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RECOs/April14/2Cosmics_Raw2Reco_PilotBlade_94.root',
	'file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RECOs/April14/2Cosmics_Raw2Reco_PilotBlade_95.root',
	'file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RECOs/April14/2Cosmics_Raw2Reco_PilotBlade_96.root',
	'file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RECOs/April14/2Cosmics_Raw2Reco_PilotBlade_97.root',
	'file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RECOs/April14/2Cosmics_Raw2Reco_PilotBlade_98.root',
	'file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RECOs/April14/2Cosmics_Raw2Reco_PilotBlade_99.root',
	'file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RECOs/April14/2Cosmics_Raw2Reco_PilotBlade_100.root',
	'file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RECOs/April14/2Cosmics_Raw2Reco_PilotBlade_101.root',
	'file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RECOs/April14/2Cosmics_Raw2Reco_PilotBlade_102.root',
	'file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RECOs/April14/2Cosmics_Raw2Reco_PilotBlade_103.root',
	'file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RECOs/April14/2Cosmics_Raw2Reco_PilotBlade_104.root',
	'file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RECOs/April14/2Cosmics_Raw2Reco_PilotBlade_105.root',             
    ),
    eventsToProcess = cms.untracked.VEventRange('269794:286802','269807:198295'),
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

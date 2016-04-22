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
   fileNames = cms.untracked.vstring(   
   "file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RAW/041E471E-1CE8-E511-BF54-02163E011E50.root",
   "file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RAW/06B74776-0AE8-E511-A77B-02163E011838.root",
   "file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RAW/08699F6E-1FE8-E511-94AD-02163E014176.root",
   "file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RAW/08C3C9D2-3BE8-E511-BE0E-02163E0139AE.root",
   "file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RAW/08D1A650-00E8-E511-B7DB-02163E0143DE.root",
   "file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RAW/0AD9F8D3-07E8-E511-83BC-02163E011939.root",
   "file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RAW/0C34010F-30E8-E511-9116-02163E013661.root",
   "file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RAW/0EE83415-4AE8-E511-B5BA-02163E011A99.root",
   "file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RAW/1047046D-55F0-E511-994A-02163E0145BF.root",
   "file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RAW/106D48F5-71E6-E511-B4B6-02163E012236.root",
   "file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RAW/10C29057-F3E7-E511-BA70-02163E0145AD.root",
   "file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RAW/14260525-26E8-E511-A36B-02163E0146EC.root",
   "file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RAW/1463B860-27E8-E511-B0FA-02163E0133C1.root",
   "file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RAW/160D9AF3-6CE6-E511-9840-02163E014157.root",
   "file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RAW/169679F4-29E8-E511-B38A-02163E0120CD.root",
   "file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RAW/1E92449A-93E6-E511-A48E-02163E0123F1.root",
   "file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RAW/2061F531-57E6-E511-BDF1-02163E0145AD.root",
   "file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RAW/226A9173-35E8-E511-B001-02163E01422E.root",
   "file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RAW/2284FE08-A7E6-E511-9C84-02163E014669.root",
   "file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RAW/22D8D32C-F4E7-E511-967F-02163E011DD1.root",
   "file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RAW/240E6FCA-19E8-E511-B267-02163E011FCE.root",
   "file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RAW/24B0EC60-6AE6-E511-846C-02163E012236.root",
   "file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RAW/2819568A-60E6-E511-A972-02163E0124F7.root",
   "file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RAW/2845B643-57E6-E511-A00E-02163E014796.root",
   "file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RAW/28849DD7-4AE8-E511-840A-02163E012B24.root",
   "file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RAW/2AB73E47-EA02-E611-A40E-02163E01383A.root",
   "file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RAW/2EC5B8AB-41E8-E511-8806-02163E011FCE.root",
   "file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RAW/30661315-49E8-E511-B93E-02163E01380B.root",
   "file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RAW/3071FF00-4DE8-E511-B4CB-02163E011DD1.root",
   "file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RAW/30D5537F-C3EF-E511-A6DA-02163E014450.root",
   "file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RAW/32241F67-69E6-E511-9921-02163E013927.root",
   "file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RAW/342BCF07-1DE8-E511-8361-02163E011E50.root",
   "file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RAW/363E86A9-EE02-E611-A47A-02163E0142E5.root",
   "file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RAW/3C0CAFF4-81E6-E511-9DC8-02163E011B04.root",
   "file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RAW/3EDD74BD-93E6-E511-849F-02163E013425.root",
   "file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RAW/3EE1CCE1-86E6-E511-AC3E-02163E013613.root",
   "file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RAW/445A5811-75E6-E511-9D0F-02163E012B15.root",
   "file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RAW/44A003DD-67E6-E511-B5F2-02163E014796.root",
   "file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RAW/44E906C9-00E8-E511-A4C4-02163E0141B2.root",
   "file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RAW/4829FB8F-85E6-E511-BF43-02163E013613.root",
   "file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RAW/4CEA1EF3-4705-E611-83D6-02163E014408.root",
   "file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RAW/505FBB6F-14E8-E511-B175-02163E0134CD.root",
   "file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RAW/50A6569E-26E8-E511-9E7D-02163E0141E4.root",
   "file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RAW/540756B9-8AE6-E511-9C0C-02163E01369D.root",
   "file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RAW/58FE8D67-11E8-E511-9954-02163E011B04.root",
   "file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RAW/5CFC1B88-94E6-E511-902E-02163E0134D0.root",
   "file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RAW/5E94796E-0AE8-E511-97CA-02163E011FCE.root",
   "file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RAW/62E63F4F-2BE8-E511-8298-02163E0127BC.root",
   "file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RAW/6444C23B-39E8-E511-9FBC-02163E011F50.root",
   "file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RAW/6444DBFF-38E8-E511-812B-02163E014720.root",
   "file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RAW/64595846-38E8-E511-BB84-02163E014408.root",
   "file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RAW/681DA9EE-5FE6-E511-B152-02163E0143FE.root",
   "file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RAW/68AEFC57-3DE8-E511-94A7-02163E014176.root",
   "file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RAW/6CAE51E3-55E6-E511-A864-02163E012236.root",
   "file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RAW/6CD66B64-2CE8-E511-95CA-02163E013825.root",
   "file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RAW/6E29DB9C-EEE7-E511-9005-02163E01410C.root",
   "file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RAW/72D5C63F-32E8-E511-B91B-02163E01422E.root",
   "file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RAW/745187E7-7AE6-E511-A5D8-02163E0124F7.root",
   "file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RAW/76E65AF5-46E8-E511-ACE4-02163E014157.root",
   "file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RAW/784586F6-56E6-E511-9499-02163E013476.root",
   "file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RAW/7872836B-1AE8-E511-99A9-02163E0133A6.root",
   "file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RAW/7CB3244D-16E8-E511-A5F1-02163E012236.root",
   "file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RAW/7CCC350C-5CE6-E511-8CD8-02163E012236.root",
   "file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RAW/7E0E295C-89E6-E511-81C0-02163E011939.root",
   "file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RAW/82E9E0E1-1FE8-E511-8815-02163E0137A4.root",
   "file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RAW/8633E8E8-FAE7-E511-9211-02163E01410C.root",
   "file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RAW/86383302-46E8-E511-9A47-02163E012B24.root",
   "file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RAW/86ADB60E-FBE7-E511-888F-02163E013927.root",
   "file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RAW/88094FA7-02E8-E511-B061-02163E0134CD.root",
   "file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RAW/882C1591-3EE8-E511-8F54-02163E011DD1.root",
   "file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RAW/8AA50010-8DE6-E511-95D4-02163E011939.root",
   "file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RAW/92DD2ECC-F2E7-E511-AA45-02163E0144EB.root",
   "file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RAW/9489AD8A-9AE6-E511-BFEF-02163E011BBB.root",
   "file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RAW/980744C1-0DE8-E511-887B-02163E011EB6.root",
   "file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RAW/A23369F6-5BE6-E511-B95C-02163E012236.root",
   "file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RAW/A4E02D7C-EDE7-E511-8566-02163E014176.root",
   "file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RAW/A6C1E473-06E8-E511-955F-02163E011FCE.root",
   "file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RAW/A84428AD-A6E6-E511-8688-02163E013449.root",
   "file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RAW/AA6D58A1-F1E7-E511-B504-02163E011939.root",
   "file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RAW/AC0103C6-6FE6-E511-BA56-02163E0146EB.root",
   "file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RAW/AE641F2C-9CE6-E511-AB9F-02163E011C50.root",
   "file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RAW/B4B1513E-17E8-E511-BEDD-02163E0134CD.root",
   "file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RAW/B6596526-26E8-E511-A005-02163E0133A6.root",
   "file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RAW/B8BA0044-7FE6-E511-9E15-02163E0117FF.root",
   "file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RAW/BA01EC7D-00E8-E511-80CA-02163E011FCE.root",
   "file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RAW/BE71524C-3EE8-E511-AE0F-02163E01380B.root",
   "file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RAW/C0B97189-5DE6-E511-975D-02163E0144F4.root",
   "file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RAW/C267E2E4-81E6-E511-BF0F-02163E0146EB.root",
   "file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RAW/C829EC29-57E6-E511-BC54-02163E012236.root",
   "file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RAW/CE82DCA7-7FE6-E511-B81C-02163E012B15.root",
   "file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RAW/CEF2D7A0-05E8-E511-84A8-02163E011FCE.root",
   "file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RAW/D060545B-9CE6-E511-9BC6-02163E011E50.root",
   "file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RAW/D21F8D7A-A6E6-E511-A84C-02163E011C50.root",
   "file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RAW/D27B88E1-74E6-E511-80A0-02163E013613.root",
   "file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RAW/D66053D5-68E6-E511-8E6A-02163E0124F7.root",
   "file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RAW/D6921E60-63E6-E511-871F-02163E013927.root",
   "file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RAW/E018ECAE-93E6-E511-B83F-02163E011996.root",
   "file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RAW/E0BE8F1C-4EE8-E511-99AB-02163E014503.root",
   "file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RAW/E264CF4A-62E6-E511-90F6-02163E0124F7.root",
   "file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RAW/E6C33FC8-0FE8-E511-B12E-02163E014176.root",
   "file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RAW/E822FB7D-71E6-E511-963D-02163E013927.root",
   "file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RAW/E8CFD286-FBE7-E511-8EA8-02163E0143FE.root",
   "file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RAW/EA032410-36E8-E511-B036-02163E011CC5.root",
   "file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RAW/EA1F98F6-46E8-E511-9D1B-02163E013927.root",
   "file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RAW/EE1C276F-11E8-E511-9ADE-02163E011939.root",
   "file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RAW/EE4D5F0A-44E8-E511-9F4A-02163E0142D9.root",
   "file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RAW/EE9BC15C-89E6-E511-9EBB-02163E012B15.root",
   "file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RAW/F2F766B6-FBE7-E511-96E9-02163E013927.root",
   "file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RAW/F4E9DF9C-0CE8-E511-9255-02163E011B04.root",
   "file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RAW/F83780DB-50F0-E511-8A9A-02163E014207.root",
   "file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RAW/F89DB064-2FE8-E511-8F28-02163E014508.root",
   "file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RAW/F8AB24AF-EAE7-E511-87BD-02163E011CC5.root",
   "file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RAW/FAC33985-03E8-E511-AB1C-02163E0142E1.root",
   "file:/data/vami/projects/pilotBlade/2016CosmicsProcessing/RAW/FCF168AD-78E6-E511-B659-02163E013927.root",
 ),
    eventsToProcess = cms.untracked.VEventRange('266423:43060','266423:48577','266423:54422','266423:76257','267363:2752','267363:2752','267537:702','267602:16211','266665:7744','269794:286802','269807:198295'),
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
    MissCalibrate = cms.untracked.bool(True),
    SplitClusters = cms.bool(False),
    VCaltoElectronGain = cms.int32(65),
    VCaltoElectronOffset = cms.int32(-414),                          
    payloadType = cms.string('Offline'),
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


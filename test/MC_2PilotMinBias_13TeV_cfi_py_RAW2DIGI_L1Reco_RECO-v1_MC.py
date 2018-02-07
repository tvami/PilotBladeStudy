# Auto generated configuration file
# using: 
# Revision: 1.19 
# Source: /local/reps/CMSSW/CMSSW/Configuration/Applications/python/ConfigBuilder.py,v 
# with command line options: MinBias_13TeV_cfi.py -s RAW2DIGI,L1Reco,RECO --mc --conditions auto:run2_mc --pileup=NoPileUp --magField 38T_PostLS1 --customise SLHCUpgradeSimulations/Configuration/postLS1Customs.customisePostLS1 -n 10 --no_exec
import FWCore.ParameterSet.Config as cms

process = cms.Process('RECO')

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('SimGeneral.MixingModule.mixNoPU_cfi')
#process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.Geometry.GeometrySimDB_cff')
process.load('Configuration.Geometry.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_PostLS1_cff')
process.load('Configuration.StandardSequences.RawToDigi_cff')
process.load('Configuration.StandardSequences.L1Reco_cff')
process.load('Configuration.StandardSequences.Reconstruction_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')

# ------------------- Input ----------------------------
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(25)
)

# Input source
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring('file:MinBias_13TeV_cfi_py_GEN_SIM_DIGI_L1_DIGI2RAW-N1.root'),
    secondaryFileNames = cms.untracked.vstring()
)

process.options = cms.untracked.PSet(

)

# Production Info
process.configurationMetadata = cms.untracked.PSet(
    annotation = cms.untracked.string('MinBias_13TeV_cfi.py nevts:10'),
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
    fileName = cms.untracked.string('MinBias_13TeV_cfi_py_RAW2DIGI_L1Reco_RECO.root'),
    outputCommands = cms.untracked.vstring('drop *','keep *_*ixel*_*_*'),
    #outputCommands = process.RECOSIMEventContent.outputCommands,
    splitLevel = cms.untracked.int32(0)
)

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('digicluster_histos.root')
)

#-------------------------------------------------------
# Other statements
# --------------------- GlobalTag ----------------------
from Configuration.AlCa.GlobalTag_condDBv2 import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:run2_mc', '')
print process.GlobalTag.globaltag
import CalibTracker.Configuration.Common.PoolDBESSource_cfi


# ---------------------- PB Geometry -------------------
process.trackerGeometryDB.applyAlignment = cms.bool(False)
process.XMLFromDBSource.label=''
process.PoolDBESSourceGeometry = cms.ESSource("PoolDBESSource",
                               process.CondDBSetup,
                               timetype = cms.string('runnumber'),
                               toGet = cms.VPSet(
							cms.PSet(record = cms.string('GeometryFileRcd'),tag = cms.string('XMLFILE_Geometry_74YV2_Extended2015_mc')),
                                                        cms.PSet(record = cms.string('IdealGeometryRecord'),tag = cms.string('TKRECO_Geometry_74YV2')),
                                                        cms.PSet(record = cms.string('PGeometricDetExtraRcd'),tag = cms.string('TKExtra_Geometry_74YV2')),
                                                        cms.PSet(record = cms.string('PTrackerParametersRcd'),tag = cms.string('TKParameters_Geometry_74YV2')),
                                                        cms.PSet(record = cms.string('PEcalBarrelRcd'),   tag = cms.string('EBRECO_Geometry_74YV2')),
                                                        cms.PSet(record = cms.string('PEcalEndcapRcd'),   tag = cms.string('EERECO_Geometry_74YV2')),
                                                        cms.PSet(record = cms.string('PEcalPreshowerRcd'),tag = cms.string('EPRECO_Geometry_74YV2')),
                                                        cms.PSet(record = cms.string('PHcalRcd'),         tag = cms.string('HCALRECO_Geometry_74YV2')),
                                                        cms.PSet(record = cms.string('PCaloTowerRcd'),    tag = cms.string('CTRECO_Geometry_74YV2')),
                                                        cms.PSet(record = cms.string('PZdcRcd'),          tag = cms.string('ZDCRECO_Geometry_74YV2')),
                                                        cms.PSet(record = cms.string('PCastorRcd'),       tag = cms.string('CASTORRECO_Geometry_74YV2')),
                                                        cms.PSet(record = cms.string('CSCRecoGeometryRcd'),tag = cms.string('CSCRECO_Geometry_74YV2')),
                                                        cms.PSet(record = cms.string('CSCRecoDigiParametersRcd'),tag = cms.string('CSCRECODIGI_Geometry_74YV2')),
                                                        cms.PSet(record = cms.string('DTRecoGeometryRcd'),tag = cms.string('DTRECO_Geometry_74YV2')),
                                                        cms.PSet(record = cms.string('RPCRecoGeometryRcd'),tag = cms.string('RPCRECO_Geometry_74YV2'))
                                                        ),
                               connect = cms.string('sqlite_file:/data/vami/projects/PilotBlade/PilotGeometry.db')
                               )
process.es_prefer_geometry = cms.ESPrefer( "PoolDBESSource", "PoolDBESSourceGeometry" )
#-------------------------------------------------------
# --------------------- SiPixelQuality -----------------
process.SiPixelQualityDBReader = cms.ESSource("PoolDBESSource",
	BlobStreamerName = cms.untracked.string('TBufferBlobStreamingService'),
    DBParameters = cms.PSet(
	    messageLevel = cms.untracked.int32(0),
	    authenticationPath = cms.untracked.string('')
	),
	connect = cms.string ('sqlite_file:/data/vami/projects/PilotBlade/SiPixelQuality_PilotBlade3.db'),
    toGet = cms.VPSet(
    	cms.PSet(
			record = cms.string('SiPixelQualityFromDbRcd'),
			tag = cms.string('SiPixelQuality_PilotBlade')
        )
    )
)
process.es_prefer_Quality = cms.ESPrefer("PoolDBESSource","SiPixelQualityDBReader")
#-------------------------------------------------------

# --------------------- CablingMap ---------------------
process.CablingMapDBReader = cms.ESSource("PoolDBESSource",
	BlobStreamerName = cms.untracked.string('TBufferBlobStreamingService'),
    DBParameters = cms.PSet(
	    messageLevel = cms.untracked.int32(0),
	    authenticationPath = cms.untracked.string('')
	),
	connect = cms.string('sqlite_file:/data/vami/projects/PilotBlade/SiPixelCabling_PilotBlade.db'),
    toGet = cms.VPSet(
    	cms.PSet(
			record = cms.string('SiPixelFedCablingMapRcd'),
			tag = cms.string('SiPixelFedCablingMap_mc')
    	)
    )
)
process.es_prefer_CablingReader = cms.ESPrefer("PoolDBESSource","CablingMapDBReader")

#-------------------------------------------------------

# --------------------- LorentzAngle -------------------

process.LorentzAngleDBReader = cms.ESSource("PoolDBESSource",
	BlobStreamerName = cms.untracked.string('TBufferBlobStreamingService'),
    DBParameters = cms.PSet(
	    messageLevel = cms.untracked.int32(0),
	    authenticationPath = cms.untracked.string('')
	),
	connect = cms.string ('sqlite_file:/data/vami/projects/PilotBlade/SiPixelLorentzAngle_PilotBlade.db'),
    toGet = cms.VPSet(
      	cms.PSet(
			record = cms.string('SiPixelLorentzAngleSimRcd'),
            tag = cms.string('SiPixelLorentzAngleSim_v02_mc')
		)
	)
)
process.es_prefer_LA = cms.ESPrefer("PoolDBESSource","LorentzAngleDBReader")


# --------------------- Reconstruction --------------------
process.load('CondTools.SiPixel.SiPixelGainCalibrationService_cfi')
process.load('RecoLocalTracker.SiPixelRecHits.PixelCPEESProducers_cff')

process.siPixelDigis.UsePilotBlade = cms.bool(True)

process.PixelCPEGenericESProducer.UseErrorsFromTemplates = cms.bool(False)
process.PixelCPEGenericESProducer.TruncatePixelCharge = cms.bool(False)
process.PixelCPEGenericESProducer.IrradiationBiasCorrection = cms.bool(False)
process.PixelCPEGenericESProducer.LoadTemplatesFromDB = cms.bool(False)
process.PixelCPEGenericESProducer.DoCosmics = cms.bool(False)
'''
###process.load('RecoLocalTracker.SiPixelClusterizer.SiPixelClusterizer_cfi')

process.siPixelClusters = cms.EDProducer("SiPixelClusterProducer",
    ###SiPixelGainCalibrationServiceParameters,
    src = cms.InputTag("siPixelDigis"),
    ChannelThreshold = cms.int32(1000),
    MissCalibrate = cms.untracked.bool(False),
    SplitClusters = cms.bool(False),
    VCaltoElectronGain = cms.int32(65),
    VCaltoElectronOffset = cms.int32(-414),                          
    # **************************************
    # ****  payLoadType Options         ****
    # ****  HLT - column granularity    ****
    # ****  Offline - gain:col/ped:pix  ****
    # **************************************
    payloadType = cms.string('Offline'),
    SeedThreshold = cms.int32(1000),
    ClusterThreshold = cms.double(4000.0),
    # **************************************
    maxNumberOfClusters = cms.int32(-1), # -1 means no limit.
)


###process.load('RecoLocalTracker.SiPixelRecHits.SiPixelRecHits_cfi')

process.siPixelRecHits = cms.EDProducer("SiPixelRecHitConverter",
    src = cms.InputTag("siPixelClusters"),
    CPE = cms.string('PixelCPEGeneric'),
    VerboseLevel = cms.untracked.int32(0),

)
'''
#-------------------------------------------------------

#---------------------- Analyzers ----------------------
process.analyzeDigis = cms.EDAnalyzer("PixelDigisTest",
    Verbosity = cms.untracked.bool(True),
    src = cms.InputTag("siPixelDigis"),
)

process.analyzeClusters = cms.EDAnalyzer("ReadPixClusters",
    Verbosity = cms.untracked.bool(True),
    src = cms.InputTag("siPixelClusters"),
)

process.analyzeRecHits = cms.EDAnalyzer("ReadPixelRecHit",
    Verbosity = cms.untracked.bool(True),
    src = cms.InputTag("siPixelRecHits"),
)
#-------------------------------------------------------

# ------------------------ Path ------------------------
process.raw2digi_step = cms.Path(process.RawToDigi)
process.L1Reco_step = cms.Path(process.L1Reco)
process.reconstruction_step = cms.Path(process.reconstruction)
process.siPixelClusters_step = cms.Path(process.siPixelClusters)
process.siPixelRecHits_step = cms.Path(process.siPixelRecHits)

process.analyzePBDigis_step = cms.Path(process.analyzeDigis)
process.analyzePBClusters_step = cms.Path(process.analyzeClusters)
process.analyzePBRecHits_step = cms.Path(process.analyzeRecHits)

process.endjob_step = cms.EndPath(process.endOfProcess)
process.RECOSIMoutput_step = cms.EndPath(process.RECOSIMoutput)

# Schedule definition
process.schedule = cms.Schedule(
	process.raw2digi_step,
	process.L1Reco_step,
	process.reconstruction_step,
	#process.siPixelClusters_step,
	#process.siPixelRecHits_step,
	process.analyzePBDigis_step,
	process.analyzePBClusters_step,
	process.analyzePBRecHits_step,
	process.endjob_step,
	process.RECOSIMoutput_step
)

# customisation of the process.

# Automatic addition of the customisation function from SLHCUpgradeSimulations.Configuration.postLS1Customs
from SLHCUpgradeSimulations.Configuration.postLS1Customs import customisePostLS1 

#call to customisation function customisePostLS1 imported from SLHCUpgradeSimulations.Configuration.postLS1Customs
process = customisePostLS1(process)

# End of customisation functions


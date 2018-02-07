# Auto generated configuration file
# using: 
# Revision: 1.19 
# Source: /local/reps/CMSSW/CMSSW/Configuration/Applications/python/ConfigBuilder.py,v 
# with command line options: MinBias_13TeV_cfi.py -s GEN,SIM,DIGI,L1,DIGI2RAW --mc --conditions auto:run2_mc --pileup=NoPileUp --magField 38T_PostLS1 --customise SLHCUpgradeSimulations/Configuration/postLS1Customs.customisePostLS1 -n 10 --no_exec
import FWCore.ParameterSet.Config as cms

process = cms.Process('DIGI2RAW')

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
process.load('Configuration.StandardSequences.Generator_cff')
process.load('IOMC.EventVertexGenerators.VtxSmearedNominalCollision2015_cfi')
process.load('GeneratorInterface.Core.genFilterSummary_cff')
process.load('Configuration.StandardSequences.SimIdeal_cff')
process.load('Configuration.StandardSequences.Digi_cff')
process.load('Configuration.StandardSequences.SimL1Emulator_cff')
process.load('Configuration.StandardSequences.DigiToRaw_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')

# ---------------------- PB Geometry -------------------
#process.load("Geometry.CMSCommonData.cmsExtendedGeometry2015PilotXML_cfi")
#process.load('Geometry.TrackerGeometryBuilder.trackerGeometry_cfi')
process.trackerGeometryDB.applyAlignment = cms.bool(False)
process.mix.digitizers.pixel.enablePilotBlades = cms.bool(True)

process.mix.digitizers.pixel.DeadModules_DB = cms.bool(True) #SiPixelQuality
process.mix.digitizers.pixel.LorentzAngle_DB = cms.bool(True)

#-------------------------------------------------------
# ------------------- Input ----------------------------
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(25)
)

# Input source
process.source = cms.Source("EmptySource")

process.options = cms.untracked.PSet(

)
#-------------------------------------------------------
#----------------Production Info------------------------
process.configurationMetadata = cms.untracked.PSet(
    annotation = cms.untracked.string('MinBias_13TeV_cfi.py nevts:10'),
    name = cms.untracked.string('Applications'),
    version = cms.untracked.string('$Revision: 1.19 $')
)
#-------------------------------------------------------

# ------------------- Output ---------------------------
process.MYoutput = cms.OutputModule("PoolOutputModule",
    SelectEvents = cms.untracked.PSet(
        SelectEvents = cms.vstring('generation_step')
    ),
    dataset = cms.untracked.PSet(
        dataTier = cms.untracked.string(''),
        filterName = cms.untracked.string('')
    ),
    eventAutoFlushCompressedSize = cms.untracked.int32(5242880),
    fileName = cms.untracked.string('MinBias_13TeV_cfi_py_GEN_SIM_DIGI_L1_DIGI2RAW.root'),
    outputCommands = cms.untracked.vstring(
    'keep *',
    'drop *_simCastorDigis_*_*',
    'drop *_simEcalUnsuppressedDigis_*_*',
    'drop *_simHcalUnsuppressedDigis_*_*',
    'drop *_simSiPixelDigis_*_*',
    'drop *_simSiStripDigis_*_*',
    ),
    splitLevel = cms.untracked.int32(0)
)
process.TFileService = cms.Service("TFileService",
    fileName = cms.string('Pilot_digi_histos_3k.root')
)
#-------------------------------------------------------

# Other statements
# --------------------- GlobalTag ----------------------
from Configuration.AlCa.GlobalTag_condDBv2 import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:run2_mc', '')
print process.GlobalTag.globaltag
import CalibTracker.Configuration.Common.PoolDBESSource_cfi

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

# --------------------- Gain Calab DB ------------------
process.GainDBReader = cms.ESSource("PoolDBESSource",
        BlobStreamerName = cms.untracked.string('TBufferBlobStreamingService'),
    DBParameters = cms.PSet(
            messageLevel = cms.untracked.int32(0),
            authenticationPath = cms.untracked.string('')
        ),
        connect = cms.string ('sqlite_file:/data/vami/projects/PilotBlade/GainDB_PilotBlade.db'),
    toGet = cms.VPSet(
        cms.PSet(
                        record = cms.string('SiPixelGainCalibrationOfflineRcd'),
                        tag = cms.string('GainCalib_TEST_offline')
        )
    )
)
process.es_prefer_GainCalib = cms.ESPrefer("PoolDBESSource","GainDBReader")

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

#-------------------------------------------------------
#-------------------------------------------------------
process.genstepfilter.triggerConditions=cms.vstring("generation_step")
process.generator = cms.EDFilter("Pythia6GeneratorFilter",
    PythiaParameters = cms.PSet(
        parameterSets = cms.vstring('pythiaUESettings', 
            'processParameters'),
        processParameters = cms.vstring('MSEL=0         ! User defined processes', 
            'MSUB(11)=1     ! Min bias process', 
            'MSUB(12)=1     ! Min bias process', 
            'MSUB(13)=1     ! Min bias process', 
            'MSUB(28)=1     ! Min bias process', 
            'MSUB(53)=1     ! Min bias process', 
            'MSUB(68)=1     ! Min bias process', 
            'MSUB(92)=1     ! Min bias process, single diffractive', 
            'MSUB(93)=1     ! Min bias process, single diffractive', 
            'MSUB(94)=1     ! Min bias process, double diffractive', 
            'MSUB(95)=1     ! Min bias process'),
        pythiaUESettings = cms.vstring('MSTU(21)=1     ! Check on possible errors during program execution', 
            'MSTJ(22)=2     ! Decay those unstable particles', 
            'PARJ(71)=10 .  ! for which ctau  10 mm', 
            'MSTP(33)=0     ! no K factors in hard cross sections', 
            'MSTP(2)=1      ! which order running alphaS', 
            'MSTP(51)=10042 ! structure function chosen (external PDF CTEQ6L1)', 
            'MSTP(52)=2     ! work with LHAPDF', 
            'PARP(82)=1.921 ! pt cutoff for multiparton interactions', 
            'PARP(89)=1800. ! sqrts for which PARP82 is set', 
            'PARP(90)=0.227 ! Multiple interactions: rescaling power', 
            'MSTP(95)=6     ! CR (color reconnection parameters)', 
            'PARP(77)=1.016 ! CR', 
            'PARP(78)=0.538 ! CR', 
            'PARP(80)=0.1   ! Prob. colored parton from BBR', 
            'PARP(83)=0.356 ! Multiple interactions: matter distribution parameter', 
            'PARP(84)=0.651 ! Multiple interactions: matter distribution parameter', 
            'PARP(62)=1.025 ! ISR cutoff', 
            'MSTP(91)=1     ! Gaussian primordial kT', 
            'PARP(93)=10.0  ! primordial kT-max', 
            'MSTP(81)=21    ! multiple parton interactions 1 is Pythia default', 
            'MSTP(82)=4     ! Defines the multi-parton model')
    ),
    comEnergy = cms.double(13000.0),
    filterEfficiency = cms.untracked.double(1.0),
    maxEventsToPrint = cms.untracked.int32(0),
    pythiaHepMCVerbosity = cms.untracked.bool(False),
    pythiaPylistVerbosity = cms.untracked.int32(0)
)
#---------------------- Analyzers ----------------------
process.analyzeDigis = cms.EDAnalyzer("PixelDigisTest",
    Verbosity = cms.untracked.bool(True),
    src = cms.InputTag("mix"),
)
#-------------------------------------------------------

# ------------------------ Path ------------------------
# Path and EndPath definitions
process.generation_step = cms.Path(process.pgen)
process.simulation_step = cms.Path(process.psim)
process.digitisation_step = cms.Path(process.pdigi)
process.L1simulation_step = cms.Path(process.SimL1Emulator)
process.digi2raw_step = cms.Path(process.DigiToRaw)

process.analyzeDigis_step = cms.Path(process.analyzeDigis)

process.genfiltersummary_step = cms.EndPath(process.genFilterSummary)
process.endjob_step = cms.EndPath(process.endOfProcess)
process.MYoutput_step = cms.EndPath(process.MYoutput)
#-------------------------------------------------------
# ------------------------ Schedule --------------------
process.schedule = cms.Schedule(
	process.generation_step,
	process.genfiltersummary_step,
	process.simulation_step,
	process.digitisation_step,
	process.L1simulation_step,
	process.digi2raw_step,
	process.analyzeDigis_step,
	process.endjob_step,
	process.MYoutput_step
)
#-------------------------------------------------------
# filter all path with the production filter sequence
for path in process.paths:
	getattr(process,path)._seq = process.generator * getattr(process,path)._seq 

# customisation of the process.

# Automatic addition of the customisation function from SLHCUpgradeSimulations.Configuration.postLS1Customs
from SLHCUpgradeSimulations.Configuration.postLS1Customs import customisePostLS1 

#call to customisation function customisePostLS1 imported from SLHCUpgradeSimulations.Configuration.postLS1Customs
process = customisePostLS1(process)

# End of customisation functions


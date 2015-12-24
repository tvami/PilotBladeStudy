import FWCore.ParameterSet.Config as cms

from Configuration.Geometry.GeometrySimDB_cff import*
from Configuration.Geometry.GeometryRecoDB_cff import*
from Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff import*

import CalibTracker.Configuration.Common.PoolDBESSource_cfi

PB = cms.bool(True)

# Output for the histograms
TFileService = cms.Service("TFileService",
  fileName = cms.string('histos.root')
)

#---------------------- Analyzers ----------------------
analyzeDigis = cms.EDAnalyzer("PixelDigisTest",
  Verbosity = cms.untracked.bool(False),
  src = cms.InputTag("siPixelDigis"),
)

analyzeClusters = cms.EDAnalyzer("ReadPixClusters",
  Verbosity = cms.untracked.bool(False),
  src = cms.InputTag("siPixelClusters"),
)

analyzeRecHits = cms.EDAnalyzer("ReadPixelRecHit",
  Verbosity = cms.untracked.bool(False),
  src = cms.InputTag("siPixelRecHits"),
)

if PB :
  analyzePBDigis = cms.EDAnalyzer("PixelDigisTest",
    Verbosity = cms.untracked.bool(False),
    src = cms.InputTag("PBDigis"),
  )

  analyzePBClusters = cms.EDAnalyzer("ReadPixClusters",
    Verbosity = cms.untracked.bool(False),
    src = cms.InputTag("PBClusters"),
  )
  analyzePBRecHits = cms.EDAnalyzer("ReadPixelRecHit",
    Verbosity = cms.untracked.bool(False),
    src = cms.InputTag("PBRecHits"),
  )
#endif
#-------------------------------------------------------

#--------------------- EndPath -------------------------
analyze_step = cms.Path(
  analyzeDigis*
  analyzeClusters*
  analyzeRecHits
)

if PB :
  analyzePB_step = cms.Path(
    analyzePBDigis*
    analyzePBClusters*
    analyzePBRecHits
  )
#endif
#-------------------------------------------------------
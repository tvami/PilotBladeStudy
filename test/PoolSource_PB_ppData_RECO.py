# Desciption: example how to set up many input files. After 255 files put the next files to the .extend part
import FWCore.ParameterSet.Config as cms
myfilelist = cms.untracked.vstring()
myfilelist.extend([
  'file:/data/vami/projects/pilotBlade/ppProcessing/Results/PilotMinBias_13TeV_cfi_py_RAW2DIGI_L1Reco_RECO2900Event.root',
  ])
#myfilelist.extend([  
#  ])
FileNames = myfilelist

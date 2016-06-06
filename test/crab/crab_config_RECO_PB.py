from CRABClient.UserUtilities import config 
config = config()

config.section_('General')
config.General.requestName = 'PilotBlade_data_RECO_pp_Run274387_v1'
config.General.transferOutputs = True
config.General.transferLogs = True

config.section_('JobType')
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = '2ppRaw2Reco_CMSSW80X.py'
#config.JobType.maxMemoryMB = 3000


config.section_('Data')
config.Data.inputDataset = '/ExpressPhysics/Run2016B-Express-v2/FEVT'
config.Data.runRange = '274000-274443'
config.Data.splitting = 'LumiBased'
config.Data.unitsPerJob = 1 
config.Data.outLFNDirBase = '/store/user/tvami/PilotBlade_data_RECO_pp_Run274387_v1/'
config.Data.publication = True
config.Data.outputDatasetTag  = config.General.requestName

config.section_('Site')
config.Site.storageSite = 'T2_HU_Budapest'

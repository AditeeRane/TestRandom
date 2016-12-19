# Auto generated configuration file
# using: 
# Revision: 1.19 
# Source: /local/reps/CMSSW/CMSSW/Configuration/Applications/python/ConfigBuilder.py,v 
# with command line options: Sep13_NewTemplate/SampleProduction/python/SingleW_Pt_0_pythia8_cfi.py --conditions auto:run2_mc -n 10 --eventcontent FEVTDEBUG -s GEN,SIM --datatier GEN-SIM --beamspot Realistic50ns13TeVCollision --era Run2_2016 --fileout step1.root
import FWCore.ParameterSet.Config as cms
import sys
from Configuration.StandardSequences.Eras import eras

process = cms.Process('SIM',eras.Run2_2016)

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('SimGeneral.MixingModule.mixNoPU_cfi')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.Geometry.GeometrySimDB_cff')
process.load('Configuration.StandardSequences.MagneticField_cff')
process.load('Configuration.StandardSequences.Generator_cff')
process.load('IOMC.EventVertexGenerators.VtxSmearedRealistic50ns13TeVCollision_cfi')
process.load('GeneratorInterface.Core.genFilterSummary_cff')
process.load('Configuration.StandardSequences.SimIdeal_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(500)
)

# Input source
process.source = cms.Source("EmptySource")

process.options = cms.untracked.PSet(

)
#seed = int(raw_input("Enter a Number->"))
sys.stdout.write('Enter integer to provide seed\n')
x = sys.stdin.readline()
print x
print 'Number of arguments: ',len(sys.argv)
print 'Argument List:', str(sys.argv)
print 'Argument_0: ', sys.argv[0]
print 'Argument_1: ', sys.argv[1]
seed = int(sys.argv[2])
print 'seed: ',seed

OutName = sys.argv[3]
print 'OutName: ',OutName
#seed = int(x)
#seed = x
# Production Info
process.configurationMetadata = cms.untracked.PSet(
    annotation = cms.untracked.string('Sep13_NewTemplate/SampleProduction/python/SingleW_Pt_0_pythia8_cfi.py nevts:10'),
    name = cms.untracked.string('Applications'),
    version = cms.untracked.string('$Revision: 1.19 $')
)

# Output definition

process.FEVTDEBUGoutput = cms.OutputModule("PoolOutputModule",
    SelectEvents = cms.untracked.PSet(
        SelectEvents = cms.vstring('generation_step')
    ),
    dataset = cms.untracked.PSet(
        dataTier = cms.untracked.string('GEN-SIM'),
        filterName = cms.untracked.string('')
    ),
    eventAutoFlushCompressedSize = cms.untracked.int32(5242880),
    fileName = cms.untracked.string(OutName),
    outputCommands = process.FEVTDEBUGEventContent.outputCommands,
    splitLevel = cms.untracked.int32(0)
)

# Additional output definition

# Other statements
process.genstepfilter.triggerConditions=cms.vstring("generation_step")
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:run2_mc', '')

process.generator = cms.EDFilter("Pythia8PtGun",
				 PGunParameters = cms.PSet(
		AddAntiParticle = cms.bool(False),
		MaxEta = cms.double(2.4),
		MaxPhi = cms.double(3.14159265359),
		MaxPt = cms.double(160.0),
		MinEta = cms.double(-2.4),
		MinPhi = cms.double(-3.14159265359),
		MinPt = cms.double(0.0),
		ParticleID = cms.vint32(-24)
		),
				 initialSeed = cms.untracked.uint32(123456789),
				 engineName = cms.untracked.string('HepJamesRandom'),
				 PythiaParameters = cms.PSet(
		#        parameterSets = cms.vstring()
			parameterSets = cms.vstring('pythia8CommonSettings', 
						    'py8WDecaySettings', 
						    'pythiaTauJets'),
			py8WDecaySettings = cms.vstring('24:onMode = off', 
							'24:onIfAny = 15 16'),
			pythia8CUEP8M1Settings = cms.vstring('Tune:pp 14', 
							     'Tune:ee 7', 
							     'MultipartonInteractions:pT0Ref=2.4024', 
							     'MultipartonInteractions:ecmPow=0.25208', 
							     'MultipartonInteractions:expPow=1.6'),
			pythia8CommonSettings = cms.vstring('Tune:preferLHAPDF = 2', 
							    'Main:timesAllowErrors = 10000', 
							    'Check:epTolErr = 0.01', 
							    'Beams:setProductionScalesFromLHEF = off', 
							    'SLHA:keepSM = on', 
							    'SLHA:minMassSM = 1000.', 
							    'ParticleDecays:limitTau0 = on', 
							    'ParticleDecays:tau0Max = 10', 
							    'ParticleDecays:allowPhotonRadiation = on'),
			pythiaTauJets = cms.vstring(#'ParticleDecays:sophisticatedTau = 2', 
				#'ParticleDecays:tauPolarization = 0', 
				'15:onMode = off', 
				'15:onIfAny = 211 -211 321 -321')
			)
				 )
					   
#process.RandomNumberGeneratorService.generator.initialSeed = 10
#process.RandomNumberGeneratorService.generator.initialSeed = cms.vint32(x)
process.RandomNumberGeneratorService.generator.initialSeed = seed
#process.RandomNumberGeneratorService.generator.initialSeed = pythia.readString("Random:seed = 0")
#process.RandomNumberGeneratorService.generator.initialSeed = cms.vstring('Random:seed = 0')

process.printGenParticles = cms.EDAnalyzer("ParticleListDrawer",
					   src = cms.InputTag("genParticles"),
					   maxEventsToPrint = cms.untracked.int32(10) )

# Path and EndPath definitions
process.generation_step = cms.Path(process.pgen * process.printGenParticles)
process.simulation_step = cms.Path(process.psim)
process.genfiltersummary_step = cms.EndPath(process.genFilterSummary)
process.endjob_step = cms.EndPath(process.endOfProcess)
process.FEVTDEBUGoutput_step = cms.EndPath(process.FEVTDEBUGoutput)

# Schedule definition
process.schedule = cms.Schedule(process.generation_step,process.simulation_step,process.genfiltersummary_step,process.endjob_step,process.FEVTDEBUGoutput_step)
# filter all path with the production filter sequence
for path in process.paths:
	getattr(process,path)._seq = process.generator * getattr(process,path)._seq 



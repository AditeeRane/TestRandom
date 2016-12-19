#!/bin/sh
#cd /home/borzou/CMSSW_7_4_0_pre1/src/RA2-RA2b-2015/New_RA2b_2015

ArgOne=$1   # 
ArgTwo=$2   # 
ArgThree=$3 # 
ArgFour=$4  # 
ArgSeven=$5 

echo ArgOne $ArgOne 
echo ArgTwo $ArgTwo 
echo ArgThree $ArgThree 
echo ArgFour $ArgFour 
echo ArgSeven $ArgSeven

#
# first go to the submission dir, and set up the environment
#
cd $ArgSeven 
source /cvmfs/cms.cern.ch/cmsset_default.sh
eval `scram runtime -sh`
cmsenv
#
# now go to the condor's scratch area, where we copied the contents of TestRandom
#
cd ${_CONDOR_SCRATCH_DIR} 

mkdir -p StepOne

pwd
ls -l
#mkdir -p HadTauMultiple
#mkdir -p HadTau2Multiple

#
# run the job
#
echo $ArgOne $ArgTwo $ArgThree $ArgFour
$ArgOne $ArgTwo $ArgThree $ArgFour

#xrdcp fdfkdflkdkj outputfilename eosarea
xrdcp -f $ArgFour root://cmseos.fnal.gov//store/user/arane/SingleW_StepOne/
#rm $datasetName'_'$outputFileTag


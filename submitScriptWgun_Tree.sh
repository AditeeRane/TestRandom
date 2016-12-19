#!/bin/sh
#cd /home/borzou/CMSSW_7_4_0_pre1/src/RA2-RA2b-2015/New_RA2b_2015

ArgOne=$1   # 
ArgTwo=$2   # 
ArgThree=$3 # 
ArgFour=$4  #
ArgFive=$5
ArgSix=$6 
ArgSeven=$7 
ArgEight=$8
ArgNine=$9
#OutFile=$10
#ArgNine=$10
#OutFile=$9
#JER=$11
#PILEUP=$12
#OutFile=$13
echo ArgOne $ArgOne 
echo ArgTwo $ArgTwo 
echo ArgThree $ArgThree 
echo ArgFour $ArgFour
echo ArgFive $ArgFive
echo ArgSix $ArgSix 
echo ArgSeven $ArgSeven
echo ArgEight $ArgEight
echo ArgNine $ArgNine

export ArgOutput="outfile=$ArgSix"
export NameOutput=${ArgSix}_RA2AnalysisTree.root
echo $ArgOutput
echo $NameOutput
#
# first go to the submission dir, and set up the environment
#
cd $ArgNine 
source /cvmfs/cms.cern.ch/cmsset_default.sh
eval `scram runtime -sh`
cmsenv
#
# now go to the condor's scratch area, where we copied the contents of TestRandom
#
cd ${_CONDOR_SCRATCH_DIR} 

mkdir -p TreeFiles

pwd
ls -l
#mkdir -p HadTauMultiple
#mkdir -p HadTau2Multiple

#
# run the job
#
#echo $ArgOne $ArgTwo $ArgThree $ArgFour

#$ArgOne $ArgTwo scenario=$ArgThree tagname=$ArgFour dataset=/store/user/arane/SingleW_StepThree/$ArgFive outfile=$ArgSix doPDFs=$ArgSeven hadtaurecluster=$ArgEight
$ArgOne $ArgTwo $ArgThree $ArgFour $ArgFive $ArgOutput $ArgSeven $ArgEight
#xrdcp fdfkdflkdkj outputfilename eosarea
xrdcp -f $NameOutput root://cmseos.fnal.gov//store/user/arane/SingleW_TreeFiles/
#rm $datasetName'_'$outputFileTag


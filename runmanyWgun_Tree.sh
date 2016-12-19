#!/bin/sh

#submitscript=submitScriptWgun_S1.sh
#submitscript=submitScriptWgun_S1.sh


#type=$1
#outStr=$2
export SUBMIT_DIR=`pwd -P`
echo SUBMIT_DIR ${SUBMIT_DIR}
#mkdir -p qsub

#if [ $type -eq 0 ]; then

  #for index in 1; do 

#    njobs=`ls InputFiles_T/filelist_Spring15_ST_${TStr}_* | wc -l`
    #njobs=$[$njobs+1]
 #   echo number of jobs: $njobs
    #for i in `seq 1 $njobs`; do
for index in Wgun; do


    export SubmitFile=submitScript_${index}_Tree.jdl
    if [ -e ${SubmitFile} ]; then
	rm ${SubmitFile}
    fi

    export Str=$index
    for i in `seq 1 1500`; do
	
	export filenum=$i
	export Suffix=${Str}_$filenum
	export ArgOne=cmsRun
	export ArgTwo=runMakeTreeFromMiniAOD_cfg.py
	export ArgThree="scenario=Spring16"
	export ArgFour="tagname=RECO"
	export ArgFiveA=step3_inMINIAODSIM_${filenum}.root
	export ArgFiveB=StepThree/${ArgFiveA}
	export ArgFive="dataset=/store/user/arane/SingleW_StepThree/step3_inMINIAODSIM_${filenum}.root"
	export ArgSeven="doPDFs=False"
	export ArgEight="hadtaurecluster=3"
	export ArgNine=${SUBMIT_DIR}	      
	export jecA=Spring16_25nsV6_MC.db
	export JEC=data/jec/${jecA}
	export JER=data/jer/${jecA}
	export dataA=QGL_80X.db
	export Data=data/${dataA}
	export pileupA=PileupHistograms_0721_63mb_pm5.root
	export PILEUP=data/${pileupA}
	export Output=qsub/condor_${Suffix}.out
	export Error=qsub/condor_${Suffix}.err
	export Log=qsub/condor_${Suffix}.log
	export Proxy=\$ENV\(X509_USER_PROXY\)
	
	source /cvmfs/cms.cern.ch/cmsset_default.sh
	
	cd $SUBMIT_DIR
	eval `scram runtime -sh`

	
	      #export Output_root_file=step1_${filenum}.root
      #
                # Creating the submit .jdl file
                #
	echo $filenum
	echo submitting ${Str}_${filenum}

	if [ $i -eq 1 ]; then
	    echo executable = submitScriptWgun_Tree.sh>> ${SubmitFile}
	    echo universe =vanilla>> ${SubmitFile}
	    echo x509userproxy = ${Proxy}>> ${SubmitFile}
	    echo notification = never>> ${SubmitFile}
	    echo should_transfer_files = YES>> ${SubmitFile}
	    echo WhenToTransferOutput = ON_EXIT>> ${SubmitFile}
	fi
	
	echo "">> ${SubmitFile}
	echo Arguments =${ArgOne} ${ArgTwo} ${ArgThree} ${ArgFour} ${ArgFive} ${Suffix} ${ArgSeven} ${ArgEight} ${ArgNine}>> ${SubmitFile} 
	#echo Arguments =${ArgOne} ${ArgTwo} ${ArgThree} ${ArgFour} ${ArgFive} ${ArgSix} ${ArgSeven} ${ArgEight} ${OutFile} ${ArgNine} >> ${SubmitFile} 

	echo Output = ${Output}>> ${SubmitFile}
	echo Error = ${Error}>> ${SubmitFile}
	echo Log = ${Log}>> ${SubmitFile}
	echo Transfer_Input_Files = ${SUBMIT_DIR}/runMakeTreeFromMiniAOD_cfg.py,${SUBMIT_DIR}/${PILEUP},${SUBMIT_DIR}/${JEC},${SUBMIT_DIR}/${JER},${SUBMIT_DIR}/${Data}>> ${SubmitFile}
	
	echo Transfer_Output_Files = ${index}_${filenum}_RA2AnalysisTree.root>> ${SubmitFile}
	echo transfer_output_remaps = '"'${index}_${filenum}_RA2AnalysisTree.root = TreeFiles/${index}_${filenum}_RA2AnalysisTree.root'"'>> ${SubmitFile}
	
	echo queue>> ${SubmitFile}	
	
	
    done
    
    #
    # Actual submission
    # 
    condor_submit ${SubmitFile}
    
done







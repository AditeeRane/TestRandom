#!/bin/sh

#submitscript=submitScriptWgun_S3.sh
#submitscript=submitScriptWgun_S3.sh


#type=$1
#outStr=$2
export SUBMIT_DIR=`pwd -P`
echo SUBMIT_DIR ${SUBMIT_DIR}
export INPUT_DIR=${SUBMIT_DIR}/StepTwo
#mkdir -p qsub

#if [ $type -eq 0 ]; then

  #for index in 1; do 

#    njobs=`ls InputFiles_T/filelist_Spring15_ST_${TStr}_* | wc -l`
    #njobs=$[$njobs+1]
 #   echo number of jobs: $njobs
    #for i in `seq 1 $njobs`; do
for index in Wgun; do


    export SubmitFile=submitScript_${index}_S3.jdl
    if [ -e ${SubmitFile} ]; then
	rm ${SubmitFile}
    fi

    export Str=$index
    for i in `seq 1 1500`; do
	
	export filenum=$i
	export Suffix=${Str}_$filenum
	export ArgOne=cmsRun
	export ArgTwo=step3_RAW2DIGI_L1Reco_RECO_EI_PAT.py
	export ArgThree=step2_$filenum.root
	#export ArgThreeB=StepTwo/${ArgThree}
	export ArgFour=step3_$filenum.root
	export ArgFive=step3_inMINIAODSIM_$filenum.root 
	export ArgSeven=$SUBMIT_DIR	      
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
	    echo executable = submitScriptWgun_S3.sh>> ${SubmitFile}
	    echo universe =vanilla>> ${SubmitFile}
	    echo x509userproxy = ${Proxy}>> ${SubmitFile}
	    echo notification = never>> ${SubmitFile}
	    echo should_transfer_files = YES>> ${SubmitFile}
	    echo WhenToTransferOutput = ON_EXIT>> ${SubmitFile}
	fi
	
	echo "">> ${SubmitFile}
	echo Arguments =${ArgOne} ${ArgTwo} ${ArgThree} ${ArgFour} ${ArgFive} ${ArgSeven}>> ${SubmitFile} 
	echo Output = ${Output}>> ${SubmitFile}
	echo Error = ${Error}>> ${SubmitFile}
	echo Log = ${Log}>> ${SubmitFile}
	echo Transfer_Input_Files = ${SUBMIT_DIR}/step3_RAW2DIGI_L1Reco_RECO_EI_PAT.py>> ${SubmitFile}
	echo Transfer_Output_Files = step3_$filenum.root','step3_inMINIAODSIM_$filenum.root>> ${SubmitFile}
		#echo Transfer_Output_Files = MuJetMatchRate_TTbar_${TTbarStr}_${outStr}_${i}_00.root>> ${SubmitFile}        
	echo transfer_output_remaps = '"'step3_$filenum.root = StepThree/step3_$filenum.root';'step3_inMINIAODSIM_$filenum.root = StepThree/step3_inMINIAODSIM_$filenum.root'"'>> ${SubmitFile}
#		echo transfer_output_remaps = '"'MuJetMatchRate_TTbar_${TTbarStr}_${outStr}_${i}_00.root = TauHad2Multiple/MuJetMatchRate_TTbar_${TTbarStr}_${outStr}_${i}_00.root'"'>> ${SubmitFile}
	
	echo queue>> ${SubmitFile}	
	
	
    done
    
    #
    # Actual submission
    # 
    condor_submit ${SubmitFile}
    
done



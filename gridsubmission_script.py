import getopt,os,sys
system=os.system

user = "user.klooper."

#submitversion = ".mc.cf.5"
#submitversion = ".data.cf.9"
submitversion = ".mc.hfor.13"
#submitversion = ".d.test.1"
#submitversion = ".mc.met.1"
#submitversion = ".data.met.1"
#submitversion = ".data.w.2"
#submitversion = ".mc.mv1.1"
#submitversion = ".data.mv1.1"
#submitversion =".mymc.10"
#submitversion = ".aracf.0"
#submitversion = ".mydata.8"
#submitversion = ".datatest.1"
#runscript = "run_nopackages_grid.C"
runscript = "run_grid.C"

# the first argument in the command line is a text file with a list of input dataset
inputFile = sys.argv[1]

f = open(inputFile)
for line in f.readlines():
    input_ds = line.strip()
    # replace features of the input dataset (NTUP_COMMON-specific)
    tmp = input_ds.replace('.merge.NTUP_COMMON','')
    tmp = tmp.replace('.PhysCont.NTUP_COMMON','')
    tmp = tmp.replace('/','')
    tmp = tmp.replace('singletop_','')
    output_ds = user+tmp+submitversion
    output_ds = output_ds.replace('/','')
    rootoutfile = 'output.root'
#    print " * input_ds:", input_ds
 #   print " * output_ds:",output_ds
  #  print " * root file:",rootoutfile
    # note that root file name must be less than about 150 characters

    #match = for single file run
#    cmd = 'prun --exec "echo %IN > input.txt; root -q -b -l '+runscript+'" --rootVer=5.34/10 --cmtConfig=x86_64-slc5-gcc43-opt --inDS='+input_ds+' --outDS='+output_ds+' --outputs='+rootoutfile+' --useRootCore --nGBPerJob=MAX --mergeOutput --maxFileSize=5500000 --match="NTUP_COMMON.05842173._000016.pool.root.1" --extFile=./packages/TileTripReader/data/CompleteTripList_2011-2012.root,./packages/ilumicalc_2012_AllYear_All_Good.root,./packages/BCHCleaningTool/share/FractionsRejectedJetsMC.root,./packages/mc12ab_defaults.prw.root,./packages/egammaAnalysisUtils/share/zvtx_weights_2011_2012.root'

    #cmd = 'prun --exec "echo %IN > input.txt; root -q -b -l '+runscript+'" --rootVer=5.34/10 --cmtConfig=x86_64-slc5-gcc43-opt --inDS='+input_ds+' --outDS='+output_ds+' --outputs='+rootoutfile+' --useRootCore --nGBPerJob=MAX --mergeOutput --maxFileSize=5500000 --match="NTUP_COMMON.01451026._000053.root.1" --extFile=./packages/TileTripReader/data/CompleteTripList_2011-2012.root,./packages/ilumicalc_2012_AllYear_All_Good.root,./packages/BCHCleaningTool/share/FractionsRejectedJetsMC.root,./packages/mc12ab_defaults.prw.root,./packages/egammaAnalysisUtils/share/zvtx_weights_2011_2012.root'

    cmd = 'prun --exec "echo %IN > input.txt; root -q -b -l '+runscript+'" --rootVer=5.34/10 --cmtConfig=x86_64-slc5-gcc43-opt --inDS='+input_ds+' --outDS='+output_ds+' --outputs='+rootoutfile+' --useRootCore --nGBPerJob=MAX --mergeOutput --maxFileSize=5500000  --extFile=./packages/TileTripReader/data/CompleteTripList_2011-2012.root,./packages/ilumicalc_2012_AllYear_All_Good.root,./packages/BCHCleaningTool/share/FractionsRejectedJetsMC.root,./packages/mc12ab_defaults.prw.root,./packages/egammaAnalysisUtils/share/zvtx_weights_2011_2012.root, --useNewCode'


    print cmd

    system(cmd)

from ROOT import TFile, TH1D, TH2D, gROOT, TH1
import os,sys

#Dictionary stores list with ["processname",min,max,binning]

process_dict = {"Z_mass":["Mll",70,110,20],"Z_pt":["Pt",0,1000,20],"Z_y":["Y",-3.5,3.5,20]}

process = sys.argv[1]
print process

isShort = False

TH1.AddDirectory(0)

samples = ["zmumu","zmumubb","zmumucc","ztautau","wjets","ttbar","tchan","schan","Wtchan","WW","WZ","ZZ"]

uf_process = process_dict[process]
uf_samples = ["ZmumuL_Alpgen","ZmumuBB_Alpgen","ZmumuCC_Alpgen","Ztautau","Wmunu","ttbar","singletop_t","singletop_s","singletop_Wt","WW","WZ","ZZ"]
uf_channel = "_Mu_Z"
uf_min = uf_process[1]
uf_max = uf_process[2]
uf_binning = uf_process[3]

uf_hist_list = ["","_truth_dressed","_match","_unmatch","_migration"]


gROOT.ProcessLine(".L analysis_plots.C+")

for hist in uf_hist_list:
    var_2_plot = process + hist
    if isShort:
        cmd = "analysis_plots(\"" + var_2_plot + "\",false,true,false)"
    else:
        cmd = "analysis_plots(\"" + var_2_plot + "\",true,true,false)"
    print cmd
    gROOT.ProcessLine(cmd)


hist_arr = []
for hist in uf_hist_list:
    var_f_name = "unfolding_preprocessed/"+ process + hist
    if isShort:
        var_f_name += "_short.root"
    else:
        var_f_name += ".root"
    f = TFile(var_f_name,"READ")
    var_arr = []
    uf_h_name = "Z_Alpgen"
    if hist == "_truth_dressed":
        uf_h_name += "_dressedMu_dressedZ_truth_"
        uf_h_name += uf_process[0]
    else:
        uf_h_name = uf_h_name + uf_channel + hist + "_" + uf_process[0]
    for sample in samples:
        sample_hist = sample + "_sum"
        h = f.Get(sample_hist)
        if not h:
            print "Could not find histogram " + sample_hist + "in file " + var_f_name
        h.SetName(uf_h_name)
        var_arr.append(h)
    hist_arr.append(var_arr)

for j in range(0,len(samples)):
    uf_fname = "unfolding_inputs/hist-"+uf_samples[j] + ".root"
    uf_f = TFile(uf_fname,"UPDATE")
    for i in range(0,len(uf_hist_list)):
        uf_h = hist_arr[i][j]
        uf_h.Write()
    uf_f.Close()




    
    


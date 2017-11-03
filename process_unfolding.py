from ROOT import TFile, TH1D, TH2D, gROOT, TH1
import os,sys

isShort = False

TH1.AddDirectory(0)
process = "Z_mass"
samples = ["zmumu","zmumubb","zmumucc"]

uf_process = "Mll"
uf_samples = ["ZmumuL_Alpgen","ZmumuBB_Alpgen","ZmumuCC_Alpgen"]
uf_channel = "_Mu_Z"

uf_hist_list = ["","_truth_dressed","_match","_unmatch","_migration"]

gROOT.ProcessLine(".L analysis_plots.C+")

for hist in uf_hist_list:
    var_2_plot = process + hist
    if isShort:
        cmd = "analysis_plots(\"" + var_2_plot + "\",false,true,true)"
    else:
        cmd = "analysis_plots(\"" + var_2_plot + "\",true,true,true)"
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
        uf_h_name += "_dressedMu_dressedZ_truth_Mll"
    else:
        uf_h_name = uf_h_name + uf_channel + hist + "_" + uf_process
    for sample in samples:
        sample_hist = sample + "_sum"
        h = f.Get(sample_hist)
        if not h:
            print "Could not find histogram " + sample_hist + "in file " + var_f_name
        if hist != "_migration":
            hnew = TH1D(uf_h_name,uf_h_name,20,70,110)
            min_bin = h.FindBin(70)
            max_bin = h.FindBin(110)            
            newbin = 0
            for n in range(min_bin,max_bin+1):
                content = h.GetBinContent(n)
                error = h.GetBinError(n)
                hnew.SetBinContent(newbin,content)
                hnew.SetBinError(newbin,error)
                newbin += 1
            var_arr.append(hnew)
        else:
            h.SetName(uf_h_name)
            var_arr.append(h)
    hist_arr.append(var_arr)

for j in range(0,len(samples)):
    uf_fname = "unfolding_inputs/hist-"+uf_samples[j] + ".root"
    uf_f = TFile(uf_fname,"RECREATE")
    for i in range(0,len(uf_hist_list)):
        uf_h = hist_arr[i][j]
        uf_h.Write()
    uf_f.Close()




    
    


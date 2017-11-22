from ROOT import TFile, TH1D, TH2D, gROOT, TH1
import os,sys

#Dictionary stores list with ["distributionname",min,max,binning]

distribution_dict = {"Z_mass":["Mll",70,110,20],"Z_pt":["Pt",0,1000,20],"Z_y":["Y",-3.5,3.5,20]}

distribution = sys.argv[1]

TH1.AddDirectory(0)

sig_samples = ["zmumu","zmumubb","zmumucc"]
bkg_samples = ["ztautau","wmunu","wcc","wc","wbb","ttbar","tchan","schan","Wtchan","WW","WZ","ZZ"]

uf_distribution = distribution_dict[distribution]
uf_sig_samples = ["ZmumuL_Alpgen","ZmumuBB_Alpgen","ZmumuCC_Alpgen"]
uf_bkg_samples = ["Ztautau","WmunuL_Alpgen","WmunuCC_Alpgen","WmunuC_Alpgen","WmunuBB_Alpgen","ttbar","singletop_t","singletop_s","singletop_Wt","WW","WZ","ZZ"]
uf_h_name_sig = "Z_Alpgen"
uf_h_name_bkg = ["Ztautau","W_Alpgen","W_Alpgen","W_Alpgen","W_Alpgen","ttbar","stopt","stops","stopWt","WW","WZ","ZZ"]
uf_channel = "_Mu_Z"
uf_min = uf_distribution[1]
uf_max = uf_distribution[2]
uf_binning = uf_distribution[3]

uf_hist_list = ["","_truth_dressed","_match","_unmatch","_migration"]

gROOT.ProcessLine(".L analysis_plots.C+")

for hist in uf_hist_list:
    var_2_plot = distribution
    if distribution == "Z_mass" and hist != "_truth_dressed":
        var_2_plot += "_MET"
    var_2_plot += hist
    cmd = "analysis_plots(\"" + var_2_plot + "\",true,true,false)"
    print cmd
    gROOT.ProcessLine(cmd)


hist_arr = []
plot_file = distribution
for hist in uf_hist_list:
    if distribution == "Z_mass" and hist != "_truth_dressed":
        plot_file = distribution + "_MET"
    else:
        plot_file = distribution
    var_f_name = "unfolding_preprocessed/"+ plot_file + hist + ".root"
    f = TFile(var_f_name,"READ")
    var_arr = []
    uf_h_name = uf_h_name_sig
    if hist == "_truth_dressed":
        uf_h_name += "_dressedMu_dressedZ_truth_"
        uf_h_name += uf_distribution[0]
    else:
        uf_h_name = uf_h_name + uf_channel + hist + "_" + uf_distribution[0]
    for sample in sig_samples:
        sample_hist = sample + "_sum"
        h = f.Get(sample_hist)
        if not h:
            print "Could not find histogram " + sample_hist + "in file " + var_f_name
        h.SetName(uf_h_name)
        var_arr.append(h)
    hist_arr.append(var_arr)

for j in range(0,len(sig_samples)):
    uf_fname = "unfolding_inputs/hist-"+uf_sig_samples[j] + ".root"
    uf_f = TFile(uf_fname,"UPDATE")
    for i in range(0,len(uf_hist_list)):
        uf_h = hist_arr[i][j]
        uf_h.Write()
    uf_f.Close()

var_2_plot = distribution
if distribution == "Z_mass":
    var_2_plot+="_MET"
bkg_var_f_name = "unfolding_preprocessed/"+ var_2_plot +".root"
f_reco = TFile(bkg_var_f_name,"READ")
for k in range(0,len(bkg_samples)):
    sample_hist = bkg_samples[k] + "_sum"
    h = f_reco.Get(sample_hist)
    if not h:
        print "Could not find histogram " + sample_hist + "in file " + bkg_var_f_name
    uf_h_name = uf_h_name_bkg[k] + "_" +  uf_channel + "_" + uf_distribution[0]
    h.SetName(uf_h_name)
    uf_fname = "unfolding_inputs/hist-"+uf_bkg_samples[k]+".root"
    uf_f = TFile(uf_fname,"UPDATE")
    h.Write()
    uf_f.Close()

h_data = f_reco.Get("data")
uf_h_name_data = "data"+uf_channel+"_"+ uf_distribution[0]
h_data.SetName(uf_h_name_data)
uf_fname_data = "unfolding_inputs/hist-data.root"
uf_f_data = TFile(uf_fname_data,"UPDATE")
h_data.Write()
uf_f_data.Close()

f_reco.Close()



    
    


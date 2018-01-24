from ROOT import TFile, TH1D, TH2D, gROOT, TH1
import os,sys

#Dictionary stores list with ["distributionname",min,max,binning]

distribution_dict = {"Z_mass":"Mll_nomet","Z_mass_MET":"Z_Mll","Z_pt_MET":"Pt","Z_y_MET":"Y","Z_pt":"Pt_nomet","Z_y":"Y_nomet","n_jets_tightmet":"nJetsInBTagAccept_ex", "leadjet_pt_tightmet":"bTagAcceptance_leadJet_Pt"}
truth_name = {"Z_mass":"Z_mass","Z_mass_MET":"Z_mass","Z_pt":"Z_pt", "Z_pt_MET":"Z_pt", "Z_y":"Z_y", "Z_y_MET":"Z_y",
              "n_jets_tightmet":"n_jets","leadjet_pt_tightmet":"leadjet_pt"}

distribution = sys.argv[1]
truth_distribution = truth_name[distribution]

TH1.AddDirectory(0)

sig_samples = ["zjets"]
bkg_samples = ["ztautau","wmunu","wcc","wc","wbb","ttbar","tchan","schan","Wtchan","WW","WZ","ZZ"]

uf_distribution = distribution_dict[distribution]
uf_sig_samples = ["Zmumujet_Alpgen"]
uf_bkg_samples = ["Ztautau","WmunuL_Alpgen","WmunuCC_Alpgen","WmunuC_Alpgen","WmunuBB_Alpgen","ttbar","singletop_t","singletop_s","singletop_Wt","WW","WZ","ZZ"]
uf_h_name_sig = "Z_Alpgen"
uf_h_name_bkg = ["Ztautau","W_Alpgen","W_Alpgen","W_Alpgen","W_Alpgen","ttbar","stopt","stops","stopWt","WW","WZ","ZZ"]

channel = "Mu"
truth_channel = "dressedMu"
reco_region = "iBiJ"
truth_region = "dressed"


uf_hist_list = ["","_truth","_match","_unmatch","_migration"]



gROOT.ProcessLine(".L analysis_plots.C+")

for hist in uf_hist_list:
    var_2_plot = distribution
    if hist == "_truth":
        var_2_plot = truth_distribution
    var_2_plot += hist
    cmd = "analysis_plots(\"" + var_2_plot + "\",true,true,false)"
    print cmd
    gROOT.ProcessLine(cmd)


nbins_list = []
hist_arr = []
plot_file = distribution
for hist in uf_hist_list:
    var_f_name = ""
    if hist == "_truth":
        var_f_name = "unfolding_preprocessed/"+ truth_distribution + hist + ".root"
    else:
        var_f_name = "unfolding_preprocessed/"+ distribution + hist + ".root"
    f = TFile(var_f_name,"READ")
    var_arr = []
    uf_h_name = uf_h_name_sig
    if hist == "_truth":
        uf_h_name = uf_h_name + "_" + truth_channel + "_" + truth_region + hist + "_" + uf_distribution
    else:
        uf_h_name = uf_h_name + "_" + channel + "_" + reco_region + hist + "_"+ uf_distribution
    for sample in sig_samples:
        sample_hist = sample + "_sum"
        h = f.Get(sample_hist)
        if not h:
            print "Could not find histogram " + sample_hist + "in file " + var_f_name
        nbins = h.GetSize()
        nbins_list.append([nbins,sample_hist])
        h.SetName(uf_h_name)
        var_arr.append(h)
    hist_arr.append(var_arr)
    print uf_h_name

for j in range(0,len(sig_samples)):
    uf_fname = "unfolding_inputs/hist-"+uf_sig_samples[j] + ".root"
    uf_f = TFile(uf_fname,"UPDATE")
    for i in range(0,len(uf_hist_list)):
        uf_h = hist_arr[i][j]
        uf_h.Write()
    uf_f.Close()

for element in nbins_list:
    print "Number of bins in " + element[1] + ": " + str(element[0])

bkg_var_f_name = "unfolding_preprocessed/"+ distribution +".root"
f_reco = TFile(bkg_var_f_name,"READ")
for k in range(0,len(bkg_samples)):
    sample_hist = bkg_samples[k] + "_sum"
    h = f_reco.Get(sample_hist)
    if not h:
        print "Could not find histogram " + sample_hist + "in file " + bkg_var_f_name
    uf_h_name = uf_h_name_bkg[k] + "_" +  channel + "_"
    uf_h_name += uf_distribution
    h.SetName(uf_h_name)
    print uf_h_name
    uf_fname = "unfolding_inputs/hist-"+uf_bkg_samples[k]+".root"
    uf_f = TFile(uf_fname,"UPDATE")
    h.Write()
    uf_f.Close()

h_data = f_reco.Get("data")
uf_h_name_data = "data"+channel+"_"+ uf_distribution
h_data.SetName(uf_h_name_data)
uf_fname_data = "unfolding_inputs/hist-data.root"
uf_f_data = TFile(uf_fname_data,"UPDATE")
h_data.Write()
uf_f_data.Close()

f_reco.Close()



    
    


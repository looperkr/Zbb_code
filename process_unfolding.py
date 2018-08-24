from ROOT import TFile, TH1D, TH2D, gROOT, TH1
import os,sys
import csv

def divideByBFraction(histo):
    f = TFile("flavor_fractions/ffrac.root","READ")
    h_bfrac = f.Get("bfrac_Z_pt")
    histo.Multiply(h_bfrac)
    f.Close()

isBresult = False
#Dictionary stores list with ["distributionname",min,max,binning]
#testing
fill_empty = True #Creates empty background histograms for testing

distribution_dict = {"Z_mass":"Mll_nomet","Z_mass_MET":"Z_Mll","Z_pt_MET":"Z_Pt","Z_y_MET":"Z_Y","Z_pt":"Z_Pt","Z_y":"Z_Y","n_jets_tightmet":"nJetsEx","Z_pt_1j":"Z_Pt_1j","Z_pt_1b":"Z_Pt_1b"} #map my_names -> unfolding_names
truth_name = {"Z_mass":"Z_mass","Z_mass_MET":"Z_mass","Z_pt":"Z_pt", "Z_pt_MET":"Z_pt", "Z_y":"Z_y", "Z_y_MET":"Z_y",
              "n_jets_tightmet":"n_jets","leadjet_pt_tightmet":"leadjet_pt","Z_pt_1j":"Z_pt_1j","Z_pt_1b":"Z_pt_1b"} #map reco distribution -> truth distribution

distribution = sys.argv[1]
truth_distribution = truth_name[distribution]

if distribution == "Z_pt_1b":
    isBresult = True

TH1.AddDirectory(0)

sig_samples = ["zjets"]
bkg_samples = ["ztautau","wjets","ttbar","tchan","schan","Wtchan","WW","WZ","ZZ"]

uf_distribution = distribution_dict[distribution]
uf_sig_samples = ["Zmumujet_Alpgen"]
uf_bkg_samples = ["Ztautaujet_Alpgen","Wmunujet_Alpgen","ttbar","singletop_t","singletop_s","singletop_Wt","diboson","diboson","diboson"] #file name
uf_h_name_sig = "Z_Alpgen"
uf_h_name_bkg = ["Z_Alpgen","W_Alpgen","ttbar","stopt","stops","stopWt","WW","WZ","ZZ"] #histogram name (Ztautau is also Z_Alpgen)

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
    if isBresult and hist == "":
        var_2_plot = "Z_pt_1b_reco"
    var_2_plot += hist
    cmd = "analysis_plots(\"" + var_2_plot + "\",true,true,false)"
    print cmd
    gROOT.ProcessLine(cmd)

if isBresult:
    cmd = "analysis_plots(\"Z_pt_1j\")"
    gROOT.ProcessLine(cmd)


nbins_list = []
hist_arr = []
plot_file = distribution
for hist in uf_hist_list:
    var_f_name = ""
    if hist == "_truth":
        var_f_name = "unfolding_preprocessed/"+ truth_distribution + hist + ".root"
    elif hist == "" and isBresult:
        var_f_name = "unfolding_preprocessed/" + distribution + "_reco" + ".root"
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
        int_sig_sample = h.Integral()
        print "Hist " + hist + " integral: " + str(int_sig_sample)
        if isBresult:
            h.SetBinContent(1,0)
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

if isBresult:
    distribution = "Z_pt_1j"
bkg_var_f_name = "unfolding_preprocessed/"+ distribution +".root"
f_reco = TFile(bkg_var_f_name,"READ")
for k in range(0,len(bkg_samples)):
    sample_hist = bkg_samples[k] + "_sum"
    h = f_reco.Get(sample_hist)
    if not h:
        print "Could not find histogram " + sample_hist + "in file " + bkg_var_f_name
    uf_h_name = uf_h_name_bkg[k] + "_" + channel + "_" + reco_region + "_" + uf_distribution
    if isBresult:
        h.SetBinContent(1,0)
    h.SetName(uf_h_name)
    print uf_h_name
    uf_fname = "unfolding_inputs/hist-"+uf_bkg_samples[k]+".root"
    print uf_fname
    uf_f = TFile(uf_fname,"UPDATE")
    if fill_empty:
        h_empty = h.Clone(uf_h_name)
        h_empty.Reset("M")
        h_empty.Write()
    else:
        h.Write()
    uf_f.Close()

h_data = f_reco.Get("data")
uf_h_name_data = "data_"+channel+"_"+ reco_region + "_" + uf_distribution
print uf_h_name_data
h_data.SetName(uf_h_name_data)
uf_fname_data = "unfolding_inputs/hist-data.root"
uf_f_data = TFile(uf_fname_data,"UPDATE")
if isBresult:
    h_data.SetBinContent(1,0)
#    divideByBFraction(h_data)
uf_f_data.cd()
h_data.Write()
uf_f_data.Close()

f_reco.Close()



    
    


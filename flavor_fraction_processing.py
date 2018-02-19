from ROOT import TFile, TH1D, TH2D, gROOT, TH1, TAxis
import os,sys

# Code takes flavor fractions from template fits and scales distributions by them
# Inputs --  variable vs b-fraction (TH2), reco distribution, data distribution
# Outputs -- scaled reco and data with name BTag_(var)
TH1.AddDirectory(0)

samples = ["zjets_sum","ztautau_sum","wjets_sum","ttbar_sum","tchan_sum","schan_sum","Wtchan_sum","WW_sum","WZ_sum","ZZ_sum","data"]

kin_var = "Z_pt"

f_bfrac_name = "flavor_fractions/ffrac.root"
h_bfrac_name = "bfrac_" + kin_var

data_var = ""

if kin_var == "Z_pt":
    data_var = "Z_pt_1j"
else:
    data_var = kin_var

f_toscale_name = "unfolding_preprocessed/" + data_var + ".root"
f_toscale = TFile(f_toscale_name,"READ")

f_scaled_name = "unfolding_preprocessed/BTag_" + data_var + ".root"
f_scaled = TFile(f_scaled_name,"RECREATE")

f_bfrac = TFile(f_bfrac_name,"READ")
h_bfrac = f_bfrac.Get(h_bfrac_name)

#Get number of bins in kinematic distribution
n_bfrac_bins = h_bfrac.GetNbinsY()

for sample in samples:
    h_toscale = f_toscale.Get(sample)
    h_scaled = h_toscale.Clone()
    for bin_i in range(1,n_bfrac_bins+1):
        bfrac = h_bfrac.GetBinContent(1,bin_i)
        oldbin = h_toscale.GetBinContent(bin_i)
        newbin = bfrac*oldbin
        h_scaled.SetBinContent(bin_i,newbin)
    f_scaled.cd()
    h_scaled.Write()





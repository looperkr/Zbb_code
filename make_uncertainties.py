from ROOT import TFile, TH1D, TH2D, gROOT, TH1
import os,sys

def scale_hists(hist,file_n,syst):
    file_n = "unfolding_inputs/"+file_n
    f = TFile(file_n,"UPDATE")
    h = f.Get(hist)
    h_up = h.Clone()
    h_down = h.Clone()
    h_n_up = "Systematics_"+hist+"_"+syst+"__1up"
    h_n_down = "Systematics_"+hist+"_"+syst+"__1down"
    print h_n_up
    print h_n_down
    h_up.SetName(h_n_up)
    h_down.SetName(h_n_down)

#    h_up.Scale(1.019)
#    h_down.Scale(0.981)
#    h_up.Scale(1.1)
#    h_down.Scale(.9)
#    h_up.Scale(1.2)
#    h_down.Scale(.8)
    nbins = h.GetNbinsX()+1
    n_var = 0.01
    for i in range(1,nbins):
        print n_var
        bincontent = h.GetBinContent(i)
        print bincontent
        bin_up = bincontent*(1+n_var)
        bin_down = bincontent*(1-n_var)
        print bin_up
        h_up.SetBinContent(i,bin_up)
        h_down.SetBinContent(i,bin_down)
        n_var+=.01
    h_up.Write()
    h_down.Write()
    f.Close()

process = "Z_Pt_1j"

bkg_dict = {"W_Alpgen":"hist-Wmunujet_Alpgen.root", "ttbar":"hist-ttbar.root", "stopt":"hist-singletop_t.root", "stops":"hist-singletop_s.root", "stopWt":"hist-singletop_Wt.root", "WW":"hist-diboson.root", "WZ": "hist-diboson.root", "ZZ":"hist-diboson.root"}

l_file_sig = "hist-Zmumujet_Alpgen.root"

l_hists = ["truth_","match_","unmatch_","migration_",""]

#syst = "SysJET_21NP_JET_EffectiveNP_1"
#syst = "SysJET_21NP_JET_EffectiveNP_2"
#syst = "SysJET_JER_SINGLE_NP"
syst = "SysJET_21NP_JET_EffectiveNP_3"

for k in bkg_dict:
    f_n = bkg_dict[k]
    h_n = k+"_Mu_iBiJ_" + process
    scale_hists(h_n,f_n,syst)

for h in l_hists:
    if h == "truth_":
        h_n = "Z_Alpgen_dressedMu_dressed_truth_" + process
    else:
        h_n = "Z_Alpgen_Mu_iBiJ_" + h + process
    scale_hists(h_n,l_file_sig,syst)

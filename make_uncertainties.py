from ROOT import TFile, TH1D, TH2D, gROOT, TH1
import os,sys
import csv
import math

'''  uncert_el.insert(pair<int,int>(0,0));
  uncert_el.insert(pair<int,int>(1,0));
  uncert_el.insert(pair<int,int>(2,0));
  uncert_el.insert(pair<int,int>(3,0));
  uncert_el.insert(pair<int,int>(4,0));
  uncert_el.insert(pair<int,int>(5,1));
  uncert_el.insert(pair<int,int>(6,1));
  uncert_el.insert(pair<int,int>(7,2));
  uncert_el.insert(pair<int,int>(8,2));
  uncert_el.insert(pair<int,int>(9,3));
  uncert_el.insert(pair<int,int>(10,3));
  uncert_el.insert(pair<int,int>(11,4));
  uncert_el.insert(pair<int,int>(12,4));
  uncert_el.insert(pair<int,int>(13,5));
  uncert_el.insert(pair<int,int>(14,5));
  uncert_el.insert(pair<int,int>(15,6));
  uncert_el.insert(pair<int,int>(16,6));
  uncert_el.insert(pair<int,int>(17,7));
  uncert_el.insert(pair<int,int>(18,8));
  uncert_el.insert(pair<int,int>(19,9));
  uncert_el.insert(pair<int,int>(20,10));
  uncert_el.insert(pair<int,int>(21,11));
  '''
def scale_hists(hist,file_n,syst,syst_vals_up,syst_vals_down=None):
    file_n = "unfolding_inputs/"+file_n
    f = TFile(file_n,"UPDATE")
    syst_dict = {0:0,1:0,2:0,3:0,4:0,5:1,6:1,7:2,8:2,9:3,10:3,11:4,12:4,13:5,14:5,15:6,16:6,17:7,18:8,19:9,20:10,21:11}
    print file_n
    print hist
    h = f.Get(hist)
    h_up = h.Clone()
    h_down = h.Clone()
    h_n_up = "Systematics_"+hist+"_"+syst+"__1up"
    h_n_down = "Systematics_"+hist+"_"+syst+"__1down"
    h_up.SetName(h_n_up)
    h_down.SetName(h_n_down)
    nbins = h.GetNbinsX()+1
    for i in range(0,nbins):
        uncert_bin = syst_dict[1]
        bincontent = h.GetBinContent(i)        
        if syst_vals_down is None:
            bin_up = bincontent*(1+syst_vals_up)
            bin_down = bincontent*(1-syst_vals_up)
        else:
            bin_up = bincontent*(1+syst_vals_up[uncert_bin])
            bin_down = bincontent*(1-syst_vals_down[uncert_bin])
        h_up.SetBinContent(i,bin_up)
        h_down.SetBinContent(i,bin_down)
    print h_n_up
    h_up.Write()
    h_down.Write()
    f.Close()

def isfloat(value):
  try:
    float(value)
    return True
  except ValueError:
    return False

def read_uncert(file_n):
    csv_data = []
    with open(file_n) as csv_f:
        csv_reader = csv.reader(csv_f, delimiter=',')
        for row in csv_reader:
            hold_row = []
            for el in row:
                if isfloat(el):
                    hold_row.append(float(el));
                else:
                    hold_row.append(el);
            csv_data.append(hold_row)
    return csv_data

def add_column_in_quad(n,csv_data):
    sumsqr_up = 0
    sumsqr_down = 0
    sum_up = [r[n]**2 for r in csv_data if r[0][-2:]=="up"]    
    sum_down = [t[n]**2 for t in csv_data if t[0][-4:]=="down"]
    for val in sum_up:
        sumsqr_up+=val
    for val in sum_down:
        sumsqr_down+=val
    return (sumsqr_up,sumsqr_down)


process = "Z_Pt_1b"

bkg_dict = {"W_Alpgen":"hist-Wmunujet_Alpgen.root", "ttbar":"hist-ttbar.root", "stopt":"hist-singletop_t.root", "stops":"hist-singletop_s.root", "stopWt":"hist-singletop_Wt.root", "WW":"hist-diboson.root", "WZ": "hist-diboson.root", "ZZ":"hist-diboson.root"}

l_file_sig = "hist-Zmumujet_Alpgen.root"

l_hists = ["truth_","match_","unmatch_","migration_",""]

#syst_jes = "SysJET_21NP_JET_EffectiveNP_1"
#syst_bsf = "SysFT_EFF_Eigen_B_0_AntiKt4EMTopoJets"
#syst_jer = "SysJET_JER_SINGLE_NP"
#syst_jvf = "SysMET_SoftTrk_Scale"
#syst_lumi = "SysModelling"

syst_names = ["SysJET_21NP_JET_EffectiveNP_1","SysFT_EFF_Eigen_B_0_AntiKt4EMTopoJets","SysJET_JER_SINGLE_NP","SysMET_SoftTrk_Scale","SysModelling"]
syst_vals = []

'''  double jes_val = 4.8;
  double jer_val = 2.4;
  double jvf_val = 1.0;
  double lumi_val = 1.9;'''
b_tag_csv = read_uncert("uncertainty_block_b.csv")

jes_val = 4.8/100.
syst_vals.append(jes_val)

uncert_vals_b_up = []
uncert_vals_b_down = []
for i in range(1,13):
    unc_bin_pair = add_column_in_quad(i,b_tag_csv)
    uncert_vals_b_up.append(math.sqrt(unc_bin_pair[0]/100.))
    uncert_vals_b_down.append(math.sqrt(unc_bin_pair[1]/100.))

syst_vals.append((uncert_vals_b_up,uncert_vals_b_down))

jvf_val = 1.0/100.
syst_vals.append(jvf_val)
jer_val = 2.4/100.
syst_vals.append(jer_val)
lumi_val = 1.9/100.
syst_vals.append(lumi_val)



for s in range(0,len(syst_names)):
    syst = syst_names[s]
    for k in bkg_dict:
        f_n = bkg_dict[k]
        h_n = k+"_Mu_iBiJ_" + process
        if s==1:
            scale_hists(h_n,f_n,syst,syst_vals[1][0],syst_vals[1][1])            
        else:
            scale_hists(h_n,f_n,syst,syst_vals[s])

    for h in l_hists:
        if h == "truth_":
            h_n = "Z_Alpgen_dressedMu_dressed_truth_" + process
        else:
            h_n = "Z_Alpgen_Mu_iBiJ_" + h + process
        if s==1:
            scale_hists(h_n,l_file_sig,syst,syst_vals[1][0],syst_vals[1][1])
        else:
            scale_hists(h_n,l_file_sig,syst,syst_vals[s])

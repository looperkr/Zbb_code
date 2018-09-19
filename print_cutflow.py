from ROOT import TH1,TFile
import string

isTruth = True
isSherpa = True

cf_name = "cutflow"
if isTruth:
    cf_name = "truth_" + cf_name

cf_path = "MC_histograms_root/" + cf_name + ".root"

cf_f = TFile(cf_path)

if isSherpa:
    cf_name += "_sherpa"
else:
    cf_name += "_mc"

h_cf = cf_f.Get(cf_name)

cf_text_name = "cutflow.txt"
if isTruth:
    cf_text_name = "truth_" + cf_text_name

with open(cf_text_name) as f_t:
    cf_lines = f_t.read().splitlines()

f_out_n = cf_name+".csv"
with open(f_out_n,"w") as f_out:
    for i in range(0,len(cf_lines)):
        f_out.write(cf_lines[i] + ";" + str(h_cf.GetBinContent(i+1)) + "\n")

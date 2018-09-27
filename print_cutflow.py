from ROOT import TH1,TFile
import string

isTruth = True
isSherpa = False
isJustZ = False

cf_name = "cutflow"
if isTruth:
    cf_name = "truth_" + cf_name

cf_path = "MC_histograms_root/" + cf_name + ".root"
if isJustZ:
    cf_path = "unfolding_preprocessed/" + cf_name + ".root"

cf_f = TFile(cf_path)

if not isJustZ:
    if isSherpa:
        cf_name += "_sherpa"
    else:
        cf_name += "_mc"
else:
    if isSherpa:
        cf_name = "zjets_sherpa_sum"
    else:
        cf_name = "zjets_sum"

h_cf = cf_f.Get(cf_name)

cf_text_name = "cutflow.txt"
if isTruth:
    cf_text_name = "truth_" + cf_text_name

with open(cf_text_name) as f_t:
    cf_lines = f_t.read().splitlines()

if isJustZ and isTruth:
    cf_name = "truth_cutflow_" + cf_name;
elif isJustZ:
    cf_name = "cutflow_" + cf_name;

f_out_n = cf_name+".csv"
with open(f_out_n,"w") as f_out:
    for i in range(0,len(cf_lines)):
        print '{:.2e}'.format(float(h_cf.GetBinContent(i+1)))
        print str(h_cf.GetBinContent(i+1))
        f_out.write(cf_lines[i] + ";" + str(h_cf.GetBinContent(i+1)) + "\n")

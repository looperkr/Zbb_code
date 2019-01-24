from ROOT import TH1D,TFile
import math
import matplotlib.pyplot as plt

path = "./MC_histograms_root/"
f_s_n = path+"met_leadingb"
f_b_n = path+"met_notleadingb"
hist_s_n = "met_leadingb_mc"
hist_b_n = "met_notleadingb_mc"

f_s = TFile(f_s_n)
f_b = TFile(f_b_n)
h_s = f_s.Get(hist_s_n)
h_b = f_b.Get(hist_b_n)

bins = h_s.GetNBinsX()
soverb_lst = []
met_lst = []

for bin in range(1,bins+1):
    s = h_s.GetBinContent(bin)
    b = h_b.GetBinContent(bin)
    val = s/math.sqrt(b)
    soverb_lst.append(val)
    met = h_s.GetXaxis().GetBinCenter(bin)
    met_lst.append(met)

plt.figure(1)
plt.scatter(met_lst,soverb_lst,marker='.')
plt.xlabel("MET [GeV]")
plt.ylabel("S/sqrt(B)")
plt.show()

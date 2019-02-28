from ROOT import TFile, TH1D, TH2D, gROOT, TH1

f = TFile("MC_histograms_root/recoleadb_truebrank.root")

h = f.Get("recoleadb_truebrank_mc")

n_bins = h.GetSize()
bin_contents = []

for i in range(1,n_bins+1):
    bin_contents.append(h.GetBinContent(i))
    print "Bin " + str(i) + ": " + str(bin_contents[i-1])
    print h.GetBinLowEdge(i)

print bin_contents[0]/sum(bin_contents)

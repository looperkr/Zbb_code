from ROOT import TFile, TH1D, TH2D, gROOT, TH1

f1 = TFile("MC_histograms_root/Z_mass_MET_match.root")
f2 = TFile("MC_histograms_root/Z_mass_MET_unmatch.root")

h1 = f1.Get("Z_mass_MET_match_mc")
h2 = f2.Get("Z_mass_MET_unmatch_mc")

h1_integral = h1.Integral()
h2_integral = h2.Integral()

print h1_integral
print h2_integral

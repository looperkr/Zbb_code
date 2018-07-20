from ROOT import TFile, TH1D, TH2D, gROOT, TH1

f1 = TFile("MC_histograms_root/recoleadb_trueZ_ZpT.root")
f2 = TFile("MC_histograms_root/recoleadb_notrueZ_ZpT.root")
f3 = TFile("MC_histograms_root/recoleadb_trueZ_truej_ZpT.root")
f4 = TFile("MC_histograms_root/recoleadb_trueZ_notruej_ZpT.root")
f5 = TFile("MC_histograms_root/Z_pt_1b_match.root")

h1 = f1.Get("recoleadb_trueZ_ZpT_mc")
h2 = f2.Get("recoleadb_notrueZ_ZpT_mc")
h3 = f3.Get("recoleadb_trueZ_truej_ZpT_mc")
h4 = f4.Get("recoleadb_trueZ_notruej_ZpT_mc")
h5 = f5.Get("Z_pt_1b_match_mc")

h1_integral = h1.Integral()
h2_integral = h2.Integral()
h3_integral = h3.Integral()
h4_integral = h4.Integral()
h5_integral = h5.Integral()

total = h1_integral + h2_integral
frac_fake_Z = h2_integral/total
frac_fake_j = h4_integral/h1_integral
frac_fake_b = 1-(h5_integral/h3_integral)

print "True Z: " + str(h1_integral)
print "no True Z: " + str(h2_integral)
print "True Z, true j: " + str(h3_integral)
print "True Z, no true j: " + str(h4_integral)

print "total events: " + str(total)
print "fraction of events that fail truth Z: " + str(frac_fake_Z)
print "fraction of events that pass truth Z, fail jet: " + str(frac_fake_j)
print "fraction of events that pass truth Z, truth j, fail leading truth b: " +str(frac_fake_b)

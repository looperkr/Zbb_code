from ROOT import TH1D,TFile
import subprocess
import math
import matplotlib.pyplot as plt

xsec_dict = {}
with open('scaling_info.txt', 'r') as xsec_file:
    for line in xsec_file:
        xsec_lst = line.split(',')
        filename = xsec_lst[0].strip()
        xsec_dict[filename] = xsec_lst[1:len(xsec_lst)]

def normalize(hist_file_name,xsec_map,luminosity):
    param_lst = xsec_map[hist_file_name]
    xsec = float(param_lst[0])
    kfactor = float(param_lst[1])
    efficiency = float(param_lst[2])
    nevents = float(param_lst[3])
    xsec_value = xsec*kfactor*efficiency
    norm_factor = luminosity/(nevents/xsec_value);
    return norm_factor

path = "./MC_histograms/"
cmd = "ls " + path
files = subprocess.check_output(cmd,shell=True)
files = files.strip()
file_lst = files.split("\n")

hist_n = range(2,16)
met_lst = []
for n in hist_n:
    met_lst.append(n*10)

sig_lst = []
bkg_lst = []

lumi = 3413.06 #last lumi calculation, redo

for number in met_lst:
    sig_integral = 0
    bkg_integral = 0
    hist_name = "met"+str(number)+"_bjetn"
    for file_name in file_lst:
        f = TFile(path+file_name)
        h = f.Get(hist_name)
        scaling_factor = normalize(file_name,xsec_dict,lumi)
        integral = h.GetBinContent(h.FindBin(2))
        print "Debugging, prescaling integral = " + str(integral) 
        h.Scale(scaling_factor)
        integral = h.GetBinContent(h.FindBin(2))
        print "Debugging, postscaling integral = " + str(integral)
        #integral = h.Integral()
        print integral
        if file_name[0:9] == "ZmumubbNp":
            sig_integral += integral
        else:
            bkg_integral += integral
    sig_lst.append(sig_integral)
    bkg_lst.append(bkg_integral)

soverb_lst = []
for i in range(0,len(sig_lst)):
    soverb = sig_lst[i]/math.sqrt(bkg_lst[i])
    soverb_lst.append(soverb)

plt.figure(1)
plt.plot(met_lst,soverb_lst)
plt.show()



from ROOT import TH1D,TFile
import subprocess
import math
from mpl_toolkits.mplot3d import Axes3D
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

met_lst = [40,50,60,70,80]
mv1_lst = [85,80,70,60]
mv1c_lst = [80,70,60,57,50]

sig_lst = []
bkg_lst = []
met_plt_lst = []
mv1_plt_lst = []

lumi = 3413.06 #last lumi calculation, redo

for number in met_lst:
    for weight in mv1_lst:
        sig_integral = 0
        bkg_integral = 0
        hist_name = "mv1_"+str(weight)+"_met"+str(number)+"_bjetn"
        for file_name in file_lst:
            f = TFile(path+file_name)
            h = f.Get(hist_name)
            scaling_factor = normalize(file_name,xsec_dict,lumi)
            h.Scale(scaling_factor)
            integral = h.GetBinContent(h.FindBin(2))
            if file_name[0:9] == "ZmumubbNp":
                sig_integral += integral
            else:
                bkg_integral += integral
        sig_lst.append(sig_integral)
        bkg_lst.append(bkg_integral)
        met_plt_lst.append(number)
        mv1_plt_lst.append(weight)


soverb_lst = []
for i in range(0,len(sig_lst)):
    soverb = sig_lst[i]/math.sqrt(bkg_lst[i])
    soverb_lst.append(soverb)

mv1_80_met_list = []
soverb_new_list = []
for ind in range(0,len(soverb_lst)):
    if mv1_plt_lst[ind] == 80:
        print met_plt_lst[ind]
        mv1_80_met_list.append(met_plt_lst[ind])
        soverb_new_list.append(soverb_lst[ind])

print soverb_new_list
plt.figure(1)
plt.scatter(mv1_80_met_list,soverb_new_list,marker='o')
plt.xlabel("MET selection [GeV]")
plt.ylabel("S/sqrt(B)")
plt.grid()
plt.show()
'''
fig = plt.figure()
ax = fig.add_subplot(111,projection='3d')
ax.scatter(met_plt_lst,mv1_plt_lst,soverb_lst,marker='o')
ax.set_xlabel('MET cut [GeV]')
ax.set_ylabel('mv1c working point [%]')
ax.set_zlabel('S over sqrt(B)')

plt.show()
'''
#plt.figure(1)
#plt.scatter(met_plt_lst,mv1_plt_lst,soverb_lst,marker='o')
#plt.show()



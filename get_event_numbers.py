import subprocess
from ROOT import TFile

output_f_name = 'scaling_info.txt'

files = subprocess.check_output("ls ./MC_histograms_grid",shell=True)
files = files.strip()
file_lst = files.split("\n")

#dict. list order: x-sec,k-factor, eff
xsec_dict = {'ZmumuNp0_hists.root':[719.16,1.18,1.0],'ZmumuNp1_hists.root':[175.74,1.18,1.0],'ZmumuNp2_hists.root':[58.882,1.18,1.0],'ZmumuNp3_hists.root':[15.673,1.18,1.0],'ZmumuNp4_hists.root':[4.0057,1.18,1.0],'ZmumuNp5_hists.root':[1.2544,1.18,1.0],'ZmumubbNp0_hists.root':[6.5056,1.18,1.0],'ZmumubbNp1_hists.root':[3.2909,1.18,1.0],'ZmumubbNp2_hists.root':[1.2585,1.18,1.0],'ZmumubbNp3_hists.root':[0.61808,1.18,1.0],'ZmumuccNp0_hists.root':[11.795,1.18,1.0],'ZmumuccNp1_hists.root':[4.1254,1.18,1.0],'ZmumuccNp2_hists.root':[3.3694,1.18,1.0],'ZmumuccNp3_hists.root':[1.7003,1.18,1.0],'ZtautauNp0_hists.root':[711.89,1.2290,1.0],'ZtautauNp1_hists.root':[155.09,1.2290,1.0],'ZtautauNp2_hists.root':[48.805,1.2290,1.0],'ZtautauNp3_hists.root':[14.140,1.2290,1.0],'ZtautauNp4_hists.root':[3.7711,1.2290,1.0],'ZtautauNp5_hists.root':[1.1122,1.2290,1.0],'ttbar_hists.root':[114.49,1.1994,1.0],'singletop_tchan_mu_hists.root':[8.5889,1.1035,1.0],'singletop_WtChanIncl_hists.root':[20.666,1.0736,1.0],'singletop_SChan_Wmunu_hists.root':[0.56430,1.0737,1.0],'WW_hists.root':[32.501,1.6833,0.38203],'ZZ_hists.root':[4.9614,1.5496,0.24465],'WZ_hists.root':[12.008,1.9011,0.30546]}

f_out = open(output_f_name,'w')
for file_name in file_lst:
    f = TFile("./MC_histograms_grid/"+file_name)
    h = f.Get("ICUTZ")
    event_n = h.GetBinContent(3);
    xsec = xsec_dict[file_name][0]
    kfact = xsec_dict[file_name][1]
    eff = xsec_dict[file_name][2]
    line_to_write = file_name + ',' + str(xsec) + ',' + str(kfact) + ',' + str(eff) + ',' + str(event_n) + '\n'
    f_out.write(line_to_write)
f_out.close()

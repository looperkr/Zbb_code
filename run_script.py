import ROOT
import PyCintex
import os,sys
from ROOT import TChain,TFile,TDirectory,TChain,TTree,gInterpreter,gROOT

isMC = False

file_list = str(sys.argv[1])

chain = TChain("physics")

with open(file_list) as f:
    for line in f:
        newline=line.strip()
        chain.Add(newline)

if isMC:
    output_el = file_list.split("_")
    output_el_el= output_el[-2].strip()
    output_type_name = output_el_el.split("/")
    output_type = output_type_name[-1].strip()
    if output_type == "mu":
        output_type = "singletop_tchan_mu"
    elif output_type == "SChanWmunu":
        output_type = "singletop_SChan_Wmunu"
    elif output_type == "WtChanIncl":
        output_type = "singletop_WtChanIncl"
    output_name = "./MC_histograms/" + output_type + "_hists.root"
    print output_name
else:
    output_el = file_list.split("_")
    output_el_el= output_el[-2].strip()
    output_type_name = output_el_el.split("/")
    output_type = output_type_name[-1].strip()
    output_name = "./data_histograms/" + output_type + "_hists.root"
    print output_name

gInterpreter.GenerateDictionary("vector<vector<int> >","vector")
gROOT.ProcessLine(".x $ROOTCOREDIR/scripts/load_packages.C");
chain.Process("analysis_Zmumu.C+",output_name) #look at GetOption in analysis_Zmumu::SlaveBegin()

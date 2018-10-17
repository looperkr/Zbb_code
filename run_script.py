import ROOT
import PyCintex
import os,sys
from ROOT import TChain,TFile,TDirectory,TChain,TTree,gInterpreter,gROOT

isMC = False
isMJ = False
isWide = True

#processes until 5k events have passed Z+1jet selection
isShort = False

file_list = str(sys.argv[1])

chain = TChain("physics")

firstline = ""
lineit = 0;
with open(file_list) as f:
    for line in f:
        newline=line.strip()
        chain.Add(newline)
        if lineit == 0:
            firstline = newline
            lineit = 1;
#get generator
mapIndex = 0
if isMC:
    dataset_name = firstline.split("/")[6]
    generator_el = dataset_name.split("_")[2]
    generator = generator_el.split(".")[1]
    if "Pythia" in generator:
        mapIndex = 0
    elif "Jimmy" in generator:
        mapIndex = 1
    elif "Sherpa" in generator:
        mapIndex = 2
    elif "Herwig" in generator:
        mapIndex = 1
    else: 
        print "DEBUG!"
        exit

print mapIndex

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
    output_name = "./MC_histograms/" + output_type + "_hists"
    if isMJ:
        output_name = "./MC_histograms_MJ/" + output_type + "_hists"
    elif isWide:
        output_name = "./MC_histograms_wide/" + output_type + "_hists"
    print output_name
else:
    output_el = file_list.split("_")
    output_el_el= output_el[-2].strip()
    output_type_name = output_el_el.split("/")
    output_type = output_type_name[-1].strip()
    output_name = "./data_histograms/" + output_type + "_hists"
    if isMJ:
        output_name = "./data_histograms_MJ/" + output_type + "_hists"
    elif isWide:
        output_name = "./data_histograms_wide/" + output_type + "_hists"
    print output_name
if isShort:
    output_name += "_short"
if isMJ:
    output_name += "_MJ.root"
elif isWide:
    output_name += "_wide.root"
else:
    output_name += ".root"

if isMC:
    optionslist = output_name + ',' + str(mapIndex)
    print optionslist
else:
    optionslist = output_name
    print optionslist
gInterpreter.GenerateDictionary("vector<vector<int> >","vector")
gROOT.ProcessLine(".x $ROOTCOREDIR/scripts/load_packages.C");
chain.Process("analysis_Zmumu.C+",optionslist) #look at GetOption in analysis_Zmumu::SlaveBegin()


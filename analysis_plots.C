///////////////macro for plotting Z+bb results //////////////
/*
Created by: K. Looper (2 Oct 2015)
*/



#include <iostream>
#include <string>
#include "TString.h"
#include "TFile.h"
#include "analysis_plots.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TMath.h"
#include "TPad.h"
#include "TLatex.h"
#include "THStack.h"


void analysis_plots(string var_2_plot,bool scale_to_lumi=true, bool make_log=true, bool include_sherpa=false, bool isMJ=false, bool isWide=false){

  bool isShort = false;
  bool isTruth = false;
  int j = 0; //debugging iterator
  //plot luminosity
  double lumi;
  if(scale_to_lumi){
    //luminosity in picobarns
    lumi = 20239.2; //lumi calculator
    //lumi = 20281.48; //arantxa
    //    lumi = 785.355; //period A
    //lumi = 794.02; // period A arantxa
    //lumi = 5047.21; //period B
    //    lumi = 1397.5; //period C
    //    lumi = 3275.01; //period D
    //lumi = 2525.51; //period E
    //    lumi = 1278.5; //period G
    //lumi = 1452.42; // period H
    //    lumi = 1021.54; //period I
    //    lumi = 2609.89; //period J
    //  lumi = 846.306; //period L
  }
  else{
    lumi = 5000.0;
  }
  TString histo_name; //histogram name
  TString x_name;     //x-axis label
  TString y_name;     //y-axis label
  double x_min, x_max, y_min, y_max; //axis min and max values
  int rebin;
  double ratiomin = 0.45; //default values, some are changed
  double ratiomax = 1.85;
  float logmax = 100000; //use variable when wanting non-log plot option

  //Plot options for chosen variable
  if(var_2_plot == "mu_pt"){
    chooseHistOptions("mu_pt_nocut", "p_{T}^{#mu} [GeV]", "Events/0.5 GeV", 0, 200, 1,  1000000000, 1, ratiomin, ratiomax);
  }
  else if(var_2_plot == "mu_pt_Z"){
    chooseHistOptions("mu_pT","p_{T}^{#mu} [GeV]", "Events/5 GeV", 15, 400, 1, 1000000000, 10, ratiomin, ratiomax);
  }
  else if(var_2_plot == "mu_phi"){
    chooseHistOptions("mu_phi","#phi^{#mu}","Events/0.1", -TMath::Pi()-.5, TMath::Pi()+.5, 1, 100000000, 1, ratiomin, ratiomax);
  }
  else if(var_2_plot == "mu_eta"){
    chooseHistOptions("mu_eta","#eta^{#mu}","Events/0.1", -3, 3, 1, 100000000, 1, ratiomin, ratiomax);
  }
  else if(var_2_plot == "cutflow"){
    chooseHistOptions("cutflow_calib","cutflow","Events",0,60,0.1,100000000,1,ratiomin,ratiomax);
  }
  else if(var_2_plot == "truth_cutflow"){
    isTruth = true;
    chooseHistOptions("cutflow_truth","truth cutflow","Events",0,30,0.1,100000000,1,ratiomin,ratiomax);
  }
  else if(var_2_plot == "Z_mass"){
    if(!isMJ && !isWide){
      chooseHistOptions("Z_mass","m_{#mu#mu} [GeV]","Events/2 GeV", 70, 110, 1, 1000000000, 1, 0.7, 1.5);
    }
    else{
      if(make_log) chooseHistOptions("Z_mass","m_{#mu#mu} [GeV]","Events/GeV", 70, 120, 1, 10000000, 2, ratiomin, ratiomax);
      else chooseHistOptions("Z_mass","m_{#mu#mu} [GeV]","Events/GeV", 70, 120, 1, 4000, 2, ratiomin, ratiomax);
    }
  }
  else if(var_2_plot == "m_mumu"){
    chooseHistOptions("m_mumu","m_{#mu#mu} [GeV]","Events/GeV", 20, 300, 1, 1000000000, 2, 0.7, 1.5);
  }
  else if(var_2_plot == "Z_mass_0j"){
    chooseHistOptions("Z_mass_0j", "m_{#mu#mu} [GeV]",  "Events/GeV", 75, 107, 1,  1000000000, 2, ratiomin, ratiomax);
  }
  else if(var_2_plot == "Z_mass_MET"){
    if(!isMJ && !isWide){
      chooseHistOptions("Z_mass_MET", "m_{#mu#mu} [GeV]","Events/GeV", 75, 107, 1, 1000000000, 1, 0.7, 1.5);
    }
    else{
      if(make_log) chooseHistOptions("Z_mass_MET","m_{#mu#mu} [GeV]","Events/GeV", 70, 120, 1, 10000000, 2, ratiomin, ratiomax);
      else chooseHistOptions("Z_mass_MET","m_{#mu#mu} [GeV]","Events/GeV", 70, 120, 1, 4000, 2, ratiomin, ratiomax);
    }
  }
  else if(var_2_plot == "Z_mass_exactly0j"){
    chooseHistOptions("Z_mass_exactly0j", "m_{#mu#mu} [GeV]", "Events/GeV", 75, 107, 1, 1000000000, 2, ratiomin, ratiomax);
  }
  else if(var_2_plot == "Z_mass_1j"){
    if(!isMJ && !isWide){
      chooseHistOptions("Z_mass_1j", "m_{#mu#mu} [GeV]", "Events/GeV", 75, 107, 1, 1000000000, 2, ratiomin, ratiomax); 
    }
    else{
      chooseHistOptions("Z_mass_1j","m_{#mu#mu} [GeV]", "Events/GeV", 60, 120, 1, 1000000000, 2, ratiomin, ratiomax);
    }
  }
  else if(var_2_plot == "Z_mass_1j_MET"){
    if(!isMJ && !isWide){
      chooseHistOptions("Z_mass_1j_MET", "m_{#mu#mu} [GeV]", "Events/GeV", 75, 107, 1, 1000000000, 2, ratiomin, ratiomax);
    }
    else{
      chooseHistOptions("Z_mass_1j_MET","m_{#mu#mu} [GeV]", "Events/GeV", 60, 120, 1, 1000000000, 2, ratiomin, ratiomax);
    }
  }
  else if(var_2_plot == "Z_mass_1j_tight_MET"){
    if(!isMJ && !isWide){
      chooseHistOptions("Z_mass_1j_tighteta_MET", "m_{#mu#mu} [GeV]", "Events/GeV", 75, 107, 1, 1000000000, 2, ratiomin, ratiomax);
    }
    else{
      chooseHistOptions("Z_mass_1j_tighteta_MET","m_{#mu#mu} [GeV]", "Events/GeV", 60, 120, 1, 1000000000, 2, ratiomin, ratiomax);
    }
 
  }
  else if(var_2_plot == "Z_mass_1b"){
    chooseHistOptions("Z_mass_1b", "m_{#mu#mu} [GeV] (N_{b-jets} #geq 1)",  "Events/GeV", 75, 107, 1, 1000000000, 2, 0.7, 1.5);
  }
  else if(var_2_plot == "Z_mass_2b"){
    chooseHistOptions("Z_mass_1b", "m_{#mu#mu} [GeV] (N_{b-jets} #geq 2)",  "Events/GeV", 70, 110, 1, 1000000000, 2, 0.7, 1.5);
  }
  else if(var_2_plot == "Z_y"){
    if(make_log) logmax = 1000000000;
    chooseHistOptions("Z_y", "Z rapidity", "Events/0.1", -3.5, 3.5, 1, logmax, 1, ratiomin, ratiomax);
  }
  else if(var_2_plot == "Z_eta"){
    if(make_log) logmax = 1000000000;
    chooseHistOptions("Z_eta", "Z pseudorapidity", "Events/0.1", -6., 6., 1, logmax, 2, ratiomin, ratiomax);
  }
  else if(var_2_plot == "Z_phi"){
    chooseHistOptions("Z_phi", "#phi^{Z}", "Events/0.1", -TMath::Pi()-.5, TMath::Pi()+.5, 1, 100000000, 1, ratiomin, ratiomax);
  }
  else if(var_2_plot == "Z_pt"){
    chooseHistOptions("Z_pT","Z p_{T}", "Events/50 GeV", 0., 800., 1, 100000000, 1, ratiomin, ratiomax);
  }
  else if(var_2_plot == "met"){
    chooseHistOptions("met","MET [GeV]","Events/5 GeV", 0., 200., 1, 100000000, 10, ratiomin, ratiomax);
  }
  else if(var_2_plot == "met_1tag"){
    chooseHistOptions("met_1tag","MET( >= 1 b)","Events/5 GeV", 0., 200., 1, 100000000, 10, ratiomin, ratiomax);
  }
  else if(var_2_plot == "n_jets"){
    chooseHistOptions("jet_n", "#jets/events", "Events", 0, 7, 1., 100000000, 1, ratiomin, ratiomax);
  }
  else if(var_2_plot == "jet_pt"){
    chooseHistOptions("jet_pt","jet pT [GeV]", "Events/10 GeV", 0., 500., 1, 10000000, 20, ratiomin, ratiomax);
  }
  else if(var_2_plot == "jet_y"){
    chooseHistOptions("jet_y", "jet rapidity", "Events/0.4", -5, 5, 1, 1000000000, 4, ratiomin, ratiomax);
  }
  else if(var_2_plot == "jet_st"){
    chooseHistOptions("jet_st","ST [GeV]", "Events/10 GeV", 25., 500., 1, 1000000000, 20, ratiomin, ratiomax);
  }
  else if(var_2_plot == "jet_ht"){
    chooseHistOptions("jet_mu_ht","HT [GeV]", "Events/10 GeV", 0., 1000., 1, 1000000000, 20, ratiomin, ratiomax);
  }
  else if(var_2_plot == "lead_jet_pt"){
    chooseHistOptions("jet_pt_lead","leading jet pT [GeV]", "Events/GeV", 0., 500., 1, 10000000,20, ratiomin, ratiomax);
  }
  else if(var_2_plot == "lead_jet_y"){
    chooseHistOptions("jet_y_lead","leading jet rapidity", "Events/0.4", -4.5, 4.5, 1, 100000000, 4, ratiomin, ratiomax);
  }
  else if(var_2_plot == "dijet_m"){
    chooseHistOptions("dijet_m", "m_{jj} [GeV]", "Events/20 GeV", 0., 1000., 1, 100000000, 40, ratiomin, ratiomax);
  }
  else if(var_2_plot == "n_jets_tight"){
    chooseHistOptions("jet_n_tighteta", "#jets/events", "Events", 0, 7, 1., 100000000, 1, ratiomin, ratiomax);
  }
  else if(var_2_plot == "jet_pt_tight"){
    chooseHistOptions("jet_pt_tighteta","jet pT [GeV]","Events/10 GeV", 0., 500., 1, 10000000, 20, ratiomin, ratiomax);
  }
  else if(var_2_plot == "jet_y_tight"){
    chooseHistOptions("jet_y_tighteta", "jet rapidity", "Events/0.4",  -3.5, 3.5, 1, 1000000000, 4, ratiomin, ratiomax);
  } 
  else if(var_2_plot == "jet_st_tight"){
    chooseHistOptions("jet_st_tighteta","ST [GeV]", "Events/10 GeV", 25.,500., 1, 1000000000, 20, ratiomin, ratiomax);
  }
  else if(var_2_plot == "jet_ht_tight"){
    chooseHistOptions("jet_mu_ht_tighteta","HT [GeV]", "Events/10 GeV", 0., 1000., 1, 1000000000, 20, ratiomin, ratiomax);
  }
  else if(var_2_plot == "lead_jet_pt_tight"){
    chooseHistOptions("jet_pt_lead_tighteta","leading jet pT [GeV]", "Events", 0., 1000., 1, 10000000,1, ratiomin, ratiomax);
  }
  else if(var_2_plot == "jet_pt_lead_gtr100"){
    chooseHistOptions("jet_pt_lead_tighteta_gtr100","leading jet pT [GeV], > 100GeV","Events", 0., 1000., 1, 10000000,1, ratiomin, ratiomax);
  }
  else if(var_2_plot == "jet_pt_lead_truth_gtr100"){
    isTruth = true;
    chooseHistOptions("leadjet_pt_truth_dressed_gtr100","leading truth jet pT [GeV], > 100GeV","Events", 0., 1000., 1, 10000000,1, ratiomin, ratiomax);
  }
  else if(var_2_plot == "dijet_m_tight"){
    chooseHistOptions("dijet_m_tighteta", "m_{jj} [GeV]","Events/20 GeV", 0., 1000., 1, 100000000, 40,ratiomin, ratiomax);
  }
  else if(var_2_plot == "n_jets_tightmet"){
    chooseHistOptions("jet_n_tighteta_MET", "#jets/events", "Events", 0, 7, 1., 100000000, 1, ratiomin, ratiomax);
  }
  else if(var_2_plot == "jet_pt_tightmet"){
    chooseHistOptions("jet_pt_tighteta_MET","jet pT [GeV]","Events/10 GeV", 0., 500., 1, 10000000, 20, ratiomin, ratiomax);
  }
  else if(var_2_plot == "jet_y_tightmet"){
    chooseHistOptions("jet_y_tighteta_MET", "jet rapidity", "Events/0.4",  -3.5, 3.5, 1, 1000000000, 4, ratiomin, ratiomax);
  }
  else if(var_2_plot == "jet_st_tightmet"){
    chooseHistOptions("jet_st_tighteta_MET","ST [GeV]", "Events/10 GeV", 25.,500., 1, 1000000000, 20, ratiomin, ratiomax);
  }
  else if(var_2_plot == "jet_ht_tightmet"){
    chooseHistOptions("jet_mu_ht_tighteta_MET","HT [GeV]", "Events/10 GeV", 0., 1000., 1, 1000000000, 40, ratiomin, ratiomax);
  }
  else if(var_2_plot == "leadjet_pt_tightmet"){
    chooseHistOptions("jet_pt_lead_tighteta_MET","leading jet pT [GeV]", "Events", 0., 800., 1, 10000000,1, ratiomin, ratiomax);
  }
  else if(var_2_plot == "dijet_m_tightmet"){
    chooseHistOptions("dijet_m_tighteta_MET", "m_{jj} [GeV]","Events/20 GeV", 0., 1000., 1, 100000000, 40,ratiomin, ratiomax);
  }
  else if(var_2_plot == "n_bjets"){
    chooseHistOptions("bjet_n", "N_{bjets}","Events", 0., 5., 1, 10000000, 1, ratiomin, ratiomax);
  }
  else if(var_2_plot == "bjet_pt"){
    chooseHistOptions("bjet_pt", "p_{T}(b-jets) [GeV]","Events/10 GeV", 0., 500, 1, 100000, 40, ratiomin, ratiomax);
  }
  else if(var_2_plot == "bjet_y"){
    chooseHistOptions("bjet_y", "b-jet rapidity", "Events/0.2",-3.5, 3.5, 1, 5000000, 4, ratiomin, ratiomax);
  }
  else if(var_2_plot == "bjet_lead_pt"){
    chooseHistOptions("bjet_lead_pt","p_{T}(leading b-jet) [GeV]", "Events/10 GeV", 0, 500, 1, 100000, 20, ratiomin, ratiomax);
  }
  else if(var_2_plot == "bjet_sublead_pt"){
    chooseHistOptions("bjet_sublead_pt","p_{T}(subleading b-jet) [GeV]", "Events/10 GeV", 0, 500, 1,100000,20, ratiomin, ratiomax);
  }
  else if(var_2_plot == "bjet_mass"){
    if(make_log) chooseHistOptions("bjet_m_bb", "m(b,b) [GeV]", "Events/10 GeV", 0, 500, 1, 10000, 20, ratiomin, ratiomax);
    else chooseHistOptions("bjet_m_bb", "m(b,b) [GeV]", "Events/10 GeV", 0, 400, 1, 1000, 20, ratiomin, ratiomax);
  }
  else if(var_2_plot == "deltaR_bb"){
    chooseHistOptions("bjet_delR_bb", "#Delta R (b,b)", "Events/0.5", 0, 5.0, 1, 3000, 10, ratiomin, ratiomax);
  }
  else if(var_2_plot == "deltaphi_bb"){
    chooseHistOptions("bjet_delphi_bb",  "#Delta#phi (b,b)", "Events/0.5", 0., 3.5, 1, 4000, 10, ratiomin, ratiomax);
  }
  else if(var_2_plot == "deltaeta_bb"){
    chooseHistOptions("bjet_deltaeta_bb","|#Delta#eta (b,b)|","Events/0.5", 0., 5.5, 1, 3000, 10, ratiomin, ratiomax);
  }
  else if(var_2_plot == "deltaR_Zb"){
    chooseHistOptions("bjet_delR_Zb", "#Delta R(Z,b)","Events/0.5", 0., 5.0, 1, 30000000, 10, ratiomin, ratiomax);
  }
  else if(var_2_plot == "deltaphi_Zb"){
    chooseHistOptions("bjet_deltaphi_bZ", "#Delta #phi (Z,b)", "Events/0.5", 0, 3.5, 1, 100000000, 10, ratiomin, ratiomax);
  }
  else if(var_2_plot == "deltaeta_Zb"){
    chooseHistOptions("bjet_deltaeta_Zb", "#Delta#eta (Z,b)", "Events/0.5", 0., 5.5, 1, 30000000, 10, ratiomin, ratiomax);
  }
  else if(var_2_plot == "bjet_pt_bb"){
    if(make_log) chooseHistOptions("bjet_pt_bb", "di-bjet p_{T}", "Events/10 GeV", 0, 350, 1, 100000, 20, ratiomin, ratiomax);
    else chooseHistOptions("bjet_pt_bb", "di-bjet p_{T}", "Events/10 GeV", 0, 350, 1, 500, 20, ratiomin, ratiomax);
  }
  else if(var_2_plot == "mv1cweight"){
    chooseHistOptions("mv1cweight", "mv1c weight", "Events/0.02", 0, 1, 1, 10000000, 10, ratiomin, ratiomax);
  }
  else if(var_2_plot == "mv1c_bins"){
    chooseHistOptions("mv1cweight_binned","mv1c weight", "Events",0, 1, 100,100000000, 1, ratiomin, ratiomax);
  }
  else if(var_2_plot == "mv1c_bins_leadjet"){
    chooseHistOptions("mv1cweight_binned_leadjet","mv1c weight (leading jet)","Event",0,1,100,100000000, 1, ratiomin, ratiomax);
  }
  else if(var_2_plot == "bottom_jets_hmatch_leadjet"){
    isTruth = true;
    chooseHistOptions("mv1cweight_bottom_had_match_leadjet","mv1c weight", "Events",0,1,1,100000000, 1, ratiomin, ratiomax);
}
  else if(var_2_plot == "charm_jets_hmatch_leadjet"){
    isTruth = true;
    chooseHistOptions("mv1cweight_charm_had_match_leadjet","mv1c weight", "Events",0,1,1,100000000, 1, ratiomin, ratiomax);
}
  else if(var_2_plot == "light_jets_hmatch_leadjet"){
    isTruth = true;
    chooseHistOptions("mv1cweight_light_had_match_leadjet","mv1c weight", "Events",0,1,1,100000000, 1, ratiomin, ratiomax);
}
  else if(var_2_plot == "light_jets"){
    isTruth = true;
    chooseHistOptions("mv1cweight_light","mv1c weight", "Events",0,1,1,100000000, 1, ratiomin, ratiomax);
  }
  else if(var_2_plot == "charm_jets"){
    isTruth = true;
    chooseHistOptions("mv1cweight_charm","mv1c weight", "Events",0,1,1,100000000, 1, ratiomin, ratiomax);
  }
  else if(var_2_plot == "bottom_jets"){
    isTruth = true;
    chooseHistOptions("mv1cweight_bottom","mv1c weight", "Events",0,1,1,100000000, 1, ratiomin, ratiomax);
  }
  else if(var_2_plot == "light_jets_hmatch"){
    isTruth = true;
    chooseHistOptions("mv1cweight_light_had_match","mv1c weight", "Events",0,1,1,100000000, 1, ratiomin, ratiomax);
  }
  else if(var_2_plot == "charm_jets_hmatch"){
    isTruth = true;
    chooseHistOptions("mv1cweight_charm_had_match","mv1c weight", "Events",0,1,1,100000000, 1, ratiomin, ratiomax);
  }
  else if(var_2_plot == "bottom_jets_hmatch"){
    isTruth = true;
    chooseHistOptions("mv1cweight_bottom_had_match","mv1c weight", "Events",0,1,1,100000000, 1, ratiomin, ratiomax);
  }
  else if(var_2_plot == "bottom_jets_hmatch_up"){
    isTruth = true;
    chooseHistOptions("mv1cweight_bottom_had_match_up","mv1c weight", "Events",0,1,1,100000000, 1, ratiomin, ratiomax);
  }
  else if(var_2_plot =="bottom_jets_hmatch_down"){
    isTruth = true;
    chooseHistOptions("mv1cweight_bottom_had_match_down","mv1c weight", "Events",0,1,1,100000000, 1, ratiomin, ratiomax);
  }
  else if(var_2_plot == "Z_ptmv1c_light_jets_hmatch"){
    isTruth = true;
    chooseHistOptions("mv1cweight_light_had_match_ptbinned","Z pT vs mv1c weight", "Z pT", 0,1,0,1000,1,ratiomin,ratiomax);
  }
  else if(var_2_plot == "Z_ptmv1c_charm_jets_hmatch"){
    isTruth = true;
    chooseHistOptions("mv1cweight_charm_had_match_ptbinned","Z pT vs mv1c weight", "Z pT", 0,1,0,1000,1,ratiomin,ratiomax);
}
  else if(var_2_plot == "Z_ptmv1c_bottom_jets_hmatch"){
    isTruth = true;
    chooseHistOptions("mv1cweight_bottom_had_match_ptbinned","Z pT vs mv1c weight", "Z pT", 0,1,0,1000,1,ratiomin,ratiomax);
}
  else if(var_2_plot == "Z_ptmv1c"){
    chooseHistOptions("mv1cweight_ptbinned","Z pT vs mv1c weight", "Z pT", 0,1,0,1000,1,ratiomin,ratiomax);
  }
  else if(var_2_plot == "Z_ptmv1c_light_jets_hmatch_leadjet"){
    isTruth = true;
    chooseHistOptions("mv1cweight_light_had_match_ptbinned_leadjet","Z pT vs mv1c weight", "Z pT", 0,1,0,1000,1,ratiomin,ratiomax);
  }
  else if(var_2_plot == "Z_ptmv1c_charm_jets_hmatch_leadjet"){
    isTruth = true;
    chooseHistOptions("mv1cweight_charm_had_match_ptbinned_leadjet","Z pT vs mv1c weight", "Z pT", 0,1,0,1000,1,ratiomin,ratiomax);
  }
  else if(var_2_plot == "Z_ptmv1c_bottom_jets_hmatch_leadjet"){
    isTruth = true;
    chooseHistOptions("mv1cweight_bottom_had_match_ptbinned_leadjet","Z pT vs mv1c weight", "Z pT", 0,1,0,1000,1,ratiomin,ratiomax);
  }
  else if(var_2_plot == "Z_ptmv1c_leadjet"){
    //isTruth = true;
    chooseHistOptions("mv1cweight_ptbinned_leadjet","Z pT vs mv1c weight", "Z pT", 0,1,0,1000,1,ratiomin,ratiomax);
  }
  else if(var_2_plot == "Z_ptmv1c_leadjet_trueZ"){
    isTruth = true;
    chooseHistOptions("mv1cweight_ptbinned_leadjet_trueZ","Z pT vs mv1c weight(truth Z)", "Z pT", 0,1,0,1000,1,ratiomin,ratiomax);
  }
  else if(var_2_plot == "Z_ptmv1c_light_jets_hmatch_leadjet_trueZ"){
    isTruth = true;
    chooseHistOptions("mv1cweight_light_had_match_ptbinned_leadjet_trueZ","Z pT vs mv1c weight", "Z pT", 0,1,0,1000,1,ratiomin,ratiomax);
  }
  else if(var_2_plot == "Z_ptmv1c_charm_jets_hmatch_leadjet_trueZ"){
    isTruth = true;
    chooseHistOptions("mv1cweight_charm_had_match_ptbinned_leadjet_trueZ","Z pT vs mv1c weight", "Z pT", 0,1,0,1000,1,ratiomin,ratiomax);
  }
  else if(var_2_plot == "Z_ptmv1c_bottom_jets_hmatch_leadjet_trueZ"){
    isTruth = true;
    chooseHistOptions("mv1cweight_bottom_had_match_ptbinned_leadjet_trueZ","Z pT vs mv1c weight", "Z pT", 0,1,0,1000,1,ratiomin,ratiomax);
  }
  else if(var_2_plot == "pileup"){
    if(make_log) logmax = 50000000000;
    else logmax = 700000;
    chooseHistOptions("pileup_Z_avg", "<#mu>", "Events", 0, 45, 1, logmax, 200, ratiomin, ratiomax);
  }
  else if(var_2_plot == "pileup_noweight"){
    if(make_log) logmax = 50000000000;
    else logmax = 700000;
    chooseHistOptions("pileup_Z_avg_norw", "<#mu>", "Events", 0, 45, 1, logmax, 200, ratiomin, ratiomax);
  }
  else if(var_2_plot == "actual_pileup"){
    if(make_log) logmax = 5000000000;
    else logmax = 700000;
    chooseHistOptions("pileup_Z", "pileup", "Events", 0, 45, 1, logmax, 200, ratiomin, ratiomax);
  }
  else if(var_2_plot == "Z_mass_truth"){
    if(make_log) logmax = 10000000000000;
    else logmax = 4000;
    isTruth = true;
    chooseHistOptions("Z_mass_truth_dressed", "m_{#mu#mu} [GeV] (truth dressed)","Events/2 GeV", 70, 110, 1, logmax, 1, 0.7, 1.5);
  }
  else if(var_2_plot == "dimu_mass_truth_dressed"){
    if(make_log) logmax = 10000000000000;
    else logmax = 4000;
    isTruth = true;
    chooseHistOptions("dimu_mass_truth_dressed", "m_{#mu#mu} [GeV] (truth dressed)","Events/2 GeV", 70, 110, 1, logmax, 1, 0.7, 1.5);
  }
  else if(var_2_plot == "Z_mass_match"){
    if(make_log) logmax = 50000000000;
    else logmax = 4000;
    isTruth = true;
    chooseHistOptions("Z_mass_match", "m_{#mu#mu} [GeV] (matched reco)","Events/2 GeV", 70, 110, 1, logmax, 1, 0.7, 1.5);
  }
  else if(var_2_plot =="Z_mass_unmatch"){
    if(make_log) logmax = 50000000000;
    else logmax = 4000;
    isTruth = true;
    chooseHistOptions("Z_mass_unmatch", "m_{#mu#mu} [GeV] (unmatched reco)","Events/2 GeV", 70, 110, 1, logmax, 1, 0.7, 1.5);
  }
  else if(var_2_plot == "Z_mass_migration"){
    isTruth = true;
    chooseHistOptions("Z_mass_migration","m_{#mu#mu} [GeV] (migration matrix)", "m_{#mu#mu} [GeV] (truth)",70,110,70,110,1,0.7,1.5);
  }
  else if(var_2_plot == "Z_mass_MET_match"){
    if(make_log) logmax = 50000000000;
    else logmax = 4000;
    isTruth = true;
    chooseHistOptions("Z_mass_MET_match", "m_{#mu#mu} [GeV] (matched reco)","Events/2 GeV", 70, 110, 1, logmax, 1, 0.7, 1.5);
  }
  else if(var_2_plot =="Z_mass_MET_unmatch"){
    if(make_log) logmax = 50000000000;
    else logmax = 4000;
    isTruth = true; 
    chooseHistOptions("Z_mass_MET_unmatch", "m_{#mu#mu} [GeV] (unmatched reco)","Events/2 GeV", 70, 110, 1, logmax, 1, 0.7, 1.5);
  }
  else if(var_2_plot == "Z_mass_MET_migration"){
    isTruth = true;
    chooseHistOptions("Z_mass_MET_migration","m_{#mu#mu} [GeV] (migration matrix)", "m_{#mu#mu} [GeV] (truth)",70,110,70,110,1,0.7,1.5);
  }
  else if(var_2_plot == "Z_y_truth"){
    if(make_log) logmax = 50000000000;
    else logmax = 4000;
    isTruth = true;
    chooseHistOptions("Z_y_truth_dressed", "Z rapidity (truth dressed)", "Events/0.1", -3.5, 3.5, 1, logmax, 1, ratiomin, ratiomax);
  }
  else if(var_2_plot == "Z_y_match"){
    if(make_log) logmax = 50000000000;
    else logmax= 4000;
    isTruth = true;
    chooseHistOptions("Z_y_match","Z rapidity (matched reco)","Events/0.1", -3.5, 3.5, 1, logmax, 1, ratiomin, ratiomax);
  }
  else if(var_2_plot == "Z_y_unmatch"){
    if(make_log) logmax = 50000000000;
    else logmax= 4000;
    isTruth = true;
    chooseHistOptions("Z_y_unmatch","Z rapidity (unmatched reco)","Events/0.1", -3.5, 3.5, 1, logmax, 1, ratiomin, ratiomax);
  }
  else if(var_2_plot == "Z_y_migration"){
    isTruth = true;
    chooseHistOptions("Z_y_migration","Z rapidity (migration matrix)","Z y",-3.5,3.5,-3.5,3.5,1,0.7,1.5);
  }
  else if(var_2_plot == "Z_pt_truth"){
    isTruth = true;
    chooseHistOptions("Z_pt_truth_dressed","Z p_{T} (truth dressed)", "Events/50 GeV", 0., 1000., 1, 100000000, 1, ratiomin, ratiomax);
  }
  else if(var_2_plot == "Z_pt_match"){
    isTruth = true;
    chooseHistOptions("Z_pt_match","Z p_{T} (matched reco)", "Events/50 GeV", 0., 1000., 1, 100000000, 1, ratiomin, ratiomax);
  }
  else if(var_2_plot == "Z_pt_unmatch"){
    isTruth = true;
    chooseHistOptions("Z_pt_unmatch","Z p_{T} (unmached reco)", "Events/50 GeV", 0., 1000., 1, 100000000, 1, ratiomin, ratiomax);
  }
  else if(var_2_plot == "Z_pt_migration"){
    isTruth = true;
    chooseHistOptions("Z_pt_migration","Z p_{T} (migration matrix)", "Events/50 GeV", 0., 1000., 0., 1000, 1, ratiomin, ratiomax);
  }
  else if(var_2_plot == "Z_pt_1j_notb_truth"){
    isTruth = true;
    chooseHistOptions("Z_pt_1j_tighteta_notb_truth","Z p_{T} [GeV]","Events",0., 800., 1, 100000000, 1, ratiomin, ratiomax);
  }
  else if(var_2_plot == "Z_pt_1b_truelightjet"){
    isTruth = true;
    chooseHistOptions("Z_pt_1b_truelightjet","Z p_{T} [GeV]","Events",0.,800.,1,100000000, 1, ratiomin, ratiomax);
  }
  else if(var_2_plot == "Z_pt_trueb_notbreco"){
    isTruth = true;
    chooseHistOptions("Z_pt_trueb_notbreco","Z p_{T} [GeV]","Events",0.,800.,1,100000000, 1, ratiomin, ratiomax);
  }
  else if(var_2_plot == "Z_pt_1j_cjets"){
    isTruth = true;
    chooseHistOptions("Z_pt_1j_cjets","Z p_{T} [GeV]","Events",0., 200., 1, 100000000, 1, ratiomin, ratiomax);
  }
  else if(var_2_plot == "Z_pt_1j_bjets"){
    isTruth = true;
    chooseHistOptions("Z_pt_1j_bjets","Z p_{T} [GeV]","Events",0., 200., 1, 100000000, 1, ratiomin, ratiomax);
  }
  else if(var_2_plot =="Z_pt_1j_ljets"){
    isTruth = true;
    chooseHistOptions("Z_pt_1j_ljets","Z p_{T} [GeV]","Events",0., 200., 1, 100000000, 1, ratiomin, ratiomax);
  }
  else if(var_2_plot == "Z_pt_1b_bjets"){
    isTruth = true;
    chooseHistOptions("Z_pt_1b_bjets","Z p_{T} [GeV]","Events",0., 200., 1, 100000000, 1, ratiomin, ratiomax);
  }
  else if(var_2_plot == "Z_pt_1j_cjets_reco"){
    isTruth = true;
    chooseHistOptions("Z_pt_1j_cjets_reco","Z p_{T} [GeV]","Events",0., 200., 1, 100000000, 1, ratiomin, ratiomax);
  }
  else if(var_2_plot == "Z_pt_1j_bjets_reco"){
    isTruth = true;
    chooseHistOptions("Z_pt_1j_bjets_reco","Z p_{T} [GeV]","Events",0., 200., 1, 100000000, 1, ratiomin, ratiomax);
  }
  else if(var_2_plot == "Z_pt_1j_ljets_reco"){
    isTruth = true;
    chooseHistOptions("Z_pt_1j_ljets_reco","Z p_{T} [GeV]","Events",0., 200., 1, 100000000, 1, ratiomin, ratiomax);
  }
  else if(var_2_plot == "Z_pt_v_p_bjets"){
    isTruth = true;
    chooseHistOptions("Z_pt_v_p_bjets","Z p_{T} [GeV]","Z p",0.,200.,0.,200.,1,ratiomin,ratiomax);
  }
  else if(var_2_plot == "Z_pt_v_p_ljets"){
    isTruth = true;
    chooseHistOptions("Z_pt_v_p_ljets","Z p_{T} [GeV]","Z p",0.,200.,0.,200.,1,ratiomin,ratiomax);
  }
  else if(var_2_plot == "Z_pt_1b_reco"){
    isTruth = true;
    chooseHistOptions("Z_pt_1j_tighteta_b_reco","Z p_{T} [GeV]","Events",0., 800., 1, 100000000, 1, ratiomin, ratiomax);
  }
  else if(var_2_plot == "Z_pt_1b_matchedjet_reco"){
    isTruth = true;
    chooseHistOptions("Z_pt_1b_matchedjet_reco","Z p_{T} [GeV]","Events",0., 800., 1, 100000000, 1, ratiomin, ratiomax);
  }
  else if(var_2_plot == "Z_pt_1b_matchedjet_0225_reco"){
    isTruth = true;
    chooseHistOptions("Z_pt_1b_matchedjet_0225_reco","Z p_{T} [GeV]","Events",0., 800., 1, 100000000, 1, ratiomin, ratiomax);
  }
  else if(var_2_plot == "Z_pt_1b_matchedjet_025_reco"){
    isTruth = true;
    chooseHistOptions("Z_pt_1b_matchedjet_025_reco","Z p_{T} [GeV]","Events",0., 800., 1, 100000000, 1, ratiomin, ratiomax);
  }
  else if(var_2_plot == "Z_pt_1b_matchedjet_0275_reco"){
    isTruth = true;
    chooseHistOptions("Z_pt_1b_matchedjet_0275_reco","Z p_{T} [GeV]","Events",0., 800., 1, 100000000, 1, ratiomin, ratiomax);
  }
  else if(var_2_plot == "Z_pt_1b_matchedjet_03_reco"){
    isTruth = true;
    chooseHistOptions("Z_pt_1b_matchedjet_03_reco","Z p_{T} [GeV]","Events",0., 800., 1, 100000000, 1, ratiomin, ratiomax);
  }
  else if(var_2_plot == "Z_pt_1b_matchedjet_notrueZ_reco"){
    isTruth = true;
    chooseHistOptions("Z_pt_1b_matchedjet_notrueZ_reco","Z p_{T} [GeV]","Events",0., 800., 1, 100000000, 1, ratiomin, ratiomax);
  }
  else if(var_2_plot == "Z_pt_1b_truth_postcalib"){
    isTruth = true;
    chooseHistOptions("Z_pt_1j_tighteta_b_truth","Z p_{T} [GeV]","Events",0., 800., 1, 100000000, 1, ratiomin, ratiomax);
  }
  else if(var_2_plot == "Z_pt_1notb_reco"){
    isTruth = true;
    chooseHistOptions("Z_pt_1j_tighteta_notb_reco","Z p_{T} [GeV]","Events",0., 800., 1, 100000000, 1, ratiomin, ratiomax);
  }
  else if(var_2_plot == "truebrank_Z1b_reco"){
    isTruth = true;
    chooseHistOptions("truebrank_Z1b_reco","Truth b rank","Events",0,10,1,100000000, 1, ratiomin, ratiomax);
  }
  else if(var_2_plot == "truebrank_Z1b_trueZ_reco"){
    isTruth = true;
    chooseHistOptions("truebrank_Z1b_trueZ_reco","Truth b rank","Events",0,10,1,100000000, 1, ratiomin, ratiomax);
  }
  else if(var_2_plot == "Z_pt_1j"){
    chooseHistOptions("Z_pt_1j","Z p_{T} [GeV] ","Events", 0., 800., 1, 100000000, 1, ratiomin, ratiomax);
  }
  else if(var_2_plot == "Z_pt_1j_truth"){
    isTruth = true;
    chooseHistOptions("Z_pt_1j_truth","Z p_{T}, >= 1j","Events", 0., 800., 1, 100000000, 1, ratiomin, ratiomax);
  }
  else if(var_2_plot == "Z_pt_1j_match"){
    isTruth = true;
    chooseHistOptions("Z_pt_1j_match","Z p_{T}, >= 1j","Events", 0., 800., 1, 100000000, 1, ratiomin, ratiomax);
  }
  else if(var_2_plot == "Z_pt_1j_unmatch"){
    isTruth = true;
    chooseHistOptions("Z_pt_1j_unmatch","Z p_{T}, >= 1j","Events", 0., 800., 1, 100000000, 1, ratiomin, ratiomax);
  }
  else if(var_2_plot == "Z_pt_1j_migration"){
    isTruth = true;
    chooseHistOptions("Z_pt_1j_migration","Z p_{T}, >= 1j","Events", 0., 800., 0., 800, 1, ratiomin, ratiomax);
  }
  else if(var_2_plot == "Z_pt_1b_truth"){
    isTruth = true;
    chooseHistOptions("Z_pt_1j_b_truth","Z p_{T}, >= 1b","Events", 0., 800., 1, 100000000, 1, ratiomin, ratiomax);
  }
  else if(var_2_plot == "Z_pt_1b_match"){
    isTruth= true;
    chooseHistOptions("Z_pt_1j_b_match","Z p_{T}, >= 1b","Events", 0., 800., 1, 100000000, 1, ratiomin, ratiomax);
  }
  else if(var_2_plot == "Z_pt_1b_unmatch"){
    isTruth= true;
    chooseHistOptions("Z_pt_1j_b_unmatch","Z p_{T}, >= 1b","Events", 0., 800., 1, 100000000, 1, ratiomin, ratiomax);
  }
  else if(var_2_plot == "Z_pt_1b_migration"){
    isTruth= true;
    chooseHistOptions("Z_pt_1j_b_migration","Z p_{T}, >= 1b","Events", 0., 800., 0., 800, 1, ratiomin, ratiomax);
  }
  else if(var_2_plot == "Z_pt_1j_b_reco"){
    isTruth = true;
    chooseHistOptions("Z_pt_1j_tighteta_b_reco","Z p_{T}, >= 1b","Events",0.,800.,1,100000000, 1, ratiomin, ratiomax);
  }
  else if(var_2_plot == "jet_pt_2D"){
    isTruth = true;
    chooseHistOptions("jet_pt_2D","jet p_{T}, reco v. truth","Events",0.,800.,0,800.,1,ratiomin,ratiomax);
  }
  else if(var_2_plot == "dRtoB"){
    isTruth = true;
    chooseHistOptions("dRtoB","#Delta R (j_reco,B)", "Events/0.5", 0, 5.0, 1, 10000000., 10, ratiomin, ratiomax);
  }
  else if(var_2_plot == "Nb_truth"){
    isTruth = true;
    chooseHistOptions("Nb_truth","N_b (truth)","Events",-0.5,5.5,1,10000000.,1,ratiomin,ratiomax);
  }
  else if(var_2_plot == "Nb_reco"){
    isTruth = true;
    chooseHistOptions("Nb_reco","N_b (reco)","Events",-0.5,5.5,1,10000000.,1,ratiomin,ratiomax);
  }
  else if(var_2_plot == "Zpt_1j_incl"){
    chooseHistOptions("Zpt_1j_incl","Z p_T inclusive (events >= cut value)","Events",0.,800.,1,100000000, 1, ratiomin, ratiomax);
  }
  else if(var_2_plot == "Zpt_1j_truth_incl"){
    isTruth = true;
    chooseHistOptions("Zpt_1j_truth_incl","Z p_T inclusive (truth events >= cut value)","Events",0.,800.,1,100000000, 1, ratiomin, ratiomax);
  }
  else if(var_2_plot == "dR_trueleadjet_recoleadjet"){
    isTruth = true;
    chooseHistOptions("dR_trueleadjet_recoleadjet","#Delta R (j_true,j_reco)", "Events/0.5", 0, 5.0, 1, 10000000., 10, ratiomin, ratiomax);
  }
  else if(var_2_plot == "dR_trueleadb_recoleadjet"){
    isTruth = true;
    chooseHistOptions("dR_trueleadb_recoleadjet","#Delta R(b(true),j(reco))","Events/0.5", 0, 5.0, 1, 10000000., 10, ratiomin, ratiomax);
  }
  else if(var_2_plot == "trueb_pt_noleadingrecojet"){
    isTruth = true;
    chooseHistOptions("trueb_pt_noleadingrecojet","Truth leading jet p_{T}","Events", 0., 1000., 1, 100000, 1, ratiomin, ratiomax);
  }
  else if(var_2_plot == "dphi_deta_trueleadb_recoleadjet"){
    isTruth = true;
    chooseHistOptions("dphi_deta_trueleadb_recoleadjet","dPhi","dEta",-4.,4.,-5.,5.,1,ratiomin,ratiomax);
  }
  else if(var_2_plot == "dR_Z_leadjet"){
    chooseHistOptions("dR_Z_leadjet","Delta R(Z,j(leading))","Events/0.5", 0, 5.0, 1, 10000000., 10, ratiomin, ratiomax);
  }
  else if(var_2_plot == "dR_Z_leadjet_true_reco"){
    isTruth = true;
    chooseHistOptions("dR_Z_leadjet_true_reco","#Delta R(Z,j(leading)) (truth)","#Delta R(Z,j(leading)) (reco)",0,5.0,0,5.0,1,ratiomin,ratiomax);
  }
  else if(var_2_plot == "recoleadb_truejrank"){
    isTruth = true;
    chooseHistOptions("recoleadb_truejrank","Rank of truth jet matching leading reco b-jet","Events",0.,10.,1,100000000.,1,ratiomin,ratiomax);
  }
  else if(var_2_plot == "recoleadb_truebrank"){
    isTruth = true;
    chooseHistOptions("recoleadb_truebrank","Rank of truth b-jet matching leading reco b-jet","Events",0.,10.,1,100000000.,1,ratiomin,ratiomax);
  }
  else if(var_2_plot == "recoleadb_trueZ_ZpT"){
    isTruth = true;
    chooseHistOptions("recoleadb_trueZ_ZpT","Z pT [GeV]","Events", 0., 800., 1, 100000000, 1, ratiomin, ratiomax);
  }
  else if(var_2_plot == "recoleadb_notrueZ_ZpT"){
    isTruth = true;
    chooseHistOptions("recoleadb_notrueZ_ZpT","Z pT [GeV]","Events", 0., 800., 1, 100000000, 1, ratiomin, ratiomax);
  }
  else if(var_2_plot == "recoleadb_trueZ_truej_ZpT"){
    isTruth = true;
    chooseHistOptions("recoleadb_trueZ_truej_ZpT","Z pT [GeV]","Events", 0., 800., 1, 100000000, 1, ratiomin, ratiomax);
  }
  else if(var_2_plot == "recoleadb_trueZ_notruej_ZpT"){
    isTruth = true;
    chooseHistOptions("recoleadb_trueZ_notruej_ZpT","Z pT [GeV]","Events", 0., 800., 1, 100000000, 1, ratiomin, ratiomax);
  }
  else if(var_2_plot == "trueleadb_recorank"){
    isTruth = true;
    chooseHistOptions("trueleadb_recorank","Rank of reco jet matching true b (0 == no match)","Events",0.,10.,1,10000000.,1,ratiomin,ratiomax);
  }
  else if(var_2_plot == "trueleadb_matchingDeltaR"){
    isTruth = true;
    chooseHistOptions("trueleadb_matchingDeltaR","deltaR of matching jet","Events",0,5.0,1,10000000., 10, ratiomin, ratiomax);
  }
  else if(var_2_plot == "trueleadb_matchingpT"){
    isTruth = true;
    chooseHistOptions("trueleadb_matchingpT","pT of matching jet","Events",0.,1000.,1,1000000.,20,ratiomin,ratiomax);
  }
  else if(var_2_plot == "trueleadb_matchingpT_isb"){
    isTruth = true;
    chooseHistOptions("trueleadb_matchingpT_isb","pT of matching bjet","Events",0.,1000.,1,1000000,20,ratiomin,ratiomax);
  }
  else if(var_2_plot == "trueleadb_recorank_isb"){
    isTruth = true;
    chooseHistOptions("trueleadb_recorank_isb","rank of matching b-jet","Events",0.,10.,1,10000000.,1,ratiomin,ratiomax);
  }
  else if(var_2_plot == "trueleadb_pt_nomatchingbjet"){
    isTruth = true;
    chooseHistOptions("trueleadb_pt_nomatchingbjet","pt of true b with no matching b-jet","Events",0.,1000.,1,1000000,20,ratiomin,ratiomax);
  }
  else if(var_2_plot == "trueleadb_pt_nomatchingleadjet"){
    isTruth = true;
    chooseHistOptions("trueleadb_pt_nomatchingleadjet","p_{T} [GeV]","Events/10 GeV",0.,800.,1,100000,20,ratiomin,ratiomax);
  }
  else if(var_2_plot =="trueleadb_pt_nomatchingjet"){
    isTruth = true;
    chooseHistOptions("trueleadb_pt_nomatchingjet","p_{T} [GeV]","Events/10 GeV",0.,800.,1,100000,20,ratiomin,ratiomax);
  }
  else if(var_2_plot == "n_jets_truth"){
    isTruth = true;
    chooseHistOptions("n_jets_truth_dressed","N jets truth","Events", 0., 12., 1, 100000000, 1, ratiomin, ratiomax);
  }
  else if(var_2_plot == "n_jets_tightmet_match"){
    isTruth = true;
    chooseHistOptions("n_jets_match","N jets match","Events", 0., 12., 1, 100000000, 1, ratiomin, ratiomax);
  }
  else if(var_2_plot == "n_jets_tightmet_unmatch"){
    isTruth = true;
    chooseHistOptions("n_jets_unmatch","N jets unmatch","Events", 0., 12., 1, 100000000, 1, ratiomin, ratiomax);
  }
  else if(var_2_plot == "n_jets_tightmet_migration"){
    isTruth = true;
    chooseHistOptions("n_jets_migration","N jets migration","Events", 0., 12., 0, 12., 1, ratiomin, ratiomax);
  }
  else if(var_2_plot == "leadjet_pt_truth"){
    isTruth = true;
    chooseHistOptions("leadjet_pt_truth_dressed","Truth leadjet pt","Events", 0., 1000., 1, 100000000, 1, ratiomin, ratiomax);
  }
  else if(var_2_plot == "leadjet_pt_truth_aftercalib"){
    isTruth = true;
    chooseHistOptions("leadjet_pt_truth_aftercalib","Truth leadjet pt (after calib","Events",0.,1000.,1,100000000, 1, ratiomin, ratiomax);
  }
  else if(var_2_plot == "leadjet_pt_tightmet_match"){
    isTruth = true;
    chooseHistOptions("leadjet_pt_match","leadjet pt match", "Events", 0., 1000., 1, 100000000, 1, ratiomin, ratiomax);
  }
  else if(var_2_plot == "leadjet_pt_tightmet_unmatch"){
    isTruth = true;
    chooseHistOptions("leadjet_pt_unmatch","leadjet pt unmatch", "Events", 0., 1000., 1, 100000000, 1, ratiomin, ratiomax);
  }
  else if(var_2_plot == "leadjet_pt_tightmet_migration"){
    isTruth = true;
    chooseHistOptions("leadjet_pt_migration","leadjet pt migration","Events", 0., 1000., 1, 1000., 1, ratiomin, ratiomax);
  }
  else{
    cout << "This variable is not supported" << endl;
    exit(0);
  }

  histo_name = histToPlot.histo_name;
  x_name = histToPlot.x_name;
  y_name = histToPlot.y_name;
  x_min = histToPlot.x_min;
  x_max = histToPlot.x_max;
  y_min = histToPlot.y_min;
  y_max = histToPlot.y_max;
  rebin = histToPlot.rebin;
  ratiomin = histToPlot.ratiomin;
  ratiomax = histToPlot.ratiomax;
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
~~~~~~~~~~~~MC CROSS SECTIONS~~~~~~~~~~~~~~~~~~~~
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  double xsec = 0;
  /*~~~~~~~~~~~~~~Sherpa Zmumu~~~~~~~~~~~~~~~~~~~~*/
  //Dataset 147771
  //xsections from arantxa's note

  string zmumu_sherpa_process = "zmumu_sherpa";
  vector<double> zmumu_sherpa_xsec;
  double sigma_zmumu_sherpa[1] = {1207.8};

  double k_factor_zmumu_sherpa = 1.0276;
  double eff_zmumu_sherpa = 1.0;
  xsec = sigma_zmumu_sherpa[0]*k_factor_zmumu_sherpa*eff_zmumu_sherpa;
  zmumu_sherpa_xsec.push_back(xsec);

  /*~~~~~~~~~~~~~~~~~~~Zmumu_NpX~~~~~~~~~~~~~~~~~~~~~~~~~*/
  //Datasets 147113 through 147118 (AlpgenPythia_Auto_P2011C_ZmumuNpX)
  //note: Np2 uses eta-corrected tag (e3405)
  //xsections recalculated for HFOR
  string zmumu_process = "zmumu";
  vector<double> zmumu_xsec;
  //  double sigma_zmumu[6] = {719.16, 175.74, 58.882, 15.673, 4.0057, 1.2544};
  double sigma_zmumu[6] = {684.75988,152.98614,47.970835,11.76804,2.8591346,0.8419257};

  //7 TeV cross sections (for comparing)
  //  double sigma_zmumu[6] = {675.60,153.38,49.369,12.569,3.0427,0.83944};
  //  double k_factor_zmumu = 1.18;
  double k_factor_zmumu = 1.2355;
  double eff_zmumu = 1.0;
  for(int i=0;i<6;i++){
    xsec = sigma_zmumu[i]*k_factor_zmumu*eff_zmumu;
    zmumu_xsec.push_back(xsec);
  }
  /*~~~~~~~~~~~~~~~~~~~~~~~Zmumubb_NpX~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  //Datasets 200340 through 200343
  //x-section sources: https://twiki.cern.ch/twiki/bin/viewauth/AtlasProtected/TopMC12ZjetsSamples
  string zmumubb_process = "zmumubb";
  vector<double> zmumubb_xsec;
  //  double sigma_zmumubb[4] = {6.5056, 3.2909, 1.2585, 0.61808};
  double sigma_zmumubb[4] = {6.3456008,3.1204688,1.1525835,0.53671763};
  //  double k_factor_zmumubb = 1.18;
  double k_factor_zmumubb = 1.2355;
  double eff_zmumubb = 1.0;
  for(int i=0; i < 4; i++){
    xsec = sigma_zmumubb[i]*k_factor_zmumubb*eff_zmumubb;
    zmumubb_xsec.push_back(xsec);
  }
  /*~~~~~~~~~~~~~~~~~~~~~~Zmumucc_NpX~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  //Datasets 200440 through 200443
  //x-section sources: https://twiki.cern.ch/twiki/bin/viewauth/AtlasProtected/TopMC12ZjetsSamples
  string zmumucc_process = "zmumucc";
  vector<double> zmumucc_xsec;
  //  double sigma_zmumucc[4] = {11.795, 4.1254, 3.3694, 1.7003};
  double sigma_zmumucc[4] = {11.310982,3.7487935,2.9370389,1.3568115};
  //  double k_factor_zmumucc = 1.18;
  double k_factor_zmumucc = 1.2355;
  double eff_zmumucc = 1.0;
  for(int i=0; i<4; i++){
    xsec = sigma_zmumucc[i]*k_factor_zmumucc*eff_zmumucc;
    zmumucc_xsec.push_back(xsec);
  }
  /*~~~~~~~~~~~~~~~~~~~~~~Ztautau_NpX~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  //Datasets 107670 through 107675
  //x-section source: https://twiki.cern.ch/twiki/bin/viewauth/AtlasProtected/TopMC12ZjetsSamples
  string ztautau_process = "ztautau";
  vector<double> ztautau_xsec;
  double sigma_ztautau[6] = {711.89, 155.09, 48.805, 14.140, 3.7711, 1.1122};
  double k_factor_ztautau = 1.2290;
  double eff_ztautau = 1.0;
  for(int i=0; i<6; i++){
    xsec=sigma_ztautau[i]*k_factor_ztautau*eff_ztautau;
    ztautau_xsec.push_back(xsec);
  }
  /*~~~~~~~~~~~~~~~~~~~~~Wmunu_NpX~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  //datasets 147033-147038 (alpgen+pythia)
  //x-section source: https://twiki.cern.ch/twiki/bin/viewauth/AtlasProtected/TopMC12WjetsSamples
  string wmunu_process = "wmunu";
  vector<double> wmunu_xsec;
  double sigma_wmunu[6] = {8127.1, 1792.9, 542.24, 147.66, 37.745, 11.970};
  double k_factor_wmunu = 1.133;
  double eff_wmunu = 1.0;
  for(int i=0; i<6; i++){
    xsec=sigma_wmunu[i]*k_factor_wmunu*eff_wmunu;
    wmunu_xsec.push_back(xsec);
  }
  /*~~~~~~~~~~~~~~~~~~Wcc_NpX~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  //datasets 200156-200159
  //x-section source:  https://twiki.cern.ch/twiki/bin/viewauth/AtlasProtected/TopMC12WjetsSamples
  string wcc_process = "wcc";
  vector<double> wcc_xsec;
  double sigma_wcc[4] = {149.39, 143.90, 84.227, 44.277};
  double k_factor_wcc = 1.133;
  double eff_wcc = 1.0;
  for(int i=0; i<4; i++){
    xsec=sigma_wcc[i]*k_factor_wcc*eff_wcc;
    wcc_xsec.push_back(xsec);
  }
  /*~~~~~~~~~~~~~~~~~~Wc_NpX~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  //datasets 200056-200060
  //x-section source: same as other w+jets
  string wc_process = "wc";
  vector<double> wc_xsec;
  double sigma_wc[5] = {758.93, 274.47, 71.643, 16.482, 4.7824};
  double k_factor_wc = 1.52;
  double eff_wc = 1.0;
  for(int i=0; i<5; i++){
    xsec=sigma_wc[i]*k_factor_wc*eff_wc;
    wc_xsec.push_back(xsec);
  }
  /*~~~~~~~~~~~~~~~Wbb_NpX~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  //datasets 200256-200259
  string wbb_process = "wbb";
  vector<double> wbb_xsec;
  double sigma_wbb[4] = {52.237, 45.628, 23.955, 13.633};
  double k_factor_wbb = 1.133;
  double eff_wbb =1.0;
  for(int i=0; i<4; i++){
    xsec=sigma_wbb[i]*k_factor_wbb*eff_wbb;
    wbb_xsec.push_back(xsec);
  }
  /*~~~~~~~~~~~~~~~~~~~~~~~tt-bar~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  //dataset 117050
  //x-section source: https://twiki.cern.ch/twiki/bin/viewauth/AtlasProtected/TopMC12DiTopSamples
  string ttbar_process = "ttbar";
  vector<double> ttbar_xsec;
  //  double sigma_ttbar[1] = {114.49};
  double sigma_ttbar[1] = {253.00};
  double k_factor_ttbar = 1.1994;
  //  double eff_ttbar = 1.0
  double eff_ttbar = 0.543;
  for(int i=0; i<1; i++){
    xsec = sigma_ttbar[i]*k_factor_ttbar*eff_ttbar;
    ttbar_xsec.push_back(xsec);
  }

  /*~~~~~~~~~~~~~~~new single top~~~~~~~~~~~~~~~~~~~~~~~*/
  //datasets 110090, 110091, 110119, 110140 (Powheg+Pythia)
  // t-chan, anti t-chan, s-chan, Wtchan
  //x-section source: arantxa's note (double-check)
  //k-factor source: arantxa's note (double-check)
  /*  string singletop_process = "singletop";
  vector<double> singletop_xsec;
  double sigma_singletop[4] = {17.520,9.3932,1.642400,20.46100};
  double k_factor_singletop[4] = {1.0500,1.0616,1.106700,1.093300};
  double eff_singletop = 1.0;
  for(int i=0; i<4; i++){
    xsec = sigma_singletop[i]*k_factor_singletop[i]*eff_singletop;
    singletop_xsec.push_back(xsec);
    }*/
  
  double eff_singletop = 1.0;

  string tchan_process = "tchan";
  vector<double> tchan_xsec;
  double sigma_tchan[2] = {17.520,9.3932};
  double k_factor_tchan[2] = {1.0500,1.0616};
  for(int i=0; i<2; i++){
    xsec = sigma_tchan[i]*k_factor_tchan[i]*eff_singletop;
    tchan_xsec.push_back(xsec);
  }
  string schan_process = "schan";
  vector<double> schan_xsec;
  double sigma_schan[1] = {1.642400};
  double k_factor_schan[1] = {1.106700};
  xsec = sigma_schan[0]*k_factor_schan[0]*eff_singletop;
  schan_xsec.push_back(xsec);

  string Wtchan_process = "Wtchan";
  vector<double> Wtchan_xsec;
  double sigma_Wtchan[1] = {20.46100};
  double k_factor_Wtchan[1] = {1.093300};
  xsec = sigma_Wtchan[0]*k_factor_Wtchan[0]*eff_singletop;
  Wtchan_xsec.push_back(xsec);
 
  //datasets: WWtomunuqq(183736), WZtomunuqq(183737), ZWtomumuqq(183587), ZWtotautauqq(183589), ZZtomumuqq(183588), ZZtotautauqq(183590)
  /*  string diboson_process = "diboson";
  vector<double> diboson_xsec;
  double sigma_diboson[6] = {7.2854,1.9057,1.4637,1.4523,0.24747,0.24167};
  double k_factor_diboson[6] = {1.05,1.05,1.05,1.05,1.,1.};
  double eff_diboson = 1.0;
  for(int i=0; i<6; i++){
    xsec = sigma_diboson[i]*k_factor_diboson[i]*eff_diboson;
    diboson_xsec.push_back(xsec);
    }*/

  double eff_diboson = 1.0;

  string WW_process = "WW";
  vector<double> WW_xsec;
  double sigma_WW[1] = {7.2854};
  double k_factor_WW = 1.05;
  xsec = sigma_WW[0]*k_factor_WW*eff_diboson;
  WW_xsec.push_back(xsec);

  string WZ_process = "WZ";
  vector<double> WZ_xsec;
  double sigma_WZ[3] = {1.9057,1.4637,1.4523};
  double k_factor_WZ = 1.05;
  for(int i=0; i<3; i++){
    xsec = sigma_WZ[i]*k_factor_WZ*eff_diboson;
    WZ_xsec.push_back(xsec);
  }
  
  string ZZ_process = "ZZ";
  vector<double> ZZ_xsec;
  double sigma_ZZ[2] = {0.24747,0.24167};
  double k_factor_ZZ = 1.0;
  for(int i=0; i<2; i++){
    xsec = sigma_ZZ[i]*k_factor_ZZ*eff_diboson;
    ZZ_xsec.push_back(xsec);
  }

  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    ~~~~~~~~~~~OPEN FILES~~~~~~~~~~~~~~~~~~~~~~~~~~
    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  //====================
  //== Monte Carlo =====
  //====================
  string cutflow_h_path = "/n/atlas02/user_codes/looper.6/Vbb/hfor_histograms_new/";
  string mc_path = "/n/atlas02/user_codes/looper.6/Vbb/analysis_code/MC_histograms/";
  if(isMJ){
    mc_path = "/n/atlas02/user_codes/looper.6/Vbb/analysis_code/MC_histograms_MJ/";
  }
  else if(isWide){
    mc_path =  "/n/atlas02/user_codes/looper.6/Vbb/analysis_code/MC_histograms_wide/";
  }

  //Sherpa Zmumu

  string file_suffix;
  if(isMJ) file_suffix = "_MJ.root";
  else if(isWide) file_suffix = "_wide.root";
  else if(isShort) file_suffix = "_short.root";
  else file_suffix = ".root";

  string mc_type_zmumu_sherpa = "Zmumu_sherpa";
  const int n_files_zmumu_sherpa = 1;
  TFile * fzmumu_sherpa[1];
  TFile * fzmumu_sherpa_cf[1];
  string fname_zmumu_sherpa[1];
  string zmumu_sherpa_name;
  string zmumu_sherpa_cf_name;
  zmumu_sherpa_name = "SherpaZmumu_hists";
  zmumu_sherpa_cf_name = cutflow_h_path + zmumu_sherpa_name + ".root";
  zmumu_sherpa_name += file_suffix;
  fname_zmumu_sherpa[0] = zmumu_sherpa_name;
  zmumu_sherpa_name = mc_path + zmumu_sherpa_name;
  if(include_sherpa){
    cout << "Opening sherpa" << endl;
    fzmumu_sherpa[0] = TFile::Open(zmumu_sherpa_name.c_str(),"UPDATE");
    fzmumu_sherpa_cf[0] = TFile::Open(zmumu_sherpa_cf_name.c_str(),"UPDATE");
  }

  //Zmumu_NpX
  string mc_type_zmumu = "Zmumu_Np";
  const int n_files_zmumu = 6;
  TFile * fzmumu[6];
  TFile * fzmumu_cf[6];
  string fname_zmumu[6];
  string zmumu_name;
  string zmumu_cf_name;
  cout << "Opening Z+jets" << endl;
  for(int i=0;i<6;i++){
    zmumu_name = "ZmumuNp"+ NumToStr(i) + "_hists";
    zmumu_cf_name = cutflow_h_path + zmumu_name + ".root";
    zmumu_name += file_suffix;
    fname_zmumu[i] = zmumu_name;
    zmumu_name = mc_path + zmumu_name;
    fzmumu[i] = TFile::Open(zmumu_name.c_str(),"UPDATE");
    fzmumu_cf[i] = TFile::Open(zmumu_cf_name.c_str(),"UPDATE");
  }

  //Zmumubb_NpX
  string mc_type_zmumubb = "Zmumubb_Np";
  const int n_files_zmumubb = 4;
  TFile *fzmumubb[4];
  TFile *fzmumubb_cf[4];
  string fname_zmumubb[4];
  string zmumubb_name;
  string zmumubb_cf_name;
  cout << "Opening Z+bjets" << endl;
  for(int i=0;i<4;i++){
    zmumubb_name = "ZmumubbNp" + NumToStr(i) + "_hists";
    zmumubb_cf_name = cutflow_h_path + zmumubb_name + ".root";
    zmumubb_name += file_suffix;
    fname_zmumubb[i] = zmumubb_name;
    zmumubb_name = mc_path + zmumubb_name;
    fzmumubb[i] = TFile::Open(zmumubb_name.c_str(),"UPDATE");
    fzmumubb_cf[i] = TFile::Open(zmumubb_cf_name.c_str(),"UPDATE");
  }

  //Zmumucc_NpX
  string mc_type_zmumucc = "Zmumucc_Np";
  const int n_files_zmumucc = 4;
  TFile *fzmumucc[4];
  TFile *fzmumucc_cf[4];
  string fname_zmumucc[4];
  string zmumucc_name;
  string zmumucc_cf_name;
  cout << "Opening Z+cjets" << endl;
  for(int i=0;i<4;i++){
    zmumucc_name = "ZmumuccNp" + NumToStr(i) + "_hists";
    zmumucc_cf_name = cutflow_h_path + zmumucc_name + ".root";
    zmumucc_name += file_suffix;
    fname_zmumucc[i] = zmumucc_name;
    zmumucc_name = mc_path + zmumucc_name;
    fzmumucc[i] = TFile::Open(zmumucc_name.c_str(),"UPDATE");
    fzmumucc_cf[i] = TFile::Open(zmumucc_cf_name.c_str(),"UPDATE");
  }

  //Ztautau_NpX
  string mc_type_ztautau = "Ztautau_Np";
  const int n_files_ztautau = 6;
  TFile *fztautau[6];
  TFile *fztautau_cf[6];
  string fname_ztautau[6];
  string ztautau_name;
  string ztautau_cf_name;
  cout << "opening Z->tautau" << endl;
  for(int i=0; i<6; i++){
    ztautau_name = "ZtautauNp" + NumToStr(i) + "_hists";
    ztautau_cf_name = cutflow_h_path + ztautau_name + ".root";
    ztautau_name += file_suffix;
    fname_ztautau[i] = ztautau_name;
    ztautau_name = mc_path + ztautau_name;
    fztautau[i] = TFile::Open(ztautau_name.c_str(),"UPDATE");
    fztautau_cf[i] = TFile::Open(ztautau_cf_name.c_str(),"UPDATE");
  }


  //Wmunu_NpX
  string mc_type_wmunu = "Wmunu_Np";
  const int n_files_wmunu = 6;
  TFile *fwmunu[6];
  TFile *fwmunu_cf[6];
  string fname_wmunu[6];
  string wmunu_name;
  string wmunu_cf_name;
  cout << "opening W+jets" << endl;
  for(int i=0; i<6; i++){
    wmunu_name = "WmunuNp" + NumToStr(i) + "_hists";
    wmunu_cf_name = cutflow_h_path + wmunu_name + ".root";
    wmunu_name += file_suffix;
    fname_wmunu[i] = wmunu_name;
    wmunu_name = mc_path + wmunu_name;
    fwmunu[i] = TFile::Open(wmunu_name.c_str(),"UPDATE");
    fwmunu_cf[i] = TFile::Open(wmunu_cf_name.c_str(),"UPDATE");
  }

  //Wcc_NpX
  string mc_type_wcc = "Wcc_Np";
  const int n_files_wcc = 4;
  TFile *fwcc[4];
  TFile *fwcc_cf[4];
  string fname_wcc[4];
  string wcc_name;
  string wcc_cf_name;
  cout << "Opening W+cc" << endl;
  for(int i=0; i<4; i++){
    wcc_name = "WccNp" + NumToStr(i) + "_hists";
    wcc_cf_name = cutflow_h_path + wcc_name + ".root";
    wcc_name += file_suffix;
    fname_wcc[i] = wcc_name;
    wcc_name = mc_path + wcc_name;
    fwcc[i] = TFile::Open(wcc_name.c_str(),"UPDATE");
    fwcc_cf[i] = TFile::Open(wcc_cf_name.c_str(),"UPDATE");
  }

  //Wc_NpX
  string mc_type_wc = "Wc_Np";
  const int n_files_wc= 5;
  TFile*fwc[5];
  TFile*fwc_cf[5];
  string fname_wc[5];
  string wc_name;
  string wc_cf_name;
  cout << "Opening W+c" << endl;
  for(int i=0; i<5; i++){
    wc_name = "WcNp" + NumToStr(i) + "_hists";
    wc_cf_name= cutflow_h_path + wc_name + ".root";
    wc_name += file_suffix;
    fname_wc[i] = wc_name;
    wc_name = mc_path + wc_name;
    fwc[i] = TFile::Open(wc_name.c_str(),"UPDATE");
    fwc_cf[i] = TFile::Open(wc_cf_name.c_str(),"UPDATE");
  }

  //Wbb_NpX
  string mc_type_wbb = "Wbb_Np";
  const int n_files_wbb= 4;
  TFile*fwbb[4];
  TFile*fwbb_cf[4];
  string fname_wbb[4];
  string wbb_name;
  string wbb_cf_name;
  cout << "Opening W+bb" << endl;
  for(int i=0; i<4; i++){
    wbb_name = "WbbNp" + NumToStr(i) + "_hists";
    wbb_cf_name= cutflow_h_path + wbb_name + ".root";
    wbb_name += file_suffix;
    fname_wbb[i] = wbb_name;
    wbb_name = mc_path + wbb_name;
    fwbb[i] = TFile::Open(wbb_name.c_str(),"UPDATE");
    fwbb_cf[i] = TFile::Open(wbb_cf_name.c_str(),"UPDATE");
  }

  //tt-bar
  string mc_type_ttbar = "ttbar";
  const int n_files_ttbar = 1;
  TFile *fttbar[1];
  TFile *fttbar_cf[1];
  string fname_ttbar[1];
  string ttbar_name = mc_type_ttbar + "_hists";
  string ttbar_cf_name = cutflow_h_path + ttbar_name + ".root";
  cout << "opening ttbar" << endl;
  ttbar_name += file_suffix;
  fname_ttbar[0] = ttbar_name;
  ttbar_name = mc_path + ttbar_name;
  fttbar[0] = TFile::Open(ttbar_name.c_str(),"UPDATE");
  fttbar_cf[0] = TFile::Open(ttbar_cf_name.c_str(),"UPDATE");

  /*  string mc_type_singletop = "singletop";
  const int n_files_singletop = 4;
  TFile *fsingletop[4];
  TFile *fsingletop_cf[4];
  string fname_singletop[4];
  string singletop_name;
  string singletop_cf_name;
  for(int i=0; i<4; i++){
    if(i==0) singletop_name = "tchanTopPythia_hists";
    else if(i==1) singletop_name = "tchanAntitopPythia_hists";
    else if(i==2) singletop_name = "schanLepPythia_hists";
    else if(i==3) singletop_name = "WtchanPythia_hists";
    singletop_cf_name = cutflow_h_path + singletop_name + ".root";
    singletop_name += file_suffix;
    fname_singletop[i] = singletop_name;
    singletop_name = mc_path + singletop_name;
    fsingletop[i] = TFile::Open(singletop_name.c_str(),"UPDATE");
    fsingletop_cf[i] = TFile::Open(singletop_cf_name.c_str(),"UPDATE");
    }*/

  string mc_type_tchan = "tchan";
  const int n_files_tchan = 2;
  TFile *ftchan[2];
  TFile *ftchan_cf[2];
  string fname_tchan[2];
  string tchan_name;
  string tchan_cf_name;
  cout << "opening singletop" << endl;
  for(int i=0; i<2; i++){
    if(i==0) tchan_name = "tchanTopPythia_hists";
    else if(i==1) tchan_name = "tchanAntitopPythia_hists";
    tchan_cf_name = cutflow_h_path + tchan_name + ".root";
    tchan_name += file_suffix;
    fname_tchan[i] = tchan_name;
    tchan_name = mc_path + tchan_name;
    ftchan[i] = TFile::Open(tchan_name.c_str(),"UPDATE");
    ftchan_cf[i] = TFile::Open(tchan_cf_name.c_str(),"UPDATE");
  }
 
  string mc_type_schan = "schan";
  const int n_files_schan = 1;
  TFile *fschan[1];
  TFile *fschan_cf[1];
  string fname_schan[1];
  string schan_name;
  string schan_cf_name;
  schan_name = "schanLepPythia_hists";
  schan_cf_name = cutflow_h_path + schan_name + ".root";
  schan_name += file_suffix;
  fname_schan[0] = schan_name;
  schan_name = mc_path + schan_name;
  fschan[0] = TFile::Open(schan_name.c_str(),"UPDATE");
  fschan_cf[0] = TFile::Open(schan_cf_name.c_str(),"UPDATE");

  string mc_type_Wtchan = "Wtchan";
  const int n_files_Wtchan = 1;
  TFile *fWtchan[1];
  TFile *fWtchan_cf[1];
  string fname_Wtchan[1];
  string Wtchan_name;
  string Wtchan_cf_name;
  Wtchan_name = "WtchanPythia_hists";
  Wtchan_cf_name = cutflow_h_path + Wtchan_name + ".root";
  Wtchan_name += file_suffix;
  fname_Wtchan[0] = Wtchan_name;
  Wtchan_name = mc_path + Wtchan_name;
  fWtchan[0] = TFile::Open(Wtchan_name.c_str(),"UPDATE");
  fWtchan_cf[0] = TFile::Open(Wtchan_cf_name.c_str(),"UPDATE");

  //Diboson
  /*
  string mc_type_diboson = "diboson";
  const int n_files_diboson = 6;
  TFile *fdiboson[6];
  TFile *fdiboson_cf[6];
  string fname_diboson[6];
  string diboson_name;
  string diboson_cf_name;
  //  WWtomunuqq(183736), WZtomunuqq(183737), ZWtomumuqq(183587), ZWtotautauqq(183589), ZZtomumuqq(183588), ZZtotautauqq(183590)
  for(int i=0; i<6; i++){
    if(i==0) diboson_name = "WWtomunuqq_hists";
    else if(i==1) diboson_name = "WZtomunuqq_hists";
    else if(i==2) diboson_name = "ZWtomumuqq_hists";
    else if(i==3) diboson_name = "ZWtotautauqq_hists";
    else if(i==4) diboson_name = "ZZtomumuqq_hists";
    else if(i==5) diboson_name = "ZZtotautauqq_hists";
    diboson_cf_name = cutflow_h_path + diboson_name + ".root";
    diboson_name += file_suffix;
    fname_diboson[i] = diboson_name;
    diboson_name = mc_path + diboson_name;
    fdiboson[i] = TFile::Open(diboson_name.c_str(),"UPDATE");
    fdiboson_cf[i] = TFile::Open(diboson_cf_name.c_str(),"UPDATE");
    }*/
  string mc_type_WW = "WW";
  const int n_files_WW = 1;
  TFile *fWW[1];
  TFile *fWW_cf[1];
  string fname_WW[1];
  string WW_name;
  string WW_cf_name;
  cout << "opening diboson" << endl;
  WW_name = "WWtomunuqq_hists";
  WW_cf_name = cutflow_h_path + WW_name + ".root";
  WW_name += file_suffix;
  fname_WW[0] = WW_name;
  WW_name = mc_path + WW_name;
  fWW[0] = TFile::Open(WW_name.c_str(),"UPDATE");
  fWW_cf[0] = TFile::Open(WW_cf_name.c_str(),"UPDATE");

  string mc_type_WZ = "WZ";
  const int n_files_WZ = 3;
  TFile *fWZ[3];
  TFile *fWZ_cf[3];
  string fname_WZ[3];
  string WZ_name;
  string WZ_cf_name;
  for(int i=0; i<3; i++){
    if(i==0) WZ_name = "WZtomunuqq_hists";
    else if(i==1) WZ_name = "ZWtomumuqq_hists";
    else if(i==2) WZ_name = "ZWtotautauqq_hists";
    WZ_cf_name = cutflow_h_path + WZ_name + ".root";
    WZ_name += file_suffix;
    fname_WZ[i] = WZ_name;
    WZ_name = mc_path + WZ_name;
    fWZ[i] = TFile::Open(WZ_name.c_str(),"UPDATE");
    fWZ_cf[i] = TFile::Open(WZ_cf_name.c_str(),"UPDATE");
  }

  string mc_type_ZZ = "ZZ";
  const int n_files_ZZ = 2;
  TFile *fZZ[2];
  TFile *fZZ_cf[2];
  string fname_ZZ[2];
  string ZZ_name;
  string ZZ_cf_name;
  for(int i=0; i<2; i++){
    if(i==0) ZZ_name = "ZZtomumuqq_hists";
    else if(i==1) ZZ_name = "ZZtotautauqq_hists";
    ZZ_cf_name = cutflow_h_path + ZZ_name + ".root";
    ZZ_name += file_suffix;
    fname_ZZ[i] = ZZ_name;
    ZZ_name = mc_path + ZZ_name;
    fZZ[i] = TFile::Open(ZZ_name.c_str(),"UPDATE");
    fZZ_cf[i] = TFile::Open(ZZ_cf_name.c_str(),"UPDATE");
  }



  //====================
  //===== Data =========
  //====================
  //My data
  string data_path = "/n/atlas02/user_codes/looper.6/Vbb/analysis_code/data_histograms/";
  if(isMJ){
    data_path = "/n/atlas02/user_codes/looper.6/Vbb/analysis_code/data_histograms_MJ/";
  }
  else if(isWide){
    data_path = "/n/atlas02/user_codes/looper.6/Vbb/analysis_code/data_histograms_wide/";
  }

  TFile *fdata;
  string data_name = data_path + "alldata";
  cout << "Opening data" << endl;
  if(isMJ) data_name += "_MJ.root";
  else if(isWide){
    if(isShort) data_name += "_short";
    data_name += "_wide.root";
  }
  else data_name += ".root";
  //string data_name = data_path + "periodH.root";
  if(var_2_plot == "bottom_jets_hmatch_up" || var_2_plot == "bottom_jets_hmatch_down"){histo_name = "mv1cweight_bottom_had_match";}
  if(!isTruth) fdata = TFile::Open(data_name.c_str(),"UPDATE");
  TH1D *h_data;
  if(!isTruth){
    h_data = (TH1D*)fdata->Get(histo_name);
    h_data->GetXaxis()->SetRangeUser(x_min,x_max);
  }

  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    ~~~~~~~~~~~~~~~ADD HISTOGRAMS~~~~~~~~~~~~~~~~~
    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

  //Add MC histograms by process: function add_histo is defined in header file
  //add_histo is overloaded to deal with TH1D and TH2D
  //Zmumu
  Histogram h_zmumu_sherpa_sum;
  if(include_sherpa){
    h_zmumu_sherpa_sum = add_histo(fzmumu_sherpa,n_files_zmumu_sherpa,fname_zmumu_sherpa,histo_name,zmumu_sherpa_xsec,fzmumu_sherpa_cf,lumi,zmumu_sherpa_process,x_min,x_max);
  }
  Histogram h_zmumu_sum     = add_histo(fzmumu,n_files_zmumu,fname_zmumu,histo_name,zmumu_xsec,fzmumu_cf,lumi,zmumu_process,x_min,x_max);
  cout << h_zmumu_sum.IntegralHist() << endl;
  Histogram h_zmumubb_sum   = add_histo(fzmumubb,n_files_zmumubb,fname_zmumubb,histo_name,zmumubb_xsec,fzmumubb_cf,lumi,zmumubb_process,x_min,x_max);
  cout << h_zmumubb_sum.IntegralHist() << endl;
  Histogram h_zmumucc_sum   = add_histo(fzmumucc,n_files_zmumucc,fname_zmumucc,histo_name,zmumucc_xsec,fzmumucc_cf,lumi,zmumucc_process,x_min,x_max);
  cout << h_zmumucc_sum.IntegralHist() << endl;
  Histogram h_ztautau_sum   = add_histo(fztautau,n_files_ztautau,fname_ztautau,histo_name,ztautau_xsec,fztautau_cf,lumi,ztautau_process,x_min,x_max);
  Histogram h_wmunu_sum     = add_histo(fwmunu,n_files_wmunu,fname_wmunu,histo_name,wmunu_xsec,fwmunu_cf,lumi,wmunu_process,x_min,x_max);
  Histogram h_wcc_sum       = add_histo(fwcc,n_files_wcc,fname_wcc,histo_name,wcc_xsec,fwcc_cf,lumi,wcc_process,x_min,x_max);
  Histogram h_wc_sum        = add_histo(fwc,n_files_wc,fname_wc,histo_name,wc_xsec,fwc_cf,lumi,wc_process,x_min,x_max);
  Histogram h_wbb_sum       = add_histo(fwbb,n_files_wbb,fname_wbb,histo_name,wbb_xsec,fwbb_cf,lumi,wbb_process,x_min,x_max);
  Histogram h_ttbar_sum     = add_histo(fttbar,n_files_ttbar,fname_ttbar,histo_name,ttbar_xsec,fttbar_cf,lumi,ttbar_process,x_min,x_max);
  Histogram h_tchan_sum     = add_histo(ftchan,n_files_tchan,fname_tchan,histo_name,tchan_xsec,ftchan_cf,lumi,tchan_process,x_min,x_max);
  Histogram h_schan_sum     = add_histo(fschan,n_files_schan,fname_schan,histo_name,schan_xsec,fschan_cf,lumi,schan_process,x_min,x_max);
  Histogram h_Wtchan_sum    = add_histo(fWtchan,n_files_Wtchan,fname_Wtchan,histo_name,Wtchan_xsec,fWtchan_cf,lumi,Wtchan_process,x_min,x_max);
  Histogram h_WW_sum        = add_histo(fWW,n_files_WW,fname_WW,histo_name,WW_xsec,fWW_cf,lumi,WW_process,x_min,x_max);
  Histogram h_WZ_sum        = add_histo(fWZ,n_files_WZ,fname_WZ,histo_name,WZ_xsec,fWZ_cf,lumi,WZ_process,x_min,x_max);
  Histogram h_ZZ_sum        = add_histo(fZZ,n_files_ZZ,fname_ZZ,histo_name,ZZ_xsec,fZZ_cf,lumi,ZZ_process,x_min,x_max); 


  Histogram h_zjets_sum = h_zmumu_sum.CloneHist();
  h_zjets_sum.AddHist(h_zmumubb_sum);
  h_zjets_sum.AddHist(h_zmumucc_sum);
  cout << "h_zjets: " << h_zjets_sum.IntegralHist() << endl;
  cout << "h_zmumu: " << h_zmumu_sum.IntegralHist() << endl;

  //  TH1D *h_wjets_sum = (TH1D*)h_wmunu_sum->Clone();
  Histogram h_wjets_sum = h_wmunu_sum.CloneHist();
  h_wjets_sum.AddHist(h_wcc_sum);
  h_wjets_sum.AddHist(h_wc_sum);
  h_wjets_sum.AddHist(h_wbb_sum);
  h_wjets_sum.SetName("wjets_sum");

  Histogram h_diboson_sum = h_WW_sum.CloneHist();
  h_diboson_sum.AddHist(h_WZ_sum);
  h_diboson_sum.AddHist(h_ZZ_sum);
  h_diboson_sum.SetName("diboson_sum");

  Histogram h_singletop_sum = h_tchan_sum.CloneHist();
  h_singletop_sum.AddHist(h_schan_sum);
  h_singletop_sum.AddHist(h_Wtchan_sum);

  h_zmumu_sum.SetFillColorHist(kYellow);
  h_zmumubb_sum.SetFillColorHist(kGreen);
  h_zmumucc_sum.SetFillColorHist(kRed);
  h_ztautau_sum.SetFillColorHist(kCyan);
  h_wjets_sum.SetFillColorHist(kAzure+3);
  h_ttbar_sum.SetFillColorHist(kViolet);
  h_singletop_sum.SetFillColorHist(kViolet-6);
  h_diboson_sum.SetFillColorHist(kOrange);

  gStyle->SetOptStat("");

  double zplusjets_sum = h_zmumu_sum.IntegralHist();
  cout << "zplusjets sum: " << zplusjets_sum << endl;
  zplusjets_sum += h_zmumubb_sum.IntegralHist();
  cout << "zplusjets sum: " << zplusjets_sum << endl;
  zplusjets_sum += h_zmumucc_sum.IntegralHist();
  cout << "zplusjets sum: " << zplusjets_sum << endl;

  double zplusjets_debug_sum = h_zjets_sum.IntegralHist();
  double zplusjets_debug_ratio = zplusjets_debug_sum/zplusjets_sum;
  double zplusjets_debug_dif  = zplusjets_debug_sum-zplusjets_sum;
  double dif_tolerence = 0.00001;
  if( ((1-dif_tolerence) < zplusjets_debug_ratio) && (zplusjets_debug_ratio < (1+dif_tolerence))) cout << "ok" << endl;
  else {
    cout << "SOMETHING IS WRONG" << endl;
    cout << zplusjets_debug_ratio << endl;
    cout << zplusjets_debug_dif << endl;
  }
  cout << "Z plus jets: " << zplusjets_sum << endl;
  cout << "Z plus jets combined: " << zplusjets_debug_sum << endl;

  double zplusjets_sherpa_sum;
  if(include_sherpa) zplusjets_sherpa_sum = h_zmumu_sherpa_sum.IntegralHist();

  cout.precision(9);
  cout << "Z->mumu + jets (Alpgen): " << zplusjets_sum << endl;
  if(include_sherpa)  cout << "Z->mumu + jets (Sherpa): " << zplusjets_sherpa_sum << endl;
  cout << "Z->tautau + jets: " << h_ztautau_sum.IntegralHist() << endl;
  cout << "W+jets: " << h_wjets_sum.IntegralHist() << endl;
  cout << "ttbar: " << h_ttbar_sum.IntegralHist() << endl;
  cout << "single top: " << h_singletop_sum.IntegralHist() << endl;
  cout << "diboson: " << h_diboson_sum.IntegralHist() << endl;

  /*****************************************
   ***********WRITE HISTS TO FILE *********
   ****************************************/

  string plt_path = "/n/atlas02/user_codes/looper.6/Vbb/analysis_plots/";
  string plt_dir; // final place plots will be written
  create_dir(plt_path,plt_dir);

  /******************************************
   **********Make Stack Plot***************
   ****************************************/
  string stack_name = string(histo_name.Data()) + "_stack";
  THStack *sum_stack = new THStack("stack","stack");

  if(rebin != 1){
    if(include_sherpa) h_zmumu_sherpa_sum.RebinHist(rebin);
    h_zmumu_sum.RebinHist(rebin);
    h_zmumubb_sum.RebinHist(rebin);
    h_zmumucc_sum.RebinHist(rebin);
    h_ztautau_sum.RebinHist(rebin);
    cout << "before rebinning, Wmunu bins  =" << h_wmunu_sum.GetSize() << endl;
    cout << "before rebinning, Wjets bins = " << h_wjets_sum.GetSize() << endl;
    h_wjets_sum.RebinHist(rebin);
    h_wmunu_sum.RebinHist(rebin);
    cout << "after rebinning, Wmunu bins = " << h_wmunu_sum.GetSize() << endl;
    cout << "after rebinning, Wjets bins = " << h_wjets_sum.GetSize() << endl;
    h_wcc_sum.RebinHist(rebin);
    h_wc_sum.RebinHist(rebin);
    h_wbb_sum.RebinHist(rebin);
    h_ttbar_sum.RebinHist(rebin);
    h_tchan_sum.RebinHist(rebin);
    h_schan_sum.RebinHist(rebin);
    h_Wtchan_sum.RebinHist(rebin);
    h_singletop_sum.RebinHist(rebin);
    h_WW_sum.RebinHist(rebin);
    h_WZ_sum.RebinHist(rebin);
    h_ZZ_sum.RebinHist(rebin);
    h_diboson_sum.RebinHist(rebin);
    if(!isTruth) h_data->Rebin(rebin);
  }
  if(include_sherpa) h_zmumu_sherpa_sum.SetXRangeHist(x_min,x_max);
  h_zmumu_sum.SetXRangeHist(x_min,x_max);
  h_zmumubb_sum.SetXRangeHist(x_min,x_max);
  h_zmumucc_sum.SetXRangeHist(x_min,x_max);
  h_zjets_sum.SetXRangeHist(x_min,x_max);
  h_ztautau_sum.SetXRangeHist(x_min,x_max);
  h_wjets_sum.SetXRangeHist(x_min,x_max);
  h_wmunu_sum.SetXRangeHist(x_min,x_max);
  h_wcc_sum.SetXRangeHist(x_min,x_max);
  h_wc_sum.SetXRangeHist(x_min,x_max);
  h_wbb_sum.SetXRangeHist(x_min,x_max);
  h_ttbar_sum.SetXRangeHist(x_min,x_max);
  h_singletop_sum.SetXRangeHist(x_min,x_max);
  h_tchan_sum.SetXRangeHist(x_min,x_max);
  h_schan_sum.SetXRangeHist(x_min,x_max);
  h_Wtchan_sum.SetXRangeHist(x_min,x_max);
  h_diboson_sum.SetXRangeHist(x_min,x_max);
  h_WW_sum.SetXRangeHist(x_min,x_max);
  h_WZ_sum.SetXRangeHist(x_min,x_max);
  h_ZZ_sum.SetXRangeHist(x_min,x_max);
  if(!isTruth) h_data->GetXaxis()->SetRangeUser(x_min,x_max);
  if(!(h_zmumu_sum.GetIs1D())){
    if(include_sherpa) h_zmumu_sherpa_sum.SetYRangeHist(y_min,y_max);
    h_zmumu_sum.SetYRangeHist(y_min,y_max);
    h_zmumubb_sum.SetYRangeHist(y_min,y_max);
    h_zmumucc_sum.SetYRangeHist(y_min,y_max);
    h_zjets_sum.SetYRangeHist(y_min,y_max);
    h_ztautau_sum.SetYRangeHist(y_min,y_max);
    h_wjets_sum.SetYRangeHist(y_min,y_max);
    h_wmunu_sum.SetYRangeHist(y_min,y_max);
    h_wcc_sum.SetYRangeHist(y_min,y_max);
    h_wc_sum.SetYRangeHist(y_min,y_max);
    h_wbb_sum.SetYRangeHist(y_min,y_max);
    h_ttbar_sum.SetYRangeHist(y_min,y_max);
    h_singletop_sum.SetYRangeHist(y_min,y_max);
    h_tchan_sum.SetYRangeHist(y_min,y_max);
    h_schan_sum.SetYRangeHist(y_min,y_max);
    h_Wtchan_sum.SetYRangeHist(y_min,y_max);
    h_diboson_sum.SetYRangeHist(y_min,y_max);
    h_WW_sum.SetYRangeHist(y_min,y_max);
    h_WZ_sum.SetYRangeHist(y_min,y_max);
    h_ZZ_sum.SetYRangeHist(y_min,y_max);
  }

  /*  TH1D *h_mc_sum = (TH1D*)h_zmumu_sum->Clone();
  TH1D *h_zmumu_sum_clone = (TH1D*)h_zmumu_sum->Clone();
  TH1D *h_zmumubb_sum_clone = (TH1D*)h_zmumubb_sum->Clone();
  TH1D *h_ztautau_sum_clone = (TH1D*)h_ztautau_sum->Clone();
  TH1D *h_wjets_sum_clone = (TH1D*)h_wjets_sum->Clone();
  TH1D *h_zmumucc_sum_clone = (TH1D*)h_zmumucc_sum->Clone();
  TH1D *h_ttbar_sum_clone = (TH1D*)h_ttbar_sum->Clone();
  TH1D *h_singletop_sum_clone = (TH1D*)h_singletop_sum->Clone();
  TH1D *h_diboson_sum_clone = (TH1D*)h_diboson_sum->Clone();*/


  Histogram h_mc_sum = h_zmumu_sum.CloneHist();
  Histogram h_zmumu_sum_clone = h_zmumu_sum.CloneHist();
  Histogram h_zmumubb_sum_clone = h_zmumubb_sum.CloneHist();
  Histogram h_ztautau_sum_clone = h_ztautau_sum.CloneHist();
  Histogram h_wjets_sum_clone = h_wjets_sum.CloneHist();
  Histogram h_zmumucc_sum_clone = h_zmumucc_sum.CloneHist();
  Histogram h_ttbar_sum_clone = h_ttbar_sum.CloneHist();
  Histogram h_singletop_sum_clone = h_singletop_sum.CloneHist();
  Histogram h_diboson_sum_clone = h_diboson_sum.CloneHist();
  

  //sherpa comparison clones: cloning two, electric boogaloo
  
  Histogram h_mc_sherpa_sum;
  Histogram h_ztautau_sherpa_sum_clone;
  Histogram h_wjets_sherpa_sum_clone;
  Histogram h_ttbar_sherpa_sum_clone;
  Histogram h_singletop_sherpa_sum_clone;
  Histogram h_diboson_sherpa_sum_clone;
  
  if(include_sherpa){
    h_mc_sherpa_sum = h_zmumu_sherpa_sum.CloneHist();
    h_ztautau_sherpa_sum_clone = h_ztautau_sum.CloneHist();
    h_wjets_sherpa_sum_clone = h_wjets_sum.CloneHist();
    h_ttbar_sherpa_sum_clone = h_ttbar_sum.CloneHist();
    h_singletop_sherpa_sum_clone = h_singletop_sum.CloneHist();
    h_diboson_sherpa_sum_clone = h_diboson_sum.CloneHist();
  }

  h_mc_sum.AddHist(h_zmumubb_sum_clone);
  h_mc_sum.AddHist(h_zmumucc_sum_clone);
  h_mc_sum.AddHist(h_ztautau_sum_clone);
  h_mc_sum.AddHist(h_wjets_sum_clone);
  h_mc_sum.AddHist(h_ttbar_sum_clone);
  h_mc_sum.AddHist(h_singletop_sum_clone);
  h_mc_sum.AddHist(h_diboson_sum_clone);


  if(include_sherpa){
    h_mc_sherpa_sum.AddHist(h_ztautau_sherpa_sum_clone);
    h_mc_sherpa_sum.AddHist(h_wjets_sherpa_sum_clone);
    h_mc_sherpa_sum.AddHist(h_ttbar_sherpa_sum_clone);
    h_mc_sherpa_sum.AddHist(h_singletop_sherpa_sum_clone);
    h_mc_sherpa_sum.AddHist(h_diboson_sherpa_sum_clone);
  }

  
  //  TH1D *h_mc_sum_clone =(TH1D*)h_mc_sum->Clone();
  // TH1D *h_mc_sherpa_sum_clone;
  Histogram h_mc_sum_clone;
  Histogram h_mc_sherpa_sum_clone;
  h_mc_sum_clone = h_mc_sum.CloneHist();
  if(include_sherpa) h_mc_sherpa_sum_clone = h_mc_sherpa_sum.CloneHist();
  if(!scale_to_lumi && !isTruth){
    cout << "ENTERED INTO NORMALIZING TO DATA BLOCK" << endl;
    h_mc_sum_clone.ScaleHist(h_data->Integral()/h_mc_sum.IntegralHist());
    cout << "Normalization ratio: " << h_data->Integral()/h_mc_sum.IntegralHist() << endl;
    h_singletop_sum_clone.ScaleHist(h_data->Integral()/h_mc_sum.IntegralHist());
    h_ttbar_sum_clone.ScaleHist(h_data->Integral()/h_mc_sum.IntegralHist());
    h_diboson_sum_clone.ScaleHist(h_data->Integral()/h_mc_sum.IntegralHist());
    h_ztautau_sum_clone.ScaleHist(h_data->Integral()/h_mc_sum.IntegralHist());
    h_wjets_sum_clone.ScaleHist(h_data->Integral()/h_mc_sum.IntegralHist());
    h_zmumucc_sum_clone.ScaleHist(h_data->Integral()/h_mc_sum.IntegralHist());
    h_zmumu_sum_clone.ScaleHist(h_data->Integral()/h_mc_sum.IntegralHist());
    h_zmumubb_sum_clone.ScaleHist(h_data->Integral()/h_mc_sum.IntegralHist());

    if(include_sherpa){
      h_mc_sherpa_sum_clone.ScaleHist(h_data->Integral()/h_mc_sherpa_sum.IntegralHist());
      cout << "Normalization ratio (sherpa): " << h_data->Integral()/h_mc_sherpa_sum.IntegralHist() << endl;
      h_ztautau_sherpa_sum_clone.ScaleHist(h_data->Integral()/h_mc_sherpa_sum.IntegralHist());
      h_wjets_sherpa_sum_clone.ScaleHist(h_data->Integral()/h_mc_sherpa_sum.IntegralHist());
      h_ttbar_sherpa_sum_clone.ScaleHist(h_data->Integral()/h_mc_sherpa_sum.IntegralHist());
      h_singletop_sherpa_sum_clone.ScaleHist(h_data->Integral()/h_mc_sherpa_sum.IntegralHist());
      h_diboson_sherpa_sum_clone.ScaleHist(h_data->Integral()/h_mc_sherpa_sum.IntegralHist());
    }
  }
  //Stack for Alpgen samples (no sherpa stack)
  sum_stack->Add(h_singletop_sum_clone.GetHist());
  sum_stack->Add(h_ttbar_sum_clone.GetHist());
  sum_stack->Add(h_diboson_sum_clone.GetHist());
  sum_stack->Add(h_ztautau_sum_clone.GetHist());
  sum_stack->Add(h_wjets_sum_clone.GetHist());
  sum_stack->Add(h_zmumucc_sum_clone.GetHist());
  sum_stack->Add(h_zmumu_sum_clone.GetHist());
  sum_stack->Add(h_zmumubb_sum_clone.GetHist());


  float mc_events = h_mc_sum.IntegralHist();
  cout << "MC sum: " << mc_events << endl;
  float mc_events_sherpa;
  if(include_sherpa){
    mc_events_sherpa = h_mc_sherpa_sum.IntegralHist();
    cout << "MC sum (sherpa): " << mc_events_sherpa << endl;
  }
  float data_events;
  if(!isTruth){
    data_events = h_data->Integral();
    cout << "Data sum: " << data_events << endl;
  }

  float data_minus_background;
  if(!isTruth){
    data_minus_background = data_events;
    data_minus_background -= h_ztautau_sum.IntegralHist();
    data_minus_background -= h_wjets_sum.IntegralHist();
    data_minus_background -= h_ttbar_sum.IntegralHist();
    data_minus_background -= h_singletop_sum.IntegralHist();
    data_minus_background -= h_diboson_sum.IntegralHist();
  
    cout << "Data minus background (Z+jets): " << data_minus_background << endl;
  }

  float percent_difference;
  float percentage_difference_sherpa;
  float ratio;
  float ratio_sherpa;

  if(!isTruth){
    percent_difference = (data_events-mc_events)/data_events;
    cout << "Percentage difference: " << percent_difference << endl;
    percentage_difference_sherpa;
    if(include_sherpa){
      percentage_difference_sherpa = (data_events-mc_events_sherpa)/data_events;
      cout << "Percentage difference (sherpa): " << percentage_difference_sherpa << endl;
    }
    ratio = (data_events)/(mc_events);
    cout << "Ratio (Data/MC): " << ratio << endl;
    if(include_sherpa){
      ratio_sherpa = (data_events)/(mc_events_sherpa);
      cout << "Ratio (sherpa): " << ratio_sherpa << endl;
    }
  }

  //
  h_wmunu_sum.SetName("wmunu_sum");
  h_wcc_sum.SetName("wcc_sum");
  h_wbb_sum.SetName("wbb_sum");
  h_wc_sum.SetName("wc_sum");
  h_zjets_sum.SetName("zjets_sum");
  h_wjets_sum.SetName("wjets_sum");
  h_WW_sum.SetName("WW_sum");
  h_WZ_sum.SetName("WZ_sum");
  h_ZZ_sum.SetName("ZZ_sum");
  //Save histograms separated by channel for unfolding code
  const int n_samples = 10;
  Histogram sample_h[] = {h_zjets_sum,h_ztautau_sum,h_wjets_sum,h_ttbar_sum,h_tchan_sum,h_schan_sum,h_Wtchan_sum,h_WW_sum, h_WZ_sum, h_ZZ_sum};
  string unfolding_name = "unfolding_preprocessed/"+var_2_plot;
  if(isShort) unfolding_name += "_short";
  unfolding_name += ".root";
  TFile *f_unfolding = TFile::Open(unfolding_name.c_str(),"RECREATE");
  for(int i = 0; i<n_samples; i++){
    sample_h[i].GetHist()->Write();
  }
  if(!isTruth){
    h_data->SetName("data");
    h_data->Write();
  }
  if(include_sherpa){
    h_zmumu_sherpa_sum.SetName("zjets_sherpa_sum");
    h_zmumu_sherpa_sum.GetHist()->Write();
  }
  f_unfolding->Close();

  //Write mc_sum as root file for further manipulation (like fitting)
  string rootfile_name = "MC_histograms_root/"+var_2_plot;
  if(isMJ) rootfile_name += "_ctrlregion.root";
  else if(isWide) {
    if(isShort) rootfile_name += "_small";
    rootfile_name += "_wide.root";
  }
  else rootfile_name += ".root";
  TFile * f_root = TFile::Open(rootfile_name.c_str(),"RECREATE");
  string mc_hist_name = var_2_plot+"_mc";
  string data_hist_name = var_2_plot+"_data";
  string mc_sherpa_hist_name = var_2_plot+"_sherpa";
  h_mc_sum.SetName(mc_hist_name.c_str());
  if(!isTruth)  h_data->SetName(data_hist_name.c_str());
  if(include_sherpa){
    h_mc_sherpa_sum.SetName(mc_sherpa_hist_name.c_str());
    h_mc_sherpa_sum.GetHist()->Write();
  }
  h_mc_sum.GetHist()->Write();
  if(!isTruth) h_data->Write();
  f_root->Close();

  /**************************************
   ********DRAW SUMMED HISTS************
   **********************************/
  string canvas_name = var_2_plot + "canvas";
  TCanvas *c1 = new TCanvas(canvas_name.c_str(),canvas_name.c_str(),800,800);

  if(make_log){
    sum_stack->SetMaximum(y_max);
    sum_stack->SetMinimum(y_min);
    if(include_sherpa){
      h_mc_sherpa_sum.SetMaxHist(y_max);
      h_mc_sherpa_sum.SetMinHist(y_min);
    }
 }
  else{
    sum_stack->SetMaximum(y_max);
    sum_stack->SetMinimum(y_min);
    if(include_sherpa){
      h_mc_sherpa_sum.SetMaxHist(y_max);
      h_mc_sherpa_sum.SetMinHist(y_min);
    }
  }


  //draw mc and data and make ratio plot
  TPad *pad1;// = new TPad("pad1","pad1",0,0.3,1,1);
  if(!isTruth) pad1 = new TPad("pad1","pad1",0,0.3,1,1);
  else pad1 = new TPad("pad1","pad1",0,0,1,1);
  if(make_log){
    pad1->SetLogy();
  }
  pad1->SetTopMargin(0.05);
  if(!isTruth)pad1->SetBottomMargin(0);
  else pad1->SetBottomMargin(0.15);
  pad1->SetRightMargin(0.05);
  pad1->SetLeftMargin(0.16);
  pad1->SetFillStyle(4000);
  pad1->Draw("9");
  pad1->cd();

  if(include_sherpa){
    h_mc_sherpa_sum.SetLineStyleHist(2);
    h_mc_sherpa_sum.SetLineColorHist(2);
    h_mc_sherpa_sum.SetLineWidthHist(2);
  }

  
  sum_stack->Draw("HIST");
  if(!isTruth)sum_stack->GetXaxis()->SetNdivisions(000);
  if(include_sherpa) h_mc_sherpa_sum.GetHist()->Draw("HIST SAME");
  if(!isTruth) h_data->Draw("HIST ELP SAME");
  sum_stack->GetXaxis()->SetRangeUser(x_min,x_max);
  if(var_2_plot == "n_jets" || var_2_plot == "n_bjets"){
    sum_stack->GetXaxis()->CenterTitle();
  }
  sum_stack->GetYaxis()->SetTitle(y_name);
  if(isTruth) sum_stack->GetXaxis()->SetTitle(x_name);
  c1->Modified();

  c1->cd();
  TPad *pad2;//= new TPad("pad2","pad2",0,0,1,0.3);
  if(!isTruth){
    if(!isTruth) pad2 = new TPad("pad2","pad2",0,0,1,0.3);
    pad2->SetTopMargin(0);
    pad2->SetBottomMargin(0.48);
    pad2->SetRightMargin(0.05);
    pad2->SetLeftMargin(0.16);
    pad2->SetFillStyle(4000);
    pad2->SetGridx();
    pad2->SetGridy();
    pad2->Draw("9");
    pad2->cd();

    TH1D * h_mc_sum_clone_h = (TH1D*)h_mc_sum_clone.GetHist();
    TH1D * h_mc_sherpa_sum_clone_h;
    h_mc_sum_clone_h->SetStats(0);
    h_mc_sum_clone_h->SetMarkerSize(0.5);
    h_mc_sum_clone_h->GetYaxis()->SetTickLength(0.04);
    h_mc_sum_clone_h->GetYaxis()->SetNdivisions(505);
    h_mc_sum_clone_h->GetXaxis()->SetLabelSize(0.04*3./1.);
    h_mc_sum_clone_h->GetXaxis()->SetTitleSize(0.04*3./1.);
    h_mc_sum_clone_h->GetYaxis()->SetLabelSize(0.04*3./1.);
    h_mc_sum_clone_h->GetYaxis()->SetTitleSize(0.04*3./1.);
    h_mc_sum_clone_h->GetXaxis()->SetTitleOffset(1.2);
    h_mc_sum_clone_h->GetYaxis()->SetTitleOffset(1.2/2.);
    h_mc_sum_clone_h->GetXaxis()->SetTitle("");
    
    h_mc_sum_clone_h->GetYaxis()->SetTitle("Data/MC");
    //h_mc_sum_clone_h->GetYaxis()->SetTitle("MC/Data");
    h_mc_sum_clone_h->SetLineColor(kBlack);
    h_mc_sum_clone_h->Divide(h_data,h_mc_sum_clone_h);

    h_mc_sum_clone_h->SetMinimum(ratiomin);
    h_mc_sum_clone_h->SetMaximum(ratiomax);
 
    h_mc_sum_clone_h->SetMarkerStyle(20);
    h_mc_sum_clone_h->SetXTitle(x_name);
    h_mc_sum_clone_h->Draw("ep");

    if(include_sherpa){
      h_mc_sherpa_sum_clone_h =(TH1D*)h_mc_sherpa_sum_clone.GetHist();
      h_mc_sherpa_sum_clone_h->SetMinimum(ratiomin);
      h_mc_sherpa_sum_clone_h->SetMaximum(ratiomax);
      h_mc_sherpa_sum_clone_h->SetMarkerSize(0.5);
      h_mc_sherpa_sum_clone_h->SetMarkerColor(kRed);
      h_mc_sherpa_sum_clone_h->SetLineColor(kRed);
      h_mc_sherpa_sum_clone_h->Divide(h_data,h_mc_sherpa_sum_clone_h);
      h_mc_sherpa_sum_clone_h->SetMarkerStyle(20);
      h_mc_sherpa_sum_clone_h->Draw("ep same");
    }
    TLegend *ratiolegend = new TLegend(0.3,0.84,0.65,0.97);
    ratiolegend->SetFillStyle(0);
    ratiolegend->SetTextSize(0.07);
    ratiolegend->SetBorderSize(0);
    ratiolegend->SetNColumns(2);
    ratiolegend->AddEntry(h_mc_sum_clone_h,"Alpgen","lp");
    if(include_sherpa) ratiolegend->AddEntry(h_mc_sherpa_sum_clone_h,"Sherpa","lp");
    ratiolegend->Draw();
  }
  pad1->cd();
    

  TLegend *legend = new TLegend(0.6,0.64,0.95,0.95);
  legend->SetTextSize(0.03);
  if(!isTruth) legend->AddEntry(h_data,"Data","lp");
  if(include_sherpa) legend->AddEntry(h_mc_sherpa_sum.GetHist(),"Sherpa MC","l");
  legend->AddEntry(h_zmumubb_sum_clone.GetHist(),"Z(#rightarrow#mu#mu)+bb+jets MC","f");
  legend->AddEntry(h_zmumu_sum_clone.GetHist(),"Z(#rightarrow#mu#mu)+jets MC","f");
  legend->AddEntry(h_zmumucc_sum_clone.GetHist(),"Z(#rightarrow#mu#mu)+cc+jets MC","f");
  legend->AddEntry(h_ztautau_sum_clone.GetHist(),"Z#rightarrow#tau#tau+jets MC","f");
  legend->AddEntry(h_wjets_sum_clone.GetHist(),"W+jets MC","f");
  legend->AddEntry(h_diboson_sum_clone.GetHist(),"Diboson MC","f");
  legend->AddEntry(h_ttbar_sum_clone.GetHist(),"tt-bar MC","f");
  legend->AddEntry(h_singletop_sum_clone.GetHist(), "single-top MC","f");

  legend->Draw();

  TLatex *tex1 = new TLatex();
  tex1->SetNDC();
  string mc_evt_label = "#font[18]{MC events: " + NumToStr(mc_events) + "}";
  //  tex1->DrawLatex(0.19,0.9-0.03,mc_evt_label.c_str());

  TLatex *tex2 = new TLatex();
  tex2->SetNDC();
  string data_evt_label;
  if(!isTruth) data_evt_label = "#font[18]{Data events: " + NumToStr(data_events) + "}";
  //  tex2->DrawLatex(0.19,0.9-0.001,data_evt_label.c_str());

  c1->cd();
  c1->Update();

  //TImage *img = TImage::Create();
  //img->FromPad(c1);
  string img_name = plt_dir + "/" + var_2_plot;
  if(isMJ) img_name += "_MJ";
  if(isShort) img_name += "_small";
  else if(isWide){
    img_name += "_wide";
  }
  if(!include_sherpa) img_name += "_nosherpa";
  if(make_log){
    img_name += ".pdf";
  }
  else{
    img_name += "nolog.pdf";
  }
  //  img->WriteImage(img_name.c_str());
  c1->SaveAs(img_name.c_str());

  //Test block for Histogram class

  //Close files
  if(include_sherpa){
    close_files(fzmumu_sherpa, 1);
    close_files(fzmumu_sherpa_cf, 1);
  }
  close_files(fzmumu, 6);
  close_files(fzmumu_cf, 6);
  close_files(fzmumubb, 4);
  close_files(fzmumubb_cf, 4);
  close_files(fzmumucc, 4);
  close_files(fzmumucc_cf, 4);
  close_files(fztautau, 6);
  close_files(fztautau_cf, 6);
  close_files(fwmunu, 6);
  close_files(fwmunu_cf, 6);
  close_files(fwc, 5);
  close_files(fwc_cf, 5);
  close_files(fwcc, 4);
  close_files(fwcc_cf, 4);
  close_files(fwbb, 4);
  close_files(fwbb_cf, 4);
  close_files(fttbar, 1);
  close_files(fttbar_cf, 1);
  close_files(ftchan,2);
  close_files(ftchan_cf,2);
  close_files(fschan,1);
  close_files(fschan_cf,1);
  close_files(fWtchan,1);
  close_files(fWtchan_cf,1);
  close_files(fWW,1);
  close_files(fWW_cf,1);
  close_files(fWZ,3);
  close_files(fWZ_cf,3);
  close_files(fZZ,2);
  close_files(fZZ_cf,2);

  if(!isTruth) fdata->Close();

}

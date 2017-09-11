///////////////macro for plotting Z+bb results //////////////
/*
Created by: K. Looper (2 Oct 2015)
Last edited: 10 Dec 2015
Last edited by: K. Looper
Note: support for Evelin's code removed 5 Nov. See backup code to run on that.
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


void analysis_plots(string var_2_plot,bool scale_to_lumi, bool make_log, bool include_sherpa, bool isMJ=false, bool isWide=false){

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
  else if(var_2_plot == "Z_mass"){
    if(!isMJ && !isWide){
      chooseHistOptions("Z_mass","m_{#mu#mu} [GeV]","Events/GeV", 75, 107, 1, 1000000000, 2, 0.7, 1.5);
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
      chooseHistOptions("Z_mass_MET", "m_{#mu#mu} [GeV]","Events/GeV", 75, 107, 1, 1000000000, 2, 0.7, 1.5);
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
    chooseHistOptions("Z_y", "Z rapidity", "Events/0.1", -3.5, 3.5, 1, logmax, 2, ratiomin, ratiomax);
  }
  else if(var_2_plot == "Z_eta"){
    if(make_log) logmax = 1000000000;
    chooseHistOptions("Z_eta", "Z pseudorapidity", "Events/0.1", -6., 6., 1, logmax, 2, ratiomin, ratiomax);
  }
  else if(var_2_plot == "Z_phi"){
    chooseHistOptions("Z_phi", "#phi^{Z}", "Events/0.1", -TMath::Pi()-.5, TMath::Pi()+.5, 1, 100000000, 1, ratiomin, ratiomax);
  }
  else if(var_2_plot == "Z_pt"){
    chooseHistOptions("Z_pT","Z p_{T}", "Events/50 GeV", 0., 800., 1, 100000000, 100, ratiomin, ratiomax);
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
    chooseHistOptions("jet_pt_lead_tighteta","leading jet pT [GeV]", "Events/10 GeV", 0., 500., 1, 10000000,20, ratiomin, ratiomax);
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
  else if(var_2_plot == "lead_jet_pt_tightmet"){
    chooseHistOptions("jet_pt_lead_tighteta_MET","leading jet pT [GeV]", "Events/10 GeV", 0., 500., 1, 10000000,20, ratiomin, ratiomax);
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
  else if(var_2_plot == "light_jets"){
    chooseHistOptions("mv1cweight_light","mv1c weight", "Events",0,1,1,100000000, 1, ratiomin, ratiomax);
  }
  else if(var_2_plot == "charm_jets"){
    chooseHistOptions("mv1cweight_charm","mv1c weight", "Events",0,1,1,100000000, 1, ratiomin, ratiomax);
  }
  else if(var_2_plot == "bottom_jets"){
    chooseHistOptions("mv1cweight_bottom","mv1c weight", "Events",0,1,1,100000000, 1, ratiomin, ratiomax);
  }
  else if(var_2_plot == "light_jets_hmatch"){
    chooseHistOptions("mv1cweight_light_had_match","mv1c weight", "Events",0,1,1,100000000, 1, ratiomin, ratiomax);
  }
  else if(var_2_plot == "charm_jets_hmatch"){
    chooseHistOptions("mv1cweight_charm_had_match","mv1c weight", "Events",0,1,1,100000000, 1, ratiomin, ratiomax);
  }
  else if(var_2_plot == "bottom_jets_hmatch"){
    chooseHistOptions("mv1cweight_bottom_had_match","mv1c weight", "Events",0,1,1,100000000, 1, ratiomin, ratiomax);
  }
  else if(var_2_plot == "bottom_jets_hmatch_up"){
    chooseHistOptions("mv1cweight_bottom_had_match_up","mv1c weight", "Events",0,1,1,100000000, 1, ratiomin, ratiomax);
  }
  else if(var_2_plot =="bottom_jets_hmatch_down"){
    chooseHistOptions("mv1cweight_bottom_had_match_down","mv1c weight", "Events",0,1,1,100000000, 1, ratiomin, ratiomax);
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
  /*~~~~~~~~~~~~~~~~~~single top~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  //datasets 117361, 108346, 108344 (AcerMCPythia, MC@NLOJimmy
  //x-section source: AMI
  //k-factor source:  https://twiki.cern.ch/twiki/bin/viewauth/AtlasProtected/TopMC12SingleTopSamples
  /*
  string singletop_process = "singletop";
  vector<double> singletop_xsec;
  double sigma_singletop[3] = {8.5889, 20.666,0.56430};
  double k_factor_singletop[3] = {1.1035,1.0736,1.0737};
  double eff_singletop = 1.0;
  for(int i=0; i<3; i++){
    xsec = sigma_singletop[i]*k_factor_singletop[i]*eff_singletop;
    singletop_xsec.push_back(xsec);
  }
  */
  /*~~~~~~~~~~~~~~~new single top~~~~~~~~~~~~~~~~~~~~~~~*/
  //datasets 110090, 110091, 110119, 110140 (Powheg+Pythia)
  //x-section source: arantxa's note (double-check)
  //k-factor source: arantxa's note (double-check)
  string singletop_process = "singletop";
  vector<double> singletop_xsec;
  double sigma_singletop[4] = {17.520,9.3932,1.642400,20.46100};
  double k_factor_singletop[4] = {1.0500,1.0616,1.106700,1.093300};
  double eff_singletop = 1.0;
  for(int i=0; i<4; i++){
    xsec = sigma_singletop[i]*k_factor_singletop[i]*eff_singletop;
    singletop_xsec.push_back(xsec);
  }
  
  /*~~~~~~~~~~~~~~~~~~~~~~~~di-boson~~~~~~~~~~~~~~~~~~~~~*/
  //datasets: 105986(ZZ), 105985(WW), 105987 (WZ)
  //x-section source: ami (top group information looks incorrect)
  /*
  string diboson_process = "diboson";
  vector<double> diboson_xsec;
  //order of cross-sections: WW, ZZ, WZ
  double sigma_diboson[3] = {32.501, 4.9614, 12.008};
  double k_factor_diboson[3] = {1.6833, 1.5496, 1.9011};
  double eff_diboson[3] ={0.38203,0.24465,0.30546};
  for(int i=0; i<3; i++){
    xsec = sigma_diboson[i]*k_factor_diboson[i]*eff_diboson[i];
    diboson_xsec.push_back(xsec);
  } 
  */
  //datasets: WWtomunuqq(183736), WZtomunuqq(183737), ZWtomumuqq(183587), ZWtotautauqq(183589), ZZtomumuqq(183588), ZZtotautauqq(183590)
  string diboson_process = "diboson";
  vector<double> diboson_xsec;
  double sigma_diboson[6] = {7.2854,1.9057,1.4637,1.4523,0.24747,0.24167};
  double k_factor_diboson[6] = {1.05,1.05,1.05,1.05,1.,1.};
  double eff_diboson = 1.0;
  for(int i=0; i<6; i++){
    xsec = sigma_diboson[i]*k_factor_diboson[i]*eff_diboson;
    diboson_xsec.push_back(xsec);
  }
  

  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    ~~~~~~~~~~~OPEN FILES~~~~~~~~~~~~~~~~~~~~~~~~~~
    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  //====================
  //== Monte Carlo =====
  //====================
  string cutflow_h_path = "/n/atlas02/user_codes/looper.6/Vbb/hfor_histograms_new/";
  //string mc_path = "/n/atlas02/user_codes/looper.6/Vbb/analysis_code/MC_histograms/";
  string mc_path = "/n/atlas02/user_codes/looper.6/Vbb/old_histograms/old_MC_histograms/MC_histograms_Aug24/";
  //  string mc_path = "/n/atlas02/user_codes/looper.6/Vbb/analysis_code/../old_histograms/old_MC_histograms/MC_histograms_Oct13/";
  //  string mc_path = "/n/atlas02/user_codes/looper.6/Vbb/analysis_code/hfor_histograms/";
  //  string mc_path = "/n/atlas02/user_codes/looper.6/Vbb/analysis_code/MC_debug/";
  //  string mc_path = "/n/atlas02/user_codes/looper.6/Vbb/analysis_code/MC_histograms_arantxa/";

  //Sherpa Zmumu

  string file_suffix;
  if(isMJ) file_suffix = "_MJ.root";
  else if(isWide) file_suffix = "_wide.root";
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
    fzmumu_sherpa[0] = TFile::Open(zmumu_sherpa_name.c_str(),"UPDATE");
    fzmumu_sherpa_cf[0] = TFile::Open(zmumu_sherpa_cf_name.c_str(),"UPDATE");
  }
  TH1D *h_zmumu_sherpa_array[1];

  //Zmumu_NpX
  string mc_type_zmumu = "Zmumu_Np";
  const int n_files_zmumu = 6;
  TFile * fzmumu[6];
  TFile * fzmumu_cf[6];
  string fname_zmumu[6];
  string zmumu_name;
  string zmumu_cf_name;
  for(int i=0;i<6;i++){
    zmumu_name = "ZmumuNp"+ NumToStr(i) + "_hists";
    zmumu_cf_name = cutflow_h_path + zmumu_name + ".root";
    zmumu_name += file_suffix;
    fname_zmumu[i] = zmumu_name;
    zmumu_name = mc_path + zmumu_name;
    fzmumu[i] = TFile::Open(zmumu_name.c_str(),"UPDATE");
    fzmumu_cf[i] = TFile::Open(zmumu_cf_name.c_str(),"UPDATE");
  }
  TH1D * h_zmumu_array[6];

  //Zmumubb_NpX
  string mc_type_zmumubb = "Zmumubb_Np";
  const int n_files_zmumubb = 4;
  TFile *fzmumubb[4];
  TFile *fzmumubb_cf[4];
  string fname_zmumubb[4];
  string zmumubb_name;
  string zmumubb_cf_name;
  for(int i=0;i<4;i++){
    zmumubb_name = "ZmumubbNp" + NumToStr(i) + "_hists";
    zmumubb_cf_name = cutflow_h_path + zmumubb_name + ".root";
    zmumubb_name += file_suffix;
    fname_zmumubb[i] = zmumubb_name;
    zmumubb_name = mc_path + zmumubb_name;
    fzmumubb[i] = TFile::Open(zmumubb_name.c_str(),"UPDATE");
    fzmumubb_cf[i] = TFile::Open(zmumubb_cf_name.c_str(),"UPDATE");
  }
  TH1D * h_zmumubb_array[4];

  //Zmumucc_NpX
  string mc_type_zmumucc = "Zmumucc_Np";
  const int n_files_zmumucc = 4;
  TFile *fzmumucc[4];
  TFile *fzmumucc_cf[4];
  string fname_zmumucc[4];
  string zmumucc_name;
  string zmumucc_cf_name;
  for(int i=0;i<4;i++){
    zmumucc_name = "ZmumuccNp" + NumToStr(i) + "_hists";
    zmumucc_cf_name = cutflow_h_path + zmumucc_name + ".root";
    zmumucc_name += file_suffix;
    fname_zmumucc[i] = zmumucc_name;
    zmumucc_name = mc_path + zmumucc_name;
    fzmumucc[i] = TFile::Open(zmumucc_name.c_str(),"UPDATE");
    fzmumucc_cf[i] = TFile::Open(zmumucc_cf_name.c_str(),"UPDATE");
  }
  TH1D * h_zmumucc_array[4];

  //Ztautau_NpX
  string mc_type_ztautau = "Ztautau_Np";
  const int n_files_ztautau = 6;
  TFile *fztautau[6];
  TFile *fztautau_cf[6];
  string fname_ztautau[6];
  string ztautau_name;
  string ztautau_cf_name;
  for(int i=0; i<6; i++){
    ztautau_name = "ZtautauNp" + NumToStr(i) + "_hists";
    ztautau_cf_name = cutflow_h_path + ztautau_name + ".root";
    ztautau_name += file_suffix;
    fname_ztautau[i] = ztautau_name;
    ztautau_name = mc_path + ztautau_name;
    fztautau[i] = TFile::Open(ztautau_name.c_str(),"UPDATE");
    fztautau_cf[i] = TFile::Open(ztautau_cf_name.c_str(),"UPDATE");
  }
  TH1D *h_ztautau_array[6];

  //Wmunu_NpX
  string mc_type_wmunu = "Wmunu_Np";
  const int n_files_wmunu = 6;
  TFile *fwmunu[6];
  TFile *fwmunu_cf[6];
  string fname_wmunu[6];
  string wmunu_name;
  string wmunu_cf_name;
  for(int i=0; i<6; i++){
    wmunu_name = "WmunuNp" + NumToStr(i) + "_hists";
    wmunu_cf_name = cutflow_h_path + wmunu_name + ".root";
    wmunu_name += file_suffix;
    fname_wmunu[i] = wmunu_name;
    wmunu_name = mc_path + wmunu_name;
    fwmunu[i] = TFile::Open(wmunu_name.c_str(),"UPDATE");
    fwmunu_cf[i] = TFile::Open(wmunu_cf_name.c_str(),"UPDATE");
  }
  TH1D *h_wmunu_array[6];

  //Wcc_NpX
  string mc_type_wcc = "Wcc_Np";
  const int n_files_wcc = 4;
  TFile *fwcc[4];
  TFile *fwcc_cf[4];
  string fname_wcc[4];
  string wcc_name;
  string wcc_cf_name;
  for(int i=0; i<4; i++){
    wcc_name = "WccNp" + NumToStr(i) + "_hists";
    wcc_cf_name = cutflow_h_path + wcc_name + ".root";
    wcc_name += file_suffix;
    fname_wcc[i] = wcc_name;
    wcc_name = mc_path + wcc_name;
    fwcc[i] = TFile::Open(wcc_name.c_str(),"UPDATE");
    fwcc_cf[i] = TFile::Open(wcc_cf_name.c_str(),"UPDATE");
  }
  TH1D *h_wcc_array[4];

  //Wc_NpX
  string mc_type_wc = "Wc_Np";
  const int n_files_wc= 5;
  TFile*fwc[5];
  TFile*fwc_cf[5];
  string fname_wc[5];
  string wc_name;
  string wc_cf_name;
  for(int i=0; i<5; i++){
    wc_name = "WcNp" + NumToStr(i) + "_hists";
    wc_cf_name= cutflow_h_path + wc_name + ".root";
    wc_name += file_suffix;
    fname_wc[i] = wc_name;
    wc_name = mc_path + wc_name;
    fwc[i] = TFile::Open(wc_name.c_str(),"UPDATE");
    fwc_cf[i] = TFile::Open(wc_cf_name.c_str(),"UPDATE");
  }
  TH1D *h_wc_array[5];

  //Wbb_NpX
  string mc_type_wbb = "Wbb_Np";
  const int n_files_wbb= 4;
  TFile*fwbb[4];
  TFile*fwbb_cf[4];
  string fname_wbb[4];
  string wbb_name;
  string wbb_cf_name;
  for(int i=0; i<4; i++){
    wbb_name = "WbbNp" + NumToStr(i) + "_hists";
    wbb_cf_name= cutflow_h_path + wbb_name + ".root";
    wbb_name += file_suffix;
    fname_wbb[i] = wbb_name;
    wbb_name = mc_path + wbb_name;
    fwbb[i] = TFile::Open(wbb_name.c_str(),"UPDATE");
    fwbb_cf[i] = TFile::Open(wbb_cf_name.c_str(),"UPDATE");
  }
  TH1D *h_wbb_array[4];

  //tt-bar
  string mc_type_ttbar = "ttbar";
  const int n_files_ttbar = 1;
  TFile *fttbar[1];
  TFile *fttbar_cf[1];
  string fname_ttbar[1];
  string ttbar_name = mc_type_ttbar + "_hists";
  string ttbar_cf_name = cutflow_h_path + ttbar_name + ".root";
  ttbar_name += file_suffix;
  fname_ttbar[0] = ttbar_name;
  ttbar_name = mc_path + ttbar_name;
  fttbar[0] = TFile::Open(ttbar_name.c_str(),"UPDATE");
  fttbar_cf[0] = TFile::Open(ttbar_cf_name.c_str(),"UPDATE");
  TH1D *h_ttbar_array[1];

  //single top
  /*
    string mc_type_singletop = "singletop";
    const int n_files_singletop = 3;
    TFile *fsingletop[3];
    TFile *fsingletop_cf[3];
    string fname_singletop[3];
    string singletop_name;
    string singletop_cf_name;
    for(int i=0; i<3; i++){
      if(i==0) singletop_name = "singletop_tchan_mu_hists.root";
      else if(i==1) singletop_name = "singletop_WtChanIncl_hists.root";
      else if(i==2) singletop_name = "singletop_SChan_Wmunu_hists.root";
      fname_singletop[i] = singletop_name;
      singletop_cf_name = cutflow_h_path + singletop_name;
      singletop_name = mc_path + singletop_name;
      fsingletop[i] = TFile::Open(singletop_name.c_str(),"UPDATE");
      fsingletop_cf[i] = TFile::Open(singletop_cf_name.c_str(),"UPDATE");
    }
    TH1D *h_singletop_array[3];
  */

  string mc_type_singletop = "singletop";
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
  }
  TH1D *h_singletop_array[4];

  //Diboson
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
  }
  TH1D *h_diboson_array[6];


  //====================
  //===== Data =========
  //====================
  //My data
  //  string data_path = "/n/atlas02/user_codes/looper.6/Vbb/analysis_code/data_histograms/";
  string data_path ="/n/atlas02/user_codes/looper.6/Vbb/analysis_code/../old_histograms/old_data_histograms/data_histograms_Aug24/";
  //  string data_path = "/n/atlas02/user_codes/looper.6/Vbb/analysis_code/data_debug/";
  //  string data_path = "/n/atlas02/user_codes/looper.6/Vbb/analysis_code/data_histograms_arantxa/";
  TFile *fdata;
  string data_name = data_path + "alldata";
  if(isMJ) data_name += "_MJ.root";
  else if(isWide) data_name += "_wide.root";
  else data_name += ".root";
  //string data_name = data_path + "periodH.root";
  if(var_2_plot == "bottom_jets_hmatch_up" || var_2_plot == "bottom_jets_hmatch_down"){histo_name = "mv1cweight_bottom_had_match";}
  fdata = TFile::Open(data_name.c_str(),"UPDATE");
  TH1D *h_data = (TH1D*)fdata->Get(histo_name);
  h_data->GetXaxis()->SetRangeUser(x_min,x_max);
  //  h_data->SetLineWidth(5);

  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    ~~~~~~~~~~~~~~~ADD HISTOGRAMS~~~~~~~~~~~~~~~~~
    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

  //Add MC histograms by process: function add_histo is defined in header file
  //Zmumu
  TH1D *h_zmumu_sherpa_sum;
  if(include_sherpa){
    h_zmumu_sherpa_sum = add_histo(fzmumu_sherpa,n_files_zmumu_sherpa,fname_zmumu_sherpa,histo_name,zmumu_sherpa_xsec,fzmumu_sherpa_cf,lumi,h_zmumu_sherpa_array,zmumu_sherpa_process,x_min,x_max);
  }
  TH1D *h_zmumu_sum     = add_histo(fzmumu,n_files_zmumu,fname_zmumu,histo_name,zmumu_xsec,fzmumu_cf,lumi,h_zmumu_array,zmumu_process,x_min,x_max);
  TH1D *h_zmumubb_sum   = add_histo(fzmumubb,n_files_zmumubb,fname_zmumubb,histo_name,zmumubb_xsec,fzmumubb_cf,lumi,h_zmumubb_array,zmumubb_process,x_min,x_max);
  TH1D *h_zmumucc_sum   = add_histo(fzmumucc,n_files_zmumucc,fname_zmumucc,histo_name,zmumucc_xsec,fzmumucc_cf,lumi,h_zmumucc_array,zmumucc_process,x_min,x_max);
  TH1D *h_ztautau_sum   = add_histo(fztautau,n_files_ztautau,fname_ztautau,histo_name,ztautau_xsec,fztautau_cf,lumi,h_ztautau_array,ztautau_process,x_min,x_max);
  TH1D *h_wmunu_sum     = add_histo(fwmunu,n_files_wmunu,fname_wmunu,histo_name,wmunu_xsec,fwmunu_cf,lumi,h_wmunu_array,wmunu_process,x_min,x_max);
  TH1D *h_wcc_sum       = add_histo(fwcc,n_files_wcc,fname_wcc,histo_name,wcc_xsec,fwcc_cf,lumi,h_wcc_array,wcc_process,x_min,x_max);
  TH1D *h_wc_sum        = add_histo(fwc,n_files_wc,fname_wc,histo_name,wc_xsec,fwc_cf,lumi,h_wc_array,wc_process,x_min,x_max);
  TH1D *h_wbb_sum       = add_histo(fwbb,n_files_wbb,fname_wbb,histo_name,wbb_xsec,fwbb_cf,lumi,h_wbb_array,wbb_process,x_min,x_max);
  TH1D *h_ttbar_sum     = add_histo(fttbar,n_files_ttbar,fname_ttbar,histo_name,ttbar_xsec,fttbar_cf,lumi,h_ttbar_array,ttbar_process,x_min,x_max);
  TH1D *h_singletop_sum = add_histo(fsingletop,n_files_singletop,fname_singletop,histo_name,singletop_xsec,fsingletop_cf,lumi,h_singletop_array,singletop_process,x_min,x_max);
  TH1D *h_diboson_sum   = add_histo(fdiboson,n_files_diboson,fname_diboson,histo_name,diboson_xsec,fdiboson_cf,lumi,h_diboson_array,diboson_process,x_min,x_max);


  TH1D *h_wjets_sum = (TH1D*)h_wmunu_sum->Clone();
  h_wjets_sum->Add(h_wcc_sum);
  h_wjets_sum->Add(h_wc_sum);
  h_wjets_sum->Add(h_wbb_sum);


  h_zmumu_sum->SetFillColor(kBlue);
  h_zmumubb_sum->SetFillColor(kYellow);
  h_zmumucc_sum->SetFillColor(kGreen);
  h_ztautau_sum->SetFillColor(kCyan);
  h_wjets_sum->SetFillColor(kAzure+3);
  h_ttbar_sum->SetFillColor(kViolet);
  h_singletop_sum->SetFillColor(kRed+1);
  h_diboson_sum->SetFillColor(kOrange);

  gStyle->SetOptStat("");

  /*  h_zmumu_sum->SetLineWidth(5);
  h_zmumubb_sum->SetLineWidth(5);
  h_zmumucc_sum->SetLineWidth(5);
  h_ztautau_sum->SetLineWidth(5);
  h_wjets_sum->SetLineWidth(5);
  h_ttbar_sum->SetLineWidth(5);
  h_singletop_sum->SetLineWidth(5);
  h_diboson_sum->SetLineWidth(5);
  */

  double zplusjets_sum = h_zmumu_sum->Integral();
  zplusjets_sum += h_zmumubb_sum->Integral();
  zplusjets_sum += h_zmumucc_sum->Integral();

  double zplusjets_sherpa_sum;
  if(include_sherpa) zplusjets_sherpa_sum = h_zmumu_sherpa_sum->Integral();

  cout.precision(9);
  cout << "Z->mumu + jets (Alpgen): " << zplusjets_sum << endl;
  if(include_sherpa)  cout << "Z->mumu + jets (Sherpa): " << zplusjets_sherpa_sum << endl;
  cout << "Z->tautau + jets: " << h_ztautau_sum->Integral() << endl;
  cout << "W+jets: " << h_wjets_sum->Integral() << endl;
  cout << "ttbar: " << h_ttbar_sum->Integral() << endl;
  cout << "single top: " << h_singletop_sum->Integral() << endl;
  cout << "diboson: " << h_diboson_sum->Integral() << endl;

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
    if(include_sherpa) h_zmumu_sherpa_sum->Rebin(rebin);
    h_zmumu_sum->Rebin(rebin);
    h_zmumubb_sum->Rebin(rebin);
    h_zmumucc_sum->Rebin(rebin);
    h_ztautau_sum->Rebin(rebin);
    h_wjets_sum->Rebin(rebin);
    h_ttbar_sum->Rebin(rebin);
    h_singletop_sum->Rebin(rebin);
    h_diboson_sum->Rebin(rebin);
    h_data->Rebin(rebin);
  }
  if(include_sherpa) h_zmumu_sherpa_sum->GetXaxis()->SetRangeUser(x_min,x_max);
  h_zmumu_sum->GetXaxis()->SetRangeUser(x_min,x_max);
  h_zmumubb_sum->GetXaxis()->SetRangeUser(x_min,x_max);
  h_zmumucc_sum->GetXaxis()->SetRangeUser(x_min,x_max);
  h_ztautau_sum->GetXaxis()->SetRangeUser(x_min,x_max);
  h_wjets_sum->GetXaxis()->SetRangeUser(x_min,x_max);
  h_ttbar_sum->GetXaxis()->SetRangeUser(x_min,x_max);
  h_singletop_sum->GetXaxis()->SetRangeUser(x_min,x_max);
  h_diboson_sum->GetXaxis()->SetRangeUser(x_min,x_max);
  h_data->GetXaxis()->SetRangeUser(x_min,x_max);

  TH1D *h_mc_sum = (TH1D*)h_zmumu_sum->Clone();
  TH1D *h_zmumu_sum_clone = (TH1D*)h_zmumu_sum->Clone();
  TH1D *h_zmumubb_sum_clone = (TH1D*)h_zmumubb_sum->Clone();
  TH1D *h_ztautau_sum_clone = (TH1D*)h_ztautau_sum->Clone();
  TH1D *h_wjets_sum_clone = (TH1D*)h_wjets_sum->Clone();
  TH1D *h_zmumucc_sum_clone = (TH1D*)h_zmumucc_sum->Clone();
  TH1D *h_ttbar_sum_clone = (TH1D*)h_ttbar_sum->Clone();
  TH1D *h_singletop_sum_clone = (TH1D*)h_singletop_sum->Clone();
  TH1D *h_diboson_sum_clone = (TH1D*)h_diboson_sum->Clone();

  //sherpa comparison clones: cloning two, electric boogaloo
  
  TH1D *h_mc_sherpa_sum;
  TH1D *h_ztautau_sherpa_sum_clone;
  TH1D *h_wjets_sherpa_sum_clone;
  TH1D *h_ttbar_sherpa_sum_clone;
  TH1D *h_singletop_sherpa_sum_clone;
  TH1D *h_diboson_sherpa_sum_clone;
  
  if(include_sherpa){
    h_mc_sherpa_sum = (TH1D*)h_zmumu_sherpa_sum->Clone();
    h_ztautau_sherpa_sum_clone = (TH1D*)h_ztautau_sum->Clone();
    h_wjets_sherpa_sum_clone = (TH1D*)h_wjets_sum->Clone();
    h_ttbar_sherpa_sum_clone = (TH1D*)h_ttbar_sum->Clone();
    h_singletop_sherpa_sum_clone = (TH1D*)h_singletop_sum->Clone();
    h_diboson_sherpa_sum_clone = (TH1D*)h_diboson_sum->Clone();
  }

  h_mc_sum->Add(h_zmumubb_sum_clone);
  h_mc_sum->Add(h_zmumucc_sum_clone);
  h_mc_sum->Add(h_ztautau_sum_clone);
  h_mc_sum->Add(h_wjets_sum_clone);
  h_mc_sum->Add(h_ttbar_sum_clone);
  h_mc_sum->Add(h_singletop_sum_clone);
  h_mc_sum->Add(h_diboson_sum_clone);

  if(include_sherpa){
    h_mc_sherpa_sum->Add(h_ztautau_sherpa_sum_clone);
    h_mc_sherpa_sum->Add(h_wjets_sherpa_sum_clone);
    h_mc_sherpa_sum->Add(h_ttbar_sherpa_sum_clone);
    h_mc_sherpa_sum->Add(h_singletop_sherpa_sum_clone);
    h_mc_sherpa_sum->Add(h_diboson_sherpa_sum_clone);
  }
  //rescale attempt
  
  TH1D *h_mc_sum_clone =(TH1D*)h_mc_sum->Clone();
  TH1D *h_mc_sherpa_sum_clone;
  if(include_sherpa) h_mc_sherpa_sum_clone = (TH1D*)h_mc_sherpa_sum->Clone();
  if(!scale_to_lumi){
    h_mc_sum_clone->Scale(h_data->Integral()/h_mc_sum->Integral());
    cout << "Normalization ratio: " << h_data->Integral()/h_mc_sum->Integral() << endl;
    h_singletop_sum_clone->Scale(h_data->Integral()/h_mc_sum->Integral());
    h_ttbar_sum_clone->Scale(h_data->Integral()/h_mc_sum->Integral());
    h_diboson_sum_clone->Scale(h_data->Integral()/h_mc_sum->Integral());
    h_ztautau_sum_clone->Scale(h_data->Integral()/h_mc_sum->Integral());
    h_wjets_sum_clone->Scale(h_data->Integral()/h_mc_sum->Integral());
    h_zmumucc_sum_clone->Scale(h_data->Integral()/h_mc_sum->Integral());
    h_zmumu_sum_clone->Scale(h_data->Integral()/h_mc_sum->Integral());
    h_zmumubb_sum_clone->Scale(h_data->Integral()/h_mc_sum->Integral());

    if(include_sherpa){
      h_mc_sherpa_sum_clone->Scale(h_data->Integral()/h_mc_sherpa_sum->Integral());
      cout << "Normalization ratio (sherpa): " << h_data->Integral()/h_mc_sherpa_sum->Integral() << endl;
      h_ztautau_sherpa_sum_clone->Scale(h_data->Integral()/h_mc_sherpa_sum->Integral());
      h_wjets_sherpa_sum_clone->Scale(h_data->Integral()/h_mc_sherpa_sum->Integral());
      h_ttbar_sherpa_sum_clone->Scale(h_data->Integral()/h_mc_sherpa_sum->Integral());
      h_singletop_sherpa_sum_clone->Scale(h_data->Integral()/h_mc_sherpa_sum->Integral());
      h_diboson_sherpa_sum_clone->Scale(h_data->Integral()/h_mc_sherpa_sum->Integral());
    }
  }
  //Stack for Alpgen samples (no sherpa stack)
  sum_stack->Add(h_singletop_sum_clone);
  sum_stack->Add(h_ttbar_sum_clone);
  sum_stack->Add(h_diboson_sum_clone);
  sum_stack->Add(h_ztautau_sum_clone);
  sum_stack->Add(h_wjets_sum_clone);
  sum_stack->Add(h_zmumucc_sum_clone);
  sum_stack->Add(h_zmumu_sum_clone);
  sum_stack->Add(h_zmumubb_sum_clone);


  float mc_events = h_mc_sum->Integral();
  cout << "MC sum: " << mc_events << endl;
  float mc_events_sherpa;
  if(include_sherpa){
    mc_events_sherpa = h_mc_sherpa_sum->Integral();
    cout << "MC sum (sherpa): " << mc_events_sherpa << endl;
  }
  float data_events = h_data->Integral();
  cout << "Data sum: " << data_events << endl;

  float data_minus_background = data_events;
  data_minus_background -= h_ztautau_sum->Integral();
  data_minus_background -= h_wjets_sum->Integral();
  data_minus_background -= h_ttbar_sum->Integral();
  data_minus_background -= h_singletop_sum->Integral();
  data_minus_background -= h_diboson_sum->Integral();

  cout << "Data minus background (Z+jets): " << data_minus_background << endl;

  float percent_difference = (data_events-mc_events)/data_events;
  cout << "Percentage difference: " << percent_difference << endl;
  float percentage_difference_sherpa;
  if(include_sherpa){
    percentage_difference_sherpa = (data_events-mc_events_sherpa)/data_events;
    cout << "Percentage difference (sherpa): " << percentage_difference_sherpa << endl;
  }
  float ratio = (data_events)/(mc_events);
  cout << "Ratio (Data/MC): " << ratio << endl;
  float ratio_sherpa;
  if(include_sherpa){
    ratio_sherpa = (data_events)/(mc_events_sherpa);
    cout << "Ratio (sherpa): " << ratio_sherpa << endl;
  }
  write_event_numbers(h_zmumu_sum,h_data,histo_name,lumi);

  //make n_jets tables
  if(var_2_plot == "n_jets" || var_2_plot == "n_jets_eta"){
    write_table(h_mc_sum, h_data, histo_name);
  }

  //Write mc_sum as root file for further manipulation (like fitting)
  string rootfile_name = "MC_histograms_root/"+var_2_plot;
  if(isMJ) rootfile_name += "_ctrlregion.root";
  else if(isWide) rootfile_name += "_wide.root";
  else rootfile_name += ".root";
  TFile * f_root = TFile::Open(rootfile_name.c_str(),"RECREATE");
  string mc_hist_name = var_2_plot+"_mc";
  string data_hist_name = var_2_plot+"_data";
  string mc_sherpa_hist_name = var_2_plot+"_sherpa";
  h_mc_sum->SetName(mc_hist_name.c_str());
  h_data->SetName(data_hist_name.c_str());
  if(include_sherpa){
    h_mc_sherpa_sum->SetName(mc_sherpa_hist_name.c_str());
    h_mc_sherpa_sum->Write();
  }
  h_mc_sum->Write();
  h_data->Write();
  f_root->Close();


  /**************************************
   ********DRAW SUMMED HISTS************
   **********************************/
  string canvas_name = var_2_plot + "canvas";
  TCanvas *c1 = new TCanvas(canvas_name.c_str(),canvas_name.c_str(),800,800);

  float mc_max = h_mc_sum_clone->GetMaximum();
  float data_max = h_data->GetMaximum();
  //plot the histogram with the larger number of events first (makes the y-axis range correct)
  if(make_log){
    sum_stack->SetMaximum(y_max);
    sum_stack->SetMinimum(y_min);
    if(include_sherpa){
      h_mc_sherpa_sum->SetMaximum(y_max);
      h_mc_sherpa_sum->SetMinimum(y_min);
    }
    //h_data->GetYaxis()->SetRangeUser(y_min,y_max);
 }
  else{
    sum_stack->SetMaximum(y_max);
    sum_stack->SetMinimum(y_min);
    if(include_sherpa){
      h_mc_sherpa_sum->SetMaximum(y_max);
      h_mc_sherpa_sum->SetMinimum(y_min);
    }
  }


  //draw mc and data and make ratio plot
  TPad *pad1 = new TPad("pad1","pad1",0,0.3,1,1);
  if(make_log){
    pad1->SetLogy();
  }
  pad1->SetTopMargin(0.05);
  pad1->SetBottomMargin(0);
  pad1->SetRightMargin(0.05);
  pad1->SetLeftMargin(0.16);
  pad1->SetFillStyle(4000);
  pad1->Draw("9");
  pad1->cd();

  if(include_sherpa){
    h_mc_sherpa_sum->SetLineStyle(2);
    h_mc_sherpa_sum->SetLineColor(2);
    h_mc_sherpa_sum->SetLineWidth(2);
  }

  sum_stack->Draw("HIST");
  sum_stack->GetXaxis()->SetNdivisions(000);
  if(include_sherpa) h_mc_sherpa_sum->Draw("HIST SAME");
  h_data->Draw("HIST ELP SAME");
  sum_stack->GetXaxis()->SetRangeUser(x_min,x_max);
  if(var_2_plot == "n_jets" || var_2_plot == "n_bjets"){
    sum_stack->GetXaxis()->CenterTitle();
  }
  sum_stack->GetYaxis()->SetTitle(y_name);
  c1->Modified();

  c1->cd();
  TPad *pad2 = new TPad("pad2","pad2",0,0,1,0.3);
  pad2->SetTopMargin(0);
  pad2->SetBottomMargin(0.48);
  pad2->SetRightMargin(0.05);
  pad2->SetLeftMargin(0.16);
  pad2->SetFillStyle(4000);
  pad2->SetGridx();
  pad2->SetGridy();
  pad2->Draw("9");
  pad2->cd();

  //double ratiomin = 0.45;
  //double ratiomax = 1.85;
  
  //double ratiomin = 0.8;
  //double ratiomax = 1.2;

  h_mc_sum_clone->SetStats(0);
  h_mc_sum_clone->SetMarkerSize(0.5);
  h_mc_sum_clone->GetYaxis()->SetTickLength(0.04);
  h_mc_sum_clone->GetYaxis()->SetNdivisions(505);
  h_mc_sum_clone->GetXaxis()->SetLabelSize(0.04*3./1.);
  h_mc_sum_clone->GetXaxis()->SetTitleSize(0.04*3./1.);
  h_mc_sum_clone->GetYaxis()->SetLabelSize(0.04*3./1.);
  h_mc_sum_clone->GetYaxis()->SetTitleSize(0.04*3./1.);
  h_mc_sum_clone->GetXaxis()->SetTitleOffset(1.2);
  h_mc_sum_clone->GetYaxis()->SetTitleOffset(1.2/2.);
  h_mc_sum_clone->GetXaxis()->SetTitle("");
  
  h_mc_sum_clone->GetYaxis()->SetTitle("Data/MC");
  //h_mc_sum_clone->GetYaxis()->SetTitle("MC/Data");
  h_mc_sum_clone->SetLineColor(kBlack);
  h_mc_sum_clone->Divide(h_data,h_mc_sum_clone);

  h_mc_sum_clone->SetMinimum(ratiomin);
  h_mc_sum_clone->SetMaximum(ratiomax);
 
  h_mc_sum_clone->SetMarkerStyle(20);
  h_mc_sum_clone->SetXTitle(x_name);
  h_mc_sum_clone->Draw("ep");

  if(include_sherpa){
    h_mc_sherpa_sum_clone->SetMinimum(ratiomin);
    h_mc_sherpa_sum_clone->SetMaximum(ratiomax);
    h_mc_sherpa_sum_clone->SetMarkerSize(0.5);
    h_mc_sherpa_sum_clone->SetMarkerColor(kRed);
    h_mc_sherpa_sum_clone->SetLineColor(kRed);
    h_mc_sherpa_sum_clone->Divide(h_data,h_mc_sherpa_sum_clone);
    h_mc_sherpa_sum_clone->SetMarkerStyle(20);
    h_mc_sherpa_sum_clone->Draw("ep same");
  }
  TLegend *ratiolegend = new TLegend(0.3,0.84,0.65,0.97);
  ratiolegend->SetFillStyle(0);
  ratiolegend->SetTextSize(0.07);
  ratiolegend->SetBorderSize(0);
  ratiolegend->SetNColumns(2);
  ratiolegend->AddEntry(h_mc_sum_clone,"Alpgen","lp");
  if(include_sherpa) ratiolegend->AddEntry(h_mc_sherpa_sum_clone,"Sherpa","lp");
  ratiolegend->Draw();

  pad1->cd();

  TLegend *legend = new TLegend(0.6,0.64,0.95,0.95);
  legend->SetTextSize(0.03);
  legend->AddEntry(h_data,"Data","lp");
  if(include_sherpa) legend->AddEntry(h_mc_sherpa_sum,"Sherpa MC","l");
  legend->AddEntry(h_zmumubb_sum_clone,"Z(#rightarrow#mu#mu)+bb+jets MC","f");
  legend->AddEntry(h_zmumu_sum_clone,"Z(#rightarrow#mu#mu)+jets MC","f");
  legend->AddEntry(h_zmumucc_sum_clone,"Z(#rightarrow#mu#mu)+cc+jets MC","f");
  legend->AddEntry(h_ztautau_sum_clone,"Z#rightarrow#tau#tau+jets MC","f");
  legend->AddEntry(h_wjets_sum_clone,"W+jets MC","f");
  legend->AddEntry(h_diboson_sum_clone,"Diboson MC","f");
  legend->AddEntry(h_ttbar_sum_clone,"tt-bar MC","f");
  legend->AddEntry(h_singletop_sum_clone, "single-top MC","f");

  legend->Draw();

  TLatex *tex1 = new TLatex();
  tex1->SetNDC();
  string mc_evt_label = "#font[18]{MC events: " + NumToStr(mc_events) + "}";
  //  tex1->DrawLatex(0.19,0.9-0.03,mc_evt_label.c_str());

  TLatex *tex2 = new TLatex();
  tex2->SetNDC();
  string data_evt_label = "#font[18]{Data events: " + NumToStr(data_events) + "}";
  //  tex2->DrawLatex(0.19,0.9-0.001,data_evt_label.c_str());

  c1->cd();
  c1->Update();

  //TImage *img = TImage::Create();
  //img->FromPad(c1);
  string img_name = plt_dir + "/" + var_2_plot;
  if(isMJ) img_name += "_MJ";
  else if(isWide) img_name += "_wide";
  if(!include_sherpa) img_name += "_nosherpa";
  if(make_log){
    img_name += ".pdf";
  }
  else{
    img_name += "nolog.pdf";
  }
  //  img->WriteImage(img_name.c_str());
  c1->SaveAs(img_name.c_str());

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
  close_files(fsingletop, 4);
  close_files(fsingletop_cf, 4);
  close_files(fdiboson, 6);
  close_files(fdiboson_cf, 6);

  fdata->Close();

}

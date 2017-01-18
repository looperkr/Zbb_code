///////////////macro for plotting Z+bb results //////////////
/*
Created by: K. Looper (2 Oct 2015)
Last edited: 10 Dec 2015
Last edited by: K. Looper
Note: support for Evelin's code removed 5 Nov. See backup code to run on that.
*/
/*
Variables that can be plotted:
single muon pT: mu_pt (before Z cut)
single muon pT: mu_pt_Z (after Z cut)
single muon phi: mu_phi
single muon eta: mu_eta
dimuon mass: dimu_mass
dimuon mass: Z_mass (after Z window cut)
dimuon y: Z_y
dimuon pT (after Z window cuts): Z_pt
number of jets: n_jets
jet pT: jet_pt
number of jets (for given jet pT cut): jet_n_X, X = [35,40,45,50,55,60]
jet y: jet_y
leading jet pT: lead_jet_pt
jet pT scalar sum (ST): jet_st
jet pT and muon scalar sum (HT): jet_ht
dijet invariant mass (leading and subleading): dijet_m
number of b-tagged jets: n_bjets
pT of b-tagged jets:  bjet_pt
rapidity of b-tagged jets: bjet_y
pT of leading b-tagged jet: bjet_lead_pt
pT of subleading b-tagged jet: bjet_sublead_pt
dijet invariant mass of leading and subleading b-tagged jet: bjet_mass
Delta R between leading and subleading b-tagged jets: deltaR_bb
Delta R between leading b-tagged jet and Z: deltaR_Zb
Delta phi between leading b-tagged jet and Z: deltaphi_Zb
Rank of the bjet among all the jets: bjet_rank
Di-bjet pT: bjet_pt_bb
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

void analysis_plots(string var_2_plot,bool scale_to_lumi, bool make_log){

  int j = 0; //debugging iterator
  //plot luminosity
  double lumi;
  if(scale_to_lumi){
    //luminosity in picobarns
    //    lumi = 3413.06; //second packages run
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
      //    lumi = 21300.0; //nominal 8 TeV
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

  //Plot options for chosen variable
  if(var_2_plot == "mu_pt"){
    histo_name = "mu_pt_nocut"; //before pt cut applied
    x_name = "p_{T}^{#mu} [GeV]";
    y_name = "Events";
    x_min = 0; x_max = 200;
    y_min = 0.01; y_max = 1000000000;
    rebin = 1;
  }
  else if(var_2_plot == "mu_pt_Z"){
    histo_name = "mu_pT"; //after Z selection
    x_name = "p_{T}^{#mu} [GeV]";
    y_name = "Events";
    x_min = 15; x_max = 400;
    y_min = 0.1; y_max = 1000000000;
    rebin = 10;
  }
  else if(var_2_plot == "mu_phi"){
    histo_name = "mu_phi";
    x_name = "#phi^{#mu}";
    y_name = "Events";
    x_min = -TMath::Pi()-.5; x_max = TMath::Pi()+.5;
    //y_min = 0.1; y_max = 1000000000;
    y_min = 0.1; y_max = 1000000;
    rebin = 1;
  }
  else if(var_2_plot == "mu_eta"){
    histo_name = "mu_eta"; //after Z selection
    x_name = "#eta^{#mu}";
    y_name = "Events";
    x_min = -3; x_max = 3;
    //    y_min = 0.1; y_max = 1000000000;
    y_min = 0.1; y_max = 1000000;
    rebin = 1;
  }
  else if(var_2_plot == "Z_mass"){
    histo_name = "Z_mass"; //after Z mass window cut
    x_name = "m_{#mu#mu} [GeV]";
    y_name = "Events";
    x_min = 70; x_max = 110;
    y_min = 1; y_max = 1000000000;
    rebin = 2;
    ratiomin = 0.8;
    ratiomax = 1.4;
  }
  else if(var_2_plot == "Z_mass_nopw"){
    histo_name = "Z_mass_nopw"; //after Z mass window cut
    x_name = "m_{#mu#mu} [GeV]";
    y_name = "Events";
    x_min = 70; x_max = 110;
    y_min = 1; y_max = 1000000000;
    rebin = 2;
    ratiomin = 0.8;
    ratiomax = 1.4;
  }
  else if(var_2_plot == "m_mumu"){
    histo_name = "m_mumu"; // before Z mass window cut
    x_name = "m_{#mu#mu} [GeV]";
    y_name = "Events";
    x_min = 40; x_max = 200;
    y_min = 1; y_max = 1000000000;
    rebin = 2;
  }
  else if(var_2_plot == "Z_mass_0j"){
    histo_name = "Z_mass_0j"; 
    x_name = "m_{#mu#mu} [GeV]";
    y_name = "Events";
    x_min = 60; x_max = 120;
    y_min = 1; y_max = 1000000000;
    rebin = 2;
  }
  else if(var_2_plot == "Z_mass_MET"){
    histo_name = "Z_mass_MET";
    x_name = "m_{#mu#mu} [GeV]";
    y_name = "Events";
    x_min = 70; x_max = 110;
    y_min = 1; y_max = 1000000000;
    rebin = 2;
  }
  else if(var_2_plot == "Z_mass_exactly0j"){
    histo_name = "Z_mass_exactly0j";
    x_name = "m_{#mu#mu} [GeV]";
    y_name = "Events";
    x_min = 60; x_max = 120;
    y_min = 1; y_max = 1000000000;
    rebin = 2;
  }
  else if(var_2_plot == "Z_mass_0j_bch"){
    histo_name = "Z_mass_0j_bch";
    x_name = "m_{#mu#mu} [GeV]";
    y_name = "Events";
    x_min = 60; x_max = 120;
    y_min = 1; y_max = 1000000000;
    rebin = 2;
  }
  else if(var_2_plot == "Z_y"){
    histo_name = "Z_y";
    x_name = "Z rapidity";
    y_name = "Events";
    x_min = -3.5; x_max = 3.5;
    if(make_log){
      y_min = 0.1; y_max = 1000000000;
    }
    else{
      y_min = 0.1; y_max = 100000; 
    }
    rebin = 2;
  }
  else if(var_2_plot == "Z_y_nopw"){
    histo_name = "Z_y_nopw";
    x_name = "Z rapidity";
    y_name = "Events";
    x_min = -3.5; x_max = 3.5;
    if(make_log){
      y_min = 0.1; y_max = 1000000000;
    }
    else{
      y_min = 0.1; y_max = 100000;
    }
    rebin = 2;
  }
  else if(var_2_plot == "Z_eta"){
    histo_name = "Z_eta";
    x_name = "Z pseudorapidity";
    y_name = "Events";
    x_min = -6.; x_max = 6.;
    if(make_log){
      y_min = 0.1; y_max = 1000000000;
    }
    else{
      y_min = 0.1; y_max = 80000;
    }
    rebin = 2;

  }
  else if(var_2_plot == "Z_phi"){
    histo_name = "Z_phi";
    x_name = "#phi^{Z}";
    y_name = "Events";
    x_min = -TMath::Pi()-.5; x_max = TMath::Pi()+.5;
    y_min = 0.1; y_max = 100000000;
    rebin = 1;
  }
  else if(var_2_plot == "Z_phi_nopw"){
    histo_name = "Z_phi_nopw";
    x_name = "#phi^{Z}";
    y_name = "Events";
    x_min = -TMath::Pi()-.5; x_max = TMath::Pi()+.5;
    y_min = 0.1; y_max = 100000000;
    rebin = 1;
  }
  else if(var_2_plot == "Z_pt"){
    histo_name = "Z_pT";
    x_name = "Z p_{T}";
    x_min = 0; x_max = 800.;
    y_min = 0.1; y_max = 100000000;
    rebin = 100;
  }
  else if(var_2_plot == "Z_pt_nopw"){
    histo_name = "Z_pT_nopw";
    x_name = "Z p_{T}";
    x_min = 0; x_max = 800.;
    y_min = 0.1; y_max = 100000000;
    rebin = 100;
  }
  else if(var_2_plot == "met"){
    histo_name = "met";
    x_name = "MET";
    x_min = 0; x_max = 200.;
    y_min = 0.1; y_max = 100000000;
    rebin = 10;
  }
  else if(var_2_plot == "met_1tag"){
    histo_name = "met_1tag";
    x_name = "MET (>= 1 b)";
    x_min = 0; x_max = 200.;
    y_min = 0.1; y_max = 100000000;
    rebin = 10;
  }
  else if(var_2_plot == "n_jets"){
    histo_name = "jet_n";
    x_name = "#jets/event";
    x_min = 0; x_max = 7;
    y_min = 1.; y_max = 100000000;
    rebin = 1;
  }
  else if(var_2_plot == "n_jets_tight"){
    histo_name = "jet_n_tighteta";
    x_name = "#jets/event";
    x_min = 0; x_max = 7;
    y_min = 1.; y_max = 100000000;
    rebin = 1;
  }
  else if(var_2_plot == "n_jets_met"){
    histo_name = "njets_MET";
    x_name = "#jets/event";
    x_min = 0; x_max = 7;
    y_min = 1.; y_max = 100000000;
    rebin = 1;
  }
  else if(var_2_plot == "n_jets_eta"){
    histo_name = "jet_n_tight_eta";
    x_name = "#jets/event (|eta| < 2.4)";
    x_min = 0; x_max = 7;
    y_min = 1.; y_max = 1000000000;
    rebin = 1;
  }
  else if(var_2_plot == "jet_pt"){
    histo_name = "jet_pt";
    x_name = "jet pT [GeV]";
    x_min = 0.; x_max = 500.;
    y_min = 0.1; y_max = 10000000;
    rebin = 20;
  }
  else if(var_2_plot == "jet_pt_tight"){
    histo_name = "jet_pt_tighteta";
    x_name = "jet pT [GeV]";
    x_min = 0.; x_max = 500.;
    y_min = 0.1; y_max = 10000000;
    rebin = 20;
  }
  else if(var_2_plot == "jet_pt_eta"){
    histo_name = "jet_pt_tight_eta";
    x_name = "jet pT (|#eta| < 2.4) [GeV]";
    x_min = 0.; x_max = 300.;
    y_min = 0.1; y_max = 1000000000;
    rebin = 5;
  }
  else if(var_2_plot == "lead_jet_pt"){
    histo_name = "jet_pt_lead";
    x_name = "leading jet pT [GeV]";
    x_min = 0.; x_max = 600.;
    y_min = 0.1; y_max = 1000000000;
    rebin = 50;
  }
  else if(var_2_plot == "lead_jet_pt_tight"){
    histo_name = "jet_pt_lead_tighteta";
    x_name = "leading jet pT [GeV]";
    x_min = 0.; x_max = 600.;
    y_min = 0.1; y_max = 1000000000;
    rebin = 50;
  }
  else if(var_2_plot == "jet_y"){
    histo_name = "jet_y";
    x_name = "jet rapidity";
    x_min = -5; x_max = 5;
    y_min = 0.1; y_max = 1000000000;
    rebin = 4;
  }
  else if(var_2_plot == "jet_y_tight"){
    histo_name = "jet_y_tighteta";
    x_name = "jet rapidity";
    x_min = -3.5; x_max = 3.5;
    y_min = 0.1; y_max = 1000000000;
    rebin =4;
  }
  else if(var_2_plot == "leadjet_y"){
    histo_name = "jet_y_lead";
    x_min = -4.5; x_max = 4.5;
    y_min = 0.1; y_max = 10000000;
    rebin = 2;
  }
  else if(var_2_plot == "jet_st"){
    histo_name = "jet_st";
    x_name = "ST [GeV]";
    x_min = 25.; x_max = 500.;
    y_min = 0.1; y_max = 1000000000;
    rebin =20;
  }
  else if(var_2_plot == "jet_st_tight"){
    histo_name = "jet_st_tighteta";
    x_name = "ST [GeV]";
    x_min = 25.; x_max = 500.;
    y_min = 0.1; y_max = 1000000000;
    rebin =20;
  }
  else if(var_2_plot == "jet_ht"){
    histo_name = "jet_mu_ht";
    x_name = "ST [GeV]";
    x_min = 0.; x_max = 1000.;
    y_min = 0.1; y_max = 1000000000;
    rebin =20;
  }
  else if(var_2_plot == "jet_ht_tight"){
    histo_name = "jet_mu_ht_tighteta";
    x_name = "ST [GeV]";
    x_min = 0.; x_max = 1000.;
    y_min = 0.1; y_max = 1000000000;
    rebin =20;
  }
  else if(var_2_plot == "dijet_m"){
    histo_name = "dijet_m";
    x_name = "m_{jj} [GeV]";
    x_min = 0.; x_max = 1000.;
    y_min = 0.1; y_max = 100000000;
    rebin = 40;
  }
  else if(var_2_plot == "dijet_m_tight"){
    histo_name = "dijet_m_tighteta";
    x_name = "m_{jj} [GeV]";
    x_min = 0.; x_max = 1000.;
    y_min = 0.1; y_max = 100000000;
    rebin = 40;
  }
  else if(var_2_plot == "n_bjets"){
    histo_name = "bjet_n";
    x_name = "N_{bjets}";
    x_min = 0.; x_max = 5.;
    y_min = 1; y_max = 100000000;
    rebin = 1;
  }
  else if(var_2_plot == "bjet_pt"){
    histo_name = "bjet_pt";
    x_name = "p_{T}(b-jets) [GeV]";
    x_min = 0.; x_max = 500;
    y_min = 0.1; y_max = 100000;
    //rebin = 20;
    rebin = 40;
  }
  else if(var_2_plot == "bjet_y"){
    histo_name = "bjet_y";
    x_name = "b-jet rapidity";
    x_min = -3.5; x_max = 3.5;
    y_min = 0.1; y_max = 5000000;
    rebin = 4;
  }
  else if(var_2_plot == "bjet_lead_pt"){
    histo_name = "bjet_lead_pt";
    x_name = "p_{T}(leading b-jet) [GeV]";
    x_min =0.;x_max =500;
    y_min = 0.1; y_max = 100000;
    rebin = 20;
  }
  else if(var_2_plot == "bjet_sublead_pt"){
    histo_name = "bjet_sublead_pt";
    x_name = "p_{T}(subleading b-jet) [GeV]";
    x_min =0.;x_max =200;
    y_min = 0.1; y_max = 1000000;
    rebin = 20;
  }
  else if(var_2_plot == "bjet_mass"){
    histo_name = "bjet_m_bb";
    x_name = "m(b,b) [GeV]";
    x_min = 0.; x_max = 400;
    y_min = 0.1; y_max = 400;
    rebin = 20;
  }
  else if(var_2_plot == "deltaR_bb"){
    histo_name = "bjet_delR_bb";
    x_name = "#Delta R (b,b)";
    x_min = 0.; x_max = 5.0;
    y_min = 0.1; y_max = 2500;
    rebin = 10;
  }
  else if(var_2_plot == "deltaphi_bb"){
    histo_name ="bjet_delphi_bb";
    x_name = "#Delta#phi (b,b)";
    x_min = 0.0; x_max = 3.5;
    y_min = 0.1; y_max = 4000;
    rebin = 10;
  }
  else if(var_2_plot == "deltaeta_bb"){
    histo_name = "bjet_deltaeta_bb";
    x_name = "|#Delta#eta (b,b)|";
    x_min = 0.0; x_max = 5.5;
    y_min = 0.1; y_max = 3000;
    rebin = 10;
  }
  else if(var_2_plot == "deltaR_Zb"){
    histo_name = "bjet_delR_Zb";
    x_name = "#Delta R(Z,b)";
    x_min = 0.; x_max = 5.0;
    y_min = 0.1; y_max = 30000000;
    rebin = 10;
  }
  else if(var_2_plot == "deltaphi_Zb"){
    histo_name = "bjet_deltaphi_bZ";
    x_name = "#Delta #phi (Z,b)";
    x_min = 0; x_max = 3.5;
    y_min = 0.1; y_max = 100000000;
    rebin = 10;
  }
  else if(var_2_plot == "deltaeta_Zb"){
    histo_name = "bjet_deltaeta_Zb";
    x_name = "#Delta#eta (Z,b)";
    x_min = 0.; x_max = 5.5;
    y_min = 0.1; y_max = 30000000;
    rebin = 10;
  }
  else if(var_2_plot == "bjet_rank"){
    histo_name = "bjet_rank";
    x_name = "b-jet rank";
    x_min = 0; x_max= 5;
    y_min = 0.1; y_max = 1000000000;
    rebin = 1;
  }
  else if(var_2_plot == "bjet_pt_bb"){
    histo_name = "bjet_pt_bb";
    x_name = "di-bjet pT";
    x_min = 0; x_max = 350;
    y_min = 0.1; y_max = 1000;
    rebin = 20;
  }
  else if(var_2_plot == "Zpt_v_jj_pt"){
    histo_name = "Z_pt_v_jj_pt";
    x_name = "dijet pT";
    x_min = 0; x_max = 700;
    y_min = 0; y_max = 700;
    rebin = 1;
  }
  else if(var_2_plot == "Z_pt_v_bb_pt"){
    histo_name = "Z_pt_v_bb_pt";
    x_name = "dijet pT";
    x_min = 0; x_max = 700;
    y_min = 0; y_max = 700;
    rebin = 1;
  }
  else if(var_2_plot == "mv1weight"){
    histo_name = "mv1weight";
    x_name = "mv1 weight";
    x_min = 0; x_max = 1;
    y_min = 0.1; y_max = 1000000;
    rebin = 10;
  }
  else if(var_2_plot == "mv1cweight"){
    histo_name = "mv1cweight";
    x_name = "mv1c weight";
    x_min = 0; x_max = 1;
    y_min = 0.1; y_max = 1000000;
    rebin = 10;         
  }
  else if(var_2_plot == "pileup"){
    histo_name = "pileup_Z_avg";
    x_name = "pileup";
    x_min = 0; x_max = 50;
    if(make_log){
      y_min = 10; y_max = 50000000;
    }
    else{
      y_min = 0; y_max = 700000;
    }
    rebin = 20;
  }
  else if(var_2_plot == "pileup_norw_Z"){
    histo_name = "pileup_Z_avg_norw";
    x_min = 0; x_max = 50;
    if(make_log){
      y_min = 0.1; y_max = 50000000;
    }
    else{
      y_min = 0; y_max = 700000;
    }
    rebin = 10;
  } 
  else if(var_2_plot == "pileup_preZ"){
    histo_name = "avg_pileup";
    x_min = 0; x_max = 50;
    if(make_log){
      y_min = 0.1; y_max = 500000000;
    }
    else{
      y_min = 0; y_max - 7000000;
    }
    rebin = 10;
  }
  else if(var_2_plot == "avg_pileup_oldvar"){
    histo_name = "avg_pileup_oldvar";
    x_min = 0; x_max = 50;
    if(make_log){
      y_min = 0.1; y_max = 5000000000;
    }
    else{
      y_min = 0; y_max - 7000000;
    }
    rebin = 10;
  }
  else if(var_2_plot =="avg_pileup_oldvar_norw"){
    histo_name = "avg_pileup_oldvar_norw";
    x_min = 0; x_max = 50;
    if(make_log){
      y_min = 0.1; y_max = 5000000000;
    }
    else{
      y_min = 0; y_max - 7000000;
    }
    rebin = 10;
  }
  //following plot includes the recalculation of AverageIntPerXing, but not the pileup weight
  else if(var_2_plot == "avg_pileup_noprw"){
    histo_name = "avg_pileup_noprw";
    x_min = 0; x_max = 50;
    if(make_log){
      y_min = 0.1; y_max = 5000000000;
    }
    else{
      y_min = 0; y_max - 7000000;
    }
    rebin = 10;
  }
  else if(var_2_plot == "avg_pileup_norw"){
    histo_name = "avg_pileup_norw";
    x_min = 0; x_max = 50;
    if(make_log){
      y_min = 0.1; y_max = 5000000000;
    }
    else{
      y_min = 0; y_max - 7000000;
    }
    rebin = 10;
  }
  else if(var_2_plot == "avg_pileup_noweight"){
    histo_name = "avg_pileup_noweight";
    x_min = 0; x_max = 50;
    if(make_log){
      y_min = 0.1; y_max = 500000000;
    }
    else{
      y_min = 0; y_max - 7000000;
    }
    rebin = 10;
  }
  else if(var_2_plot == "avg_pileup_firstline"){
    histo_name = "avg_pileup_firstline";
    x_min = 0; x_max = 50;
    if(make_log){
      y_min = 0.1; y_max = 5000000000;
    }
    else{
      y_min = 0; y_max - 7000000;
    }
    rebin = 10;
  }
  else if(var_2_plot == "avg_pileup_mcweight"){
    histo_name = "avg_pileup_mcweight";
    x_min = 0; x_max = 50;
    if(make_log){
      y_min = 0.1; y_max = 5000000000;
    }
    else{
      y_min = 0; y_max - 7000000;
    }
    rebin = 10;
  }
  else if(var_2_plot == "avg_pileup_hfor"){
    histo_name = "avg_pileup_hfor";
    x_min = 0; x_max = 50;
    if(make_log){
      y_min = 0.1; y_max = 5000000000;
    }
    else{
      y_min = 0; y_max - 7000000;
    }
    rebin = 10;
  }
  else if(var_2_plot == "avg_pileup_hfor_nopw"){
    histo_name = "avg_pileup_hfor_nopw";
    x_min = 0; x_max = 50;
    if(make_log){
      y_min = 0.1; y_max = 5000000000;
    }
    else{
      y_min = 0; y_max - 7000000;
    }
    rebin = 10;
  }
  else if(var_2_plot =="avg_pileup_Zvertex"){
    histo_name = "avg_pileup_Zvertex";
    x_min = 0; x_max = 50;
    if(make_log){
      y_min = 0.1; y_max = 5000000000;
    }
    else{
      y_min = 0; y_max - 7000000;
    }
    rebin = 10;
  }
  else if(var_2_plot == "avg_pileup_Zvertex_nopw"){
    histo_name = "avg_pileup_Zvertex_nopw";
    x_min = 0; x_max = 50;
    if(make_log){
      y_min = 0.1; y_max = 5000000000;
    }
    else{
      y_min = 0; y_max - 7000000;
    }
    rebin = 10;
  }
  else if(var_2_plot == "avg_pileup_trigger"){
    histo_name = "avg_pileup_trigger";
    x_min = 0; x_max = 50;
    if(make_log){
      y_min = 0.1; y_max = 5000000000;
    }
    else{
      y_min = 0; y_max - 7000000;
    }
    rebin = 10;
  }
  else if(var_2_plot == "avg_pileup_trigger_nopw"){
    histo_name = "avg_pileup_trigger_nopw";
    x_min = 0; x_max = 50;
    if(make_log){
      y_min = 0.1; y_max = 5000000000;
    }
    else{
      y_min = 0; y_max - 7000000;
    }
    rebin = 10;
  }
  else if(var_2_plot == "avg_pileup_dataquality"){
    histo_name = "avg_pileup_dataquality";
    x_min = 0; x_max = 50;
    if(make_log){
      y_min = 0.1; y_max = 5000000000;
    }
    else{
      y_min = 0; y_max - 7000000;
    }
    rebin = 10;
  }
  else if(var_2_plot == "avg_pileup_dataquality_nopw"){
    histo_name = "avg_pileup_dataquality_nopw";
    x_min = 0; x_max = 50;
    if(make_log){
      y_min = 0.1; y_max = 5000000000;
    }
    else{
      y_min = 0; y_max - 7000000;
    }
    rebin = 10;
  }
  else if(var_2_plot == "avg_pileup_vertex"){
    histo_name = "avg_pileup_vertex";
    x_min = 0; x_max = 50;
    if(make_log){
      y_min = 0.1; y_max = 5000000000;
    }
    else{
      y_min = 0; y_max - 7000000;
    }
    rebin = 10;
  }
  else if(var_2_plot == "avg_pileup_vertex_nopw"){
    histo_name = "avg_pileup_vertex_nopw";
    x_min = 0; x_max = 50;
    if(make_log){
      y_min = 0.1; y_max = 5000000000;
    }
    else{
      y_min = 0; y_max - 7000000;
    }
    rebin = 10;
  }
  else if(var_2_plot == "avg_pileup_muonSF"){
    histo_name = "avg_pileup_muonSF";
    x_min = 0; x_max = 50;
    if(make_log){
      y_min = 0.1; y_max = 5000000000;
    }
    else{
      y_min = 0; y_max - 7000000;
    }
    rebin = 10;
  }
  else if(var_2_plot == "avg_pileup_muonSF_nopw"){
    histo_name = "avg_pileup_muonSF_nopw";
    x_min = 0; x_max = 50;
    if(make_log){
      y_min = 0.1; y_max = 5000000000;
    }
    else{
      y_min = 0; y_max - 7000000;
    }
    rebin = 10;
  }
  else if(var_2_plot == "avg_pileup_muonSF_nomuonSF"){
    histo_name = "avg_pileup_muonSF_nomuonSF";
    x_min = 0; x_max = 50;
    if(make_log){
      y_min = 0.1; y_max = 5000000000;
    }
    else{
      y_min = 0; y_max = 7000000;
    }
    rebin = 10;
  }
  else if(var_2_plot == "high_mu_weight"){
    histo_name = "high_mu_weight";
    x_min = -2; x_max = 2;
    if(make_log){
	y_min = 0.1; y_max = 5000000000;
    }
    else{
      y_min = 0; y_max = 7000000;
    }
    rebin = 1;
  }
  else{
    cout << "This variable is not supported" << endl;
    exit(0);
  }
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
~~~~~~~~~~~~MC CROSS SECTIONS~~~~~~~~~~~~~~~~~~~~
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  double xsec = 0;
  /*~~~~~~~~~~~~~~Sherpa Zmumu~~~~~~~~~~~~~~~~~~~~*/
  //Dataset 147771
  //xsections from arantxa's note
/*
  string zmumu_sherpa_process = "zmumu_sherpa";
  vector<double> zmumu_sherpa_xsec;
  double sigma_zmumu_sherpa[1] = {1207.8};

  double k_factor_zmumu_sherpa = 1.0276;
  double eff_zmumu_sherpa = 1.0;
  xsec = sigma_zmumu_sherpa[0]*k_factor_zmumu_sherpa*eff_zmumu_sherpa;
  zmumu_sherpa_xsec.push_back(xsec);*/

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

  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    ~~~~~~~~~~~OPEN FILES~~~~~~~~~~~~~~~~~~~~~~~~~~
    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  //====================
  //== Monte Carlo =====
  //====================
  string cutflow_h_path = "/n/atlas02/user_codes/looper.6/Vbb/hfor_histograms_new/";
  string mc_path = "/n/atlas02/user_codes/looper.6/Vbb/analysis_code/MC_histograms/";
  //  string mc_path = "/n/atlas02/user_codes/looper.6/Vbb/analysis_code/../old_histograms/old_MC_histograms/MC_histograms_Oct13/";
  //  string mc_path = "/n/atlas02/user_codes/looper.6/Vbb/analysis_code/hfor_histograms/";
  //  string mc_path = "/n/atlas02/user_codes/looper.6/Vbb/analysis_code/MC_debug/";
  //  string mc_path = "/n/atlas02/user_codes/looper.6/Vbb/analysis_code/MC_histograms_arantxa/";

  //Sherpa Zmumu
  /*
  string mc_type_zmumu_sherpa = "Zmumu_sherpa";
  const int n_files_zmumu_sherpa = 1;
  TFile * fzmumu_sherpa[1];
  TFile * fzmumu_sherpa_cf[1];
  string fname_zmumu_sherpa[1];
  string zmumu_sherpa_name;
  string zmumu_sherpa_cf_name;
  zmumu_sherpa_name = "Zmumu_sherpa_hists.root";
  fname_zmumu_sherpa[0] = zmumu_sherpa_name;
  zmumu_sherpa_cf_name = cutflow_h_path + zmumu_sherpa_name;
  zmumu_sherpa_name = mc_path + zmumu_sherpa_name;*/
  //  fzmumu_sherpa[0] = TFile::Open(zmumu_sherpa_name.c_str(),"UPDATE");
  //fzmumu_sherpa_cf[0] = TFile::Open(zmumu_sherpa_cf_name.c_str(),"UPDATE");
  //TH1D *h_zmumu_sherpa_array[1];

  //Zmumu_NpX
  string mc_type_zmumu = "Zmumu_Np";
  const int n_files_zmumu = 6;
  TFile * fzmumu[6];
  TFile * fzmumu_cf[6];
  string fname_zmumu[6];
  string zmumu_name;
  string zmumu_cf_name;
  for(int i=0;i<6;i++){
    zmumu_name = "ZmumuNp"+ NumToStr(i) + "_hists.root";
    fname_zmumu[i] = zmumu_name;
    zmumu_cf_name = cutflow_h_path + zmumu_name;
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
    zmumubb_name = "ZmumubbNp" + NumToStr(i) + "_hists.root";
    fname_zmumubb[i] = zmumubb_name;
    zmumubb_cf_name = cutflow_h_path + zmumubb_name;
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
    zmumucc_name = "ZmumuccNp" + NumToStr(i) + "_hists.root";
    fname_zmumucc[i] = zmumucc_name;
    zmumucc_cf_name = cutflow_h_path + zmumucc_name;
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
    ztautau_name = "ZtautauNp" + NumToStr(i) + "_hists.root";
    fname_ztautau[i] = ztautau_name;
    ztautau_cf_name = cutflow_h_path + ztautau_name;
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
    wmunu_name = "WmunuNp" + NumToStr(i) + "_hists.root";
    fname_wmunu[i] = wmunu_name;
    wmunu_cf_name = cutflow_h_path + wmunu_name;
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
    wcc_name = "WccNp" + NumToStr(i) + "_hists.root";
    fname_wcc[i] = wcc_name;
    wcc_cf_name = cutflow_h_path + wcc_name;
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
    wc_name = "WcNp" + NumToStr(i) + "_hists.root";
    fname_wc[i] = wc_name;
    wc_cf_name= cutflow_h_path + wc_name;
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
    wbb_name = "WbbNp" + NumToStr(i) + "_hists.root";
    fname_wbb[i] = wbb_name;
    wbb_cf_name= cutflow_h_path + wbb_name;
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
  string ttbar_name = mc_type_ttbar + "_hists.root";
  fname_ttbar[0] = ttbar_name;
  string ttbar_cf_name = cutflow_h_path + ttbar_name;
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
    if(i==0) singletop_name = "tchanTopPythia_hists.root";
    else if(i==1) singletop_name = "tchanAntitopPythia_hists.root";
    else if(i==2) singletop_name = "schanLepPythia_hists.root";
    else if(i==3) singletop_name = "WtchanPythia_hists.root";
    fname_singletop[i] = singletop_name;
    singletop_cf_name = cutflow_h_path + singletop_name;
    cout << singletop_cf_name << endl;
    singletop_name = mc_path + singletop_name;
    fsingletop[i] = TFile::Open(singletop_name.c_str(),"UPDATE");
    fsingletop_cf[i] = TFile::Open(singletop_cf_name.c_str(),"UPDATE");
  }
  TH1D *h_singletop_array[4];

  //Diboson
  string mc_type_diboson = "diboson";
  const int n_files_diboson = 3;
  TFile *fdiboson[3];
  TFile *fdiboson_cf[3];
  string fname_diboson[3];
  string diboson_name;
  string diboson_cf_name;
  for(int i=0; i<3; i++){
    if(i==0) diboson_name = "WW_hists.root";
    else if(i==1) diboson_name = "ZZ_hists.root";
    else if(i==2) diboson_name = "WZ_hists.root";
    fname_diboson[i] = diboson_name;
    diboson_cf_name = cutflow_h_path + diboson_name;
    diboson_name = mc_path + diboson_name;
    fdiboson[i] = TFile::Open(diboson_name.c_str(),"UPDATE");
    fdiboson_cf[i] = TFile::Open(diboson_cf_name.c_str(),"UPDATE");
  }
  TH1D *h_diboson_array[3];


  //====================
  //===== Data =========
  //====================
  //My data
  string data_path = "/n/atlas02/user_codes/looper.6/Vbb/analysis_code/data_histograms/";
  //  string data_path ="/n/atlas02/user_codes/looper.6/Vbb/analysis_code/../old_histograms/old_data_histograms/data_histograms_Oct13/";
  //  string data_path = "/n/atlas02/user_codes/looper.6/Vbb/analysis_code/data_debug/";
  //  string data_path = "/n/atlas02/user_codes/looper.6/Vbb/analysis_code/data_histograms_arantxa/";
  TFile *fdata;
  string data_name = data_path + "alldata.root";
  //string data_name = data_path + "periodH.root";
  fdata = TFile::Open(data_name.c_str(),"UPDATE");
  TH1D *h_data = (TH1D*)fdata->Get(histo_name);
  h_data->GetXaxis()->SetRangeUser(x_min,x_max);

  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    ~~~~~~~~~~~~~~~ADD HISTOGRAMS~~~~~~~~~~~~~~~~~
    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

  //Add MC histograms by process: function add_histo is defined in header file
  //Zmumu
  //  TH1D *h_zmumu_sherpa_sum = add_histo(fzmumu_sherpa,n_files_zmumu_sherpa,fname_zmumu_sherpa,histo_name,zmumu_sherpa_xsec,fzmumu_sherpa_cf,lumi,h_zmumu_sherpa_array,zmumu_sherpa_process,x_min,x_max);
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

  double zplusjets_sum = h_zmumu_sum->Integral();
  zplusjets_sum += h_zmumubb_sum->Integral();
  zplusjets_sum += h_zmumucc_sum->Integral();

  //  double zplusjets_sherpa_sum = h_zmumu_sherpa_sum->Integral();

  cout.precision(9);
  cout << "Z->mumu + jets (Alpgen): " << zplusjets_sum << endl;
  //  cout << "Z->mumu + jets (Sherpa): " << zplusjets_sherpa_sum << endl;
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
  /*
  write_plots_2_file(h_zmumu_array, n_files_zmumu, h_zmumu_sum, var_2_plot,mc_type_zmumu, plt_dir, x_min, x_max);
  write_plots_2_file(h_zmumubb_array,n_files_zmumubb, h_zmumubb_sum, var_2_plot, mc_type_zmumubb, plt_dir, x_min, x_max);
  write_plots_2_file(h_zmumucc_array,n_files_zmumucc, h_zmumucc_sum, var_2_plot, mc_type_zmumucc, plt_dir,x_min,x_max);
  write_plots_2_file(h_ztautau_array,n_files_ztautau, h_ztautau_sum, var_2_plot, mc_type_ztautau, plt_dir, x_min,x_max);
  write_plots_2_file(h_ttbar_array,n_files_ttbar, h_ttbar_sum, var_2_plot,mc_type_ttbar, plt_dir,x_min,x_max);
  write_plots_2_file(h_singletop_array,n_files_singletop, h_singletop_sum, var_2_plot, mc_type_singletop, plt_dir, x_min,x_max);
  write_plots_2_file(h_diboson_array,n_files_diboson,h_diboson_sum,var_2_plot,mc_type_diboson,plt_dir,x_min,x_max);
  */
  /******************************************
   **********Make Stack Plot***************
   ****************************************/
  string stack_name = string(histo_name.Data()) + "_stack";
  THStack *sum_stack = new THStack("stack","stack");

  if(rebin != 1){
    //h_zmumu_sherpa_sum->Rebin(rebin);
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
  //  h_zmumu_sherpa_sum->GetXaxis()->SetRangeUser(x_min,x_max);
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
  /*
  TH1D *h_mc_sherpa_sum = (TH1D*)h_zmumu_sherpa_sum->Clone();
  TH1D *h_ztautau_sherpa_sum_clone = (TH1D*)h_ztautau_sum->Clone();
  TH1D *h_wjets_sherpa_sum_clone = (TH1D*)h_wjets_sum->Clone();
  TH1D *h_ttbar_sherpa_sum_clone = (TH1D*)h_ttbar_sum->Clone();
  TH1D *h_singletop_sherpa_sum_clone = (TH1D*)h_singletop_sum->Clone();
  TH1D *h_diboson_sherpa_sum_clone = (TH1D*)h_diboson_sum->Clone();
  */

  h_mc_sum->Add(h_zmumubb_sum_clone);
  h_mc_sum->Add(h_zmumucc_sum_clone);
  h_mc_sum->Add(h_ztautau_sum_clone);
  h_mc_sum->Add(h_wjets_sum_clone);
  h_mc_sum->Add(h_ttbar_sum_clone);
  h_mc_sum->Add(h_singletop_sum_clone);
  h_mc_sum->Add(h_diboson_sum_clone);

  /*  h_mc_sherpa_sum->Add(h_ztautau_sherpa_sum_clone);
  h_mc_sherpa_sum->Add(h_wjets_sherpa_sum_clone);
  h_mc_sherpa_sum->Add(h_ttbar_sherpa_sum_clone);
  h_mc_sherpa_sum->Add(h_singletop_sherpa_sum_clone);
  h_mc_sherpa_sum->Add(h_diboson_sherpa_sum_clone);
  */
  //rescale attempt
  
  TH1D *h_mc_sum_clone =(TH1D*)h_mc_sum->Clone();
  //  TH1D *h_mc_sherpa_sum_clone = (TH1D*)h_mc_sherpa_sum->Clone();
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
    /*
    h_mc_sherpa_sum_clone->Scale(h_data->Integral()/h_mc_sherpa_sum->Integral());
    cout << "Normalization ratio (sherpa): " << h_data->Integral()/h_mc_sherpa_sum->Integral() << endl;
    h_ztautau_sherpa_sum_clone->Scale(h_data->Integral()/h_mc_sherpa_sum->Integral());
    h_wjets_sherpa_sum_clone->Scale(h_data->Integral()/h_mc_sherpa_sum->Integral());
    h_ttbar_sherpa_sum_clone->Scale(h_data->Integral()/h_mc_sherpa_sum->Integral());
    h_singletop_sherpa_sum_clone->Scale(h_data->Integral()/h_mc_sherpa_sum->Integral());
    h_diboson_sherpa_sum_clone->Scale(h_data->Integral()/h_mc_sherpa_sum->Integral());*/
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
  //  float mc_events_sherpa = h_mc_sherpa_sum->Integral();
  // cout << "MC sum (sherpa): " << mc_events_sherpa << endl;
  float data_events = h_data->Integral();
  cout << "Data sum: " << data_events << endl;

  float percent_difference = (data_events-mc_events)/data_events;
  cout << "Percentage difference: " << percent_difference << endl;
  //float percentage_difference_sherpa = (data_events-mc_events_sherpa)/data_events;
  // cout << "Percentage difference (sherpa): " << percentage_difference_sherpa << endl;
  float ratio = (data_events)/(mc_events);
  cout << "Ratio (Data/MC): " << ratio << endl;
  //float ratio_sherpa = (data_events)/(mc_events);
  //cout << "Ratio (sherpa): " << ratio_sherpa << endl;

  write_event_numbers(h_zmumu_sum,h_data,histo_name,lumi);

  //make n_jets tables
  if(var_2_plot == "n_jets" || var_2_plot == "n_jets_eta"){
    write_table(h_mc_sum, h_data, histo_name);
  }
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
    //h_data->GetYaxis()->SetRangeUser(y_min,y_max);
 }
  else{
    sum_stack->SetMaximum(y_max);
    sum_stack->SetMinimum(y_min);
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

  //  SetFormats(h_data,x_name,y_name);
  //  h_mc_sherpa_sum->SetLineStyle(2);
  //  h_data->SetXTitle(x_name);

  sum_stack->Draw("HIST");
  //  h_mc_sherpa_sum->Draw("HIST ELP SAME");
  h_data->Draw("HIST ELP SAME");
  sum_stack->GetXaxis()->SetRangeUser(x_min,x_max);
  if(var_2_plot == "n_jets" || var_2_plot == "n_bjets"){
    sum_stack->GetXaxis()->CenterTitle();
  }
  
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
  h_mc_sum_clone->SetLineColor(kRed);
  h_mc_sum_clone->Divide(h_data,h_mc_sum_clone);

  h_mc_sum_clone->SetMinimum(ratiomin);
  h_mc_sum_clone->SetMaximum(ratiomax);
 
  h_mc_sum_clone->SetMarkerStyle(20);
  h_mc_sum_clone->SetXTitle(x_name);
  h_mc_sum_clone->Draw("ep");

  /*  h_mc_sherpa_sum_clone->SetMinimum(ratiomin);
  h_mc_sherpa_sum_clone->SetMaximum(ratiomax);
  h_mc_sherpa_sum_clone->SetLineColor(kBlue);
  h_mc_sherpa_sum_clone->Divide(h_data,h_mc_sherpa_sum_clone);
  h_mc_sherpa_sum_clone->SetMarkerStyle(20);
  h_mc_sherpa_sum_clone->Draw("ep same");
  */
  pad1->cd();

  TLegend *legend = new TLegend(0.6,0.64,0.95,0.95);
  legend->SetTextSize(0.04);
  legend->AddEntry(h_data,"Data","lp");
  //  legend->AddEntry(h_mc_sherpa_sum,"Sherpa MC","lp");
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
  tex1->DrawLatex(0.19,0.9-0.03,mc_evt_label.c_str());

  TLatex *tex2 = new TLatex();
  tex2->SetNDC();
  string data_evt_label = "#font[18]{Data events: " + NumToStr(data_events) + "}";
  tex2->DrawLatex(0.19,0.9-0.001,data_evt_label.c_str());

  c1->cd();
  c1->Update();
}

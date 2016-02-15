////////////////macro for plotting Z+bb results //////////////
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
  //cutflow histogram used to get initial event count
  string cutflow_h_name = "ICUTZ";
  //plot luminosity
  double lumi;
  if(scale_to_lumi){
    //luminosity in picobarns
    //    lumi = 3865.57; //new cutflow sample, my data
    //    lumi = 3924.93; //new cutflow sample, Nov 2
    //    lumi = 2296.41; //bug corrected
    //    lumi = 3394.65; //bug not corrected
    //lumi = 3019.86; //b-tag sample
    // lumi = 3664.42; //b-tag 2 sample (includes narrow eta)
    //    lumi = 3201.51; //first packages run
    lumi = 3413.06; //second packages run
  }
  else{
    lumi = 5000.0;
  }
  TString histo_name; //histogram name
  TString x_name;     //x-axis label
  TString y_name;     //y-axis label
  double x_min, x_max, y_min, y_max; //axis min and max values
  int rebin;

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
    y_min = 0.1; y_max = 100000000;
    rebin = 1;
  }
  else if(var_2_plot == "mu_eta"){
    histo_name = "mu_eta"; //after Z selection
    x_name = "#eta^{#mu}";
    y_name = "Events";
    x_min = -3; x_max = 3;
    y_min = 0.1; y_max = 100000000;
    rebin = 1;
  }
  else if(var_2_plot == "dimu_mass"){
    histo_name = "dimuon_mass"; //before Z mass window cut
    x_name = "m_{#mu#mu} [GeV]";
    y_name = "Events";
    x_min = 0; x_max = 200;
    y_min = 0.1; y_max = 1000000000;
    rebin = 1;
  }
  else if(var_2_plot == "Z_mass"){
    histo_name = "Z_mass"; //after Z mass window cut
    x_name = "m_{#mu#mu} [GeV]";
    y_name = "Events";
    x_min = 70; x_max = 110;
    y_min = 1; y_max = 100000000;
    rebin = 1;
  }
  else if(var_2_plot == "Z_y"){
    histo_name = "Z_y";
    x_name = "Z rapidity";
    y_name = "Events";
    x_min = -3.5; x_max = 3.5;
    y_min = 0.1; y_max = 100000000;
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
  else if(var_2_plot == "Z_pt"){
    histo_name = "Z_pT";
    x_name = "Z p_{T}";
    x_min = 0; x_max = 500.;
    y_min = 0.1; y_max = 100000000;
    rebin = 10;
  }
  else if(var_2_plot == "met"){
    histo_name = "met";
    x_name = "MET";
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
    x_min = 0.; x_max = 500.;
    y_min = 0.1; y_max = 1000000000;
    rebin = 20;
  }
  else if(var_2_plot == "jet_n_35"){
    histo_name = "jet_n35";
    x_name = "#jets/event (pT > 35 GeV)";
    x_min = 0; x_max = 12;
    y_min = 0.1; y_max = 1000000000;
    rebin = 1;
  }
  else if(var_2_plot =="jet_n_40"){
    histo_name = "jet_n40";
    x_name = "#jets/event (pT > 40 GeV)";
    x_min =0; x_max = 12;
    y_min =0.1; y_max = 1000000000;
    rebin = 1;
  }
  else if(var_2_plot =="jet_n_45"){
    histo_name = "jet_n45";
    x_name = "#jets/event (pT > 45 GeV)";
    x_min =0; x_max = 12;
    y_min =0.1; y_max = 1000000000;
    rebin = 1;
  }
  else if(var_2_plot =="jet_n_50"){
    histo_name = "jet_n50";
    x_name = "#jets/event (pT > 50 GeV)";
    x_min =0; x_max = 12;
    y_min =0.1; y_max = 1000000000;
    rebin =1;
  }
  else if(var_2_plot =="jet_n_55"){
    histo_name = "jet_n55";
    x_name = "#jets/event (pT > 55 GeV)";
    x_min =0; x_max = 12;
    y_min =0.0001; y_max = 1000000000;
    rebin =1;
  }
  else if(var_2_plot =="jet_n_60"){
    histo_name = "jet_n60";
    x_name = "#jets/event (pT > 60 GeV)";
    x_min =0; x_max = 12;
    y_min =0.0001; y_max = 1000000000;
    rebin =1;
  }
  else if(var_2_plot == "jet_y"){
    histo_name = "jet_y";
    x_name = "jet rapidity";
    x_min = -5; x_max = 5;
    y_min = 0.1; y_max = 1000000000;
    rebin =1;
  }
  else if(var_2_plot == "jet_st"){
    histo_name = "jet_st";
    x_name = "ST [GeV]";
    x_min = 25.; x_max = 500.;
    y_min = 0.1; y_max = 1000000000;
    rebin =20;
  }
  else if(var_2_plot == "jet_ht"){
    histo_name = "jet_mu_ht";
    x_name = "ST [GeV]";
    x_min = 50.; x_max = 1000.;
    y_min = 0.1; y_max = 1000000000;
    rebin =20;
  }
  else if(var_2_plot == "dijet_m"){
    histo_name = "dijet_m";
    x_name = "m_{jj} [GeV]";
    x_min = 0.; x_max = 1000.;
    y_min = 0.1; y_max = 100000000;
    rebin = 20;
  }
  else if(var_2_plot == "n_bjets"){
    histo_name = "met100_bjetn";
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
    rebin = 10;
  }
  else if(var_2_plot == "bjet_y"){
    histo_name = "bjet_y";
    x_name = "b-jet rapidity";
    x_min = -3.5; x_max = 3.5;
    y_min = 0.1; y_max = 1000000;
    rebin = 5;
  }
  else if(var_2_plot == "bjet_lead_pt"){
    histo_name = "bjet_lead_pt";
    x_name = "p_{T}(leading b-jet) [GeV]";
    x_min =0.;x_max =500;
    y_min = 0.1; y_max = 100000;
    rebin = 10;
  }
  else if(var_2_plot == "bjet_sublead_pt"){
    histo_name = "bjet_sublead_pt";
    x_name = "p_{T}(subleading b-jet) [GeV]";
    x_min =0.;x_max =200;
    y_min = 0.1; y_max = 1000000;
    rebin = 10;
  }
  else if(var_2_plot == "bjet_mass"){
    histo_name = "bjet_m_bb";
    x_name = "m(b,b) [GeV]";
    x_min = 0.; x_max = 350;
    y_min = 0.1; y_max = 40;
    rebin = 10;
  }
  else if(var_2_plot == "deltaR_bb"){
    histo_name = "bjet_delR_bb";
    x_name = "#Delta R (b,b)";
    x_min = 0.; x_max = 5.5;
    y_min = 0.1; y_max = 50;
    rebin = 2;
  }
  else if(var_2_plot == "deltaphi_bb"){
    histo_name ="bjet_delphi_bb";
    x_name = "#Delta#phi (b,b)";
    x_min = 0.; x_max = 4.;
    y_min = 0.1; y_max = 50;
    rebin = 2;
  }
  else if(var_2_plot == "deltaR_Zb"){
    histo_name = "bjet_delR_Zb";
    x_name = "#Delta R(Z,b)";
    x_min = 0.; x_max = 5.5;
    y_min = 0.1; y_max = 1500;
    rebin = 2;
  }
  else if(var_2_plot == "deltaphi_Zb"){
    histo_name = "bjet_deltaphi_bZ";
    x_name = "#Delta #phi (Z,b)";
    x_min = 0; x_max = 3.5;
    y_min = 0.1; y_max = 1200;
    rebin = 2;
  }
  else if(var_2_plot == "deltaeta_Zb"){
    histo_name = "bjet_deltaeta_Zb";
    x_name = "#Delta#eta (Z,b)";
    x_min = 0.; x_max = 5.5;
    y_min = 0.1; y_max = 800;
    rebin = 2;
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
    y_min = 0.1; y_max = 50;
    rebin = 10;
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
  else{
    cout << "This variable is not supported" << endl;
    exit(0);
  }
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
~~~~~~~~~~~~MC CROSS SECTIONS~~~~~~~~~~~~~~~~~~~~
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  double xsec = 0;
  /*~~~~~~~~~~~~~~~~~~~Zmumu_NpX~~~~~~~~~~~~~~~~~~~~~~~~~*/
  //Datasets 147113 through 147118 (AlpgenPythia_Auto_P2011C_ZmumuNpX)
  //note: Np2 uses eta-corrected tag (e3405)
  string zmumu_process = "zmumu";
  vector<double> zmumu_xsec;
  double sigma_zmumu[6] = {719.16, 175.74, 58.882, 15.673, 4.0057, 1.2544};
  //7 TeV cross sections (for comparing)
  //  double sigma_zmumu[6] = {675.60,153.38,49.369,12.569,3.0427,0.83944};
  double k_factor_zmumu = 1.18;
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
  double sigma_zmumubb[4] = {6.5056, 3.2909, 1.2585, 0.61808};
  double k_factor_zmumubb = 1.18;
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
  double sigma_zmumucc[4] = {11.795, 4.1254, 3.3694, 1.7003};
  double k_factor_zmumucc = 1.18;
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
  /*~~~~~~~~~~~~~~~~~~~~~~~tt-bar~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  //dataset 117050
  //x-section source: https://twiki.cern.ch/twiki/bin/viewauth/AtlasProtected/TopMC12DiTopSamples
  string ttbar_process = "ttbar";
  vector<double> ttbar_xsec;
  double sigma_ttbar[1] = {114.49};
  double k_factor_ttbar = 1.1994;
  double eff_ttbar = 1.0;
  for(int i=0; i<1; i++){
    xsec = sigma_ttbar[i]*k_factor_ttbar*eff_ttbar;
    ttbar_xsec.push_back(xsec);
  }
  /*~~~~~~~~~~~~~~~~~~single top~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  //datasets 117361, 108346, 108344 (AcerMCPythia, MC@NLOJimmy
  //x-section source: AMI
  //k-factor source:  https://twiki.cern.ch/twiki/bin/viewauth/AtlasProtected/TopMC12SingleTopSamples
  string singletop_process = "singletop";
  vector<double> singletop_xsec;
  double sigma_singletop[3] = {8.5889, 20.666,0.56430};
  double k_factor_singletop[3] = {1.1035,1.0736,1.0737};
  double eff_singletop = 1.0;
  for(int i=0; i<3; i++){
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
  string mc_path = "/n/atlas02/user_codes/looper.6/Vbb/analysis_code/MC_histograms/";

  //Zmumu_NpX
  string mc_type_zmumu = "Zmumu_Np";
  const int n_files_zmumu = 6;
  TFile * fzmumu[6];
  string zmumu_name;
  for(int i=0;i<6;i++){
    zmumu_name = mc_path + "ZmumuNp" + NumToStr(i) + "_hists.root";
    fzmumu[i] = TFile::Open(zmumu_name.c_str(),"UPDATE");
    cout << "MC file : " << zmumu_name << endl;
  }
  TH1D * h_zmumu_array[6];

  //Zmumubb_NpX
  string mc_type_zmumubb = "Zmumubb_Np";
  const int n_files_zmumubb = 4;
  TFile *fzmumubb[4];
  string zmumubb_name;
  for(int i=0;i<4;i++){
    zmumubb_name = mc_path + "ZmumubbNp" + NumToStr(i) + "_hists.root";
    fzmumubb[i] = TFile::Open(zmumubb_name.c_str(),"UPDATE");
    cout << "MC file: " << zmumubb_name << endl;
  }
  TH1D * h_zmumubb_array[4];

  //Zmumucc_NpX
  string mc_type_zmumucc = "Zmumucc_Np";
  const int n_files_zmumucc = 4;
  TFile *fzmumucc[4];
  string zmumucc_name;
  for(int i=0;i<4;i++){
    zmumucc_name = mc_path + "ZmumuccNp" + NumToStr(i) + "_hists.root";
    fzmumucc[i] = TFile::Open(zmumucc_name.c_str(),"UPDATE");
    cout << "MC file: " << zmumucc_name << endl;
  }
  TH1D * h_zmumucc_array[4];

  //Ztautau_NpX
  string mc_type_ztautau = "Ztautau_Np";
  const int n_files_ztautau = 6;
  TFile *fztautau[6];
  string ztautau_name;
  for(int i=0; i<6; i++){
    ztautau_name = mc_path + "ZtautauNp" + NumToStr(i) + "_hists.root";
    fztautau[i] = TFile::Open(ztautau_name.c_str(),"UPDATE");
    cout << "MC file: " << ztautau_name << endl;
  }
  TH1D *h_ztautau_array[6];

  //tt-bar
  string mc_type_ttbar = "ttbar";
  const int n_files_ttbar = 1;
  TFile *fttbar[1];
  string ttbar_name = mc_path + mc_type_ttbar + "_hists.root";
  fttbar[0] = TFile::Open(ttbar_name.c_str(),"UPDATE");
  cout << "MC file: " << ttbar_name << endl;
  TH1D *h_ttbar_array[1];

  //single top
  string mc_type_singletop = "singletop";
  const int n_files_singletop = 3;
  TFile *fsingletop[3];
  string singletop_name;
  for(int i=0; i<3; i++){
    if(i==0) singletop_name = mc_path + "singletop_tchan_mu_hists.root";
    else if(i==1) singletop_name = mc_path + "singletop_WtChanIncl_hists.root";
    else if(i==2) singletop_name = mc_path + "singletop_SChan_Wmunu_hists.root";
    fsingletop[i] = TFile::Open(singletop_name.c_str(),"UPDATE");
    cout << "MC file: " << singletop_name << endl;
  }
  TH1D *h_singletop_array[3];

  //Diboson
  string mc_type_diboson = "diboson";
  const int n_files_diboson = 3;
  TFile *fdiboson[3];
  string diboson_name;
  for(int i=0; i<3; i++){
    if(i==0) diboson_name = mc_path + "WW" + "_hists.root";
    else if(i==1) diboson_name = mc_path + "ZZ" + "_hists.root";
    else if(i==2) diboson_name = mc_path + "WZ" + "_hists.root";
    fdiboson[i] = TFile::Open(diboson_name.c_str(),"UPDATE");
    cout << "MC file: " << diboson_name << endl;
  }
  TH1D *h_diboson_array[3];

  //====================
  //===== Data =========
  //====================
  //My data
  string data_path = "/n/atlas02/user_codes/looper.6/Vbb/analysis_code/data_histograms/";
  TFile *fdata;
  string data_name = data_path + "data_hists.root";
  fdata = TFile::Open(data_name.c_str(),"UPDATE");
  TH1D *h_data = (TH1D*)fdata->Get(histo_name);
  cout << "Data file: " << data_name << endl;
  h_data->GetXaxis()->SetRangeUser(x_min,x_max);

  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    ~~~~~~~~~~~~~~~ADD HISTOGRAMS~~~~~~~~~~~~~~~~~
    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

  //Add MC histograms by process: function add_histo is defined in header file
  //Zmumu
  TH1D *h_zmumu_sum = add_histo(fzmumu,n_files_zmumu,histo_name,zmumu_xsec,cutflow_h_name,lumi,h_zmumu_array,zmumu_process,x_min,x_max);
  TH1D *h_zmumubb_sum = add_histo(fzmumubb,n_files_zmumubb,histo_name,zmumubb_xsec,cutflow_h_name,lumi,h_zmumubb_array,zmumubb_process,x_min,x_max);
  TH1D *h_zmumucc_sum = add_histo(fzmumucc,n_files_zmumucc,histo_name,zmumucc_xsec,cutflow_h_name,lumi,h_zmumucc_array,zmumucc_process,x_min,x_max);
  TH1D *h_ztautau_sum = add_histo(fztautau,n_files_ztautau,histo_name,ztautau_xsec,cutflow_h_name,lumi,h_ztautau_array,ztautau_process,x_min,x_max);
  TH1D *h_ttbar_sum = add_histo(fttbar,n_files_ttbar,histo_name,ttbar_xsec,cutflow_h_name,lumi,h_ttbar_array,ttbar_process,x_min,x_max);
  TH1D *h_singletop_sum = add_histo(fsingletop,n_files_singletop,histo_name,singletop_xsec,cutflow_h_name,lumi,h_singletop_array,singletop_process,x_min,x_max);
  TH1D *h_diboson_sum = add_histo(fdiboson,n_files_diboson,histo_name,diboson_xsec,cutflow_h_name,lumi,h_diboson_array,diboson_process,x_min,x_max);

  h_zmumu_sum->SetFillColor(kBlue);
  h_zmumubb_sum->SetFillColor(kYellow);
  h_zmumucc_sum->SetFillColor(kGreen);
  h_ztautau_sum->SetFillColor(kCyan);
  h_ttbar_sum->SetFillColor(kViolet);
  h_singletop_sum->SetFillColor(kRed+1);
  h_diboson_sum->SetFillColor(kOrange);

  gStyle->SetOptStat("");


  /*****************************************
   ***********WRITE HISTS TO FILE *********
   ****************************************/

  string plt_path = "/n/atlas02/user_codes/looper.6/Vbb/analysis_code/plots/";
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
    h_zmumu_sum->Rebin(rebin);
    h_zmumubb_sum->Rebin(rebin);
    h_zmumucc_sum->Rebin(rebin);
    h_ztautau_sum->Rebin(rebin);
    h_ttbar_sum->Rebin(rebin);
    h_singletop_sum->Rebin(rebin);
    h_diboson_sum->Rebin(rebin);
    h_data->Rebin(rebin);
  }
  h_zmumu_sum->GetXaxis()->SetRangeUser(x_min,x_max);
  h_zmumubb_sum->GetXaxis()->SetRangeUser(x_min,x_max);
  h_zmumucc_sum->GetXaxis()->SetRangeUser(x_min,x_max);
  h_ztautau_sum->GetXaxis()->SetRangeUser(x_min,x_max);
  h_ttbar_sum->GetXaxis()->SetRangeUser(x_min,x_max);
  h_singletop_sum->GetXaxis()->SetRangeUser(x_min,x_max);
  h_diboson_sum->GetXaxis()->SetRangeUser(x_min,x_max);
  h_data->GetXaxis()->SetRangeUser(x_min,x_max);

  TH1D *h_mc_sum = (TH1D*)h_zmumu_sum->Clone();
  TH1D *h_zmumu_sum_clone = (TH1D*)h_zmumu_sum->Clone();
  TH1D *h_zmumubb_sum_clone = (TH1D*)h_zmumubb_sum->Clone();
  TH1D *h_ztautau_sum_clone = (TH1D*)h_ztautau_sum->Clone();
  TH1D *h_zmumucc_sum_clone = (TH1D*)h_zmumucc_sum->Clone();
  TH1D *h_ttbar_sum_clone = (TH1D*)h_ttbar_sum->Clone();
  TH1D *h_singletop_sum_clone = (TH1D*)h_singletop_sum->Clone();
  TH1D *h_diboson_sum_clone = (TH1D*)h_diboson_sum->Clone();

  h_mc_sum->Add(h_zmumubb_sum_clone);
  h_mc_sum->Add(h_zmumucc_sum_clone);
  h_mc_sum->Add(h_ztautau_sum_clone);
  h_mc_sum->Add(h_ttbar_sum_clone);
  h_mc_sum->Add(h_singletop_sum_clone);
  h_mc_sum->Add(h_diboson_sum_clone);



  //rescale attempt

  TH1D *h_mc_sum_temp =(TH1D*)h_mc_sum->Clone();
  h_mc_sum_temp->Scale(h_data->Integral()/h_mc_sum->Integral());
  h_singletop_sum_clone->Scale(h_data->Integral()/h_mc_sum->Integral());
  h_ttbar_sum_clone->Scale(h_data->Integral()/h_mc_sum->Integral());
  h_diboson_sum_clone->Scale(h_data->Integral()/h_mc_sum->Integral());
  h_ztautau_sum_clone->Scale(h_data->Integral()/h_mc_sum->Integral());
  h_zmumucc_sum_clone->Scale(h_data->Integral()/h_mc_sum->Integral());
  h_zmumu_sum_clone->Scale(h_data->Integral()/h_mc_sum->Integral());
  h_zmumubb_sum_clone->Scale(h_data->Integral()/h_mc_sum->Integral());

  sum_stack->Add(h_singletop_sum_clone);
  sum_stack->Add(h_ttbar_sum_clone);
  sum_stack->Add(h_diboson_sum_clone);
  sum_stack->Add(h_ztautau_sum_clone);
  sum_stack->Add(h_zmumucc_sum_clone);
  sum_stack->Add(h_zmumu_sum_clone);
  sum_stack->Add(h_zmumubb_sum_clone);
  //  h_zmumu_sum_clone->SetFillColor(kBlue);
  //h_zmumubb_sum_clone->SetFillColor(kYellow);

  TH1D *h_mc_sum_forshape = (TH1D*)h_mc_sum->Clone();
  TH1D *h_data_forshape = (TH1D*)h_data->Clone();
  double temp_norm = 1.0;
  //Edits for scaling to data
  h_mc_sum_forshape->Scale(h_data_forshape->Integral()/h_mc_sum_forshape->Integral());
  //  h_data_forshape->Scale(temp_norm/h_data_forshape->Integral());
  double shape_max =  h_data_forshape->GetMaximum();
  h_mc_sum_forshape->SetMaximum(shape_max*5);
  h_data_forshape->SetMaximum(shape_max*5);

  float mc_events = h_mc_sum->Integral();
  cout << "MC sum: " << mc_events << endl;
  float data_events = h_data->Integral();
  cout << "Data sum: " << data_events << endl;
  if(!scale_to_lumi){
    mc_events = h_mc_sum_forshape->Integral();
    data_events = h_data_forshape->Integral();
    cout << "MC sum (integral == 1): " << mc_events << endl;
    cout << "Data sum (integral == 1): " << data_events << endl;
  }

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
  //  TCanvas *c2 = new TCanvas("shapeplot","shapeplot",800,800);

  float mc_max = h_mc_sum->GetMaximum();
  float data_max = h_data->GetMaximum();
  //plot the histogram with the larger number of events first (makes the y-axis range correct)
  if(make_log){
    //    sum_stack->SetMaximum(data_max*3.5);
    sum_stack->SetMaximum(y_max);
  }
  else{
    //    sum_stack->SetMaximum(data_max*3.5);
    sum_stack->SetMaximum(y_max);
  }
  sum_stack->SetMinimum(y_min);
    

  cout << "mc max: " << mc_max << endl;
  cout << "data max: " << data_max << endl;

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

  SetFormats(h_data,x_name,y_name);

  if(scale_to_lumi){
    sum_stack->Draw("HIST");
    h_data->Draw("HIST ELP SAME");
    sum_stack->GetXaxis()->SetRangeUser(x_min,x_max);
    if(var_2_plot == "n_jets" || var_2_plot == "n_bjets"){
      sum_stack->GetXaxis()->CenterTitle();
    }
  }
  else{
    h_mc_sum_forshape->Draw("HIST");
    h_data_forshape->Draw("HIST P SAME");
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

  if(scale_to_lumi){
    h_mc_sum_temp->SetStats(0);
    h_mc_sum_temp->SetMarkerSize(0.5);
    h_mc_sum_temp->GetYaxis()->SetTickLength(0.04);
    h_mc_sum_temp->GetYaxis()->SetNdivisions(305);
    h_mc_sum_temp->GetXaxis()->SetLabelSize(0.04*3./1.);
    h_mc_sum_temp->GetXaxis()->SetTitleSize(0.04*3./1.);
    h_mc_sum_temp->GetYaxis()->SetLabelSize(0.04*3./1.);
    h_mc_sum_temp->GetYaxis()->SetTitleSize(0.04*3./1.);
    h_mc_sum_temp->GetXaxis()->SetTitleOffset(1.2);
    h_mc_sum_temp->GetYaxis()->SetTitleOffset(1.2/2.);
    h_mc_sum_temp->GetXaxis()->SetTitle("");
    //change back
    //    h_mc_sum_temp->GetYaxis()->SetTitle("MC/Data");
    h_mc_sum_temp->GetYaxis()->SetTitle("Data/MC");
    h_mc_sum_temp->SetLineColor(kRed);
    
    // Divide: change this back
    //    h_mc_sum_temp->Divide(h_data);
    h_mc_sum_temp->Divide(h_data,h_mc_sum_temp);
    //    h_mc_sum_temp->Divide(h_mc_sum_temp,h_data);
    if(var_2_plot == "mu_pt_Z" || var_2_plot == "mu_eta" || var_2_plot == "mu_phi" || var_2_plot == "Z_mass" || var_2_plot == "Z_pt" || var_2_plot == "Z_y"){
      h_mc_sum_temp->SetMinimum(0.75);
      h_mc_sum_temp->SetMaximum(1.25);
    }
    else{
      h_mc_sum_temp->SetMinimum(0.45);
      h_mc_sum_temp->SetMaximum(1.85);
    }
    h_mc_sum_temp->SetMarkerStyle(20);
    if(var_2_plot=="n_jets" || var_2_plot=="n_bjets"){
      //      h_mc_sum_temp->GetXaxis()->CenterTitle();
    }
    h_mc_sum_temp->Draw("ep");
  }
  else{
    TH1D *h_mc_sum_shape_clone = (TH1D*)h_mc_sum_forshape->Clone();
    h_mc_sum_shape_clone->SetStats(0);
    h_mc_sum_shape_clone->SetMarkerSize(0.5);
    h_mc_sum_shape_clone->GetYaxis()->SetTickLength(0.04);
    h_mc_sum_shape_clone->GetYaxis()->SetNdivisions(305);
    h_mc_sum_shape_clone->GetXaxis()->SetLabelSize(0.04*3./1.);
    h_mc_sum_shape_clone->GetXaxis()->SetTitleSize(0.04*3./1.);
    h_mc_sum_shape_clone->GetYaxis()->SetLabelSize(0.04*3./1.);
    h_mc_sum_shape_clone->GetYaxis()->SetTitleSize(0.04*3./1.);
    h_mc_sum_shape_clone->GetXaxis()->SetTitleOffset(1.2);
    h_mc_sum_shape_clone->GetYaxis()->SetTitleOffset(1.2/2.);
    h_mc_sum_shape_clone->GetXaxis()->SetTitle("");
    //Change this back
    h_mc_sum_shape_clone->GetYaxis()->SetTitle("MC/Data");
    h_mc_sum_shape_clone->SetLineColor(kRed);
    h_mc_sum_shape_clone->Divide(h_data_forshape);
    h_mc_sum_shape_clone->SetMinimum(0.35);
    h_mc_sum_shape_clone->SetMaximum(1.75);
    h_mc_sum_shape_clone->SetMarkerStyle(20);
    h_mc_sum_shape_clone->Draw("hist p");
  }
  pad1->cd();

  //  TLegend *legend = new TLegend(0.6,0.70,0.95,0.95);
  TLegend *legend = new TLegend(0.6,0.64,0.95,0.95);
  legend->SetTextSize(0.04);
  legend->AddEntry(h_data,"Data","lp");
  legend->AddEntry(h_zmumubb_sum_clone,"Z(#rightarrow#mu#mu)+bb+jets MC","f");
  legend->AddEntry(h_zmumu_sum_clone,"Z(#rightarrow#mu#mu)+jets MC","f");
  legend->AddEntry(h_zmumucc_sum_clone,"Z(#rightarrow#mu#mu)+cc+jets MC","f");
  legend->AddEntry(h_ztautau_sum_clone,"Z#rightarrow#tau#tau+jets MC","f");
  legend->AddEntry(h_diboson_sum_clone,"Diboson MC","f");
  legend->AddEntry(h_ttbar_sum_clone,"tt-bar MC","f");
  legend->AddEntry(h_singletop_sum_clone, "single-top MC","f");
  if(scale_to_lumi){
    legend->Draw();
  }
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
  //  c2->cd();
}

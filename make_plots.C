#include <TROOT.h>
#include <iostream>
#include <string>
#include <vector>

void make_plots(){

  //  vector<string> plots_log_true;
  //vector<string> plots_log_false;
 
  string plots_log_true[37] = {"mu_pt_Z", "mu_phi", "mu_eta", "Z_mass", "Z_mass_MET", "Z_mass_1b", "Z_y", "Z_eta", "Z_phi", "Z_pt",
		    "met", "met_1tag", "n_jets", "n_jets_tight", "jet_pt", "jet_pt_tight", "jet_pt_met", "lead_jet_pt",
		    "lead_jet_pt_tight", "jet_y", "jet_y_tight", "jet_st", "jet_st_tight", "jet_ht", "jet_ht_tight", "dijet_m",
		    "dijet_m_tight","n_bjets", "bjet_pt", "bjet_y", "bjet_lead_pt", "bjet_sublead_pt", "deltaR_Zb", 
		    "deltaphi_Zb", "deltaeta_Zb", "mv1cweight", "pileup"};
  
  string plots_log_false[5] = {"bjet_mass", "deltaR_bb", "deltaphi_bb", "deltaeta_bb", "bjet_pt_bb"};

  gROOT->LoadMacro("analysis_plots.C+");
  //  analysis_plots("Z_mass",true,true,true);
  
  for(unsigned int i=0; i < 37; i++){
    analysis_plots(plots_log_true[i], true, true, true);
  }
  for(unsigned int j=0; j < 5; j++){
    analysis_plots(plots_log_false[j], true, false, true);
  }

}

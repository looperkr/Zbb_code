#include <TROOT.h>
#include <iostream>
#include <string>
#include <vector>

void make_plots(){
 
  string plots_log_true[54] = {"Z_eta","Z_mass","Z_mass_0j","Z_mass_1b","Z_mass_1j","Z_mass_1j_MET","Z_mass_1j_tight_MET","Z_mass_2b","Z_mass_MET","Z_mass_exactly0j","Z_phi","Z_y","bjet_lead_pt","bjet_mass","bjet_pt","bjet_sublead_pt","bjet_y","deltaR_Zb","deltaeta_Zb","deltaphi_Zb","dijet_m","dijet_m_tight","dijet_m_tightmet","jet_ht","jet_ht_tight","jet_ht_tightmet","jet_pt","jet_pt_tight","jet_pt_tightmet","jet_st","jet_st_tight","jet_st_tightmet","jet_y","jet_y_tight","jet_y_tightmet","lead_jet_pt","lead_jet_pt_tight","lead_jet_pt_tightmet","lead_jet_y","m_mumu","met","met_1tag","mu_eta","mu_phi","mu_pt","mu_pt_Z","mv1c_bins","mv1cweight","n_bjets","n_jets","n_jets_tight","n_jets_tightmet","pileup","pileup_noweight"};

  string plots_log_false[5] = {"bjet_mass", "deltaR_bb", "deltaphi_bb", "deltaeta_bb", "bjet_pt_bb"};

  gROOT->LoadMacro("analysis_plots.C+");
  //  analysis_plots("Z_mass",true,true,true);
  
  for(unsigned int i=0; i < 39; i++){
    analysis_plots(plots_log_true[i], true, true, true);
  }
  for(unsigned int j=0; j < 5; j++){
    analysis_plots(plots_log_false[j], true, false, true);
  }

}

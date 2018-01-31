#include <TROOT.h>
#include <iostream>
#include <string>
#include <vector>

void make_plots(){

  const int log_true = 64;
  const int bjets = 9;
  const int log_false = 5;
 
  string plots_log_true[log_true] = {"Z_eta","Z_mass","Z_mass_0j","Z_mass_1b","Z_mass_1j","Z_mass_1j_MET","Z_mass_1j_tight_MET","Z_mass_2b","Z_mass_MET","Z_mass_exactly0j","Z_phi","Z_y","Z_pt","dijet_m","dijet_m_tight","dijet_m_tightmet","jet_ht","jet_ht_tight","jet_ht_tightmet","jet_pt","jet_pt_tight","jet_pt_tightmet","jet_st","jet_st_tight","jet_st_tightmet","jet_y","jet_y_tight","jet_y_tightmet","lead_jet_pt","lead_jet_pt_tight","lead_jet_pt_tightmet","lead_jet_y","m_mumu","met","met_1tag","mu_eta","mu_phi","mu_pt","mu_pt_Z","mv1c_bins","mv1cweight","n_jets","n_jets_tight","n_jets_tightmet","pileup","pileup_noweight","light_jets","charm_jets","bottom_jets","light_jets_hmatch","charm_jets_hmatch","bottom_jets_hmatch","Z_mass_truth_dressed","Z_mass_match","Z_mass_unmatch","Z_mass_migration","Z_y_truth_dressed","Z_y_match","Z_y_unmatch","Z_y_migration","Z_pt_truth_dressed","Z_pt_match","Z_pt_unmatch","Z_pt_migration"};

  string plots_bjets[bjets] = {"bjet_lead_pt","bjet_mass","bjet_pt","bjet_sublead_pt","bjet_y","deltaR_Zb","deltaeta_Zb","deltaphi_Zb","n_bjets"};
  string plots_log_false[log_false] = {"bjet_mass", "deltaR_bb", "deltaphi_bb", "deltaeta_bb", "bjet_pt_bb"};

  gROOT->LoadMacro("analysis_plots.C+");
  //  analysis_plots("Z_mass",true,true,true);
  
  for(unsigned int i=0; i < log_true; i++){
    if(plots_log_true[i].substr(0,6) == "Z_mass"){
      analysis_plots(plots_log_true[i], true, true, true);
    }
  }
  /*  for(unsigned int l=0; l < bjets; l++){
    analysis_plots(plots_bjets[l], true, true, false);
  }
  for(unsigned int j=0; j < log_false; j++){
    analysis_plots(plots_log_false[j], true, false, true);
    }*/

}

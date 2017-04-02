#define analysis_Zmumu_cxx
// The following methods are defined in this file:
//    Begin():        called every time a loop on the tree starts,
//                    a convenient place to create your histograms.
//    SlaveBegin():   called after Begin(), when on PROOF called only on the
//                    slave servers.
//    Process():      called for each event, in this function you decide what
//                    to read and fill your histograms.
//    SlaveTerminate: called at the end of the loop on the tree, when on PROOF
//                    called only on the slave servers.
//    Terminate():    called at the end of the loop on the tree,
//                    a convenient place to draw/fit your histograms.
//
// To use this file, try the following session on your Tree T:
//
// Root > T->Process("analysis_Zmumu.C")
// Root > T->Process("analysis_Zmumu.C","some options")
// Root > T->Process("analysis_Zmumu.C+")
//

#include "analysis_Zmumu.h"
#include <TH2.h>
#include <TStyle.h>
#include <vector>
#include "TMath.h"
#ifdef __MAKECINT__
#pragma link C++ class vector<vector<float> >+;
#pragma link C++ class vector<vector<unsigned int> >+;

#endif


void analysis_Zmumu::Begin(TTree * /*tree*/)
{
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

}

void analysis_Zmumu::SlaveBegin(TTree * /*tree*/)
{
  // The SlaveBegin() function is called after the Begin() function.
   // When running with PROOF SlaveBegin() is called on each slave server.
   // The tree argument is deprecated (on PROOF 0 is passed).

   //run flags
  isMC = false;
  isData = !isMC;
  isArantxa = false;
  isGrid = false;
  
  TString option = GetOption();
  Info("Begin", "starting h1analysis with process option: %s", option.Data());

  if(isMC){
    TObjArray *toption = option.Tokenize(",");
    
    //   toption->Print();
    output_name = ((TObjString *)(toption->At(0)))->String();
    TString mapIndex_str = ((TObjString *)(toption->At(1)))->String();
    mapIndex = mapIndex_str.Atoi();
  }
  else{
    output_name = option;
  }

   //print current time
   time_t now = time(0);
   char* dt = ctime(&now);
   cout << "Starting time: " << dt << endl;

   //trigger matching counter 
   m_event_counter = 0;
   //   muon_matched = false; //set to true when trigger matching returns true

   //   run_evt_set = {};

   bch_bad = false; //true when bch flagged as bad

   n_TRT = 0;
   n_events = 0;
   n_zevents = 0;
   n_true_bjets = 0;
   n_passing_jets = 0;
   eventcheckcut = -1;
   h_good_zeroweight_events = new TH1D("good_zeroweight_events","good_zeroweight_events",1,0,1);
   h_good_zeroweight_events_pw = new TH1D("good_zeroweight_events_pw","good_zeroweight_events_pw",1,0,1);
   h_triggerSF_size = new TH1D("triggerSF","triggerSF",20000,0,5);
   h_Z_mumu = new TH1D("Z_mass","Dimuon mass spectrum (Z window)",20000,0,10000);
   h_Z_mumu_nopw = new TH1D("Z_mass_nopw","Dimuon mass spectrum (no pileup weighting)",20000,0,10000);
   h_Zmumu_hottile = new TH1D("Z_mass_hottile","Dimuon mass spectrum (Z window)",20000,0,10000);
   h_m_mumu = new TH1D("m_mumu","Dimuon mass spectrum (no window cut)",20000,0,10000);
   h_Z_mass_0j = new TH1D("Z_mass_0j","Dimuon mass spectrum (Z window)",20000,0,10000);
   h_Z_mass_1j = new TH1D("Z_mass_1j","Dimuon mass spectrum (Z window)",20000,0,10000);
   h_Z_mass_2j = new TH1D("Z_mass_2j","Dimuon mass spectrum (Z window)",20000,0,10000);
   h_Z_mass_3j = new TH1D("Z_mass_3j","Dimuon mass spectrum (Z window)",20000,0,10000);
   h_Z_mass_4j = new TH1D("Z_mass_4j","Dimuon mass spectrum (Z window)",20000,0,10000);
   h_Z_mass_5j = new TH1D("Z_mass_5j","Dimuon mass spectrum (Z window)",20000,0,10000);
   h_Z_mass_exactly0j = new TH1D("Z_mass_exactly0j","Dimuon mass spectrum (Z window), njets == 0",20000,0,10000);
   h_Z_mass_exactly1j = new TH1D("Z_mass_exactly1j","Dimuon mass spectrum (Z window), njets == 1",20000,0,10000);
   h_Z_mass_1b = new TH1D("Z_mass_1b","Dimuon mass spectrum (Z window), nbjets >= 1",20000,0,10000);
   h_Z_mass_2b = new TH1D("Z_mass_2b","Dimuon mass spectrum (Z window), nbjets >= 2",20000,0,10000);
   h_Z_pt = new TH1D("Z_pT", "Z boson pT", 4000, 0, 2000);
   h_Z_pt_nopw = new TH1D("Z_pT_nopw","Z boson pT (no pileup)", 4000,0,2000);
   h_Z_y = new TH1D("Z_y", "Z boson rapidity", 240,-6,6);
   h_Z_y_nopw = new TH1D("Z_y_nopw","Z boson rapidity (no pileup)",240,-6,6);
   h_Z_eta = new TH1D("Z_eta","Z boson #eta", 240,-6,6);
   h_Z_phi = new TH1D("Z_phi","Z boson #phi", 128,-2*TMath::Pi(),2*TMath::Pi());
   h_Z_phi_nopw = new TH1D("Z_phi_nopw","Z boson #phi",128,-2*TMath::Pi(),2*TMath::Pi());
   h_mu_pt = new TH1D("mu_pT","Single muon pT",4000,0,2000);
   h_mu_pt_nocut = new TH1D("mu_pt_nocut","Single muon pT (full range)",4000,0,2000);
   h_mu_eta_nocut = new TH1D("mu_eta_nocut","Single muon #eta (no pT or Z cuts)",120,-6,6);
   h_mu_eta = new TH1D("mu_eta", "Single muon #eta",120,-6,6);
   h_mu_iso = new TH1D("mu_iso","Muon isolation (no cut applied)",1000,0,1);
   h_mu_iso_cut = new TH1D("mu_iso_cut","Muon isolation (after cut applied)",1000,0,1);
   h_mu_phi_nocut = new TH1D("mu_phi_nocut","Single muon #phi (no pT or Z cuts)",128,-2*TMath::Pi(),2*TMath::Pi());
   h_mu_phi = new TH1D("mu_phi","Single muon #phi",128,-2*TMath::Pi(),2*TMath::Pi());
   h_cutflow = new TH1F("ICUTZ","ICUTZ",50,0.,50.);
   h_cutflow_w = new TH1F("ICUTZ_w","ICUTZ_w",50,0.,50.);
   //pileup reweighting histograms
   h_avg_pileup_norw = new TH1D("avg_pileup_norw","avg_pileup_norw",5000,0.,50.);
   h_avg_pileup_noprw = new TH1D("avg_pileup_noprw","avg_pileup_noprw",5000,0.,50.);
   h_pileup_norw = new TH1D("pileup_no_rw","pileup_no_rw",5000,0.,50.);
   h_pileup = new TH1D("pileup","pileup",5000,0.,50.);
   h_avg_pileup = new TH1D("avg_pileup","average pileup",5000,0.,50.);
   h_pileupSF = new TH1D("pileup_rw_sf","pileup reweighting scale factor",5000,-2.5,2.5);
   h_pileup_Zsel = new TH1D("pileup_Z","pileup (event with Z candidate)",5000,0.,50);
   h_pileup_Zsel_norw = new TH1D("pileup_Z_norw","pileup (event with Z candidate)",5000,0.,50);
   h_pileup_avg_Zsel = new TH1D("pileup_Z_avg","average pileup (event with Z candidate)",51,-0.5,50.5);
   h_pileup_avg_Zsel_norw = new TH1D("pileup_Z_avg_norw","average pileup (event with Z candidate)",51,-0.5,50.5);

   h_jet_pt = new TH1D("jet_pt","jet pT",4000,0,2000);
   h_jet_y = new TH1D("jet_y","jet rapidity",120,-6,6);
   h_jet_n = new TH1D("jet_n","number of jets per event",15,0,15);  
   h_jet_st = new TH1D("jet_st","ST",4000,0,2000);
   h_jet_mu_ht = new TH1D("jet_mu_ht","HT",4000,0,2000);
   h_leadjet_pt = new TH1D("jet_pt_lead","leading jet pT",4000,0,2000);
   h_leadjet_y = new TH1D("jet_y_lead","leading jet y",240,-6,6);
   h_subjet_pt = new TH1D("jet_pt_sublead","subleading jet pT",4000,0,2000);
   h_subjet_y = new TH1D("jet_y_sublead","subleading jet y",240,-6,6);
   h_dijet_m = new TH1D("dijet_m","dijet mass",4000,0,2000);
   h_dijet_dR = new TH1D("dijet_dR","#Delta R between jets",110,0,5.5);
   h_dijet_dphi = new TH1D("dijet_dphi","#Delta#phi between jets",160,-4,4);
   h_dijet_dy = new TH1D("dijet_dy","#Delta y between jets",200,-5,5);
   h_dijet_deta = new TH1D("dijet_deta","#Delta #eta between jets",200,-5,5);
   h_dijet_dR_eta = new TH1D("dijet_dR_eta","#Delta R between jets (calculated w/ #eta)",110,0,5.5);
   h_dijet_dR_y = new TH1D("dijet_dR_y", "#Delta R between jets (calculated w/ y)",110,0,5.5);
   h_3jet_pt = new TH1D("third_jet_pt","3rd jet pT",4000,0,2000);
   h_3jet_y = new TH1D("third_jet_y","3rd jet y",240,-6,6);
   h_4jet_pt = new TH1D("fourth_jet_pt","4th jet pT",4000,0,2000);
   h_4jet_y = new TH1D("fourth_jet_y","4th jet y",240,-6,6);
   h_Zpt_v_jj_pt = new TH2D("Zpt_v_jj_pt","Z pT v. dijet pT",4000,0,2000,4000,0,2000);

   //light jet distributions in tracking volume: |eta| < 2.4
   h_jet_n_tighteta = new TH1D("jet_n_tighteta","number of jets per event (|#eta| < 2.4)",15,0,15);
   h_jet_pt_tighteta = new TH1D("jet_pt_tighteta","jet pT (|#eta| < 2.4)",4000,0,2000);
   h_jet_y_tighteta = new TH1D("jet_y_tighteta","jet rapidity (|#eta| < 2.4)",120,-6,6);
   h_jet_st_tighteta = new TH1D("jet_st_tighteta","ST (|#eta| < 2.4)",4000,0,2000);
   h_jet_mu_ht_tighteta = new TH1D("jet_mu_ht_tighteta","HT (|#eta| < 2.4)",4000,0,2000);
   h_leadjet_pt_tighteta = new TH1D("jet_pt_lead_tighteta","leading jet pT (|#eta| < 2.4)",4000,0,2000);
   h_leadjet_y_tighteta = new TH1D("jet_y_lead_tighteta","leading jet y (|#eta| < 2.4)",240,-6,6);
   h_subjet_pt_tighteta = new TH1D("jet_pt_sublead_tighteta","subleading jet pT (|#eta| < 2.4)",4000,0,2000);
   h_subjet_y_tighteta = new TH1D("jet_y_sublead_tighteta","subleading jet y (|#eta| < 2.4)",240,-6,6);
   h_dijet_m_tighteta = new TH1D("dijet_m_tighteta","dijet mass (|#eta| < 2.4)",4000,0,2000);
   h_dijet_dR_tighteta = new TH1D("dijet_dR_tighteta","#Delta R between jets (|#eta| < 2.4)",110,0,5.5);
   h_dijet_dphi_tighteta = new TH1D("dijet_dphi_tighteta","#Delta#phi between jets (|#eta| < 2.4)",160,-4,4);
   h_dijet_dy_tighteta = new TH1D("dijet_dy_tighteta","#Delta y between jets (|#eta| < 2.4)",200,-5,5);
   h_dijet_deta_tighteta = new TH1D("dijet_deta_tighteta","#Delta #eta between jets (|#eta| < 2.4)",200,-5,5);

   h_Z_mass_MET = new TH1D("Z_mass_MET","Z mass after MET cut",4000,0,2000);
   h_Z_pt_MET = new TH1D("Z_pt_MET","Z pT after MET cut",4000,0,2000);
   h_njets_MET = new TH1D("njets_MET","N_jets after MET cut",12,0,12);
   h_jet_pt_MET = new TH1D("jet_pt_MET","jet pT after MET cut",4000,0,2000);
   h_leadjet_pt_MET = new TH1D("jet_leading_pt_MET","Leading jet pT after MET cut",4000,0,2000);
   h_dijet_m_MET = new TH1D("dijet_m_MET","Dijet mass after MET cut",4000,0,2000);
   h_Zpt_v_jj_pt_MET = new TH2D("Zpt_v_jj_pt_MET","Zpt versus dijet pT after MET cut",4000,0,2000,4000,0,2000);
   h_jet_st_MET = new TH1D("jet_st_MET","ST after MET cut",4000,0,2000);
   h_jet_mu_ht_MET = new TH1D("jet_ht_MET","HT after MET cut",4000,0,2000);

   h_mv1weight = new TH1D("mv1weight","mv1weight",500,0,1);
   h_mv1cweight = new TH1D("mv1cweight","mv1cweight",500,0,1);

   tagging_bins[0] = 0.;
   tagging_bins[1] = 0.4051;
   tagging_bins[2] = 0.7068;
   tagging_bins[3] = 0.8349;
   tagging_bins[4] = 0.9195;
   tagging_bins[5] = 1.;

   h_mv1cweight_binned = new TH1D("mv1cweight_binned","mv1c weights", 5, tagging_bins);
   //following three are MC only
   h_mv1cweight_light = new TH1D("mv1cweight_light","mv1c weight (light)", 5, tagging_bins);
   h_mv1cweight_charm = new TH1D("mv1cweight_charm","mv1c weight (charm)", 5, tagging_bins);
   h_mv1cweight_bottom = new TH1D("mv1cweight_bottom","mv1c weight (bottom)", 5, tagging_bins);

   h_bjet_n = new TH1D("bjet_n","Number of b-tagged jets",12,0,12);
   h_bjet_pt = new TH1D("bjet_pt","b-tagged jet pT",4000,0,2000);
   h_bjet_lead_pt = new TH1D("bjet_lead_pt","Leading tagged jet pT",4000,0,2000);
   h_bjet_sublead_pt = new TH1D("bjet_sublead_pt","Subleading tagged jet pT",4000,0,2000);
   h_bjet_y = new TH1D("bjet_y","b-tagged jet rapidity",240,-6,6);
   h_bjet_m_bb = new TH1D("bjet_m_bb","Dijet mass (two b-tags)",4000,0,2000);
   //_mv1c => highest tag weight jets instead of leading and subleading
   h_bjet_m_bb_mv1c = new TH1D("bjet_m_bb_mv1c","Diijet mass (two b-tags, highest mv1c weight)",4000,0,2000);
   h_bjet_deltaR_bb = new TH1D("bjet_delR_bb","#Delta R(b,b)",120,0,6);
   h_bjet_deltaR_bb_mv1c = new TH1D("bjet_delR_bb_mv1c","#Delta R(b,b) (MV1c)",120,0,6);
   h_bjet_deltaphi_bb = new TH1D("bjet_delphi_bb","#Delta#phi(b,b)",160,-4,4);
   h_bjet_deltaphi_bb_mv1c = new TH1D("bjet_delphi_bb_mv1","#Delta#phi(b,b) (MV1)",160,-4,4);
   h_bjet_deltaR_Zb = new TH1D("bjet_delR_Zb","#Delta R(Z,b)",120,0,6);
   h_bjet_deltaR_Zb_mv1c = new TH1D("bjet_delR_Zb_mv1c","#Delta R(Z,b) (MV1c)",120,0,6);
   h_bjet_deltaphi_Zb = new TH1D("bjet_deltaphi_bZ","#Delta#phi(Z,b)",200,0,10);
   h_bjet_deltaphi_Zb_mv1c = new TH1D("bjet_deltaphi_bZ_mv1c","#Delta#phi(Z,b) (MV1)",200,0,10);
   h_bjet_deltaeta_Zb = new TH1D("bjet_deltaeta_Zb","#Delta#eta(Z,b)",200,0,10);
   h_bjet_deltaeta_Zb_mv1c = new TH1D("bjet_deltaeta_Zb_mv1c","#Delta#eta(Z,b) (MV1c)",200,0,10);
   h_bjet_deltaeta_bb = new TH1D("bjet_deltaeta_bb","#Delta#eta(b,b)",200,0,10);
   h_bjet_deltaeta_bb_mv1c = new TH1D("bjet_deltaeta_bb_mv1c","#Delta#eta(b,b) (MV1c)",200,0,10);
   h_bjet_rank = new TH1D("bjet_rank","p_{T} rank of b-tagged jets",20,0,20);
   h_bjet_pt_bb = new TH1D("bjet_pt_bb","di b-jet pT",4000,0,2000);
   h_bjet_pt_bb_mv1c = new TH1D("bjet_pt_bb_mv1c","di b-jet pT (MV1c)",4000,0,2000);
   h_Zpt_v_bb_pt = new TH2D("Zpt_v_bb_pt","Z pT versus di b-jet pT",4000,0,2000,4000,0,2000);
   h_Zpt_v_bb_pt_mv1c =new TH2D("Zpt_v_bb_pt_mv1c","Z pT versus di b-jet pT (MV1c)",4000,0,2000,4000,0,2000);
   h_MET = new TH1D("met","MET",4000,0,2000);
   h_MET_1tag = new TH1D("met_1tag","MET (1 b-tag)",4000,0,2000);
   h_MET_2tag =new TH1D("met_2tag","MET (2 b-tag)",4000,0,2000);

   //MV1/MET optimization histograms
   h_mv1_85_met40_bjetn = new TH1D("mv1_85_met40_bjetn","#bjets, MET < 40, mv1 85% wp",12,0,12); 
   h_mv1_80_met40_bjetn = new TH1D("mv1_80_met40_bjetn","#bjets, MET < 40, mv1 80% wp",12,0,12);
   h_mv1_70_met40_bjetn = new TH1D("mv1_70_met40_bjetn","#bjets, MET < 40, mv1 70% wp",12,0,12);
   h_mv1_60_met40_bjetn = new TH1D("mv1_60_met40_bjetn","#bjets, MET < 40, mv1 60% wp",12,0,12);
   h_mv1c_80_met40_bjetn = new TH1D("mv1c_80_met40_bjetn","#bjets, MET < 40, mv1c 80% wp",12,0,12);
   h_mv1c_70_met40_bjetn = new TH1D("mv1c_70_met40_bjetn","#bjets, MET < 40, mv1c 70% wp",12,0,12);
   h_mv1c_60_met40_bjetn = new TH1D("mv1c_60_met40_bjetn","#bjets, MET < 40, mv1c 60% wp",12,0,12);
   h_mv1c_57_met40_bjetn = new TH1D("mv1c_57_met40_bjetn","#bjets, MET < 40, mv1c 57% wp",12,0,12);
   h_mv1c_50_met40_bjetn = new TH1D("mv1c_50_met40_bjetn","#bjets, MET < 40, mv1c 50% wp",12,0,12);

   h_mv1_85_met50_bjetn = new TH1D("mv1_85_met50_bjetn","#bjets, MET < 50, mv1 85% wp",12,0,12);
   h_mv1_80_met50_bjetn = new TH1D("mv1_80_met50_bjetn","#bjets, MET < 50, mv1 80% wp",12,0,12);
   h_mv1_70_met50_bjetn = new TH1D("mv1_70_met50_bjetn","#bjets, MET < 50, mv1 70% wp",12,0,12);
   h_mv1_60_met50_bjetn = new TH1D("mv1_60_met50_bjetn","#bjets, MET < 50, mv1 60% wp",12,0,12);
   h_mv1c_80_met50_bjetn = new TH1D("mv1c_80_met50_bjetn","#bjets, MET < 50, mv1c 80% wp",12,0,12);
   h_mv1c_70_met50_bjetn = new TH1D("mv1c_70_met50_bjetn","#bjets, MET < 50, mv1c 70% wp",12,0,12);
   h_mv1c_60_met50_bjetn = new TH1D("mv1c_60_met50_bjetn","#bjets, MET < 50, mv1c 60% wp",12,0,12);
   h_mv1c_57_met50_bjetn = new TH1D("mv1c_57_met50_bjetn","#bjets, MET < 50, mv1c 57% wp",12,0,12);
   h_mv1c_50_met50_bjetn = new TH1D("mv1c_50_met50_bjetn","#bjets, MET < 50, mv1c 50% wp",12,0,12);

   h_mv1_85_met60_bjetn = new TH1D("mv1_85_met60_bjetn","#bjets, MET < 60, mv1 85% wp",12,0,12);
   h_mv1_80_met60_bjetn = new TH1D("mv1_80_met60_bjetn","#bjets, MET < 60, mv1 80% wp",12,0,12);
   h_mv1_70_met60_bjetn = new TH1D("mv1_70_met60_bjetn","#bjets, MET < 60, mv1 70% wp",12,0,12);
   h_mv1_60_met60_bjetn = new TH1D("mv1_60_met60_bjetn","#bjets, MET < 60, mv1 60% wp",12,0,12);
   h_mv1c_80_met60_bjetn = new TH1D("mv1c_80_met60_bjetn","#bjets, MET < 60, mv1c 80% wp",12,0,12);
   h_mv1c_70_met60_bjetn = new TH1D("mv1c_70_met60_bjetn","#bjets, MET < 60, mv1c 70% wp",12,0,12);
   h_mv1c_60_met60_bjetn = new TH1D("mv1c_60_met60_bjetn","#bjets, MET < 60, mv1c 60% wp",12,0,12);
   h_mv1c_57_met60_bjetn = new TH1D("mv1c_57_met60_bjetn","#bjets, MET < 60, mv1c 57% wp",12,0,12);
   h_mv1c_50_met60_bjetn = new TH1D("mv1c_50_met60_bjetn","#bjets, MET < 60, mv1c 50% wp",12,0,12);

   h_mv1_85_met70_bjetn = new TH1D("mv1_85_met70_bjetn","#bjets, MET < 70, mv1 85% wp",12,0,12);
   h_mv1_80_met70_bjetn = new TH1D("mv1_80_met70_bjetn","#bjets, MET < 70, mv1 80% wp",12,0,12);
   h_mv1_70_met70_bjetn = new TH1D("mv1_70_met70_bjetn","#bjets, MET < 70, mv1 70% wp",12,0,12);
   h_mv1_60_met70_bjetn = new TH1D("mv1_60_met70_bjetn","#bjets, MET < 70, mv1 60% wp",12,0,12);
   h_mv1c_80_met70_bjetn = new TH1D("mv1c_80_met70_bjetn","#bjets, MET < 70, mv1c 80% wp",12,0,12);
   h_mv1c_70_met70_bjetn = new TH1D("mv1c_70_met70_bjetn","#bjets, MET < 70, mv1c 70% wp",12,0,12);
   h_mv1c_60_met70_bjetn = new TH1D("mv1c_60_met70_bjetn","#bjets, MET < 70, mv1c 60% wp",12,0,12);
   h_mv1c_57_met70_bjetn = new TH1D("mv1c_57_met70_bjetn","#bjets, MET < 70, mv1c 57% wp",12,0,12);
   h_mv1c_50_met70_bjetn = new TH1D("mv1c_50_met70_bjetn","#bjets, MET < 70, mv1c 50% wp",12,0,12);

   h_mv1_85_met80_bjetn = new TH1D("mv1_85_met80_bjetn","#bjets, MET < 80, mv1 85% wp",12,0,12);
   h_mv1_80_met80_bjetn = new TH1D("mv1_80_met80_bjetn","#bjets, MET < 80, mv1 80% wp",12,0,12);
   h_mv1_70_met80_bjetn = new TH1D("mv1_70_met80_bjetn","#bjets, MET < 80, mv1 70% wp",12,0,12);
   h_mv1_60_met80_bjetn = new TH1D("mv1_60_met80_bjetn","#bjets, MET < 80, mv1 60% wp",12,0,12);
   h_mv1c_80_met80_bjetn = new TH1D("mv1c_80_met80_bjetn","#bjets, MET < 80, mv1c 80% wp",12,0,12);
   h_mv1c_70_met80_bjetn = new TH1D("mv1c_70_met80_bjetn","#bjets, MET < 80, mv1c 70% wp",12,0,12);
   h_mv1c_60_met80_bjetn = new TH1D("mv1c_60_met80_bjetn","#bjets, MET < 80, mv1c 60% wp",12,0,12);
   h_mv1c_57_met80_bjetn = new TH1D("mv1c_57_met80_bjetn","#bjets, MET < 80, mv1c 57% wp",12,0,12);
   h_mv1c_50_met80_bjetn = new TH1D("mv1c_50_met80_bjetn","#bjets, MET < 80, mv1c 50% wp",12,0,12);

   //crosscheck histograms
   h_d0 = new TH1D("d0","d0",100,-50,50);
   h_d0sig = new TH1D("d0sig","d0sig",100,-50,50);
   h_z0 = new TH1D("z0","z0",100,-50,50);
   h_z0sintheta = new TH1D("z0sintheta","z0sintheta",100,-50,50);
   h_nvertices = new TH1D("nvtx","nvtx",50,0,50);
   h_nmuons = new TH1D("nmu","nmu",50,0,50);
   h_vx_z = new TH1D("vx_z","vx_z",100,-50,50);

   h_d0_aftercut = new TH1D("d0_ac","d0_ac",100,-50,50);
   h_d0sig_aftercut = new TH1D("d0sig_ac","d0sig_ac",100,-50,50);
   h_z0_aftercut = new TH1D("z0_ac","z0_ac",100,-50,50);
   h_z0sintheta_aftercut = new TH1D("z0sintheta_ac","z0sintheta_ac",100,-50,50);
   h_nvertices_aftercut = new TH1D("nvtx_ac","nvtx_ac",50,0,50);
   h_vx_z_rw = new TH1D("vx_z_rw","vx_z_rw",100,-50,50);

   //comparison vector
   cutflowjet_v.clear();
   cutflow_event.clear();
   onejet_eventn.clear();

   icut_max = 19;

   char* rootpath_char;
   rootpath_char = getenv("ROOTCOREBIN");
   string rootpath = string(rootpath_char);

   /*~~~~~~~~~~~~~Good Runs List~~~~~~~~~~~~~~~~*/
   grlR = new Root::TGoodRunsListReader();
   grlR->SetXMLFile("packages/data12_8TeV.periodAllYear_DetStatus-v61-pro14-02_DQDefects-00-01-00_PHYS_StandardGRL_All_Good.xml");
   grlR->Interpret();
   grl=grlR->GetMergedGoodRunsList();
   /*~~~~~~~~~~~~Tile Trip Reader~~~~~~~~~~~~~~*/
   m_treader=new Root::TTileTripReader("myTripReader");
   string tiletrippath = rootpath+"/../TileTripReader/data/CompleteTripList_2011-2012.root";
   m_treader->setTripFile(tiletrippath.c_str());
   /*~~~~~~~~~~~Pileup Reweighting~~~~~~~~~~~~~*/
   m_pileupTool = new Root::TPileupReweighting("PileupReweightingTool");
   //   m_pileupTool->AddConfigFile("packages/mc12ab_defaults.prw.root");
   m_pileupTool->AddConfigFile("packages/MC12ab_myprw_27.2.17.root");
   m_pileupTool->SetDataScaleFactors(1./1.09);
   m_pileupTool->AddLumiCalcFile("packages/ilumicalc_2012_AllYear_All_Good.root");
   m_pileupTool->SetDefaultChannelByMCRunNumber(0, 195847);
   m_pileupTool->SetDefaultChannelByMCRunNumber(1, 195848);
   m_pileupTool->SetUnrepresentedDataAction(2);
   m_pileupTool->EnableDebugging(true);
   m_pileupTool->Initialize();
   /*~~~~~~~~~~~Z Vertex Reweighting~~~~~~~~~~~~~*/
   ZVertexTool = new VertexPositionReweightingTool(VertexPositionReweightingTool::MC12a,"packages/egammaAnalysisUtils/share/zvtx_weights_2011_2012.root");
   /*~~~~~~~~~~Muon Efficiency Corrections~~~~~~~~~~~~~*/
   //Using Medium+ working point file, may want to confirm
   m_MCPsf = new Analysis::AnalysisMuonConfigurableScaleFactors("","MuonsChain_MediumPlus_2012_SF.txt.gz","MeV",Analysis::AnalysisMuonConfigurableScaleFactors::AverageOverPeriods);
   m_MCPsf->Initialise();
   /*~~~~~~~~~~Muon Smearing~~~~~~~~~~~~~~~~~~~~~~~~*/
   mcp_smear.SetAlgoSmearRelDir("Data12","muons","q_pT","Rel17.2Sum13","");
   /*~~~~~~~~~~Jet Calibration~~~~~~~~~~~~~~~~~~~~~*/
   if(isMC && RunNumber == 195848){ //MC12b
     myJES = new JetAnalysisCalib::JetCalibrationTool("AntiKt4LCTopo","CalibrationConfigs/JES_Full2012dataset_MC12b_May2014.config",false);
   }
   else if(isMC){ //MC12a
     myJES = new JetAnalysisCalib::JetCalibrationTool("AntiKt4LCTopo","CalibrationConfigs/JES_Full2012dataset_May2014.config",false);
   }
   else{ //data
     myJES = new JetAnalysisCalib::JetCalibrationTool("AntiKt4LCTopo","CalibrationConfigs/JES_Full2012dataset_May2014.config",true);
   }
   /*~~~~~~~~~~Jet Smearing~~~~~~~~~~~~~~~~~~~~~~~~*/
   //not applied, 2012 MC (release 17.2) and 2012 data agree within uncertainties. May be applied with +/- one sigma for systematics studies

   /*~~~~~~~BCH Cleaning Tool~~~~~~~~~~~~~~~~~~~~~~*/
   thebchTool = new BCHTool::BCHCleaningToolRoot();
   string bchTool_string = rootpath + "/../BCHCleaningTool/share/FractionsRejectedJetsMC.root";
   thebchTool->InitializeTool(isData,m_treader,bchTool_string.c_str());
   /*~~~~~~~~~~~MET Utility~~~~~~~~~~~~~*/
   m_metRebuild= new METUtility;
   m_metRebuild->configMissingET(true,false); //is2012, isSTVF 
   /*~~~~~~~~~~~~B-jet calibration~~~~~~~*/

   calib = new Analysis::CalibrationDataInterfaceROOT("MV1c","packages/CalibrationDataInterface/share/BTagCalibration.env");
   ajet.jetAuthor = "AntiKt4TopoLCJVF0_5";

   //Analysis::Uncertainty uncertainty = Analysis::Total;
   /*~~~~~~~~~~~Muon trigger SF~~~~~~~~*/
   my_muonTrigSFTool = new LeptonTriggerSF(2012,"packages/TrigMuonEfficiency/share","muon_trigger_sf_2012_AtoL.p1328.root", "packages/ElectronEfficiencyCorrection/data", "rel17p2.v07" );

}

Bool_t analysis_Zmumu::Process(Long64_t entry)
{
   // The Process() function is called for each entry in the tree (or possibly
   // keyed object in the case of PROOF) to be processed. The entry argument
   // specifies which entry in the currently loaded tree is to be processed.
   // It can be passed to either analysis_Zmumu::GetEntry() or TBranch::GetEntry()
   // to read either all or the required parts of the data. When processing
   // keyed objects with PROOF, the object is already loaded and is available
   // via the fObject pointer.
   //
   // This function should contain the "body" of the analysis. It can contain
   // simple or elaborate selection criteria, run algorithms on the data
   // of the event and typically fill histograms.
   //
   // The processing can be stopped by calling Abort().
   //
   // Use fStatus to set the return value of TTree::Process().
   //
   // The return value is currently not used.

  //  if(m_event_counter == 0) initTriggerMatch();
  //m_event_counter++;

  fChain->GetTree()->GetEntry(entry);

  pair<UInt_t,UInt_t> run_event_number; 
  run_event_number.first = RunNumber;
  run_event_number.second = EventNumber;
  is_in = run_evt_set.find(run_event_number) != run_evt_set.end();
  if(is_in){
    cout << "#############################################################" << endl;
    cout << "DUPLICATE EVENT: " << run_event_number.first << ", " << run_event_number.second << endl;
    cout << "#############################################################" << endl;
    return kFALSE;
  }
  run_evt_set.insert(run_event_number);

  n_events++;
  //  muon_matched = false;
  good_mu_v.clear();
  good_mu_v_index.clear();
  Z_fourv.Clear();
  
  Zmass = 0;
  jet_v.clear();
  jet_v_tight.clear();
  bjet_v.clear();

  float mcw;
  if(isMC)  mcw = mc_event_weight;
  isTileTrip = kFALSE;
  bool mucut1 = false;
  weight = 1.;
  weight_nopw = 1.;
  weight_notriggerSF = 1.;
  weight_notriggerSF_nopileup = 1.;
  weight_nomuonSF = 1.;
  double sf = 1.;


  bch_bad = false;
  //MET optimization initialization
  met30 =false;
  met40 =false;
  met50 =false;
  met60 =false;
  met70 =false;
  met80 =false;
  met90 =false;

  if(isMC){
    weight *= mcw;
    weight_nopw *= mcw;
  }

  //cutflow variables
  icut = 0; //resets at the beginning of each event: keeps track of which cut you're on
  h_cutflow->Fill((Float_t)icut,1);
  h_cutflow_w->Fill((Float_t)icut,1);
  cutdes[icut] = "No cut, no weights";
  icut++;
  if(isMC){
    h_cutflow->Fill((Float_t)icut,mcw);
    h_cutflow_w->Fill((Float_t)icut,weight);
    cutdes[icut] = "No cut, MC weight only";
    icut++;
  }

  //hfor (overlap removal cutflow) -- removal is later
  if(isMC){
    if(top_hfor_type != 4){
      h_cutflow->Fill((Float_t)icut);
      h_cutflow_w->Fill((Float_t)icut,weight);
    }
    cutdes[icut] = "HFOR overlap removal";
    icut++;
  }


  if(isData){
    //Good runs list
    if(!(grl.HasRunLumiBlock(RunNumber,lbn))) return kFALSE;
    h_cutflow->Fill((Float_t)icut,1);
    h_cutflow_w->Fill((Float_t)icut,weight);
    cutdes[icut] = "GRL"; 
    icut++;
  }
  float pileupweight;
  //pileup reweighting
  h_pileup_norw->Fill(actualIntPerXing,weight);
  h_avg_pileup_norw->Fill(averageIntPerXing,weight);
  Float_t old_mu = averageIntPerXing;
  if(isMC){
    averageIntPerXing = (isSimulation && lbn==1 && int(averageIntPerXing+0.5)==1) ? 0. : averageIntPerXing;
    m_pileupTool->SetRandomSeed(314159 + mc_channel_number*2718 + EventNumber);
    pileupweight = m_pileupTool->GetCombinedWeight(RunNumber,mc_channel_number,averageIntPerXing);
    weight *= pileupweight;
    h_pileupSF->Fill(pileupweight);
    h_cutflow->Fill((Float_t)icut,weight);
    h_cutflow_w->Fill((Float_t)icut,weight);
    cutdes[icut] = "No cut, MC and pileup weight";
    icut++;
  }

  h_pileup->Fill(actualIntPerXing,weight);

  if(!isMC){
    h_avg_pileup->Fill(averageIntPerXing*(1.0/1.09),weight);
  }
  else{
    h_avg_pileup->Fill(averageIntPerXing,weight);
  }
  h_avg_pileup_noprw->Fill(averageIntPerXing,weight_nopw);

  /*~~~~~~~~~~~selection cuts~~~~~~~~~~~~~*/

  //Z vertex reweighting
  for(int i = 0; i < vxp_n; i++){
    h_vx_z->Fill(vxp_z->at(i),weight);
  }
  if(isMC){
    float vx_z = 0;
    for(int imc = 0; imc < mc_n; imc++){
      vx_z = mc_vx_z->at(imc);
      if(vx_z != 0) break;
    }
    weight *= ZVertexTool->GetWeight(vx_z);
    weight_nopw *= ZVertexTool->GetWeight(vx_z);
    h_cutflow->Fill((Float_t)icut);
    h_cutflow_w->Fill((Float_t)icut,weight);
    cutdes[icut] = "Z vertex reweighting";
    icut++;
  }

  for(int i = 0; i < vxp_n; i++){
    h_vx_z_rw->Fill(vxp_z->at(i),weight);
  }


  //HFOR (overlap removal)
  if(isMC){
    if(top_hfor_type == 4){
      return kFALSE;
    }
    h_cutflow->Fill((Float_t)icut);
    h_cutflow_w->Fill((Float_t)icut,weight);
    cutdes[icut] = "HFOR overlap removal (after PU and Z vertex reweighting)";
    icut++;
  }

  //Trigger                                                                                                                                                                                                               
  if(!EF_mu18_tight_mu8_EFFS) return kFALSE;
  h_cutflow_w->Fill((Float_t)icut,weight);
  h_cutflow->Fill((Float_t)icut);
  cutdes[icut] = "Trigger";
  icut++;

  if(isData){
    isTileTrip=m_treader->checkEvent(RunNumber,lbn,EventNumber);
  }
  //separating out cuts for cutflow
  if(larError == 2) return kFALSE;
  h_cutflow->Fill((Float_t)icut);
  h_cutflow_w->Fill((Float_t)icut,weight);
  cutdes[icut] = "LAr Error";
  icut++;

  if(tileError == 2) return kFALSE;
  h_cutflow->Fill((Float_t)icut);
  h_cutflow_w->Fill((Float_t)icut,weight);
  cutdes[icut] = "Tile Error";
  icut++;

  if(coreFlags&0x40000!=0) return kFALSE;
  h_cutflow->Fill((Float_t)icut);
  h_cutflow_w->Fill((Float_t)icut,weight);
  cutdes[icut] = "Core flag";
  icut++;


  h_nvertices->Fill(vxp_n,weight);
  //vtx: >=1 vertex, with >=3 tracks
  bool good_vtx = false;
  if(vxp_n > 0){
    if(vxp_nTracks->at(0) >= 3) good_vtx = true;
    for(int i = 0; i < vxp_n; i++){
      //h_vx_z_rw->Fill(vxp_z->at(i),weight);
      // if(vxp_nTracks->at(i) >= 3) good_vtx = true;
    }
  }
  if(!good_vtx) return kFALSE;
  h_cutflow->Fill((Float_t)icut);
  h_cutflow_w->Fill((Float_t)icut,weight);
  cutdes[icut] = "Vertex";
  icut++;
  h_nvertices_aftercut->Fill(vxp_n,weight);

  if(!isTileTrip && isData) return kFALSE;
  h_cutflow->Fill((Float_t)icut);
  h_cutflow_w->Fill((Float_t)icut,weight);
  cutdes[icut] = "Tile Trip";
  icut++;


  //muon selections: good muon
  //3rd chain
  //Medium+ && !(isStandAloneMuon)
  double m_charge;
  double m_mass;
  double m_eta;
  double m_phi;
  double m_ptCB;
  double m_ptID;
  double m_ptMS;

  double m_ptCB_smeared;
  double m_ptID_smeared;
  double m_ptMS_smeared;

  const int muoncf_n = 10;
  int muon_cf [muoncf_n] = {0};

  MuonPtContainer.clear();
  MuonMSPtContainer.clear();
  JetPtContainer.clear();
  JetEtaContainer.clear();
  JetPhiContainer.clear();
  JetEContainer.clear();

  for(int imu = 0; imu < mu_n; imu++){
    m_charge = mu_charge->at(imu);
    m_mass = mu_m->at(imu);
    m_eta = mu_eta->at(imu);
    m_phi = mu_phi->at(imu);
    m_ptCB = mu_pt->at(imu);
    m_ptID = fabs(sin(mu_id_theta_exPV->at(imu))/mu_id_qoverp_exPV->at(imu));
    m_ptMS = fabs(sin(mu_me_theta_exPV->at(imu))/mu_me_qoverp_exPV->at(imu));
    
    mu_fourv.Clear();
    //Perform muon smearing
    if(isMC){
      mcp_smear.SetSeed(EventNumber, imu);
      if(mu_isCombinedMuon->at(imu) && m_ptMS > 0.){
	mcp_smear.Event(m_ptMS,m_ptID,m_ptCB,m_eta,m_charge,m_phi);
      }
      else if(mu_isSegmentTaggedMuon->at(imu) || m_ptMS <= 0.){
	mcp_smear.Event(m_ptID,m_eta,"ID",m_charge,m_phi);
      }
      else if(mu_isStandAloneMuon->at(imu)){
	mcp_smear.Event(m_ptMS,m_eta,"MS",m_charge,m_phi);
      }
      m_ptCB_smeared = mcp_smear.pTCB();
      m_ptMS_smeared = mcp_smear.pTMS();
      m_ptID_smeared = mcp_smear.pTID();
      //debug, smearing removal
      //      m_ptMS_smeared = m_ptMS;
      //m_ptID_smeared = m_ptID;
      //m_ptCB_smeared = m_ptCB;
    }
    else{ //isData
      m_ptCB_smeared = m_ptCB;
    }
    //Values for MET tool
    MuonPtContainer.push_back(m_ptCB_smeared);
    MuonMSPtContainer.push_back(m_ptMS_smeared);

    //Medium+ selection                                                                                                                           
    if (!((
	   (mu_author->at(imu)==11&&mu_nprecisionLayers->at(imu)>2&&fabs(mu_eta->at(imu))>2.5)||
           (mu_author->at(imu)==6)||
           (mu_author->at(imu)==12&&mu_momentumBalanceSignificance->at(imu)<4)||
           (mu_author->at(imu)==13&&mu_momentumBalanceSignificance->at(imu)<4&&mu_isCombinedMuon->at(imu))
           ) 
	  && !(mu_isStandAloneMuon->at(imu)))) continue;
    muon_cf[0]++;
    //ID track selection (as described in muon CP Twiki) 
    if(!(mu_nPixHits->at(imu)+mu_nPixelDeadSensors->at(imu) > 0)) continue;
    muon_cf[1]++; //pixel req.
    if(!(mu_nSCTHits->at(imu)+mu_nSCTDeadSensors->at(imu) > 4)) continue;
    muon_cf[2]++; // sct req.
    if(!(mu_nPixHoles->at(imu)+mu_nSCTHoles->at(imu) < 3)) continue;
    muon_cf[3]++; //hole req.
    if((fabs(mu_eta->at(imu)) > 0.1) && (fabs(mu_eta->at(imu)) < 1.9)){
      n_TRT = mu_nTRTHits->at(imu) + mu_nTRTOutliers->at(imu);
      if(!(n_TRT > 5)) continue;
      if(!(mu_nTRTOutliers->at(imu) < 0.9*n_TRT)) continue;
    }
    muon_cf[4]++; //TRT req.
    //IP significance < 3
    h_d0sig_aftercut->Fill(fabs(mu_trackd0pvunbiased->at(imu)/mu_tracksigd0pvunbiased->at(imu)));
    
    if(!(fabs(mu_trackd0pvunbiased->at(imu)/mu_tracksigd0pvunbiased->at(imu)) < 3)) continue;
    
    h_d0sig->Fill(fabs(mu_trackd0pvunbiased->at(imu)/mu_tracksigd0pvunbiased->at(imu)));
    muon_cf[5]++;
    //isolation: ptcone20/pt < 0.1
    h_mu_iso->Fill(mu_ptcone20->at(imu)/m_ptCB_smeared);
    if(!(mu_ptcone20->at(imu)/m_ptCB_smeared < 0.1)) continue;
    muon_cf[6]++;
    h_mu_iso_cut->Fill(mu_ptcone20->at(imu)/m_ptCB_smeared);
    //|eta| < 2.4
    if(!(fabs(mu_eta->at(imu)) < 2.4)) continue;
    muon_cf[7]++;
    //impact parameter < 0.5 mm
    h_z0->Fill(mu_trackz0pvunbiased->at(imu));
    h_z0sintheta->Fill(fabs(mu_trackz0pvunbiased->at(imu)) * TMath::Sin(mu_tracktheta->at(imu)));
    if(!isArantxa){
	//if(!(fabs(mu_trackz0pvunbiased->at(imu)) * TMath::Sin(mu_tracktheta->at(imu)) < 0.5)) continue;
      if(!(fabs(mu_trackz0pvunbiased->at(imu)) < 1.0)) continue; //changed to match 7 TeV cut (old cut was for staco muons? may want to optimize)
    }
    h_z0_aftercut->Fill(mu_trackz0pvunbiased->at(imu));
    h_z0sintheta_aftercut->Fill(fabs(mu_trackz0pvunbiased->at(imu)) * TMath::Sin(mu_tracktheta->at(imu)));
    //pt > 25 GeV
    h_mu_pt_nocut->Fill(mu_pt->at(imu)/1000.,weight);
    h_mu_phi_nocut->Fill(mu_phi->at(imu),weight);
    h_mu_eta_nocut->Fill(mu_eta->at(imu),weight);
    if(m_ptCB_smeared/1000. > 20.0 && !mucut1){
      muon_cf[8]++;
      mucut1 = true;
    }
    if(isArantxa){
      if(!(m_ptCB_smeared/1000. > 20.)) continue; //Arantxa's cut
    }
    else{
      if(!(m_ptCB_smeared/1000. > 25.)) continue;
    }
    mu_fourv.SetPtEtaPhiM(m_ptCB_smeared, m_eta, m_phi, m_mass);
    //    if(muonTriggerMatchTool->match(mu_fourv.Eta(),mu_fourv.Phi(),"EF_mu18_tight_mu8_EFFS")){
      //      muon_matched = true;
    // }
    good_mu_v.push_back(mu_fourv);
    good_mu_v_index.push_back(imu);
    
  }
  //Muon selection cutflow
  //Changed >0 to >1 to require at least two 3rd chain muons that pass cuts
  if(muon_cf[0] > 1){
    h_cutflow_w->Fill(Float_t(icut),weight);
    h_cutflow->Fill(Float_t(icut));
  }
  cutdes[icut] = "Medium+";
  icut++;
  if(muon_cf[1] > 1){
    h_cutflow_w->Fill(Float_t(icut),weight);
    h_cutflow->Fill(Float_t(icut));
  }
  cutdes[icut] = "Pixel req.";
  icut++;
  if(muon_cf[2] > 1){
    h_cutflow_w->Fill(Float_t(icut),weight);
    h_cutflow->Fill(Float_t(icut));
  }
  cutdes[icut] = "SCT req.";
  icut++;
  if(muon_cf[3] > 1){
    h_cutflow_w->Fill(Float_t(icut),weight);
    h_cutflow->Fill(Float_t(icut));
  }    
  cutdes[icut] = "Hole req.";
  icut++;
  if(muon_cf[4] > 1){
    h_cutflow_w->Fill(Float_t(icut),weight);
    h_cutflow->Fill(Float_t(icut));
  }
  cutdes[icut] = "TRT req.";
  icut++;
  if(muon_cf[5] > 1){
    h_cutflow_w->Fill(Float_t(icut),weight);
    h_cutflow->Fill(Float_t(icut));
  }
  cutdes[icut] = "d0 significance";
  icut++;
  if(muon_cf[6] > 1){
    h_cutflow_w->Fill(Float_t(icut),weight);
    h_cutflow->Fill(Float_t(icut));
  }    
  cutdes[icut] = "Isolation req.";
  icut++;
  if(muon_cf[7] > 1){
    h_cutflow_w->Fill(Float_t(icut),weight);
    h_cutflow->Fill(Float_t(icut));
  }
  cutdes[icut] = "|eta| < 2.4";
  icut++;
  if(muon_cf[8] > 0){
    h_cutflow_w->Fill(Float_t(icut),weight);
    h_cutflow->Fill(Float_t(icut));
  }
  cutdes[icut] = "AT LEAST 1 GOOD MUON with pT> 20 GeV (includes eta cut)";
  icut++;
  
  h_nmuons->Fill(good_mu_v.size(),weight);

  /*~~~~~~~~~build Z~~~~~~~~~~~~*/
  //require exactly two muons
  if(good_mu_v.size() == 2){
    h_cutflow_w->Fill(Float_t(icut),weight);
    h_cutflow->Fill(Float_t(icut));
    if(isArantxa)cutdes[icut] = "Exactly 2 good muons with pT > 20 GeV";
    else cutdes[icut] = "Exactly 2 good muons with pT > 25 GeV";
    icut++;
  }
  else return kFALSE;

  //TriggerSF (is this in the right spot???)
  if(isMC){
    double RunNumberPileupSF=m_pileupTool->GetRandomRunNumber(RunNumber,averageIntPerXing);
    if(RunNumberPileupSF == 0 && pileupweight != 0){
      cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
      cout << "THERE IS A PROBLEM: PILEUP WEIGHT INCORRECT" << endl;
      cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
    }
    vector<muon_quality> muonQualities;
    muonQualities.push_back(muon_quality(2));  //2 means medium+
    muonQualities.push_back(muon_quality(2));
    pair<Double_t,Double_t> sfEvt_trig = my_muonTrigSFTool->GetTriggerSF(RunNumberPileupSF, kFALSE, good_mu_v, muonQualities, string("mu18_tight_mu8_EFFS"));
    weight_notriggerSF = weight;
    weight_notriggerSF_nopileup = weight_nopw;
    weight *= sfEvt_trig.first;
    weight_nopw*= sfEvt_trig.first;
    h_triggerSF_size->Fill(sfEvt_trig.first);
  }

  int mu1_ind = good_mu_v_index.at(0);
  int mu2_ind = good_mu_v_index.at(1);
  Z_fourv = good_mu_v.at(0) + good_mu_v.at(1);
  Zmass = Z_fourv.M()/1000.;
  if((mu_charge->at(mu1_ind) * mu_charge->at(mu2_ind)) == -1){
    h_cutflow_w->Fill(Float_t(icut),weight);
    h_cutflow->Fill(Float_t(icut));
    cutdes[icut] = "Opposite sign";
    icut++;
  }
  else return kFALSE;

  if(isArantxa){
    Zwindow_min = 71.0;
    Zwindow_max = 111.0;
  }
  else{
    Zwindow_min = 76.0;
    Zwindow_max = 106.0;
  }
  h_m_mumu->Fill(Zmass,weight); // dimuon spectrum before mass window selection
  
  if(Zmass > Zwindow_min && Zmass < Zwindow_max && ((mu_charge->at(mu1_ind) * mu_charge->at(mu2_ind)) == -1)){
    //muon scale factor
    if(isMC){
      sf *= m_MCPsf->scaleFactor(mu_charge->at(mu1_ind),good_mu_v.at(0));
      sf *= m_MCPsf->scaleFactor(mu_charge->at(mu2_ind),good_mu_v.at(1));
      weight *= sf;
      weight_nomuonSF *= weight_nopw;
      weight_nopw*= sf;
      weight_notriggerSF *= sf;
    }
    
    h_cutflow_w->Fill(Float_t(icut),weight);
    h_cutflow->Fill(Float_t(icut));
    if(isArantxa) cutdes[icut] = "Mass cut:  71 < MZ < 111 GeV";
    else cutdes[icut] = "Mass cut:  76 < MZ < 106 GeV";
    icut++;
  }
  else return kFALSE;

  //deltaR(mu,mu) > 0.2
  if(isArantxa){
    if(good_mu_v.at(0).DeltaR(good_mu_v.at(1)) > 0.2){
      h_cutflow_w->Fill(Float_t(icut),weight);
      h_cutflow->Fill(Float_t(icut));
      cutdes[icut] = "DeltaR(mu,mu) > 0.2";
      icut++;
    }
    else return kFALSE;
  }

  //Fill inclusive Z histograms
  if(isMC && weight == 0) {
    h_good_zeroweight_events->Fill(0);
    if(pileupweight == 0) h_good_zeroweight_events_pw->Fill(0);
  }
  h_Z_mumu->Fill(Zmass,weight);
  h_Z_pt->Fill(Z_fourv.Pt()/1000.,weight);
  h_Z_y->Fill(Z_fourv.Rapidity(),weight);
  h_Z_eta->Fill(Z_fourv.Eta(),weight);
  h_Z_phi->Fill(Z_fourv.Phi(),weight);
  h_mu_pt->Fill(good_mu_v.at(0).Pt()/1000.,weight);
  h_mu_pt->Fill(good_mu_v.at(1).Pt()/1000.,weight);
  h_mu_eta->Fill(good_mu_v.at(0).Eta(),weight);
  h_mu_eta->Fill(good_mu_v.at(1).Eta(),weight);
  h_mu_phi->Fill(good_mu_v.at(0).Phi(),weight);
  h_mu_phi->Fill(good_mu_v.at(1).Phi(),weight);

  h_pileup_avg_Zsel_norw->Fill(averageIntPerXing,weight_nopw);
  h_pileup_Zsel_norw->Fill(actualIntPerXing,weight_nopw);

  if(isMC){
    h_pileup_avg_Zsel->Fill(averageIntPerXing,weight);
    h_pileup_Zsel->Fill(actualIntPerXing,weight);
  }
  else{
    h_pileup_avg_Zsel->Fill(averageIntPerXing*1/1.09,weight);
    h_pileup_Zsel->Fill(actualIntPerXing*1/1.09,weight);
  }
  
  h_Z_mumu_nopw->Fill(Zmass,weight_nopw);
  h_Z_pt_nopw->Fill(Z_fourv.Pt()/1000.,weight_nopw);
  h_Z_y_nopw->Fill(Z_fourv.Rapidity(),weight_nopw);
  h_Z_phi_nopw->Fill(Z_fourv.Phi(),weight_nopw);

  n_zevents++;

  /*~~~~~~~~~jet selection~~~~~~~~~~~*/
  int jetn_final = 0;
  int jetn_final_tight = 0;
  float deltaR_jlep1 = 0 ;
  float deltaR_jlep2 = 0;

  //Hot Tile Cell Veto
  float j_fmax;
  float j_smax;
  float j_eta;
  float j_phi;
  bool in_hotruns = false;
  bool _etaphi28 = false;
  unsigned int hot_runs[9] = {202660,202668,202712,202740,202965,202987,202991,203027,203169};
  for(int r = 0; r < 9; r++){
    if(RunNumber == hot_runs[r]) in_hotruns = true;
  }
  //  thebchTool->SetSeed(EventNumber);
  if(isMC) thebchTool->SetSeed(314159+mc_channel_number*2718+EventNumber);
  int runnumber_bch;
  int luminumber_bch;
  bool toolFlag = false;
  if(isMC){ //MC
    runnumber_bch = m_pileupTool->GetRandomRunNumber(RunNumber,averageIntPerXing);
    luminumber_bch = 0.;
    if(runnumber_bch > 0){
      luminumber_bch = m_pileupTool->GetRandomLumiBlockNumber(runnumber_bch);
    }
    else{
      return kFALSE;
    }
  }
  else{ //Data
    runnumber_bch = RunNumber;
    luminumber_bch = lbn;
  }

  bool badlooseveto = false;
  bool hottilecellveto = false;
  
  for(int ijet = 0; ijet < jet_AntiKt4LCTopo_n; ijet++){
    //JES variables
    double Eraw = jet_AntiKt4LCTopo_constscale_E->at(ijet);
    double eta_det = jet_AntiKt4LCTopo_constscale_eta->at(ijet);
    double phi = jet_AntiKt4LCTopo_constscale_phi->at(ijet);
    double m = jet_AntiKt4LCTopo_constscale_m->at(ijet);
    double eta_origin = jet_AntiKt4LCTopo_EtaOrigin->at(ijet);
    double phi_origin = jet_AntiKt4LCTopo_PhiOrigin->at(ijet);
    double m_origin = jet_AntiKt4LCTopo_MOrigin->at(ijet);
    double Ax = jet_AntiKt4LCTopo_ActiveAreaPx->at(ijet);
    double Ay = jet_AntiKt4LCTopo_ActiveAreaPy->at(ijet);
    double Az = jet_AntiKt4LCTopo_ActiveAreaPz->at(ijet);
    double Ae = jet_AntiKt4LCTopo_ActiveAreaE->at(ijet);
    double rho = Eventshape_rhoKt4LC;
    double fEM3 = -999;
    double fTile0 = -999;
    double nTrk = jet_AntiKt4LCTopo_nTrk_pv0_1GeV->at(ijet);
    double trackWIDTH = jet_AntiKt4LCTopo_trackWIDTH_pv0_1GeV->at(ijet);
    double Nseg = Nsegments(eta_det,phi);
    int NPV = 0;
    double mu = averageIntPerXing;
    //calculate NVP
    for(unsigned int j= 0; j<vxp_nTracks->size();j++){
      if(vxp_nTracks->at(j) >= 2) NPV++;
    }
  
    jet_fourv.Clear();
    jet_fourv = myJES->ApplyJetAreaOffsetOriginEtaJESGSC(Eraw,eta_det,phi,m,eta_origin,phi_origin,m_origin,Ax,Ay,Az,Ae,rho,trackWIDTH,nTrk,fTile0,fEM3,Nseg,mu,NPV);


    JetPtContainer.push_back(jet_fourv.Pt());
    JetEtaContainer.push_back(jet_fourv.Eta());
    JetPhiContainer.push_back(jet_fourv.Phi());
    JetEContainer.push_back(jet_fourv.E());

    //Bad Loose Minus jet veto
    if(jet_AntiKt4LCTopo_isBadLooseMinus->at(ijet) && jet_fourv.Pt()/1000. > 20.0){
      badlooseveto = true;
    }

    //Hot tile cell veto
    j_fmax = jet_AntiKt4LCTopo_fracSamplingMax->at(ijet);
    j_smax = jet_AntiKt4LCTopo_SamplingMax->at(ijet);
    j_eta = jet_AntiKt4LCTopo_eta->at(ijet);
    j_phi = jet_AntiKt4LCTopo_phi->at(ijet);
    if(j_eta > -0.2 && j_eta < -0.1 && j_phi > 2.65 && j_phi < 2.75) _etaphi28=true;
    if(j_fmax > 0.6 && j_smax==13 && _etaphi28 && in_hotruns) hottilecellveto=true;

    //jet overlap removal
    deltaR_jlep1 = jet_fourv.DeltaR(good_mu_v.at(0));
    deltaR_jlep2 = jet_fourv.DeltaR(good_mu_v.at(1));
    if(isArantxa){
      if(deltaR_jlep1 < 0.5 || deltaR_jlep2 < 0.5) {
	continue;
      }
    }
    else{
      if(deltaR_jlep1 < 0.5 || deltaR_jlep2 < 0.5){
	continue;
      }
    }

    //pT > 30 GeV
    if(!(jet_fourv.Pt()/1000. > 30.0)) continue;
    //eta < 4.4
    if(!(fabs(jet_AntiKt4LCTopo_constscale_eta->at(ijet)) < 4.4)) continue;

    //JVF
    if(fabs(jet_AntiKt4LCTopo_constscale_eta->at(ijet)) < 2.4 && jet_fourv.Pt()/1000. < 50.){
      if(!(fabs(jet_AntiKt4LCTopo_jvtxf->at(ijet)) > 0.5)){
	continue;
      }
    }

    if(thebchTool->IsBadMediumBCH(runnumber_bch,luminumber_bch,jet_fourv.Eta(),jet_fourv.Phi(),jet_AntiKt4LCTopo_BCH_CORR_CELL->at(ijet),jet_AntiKt4LCTopo_emfrac->at(ijet),jet_fourv.Pt())) toolFlag = true;
    if(EventNumber == 91972557){
      run_bch_v.push_back(runnumber_bch);
      lbn_bch_v.push_back(luminumber_bch);
      eta_bch_v.push_back(jet_fourv.Eta());
      phi_bch_v.push_back(jet_fourv.Phi());
      BCH_CORR_CELL_v.push_back(jet_AntiKt4LCTopo_BCH_CORR_CELL->at(ijet));
      emfrac_v.push_back(jet_AntiKt4LCTopo_emfrac->at(ijet));
      pt_bch_v.push_back(jet_fourv.Pt());
      }

    jetn_final++;
    n_passing_jets++;
    jet_pair.first = ijet;
    jet_pair.second = jet_fourv;
    jet_v.push_back(jet_pair);
    h_jet_pt->Fill(jet_fourv.Pt()/1000.,weight);
    h_jet_y->Fill(jet_fourv.Rapidity(),weight);

    //tighter eta selection: |eta| < 2.4
    if(fabs(jet_AntiKt4LCTopo_constscale_eta->at(ijet)) > 2.4) continue;
    jetn_final_tight++;
    jet_pair_tight.first = ijet;
    jet_pair_tight.second = jet_fourv;
    jet_v_tight.push_back(jet_pair_tight);
    h_jet_pt_tighteta->Fill(jet_fourv.Pt()/1000.,weight);
    h_jet_y_tighteta->Fill(jet_fourv.Rapidity(),weight);

  }

  //Check event 91972557  
  if(EventNumber == 91972557){
    for(int j = 0; j < jet_v.size(); j++){
      eventcheck_pair.first = jet_v[j].second;
      eventcheck_pair.second = jet_AntiKt4LCTopo_jvtxf->at(jet_v[j].first);
      eventmap_pair.first = EventNumber;
      eventmap_pair.second = eventcheck_pair;
      eventcheck_map.insert(eventmap_pair);
    }
  }

  if(EventNumber == 91972557) eventcheckcut = icut;
  //Bad loose jet veto
  if(badlooseveto) return kFALSE;
  h_cutflow_w->Fill(Float_t(icut),weight);
  h_cutflow->Fill(Float_t(icut));
  cutdes[icut] = "isBadLooseMinus";
  icut++;

  if(EventNumber == 91972557) eventcheckcut = icut;
  //Hot Tile Cell veto
  if(hottilecellveto){
    return kFALSE;
  }
  h_cutflow_w->Fill(Float_t(icut),weight);
  h_cutflow->Fill(Float_t(icut));
  cutdes[icut] = "HotTile";
  icut++;

  h_Zmumu_hottile->Fill(Zmass,weight);

  if(EventNumber == 91972557) eventcheckcut = icut;
  //BCH tool veto
  if(toolFlag){
    return kFALSE;
  }

  h_cutflow_w->Fill(Float_t(icut),weight);
  h_cutflow->Fill(Float_t(icut));
  cutdes[icut] = "BCH";
  icut++;

  if(EventNumber == 91972557) eventcheckcut = icut;
  rebuild_MET();
  h_MET->Fill(finalMET_et/1000.,weight);
  //Fill Z+jets histograms (selections complete)

  h_Z_mass_0j->Fill(Zmass,weight);
  if(jet_v.size() == 0) h_Z_mass_exactly0j->Fill(Zmass,weight);
  if(jet_v.size() == 1) h_Z_mass_exactly1j->Fill(Zmass,weight);
  if(jet_v.size() >= 1){
    h_Z_mass_1j->Fill(Zmass,weight);
   }
  if(jet_v.size() >= 2){
    h_Z_mass_2j->Fill(Zmass,weight);
   }
  if(jet_v.size() >= 3){
    h_Z_mass_3j->Fill(Zmass,weight);
   }
  if(jet_v.size() >= 4){
    h_Z_mass_4j->Fill(Zmass,weight);
   }
  if(jet_v.size() >= 5){
    h_Z_mass_5j->Fill(Zmass,weight);
  }

  h_jet_n->Fill(jetn_final,weight);
  h_jet_n_tighteta->Fill(jetn_final_tight,weight);

  //Add pTs for HT and ST
  //ST: scalar sum of jet pTs
  //HT: scalar sum of jet and lepton pTs
  float st = 0;
  float ht = 0;
  float st_tight = 0;
  float ht_tight = 0;
  for(unsigned int njet = 0; njet < jet_v.size(); njet++){
    st += jet_v[njet].second.Pt();
  }
  ht += st;
  ht += good_mu_v[0].Pt();
  ht+= good_mu_v[1].Pt();

  if(jet_v.size() > 0){
    h_jet_st->Fill(st/1000.,weight);
    h_jet_mu_ht->Fill(ht/1000.,weight);
  }
  
  for(unsigned int njet = 0; njet < jet_v_tight.size(); njet++){
    st_tight += jet_v_tight[njet].second.Pt();
  }
  ht_tight += st_tight;
  ht_tight += good_mu_v[0].Pt();
  ht_tight += good_mu_v[1].Pt();

  if(jet_v_tight.size() > 0){
    h_jet_st_tighteta->Fill(st_tight/1000.,weight);
    h_jet_mu_ht_tighteta->Fill(ht_tight/1000.,weight);
  }

  //sort jets by pT
  int j;
  pair<int,TLorentzVector> tmp;
  for(unsigned int njet = 1; njet < jet_v.size(); njet++){
    j = njet;
    while(j > 0 && jet_v[j-1].second.Pt() < jet_v[j].second.Pt()){
      tmp = jet_v[j];
      jet_v[j] = jet_v[j-1];
      jet_v[j-1] = tmp;
      j--;
    }
  }

  //sort tight jets by pT
  for(unsigned int njet = 1; njet < jet_v_tight.size(); njet++){
    j = njet;
    while(j > 0 && jet_v_tight[j-1].second.Pt() < jet_v_tight[j].second.Pt()){
      tmp = jet_v_tight[j];
      jet_v_tight[j] = jet_v_tight[j-1];
      jet_v_tight[j-1] = tmp;
      j--;
    }
  }

  //jet cutflow
  if(jet_v.size() == 0){
    h_cutflow_w->Fill(Float_t(icut),weight);
    h_cutflow->Fill(Float_t(icut));
  }
  cutdes[icut] = "Njets == 0";
  icut++;
  if(jet_v.size() == 1){
    h_cutflow_w->Fill(Float_t(icut),weight);
    h_cutflow->Fill(Float_t(icut));
  }
  cutdes[icut] = "Njets == 1";
  icut++;
  if(jet_v.size() == 2){
    h_cutflow_w->Fill(Float_t(icut),weight);
    h_cutflow->Fill(Float_t(icut));
  }
  cutdes[icut] = "Njets == 2";
  icut++;
  if(jet_v.size() == 3){
    h_cutflow_w->Fill(Float_t(icut),weight);
    h_cutflow->Fill(Float_t(icut));
    for(int j=0; j<3;j++){
      cutflowpair.first = jet_v[j].second;
      cutflowpair.second = jet_AntiKt4LCTopo_jvtxf->at(jet_v[j].first);
      mappair.first = EventNumber;
      mappair.second = cutflowpair;
      cutflowjet_map.insert(mappair);
    }
    /*    jetcf_pair.first = 3;
    jetcf_pair.second = EventNumber;
    onejet_eventn.push_back(jetcf_pair);
    cutflowjet_v.push_back(jet_v[0].second);*/
  }
  cutdes[icut] = "Njets == 3";
  icut++;
  if(jet_v.size() == 4){
    h_cutflow_w->Fill(Float_t(icut),weight);
    h_cutflow->Fill(Float_t(icut));
    for(int j=0; j<4;j++){
      cutflowpair.first= jet_v[j].second;
      cutflowpair.second = jet_AntiKt4LCTopo_jvtxf->at(jet_v[j].first);
      mappair.first = EventNumber;
      mappair.second = cutflowpair;
      cutflowjet_map.insert(mappair);
    }
  }
  cutdes[icut] = "Njets == 4";
  icut++;
  if(jet_v.size() >= 5){
    h_cutflow_w->Fill(Float_t(icut),weight);
    h_cutflow->Fill(Float_t(icut));
  }
  cutdes[icut] = "Njets >= 5";
  icut++;
  icut_max = icut;

  if(jet_v.size() > 0){
    h_leadjet_pt->Fill(jet_v[0].second.Pt()/1000.,weight);
    h_leadjet_y->Fill(jet_v[0].second.Rapidity(),weight);
  }

  double del_eta;
  double del_phi;
  double del_y;
  double del_r_eta;
  double del_r_y;
  if(jet_v.size() > 1){
    TLorentzVector tmp_4v = jet_v[0].second + jet_v[1].second;
    h_subjet_pt->Fill(jet_v[1].second.Pt()/1000.,weight);
    h_subjet_y->Fill(jet_v[1].second.Rapidity(),weight);
    h_dijet_m->Fill((tmp_4v.M())/1000.,weight);
    h_dijet_dR->Fill(jet_v[1].second.DeltaR(jet_v[0].second),weight);
    h_dijet_dphi->Fill(fabs(jet_v[1].second.DeltaPhi(jet_v[0].second)),weight);
    del_eta = jet_AntiKt4LCTopo_eta->at(jet_v[0].first) - jet_AntiKt4LCTopo_eta->at(jet_v[1].first);
    del_phi = fabs(jet_AntiKt4LCTopo_phi->at(jet_v[0].first) - jet_AntiKt4LCTopo_phi->at(jet_v[1].first));
    if(del_phi > TMath::Pi()) del_phi = (2*TMath::Pi()) - del_phi;
    del_y = jet_v[1].second.Rapidity()-jet_v[0].second.Rapidity();
    del_r_eta = TMath::Sqrt(TMath::Power(fabs(del_eta),2) + TMath::Power(del_phi,2));
    del_r_y = TMath::Sqrt(TMath::Power(del_y,2) + TMath::Power(del_phi,2));
    h_dijet_dy->Fill(fabs(del_y),weight);
    h_dijet_deta->Fill(fabs(del_eta),weight);
    h_dijet_dR_eta->Fill(del_r_eta,weight);
    h_dijet_dR_y->Fill(del_r_y,weight);
    h_Zpt_v_jj_pt->Fill(Z_fourv.Pt()/1000.,tmp_4v.Pt()/1000.,weight);
  }
  if(jet_v.size() > 2){
    h_3jet_pt->Fill(jet_v[2].second.Pt()/1000.,weight);
    h_3jet_y->Fill(jet_v[2].second.Rapidity(),weight);
  }
  if(jet_v.size() > 3){
    h_4jet_pt->Fill(jet_v[3].second.Pt()/1000.,weight);
    h_4jet_y->Fill(jet_v[3].second.Rapidity(),weight);
  }

  //moved to after b-tag calibration
  /*
  for(unsigned int i=0; i<jet_v_tight.size(); i++){
    h_mv1weight->Fill(jet_AntiKt4LCTopo_flavor_weight_MV1->at(jet_v_tight[i].first),weight);
    h_mv1cweight->Fill(jet_AntiKt4LCTopo_flavor_weight_MV1c->at(jet_v_tight[i].first),weight);
    h_mv1cweight_binned->Fill(jet_AntiKt4LCTopo_flavor_weight_MV1c->at(jet_v_tight[i].first),weight);
    if(isMC){
      switch (jet_AntiKt4LCTopo_flavor_truth_label->at(jet_v_tight[i].first)){
      case 5:
	h_mv1cweight_bottom->Fill(jet_AntiKt4LCTopo_flavor_weight_MV1c->at(jet_v_tight[i].first),weight);
	break;
      case 4:
	h_mv1cweight_charm->Fill(jet_AntiKt4LCTopo_flavor_weight_MV1c->at(jet_v_tight[i].first),weight);
	break;
      case 15:
	break;
      default:
	h_mv1cweight_light->Fill(jet_AntiKt4LCTopo_flavor_weight_MV1c->at(jet_v_tight[i].first),weight);
      }
    }
  }
  */
  if(jet_v_tight.size() > 0){
    h_leadjet_pt_tighteta->Fill(jet_v_tight[0].second.Pt()/1000.,weight);
    h_leadjet_y_tighteta->Fill(jet_v_tight[0].second.Rapidity(),weight);
  }
  if(jet_v_tight.size() > 1){
    TLorentzVector tmp_4v_tight = jet_v_tight[0].second + jet_v_tight[1].second;
    h_subjet_pt_tighteta->Fill(jet_v_tight[1].second.Pt()/1000.,weight);
    h_subjet_y_tighteta->Fill(jet_v_tight[1].second.Pt()/1000.,weight);
    h_dijet_m_tighteta->Fill((tmp_4v_tight.M())/1000.,weight);
    h_dijet_dR_tighteta->Fill(jet_v_tight[1].second.DeltaR(jet_v_tight[0].second),weight);
    h_dijet_dphi_tighteta->Fill(fabs(jet_v_tight[1].second.DeltaPhi(jet_v_tight[0].second)),weight);
    del_eta = jet_AntiKt4LCTopo_eta->at(jet_v_tight[0].first) - jet_AntiKt4LCTopo_eta->at(jet_v_tight[1].first);
    del_phi = fabs(jet_AntiKt4LCTopo_phi->at(jet_v_tight[0].first) - jet_AntiKt4LCTopo_phi->at(jet_v_tight[1].first));
    if(del_phi > TMath::Pi()) del_phi = (2*TMath::Pi()) - del_phi;
    del_y = jet_v_tight[1].second.Rapidity()-jet_v_tight[0].second.Rapidity();
    h_dijet_dy_tighteta->Fill(fabs(del_y),weight);
    h_dijet_deta_tighteta->Fill(fabs(del_eta),weight);
  }

  //apply MET cut

  //  if(finalMET_et/1000. > 70.0) return kFALSE;
  //MET optimization block
  if(finalMET_et/1000. <= 40) met40 = true;
  if(finalMET_et/1000. <= 50) met50 = true;
  if(finalMET_et/1000. <= 60) met60 = true;
  if(finalMET_et/1000. <= 70) met70 = true;
  if(finalMET_et/1000. <= 80) met80 = true;

  if(met70){
    h_Z_mass_MET->Fill(Zmass,weight);
    h_Z_pt_MET->Fill(Z_fourv.Pt()/1000.,weight);
    h_njets_MET->Fill(jetn_final,weight);
    for(int i = 0; i < jet_v.size(); i++){
      h_jet_pt_MET->Fill(jet_v[i].second.Pt()/1000.,weight);
    }
    if(jet_v.size() > 0){
      h_leadjet_pt_MET->Fill(jet_v[0].second.Pt()/1000.,weight);
      h_jet_st_MET->Fill(st/1000.,weight);
      h_jet_mu_ht_MET->Fill(ht/1000.,weight);
    }
    if(jet_v.size() > 1){
      TLorentzVector dijet_fourv = jet_v[0].second + jet_v[1].second;
      h_dijet_m_MET->Fill(dijet_fourv.M()/1000.,weight);
      h_Zpt_v_jj_pt_MET->Fill(Z_fourv.Pt()/1000.,dijet_fourv.Pt()/1000.,weight);
    }
  }

  //btag optimization   

  float mv1_85_wp = 0.1340;
  float mv1_80_wp = 0.3511;
  float mv1_70_wp = 0.7892;
  float mv1_60_wp = 0.9827;
  float mv1c_80_wp = 0.4051;
  float mv1c_70_wp = 0.7068;
  float mv1c_60_wp = 0.8349;
  float mv1c_57_wp = 0.8641;
  float mv1c_50_wp = 0.9195;

  string label;
  int jet_i;
  //bjet calibration
  //comment out until new skims are complete
  
  for(unsigned int i = 0; i < jet_v.size(); i++){
    
  if(isMC){
      jet_i = jet_v[i].first;
      ajet.jetPt =jet_fourv.Pt(); //MeV
      ajet.jetEta = jet_AntiKt4LCTopo_constscale_eta->at(jet_i);
      ajet.jetTagWeight = jet_AntiKt4LCTopo_flavor_weight_MV1c->at(jet_i);
      if (abs(ajet.jetEta) > 2.5) continue;
      switch (jet_AntiKt4LCTopo_flavor_truth_label->at(jet_i)){
      case 5:
        label = "B";
        break;
      case 4:
        label = "C";
        break;
      case 15 :
        label = "T";
        break;
      default :
        label = "Light";
      }
      //   res = calib->getScaleFactor(ajet, label.c_str(), "0_4051", uncertainty,mapIndex);
      // resineff = calib->getInefficiencyScaleFactor(ajet, label.c_str(), "0_4051", uncertainty,mapIndex);
      res = calib->getScaleFactor(ajet, label.c_str(), "continuous", Analysis::None);
      if(fabs(jet_v[i].second.Eta()) < 2.4) weight *= res.first;

      //if(jet_AntiKt4LCTopo_flavor_weight_MV1c->at(jet_i) > mv1c_80_wp && fabs(jet_v[i].second.Eta()) < 2.4) weight *= res.first;
      //else weight *= resineff.first;
  }
 
  for(unsigned int i=0; i<jet_v_tight.size(); i++){
    h_mv1weight->Fill(jet_AntiKt4LCTopo_flavor_weight_MV1->at(jet_v_tight[i].first),weight);
    h_mv1cweight->Fill(jet_AntiKt4LCTopo_flavor_weight_MV1c->at(jet_v_tight[i].first),weight);
    h_mv1cweight_binned->Fill(jet_AntiKt4LCTopo_flavor_weight_MV1c->at(jet_v_tight[i].first),weight);
    if(isMC){
      switch (jet_AntiKt4LCTopo_flavor_truth_label->at(jet_v_tight[i].first)){
      case 5:
        h_mv1cweight_bottom->Fill(jet_AntiKt4LCTopo_flavor_weight_MV1c->at(jet_v_tight[i].first),weight);
        break;
      case 4:
        h_mv1cweight_charm->Fill(jet_AntiKt4LCTopo_flavor_weight_MV1c->at(jet_v_tight[i].first),weight);
        break;
      case 15:
        break;
      default:
        h_mv1cweight_light->Fill(jet_AntiKt4LCTopo_flavor_weight_MV1c->at(jet_v_tight[i].first),weight);
      }
    }
  }


    if(jet_AntiKt4LCTopo_flavor_weight_MV1c->at(jet_v[i].first) > mv1c_80_wp && fabs(jet_v[i].second.Eta()) < 2.4){
      bjet_v.push_back(jet_v[i]);
      h_bjet_rank->Fill(i,weight);
      h_bjet_pt->Fill(jet_v[i].second.Pt()/1000.,weight);
      h_bjet_y->Fill(jet_v[i].second.Rapidity(),weight);
    }
  }

  if(met70){
    h_bjet_n->Fill(bjet_v.size(),weight);
  }
  for(unsigned int i = 0; i < jet_v.size(); i++){
    if(jet_AntiKt4LCTopo_flavor_weight_MV1->at(jet_v[i].first) > mv1_85_wp && fabs(jet_v[i].second.Eta()) < 2.4){
      bjet_v_mv1_85.push_back(jet_v[i]);
    }
    if(jet_AntiKt4LCTopo_flavor_weight_MV1->at(jet_v[i].first) > mv1_80_wp && fabs(jet_v[i].second.Eta()) < 2.4){
      bjet_v_mv1_80.push_back(jet_v[i]);
    }
    if(jet_AntiKt4LCTopo_flavor_weight_MV1->at(jet_v[i].first) > mv1_70_wp && fabs(jet_v[i].second.Eta()) < 2.4){
      bjet_v_mv1_70.push_back(jet_v[i]);
    }
    if(jet_AntiKt4LCTopo_flavor_weight_MV1->at(jet_v[i].first) > mv1_60_wp && fabs(jet_v[i].second.Eta()) < 2.4){
      bjet_v_mv1_60.push_back(jet_v[i]);
    }
    if(jet_AntiKt4LCTopo_flavor_weight_MV1c->at(jet_v[i].first) > mv1c_80_wp && fabs(jet_v[i].second.Eta()) < 2.4){
      bjet_v_mv1c_80.push_back(jet_v[i]);
    }
    if(jet_AntiKt4LCTopo_flavor_weight_MV1c->at(jet_v[i].first) > mv1c_70_wp && fabs(jet_v[i].second.Eta()) < 2.4){
      bjet_v_mv1c_70.push_back(jet_v[i]);
    }
    if(jet_AntiKt4LCTopo_flavor_weight_MV1c->at(jet_v[i].first) > mv1c_60_wp && fabs(jet_v[i].second.Eta()) < 2.4){
      bjet_v_mv1c_60.push_back(jet_v[i]);
    }
    if(jet_AntiKt4LCTopo_flavor_weight_MV1c->at(jet_v[i].first) > mv1c_57_wp && fabs(jet_v[i].second.Eta()) < 2.4){
      bjet_v_mv1c_57.push_back(jet_v[i]);
    }
    if(jet_AntiKt4LCTopo_flavor_weight_MV1c->at(jet_v[i].first) > mv1c_50_wp && fabs(jet_v[i].second.Eta()) < 2.4){
      bjet_v_mv1c_50.push_back(jet_v[i]);
    }
  }

  if(met40 && (entry%10 == 0 || entry%10 == 5)){
    h_mv1_85_met40_bjetn->Fill(bjet_v_mv1_85.size(),weight);
    h_mv1_80_met40_bjetn->Fill(bjet_v_mv1_80.size(),weight);
    h_mv1_70_met40_bjetn->Fill(bjet_v_mv1_70.size(),weight);
    h_mv1_60_met40_bjetn->Fill(bjet_v_mv1_60.size(),weight);
    h_mv1c_80_met40_bjetn->Fill(bjet_v_mv1c_80.size(),weight);
    h_mv1c_70_met40_bjetn->Fill(bjet_v_mv1c_70.size(),weight);
    h_mv1c_60_met40_bjetn->Fill(bjet_v_mv1c_60.size(),weight);
    h_mv1c_57_met40_bjetn->Fill(bjet_v_mv1c_57.size(),weight);
    h_mv1c_50_met40_bjetn->Fill(bjet_v_mv1c_50.size(),weight);
  }
  if(met50 && (entry%10 == 1 || entry%10 == 6 )){
    h_mv1_85_met50_bjetn->Fill(bjet_v_mv1_85.size(),weight);
    h_mv1_80_met50_bjetn->Fill(bjet_v_mv1_80.size(),weight);
    h_mv1_70_met50_bjetn->Fill(bjet_v_mv1_70.size(),weight);
    h_mv1_60_met50_bjetn->Fill(bjet_v_mv1_60.size(),weight);
    h_mv1c_80_met50_bjetn->Fill(bjet_v_mv1c_80.size(),weight);
    h_mv1c_70_met50_bjetn->Fill(bjet_v_mv1c_70.size(),weight);
    h_mv1c_60_met50_bjetn->Fill(bjet_v_mv1c_60.size(),weight);
    h_mv1c_57_met50_bjetn->Fill(bjet_v_mv1c_57.size(),weight);
    h_mv1c_50_met50_bjetn->Fill(bjet_v_mv1c_50.size(),weight);
  }
  if(met60 && (entry%10 == 2 || entry%10 == 7)){
    h_mv1_85_met60_bjetn->Fill(bjet_v_mv1_85.size(),weight);
    h_mv1_80_met60_bjetn->Fill(bjet_v_mv1_80.size(),weight);
    h_mv1_70_met60_bjetn->Fill(bjet_v_mv1_70.size(),weight);
    h_mv1_60_met60_bjetn->Fill(bjet_v_mv1_60.size(),weight);
    h_mv1c_80_met60_bjetn->Fill(bjet_v_mv1c_80.size(),weight);
    h_mv1c_70_met60_bjetn->Fill(bjet_v_mv1c_70.size(),weight);
    h_mv1c_60_met60_bjetn->Fill(bjet_v_mv1c_60.size(),weight);
    h_mv1c_57_met60_bjetn->Fill(bjet_v_mv1c_57.size(),weight);
    h_mv1c_50_met60_bjetn->Fill(bjet_v_mv1c_50.size(),weight);
  }
  if(met70 && (entry%10 == 3 || entry%10 == 8)){
    h_mv1_85_met70_bjetn->Fill(bjet_v_mv1_85.size(),weight);
    h_mv1_80_met70_bjetn->Fill(bjet_v_mv1_80.size(),weight);
    h_mv1_70_met70_bjetn->Fill(bjet_v_mv1_70.size(),weight);
    h_mv1_60_met70_bjetn->Fill(bjet_v_mv1_60.size(),weight);
    h_mv1c_80_met70_bjetn->Fill(bjet_v_mv1c_80.size(),weight);
    h_mv1c_70_met70_bjetn->Fill(bjet_v_mv1c_70.size(),weight);
    h_mv1c_60_met70_bjetn->Fill(bjet_v_mv1c_60.size(),weight);
    h_mv1c_57_met70_bjetn->Fill(bjet_v_mv1c_57.size(),weight);
    h_mv1c_50_met70_bjetn->Fill(bjet_v_mv1c_50.size(),weight);
  }
  if(met80 && (entry%10 == 4 || entry%10 == 9)){
    h_mv1_85_met80_bjetn->Fill(bjet_v_mv1_85.size(),weight);
    h_mv1_80_met80_bjetn->Fill(bjet_v_mv1_80.size(),weight);
    h_mv1_70_met80_bjetn->Fill(bjet_v_mv1_70.size(),weight);
    h_mv1_60_met80_bjetn->Fill(bjet_v_mv1_60.size(),weight);
    h_mv1c_80_met80_bjetn->Fill(bjet_v_mv1c_80.size(),weight);
    h_mv1c_70_met80_bjetn->Fill(bjet_v_mv1c_70.size(),weight);
    h_mv1c_60_met80_bjetn->Fill(bjet_v_mv1c_60.size(),weight);
    h_mv1c_57_met80_bjetn->Fill(bjet_v_mv1c_57.size(),weight);
    h_mv1c_50_met80_bjetn->Fill(bjet_v_mv1c_50.size(),weight);
  }

  if(bjet_v.size() >= 1){
    h_MET_1tag->Fill(finalMET_et/1000.);
    if(met70){
      h_bjet_deltaR_Zb->Fill(bjet_v[0].second.DeltaR(Z_fourv),weight);
      h_bjet_deltaphi_Zb->Fill(fabs(bjet_v[0].second.DeltaPhi(Z_fourv)),weight);
      h_bjet_lead_pt->Fill(bjet_v[0].second.Pt()/1000.,weight);
      double delta_eta_Zb = fabs(Z_fourv.Eta() - bjet_v[0].second.Eta());
      h_bjet_deltaeta_Zb->Fill(delta_eta_Zb,weight);
      h_Z_mass_1b->Fill(Zmass,weight);
    }  
  }
  if(bjet_v.size() >= 2){
    h_MET_2tag->Fill(finalMET_et/1000.);
    if(met70){
      h_bjet_deltaR_bb->Fill(bjet_v[0].second.DeltaR(bjet_v[1].second),weight);
      h_bjet_deltaphi_bb->Fill(fabs(bjet_v[0].second.DeltaPhi(bjet_v[1].second)),weight);
      h_bjet_sublead_pt->Fill(bjet_v[1].second.Pt()/1000.,weight);
      TLorentzVector b_jets_sum = bjet_v[0].second + bjet_v[1].second;
      h_bjet_m_bb->Fill(b_jets_sum.M()/1000.,weight);
      h_bjet_pt_bb->Fill(b_jets_sum.Pt()/1000.,weight);
      double delta_eta_bb = fabs(bjet_v[0].second.Eta()-bjet_v[1].second.Eta());
      h_bjet_deltaeta_bb->Fill(delta_eta_bb,weight);
      h_Zpt_v_bb_pt->Fill(Z_fourv.Pt()/1000.,b_jets_sum.Pt()/1000.,weight);
      h_Z_mass_2b->Fill(Zmass,weight);
    }
  }
  if(!met70) return kFALSE;
  //re-sort b-jets by mv1c weight
  int s;
  pair<int,TLorentzVector> tmp_s;
  for(unsigned int b = 1; b < bjet_v.size(); b++){
    s = b;
    while(s > 0 && jet_AntiKt4LCTopo_flavor_weight_MV1c->at(bjet_v[s-1].first) < jet_AntiKt4LCTopo_flavor_weight_MV1c->at(bjet_v[s].first)){
      tmp_s = bjet_v[s];
      bjet_v[s] = bjet_v[s-1];
      bjet_v[s-1] = tmp_s;
      s--;
    }
  }
  if(bjet_v.size() >= 1){
    h_bjet_deltaR_Zb_mv1c->Fill(bjet_v[0].second.DeltaR(Z_fourv),weight);
    h_bjet_deltaphi_Zb_mv1c->Fill(fabs(bjet_v[0].second.DeltaPhi(Z_fourv)),weight);
    double delta_eta_Zb_mv1c = fabs(Z_fourv.Eta() - bjet_v[0].second.Eta());
    h_bjet_deltaeta_Zb_mv1c->Fill(delta_eta_Zb_mv1c,weight);
  }
  if(bjet_v.size() >= 2){
    h_bjet_deltaR_bb_mv1c->Fill(bjet_v[0].second.DeltaR(bjet_v[1].second),weight);
    h_bjet_deltaphi_bb_mv1c->Fill(fabs(bjet_v[0].second.DeltaPhi(bjet_v[1].second)),weight);
    TLorentzVector b_jets_sum_mv1c = bjet_v[0].second + bjet_v[1].second;
    h_bjet_m_bb_mv1c->Fill(b_jets_sum_mv1c.M()/1000.,weight);
    h_bjet_pt_bb_mv1c->Fill(b_jets_sum_mv1c.Pt()/1000.,weight);
    double delta_eta_bb_mv1c = fabs(bjet_v[0].second.Eta()-bjet_v[1].second.Eta());
    h_bjet_deltaeta_bb_mv1c->Fill(delta_eta_bb_mv1c,weight);
    h_Zpt_v_bb_pt_mv1c->Fill(Z_fourv.Pt()/1000.,b_jets_sum_mv1c.Pt()/1000.,weight);
  }

   return kTRUE;
}

void analysis_Zmumu::SlaveTerminate()
{
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.

}

void analysis_Zmumu::Terminate()
{
   // The Terminate() function is the last function to be called during
   // a query. It always runs on the client, it can be used to present
   // the results graphically or save the results to file.

  string output_name_string;
  vector<string> output_split;
  string output_split_str;
  vector<string> fname_split;
  ofstream results_txt;
  string cf_filename;

  if(!isGrid){
    output_name_string = string(output_name.Data());
    output_split = splitstring(output_name_string,'/');
    output_split_str = output_split.back();
    fname_split = splitstring(output_split_str,'_');
    
    cf_filename = "./cutflows/" + fname_split.front() + ".txt";
    cout << "cutflow file name: " << cf_filename << endl;
    results_txt.open(cf_filename.c_str(), ios::out);
  }

  cout << "Number of events processed: " << n_events << endl;
  cout << "Number of Z bosons (includes BCH flag cut): " << h_Z_mumu->GetEntries() << endl;
  
  cout << "Cutflow values (unweighted)" << endl;
  cout << "---------------------------------------------------------" << endl;
  for(int i=0; i < icut_max; i++){
    cout << "Cut Z " << setw(3) << i << " : " << setw(30) << cutdes[i] << " : " << h_cutflow->GetBinContent(i+1) << endl;
  }  

  cout << "Cutflow values (weighted)" << endl;
  cout << "---------------------------------------------------------" << endl;
  for(int i=0; i < icut_max; i++){
    cout << "Cut Z " << setw(3) << i << " : " << setw(30) << cutdes[i] << " : " << h_cutflow_w->GetBinContent(i+1) << endl;
  }

  /*  cout << "Event numbers and pT: 3 and 4 jet bin" << endl;
  for(unsigned int i = 0; i < onejet_eventn.size(); i++){
    cout << "Jet multiplicity: " << onejet_eventn[i].first << "; EventNumber: " << onejet_eventn[i].second << endl;
    cout << "Jet (E,px,py,pz): " << cutflowjet_v.at(i).E() << " " << cutflowjet_v.at(i).Px() << " " << cutflowjet_v.at(i).Py() << " " << cutflowjet_v.at(i).Pz() << endl;
    cout << "--------------------------------------------------------" << endl;
    }*/
  /*  cout << "Event numbers and pT: 3 and 4 jet bin" << endl;
  for(multimap<UInt_t,pair<TLorentzVector,float> >::iterator it = cutflowjet_map.begin();
      it != cutflowjet_map.end();
      ++it){
    cout << "Event Number: " << (*it).first << ", jet(pT,eta,jvf): " << (*it).second.first.Pt() << "," << (*it).second.first.Eta() << "," << (*it).second.second << endl;
  }
*/
  /*  cout << "Check event number 91972557" << endl;
  cout << "cut failed: " << eventcheckcut << endl;
  for(multimap<UInt_t,pair<TLorentzVector,float> >::iterator it = eventcheck_map.begin();
      it != eventcheck_map.end();
      ++it){
    cout << "Event Number: " << (*it).first << ", jet(pT,eta,jvf): " << (*it).second.first.Pt() << "," << (*it).second.first.Eta() << "," << (*it).second.second << endl;
    }*/
  /*cout << "Check BCH: event number 91972557" << endl;
  for(unsigned int x=0; x < run_bch_v.size(); x++){
    cout << "(run, lbn, eta, phi, BCH_CORR_CELL, emfrac,pt): " << run_bch_v.at(x) << " " << lbn_bch_v.at(x) << " " << eta_bch_v.at(x) << " " << phi_bch_v.at(x) << " " << BCH_CORR_CELL_v.at(x) << " " << emfrac_v.at(x) << " " << pt_bch_v.at(x) << endl;
  }
  */
  if(!isGrid){
    results_txt << "Cutflow values (weighted)" << endl;
    for(int i=0; i < icut_max; i++){
      results_txt << "Cut Z " << setw(3) << i << " : " << setw(30) << cutdes[i] << " : " << h_cutflow_w->GetBinContent(i+1) << endl;
    }
    results_txt.close();
  }

  time_t end = time(0);
  char* enddt = ctime(&end);
  cout << "Ending time: " << enddt << endl;

  if(isGrid){
    output_name = "output.root";
  }

  cout << "Output file: " << output_name << endl;
  TFile f(output_name,"recreate");
 
  h_good_zeroweight_events->Write();
  h_good_zeroweight_events_pw->Write();
  h_cutflow->Write();
  h_cutflow_w->Write();
  h_triggerSF_size->Write();
  h_Z_mumu->Write();
  h_m_mumu->Write();
  h_Zmumu_hottile->Write();
  h_Z_pt->Write();
  h_Z_y->Write();
  h_Z_mumu_nopw->Write();
  h_Z_pt_nopw->Write();
  h_Z_y_nopw->Write();
  h_Z_phi_nopw->Write();
  h_Z_eta->Write();
  h_Z_phi->Write();
  h_mu_pt->Write();
  h_mu_pt_nocut->Write();
  h_mu_eta->Write();
  h_mu_eta_nocut->Write();
  h_mu_iso->Write();
  h_mu_iso_cut->Write();
  h_mu_phi->Write();
  h_mu_phi_nocut->Write();
  h_avg_pileup_norw->Write();
  h_avg_pileup_noprw->Write();
  h_pileup_norw->Write();
  h_pileup->Write();
  h_avg_pileup->Write();
  h_pileupSF->Write();
  h_pileup_Zsel->Write();
  h_pileup_Zsel_norw->Write();
  h_pileup_avg_Zsel->Write();
  h_pileup_avg_Zsel_norw->Write();
  h_jet_pt->Write();
  h_jet_y->Write();
  h_jet_n->Write();
  h_jet_st->Write();
  h_jet_mu_ht->Write();
  h_leadjet_pt->Write();
  h_leadjet_y->Write();
  h_subjet_pt->Write();
  h_subjet_y->Write();
  h_dijet_m->Write();
  h_dijet_dR->Write();
  h_dijet_dphi->Write();
  h_dijet_dy->Write();
  h_dijet_deta->Write();
  h_dijet_dR_eta->Write();
  h_dijet_dR_y->Write();
  h_3jet_pt->Write();
  h_3jet_y->Write();
  h_4jet_pt->Write();
  h_4jet_y->Write();
  h_Zpt_v_jj_pt->Write();
  h_jet_n_tighteta->Write();
  h_jet_pt_tighteta->Write();
  h_jet_y_tighteta->Write();
  h_jet_st_tighteta->Write();
  h_jet_mu_ht_tighteta->Write();
  h_leadjet_pt_tighteta->Write();
  h_leadjet_y_tighteta->Write();
  h_subjet_pt_tighteta->Write();
  h_subjet_y_tighteta->Write();
  h_dijet_m_tighteta->Write();
  h_dijet_dR_tighteta->Write();
  h_dijet_dphi_tighteta->Write();
  h_dijet_dy_tighteta->Write();
  h_dijet_deta_tighteta->Write();
  h_mv1weight->Write();
  h_mv1cweight->Write();
  h_mv1cweight_binned->Write();
  h_mv1cweight_bottom->Write();
  h_mv1cweight_charm->Write();
  h_mv1cweight_light->Write();

  h_Z_mass_0j->Write();
  h_Z_mass_1j->Write();
  h_Z_mass_2j->Write();
  h_Z_mass_3j->Write();
  h_Z_mass_4j->Write();
  h_Z_mass_5j->Write();
  h_Z_mass_exactly0j->Write();
  h_Z_mass_exactly1j->Write();
  h_Z_mass_1b->Write();
  h_Z_mass_2b->Write();

  h_Z_mass_MET->Write();
  h_Z_pt_MET->Write();
  h_njets_MET->Write();
  h_jet_pt_MET->Write();
  h_leadjet_pt_MET->Write();
  h_dijet_m_MET->Write();
  h_Zpt_v_jj_pt_MET->Write();
  h_jet_st_MET->Write();
  h_jet_mu_ht_MET->Write();

  h_bjet_n->Write();
  h_bjet_pt->Write();
  h_bjet_lead_pt->Write();
  h_bjet_sublead_pt->Write();
  h_bjet_y->Write();
  h_bjet_m_bb->Write();
  h_bjet_m_bb_mv1c->Write();
  h_bjet_deltaR_bb->Write();
  h_bjet_deltaR_bb_mv1c->Write();
  h_bjet_deltaphi_bb->Write();
  h_bjet_deltaphi_bb_mv1c->Write();
  h_bjet_deltaR_Zb->Write();
  h_bjet_deltaR_Zb_mv1c->Write();
  h_bjet_deltaphi_Zb->Write();
  h_bjet_deltaphi_Zb_mv1c->Write();
  h_bjet_deltaeta_Zb->Write();
  h_bjet_deltaeta_Zb_mv1c->Write();
  h_bjet_deltaeta_bb->Write();
  h_bjet_deltaeta_bb_mv1c->Write();
  h_bjet_rank->Write();
  h_bjet_pt_bb->Write();
  h_bjet_pt_bb_mv1c->Write();
  h_Zpt_v_bb_pt->Write();
  h_Zpt_v_bb_pt_mv1c->Write();
  h_MET->Write();
  h_MET_1tag->Write();
  h_MET_2tag->Write();

  //mv1 optimization
  h_mv1_85_met40_bjetn->Write();
  h_mv1_80_met40_bjetn->Write();
  h_mv1_70_met40_bjetn->Write();
  h_mv1_60_met40_bjetn->Write();
  h_mv1c_80_met40_bjetn->Write();
  h_mv1c_70_met40_bjetn->Write();
  h_mv1c_60_met40_bjetn->Write();
  h_mv1c_57_met40_bjetn->Write();
  h_mv1c_50_met40_bjetn->Write();

  h_mv1_85_met50_bjetn->Write();
  h_mv1_80_met50_bjetn->Write();
  h_mv1_70_met50_bjetn->Write();
  h_mv1_60_met50_bjetn->Write();
  h_mv1c_80_met50_bjetn->Write();
  h_mv1c_70_met50_bjetn->Write();
  h_mv1c_60_met50_bjetn->Write();
  h_mv1c_57_met50_bjetn->Write();
  h_mv1c_50_met50_bjetn->Write();

  h_mv1_85_met60_bjetn->Write();
  h_mv1_80_met60_bjetn->Write();
  h_mv1_70_met60_bjetn->Write();
  h_mv1_60_met60_bjetn->Write();
  h_mv1c_80_met60_bjetn->Write();
  h_mv1c_70_met60_bjetn->Write();
  h_mv1c_60_met60_bjetn->Write();
  h_mv1c_57_met60_bjetn->Write();
  h_mv1c_50_met60_bjetn->Write();

  h_mv1_85_met70_bjetn->Write();
  h_mv1_80_met70_bjetn->Write();
  h_mv1_70_met70_bjetn->Write();
  h_mv1_60_met70_bjetn->Write();
  h_mv1c_80_met70_bjetn->Write();
  h_mv1c_70_met70_bjetn->Write();
  h_mv1c_60_met70_bjetn->Write();
  h_mv1c_57_met70_bjetn->Write();
  h_mv1c_50_met70_bjetn->Write();

  h_mv1_85_met80_bjetn->Write();
  h_mv1_80_met80_bjetn->Write();
  h_mv1_70_met80_bjetn->Write();
  h_mv1_60_met80_bjetn->Write();
  h_mv1c_80_met80_bjetn->Write();
  h_mv1c_70_met80_bjetn->Write();
  h_mv1c_60_met80_bjetn->Write();
  h_mv1c_57_met80_bjetn->Write();
  h_mv1c_50_met80_bjetn->Write();

  h_d0->Write();
  h_d0sig->Write();
  h_z0->Write();
  h_z0sintheta->Write();
  h_nvertices->Write();
  h_nmuons->Write();
  h_vx_z->Write();

  h_d0_aftercut->Write();
  h_d0sig_aftercut->Write();
  h_z0_aftercut->Write();
  h_z0sintheta_aftercut->Write();
  h_nvertices_aftercut->Write();
  h_vx_z_rw->Write();
  
  f.Close();

}

vector<string> analysis_Zmumu::splitstring(const string &s, char delim){
  stringstream ss(s);
  string item;
  vector<string> tokens;
  while(getline(ss,item,delim)){
    tokens.push_back(item);
  }
  return tokens;
}

//For JES package
int analysis_Zmumu::Nsegments(float jet_eta, float jet_phi){
  double delR = 0;
  double delta_phi;
  double delta_eta;

  //Match mspn container to jet delR < 0.4
  delR = 100;
  int index_musp=-1;
  for(int i = 0; i < musp_n; i++){
    delta_phi = fabs(jet_phi - musp_phi->at(i)); //calculate the distance in phi
    if (delta_phi > TMath::Pi()) delta_phi = (2 * TMath::Pi()) - delta_phi; //always take angle below 180 deg
    delta_eta = jet_eta - musp_eta->at(i); //distance in eta
    if(sqrt(pow(delta_phi,2) + pow(delta_eta,2)) < delR){
      delR = sqrt(pow(delta_phi,2) + pow(delta_eta,2));
      index_musp = i;
    }
  }
  if(delR >= 0.4){
    index_musp = -1;
  }
  double Nseg = 0;
  if(index_musp >= 0) Nseg = musp_innerSegments->at(index_musp) + musp_outerSegments->at(index_musp) + musp_middleSegments->at(index_musp);

  return Nseg;

}
//For trigger matching
/*
void analysis_Zmumu::initTriggerMatch(){
  //Code taken from https://twiki.cern.ch/twiki/bin/view/Atlas/TriggerObjectMatching
  triggerNavigationVariables = new TriggerNavigationVariables();
  triggerNavigationVariables->set_trig_DB_SMK(trig_DB_SMK);
  triggerNavigationVariables->set_trig_Nav_n(trig_Nav_n);
  triggerNavigationVariables->set_trig_Nav_chain_ChainId(trig_Nav_chain_ChainId);
  triggerNavigationVariables->set_trig_Nav_chain_RoIType(trig_Nav_chain_RoIType);
  triggerNavigationVariables->set_trig_Nav_chain_RoIIndex(trig_Nav_chain_RoIIndex);*/
/* muon *//*
  triggerNavigationVariables->set_trig_RoI_EF_mu_Muon_ROI(trig_RoI_EF_mu_Muon_ROI);
  triggerNavigationVariables->set_trig_RoI_EF_mu_TrigMuonEFInfoContainer(trig_RoI_EF_mu_TrigMuonEFInfoContainer);
  triggerNavigationVariables->set_trig_RoI_EF_mu_TrigMuonEFInfoContainerStatus(trig_RoI_EF_mu_TrigMuonEFInfoContainerStatus);
  triggerNavigationVariables->set_trig_RoI_L2_mu_CombinedMuonFeature(trig_RoI_L2_mu_CombinedMuonFeature);
  triggerNavigationVariables->set_trig_RoI_L2_mu_CombinedMuonFeatureStatus(trig_RoI_L2_mu_CombinedMuonFeatureStatus);
  triggerNavigationVariables->set_trig_RoI_L2_mu_MuonFeature(trig_RoI_L2_mu_MuonFeature);
  triggerNavigationVariables->set_trig_RoI_L2_mu_Muon_ROI(trig_RoI_L2_mu_Muon_ROI);
  triggerNavigationVariables->set_trig_EF_trigmuonef_track_CB_pt(trig_EF_trigmuonef_track_CB_pt);
  triggerNavigationVariables->set_trig_EF_trigmuonef_track_CB_eta(trig_EF_trigmuonef_track_CB_eta);
  triggerNavigationVariables->set_trig_EF_trigmuonef_track_CB_phi(trig_EF_trigmuonef_track_CB_phi);
  triggerNavigationVariables->set_trig_EF_trigmuonef_track_SA_pt(trig_EF_trigmuonef_track_SA_pt);
  triggerNavigationVariables->set_trig_EF_trigmuonef_track_SA_eta(trig_EF_trigmuonef_track_SA_eta);
  triggerNavigationVariables->set_trig_EF_trigmuonef_track_SA_phi(trig_EF_trigmuonef_track_SA_phi);
  triggerNavigationVariables->set_trig_EF_trigmugirl_track_CB_pt(trig_EF_trigmugirl_track_CB_pt);
  triggerNavigationVariables->set_trig_EF_trigmugirl_track_CB_eta(trig_EF_trigmugirl_track_CB_eta);
  triggerNavigationVariables->set_trig_EF_trigmugirl_track_CB_phi(trig_EF_trigmugirl_track_CB_phi);
  triggerNavigationVariables->set_trig_L2_combmuonfeature_eta(trig_L2_combmuonfeature_eta);
  triggerNavigationVariables->set_trig_L2_combmuonfeature_phi(trig_L2_combmuonfeature_phi);
  triggerNavigationVariables->set_trig_L2_muonfeature_eta(trig_L2_muonfeature_eta);
  triggerNavigationVariables->set_trig_L2_muonfeature_phi(trig_L2_muonfeature_phi);
  triggerNavigationVariables->set_trig_L1_mu_eta(trig_L1_mu_eta);
  triggerNavigationVariables->set_trig_L1_mu_phi(trig_L1_mu_phi);
  triggerNavigationVariables->set_trig_L1_mu_thrName(trig_L1_mu_thrName);
  triggerNavigationVariables->set_trig_RoI_EF_mu_TrigMuonEFIsolationContainer(trig_RoI_EF_mu_TrigMuonEFIsolationContainer); // for 2012 isolated trigger
  triggerNavigationVariables->set_trig_RoI_EF_mu_TrigMuonEFIsolationContainerStatus(trig_RoI_EF_mu_TrigMuonEFIsolationContainerStatus); // for 2012 isolated trigger
  triggerNavigationVariables->set_trig_EF_trigmuonef_track_MuonType(trig_EF_trigmuonef_track_MuonType);  // for full scan trigger matching in 2012

  if(not triggerNavigationVariables->isValid()){
    cerr << "TRIGGER MATCHING VARIABLES NOT CORRECTLY SET" << endl;
  }

  muonTriggerMatchTool = new MuonTriggerMatching(triggerNavigationVariables);
}
*/

//for missing ET tool
void analysis_Zmumu::rebuild_MET(){
  m_metRebuild->reset();
  m_metRebuild->setDoMuEloss(true); 
  m_metRebuild->setIsMuid(true);
  m_metRebuild->setDoJetJVF(kTRUE);

  m_metRebuild->setJetParameters(&JetPtContainer,
                                 &JetEtaContainer,
                                 &JetPhiContainer,
                                 &JetEContainer,
                                 jet_AntiKt4LCTopo_MET_wet,
                                 jet_AntiKt4LCTopo_MET_wpx,
                                 jet_AntiKt4LCTopo_MET_wpy,
                                 jet_AntiKt4LCTopo_MET_statusWord);

  m_metRebuild->setMuonParameters(&MuonPtContainer,
                                  mu_eta,
                                  mu_phi,
                                  mu_MET_wet,
                                  mu_MET_wpx,
                                  mu_MET_wpy,
                                  mu_MET_statusWord);

  m_metRebuild->setExtraMuonParameters(&MuonMSPtContainer,
                                       mu_ms_theta,
                                       mu_ms_phi);
  // calo Eloss correction
  m_metRebuild->setMuonEloss(mu_energyLossPar);

  // remove double-counted segment-tagged muons
  m_metRebuild->configMuTagFix(true, mu_isSegmentTaggedMuon);

  // set soft term
  m_metRebuild->setMETTerm(METUtil::SoftTerms, 
                           MET_CellOut_Eflow_et*cos(MET_CellOut_Eflow_phi), 
                           MET_CellOut_Eflow_et*sin(MET_CellOut_Eflow_phi), 
                           MET_CellOut_Eflow_sumet);


  METUtil::METObject refFinal=m_metRebuild->getMissingET(METUtil::RefFinal);
  finalMET_et=refFinal.et();
  finalMET_phi=refFinal.phi();
  finalMET_etx=refFinal.et()*cos(refFinal.phi());
  finalMET_ety=refFinal.et()*sin(refFinal.phi());
}

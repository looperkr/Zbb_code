#define analysis_Zmumu_cxx
// The class definition in analysis_Zmumu.h has been generated automatically
// by the ROOT utility TTree::MakeSelector(). This class is derived
// from the ROOT class TSelector. For more information on the TSelector
// framework see $ROOTSYS/README/README.SELECTOR or the ROOT User Manual.

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

   TString option = GetOption();

   //print current time
   time_t now = time(0);
   char* dt = ctime(&now);
   cout << "Starting time: " << dt << endl;

   //run flags
   isMC = true;
   isData = !isMC;

   bch_fail = 0;

   n_TRT = 0;
   n_events = 0;
   n_true_bjets = 0;
   n_passing_jets = 0;
   h_Z_mumu = new TH1D("Z_mass","Dimuon mass spectrum (Z window)",4000,0,2000);
   h_mass_nowindow = new TH1D("dimuon_mass","Dimuon mass spectrum",4000,0,2000);
   h_Z_pt = new TH1D("Z_pT", "Z boson pT", 4000, 0, 2000);
   h_Z_y = new TH1D("Z_y", "Z boson rapidity", 240,-6,6);
   h_Z_eta = new TH1D("Z_eta","Z boson #eta", 240,-6,6);
   h_Z_phi = new TH1D("Z_phi","Z boson #phi", 128,-2*TMath::Pi(),2*TMath::Pi());
   h_mu_pt = new TH1D("mu_pT","Single muon pT",4000,0,2000);
   h_mu_pt_nocut = new TH1D("mu_pt_nocut","Single muon pT (full range)",4000,0,2000);
   h_mu_eta_nocut = new TH1D("mu_eta_nocut","Single muon #eta (no pT or Z cuts)",120,-6,6);
   h_mu_eta = new TH1D("mu_eta", "Single muon #eta",120,-6,6);
   h_mu_phi_nocut = new TH1D("mu_phi_nocut","Single muon #phi (no pT or Z cuts)",128,-2*TMath::Pi(),2*TMath::Pi());
   h_mu_phi = new TH1D("mu_phi","Single muon #phi",128,-2*TMath::Pi(),2*TMath::Pi());
   h_cutflow = new TH1F("ICUTZ","ICUTZ",50,0.,50.);
   h_cutflow_w = new TH1F("ICUTZ_w","ICUTZ_w",50,0.,50.);
   h_pileup = new TH1D("pileup","pileup",80,0.,40.);
   h_avg_pileup = new TH1D("avg_pileup","average pileup",80,0.,40.);
   h_pileupSF = new TH1D("pileup_rw_sf","pileup reweighting scale factor",1000,0.,2.5);
   h_jet_pt = new TH1D("jet_pt","jet pT",4000,0,2000);
   h_jet_y = new TH1D("jet_y","jet rapidity",120,-6,6);
   h_jet_n = new TH1D("jet_n","number of jets per event",15,0,15);  
   h_jet_n_tight_eta = new TH1D("jet_n_tight_eta","number of jets per event (|eta| < 2.4)",15,0,15);
   h_jet_pt_tight_eta = new TH1D("jet_pt_tight_eta","jet pT (|eta| < 2.4)",4000,0,2000);
   h_jet_y_tight_eta = new TH1D("jet_y_tight_eta","jet rapidity (|eta| < 2.4)",120,-6,6);
   h_jet_n_35 = new TH1D("jet_n35","#jets (pT > 35 GeV)",15,0,15);
   h_jet_n_40 = new TH1D("jet_n40","#jets (pT > 40 GeV)",15,0,15);
   h_jet_n_45 = new TH1D("jet_n45","#jets (pT > 45 GeV)",15,0,15);
   h_jet_n_50 = new TH1D("jet_n50","#jets (pT > 50 GeV)",15,0,15);
   h_jet_n_55 = new TH1D("jet_n55","#jets (pT > 55 GeV)",15,0,15);
   h_jet_n_60 = new TH1D("jet_n60","#jets (pT > 60 GeV)",15,0,15);
   h_jet_n_100 = new TH1D("jet_n100","#jets (pT > 100 GeV)",15,0,15);
   h_jet_n_150 = new TH1D("jet_n150","#jets (pT > 150 GeV)",15,0,15);
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

   h_Z_mass_MET = new TH1D("Z_mass_MET","Z mass after MET cut",4000,0,2000);
   h_Z_pt_MET = new TH1D("Z_pt_MET","Z pT after MET cut",4000,0,2000);
   h_njets_MET = new TH1D("njets_MET","N_jets after MET cut",12,0,12);
   h_jet_pt_MET = new TH1D("jet_pt_MET","jet pT after MET cut",4000,0,2000);
   h_leadjet_pt_MET = new TH1D("jet_leading_pt_MET","Leading jet pT after MET cut",4000,0,2000);
   h_dijet_m_MET = new TH1D("dijet_m_MET","Dijet mass after MET cut",4000,0,2000);
   h_Zpt_v_jj_pt_MET = new TH2D("Zpt_v_jj_pt_MET","Zpt versus dijet pT after MET cut",4000,0,2000,4000,0,2000);
   h_jet_st_MET = new TH1D("jet_st_MET","ST after MET cut",4000,0,2000);
   h_jet_mu_ht_MET = new TH1D("jet_ht_MET","HT after MET cut",4000,0,2000);

   h_bjet_n = new TH1D("bjet_n","Number of b-tagged jets",12,0,12);
   h_bjet_n_mv1c = new TH1D("bjet_n_mv1c","Number of b-tagged jets (MV1c)",12,0,12);
   h_bjet_pt = new TH1D("bjet_pt","b-tagged jet pT",4000,0,2000);
   h_bjet_pt_mv1c = new TH1D("bjet_pt_mv1c","b-tagged jet pT (MV1c)",4000,0,2000);
   h_bjet_lead_pt = new TH1D("bjet_lead_pt","Leading tagged jet pT",4000,0,2000);
   h_bjet_lead_pt_mv1c = new TH1D("bjet_lead_pt_mv1c","Leading tagged jet pT (MV1c)",4000,0,2000);
   h_bjet_sublead_pt = new TH1D("bjet_sublead_pt","Subleading tagged jet pT",4000,0,2000);
   h_bjet_sublead_pt_mv1c = new TH1D("bjet_sublead_pt_mv1c","Subleading tagged jet pT (MV1c)",4000,0,2000);
   h_bjet_mv1_pt = new TH1D("bjet_mv1_pt","pT of jet with highest MV1 weight",4000,0,2000);
   h_bjet_mv1c_pt = new  TH1D("bjet_mv1c_pt","pT of jet with highest MV1c weight",4000,0,2000);
   h_bjet_y = new TH1D("bjet_y","b-tagged jet rapidity",240,-6,6);
   h_bjet_y_mv1c = new TH1D("bjet_y_mv1c","b-tagged jet rapidity (MV1c)",240,-6,6);
   h_bjet_m_bb = new TH1D("bjet_m_bb","Dijet mass (two b-tags)",4000,0,2000);
   h_bjet_m_bb_mv1 = new TH1D("bjet_m_bb_mv1","Diijet mass (two b-tags, highest mv1 weight)",4000,0,2000);
   h_bjet_m_bb_mv1c = new TH1D("bjet_m_bb_mv1c","Diijet mass (two b-tags, highest mv1c weight)",4000,0,2000);
   h_bjet_deltaR_bb = new TH1D("bjet_delR_bb","#Delta R(b,b)",120,0,6);
   h_bjet_deltaR_bb_mv1 = new TH1D("bjet_delR_bb_mv1","#Delta R(b,b) (MV1)",120,0,6);
   h_bjet_deltaR_bb_mv1c = new TH1D("bjet_delR_bb_mv1c","#Delta R(b,b) (MV1c)",120,0,6);
   h_bjet_deltaphi_bb = new TH1D("bjet_delphi_bb","#Delta#phi(b,b)",160,-4,4);
   h_bjet_deltaphi_bb_mv1 = new TH1D("bjet_delphi_bb_mv1","#Delta#phi(b,b) (MV1)",160,-4,4);
   h_bjet_deltaphi_bb_mv1c = new TH1D("bjet_delphi_bb_mv1","#Delta#phi(b,b) (MV1)",160,-4,4);
   h_bjet_deltaR_Zb = new TH1D("bjet_delR_Zb","#Delta R(Z,b)",120,0,6);
   h_bjet_deltaR_Zb_mv1 = new TH1D("bjet_delR_Zb_mv1","#Delta R(Z,b) (MV1)",120,0,6);
   h_bjet_deltaR_Zb_mv1c = new TH1D("bjet_delR_Zb_mv1c","#Delta R(Z,b) (MV1c)",120,0,6);
   h_bjet_deltaphi_Zb = new TH1D("bjet_deltaphi_bZ","#Delta#phi(Z,b)",200,0,10);
   h_bjet_deltaphi_Zb_mv1 = new TH1D("bjet_deltaphi_bZ_mv1","#Delta#phi(Z,b) (MV1)",200,0,10);
   h_bjet_deltaphi_Zb_mv1c = new TH1D("bjet_deltaphi_bZ_mv1c","#Delta#phi(Z,b) (MV1)",200,0,10);
   h_bjet_deltaeta_Zb = new TH1D("bjet_deltaeta_Zb","#Delta#eta(Z,b)",200,0,10);
   h_bjet_deltaeta_Zb_mv1 = new TH1D("bjet_deltaeta_Zb_mv1","#Delta#eta(Z,b) (MV1)",200,0,10);
   h_bjet_deltaeta_Zb_mv1c = new TH1D("bjet_deltaeta_Zb_mv1c","#Delta#eta(Z,b) (MV1c)",200,0,10);
   h_bjet_deltaeta_bb = new TH1D("bjet_deltaeta_bb","#Delta#eta(b,b)",200,0,10);
   h_bjet_deltaeta_bb_mv1 = new TH1D("bjet_deltaeta_bb_mv1","#Delta#eta(b,b) (MV1)",200,0,10);
   h_bjet_deltaeta_bb_mv1c = new TH1D("bjet_deltaeta_bb_mv1c","#Delta#eta(b,b) (MV1c)",200,0,10);
   h_bjet_rank = new TH1D("bjet_rank","p_{T} rank of b-tagged jets",20,0,20);
   h_bjet_rank_mv1c = new TH1D("bjet_rank_mv1c","p_{T} rank of b-tagged jets (MV1c)",20,0,20);
   h_bjet_pt_bb = new TH1D("bjet_pt_bb","di b-jet pT",4000,0,2000);
   h_bjet_pt_bb_mv1 = new TH1D("bjet_pt_bb_mv1","di b-jet pT (MV1)",4000,0,2000);
   h_bjet_pt_bb_mv1c = new TH1D("bjet_pt_bb_mv1c","di b-jet pT (MV1c)",4000,0,2000);
   h_Zpt_v_bb_pt = new TH2D("Zpt_v_bb_pt","Z pT versus di b-jet pT",4000,0,2000,4000,0,2000);
   h_Zpt_v_bb_pt_mv1 =new TH2D("Zpt_v_bb_pt_mv1","Z pT versus di b-jet pT (MV1)",4000,0,2000,4000,0,2000);
   h_Zpt_v_bb_pt_mv1c =new TH2D("Zpt_v_bb_pt_mv1c","Z pT versus di b-jet pT (MV1c)",4000,0,2000,4000,0,2000);
   h_MET = new TH1D("met","MET",4000,0,2000);

   //MET optimization histograms
   h_met20_bjetn = new TH1D("met20_bjetn","#bjets, MET > 20",12,0,12);
   h_met30_bjetn = new TH1D("met30_bjetn","#bjets, MET > 30",12,0,12);
   h_met40_bjetn = new TH1D("met40_bjetn","#bjets, MET > 40",12,0,12);
   h_met50_bjetn = new TH1D("met50_bjetn","#bjets, MET > 50",12,0,12);
   h_met60_bjetn = new TH1D("met60_bjetn","#bjets, MET > 60",12,0,12);
   h_met70_bjetn = new TH1D("met70_bjetn","#bjets, MET > 70",12,0,12);
   h_met80_bjetn = new TH1D("met80_bjetn","#bjets, MET > 80",12,0,12);
   h_met90_bjetn = new TH1D("met90_bjetn","#bjets, MET > 90",12,0,12);
   h_met100_bjetn = new TH1D("met100_bjetn","#bjets, MET > 100",12,0,12);
   h_met110_bjetn = new TH1D("met110_bjetn","#bjets, MET > 120",12,0,12);
   h_met120_bjetn = new TH1D("met120_bjetn","#bjets, MET > 130",12,0,12);
   h_met130_bjetn = new TH1D("met130_bjetn","#bjets, MET > 140",12,0,12);
   h_met140_bjetn = new TH1D("met140_bjetn","#bjets, MET > 150",12,0,12);
   h_met150_bjetn = new TH1D("met150_bjetn","#bjets, MET > 160",12,0,12);
   
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
   m_pileupTool->AddConfigFile("packages/mc12ab_defaults.prw.root");
   m_pileupTool->SetDataScaleFactors(1./1.09);
   m_pileupTool->AddLumiCalcFile("packages/ilumicalc_2012_AllYear_All_Good.root");
   m_pileupTool->EnableDebugging(true);
   m_pileupTool->Initialize();
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
   //   thebchTool->InitializeTool(isData,m_treader,"share/FractionsRejectedJetsMC.root");
   string bchTool_string = rootpath + "/../BCHCleaningTool/share/FractionsRejectedJetsMC.root";
   thebchTool->InitializeTool(isData,m_treader,bchTool_string.c_str());
   /*~~~~~~~~~~~MET Utility~~~~~~~~~~~~~*/
   m_metRebuild= new METUtility;
   m_metRebuild->configMissingET(true,false); //is2012, isSTVF 
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


  fChain->GetTree()->GetEntry(entry);

  n_events++;
  good_mu_v.clear();
  good_mu_v_index.clear();
  Z_fourv.Clear();
  
  Zmass = 0;
  jet_v.clear();
  bjet_v.clear();
  bjet_v_mv1c.clear();
  float mcw;
  if(isMC)  mcw = mc_event_weight;
  isTileTrip = kFALSE;
  bool mucut1 = false;
  weight = 1.;
  double sf = 1.;

  //MET optimization initialization
  met20 = false;
  met30 =false;
  met40 =false;
  met50 =false;
  met60 =false;
  met70 =false;
  met80 =false;
  met90 =false;
  met100 =false;
  met110 =false;
  met120 =false;
  met130 =false;
  met140 =false;
  met150 =false;

  if(isMC){
    weight *= mcw;
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
  else if(isData){
    //Good runs list
    if(!(grl.HasRunLumiBlock(RunNumber,lbn))) return kFALSE;
    h_cutflow->Fill((Float_t)icut,1);
    h_cutflow_w->Fill((Float_t)icut,weight);
    cutdes[icut] = "GRL"; 
    icut++;
  }
  float pileupweight;
  //pileup reweighting
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
  h_avg_pileup->Fill(averageIntPerXing,weight);


  /*~~~~~~~~~~~selection cuts~~~~~~~~~~~~~*/
  //hfor (overlap removal)
  if(isMC){
    if(top_hfor_type == 4){
      return kFALSE;
    }
    h_cutflow->Fill((Float_t)icut);
    h_cutflow_w->Fill((Float_t)icut,weight);
    cutdes[icut] = "HFOR overlap removal";
    icut++;
  }

  //vtx: >=1 vertex, with >=3 tracks 
  bool good_vtx = false;
  if(vxp_n > 0){
    for(int i = 0; i < vxp_n; i++){
      if(vxp_nTracks->at(i) >= 3) good_vtx = true;
    }
  }
  if(!good_vtx) return kFALSE;
  h_cutflow->Fill((Float_t)icut);
  h_cutflow_w->Fill((Float_t)icut,weight);
  cutdes[icut] = "Vertex";
  icut++;

  //trigger: EF_mu24i_tight || EF_mu36_tight
  //  if(!(EF_mu24i_tight || EF_mu36_tight)) return kFALSE;
  if(!EF_mu18_tight_mu8_EFFS) return kFALSE;
  h_cutflow_w->Fill((Float_t)icut,weight);
  h_cutflow->Fill((Float_t)icut);
  cutdes[icut] = "Trigger";
  icut++;

  if(isData){
    isTileTrip=m_treader->checkEvent(RunNumber,lbn,EventNumber);
  }
  if((!isTileTrip && isData) || larError==2 || tileError==2 || (coreFlags&0x40000)!=0) return kFALSE;
  h_cutflow->Fill((Float_t)icut);
  h_cutflow_w->Fill((Float_t)icut,weight);
  cutdes[icut] = "Bad events";
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
  int muon_cf [muoncf_n] = {};

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
    if (!(((mu_author->at(imu)==11&&mu_nprecisionLayers->at(imu)>2&&fabs(mu_eta->at(imu))>2.5)||
           (mu_author->at(imu)==6)||
           (mu_author->at(imu)==12&&mu_momentumBalanceSignificance->at(imu)<4)||
           (mu_author->at(imu)==13&&mu_momentumBalanceSignificance->at(imu)<4&&mu_isCombinedMuon->at(imu))
           ) && !(mu_isStandAloneMuon->at(imu)))) continue;
    muon_cf[0]++;
    //ID track selection (as described in muon CP Twiki) 
    if(!(mu_nPixHits->at(imu)+mu_nPixelDeadSensors->at(imu) > 0)) continue;
    muon_cf[1]++; //pixel req.
    if(!(mu_nSCTHits->at(imu)+mu_nSCTDeadSensors->at(imu) > 4)) continue;
    muon_cf[2]++; // sct req.
    if(!(mu_nPixHoles->at(imu)+mu_nSCTHoles->at(imu) < 3)) continue;
    muon_cf[3]++; //hole req.
    if((fabs(mu_eta->at(imu)) >= 0.1) && (fabs(mu_eta->at(imu)) < 1.9)){
      n_TRT = mu_nTRTHits->at(imu) + mu_nTRTOutliers->at(imu);
      if(!(n_TRT > 5)) continue;
      if(!(mu_nTRTOutliers->at(imu) < 0.9*n_TRT)) continue;
    }
    muon_cf[4]++; //TRT req.
    //IP significance < 3
    if(!(fabs(mu_trackd0pvunbiased->at(imu)/mu_tracksigd0pvunbiased->at(imu)) < 3)) continue;    
    muon_cf[5]++;
    //isolation: ptcone20/pt <= 0.1 
    if(!(mu_ptcone20->at(imu)/mu_pt->at(imu) <= 0.1)) continue;
    muon_cf[6]++;
    //|eta| < 2.4
    if(!(fabs(mu_eta->at(imu)) < 2.4)) continue;
    muon_cf[7]++;
    //impact parameter < 0.5 mm
    if(!(fabs(mu_trackz0pvunbiased->at(imu)) * TMath::Sin(mu_tracktheta->at(imu)) < 0.5)) continue;
    //pt > 25 GeV
    h_mu_pt_nocut->Fill(mu_pt->at(imu)/1000.,weight);
    h_mu_phi_nocut->Fill(mu_phi->at(imu),weight);
    h_mu_eta_nocut->Fill(mu_eta->at(imu),weight);
    if(m_ptCB_smeared/1000. > 7.0 && !mucut1){
      muon_cf[8]++;
      mucut1 = true;
    }
    if(!(m_ptCB_smeared/1000. > 25.)) continue;
    //if(!(mu_pt->at(imu)/1000. > 20.)) continue;
    /*    mu_fourv.SetPx(mu_px->at(imu));
    mu_fourv.SetPy(mu_py->at(imu));
    mu_fourv.SetPz(mu_pz->at(imu));
    mu_fourv.SetE(mu_E->at(imu));
    */
    mu_fourv.SetPtEtaPhiM(m_ptCB_smeared, m_eta, m_phi, m_mass);
    good_mu_v.push_back(mu_fourv);
    good_mu_v_index.push_back(imu);
    
  }
  //Muon selection cutflow
  if(muon_cf[0] > 0){
    h_cutflow_w->Fill(Float_t(icut),weight);
    h_cutflow->Fill(Float_t(icut));
  }
  cutdes[icut] = "Medium+";
  icut++;
  if(muon_cf[1] > 0){
    h_cutflow_w->Fill(Float_t(icut),weight);
    h_cutflow->Fill(Float_t(icut));
  }
  cutdes[icut] = "Pixel req.";
  icut++;
  if(muon_cf[2] > 0){
    h_cutflow_w->Fill(Float_t(icut),weight);
    h_cutflow->Fill(Float_t(icut));
  }
  cutdes[icut] = "SCT req.";
  icut++;
  if(muon_cf[3] > 0){
    h_cutflow_w->Fill(Float_t(icut),weight);
    h_cutflow->Fill(Float_t(icut));
  }    
  cutdes[icut] = "Hole req.";
  icut++;
  if(muon_cf[4] > 0){
    h_cutflow_w->Fill(Float_t(icut),weight);
    h_cutflow->Fill(Float_t(icut));
  }
  cutdes[icut] = "TRT req.";
  icut++;
  if(muon_cf[5] > 0){
    h_cutflow_w->Fill(Float_t(icut),weight);
    h_cutflow->Fill(Float_t(icut));
  }
  cutdes[icut] = "d0 significance";
  icut++;
  if(muon_cf[6] > 0){
    h_cutflow_w->Fill(Float_t(icut),weight);
    h_cutflow->Fill(Float_t(icut));
  }    
  cutdes[icut] = "Isolation req.";
  icut++;
  if(muon_cf[7] > 0){
    h_cutflow_w->Fill(Float_t(icut),weight);
    h_cutflow->Fill(Float_t(icut));
  }
  cutdes[icut] = "|eta| < 2.4";
  icut++;
  if(muon_cf[8] > 0){
    h_cutflow_w->Fill(Float_t(icut),weight);
    h_cutflow->Fill(Float_t(icut));
  }
  cutdes[icut] = "AT LEAST 1 GOOD MUON with pT> 7 GeV (includes eta cut)";
  icut++;
  
  /*~~~~~~~~~build Z~~~~~~~~~~~~*/
  //require exactly two muons
  if(good_mu_v.size() == 2){
    h_cutflow_w->Fill(Float_t(icut),weight);
    h_cutflow->Fill(Float_t(icut));
    cutdes[icut] = "Exactly 2 good muons with pT > 25 GeV";
    icut++;
  }
  else return kFALSE;

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

  if(Zmass > 76 && Zmass < 106 && ((mu_charge->at(mu1_ind) * mu_charge->at(mu2_ind)) == -1)){
    //muon scale factor
    if(isMC){
      sf *= m_MCPsf->scaleFactor(mu_charge->at(mu1_ind),good_mu_v.at(0));
      sf *= m_MCPsf->scaleFactor(mu_charge->at(mu2_ind),good_mu_v.at(1));
      weight *= sf;
    }
    h_cutflow_w->Fill(Float_t(icut),weight);
    h_cutflow->Fill(Float_t(icut));
    cutdes[icut] = "Mass cut:  76 <MZ <106 GeV";
    icut++;
    icut_max = icut;
  }
  else return kFALSE;

  /*~~~~~~~~~jet selection~~~~~~~~~~~*/
  int jetn_final = 0;
  int jetn_tight_eta_final = 0;
  int jetn_35 = 0;
  int jetn_40 = 0;
  int jetn_45 = 0;
  int jetn_50 = 0;
  int jetn_55 = 0;
  int jetn_60 = 0;
  int jetn_100 = 0;
  int jetn_150 = 0;
  float deltaR_jlep1 = 0 ;
  float deltaR_jlep2 = 0;

  thebchTool->SetSeed(EventNumber);
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
      bch_fail++;
      return kFALSE;
    }
  }
  else{ //Data
    runnumber_bch = RunNumber;
    luminumber_bch = lbn;
  }


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
    //    jet_fourv.SetPtEtaPhiE(jet_AntiKt4LCTopo_pt->at(ijet),jet_AntiKt4LCTopo_eta->at(ijet),jet_AntiKt4LCTopo_phi->at(ijet),jet_AntiKt4LCTopo_E->at(ijet));
    jet_fourv = myJES->ApplyJetAreaOffsetOriginEtaJESGSC(Eraw,eta_det,phi,m,eta_origin,phi_origin,m_origin,Ax,Ay,Az,Ae,rho,trackWIDTH,nTrk,fTile0,fEM3,Nseg,mu,NPV);

    JetPtContainer.push_back(jet_fourv.Pt());
    JetEtaContainer.push_back(jet_fourv.Eta());
    JetPhiContainer.push_back(jet_fourv.Phi());
    JetEContainer.push_back(jet_fourv.E());

    //BCH flag

    if(runnumber_bch > 0){
      toolFlag = thebchTool->IsInMaskedRegion(runnumber_bch,luminumber_bch,jet_fourv.Eta(),jet_fourv.Phi());
    }
    if(toolFlag) return kFALSE; //Discard event if jet falls in masked region of the calorimeter


    //jet overlap removal
    deltaR_jlep1 = jet_fourv.DeltaR(good_mu_v.at(0));
    deltaR_jlep2 = jet_fourv.DeltaR(good_mu_v.at(1));
    if(deltaR_jlep1 < 0.5 || deltaR_jlep2 < 0.5) continue;

    //pT > 30 GeV
    if(!(jet_fourv.Pt()/1000. > 30)) continue;
    //    if(!(fabs(jet_fourv.Eta()) < 4.4)) continue;
    if(!(fabs(jet_AntiKt4LCTopo_constscale_eta->at(ijet)) < 4.4)) continue;
    //    if((fabs(jet_AntiKt4LCTopo_constscale_eta->at(ijet)) < 2.4 && jet_fourv.Pt()/1000. < 50) && jet_AntiKt4LCTopo_jvtxf->at(ijet) <= 0.5) continue;
    if(fabs(jet_AntiKt4LCTopo_constscale_eta->at(ijet)) < 2.4 && jet_fourv.Pt()/1000. < 50){
      if(!(fabs(jet_AntiKt4LCTopo_jvtxf->at(ijet)) > 0.5)) continue;
    }
    jetn_final++;
    n_passing_jets++;
    jet_pair.first = ijet;
    jet_pair.second = jet_fourv;
    jet_v.push_back(jet_pair);
    h_jet_pt->Fill(jet_fourv.Pt()/1000.);
    h_jet_y->Fill(jet_fourv.Rapidity());
    //tighter eta cuts
    if(fabs(jet_fourv.Eta()) < 2.4){
      jetn_tight_eta_final++;
      h_jet_pt_tight_eta->Fill(jet_fourv.Pt()/1000.);
      h_jet_y_tight_eta->Fill(jet_fourv.Rapidity());
    }
    if(jet_fourv.Pt()/1000. > 35) jetn_35++;
    if(jet_fourv.Pt()/1000. > 40) jetn_40++;
    if(jet_fourv.Pt()/1000. > 45) jetn_45++;
    if(jet_fourv.Pt()/1000. > 50) jetn_50++;
    if(jet_fourv.Pt()/1000. > 55) jetn_55++;
    if(jet_fourv.Pt()/1000. > 60) jetn_60++;
    if(jet_fourv.Pt()/1000. > 100) jetn_100++;
    if(jet_fourv.Pt()/1000. > 150) jetn_150++;
  }

  rebuild_MET();
  h_MET->Fill(finalMET_et/1000.,weight);
  //Fill histograms (selections complete)
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

  h_jet_n->Fill(jetn_final,weight);
  h_jet_n_tight_eta->Fill(jetn_tight_eta_final,weight);
  h_jet_n_35->Fill(jetn_35,weight);
  h_jet_n_40->Fill(jetn_40,weight);
  h_jet_n_45->Fill(jetn_45,weight);
  h_jet_n_50->Fill(jetn_50,weight);
  h_jet_n_55->Fill(jetn_55,weight);
  h_jet_n_60->Fill(jetn_60,weight);
  h_jet_n_100->Fill(jetn_100,weight);
  h_jet_n_150->Fill(jetn_150,weight);
  
  //Add pTs for HT and ST
  //ST: scalar sum of jet pTs
  //HT: scalar sum of jet and lepton pTs
  float st = 0;
  float ht = 0;
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

  if(jet_v.size() > 0){
    h_leadjet_pt->Fill(jet_v[0].second.Pt()/1000.,weight);
    h_leadjet_y->Fill(jet_v[0].second.Rapidity(),weight);
  }

  if(jet_v.size() > 1){
    TLorentzVector tmp_4v = jet_v[0].second + jet_v[1].second;
    h_subjet_pt->Fill(jet_v[1].second.Pt()/1000.,weight);
    h_subjet_y->Fill(jet_v[1].second.Rapidity(),weight);
    h_dijet_m->Fill((tmp_4v.M())/1000.,weight);
    h_dijet_dR->Fill(jet_v[1].second.DeltaR(jet_v[0].second),weight);
    h_dijet_dphi->Fill(fabs(jet_v[1].second.DeltaPhi(jet_v[0].second)),weight);
    float del_eta = jet_AntiKt4LCTopo_eta->at(jet_v[0].first) - jet_AntiKt4LCTopo_eta->at(jet_v[1].first);
    float del_phi = fabs(jet_AntiKt4LCTopo_phi->at(jet_v[0].first) - jet_AntiKt4LCTopo_phi->at(jet_v[1].first));
    if(del_phi > TMath::Pi()) del_phi = (2*TMath::Pi()) - del_phi;
    float del_y = jet_v[1].second.Rapidity()-jet_v[0].second.Rapidity();
    float del_r_eta = TMath::Sqrt(TMath::Power(fabs(del_eta),2) + TMath::Power(del_phi,2));
    float del_r_y = TMath::Sqrt(TMath::Power(del_y,2) + TMath::Power(del_phi,2));
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

  //apply MET cut

  //  if(finalMET_et/1000. > 70.0) return kFALSE;
  //MET optimization block
  if(finalMET_et/1000. > 20) met20 = true;
  if(finalMET_et/1000. > 30) met30 = true;
  if(finalMET_et/1000. > 40) met40 = true;
  if(finalMET_et/1000. > 50) met50 = true;
  if(finalMET_et/1000. > 60) met60 = true;
  if(finalMET_et/1000. > 70) met70 = true;
  if(finalMET_et/1000. > 80) met80 = true;
  if(finalMET_et/1000. > 90) met90 = true;
  if(finalMET_et/1000. > 100) met100 = true;
  if(finalMET_et/1000. > 110) met110 = true;
  if(finalMET_et/1000. > 120) met120 = true;
  if(finalMET_et/1000. > 130) met130 = true;
  if(finalMET_et/1000. > 140) met140 = true;
  if(finalMET_et/1000. > 150) met150 = true;

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
  //jet_AntiKt4LCTopo_flavor_weight_MV1>0.7892 is 70% working point
  for(unsigned int i = 0; i < jet_v.size(); i++){
    if(jet_AntiKt4LCTopo_flavor_weight_MV1->at(jet_v[i].first) > 0.7892 && fabs(jet_v[i].second.Eta()) < 2.4){
      bjet_v.push_back(jet_v[i]);
      h_bjet_rank->Fill(i,weight);
      h_bjet_pt->Fill(jet_v[i].second.Pt()/1000.,weight);
      h_bjet_y->Fill(jet_v[i].second.Rapidity(),weight);
    }
  }
  h_bjet_n->Fill(bjet_v.size(),weight);
  //MET optimization with multiplicity distribution
  if(met20) h_met20_bjetn->Fill(bjet_v.size(),weight);
  if(met30) h_met30_bjetn->Fill(bjet_v.size(),weight);
  if(met40) h_met40_bjetn->Fill(bjet_v.size(),weight);
  if(met50) h_met50_bjetn->Fill(bjet_v.size(),weight);
  if(met60) h_met60_bjetn->Fill(bjet_v.size(),weight);
  if(met70) h_met70_bjetn->Fill(bjet_v.size(),weight);
  if(met80) h_met80_bjetn->Fill(bjet_v.size(),weight);
  if(met90) h_met90_bjetn->Fill(bjet_v.size(),weight);
  if(met100) h_met100_bjetn->Fill(bjet_v.size(),weight);
  if(met110) h_met110_bjetn->Fill(bjet_v.size(),weight);
  if(met120) h_met120_bjetn->Fill(bjet_v.size(),weight);
  if(met130) h_met130_bjetn->Fill(bjet_v.size(),weight);
  if(met140) h_met140_bjetn->Fill(bjet_v.size(),weight);
  if(met150) h_met150_bjetn->Fill(bjet_v.size(),weight);
  
  if(bjet_v.size() >= 1){
    h_bjet_deltaR_Zb->Fill(bjet_v[0].second.DeltaR(Z_fourv),weight);
    h_bjet_deltaphi_Zb->Fill(fabs(bjet_v[0].second.DeltaPhi(Z_fourv)),weight);
    h_bjet_lead_pt->Fill(bjet_v[0].second.Pt()/1000.,weight);
    double delta_eta_Zb = fabs(Z_fourv.Eta() - bjet_v[0].second.Eta());
    h_bjet_deltaeta_Zb->Fill(delta_eta_Zb,weight);
  }
  if(bjet_v.size() >= 2){
    h_bjet_deltaR_bb->Fill(bjet_v[0].second.DeltaR(bjet_v[1].second),weight);
    h_bjet_deltaphi_bb->Fill(fabs(bjet_v[0].second.DeltaPhi(bjet_v[1].second)),weight);
    h_bjet_sublead_pt->Fill(bjet_v[1].second.Pt()/1000.,weight);
    TLorentzVector b_jets_sum = bjet_v[0].second + bjet_v[1].second;
    h_bjet_m_bb->Fill(b_jets_sum.M()/1000.,weight);
    h_bjet_pt_bb->Fill(b_jets_sum.Pt()/1000.,weight);
    double delta_eta_bb = fabs(bjet_v[0].second.Eta()-bjet_v[1].second.Eta());
    h_bjet_deltaeta_bb->Fill(delta_eta_bb,weight);
    h_Zpt_v_bb_pt->Fill(Z_fourv.Pt()/1000.,b_jets_sum.Pt()/1000.,weight);
  }
  //re-sort b-jets by mv1 weight
  int s;
  pair<int,TLorentzVector> tmp_s;
  for(unsigned int b = 1; b < bjet_v.size(); b++){
    s = b;
    while(s > 0 && jet_AntiKt4LCTopo_flavor_weight_MV1->at(bjet_v[s-1].first) < jet_AntiKt4LCTopo_flavor_weight_MV1->at(bjet_v[s].first)){
      tmp_s = bjet_v[s];
      bjet_v[s] = bjet_v[s-1];
      bjet_v[s-1] = tmp_s;
      s--;
    }
  }
  if(bjet_v.size() >= 1){
    h_bjet_deltaR_Zb_mv1->Fill(bjet_v[0].second.DeltaR(Z_fourv),weight);
    h_bjet_deltaphi_Zb_mv1->Fill(fabs(bjet_v[0].second.DeltaPhi(Z_fourv)),weight);
    double delta_eta_Zb_mv1 = fabs(Z_fourv.Eta() - bjet_v[0].second.Eta());
    h_bjet_deltaeta_Zb_mv1->Fill(delta_eta_Zb_mv1,weight);
  }
  if(bjet_v.size() >= 2){
    h_bjet_deltaR_bb_mv1->Fill(bjet_v[0].second.DeltaR(bjet_v[1].second),weight);
    h_bjet_deltaphi_bb_mv1->Fill(fabs(bjet_v[0].second.DeltaPhi(bjet_v[1].second)),weight);
    TLorentzVector b_jets_sum_mv1 = bjet_v[0].second + bjet_v[1].second;
    h_bjet_m_bb_mv1->Fill(b_jets_sum_mv1.M()/1000.,weight);
    h_bjet_pt_bb_mv1->Fill(b_jets_sum_mv1.Pt()/1000.,weight);
    double delta_eta_bb_mv1 = fabs(bjet_v[0].second.Eta()-bjet_v[1].second.Eta());
    h_bjet_deltaeta_bb_mv1->Fill(delta_eta_bb_mv1,weight);
    h_Zpt_v_bb_pt_mv1->Fill(Z_fourv.Pt()/1000.,b_jets_sum_mv1.Pt()/1000.,weight);
  }

  /*MV1c version of b-tagging section*/
  //jet_AntiKt4LCTopo_flavor_weight_MV1c>0.7068 is 70% working point
  for(unsigned int i = 0; i < jet_v.size(); i++){
    if(jet_AntiKt4LCTopo_flavor_weight_MV1c->at(jet_v[i].first) > 0.7068 && fabs(jet_v[i].second.Eta()) < 2.4){
      bjet_v_mv1c.push_back(jet_v[i]);
      h_bjet_rank_mv1c->Fill(i,weight);
      h_bjet_pt_mv1c->Fill(jet_v[i].second.Pt()/1000.,weight);
      h_bjet_y_mv1c->Fill(jet_v[i].second.Rapidity(),weight);
    }
  }
  h_bjet_n_mv1c->Fill(bjet_v_mv1c.size(),weight);
  if(bjet_v_mv1c.size() >= 1){
    h_bjet_deltaR_Zb_mv1c->Fill(bjet_v[0].second.DeltaR(Z_fourv),weight);
    h_bjet_deltaphi_Zb_mv1c->Fill(fabs(bjet_v[0].second.DeltaPhi(Z_fourv)),weight);
    h_bjet_lead_pt_mv1c->Fill(bjet_v[0].second.Pt()/1000.,weight);
  }
  if(bjet_v.size() >= 2){
     h_bjet_sublead_pt_mv1c->Fill(bjet_v[1].second.Pt()/1000.,weight);
  }
  //re-sort by mv1c weight
  int c;
  pair<int,TLorentzVector> tmp_c;
  for(unsigned int bc = 1; bc < bjet_v_mv1c.size(); bc++){
    c = bc;
    while(c > 0 && jet_AntiKt4LCTopo_flavor_weight_MV1->at(bjet_v_mv1c[c-1].first) < jet_AntiKt4LCTopo_flavor_weight_MV1->at(bjet_v_mv1c[c].first)){
      tmp_c = bjet_v_mv1c[c];
      bjet_v_mv1c[c] = bjet_v_mv1c[c-1];
      bjet_v_mv1c[c-1] = tmp_c;
      c--;
    }
  }
  if(bjet_v_mv1c.size() >= 1){
    h_bjet_deltaR_Zb_mv1c->Fill(bjet_v_mv1c[0].second.DeltaR(Z_fourv),weight);
    h_bjet_deltaphi_Zb_mv1c->Fill(fabs(bjet_v_mv1c[0].second.DeltaPhi(Z_fourv)),weight);
    double delta_eta_Zb_mv1c = fabs(Z_fourv.Eta() - bjet_v_mv1c[0].second.Eta());
    h_bjet_deltaeta_Zb_mv1c->Fill(delta_eta_Zb_mv1c,weight);
  }
  if(bjet_v_mv1c.size() >= 2){
    h_bjet_deltaR_bb_mv1c->Fill(bjet_v_mv1c[0].second.DeltaR(bjet_v_mv1c[1].second),weight);
    h_bjet_deltaphi_bb_mv1c->Fill(fabs(bjet_v_mv1c[0].second.DeltaPhi(bjet_v_mv1c[1].second)),weight);
    TLorentzVector b_jets_sum_mv1c = bjet_v_mv1c[0].second + bjet_v_mv1c[1].second;
    h_bjet_m_bb_mv1c->Fill(b_jets_sum_mv1c.M()/1000.,weight);
    h_bjet_pt_bb_mv1c->Fill(b_jets_sum_mv1c.Pt()/1000.,weight);
    double delta_eta_bb_mv1c = fabs(bjet_v_mv1c[0].second.Eta()-bjet_v_mv1c[1].second.Eta());
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

  //ofstream results_txt;
  //results_txt.open("results.txt", ios::out | ios::app);
  cout << "Number of events processed: " << n_events << endl;
  cout << "Number of Z bosons (includes BCH flag cut): " << h_Z_mumu->GetEntries() << endl;
  
  cout << "Cutflow values (unweighted)" << endl;
  cout << "---------------------------------------------------------" << endl;
  for(int i=0; i < icut_max; i++){
    cout << "Cut Z " << setw(3) << i << " : " << setw(30) << cutdes[i] << " : " << h_cutflow->GetBinContent(i+1) << endl;
  }  
  //for(int i=0; i < icut_max; i++){
  // results_txt << h_cutflow->GetBinContent(i+1) << ";";
  // }
  //results_txt << endl;
  //results_txt.close();

  cout << "Cutflow values (weighted)" << endl;
  cout << "---------------------------------------------------------" << endl;
  for(int i=0; i < icut_max; i++){
    cout << "Cut Z " << setw(3) << i << " : " << setw(30) << cutdes[i] << " : " << h_cutflow_w->GetBinContent(i+1) << endl;
  }

  cout << "bch failures: " << bch_fail << endl;

  time_t end = time(0);
  char* enddt = ctime(&end);
  cout << "Ending time: " << enddt << endl;

  //TFile f("output.root","recreate");
  TFile f("output_Ztautau5.root","recreate");

  h_cutflow->Write();
  h_cutflow_w->Write();
  h_Z_mumu->Write();
  h_mass_nowindow->Write();
  h_Z_pt->Write();
  h_Z_y->Write();
  h_Z_eta->Write();
  h_Z_phi->Write();
  h_mu_pt->Write();
  h_mu_pt_nocut->Write();
  h_mu_eta->Write();
  h_mu_eta_nocut->Write();
  h_mu_phi->Write();
  h_mu_phi_nocut->Write();
  h_pileup->Write();
  h_avg_pileup->Write();
  h_pileupSF->Write();
  h_jet_pt->Write();
  h_jet_y->Write();
  h_jet_n->Write();
  h_jet_n_tight_eta->Write();
  h_jet_pt_tight_eta->Write();
  h_jet_y_tight_eta->Write();
  h_jet_n_35->Write();
  h_jet_n_40->Write();
  h_jet_n_45->Write();
  h_jet_n_50->Write();
  h_jet_n_55->Write();
  h_jet_n_60->Write();
  h_jet_n_100->Write();
  h_jet_n_150->Write();
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
  h_bjet_n_mv1c->Write();
  h_bjet_pt->Write();
  h_bjet_pt_mv1c->Write();
  h_bjet_lead_pt->Write();
  h_bjet_lead_pt_mv1c->Write();
  h_bjet_sublead_pt->Write();
  h_bjet_sublead_pt_mv1c->Write();
  h_bjet_mv1_pt->Write();
  h_bjet_mv1c_pt->Write();
  h_bjet_y->Write();
  h_bjet_y_mv1c->Write();
  h_bjet_m_bb->Write();
  h_bjet_m_bb_mv1->Write();
  h_bjet_m_bb_mv1c->Write();
  h_bjet_deltaR_bb->Write();
  h_bjet_deltaR_bb_mv1->Write();
  h_bjet_deltaR_bb_mv1c->Write();
  h_bjet_deltaphi_bb->Write();
  h_bjet_deltaphi_bb_mv1->Write();
  h_bjet_deltaphi_bb_mv1c->Write();
  h_bjet_deltaR_Zb->Write();
  h_bjet_deltaR_Zb_mv1->Write();
  h_bjet_deltaR_Zb_mv1c->Write();
  h_bjet_deltaphi_Zb->Write();
  h_bjet_deltaphi_Zb_mv1->Write();
  h_bjet_deltaphi_Zb_mv1c->Write();
  h_bjet_deltaeta_Zb->Write();
  h_bjet_deltaeta_Zb_mv1->Write();
  h_bjet_deltaeta_Zb_mv1c->Write();
  h_bjet_deltaeta_bb->Write();
  h_bjet_deltaeta_bb_mv1->Write();
  h_bjet_deltaeta_bb_mv1c->Write();
  h_bjet_rank->Write();
  h_bjet_rank_mv1c->Write();
  h_bjet_pt_bb->Write();
  h_bjet_pt_bb_mv1->Write();
  h_bjet_pt_bb_mv1c->Write();
  h_Zpt_v_bb_pt->Write();
  h_Zpt_v_bb_pt_mv1->Write();
  h_Zpt_v_bb_pt_mv1c->Write();
  h_MET->Write();

  //MET optimization
  
  h_met20_bjetn->Write();
  h_met30_bjetn->Write();
  h_met40_bjetn->Write();
  h_met50_bjetn->Write();
  h_met60_bjetn->Write();
  h_met70_bjetn->Write();
  h_met80_bjetn->Write();
  h_met90_bjetn->Write();
  h_met100_bjetn->Write();
  h_met110_bjetn->Write();
  h_met120_bjetn->Write();
  h_met130_bjetn->Write();
  h_met140_bjetn->Write();
  h_met150_bjetn->Write();
  
  f.Close();

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

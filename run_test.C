{
  TChain *chain = new TChain("physics");
  //  chain->Add("/n/atlas05/userdata/klooper/mc12_8TeV.117665.AlpgenPythia_P2011C_ZmumuNp5.merge.NTUP_COMMON.e1477_s1499_s1504_r3658_r3549_p1575/NTUP_COMMON.01344691._000001.root.2");
  //chain->Add("/n/atlas05/userdata/klooper/mc12_8TeV.117665.AlpgenPythia_P2011C_ZmumuNp5.merge.NTUP_COMMON.e1477_s1499_s1504_r3658_r3549_p1575/NTUP_COMMON.01344691._000002.root.2");
  //chain->Add("/n/atlas05/userdata/klooper/mc12_8TeV.110821.AlpgenPythia_P2011C_ZmumubbNp0.merge.NTUP_COMMON.e1477_s1499_s1504_r3658_r3549_p1575/NTUP_COMMON.01344713._000001.root.1");
  //  chain->Add("/n/atlas05/userdata/klooper/data12_8TeV.00213204.physics_Muons.merge.NTUP_COMMON.r4065_p1278_p1675_tid01453025_00/NTUP_COMMON.01453025._000016.root.1");
  //  chain->Add("/n/atlas05/userdata/klooper/data12_8TeV.00213204.physics_Muons.merge.NTUP_COMMON.r4065_p1278_p1675_tid01453025_00/NTUP_COMMON.01453025._000003.root.1");
  //  chain->Add("/n/atlas05/userdata/klooper/mc12_8TeV.147116.AlpgenPythia_Auto_P2011C_ZmumuNp3.merge.NTUP_COMMON.e1880_s1581_s1586_r3658_r3549_p1575/NTUP_COMMON.01344455._000050.root.1");
  //chain->Add("/n/atlas05/userdata/klooper/mc12_8TeV.117661.AlpgenPythia_P2011C_ZmumuNp1.merge.NTUP_COMMON.e1477_s1499_s1504_r3658_r3549_p1575_tid01344687_00/NTUP_COMMON.01344687._000130.root.1");
//ZtautauNp4, because fuck the grid
//   chain->Add("/n/atlas05/userdata/klooper/mc12_8TeV.107674.AlpgenJimmy_AUET2CTEQ6L1_ZtautauNp4.merge.NTUP_COMMON.e1571_s1499_s1504_r3658_r3549_p1575/NTUP_COMMON.01344620._000001.root.1");
//  chain->Add("/n/atlas05/userdata/klooper/mc12_8TeV.107674.AlpgenJimmy_AUET2CTEQ6L1_ZtautauNp4.merge.NTUP_COMMON.e1571_s1499_s1504_r3658_r3549_p1575/NTUP_COMMON.01344620._000002.root.1");
  //chain->Add("/n/atlas05/userdata/klooper/mc12_8TeV.107674.AlpgenJimmy_AUET2CTEQ6L1_ZtautauNp4.merge.NTUP_COMMON.e1571_s1499_s1504_r3658_r3549_p1575/NTUP_COMMON.01344620._000003.root.1");
  //chain->Add("/n/atlas05/userdata/klooper/mc12_8TeV.107674.AlpgenJimmy_AUET2CTEQ6L1_ZtautauNp4.merge.NTUP_COMMON.e1571_s1499_s1504_r3658_r3549_p1575/NTUP_COMMON.01344620._000004.root.1");
  //chain->Add("/n/atlas05/userdata/klooper/mc12_8TeV.107674.AlpgenJimmy_AUET2CTEQ6L1_ZtautauNp4.merge.NTUP_COMMON.e1571_s1499_s1504_r3658_r3549_p1575/NTUP_COMMON.01344621._000005.root.1");
  //chain->Add("/n/atlas05/userdata/klooper/mc12_8TeV.107674.AlpgenJimmy_AUET2CTEQ6L1_ZtautauNp4.merge.NTUP_COMMON.e1571_s1499_s1504_r3658_r3549_p1575/NTUP_COMMON.01344621._000006.root.1");
  //  chain->Add("/n/atlas05/userdata/klooper/mc12_8TeV.147113.AlpgenPythia_Auto_P2011C_ZmumuNp0.merge.NTUP_COMMON.e1880_s1581_s1586_r3658_r3549_p1675/NTUP_COMMON.05841972._000067.pool.root.1");  
  /*  chain->Add("/n/atlas05/userdata/klooper/mc12_8TeV.117050.PowhegPythia_P2011C_ttbar.merge.NTUP_COMMON.e1728_s1581_s1586_r3658_r3549_p1675/NTUP_COMMON.01447622._001565.root.1");
  chain->Add("/n/atlas05/userdata/klooper/mc12_8TeV.117050.PowhegPythia_P2011C_ttbar.merge.NTUP_COMMON.e1728_s1581_s1586_r3658_r3549_p1675/NTUP_COMMON.01447621._001077.root.1");
  chain->Add("/n/atlas05/userdata/klooper/mc12_8TeV.117050.PowhegPythia_P2011C_ttbar.merge.NTUP_COMMON.e1728_s1581_s1586_r3658_r3549_p1675/NTUP_COMMON.01447619._000394.root.2");
  */
  chain->Add("/n/atlas05/userdata/klooper/skim_output/user.klooper.prun_slimmed_147118.AlpgenPythia_Auto_P2011C_ZmumuNp5_16.4.1_v1_skim.root/user.klooper.7374882._000001.skim.root");
  chain->Add("/n/atlas05/userdata/klooper/skim_output/user.klooper.prun_slimmed_147118.AlpgenPythia_Auto_P2011C_ZmumuNp5_16.4.1_v1_skim.root/user.klooper.7374882._000028.skim.root");
  gInterpreter->GenerateDictionary("vector<vector<int> >","vector");
  gROOT->ProcessLine (".x $ROOTCOREDIR/scripts/load_packages.C");
  chain->Process("analysis_Zmumu.C+");
}

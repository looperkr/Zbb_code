#include "AtlasStyle.C"
#include "AtlasLabels.C"
#include "AtlasUtils.h"

void mj_fit(){
  using namespace RooFit;
  
  string f_name = "/n/atlas02/user_codes/looper.6/Vbb/analysis_code/MC_histograms_root/Z_mass_ctrlregion.root";
  string mc_name = "Z_mass_mc";
  string data_name = "Z_mass_data";

  TFile *f = TFile::Open(f_name.c_str(),"READ");
  TH1D *h_mc = (TH1D*)f->Get(mc_name.c_str());
  TH1D *h_data = (TH1D*)f->Get(data_name.c_str());

  RooRealVar  x("x","x",70,120);
  
  RooRealVar N_mc("N_mc","# of events in signal and MC backgrounds",5000,0,1000000);
  RooRealVar N_mj("N_mj","# of multijet events",5000,0,1000000);
  RooRealVar alpha("alpha","alpha",-.05,-2,0);

  RooDataHist h_mc_roofit("mc","mc with x", x, h_mc);
  RooHistPdf mc("mc","mc pdf", x, h_mc_roofit);
  RooExponential mj("mj","multijet background",x,alpha);
  RooDataHist data("data","data", x, h_data);

  TCanvas *c = new TCanvas();
  RooPlot* xframe = x.frame();
  
  RooAddPdf model("model","MC + exponential", RooArgList(mc,mj),RooArgList(N_mc,N_mj));
  RooFitResult *fitres = model.fitTo(data,Save(kTRUE),SumW2Error(kTRUE),PrintEvalErrors(-1));

  /*
  data.plotOn(xframe);
  model.plotOn(xframe,Components(mc),LineStyle(kDashed),LineColor(kRed));
  model.plotOn(xframe,Components(mj),LineStyle(kDashed),LineColor(kBlue));
  model.plotOn(xframe,LineColor(kBlack));
  model.paramOn(xframe,Layout(0.55));
  xframe->Draw();
  */

  cout << "##################" << endl;
  cout << alpha << endl;
  alpha.setConstant(kTRUE);

  //Use fit of control region to fit background in signal region

  string f_name_sregion = "/n/atlas02/user_codes/looper.6/Vbb/analysis_code/MC_histograms_root/m_mumu.root";
  TFile *f_sregion = TFile::Open(f_name_sregion.c_str(),"READ");
  string mc_name_sregion = "m_mumu_mc";
  string data_name_sregion = "m_mumu_data";
  TH1D *h_mc_sregion = (TH1D*)f_sregion->Get(mc_name_sregion.c_str());
  TH1D *h_data_sregion = (TH1D*)f_sregion->Get(data_name_sregion.c_str());

  RooDataHist h_mc_roofit_sregion("mc","mc with x", x, h_mc_sregion);
  RooHistPdf mc_sregion("mc","mc pdf", x, h_mc_roofit_sregion);
  RooExponential mj_sregion("mj","multijet background",x,alpha);
  RooDataHist data_sregion("data","data", x, h_data_sregion);
  
  RooRealVar N_mc_sregion("N_mc_sregion","# of events in signal and MC backgrounds",7223577,0,10E7);
  RooRealVar N_mj_sregion("N_mj_sregion","# of multijet events",100,10,10E7);
  RooAddPdf model_sregion("model_sregion","MC + exponential", RooArgList(mc_sregion,mj_sregion),RooArgList(N_mc_sregion,N_mj_sregion));
  RooFitResult *fitres = model_sregion.fitTo(data_sregion,Save(kTRUE),SumW2Error(kTRUE),PrintEvalErrors(-1));

  //  c->SetLogy();
  //  xframe->SetMinimum(10);
  // xframe->SetMaximum(10E9);
  data_sregion.plotOn(xframe);
  model_sregion.plotOn(xframe,Components(mc_sregion),LineStyle(kDashed),LineColor(kRed));
  model_sregion.plotOn(xframe,Components(mj_sregion),LineStyle(kDashed),LineColor(kBlue));
  model_sregion.plotOn(xframe,LineColor(kBlack));
  model_sregion.paramOn(xframe,Layout(0.55));
 
  //  xframe->SetMinimum(100);
  // xframe->SetMaximum(10E9);
  //c->SetLogy();
  xframe->Draw();

  cout << alpha << endl;

}

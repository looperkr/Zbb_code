#include "AtlasStyle.C"
#include "AtlasLabels.C"
#include "AtlasUtils.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "TH1.h"
#include "TLegend.h"
#include "TImage.h"
#include "TString.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TMath.h"
#include "TPad.h"
#include "TLatex.h"
#include "THStack.h"
#ifndef __CINT__
#include <ctime>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#endif

string NumToStr(int number_val){
  ostringstream ss;
  ss << number_val;
  return ss.str();
}

string NumToStr(float number_val){
  ostringstream ss;
  ss << number_val;
  return ss.str();
}

string NumToStr(double number_val){
  ostringstream ss;
  ss << number_val;
  return ss.str();
}
void create_dir(string & plots_path, string & plots_dir){
  //Get current date and save to vector<string>                                                                                                                              
  time_t now = time(0);
  string date_str(ctime(&now));
  string buffer_str;
  stringstream ss(date_str);

  vector<string> tokens;
  while (ss >> buffer_str) tokens.push_back(buffer_str);

  plots_dir = plots_path + "plots_" + tokens[1] + tokens[2];

  //check if directory for today's date exists: if not, create directory                                                                                                     
  //  struct stat statbuf;
  bool isDir = false;
  if(gSystem->OpenDirectory(plots_dir.c_str()) != 0){
    isDir = true;
  }
  if(!isDir){
    gSystem->mkdir(plots_dir.c_str());
    cout << "Test" << endl;
  }
}


void mj_fit(string process, bool isSherpa=false){
  using namespace RooFit;

  bool isLog = true;

  string f_name = "/n/atlas02/user_codes/looper.6/Vbb/analysis_code/MC_histograms_root/"+process+"_ctrlregion.root";
  string mc_name = process;
  if(isSherpa) mc_name += "_sherpa";
  else mc_name += "_mc";
  string data_name = process + "_data";

  TFile *f = TFile::Open(f_name.c_str(),"READ");
  TH1D *h_mc = (TH1D*)f->Get(mc_name.c_str());
  TH1D *h_data = (TH1D*)f->Get(data_name.c_str());

  double data_max_ctrl = h_data->GetMaximum();

  RooRealVar  x("m_{#mu#mu} [GeV]","m_{#mu#mu} [GeV]",70,120);
  
  RooRealVar N_mc("N_{mc}","# of events in signal and MC backgrounds",5000,0,1000000);
  RooRealVar N_mj("N_{multijet}","# of multijet events",5000,0,1000000);
  RooRealVar alpha("#alpha","alpha",-.05,-2,0);

  RooDataHist h_mc_roofit("mc","mc with x", x, h_mc);
  RooHistPdf mc("mc","mc pdf", x, h_mc_roofit);
  RooExponential mj("mj","multijet background",x,alpha);
  RooDataHist data("data","data", x, h_data);

  TCanvas *c = new TCanvas("c","c",800,600);
  RooPlot* xframe = x.frame();
  
  RooAddPdf model("model","MC + exponential", RooArgList(mc,mj),RooArgList(N_mc,N_mj));
  RooFitResult *fitres = model.fitTo(data,Save(kTRUE),SumW2Error(kTRUE),PrintEvalErrors(-1));

  string plt_path = "/n/atlas02/user_codes/looper.6/Vbb/analysis_plots/";
  string plt_dir;

  create_dir(plt_path,plt_dir);

  TLegend *leg = new TLegend(0.6,0.6,0.95,0.76);
  
  data.plotOn(xframe,Name("data"));
  model.plotOn(xframe,Components(mc),LineStyle(kDashed),LineColor(kRed),Name("mc"));
  model.plotOn(xframe,Components(mj),LineStyle(kDashed),LineColor(kBlue),Name("mj"));
  model.plotOn(xframe,LineColor(kBlack),Name("model"));
  model.paramOn(xframe,Layout(0.55));
  xframe->Draw();

  Double_t chi2 = xframe->chiSquare("model","data",3);
  cout << "Chi2: " << chi2 << endl;

  string chi2_str = NumToStr(chi2);
  chi2_str = "#chi^{2}/ndf: " + chi2_str;

  double chi2_placement = data_max_ctrl*0.57;

  TLatex* txt = new TLatex(99,chi2_placement,chi2_str.c_str());
  txt->SetTextSize(0.04);
  xframe->addObject(txt);

  leg->AddEntry(xframe->findObject("model"),"Total model","l");
  leg->AddEntry(xframe->findObject("data"),"data","lp");
  leg->AddEntry(xframe->findObject("mc"),"non-multijet","l");
  leg->AddEntry(xframe->findObject("mj"),"multijet","l");
  leg->SetBorderSize(0);

  xframe->Draw();
  leg->Draw();
  
  string ctrl_name = plt_dir + "/" + process + "_ctrl";
  if(isSherpa) ctrl_name += "_sherpa";
  string ctrl_pdf = ctrl_name + ".pdf";

  c->SaveAs(ctrl_pdf.c_str());

  //end control region plotting
  cout << "##################" << endl;
  cout << alpha << endl;
  alpha.setConstant(kTRUE);

  //Use fit of control region to fit background in signal region

  TCanvas *c2 = new TCanvas("c2","c2",800,600);
  RooPlot* xframe_sig = x.frame();

  string f_name_sregion = "/n/atlas02/user_codes/looper.6/Vbb/analysis_code/MC_histograms_root/"+process+"_wide.root";
  //  string f_name_0j = "/n/atlas02/user_codes/looper.6/Vbb/analysis_code/MC_histograms_root/Z_mass_exactly0j_wide.root";
  TFile *f_sregion = TFile::Open(f_name_sregion.c_str(),"READ");
  //  TFile *f_0j = TFile::Open(f_name_0j.c_str(),"READ");
  string mc_name_sregion = process;
  if(isSherpa) mc_name_sregion += "_sherpa";
  else mc_name_sregion += "_mc";
  string data_name_sregion = process+"_data";
  TH1D *h_mc_sregion = (TH1D*)f_sregion->Get(mc_name_sregion.c_str());
  TH1D *h_data_sregion = (TH1D*)f_sregion->Get(data_name_sregion.c_str());
  //  TH1D *h_data_nojets = (TH1D*)f_0j->Get("Z_mass_exactly0j_data");

  double data_max_sig = h_data_sregion->GetMaximum();

  RooDataHist h_mc_roofit_sregion("mc","mc with x", x, h_mc_sregion);
  RooHistPdf mc_sregion("mc","mc pdf", x, h_mc_roofit_sregion);

  RooExponential mj_sregion("mj","multijet background",x,alpha);
  RooHistPdf data_ctrlreg("data_ctrl","data_ctrl",x,data);
  
  RooDataHist data_sregion("data","data_sregion", x, h_data_sregion);
  //  RooDataHist data_nojets_hist("nojets","nojets",x,h_data_nojets);


  double n_mj_fit;
  double n_mc_fit;
  if(isSherpa){
    n_mj_fit = 5000;
    n_mc_fit = 7223577;
  }
  else{
    n_mj_fit = 100;
    n_mc_fit = 7223577;
  }


  RooRealVar N_mc_sregion("N_{mc}","# of events in signal and MC backgrounds",n_mc_fit,0,10E7);
  RooRealVar N_mj_sregion("N_{multijet}","# of multijet events",n_mj_fit,0,10E7);
  RooAddPdf model_sregion("model_sregion","model_sregion", RooArgList(mc_sregion,mj_sregion),RooArgList(N_mc_sregion,N_mj_sregion));
  //  RooAddPdf model_sregion("model_sregion","model_sregion", RooArgList(mc_sregion,data_ctrlreg),RooArgList(N_mc_sregion,N_mj_sregion));
  RooFitResult *fitres = model_sregion.fitTo(data_sregion,Save(kTRUE),SumW2Error(kTRUE),PrintEvalErrors(-1));


  //begin plot
  TLegend *leg_sig = new TLegend(0.6,0.64,0.95,0.80);

  data_sregion.plotOn(xframe_sig,Name("data_sregion"));
  model_sregion.plotOn(xframe_sig,Components(mc_sregion),LineStyle(kDashed),LineColor(kRed),Name("mc_sregion"));
  model_sregion.plotOn(xframe_sig,Components(mj_sregion),LineStyle(kDashed),LineColor(kBlue),Name("mj_sregion"));
  //model_sregion.plotOn(xframe_sig,Components(data_ctrlreg),LineStyle(kDashed),LineColor(kBlue),Name("mj_sregion"));
  model_sregion.plotOn(xframe_sig,LineColor(kBlack),Name("model_sregion"));
  model_sregion.paramOn(xframe_sig,Layout(0.55));

  Double_t chi2_sig = xframe_sig->chiSquare("model_sregion","data_sregion",2);

  string chi2_str_sig = NumToStr(chi2_sig);
  chi2_str_sig = "#chi^{2}/NDF: " + chi2_str_sig;
  double chi2_sig;
  if(isLog) chi2_sig = 240000;
  else chi2_sig = data_max_sig*0.59;
  cout << "CHI 2 PLACEMENT: " << chi2_sig << endl;

  TLatex* txt_sig = new TLatex(99,chi2_sig,chi2_str_sig.c_str());
  txt_sig->SetTextSize(0.04);
  //  xframe_sig->addObject(txt_sig);

  if(isLog){
    xframe_sig->SetMaximum(10E8);
  }
  else{
    //xframe_sig->SetMaximum(12E5);
    xframe_sig->SetMaximum(data_max_sig*1.15);
  }
  xframe_sig->SetMinimum(10);
  if(isLog) c2->SetLogy();
  xframe_sig->addObject(txt_sig);
  
  leg_sig->AddEntry(xframe_sig->findObject("model_sregion"),"Total model","l");
  leg_sig->AddEntry(xframe_sig->findObject("data_sregion"),"data","lp");
  leg_sig->AddEntry(xframe_sig->findObject("mc_sregion"),"non-multijet","l");
  leg_sig->AddEntry(xframe_sig->findObject("mj_sregion"),"multijet","l");
  //leg_sig->AddEntry(xframe_sig->findObject("mj_sregion"),"multijet (ctrl-region data)","l");
  leg_sig->SetBorderSize(0);

  xframe_sig->Draw();
  leg_sig->Draw();
  
  TImage *img_sig = TImage::Create();
  string sig_name = plt_dir + "/" + process + "_sigfit";
  if(!isLog) sig_name += "_linear";
  if(isSherpa) sig_name += "_sherpa";
  string sig_pdf = sig_name + ".pdf";
  c2->SaveAs(sig_pdf.c_str());

  //end plot

  x.setRange("my_range",76,106);
  RooAbsReal *i = mj_sregion.createIntegral(x,RooFit::NormSet(x),RooFit::Range("my_range"));

  cout << "integral value: " << i->getVal() << endl;
  cout << alpha << endl;

}

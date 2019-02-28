//modified version of roofit_template.C, that can iterate over 2D (variable) vs mv1c weight histograms and fit bins, for differential cross-sections
//assumes hadron-matching

#ifndef __CINT__
#include "RooGlobalFunc.h"
#endif

#include "AtlasStyle.C"
#include "AtlasLabels.C"
#include "AtlasUtils.h"
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooDataHist.h"
#include "RooHistPdf.h"
#include "RooAddPdf.h"
#include "RooPlot.h"
#include "RooChi2Var.h"
#include "RooFitResult.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TMath.h"
#include "TPad.h"
#include "TLatex.h"
#include "THStack.h"
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <string>
#include "TFile.h"
#include "TString.h"
#include "TH1.h"
#include "TH2.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TImage.h"
#include <ctime>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "THStack.h"
#include "TSystem.h"
#include "TFractionFitter.h"
#include "TRandom3.h"
#include "TPaveText.h"
#include "TF1.h"
#include "RooMsgService.h"

bool isPrefit = false;
bool isSherpa= false;
bool isStack = true;
bool isLeadJet = true;
bool isClosure = false;
bool isTFF = false;
bool isTrueZ = false;
bool isVaried = true;
bool isOneBin = false;
bool isErrorTesting = false;
TRandom3 *r =new TRandom3(0);


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
  }
}

string NumToStr(int number_val){
  ostringstream ss;
  ss << number_val;
  return ss.str();
}

string NumToStr(double number_val){
  ostringstream ss;
  ss.precision(3);
  ss << number_val;
  return ss.str();
}

void AddSuffixes(string & starting_name){
  if(isLeadJet) starting_name += "_leadjet";
  if(isPrefit) starting_name += "_prefit";
  if(isClosure) starting_name += "_closure";
  if(isTrueZ) starting_name += "_trueZ";
  if(isTFF) starting_name += "_TFF";
  if(isSherpa) starting_name += "_sherpa";
  if(isVaried) starting_name += "_variation_asym";
  if(isOneBin) starting_name += "_onebin";
  if(isErrorTesting) starting_name += "_errortests";
}

vector<vector<double> > read_bjet_uncertainties(std::string csv_f_n){
  string line;
  vector<string> line_v;
  vector<vector<double> > value_v;
  ifstream csv_f(csv_f_n);
  while(getline(csv_f,line)){
    line_v.push_back(line);
  }
  for(unsigned int i=0;i<line_v.size();i++){
    std::istringstream ss(line_v[i]);
    std::string token;
    double value;
    vector<double> l_v_v;
    while(std::getline(ss, token, ',')){
      stringstream vs(token);
      vs >> value;
      l_v_v.push_back(value);
    }
    value_v.push_back(l_v_v);
  }
  return value_v;
}

vector<double> add_uncertainties(vector<vector<double> > btag_uncertainty, double jes_val,double jer_val, double jvf_val, double lumi_val){
  vector<double> uncert_v;
  for(unsigned int b=0;b<btag_uncertainty[0].size();b++){
    double quad_v = 0;
    for(unsigned int i=0;i<btag_uncertainty.size();i++){
      quad_v+=pow(btag_uncertainty[i][b],2);
    }
    quad_v+=pow(jes_val,2);
    quad_v+=pow(jer_val,2);
    quad_v+=pow(jvf_val,2);
    quad_v+=pow(lumi_val,2);
    uncert_v.push_back(sqrt(quad_v)/100.);
  }
  return uncert_v;
}

std::vector<Double_t> make_varied_hist(TH1D * h_mv1c, TH1D *h_mv1c_var, Double_t var_val){
  vector<Double_t> var_i_vec;
  for(int mv1bin_i=1; mv1bin_i<h_mv1c->GetNbinsX()+1; mv1bin_i++){
    Double_t var_i = r->Gaus(0,var_val);
    var_i_vec.push_back(var_i);
    Double_t scale_i = var_i+1;
    Double_t bin_cont=h_mv1c->GetBinContent(mv1bin_i);
    bin_cont*=scale_i;
    h_mv1c_var->SetBinContent(mv1bin_i,bin_cont);
  }

  return var_i_vec;
}


std::vector<Double_t> do_template_fit_rf(TH1D * hbottom, TH1D *hcharm, TH1D *hlight, TH1D *hdata,vector<Int_t> & fit_status){
  using namespace RooFit;

  std::vector<Double_t> params;
  params.resize(7);
  
  RooRealVar x("x","MV1c weight",0.,1.);

  RooRealVar frbottom("bjet_fraction","bottom fraction",0.,1.);
  RooRealVar frcharm("cjet_fraction","charm fraction",0.,1.);
  RooRealVar frlight("ljet_fraction","light fraction",0.,1.);

  RooDataHist data("data","dataset with x",x,Import(*hdata,kFALSE));
  RooDataHist bjetMC("bjetMC","bjetMC with x",x,Import(*hbottom,kFALSE));
  RooDataHist cjetMC("cjetMC","cjetMC with x",x,Import(*hcharm,kFALSE));
  RooDataHist ljetMC("ljetMC","ljetMC with x",x,Import(*hlight,kFALSE));

  /*  RooDataHist data("data","dataset with x",x,hdata);
  RooDataHist bjetMC("bjetMC","bjetMC with x",x,hbottom);
  RooDataHist cjetMC("cjetMC","cjetMC with x",x,hcharm);
  RooDataHist ljetMC("ljetMC","ljetMC with x",x,hlight);
  */
  RooHistPdf bjetTemplate("bjetTemplate","bjetTemplate",x,bjetMC);
  RooHistPdf cjetTemplate("cjetTemplate","cjetTemplate",x,cjetMC);
  RooHistPdf ljetTemplate("ljetTemplate","ljetTemplate",x,ljetMC);

  Double_t template_sum_b = bjetMC.sum(kTRUE);
  Double_t template_sum_c = cjetMC.sum(kTRUE);
  Double_t template_sum_l = ljetMC.sum(kTRUE);

  //  cout << "TEMPLATE SUMS: " << "b = " << template_sum_b << " c = " << template_sum_c << " l = " << template_sum_l << endl;


  RooArgList shapes;
  shapes.add(bjetTemplate);
  shapes.add(cjetTemplate);
  shapes.add(ljetTemplate);
  RooArgList norms;
  norms.add(frbottom);
  norms.add(frcharm);
  RooAddPdf template_model("model","model",shapes,norms);

  RooPlot* xframe = x.frame();

  RooFit::Minimizer("Minuit2");
  RooFitResult* r = template_model.fitTo(data,SumW2Error(kTRUE),Save(),PrintEvalErrors(-1),PrintLevel(-1),Verbose(kFALSE));
  double p_b = frbottom.getVal();
  double p_c = frcharm.getVal();
  double p_l = 1-p_b-p_c;

  double errP_b = frbottom.getError();
  double errP_c = frcharm.getError();
  double errP_l= sqrt(pow(errP_b,2) + pow(errP_c,2));
  xframe->SetMaximum(2000);
  xframe->SetMinimum(0);

  data.plotOn(xframe,Name("data"));
  template_model.plotOn(xframe,Name("model"),LineColor(kBlue));

  template_model.paramOn(xframe,Parameters(RooArgSet(frbottom,frcharm)));
  RooArgSet obs(x,"obs set");
  RooArgSet* flparams = template_model.getParameters(obs);
  RooChi2Var roochi2("chi2","chi2",template_model,data);
  double chi2_ndf = roochi2.getVal()/(5.-2.);
  //double chi2 = xframe->chiSquare(flparams->getSize());

  double status = r->status();
  fit_status.push_back(status);

  params[0] = p_b;
  params[1] = p_c;
  params[2] = p_l;
  params[3] = errP_b;
  params[4] = errP_c;
  params[5] = errP_l;
  params[6] = chi2_ndf;

  return params;

}

std::vector<Double_t> do_template_fit_tff(TH1D *hbottom, TH1D *hcharm, TH1D *hlight, TH1D *hdata,vector<Int_t> & fit_status){

  //Parameters: b_fraction, c_fraction, l_fraction, b_f_error, c_f_error, l_f_error, chi2_ndf
                                                                                             
  std::vector<Double_t> params;
  params.resize(7);
  
  TObjArray *mc = new TObjArray(3);
  mc->Add(hbottom);
  mc->Add(hcharm);
  mc->Add(hlight);

  TFractionFitter* fit = new TFractionFitter(hdata, mc);
  fit->Constrain(0,0.0,1.0);
  fit->Constrain(1,0.0,1.0);
  fit->Constrain(2,0.0,1.0);

  Int_t status = fit->Fit();
  fit_status.push_back(status);

  TH1F *mcp_b, *mcp_c, *mcp_l;
  Double_t p_b, p_c, p_l, errP_b, errP_c, errP_l;
  
  TH1F* result = (TH1F*) fit->GetPlot();

  double chi2 = fit->GetChisquare();
  double ndf = fit->GetNDF();
  double chi2_ndf = chi2/ndf;

  mcp_b = (TH1F*)fit->GetMCPrediction(0);
  mcp_c = (TH1F*)fit->GetMCPrediction(1);
  mcp_l = (TH1F*)fit->GetMCPrediction(2);

  fit->GetResult( 0, p_b, errP_b);
  fit->GetResult( 1, p_c, errP_c);
  fit->GetResult( 2, p_l, errP_l);

  params[0] = p_b;
  params[1] = p_c;
  params[2] = p_l;
  params[3] = errP_b;
  params[4] = errP_c;
  params[5] = errP_l;
  params[6] = chi2_ndf;


  return params;

}

std::vector<Double_t> do_random_var(TH1D * hbottom, TH1D *hcharm, TH1D *hlight, TH1D *hdata,vector<Int_t> & fit_status, int bin_n,vector<double> & b_uncert, vector<double> & c_uncert, 
				    vector<double> & l_uncert){

  TH1D *bfrac_result_check = new TH1D("bfrac_result_check","bfrac_result_check",300,0.,0.3);
  TH1D *cfrac_result_check = new TH1D("cfrac_result_check","cfrac_result_check",1000,0.,1.0);
  TH1D *lfrac_result_check = new TH1D("lfrac_result_check","lfrac_result_check",1000,0.,1.0);
  TH1D *var_val_check = new TH1D("var_val_check","var_val_check",100,-.25,0.25);

  std::vector<Double_t> param_results;

  vector<Int_t> fit_status_var;
  std::vector<Double_t> params_var;
  Double_t b_result_var;
  Double_t c_result_var;
  Double_t l_result_var;
  Double_t b_result_err_var;
  Double_t c_result_err_var;
  Double_t l_result_err_var;
  Double_t chi2_ndf_var;

  Double_t light_var = 0.05;
  Double_t charm_var = 0.10;
  Double_t bottom_var = 0.15;

  map<int,int> uncert_el;
  uncert_el.insert(pair<int,int>(0,0));
  uncert_el.insert(pair<int,int>(1,0));
  uncert_el.insert(pair<int,int>(2,0));
  uncert_el.insert(pair<int,int>(3,0));
  uncert_el.insert(pair<int,int>(4,1));
  uncert_el.insert(pair<int,int>(5,1));
  uncert_el.insert(pair<int,int>(6,2));
  uncert_el.insert(pair<int,int>(7,2));
  uncert_el.insert(pair<int,int>(8,3));
  uncert_el.insert(pair<int,int>(9,3));
  uncert_el.insert(pair<int,int>(10,4));
  uncert_el.insert(pair<int,int>(11,4));
  uncert_el.insert(pair<int,int>(12,5));
  uncert_el.insert(pair<int,int>(13,5));
  uncert_el.insert(pair<int,int>(14,6));
  uncert_el.insert(pair<int,int>(15,6));
  uncert_el.insert(pair<int,int>(16,7));
  uncert_el.insert(pair<int,int>(17,8));
  uncert_el.insert(pair<int,int>(18,9));
  uncert_el.insert(pair<int,int>(19,10));
  uncert_el.insert(pair<int,int>(20,11));
  
  int uncert_i = uncert_el[bin_n];
  light_var = l_uncert[uncert_i];
  charm_var = c_uncert[uncert_i];
  bottom_var = b_uncert[uncert_i];

  Int_t n_var = 100;
  Int_t var_i = 0;
  vector<Double_t> check_var;
  //Up variations
  TH1D *hbottom_var = (TH1D*)hbottom->Clone("bottom_var");
  TH1D *hcharm_var = (TH1D*)hcharm->Clone("charm_var");
  TH1D *hlight_var = (TH1D*)hlight->Clone("light_var");
  while(var_i < 1000){
    std::cout.clear();
    if(var_i % 100 == 0) cout << "Variation # " << var_i << ", bin # " << bin_n << endl;
    std::cout.setstate(std::ios_base::failbit);
    check_var = make_varied_hist(hbottom,hbottom_var,bottom_var);
    make_varied_hist(hcharm,hcharm_var,charm_var);
    make_varied_hist(hlight,hlight_var,light_var);

    for(unsigned int n=0;n<check_var.size();n++){
      var_val_check->Fill(check_var.at(n));
    }
    params_var = do_template_fit_rf(hbottom_var,hcharm_var,hlight_var,hdata,fit_status_var);

    b_result_var = params_var[0];
    c_result_var = params_var[1];
    l_result_var = params_var[2];
    b_result_err_var = params_var[3];
    c_result_err_var = params_var[4];
    l_result_err_var = params_var[5];
    chi2_ndf_var = params_var[6];

    bfrac_result_check->Fill(b_result_var);
    cfrac_result_check->Fill(c_result_var);
    lfrac_result_check->Fill(l_result_var);
    var_i++;
  }
  
  int fit_status_n = 0;
  for(unsigned int f=0;f<fit_status_var.size();f++){
    fit_status_n+= fit_status_var.at(f);
  }
  fit_status.push_back(fit_status_n);
  string bin_n_str = NumToStr(bin_n);
  TCanvas *ccheck = new TCanvas("ccheck","ccheck",800,800);
  bfrac_result_check->Fit("gaus");
  bfrac_result_check->GetFunction("gaus")->SetLineColor(kRed);
  bfrac_result_check->Draw();
  double bfrac_rms = bfrac_result_check->GetRMS();
  double bfrac_mean = bfrac_result_check->GetFunction("gaus")->GetParameter(1);
  double bfrac_sigma = bfrac_result_check->GetFunction("gaus")->GetParameter(2);
  double bchi2 = bfrac_result_check->GetFunction("gaus")->GetChisquare();
  double bndf = bfrac_result_check->GetFunction("gaus")->GetNDF();
  double bchi2ndf = bchi2/bndf;
  param_results.push_back(bfrac_sigma);

  string bfrac_rms_s = NumToStr(bfrac_rms);
  string bfrac_mean_s = NumToStr(bfrac_mean);
  string bfrac_sigma_s = NumToStr(bfrac_sigma);
  
  TPaveText *b_gaus_labels = new TPaveText(.8,.8,1,1,"brNDC");
  b_gaus_labels->SetShadowColor(0);
  b_gaus_labels->SetFillColor(0);

  b_gaus_labels->AddText(("RMS = " + bfrac_rms_s).c_str());
  b_gaus_labels->AddText(("Fit mean = " + bfrac_mean_s).c_str());
  b_gaus_labels->AddText(("Fit sigma = " + bfrac_sigma_s).c_str());
  b_gaus_labels->AddText(("Fit chi2/ndf = " + NumToStr(bchi2) + "/" + NumToStr(bndf) + " = " + NumToStr(bchi2ndf)).c_str());
  b_gaus_labels->Draw();

  string bfrac_check_fname = "bfrac_variation/bfrac_check_rms" + bin_n_str + "_var.pdf";
  ccheck->SaveAs(bfrac_check_fname.c_str());
  ccheck->Close();

  /*  TCanvas *ccheck1 = new TCanvas("ccheck1","ccheck1",800,800);
  var_val_check->Draw();
  string var_check_fname = "bfrac_variation/var_check" + bin_n_str+".pdf";
  ccheck1->SaveAs(var_check_fname.c_str());
  ccheck1->Close();*/

  TCanvas *c_charm = new TCanvas("c_charm","c_charm",800,800);
  cfrac_result_check->Fit("gaus");
  cfrac_result_check->GetFunction("gaus")->SetLineColor(kRed);
  cfrac_result_check->Draw();
  double cfrac_rms = cfrac_result_check->GetRMS();
  double cfrac_mean = cfrac_result_check->GetFunction("gaus")->GetParameter(1);
  double cfrac_sigma = cfrac_result_check->GetFunction("gaus")->GetParameter(2);
  double cchi2 =cfrac_result_check->GetFunction("gaus")->GetChisquare();
  double cndf = cfrac_result_check->GetFunction("gaus")->GetNDF();
  double cchi2ndf = cchi2/bndf;
  string cfrac_rms_s = NumToStr(cfrac_rms);
  string cfrac_mean_s = NumToStr(cfrac_mean);
  string cfrac_sigma_s = NumToStr(cfrac_sigma);
  param_results.push_back(cfrac_sigma);
  TPaveText *c_gaus_labels = new TPaveText(.8,.8,1,1,"brNDC");
  c_gaus_labels->SetShadowColor(0);
  c_gaus_labels->SetFillColor(0);
  c_gaus_labels->AddText(("RMS = " + cfrac_rms_s).c_str());
  c_gaus_labels->AddText(("Fit mean = " + cfrac_mean_s).c_str());
  c_gaus_labels->AddText(("Fit sigma = " + cfrac_sigma_s).c_str());
  c_gaus_labels->AddText(("Fit chi2/ndf = " + NumToStr(cchi2) + "/" + NumToStr(cndf) + " = " + NumToStr(cchi2ndf)).c_str());
  c_gaus_labels->Draw();
  string cfrac_check_fname = "bfrac_variation/cfrac_check_rms" + bin_n_str + "_var.pdf";
  c_charm->SaveAs(cfrac_check_fname.c_str());
  c_charm->Close();
  
  TCanvas *c_light = new TCanvas("c_light","c_light",800,800);
  lfrac_result_check->Fit("gaus");
  lfrac_result_check->GetFunction("gaus")->SetLineColor(kRed);
  lfrac_result_check->Draw();
  double lfrac_rms = lfrac_result_check->GetRMS();
  double lfrac_mean = lfrac_result_check->GetFunction("gaus")->GetParameter(1);
  double lfrac_sigma = lfrac_result_check->GetFunction("gaus")->GetParameter(2);
  double lchi2 =lfrac_result_check->GetFunction("gaus")->GetChisquare();
  double lndf = lfrac_result_check->GetFunction("gaus")->GetNDF();
  double lchi2ndf = lchi2/bndf;
  string lfrac_rms_s = NumToStr(lfrac_result_check->GetRMS());
  string lfrac_mean_s = NumToStr(lfrac_result_check->GetFunction("gaus")->GetParameter(1));
  string lfrac_sigma_s = NumToStr(lfrac_result_check->GetFunction("gaus")->GetParameter(2));
  param_results.push_back(lfrac_sigma);
  TPaveText *l_gaus_labels = new TPaveText(.8,.85,1,1,"brNDC");
  l_gaus_labels->SetShadowColor(0);
  l_gaus_labels->SetFillColor(0);
  l_gaus_labels->AddText(("RMS = " + lfrac_rms_s).c_str());
  l_gaus_labels->AddText(("Fit mean = " + lfrac_mean_s).c_str());
  l_gaus_labels->AddText(("Fit sigma = " + lfrac_sigma_s).c_str());
  l_gaus_labels->AddText(("Fit chi2/ndf = " + NumToStr(lchi2) + "/" + NumToStr(lndf) + " = " + NumToStr(lchi2ndf)).c_str());
  l_gaus_labels->Draw();
  string lfrac_check_fname = "bfrac_variation/lfrac_check_rms" + bin_n_str + "_var.pdf";
  c_light->SaveAs(lfrac_check_fname.c_str());
  c_light->Close();

  delete bfrac_result_check;
  delete cfrac_result_check;
  delete lfrac_result_check;
  delete var_val_check;

  delete hbottom_var;
  delete hcharm_var;
  delete hlight_var;

  delete b_gaus_labels;
  delete c_gaus_labels;
  delete l_gaus_labels;

  delete ccheck;
  delete c_charm;
  delete c_light;

  return param_results;
}

void iterate_bins(){
 


}


void template_fitter(string kin_variable = "Z_pt"){
  using namespace RooFit;

  RooMsgService::instance().setGlobalKillBelow(RooFit::ERROR);

  std::cout.setstate(std::ios_base::failbit);

  string hist_dir = "/n/atlas02/user_codes/looper.6/Vbb/analysis_code/MC_histograms_root/";
  string light_f = hist_dir + kin_variable + "mv1c_light_jets_hmatch.root";
  string charm_f = hist_dir + kin_variable + "mv1c_charm_jets_hmatch.root";
  string bottom_f = hist_dir + kin_variable + "mv1c_bottom_jets_hmatch.root";
  string hist_name_l = kin_variable + "mv1c_light_jets_hmatch";
  string hist_name_c = kin_variable + "mv1c_charm_jets_hmatch";
  string hist_name_b = kin_variable + "mv1c_bottom_jets_hmatch";

  if(isLeadJet){
     hist_dir = "/n/atlas02/user_codes/looper.6/Vbb/analysis_code/MC_histograms_root/";
     light_f = hist_dir + kin_variable + "mv1c_light_jets_hmatch_leadjet.root";
     charm_f = hist_dir + kin_variable + "mv1c_charm_jets_hmatch_leadjet.root";
     bottom_f = hist_dir + kin_variable + "mv1c_bottom_jets_hmatch_leadjet.root";
     hist_name_l = kin_variable + "mv1c_light_jets_hmatch_leadjet";
     hist_name_c = kin_variable + "mv1c_charm_jets_hmatch_leadjet";
     hist_name_b = kin_variable + "mv1c_bottom_jets_hmatch_leadjet";
  }
  if(isTrueZ){
    hist_dir = "/n/atlas02/user_codes/looper.6/Vbb/analysis_code/MC_histograms_root/";
    light_f = hist_dir + kin_variable + "mv1c_light_jets_hmatch_leadjet_trueZ.root";
    charm_f = hist_dir + kin_variable + "mv1c_charm_jets_hmatch_leadjet_trueZ.root";
    bottom_f = hist_dir + kin_variable + "mv1c_bottom_jets_hmatch_leadjet_trueZ.root";
    hist_name_l = kin_variable + "mv1c_light_jets_hmatch_leadjet_trueZ";
    hist_name_c = kin_variable + "mv1c_charm_jets_hmatch_leadjet_trueZ";
    hist_name_b = kin_variable + "mv1c_bottom_jets_hmatch_leadjet_trueZ";
  }

  string histlabel = "_mc";
  if(isSherpa) histlabel = "_sherpa";

  hist_name_l += histlabel;
  hist_name_c += histlabel;
  hist_name_b += histlabel;

  string data_f = "/n/atlas02/user_codes/looper.6/Vbb/analysis_code/data_histograms/alldata.root";
  if(isClosure && !isTrueZ) data_f = "/n/atlas02/user_codes/looper.6/Vbb/analysis_code/MC_histograms_root/Z_ptmv1c_leadjet.root";
  else if(isClosure && isTrueZ) data_f = "/n/atlas02/user_codes/looper.6/Vbb/analysis_code/MC_histograms_root/Z_ptmv1c_leadjet_trueZ.root";
  else data_f = "/n/atlas02/user_codes/looper.6/Vbb/analysis_code/data_histograms/alldata.root";

  string data_hist_name;
  if(isClosure&&!isTrueZ){
    data_hist_name = "Z_ptmv1c_leadjet" + histlabel;
  }
  else if(isTrueZ){
    data_hist_name = "Z_ptmv1c_leadjet_trueZ" + histlabel;
  }
  else data_hist_name = "mv1cweight_ptbinned_leadjet";

  TFile *flight = TFile::Open(light_f.c_str(),"READ");
  TFile *fcharm = TFile::Open(charm_f.c_str(),"READ");
  TFile *fbottom = TFile::Open(bottom_f.c_str(),"READ");

  TFile *f_data = TFile::Open(data_f.c_str(),"READ");

  TH2D *hlight_2D = (TH2D*)flight->Get(hist_name_l.c_str());
  TH2D *hcharm_2D = (TH2D*)fcharm->Get(hist_name_c.c_str());
  TH2D *hbottom_2D = (TH2D*)fbottom->Get(hist_name_b.c_str());

  TH2D *hdata_2D = (TH2D*)f_data->Get(data_hist_name.c_str());

  
  //make histogram that holds flavor fractions for each kinematic variable (Z pT) bin
  TAxis *y_axis_kinvar = hdata_2D->GetYaxis();

  TH1D *h_bfrac;
  TH1D *h_cfrac;
  TH1D *h_lfrac;

  int nYbins = hdata_2D->GetNbinsY();
  const Double_t *varbin_array = y_axis_kinvar->GetXbins()->GetArray();
  
  bool isVarBinned = true;

  if(y_axis_kinvar->GetXbins()->GetSize() == 0){
    isVarBinned = false;

    double y_min_kinvar = y_axis_kinvar->GetXmin();
    double y_max_kinvar = y_axis_kinvar->GetXmax();
    double n_bins_kinvar = y_axis_kinvar->GetNbins();
    
    h_bfrac = new TH1D(("bfrac_"+kin_variable).c_str(), (kin_variable + " b fraction").c_str(),n_bins_kinvar,y_min_kinvar,y_max_kinvar);
    h_cfrac = new TH1D(("cfrac_"+kin_variable).c_str(), (kin_variable + " c fraction").c_str(),n_bins_kinvar,y_min_kinvar,y_max_kinvar);
    h_lfrac = new TH1D(("lfrac_"+kin_variable).c_str(), (kin_variable + " lfraction").c_str(),n_bins_kinvar,y_min_kinvar,y_max_kinvar);
    /*
    h_bfrac = new TH2D(("bfrac_"+kin_variable).c_str(), (kin_variable + " b fraction").c_str(),1,0,1,n_bins_kinvar,y_min_kinvar,y_max_kinvar);
    h_cfrac = new TH2D(("cfrac_"+kin_variable).c_str(), (kin_variable + " c fraction").c_str(),1,0,1,n_bins_kinvar,y_min_kinvar,y_max_kinvar);
    h_lfrac = new TH2D(("lfrac_"+kin_variable).c_str(), (kin_variable + " lfraction").c_str(),1,0,1,n_bins_kinvar,y_min_kinvar,y_max_kinvar);*/
  }
  else{
    h_bfrac = new TH1D(("bfrac_"+kin_variable).c_str(), (kin_variable + " b fraction").c_str(),nYbins,varbin_array);
    h_cfrac = new TH1D(("cfrac_"+kin_variable).c_str(), (kin_variable + " c fraction").c_str(),nYbins,varbin_array);
    h_lfrac = new TH1D(("lfrac_"+kin_variable).c_str(), (kin_variable + " lfraction").c_str(),nYbins,varbin_array);
    /*
    h_bfrac = new TH2D(("bfrac_"+kin_variable).c_str(), (kin_variable + " b fraction").c_str(),1,0,1,nXbins,varbin_array);
    h_cfrac = new TH2D(("cfrac_"+kin_variable).c_str(), (kin_variable + " c fraction").c_str(),1,0,1,nXbins,varbin_array);
    h_lfrac = new TH2D(("lfrac_"+kin_variable).c_str(), (kin_variable + " lfraction").c_str(),1,0,1,nXbins,varbin_array);*/
  }

  //Default values -- dynamically changed in fitting loop
  double y_min = 10.;
  double y_max = 1500000;

  vector<Int_t> fit_status;

  vector<Double_t> bin_center_vec;
  vector<Double_t> b_frac_vec;
  vector<Double_t> err_up_vec;
  vector<Double_t> err_down_vec;
  vector<Double_t> err_x_vec;

  vector<Double_t> b_frac_dif_vec;
  vector<Double_t> err_up_dif_vec;
  vector<Double_t> err_down_dif_vec;

  string plt_path = "/n/atlas02/user_codes/looper.6/Vbb/analysis_plots/";
  string plt_dir;
  create_dir(plt_path,plt_dir);

  //output b-fraction crosschecks to .csv
  string fname_csv = "bfractions_and_difs";
  AddSuffixes(fname_csv);
  fname_csv += ".csv";

  ofstream f_csv;
  f_csv.open(fname_csv.c_str()); 
  f_csv << "Bin low edge,Bin high edge,b result,b error,template b frac,template b err,difference,difference err,N events\n";

  //create .csv of results
  string fname_results = "results";
  AddSuffixes(fname_results);
  fname_results += ".csv";

  ofstream f_results;
  f_results.open(fname_results.c_str());
  f_results << "binlow,binhigh,bfraction,berr,cfraction,cerr,lfraction,lerr,chi2,Ndata\n";

  vector<vector<double> > btag_uncertainty_b = read_bjet_uncertainties("uncertainty_block_b.csv");
  vector<vector<double> > btag_uncertainty_c = read_bjet_uncertainties("uncertainty_block_c.csv");
  vector<vector<double> > btag_uncertainty_l = read_bjet_uncertainties("uncertainty_block_l.csv");

  double jes_val = 4.8;
  double jer_val = 2.4;
  double jvf_val = 1.0;
  double lumi_val = 1.9;
  
  vector<double> b_uncertainties = add_uncertainties(btag_uncertainty_b, jes_val, jer_val, jvf_val, lumi_val);
  vector<double> c_uncertainties = add_uncertainties(btag_uncertainty_c, jes_val, jer_val, jvf_val, lumi_val);
  vector<double> l_uncertainties = add_uncertainties(btag_uncertainty_l, jes_val, jer_val, jvf_val, lumi_val);

  //begin loop over kinematic variable
  int n_kinbins = hdata_2D->GetNbinsY();
  for(int bin_i = 1; bin_i < n_kinbins+1; bin_i++){
  //  for(int bin_i=3;bin_i<4;bin_i++){
    bool hasEmptyBin = false;
    std::cout.clear();
    cout << "BEGIN LOOP " << bin_i << " OF " << n_kinbins << endl;
    cout << "###############################################" << endl;
    std::cout.setstate(std::ios_base::failbit);
    TH1D *hlight = hlight_2D->ProjectionX("light_px", bin_i, bin_i);
    TH1D *hcharm = hcharm_2D->ProjectionX("charm_px", bin_i, bin_i);
    TH1D *hbottom = hbottom_2D->ProjectionX("bottom_px", bin_i, bin_i);
    TH1D *hdata = hdata_2D->ProjectionX("data_px", bin_i, bin_i);


    //Dynamic y-axis adjustment
    y_min = (hdata->GetMinimum()) * 0.1;
    y_max = (hdata->GetMaximum()) * 15.;


    Int_t Nlight = hlight->Integral();
    Int_t Ncharm = hcharm->Integral();
    Int_t Nbottom = hbottom->Integral();
    Int_t Ndata = hdata->Integral();

    if(Ndata == 0){
      cout << "EMPTY DATA HISTOGRAM, SKIP!" << endl;
      h_bfrac->SetBinContent(bin_i,0);
      continue;
    }
    for(int k = 1; k < hdata->GetNbinsX()+1; k++){
      double bin_value = hdata->GetBinContent(k);
      if(bin_value == 0) hasEmptyBin = true;
    }

    //create false data histogram that is a weighted sum of the template histograms
    if(isClosure){
      hdata->Reset("ICESM");
      hdata->GetSumw2()->Set(0);
      hdata->Sumw2();
      TH1D *l_clone = (TH1D*)hlight->Clone();
      TH1D *c_clone = (TH1D*)hcharm->Clone();
      TH1D *b_clone = (TH1D*)hbottom->Clone();
      
      Double_t scale_l = 1/l_clone->Integral();
      Double_t scale_c = 1/c_clone->Integral();
      Double_t scale_b = 1/b_clone->Integral();

      l_clone->Scale(scale_l);
      c_clone->Scale(scale_c);
      b_clone->Scale(scale_b);
      
      Double_t lweight = .82;
      Double_t cweight = .15;
      Double_t bweight = .03;

      hdata->Add(l_clone,lweight);
      hdata->Add(c_clone,cweight);
      hdata->Add(b_clone,bweight);

      cout << "DEBUG ADDITION: " << hdata->Integral() << endl;

      hdata->Scale(Ndata/hdata->Integral());

    }

    std::vector<Double_t> parameters;
    std::vector<Double_t> var_parameters;
    
    if(isErrorTesting){
      for(int k = 1; k < hdata->GetNbinsX()+1; k++){
	double bin_error = 100;
	hdata->SetBinError(k,bin_error);
	hbottom->SetBinError(k,bin_error);
	hcharm->SetBinError(k,bin_error);
	hlight->SetBinError(k,bin_error);
      }
      }

    if(isTFF)parameters = do_template_fit_tff(hbottom,hcharm,hlight,hdata,fit_status);
    else parameters = do_template_fit_rf(hbottom,hcharm,hlight,hdata,fit_status);
    
    //BIN VARIATION
    if(isVaried) var_parameters = do_random_var(hbottom,hcharm,hlight,hdata,fit_status,bin_i,b_uncertainties,c_uncertainties,l_uncertainties);

    Double_t b_result = parameters[0];
    Double_t c_result = parameters[1];
    Double_t l_result = parameters[2];
    Double_t b_result_err = parameters[3];
    Double_t c_result_err = parameters[4];
    Double_t l_result_err = parameters[5];
    Double_t chi2_ndf = parameters[6];

    if(isVaried){
      b_result_err = sqrt(var_parameters[0]*var_parameters[0] + parameters[3]*parameters[3]);
      c_result_err = sqrt(var_parameters[1]*var_parameters[1] + parameters[4]*parameters[4]);
      l_result_err = sqrt(var_parameters[2]*var_parameters[2] + parameters[5]*parameters[5]);
    }


    TCanvas *c1 = new TCanvas("c1","c1",1200,800);

    h_bfrac->SetBinContent(bin_i,b_result);
    h_cfrac->SetBinContent(bin_i,c_result);
    h_lfrac->SetBinContent(bin_i,l_result);
    h_bfrac->SetBinError(bin_i,b_result_err);
    h_cfrac->SetBinError(bin_i,c_result_err);
    h_lfrac->SetBinError(bin_i,l_result_err);

    if(!isPrefit){
      hbottom->Scale(Ndata*b_result/Nbottom);
      hcharm->Scale(Ndata*c_result/Ncharm);
      hlight->Scale(Ndata*l_result/Nlight);
    }
    TH1F *final_sum = (TH1F*)hbottom->Clone();
    final_sum->Add(hcharm);
    final_sum->Add(hlight);
    
    double final_integral = final_sum->Integral();
    double b_integral = hbottom->Integral();
    double b_ratio_integral = b_integral/final_integral;
    
    hdata->SetLineColor(kBlack);
    final_sum->SetLineColor(kBlue);
    
    TLegend *leg = new TLegend(0.6,0.76,0.95,0.92);
    leg->SetTextSize(0.03);
    
    if(!hasEmptyBin) c1->SetLogy();
    
    string x_label = "MV1c weight";
    string y_label = "Events";
    string data_label = "Data (#events = " + NumToStr(Ndata) + ")";
    
    hdata->GetXaxis()->SetTitle(x_label.c_str());
    hdata->GetYaxis()->SetTitle(y_label.c_str());
    
    
    if(!isStack){
      hbottom->SetLineColor(kGreen);
      hcharm->SetLineColor(kRed);
      hlight->SetLineColor(kYellow);
      
      hbottom->SetLineStyle(kDashed);
      hcharm->SetLineStyle(kDashed);
      hlight->SetLineStyle(kDashed);
      
      hdata->Draw("p");
      final_sum->Draw("hist same");
      hbottom->Draw("hist same");
      hcharm->Draw("hist same");
      hlight->Draw("hist same");
      
      leg->AddEntry(hdata,data_label.c_str(),"lp");
      leg->AddEntry(final_sum,"fit result","l");
      leg->AddEntry(hbottom,"bottom","l");
      leg->AddEntry(hcharm,"charm","l");
      leg->AddEntry(hlight,"light","l");
      
      leg->Draw();
      
    }
    else{
      hbottom->SetFillColor(kGreen);
      hcharm->SetFillColor(kRed);
      hlight->SetFillColor(kYellow);
      
      THStack *mc_stack =  new THStack("stack","stack");
      mc_stack->Add(hlight);
      mc_stack->Add(hcharm);
      mc_stack->Add(hbottom);
      
      mc_stack->SetMinimum(y_min);
      mc_stack->SetMaximum(y_max);
      
      mc_stack->Draw("hist");
      hdata->Draw("p e same");
      
      mc_stack->GetYaxis()->SetTitle("Events");
      mc_stack->GetXaxis()->SetTitle("MV1c weight");
      c1->Modified();
      
      leg->AddEntry(hdata,data_label.c_str(),"lp");
      leg->AddEntry(hbottom,"bottom","f");
      leg->AddEntry(hcharm,"charm","f");
      leg->AddEntry(hlight,"light","f");
      
      leg->Draw();
      
    }	

    int low_edge = varbin_array[bin_i-1];
    int high_edge = varbin_array[bin_i];

    /***********/
    //Block puts together vectors to fill the b-fraction before and after fit plot
    double del_B = sqrt(Nbottom);
    double del_CL = sqrt(Nlight) + sqrt(Ncharm);
    double B_template_fraction = (Double_t)Nbottom/(Ncharm+Nlight);
    double prefit_err = sqrt(pow(del_B/Nbottom,2) + pow(del_CL/(Ncharm+Nlight),2))*B_template_fraction;

    Double_t bin_width = high_edge-low_edge;
    Double_t bin_center = low_edge + bin_width/2;

    bin_center_vec.push_back(bin_center);
    if(!isPrefit){
      b_frac_vec.push_back(b_result);
      err_up_vec.push_back(b_result_err);
      if(b_result - b_result_err < 0){
	err_down_vec.push_back(b_result);
      }
      else err_down_vec.push_back(b_result_err);
    }
    else{
      b_frac_vec.push_back(B_template_fraction);
      err_up_vec.push_back(prefit_err);
      if(B_template_fraction - prefit_err < 0){
	err_down_vec.push_back(B_template_fraction);
      }
      else err_down_vec.push_back(prefit_err);
    }
    err_x_vec.push_back(bin_width/2);

    Double_t b_frac_dif = B_template_fraction - b_result;
    Double_t b_err_dif = sqrt(pow(b_result_err,2) + pow(prefit_err,2));
    b_frac_dif_vec.push_back(b_frac_dif);
    err_up_dif_vec.push_back(b_err_dif);
    err_down_dif_vec.push_back(b_err_dif);

    f_csv << NumToStr(low_edge) << "," << NumToStr(high_edge) << "," << NumToStr(b_result) << "," << NumToStr(b_result_err) << "," << NumToStr(B_template_fraction) << "," << NumToStr(prefit_err) << "," << NumToStr(b_frac_dif) << "," << NumToStr(b_err_dif) << "," << NumToStr(Ndata) << "\n";
    
    f_results << NumToStr(low_edge) << "," << NumToStr(high_edge) << "," << NumToStr(b_result) << "," << NumToStr(b_result_err) << "," << NumToStr(c_result) << "," << NumToStr(c_result_err) << "," << NumToStr(l_result) << "," << NumToStr(l_result_err) << "," << NumToStr(chi2_ndf) << "," << NumToStr(Ndata) << "\n";


    //end block

    string img_name = plt_dir + "/" + "template_" + NumToStr(low_edge) + "to"+ NumToStr(high_edge);
    AddSuffixes(img_name);
    img_name += ".pdf";
    c1->SaveAs(img_name.c_str());
    c1->Close();
  }
  //end bin loop
  f_csv.close();
  f_results.close();

  string f_frac_fname = "flavor_fractions/ffrac.root";
  TFile *f_ffrac = TFile::Open(f_frac_fname.c_str(),"RECREATE");
  h_bfrac->Write();
  h_cfrac->Write();
  h_lfrac->Write();

  TCanvas c2 = TCanvas();
  Double_t x_axis_min = 0;
  Double_t y_axis_min = -0.005;
  Double_t x_axis_max = 800;
  Double_t y_axis_max = 0.1;
  if(isSherpa) y_axis_max = 0.3;

  TH1F *frame = c2.DrawFrame(x_axis_min,y_axis_min,x_axis_max,y_axis_max);
  TGraphAsymmErrors *gr = new TGraphAsymmErrors(bin_center_vec.size(),&bin_center_vec[0],&b_frac_vec[0],&err_x_vec[0],&err_x_vec[0],&err_down_vec[0],&err_up_vec[0]);
  if(isErrorTesting){
    std::cout.clear();
    for(unsigned int j=0;j<err_down_vec.size();j++){
      cout << "Error on b-frac, up = " << err_up_vec[j] << ", down = " << err_down_vec[j] << endl;
    }
  }
  gr->SetMarkerStyle(21);
  gr->Draw("p");
  frame->GetXaxis()->SetTitle("Z p_{T} [GeV]");
  frame->GetYaxis()->SetTitle("b-jet fraction");
  string bfrac_plot_n = plt_dir +"/bfraction_asymerr";
  AddSuffixes(bfrac_plot_n);
  bfrac_plot_n += ".pdf";
  c2.Update();
  c2.SaveAs(bfrac_plot_n.c_str());


  TCanvas c3 = TCanvas();
  Double_t x_axis_min_dif = 0;
  Double_t y_axis_min_dif = -0.25;
  Double_t x_axis_max_dif = 800;
  Double_t y_axis_max_dif = 0.25;

  TH1F *frame_dif = c3.DrawFrame(x_axis_min_dif,y_axis_min_dif,x_axis_max_dif,y_axis_max_dif);
  TGraphAsymmErrors *gr_dif = new TGraphAsymmErrors(bin_center_vec.size(),&bin_center_vec[0],&b_frac_dif_vec[0],&err_x_vec[0],&err_x_vec[0],&err_down_dif_vec[0],&err_up_dif_vec[0]);
  gr_dif->SetMarkerStyle(21);
  gr_dif->Draw("p");
  frame_dif->GetXaxis()->SetTitle("Z p_{T} [GeV]");
  frame_dif->GetYaxis()->SetTitle("Prefit minus postfit b-fraction");
  string bfrac_plot_n_dif = plt_dir +"/bfraction_asymerr_dif";
  AddSuffixes(bfrac_plot_n_dif);
  bfrac_plot_n_dif += ".pdf";
  c3.Update();
  c3.SaveAs(bfrac_plot_n_dif.c_str());
				 
    
  for(unsigned int i=0; i<fit_status.size(); i++){
    if(fit_status.at(i) != 0) cout << "FIT #" << i << " DID NOT CONVERGE" << endl;
  }
}

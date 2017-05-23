#include "AtlasStyle.C"
#include "AtlasLabels.C"
#include "AtlasUtils.h"

void roofit_template(){
  using namespace RooFit;
  gROOT->LoadMacro("AtlasUtils.C");
  gROOT->LoadMacro("AtlasLabels.C");

  bool isHadMatch = true;
  //bottom_jets_hmatch.root

  string hist_name = "zmumu_sum";
  string hist_dir = "/n/atlas02/user_codes/looper.6/Vbb/analysis_code/MC_histograms_root/";
  string light_f = hist_dir + "light_jets";
  string charm_f = hist_dir + "charm_jets";
  string bottom_f = hist_dir + "bottom_jets";

  if(isHadMatch){
    light_f += "_hmatch.root";
    charm_f += "_hmatch.root";
    bottom_f += "_hmatch.root";
  }
  else{
    light_f += ".root";
    charm_f += ".root";
    bottom_f += ".root";
  }

  string data_f = "/n/atlas02/user_codes/looper.6/Vbb/analysis_code/data_histograms/alldata.root";
  string data_hist_name = "mv1cweight_binned";

  TFile *flight = TFile::Open(light_f.c_str(),"READ");
  TFile *fcharm = TFile::Open(charm_f.c_str(),"READ");
  TFile *fbottom = TFile::Open(bottom_f.c_str(),"READ");

  TFile *f_data = TFile::Open(data_f.c_str(),"READ");

  TH1D *hlight = (TH1D*)flight->Get(hist_name.c_str());
  TH1D *hcharm = (TH1D*)fcharm->Get(hist_name.c_str());
  TH1D *hbottom = (TH1D*)fbottom->Get(hist_name.c_str());
  TH1D *hdata = (TH1D*)f_data->Get(data_hist_name.c_str());


  Int_t Ndata = hdata->Integral();
  Int_t Nlight = hlight->Integral();
  Int_t Ncharm = hcharm->Integral();
  Int_t Nbottom = hbottom->Integral();

  RooRealVar x("x","x",-20,20);
  //  RooRealVar fsig("fsig","signal fraction",0.,1.);
  RooRealVar frbottom("frbottom","bottom fraction",0.,1.);
  RooRealVar frcharm("frcharm","charm fraction",0.,1.);

  RooDataHist data("data","dataset with x",x,hdata);
  RooDataHist bjetMC("bjetMC","bjetMC with x",x,hbottom);
  RooDataHist cjetMC("cjetMC","cjetMC with x",x,hcharm);
  RooDataHist ljetMC("ljetMC","ljetMC with x",x,hlight);

  RooHistPdf bjetTemplate("bjetTemplate","bjetTemplate",x,bjetMC);
  RooHistPdf cjetTemplate("cjetTemplate","cjetTemplate",x,cjetMC);
  RooHistPdf ljetTemplate("ljetTemplate","ljetTemplate",x,ljetMC);

  cout << "test" << endl;

  RooAddPdf template_model("model","model",RooArgList(bjetTemplate,cjetTemplate,ljetTemplate),RooArgList(frbottom,frcharm));

  template_model.fitTo(data);

  RooPlot* xframe = x.frame();
  data.plotOn(xframe,Name("data"),DataError(RooAbsData::SumW2));
  template_model.plotOn(xframe,Name("model"));
  template_model.plotOn(xframe,Components(bjetTemplate),LineColor(kGreen),LineStyle(kDashed),Name("bjets"));
  template_model.plotOn(xframe,Components(cjetTemplate),LineColor(kRed),LineStyle(kDashed),Name("cjets"));
  template_model.plotOn(xframe,Components(ljetTemplate),LineColor(kYellow),LineStyle(kDashed),Name("ljets"));
  template_model.paramOn(xframe);
  xframe->Draw();

  THStack *sum_stack = new THStack("stack","stack");





}

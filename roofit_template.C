#include "AtlasStyle.C"
#include "AtlasLabels.C"
#include "AtlasUtils.h"


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


void roofit_template(bool isPrefit = true, bool isSherpa=false){
  using namespace RooFit;

  bool isHadMatch = true;
  bool isStack = true;

  string hist_dir = "/n/atlas02/user_codes/looper.6/Vbb/analysis_code/MC_histograms_root/";
  string light_f = hist_dir + "light_jets";
  string charm_f = hist_dir + "charm_jets";
  string bottom_f = hist_dir + "bottom_jets";
  string hist_name_l = "light_jets";
  string hist_name_c = "charm_jets";
  string hist_name_b = "bottom_jets";

  string histlabel = "_mc";
  if(isSherpa) histlabel = "_sherpa";
  string hist_label_had = "_hmatch_leadjet" + histlabel;

  if(isHadMatch){
    light_f += "_hmatch_leadjet.root";
    charm_f += "_hmatch_leadjet.root";
    bottom_f += "_hmatch_leadjet.root";
    hist_name_l += hist_label_had;
    hist_name_c += hist_label_had;
    hist_name_b += hist_label_had;
  }
  else{
    light_f += ".root";
    charm_f += ".root";
    bottom_f += ".root";
    hist_name_l += histlabel;
    hist_name_c += histlabel;
    hist_name_b += histlabel;
  }

  string data_f = "/n/atlas02/user_codes/looper.6/Vbb/analysis_code/data_histograms/alldata.root";
  string data_hist_name = "mv1cweight_binned_leadjet";

  TFile *flight = TFile::Open(light_f.c_str(),"READ");
  TFile *fcharm = TFile::Open(charm_f.c_str(),"READ");
  TFile *fbottom = TFile::Open(bottom_f.c_str(),"READ");

  TFile *f_data = TFile::Open(data_f.c_str(),"READ");

  TH1D *hlight = (TH1D*)flight->Get(hist_name_l.c_str());
  TH1D *hcharm = (TH1D*)fcharm->Get(hist_name_c.c_str());
  TH1D *hbottom = (TH1D*)fbottom->Get(hist_name_b.c_str());
  TH1D *hdata = (TH1D*)f_data->Get(data_hist_name.c_str());


  Int_t Nlight = hlight->Integral();
  Int_t Ncharm = hcharm->Integral();
  Int_t Nbottom = hbottom->Integral();
  Int_t Ndata = hdata->Integral();

  RooRealVar x("x","MV1c weight",0.,1.);
  
  RooRealVar frbottom("bjet_fraction","bottom fraction",0.,1.);
  RooRealVar frcharm("cjet_fraction","charm fraction",0.,1.);
  RooRealVar frlight("ljet_fraction","light fraction",0.,1.);

  RooDataHist data("data","dataset with x",x,hdata);
  RooDataHist bjetMC("bjetMC","bjetMC with x",x,hbottom);
  RooDataHist cjetMC("cjetMC","cjetMC with x",x,hcharm);
  RooDataHist ljetMC("ljetMC","ljetMC with x",x,hlight);

  RooHistPdf bjetTemplate("bjetTemplate","bjetTemplate",x,bjetMC);
  RooHistPdf cjetTemplate("cjetTemplate","cjetTemplate",x,cjetMC);
  RooHistPdf ljetTemplate("ljetTemplate","ljetTemplate",x,ljetMC);
  RooAddPdf template_model("model","model",RooArgList(bjetTemplate,cjetTemplate,ljetTemplate),RooArgList(frbottom,frcharm));

  RooPlot* xframe = x.frame();
  TCanvas *c1 = new TCanvas("c1","c1",1200,800);

  RooFitResult *fitres = template_model.fitTo(data,Save(kTRUE));//,SumW2Error(kTRUE),PrintEvalErrors(-1));
  double b_result = frbottom.getVal();
  double c_result = frcharm.getVal();
  double l_result = 1-b_result-c_result;

  
  xframe->SetMaximum(2000);
  xframe->SetMinimum(0);
  data.plotOn(xframe,Name("data"));//, DataError(RooAbsData::SumW2));
  template_model.plotOn(xframe,Name("model"),LineColor(kBlue));
  template_model.plotOn(xframe,Components(bjetTemplate),LineColor(kGreen),LineStyle(kDashed),Name("bjets"));
  template_model.plotOn(xframe,Components(cjetTemplate),LineColor(kRed),LineStyle(kDashed),Name("cjets"));
  template_model.plotOn(xframe,Components(ljetTemplate),LineColor(kYellow),LineStyle(kDashed),Name("ljets"));

  Double_t chi2 = xframe->chiSquare(2);
  cout << "Chi2: " << chi2 << endl;  

  RooChi2Var roochi2("chi2","chi2",template_model,data);
  double chi2red = roochi2.getVal()/2.;
  
  cout << "Chi2 2, electric boogaloo: " << chi2red << endl;

  //  RooAbsPdf::paramOn(xframe, Parameters(RooArgSet(bjetTemplate,cjetTemplate)));
  //  template_model.paramOn(xframe,Parameters(RooArgSet(frbottom,frcharm)));
  cout << "frbottom: " << frbottom << endl;
  cout << "frcharm: " << frcharm << endl;
  //  xframe->getAttText()->SetTextSize(0.03);
  //xframe->getAttLine()->SetLineWidth(0);
  //xframe->getAttFill()->SetFillStyle(0);

  if(!isPrefit){
    hbottom->Scale(Ndata*b_result/Nbottom);
    hcharm->Scale(Ndata*c_result/Ncharm);
    hlight->Scale(Ndata*l_result/Nlight);
  }
  TH1F *final_sum = (TH1F*)hbottom->Clone();
  final_sum->Add(hcharm);
  final_sum->Add(hlight);

  hdata->SetLineColor(kBlack);
  final_sum->SetLineColor(kBlue);

  TLegend *leg = new TLegend(0.6,0.64,0.95,0.80);
  leg->SetTextSize(0.03);

  c1->SetLogy();

  string x_label = "MV1c weight";
  string y_label = "Events";

  hdata->GetXaxis()->SetTitle(x_label.c_str());
  hdata->GetYaxis()->SetTitle(y_label.c_str());

  /*  if(!isStack){
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

    leg->AddEntry(hdata,"Data","lp");
    leg->AddEntry(final_sum,"fit result","l");
    leg->AddEntry(hbottom,"bottom","l");
    leg->AddEntry(hcharm,"charm","l");
    leg->AddEntry(hlight,"light","l");

    leg->Draw();

  }
  else{*/
  hbottom->SetFillColor(kGreen);
  hcharm->SetFillColor(kRed);
  hlight->SetFillColor(kYellow);
  
  THStack *mc_stack =  new THStack("stack","stack");
  mc_stack->Add(hlight);
  mc_stack->Add(hcharm);
  mc_stack->Add(hbottom);
  
  mc_stack->SetMinimum(5000);
  
  mc_stack->Draw("hist");
  hdata->Draw("p same");
  
  mc_stack->GetYaxis()->SetTitle("Events");
  mc_stack->GetXaxis()->SetTitle("MV1c weight");
  c1->Modified();
  
  leg->AddEntry(hdata,"Data","lp");
  leg->AddEntry(hbottom,"bottom","f");
  leg->AddEntry(hcharm,"charm","f");
  leg->AddEntry(hlight,"light","f");
  
  leg->Draw();
  
  //  if(!isPrefit) xframe->Draw("same");
  string plt_path = "/n/atlas02/user_codes/looper.6/Vbb/analysis_plots/";
  string plt_dir;
  create_dir(plt_path,plt_dir);
  
  cout << hdata << endl;
  string img_name = plt_dir + "/" + "template_text";
  if(isPrefit) img_name += "_prefit";
  if(isSherpa) img_name += "_sherpa.pdf";
  else img_name += ".pdf";
  c1->SaveAs(img_name.c_str());

  


}

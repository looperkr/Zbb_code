//modified version of roofit_template.C, that can iterate over 2D (variable) vs mv1c weight histograms and fit bins, for differential cross-sections
//assumes hadron-matching

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

void template_fitter(string kin_variable = "Z_pt", bool isPrefit = false, bool isSherpa=false){
  using namespace RooFit;

  bool isStack = true;

  string hist_dir = "/n/atlas02/user_codes/looper.6/Vbb/analysis_code/MC_histograms_root/";
  string light_f = hist_dir + kin_variable + "mv1c_light_jets_hmatch.root";
  string charm_f = hist_dir + kin_variable + "mv1c_charm_jets_hmatch.root";
  string bottom_f = hist_dir + kin_variable + "mv1c_bottom_jets_hmatch.root";
  string hist_name_l = kin_variable + "mv1c_light_jets_hmatch";
  string hist_name_c = kin_variable + "mv1c_charm_jets_hmatch";
  string hist_name_b = kin_variable + "mv1c_bottom_jets_hmatch";


  string histlabel = "_mc";
  if(isSherpa) histlabel = "_sherpa";

  hist_name_l += histlabel;
  hist_name_c += histlabel;
  hist_name_b += histlabel;

  string data_f = "/n/atlas02/user_codes/looper.6/Vbb/analysis_code/data_histograms/alldata.root";
  
  string data_hist_name = "mv1cweight_ptbinned";

  TFile *flight = TFile::Open(light_f.c_str(),"READ");
  TFile *fcharm = TFile::Open(charm_f.c_str(),"READ");
  TFile *fbottom = TFile::Open(bottom_f.c_str(),"READ");

  TFile *f_data = TFile::Open(data_f.c_str(),"READ");

  TH2D *hlight_2D = (TH2D*)flight->Get(hist_name_l.c_str());
  TH2D *hcharm_2D = (TH2D*)fcharm->Get(hist_name_c.c_str());
  TH2D *hbottom_2D = (TH2D*)fbottom->Get(hist_name_b.c_str());

  TH2D *hdata_2D = (TH2D*)f_data->Get(data_hist_name.c_str());

  
  //make 2D histogram that holds flavor fractions for each kinematic variable (Z pT) bin
  TAxis *y_axis_kinvar = hdata_2D->GetYaxis();

  TH2D *h_bfrac;
  TH2D *h_cfrac;
  TH2D *h_lfrac;

  int nXbins = hdata_2D->GetNbinsX();
  const Double_t *varbin_array = y_axis_kinvar->GetXbins()->GetArray();

  bool isVarBinned = true;

  if(y_axis_kinvar->GetXbins()->GetSize() == 0){
    isVarBinned = false;

    double y_min_kinvar = y_axis_kinvar->GetXmin();
    double y_max_kinvar = y_axis_kinvar->GetXmax();
    double n_bins_kinvar = y_axis_kinvar->GetNbins();
    
    h_bfrac = new TH2D(("bfrac_"+kin_variable).c_str(), (kin_variable + " b fraction").c_str(),1,0,1,n_bins_kinvar,y_min_kinvar,y_max_kinvar);
    h_cfrac = new TH2D(("cfrac_"+kin_variable).c_str(), (kin_variable + " c fraction").c_str(),1,0,1,n_bins_kinvar,y_min_kinvar,y_max_kinvar);
    h_lfrac = new TH2D(("lfrac_"+kin_variable).c_str(), (kin_variable + " lfraction").c_str(),1,0,1,n_bins_kinvar,y_min_kinvar,y_max_kinvar);
  }
  else{
    h_testb = new TH2D("test","test",1,0,1,nXbins,varbin_array);
    h_bfrac = new TH2D(("bfrac_"+kin_variable).c_str(), (kin_variable + " b fraction").c_str(),1,0,1,nXbins,varbin_array);
    h_cfrac = new TH2D(("cfrac_"+kin_variable).c_str(), (kin_variable + " c fraction").c_str(),1,0,1,nXbins,varbin_array);
    h_lfrac = new TH2D(("lfrac_"+kin_variable).c_str(), (kin_variable + " lfraction").c_str(),1,0,1,nXbins,varbin_array);
  }

  //Default values -- dynamically changed in fitting loop
  double y_min = 10.;
  double y_max = 1500000;

  //output before and after bin values and errors to make sure things are sensical
  std::ofstream data_scaling("data_scaling.txt");

  vector<Int_t> fit_status;
  //begin loop over kinematic variable
  int n_kinbins = hdata_2D->GetNbinsY();
  for(int bin_i = 1; bin_i < n_kinbins+1; bin_i++){
    cout << "BEGIN LOOP " << bin_i << "OF " << n_kinbins << endl;
    cout << "###############################################" << endl;

    TH1D *hlight = hlight_2D->ProjectionX("light_px", bin_i, bin_i);
    TH1D *hcharm = hcharm_2D->ProjectionX("charm_px", bin_i, bin_i);
    TH1D *hbottom = hbottom_2D->ProjectionX("bottom_px", bin_i, bin_i);
    TH1D *hdata = hdata_2D->ProjectionX("data_px", bin_i, bin_i);

    hlight->Sumw2();
    hcharm->Sumw2();
    hbottom->Sumw2();
    //    hdata->SetBinErrorOption(TH1::kPoisson);
    //    hdata->Sumw2();

    //Dynamic y-axis adjustment
    y_min = (hdata->GetMinimum()) * 0.1;
    y_max = (hdata->GetMaximum()) * 15.;

    data_scaling << "BEGIN LOOP " << bin_i << "OF " << n_kinbins << endl;
    data_scaling  << "###############################################" << endl;
    //Temporary loop to add uncertainty to data histogram
    for(int k = 1; k < hdata->GetNbinsX()+1; k++){
      double d_bin_value = hdata->GetBinContent(k);
      double d_bin_error = hdata->GetBinError(k);
      data_scaling << "Bin " << k << ": " << "original value = " << d_bin_value << ", original error = " << d_bin_error << endl;
      hdata->SetBinContent(k,d_bin_value*0.1);
    }
    hdata->SetBinErrorOption(TH1::kPoisson);
    for(int k = 1; k < hdata->GetNbinsX()+1; k++){
      double d_bin_value = hdata->GetBinContent(k);
      double d_bin_error = hdata->GetBinError(k);
      data_scaling << "Bin " << k << ": " << "new value = " << d_bin_value << ", new error = " << d_bin_error << endl;
    }
    Int_t Nlight = hlight->Integral();
    Int_t Ncharm = hcharm->Integral();
    Int_t Nbottom = hbottom->Integral();
    Int_t Ndata = hdata->Integral();

    if(Ndata == 0){
      cout << "EMPTY DATA HISTOGRAM, SKIP!" << endl;
      continue;
    }

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
 
    RooArgList shapes;
    shapes.add(bjetTemplate);
    shapes.add(cjetTemplate);
    shapes.add(ljetTemplate);
    RooArgList norms;
    norms.add(frbottom);
    norms.add(frcharm);
    RooAddPdf template_model("model","model",shapes,norms);

    RooPlot* xframe = x.frame();
    TCanvas *c1 = new TCanvas("c1","c1",1200,800);


    RooFit::Minimizer("Minuit2");
     RooFitResult* r = template_model.fitTo(data,SumW2Error(kTRUE),Save());
    double b_result = frbottom.getVal();
    double c_result = frcharm.getVal();
    double l_result = 1-b_result-c_result;

    double b_result_err = frbottom.getError();
    double c_result_err = frcharm.getError();

    h_bfrac->SetBinContent(1,bin_i,b_result);
    h_cfrac->SetBinContent(1,bin_i,c_result);
    h_lfrac->SetBinContent(1,bin_i,l_result);

    //begin old comment
      xframe->SetMaximum(2000);
      xframe->SetMinimum(0);
 
      data.plotOn(xframe,Name("data"));
      template_model.plotOn(xframe,Name("model"),LineColor(kBlue));
 
      //end old comment
      template_model.paramOn(xframe,Parameters(RooArgSet(frbottom,frcharm)));
      RooArgSet obs(x,"obs set");
      RooArgSet* flparams = template_model.getParameters(obs);
      RooChi2Var roochi2("chi2","chi2",template_model,data);
      double chi2red = roochi2.getVal()/(5.-2.);

      double chi2 = xframe->chiSquare(flparams->getSize());

      fit_status.push_back(r->status());

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

      TLatex chi2_label;
      chi2_label.SetNDC();
      chi2_label.SetTextSize(0.03);
      TLatex bresult_label;
      TLatex cresult_label;
      bresult_label.SetNDC();
      bresult_label.SetTextSize(0.03);
      cresult_label.SetNDC();
      cresult_label.SetTextSize(0.03);

      c1->SetLogy();

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
	hdata->Draw("p same");
      
	mc_stack->GetYaxis()->SetTitle("Events");
	mc_stack->GetXaxis()->SetTitle("MV1c weight");
	c1->Modified();
      
	leg->AddEntry(hdata,data_label.c_str(),"lp");
	leg->AddEntry(hbottom,"bottom","f");
	leg->AddEntry(hcharm,"charm","f");
	leg->AddEntry(hlight,"light","f");
      
	leg->Draw();

      }	

      string chi2_label_text = "Chi2/ndf = " + NumToStr(chi2red) + " (Compare to: " + NumToStr(chi2) + ")" ;
      chi2_label.DrawLatex(0.6,0.9,chi2_label_text.c_str());
      string bfrac_text = "b fraction = " + NumToStr(b_result) + " #pm " + NumToStr(b_result_err);
      string cfrac_text = "c fraction = " + NumToStr(c_result) + " #pm " + NumToStr(c_result_err);
      bresult_label.DrawLatex(0.6,0.86,bfrac_text.c_str());
      cresult_label.DrawLatex(0.6,0.82,cfrac_text.c_str());

      string plt_path = "/n/atlas02/user_codes/looper.6/Vbb/analysis_plots/";
      string plt_dir;
      create_dir(plt_path,plt_dir);
      
      int low_edge = varbin_array[bin_i-1];
      int high_edge = varbin_array[bin_i];
      string img_name = plt_dir + "/" + "template_text" + NumToStr(low_edge) + "to"+ NumToStr(high_edge) + "_scaleddata";

      if(isPrefit) img_name += "_prefit";
      if(isSherpa) img_name += "_sherpa.pdf";
      else img_name += ".pdf";
      c1->SaveAs(img_name.c_str());

  }
   //end bin loop


  string f_frac_fname = "flavor_fractions/ffrac.root";
  TFile *f_ffrac = TFile::Open(f_frac_fname.c_str(),"RECREATE");
  h_bfrac->Write();
  h_cfrac->Write();
  h_lfrac->Write();

  for(int i=0; i<fit_status.size(); i++){
    if(fit_status.at(i) != 0) cout << "FIT #" << i << " DID NOT CONVERGE" << endl;
  }

}

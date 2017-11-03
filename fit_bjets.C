#include "AtlasStyle.C"
#include "AtlasLabels.C"
#include "AtlasUtils.h"

void fit_bjets(){

  gROOT->LoadMacro("AtlasUtils.C");
  gROOT->LoadMacro("AtlasLabels.C");

  bool isHadMatched = false;

  string hist_name = "zmumu_sum";
  string hist_dir = "/n/atlas02/user_codes/looper.6/Vbb/analysis_code/MC_histograms_root/";

  string light_f = hist_dir + "light_jets";
  string charm_f = hist_dir + "charm_jets";
  string bottom_f = hist_dir + "bottom_jets";

  if(isHadMatched){
    light_f += "_hmatch.root";
    charm_f += "_hmatch.root";
    bottom_f += "_hmatch.root";
  }
  else{
    light_f += ".root";
    charm_f += ".root";
    bottom_f+= ".root";
  }


  string data_f = "/n/atlas02/user_codes/looper.6/Vbb/analysis_code/data_histograms/alldata.root";
  string data_hist_name = "mv1cweight_binned";

  TFile *f0 = TFile::Open(light_f.c_str(),"READ");
  TFile *f1 = TFile::Open(charm_f.c_str(),"READ");
  TFile *f2 = TFile::Open(bottom_f.c_str(),"READ");

  TFile *f_data = TFile::Open(data_f.c_str(),"READ");

  TH1D *h0 = (TH1D*)f0->Get(hist_name.c_str());
  TH1D *h1 = (TH1D*)f1->Get(hist_name.c_str());
  TH1D *h2 = (TH1D*)f2->Get(hist_name.c_str());
  TH1D *data = (TH1D*)f_data->Get(data_hist_name.c_str());  


  Int_t Ndata = data->Integral();
  Int_t N0 = h0->Integral();
  Int_t N1 = h1->Integral();
  Int_t N2 = h2->Integral();
  

  TObjArray *mc = new TObjArray(3);
  mc->Add(h0);
  mc->Add(h1);
  mc->Add(h2);

  TH1D *h_sum =  (TH1D*)h0->Clone();
  h_sum->Add(h1);
  h_sum->Add(h2);

  THStack *mc_stack =  new THStack("stack","stack");
  mc_stack->Add(h0);
  mc_stack->Add(h1);
  mc_stack->Add(h2);

  h0->SetFillColor(2);
  h1->SetFillColor(3);
  h2->SetFillColor(4);

  TFractionFitter* fit = new TFractionFitter(data, mc);
  fit->Constrain(0,0.0,1.0);
  fit->Constrain(1,0.0,1.0);
  fit->Constrain(2,0.0,1.0);

  Int_t status = fit->Fit();
  cout << "fit status: " << status << endl;

  TH1F *mcp0, *mcp1, *mcp2;
  Double_t p0, p1, p2, errP0, errP1, errP2;
  if (status == 0){
    TH1F* result = (TH1F*) fit->GetPlot();

    mcp0 = (TH1F*)fit->GetMCPrediction(0);
    mcp1 = (TH1F*)fit->GetMCPrediction(1);
    mcp2 = (TH1F*)fit->GetMCPrediction(2);

    fit->GetResult( 0, p0, errP0);
    fit->GetResult( 1, p1, errP1);
    fit->GetResult( 2, p2, errP2);

    cout << "p0"<< p0 << endl;
    cout << "p1"<< p1 << endl;
    cout << "p2"<< p2 << endl;

    mcp0->Scale(Ndata*p0/N0);
    mcp1->Scale(Ndata*p1/N1);
    mcp2->Scale(Ndata*p2/N2);

    TH1D *mcp_sum =  (TH1D*)mcp0->Clone();
    mcp_sum->Add(mcp1);
    mcp_sum->Add(mcp2);

    mcp0->SetFillColor(2);
    mcp1->SetFillColor(3);
    mcp2->SetFillColor(4);

    THStack *sum_stack = new THStack("stack","stack");
    sum_stack->Add(mcp0);
    sum_stack->Add(mcp1);
    sum_stack->Add(mcp2);
    
    TCanvas *c1 = new TCanvas("c", "Fitted distribution", 800, 600);
    TPad *pad1 = new TPad("pad1","pad1",0,0.3,1,1);
    pad1->SetLogy();
    pad1->SetTopMargin(0.05);
    pad1->SetBottomMargin(0);
    pad1->SetRightMargin(0.05);
    pad1->SetLeftMargin(0.16);
    pad1->SetFillStyle(4000);
    pad1->Draw("9");
    pad1->cd();

    sum_stack->SetMaximum(10000000);
    sum_stack->Draw("HIST");
    sum_stack->GetYaxis()->SetTitle("Events");
    sum_stack->GetXaxis()->SetTitle("jet MV1c weight");
    c1->Modified();
    data->Draw("Ep same");
    
    TLegend *legend = new TLegend(0.60,0.7,0.95,0.9);
    legend->SetTextSize(0.03);
    legend->SetFillStyle(0);
    legend->SetBorderSize(0);

    Char_t p_text[200];
    legend->AddEntry(data,"Data 2012","lp");
    sprintf(p_text,"Light jets = %.4f #pm %.4f", p0, errP0);
    legend->AddEntry(mcp0,p_text,"f");
    sprintf(p_text,"c jets = %.4f #pm %.4f",p1,errP1);
    legend->AddEntry(mcp1,p_text, "f");
    sprintf(p_text,"b jets = %.4f #pm %.4f",p2,errP2);
    legend->AddEntry(mcp2,p_text,"f");

    legend->Draw();
    ATLASLabel(.6,.6,"Internal");
    TLatex d_label;
    d_label.SetNDC();
    d_label.SetTextFont(42);
    d_label.DrawLatex(.6,.55,"#sqrt{s} = 8 TeV, 20.2 fb^{-1}");
    c1->cd();

    TPad *pad2 = new TPad("pad2","pad2",0,0,1,0.3);
    pad2->SetTopMargin(0);
    pad2->SetBottomMargin(0.48);
    pad2->SetRightMargin(0.05);
    pad2->SetLeftMargin(0.16);
    pad2->SetFillStyle(4000);
    pad2->SetGridx();
    pad2->SetGridy();
    pad2->Draw("9");
    pad2->cd();


    mcp_sum->SetStats(0);
    mcp_sum->SetMarkerSize(0.5);
    mcp_sum->GetYaxis()->SetTickLength(0.04);
    mcp_sum->GetYaxis()->SetNdivisions(505);
    mcp_sum->GetXaxis()->SetLabelSize(0.04*3./1.);
    mcp_sum->GetXaxis()->SetTitleSize(0.04*3./1.);
    mcp_sum->GetYaxis()->SetLabelSize(0.04*3./1.);
    mcp_sum->GetYaxis()->SetTitleSize(0.04*3./1.);
    mcp_sum->GetXaxis()->SetTitleOffset(1.2);
    mcp_sum->GetYaxis()->SetTitleOffset(1.2/2.);
    mcp_sum->GetXaxis()->SetTitle("");

    mcp_sum->GetYaxis()->SetTitle("Data/MC");
    mcp_sum->GetXaxis()->SetTitle("MV1c weight");
    mcp_sum->SetLineColor(kBlack);
    mcp_sum->Divide(data,mcp_sum);

    mcp_sum->SetMinimum(0.8);
    mcp_sum->SetMaximum(1.15);
    mcp_sum->SetMarkerStyle(20);
    mcp_sum->Draw("ep");

    c1->cd();
    c1->Update();

  }

  TCanvas *c2 = new TCanvas("c2", "Original distribution", 800, 600);
  c2->cd();
  TPad *pad3 = new TPad("pad3","pad3",0,0.3,1,1);
  pad3->SetLogy();
  pad3->SetTopMargin(0.05);
  pad3->SetBottomMargin(0);
  pad3->SetRightMargin(0.05);
  pad3->SetLeftMargin(0.16);
  pad3->SetFillStyle(4000);
  pad3->Draw("9");
  pad3->cd();

  mc_stack->SetMaximum(10000000);
  mc_stack->Draw("HIST");
  mc_stack->GetYaxis()->SetTitle("Events");
  mc_stack->GetXaxis()->SetTitle("jet MV1c weight");
  c2->Modified();
  data->Draw("Ep same");

  TLegend *legend2 = new TLegend(0.60,0.7,0.95,0.9);
  legend2->SetTextSize(0.03);
  legend2->SetFillStyle(0);
  legend2->SetBorderSize(0);

  Char_t p_text[200];
  legend2->AddEntry(data,"Data 2012","lp");
  legend2->AddEntry(h0,"light jets","f");
  legend2->AddEntry(h1,"charm jets", "f");
  legend2->AddEntry(h2,"bottom jets","f");

  legend2->Draw();
  ATLASLabel(.6,.6,"Internal");
  TLatex d_label;
  d_label.SetNDC();
  d_label.SetTextFont(42);
  d_label.DrawLatex(.6,.55,"#sqrt{s} = 8 TeV, 20.2 fb^{-1}");
  c2->cd();

  TPad *pad4 = new TPad("pad4","pad4",0,0,1,0.3);
  pad4->SetTopMargin(0);
  pad4->SetBottomMargin(0.48);
  pad4->SetRightMargin(0.05);
  pad4->SetLeftMargin(0.16);
  pad4->SetFillStyle(4000);
  pad4->SetGridx();
  pad4->SetGridy();
  pad4->Draw("9");
  pad4->cd();

  h_sum->SetStats(0);
  h_sum->SetMarkerSize(0.5);
  h_sum->GetYaxis()->SetTickLength(0.04);
  h_sum->GetYaxis()->SetNdivisions(505);
  h_sum->GetXaxis()->SetLabelSize(0.04*3./1.);
  h_sum->GetXaxis()->SetTitleSize(0.04*3./1.);
  h_sum->GetYaxis()->SetLabelSize(0.04*3./1.);
  h_sum->GetYaxis()->SetTitleSize(0.04*3./1.);
  h_sum->GetXaxis()->SetTitleOffset(1.2);
  h_sum->GetYaxis()->SetTitleOffset(1.2/2.);
  h_sum->GetXaxis()->SetTitle("");

  h_sum->GetYaxis()->SetTitle("Data/MC");
  h_sum->GetXaxis()->SetTitle("MV1c weight");
  h_sum->SetLineColor(kBlack);
  h_sum->Divide(data,h_sum);

  h_sum->SetMinimum(0.5);
  h_sum->SetMaximum(1.5);
  h_sum->SetMarkerStyle(20);
  h_sum->Draw("ep");

  c2->cd();
  c2->Update();

}

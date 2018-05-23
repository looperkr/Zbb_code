#include "AtlasStyle.C"
#include "AtlasLabels.C"
#include "AtlasUtils.h"

void plot_var(){

  string hist_name = "zmumu_sum";
  string hist_dir = "/n/atlas02/user_codes/looper.6/Vbb/analysis_code/MC_histograms_root/";

  string down = hist_dir + "bottom_jets_hmatch_down.root";
  string up = hist_dir + "bottom_jets_hmatch_up.root";
  string center = hist_dir + "bottom_jets_hmatch.root";

  TFile *f_down = TFile::Open(down.c_str(),"READ");
  TFile *f_up = TFile::Open(up.c_str(),"READ");
  TFile *f_center = TFile::Open(center.c_str(),"READ");

  TH1D *h_down = (TH1D*)f_down->Get(hist_name.c_str());
  TH1D *h_up = (TH1D*)f_up->Get(hist_name.c_str());
  TH1D *h_center = (TH1D*)f_center->Get(hist_name.c_str());

  TH1D *h_center_clone1 = (TH1D*)h_center->Clone();
  TH1D *h_center_clone2 = (TH1D*)h_center->Clone();

  TCanvas *c1 = new TCanvas("c", "c", 800, 600);
  //c1->SetLogy();
  /*h_down->SetLineColor(kBlue);
  h_up->SetLineColor(kRed);
  h_down->Draw("HIST");
  h_up->Draw("HIST same");*/
  h_center_clone1->Divide(h_up,h_center_clone1);
  h_center_clone1->Draw("HIST");
  h_center_clone2->SetLineColor(kBlue);
  h_center_clone2->Divide(h_down,h_center_clone2);
  h_center_clone2->Draw("HIST SAME");
  //  h_mc_sum_clone->Divide(h_data,h_mc_sum_clone);
  //h_center->Draw("HIST same");

}

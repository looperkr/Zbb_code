#include "AtlasStyle.C"
#include "AtlasLabels.C"
#include "AtlasUtils.h"

#include <iostream>
#include <TFile.h>
#include <TH1.h>
#include <TCanvas.h>
#include <TPad.h>
#include <TLegend.h>

void compare_vars(){

  string fname_b = "Z_pt_1b_truth";
  string fname_l = "Z_pt_1j_notb_truth";
  
  string hname_b = fname_b + "_mc";
  string hname_l = fname_l + "_mc";

  string histo_path  = "MC_histograms_root/";
  fname_b = histo_path+fname_b+".root";
  fname_l = histo_path+fname_l+".root";

  TFile *f_b = TFile::Open(fname_b.c_str(),"READ");
  TFile *f_l = TFile::Open(fname_l.c_str(),"READ");
  

  TH1D *h_b = (TH1D*)f_b->Get(hname_b.c_str());
  TH1D *h_l = (TH1D*)f_l->Get(hname_l.c_str());
  Double_t scale_b = 1/h_b->Integral();
  Double_t scale_l = 1/h_l->Integral();

  h_b->Scale(scale_b);
  h_l->Scale(scale_l);

  h_b->SetLineColor(kRed);
  h_l->SetLineColor(kBlue);

  TCanvas *c1 = new TCanvas("c", "c", 800, 1000);

  h_l->Draw("HIST");
  h_b->Draw("HIST SAME");
  
  TLegend *leg = new TLegend(0.6,0.75,0.95,0.95);
  leg->SetTextSize(0.02);

  leg->AddEntry(h_b,"#splitline{Z with leading jet == b}{(dressed truth pT)}","l");
  leg->AddEntry(h_l,"#splitline{Z with leading jet != b}{(dressed truth pT)}","l");
  leg->Draw();


}

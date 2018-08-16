#include "AtlasStyle.C"
#include "AtlasLabels.C"
#include "AtlasUtils.h"

#include <iostream>
#include <TFile.h>
#include <TH1.h>
#include <TCanvas.h>
#include <TPad.h>
#include <TLegend.h>

void draw_vars(){

  string fname_r = "Z_pt_1b_reco";
  string fname_t = "Z_pt_1b_truth";
  string fname_d = "scaled_data";

  string hname_r = fname_r + "_mc";
  string hname_t = fname_t + "_mc";
  string hname_d = "h_dataZ_Nominal";

  string histo_path  = "MC_histograms_root/";
  fname_r = histo_path+fname_r+".root";
  fname_t = histo_path+fname_t+".root";
  fname_d = histo_path+fname_d+".root";

  TFile *f_r = TFile::Open(fname_r.c_str(),"READ");
  TFile *f_t = TFile::Open(fname_t.c_str(),"READ");
  TFile *f_d = TFile::Open(fname_d.c_str(),"READ");


  TH1D *h_r = (TH1D*)f_r->Get(hname_r.c_str());
  TH1D *h_t = (TH1D*)f_t->Get(hname_t.c_str());
  TH1D *h_d = (TH1D*)f_d->Get(hname_d.c_str());

  cout << "Data integral: " << h_d->Integral() << endl;
  cout << "reco integral: " << h_r->Integral() << endl;
  cout << "truth integral: " << h_t->Integral() << endl;

  h_r->SetLineColor(kRed);
  h_t->SetLineColor(kBlue);
  h_d->SetLineColor(kBlack);

  TCanvas *c1 = new TCanvas("c", "c", 800, 1000);

  h_d->GetXaxis()->SetTitle("Z p_{T} [GeV]");

  h_d->Draw("HIST");
  h_r->Draw("HIST SAME");
  h_t->Draw("HIST SAME");

  
  TLegend *leg = new TLegend(0.6,0.75,0.95,0.95);
  leg->SetTextSize(0.02);

  leg->AddEntry(h_r,"reco","l");
  leg->AddEntry(h_t,"truth","l");
  leg->AddEntry(h_d,"data","l");
  leg->Draw();


}

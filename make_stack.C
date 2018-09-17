#include "TString.h"
#include "TFile.h"
#include "TH1.h"
#include "THStack.h"

void make_stack(bool isSherpa = true){

  
  TString fn_c = "MC_histograms_root/Z_pt_1j_cjets.root";
  TString fn_b = "MC_histograms_root/Z_pt_1j_bjets.root";
  TString fn_l = "MC_histograms_root/Z_pt_1j_ljets.root";
  TString fn_bsel = "MC_histograms_root/Z_pt_1b_bjets.root";

  TString hn_c = "Z_pt_1j_cjets";
  TString hn_b = "Z_pt_1j_bjets";
  TString hn_l = "Z_pt_1j_ljets";
  TString hn_bsel = "Z_pt_1b_bjets";
  
  if(isSherpa){
    hn_c += "_sherpa";
    hn_b += "_sherpa";
    hn_l += "_sherpa";
    hn_bsel += "_sherpa";
  }
  else{
    hn_c += "_mc";
    hn_b += "_mc";
    hn_l += "_mc";
    hn_bsel += "_mc";
  }

  cout << "hn_c: " << hn_c << endl;

  TFile *f_c = TFile::Open(fn_c,"read");
  TFile *f_b = TFile::Open(fn_b,"read");
  TFile *f_l = TFile::Open(fn_l,"read");
  TFile *f_bsel = TFile::Open(fn_bsel,"read");

  TH1D *h_c = (TH1D*)f_c->Get(hn_c);
  TH1D *h_b = (TH1D*)f_b->Get(hn_b);
  TH1D *h_l = (TH1D*)f_l->Get(hn_l);
  TH1D *h_bsel = (TH1D)f_bsel->Get(hn_l);

  h_c->GetXaxis()->SetTitle("Z p_{T} [GeV]");
  h_l->GetXaxis()->SetTitle("Z p_{T} [GeV]");
  h_b->GetXaxis()->SetTitle("Z p_{T} [GeV]");

  h_l->GetYaxis()->SetTitle("Events/GeV");

  h_c->SetTitle("c jets");
  h_l->SetTitle("light jets");
  h_b->SetTitle("b jets");

  TCanvas *c = new TCanvas("c","c",1440,600);
  c->Divide(3,1);
  c->cd(1);
  h_l->Draw();
  c->cd(2);
  h_c->Draw();
  c->cd(3);
  h_b->Draw();

  TString img_name_splt = "flavor_split_";
  if(isSherpa) img_name_splt += "sherpa.pdf";
  else img_name_splt += "alpgen.pdf";
  c->SaveAs(img_name_splt);

  h_c->SetFillColor(kRed);
  h_b->SetFillColor(kGreen);
  h_l->SetFillColor(kYellow);

  THStack *h_stack = new THStack("stack","stack");
  h_stack->Add(h_b);
  h_stack->Add(h_c);
  h_stack->Add(h_l);

  TCanvas *c1 = new TCanvas("c1","c1",1200,1200);  
  c1->SetLogy();

  h_stack->SetMinimum(10);
  h_stack->Draw("HIST");

  h_stack->GetXaxis()->SetTitle("Z p_{T} [GeV]");
  h_stack->GetYaxis()->SetTitle("Events/GeV");

  TLegend *legend = new TLegend(0.8,0.84,0.95,0.95);
  legend->SetTextSize(0.03);
  legend->AddEntry(h_b,"b jets","f");
  legend->AddEntry(h_c,"c jets","f");
  legend->AddEntry(h_l,"other","f");
  legend->Draw();

  c1->Modified();

  TString img_name_stack = "flavor_stack_";
  if(isSherpa) img_name_stack += "sherpa.pdf";
  else img_name_stack += "alpgen.pdf";
  c1->SaveAs(img_name_stack);

}

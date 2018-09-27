#include "TString.h"
#include "TFile.h"
#include "TH1.h"
#include "THStack.h"

void make_stack(bool isSherpa = false){

  
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

  TCanvas *c1 = new TCanvas("","",600,800);
  string img_name_flav;
  h_l->Draw();
  if(isSherpa) img_name_flav = "Zpt_light_sherpa.pdf";
  else img_name_flav = "Zpt_light_alpgen.pdf";
  c1->SaveAs(img_name_flav.c_str());
  c1->Clear();
  h_c->Draw();
  if(isSherpa) img_name_flav = "Zpt_charm_sherpa.pdf";
  else img_name_flav = "Zpt_charm_alpgen.pdf";
  c1->SaveAs(img_name_flav.c_str());
  c1->Clear();
  h_b->Draw();
  if(isSherpa) img_name_flav = "Zpt_bottom_sherpa.pdf";
  else img_name_flav = "Zpt_bottom_alpgen.pdf";
  c1->SaveAs(img_name_flav.c_str());
  c1->Clear();
 

  TCanvas *c2 = new TCanvas("c2","c2",1440,600);
  c2->Divide(3,1);
  c2->cd(1);
  h_l->Draw();
  c2->cd(2);
  h_c->Draw();
  c2->cd(3);
  h_b->Draw();

  TString img_name_splt = "flavor_split_";
  if(isSherpa) img_name_splt += "sherpa.pdf";
  else img_name_splt += "alpgen.pdf";
  c2->SaveAs(img_name_splt);

  h_c->SetFillColor(kRed);
  h_b->SetFillColor(kGreen);
  h_l->SetFillColor(kYellow);

  THStack *h_stack = new THStack("stack","stack");
  h_stack->Add(h_b);
  h_stack->Add(h_c);
  h_stack->Add(h_l);

  TCanvas *c3 = new TCanvas("c3","c3",1200,1200);  
  c3->SetLogy();

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

  c3->Modified();

  TString img_name_stack = "flavor_stack_";
  if(isSherpa) img_name_stack += "sherpa.pdf";
  else img_name_stack += "alpgen.pdf";
  c3->SaveAs(img_name_stack);

}

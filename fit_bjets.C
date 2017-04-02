void fit_bjets(){

  string hist_name = "zmumu_sum";
  string hist_dir = "/n/atlas02/user_codes/looper.6/Vbb/analysis_code/MC_histograms_root/";
  string light_f = hist_dir + "light_jets.root";
  string charm_f = hist_dir + "charm_jets.root";
  string bottom_f = hist_dir + "bottom_jets.root";

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

    //    mcp0->SetLineStyle(2);
    // mcp1->SetLineStyle(2);
    //mcp2->SetLineStyle(2);

    //    mcp0->SetLineColor(2);
    //mcp1->SetLineColor(3);
    //mcp2->SetLineColor(4);

    mcp0->SetFillColor(2);
    mcp1->SetFillColor(3);
    mcp2->SetFillColor(4);

    THStack *sum_stack = new THStack("stack","stack");
    sum_stack->Add(mcp0);
    sum_stack->Add(mcp1);
    sum_stack->Add(mcp2);
    
    TCanvas *c1 = new TCanvas("c", "FractionFitter example", 1000, 700);
    //    data->Draw("Ep");
    c1->SetLogy();
    sum_stack->SetMaximum(10000000);
    sum_stack->Draw("HIST");
    data->Draw("Ep same");
    
    TLegend *legend = new TLegend(0.60,0.75,0.9,0.9);
    legend->SetTextSize(0.02);
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
  }

}

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iomanip>
#include "TFile.h"
#include "TString.h"
#include "TH1.h"
#include "TH2.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TImage.h"
#include <ctime>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "THStack.h"


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
  struct stat statbuf;
  bool isDir = false;
  if(stat(plots_dir.c_str(), &statbuf) != -1){
    if (S_ISDIR(statbuf.st_mode)){
      isDir = true;
    }
  }

  if(!isDir){
    mkdir(plots_dir.c_str(),S_IRWXU | S_IRWXG | S_IROTH);
  }

}


void rebin2(TH1 *h, Int_t ngx, Int_t ngy)
{
  //Rebin 2-d histogram h, grouping ngx bins together along X
  //and ngy bins together along Y
  //NB: this macro ignores histogram errors if defined
   
  //make a clone of h
  TH1 *hold = (TH1*)h->Clone();
  hold->SetDirectory(0);

  Int_t  nbinsx = hold->GetXaxis()->GetNbins();
  Int_t  nbinsy = hold->GetYaxis()->GetNbins();
  Float_t xmin  = hold->GetXaxis()->GetXmin();
  Float_t xmax  = hold->GetXaxis()->GetXmax();
  Float_t ymin  = hold->GetYaxis()->GetXmin();
  Float_t ymax  = hold->GetYaxis()->GetXmax();
  Int_t nx = nbinsx/ngx;
  Int_t ny = nbinsy/ngy;
  h->SetBins (nx,xmin,xmax,ny,ymin,ymax);

  //loop on all bins to reset contents and errors
  Double_t cu;
  Float_t bx,by;
  Int_t ix,iy,ibin,bin,binx,biny;
  for (biny=1;biny<=nbinsy;biny++) {
    for (binx=1;binx<=nbinsx;binx++) {
      ibin = h->GetBin(binx,biny);
      h->SetBinContent(ibin,0);
    }
  }
  //loop on all bins and refill
  for (biny=1;biny<=nbinsy;biny++) {
    by  = hold->GetYaxis()->GetBinCenter(biny);
    iy  = h->GetYaxis()->FindBin(by);
    for (binx=1;binx<=nbinsx;binx++) {
      bx = hold->GetXaxis()->GetBinCenter(binx);
      ix  = h->GetXaxis()->FindBin(bx);
      bin = hold->GetBin(binx,biny);
      ibin= h->GetBin(ix,iy);
      cu  = hold->GetBinContent(bin);
      h->AddBinContent(ibin,cu);
    }
  }
  delete hold;          
}

void draw_2D(){

  bool isSherpa = false;

  string var = "Z_pt_v_p_bjets";
  string path = "MC_histograms_root/" + var + ".root";

  if(isSherpa){
    var+="_sherpa";
  }
  else{
    var+= "_mc";
  }

  cout << path << endl;
  cout << var << endl;

  TFile *f = TFile::Open(path.c_str(),"READ");
  TH1D *h = (TH1D*)f->Get(var.c_str());
  h->SetAxisRange(0.,200.,"X");
  h->SetAxisRange(0.,200.,"Y");
  rebin2(h,5,5);
  
  TCanvas *c1 = new TCanvas("","",800,600);

  h->SetXTitle("Z p_{T} [GeV]");
  h->SetYTitle("Z p [GeV]");
  h->Draw("BOX");

  string plt_path = "/n/atlas02/user_codes/looper.6/Vbb/analysis_plots/";
  string plt_dir; // final place plots will be written                                                                             
  create_dir(plt_path,plt_dir);
  
  string img_name = plt_dir + "/" + var + ".pdf";
  c1->SaveAs(img_name.c_str());
}


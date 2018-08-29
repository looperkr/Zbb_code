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

  TFile *f = TFile::Open("output.root","READ");
  TH1D *h = (TH1D*)f->Get("jet_pt_2D");
  h->SetAxisRange(0.,400.,"X");
  h->SetAxisRange(0.,400.,"Y");
  //  rebin2(h,5,5);
  
  //  h->Draw("BOX");
  h->SetXTitle("reco");
  h->SetYTitle("truth");
  h->Draw("BOX");


}


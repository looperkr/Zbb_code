#ifndef ANALYSIS_PLOTS_H
#define ANALYSIS_PLOTS_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
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


struct HistoOpts{
  TString histo_name;
  TString x_name;
  TString y_name;
  double x_min;
  double x_max;
  double y_min;
  double y_max;
  int rebin;
  double ratiomin;
  double ratiomax;
} histToPlot;

void chooseHistOptions(const TString & histo_name, const TString & x_name, const TString & y_name, double x_min, double x_max, double y_min, double y_max, 
			int rebin, double ratiomin, double ratiomax){
  histToPlot.histo_name = histo_name;
  histToPlot.x_name = x_name;
  histToPlot.y_name = y_name;
  histToPlot.x_min = x_min;
  histToPlot.x_max = x_max;
  histToPlot.y_min = y_min;
  histToPlot.y_max = y_max;
  histToPlot.rebin = rebin;
  histToPlot.ratiomin = ratiomin;
  histToPlot.ratiomax = ratiomax;
}

class Histogram{
 private:
  TH1D * hist_1D;
  TH2D * hist_2D;
  string name;
  bool is1D;

 public:
  
  void SetHistogram(TH1D * histo, string & h_name){
    hist_1D = histo;
    is1D = true;
    name = h_name;
  }
  void SetHistogram(TH2D * histo, string & h_name){
    hist_2D = histo;
    is1D = false;
    name = h_name;
  }
  bool GetIs1D(){
    return is1D;
  }
  string GetName(){
    return name;
  }
  TH1 * GetHist(){
    if(is1D) return hist_1D;
    else return hist_2D;
  }
  void SetName(string n){
    name = n;
    if(is1D) hist_1D->SetName(name.c_str());
    else hist_2D->SetName(name.c_str());
  }
  void DrawHist(){
    if(is1D) hist_1D->Draw();
    else hist_2D->Draw();
  }
  Histogram CloneHist(){
    Histogram newHist;
    if(is1D) {
      TH1D *new_h = (TH1D*)hist_1D->Clone();
      string name_copy(hist_1D->GetName());
      newHist.SetHistogram(new_h,name_copy);
    }
    else{
      TH2D *new_h = (TH2D*)hist_2D->Clone();
      string name_copy(hist_2D->GetName());
      newHist.SetHistogram(new_h,name_copy);
    }
    //    if(is1D) newHist = SetHistogram(hist_1D, name);
    //    else newHist.SetHistogram(hist_2D,name);
    return newHist;
  }
  void AddHist(Histogram & h_add){
    try{
      if(is1D && h_add.GetIs1D()){
	hist_1D->Add(h_add.hist_1D);
      }
      else if(!is1D && !(h_add.GetIs1D())){
	hist_2D->Add(h_add.hist_2D);
      }
      else{
	throw 10;
      }
    }
    catch(int x){
      cout << "Your histogram dimensions don't match!" << endl;
    }
  }
  void SetFillColorHist(Color_t color){
    if(is1D) hist_1D->SetFillColor(color);
    else hist_2D->SetFillColor(color);
  }
  void SetLineStyleHist(int n){
    if(is1D) hist_1D->SetLineStyle(n);
    else hist_2D->SetLineStyle(n);
  }
  void SetLineColorHist(int n){
    if(is1D) hist_1D->SetLineColor(n);
    else hist_2D->SetLineColor(n);
  }
  void SetLineWidthHist(int n){
    if(is1D) hist_1D->SetLineWidth(n);
    else hist_2D->SetLineWidth(n);
  }
  double IntegralHist(){
    double n_events;
    if(is1D) n_events = hist_1D->Integral();
    else n_events = hist_2D->Integral();
    return n_events;
  }
  void RebinHist(int rebin){
    if(is1D) hist_1D->Rebin(rebin);
    else hist_2D->Rebin2D(rebin);
  }
  void SetXRangeHist(double min, double max){
    if(is1D) hist_1D->GetXaxis()->SetRangeUser(min,max);
    else hist_2D->GetXaxis()->SetRangeUser(min,max);
  }
  void SetYRangeHist(double min, double max){
    hist_2D->GetYaxis()->SetRangeUser(min,max);
  }
  void ScaleHist(double scale_value){
    if(is1D) hist_1D->Scale(scale_value);
    else hist_2D->Scale(scale_value);
  }
  void SetMaxHist(double max){
    if(is1D) hist_1D->SetMaximum(max);
    else hist_2D->SetMaximum(max);
  }
  void SetMinHist(double min){
    if(is1D) hist_1D->SetMinimum(min);
    else hist_2D->SetMinimum(min);
  }
};

string NumToStr(int number_val){
  ostringstream ss;
  ss << number_val;
  return ss.str();
}

string NumToStr(float number_val){
  ostringstream ss;
  ss << number_val;
  return ss.str();
}

string NumToStr(double number_val){
  ostringstream ss;
  ss << number_val;
  return ss.str();
}

void debug(int debug_int){
  cout << "DEBUG " << debug_int << endl;
}

void SetFormats(TH1D * h_in, TString & x_name, TString & y_name){
  h_in->GetXaxis()->SetTitle(x_name);
  h_in->GetXaxis()->SetTitle(y_name);
  h_in->GetXaxis()->SetTitleSize(0.04*3./2.);
  h_in->GetYaxis()->SetLabelSize(0.04*3./2.);
  h_in->GetYaxis()->SetTitleSize(0.04*3./2.);
  h_in->GetXaxis()->SetTitleOffset(1.2);
  h_in->GetYaxis()->SetTitleOffset(1.2);
}

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


void write_table(TH1D * h_mc, TH1D * h_data, TString & process_name){
  ofstream tablefile;
  tablefile.open("njets_values_table.txt",ios::out);
  int bins = h_mc->GetSize(); //gives #bins + overflow + underflow
  double content_mc;
  double content_data;
  double bin_value;
  tablefile << "Process: " << process_name << endl;
  tablefile << "==================================================================" << endl;
  for(int i=0; i<bins; i++){
    tablefile << "- - - - - - - - - - - - - - - - - - - - - " << endl;
    bin_value = h_mc->GetXaxis()->GetBinCenter(i);
    content_mc = h_mc->GetBinContent(i);
    content_data = h_data->GetBinContent(i);
    tablefile << "BIN VALUE: " << bin_value << endl;
    tablefile << "MC, BIN #" << i << ": " << content_mc << endl;
    tablefile << "DATA, BIN #" << i << ": " << content_data << endl;
    tablefile << "- - - - - - - - - - - - - - - - - - - - - " << endl;
  }
  tablefile << "==================================================================" << endl;
}

void close_files(TFile ** farray, const int farray_size){
  for(int i = 0; i < farray_size; i++){
    farray[i]->Close();
  }
}

Histogram add_histo(TFile ** farray, const int farray_size, string *file_name, TString &h_name, vector<double> &xsec_values,TFile ** cfarray, double luminosity, TString process_str, int x_min, int x_max){
  //check to see if file and histogram opens
  cout << "Opening " << process_str << endl;
  if (farray[0]->IsOpen()){
    cout << "File opened." << endl;
    TH1D * histo_check = (TH1D*)farray[0]->Get(h_name);
    //cout << h_name << endl;
    if(histo_check) cout << "Histogram opened." << endl;
    else cout << "Histogram " << *file_name << " failed to open." << endl;
  }
  else cout << "ERROR: could not open file." << endl;

  string cutflow_location;
  //hfor numbers do not include pileup reweighting (and shouldn't!)
  double eventn_array[farray_size]; //total number of events in sample with pileup reweighting
  double norm_factor[farray_size];
 
  for(int i=0;i<farray_size;i++){
    TH1D *h_cutflow= (TH1D*)cfarray[i]->Get("ICUTZ_w");
    eventn_array[i] = h_cutflow->GetBinContent(3);
  }

  double eff_xsec[farray_size];

  //Normalization factor = xsec * lumi * (1/entries)
  //entries includes the pileup reweighting
  for(int i=0;i<farray_size;i++){
    norm_factor[i] = luminosity/(eventn_array[i]/xsec_values[i]);
  }
  double events_before_scaling = 0;
  double events_after_scaling = 0;
  //Open histograms and scale
  TH1D *h_array[farray_size];
  for(int i=0;i<farray_size;i++){
    h_array[i] = (TH1D*)farray[i]->Get(h_name);
    if(!h_array[i]) cout << "histogram " << h_name << " in " << i << "th file failed to open";
    events_before_scaling += h_array[i]->Integral();
    h_array[i]->Sumw2();
    h_array[i]->Scale(norm_factor[i]);
    events_after_scaling += h_array[i]->Integral();
  }

  string process_str_new(process_str);
  string sum_name = process_str_new + "_sum";
  cout.precision(8);
  cout << sum_name << " before scaling: " << events_before_scaling << endl;
  TH1D *h_sum = (TH1D*)h_array[0]->Clone();
  h_sum->SetName(sum_name.c_str());
  h_sum->Sumw2();
  for(int i=0;i<farray_size;i++){
    if(i>0) h_sum->Add(h_array[i]);
  }
  h_sum->GetXaxis()->SetRangeUser(x_min,x_max);
  cout << sum_name << " after scaling: " << events_after_scaling << endl;

  Histogram sumHist;
  sumHist.SetHistogram(h_sum,sum_name);
  
  return sumHist;

}

#endif

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

void write_event_numbers(TH1D * h_mc, TH1D * h_data, TString & variable_name, double luminosity){
  time_t now = time(0);
  string date_str(ctime(&now));
  string buffer_str;
  stringstream ss(date_str);

  ofstream textfile;
  textfile.open("/n/atlas02/user_codes/looper.6/Vbb/analysis_code/event_numbers/event_n_log.txt",ios::app);
  double mc_n = h_mc->Integral();
  double data_n = h_data->Integral();
  textfile << "Date and time: " << ss.rdbuf() << endl;
  textfile << "Histogram: " << variable_name << endl;
  textfile << "MC events: " << mc_n << endl;
  textfile << "Data events: " << data_n << endl;
  textfile << "Luminosity: " << luminosity << endl;
  textfile << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
  textfile.close();
}

void write_plots_2_file(TH1D ** h_array, const int h_array_size, TH1D * h_sum, string & variable_name, string & mc_name, string & img_path, int x_min, int x_max){

  TCanvas *c_hists = new TCanvas(variable_name.c_str(),variable_name.c_str(),800,600);
  TLegend *l = new TLegend(0.6,0.65,0.95,0.85);
  TImage *img = TImage::Create();
  string image_name;

  for(int i=0; i<h_array_size; i++){
    c_hists->Clear();
    h_array[i]->GetXaxis()->SetRangeUser(x_min,x_max);
    h_array[i]->Draw();
    c_hists->Update();
    img->FromPad(c_hists);
    image_name = img_path + "/" + variable_name + "_" + mc_name + NumToStr(i)+".png";
    img->WriteImage(image_name.c_str());
  }
  c_hists->Clear();
  h_sum->GetXaxis()->SetRangeUser(x_min,x_max);
  h_sum->Draw();
  c_hists->Update();
  img->FromPad(c_hists);
  image_name = img_path + "/" + variable_name + "_" + mc_name + "_sum.png";
  img->WriteImage(image_name.c_str());
  
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

TH1D * add_histo(TFile ** farray, const int farray_size, string *file_name, TString &h_name, vector<double> &xsec_values,TFile ** cfarray, double luminosity, TH1D ** h_array, TString process_str, int x_min, int x_max){
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
  double eventn_before_hfor[farray_size];
  double eventn_after_hfor[farray_size]; //hfor numbers do not include pileup reweighting (and shouldn't!)
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
  for(int i=0;i<farray_size;i++){
    h_array[i] = (TH1D*)farray[i]->Get(h_name);
    if(!h_array[i]) cout << "histogram " << h_name << " in " << i << "th file failed to open";
    events_before_scaling += h_array[i]->Integral();
    h_array[i]->Sumw2();
    h_array[i]->Scale(norm_factor[i]);
    events_after_scaling += h_array[i]->Integral();
  }
  TString sum_name = process_str + "_sum";
  cout.precision(8);
  cout << sum_name << " before scaling: " << events_before_scaling << endl;
  TH1D *h_sum = (TH1D*)h_array[0]->Clone();
  h_sum->SetName(sum_name);
  h_sum->Sumw2();
  for(int i=0;i<farray_size;i++){
    if(i>0) h_sum->Add(h_array[i]);
  }
  h_sum->GetXaxis()->SetRangeUser(x_min,x_max);
  cout << sum_name << " after scaling: " << events_after_scaling << endl;

  return h_sum;
}

#endif

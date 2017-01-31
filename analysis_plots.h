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

TH1D * add_histo(TFile ** farray, const int farray_size, string *file_name, TString &h_name, vector<double> &xsec_values,TFile ** cfarray, double luminosity, TH1D ** h_array, TString process_str, int x_min, int x_max){
  //check to see if file and histogram opens
  if (farray[0]->IsOpen()){
    cout << "File opened." << endl;
    TH1D * histo_check = (TH1D*)farray[0]->Get(h_name);
    //cout << h_name << endl;
    if(histo_check) cout << "Histogram opened." << endl;
    else cout << "Histogram failed to open." << endl;
  }
  else cout << "ERROR: could not open file." << endl;

  string cutflow_location;
  double eventn_before_hfor[farray_size];
  double eventn_after_hfor[farray_size]; //hfor numbers do not include pileup reweighting (and shouldn't!)
  double eventn_array[farray_size]; //total number of events in sample with pileup reweighting
  double norm_factor[farray_size];
 
  for(int i=0;i<farray_size;i++){
    cout << file_name[i] << endl;
    TH1D *h_cutflow= (TH1D*)cfarray[i]->Get("ICUTZ_w");
    eventn_array[i] = h_cutflow->GetBinContent(3);
    /*    if(file_name[i] != "WWtomunuqq_hists.root" && file_name[i] != "WZtomunuqq_hists.root"){
      TH1D *h_cutflow= (TH1D*)cfarray[i]->Get("ICUTZ_w");
      cout << "debug0" << endl;
      //eventn_array[i] = h_cutflow->GetBinContent(5);
      eventn_array[i] = h_cutflow->GetBinContent(3);
    }
    else if(file_name[i] == "WWtomunuqq_hists.root"){
      eventn_array[i] = 3160000;
    }
    else if(file_name[i] == "WZtomunuqq_hists.root"){
      eventn_array[i] = 840000;
      }*/
    cout << "debug1" << endl;
    //if(process_str == "wmunu" && i == 1) eventn_array[i] = 13094468;
    //else if(process_str == "wmunu" && i == 2) eventn_array[i] = 8216080;
    //else if(process_str == "wc" && i == 0) eventn_array[i] = 5059786;
    //  eventn_before_hfor[i] = h_cutflow->GetBinContent(1);
    //cout.precision(8);
    //eventn_after_hfor[i] = h_cutflow->GetBinContent(4);
  }
  //calculate k-factor for HFOR
  //event numbers don't include pileup reweighting
  double eff_xsec[farray_size];
  double k_hfor[farray_size];
  for(int i=0;i<farray_size;i++){
    //eff_xsec[i] = (xsec_values[i]*eventn_after_hfor[i])/eventn_before_hfor[i];
    //cout << file_name[i] << ", cross-section (with k-factors): " << xsec_values[i] << ", Effective cross-section (HFOR): " << eff_xsec[i] << endl;
    //    k_hfor[i] = xsec_values[i]/eff_xsec[i];
    // k_hfor[i] = eff_xsec[i]/xsec_values[i];
    //cout << file_name[i] << ", hfor k-factor: " << k_hfor[i] << endl;
  }

  //Normalization factor = xsec * lumi * (1/entries)
  //entries includes the pileup reweighting
  for(int i=0;i<farray_size;i++){
    //    norm_factor[i] = (luminosity*xsec_values[i]*k_hfor[i])/eventn_array[i];
    norm_factor[i] = luminosity/(eventn_array[i]/xsec_values[i]);
    //    cout << "Norm factor: " << norm_factor[i] << endl;
  }
  double events_before_scaling = 0;
  double events_after_scaling = 0;
  //Open histograms and scale
  for(int i=0;i<farray_size;i++){
    h_array[i] = (TH1D*)farray[i]->Get(h_name);
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
  //Write sum to file for mulitjet fits
  /*  if(h_name == "Z_mass"){
    TString mjfilename = "./multijet_calculation/"+process_str+".root";
    TFile * mjfile = TFile::Open(mjfilename,"UPDATE");
    h_sum->Write();
    mjfile->Close();
    }*/
  return h_sum;
}

#endif

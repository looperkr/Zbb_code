#include <TROOT.h>
#include <TChain.h>
#include <iostream>
#include <string>
#include <fstream>

void run_grid(){
  TChain *chain = new TChain("physics");

  std::string argStr;
  std::ifstream ifs("input.txt");
  std::getline(ifs,argStr);

  std::vector<std::string> fileList;
  for(size_t i=0,n; i <= argStr.length(); i=n+1){
    n = argStr.find_first_of(',',i);
    if(n == string::npos) n = argStr.length();
    string tmp = argStr.substr(i,n-i);
    fileList.push_back(tmp);
  }

  for(int iFile=0; iFile<fileList.size(); ++iFile){
    std::cout << "open " << fileList[iFile].c_str() << std::endl;
    chain->Add(fileList[iFile].c_str());
  }

  gInterpreter->GenerateDictionary("vector<vector<int> >","vector");
  gROOT->ProcessLine (".x $ROOTCOREDIR/scripts/load_packages.C");
  chain->Process("analysis_Zmumu.C+");
}

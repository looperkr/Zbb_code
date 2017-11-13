analysis_Zmumu.C: applies selections to data and MC, creates output histograms. Main analysis code.
analysis_plots.C: uses histograms from analysis_Zmumu.C to create kinematic plots. Combines MC based on x-section. Plots with data.
run_script.py: run script for analysis_Zmumu.C

Make sure to install ROOTCORE packages in packages.txt

To run analysis_Zmumu:
   Make sure to change isMC to the correct boolean value in both the run script and in analysis_Zmumu.C
   setup ROOT (make sure the version is ROOT 5)
   source ROOTCORE packages (source packages/RootCore/scripts/setup.sh) 
   > python run_script.py list_of_data_files.txt
   Puts outputs in directory MC_histograms or data_histograms

analysis_plots.C is a stand-alone ROOT macro that scales MC samples to cross-section and adds them. Can also scale MC to the data integral:
   Before running, make sure that data periods are added into one alldata.root file.
   Make_plots.C will run analysis_plots.C over all supported kinematic distributions




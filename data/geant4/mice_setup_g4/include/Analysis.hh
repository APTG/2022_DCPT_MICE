#ifndef Analysis_h
#define Analysis_h 1

#include "SimulationParameters.hh"
#include "G4AnalysisManager.hh"

#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&);               \
  void operator=(const TypeName&)

class Analysis
{
 public:
  ~Analysis();
   void SetAnalysis(SimulationParameters* aSMP);
   static Analysis *GetAnalysis();
   void Book();
   void Open();
   void Fill(scored_quatity sd);
   void FillHisto(int histo, double value);
   void Save();
   void Close();
   double GetBinVolume(int i);
   void SetSimulationParameters(SimulationParameters* aSMP){SMP  = aSMP;};
   int GetPGDCode(string name);
   int GetQuantityCode(string name);
   bool StringCompare(std::string s1, std::string s2);

 private:
   DISALLOW_COPY_AND_ASSIGN(Analysis);
   Analysis();
   vector<int>    histo;
   vector<int>    histo2D;
   vector<int>    histo3D;
   vector<int>    histo_dimension;
   vector<int>    histo_xaxis;
   vector<int>    histo_yaxis;
   vector<int>    histo_zaxis;
   vector<int>    histo_nBinx;
   vector<int>    histo_nBiny;
   vector<int>    histo_nBinz;
   vector<double> histo_xmin;
   vector<double> histo_ymin;
   vector<double> histo_zmin;
   vector<double> histo_xmax;
   vector<double> histo_ymax;
   vector<double> histo_zmax;
   vector<double> histo_binVolume;
   vector<string> histo_quantity;
   vector<int>    histo_watequ;
   vector<string> histo_particleName;
   vector<int>    histo_generation;
   vector<int>    histo_particleID;
   vector<int>    histo_particleType;
   vector<int>    histo_quantityID;
   double pos_edep[3], WDF, WEF, WSPF;
   int num_Histograms;
   SimulationParameters* SMP;
   scored_quatity sdata;
};
#endif

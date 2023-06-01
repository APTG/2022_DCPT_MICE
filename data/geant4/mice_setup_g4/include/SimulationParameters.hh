#ifndef SimulationParameters_h
#define SimulationParameters_h 1

#include "DataType.hh"

class SimulationParameters
{
 public:
   SimulationParameters(int argc, char** argv);
  ~SimulationParameters();
   void AssignDefaultParameters();
   void AssignInputParameters();
   void Initialization(std::vector<std::string> data);
   void PrintInititalParameters();

   source_parameter GetSourceParameters(){return source;}
   setup_parameter GetSetupParameters(){return setup;}
   physics_parameter GetPhysicsParameters(){return physics;}
   vector<histogram_parameter>  GetHistogramParameters(){return histograms;}
   vector<plan_sobp>            GetSpots(){ return spots;}
   plan_sobp GetSingleSpot(int i){ return spots[i];}
   vector<double> GetPhantomOut() {  return container_out;  }
   vector<double> GetPhantomIn()  {  return container_in;   }
   vector<double> GetWater()      {  return water;          }
   vector<double> GetLid()        {  return lid;            }
   vector<double> GetColl()       {  return coll_total;     }
   vector<double> GetCollGap()    {  return coll_space;     }



   void AssignSetupParameters(std::vector<string> sp);
   void AssignPhysicsParameters(std::vector<string> phy);
   void AssignHistoParameters(std::vector<string> his);
   void AssignPlanParameters(std::vector<string> plan);
   void AssignSpotsParameters(std::vector<string> plan);
   void AssignOuterCont(std::vector<string> outcon);
   void AssignInnerCont(std::vector<string> incon);
   void AssignCollTotal(std::vector<string> tcoll);
   void AssignCollSpace(std::vector<string> scoll);
   void AssignWaterLevel(std::vector<string> wat);
   void AssignLIDinfo(std::vector<string> plid);

   void PrintSetupParameters();
   void PrintPhysicsParameters();
   void PrintHistoParameters();
   void PrintSpotsParameters();
   void PrintContainerInfo();
   void PrintLidInfo();
   void PrintWaterInfo();

   int getcode (std::string const& inString);
   std::vector<std::string> ReadLine(std::string line);
   bool StringCompare(std::string s1, std::string s2);

   // void SetBeamParameter(beam_parameter* bp){beam = bp;}

 private:
   source_parameter source;
   setup_parameter setup;
   physics_parameter physics;
   vector<histogram_parameter> histograms;
   vector<plan_sobp> spots;
   string file_name;

   vector<double> container_out;
   vector<double> container_in;
   vector<double> water;
   vector<double> lid;
   vector<double> coll_total;
   vector<double> coll_space;

   int    useWaterEquivalent;
   const string parameters[10] = {"SETUP", "PHYSICS",  "PHASE", "COLLI", "SLICE", "HISTO", "PLAN", "SCAT"};
   const string list_pcut_particle[5] = {"proton", "photon", "e-", "e+", "neutron"};
   const string list_particle[5]= {"PROTON", "PHOTON", "ELECTRON", "POSITRON", "NEUTRON"};
};

#endif

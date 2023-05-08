#include "SimulationParameters.hh"

using namespace std;
SimulationParameters::SimulationParameters(int argc, char** argv){
  // Assign input file containing simulation Parameters
  if(argc>1){ file_name = argv[1];}
  else{file_name = "/home/fardous/PhD/Projects/Mice_Experiment_Old_Setup/SubProject(Cathrine_1st_paper)/test.dat";}
  AssignInputParameters();
}

SimulationParameters::~SimulationParameters(){

}

void SimulationParameters::AssignInputParameters(){
  string  line;
  fstream InputFile;
  InputFile.open(file_name);
  if (InputFile.is_open()){
    while (getline(InputFile,line)){
     if(line.length() != 0){
        vector<string> line_segments = ReadLine(line);
        char comments = line_segments[0][0];
        if(!(comments=='#' || comments=='%')){
            Initialization(line_segments);
        }
      }
      else{continue;}
    }
    InputFile.close();
  }

  else{
     cout <<"Error in file loading!"<<endl
          <<"The input file '"<<file_name<<"' is not found!" << endl
          <<"Program is terminating......."<<endl;
     exit(1);
    }
  return;
}

void SimulationParameters::PrintInititalParameters()
{
   PrintSetupParameters();
   PrintPhysicsParameters();
   if(histograms.size()>0)  { PrintHistoParameters();     }
   PrintSpotsParameters();
   PrintContainerInfo();
   PrintWaterInfo();
   PrintLidInfo();
   PrintCollimatorInfo();
   return;
}

void SimulationParameters::Initialization(std::vector<std::string> data)
{
  switch(getcode(data[0])) {
  //Setup Parameters
  case 1:
      AssignSetupParameters(data);
      break;

  case 2:
      AssignPhysicsParameters(data);
      break;

  case 3:
      AssignHistoParameters(data);
      break;

  case 4:{
      AssignPlanParameters(data);
      break;}

  case 5:
      AssignOuterCont(data);
      break;

  case 6:
      AssignInnerCont(data);
      break;

  case 7:
      AssignCollTotal(data);
      break;

  case 8:
      AssignCollSpace(data);
      break;

  case 9:
      AssignWaterLevel(data);
      break;

  case 10:
      AssignLIDinfo(data);
      break;

  case 0:{
      cout<<"Worning!"
          <<"'"<< data[0] << "' is not a valid 'parameter key'!"<< G4endl
          <<"Program is terminating......."<<endl;
      exit(1);}
  }
}


vector<string>  SimulationParameters::ReadLine(string line){
  vector<string> out;
  char *token = strtok(const_cast<char*>(line.c_str()), " ");
    while (token != nullptr)
    {
        out.push_back(string(token));
        token = strtok(nullptr, " ");
    }
   return out;
}

bool  SimulationParameters::StringCompare(string s1, string s2){
  transform(s1.begin(), s1.end(), s1.begin(), ::tolower);
  transform(s2.begin(), s2.end(), s2.begin(), ::tolower);
  if(s1.compare(s2) == 0){return true;}
  return false;
}

int SimulationParameters::getcode (std::string const& inString) {
               if (inString == "SETUP")    return 1;
          else if (inString == "PHYSICS")  return 2;
          else if (inString == "HISTO")    return 3;
          else if (inString == "PLAN")     return 4;
          else if (inString == "PHAOU")    return 5;
          else if (inString == "PHAIN")    return 6;
          else if (inString == "COLLT")    return 7;
          else if (inString == "COLLS")    return 8;
          else if (inString == "WATER")    return 9;
          else if (inString == "LID")      return 10;
          else return 0;
}

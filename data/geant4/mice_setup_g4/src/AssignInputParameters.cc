#include "SimulationParameters.hh"

void SimulationParameters::AssignSetupParameters(std::vector<string> sp){
  setup.n_particle   = stoi(sp[1]);
  setup.n_progress   = stoi(sp[2]);
  setup.n_thread     = stoi(sp[3]);
  setup.out_file     = sp[4];
  setup.n_pos        = stoi(sp[5]);
  setup.use_gui      = stoi(sp[6]);
}

void SimulationParameters::AssignPhysicsParameters(std::vector<string> phy){
  int length = phy.size();
  physics.phy_list        = phy[1];
  physics.step_length     = stod(phy[2]);
  physics.use_sl_neutral  = stoi(phy[3]);
  if(length>4){
    physics.use_pro_cut = 1;
    for(int i = 4; i< length; i++){
      physics.production_cut.push_back(stod(phy[i]));
    }
  }
  else{
    physics.use_pro_cut = 0;
  }
}

void SimulationParameters::AssignHistoParameters(std::vector<string> his){
  histogram_parameter histo;
  int length = his.size();
  string _quan = his[1], _par = his[2];
  transform(_quan.begin(), _quan.end(), _quan.begin(), ::tolower);
  transform(_par.begin(), _par.end(), _par.begin(), ::tolower);
  histo.quantity          = _quan;
  histo.particle          = _par;
  histo.particleType      = stoi(his[3]);
  histo.waterEquivalent   = stoi(his[4]);
  if(histo.waterEquivalent){
    useWaterEquivalent = 1;
  }
  histo.name              = his[5];
  histo.title             = his[6];
  if(length>6){
    for(int i = 7; i< length; i++){
      histo.numbers.push_back(stod(his[i]));
    }
  }
  histograms.push_back(histo);
}

void SimulationParameters::AssignPlanParameters(std::vector<string> plan){
  string  line;
  fstream InputFile;
  InputFile.open(plan[1]);
  if (InputFile.is_open()){
    while (getline(InputFile,line)){
     if(line.length() != 0){
        vector<string> spots_data = ReadLine(line);
        AssignSpotsParameters(spots_data);
      }
      else{continue;}
    }
    InputFile.close();
  }
  source.position = stod(plan[2]);
  source.SADx     = stod(plan[3]);
  source.SADy     = stod(plan[4]);
}

void SimulationParameters::AssignSpotsParameters(std::vector<string> spt){
  plan_sobp spot;
  spot.energy   = stod(spt[0])*1000.0;
  spot.e_spread = stod(spt[1])*1000.0;
  spot.spotx    = stod(spt[2])*10.0;
  spot.spoty    = stod(spt[3])*10.0;
  spot.sig_x    = stod(spt[4])*10.0/2.355;
  spot.sig_y    = stod(spt[5])*10.0/2.355;
  spot.div_x    = stod(spt[6]);
  spot.div_y    = stod(spt[7]);
  spot.cov_x    = stod(spt[8])*10.0;
  spot.cov_y    = stod(spt[9])*10.0;
  spot.weight   = stod(spt[10]);
  spots.push_back(spot);
}

void SimulationParameters::AssignOuterCont(std::vector<string> outcon){
 int length = outcon.size();
  for(int i = 1; i< length; i++){
    container_out.push_back(stod(outcon[i]));
  }
}

void SimulationParameters::AssignInnerCont(std::vector<string> incon){
 int length = incon.size();
  for(int i = 1; i< length; i++){
    container_in.push_back(stod(incon[i]));
  }
}

void SimulationParameters::AssignCollTotal(std::vector<string> tcoll){
 int length = tcoll.size();
  for(int i = 1; i< length; i++){
    coll_total.push_back(stod(tcoll[i]));
 }
}

void SimulationParameters::AssignCollSpace(std::vector<string> scoll){
 int length = scoll.size();
  for(int i = 1; i< length; i++){
    coll_space.push_back(stod(scoll[i]));
 }
}

void SimulationParameters::AssignWaterLevel(std::vector<string> wat){
 int length = wat.size();
  for(int i = 1; i< length; i++){
    water.push_back(stod(wat[i]));
 }
}

void SimulationParameters::AssignLIDinfo(std::vector<string> plid){
 int length = plid.size();
  for(int i = 1; i< length; i++){
    lid.push_back(stod(plid[i]));
 }
}

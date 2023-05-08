#include "SimulationParameters.hh"

using namespace std;

void SimulationParameters::PrintSetupParameters(){
  cout << G4endl;
  cout << setw(40)<< "***------------------------ Setup Parameters ------------------------***" <<G4endl;
  cout << G4endl;
  cout << setw(40)<< "No of particles   = " << setw(25)<<setup.n_particle << G4endl;
  cout << setw(40)<< "Progress intervel = " << setw(25)<<setup.n_progress << G4endl;
  cout << setw(40)<< "No of threads     = " << setw(25)<<setup.n_thread   << G4endl;
  cout << setw(40)<< "Output file       = " << setw(25)<<setup.out_file   << G4endl;
  cout << setw(40)<< "Position          = " << setw(25)<<setup.n_pos      << G4endl;
  cout << setw(40)<< "Use gui?          = " << setw(25)<<setup.use_gui    << G4endl << G4endl  << G4endl;
  return;
}

void SimulationParameters::PrintPhysicsParameters(){
  cout << G4endl;
  cout << setw(40)<< "***------------------------ Physics Parameters ------------------------***" <<G4endl;
  cout << G4endl;
  cout << setw(40)<< "Physics list           = " << setw(25)<<physics.phy_list       << G4endl;
  cout << setw(40)<< "Step length(SL)        = " << setw(25)<<physics.step_length    << G4endl;
  cout << setw(40)<< "Neutral particle SL    = " << setw(25)<<physics.use_sl_neutral << G4endl;
  if(physics.use_pro_cut){
    int max;
    if((int)physics.production_cut.size()>4){max  = 4;}
    else{max = (int)physics.production_cut.size();}
    for(int i = 0; i< max; i++){
      cout << setw(26)<< "Production cut of "<<setw(10)<< list_pcut_particle[i]<< setw(3)<< "="
           << setw(25)<<physics.production_cut[i] <<setw(10)  << "[mm]" << G4endl;
    }
  }
  return;
}

void SimulationParameters::PrintHistoParameters(){
  cout << G4endl;
  cout << setw(40)<< "***---------------------------------------------- Histogram Parameters ------------------------------------------***" <<G4endl;
  cout << G4endl;
  cout << setw(5) << "No"
       << setw(12)<< "Quantity"
       << setw(10)<< "Particle"
       << setw(10)<< "Type"
       << setw(12)<< "Name"
       << setw(5) << "Dim"
       << setw(8) << "x-bins"
       << setw(8) << "x-min"
       << setw(8) << "x-max"
       << setw(8) << "y-bins"
       << setw(8) << "y-min"
       << setw(8) << "y-max"
       << setw(8) << "z-bins"
       << setw(8) << "z-min"
       << setw(8) << "z-max"<< G4endl;

  cout << setw(5) << "--"
       << setw(12)<< "--------"
       << setw(10)<< "--------"
       << setw(12)<< "----"
       << setw(5) << "---"
       << setw(8) << "------"
       << setw(8) << "-----"
       << setw(8) << "-----"
       << setw(8) << "------"
       << setw(8) << "-----"
       << setw(8) << "-----"
       << setw(8) << "------"
       << setw(8) << "-----"
       << setw(8) << "-----"<< G4endl;
  for(int i = 0; i< (int) histograms.size(); i++){
    cout << setw(5) << i + 1
         << setw(12)<< histograms[i].quantity
         << setw(10)<< histograms[i].particle
         << setw(10)<< histograms[i].particleType
         << setw(12)<< histograms[i].name
         << setw(5) << histograms[i].numbers[0]
         << setw(8) << histograms[i].numbers[1]
         << setw(8) << histograms[i].numbers[2]
         << setw(8) << histograms[i].numbers[3]
         << setw(8) << histograms[i].numbers[4]
         << setw(8) << histograms[i].numbers[5]
         << setw(8) << histograms[i].numbers[6]
         << setw(8) << histograms[i].numbers[7]
         << setw(8) << histograms[i].numbers[8]
         << setw(8) << histograms[i].numbers[9] << G4endl;
  }
  cout << G4endl  << G4endl;
  return;
}

void SimulationParameters::PrintSpotsParameters(){
  plan_sobp p_spot;
  cout << G4endl;
  cout << setw(40)<< "***----------------------------------------------------------- Spots Parameters ---------------------------------------------------------***"<<G4endl;
  cout << G4endl;
  cout <<"    Source Distance: "<<source.position
       <<" mm    SADx: "<<source.SADx
       <<" mm    SADy: "<<source.SADy <<" mm" << G4endl<< G4endl;
  cout << setw(8)  << "No"
       << setw(12) << "Energy"
       << setw(12) << "Spread"
       << setw(12) << "Spot(x)"
       << setw(12) << "Spot(y)"
       << setw(12) << "Sig(x)"
       << setw(12) << "Sig(y)"
       << setw(12) << "Div(x)"
       << setw(12) << "Div(y)"
       << setw(12) << "Cov(x)"
       << setw(12) << "Cov(y)"
       << setw(12) << "Weight" << G4endl;

  cout << setw(8)  << "---"
       << setw(12) << "------"
       << setw(12) << "------"
       << setw(12) << "------"
       << setw(12) << "------"
       << setw(12) << "------"
       << setw(12) << "------"
       << setw(12) << "------"
       << setw(12) << "------"
       << setw(12) << "------"
       << setw(12) << "------"
       << setw(12) << "------" << G4endl;
  for(int i = 0; i< (int) spots.size(); i= i+50){
    p_spot = spots[i];
    cout << setw(8)  << i + 1
         << setw(12) << setprecision(4) << p_spot.energy
         << setw(12) << setprecision(4) << p_spot.e_spread
         << setw(12) << setprecision(4) << p_spot.spotx
         << setw(12) << setprecision(4) << p_spot.spoty
         << setw(12) << setprecision(4) << p_spot.sig_x
         << setw(12) << setprecision(4) << p_spot.sig_y
         << setw(12) << setprecision(4) << p_spot.div_x
         << setw(12) << setprecision(4) << p_spot.div_y
         << setw(12) << setprecision(4) << p_spot.cov_x
         << setw(12) << setprecision(4) << p_spot.cov_y
         << setw(12) << setprecision(2) << p_spot.weight << G4endl;
  }
  cout << G4endl  << G4endl;
  return;
}

void SimulationParameters::PrintContainerInfo(){
  cout << G4endl;
  cout << setw(40)<< "***---------------------------------- Phantom -------------------------------***" <<G4endl;
  cout << G4endl;

  cout<<fixed
       << setw(15)<< "Outer x-min = "    << setw(8)<<container_out[0]
       << setw(15)<< "Outer x-max = "    << setw(8)<<container_out[1]
       << setw(20)<< "Outer x-length = " << setw(8)<<container_out[1]-container_out[0]<<"  [mm]" << G4endl
       << setw(15)<< "Outer y-min = "    << setw(8)<<container_out[2]
       << setw(15)<< "Outer y-max = "    << setw(8)<<container_out[3]
       << setw(20)<< "Outer y-length = " << setw(8)<<container_out[3]-container_out[2]<<"  [mm]" << G4endl
       << setw(15)<< "Outer z-min = "    << setw(8)<<container_out[4]
       << setw(15)<< "Outer z-max = "    << setw(8)<<container_out[5]
       << setw(20)<< "Outer z-length = " << setw(8)<<container_out[5]-container_out[4]<<"  [mm]" << G4endl << G4endl
       << setw(15)<< "Inner x-min = "    << setw(8)<<container_in[0]
       << setw(15)<< "Inner x-max = "    << setw(8)<<container_in[1]
       << setw(20)<< "Inner x-length = " << setw(8)<<container_in[1]-container_in[0]<<"  [mm]" << G4endl
       << setw(15)<< "Inner y-min = "    << setw(8)<<container_in[2]
       << setw(15)<< "Inner y-max = "    << setw(8)<<container_in[3]
       << setw(20)<< "Inner y-length = " << setw(8)<<container_in[3]-container_in[2]<<"  [mm]" << G4endl
       << setw(15)<< "Inner z-min = "    << setw(8)<<container_in[4]
       << setw(15)<< "Inner z-max = "    << setw(8)<<container_in[5]
       << setw(20)<< "Inner z-length = " << setw(8)<<container_in[5]-container_in[4]<<"  [mm]" << G4endl << G4endl  << G4endl;
  return;
}

void SimulationParameters::PrintLidInfo(){
  cout << G4endl;
  cout << setw(40)<< "***------------------------------- LID Dimension ----------------------------***" <<G4endl;
  cout << G4endl;

  cout<<fixed
       << setw(15)<< "Lid x-min = "    << setw(8)<<lid[0]
       << setw(15)<< "Lid x-max = "    << setw(8)<<lid[1]
       << setw(20)<< "Lid x-length = " << setw(8)<<lid[1]-lid[0]<<"  [mm]" << G4endl
       << setw(15)<< "Lid y-min = "    << setw(8)<<lid[2]
       << setw(15)<< "Lid y-max = "    << setw(8)<<lid[3]
       << setw(20)<< "Lid y-length = " << setw(8)<<lid[3]-lid[2]<<"  [mm]" << G4endl
       << setw(15)<< "Lid z-min = "    << setw(8)<<lid[4]
       << setw(15)<< "Lid z-max = "    << setw(8)<<lid[5]
       << setw(20)<< "Lid z-length = " << setw(8)<<lid[5]-lid[4]<<"  [mm]" << G4endl << G4endl  << G4endl;
  return;
}

void SimulationParameters::PrintWaterInfo(){
  cout << G4endl;
  cout << setw(40)<< "***------------------------------- Water Level ------------------------------***" <<G4endl;
  cout << G4endl;

  cout<<fixed
       << setw(15)<< "Water x-min = "    << setw(8)<<water[0]
       << setw(15)<< "Water x-max = "    << setw(8)<<water[1]
       << setw(20)<< "Water x-length = " << setw(8)<<water[1]-water[0]<<"  [mm]" << G4endl
       << setw(15)<< "Water y-min = "    << setw(8)<<water[2]
       << setw(15)<< "Water y-max = "    << setw(8)<<water[3]
       << setw(20)<< "Water y-length = " << setw(8)<<water[3]-water[2]<<"  [mm]" << G4endl
       << setw(15)<< "Water z-min = "    << setw(8)<<water[4]
       << setw(15)<< "Water z-max = "    << setw(8)<<water[5]
       << setw(20)<< "Water z-length = " << setw(8)<<water[5]-water[4]<<"  [mm]" <<G4endl << G4endl  << G4endl;
  return;
  }

void SimulationParameters::PrintCollimatorInfo(){
  cout << G4endl;
  cout << setw(40)<< "***------------------------------------------------ Collimator --------------------------------------------***" <<G4endl;
  cout << G4endl;

  cout<<fixed
       << setw(25)<< "Collimator x-min = "    << setw(8)<<coll_total[0]
       << setw(25)<< "Collimator x-max = "    << setw(8)<<coll_total[1]
       << setw(30)<< "Collimator x-length = " << setw(8)<<coll_total[1]-coll_total[0]<<"  [mm]" << G4endl
       << setw(25)<< "Collimator y-min = "    << setw(8)<<coll_total[2]
       << setw(25)<< "Collimator y-max = "    << setw(8)<<coll_total[3]
       << setw(30)<< "Collimator y-length = " << setw(8)<<coll_total[3]-coll_total[2]<<"  [mm]" << G4endl
       << setw(25)<< "Collimator z-min = "    << setw(8)<<coll_total[4]
       << setw(25)<< "Collimator z-max = "    << setw(8)<<coll_total[5]
       << setw(30)<< "Collimator z-length = " << setw(8)<<coll_total[5]-coll_total[4]<<"  [mm]" << G4endl<< G4endl
       << setw(25)<< "Spacer x-min = "        << setw(8)<<coll_space[0]
       << setw(25)<< "Spacer x-max = "        << setw(8)<<coll_space[1]
       << setw(30)<< "Spacer x-length = "     << setw(8)<<coll_space[1]-coll_space[0]<<"  [mm]" << G4endl
       << setw(25)<< "Spacer y-min = "        << setw(8)<<coll_space[2]
       << setw(25)<< "Spacer y-max = "        << setw(8)<<coll_space[3]
       << setw(30)<< "Spacer y-length = "     << setw(8)<<coll_space[3]-coll_space[2]<<"  [mm]" << G4endl
       << setw(25)<< "Spacer z-min = "        << setw(8)<<coll_space[4]
       << setw(25)<< "Spacer z-max = "        << setw(8)<<coll_space[5]
       << setw(30)<< "Spacer z-length = "     << setw(8)<<coll_space[5]-coll_space[4]<<"  [mm]" << G4endl << G4endl  << G4endl;
  return;
}

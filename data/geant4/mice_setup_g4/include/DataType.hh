#ifndef DataType_h
#define DataType_h 1
#include<iostream>
#include<vector>
#include "G4Event.hh"
#include "G4SystemOfUnits.hh"
#include "G4SteppingManager.hh"
#include "G4VTouchable.hh"
#include "G4VPhysicalVolume.hh"
#include "G4TrackVector.hh"
#include "G4ProcessType.hh"

using namespace std;

#define ALL_PARTICLES -999

extern struct setup_parameter{
  int  n_particle;
  int  n_progress;
  int  n_thread;
  string out_file;
  int  n_pos;
  int  use_gui;
}setup_parameter_;

extern struct physics_parameter{
  string  phy_list;
  double  step_length;
  int     use_sl_neutral;
  int     use_pro_cut;
  vector<double>  production_cut;
}physics_parameter_;

extern struct source_parameter{
  double  position;
  double  SADx;
  double  SADy;
}beam_parameter_;

extern struct histogram_parameter{
  string quantity;
  string particle;
  int    particleType;//primary or secondary
  int    waterEquivalent;
  int    particleID;
  string name;
  string title;
  vector<double> numbers;
}histogram_parameter_;

extern struct scored_quatity{
  int EventID;
  int TrackID;
  int ParentID;
  int ProcessSubType;
  int ParticleGenType;
  int ParticlePDGcode;
  double ParticleCharge;
  double StepInitialKE;
  double StepFinalKE;
  double TotalSecondaryEnergy;
  double EnergyDeposit;
  double StepLength;
  double MaterialDensity;
  double WatDoseFactor;
  double WatSPFactor;
  double WatEnergyFactor;
  double StoppingPower;
  double WatStoppingPower;
  string ParticleName;
  string ProcessName;
  G4ThreeVector PreStepPosition;
  G4ThreeVector PostStepPosition;
  G4ThreeVector EnergyDepositPoint;
  G4ProcessType ProcessType;
}scored_quatity_;

extern struct plan_sobp{
  double energy;
  double e_spread;
  double spotx;
  double spoty;
  double sig_x;
  double sig_y;
  double div_x;
  double div_y;
  double cov_x;
  double cov_y;
  double weight;
}plan_sobp_;

extern struct pro_cut{
  string mat;
  G4Region* region;
  double energy;
  double range;
  double density;
}pro_cut_;
#endif

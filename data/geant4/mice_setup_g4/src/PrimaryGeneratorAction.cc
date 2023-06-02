
#include "PrimaryGeneratorAction.hh"
#include "G4Event.hh"
#include "cmath"
#include "G4ParticleTable.hh"
#include "Randomize.hh"
#include "G4ParticleDefinition.hh"
#include <CLHEP/Random/Randomize.h>
#include "globals.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include <random>

class G4Event;

PrimaryGeneratorAction::PrimaryGeneratorAction(SimulationParameters* aSMP): G4VUserPrimaryGeneratorAction()
{
  SMP = aSMP;
  fParticleGun  = new G4ParticleGun(1);
  CalculateTotalWeight();
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName = "proton";
  G4ParticleDefinition* particle = particleTable->FindParticle(particleName);
  fParticleGun->SetParticleDefinition(particle);
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete fParticleGun;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  spot_number = SpotSelector();
  pos_z   =  SMP->GetSourceParameters().position;
  SADx    =  SMP->GetSourceParameters().SADx;
  SADy    =  SMP->GetSourceParameters().SADy;

  energy  = G4RandGauss::shoot(SMP->GetSpots()[spot_number].energy,
                               SMP->GetSpots()[spot_number].e_spread);

  sig_x = SMP->GetSpots()[spot_number].sig_x;
  sig_y = SMP->GetSpots()[spot_number].sig_y;

  div_x = SMP->GetSpots()[spot_number].div_x;
  div_y = SMP->GetSpots()[spot_number].div_y;

  cov_x = SMP->GetSpots()[spot_number].cov_x;
  cov_y = SMP->GetSpots()[spot_number].cov_y;

  corre_x = cov_x/(sig_x * div_x);
  corre_y = cov_y/(sig_y * div_y);

  rand_pos_x = G4RandGauss::shoot(0.0, 1.0);
  rand_pos_y = G4RandGauss::shoot(0.0, 1.0);

  rand_dir_x = G4RandGauss::shoot(0.0, 1.0);
  rand_dir_y = G4RandGauss::shoot(0.0, 1.0);

  spot_x_dir = atan(SMP->GetSpots()[spot_number].spotx/SADx);
  spot_y_dir = atan(SMP->GetSpots()[spot_number].spoty/SADy);

  pos_x_iso = (rand_pos_x * sig_x)+SMP->GetSpots()[spot_number].spotx;
  pos_y_iso = (rand_pos_y * sig_y)+SMP->GetSpots()[spot_number].spoty;

  dir_x = tan((((corre_x*rand_pos_x)+ (1-(corre_x*corre_x))*rand_dir_x)*div_x)+ spot_x_dir);
  dir_y = tan((((corre_y*rand_pos_y)+ (1-(corre_y*corre_y))*rand_dir_y)*div_y)+ spot_y_dir);
  dir_z = 1; //- sqrt((dir_x*dir_x)+(dir_y*dir_y));

  pos_x = pos_x_iso + (pos_z*dir_x);
  pos_y = pos_y_iso + (pos_z*dir_y);

  fParticleGun->SetParticleEnergy(energy*MeV);
  fParticleGun->SetParticlePosition(G4ThreeVector(pos_x, pos_y, pos_z));
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(dir_x, dir_y, dir_z));
  // fParticleGun->SetParticlePosition(G4ThreeVector(SMP->GetSpots()[spot_number].spotx, SMP->GetSpots()[spot_number].spoty, pos_z));
  // fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0, 0, 1));
  fParticleGun->GeneratePrimaryVertex(anEvent);
}

// randomly
int PrimaryGeneratorAction::SpotSelector(){
 double relative_weight = G4UniformRand();
 double spot_weight = relative_weight*total_spots_weight;
 int i, spotN = 0;
 double cumulative_weight = 0;
 for(i=0; i<number_spots; i++)
  {
    cumulative_weight +=SMP->GetSpots()[i].weight;
    if(spot_weight<cumulative_weight){
      spotN = i;
      break;
    }
  }
 return spotN;
}

void PrimaryGeneratorAction::CalculateTotalWeight(){
  total_spots_weight = 0;
  number_spots = 0;
  for(int i = 0; i<(int)SMP->GetSpots().size(); i++){
    total_spots_weight = total_spots_weight + SMP->GetSpots()[i].weight;
    number_spots =  number_spots + 1;
  }
}

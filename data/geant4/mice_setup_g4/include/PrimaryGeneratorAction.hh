
#ifndef PrimaryGeneratorAction_h
#define PrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "SimulationParameters.hh"
#include "G4ParticleGun.hh"

class G4ParticleGun;
class G4Event;

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    PrimaryGeneratorAction(SimulationParameters* SMP);
    virtual ~PrimaryGeneratorAction();

    // method from the base class
    virtual void GeneratePrimaries(G4Event*);

    // method to access particle gun
    int GetBeamDistribution (std::string const& inString);
    const G4ParticleGun* GetParticleGun() const { return fParticleGun; }
    void CalculateTotalWeight();
    int  SpotSelector();

  private:
    G4ParticleGun*  fParticleGun; // pointer a to G4 gun class
    SimulationParameters* SMP;
    double pos_x, pos_y, pos_z, dir_x, dir_y, dir_z;
    double energy;
    double sig_x, sig_y, div_x, div_y, cov_x, cov_y, corre_x, corre_y;
    double SADx, SADy;
    double total_spots_weight;
    double number_spots;
    G4double rand_pos_x, rand_pos_y, rand_dir_x, rand_dir_y, spot_x_dir, spot_y_dir, pos_x_iso, pos_y_iso;
    int spot_number;
};

#endif

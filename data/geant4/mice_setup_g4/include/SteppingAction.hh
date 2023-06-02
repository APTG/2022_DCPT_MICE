
#ifndef SteppingAction_h
#define SteppingAction_h 1

#include "SimulationParameters.hh"
#include "G4UserSteppingAction.hh"
#include "G4EmCalculator.hh"
#include "RunAction.hh"


class SteppingAction : public G4UserSteppingAction
{
  public:
    SteppingAction(RunAction* runAction, SimulationParameters* aSMP);
    virtual ~SteppingAction();
    virtual void UserSteppingAction(const G4Step*);
    double GetBeta(double energy, double amass);
    double GetZeff(int z, double beta);

  private:
    RunAction* fRunAction;
    SimulationParameters* SMP;
    G4EmCalculator* emCal;

    G4String particleName;
    G4String watName;
    G4String matName;
    double particleCharge;
    double watDensity;
    double matDensity;
    double meanKE;
    double watSP;
    double matSP;
};
#endif

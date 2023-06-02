
#include "ActionInitialization.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "SteppingAction.hh"
// #include "G4EventManager.hh"


ActionInitialization::ActionInitialization(SimulationParameters* aSMP): G4VUserActionInitialization(), SMP (aSMP)
{}

ActionInitialization::~ActionInitialization()
{}

void ActionInitialization::BuildForMaster() const
{
    RunAction* runAction = new RunAction(SMP);
    SetUserAction(runAction);
}

void ActionInitialization::Build() const
{
  PrimaryGeneratorAction* PrimaryParticleGenerator = new PrimaryGeneratorAction(SMP);
  SetUserAction(PrimaryParticleGenerator);

  RunAction* runAction = new RunAction(SMP);
  SetUserAction(runAction);

  SteppingAction* steppingAction = new SteppingAction(runAction, SMP);
  SetUserAction(steppingAction);
}

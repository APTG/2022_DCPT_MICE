#ifndef ActionInitialization_h
#define ActionInitialization_h 1

#include "G4VUserActionInitialization.hh"
#include "SimulationParameters.hh"

/// Action initialization class.

class ActionInitialization : public G4VUserActionInitialization
{
  public:
    ActionInitialization(SimulationParameters* aSMP);
    virtual ~ActionInitialization();

    virtual void BuildForMaster() const;
    virtual void Build() const;

  private:
    SimulationParameters* SMP;
};
#endif

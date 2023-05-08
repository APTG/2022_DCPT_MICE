
#ifndef RunAction_h
#define RunAction_h 1

#include "G4UserRunAction.hh"
#include "SimulationParameters.hh"
#include "G4Accumulable.hh"
#include "G4Threading.hh"

using namespace std;
class G4Run;

class RunAction : public G4UserRunAction
{
  public:
    RunAction(SimulationParameters* aSP);
    virtual ~RunAction();

    // virtual G4Run* GenerateRun();
    virtual void   BeginOfRunAction(const G4Run*);
    virtual void   EndOfRunAction  (const G4Run*);


  private:
    SimulationParameters* SMP;
};

#endif

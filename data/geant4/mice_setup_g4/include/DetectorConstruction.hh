
#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "SimulationParameters.hh"
#include "G4UserLimits.hh"


/// Detector construction class to define materials and geometry.
class DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    DetectorConstruction(SimulationParameters* aSMP);
    virtual ~DetectorConstruction();
    virtual G4VPhysicalVolume* Construct();

    G4VPhysicalVolume* ConstructWorldVolume();
    G4VPhysicalVolume* ConstructAirVolume(G4LogicalVolume* MotherVolume);
    G4VPhysicalVolume* ConstructContainer(G4LogicalVolume* MotherVolume);
    G4VPhysicalVolume* ConstructWater(G4LogicalVolume* MotherVolume);
    G4VPhysicalVolume* ConstructLid(G4LogicalVolume* MotherVolume);
    G4VPhysicalVolume* ConstructBarCollimator(G4LogicalVolume* MotherVolume);

  private:
    G4UserLimits*   StepLimit;
    vector<pro_cut> ProCut;
    SimulationParameters* SMP;
    double shift;

  protected:
    G4LogicalVolume*  fScoringVolume;
};
#endif

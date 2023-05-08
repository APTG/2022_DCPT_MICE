
#include "SteppingAction.hh"
#include "G4Step.hh"
#include "G4StepPoint.hh"
#include "G4EventManager.hh"
#include "G4SystemOfUnits.hh"
#include "Analysis.hh"
#include "G4NistManager.hh"

SteppingAction::SteppingAction(RunAction* runAction, SimulationParameters* aSMP)
    :G4UserSteppingAction(), fRunAction(runAction), SMP(aSMP)
    {
      emCal = new G4EmCalculator();
    }

SteppingAction::~SteppingAction()
    {
      delete emCal;
    }

void SteppingAction::UserSteppingAction(const G4Step* step)
    {
      Analysis* myana = Analysis::GetAnalysis();
      scored_quatity SDL;
      double watDoseFactor =1, watEnergyFactor =1, watSPFactor = 1;

      // if (step->GetPostStepPoint()->GetTouchableHandle()->GetVolume()->GetMotherLogical()==nullptr)
      // {
      //    step->GetTrack()->SetTrackStatus(fStopAndKill);
      //    return;
      // }

      particleName     = step->GetTrack()->GetDynamicParticle()->GetDefinition()->GetParticleName();
      particleCharge   = step->GetTrack()->GetDynamicParticle()->GetDefinition()->GetPDGCharge();
      watName          = G4NistManager::Instance()->FindOrBuildMaterial("G4_WATER")->GetName();
      matName          = step->GetPreStepPoint()->GetMaterial()->GetName();
      watDensity       = G4NistManager::Instance()->FindOrBuildMaterial("G4_WATER")->GetDensity()/(kg/m3);
      matDensity       = step->GetPreStepPoint()->GetMaterial()->GetDensity()/(kg/m3);

      meanKE           = (step-> GetPreStepPoint()->GetKineticEnergy() + step-> GetPostStepPoint()->GetKineticEnergy())/2;
      watSP            = emCal->ComputeElectronicDEDX(meanKE, particleName, watName, 0.01);//DBL_MAX);
      matSP            = emCal->ComputeElectronicDEDX(meanKE, particleName, matName, 0.01);//DBL_MAX);
      watDoseFactor    = (watSP/watDensity)*(matDensity/matSP);
      watEnergyFactor  = (watSP/matSP);
      watSPFactor      = (watSP/matSP);

      if (watDoseFactor == watDoseFactor){
        SDL.WatDoseFactor     = watDoseFactor;
        SDL.WatEnergyFactor   = watEnergyFactor;
        SDL.WatSPFactor       = watSPFactor;
      }

      else{
        SDL.WatDoseFactor     = 1;
        SDL.WatEnergyFactor   = 1;
        SDL.WatSPFactor       = 1;
      }

      SDL.EventID  = G4EventManager::GetEventManager()->GetConstCurrentEvent()->GetEventID();
      // Get TrackID (for primary particle TrackID==1)
      SDL.TrackID = step->GetTrack()->GetTrackID();
      // Get the parentID: if not 0 then particle is a secondary
      SDL.ParentID = step->GetTrack()->GetParentID();

      SDL.PreStepPosition = step->GetPreStepPoint()->GetPosition();

      SDL.PostStepPosition = step->GetPostStepPoint()->GetPosition();

      SDL.EnergyDepositPoint = (G4UniformRand()*(step->GetPostStepPoint()->GetPosition()-step->GetPreStepPoint()->GetPosition())
                                + step->GetPreStepPoint()->GetPosition());

      SDL.StepInitialKE = step-> GetPreStepPoint()->GetKineticEnergy();

      SDL.StepFinalKE = step-> GetPostStepPoint()->GetKineticEnergy();

      SDL.TotalSecondaryEnergy = (step->GetPreStepPoint()->GetKineticEnergy() - step->GetPostStepPoint()->GetKineticEnergy()
                                  - step->GetTotalEnergyDeposit());

      SDL.EnergyDeposit = step->GetTotalEnergyDeposit();

      SDL.StepLength = step->GetStepLength();

      SDL.StoppingPower = matSP;

      SDL.WatStoppingPower = watSP;

      SDL.ParticleCharge = particleCharge;

      SDL.MaterialDensity = step->GetPreStepPoint()->GetMaterial()->GetDensity()/(kg/m3);

      SDL.ParticleName = step->GetTrack()->GetDynamicParticle()->GetDefinition()->GetParticleName();

      if(SDL.ParentID == 0 && SDL.TrackID == 1){
        SDL.ParticleGenType = 1;
      }

      else{
        SDL.ParticleGenType = 2;
      }

      SDL.ParticlePDGcode = step->GetTrack()->GetDynamicParticle()->GetDefinition()->GetPDGEncoding();

      SDL.ProcessName = step->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName();

      SDL.ProcessType = step->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessType();

      SDL.ProcessSubType = step->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessSubType();
      myana->Fill(SDL);
    }

double SteppingAction::GetBeta(double energy, double amass) {
  return sqrt(1.0 - 1.0 / ( ((energy / amass) + 1) * ((energy / amass) + 1) ));
}

double SteppingAction::GetZeff(int z, double beta) {
    return z * (1.0 - exp(-125.0 * beta * pow(abs(z), -2.0/3.0)));
}

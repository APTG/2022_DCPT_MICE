
#include  "SimulationParameters.hh"
#include  "DetectorConstruction.hh"
#include  "ActionInitialization.hh"
#include  "G4PhysListFactory.hh"
#include  "G4StepLimiterPhysics.hh"
#include  "G4HadronicProcessStore.hh"

#include  "G4SystemOfUnits.hh"
#include  "G4RunManagerFactory.hh"
#include  "G4UImanager.hh"
#include  "QBBC.hh"
#include  "G4VisExecutive.hh"
#include  "G4UIExecutive.hh"
#include  "G4UserSpecialCuts.hh"

using namespace std;

int main(int argc,char** argv)
{

  SimulationParameters* SMP = new SimulationParameters(argc, argv);
  SMP->PrintInititalParameters();

  // Set the Random engine
  // The following guarantees random generation also for different runs
  // in multithread
  CLHEP::RanluxEngine defaultEngine( 1234567, 4 );
  G4Random::setTheEngine( &defaultEngine );
  G4int seed = (G4int) time( NULL );
  G4Random::setTheSeed( seed );


  // Construct the default run manager
  #ifdef G4MULTITHREADED
  G4MTRunManager *runManager = new G4MTRunManager();
    runManager->SetNumberOfThreads(SMP->GetSetupParameters().n_thread);
  #else
    G4RunManager* runManager = new G4RunManager();
  #endif

  // G4HadronicProcessStore::Instance()->SetVerbose(0);
  // Set mandatory initialization classes
  runManager->SetUserInitialization(new DetectorConstruction(SMP));

  G4PhysListFactory physListFactory;
  const G4String phylistname = "QGSP_BIC_HP_EMY";
  G4VModularPhysicsList* physicsList = physListFactory.GetReferencePhysList(phylistname);
  G4StepLimiterPhysics* stepLimitPhys = new G4StepLimiterPhysics();
  if(SMP->GetPhysicsParameters().use_sl_neutral){
    stepLimitPhys->SetApplyToAll(true);
  }
  runManager->SetUserInitialization(physicsList);
  physicsList->RegisterPhysics(stepLimitPhys);
  ActionInitialization* ActionInitializer = new ActionInitialization(SMP);
  runManager->SetUserInitialization(ActionInitializer);


  G4UImanager* UImanager = G4UImanager::GetUIpointer();
  if (SMP->GetSetupParameters().use_gui)
  {
    // Initialize visualization
    G4UIExecutive* ui = new G4UIExecutive(argc, argv);
    G4VisManager* visManager = new G4VisExecutive;
    // G4VisManager* visManager = new G4VisExecutive("Quiet");
    visManager->SetVerboseLevel(0);
    visManager->Initialize();
    UImanager->ApplyCommand("/control/macroPath /home/fardous/PhD/Projects/Personal/Proton_Irradiation/proton-irradiation");
    UImanager->ApplyCommand("/control/execute init_vis.mac");
    // system("clear");
    ui->SessionStart();
    delete visManager;
    delete ui;
  }

  else
  {
    G4String ProgressCounter = "/run/printProgress " + to_string(SMP->GetSetupParameters().n_progress);
    G4String beamOn = "/run/beamOn " + to_string(SMP->GetSetupParameters().n_particle);
    UImanager->ApplyCommand("/run/initialize");
    UImanager->ApplyCommand(ProgressCounter);
    UImanager->ApplyCommand(beamOn);
  }

  delete runManager;
  SMP->PrintInititalParameters();
  delete SMP;

}

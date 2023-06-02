
#include "RunAction.hh"
#include "Analysis.hh"

RunAction::RunAction(SimulationParameters* aSMP) : G4UserRunAction()
{
    SMP = aSMP;
    Analysis* myana = Analysis::GetAnalysis();
    myana->SetAnalysis(SMP);
    myana->Book();

}

RunAction::~RunAction()
{

}

void RunAction::BeginOfRunAction(const G4Run* run)
{
    Analysis* myana = Analysis::GetAnalysis();
    myana->Open();
}

void RunAction::EndOfRunAction(const G4Run* run)
{
    Analysis* myana = Analysis::GetAnalysis();
    myana->Save();
    myana->Close();
}

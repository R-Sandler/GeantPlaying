// NE697
#include "runaction.hpp"
#include "run.hpp"
// Geant4
#include "G4RunManager.hh"
// std

/* Constructor. */
RunAction::RunAction():
  G4UserRunAction()
{
  G4cout << "Creating RunAction...\n";
  G4cout << "...done.\n" << G4endl;
}

/* Destructor. */
RunAction::~RunAction() {
  G4cout << "Deleting RunAction...\n";
  G4cout << "...done.\n" << G4endl;
}

/* Generate a run object for the G4RunManager. */
G4Run* RunAction::GenerateRun() {
  return new Run;
}

/* Called at the beginning of a run, ie when the user puts in /run/beamOn.
 * */
void RunAction::BeginOfRunAction(const G4Run* r) {
  // Make it clear we're starting a run
  // Number of events specified by the user
  auto nevents = r->GetNumberOfEventToBeProcessed();
  G4cout << "******************************" << G4endl;
  G4cout << "********* RUN BEGIN **********" << G4endl;
  G4cout << "******************************" << G4endl;
  G4cout << "Number of events for run: " << nevents << G4endl;
  
  // Tell the Run to open the file. The function takes a G4Run, but we need
  // the Run object functionality, so grab a mutable copy from the
  // G4RunManager
  auto run_man = G4RunManager::GetRunManager();
  auto curr_run = dynamic_cast<Run*>(run_man->GetNonConstCurrentRun());
  curr_run->openFile();
  return;
}

/* Called at the end of a run. Required by Geant4. */
void RunAction::EndOfRunAction(const G4Run* r) {
  // Make it clear we're done
  G4cout << "******************************" << G4endl;
  G4cout << "********** RUN END ***********" << G4endl;
  G4cout << "******************************" << G4endl;
  G4cout << "Number of events processed: " << r->GetNumberOfEvent()
    << G4endl;

  // Close the txt file we opened for the Hits
  auto run_man = G4RunManager::GetRunManager();
  auto curr_run = dynamic_cast<Run*>(run_man->GetNonConstCurrentRun());
  curr_run->closeFile();
  return;
}

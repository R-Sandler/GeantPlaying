/* RunAction: manages Run objects, generating them for the G4RunManager,
 * and executing Begin and End of Run actions. */
#pragma once
// NE697
// Geant4
#include "G4UserRunAction.hh"
#include "G4Run.hh"
// std

class RunAction: public G4UserRunAction {
  public:
    RunAction();
    ~RunAction();

    G4Run* GenerateRun();
    void   BeginOfRunAction(const G4Run* r);
    void   EndOfRunAction(const G4Run* r);
};

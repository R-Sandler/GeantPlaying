/* EventAction: controls what happens at the beginning and end of the
 * G4Event. */
#pragma once
// NE697
// Geant4
#include "G4UserEventAction.hh"
#include "G4Event.hh"
// std

class EventAction: public G4UserEventAction {
  public:
    EventAction();
    ~EventAction();

    void BeginOfEventAction(const G4Event*);
    void EndOfEventAction(const G4Event* e);
};

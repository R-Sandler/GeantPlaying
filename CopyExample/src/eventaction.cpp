// NE697
#include "eventaction.hpp"
#include "run.hpp"
#include "detectorhit.hpp"
// Geant4
#include "G4SDManager.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"
// std

/* Constructor. */
EventAction::EventAction():
  G4UserEventAction()
{
  G4cout << "Creating EventAction...\n";
  G4cout << "...done.\n" << G4endl;
}

/* Destructor. */
EventAction::~EventAction() {
  G4cout << "Deleting EventAction...\n";
  G4cout << "...done.\n" << G4endl;
}

/* Called by Geant4 when an event is generated. Nothing for us to do here.
 * */
void EventAction::BeginOfEventAction(const G4Event*) {
  return;
}

/* Called by Geant4 when an event is terminated. The G4Event keeps track of
 * all interactions, tracks, secondary particles etc. When the event dies
 * (the last surviving daughter particle stops or dies), this is where
 * we tally everything and tell the Run object. */
void EventAction::EndOfEventAction(const G4Event* e) {
  auto nevent = e->GetEventID();
  if ((nevent % 1000) == 0) {
    G4cout << "Event " << nevent << " terminated. Tabulating..."
      << G4endl;
  }

  // Process the hits collection for this event
  auto sd_man = G4SDManager::GetSDMpointer();
  auto run_man = G4RunManager::GetRunManager();
  auto run = dynamic_cast<Run*>(run_man->GetNonConstCurrentRun());

  // Grab the HitsCollection from this G4Event by name, make sure we have
  // something valid, then iterate over it to grab the DetectorHit objects
  auto hcID = sd_man->GetCollectionID("detector_sdHC");
  if (hcID == -1) {
    G4cerr << "Could not get collection ID for the PMT hits collection."
      << G4endl;
    return;
  }
  auto hce = e->GetHCofThisEvent();
  if (!hce) {
    G4cerr << "No hits collection for this event. hcID=" << hcID
      << G4endl;
    return;
  }
  auto hc = (G4THitsCollection<DetectorHit>*)hce->GetHC(hcID);
  if (!hc) {
    G4cerr << "Failed to grab HC from HCoE, somehow!!" << G4endl;
    return;
  }
  // Take all of the hits for this event and send them to the Run
  for (int i=0;i < hc->entries();i++) {
    // Welcome to C++: hc is a pointer to a vector full of pointers to
    // DetectorHit objects, so we first dereference with (*hc), then
    // access the element index like an array, where each element is a
    // pointer, so we use the -> to access its members
    // Same as DetectorHit* dethit = (*hc)[i];
    // Alternatively: DetectorHit* dethit = hc->at(i);
    auto dethit = (*hc)[i];
    // We ignore the y-dimension, which is the depth, for simplicity
    // Also note that we divide the units out
    double x = dethit->getPosition().x() / cm;
    double z = dethit->getPosition().z() / cm;
    double e = dethit->getEnergyDeposited() / keV;
    // getProcessName() returns a G4String, and we need a std::string, so
    // we get the raw char* string, which is converted to std::string
    // Once again, welcome to C++
    string proc = dethit->getProcessName().data();
    // Record only photoelectric and Compton events
    //if ((proc == "phot") || (proc == "compt")) {
      run->writeHit(x, z, e, proc);
    //}
  }
  return;
}

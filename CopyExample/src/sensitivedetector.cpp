// NE697
#include "sensitivedetector.hpp"
// Geant4
#include "G4VProcess.hh"
#include "G4SystemOfUnits.hh"

/* Constructor. Boilerplate, borrowed from an example. */
SensitiveDetector::SensitiveDetector(const G4String& name):
  // Initialize the base object with the name of the sensitive detector
  // The name is kept in the SensitiveDetectorName variable
  G4VSensitiveDetector(name),
  collectionID(-1),
  hitsCollection(nullptr)
{
  // Add a hits collection name to the collectionName list (defined in
  // G4VSensitiveDetector). We will use this name to retrieve the
  // HitsCollection later in the EventAction
  G4String hcname = name + "HC";
  collectionName.insert(hcname);
}

/* Required by Geant4. Sets the HitsCollection ID, allocates memory for
 * it, and passes it on to Geant4 for management. This is called for every
 * G4Event (in our case, every photon) generated. */
void SensitiveDetector::Initialize(G4HCofThisEvent* hc) {
  // Get the next collection ID
  if (collectionID < 0) {
    collectionID = GetCollectionID(0);
  }
  // Allocate the HitsCollection object. Note that this is just a typedef
  // (alias) for G4THitsCollection<DetectorHit>, which we defined in
  // detectorhit.hpp
  hitsCollection = new DetectorHitsCollection(SensitiveDetectorName,
                                              collectionName[0]);
  // By adding the newly allocated object to the G4HCofThisEvent, Geant4
  // will take responsibility for deleting it
  hc->AddHitsCollection(collectionID, hitsCollection);
  return;
}

/* This is the workhorse function - at each step, Geant4 check if there was
 * an interaction. If so, this function is called, so this is where we want
 * to add to the HitsCollection (like a tally in MCNP). */
G4bool SensitiveDetector::ProcessHits(G4Step* step, G4TouchableHistory*) {
  // Allocate a new hit for this interaction
  auto new_hit = new DetectorHit();

  // The step is split into two "points" - the pre- and post- step. For
  // most interactions these are the same point in space (need to confirm)
  // but, for instance, the energy will be different between the two if
  // the particle deposited some or all of it
  auto pre_step = step->GetPreStepPoint();
  auto post_step = step->GetPostStepPoint();
  // Get the process
  auto proc_step = post_step->GetProcessDefinedStep();

  // Record the interaction properties
  new_hit->setPosition(pre_step->GetPosition());
  G4double edep = pre_step->GetTotalEnergy()
                  - post_step->GetTotalEnergy();
  new_hit->setEnergyDeposited(edep);
  new_hit->setProcessName(proc_step->GetProcessName());
  G4cout << "***** HIT *****" << G4endl;
  G4cout << "Process: " << proc_step->GetProcessName() << G4endl;
  G4cout << "Position: " << new_hit->getPosition() / cm << G4endl;
  G4cout << "EnergyDeposited: " << new_hit->getEnergyDeposited() / keV
    << G4endl;

  // Add it to the list of hits - the HitsCollection, aka the tally - in
  // this volume
  hitsCollection->insert(new_hit);

  // I don't believe this boolean is ever used (probably a holdover from a
  // previous version, kept to maintain compatibility)
  // I'm an optimist so we set it to true
  return true;
}

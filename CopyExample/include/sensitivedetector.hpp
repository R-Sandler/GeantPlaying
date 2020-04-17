/* SensitiveDetector: this is the recommended mechanism for tracking
 * particle hits in a volume - think of it as just another piece to a
 * volumetric definition, like the Logical or Physical volumes. Note that
 * hit tracking can also be done in the SteppingAction and elsewhere,
 * however additional functionality can be used (such as hit filters) if
 * SensitiveDetectors are used. This method is also likely faster than
 * the others.
 * 
 * The process goes something like this: a G4Event (in our case, a single
 * photon emission - defined in the PrimaryGeneratorAction) is created. As
 * it traverses the geometry, it will check if there is a SensitiveDetector
 * defined for the volume. If there is, Initialize() is called, creating
 * a HitsCollection. As the particle bounces around, each interaction
 * triggers a call to ProcessHits(), which will add a DetectorHit to the
 * collection in the way we specify. When the G4Event dies,
 * EventAction::EndOfEventAction() is called, which is where we collect
 * all of the hits and do whatever we like, such as write them out to
 * file.
 *
 * The trickiest part to understand here, especially if you're coming from
 * MCNP, is that the tally *moves with the event* rather than necessarily
 * being tied to the volume. The G4Event will pick up HitCollections from
 * other volumes as it moves through them! */
#pragma once
// NE697
#include "detectorhit.hpp"
// Geant4
#include "G4VSensitiveDetector.hh"
// std

class SensitiveDetector: public G4VSensitiveDetector {
  public:
    SensitiveDetector(const G4String& name);

    void   Initialize(G4HCofThisEvent* hc);
    G4bool ProcessHits(G4Step* step, G4TouchableHistory*);

  private:
    G4int                   collectionID;
    DetectorHitsCollection* hitsCollection;
};

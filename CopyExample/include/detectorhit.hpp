/* DetectorHit: collection of information about a particle interaction
 * in a SensitiveDetector volume. Populated by the SensitiveDetector class.
 * Uses Geant4 types to ensure units are propagated correctly. The
 * structure of the class and defined operators are required by Geant4. */
#pragma once
// NE697
// Geant4
#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
// std

class DetectorHit: public G4VHit {
  public:
    DetectorHit(); 

    // Getters and setters
    inline const G4ThreeVector& getPosition() const {
      return position;
    }
    inline void                 setPosition(const G4ThreeVector& p) {
      position = p;
      return;
    }
    inline const G4double&      getEnergyDeposited() const {
      return energyDeposited;
    }
    inline void                 setEnergyDeposited(const G4double& e) {
      energyDeposited = e;
      return;
    }
    inline const G4String&      getProcessName() const {
      return processName;
    }
    inline void                 setProcessName(const G4String& n) {
      processName = n;
      return;
    }

    // Other necessary overrides
    inline void* operator new(size_t);
    inline void  operator delete(void* aHit);
    inline G4int operator ==(const DetectorHit& right) const {
      return (this == &right) ? 1 : 0;
    }

  private:
    G4ThreeVector position;
    G4double      energyDeposited;
    G4String      processName;
};

// Collection and allocator for custom Hit
typedef G4THitsCollection<DetectorHit> DetectorHitsCollection;
extern G4Allocator<DetectorHit> DetectorHitAllocator;

// Inline functions that rely on DetectorHitAllocator
inline void* DetectorHit::operator new(size_t) {
  void* aHit;
  aHit = (void*)DetectorHitAllocator.MallocSingle();
  return aHit;
}
inline void DetectorHit::operator delete(void* aHit) {
  DetectorHitAllocator.FreeSingle((DetectorHit*)aHit);
  return;
}

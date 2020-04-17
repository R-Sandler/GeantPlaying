// NE697
#include "detectorhit.hpp"
// Geant4
// std

// Required to avoid "undefined reference to NCC::DetectorHitAllocator"
// compilation error
G4Allocator<DetectorHit> DetectorHitAllocator;

/* Constructor. */
DetectorHit::DetectorHit():
  G4VHit(),
  position(G4ThreeVector()),
  energyDeposited(0.0),
  processName("")
{
}

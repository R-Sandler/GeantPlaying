/* DetectorConstruction: create all physical volumes and experimental
 * space. */
#pragma once
// NE697
#include "detector.hpp"
#include "geometrymessenger.hpp"
// Geant4
#include "G4VUserDetectorConstruction.hh"
// std

// We forward-declare the GM because of a sort of circular dependency
// problem: the DC needs to know about the GeometryMessenger, and the
// GeometryMessenger needs to know about the DetectorConstruction
class GeometryMessenger;
class DetectorConstruction: public G4VUserDetectorConstruction {
  public:
    DetectorConstruction();
    ~DetectorConstruction();

    Detector* getDetector();

    // Assemble detector geometry: required by Geant4
    G4VPhysicalVolume* Construct();

    void reloadGeometry();

  private:
    Detector*          detector;
    GeometryMessenger* messenger;
};

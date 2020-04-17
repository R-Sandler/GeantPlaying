/* Detector: keeps track of the NaI detector properties such as position
 * and dimensions. We do this so we can pass a pointer to the Detector
 * object to the GeometryMessenger for the UI commands. */
#pragma once
// NE697
#include "sensitivedetector.hpp"
// Geant4
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4VisAttributes.hh"
// std

class Detector {
  public:
    Detector(const G4String& n);
    ~Detector();

    const G4ThreeVector& getPosition() const;
    void                 setPosition(const G4ThreeVector& p);
    const G4ThreeVector& getDimensions() const;
    void                 setDimensions(const G4ThreeVector& d);

    void                 build(G4LogicalVolume* world_log);

  private:
    G4String      name;
    G4ThreeVector position;
    G4ThreeVector dimensions;

    G4Box*             geometry;
    G4LogicalVolume*   logical;
    G4PVPlacement*     physical;
    G4VisAttributes*   visAttributes;
    SensitiveDetector* sensitiveDetector;
};

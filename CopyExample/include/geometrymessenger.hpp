/* GeometryMessenger: used to communicate between the geometric objects
 * and the Geant4 UI command line. */
#pragma once
// NE697
#include "detectorconstruction.hpp"
// Geant4
#include "G4UImessenger.hh"
#include "G4UIcmdWithABool.hh"
#include "G4UIcmdWith3VectorAndUnit.hh"
// std

// We forward-declare the DC because of a sort of circular dependency
// problem: the DC needs to know about the GeometryMessenger, and the
// GeometryMessenger needs to know about the DetectorConstruction
class DetectorConstruction;
class GeometryMessenger: public G4UImessenger {
  public:
    // We take the DC instead of just the Detector so we can call the
    // function to completely rebuild the geometry (calls Construct()
    // again). Then we can just get the Detector from the
    // DetectorConstruction when we need it
    GeometryMessenger(DetectorConstruction* dc);
    ~GeometryMessenger();

    // Required by Geant4
    void     SetNewValue(G4UIcommand* cmd, G4String val);
    G4String GetCurrentValue(G4UIcommand*);

  private:
    DetectorConstruction* detectorConstruction;

    G4UIdirectory*             directory;
    G4UIcmdWithABool*          reloadCmd;
    G4UIcmdWith3VectorAndUnit* positionCmd;
    G4UIcmdWith3VectorAndUnit* dimensionsCmd;
};

// NE697
#include "geometrymessenger.hpp"
// Geant4
// std

/* Constructor. This is where we build the commands. */
GeometryMessenger::GeometryMessenger(DetectorConstruction* dc):
  G4UImessenger(),
  detectorConstruction(dc)
{
  G4cout << "Creating GeometryMessenger...\n";
  // Directory: /ne697/geometry
  directory = new G4UIdirectory("/ne697/geometry");
  directory->SetGuidance("Modify the geometry.");

  // Reload the geometry: /ne697/geometry/reload true
  reloadCmd = new G4UIcmdWithABool("/ne697/geometry/reload", this);
  reloadCmd->SetGuidance("Reload the geometry.");
  // The second argument is whether or not the value of the parameter is
  // ommitable, ie., can you just type /ne697/geometry/reload
  // We want to force the user to type true after to confirm that they
  // really want to reload the geometry
  reloadCmd->SetParameterName("reload", false);
  // This isn't totally necessary, but an extra safety to make sure we don't
  // somehow reload the geometry during a run
  reloadCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

  // Detector position: /ne697/geometry/detector/position
  positionCmd = new G4UIcmdWith3VectorAndUnit("/ne697/geometry/detector/"
                                              "position", this);
  positionCmd->SetGuidance("Detector position (x, y, z)");
  positionCmd->SetParameterName("x", "y", "z", false);
  auto det = detectorConstruction->getDetector();
  positionCmd->SetDefaultValue(det->getPosition());
  positionCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

  // Detector dimensions: /ne697/geometry/detector/dimensions
  dimensionsCmd = new G4UIcmdWith3VectorAndUnit("/ne697/geometry/detector/"
                                                "dimensions", this);
  dimensionsCmd->SetGuidance("Detector dimensions (x, y, z)");
  dimensionsCmd->SetParameterName("x", "y", "z", false);
  dimensionsCmd->SetDefaultValue(det->getDimensions());
  dimensionsCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
  G4cout << "...done" << G4endl;
}

/* Destructor. */
GeometryMessenger::~GeometryMessenger() {
  delete directory;
  delete reloadCmd;
  delete positionCmd;
  delete dimensionsCmd;
}

/* When the user tries to set a new value using one of the commands we
 * defined above, this function gets called. */
void GeometryMessenger::SetNewValue(G4UIcommand* cmd, G4String val) {
  // Check which command they used
  if (cmd == reloadCmd) {
    // Make sure they put true!
    if (reloadCmd->GetNewBoolValue(val)) {
      detectorConstruction->reloadGeometry();
    }
  } else if (cmd == positionCmd) {
    // Set the position. It'll handle the units for us, so don't even
    // worry about it
    auto user_pos = positionCmd->GetNew3VectorValue(val);
    detectorConstruction->getDetector()->setPosition(user_pos);
    G4cout << "Detector position set to "
      << positionCmd->ConvertToString(user_pos, "cm") << G4endl;
  } else if (cmd == dimensionsCmd) {
    auto user_dim = dimensionsCmd->GetNew3VectorValue(val);
    detectorConstruction->getDetector()->setDimensions(user_dim);
    G4cout << "Detector dimensions set to "
      << dimensionsCmd->ConvertToString(user_dim, "cm") << G4endl;
  }
  return;
}

/* This is supposed to be called when the user inputs a command without
 * arguments, but I haven't gotten it to really work properly, and since
 * we set the omittable flag for the commands to false, it definitely
 * won't ever be called. */
G4String GeometryMessenger::GetCurrentValue(G4UIcommand*) {
  return G4String("");
}

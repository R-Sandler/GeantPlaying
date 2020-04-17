// NE697
#include "detector.hpp"
// Geant4
#include "G4SystemOfUnits.hh"
#include "G4NistManager.hh"
#include "G4SDManager.hh"
// std

/* Constructor. Set the initial position, dimensions, and vis attributes.
 * */
Detector::Detector(const G4String& n):
  name(n),
  // Default position/dimensions are the same as what we had in the
  // DetectorConstruction
  position(0, 50.0*cm + 2.5*cm, 0),
  dimensions(50.0*cm, 5.0*cm, 50.0*cm),
  geometry(nullptr),
  logical(nullptr),
  physical(nullptr),
  visAttributes(nullptr),
  sensitiveDetector(nullptr)
{
  G4cout << "Creating Detector " << name << "...\n";
  visAttributes = new G4VisAttributes;
  visAttributes->SetColour(G4Colour::White());
  visAttributes->SetForceSolid(true);
  G4cout << "...done" << G4endl;
}

/* Destructor. */
Detector::~Detector() {
  delete visAttributes;
}

/* Accessors for the position and dimensions so we can change them from the
 * GeometryMessenger. */
const G4ThreeVector& Detector::getPosition() const {
  return position;
}

void Detector::setPosition(const G4ThreeVector& p) {
  position = p;
  return;
}

const G4ThreeVector& Detector::getDimensions() const {
  return dimensions;
}

void Detector::setDimensions(const G4ThreeVector& d) {
  dimensions = d;
  return;
}

/* Construct the detector volume. This is pretty much a copy/paste of what
 * was originally in the DetectorConstruction::Construct() function for
 * the detector portion. */
void Detector::build(G4LogicalVolume* world_log) {
  G4cout << "Building " << name << " volume...\n";
  // Solid/geometric volume
  auto gname = name + "_geom";
  geometry = new G4Box(gname,
                       dimensions.x() / 2.0,
                       dimensions.y() / 2.0,
                       dimensions.z() / 2.0);

  // Logical volume (material)
  auto lname = name + "_log";
  auto dmat =
    G4NistManager::Instance()->FindOrBuildMaterial("G4_ANTHRACENE");
  logical = new G4LogicalVolume(geometry,
                                dmat,
                                lname);
  logical->SetVisAttributes(visAttributes);
  // Attach the sensitive detector. The build function might be called
  // multiple times if we move the detector around, so we delete the old
  // sensitive detector to make sure we're starting from scratch
  delete sensitiveDetector;
  auto sdman = G4SDManager::GetSDMpointer();
  auto sdname = name + "_sd";
  sensitiveDetector = new SensitiveDetector(sdname);
  sdman->AddNewDetector(sensitiveDetector);
  // Here is where we actually connect the SD to the logical volume
  // NOTE: there will be a warning that there was already a sensitive
  // detector by this name. As long as we delete the old one ourselves
  // (performed above), it's not a problem.
  logical->SetSensitiveDetector(sensitiveDetector);

  // Physical volume: rotation, position, etc
  auto pname = name + "_phys";
  physical = new G4PVPlacement(nullptr,
                               position,
                               logical,
                               pname,
                               world_log,
                               false,
                               true);
  G4cout << "...done." << G4endl;
  return;
}

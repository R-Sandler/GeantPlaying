#include "SEDetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Tubs.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"


SEDetectorConstruction::SEDetectorConstruction()
: G4VUserDetectorConstruction(),
  fScoringVolume(0)
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SEDetectorConstruction::~SEDetectorConstruction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* SEDetectorConstruction::Construct()
{
  //Create a cube for the world
  G4double world_hx = 3.0*m;
  G4double world_hy = 2.0*m;
  G4double world_hz = 1.0*m;

  G4Box* worldBox = new G4Box("World", world_hx, world_hy, world_hz);

  //Create a cylinder
  G4double innerRadius = 0.*cm;
  G4double outerRadius = 60.*cm;
  G4double h_z = 25.*cm;
  G4double startAngle = 0.*deg;
  G4double spanningAngle = 360.*deg;

  G4Tubs* trackerTube = new G4Tubs("Tracker", innerRadius, outerRadius, h_z, startAngle, spanningAngle);

  //Use the box and cylinder to create logical volumes
  //World box is argon, cylinder is aluminum
  G4LogicalVolume* worldLog = new G4LogicalVolume(worldBox, Ar, "World");
  G4LogicalVolume* trackerLog = new G4LogicalVolume(trackerTube, Al, "Tracker");

  //Place the world, creating its physical volumes
  G4VPhysicalVolume* physWorld = new G4PVPlacement(0, G4ThreeVector(), worldLog, "World", 0, false, 0, checkOverlaps);

  //Place the tracker in the world
  G4double pos_x = -1.0*meter;
  G4double pos_y = 0.0*meter;
  G4double pos_z = 0.0*meter;

  G4VPhysicalVolume* trackerPhys = new G4PVPlacement(0, G4ThreeVector(pos_x, pos_y, pos_z), trackerLog, "Tracker", worldLog, false, 0);


return physWorld;
}

// NE697
#include "detectorconstruction.hpp"
// Geant4
#include "G4SystemOfUnits.hh"
#include "G4Box.hh"
#include "G4NistManager.hh"
#include "G4LogicalVolume.hh"
#include "G4VisAttributes.hh"
#include "G4PVPlacement.hh"
#include "G4Orb.hh"
#include "G4GeometryManager.hh"
#include "G4SolidStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4RunManager.hh"
#include "G4VVisManager.hh"
#include "G4UImanager.hh"
// std

/* Constructor. */
DetectorConstruction::DetectorConstruction():
  G4VUserDetectorConstruction(),
  // Allocate the new Detector object here so we can pass the pointer to
  // the UI messenger
  detector(new Detector("detector")),
  messenger(new GeometryMessenger(this))
{
  G4cout << "Creating DetectorConstruction...\n";
  G4cout << "...done.\n" << G4endl;
}

/* Destructor. */
DetectorConstruction::~DetectorConstruction() {
  G4cout << "Deleting DetectorConstruction...\n";
  delete messenger;
  delete detector;
  G4cout << "...done.\n" << G4endl;
}

/* Get a pointer to the Detector - needed for the GeometryMessenger. */
Detector* DetectorConstruction::getDetector() {
  return detector;
}

/* Assemble all volumes. Must return the outermost volume (the
 * experimental hall). */
G4VPhysicalVolume* DetectorConstruction::Construct() {
  // Create the simulation world: a 5x5x5 m^3 box of air
  // Note that Geant4 lets us use units - multiply to add units, divide
  // to pull them out
  G4double world_x_len = 5.0*m;
  G4double world_y_len = world_x_len;
  G4double world_z_len = world_x_len;

  // The geometric volume - just shape and size information
  // Note that usually Geant4 takes half-dimensions
  auto world_geom = new G4Box("world_geom", // name
                               world_x_len / 2.0, // x-extent/2
                               world_y_len / 2.0, // y-extent/2
                               world_z_len / 2.0);// z-extent/2

  // Geant4 has a database of NIST-defined materials which will work for
  // most cases
  auto nist_man = G4NistManager::Instance();
  auto mat_air = nist_man->FindOrBuildMaterial("G4_AIR");
  // The logical volume
  auto world_log = new G4LogicalVolume(world_geom, // my geometric volume
                                       mat_air, // material
                                       "world_log"); // name

  // Can set all sorts of things like the color, etc, but we want the
  // outmost volume to be invisible so we can see the components
  world_log->SetVisAttributes(G4VisAttributes::Invisible);

  // The physical volume - rotation, position, and connection to this
  // object's logical volume and the logical volume of the mother (outside)
  // volume, in this case 0 since this is the outermost
  auto world_phys = new G4PVPlacement(nullptr, // rotation
                                      G4ThreeVector(0, 0, 0), // position
                                      world_log, // logical vol
                                      "world_phys", // name
                                      nullptr, // mother logical (none)
                                      false, // one of many? (no)
                                      true); // check volume overlaps? (yes)

  // Build the detector volume. Note that we are not setting the optical
  // properties since we are just interested in the hit pattern
  // Detector volume is 50x50 cm^2 and 5 cm thick, extending into the y-dim
  /*G4double det_x = 50.0*cm;
  G4double det_y = 5.0*cm;
  G4double det_z = det_x;
  auto det_geom = new G4Box("det_geom", // name
                            det_x / 2.0, // x-extent/2
                            det_y / 2.0, // y-extent/2
                            det_z / 2.0);// z-extent/2
  auto mat_nai = nist_man->FindOrBuildMaterial("G4_SODIUM_IODIDE");
  auto det_log = new G4LogicalVolume(det_geom,
                                     mat_nai,
                                     "det_log");
  // Don't need to assign to variable here - we won't use it
  new G4PVPlacement(nullptr,
                    G4ThreeVector(0, 50.0*cm + det_y/2.0, 0),
                    det_log,
                    "det_phys",
                    world_log,
                    false,
                    true);
  */
  // We've replaced the above with this new Detector object, where all of
  // the Detector info is encapsulated
  detector->build(world_log);

  // Build the phantom volume
  auto phantom_geom = new G4Orb("phantom_geom", // name
                                5.0*cm); // radius
  auto mat_phantom = nist_man->FindOrBuildMaterial("G4_URANIUM_OXIDE");
  auto phantom_log = new G4LogicalVolume(phantom_geom,
                                         mat_phantom,
                                         "phantom_log");
  auto phantom_vis = new G4VisAttributes;
  phantom_vis->SetForceSolid(true);
  phantom_vis->SetColour(G4Colour::Yellow());
  phantom_log->SetVisAttributes(phantom_vis);
  new G4PVPlacement(0,
                    G4ThreeVector(0, 0, 0),
                    phantom_log,
                    "phantom_phys",
                    world_log,
                    false,
                    true);
  return world_phys;
}

/* Completely clear out the detector geometry and rebuild it from 
 * scratch. This is required to have a dynamic geometry, particularly
 * when switching shapes or materials. */
void DetectorConstruction::reloadGeometry() {
  G4cout << "Completely reloading geometry. This may take a moment...\n";
  // Clear out all of the volume stores - this takes care of the memory
  // for all of these objects
  // Note that this can be accomplished by calling
  // G4RunManager::GetRunManager()->ReinitializeGeometry(), however it
  // will not update the visual scene until a run is started
  G4GeometryManager::GetInstance()->OpenGeometry();
  G4SolidStore::GetInstance()->Clean();
  G4LogicalVolumeStore::GetInstance()->Clean();
  G4PhysicalVolumeStore::GetInstance()->Clean();

  // Construct the new geometry. NOTE: this will generate a warning from
  // the PhysicalVolume::Validate() function about the world volume
  // having the same name and copy number but being different. This is
  // safe to ignore
  G4RunManager::GetRunManager()->DefineWorldVolume(Construct());
  G4RunManager::GetRunManager()->GeometryHasBeenModified();
  // Clear out trajectories if the user is using visualization
  if (G4VVisManager::GetConcreteInstance()) {
    // Remove the particle trajectories
    G4UImanager::GetUIpointer()->
      ApplyCommand("/vis/viewer/clearTransients");
  }
  G4cout << "...geometry reload complete." << G4endl;
  return;
}

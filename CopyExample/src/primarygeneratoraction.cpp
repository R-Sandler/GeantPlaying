// NE697
#include "primarygeneratoraction.hpp"
// Geant4
#include "G4Neutron.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
// std
#include <cmath>
using std::sqrt;
using std::cos;
using std::sin;
using std::abs;

/* Constructor. */
PrimaryGeneratorAction::PrimaryGeneratorAction():
  G4VUserPrimaryGeneratorAction(),
  // G4ParticleGun(particle type, number to generate per event)
  gun(new G4ParticleGun(G4Neutron::Definition(), 1))
{
  G4cout << "Creating PrimaryGeneratorAction...\n";
  // Make the source monoenergetic
  gun->SetParticleEnergy(14.1*MeV);

  // Set the position - we want a point-like cone beam source. Note that
  // if we wanted an extended source, we would want to randomly sample the
  // position from the source volume
  gun->SetParticlePosition(G4ThreeVector(0, -50.0*cm, 0));
  G4cout << "...done.\n" << G4endl;
}

/* Destructor. */
PrimaryGeneratorAction::~PrimaryGeneratorAction() {
  G4cout << "Deleting PrimaryGeneratorAction...\n";
  delete gun;
  G4cout << "...done.\n" << G4endl;
}

/* Generate an event (1 gamma ray). The source position is fixed, so we
 * just need to grab a random direction. We sample on cosine to ensure we
 * get random points on a sphere, then force the direction to be +y since
 * we don't care about photons going the other way. */
void PrimaryGeneratorAction::GeneratePrimaries(G4Event* e) {
  // Get a random x, y, z. Sample uniformly on cosine. This gives a
  // uniform sampling of points from the sphere's surface. Sampling
  // on theta and phi, then converting, will produce a biased result!
  // double ctheta = 2.0 * G4UniformRand() - 1.0;
  //double stheta = sqrt(1.0 - pow(ctheta, 2));
  //double phi = 2.0 * CLHEP::pi * G4UniformRand();
  //double x = stheta * sin(phi);
  //double z = stheta * cos(phi);
  // Force positive direction - in the direction of the phantom/detector
  //double y = abs(ctheta);
  double x = 0;
  double y = 10;
  double z = 0;
  G4ThreeVector dir(x, y, z);
  gun->SetParticleMomentumDirection(dir);

  // Finally, tell the gun to generate the event and copy the parameters to
  // the G4Event object
  gun->GeneratePrimaryVertex(e);
  return;
}

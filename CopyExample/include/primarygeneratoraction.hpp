/* PrimaryGeneratorAction: generates G4Events, which is the introduction of
 * one or more particles in the simulation space. */
#pragma once
// NE697
// Geant4
#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
// std

class PrimaryGeneratorAction: public G4VUserPrimaryGeneratorAction {
  public:
    PrimaryGeneratorAction();
    ~PrimaryGeneratorAction();

    void GeneratePrimaries(G4Event* e);

  private:
    // True to its name, it shoots out particles
    G4ParticleGun* gun;
};

/* PhysicsList: a custom physics list for gamma rays and sub-20 MeV
 * neutrons. Allows the user to choose between EM physics lists, Livermore
 * or Penelope, and allows them to toggle high precision (HP) neutron
 * physics. */
#pragma once
// NE697 
// Geant4
#include "G4VModularPhysicsList.hh"
// std

class PhysicsList: public G4VModularPhysicsList {
  public:
    PhysicsList(const G4bool& on=true, const G4bool& nhp=false,
                const G4int& iem=0);
    virtual ~PhysicsList();

  private:
    G4bool fOn;
    G4bool fNeutronHP;
    G4int  iEMList;
    G4int  verbosityLevel;

    // Functions to construct particles and processes
    void ConstructParticle();
    void ConstructProcess();
    void ConstructEM();
    void ConstructRadioactiveDecay();
    void ConstructHadronic();

    void SetCuts();
};

// NE697
#include "physicslist.hpp"
// Geant4
#include "G4BosonConstructor.hh"
#include "G4LeptonConstructor.hh"
#include "G4MesonConstructor.hh"
#include "G4BaryonConstructor.hh"
#include "G4IonConstructor.hh"
#include "G4ShortLivedConstructor.hh"
#include "G4EmLivermorePhysics.hh"
#include "G4EmPenelopePhysics.hh"
#include "G4EmStandardPhysics.hh"
#include "G4EmExtraPhysics.hh"
#include "G4DecayPhysics.hh"
#include "G4HadronElasticPhysicsHP.hh"
#include "G4HadronElasticPhysics.hh"
#include "G4HadronPhysicsQGSP_BIC_HP.hh"
#include "G4HadronPhysicsQGSP_BIC.hh"
#include "G4HadronPhysicsQGSP_BERT_HP.hh"
#include "G4HadronPhysicsQGSP_BERT.hh"
#include "G4StoppingPhysics.hh"
#include "G4IonBinaryCascadePhysics.hh"
#include "G4IonPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"
// std
#include <iostream>
using std::cerr;
using std::endl;

/* Constructor. */
PhysicsList::PhysicsList(const G4bool& on, const G4bool& nhp,
                         const G4int& iem):
  G4VModularPhysicsList(),
  fOn(on),
  fNeutronHP(nhp),
  iEMList(iem)
{
  // Check the inputs and report
  if (!fOn) {
    G4cout << "PhysicsList constructor: Physics list is empty. "
      << "\nPass the argument 'true' to turn it on." << G4endl;
  } else {
    if (!fNeutronHP) {
      G4cout << "PhysicsList constructor: Using non-HP neutron "
        << "physics. \nPass the argument 'true' to turn on HP "
        << "neutron physics."<< G4endl;
    }
    if ((iEMList < 1) || (iEMList > 2)) {
      iEMList = 0;
      G4cout << "PhysicsList constructor: Using standard EM physics. "
        << "\nPass 1 for Livermore, 2 for Penelope." << G4endl;
    }
  }

  //Verbosity level:
  //  0: Silent
  //  1: Warning message
  //  2: More
  verbosityLevel = 0;
  SetVerboseLevel(verbosityLevel);
}

/* Destructor. */
PhysicsList::~PhysicsList() {
  G4cout << "Deleting PhysicsList..." << G4endl;
  G4cout << "...done." << G4endl << G4endl;
}

/* Construct the different types of particles with different functions.
 * We construct all particles since this should not affect performance.
 * We will not, however, add all the physics processes for each particle
 * as this would affect performance.
 * Furthermore, since particles are defined statically, they are
 * all added to the G4ParticleTable regardless of what goes on in this
 * method. */
void PhysicsList::ConstructParticle() {
  G4cout << "Constructing particles..." << G4endl;

  // Construct all bosons
  G4cout << "...bosons" << G4endl;
  G4BosonConstructor b_con;
  b_con.ConstructParticle();

  // Construct all leptons
  G4cout << "...leptons" << G4endl;
  G4LeptonConstructor l_con;
  l_con.ConstructParticle();

  // Construct all mesons
  G4cout << "...mesons" << G4endl;
  G4MesonConstructor m_con;
  m_con.ConstructParticle();

  // Construct all baryons
  G4cout << "...baryons" << G4endl;
  G4BaryonConstructor h_con;
  h_con.ConstructParticle();

  // Construct light ions
  G4cout << "...light ions" << G4endl;
  G4IonConstructor i_con;
  i_con.ConstructParticle();

  // Construct short lived as they are needed
  // for the electronuclear process
  G4cout << "...short lived" << G4endl;
  G4ShortLivedConstructor s_con;
  s_con.ConstructParticle();

  G4cout << "Done constructing particles." << G4endl << G4endl;
  return;
}

/* Construct all processes we are using. */
void PhysicsList::ConstructProcess() {
  // adds transportation so particles can move
  // protected method of G4VUserPhysicsList
  AddTransportation();

  if(fOn) {
    // Electric and Magnetic Processes
  /*  G4cout << "PhysicsList::ConstructProcess() -> Registering EM "
      << "processes" << G4endl;
    ConstructEM();
*/
    //Radioactive Decay
    G4cout << "PhysicsList::ConstructProcess() -> Registering "
      << "radioactive decay processes" << G4endl;
    ConstructRadioactiveDecay();

    //Construct hadronic physics
  /*  G4cout << "PhysicsList::ConstructProcess() -> Registering hadronic "
      << "processes" << G4endl;
    ConstructHadronic();
*/  }

  G4cout << "PhysicsList::ConstructProcess() -> Done registering "
    << "physics processes" << G4endl;
  return;
}

/* Construct all of the electromagnetic processes. */
/*void PhysicsList::ConstructEM() {
  G4VPhysicsConstructor* em_physics_list;
  switch (iEMList) {
    case 0:
      em_physics_list = new G4EmStandardPhysics(verbosityLevel);
      break;

    case 1:
      em_physics_list = new G4EmLivermorePhysics(verbosityLevel);
      break;

    case 2:
      em_physics_list = new G4EmPenelopePhysics(verbosityLevel);
      break;

    default:
      cerr << "PhysicsList::ConstructEM(): invalid physics list "
        << "selection detected." << endl;
      em_physics_list = new G4EmStandardPhysics(verbosityLevel);
      break;

  }
  em_physics_list->ConstructProcess();

  // synchrotron radiation, electro- and photo-nuclear
  G4VPhysicsConstructor *em_extra_physics_list =
    new G4EmExtraPhysics(verbosityLevel);
  em_extra_physics_list->ConstructProcess();
  return;
}
*/
/* Construct radioactive decay processes. */
void PhysicsList::ConstructRadioactiveDecay() {
  G4VPhysicsConstructor* dec_physics_list =
    new G4DecayPhysics(verbosityLevel);
  dec_physics_list->ConstructProcess();

  G4VPhysicsConstructor *rad_dec_physics_list =
    new G4RadioactiveDecayPhysics(verbosityLevel);
  rad_dec_physics_list->ConstructProcess();
  return;
}

/* The hadronic interactions for neutrons, protons and ions. */
/*void PhysicsList::ConstructHadronic() {
  // all physics below is modeled on either QGSP_BIC(_HP) or
  // QGSP_BERT(_HP) physics lists
  G4bool bic = true;
  G4VPhysicsConstructor* hadStopping = nullptr;
  G4VPhysicsConstructor* hadElastic = nullptr;
  G4VPhysicsConstructor* hadPhysics = nullptr;
  G4VPhysicsConstructor* ionPhysics = nullptr;

  // Hadron Elastic scattering
  if (fNeutronHP) {
    hadElastic = new G4HadronElasticPhysicsHP(verbosityLevel);
  } else {
    hadElastic = new G4HadronElasticPhysics(verbosityLevel);
  }

  // Ion and Hadron physics
  if (bic) {
    ionPhysics = new G4IonBinaryCascadePhysics(verbosityLevel);//from BIC
    if (fNeutronHP) {
      hadPhysics = new G4HadronPhysicsQGSP_BIC_HP(verbosityLevel);
    } else {
      hadPhysics = new G4HadronPhysicsQGSP_BIC(verbosityLevel);
    }
  } else {
    ionPhysics = new G4IonPhysics(verbosityLevel);//from BERT
    if (fNeutronHP) {
      hadPhysics = new G4HadronPhysicsQGSP_BERT_HP(verbosityLevel);
    } else {
      hadPhysics = new G4HadronPhysicsQGSP_BERT(verbosityLevel);
    }
  }

  // Stopping Physics
  hadStopping = new G4StoppingPhysics(verbosityLevel);

  // Construct processes
  hadElastic->ConstructProcess();
  hadPhysics->ConstructProcess();
  hadStopping->ConstructProcess();
  ionPhysics->ConstructProcess();
  return;
}
*/
/* Set cuts. */
void PhysicsList::SetCuts() {
  // the default cut value will only simulate things that extend
  // beyond this value.  Otherwise will treat as energy loss
  defaultCutValue = 0.01*mm;

  if (verboseLevel > 0) {
    G4cout << "PhysicsList::SetCuts():";
    G4cout << "CutLength : " << G4BestUnit(defaultCutValue,"Length")
      << G4endl;
  }

  // set cut values for gamma at first and for e- second and next for e+,
  // because some processes for e+/e- need cut values for gamma
  SetCutValue(defaultCutValue, "gamma");
  SetCutValue(defaultCutValue, "e-");
  SetCutValue(defaultCutValue, "e+");

  if (iEMList > 0) {
    G4ProductionCutsTable::GetProductionCutsTable()
      ->SetEnergyRange(250*eV, 1*GeV);
  }
  if (verboseLevel > 0) {
    DumpCutValuesTable();
  }
  G4cout << "Done initializing PhysicsList" << G4endl << G4endl;
  return;
}

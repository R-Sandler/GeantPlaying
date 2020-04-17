/* NE 697 Geant4 main function. This is the starting point for the program.
 * Created by Micah Folsom on August 9, 2017. */
// NE697
#include "detectorconstruction.hpp"
#include "primarygeneratoraction.hpp"
#include "runaction.hpp"
#include "eventaction.hpp"
#include "physicslist.hpp"
// Geant4
#include "G4RunManager.hh"
//#include "QGSP_BIC.hh"
#include "G4VisExecutive.hh"
#include "G4UImanager.hh"
#include "G4UIExecutive.hh"
// std

int main(int argc, char* argv[]) {
  // Run manager
  auto run_man = new G4RunManager;

  // Set custom initialization classes, detector construction and physics
  // list
  run_man->SetUserInitialization(new DetectorConstruction);
  // I will usually make my own PhysicsList class that explicitly identifies
  // every physics process available so I have complete control over what
  // is happening, but for this we will use QGSP_BIC which is a high energy
  // physics list covering standard EM
  run_man->SetUserInitialization(new PhysicsList);

  // Set custom action classes - particle generation, run stuff, and event
  // stuff
  run_man->SetUserAction(new PrimaryGeneratorAction);
  run_man->SetUserAction(new RunAction);
  run_man->SetUserAction(new EventAction);

  // Initialize kernal
  run_man->Initialize();
  
  // Initialize visualization, only if the user did not specify a macro
  // argument
  G4VisManager* vis_man = nullptr;
  if (argc == 1) {
    // argc==1 means there was no argument (argv[0] is the program itself)
    vis_man = new G4VisExecutive;
    vis_man->Initialize();
  }
	
  // Initialize the GUI
  auto ui_man = G4UImanager::GetUIpointer();
  // Change the default macro path to the local scripts/ directory
  ui_man->ApplyCommand("/control/macroPath scripts/");
	
  // Handle input file if there is one. argc==2 means there was 1 argument
  if (argc == 2) {
    // Instead of initializing the visualization, run the .mac provided
    G4String cmd = "/control/execute " + (G4String)argv[1];
    ui_man->ApplyCommand(cmd);
  } else {
    // No macro provided, run the visualization application
    auto ui = new G4UIExecutive(argc, argv);
    if (vis_man) {
      ui_man->ApplyCommand("/control/execute init_vis.mac");
    } else {
      ui_man->ApplyCommand("/control/execute init.mac");
    }
    ui->SessionStart();
    delete ui;
  }

  // Clean up
  delete vis_man;
  delete run_man;
  return 0;
}

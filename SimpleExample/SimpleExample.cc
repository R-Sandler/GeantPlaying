#include "G4RunManager.hh"
#include "G4UImanager.hh"

#ifdef G4UI_USE
  #include "G4VisExecutive.hh"
 #endif

#include "ExG4DetectorConstruction01.hh"
#include "ExG4PhysicsList00.hh"
/#include "ExG4PrimaryGeneratorAction01"

int main()
{
  // construct the default run manager
  G4RunManager* runManager = new G4RunManager;

  // set mandatory initialization classes
  runManager->SetUserInitialization(new ExG4DetectorConstruction01);
  runManager->SetUserInitialization(new ExG4PhysicsList00);
  runManager->SetUserAction(new ExG4PrimaryGeneratorAction01);
  //runManager->SetUserInitialization(new ExG4ActionInitialization01);

  // initialize G4 kernel
  runManager->Initialize();

  // get the pointer to the UI manager and set verbosities
  G4UImanager* UI = G4UImanager::GetUIpointer();

  if(argc == 1){
    //interactive mode: define UI Session
    #ifdef G4UI_USE
    G4UIExecutive* ui = new G4UIExecutive(argc, argv);
    UImanager->ApplyCommand("/control/execute init.mac");
    ui->SessionStart();
    delete ui;
    #endif
  }
  else{
    //batch mode
    G4String command = "/control/execute";
    G4String fileName = argv[1];
    UImanager->ApplyCommand(command+fileName);
  }
  //UI->ApplyCommand("/run/verbose 1");
  //UI->ApplyCommand("/event/verbose 1");
  //UI->ApplyCommand("/tracking/verbose 1");

  // start a run
  //int numberOfEvent = 3;
  //runManager->BeamOn(numberOfEvent);

  // job termination
  delete runManager;
  return 0;
}

/* Run: keeps track of the Run information/data. Many Runs might run in
 * parallel if multithreading is enabled. */
#pragma once
// NE697
// Geant4
#include "G4Run.hh"
// std
#include <string>
using std::string;
#include <fstream>
using std::ofstream;

class Run: public G4Run {
  public:
    Run();
    ~Run();

    void openFile();
    void closeFile();
    void writeHit(const double& x, const double& z, const double& e,
                  const string& proc);

  private:
    ofstream outFile;
};

// NE697 
#include "run.hpp"
// Geant4
// std
using std::endl;

/* Constructor. */
Run::Run():
  G4Run(),
  outFile()
{
  G4cout << "Creating Run...\n";
  G4cout << "...done.\n" << G4endl;
}

/* Destructor. */
Run::~Run() {
  G4cout << "Deleting Run...\n";
  G4cout << "...done.\n" << G4endl;
}

/* Open a text file to write the hits in. */
void Run::openFile() {
  outFile.open("hits.txt", ofstream::out);
  return;
}

/* Close the text file. */
void Run::closeFile() {
  outFile.close();
  return;
}

/* Write the hit information as text, with each hit in a row, each value
 * separated by spaces. */
void Run::writeHit(const double& x, const double& z, const double& e,
                   const string& proc) {
  outFile << x << " " << z << " " << e << " " << proc << endl;
  return;
}

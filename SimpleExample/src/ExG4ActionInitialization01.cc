#include "ExG4ActionInitialization01.hh"
#include "ExG4PrimaryGeneratorAction01.hh"

void ExG4ActionInitialization01::Build() const
{
  SetUserAction(new ExG4PrimaryGeneratorAction01);
}

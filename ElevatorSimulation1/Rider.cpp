// Lab 9, The "Elevator" Program
// Programmer: Fernando Ian Patricio
// Editor(s) used: Code::Blocks
// Compiler(s) used: GNU GCC Compiler

// Rider.cpp

#include "Floor.h" // include definition of class Floor
#include "Rider.h" // include definition of class Rider

// define and initialize static data member count to 0
int Rider::count = 0;

// overloaded assignment operator
Rider& Rider::operator=( const Rider& r )
{
  const_cast<int&>(ID) = r.ID;
  const_cast<const Floor*&>(destination) = r.destination;
  return *this;
}








// Lab 15, The "Elevator" Program
// Programmer: Fernando Ian Patricio
// Editor(s) used: Code::Blocks
// Compiler(s) used: GNU GCC Compiler

// Building.h

// Building class definition
#ifndef BUILDING_H
#define BUILDING_H

#include <iostream>
using std::ostream;

#include <vector>
using std::vector;

class Floor;
class Elevator;

class Building
{
  private:
    int time; //The simulation time in seconds, initialized to zero in the default constructor, and updated in the step function, explained below.
    vector<Floor*> floors; // A vector of Floor*'s
    vector<Elevator*> elevators; // a vector of Elevator*'s

  public:
   Building();
   ~Building();
   int getFloorCount() { return floors.size(); } const // return #of floors in the vector of Floor*'s
   int getElevatorCount() const { return elevators.size(); }   // return #of elevators in the vector of Elevator*'s
   const Floor& getFloor(int index) const { return *floors[index]; }  // return a reference to the "indexth" floor
   const Elevator& getElevator(int index) const { return *elevators[index]; }// return a reference to the "indexth" elevator

   // the function that contains the instructions for moving elevators and riders during a one-second time-step
   Building& step(int); // The int parameter indicates the number of randomly-placed riders to add in the time-step.

  friend ostream& operator<< (ostream&, const Building&);
};

#endif // BUILDING_H




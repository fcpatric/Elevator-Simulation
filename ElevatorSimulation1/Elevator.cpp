// Lab 9, The "Elevator" Program
// Programmer: Fernando Ian Patricio
// Editor(s) used: Code::Blocks
// Compiler(s) used: GNU GCC Compiler

// Elevator.cpp

#include <cstdlib>

#include <iostream>
using std::ostream;

#include <vector>
using std::vector;

#include "Floor.h" // include definition of class Floor
#include "Elevator.h" // include definition of class Elevator
#include "Rider.h" // include definition of class Rider

int Elevator::elevatorID = 0;
const int Elevator::IDLE = 0;
const int Elevator::UP = 1;
const int Elevator::DOWN = -1;

// true if distance to destination is less than OR EQUAL TO the speed
bool Elevator::isNearDestination() const
{
  if( hasADestination() )
    return ( ( abs( (toFloor->getLocation()) - location) < speed) || ( abs( (toFloor->getLocation()) - location ) == speed ) );

  return false;
}

// set location to that of destination floor (if there is one)
void Elevator::moveToDestinationFloor()
{
  if( hasADestination() )
    location = toFloor->getLocation();
}

// remove riders from vector whose destination is reached
vector<Rider> Elevator::removeRidersForDestinationFloor()
{
  // create empty vector of removed riders to be used as return value
  vector<Rider> removedRiders;

  // if elevator has any riders
  if ( hasRiders() )
  {
    // create an empty vector for riders who remain on elevator
    vector<Rider> remainingRiders;

    // traverse vector of current riders
    for(int i = 0; i < getRiderCount(); i++)
    {
      // if a rider's destination floor is same as elevator's destination...
      if( &riders[i].getDestination() == toFloor )
        // add rider to vector of removed riders
        removedRiders.push_back(riders[i]);
      // else
      else
        // add rider to vector of remaining riders
        remainingRiders.push_back(riders[i]);
    }

    // reassign elevator rider vector to vector of remaining riders
    riders = remainingRiders;
  }

  // return vector of removed riders
  return removedRiders;
}

// copy riders from parameter vector to riders vector
void Elevator::addRiders(const vector<Rider>& r)
{
  // traverse the parameter vector
  for( unsigned int i = 0; i < r.size(); i++)
  {
    // if there is still room on the elevator
    if ( getAvailableSpace() > 0 )
      // add the rider to the elevator's rider vector
      riders.push_back(r[i]);
  }
}

// reset toFloor based on riders' destinations
void Elevator::setDestinationBasedOnRiders()
{
  // if there are no riders on the elevator
  if ( !hasRiders() )
    // exit the function
    return;

  // set elevator's destination to the zeroth Rider's destination
  toFloor = &riders[0].getDestination();

  // traverse the vector of elevator riders
  for (int i = 0; i < getRiderCount(); i++)
  {
    // get the absolute value of the distance from the elevator to the rider's destination floor
    int distanceFromElevatortoRiderDestinationFloor = abs( location - riders[i].getDestination().getLocation() );

    // get the absolute value of the distance from the elevator to the elevator's destination floor
    int distanceFromElevatortoElevatorDestinationFloor= abs( location - toFloor->getLocation() );

    // if closer to the rider's destination than to the elevator's destination
    if( distanceFromElevatortoRiderDestinationFloor < distanceFromElevatortoElevatorDestinationFloor )
      // set elevator's destination to the rider's destination
      toFloor = &riders[i].getDestination();
  }
}

ostream& operator<<(ostream& out, const Elevator& e)
{
  out << "location=" << e.location << ". ";

  if ( e.direction == Elevator::UP )
    out << "Direction is up. ";
  if ( e.direction == Elevator::DOWN )
    out << "Direction is down. ";
  if ( e.direction == Elevator::IDLE )
    out << "Direction is idle. ";

  if( e.isDoorOpen() )
    out << "Door is open.";
  else
    out << "Door is closed.";

  if( e.getRiderCount() == 0 )
    out << " No Riders.";
  else
  {
    if( e.getRiderCount() == 1 )
      out << " 1 Rider.";
    else
      out << " " << e.getRiderCount() << " Riders.";
  }

  return out;
}








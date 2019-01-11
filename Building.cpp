// Lab 15, The "Elevator" Program
// Programmer: Fernando Ian Patricio
// Editor(s) used: Code::Blocks
// Compiler(s) used: GNU GCC Compiler

// Building.cpp

#include <cstdlib>

#include <iostream>
using std::ostream;
using std::endl;

#include "Floor.h"
#include "Rider.h"
#include "Elevator.h"
#include "Building.h"

// The simulation time in seconds, initialized to zero in the default constructor, and updated in the step function, explained below.
// create at least 5 floors and 2 elevators, each with characteristics of your choosing.
// Use dynamic memory allocation to create these, and use the push_back function to add them to the vectors.
Building::Building()
{
  time = 0;
  Floor* basement = new Floor(0, "Basement");
  Floor* firstFloor = new Floor(120, "First Floor");
  Floor* secondFloor = new Floor(240, "Second Floor");
  Floor* thirdFloor = new Floor(360, "Third Floor");
  Floor* fourthFloor = new Floor(480, "Fourth Floor");

  floors.push_back(basement);
  floors.push_back(firstFloor);
  floors.push_back(secondFloor);
  floors.push_back(thirdFloor);
  floors.push_back(fourthFloor);

  Elevator* e1 = new Elevator(10, 20, *firstFloor);
  Elevator* e2 = new Elevator(10, 20, *thirdFloor);
  elevators.push_back(e1);
  elevators.push_back(e2);
}

Building::~Building()
{
  for (unsigned int i = 0; i < floors.size(); i++)
    delete floors[i];

  for (unsigned int i = 0; i < elevators.size(); i++)
    delete elevators[i];
}

Building& Building::step(int n)
{
  //The following steps are executed EVERY SECOND of the simulation:
  // Implement and test code blocks in the order shown in [square brackets]

  // POSSIBLE RIDER ACTION [1]
  // add rider(s) in this time step (The number of riders to be added is sent to this function in the parameter list, and is greater or equal to 0.) [1]
  for (int i = 0; i < n; i++)
  {
    int a, b;
    do
    {
      a = rand() % 5; // range is 0 to (nPossible-1)
      b = rand() % 5; // range is 0 to (nPossible-1)
    } while (a == b); // try again if they are the same

    // create a rider with randomly selected from- and to-floors (where from- and to- are not the same!) [1]
    Rider r(*floors[a]);

    // tell the from-floor to add this rider [1]
    floors[b]->addNewRider(r); // DO NOT START ELEV ON THIS FLOOR
  }

  // ELEVATOR ACTIONS [3]
  // tell each elevator to perform an action [3]
  for (int j = 0; j < getElevatorCount(); j++)
  {
    // if elevator door is closed (move up or down) [3]
    if ( !(elevators[j]->isDoorOpen()) )
    {
      // if not near enough to destination to reach it in this time step, continue moving [3]
      if ( !(elevators[j]->isNearDestination()) )
      {
        // if elevator direction is up, move up [3]
        if ( elevators[j]->isDirectionUp() )
          elevators[j]->moveUp();

        // otherwise, move down [3]
        else
          elevators[j]->moveDown();
      }

      // otherwise it's near enough to destination to reach it in this time step... [4]
      else if ( elevators[j]->isNearDestination() )
      {
        // tell elevator to move to its destination floor [4]
        elevators[j]->moveToDestinationFloor();

        // tell elevator to open its door [4]
        elevators[j]->openDoor();

        // tell elevator to remove riders for its destination floor -- ignore returned vector of removed riders [4]
        elevators[j]->removeRidersForDestinationFloor();

        // if elevator is empty, choose a direction based on longest-waiting rider (the one with the smallest ID) on the floor: [5]
        if ( !(elevators[j]->hasRiders()) )
        {
          // if the floor's chosen direction is up [5]
          if ( elevators[j]->getDestination().isPreferredDirectionUp() )
          {
            // tell elevator to set its direction to up [5]
            elevators[j]->setDirectionUp();
          }

          // otherwise [5]
          else
          {
            // tell elevator to set its direction to down [5]
            elevators[j]->setDirectionDown();
          }
        }

        // if there is space in the elevator after letting off riders, board new ones [6]
        if ( (elevators[j]->getAvailableSpace()) > 0 )
        {
          // get a constant mutating pointer to the elevator's destination floor (using const_cast) [6] HINT: lecture topic 9
          Floor* const currentFloor = const_cast<Floor*>( &( elevators[j]->getDestination() ) );

          // if elevator direction is up, board up-riders (if any)... [6]
          if ( elevators[j]->isDirectionUp() )
          {
            if ( currentFloor->hasUpRiders() )
              elevators[j]->addRiders( currentFloor->removeUpRiders( elevators[j]->getAvailableSpace()) );
          }

          // otherwise, board down-riders (if any) [6]
          else
          {
            if ( currentFloor->hasDownRiders() )
              elevators[j]->addRiders( currentFloor->removeDownRiders( elevators[j]->getAvailableSpace() ) );
          }
        }

        // reassess elevator destination based on its riders [8]
        elevators[j]->setDestinationBasedOnRiders();
      }
    }

    // otherwise (then it already let off riders, or is in its initial state) [7]
    else
    {
      // if elevator has any riders (then they just boarded in the previous time step) [7]
      if (elevators[j]->hasRiders())
      {
        // tell elevator to close its door [7]
        elevators[j]->closeDoor();
      }

      // otherwise [9]
      else
      {
        // tell elevator to go idle [9]
        elevators[j]->setIdle();
      }
    }
  }

  // FLOOR ACTIONS [2]
  // check each floor (for waiting riders) [2]
  // index of elevators and floors should not be the same
  for (int k = 0; k < getFloorCount(); k++)
  {
    // if there are no riders waiting on this floor, continue with next floor [2]
    if (!(floors[k]->hasRidersWaiting()))
      continue;

    // look at each elevator to see if it needs to be sent here [2]
    for (int l = 0; l < getElevatorCount(); l++)
    {
      // get elevator's relative location (negative if elevator is below floor) [2]
      int distanceFromElevatortoFloor = (elevators[l]->getLocation() - floors[k]->getLocation());

      // if this elevator's idle... [2]
      if (elevators[l]->isIdle())
      {
        // if elevator is above the floor, set elevator direction to down [2]
        if (distanceFromElevatortoFloor > 0)
          elevators[l]->setDirectionDown();

        // otherwise if it's below, set elevator direction to up [2]
        else if (distanceFromElevatortoFloor < 0)
          elevators[l]->setDirectionUp();

        // set elevator's destination to this floor [2]
        elevators[l]->setDestination(floors[k]);

        // tell elevator to close its door [2]
        elevators[l]->closeDoor();
      }

      // else if there are riders on this floor waiting to go up, and the elevator is going up... [10]
      else if (floors[k]->hasUpRiders() && elevators[l]->isDirectionUp())
      {
        // get distance from elevator's destination floor to this floor (positive if elevator destination is above this floor) [10]
        int distanceFromElevatorDestinationFloortoThisFloor = (elevators[l]->getDestination().getLocation() - floors[k]->getLocation());

        // if elevator is below floor and elevator destination is above this floor [10]
        if (distanceFromElevatortoFloor < 0 && distanceFromElevatorDestinationFloortoThisFloor > 0)
        {
          // set elevator's destination to this floor [10]
          elevators[l]->setDestination(floors[k]);
        }
      }

      // else if there are riders on this floor waiting to go down, and the elevator is going down... [10]
      else if (floors[k]->hasDownRiders() && elevators[l]->isDirectionDown())
      {
        // get distance from elevator's destination floor to this floor (negative if elevator destination is below this floor) [10]
        int distanceFromElevatorDestinationFloortoThisFloor = (elevators[l]->getDestination().getLocation() - floors[k]->getLocation());

        // if elevator is above floor and elevator destination is below this floor [10]
        if (distanceFromElevatortoFloor > 0 && distanceFromElevatorDestinationFloortoThisFloor < 0)
        {
          // set elevator's destination to this floor [10]
          elevators[l]->setDestination(floors[k]);
        }
      }
    }
  }

  time++;
  return *this;
}



// Use Elevator's operator<< and Floor's operator<< in Building's operator<<.
// Be sure that your elevators "say" how many riders they carry, and their direction, and door status.
// Be sure the floors say their names, and numbers of up- and down-riders.
// Do NOT call getters of the Elevator and Floor classes in this friend function.
ostream& operator<< (ostream& out, const Building& b)
{
  // first output the time with YOUR NAME and student ID, then output the elevators, and then output the floors.
  out << "Time=" << b.time << " Fernando Ian Patricio StudentID#1428751\n";

  // Output each elevator
	for (unsigned int i = 0; i < b.elevators.size(); i++)
    out << *b.elevators[i] << endl;

  // only output the floors that have riders waiting.
  for (unsigned int i = 0; i < b.floors.size(); i++)
  {
    // b.floors[i]->upRiders.size() + b.floors[i]->downRiders.size() ) != 0
    if (b.floors[i]->hasRidersWaiting()) out << *b.floors[i] << endl;
  }

  return out;
}




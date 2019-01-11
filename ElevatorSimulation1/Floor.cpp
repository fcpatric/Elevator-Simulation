// Lab 14, The "Elevator" Program
// Programmer: Fernando Ian Patricio
// Editor(s) used: Code::Blocks
// Compiler(s) used: GNU GCC Compiler

// Floor.cpp

#include <iostream>
using std::ostream;

#include <vector>
using std::vector;

#include "Floor.h" // include definition of class Floor
#include "Rider.h" // include definition of class Rider

// based on Rider with smallest ID
bool Floor::isPreferredDirectionUp() const
{
  // if there are no downRiders, return true
  if ( downRiders.size() == 0 ) return true;

  // if there are no upRiders, return false
  if ( upRiders.size() == 0 ) return false;

  // if the ID of the first upRider (upRider[0]) is less than that of the first downRider.... return true
  if ( upRiders[0] < downRiders[0] ) return true;

  // return false
  return false;
} // end function isPreferredDirectionUp

// add to up- or down-vector
void Floor::addNewRider(const Rider& rider)
{
  // if added rider's destination is greater than the floor's location
  if ( rider.getDestination().location > location )
    // add rider to the upRiders vector
    upRiders.push_back(rider);

  // else
  else
    // add rider to the downRiders vector
    downRiders.push_back(rider);
} // end function addNewRider

// int is max #of riders...
vector<Rider> Floor::removeUpRiders(int maxRiders)
{
  // create an empty vector for riders to be removed
  vector <Rider> removedRiders;

  // if there are any up riders...
  if ( upRiders.size() > 0 )
  {
    // create an empty vector for riders to remain on the floor
    vector<Rider> remainingRiders;

    // traverse the upRiders vector
    for (unsigned int i = 0; i < upRiders.size(); i++)
    {
      // if there are still spaces left on the elevator..
			if (maxRiders > 0)
			{
				// add an upRider to the vector of riders to be removed
				removedRiders.push_back(upRiders[i]);
				maxRiders--;
			}

      // else
      else
			{
				// add an upRider to the vector of riders to remain on the floor
				remainingRiders.push_back(upRiders[i]);
			}
    }

    // replace the upRiders vector with the vector of remaining riders
    upRiders = remainingRiders;
  }

  // return the vector of removed riders
  return removedRiders;
} // end function removeUpRiders

 //...to move onto elevator
vector<Rider> Floor::removeDownRiders( int maxRiders )
{
  // create an empty vector for riders to be removed
  vector <Rider> removedRiders;

  // if there are any down riders...
  if ( downRiders.size() > 0 )
  {
    // create an empty vector for riders to remain on the floor
    vector<Rider> remainingRiders;

    // traverse the downRiders vector
    for (unsigned int i = 0; i < downRiders.size(); i++)
    {
      // if there are still spaces left on the elevator..
      if ( maxRiders > 0 )
      {
        // add an downRider to the vector of riders to be removed
        removedRiders.push_back( downRiders[i] );
        maxRiders--;
      }

      // else
      else
      {
        // add an downRider to the vector of riders to remain on the floor
        remainingRiders.push_back( downRiders[i] );
      }
    }

    // replace the downRiders vector with the vector of remaining riders
    downRiders = remainingRiders;
  }

  // return the vector of removed riders
  return removedRiders;
} // end function removeDownRiders

// say name, location, #'s of up/down riders waiting
ostream& operator<< (ostream& out, const Floor& f)
{
  out << "FLOOR NAME=" << f.NAME << " LOCATION=" << f.location << " UPRIDERS=" << f.upRiders.size() << " DOWNRIDERS=" << f.downRiders.size();

  return out;
} // end function operator<<




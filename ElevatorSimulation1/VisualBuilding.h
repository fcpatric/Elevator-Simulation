#ifndef VISUALBUILDING_H
#define VISUALBUILDING_H

#include "Building.h"
#include "Floor.h"
#include "Elevator.h"
#include "Rider.h"

#include <cmath>

#include <vector>
using std::vector;

class VisualBuilding : public Building
{
  int width; // width of MFC window, in pixels
  int height; // height of MFC window, in pixels
  int rheight; // height of a rider, in pixels
  int separation; // pixels separating riders
  int margin; // half-separation between elevators
  int max, min, overallHeight; // metrics

  int ridersPer10Seconds;
  int upFloorX; // x-location of end of up floor
  int downFloorX; // x-location of start of up floor
  vector<int> elevatorX;
  vector<int> floorY;

  public:
  void initializeForMfc(int width, int height, int rheight, int separation, int margin)
  {
    VisualBuilding::width = width;
    VisualBuilding::height = height;
    VisualBuilding::rheight = rheight;
    VisualBuilding::separation = separation;
    VisualBuilding::margin = margin;

    int i;
    int shaftWidth = 0;
    for (i = 0; i < getElevatorCount(); i++)
      shaftWidth += getElevatorWidth(i) + 2 * margin;

    upFloorX = (width - shaftWidth) / 2;
    downFloorX = width - upFloorX;

    int x = upFloorX + margin;
    for (i = 0; i < getElevatorCount(); i++)
    {
      elevatorX.push_back(x);
      x += (getElevatorWidth(i) + 2 * margin);
    }

    for (i = 0; i < getFloorCount(); i++)
    {
      int location = getFloor(i).getLocation();
      if (i == 0 || location > max) max = location;
      if (i == 0 || location < min) min = location;
    }
    max += (2 + getElevatorHeight() * (max - min + 4) / (height - rheight));
    min -= 2;
    overallHeight = (max - min);

    for (i = 0; i < getFloorCount(); i++)
    {
      int y = height * (max - getFloor(i).getLocation()) / overallHeight;
      floorY.push_back(y);
    }

    ridersPer10Seconds = 0;
  }

  int getElevatorWidth(int index) const {return (getElevator(index).getCapacity() + 1) * separation + getElevator(index).getCapacity() + 2;}
  int getElevatorHeight() const {return 5 * rheight / 4;}
  int getElevatorX(int index) const {return elevatorX[index];}
  int getElevatorY(int index) const {return height * (max - getElevator(index).getLocation()) / overallHeight;}
  int getUpFloorX() const {return upFloorX;}
  int getDownFloorX() const {return downFloorX;}
  int getFloorY(int index) const {return floorY[index];}
  int getUpRiderCount(int index) const {return getFloor(index).getUpRiderCount();}
  int getDownRiderCount(int index) const {return getFloor(index).getDownRiderCount();}
  int getRiderCount(int index) const {return getElevator(index).getRiderCount();}
  int getRiderSeparation() const {return separation;}
  int getRiderHeight() const {return rheight;}
  void incrementRidersPerSecond() {ridersPer10Seconds++;}
  void decrementRidersPerSecond() {if (ridersPer10Seconds > 0) ridersPer10Seconds--;}
  double getRidersPerSecond() const {return 0.1 * ridersPer10Seconds;}

  int poissonHits() const
  {
    int hits = 0;
    double probOfnHits = exp(-getRidersPerSecond()); // for n=0
    for(double randomValue = double(rand() % 1000) / double(1000);
      (randomValue -= probOfnHits) > 0.0;
      probOfnHits *= getRidersPerSecond() / double(++hits));
    return hits;
  }
};

#endif

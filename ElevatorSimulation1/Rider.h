// Lab 9, The "Elevator" Program
// Programmer: Fernando Ian Patricio
// Editor(s) used: Code::Blocks
// Compiler(s) used: GNU GCC Compiler

// Rider.h
// Member functions are defined here as inline functions
// Static member is defined and operator= in Rider.cpp.
// Rider class definition
#ifndef RIDER_H
#define RIDER_H

class Floor; // forward declaration of class Floor

class Rider
{
  private:
    const int ID; // identification number to uniquely identify a rider
    const Floor* const destination; // represents a rider's destination floor

  public:
    Rider( const Floor& f ) : ID( count++ ), destination( &f ) {}; // Constructor to initialize the ID of a rider and destination of the rider
    const Floor& getDestination() const { return *destination; } // Accessor to return the rider's destination floor
    bool operator==( const Rider& r ) const { return ( ID == r.ID ); } // overloaded operator to compare if a rider is equal to  another rider by using its IDs
    bool operator<( const Rider& r ) const { return ( ID < r.ID ); } // overloaded operator to compare if a rider is less than the another rider by using its IDs
    Rider& operator=( const Rider& ); // overloaded assignment operator

  // static data
  static int count; // number of Riders
}; // end class Rider

#endif // RIDER_H







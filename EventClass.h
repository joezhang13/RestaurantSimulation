#ifndef _EVENTCLASS_H_
#define _EVENTCLASS_H_

#include "constants.h"

//This class defines the events used in the simulation of a restaurant.
class EventClass
{
  private:
    int time; //Event time.
    int type; //Event type (ARRIVAL, SERVE_START, SERVE_END, LEAVE).
    int customerID; //Customer ID of this event.

  public:
    //Default constructor. Will initialize the time to 0, 
    //the type to ARRIVAL and the customerID to 0.
    EventClass(
      );

    //Constructor. Will initialize the event with user-specified 
    //time, type and customerID.
    EventClass(
      int inTime,
      int inType,
      int inCustomerID
      );

    //Copy constructor.
    EventClass(
      const EventClass &copy
      );

    //Assignment operator.
    EventClass& operator=(
      const EventClass &rhs
      );

    //Comparison operators.
    bool operator<(
      const EventClass &rhs
      ) const;

    bool operator<=(
      const EventClass &rhs
      ) const;

    bool operator==(
      const EventClass &rhs
      ) const;

    bool operator>=(
      const EventClass &rhs
      ) const;

    bool operator>(
      const EventClass &rhs
      ) const;
    
    //Returns the time.
    int getTime(
      ) const;

    //Returns the type.
    int getType(
      ) const;

    //Returns the customerID
    int getCustomerID(
      ) const;
};

//Insersion operator
ostream& operator<<(
  ostream &os, 
  const EventClass &rhs
  );

#endif // _EVENTCLASS_H_
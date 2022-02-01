#include <iostream>
using namespace std;

#include "EventClass.h"

EventClass::EventClass(
      )
{
  time = RESTAURANT_OPEN_TIME;
  type = ARRIVAL;
  customerID = DEFAULT_CUSTOMER_ID;
}

EventClass::EventClass(
  int inTime,
  int inType,
  int inCustomerID
  )
{
  time = inTime;
  type = inType;
  customerID = inCustomerID;
}

EventClass::EventClass(
  const EventClass &copy
  )
{
  time = copy.time;
  type = copy.type;
  customerID = copy.customerID;
}

EventClass& EventClass::operator=(
  const EventClass &rhs
  )
{
  time = rhs.time;
  type = rhs.type;
  customerID = rhs.customerID;

  return *this;
}

bool EventClass::operator<(
  const EventClass &rhs
  ) const
{
  return time < rhs.time;
}

bool EventClass::operator<=(
  const EventClass &rhs
  ) const
{
  return time <= rhs.time;
}

bool EventClass::operator==(
  const EventClass &rhs
  ) const
{
  return time == rhs.time;
}

bool EventClass::operator>=(
  const EventClass &rhs
  ) const
{
  return time >= rhs.time;
}

bool EventClass::operator>(
  const EventClass &rhs
  ) const
{
  return time > rhs.time;
}

int EventClass::getTime(
  ) const
{
  return time;
}

int EventClass::getType(
  ) const
{
  return type;
}

int EventClass::getCustomerID(
  ) const
{
  return customerID;
}

ostream& operator<<(
  ostream &os, 
  const EventClass &rhs
  )
{
  os << "Time: " << rhs.getTime() << 
        " Type: " << rhs.getType() << 
        " Customer ID: " << rhs.getCustomerID();

  return os;
}
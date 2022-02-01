#include <iostream>
using namespace std;

#include "RestaurantClass.h"

RestaurantClass::RestaurantClass(
  const int inMinArrivalInterval,
  const int inMaxArrivalInterval,
  const double inLeavingCustomerPercentage,
  const int inLongLineLength,
  const double inServingTimeMean,
  const double inServingTimeStdDev,
  const int inClosingTime
  )
{
  //Use the default event (ARRIVAL of customer 1) as the first event
  //at time = 0.
  eventList.insertValue(currentEvent);

  minArrivalInterval = inMinArrivalInterval;
  maxArrivalInterval = inMaxArrivalInterval;
  leavingCustomerPercentage = inLeavingCustomerPercentage;
  longLineLength = inLongLineLength;
  servingTimeMean = inServingTimeMean;
  servingTimeStdDev = inServingTimeStdDev;
  closingTime = inClosingTime;
  isBusy = false;
  totalNumCustomer = INITIAL_TOTAL_VALUE;
  totalBusyTime = INITIAL_TOTAL_VALUE;
  totalNumCustomerInLine = INITIAL_TOTAL_VALUE;
  numLeavingCustomer = INITIAL_TOTAL_VALUE;
  lengthLongestLine = INITIAL_MAX_VALUE;
  totalWaitingTime = INITIAL_TOTAL_VALUE;
  longestWaitingTime = INITIAL_MAX_VALUE;

  cout << endl;
  cout << "--------------------------START--------------------------" << endl;
}

bool RestaurantClass::getNextEvent(
  )
{
  if (eventList.removeFront(currentEvent))
  {
    return true;
  }

  cout << "---------------------------END---------------------------" << endl;
  return false;
}

void RestaurantClass::handleEvent(
  )
{
  int inTime;
  int inType;
  int inCustomerID;
  if (currentEvent.getType() == ARRIVAL)
  {
    cout << "Customer " << currentEvent.getCustomerID() << 
            " arrives at time " << currentEvent.getTime() << "." << endl;
    //If it is earlier than the closing time, 
    //create a new ARRIVAL event for the next customer.
    inTime = currentEvent.getTime() + 
               getUniform(minArrivalInterval, maxArrivalInterval);
    if (inTime <= closingTime)
    {
      inType = ARRIVAL;
      inCustomerID = currentEvent.getCustomerID() + 1;
      //Store the total number of customers showed up.
      totalNumCustomer = inCustomerID;
      EventClass newArrivalEvent(inTime, inType, inCustomerID);
      eventList.insertValue(newArrivalEvent);
    }
    else
    {
      cout << endl;
      cout << "The closing time is " << closingTime << 
              ". Customers arrive later will not be served." << endl;
      cout << endl;
    }
    //If the server is not busy, create a SERVE_START event 
    //for the current customer.
    if (!isBusy)
    {
      inTime = currentEvent.getTime();
      inType = SERVE_START;
      inCustomerID = currentEvent.getCustomerID();
      EventClass newServeStartEvent(inTime, inType, inCustomerID);
      eventList.insertValue(newServeStartEvent);
    }
    //If the server is busy, consider adding the customer to the queue. 
    //If the customer doesn't like excessively long line and the length 
    //of the line is above the threshold, then the customer will leave 
    //and no new event will be created.
    else
    {
      bool isImPatient = getUniform(0, 100) < leavingCustomerPercentage;
      bool isLongLine = customerQueue.getNumElems() > longLineLength;
      if (isImPatient && isLongLine)
      {
        cout << "Customer " << currentEvent.getCustomerID() << 
                " leaves at time " << currentEvent.getTime() << 
                " due to excessive line length." << endl;
        //Store the total number of customers that left due to excessive 
        //line length.
        numLeavingCustomer += 1;
      }
      else
      {
        customerQueue.enqueue(currentEvent);
        cout << "Customer " << currentEvent.getCustomerID() << 
                " is added to the line at time " << currentEvent.getTime() <<
                "." << endl;
        int numInLine = customerQueue.getNumElems();
        if (numInLine == 1)
        {
          cout << "There is 1 customer in the line." << endl;
        }
        else
        {
          cout << "There are " << numInLine << 
                  " customers in the line." << endl;
        }
        //Store the total number of customers had to wait in line.
        totalNumCustomerInLine += 1;
        //Store the number of customers in the longest line.
        if (numInLine > lengthLongestLine)
        {
          lengthLongestLine = numInLine;
        }
      }
    }
  }
  else if (currentEvent.getType() == SERVE_START)
  {
    cout << "The server starts serving customer " << 
            currentEvent.getCustomerID() << " at time " << 
            currentEvent.getTime() << "." << endl;
    isBusy = true;
    //Create a SERVE_END event for the current customer.
    inTime = currentEvent.getTime() + 
             getNormal(servingTimeMean, servingTimeStdDev);
    //Store the total time that the server was busy.
    totalBusyTime += (inTime - currentEvent.getTime());
    inType = SERVE_END;
    inCustomerID = currentEvent.getCustomerID();
    EventClass newServeEndEvent(inTime, inType, inCustomerID);
    eventList.insertValue(newServeEndEvent);
  }
  else
  {
    cout << "The server finishes serving customer " << 
            currentEvent.getCustomerID() << " at time " << 
            currentEvent.getTime() << "." << endl;
    //Create a SERVE_START event for the first customer in the line. 
    //If the line is empty, then the server will not be busy and no 
    //new event will be created.
    EventClass tempEvent;
    if (customerQueue.dequeue(tempEvent))
    {
      //Store the total waiting time and the longest waiting time 
      //of customers who were in the line.
      int waitingTime = currentEvent.getTime() - tempEvent.getTime();
      totalWaitingTime += waitingTime;
      if (waitingTime > longestWaitingTime)
      {
        longestWaitingTime = waitingTime;
      }
      cout << "The waiting time for customer " << 
              tempEvent.getCustomerID() << " is " << waitingTime << 
              "." << endl;
      inTime = currentEvent.getTime();
      inType = SERVE_START;
      inCustomerID = tempEvent.getCustomerID();
      EventClass newServeStartEvent(inTime, inType, inCustomerID);
      eventList.insertValue(newServeStartEvent);
    }
    else
    {
      isBusy = false;
    }
  }
}

void RestaurantClass::printStats(
  )
{
  cout << "Simulation Results: " << endl;
  cout << endl;

  cout << "Total number of customers that showed up:" << endl;
  cout << totalNumCustomer << endl;

  double busyTimePercentage = ((double) totalBusyTime / 
                              (double) currentEvent.getTime()) * 100;
  cout << "Percentage of time the server was busy helping customers:" << endl;
  cout << busyTimePercentage << "%" << endl;

  double waitingPercentage = ((double) totalNumCustomerInLine /
                             (double) (totalNumCustomer - numLeavingCustomer)) 
                             * 100;
  cout << "Percentage of customers had to wait in line " <<
          "(total number of customers who had waited in line / " <<
          "total number of customers who had been served):" << endl;
  cout << waitingPercentage << "%" << endl;

  cout << "The number of customers left due to excessive line length:" << endl;
  cout << numLeavingCustomer << endl;

  cout << "The length of the longest line throughout this simulation:" << endl;
  cout << lengthLongestLine << endl;

  double avgWaitingTime = ((double) totalWaitingTime / 
                          (double) totalNumCustomerInLine);
  cout << "The average waiting time for each customer " << 
          "who had waited in the line:" << endl;
  cout << avgWaitingTime << endl;

  cout << "The longest waiting time among all the customers:" << endl;
  cout << longestWaitingTime << endl;
}
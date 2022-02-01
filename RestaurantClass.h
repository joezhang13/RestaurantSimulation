#ifndef _RESTAURANTCLASS_H_
#define _RESTAURANTCLASS_H_

#include "SortedListClass.h"
#include "FIFOQueueClass.h"
#include "EventClass.h"
#include "random.h"
#include "input.h"
#include "constants.h"

//This class handles the events in the simulation of a restaurant 
//and calculates some statistics from the simulation.
class RestaurantClass
{
  private:
    SortedListClass< EventClass > eventList; //List of events sorted by time.
    FIFOQueueClass< EventClass > customerQueue; //FIFO queue of customers 
                                                //waiting in line.
    EventClass currentEvent; //The current event to be handled.
    int minArrivalInterval; //The minimum time between one arrival and 
                            //the next arrival.
    int maxArrivalInterval; //The maximum time between one arrival and 
                            //the next arrival.
    double leavingCustomerPercentage; //The percentage of customers who will
                                      //leave if the line is excessively long.
    int longLineLength; //If the number of customers in the line is larger 
                        //than this number, the line is considered to be 
                        //excessively long.
    double servingTimeMean; //The mean of the time for a server to 
                            //serve a customer.
    double servingTimeStdDev; //The standard deviation of the time for 
                              //a server to serve a customer. 
    int closingTime; //The closing time for the restaurant, after which 
                     //no additional customers will be allowed to get in line.
    bool isBusy; //Returns true if the server is busy, 
                 //returns false otherwise.
    int totalNumCustomer; //Total number of customers that showed up.
    int totalBusyTime; //Total time that the server was busy.
    int totalNumCustomerInLine; //Total number of customers 
                                //had to wait in line.
    int numLeavingCustomer; //Total number of customers that arrived 
                            //but left due to excessive line length.
    int lengthLongestLine; //The length of the longest line throughout 
                           //the simulation.
    int totalWaitingTime; //The sum of the waiting time of all the customers 
                          //who were in the queue.
    int longestWaitingTime; //The longest waiting time among 
                            //all the customers.

  public:
    //Constructor.
    RestaurantClass(
      const int inMinArrivalInterval,
      const int inMaxArrivalInterval,
      const double inLeavingCustomerPercentage,
      const int inLongLineLength,
      const double inServingTimeMean,
      const double inServingTimeStdDev,
      const int inClosingTime
      );

    //Get the next event in the event list. Return false if there is 
    //no event in the list.
    bool getNextEvent(
      );

    //Handle the current event.
    void handleEvent(
      );

    //Print the statistics from the simulation result.
    void printStats(
      );
};

#endif // _RESTAURANTCLASS_H_
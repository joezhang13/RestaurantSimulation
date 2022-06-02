#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#include "LinkedNodeClass.h"
#include "SortedListClass.h"
#include "FIFOQueueClass.h"
#include "EventClass.h"
#include "RestaurantClass.h"
#include "random.h"
#include "input.h"
#include "constants.h"

//Name: Zhou Zhang
//Date: 12/04/2019
//Purpose: This project implemented a event-driven simulation of 
//a fast food restaurant. Some important statistics are calculated 
//and output after the simulation. 

int main()
{
  int inSeed; 
  int inMinArrivalInterval;
  int inMaxArrivalInterval;
  double inLeavingCustomerPercentage;
  int inLongLineLength;
  double inServingTimeMean;
  double inServingTimeStdDev;
  int inClosingTime;
  string inFileName;
  ifstream inFile;

  cout << "Read parameters from a TXT file which has " << 
          "the following contents in specified order:" << endl;
  cout << endl;
  cout << "The value of the seed used to generate " << 
          "pseudo-random numbers. (integer)" << endl;
  cout << "The minimum time interval between the arrival of " << 
          "one customer and the next customer (integer)." << endl;
  cout << "The maximum time interval between the arrival of " << 
          "one customer and the next customer (integer)." << endl;
  cout << "The percentage of customers who don't like " << 
          "excessively long lines." << endl;
  cout << "The threshold of the line length above which " << 
          "the line is 'excessively long' (integer)." << endl;
  cout << "The mean of the time serving one customer." << endl;
  cout << "The standard deviation of the time serving one customer." << endl;
  cout << "The closing time after which no new customer " << 
          "will get in line (integer)." << endl;
  cout << endl;
  cout << "Please enter the name of the parameter file: ";
  cin >> inFileName;
  inFile.open(inFileName.c_str());
  if (inFile.fail())
  {
    cout << "Unable to open the parameter file!" << endl;
  }
  else
  {
    if (!input(inFile, inSeed))
    {
      cout << "Unable to read the seed value! " <<
              "Please check the format." << endl;
    }
    else if (!input(inFile, inMinArrivalInterval))
    {
      cout << "Unable to read the minimum time interval! " <<
              "Please check the format." << endl;
    }
    else if (!input(inFile, inMaxArrivalInterval))
    {
      cout << "Unable to read the maximum time interval! " <<
              "Please check the format." << endl;
    }
    else if (!input(inFile, inLeavingCustomerPercentage))
    {
      cout << "Unable to read the percentage of customers who " <<
              "don't like excessively long lines! " <<
              "Please check the format." << endl;
    }
    else if (!input(inFile, inLongLineLength))
    {
      cout << "Unable to read the threshold of the line length! " <<
              "Please check the format." << endl;
    }
    else if (!input(inFile, inServingTimeMean))
    {
      cout << "Unable to read the mean of the serving time! " <<
              "Please check the format." << endl;
    }
    else if (!input(inFile, inServingTimeStdDev))
    {
      cout << "Unable to read the standard deviation of the serving time! " <<
              "Please check the format." << endl;
    }
    else if (!input(inFile, inClosingTime))
    {
      cout << "Unable to read the closing time! " <<
              "Please check the format." << endl;
    }
    else
    {
      inFile.close();
      setSeed(inSeed);
      RestaurantClass restaurantSim(inMinArrivalInterval, 
                                    inMaxArrivalInterval,
                                    inLeavingCustomerPercentage, 
                                    inLongLineLength, 
                                    inServingTimeMean, 
                                    inServingTimeStdDev, 
                                    inClosingTime);
      while (restaurantSim.getNextEvent())
      {
        restaurantSim.handleEvent();
      }
      restaurantSim.printStats();
    }
  }

  return 0;
}

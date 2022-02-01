#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#include "input.h"

bool input(ifstream &inFile, int &val)
{
  bool success = false;

  if (inFile.eof())
  {
    cout << "EOF before reading!" << endl;
  }
  else if (inFile.fail())
  {
    inFile.clear();
    inFile.ignore(NUM_IGNORE, CHAR_IGNORE);
    cout << "Error found in reading! An integer is expected." << endl;
  }
  else
  {
    inFile >> val;
    inFile.ignore(NUM_IGNORE, CHAR_IGNORE);
    success = true;
  }

  return success;
}

bool input(ifstream &inFile, double &val)
{
  bool success = false;

  if (inFile.eof())
  {
    cout << "EOF before reading!" << endl;
  }
  else if (inFile.fail())
  {
    inFile.clear();
    inFile.ignore(NUM_IGNORE, CHAR_IGNORE);
    cout << "Error found in reading! An double-precision number " <<
            "is expected." << endl;
  }
  else
  {
    inFile >> val;
    inFile.ignore(NUM_IGNORE, CHAR_IGNORE);
    success = true;
  }

  return success;
}
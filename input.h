#ifndef _INPUT_H_
#define _INPUT_H_

#include "constants.h"

//This function inputs an integer from the ifstream to a variable
//with error handling.
bool input(ifstream &inFile, int &val);

//This function inputs an double-precision floating-point number 
//from the ifstream to a variable with error handling.
bool input(ifstream &inFile, double &val);

#endif // _INPUT_H_
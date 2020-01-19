/*
  File used to declare the global functions randomInt() and weightedProbability()

  Functiona used in main.cpp, arriveEvent.cpp, and orderEvent.cpp

  See globalFunc.cpp for function definition
*/

#ifndef GLOBALF_H
#define GLOBALF_H

#include <ctime>
#include <cstdlib>
#include <vector>
using namespace std;

//returns a random integer between given integers i and j
unsigned int randomInt(unsigned int i, unsigned int j);

//returns a random integer between given integers i and j using the weights given in the vector
unsigned int weightedProbability(vector<int> v, unsigned int i, unsigned int j);

#endif

/*
  File used to define the global functions randomInt() and weightedProbability()

  Functions used in main.cpp, arriveEvent.cpp, and orderEvent.cpp

  See globalFunc.h for function declarations
*/
#include "globalFunc.h"
#include <ctime>
#include <cstdlib>
#include <vector>
using namespace std;

//Returns a random integer between i and j
unsigned int randomInt(unsigned int i, unsigned int j) {
  return rand() % j + i;
}

//returns a random integer between given integers i and j using the weights given in the vector v
unsigned int weightedProbability(vector<int> v, unsigned int i, unsigned int j) {
  //Find total weight
  int total = 0;
  for(int k = 0; k < v.size() - 1; k++) {
    total += v[k];
  }

  //Random int between 1 and total weight
  int n = randomInt(1, total);

  //returning number between i and j based on weight
  int count = 0;
  int count2 = 0;
  for(int k = i; k <= j; k++) {
    count += v[count2++];
    if(n <= count) {
      return k;
    }
  }
  return 1;
}

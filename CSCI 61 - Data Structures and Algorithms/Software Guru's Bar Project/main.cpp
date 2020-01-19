/*
  The main code of the program

  Adds initial events to the priority queue and then runs the simulation

  prints out total profits at the end of the simulation
*/
#include "globalVars.h"
#include "globalFunc.h"
#include "arriveEvent.h"
#include <iostream>
using namespace std;

Bar bar; //Globally defined object bar used throught the program. Declared in glabalVars.h

// add arrive events to the priority queue and run the simulation
int main() {
  unsigned int t = 0;

  //Initializing seed used by randomInt() (function declared in globalFunc.h and defined in globalFunc.cpp)
  srand(time(NULL));

  //vector used to store weighted probability of number of group members
  vector<int> v;
  v.push_back(10);
  v.push_back(40);
  v.push_back(20);
  v.push_back(20);
  v.push_back(5);
  for(int i = 0; i < 5; i++) {
    v.push_back(1);
  }

  // Adding 240 minutes of arrivee events to the PQ
  while (t < 240) {
  t += randomInt(2, 5);

  bar.simulation.scheduleEvent(new ArriveEvent(t, weightedProbability(v, 1, 5)));
  }

  //Running the simulation
  bar.simulation.run();

  //Printing out total profits after simulation has ended
  cout << "Total Profit: " << bar.profit << endl;
return 0;
}

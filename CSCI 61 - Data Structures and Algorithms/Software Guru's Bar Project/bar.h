#ifndef BAR_H
#define BAR_H

#include "simulationFramework.h"
#include <iostream>
using namespace std;

class Bar {
  /*
    Class used to define the bar object

    Variables keep track of numbers of seats (capacity), and profit (profit)

    Member functions define behavior when groups of people arrive, order, and leave
  */
public:
  Bar() : capacity(60), profit(0.0) {}


  bool seat(unsigned int n);
  void order(unsigned int b);
  void reorder(unsigned int b);
  void leave(unsigned int n);

  unsigned int capacity;
  double profit;

  //Simulation Framework object that contains the priority queue used to define the order of events
  SimulationFramework simulation;
};

#endif

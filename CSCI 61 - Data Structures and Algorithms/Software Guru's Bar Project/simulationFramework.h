#ifndef SIMULATIONFRAMEWORK_H
#define SIMULATIONFRAMEWORK_H

#include "queue.h"
#include <queue>
#include <vector>
#include "event.h"
using namespace std;

class SimulationFramework {
  /*
    Class defining the framework used for the simulation.

    Contains the priority queue used to order events
  */
public:
  SimulationFramework() : currentTime(0) {}

  //Adds a given event object to the priority queue (eventQueue)
  void scheduleEvent(Event * newEvent) { eventQueue.in(newEvent); }

  //Starts the simulation
  void run();

  //Variable keeping track of the current time
  unsigned int currentTime;

protected:
  //The priority queue object used for the simulation
  MinPQ<Event *> eventQueue;
  //priority_queue <Event *, vector<Event *>, EventComparison> eventQueue; STL PQ USED FOR TESTING
};

#endif

/*
  File used to define the run member function of the SimulationFramework class

  See simulationFramework.h for class definition
*/

#include "simulationFramework.h"

//Starts the simulation
void SimulationFramework::run() {
  //takes the highest priority element from the queue, executes it, then deletes it
  //Runs until the queue is empty
  while(!eventQueue.isEmpty()) {
    //Takes event with the lowest time from the queue
    Event * nextEvent = eventQueue.delMin();

    //advances the current time based on the time of current event
    currentTime = nextEvent->time;

    //executes the event
    nextEvent->processEvent();

    //deletes the event and frees allocated data
    nextEvent = nullptr;
    delete nextEvent;

  }
}

/*
  Used to define the member function processEvent() of ArriveEvent Class

  function and class declarations found in arriveEvent.h
*/
#include "arriveEvent.h"
#include "orderEvent.h"
#include "globalVars.h"
#include "globalFunc.h"
#include <vector>
using namespace std;

//Definition of virtual processEvent() function.
//If the groupSize is smaller than capacity of the bar, then a new orderEvent will be added to the PQ
void ArriveEvent::processEvent() {
  if(bar.seat(groupSize)) {

    bar.simulation.scheduleEvent(new OrderEvent(bar.simulation.currentTime + randomInt(1, 5), groupSize));
  }
}

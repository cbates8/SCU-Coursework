/*
  Used to define the member function processEvent() of OrderEvent Class

  function and class declarations found in orderEvent.h
*/
#include "orderEvent.h"
#include "reorderEvent.h"
#include "leaveEvent.h"
#include "globalVars.h"
#include "globalFunc.h"
#include <vector>
using namespace std;

//Definition of virtual processEvent() function.
//Each member of group orders random drink. Profits are increased depending on type of drink
void OrderEvent::processEvent() {
  vector<int> v;
  v.push_back(15);
  v.push_back(60);
  v.push_back(25);

  for(int i = 0; i < groupSize; i++) {
    bar.order(weightedProbability(v, 1, 3));
  }
  //Random amount of time that they stay at the bar
  int t = bar.simulation.currentTime + randomInt(15, 35);

  //determine if they leave or re-order
  if(randomInt(1, 3) == 1) {
    //Adds new orderEvent to the priority queue
    bar.simulation.scheduleEvent(new ReorderEvent(t, groupSize));
  }
  else {
    //Adds new leaveEvent to the priority queue
    bar.simulation.scheduleEvent(new LeaveEvent(t, groupSize));
  }

}

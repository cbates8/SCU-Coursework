/*
  Used to define the member function processEvent() of LeaveEvent Class

  function and class declarations found in leaveEvent.h
*/
#include "leaveEvent.h"
#include "globalVars.h"

//Definition of virtual processEvent() function.
//the group leaves the bar
void LeaveEvent::processEvent() {
  bar.leave(groupSize);
}

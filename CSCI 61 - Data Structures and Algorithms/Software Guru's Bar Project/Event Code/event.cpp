/*
  File used to define the eventCompare member function of the event class

  See event.h for class definition
*/

#include "event.h"

//If this event has a greater time than that of given event, returns true. Otherwise returns false
bool eventCompare(Event * left, Event * right) { return left->time > right->time; }

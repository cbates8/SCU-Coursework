#ifndef ARRIVEEVENT_H
#define ARRIVEEVENT_H

#include "event.h"

class ArriveEvent : public Event {
  /*
    Class defining an event where a group Arrives at the bar
    If there are evough tables they are seated, otherwise they leave
    Subclass of Event Class
  */
public:
  ArriveEvent (unsigned int time, unsigned int size) : Event(time), groupSize(size) {}

  //One definition of the virtual processEvent() from the Event class
  void processEvent();

protected:
  unsigned int groupSize;
};

#endif

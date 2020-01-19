#ifndef LEAVEEVENT_H
#define LEAVEEVENT_H

#include "event.h"

class LeaveEvent : public Event {
  /*
    Class defining an event where a group leaves the Bar
    Subclass of Event Class
  */
public:
  LeaveEvent(unsigned int time, unsigned int size) : Event(time), groupSize(size) {}

  //One definition of the virtual processEvent() from the Event class
  void processEvent();

protected:
  unsigned int groupSize;
};

#endif

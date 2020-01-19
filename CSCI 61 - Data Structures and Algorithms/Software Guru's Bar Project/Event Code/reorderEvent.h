#ifndef REORDEREVENT_H
#define REORDEREVENT_H

#include "event.h"

class ReorderEvent : public Event {
  /*
    Class defining an event where a group reorders, is served, and profits are incresed
    Subclass of Event Class
  */
public:
  ReorderEvent (unsigned int time, unsigned int size) : Event(time), groupSize(size) {}

  //One definition of the virtual processEvent() from the Event class
  void processEvent();

protected:
  unsigned int groupSize;
};


#endif

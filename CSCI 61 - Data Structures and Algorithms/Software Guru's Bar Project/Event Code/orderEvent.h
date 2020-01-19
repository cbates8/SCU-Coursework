#ifndef ORDEREVENT_H
#define ORDEREVENT_H

#include "event.h"

class OrderEvent : public Event {
  /*
    Class defining an event where a group orders, is served, and profits are incresed
    Subclass of Event Class
  */
public:
  OrderEvent (unsigned int time, unsigned int size) : Event(time), groupSize(size) {}

  //One definition of the virtual processEvent() from the Event class
  void processEvent();

protected:
  unsigned int groupSize;
};


#endif

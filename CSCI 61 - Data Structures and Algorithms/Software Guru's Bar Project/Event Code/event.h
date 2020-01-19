#ifndef EVENT_H
#define EVENT_H

class Event {
  /*
    Class giving a general definition of an event object
    has 3 subclasses: arriveEvent, orderEvent, and leaveEvent
  */
public:
  Event(unsigned int t) : time(t) {}

  //Variable keeps track of the time associated with the specific event
  unsigned int time;

  //Member functino used in queue.h to determine if the current object has a greater time than a given event object
  bool eventCompare(Event * right) { return this->time > right->time; }

  //virtual Member function defined in arriveEvent, orderEvent, and leaveEvent
  virtual void processEvent() {}

};

/*
class EventComparison {
public:
  bool operator ( ) (Event * left, Event * right) { return left->time > right->time; }
};
*/
#endif

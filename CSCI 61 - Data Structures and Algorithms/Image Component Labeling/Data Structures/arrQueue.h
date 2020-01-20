#ifndef ARRQUEUE_H
#define ARRQUEUE_H

#include <cstdlib>
using namespace std;

template <typename T>
class arrQueue {
public:
  typedef std::size_t st;
  static const st CAPACITY = 50;

  arrQueue() : count(0), first(0), last(CAPACITY - 1) {}

  void pop();
  void push(const T& entry);

  bool empty() const { return (count == 0); }
  T front() const;
  st size() const { return count; }

private:
  T data[CAPACITY];
  st first;
  st last;
  st count;
  st next_index(st i) const { return (i + 1) % CAPACITY; }
};

#endif

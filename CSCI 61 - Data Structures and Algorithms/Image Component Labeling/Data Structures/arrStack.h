#ifndef ARRSTACK_H
#define ARRSTACK_H

#include <cstdlib>
using namespace std;

template <typename T>
class arrStack {
public:
  typedef std::size_t st;
  static const st CAPACITY = 50;

  arrStack() { used = 0; }

  void push(const T& entry);
  void pop();

  bool empty() const { return (used == 0); }
  st size() const { return used; }
  T top() const;

private:
  T data[CAPACITY];
  st used;
};

#endif

#include <cassert>
#include "arrStack.h"
using namespace std;

template <typename T>
const typename arrStack<T>::st arrStack<T>::CAPACITY;

template <typename T>
void arrStack<T>::push(const T& entry) {
  assert(size() < CAPACITY);
  data[used] = entry;
  ++used;
}

template <typename T>
void arrStack<T>::pop() {
  assert(!empty());
  --used;
}

template <typename T>
T arrStack<T>::top() const {
  assert(!empty());
  return data[used-1];
}

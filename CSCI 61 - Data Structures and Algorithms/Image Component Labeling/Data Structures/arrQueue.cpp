#include <cassert>
#include "arrQueue.h"
using namespace std;

template <typename T>
const typename arrQueue<T>::st arrQueue<T>::CAPACITY;

template <typename T>
T arrQueue<T>::front() const {
  assert(!empty());
  return data[first];
}

template <typename T>
void arrQueue<T>::pop() {
  assert(!empty());
  first = next_index(first);
  count--;
}

template <typename T>
void arrQueue<T>::push(const T& entry) {
  assert(size() < CAPACITY);
  last = next_index(last);
  data[last] = entry;
  count++;
}

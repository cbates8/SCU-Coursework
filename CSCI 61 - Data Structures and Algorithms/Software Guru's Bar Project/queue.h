#ifndef QUEUE_H
#define QUEUE_H

#include "event.h"
#include <vector>
using namespace std;

template<typename T>
class MinPQ {
  /*
    MinPQ class implements a priority queue based on MinHeap using a vector

    Sorts events based on their time. Lowest time at the front of the queue, lowest in back.

  */
public:
  //Constructor initializes the vector with size 1
  MinPQ() { pq.resize(1); }

  //returns true if the queue is empty. False otherwise
  bool isEmpty() { return pq.empty(); }

  //Swaps place of to elements in the queue
  void exch(int i, int j) { T p = pq[i]; pq[i] = pq[j]; pq[j] = p; }

  //Functions used to sort elements in the queue based on their priority
  void swim(int k);
  void sink(int k, int n);

  //inserts new element into the queue
  void in(T key);

  //returns the element with the smallest key (highest priority) then deletes it from the queue
  T delMin();
private:
  vector<T> pq; //Vector object used to impliment the priority queue
};

//IF the time of the event at index k is smaller than its parent (k/2)
//then it swaps them and continues unitl it is in the right place
template<typename T>
void MinPQ<T>::swim(int k) {
  while (k > 1 && pq[k/2]->eventCompare(pq[k])) {
    exch(k, k/2);
    k /= 2;
  }
}

//If the time of the event at index k is greater than its children, then they swap
//Continues until its time is smaller than its children
template<typename T>
void MinPQ<T>::sink(int k, int n) {
  while (2*k <= n) {
    int j = 2*k;
    if (j < n && pq[j]->eventCompare(pq[j+1])) {
      j++;
    }
    if (!pq[k]->eventCompare(pq[j])) {
      break;
    }
    exch(k, j);
    k = j;
  }
}

//adds element to the back of the queue, then swims the queue up to its rightful spot
template<typename T>
void MinPQ<T>::in(T key) {
  pq.push_back(key);
  swim(pq.size()-1);
}

//Swaps first element with the last, then sinks the new first element to its rightful place
//deletes then returns the former first element in the queue
template<typename T>
T MinPQ<T>::delMin() {
  T min = pq[1];
  exch(1, pq.size()-1);
  sink(1, pq.size()-2);
  pq.pop_back();
  return min;
}


#endif

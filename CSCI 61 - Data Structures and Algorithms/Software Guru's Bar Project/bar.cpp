/*
  File used to define member functions of the Bar class

  See bar.h for class definition
*/

#include <iostream>
#include "bar.h"
#include "simulationFramework.h"

//Defines behavior when patrons arrive at the bar
bool Bar::seat (unsigned int n) {
  cout << "Time: " << simulation.currentTime;
  cout << " Group of " << n << " customers arrives ...";

  //If sufficient room, seat customers. Otherwise, turn them away
  if (n < capacity) {
    cout << " Group is seated" << endl;
    capacity -= n;
    return true;
  }
  else {
    cout << " No room, group leaves" << endl;
    return false;
  }
}

//Defines behavior when patrons order
//Serve beer and update profit based on beer type
void Bar::order (unsigned int b) {
  cout << "Time: " << simulation.currentTime;
  cout << " Served order for beer " << b << endl;

  //Regular beer: $2
  if(b == 1) {
    profit += 2;
  }
  //Imported beer: $3
  else if(b == 2) {
    profit += 3;
  }
  //Special Beer: $4
  else {
    profit += 4;
  }
}

//Defines behavior when patrons reorder
//Serve beer and update profit based on beer type
void Bar::reorder (unsigned int b) {
  cout << "Time: " << simulation.currentTime;
  cout << " Served order for beer " << b << endl;

  //Regular beer: $2
  if(b == 1) {
    profit += 2;
  }
  //Imported beer: $3
  else if(b == 2) {
    profit += 3;
  }
  //Special Beer: $4
  else {
    profit += 4;
  }
}

//serve beer and update profit based on beer type
//customers leave, freeing chairs
void Bar::leave (unsigned int n) {
  cout << "Time: " << simulation.currentTime;
  cout <<" Group of size " << n << " leaves" << endl;
  capacity += n;
}

#include <iostream>
#include <ctime>
#include <cstdlib>
#include "arrStack.cpp"
#include "arrQueue.cpp"
using namespace std;

struct pixel {
  int label; //label of the group of elements this pixel is part of
  int order; //position in the order by which this pixel was found
};

struct position {
  int row;
  int col;
};

//Creating a 2d array using pointers
void createArray(pixel ** &p, int rows, int columns) {
  // create pointers for the rows
  p = new pixel * [rows];

  // get memory for each row
  for (int i = 0; i < rows; i++)
      p[i] = new pixel [columns];
}

//Fills each grid with pixels with labels of 0 or 1 (ammount of 1s depends on density). All pxels are given 0 order
void initializeGrids(int size, double den, pixel ** &dfsGrid, pixel ** &bfsGrid) {
  double r;
  for(int row = 1; row <= size; row++) {
    for(int col = 1; col <= size; col++) {
      r = (rand() % 100) * 0.01; //Generates random decimal between 0 and 1
      if(r < den) {
        dfsGrid[row][col].label = 1;
        dfsGrid[row][col].order = 0;
        bfsGrid[row][col].label = 1;
        bfsGrid[row][col].order = 0;
      }
      else {
        dfsGrid[row][col].label = 0;
        dfsGrid[row][col].order = 0;
        bfsGrid[row][col].label = 0;
        bfsGrid[row][col].order = 0;
      }
    }
  }
}

//Prints each grid to the console. DFS grid first, followed by BFS
void printGrids(int size, pixel ** &dfsGrid, pixel ** &bfsGrid) {
  cout << "Depth First Search Grid" << endl;
  for(int row = 1; row <= size; row++) {
    for(int col = 1; col <= size; col++) {
      cout << dfsGrid[row][col].label << ',' << dfsGrid[row][col].order << "  ";
      //Folling If/Else statements determine spacing based on the value of label and order. Soley for visual purposes
      if(dfsGrid[row][col].label/10 < 1 && dfsGrid[row][col].order/10 < 1) {
        cout << "  ";
      }
      else if(dfsGrid[row][col].label/10 < 1 || dfsGrid[row][col].order/10 < 1) {
        cout << " ";
      }
      else if(dfsGrid[row][col].label/10 >= 1 && dfsGrid[row][col].order/10 >= 1) {
        cout << "";
      }
    }
    cout << endl;
  }
  cout << endl;

  cout << "Breadth First Search Grid" << endl;
  for(int row = 1; row <= size; row++) {
    for(int col = 1; col <= size; col++) {
      cout << bfsGrid[row][col].label << ',' << bfsGrid[row][col].order << "  ";
      if(bfsGrid[row][col].label/10 < 1 && bfsGrid[row][col].order/10 < 1) {
        cout << "  ";
      }
      else if(bfsGrid[row][col].label/10 < 1 || bfsGrid[row][col].order/10 < 1) {
        cout << " ";
      }
      else if(bfsGrid[row][col].label/10 >= 1 && bfsGrid[row][col].order/10 >= 1) {
        cout << "";
      }
    }
    cout << endl;
  }
  cout << endl;
}

//Scans through the grid using the depth first method. Modifies dfsGrid
void DFS(pixel ** &dfsGrid, int row, int col, int cLabel) {

  //initializing offsets
  position offset[4];
  offset[0].row = 0; offset[0].col = 1; //right
  offset[1].row = 1; offset[1].col = 0; //down
  offset[2].row = 0; offset[2].col = -1; //left
  offset[3].row = -1; offset[3].col = 0; //up

  arrStack<position> s; // Creating the Stack (implemented as an array)

  position currentPos, nextPos;
  currentPos.row = row;
  currentPos.col = col;
  int current = 0, last = 3, counter = 1;

  dfsGrid[currentPos.row][currentPos.col].label = cLabel;
  dfsGrid[currentPos.row][currentPos.col].order = counter;
  s.push(currentPos);

  do {
    while(current <= last) {
      nextPos.row = currentPos.row + offset[current].row;
      nextPos.col = currentPos.col + offset[current].col;

      if(dfsGrid[nextPos.row][nextPos.col].label == 1) {
        break;
      }
      current++;
    }

    if(current <= last) {
      s.push(currentPos);
      currentPos.row = nextPos.row;
      currentPos.col = nextPos.col;
      counter++;
      dfsGrid[currentPos.row][currentPos.col].label = cLabel;
      dfsGrid[currentPos.row][currentPos.col].order = counter;
      current = 0;
    } else {
      currentPos = s.top();
      s.pop();
      current = 0;
    }
  } while(!s.empty());
}

//Scans through the grid using the breadth first method. Modifies bfsGrid
void BFS(pixel ** &bfsGrid, int row, int col, int cLabel) {

  position offset[4];
  offset[0].row = 0; offset[0].col = 1;
  offset[1].row = 1; offset[1].col = 0;
  offset[2].row = 0; offset[2].col = -1;
  offset[3].row = -1; offset[3].col = 0;

  arrQueue<position> q; // Creating the Queue (implemented as an array)

  position currentPos, nextPos;
  currentPos.row = row;
  currentPos.col = col;
  int current = 0, last = 3, counter = 1;
  bool found;

  bfsGrid[currentPos.row][currentPos.col].label = cLabel;
  bfsGrid[currentPos.row][currentPos.col].order = counter;
  q.push(currentPos);

  do {
    q.pop();
    found = false;

    for(int i = current; i <= last; i++) {
      nextPos.row = currentPos.row + offset[i].row;
      nextPos.col = currentPos.col + offset[i].col;

      if(bfsGrid[nextPos.row][nextPos.col].label == 1) {
        counter++;
        found = true;
        bfsGrid[nextPos.row][nextPos.col].label = cLabel;
        bfsGrid[nextPos.row][nextPos.col].order = counter;
        q.push(nextPos);
      }
    }

    if(q.empty()) {
      break;
    }

    currentPos = q.front();
  }while(!q.empty() || found);
}

// initiates the scanning and labeling of the grids using Depth first and Breadth first methods
void labelGrids(int size, pixel ** &dfsGrid, pixel ** &bfsGrid) {
  int componentLabel = 1;
  for(int row = 1; row <= size; row++) {
    for(int col = 1; col <= size; col++) {
      if(dfsGrid[row][col].label == 1) {
        componentLabel++;
        DFS(dfsGrid, row, col, componentLabel); //Scans using depth first method
        BFS(bfsGrid, row, col, componentLabel); //Scans using breadth first method
      }
    }
  }
}

int main() {
  int dimension;
  double density;

  srand(time(NULL)); //Setting seed for random

  //Taking user input for dimension of image and density of components
  cout << "Enter a dimension (between 5 and 20): ";
  cin >> dimension;
  cout << "Enter a density (between 0 and 1): ";
  cin >> density;
  cout << endl;


  //Creating pointers to 2-d arrays for each scanning method (depth first and breadth first)
  pixel **dfsGrid;
  pixel **bfsGrid;

  //creating image grids using 2-d arrays
  createArray(dfsGrid, dimension + 2, dimension + 2);
  createArray(bfsGrid, dimension + 2, dimension + 2);

  initializeGrids(dimension, density, dfsGrid, bfsGrid); //filling grids
  cout << "Pre-Labeling" << endl << endl;
  printGrids(dimension, dfsGrid, bfsGrid);
  labelGrids(dimension, dfsGrid, bfsGrid);
  cout << "Post-Labeling" << endl << endl;
  printGrids(dimension, dfsGrid, bfsGrid);

  return 0;
}

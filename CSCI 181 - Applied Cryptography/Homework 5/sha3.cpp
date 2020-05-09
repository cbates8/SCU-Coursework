/*
CSCI 181 Homework 5
Author: Casey Bates
sha3.cpp - Coding the first 3 fuctions used in the SHA-3 hash function: Theta, Rho, and Pi
*/

#include <iostream>
#include <fstream>
using namespace std;

//Converts 1-D array v[0 ... 1599] to 3-D array a[0...4][0...4][0...63]
void inputSHA3(int v[], int a[][5][64]) {
  for(int i = 0; i < 5; i++) {
    for(int j = 0; j < 5; j++) {
      for(int k = 0; k < 64; k++) {
        a[i][j][k] = v[64*(5*j + i) + k];
      }
    }
  }
}

//Converts 3-D array a[0...4][0...4][0...63] to 1-D array v[0 ... 1599]
void outputSHA3(int a[][5][64], int v[]) {
  for(int i = 0; i < 5; i++) {
    for(int j = 0; j < 5; j++) {
      for(int k = 0; k < 64; k++) {
        v[64*(5*j + i) + k] = a[i][j][k];
      }
    }
  }
}

//Implementation of the Theta function from SHA3
void theta(int ain[][5][64], int aout[][5][64]) {
  int rightCol = 0, leftCol = 0;

  for(int i = 0; i < 5; i++) {
    for(int j = 0; j < 5; j++) {
      for(int k = 0; k < 64; k++) {
        for(int jPrime = 0; jPrime < 5; jPrime++) {
          leftCol = (leftCol + ain[(i-1) % 5][jPrime][k]) % 2; // Computes the sum of the column to the left fo the original bit
          rightCol = (rightCol + ain[(i+1) % 5][jPrime][(k-1) % 64]) % 2; //Computes the sum of the column to the right and one posiiton in front of the original bit
        }
        aout[i][j][k] = (ain[i][j][k]) ^ (leftCol) ^ (rightCol);
        leftCol = 0;
        rightCol = 0;
      }
    }
  }
}

//Implementation of the Rho function from SHA3 using the given rhoMatrix
void rho(int ain[][5][64], int aout[][5][64]) {
  int rhoMatrix[5][5] = { {0,36,3,41,18}, {1,44,10,45,2}, {62,6,43,15,61}, {28,55,25,21,56}, {27,20,39,8,14}};

  for(int i = 0; i < 5; i++) {
    for(int j = 0; j < 5; j++) {
      for(int k = 0; k < 64; k++) {
        aout[i][j][k] = ain[i][j][(k - rhoMatrix[i][j]) % 64];
      }
    }
  }
}

//Implementation of the Pi function from SHA3
void pi(int ain[][5][64], int aout[][5][64]) {
  for(int i = 0; i < 5; i++) {
    for(int j = 0; j < 5; j++) {
      for(int k = 0; k < 64; k++) {
        aout[j][(2*i + 3*j) % 5][k] = ain[i][j][k];
      }
    }
  }
}

int main() {
  ifstream inFile;
  int v[1600];
  int a[5][5][64];
  int aout[5][5][64];

  inFile.open("sha3in.txt");

  //Check if file was opened successfully
  if(!inFile) {
    cout << "Unable to open file";
    exit(1);
  }

  //Copying contents of file into array a
  char x;
  for(int i = 0; i < 1600; i++) {
    inFile >> x;
    v[i] = x - '0'; //x - '0' will convert x from a char to an int
  }

  inputSHA3(v, a);

  //Checking each function using given values for a[4][3][9...18] and printing desired values for a[2][3][11 ... 20]
  theta(a, aout);
  cout << "Theta: " << endl;
  //printing calculated and given values of a[4][3][9...18] for comparison
  for(int i = 9; i < 19; i++) {
    cout << aout[4][3][i];
  }
  cout << endl;
  cout << "0011011000" << endl;

  //Printing calculated value of a[2][3][11...20]
  cout << "a[2][3][11...20]: ";
  for(int i = 11; i < 21; i++) {
    cout << aout[2][3][i];
  }
  cout << endl;
  cout << endl;

  rho(a, aout);
  cout << "Rho: " << endl;
  //printing calculated and given values of a[4][3][9...18] for comparison
  for(int i = 9; i < 19; i++) {
    cout << aout[4][3][i];
  }
  cout << endl;
  cout << "0110011001" << endl;

  //Printing calculated value of a[2][3][11...20]
  cout << "a[2][3][11...20]: ";
  for(int i = 11; i < 21; i++) {
    cout << aout[2][3][i];
  }
  cout << endl;
  cout << endl;

  pi(a, aout);
  cout << "Pi: " << endl;
  //printing calculated and given values of a[4][3][9...18] for comparison
  for(int i = 9; i < 19; i++) {
    cout << aout[4][3][i];
  }
  cout << endl;
  cout << "0110110001" << endl;

  //Printing calculated value of a[2][3][11...20]
  cout << "a[2][3][11...20]: ";
  for(int i = 11; i < 21; i++) {
    cout << aout[2][3][i];
  }
  cout << endl;

  inFile.close();
  return 0;
}

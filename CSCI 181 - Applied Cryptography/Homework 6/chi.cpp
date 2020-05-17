/*
CSCI 181 Homework 6-2
Author: Casey Bates
chi.cpp - Coding the Chi step of the SHA-3 hash function
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

//Implementation of the Chi function from SHA3
void chi(int ain[][5][64], int aout[][5][64]) {
  for(int i = 0; i < 5; i++) {
    for(int j = 0; j < 5; j++) {
      for(int k = 0; k < 64; k++) {
        aout[i][j][k] = ain[i][j][k] ^ (!(ain[(i+1) % 5][j][k]) && ain[(i+2) % 5][j][k]);
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
  chi(a, aout);
  cout << "Chi: " << endl;
  cout << "a[4][3][9...18]: Given Value vs Calculated" << endl;
  //printing calculated and given values of a[4][3][9...18] for comparison
  for(int i = 9; i < 19; i++) {
    cout << aout[4][3][i];
  }
  cout << endl;
  cout << "0110100001" << endl;
  cout << endl;

  //Printing calculated value of a[2][3][11...20]
  cout << "a[2][3][11...20]: ";
  for(int i = 11; i < 21; i++) {
    cout << aout[2][3][i];
  }
  cout << endl;

  inFile.close();
  return 0;
}

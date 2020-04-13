/* CSCI 181 Homework 1
Author: Casey Bates
kasiski.cpp - Creating Histograms of letter frequency using the Kasiski method
*/
#include <iostream>
#include <string>
using namespace std;

//Function that creates simple histograms of the frequency of each letter, following the kasiski method
//Will create amount of histograms equal to parameter kSize
void histogram(int kSize, string ct) {
  string alphabet = "abcdefghijklmnopqrstuvwxyz";
  int counter = 0;

  //These loops will check if each letter of the alphabet is equal to [0->ct.size]*kSize + [0->kSize]
  //This algorithm attempts to replicate the grid used in the lecture notes with the ciphertext split into kSize collumns
  for (int i = 0; i < kSize; i++) { //This loop cycles through each collumn in the grid
    cout << endl << "[";

    for(int j = 0; j < 26; j++) { //This loop cycles through the letters of the alphabet so we can count how many times each appears
      for(int l = 0; l < ct.size(); l++) { //This loop cycles through each row in the grid
        //Counter will increase if the current letter matches the letter in the current cell
        if (ct[(l*kSize) + i] == alphabet[j]) {
          counter += 1;
        }
      }
      cout << counter << ", "; //Prints the number of times the letter appeared in the Ciphertext
      counter = 0; //Resets the counter
    }
    cout << ']' << endl;
  }
}

int main() {
  string input;
  int size;

  cout << "Enter Ciphertext: ";
  cin >> input;
  cout << "Enter Keysize: ";
  cin >> size;

  cout << "[a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z]" << endl; //Alphabetic string will apear above the histogram outputs for visual reference
  histogram(size, input); //Calls the histogram function, which internally prints each histogram to the console

  return 0;
}

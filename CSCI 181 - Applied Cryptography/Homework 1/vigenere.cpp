/* CSCI 181 Homework 1
Author: Casey Bates
vigenere.cpp - Encryption and Decryption of the Vigenere Cipher
*/
#include <iostream>
#include <string>
using namespace std;

// Generate a key the size of the Plaintext/Ciphertext given a keyword
string keyGen(string str, string key) {
  int size = str.size();
  int count = 0;
  while(key.size() != str.size()) {
    if (size == count) {
      count = 0;
    }

    key.push_back(key[count]);
    count++;
  }

  return key;
}

//Encryption algorithm for the Vigenre cipher with plaintext and a key(from keyGen()) as inputs
string vEncrypt (string pt, string key) {
  string ct;
  int c;

  for (int i = 0; i < pt.size(); i++) {
    c = (pt[i] + key[i]) %26; //(M[i] + K[i]) mod 26 = Ciphertext

    c += 'A'; //Encoding the integer c into the english letter it is meant to represent

    ct.push_back(c);
  }

  return ct;
}

//Decryption algorithm for the Vigenre cipher with ciphertext and a key(from keyGen()) as inputs
string vDecrypt (string ct, string key) {
  string pt;
  int p;

  for (int i = 0; i < ct.size(); i++) {
    p = (ct[i] - key[i] + 26) %26; //(C[i] - K[i] + 26) mod 26 = Plaintext

    p += 'A'; //Encoding the integer p into the english letter it is meant to represent

    pt.push_back(p);
  }
   return pt;
}

int main() {
  string input, keyword;
  char operation;

  /* I made a simple UI to make it easier to test and so the plaintext/ciphertext and key arent hard-coded into the program.
     It asks the user if they would like to encrypt or decrypt, then asks for the keyword and plaintext or ciphertext depending of the mode they chose.*/
  cout << "Encryption or Decryption? [E/D]:";
  cin >> operation;
  cout << endl;

  if (operation == 'E' || operation == 'e') {
    cout << "Enter Plaintext (no spaces):";
    cin >> input;
    cout << endl << "Enter Keyword:";
    cin >> keyword;
    cout << endl;

    string key = keyGen(input, keyword); //Generating the full key from given keyword
    string cipherText = vEncrypt(input, key); //calling the Encryption function with plaintext and key as parameters

    cout << "Ciphertext: " << cipherText << endl;
  } else {
    cout << "Enter Ciphertext (no spaces):";
    cin >> input;
    cout << endl << "Enter Keyword:";
    cin >> keyword;
    cout << endl;

    string key = keyGen(input, keyword); //Generating the full key from given keyword
    string plainText = vDecrypt(input, key); //calling the decryption function with plaintext and key as parameters

    cout << "Plaintext: " << plainText << endl;
  }

  return 0;
}

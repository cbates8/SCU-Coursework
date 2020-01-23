#include <stdint.h>


int32_t Bits2Signed(int8_t []) ; // Convert array of bits to signed int.
uint32_t Bits2Unsigned(int8_t []) ; // Convert array of bits to unsigned int
void Increment(int8_t []) ; // Add 1 to value represented by bit pattern
void Unsigned2Bits(uint32_t, int8_t []) ; // Opposite of Bits2Unsigned.

uint32_t Bits2Unsigned(int8_t bits[8]) { //Sums all the bits using the formula given in the lab handout
	uint32_t n = 0;
	for (int i = 7; i >= 0; i--) {
		n = (2 * n) + bits[i];
	}
	return n;
}

int32_t Bits2Signed(int8_t bits[8]) {

	if (bits[7] == 0) { //If most signifigant bit is 0, formula is the same as bits to unsigned
		return Bits2Unsigned(bits);
	} else {
		int32_t sum = -128; //If most signifigant bit is 1, the value will be -128 + the sum of the rest of the bits
	
		int32_t n = 0;
		for (int i = 6; i >= 0; i--) { // Sums all bits EXCEPT most signifigant bit
			n = (2 * n) + bits[i];
		}
		return sum + n;
	}
}

void Increment(int8_t bits[8]) {
	if (bits[0] == 0) { //looks at least signifigant bit. If 0, changes to 1 and ends function
			bits[0] = 1;
			return;
	}
	
	int i;
	for(i = 0; i < 8; i++) { //If a bit is 1, changs to 0 then looks at the next bit. Ends function once a bit that is 0 is changed to one
		if(bits[i] == 0) {
			bits[i] = 1;
			return;
		} 
		else if (bits[i] == 1) {
			bits[i] = 0;
		}
		
	}
}

void Unsigned2Bits(uint32_t n, int8_t bits[8]) {
	int counter = 0;
	while (counter != 8) { //Uses repeated division to convert the given integer into binary
		bits[counter] = n % 2;
		counter++;
		n /= 2;
	}
}


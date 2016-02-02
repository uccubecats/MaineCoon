#include <iostream>
#include <string>
#include <sstream>

// Constants
const int A = 0;	// Index representing the a-ceofficent in an array.
const int B = 1;	// Index representing the b-ceofficent in an array.
const int C = 2;	// Index representing the c-ceofficent in an array.
const int X = 3;	// Index representing the x-value in an array.

// Specify the aprs namespace
class aprs {

	// Implementation of the absolute value function.
	float abs(float x);

	// Function used to get the best c-coefficent given the best a, b, and x values.
	int getBestC(int a, int b, int x, float v);

	// Function used to get the best b-ceofficent given the best a and x values.
	int getBestB(int a, int x, float v);

	// Function used to get the best a-ceofficent and x-value assuming b and c are zero.
	int getBestA(float v, int& xVal);

	// Function used to get the coefficents and x-value in APRS format for a given value.
	int* getAprsValues(float value);
	
	// Function used to get the coefficent string in the APRS packet format.
	unsigned int getCoeffString(char* buffer, std::string callTag, int* aArray, int* bArray, int* cArray);
	
	// Function used to get the x string in the APRS packet format.
	unsigned int getXString(char* buffer, int* xArray);
};
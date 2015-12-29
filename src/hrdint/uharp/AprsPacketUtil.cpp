#include "AprsPacketUtil.h"

// Implementation of the absolute value function.
float aprs::abs(float x) {
	if(x < 0) {
		return -1*x;
	}
	return x;
}

// Function used to get the best c-coefficent given the best a, b, and x values.
int aprs::getBestC(int a, int b, int x, float v) {
	int bestC = -128;
	for(int c = -127; c < 128; c++) {
		if(abs((a*x*x + b*x + c) - v) < abs((a*x*x + b*x + bestC) - v)) {
			bestC = c;
		}
	}
	return bestC;
}

// Function used to get the best b-ceofficent given the best a and x values.
int aprs::getBestB(int a, int x, float v) {
	int bestB = -128;
	for(int b = -127; b < 128; b++) {
		if(abs((a*x*x + b*x) - v) < abs((a*x*x + bestB*x) - v)) {
			bestB = b;
		}
	}
	return bestB;
}

// Function used to get the best a-ceofficent and x-value assuming b and c are zero.
int aprs::getBestA(float v, int& xVal) {
	int a, x;
	int bestA = -128;
	for(a = -127; a < 128; a++) {
		for(x = 0; x < 256; x++) {
			if(abs((a*x*x) - v) < abs((bestA*xVal*xVal) - v)) {
				bestA = a;
				xVal = x;
			}
		}
	}
	return bestA;
}

// Function used to get the coefficents and x-value in APRS format for a given value.
int* aprs::getAprsValues(float value) {
	
	// Create the array to return.
	int* aprsValues = new int[4];
	for(int ii = 0; ii < 4; ii++) {
		aprsValues[ii] = 0;
	}
	
	// Deduce the APRS values for the specified value.
	aprsValues[A] = getBestA(value, aprsValues[X]);
	aprsValues[B] = getBestB(aprsValues[A], aprsValues[X], value);
	aprsValues[C] = getBestC(aprsValues[A], aprsValues[B], aprsValues[X], value);
	
	// Return the APRS values.
	return aprsValues;
}

// Function used to get the coefficent string in the APRS packet format.
unsigned int aprs::getCoeffString(char* buffer, std::string callTag, int* aArray, int* bArray, int* cArray) {
	
	// Create a string to perform all initial manipulations on.
	std::string tmpString = ":" + callTag + " :EQNS.";
	for(int i = 0; i < 5; i++) {
		std::ostringstream newStream;
		newStream << aArray[i] << ",";
		newStream << bArray[i] << ",";
		newStream << cArray[i] << ((i < 4) ? "," : "");
		tmpString += newStream.str();
	}
	
	// Extract the characters from the string and its length.
	const char* tmpPointer = tmpString.c_str();
	unsigned int sizeOfBuffer = tmpString.length();
	
	// Clear the buffer if it already has data.
	if(buffer != NULL) {
		delete[] buffer;
	}
	
	// Copy the string data (using the pointer) to the specified buffer.
	buffer = new char[sizeOfBuffer];
	for(int i = 0; i < sizeOfBuffer; i++) {
		buffer[i] = tmpPointer[i];
	}
	
	// Return the size of the buffer (since we wrote the changes to it).
	return sizeOfBuffer;
}

// Function used to get the x string in the APRS packet format.
unsigned int aprs::getXString(char* buffer, int* xArray) {
	
	// Create a string to perform all initial manipulations on.
	std::string tmpString = "T#";
	for(int i = 0; i < 5; i++) {
		std::ostringstream newStream;
		newStream << xArray[i] << ((i < 4) ? "," : "");
		tmpString += newStream.str();
	}
	
	// Extract the characters from the string and its length.
	const char* tmpPointer = tmpString.c_str();
	unsigned int sizeOfBuffer = tmpString.length();
	
	// Clear the buffer if it already has data.
	if(buffer != NULL) {
		delete[] buffer;
	}
	
	// Copy the string data (using the pointer) to the specified buffer.
	buffer = new char[sizeOfBuffer];
	for(int i = 0; i < sizeOfBuffer; i++) {
		buffer[i] = tmpPointer[i];
	}
	
	// Return the size of the buffer (since we wrote the changes to it).
	return sizeOfBuffer;
}

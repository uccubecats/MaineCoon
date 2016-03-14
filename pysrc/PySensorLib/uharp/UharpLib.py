#include "AprsPacketUtil.h"

# Implementation of the absolute value function.
def abs(x):
	if(x < 0):
		return -1*x;
	return x;

# Function used to get the best c-coefficent given the best a, b, and x values.
def getBestC(a, b, x, v):
	bestC = -128;
	for c in range(-127, 128):
		if(abs((a*x*x + b*x + c) - v) < abs((a*x*x + b*x + bestC) - v)):
			bestC = c;
	return bestC;

# Function used to get the best b-ceofficent given the best a and x values.
def getBestB(a, x, v):
	bestB = -128;
	for b in range(-127, 128):
		if(abs((a*x*x + b*x) - v) < abs((a*x*x + bestB*x) - v)):
			bestB = b;
	return bestB;

# Function used to get the best a-ceofficent and x-value assuming b and c are zero.
def getBestA(v):
	a = 0;
	x = 0;
	xVal = 0;
	bestA = -128;
	for a in range(-127, 128):
		for x in range(0, 256):
			if(abs((a*x*x) - v) < abs((bestA*xVal*xVal) - v)):
				bestA = a;
				xVal = x;
	return bestA, xVal;

# Function used to get the coefficents and x-value in APRS format for a given value.
def getAprsValues(value):
	
	# Create the array to return.
	aprsValues = [0, 0, 0, 0];
	
	# Deduce the APRS values for the specified value.
	aprsValues[0], aprsValues[3] = getBestA(value);
	aprsValues[1] = getBestB(aprsValues[0], aprsValues[3], value);
	aprsValues[2] = getBestC(aprsValues[0], aprsValues[1], aprsValues[3], value);
	
	# Return the APRS values.
	return aprsValues;

# Function used to get the coefficent string in the APRS packet format.
def getCoeffString(callTag, aArray, bArray, cArray):
	
	# Create a string to perform all initial manipulations on.
	tmpString = ":" + callTag + " :EQNS.";
	for i in range(0, 5):
		tmpString = tmpString + str(aArray[i]) + ",";
		tmpString = tmpString + str(bArray[i]) + ",";
		tmpString = tmpString + str(cArray[i]);
		if(i < 4):
			tmpString = tmpString + ",";
	
	# Return the string for the packet.
	return str(tmpString);

# Function used to get the x string in the APRS packet format.
def getXString(xArray):
	
	# Create a string to perform all initial manipulations on.
	tmpString = "T#";
	for i in range(0, 5):
		tmpString = tmpString + str(xArray[i]);
		if(i < 4):
			tmpString = tmpString + ",";
	
	# Return the string for the packet.
	return str(tmpString);

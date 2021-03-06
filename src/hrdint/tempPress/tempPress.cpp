//Using the multiplexor (aka the MUX) to retrieve temperature and pressure data
//Also retrieving magnetometer data (without the MUX)

#include "tempPress.h"
#include <iostream>

//constructor
Mux::Mux()
{
	fDTempPress = wiringPiI2CSetup(fDTempPress);
	fDMagnetometer = wiringPiI2CSetup(fDMagnetometer);
	std::cout << fDTempPress << " " << fDMagnetometer << std::endl;
	//pinmode(sdaPin, INPUT);   //confirm input
	//pinmode(sclPin, OUTPUT);
	pinMode(gpioForMuxPin, OUTPUT);

}

//getters, just in case
int Mux::getSDAPin()
{
	return sdaPin;
}
int Mux::getSCLPin()
{
	return sclPin;
}
int Mux::getGPIOPin()
{
	return gpioForMuxPin;
}

//other methods............. three to be exact
int Mux::getTemperature(int binarySensorValue)
{
	//binarySensorValue represents internal vs external sensor. Ref. intSensor, extSensor
	if (binarySensorValue==0)
	{
		digitalWrite(gpioForMuxPin, LOW);
	}
	else if (binarySensorValue==1)
	{
		digitalWrite(gpioForMuxPin, HIGH);
	}
	else
	{
		return -1;		//invalid input
	}

	delay(1);
	int most=wiringPiI2CReadReg16 (fDTempPress, tMSB);
	int least=wiringPiI2CReadReg16 (fDTempPress, tLSB);
	std::cout << most << " " << least << std::endl;

	m_temperature = 256 * most + least;
	sendTemperature(binarySensorValue);

	return ((256*most)+least);
}
//And neither the angels in Heaven above, Nor the demons down under the sea,
//Can ever dissever my soul from the soul Of the beautiful Annabel Lee
int Mux::getPressure(int binarySensorValue)
{
	//binarySensorValue represents internal vs external sensor. Ref. intSensor, extSensor
	if (binarySensorValue==0)
	{
		digitalWrite(gpioForMuxPin, LOW);
	}
	else if (binarySensorValue==1)
	{
		digitalWrite(gpioForMuxPin, HIGH);
	}
	else
	{
		return -1;		//invalid input
	}

	delay(1);
	wiringPiI2CRead(fDTempPress);
	int most=wiringPiI2CReadReg16 (fDTempPress, pMSB);
	int least=wiringPiI2CReadReg16 (fDTempPress, pLSB);

	m_pressure = 256 * most + least;
	sendPressure(binarySensorValue);

	return ((256*most)+least);
}
int Mux::getOrientation()
{
//TO DO: MATH!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	int theta;

	m_orientation = theta;

	sendOrienation();

	return theta;
}


void sendTemperature(int binarySensorValue){
	if (binarySensorValue == 1){
		temperatureInside = m_temperature;
	} else {
		temperatureOutside = m_temperature;
	}
	return;
}

void sendPressure(int binarySensorValue){
	if (binarySensorValue == 1){
		pressureInside = m_pressure;
	} else {
		pressureOutside = m_pressure;
	}
	return;
}

void sendOrienation(){
	orientation = m_orientation;
	return;
}

//fin.

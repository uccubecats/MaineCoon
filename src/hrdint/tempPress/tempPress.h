//Using the multiplexor (aka the MUX) to retrieve temperature and pressure data
//Also retrieving magnetometer data (without the MUX)

#include <wiringPiI2C.h>
#include <wiringPi.h>

class Mux
{

	//fields. but more like constants. lots of constants. there aren't actually any fields.
public:
	const int intSensor=0, extSensor=1,
							//binary values of the temp/press sensors (internal and external)
							//randomly assigned for MUX use only

		sdaPin=3,	sclPin=5, gpioForMuxPin=29,
							//pi pin #s for SDA, SCL, and the GPIO pin for our MUX
							//gpioForMuxPin was arbitrarily chosen; all options are 29, 31-33, 35-38

		fDTempPress=0x60, fDMagnetometer=0x0E,
							//fd address for temp/press sensors and magnetometer
							//both temp/press sensors have the same address, hence the need of a MUX

		xMSB=0x01, xLSB=0x02, yMSB=0x03, yLSB=0x04, zMSB=0x05, zLSB=0x06,
							//register values for each axis (x, y, z), most/least significant bites
//TO DO: FIGURE OUT WHOCH ORIENTATION IS WHICH AXIS

		pMSB=0x00, pLSB=0x01, tMSB=0x02, tLSB=0x03;
							//register values for temperature/pressure, most/least significant bites

	Mux();
	int getSDAPin();
	int getSCLPin();
	int getGPIOPin();
	int getTemperature(int binarySensorValue);
	int getPressure(int binarySensorValue);
	int getOrientation();
};

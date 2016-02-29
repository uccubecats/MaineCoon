//Using the multiplexor (aka the MUX) to retrieve temperature and pressure data
//Also retrieving magnetometer data (without the MUX)

#include <wiringPiI2C.h>
#include <wiringPi.h>

#ifdef __GNUC__ 
#include <unistd.h> 
#endif

#ifdef _WIN32
#include <windows.h> 
#endif

/*! Global variables for use in passing along to wrapper function.
 *	May only be written by the Mux class.
 */
extern int temperatureInside = 0;
extern int temperatureOutside = 0;
extern int pressureInside = 0;
extern int pressureOutside = 0;
extern int orientation = 0;

class Mux
{

	//fields. but more like constants. lots of constants. there aren't actually any fields.
public:
	int intSensor=0, extSensor=1,
							//binary values of the temp/press sensors (internal and external)
							//randomly assigned for MUX use only

		sdaPin=3,	sclPin=5, gpioForMuxPin=29,
							//pi pin #s for SDA, SCL, and the GPIO pin for our MUX
							//gpioForMuxPin was arbitrarily chosen; all options are 29, 31-33, 35-38

		fDTempPress=0x76, fDMagnetometer=0x0E,
							//fd address for temp/press sensors and magnetometer
							//both temp/press sensors have the same address, hence the need of a MUX

		xMSB=0x01, xLSB=0x02, yMSB=0x03, yLSB=0x04, zMSB=0x05, zLSB=0x06,
							//register values for each axis (x, y, z), most/least significant bites
//TO DO: FIGURE OUT WHOCH ORIENTATION IS WHICH AXIS

		pMSB=0x00, pLSB=0x01, tMSB=0x02, tLSB=0x03;
							//register values for temperature/pressure, most/least significant bites

private: // internal values used for quick passing to globals
	int m_temperature = 0;
	int m_pressure = 0;
	int m_orientation = 0;

	Mux();
	int getSDAPin();
	int getSCLPin();
	int getGPIOPin();
	int getTemperature(int binarySensorValue);
	int getPressure(int binarySensorValue);
	int getOrientation();

	// Send to global
	void sendTemperature();
	void sendPressure();
	void sendOrientation();
};

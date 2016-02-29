# Local Imports
from MS5607     import MS5607   as TempPressLib
from pyoleddisp import OledDisp as OledLib
from pyslowscan import SlowScan as SstvLib
from UharpLib	import UharpLib	as UharpLib

# Python Built-in Imports
import numpy    as np
import picamera	as camera

# Global Constants
TEMP_PRESS_SENSOR = 0x00;

# Class...
class PySensorLib:

    # Constructor used to create instances of each sensor library for use
    # with each of the sensors onboard the system.
    def __init__(self):
        self.tempPressLib = TempPressLib(TEMP_PRESS_SENSOR);
        self.oledLib = OledLib();
        self.sstvLib = SstvLib();
		self.camLib = camera.PiCamera()
    
    # Function used to display a name on the OLED display, capture the image,
    # capture the image, and send it back to the ground.
    def performNameTask(self, displayText):
		
        # Set the OLED to display the desired text.
        self.oledLib.PrintText(displayText);
        
        # Capture an image using the camera.
        fileName = "OledTmpImgFile.jpg"
		self.camLib.capture(fileName);
		
		# TODO - UHARP related syncing.
		
        # Send the image back using SSTV.
		self.sstvLib.playFile(fileName);
    
    def getInternalTemperature(self):
        
        # Write to the MUX to select the internal temperature.
        
        # Obtain and return the internal temperature from the sensor.
        return self.tempPressLib.get_temperature();
    
    def getExternalTemperature(self):
        
        # Write to the MUX to select the external temperature.
        
        # Obtain and return the external temperature from the sensor.
        return self.tempPressLib.get_temperature();
    
    def getOrientation(self):
        
        # Get the requried magnetometer values to deduce the orientation.
        magX = getMagnetometerX();
        magY = getMagnetometerY();
        
        # TODO.. Math
        orientation = 0;
        
        # Return the orientation.
        return orientation;
    
    def getLogValues(self):
        
        # Create an array to return the logging values in.
        # This will contian: intTemp, extTemp, magX, magY, magZ
        arrayForLogging = np.empty((5,), dtype=np.int32);
        
        # Write the array values.
        arrayForLogging[0] = getInternalTemperature();
        arrayForLogging[1] = getExternalTemperature();
        arrayForLogging[2] = getMagnetometerX();
        arrayForLogging[3] = getMagnetometerY();
        arrayForLogging[4] = getMagnetometerZ();
        
    def sendAprsPackets(self, callTag):
        
        # TODO - send to UHARP.
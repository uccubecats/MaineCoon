#!/usr/bin/python

# Logging implementation
# Designed to run in a separate thread for "simultaneous execution"
# while running on the Raspberry Pi

from PySensorLib/PySensorLib import PySensorLib
import os
import threading
import time

# modify this to exit the thread
exitFlag = 0
SLEEP_DURATION = 0.25

class Logging(threading.Thread):
  def __init__(self, threadID, name, sensor):
    # Call base class
    threading.Thread.__init__(self)
    # Name of thread, ID of thread (both necessary for access by outside functions)
    self.threadID = threadID
    self.name = name
    # Create headers for CSV file
    self.headers = ('InternalTemp', 'ExternalTemp', 'MagnetX', 'MagnetY', 'MagnetZ')
    # Pass in sensor
    self.sensor = sensor

  def run(self):
    while true:
      sensor.getLogValues()
      if exitFlag:
        threadName.exit()
      writeLog(sensor.sensorDataArray, headers)
      time.sleep(SLEEP_DURATION)

	def writeLog(sensorDataArray, headers):
	  if not os.path.isfile('log.csv'):
		# Only append to file
		# Write headers to file if empty
		log = open('log.csv', 'a')
		for header in headers:
		  log.write(header + ',')
		log.write('\n')

	  if not log:
		log = open('log.csv', 'a')
	  for entry in sensorDataArray:
		# Write each sensor number to file
		log.write('{},'.format(entry))
	  log.write('\n')
	  log.close()

def StartLogging():
	loggingThread = loggingLogic.__init__(1, "Logging")
	loggingThread.start()

def exitLogging():
	exitFlag = 1;

def setNewSleepTime(sleepTimeInSec):
	SLEEP_DURATION = sleepTimeInSec
	

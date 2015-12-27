# Imports the necessary libraries... Gaugette 'talks' to the display ;-)

import SSD1306
#import time
#import sys

class OledDisp:

	def __init__(self):
		# Setting some variables for our reset pin etc.
		self.RESET_PIN = 15
		self.DC_PIN    = 16
		
	def PrintText(self, text):
		print(self.RESET_PIN)
		print(text)
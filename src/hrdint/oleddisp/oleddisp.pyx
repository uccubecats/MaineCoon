# Imports the necessary libraries... Gaugette 'talks' to the display ;-)

cimport cython
cimport gaugette.ssd1306
import gaugette.ssd1306
#import time
#import sys

cdef class OledDisp:
	cpdef SetUp():
		# Setting some variables for our reset pin etc.
		RESET_PIN = 15
		DC_PIN    = 16
		
		# Very important... This lets py-gaugette 'know' what pins to use in order to reset the display
		led = gaugette.ssd1306.SSD1306(reset_pin=RESET_PIN, dc_pin=DC_PIN)
		led.begin()
		led.clear_display() # This clears the display but only when there is a led.display() as well!
	
	
	cpdef PrintText(text):
		# led.draw_text2(x-axis, y-axis, whatyouwanttoprint, size) < Understand?
		# So led.drawtext2() prints simple text to the OLED display like so:
		#text = 'Hello!'
		led.draw_text2(0,0,text,2)
		led.display()
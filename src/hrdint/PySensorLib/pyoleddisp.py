# Imports the necessary libraries... Gaugette 'talks' to the display ;-)

import SSD1306
from PIL import Image, ImageDraw, ImageFont
from Adafruit_GPIO.SPI import SpiDev
#import time
#import sys

class OledDisp:

	def __init__(self):
		# Setting some variables for our reset pin etc.
		self.RESET_PIN = 22
		self.DC_PIN    = 23
		
		# Very important... This lets py-gaugette 'know' what pins to use in order to reset the display
		self.led = SSD1306.SSD1306_128_64(rst=self.RESET_PIN, dc=self.DC_PIN, spi=SpiDev(0, 0, max_speed_hz=8000000))
		self.led.begin()
		self.led.clear() # This clears the display but only when there is a led.display() as well!
		self.led.display()
		
	def PrintText(self, text):
		# led.draw_text2(x-axis, y-axis, whatyouwanttoprint, size) < Understand?
		# So led.drawtext2() prints simple text to the OLED display like so:
		#text = 'Hello!'

		# Create the image to write to the display
		# THIS MAY NEED TO CHANGE BASED ON STRING LENGTH!
		image = Image.new('1', (128, 64))
		draw = ImageDraw(image)
		draw.text((0, 0), text, font=ImageFont.load_default(), fill=255)

		# Clear the Display
		self.led.clear()
		self.led.display()

		# Write the text-based image to the display
		self.led.image(image)
		self.led.display()

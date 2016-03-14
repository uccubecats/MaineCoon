import AprsUtil as aprs

class UharpLib:

	# 
	def __init__(self, callTag):
		self.callTag = callTag;
		
	def getParmString(self):
		# Create a string to perform all initial manipulations on.
		tmpString = ":" + self.callTag + " :PARM.";
		
		#Hard coded Parameter Names
		tmpString = tmpString + "ExPres" + ",";
		tmpString = tmpString + "InTmp" + ",";
		tmpString = tmpString + "ExTmp" + ",";
		tmpString = tmpString + "Orien" + ",";
		tmpString = tmpString + "BatV" + ",";
	
		return str(tmpString);
		
	def getUnitString(self):
		# Create a string to perform all initial manipulations on.
		tmpString = ":" + self.callTag + " :PARM.";
		
		#Hard Coded Units
		tmpString = tmpString + "kPa" + ",";
		tmpString = tmpString + "degC" + ",";
		tmpString = tmpString + "degC" + ",";
		tmpString = tmpString + "radN" + ",";
		tmpString = tmpString + "Volt" + ",";
	
		return str(tmpString);
		
	def getXString(self, valuesArray):
		XArray = [0 0 0 0 0]
		tmpValue = [0 0 0 0]
		
		for ii in range(0,5):
			tmpValue = aprs.getAprsValues(valuesArray[ii])
			XArray[ii] = tmpValue[3]
		
		return aprs.getXString(self.callTag, XArray);
		
	def getCoeffString(self, valuesArray):
		aArray = [0 0 0 0 0]
		bArray = [0 0 0 0 0]
		cArray = [0 0 0 0 0] 
		tmpValue = [0 0 0 0]
		
		for ii in range(0,5):
			tmpValue = aprs.getAprsValues(valuesArray[ii])
			aArray[ii] = tmpValue[0]
			bArray[ii] = tmpValue[1]
			cArray[ii] = tmpValue[2]
		
		return aprs.getCoeffString(self.callTag, aArray, bArray, cArray);
	
	
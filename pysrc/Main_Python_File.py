
#All of this is based on “Mission Start”

#look up pThread header file
def altitudeChange()
{
	#return -1, 0, or 1 for down, no change, or up
}

def hasHitGround()
{
	#return 1 if velocity is 0 and altitude is less than 1000m
}

def hasBalloonPopped()
{
	#return 1 if altitude change is negative
}

def hasBalloonRelease()
{
	#return 1 if is mission start and altitude change is positive
}

def isMissionStart()
{
	#return 1 if altitude is above 350m
}

def isTerminalVelocity()
{
	#return 1 if Velocity[z] >= TerminalVelocity
}

def isPhotoOpp()

def isPicGood()

def hasCrossedJetstream()
{
	#return 1 if altitude is negative and probability for jetstream is high
}
#Now begin checking data from all these functions
isInAir=true;
temperature = null;
maxtemp=null;
while isInAir
{
	if temperature>maxtemp:
	{
		#turn on the fan for a while
	}
	if ()#request for temperature, pressure, magnetometer data
	{
		#give them what they want (either sendTemp(), sendPressure(), or sendMag())
	}
	if photoOpp():
	{
		#take photo;
		#send to ground;
		if (picGood())
		{
			index = yourNameInSpace(); #New Background Thread...
		}
	}
	while (jetStream() > 80):
	{
		#More often collection.
		getTemperature();
		getPressure();
		getOrientation();
	}
	if hitGround():
	{
		isInAir = false;
	}
	#Possible backup.
	if (altitude() < 147)  AND (altitudeChange() == 0):
	#assuming 147 meters is the lowest altitude we will be taking in data from
	{
			isInAir = false;
	}
}

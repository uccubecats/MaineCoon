import os
from ctypes import *

class PyFuzzy:

    def __init__(self):
        temp = os.path.abspath(__file__)
        temp = os.path.realpath(temp)
        temp = os.path.dirname(temp)
        temp = os.path.join(temp, "libPyFuzzy.so")
        self.libRef = CDLL(temp)
        self.libInst = lib.JetStream_new();

    def getJetStreamProbability(self, altitude, temperature, pressure):
        return int(self.libRef.JetStream_probablilityInJetStream(self.libInst, altitude, temperature, pressure))

from m5.params import *
from m5.SimObject import SimObject

class Sensor(SimObject):
    type = 'Sensor'
    cxx_header = "microSimProject/sensor.hh"
    
    curTemp = Param.Int("current temp of the sensor")
    newTemp = Param.Int("the new sensed temperature")

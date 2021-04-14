from m5.params import *
from m5.SimObject import SimObject

class SevenSegDis(SimObject):
    type = 'SevenSegDis'
    cxx_header = "microSimProject/sevenSegDis.hh"
    
    toDisplay = Param.String("What is to be displayed")

from m5.params import *
from m5.proxy import *
from MemObject import MemObject

#Creates object that interacts with the memory system
class SevenSegDis(MemObject):
    type = 'SevenSegDis'
    cxx_header = "microSimProject/sevenSegDis.hh"
    
    inst_port = SlavePort("CPU side port, receives requests")
    data_port = SlavePort("CPU side port, received requests")
    mem_side = MasterPort("Memory side port, sends requests")
    
    toDisplay = Param.String("What is to be displayed")

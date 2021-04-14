from m5.params import *
from m5.proxy import *
from m5.SimObject import SimObject

class SevenSegDis(SimObject):
	type = 'SevenSegDis'
	cxx_header = "microSimProject/sevenSegDis.hh"

	inst_port = SlavePort("CPU side port, receives requests")
	data_port = SlavePort("CPU side port, receives requests")
	mem_side = MasterPort("Memory side port, sends requests")

	toDisplay = Param.String("null","What is to be displayed")

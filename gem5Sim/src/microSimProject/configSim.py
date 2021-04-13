import m5
from m5.objects import *

system = System() #Created the system Object which is the parent of all other objects in our simulated system.

system.clk_domain = SrcClockDomain() #created the clock domain
system.clk_domain.clock = '1GHz' #Set the clock to 1GHz
system.clk_domain.voltage_domain = VoltageDomain() # Set the voltage domain for the clock to default option

system.mem_mode = 'timing' #Used timing mode for the memory simulation
system.mem_ranges = [AddrRange('512MB')] #Set the single memory range to size 512MB

system.cpu = TimingSimpleCPU() #Created the CPU which executes each instruction in a single clock cycle except for the memory request

system.membus = SystemXBar() #Created the system wide memory bus

#since we created the memory bus, we would then connect the cache ports directly to the memory bus
system.cpu.icache_port = system.membus.slave
system.cpu.dcache_port = system.membus.slave

#Created an I/O controller on the CPU and connected it to the memory bus
system.cpu.createInterruptController()
system.system_port = system.membus.slave

#Created the memory controller to connect to the memory bus which is responsible for the entire memory range
system.mem_ctrl = DDR3_1600_8x8()
system.mem_ctrl.range = system.mem_ranges[0]
system.mem_ctrl.port = system.membus.master

#Created the root object for the instantiation of the system and beginning of execution
root = Root(full_system = False)


root.svsgd = SevenSegDis()
root.svsgd.toDisplay = "A"
root.svsgd2 = SevenSegDis()
root.svsgd2.toDisplay = "3"

m5.instantiate()


print("Beginning simmulation!")
exit_event = m5.simulate()
print('Exiting @ tick {} because {}'.format(m5.curTick(), exit_event.getCause()))

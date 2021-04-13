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

root = Root(full_system = False)


root.svsgd = SevenSegDis()
root.svsgd.toDisplay = "A"
root.svsgd2 = SevenSegDis()
root.svsgd2.toDisplay = "3"

m5.instantiate()


print("Beginning simmulation!")
exit_event = m5.simulate()
print('Exiting @ tick {} because {}'.format(m5.curTick(), exit_event.getCause()))

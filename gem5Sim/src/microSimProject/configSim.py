import m5
from m5.objects import *

system = System()

system.clk_domain = SrcClockDomain()
system.clk_domain.clock = '1GHz'
system.clk_domain.voltage_domain = VoltageDomain()

system.mem_mode = 'timing'
system.mem_ranges = [AddrRange('512MB')]

root = Root(full_system = False)

root.svsgd = SevenSegDis()
root.svsgd.toDisplay = "A"
root.svsgd2 = SevenSegDis()
root.svsgd2.toDisplay = "3"

m5.instantiate()


print("Beginning simmulation!")
exit_event = m5.simulate()
print('Exiting @ tick {} because {}'.format(m5.curTick(), exit_event.getCause()))

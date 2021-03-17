import m5
from m5.objects import *

root = Root(full_system = False)

root.svsgd = SevenSegDis()
root.svsgd.toDisplay = 1101101

m5.instantiate()

print("Beginning simmulation!")
exit_event = m5.simulate()
print('Exiting @ tick {} because{}'.format(m5.curTick(), exit_event.getCause()))

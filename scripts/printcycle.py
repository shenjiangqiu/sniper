# Monitor SimMarker() calls made by the application.

import sim
import sys, os, sim
class Marker:
  def setup(self, args):
    self.freq = sim.dvfs.get_frequency(0) # This script does not support DVFS
    self.sd = sim.util.StatsDelta()
  def hook_magic_marker(self, thread, core, a, b, s):
    if a==2323:
        print("SNIPER::SCRIPT::PRINTCYCLE: ",b)
        sim.control.printCycle()
        elapsed_time=self.sd.getter('thread', 0, 'elapsed_time')
        elapsed_time_bcp=self.sd.getter('thread', 0, 'elapsed_time_in_bcp')
        elapsed_time.update()
        elapsed_time_bcp.update()
        c1=elapsed_time.delta * self.freq / 1e9
        c2=elapsed_time_bcp.delta * self.freq / 1e9
        print("elapsed_time: %d" %c1)
        print("elapsed_time_bcp:%d" %c2)




sim.util.register(Marker())

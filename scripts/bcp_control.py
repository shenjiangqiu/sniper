# Monitor SimMarker() calls made by the application.

import sim
class BcpControl:
  def hook_magic_marker(self, thread, core, a, b, s):
    if a==100 and b==1:
        sim.control.startBcp()
    if a==100 and b==2:
        sim.control.exitBcp()

sim.util.register(BcpControl())

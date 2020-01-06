# Scripted ROI start/end based on SimMarker iteration markers.
# Assumes start and end of each iteration is marked using SimMarker(1, i) and SimMarker(2, i), respectively.
#
# This script will switch to warmup at the beginning of iteration A (default: first SimMarker(1, *)),
# run in detailed from the start of iteration B until the end of iteration C,
# and then fast-forward to the end.
#
# run-sniper --roi-script --no-cache-warming -s roi-iter:A:B:C
#
# Start the simulation with "--roi-script --no-cache-warming" to start in fast-forward mode and ignore SimRoi{Start,End}

import sim

class pauseroi:
  def hook_magic_marker(self, core, thread, a, b, s):
    if a==5:
        if b==1:
            sim.control.roiRestart()
        elif b==2:
            sim.control.roiPause()

sim.util.register(pauseroi())

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

class branchflag:
  def setup(self, args):
    if args:
      args = dict(enumerate(args.split(':')))
    else:
      args = {}
    
  def hook_magic_marker(self, core, thread, a, b, s):
    if a==3 and b<21:
        sim.control.setBranchFlag(b) #start to use fixed memory address
    elif a==4:
        sim.control.unsetBranchFlag()
        

sim.util.register(branchflag())

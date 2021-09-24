#!/usr/bin/env python
"""

ipython -i NPMakeDivTest.py 

"""
import os
import numpy as np
import matplotlib.pyplot as plt 

# changes with python version
try:
   import commands as cmds
except ImportError:
   import subprocess as cmds
pass

def cmd(line):
    rc, out = cmds.getstatusoutput(line)
    assert rc == 0 
    return out 


class NPMakeDivTest(object):
    FOLD = "/tmp/NPMakeDivTest"
    def __init__(self):
        for name in filter(lambda n:n.endswith(".npy"),os.listdir(self.FOLD)):
            stem = name[:-4]
            path = os.path.join(self.FOLD, name)
            a = np.load(path)
            ll = cmd("ls -l %s" % path)
            print(" %10s : %-20s : %s " % (stem, str(a.shape), ll )) 
            globals()[stem] = a 
        pass

if __name__ == '__main__':
    t = NPMakeDivTest()

    fig, ax = plt.subplots(figsize=[12.8, 7.2])

    ax.plot( twod_dist[:,0], twod_dist[:,1], label="twod_dist" )
    ax.scatter( twod_dist2[:,0], twod_dist2[:,1], label="twod_dist2" )

    fig.show()


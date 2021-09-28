#!/usr/bin/env python 
"""

ipython -i NPinterpHDTest.py 

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


class NPinterpHDTest(object):
    FOLD = "/tmp/NPinterpHDTest"
    def __init__(self):
        for name in filter(lambda n:n.endswith(".npy"),os.listdir(self.FOLD)):
            stem = name[:-4]
            path = os.path.join(self.FOLD, name)
            a = np.load(path)
            ll = cmd("ls -l %s" % path)
            print(" %10s : %-20s : %s " % (stem, str(a.shape), ll )) 
            globals()[stem] = a 
        pass
    pass


if __name__ == '__main__':
    t =  NPinterpHDTest()

    np.all( icdf[:,0,0] == icdf[:,0,1] )

    title = ["np/tests/NPinterpHDTest.py"]

    fig, ax = plt.subplots(figsize=[12.8, 7.2])
    fig.suptitle("\n".join(title))

    if xy.ndim == 2:
        ax.plot( xy[:,0], xy[:,1], label="xy" )
    elif xy.ndim == 3:
        for item in range(len(xy)):
            ax.plot( xy[item,:,0], xy[item,:,1], label="xy %d" % item )
        pass
    pass

    ax.legend()

    fig.show()



 



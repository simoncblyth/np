#!/usr/bin/env python 
"""

::

    ipython -i NPCombineTest.py 


"""
import matplotlib.pyplot as plt
import os, numpy as np

FOLD = "/tmp/NPCombineTest"

if __name__ == '__main__':

    dom = np.load(os.path.join(FOLD,"dom.npy"))
    com = np.load(os.path.join(FOLD,"com.npy"))
    scan = np.load(os.path.join(FOLD,"scan.npy"))

    if dom.dtype == np.float32:
        utype = np.uint32
    elif dom.dtype == np.float64:
        utype = np.uint64
    else:
        assert 0
    pass

    fig, ax = plt.subplots(figsize=[12.8,7.2])
    for i in range(len(com)):
        ni = com[i].view(utype)[-1,-1] 
        ax.scatter( com[i,:ni,0], com[i,:ni,1], label="com-%d" % i )
        ax.plot( dom, scan[i], label="scan-%d" % i )
    pass
    ax.legend()

    fig.show()
    plt.ion()




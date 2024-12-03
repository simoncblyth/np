#!/usr/bin/env python 
"""

::

    ipython -i NPCombineTest.py 


"""
import os, numpy as np
np.set_printoptions(suppress=True)

try:
    import matplotlib.pyplot as plt
except ImportError:
    plt = None
pass


if __name__ == '__main__':

    dom = np.load(os.path.expandvars("$FOLD/dom.npy"))
    com = np.load(os.path.expandvars("$FOLD/com.npy"))
    scan = np.load(os.path.expandvars("$FOLD/scan.npy"))

    print("dom.shape:%s" % str(dom.shape) )
    print("com.shape:%s" % str(com.shape) )
    print("scan.shape:%s" % str(scan.shape) )

    print("dom\n", dom)
    print("com\n", com)
    print("scan\n", scan)

    if dom.dtype == np.float32:
        utype = np.uint32
    elif dom.dtype == np.float64:
        utype = np.uint64
    else:
        assert 0
    pass

    if not plt is None:
        fig, ax = plt.subplots(figsize=[12.8,7.2])
        for i in range(len(com)):
            ni = com[i].view(utype)[-1,-1] 
            ax.scatter( com[i,:ni,0], com[i,:ni,1], label="com-%d" % i )
            ax.plot( dom, scan[i], label="scan-%d" % i )
        pass
        ax.legend()

        fig.show()
        plt.ion()
    pass




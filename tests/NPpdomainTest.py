#!/usr/bin/env python
"""

~/np/tests/NPpdomainTest.sh
~/np/tests/NPpdomainTest.sh pdb 

"""
import os, numpy as np

try:
    import matplotlib.pyplot as plt 
except ImportError:
    plt = None
pass

def test_2d():

    fig, ax = plt.subplots()

    ax.plot( a[:,0], a[:,1], label="a" )
    ax.scatter( a[:,0], a[:,1], label="a" )

    ax.plot( b[:,1], b[:,0]+10, label="b" )
    ax.scatter( b[:,1], b[:,0]+10, label="b" )
 
    ax.legend()
    fig.show()



if __name__ == '__main__':

    a = np.load(os.path.expandvars("$FOLD/3d/a.npy"))
    b = np.load(os.path.expandvars("$FOLD/3d/b.npy"))
    assert len(a) == len(b)

    if not plt is None:
        fig, ax = plt.subplots()
        for item in range(len(a)):

            ax.plot( a[item, :,0], a[item, :,1]  )
            ax.scatter( a[item, :,0], a[item, :,1], label="a%d" % item )

            ax.plot( b[item, :,1], b[item, :,0]+10   )
            ax.scatter( b[item, :,1], b[item, :,0]+10, label="b%d" % item  )
        pass
        ax.legend()
        fig.show()
    pass



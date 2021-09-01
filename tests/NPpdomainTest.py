#!/usr/bin/env python
"""

ipython -i NPpdomainTest.py 

"""
import os, numpy as np
import matplotlib.pyplot as plt 


def test_2d():
    FOLD = "/tmp/NPpdomainTest"
    a = np.load(os.path.join(FOLD, "a.npy"))
    b = np.load(os.path.join(FOLD, "b.npy"))

    fig, ax = plt.subplots()

    ax.plot( a[:,0], a[:,1], label="a" )
    ax.scatter( a[:,0], a[:,1], label="a" )

    ax.plot( b[:,1], b[:,0]+10, label="b" )
    ax.scatter( b[:,1], b[:,0]+10, label="b" )
 
    ax.legend()
    fig.show()






if __name__ == '__main__':

    FOLD = "/tmp/NPpdomainTest/3d"
    a = np.load(os.path.join(FOLD, "a.npy"))
    b = np.load(os.path.join(FOLD, "b.npy"))
    assert len(a) == len(b)

    fig, ax = plt.subplots()
    for item in range(len(a)):

        ax.plot( a[item, :,0], a[item, :,1]  )
        ax.scatter( a[item, :,0], a[item, :,1], label="a%d" % item )

        ax.plot( b[item, :,1], b[item, :,0]+10   )
        ax.scatter( b[item, :,1], b[item, :,0]+10, label="b%d" % item  )
    pass
    ax.legend()
    fig.show()



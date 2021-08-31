#!/usr/bin/env python
"""

ipython -i NPpdomainTest.py 

"""
import os, numpy as np
import matplotlib.pyplot as plt 

if __name__ == '__main__':
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





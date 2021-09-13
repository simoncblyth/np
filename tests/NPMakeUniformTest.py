#!/usr/bin/env python
"""
::

    ipython -i NPMakeUniformTest.py

"""
import numpy as np
import matplotlib.pyplot as plt 

if __name__ == '__main__':

    path = "/tmp/NPMakeUniformTest/uu.npy"

    uu = np.load(path)
    h = np.histogram(uu)  

    fig, ax = plt.subplots()
    fig.suptitle(path)

    ax.plot( h[1][:-1], h[0] )
    ax.scatter( h[1][:-1], h[0] )
    ax.set_ylim( 0, h[0].max()*2 )

    fig.show()


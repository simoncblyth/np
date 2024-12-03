#!/usr/bin/env python 
"""
NPInterpTest.py
=================

::

   ~/np/tests/NPInterpTest.sh 
   ~/np/tests/NPInterpTest.sh pdb


"""
import os, numpy as np

try:
    import matplotlib.pyplot as plt
except ImportError:
    plt = None
pass


if __name__ == '__main__':
    src = np.load(os.path.expandvars("$FOLD/src.npy"))
    dst = np.load(os.path.expandvars("$FOLD/dst.npy"))

    print("src.shape\n", src.shape)
    print("dst.shape\n", dst.shape)
    print("src\n", src)
    print("dst\n", dst)

    if not plt is None:
        fig, ax = plt.subplots(figsize=[12.8,7.2])
        ax.scatter( src[:,0], src[:,1], label="src" )
        ax.plot( dst[:,0], dst[:,1], label="dst" )
        ax.legend()

        fig.show()
        plt.ion()
    pass




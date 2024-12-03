#!/usr/bin/env python
"""
~/np/tests/NPReadTest.sh 

"""

import os, numpy as np

if __name__ == '__main__':

    apath = os.path.expandvars("$FOLD/a.npy")
    bpath = os.path.expandvars("$FOLD/b.npy")

    a = np.load(apath)
    print("a\n",a)

    b = np.load(bpath)
    print("b\n",b)


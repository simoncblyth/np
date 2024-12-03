#!/usr/bin/env python 
"""
~/np/tests/NPMakeTest.sh 
"""

import os, numpy as np
np.set_printoptions(suppress=True)

if __name__ == '__main__':
    ap = os.path.expandvars("$FOLD/a6.npy")  
    a = np.load(ap)
    print("a\n", a)




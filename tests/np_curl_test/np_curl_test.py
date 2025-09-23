#!/usr/bin/env python

import os, numpy as np
np.set_printoptions(suppress=True)

if __name__ == '__main__':
    gs = np.load(os.path.expandvars("$FOLD/gs.npy"))
    ht = np.load(os.path.expandvars("$FOLD/ht.npy"))
    print("gs.shape\n", gs.shape)
    print("gs\n", gs)
    print("ht.shape\n", ht.shape)
    print("ht\n", ht)


#!/usr/bin/env python

import os, numpy as np

if __name__ == '__main__':
    p = os.path.expandvars("$FOLD/demo.npy")
    a = np.load(p) if os.path.exists(p) else None
    print("a:%r" % a )




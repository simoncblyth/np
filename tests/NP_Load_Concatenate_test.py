#!/usr/bin/env python

import os, numpy as np

if __name__ == '__main__':
     path = os.path.expandvars("$OUT_FOLD/concat.npy")
     a = np.load(path)
     print(a)





#!/usr/bin/env python

import os, numpy as np

if __name__ == '__main__':
     path = os.path.expandvars("$FOLD/concat/concat.npy")
     print(path)
     a = np.load(path)
     print("a.shape:%r" % a )
     print(a)





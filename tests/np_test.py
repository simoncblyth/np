#!/usr/bin/env python

import os, numpy as np

if __name__ == '__main__':
    path = os.environ["NPY"]
    a = np.load(path)
    print(repr(a))
pass

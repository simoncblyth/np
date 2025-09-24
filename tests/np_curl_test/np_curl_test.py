#!/usr/bin/env python

from np.fold import Fold
import os, numpy as np
np.set_printoptions(suppress=True)

if __name__ == '__main__':
    f = Fold.Load(symbol="f")
    print(repr(f))

    assert np.all( f.ht000 == f.ht )  # curl on cmdline should give save hits as libcurl from the test with same gensteps




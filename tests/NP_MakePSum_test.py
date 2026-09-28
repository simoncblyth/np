#!/usr/bin/env python

from np.fold import Fold
import numpy as np

if __name__ == '__main__':
    f = Fold.Load(symbol="f")
    print(repr(f))

    assert np.all( f.x[:,0] == f.s[:,0] )
    assert np.max(np.abs( f.x[:,1] - f.s[:,1] )) < 1e-10
pass

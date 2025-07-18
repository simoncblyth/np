#!/usr/bin/env python

import numpy as np
from np.fold import Fold

if __name__ == '__main__':
    f = Fold.Load(symbol="f")
    print(repr(f))
    ia0 = f.Integer.a0
    assert( np.all( ia0 == np.arange(20000,45600) ))
pass


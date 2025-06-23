#!/usr/bin/env python

import numpy as np
from np.fold import Fold

if __name__ == '__main__':
    f = Fold.Load(symbol="f")
    print(repr(f))
    a = f.a
    assert( np.all( f.a == np.arange(20000,45600) ))
pass


#!/usr/bin/env python

import numpy as np
from np.fold import Fold

if __name__ == '__main__':
    f = Fold.Load(symbol="f")
    print(repr(f))
    assert(np.all( f.n[:,0] == f.k[:,0] ))



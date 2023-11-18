#!/usr/bin/env python

import numpy as np
from np.fold import Fold

if __name__ == '__main__':
    f = Fold.Load(symbol="f")
    print(repr(f))

    nn = f.a.view("|S%d" % f.a.shape[1] ) 
    print(nn)
pass



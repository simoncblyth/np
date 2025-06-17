#!/usr/bin/env python

from np.fold import Fold
import numpy as np

if __name__ == '__main__':
    f = Fold.Load("$FOLD/$TEST", symbol="f")
    print(repr(f))
pass


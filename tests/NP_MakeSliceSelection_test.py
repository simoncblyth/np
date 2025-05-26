#!/usr/bin/env python

import numpy as np
from np.fold import Fold


if __name__ == '__main__':
    t = Fold.Load("$FOLD/$TEST", symbol="t")
    print(repr(t))



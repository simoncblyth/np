#!/usr/bin/env python
"""
NPFold_profile_test.py
=======================


"""

import numpy as np
from np.fold import Fold 

if __name__ == '__main__':
    ab = Fold.Load(symbol="ab")
    print(repr(ab))




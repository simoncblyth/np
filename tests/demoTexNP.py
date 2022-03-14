#!/usr/bin/env python

import os, numpy as np
FOLD = "/tmp/demoTexNP" 

if __name__ == '__main__':
    a = np.load(os.path.join(FOLD, "a.npy"))
    b = np.load(os.path.join(FOLD, "b.npy"))

    




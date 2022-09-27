#!/usr/bin/env python

import numpy as np

if __name__ == '__main__':

    FOLD = os.environ["FOLD"]

    a4 = np.load(os.path.join(FOLD, "a4.npy"))
    a1 = np.load(os.path.join(FOLD, "a1.npy"))
    a0 = np.load(os.path.join(FOLD, "a0.npy"))

    print("a4.shape %s " % str(a4.shape))
    print("a1.shape %s " % str(a1.shape))
    print("a0.shape %s " % str(a0.shape))



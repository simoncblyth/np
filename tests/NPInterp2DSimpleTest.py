#!/usr/bin/env python

import os, numpy as np

try:
    import matplotlib.pyplot as plt
except ImportError:
    plt = None
pass

if __name__ == '__main__':

    a = np.load(os.path.expandvars("$FOLD/a.npy"))
    b = np.load(os.path.expandvars("$FOLD/b.npy"))
    print(" a %s " % str(a.shape))
    print(" b %s " % str(b.shape))

    if not plt is None:
        fig, axs = plt.subplots(2)
        axs[0].imshow(a)
        axs[1].imshow(b)
        fig.show()
    pass
        





#!/usr/bin/env python

import os, numpy as np
import matplotlib.pyplot as plt

FOLD = "/tmp/NPInterp2DSimpleTest" 

if __name__ == '__main__':
    a = np.load(os.path.join(FOLD, "a.npy"))
    b = np.load(os.path.join(FOLD, "b.npy"))


    print(" a %s " % str(a.shape))
    print(" b %s " % str(b.shape))

    fig, axs = plt.subplots(2)
    axs[0].imshow(a)
    axs[1].imshow(b)
    fig.show()
    





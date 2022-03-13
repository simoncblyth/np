#!/usr/bin/env python

import os, numpy as np
import matplotlib.pyplot as plt

FOLD = "/tmp/NPInterp2DTest"

if __name__ == '__main__':
    a = np.load(os.path.join(FOLD, "a.npy"))
    print(a.shape)
    print(a)

    fig, ax = plt.subplots(1)
    ax.imshow(a)
    fig.show()
    





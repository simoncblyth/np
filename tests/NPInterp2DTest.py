#!/usr/bin/env python

import os, numpy as np
MODE = os.environ.get("MODE", 2)

try:
    import matplotlib.pyplot as plt
except ImportError:
    plt = None
pass


if __name__ == '__main__':
    print("MODE:%d" % MODE) 

    a = np.load(os.path.expandvars("$FOLD/a.npy"))
    b = np.load(os.path.expandvars("$FOLD/b.npy"))
    c = np.load(os.path.expandvars("$FOLD/c.npy"))

    print("a.shape\n", a.shape)
    print("b.shape\n", b.shape)
    print("c.shape\n", c.shape)

    print("a\n",a)
    print("b\n",b)
    print("c\n",c)

    if MODE == 2 and not plt is None:
        fig, ax = plt.subplots(1)
        ax.imshow(a)
        ax.set_xlabel("a")
        fig.show()

        fig, ax = plt.subplots(1)
        ax.imshow(b)
        ax.set_xlabel("b")
        fig.show()

        fig, ax = plt.subplots(1)
        ax.imshow(c)
        ax.set_xlabel("c")
        fig.show()
    pass
pass
    
        





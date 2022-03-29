#!/usr/bin/env python 
"""

FOLD=/tmp/NPspawn_itemTest ipython -i NPspawn_itemTest.py

"""
import os, numpy as np

if __name__ == '__main__':
    FOLD = os.environ["FOLD"] 
    names = list(sorted(filter(lambda name:name.endswith(".npy"), os.listdir(FOLD))))
    for idx in range(len(names)):
        name = names[idx]
        stem, ext = os.path.splitext(name)
        assert ext == ".npy"
        path = os.path.join(FOLD, name)
        _arr = np.load(path)
        globals()[stem] = _arr
        print(" %3d : %s : %10s : %s " % (idx, stem, str(_arr.shape), path))
    pass

        




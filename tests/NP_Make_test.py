#!/usr/bin/env python
"""
NP_Make_test.py
================

TEST=Large ~/np/tests/NP_Make_test.sh info_build_run_ana 


"""

import os, numpy as np

if __name__ == '__main__':
    TEST = os.environ.get("TEST","ALL")
    if TEST in ["Make","ctor"]: 
        a4 = np.load(os.path.expandvars("$FOLD/a4.npy"))
        a1 = np.load(os.path.expandvars("$FOLD/a1.npy"))
        a0 = np.load(os.path.expandvars("$FOLD/a0.npy"))

        print("a4.shape %s " % str(a4.shape))
        print("a1.shape %s " % str(a1.shape))
        print("a0.shape %s " % str(a0.shape))
    elif TEST == "Large":
        apath = os.path.expandvars("$FOLD/Large.npy")
        st = os.stat(apath)
        print("apath:%s st.st_size:%d " % (apath,st.st_size))
        os.system("ls -l %s" % apath )

        a = np.load(apath)

        print("a.shape %s " % str(a.shape))
        hsize = 128  
        xsize = hsize + a.size*a.dtype.itemsize
        print("xsize:%d st.st_size:%d " % ( xsize, st.st_size ))

        G = float(1024*1024*1024)
        fgb = float(st.st_size)/G
        xgb = float(xsize)/G

        print("fgb:%10.6f xgb:%10.6f " % ( fgb, xgb ))

    else:
        print("TEST:%s unhandled " % TEST )
    pass
pass


#!/usr/bin/env python
"""
NPFold_stamps_test.py
=======================


"""

import numpy as np
from np.fold import Fold 
MODE =  int(os.environ.get("MODE", "2"))

if MODE != 0:
    from opticks.ana.pvplt import * 
pass

labels_ = lambda l:l.view("|S%d" % l.shape[1])[:,0]  
tv_     = lambda a:a.view("datetime64[us]")  

# https://matplotlib.org/stable/gallery/color/named_colors.html
palette = ["red","green", "blue", 
           "cyan", "magenta", "yellow", 
           "tab:orange", "tab:pink", "tab:olive",
           "tab:purple", "tab:grey", "tab:cyan"
           ]

if __name__ == '__main__':
    pn = Fold.Load(symbol="pn")
    print(repr(pn))

    #f = pn.p 
    f = pn.n


    meta = " ".join(f.stamps_meta) 

    s = f.stamps

    e_sel = slice(1,None)              # skip 1st event, as initialization messes timings
    t_sel = slice(2,None)              # skip first two stamps (init, BeginOfRun) 

    e_rel = f.stamps_names[e_sel]      # rel path of the evt folds, eg shape (9,)
    t_lab = labels_(f.labels)[t_sel]

    ss =  f.stamps[e_sel,t_sel]        # selected timestamps, eg shape (9,13)

    dss = ss - ss[:,0,np.newaxis]      # subtract first column stamp from all stamps row by row
                                       # hence giving begin of event relative time delta in microseconds

    assert len(e_rel) == dss.shape[0]  # event dimension 
    assert len(t_lab) == dss.shape[1]  # time stamp dimension 

    tab = np.c_[t_lab, dss.T ]   
    print(tab)

    title = "NPFold_stamps_test "
    title += meta
    print("MODE:%d" % MODE) 

    if MODE == 2:
        print(title)
        fig, axs = mpplt_plotter(nrows=1, ncols=1, label=title, equal=False)
        ax = axs[0]

        for i in range(len(dss)):
            for j in range(len(dss[i])):
                label = None if i > 0 else t_lab[j].decode("utf-8")
                color = palette[j % len(palette)]
                ax.vlines( dss[i,j], i-0.5, i+0.5, label=label , colors=[color] ) 
            pass
        pass
        ax.legend(loc="center")
        fig.show()
    pass    
    





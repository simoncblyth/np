#!/usr/bin/env python
"""
NPFold_stamps_test.py
=======================


"""

import numpy as np
from np.fold import Fold 
MODE =  int(os.environ.get("MODE", "2"))
PICK =  os.environ.get("PICK", "AB")
TLIM =  np.array(list(map(int,os.environ.get("TLIM", "0,0").split(","))),dtype=np.int32)


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


      

class Stamps(object):
    @classmethod
    def Summarize(cls, label):
        """
        Shorten stamp labels via heuristics of distinctive chars
        """
        smry = "" 
        p = None
        for i,c in enumerate(label):
            if p is None:                      # always take first char 
                smry += c 
            elif c.isalnum() and p == "_":     # first alnum char after _
                smry += c 
            elif c.isupper() and p.islower():  # upper char following lower
                smry += c 
            elif p == "P" and c in "ro":       #  accept r or o after P to distinguish Pre and Post 
                smry += c 
            pass 
            p = c 
        pass
        return smry 


    def __init__(self, f):

        s = f.stamps
        assert len(s.shape) == 2 

        title = "Stamps " + " ".join(f.stamps_meta)

        e_sel = slice(1,None)              # skip 1st event, as initialization messes timings
        t_sel = slice(2,None)              # skip first two stamps (init, BeginOfRun) 

        e_rel = f.stamps_names[e_sel]      # rel path of the evt folds, eg shape (9,)
        t_lab = labels_(f.labels)[t_sel]

        smry_ = lambda _:self.Summarize(_.decode("utf-8"))
        s_lab = list(map(smry_, t_lab))
        hdr = (" " * 8  + " %5s " * len(s_lab) ) % tuple(s_lab) 


        ss =  f.stamps[e_sel,t_sel]        # selected timestamps, eg shape (9,13)

        dss = ss - ss[:,0,np.newaxis]      # subtract first column stamp from all stamps row by row
                                           # hence giving begin of event relative time delta in microseconds

        assert dss.shape == ss.shape 

        assert len(e_rel) == dss.shape[0]  # event dimension 
        assert len(t_lab) == dss.shape[1]  # time stamp dimension 

        self.ss  = ss 
        self.dss = dss 
        self.s_lab = s_lab
        self.hdr = hdr
        self.title = title
 
    def __repr__(self):
        return "\n".join([self.title, self.hdr, repr(self.dss)])

    def plot(self):
        st = self
        if MODE == 2:
            fig, axs = mpplt_plotter(nrows=1, ncols=1, label=st.title, equal=False)
            ax = axs[0]

            if TLIM[1] > TLIM[0]:
                ax.set_xlim(*TLIM)
            pass

            dss = st.dss
            for i in range(len(dss)):
                for j in range(len(dss[i])):
                    label = None if i > 0 else st.s_lab[j]
                    color = palette[j % len(palette)]
                    ax.vlines( dss[i,j], i-0.5, i+0.5, label=label , colors=[color] ) 
                pass
            pass
            ax.legend(loc="center")
            fig.show()
        pass  
        return ax


if __name__ == '__main__':
    ab = Fold.Load(symbol="ab")
    print(repr(ab))
    print("MODE:%d" % MODE) 

    if PICK == "A":
       ff = [ab.a,] 
    elif PICK == "B":
       ff = [ab.b,] 
    elif PICK == "AB":
       ff = [ab.a,ab.b]
    elif PICK == "BA":
       ff = [ab.b,ab.a]
    else:
       print("PICK [%s] unhandled" % PICK)
       ff = []
    pass

    for f in ff:
        st = Stamps(f)
        print(repr(st))
        ax = st.plot()
    pass



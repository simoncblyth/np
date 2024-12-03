#!/usr/bin/env python
"""

~/np/tests/NPMakeICDFTest.sh pdb 

"""
import os
import numpy as np

try:
    import matplotlib.pyplot as plt 
except ImportError:
    plt = None
pass


# changes with python version
try:
   import commands as cmds
except ImportError:
   import subprocess as cmds
pass

def cmd(line):
    rc, out = cmds.getstatusoutput(line)
    assert rc == 0 
    return out 


class NPMakeICDFTest(object):
    def __init__(self):
        FOLD = os.path.expandvars("$FOLD")
        for name in filter(lambda n:n.endswith(".npy"),os.listdir(FOLD)):
            stem = name[:-4]
            path = os.path.join(FOLD, name)
            a = np.load(path)
            ll = cmd("ls -l %s" % path)
            print(" %10s : %-20s : %s " % (stem, str(a.shape), ll )) 
            globals()[stem] = a 
        pass
    pass


def make_lookup_sample(icdf):
    uu = np.random.rand(1000000)  
    y = np.linspace(0, 1, len(icdf))  # 0->1 domain to accompany the icdf 
    xx = np.interp( uu, y, icdf )
    return xx 




if __name__ == '__main__':
    t = NPMakeICDFTest()

    #lookup_sample_py = make_lookup_sample(icdf)

    bins = np.linspace( dist[0,0], dist[-1,0], 100 ) 

    dmax = dist[:,1].max()

    if "lookup_sample" in globals():
        h = np.histogram( lookup_sample, bins=bins )
        hmax = h[0].max()  
    else:
        h = None
        hmax = None
    pass 

    print("h\n",h)
   

    if not plt is None:

        title = ["np/tests/NPMakeICDFTest.sh",
                 "poor sampling veracity where CDF is flat, ICDF is steep" 
                ]

        fig, axs = plt.subplots(1, 2, figsize=[12.8, 7.2])
        fig.suptitle("\n".join(title))

        ax = axs[0]
        ax.scatter( dist[:,0], dist[:,1],                 label="dist" )
        ax.plot(    cdf[:,0],  cdf[:,1]*dist[:,1].max() , label="cdf*dist[:,1].max" )

        if not h is None:  
            ax.plot(    h[1][:-1], h[0]*dmax/hmax,            label="h", drawstyle="steps-post" )
        pass

        #ax.scatter( xx,       uu*dmax ,                  label="xx uu*dmax" )  ## this follows the cdf line

        ax.legend()
        ax = axs[1]

        for j in range(3):
            ax.plot( icdf_prop[:,j,0], icdf_prop[:,j,1], label="icdf_prop %s" % ["all","lhs","rhs"][j]  )
        pass

        ax.legend()
        

        fig.show()
    pass

     


     



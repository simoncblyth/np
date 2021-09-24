#!/usr/bin/env python
"""

ipython -i NPMakeICDFTest.py 

"""
import os
import numpy as np
import matplotlib.pyplot as plt 

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
    FOLD = "/tmp/NPMakeICDFTest"
    def __init__(self):
        for name in filter(lambda n:n.endswith(".npy"),os.listdir(self.FOLD)):
            stem = name[:-4]
            path = os.path.join(self.FOLD, name)
            a = np.load(path)
            ll = cmd("ls -l %s" % path)
            print(" %10s : %-20s : %s " % (stem, str(a.shape), ll )) 
            globals()[stem] = a 
        pass
    pass

if __name__ == '__main__':
    t = NPMakeICDFTest()


    icdf = icdf.reshape(-1)
    uu = np.random.rand(1000000)  
    y = np.linspace(0, 1, len(icdf)) 
    xx = np.interp( uu, y, icdf )

    bins = np.linspace( dist[0,0], dist[-1,0], 100 ) 
    h = np.histogram( xx, bins=bins )

    dmax = dist[:,1].max()
    hmax = h[0].max()  


    fig, ax = plt.subplots(figsize=[12.8, 7.2])

    ax.scatter( dist[:,0], dist[:,1],                 label="dist" )
    ax.plot(    cdf[:,0],  cdf[:,1]*dist[:,1].max() , label="cdf*dist[:,1].max" )
    ax.plot(    h[1][:-1], h[0]*dmax/hmax,            label="h" )
    #ax.scatter( xx,       uu*dmax ,                  label="xx uu*dmax" )  ## this follows the cdf line

    ax.legend()
    fig.show()


     


     



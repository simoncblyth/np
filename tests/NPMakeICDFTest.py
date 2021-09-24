#!/usr/bin/env python
"""

ipython -i NPMakeICDFTest.py 

"""
import os
import numpy as np
import matplotlib.pyplot as plt 

class NPMakeICDFTest(object):
    FOLD = "/tmp/NPMakeICDFTest"
    def __init__(self):
        for name in filter(lambda n:n.endswith(".npy"),os.listdir(self.FOLD)):
            stem = name[:-4]
            path = os.path.join(self.FOLD, name)
            a = np.load(path)
            print(" %10s : %s : %s " % (stem, str(a.shape), os.system("ls -l %s" % path))) 
            globals()[stem] = a 
        pass


if __name__ == '__main__':
     t = NPMakeICDFTest()

     plt.ion()
     fig, ax = plt.subplots(figsize=[12.8, 7.2])
     ax.scatter( dist[:,0], dist[:,1], label="dist" )
     ax.plot( cdf[:,0], cdf[:,1]*dist[:,1].max() , label="cdf*dist[:,1].max" )
     ax.legend()
     fig.show()





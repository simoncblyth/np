#!/usr/bin/env python
"""
  
    ipython -i s2integralTest.py 

"""

import numpy as np
import matplotlib.pyplot as plt 

if __name__ == '__main__':

     path = "/tmp/s2integralTest.npy"
     s2i = np.load(path)

     title_ = ["np/tests/s2integralTest.py : s2i plot from sympy codegen C function", path ] 
     title = "/n".join(title_)

     print(title)

     fig, ax = plt.subplots(figsize=[12.8, 7.2])
     fig.suptitle(title)

     ax.plot( s2i[:,0], s2i[:,1], label="s2i[BetaInverse=1.55]" )
     ax.legend()
     fig.show()


#!/usr/bin/env python

import numpy as np
import textwrap
from np.fold import Fold
np.set_printoptions(precision=6)


if __name__ == '__main__':
    f = Fold.Load("$FOLD/$TEST", symbol="f")
    print(repr(f))

    theta = np.linspace( 0., np.pi/2 , 91 )
    costh = np.cos(theta)

    result = np.zeros( [len(theta), 3], dtype=np.float64 )
    for i in range(len(theta)):
        result[i,0] = np.interp( theta[i], f.th[:,0], f.th[:,1] )
        result[i,1] = np.interp( costh[i], f.ct[:,0], f.ct[:,1] )
    pass
    result[:,2] = result[:,0] - result[:,1]

    delta = f.re - result


    EXPR=r"""
    # shapes

    theta.shape
    costh.shape
    result.shape
    f.re.shape
    delta.shape

    # compare interpolation with theta and costheta domains
    f.re[:,2].min()
    f.re[:,2].max()
    result[:,2].min()
    result[:,2].max()

    # compare python and C++ impl, delta = f.re - result

    delta.min()
    delta.max()
    """

    for expr in list(filter(None,textwrap.dedent(EXPR).split("\n"))):
        line = "\n"+expr+"\n" if expr[0] == "#" else "%20s : %s" % ( expr, str(eval(expr)))
        print(line)
    pass


pass



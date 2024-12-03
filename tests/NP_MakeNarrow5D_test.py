#!/usr/bin/env python

import os, textwrap, numpy as np
from np.fold import Fold

if __name__ == '__main__':
    t = Fold.Load(symbol="t")
    print(repr(t))

    exprs = textwrap.dedent("""

    t.c.view(np.int64)[...,-1,-1]
    t.fc.view(np.int32)[...,-1,-1]

    t.d.view(np.int64)[...,-1,-1]
    t.fd.view(np.int32)[...,-1,-1]

    """)

    for expr in filter(None, exprs.split("\n")): 
        print(expr)
        print(eval(expr))
    pass
pass


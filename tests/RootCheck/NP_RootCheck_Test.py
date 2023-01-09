#!/usr/bin/env python
"""


For LPMT::

    np.all( np.arange( len(t.pmtID), dtype=np.int32 ) == t.pmtID  ) 

For SPMT::

    np.all( np.arange( len(t.pmtID), dtype=np.int32 ) + 300000  == t.pmtID  ) 


"""

import numpy as np
from opticks.ana.fold import Fold

if __name__ == '__main__':
    t = Fold.Load(symbol="t")
    print(repr(t))
pass

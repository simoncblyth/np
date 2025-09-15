#!/usr/bin/env python

import numpy as np
a = np.ones([512,512,3], dtype=np.float32)
open("arr","wb").write(a.tobytes())


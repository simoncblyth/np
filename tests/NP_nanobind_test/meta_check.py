#!/usr/bin/env python

import os, io, operator, functools, shutil, numpy as np

def make_array(shape=(2,6,4)):
    sz = functools.reduce(operator.mul,shape)
    a = np.arange(sz, dtype=np.float32).reshape(*shape)
    return a


if __name__ == '__main__':

    meta="red:1\ngreen:2\nblue:3\ncyan:3.141596"
    a = make_array()
    print("a\n",a)


    buffer = io.BytesIO()
    np.save(buffer, a)
    buffer.write(meta.encode("utf-8"))

    path = os.path.expandvars("$FOLD/out.npy")
    print(path)

    with open(path, "wb") as fp:
        buffer.seek(0)  # Move cursor to start
        shutil.copyfileobj(buffer, fp)
    pass
    buffer.close()

    b = np.load(path)
    print("b\n",b)



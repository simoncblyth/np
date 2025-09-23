#!/usr/bin/env python

import os, io, numpy as np


def write_array_data():
    fold = os.environ.get("FOLD",".")
    a = np.ones([512,512,3], dtype=np.float32)
    open(os.path.join(fold,"arr"),"wb").write(a.tobytes())

def chop_head():
    fold = os.path.expandvars("$FOLD")
    gs = np.load(os.path.join(fold,"gs.npy"))
    open(os.path.join(fold,"gs"),'wb').write(gs.tobytes())



#def reconstruct_array_from_bytes():
if __name__ == '__main__':
    """
    Without the seek back to start np.load gives::

        EOFError: No data left in file

    """
    arr0 = np.ones([512,512,3], dtype=np.float32)

    buffer = io.BytesIO()
    np.save(buffer, arr0)

    buffer.seek(0)  # Reset buffer position to the start
    arr1 = np.load(buffer)
    assert np.all(arr0 == arr1)

    buffer_bytes = buffer.getvalue()
    print(buffer_bytes[:128])

    numpy_magic = b'\x93NUMPY'
    has_numpy_magic = buffer_bytes.startswith(numpy_magic)

    print("has_numpy_magic:%s" % has_numpy_magic)




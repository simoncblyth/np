#!/usr/bin/env python

import inspect, os, io, operator, functools, shutil, numpy as np
from typing import Optional

path = os.path.expandvars("$FOLD/out.npy")

def make_array(shape=(2,6,4)):
    sz = functools.reduce(operator.mul,shape)
    a = np.arange(sz, dtype=np.float32).reshape(*shape)
    return a


def save_array_plus_meta_to_file():
    """

    1. create array and metadata
    2. save array and meta into one io.BytesIO buffer

    """
    print(f"[{inspect.currentframe().f_code.co_name}")

    # 1. create array and metadata
    meta="red:1\ngreen:2\nblue:3\ncyan:3.141596"
    a = make_array()
    print("a\n",a)
    a_meta = meta.encode("utf-8")


    # 2. save array and meta into one io.BytesIO buffer
    buffer = io.BytesIO()
    np.save(buffer, a)
    buffer.write(a_meta)

    # 3. write the buffer into a file
    print(path)
    with open(path, "wb") as fp:
        buffer.seek(0)  # Move cursor to start
        shutil.copyfileobj(buffer, fp)
    pass
    buffer.close()
    print(f"]{inspect.currentframe().f_code.co_name}")

def load_array_from_file_ignoring_meta():
    print(f"[{inspect.currentframe().f_code.co_name}")
    b = np.load(path)
    print("b\n",b)
    print(f"]{inspect.currentframe().f_code.co_name}")

def load_array_from_file_with_meta():
    print(f"[{inspect.currentframe().f_code.co_name}")
    newbuf = io.BytesIO()
    with open(path, "rb") as fp: shutil.copyfileobj(fp, newbuf)

    newbuf.seek(0)
    c = np.load(newbuf)
    print("c\n",c)

    data:bytes = newbuf.getvalue()

    buf_nbytes = newbuf.getbuffer().nbytes
    hdr_nbytes = data.find(b'\n') + 1  # 1 + index of first newline, typically 128 but can be more for arrays with many dimensions
    arr_nbytes = c.nbytes
    meta_nbytes = buf_nbytes - hdr_nbytes - arr_nbytes

    print(f" buf_nbytes {buf_nbytes}   hdr_nbytes {hdr_nbytes}  arr_nbytes {arr_nbytes}  meta_nbytes {meta_nbytes} ")

    newbuf.seek( hdr_nbytes + arr_nbytes )

    _meta:Optional[bytes] = newbuf.read(meta_nbytes) if meta_nbytes>0 else None

    meta = _meta.decode("utf-8")
    print(f" meta [{meta}]")

    print(f"]{inspect.currentframe().f_code.co_name}")


if __name__ == '__main__':
    save_array_plus_meta_to_file()
    load_array_from_file_ignoring_meta()
    load_array_from_file_with_meta()









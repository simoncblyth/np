#!/usr/bin/env python
"""
NPInterp.py
=============

Simple linear interpolation prototype for GPU implementation. see::

    opticks/qudarap/QProp.cc 
    opticks/qudarap/tests/QPropTest.cc 

::

    ipython -i NPInterp.py 

"""
import matplotlib.pyplot as plt
import numpy as np

def _np_interp( vv, ni, x):
    lo = 0 
    hi = ni-1 
    if x <= vv[2*lo+0]: return vv[2*lo+1]  
    if x >= vv[2*hi+0]: return vv[2*hi+1]

    while lo < hi-1:
        mi = (lo+hi)//2   # integer division
        if x < vv[2*mi+0]: 
            hi = mi 
        else: 
            lo = mi
        pass
    pass

    dy = vv[2*hi+1] - vv[2*lo+1] 
    dx = vv[2*hi+0] - vv[2*lo+0]  
    y = vv[2*lo+1] + dy*(x-vv[2*lo+0])/dx  
    return y   

def np_interp( a, x ):
    """
    :param a: pshaped (n,2) array
    :param x: domain scalar value at which to linearly interpolate the property values 
    """
    assert len(a.shape) == 2 and a.shape[1] == 2 and a.shape[0] > 1   
    ni = a.shape[0]
    vv = a.ravel()
    return _np_interp( vv, ni, x )

def np_interp_compound( aa, i, x ):
    """
    :param aa: compound property shaped array (num_prop, 2*(max_domain_width+1)) 
               with domain widths uint encoded in last entry 
    :param i: integer choosing the property
    :return v: interpolated value 

    ::

        In [7]: aa   ## eg shape  (3, 12)
        Out[7]:
        array([[  0.,  50.,   1., 100.,   2., 150.,   0.,   0.,   0.,   0.,   0.,   0.],
               [  0., 100.,   1., 200.,   2., 300.,   3., 400.,   0.,   0.,   0.,   0.],
               [  0., 150.,   1., 250.,   2., 350.,   3., 450.,   4., 550.,   0.,   0.]], dtype=float32)

    """
    assert len(aa.shape) == 2 and aa.shape[-1] % 2 == 0
    assert i < len(aa)
    utype = np_utype(aa.dtype)

    a = aa[i]
    i2 = a.view(utype)[-2] ; assert i2 == i
    ni = a.view(utype)[-1] ; assert ni > 1 
    return _np_interp( a, ni, x )


def np_utype(dtype):
    """
    :param dtype: float32 or float64 dtype
    :return utype: corresponding uint32 or uint64 dtype
    """
    assert str(dtype).startswith("float")   
    uint_dtype = str(dtype).replace("float","uint")
    uint_dtype = getattr(np, uint_dtype)
    return uint_dtype

def np_irregular_combine(*pp):
    dtype = pp[0].dtype
    utype = np_utype(dtype)

    width = 1 + max(map(len, pp))
    aa = np.zeros( (len(pp),2*width), dtype=dtype )
    for i,p in enumerate(pp):
        aa[i,:len(p)*2] = p.ravel() 
        aa.view(utype)[i,-2] = i
        aa.view(utype)[i,-1] = len(p)
    pass
    return aa 

def make_compound():
    dtype = np.float32
    a = np.array( [[0,50], [1,100], [2,150]], dtype=dtype )
    b = np.array( [[0,100], [1,200], [2,300], [3,400]], dtype=dtype )
    c = np.array( [[0,150], [1,250], [2,350], [3,450], [4,550]], dtype=dtype )
    pp = np_irregular_combine(a,b,c)
    return pp

def make_simple():
    dtype = np.float32
    a = np.array( [[0,10], [1,20], [2,30]], dtype=dtype )
    return a

def make_domain(n, dtype):
    dom = np.zeros((n), dtype=dtype )
    for i in range(n):
        dom[i] = -0.1 + i*0.1 
    return dom

def np_save(path, a):
    if not os.path.exists(os.path.dirname(path)):
        os.makedirs(os.path.dirname(path))
    pass
    print("np_save %s %s to %s " % (repr(a.shape),str(a.dtype), path))
    np.save(path, a)


def test_compound_np_interp():
    pp = make_compound()
    np_save("/tmp/np/test_compound_np_interp.npy", pp)

    dtype = pp[0].dtype
    dom = make_domain(50, dtype)
    utype = np_utype(dtype)

    r = np.zeros( (len(dom),1+len(pp)), dtype=dtype )
    r[:,0] = dom

    for i in range(len(pp)): 
        for j,x in enumerate(dom):
            r[j,1+i] = np_interp_compound(pp, i, x)
        pass
    pass 

    fig, ax = plt.subplots(figsize=[12.8,7.2])
    for i,p in enumerate(pp): 
        lp = p.view(utype)[-1]
        i2 = p.view(utype)[-2]
        assert i2 == i 
        pr = p.reshape(-1,2)
        ax.scatter( pr[:lp,0], pr[:lp,1], label="src-%d-lp-%d" % (i,lp) )
        ax.plot( r[:,0], r[:,1+i], label="dst-%d" % i )
    pass
    ax.legend()
    fig.show()

def test_simple_np_interp():
    p = make_simple()
    dom = make_domain(30, p.dtype)
    r = np.zeros( (len(dom),2), dtype=p.dtype )
    r[:,0] = dom
    for i,x in enumerate(dom):
        r[i,1] = np_interp(p, x)
    pass
    fig, ax = plt.subplots(figsize=[12.8,7.2])
    ax.scatter( p[:,0], p[:,1], label="src" )
    ax.plot( r[:,0], r[:,1], label="dst" )
    ax.legend()
    fig.show()


if __name__ == '__main__':
    #test_simple_np_interp()
    test_compound_np_interp()




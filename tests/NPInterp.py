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

        In [1]: pp
        Out[1]:
        array([[[  0.,  50.],
                [  1., 100.],
                [  2., 150.],
                [  0.,   0.],
                [  0.,   0.],
                [  0., *0.*]],  # < uint annotation in pp[:,-1,-1]

               [[  0., 100.],
                [  1., 200.],
                [  2., 300.],
                [  3., 400.],
                [  0.,   0.],
                [  0., *0.*]],

               [[  0., 150.],
                [  1., 250.],
                [  2., 350.],
                [  3., 450.],
                [  4., 550.],
                [  0., *0.*]]], dtype=float32)

    In [4]: pp.view(np.uint32)[:,-1,-1]
    Out[4]: array([3, 4, 5], dtype=uint32)

    In [2]: pp.shape
    Out[2]: (3, 6, 2)

    Formerly flattened the last dimension::

        In [7]: aa   ## eg shape  (3, 12)
        Out[7]:
        array([[  0.,  50.,   1., 100.,   2., 150.,   0.,   0.,   0.,   0.,   0.,   0.],
               [  0., 100.,   1., 200.,   2., 300.,   3., 400.,   0.,   0.,   0.,   0.],
               [  0., 150.,   1., 250.,   2., 350.,   3., 450.,   4., 550.,   0.,   0.]], dtype=float32)


    """
    assert len(aa.shape) == 3 and aa.shape[-1] == 2
    assert i < len(aa)
    utype = np_utype(aa.dtype)

    a = aa[i]
    ni = a.view(utype)[-1,-1] ; assert ni > 1
    vv = a.ravel()
    return _np_interp( vv, ni, x )


def np_utype(dtype):
    """
    :param dtype: float32 or float64 dtype
    :return utype: corresponding uint32 or uint64 dtype
    """
    assert str(dtype).startswith("float")
    uint_dtype = str(dtype).replace("float","uint")
    uint_dtype = getattr(np, uint_dtype)
    return uint_dtype

def np_irregular_combine(*pp, annotate=True):
    """
    :param pp: list of arrays
    :return aa: combination array, with shape annotation in uint view of extra column

    This is used as the prototype for NP.hh/NP::Combine

    Example shapes of input and output arrays::

       (n0,1) (n1,1) (n2,1) (n3,1) (n4,1)  ->   ( count(n0,n1,n2,n3,n4) = 5 , 1+max(n0,n1,n2,n3,n4) , 1 )
       (n0,2) (n1,2) (n2,2) (n3,2) (n4,2)  ->   ( count(n0,n1,n2,n3,n4) = 5 , 1+max(n0,n1,n2,n3,n4) , 2 )
       (n0,3) (n1,3) (n2,3) (n3,3) (n4,3)  ->   ( count(n0,n1,n2,n3,n4) = 5 , 1+max(n0,n1,n2,n3,n4) , 3 )

    Currently the special casing to handle the below is not implemented::

       (n0,)  (n1,)  (n2,)  (n3,)  (n4,)   ->   ( count(n0,n1,n2,n3,n4) = 5 , 1+max(n0,n1,n2,n3,n4) , 1 )

    """
    dtype = pp[0].dtype
    utype = np_utype(dtype)

    ndims = list(map(lambda _:_.ndim, pp))
    u_ndims = np.unique(ndims)
    assert len(u_ndims) == 1, ("input arrays must all have an equal number of dimensions", ndims )
    ndim = ndims[0]
    assert ndim == 2, ("input arrays must be 2d", ndim)

    ldims = list(map(lambda _:_.shape[-1],pp))   # last dimension
    u_ldims = np.unique(ldims)
    assert len(u_ldims) == 1, ("last dimension of the input arrays must be equal", ldims)
    ldim = ldims[0]

    fdims = list(map(lambda _:_.shape[0],pp))  # first dimension
    width = max(fdims) + int(annotate)

    aa = np.zeros( (len(pp),width,ldim), dtype=dtype )
    for i,p in enumerate(pp):
        aa[i,:len(p),:] = p
        if annotate:
            aa.view(utype)[i,-1,-1] = len(p)
        pass
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
        lp = p.view(utype)[-1,-1]
        ax.scatter( p[:lp,0], p[:lp,1], label="src-%d-lp-%d" % (i,lp) )
        ax.plot( r[:,0], r[:,1+i], label="dst-%d" % i )
    pass
    ax.legend()
    fig.show()
    return pp

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
    pp = test_compound_np_interp()




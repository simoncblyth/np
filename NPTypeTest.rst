type_shifting
===============

Being able to *view* data as different 
types is very useful.  For example below 
is a scratch ipython session working out how to encode 
two char "commands" into a float array from python.  

::

    In [1]: a = np.zeros( 4, dtype=np.float32 )

    In [2]: a
    Out[2]: array([0., 0., 0., 0.], dtype=float32)

    In [4]: a.view(dtype="|S16")
    Out[4]: array([''], dtype='|S16')

    In [7]: a.view(dtype="|S2")
    Out[7]: array(['', '', '', '', '', '', '', ''], dtype='|S2')

    In [8]: a.view(dtype="|S2")[0]
    Out[8]: ''

    In [9]: a.view(dtype="|S2")[0] = "c0"

    In [10]: a.view(dtype="|S2")[1] = "c1"

    In [11]: a.view(dtype="|S2")[2] = "c2"

    In [12]: a
    Out[12]: array([0., 0., 0., 0.], dtype=float32)

    In [13]: a.view(np.uint8)
    Out[13]: array([99, 48, 99, 49, 99, 50,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0], dtype=uint8)

    In [14]: a.view(dtype="|S2")[3] = "aa"

    In [15]: a.view(np.uint8)
    Out[15]: array([99, 48, 99, 49, 99, 50, 97, 97,  0,  0,  0,  0,  0,  0,  0,  0], dtype=uint8)

    In [17]: unichr(97)
    Out[17]: u'a'

    In [18]: ord('a')
    Out[18]: 97

    In [21]: a.view("|S1")
    Out[21]: array(['c', '0', 'c', '1', 'c', '2', 'a', 'a', '', '', '', '', '', '', '', ''], dtype='|S1')

    In [22]: a.view("|S2")
    Out[22]: array(['c0', 'c1', 'c2', 'aa', '', '', '', ''], dtype='|S2')

    In [23]: a   ## viewing as float often gives very large/small numbers or even Nan but no matter, the bits are unchanged
    Out[23]: array([3.3060e-09, 2.5963e+20, 0.0000e+00, 0.0000e+00], dtype=float32)


    In [24]: np.save("/tmp/a.npy", a )




::

    In [10]: a = np.zeros( 4, dtype=dtype )

    In [11]: a
    Out[11]: array([0., 0., 0., 0.], dtype=float32)

    In [12]: a.view("|S16")
    Out[12]: array([''], dtype='|S16')

    In [16]: a.view("|S16")[0] = "0011223344556677"

    In [19]: a.view(np.int8)
    Out[19]: array([48, 48, 49, 49, 50, 50, 51, 51, 52, 52, 53, 53, 54, 54, 55, 55], dtype=int8)

    In [20]: a.view(np.int8) - 48
    Out[20]: array([0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7], dtype=int8)






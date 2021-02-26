Minimal NumPy array from C++
==============================

I searched and they were all excessively complicated for my taste, so I rolled my own: 

* https://github.com/search?q=NPY+C%2B%2B

Documentation of the NPY serialization format

* https://github.com/numpy/numpy/blob/master/doc/neps/nep-0001-npy-format.rst


NP.hh(+NPU.hh) provides a lightweight header only NPY writing/reading. 
Just copy into your project and ``#include "NP.hh"`` to use. 



Tests of the header
--------------------

::

    cd tests
    ./go.sh 


Or do some manual testing::

    clang NPTest.cc -std=c++11 -lc++ -o /tmp/NPTest 
    gcc NPTest.cc -std=c++11 -lstdc++ -o /tmp/NPTest 
       ## build test executable using your compiler, 
       ## implementation is entirely in headers NP.hh and NPU.hh

    /tmp/NPTest /tmp/a.npy  
       ## run test executable writing a test NumPy array to the path given

    python -c "import numpy as np ; np.save('/tmp/b.npy', np.linspace(0,39,40,dtype=np.float32).reshape(-1,4) ) " 
       ## do the same thing from python using NumPy

    ls -l /tmp/a.npy /tmp/b.npy
       ## check the byte sizes are the same 

    diff /tmp/a.npy /tmp/b.npy
        ## check for a match 

    xxd /tmp/a.npy
    xxd /tmp/b.npy
        ## hexdump if there are differences 

    python -c "import numpy as np ; print np.load('/tmp/a.npy') " 
       ## load and print the C++ written NumPy array  

    python -c "import numpy as np ; print np.load('/tmp/b.npy') " 
       ## load and print the python written NumPy array  




A few references
-------------------

* https://github.com/diana-hep/c2numpy

* https://jcastellssala.com/2014/02/01/npy-in-c/

* https://github.com/onai/npio




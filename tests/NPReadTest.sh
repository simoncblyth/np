#!/bin/bash -l 

name=NPReadTest 
mkdir -p /tmp/$name 

gcc $name.cc \
     -std=c++11 \
       -I.. \
      -lstdc++ \
       -o /tmp/$name/$name 

[ $? -ne 0 ] && echo compile error && exit 1


/tmp/$name/$name 
[ $? -ne 0 ] && echo run error && exit 2

ipython -c "import numpy as np ; print(np.load(\"/tmp/$name/a.npy\")) ; "
[ $? -ne 0 ] && echo a error && exit 3

ipython -c "import numpy as np ; print(np.load(\"/tmp/$name/b.npy\")) ; "
[ $? -ne 0 ] && echo b error && exit 4

exit 0 

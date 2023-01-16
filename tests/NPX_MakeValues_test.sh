#!/bin/bash -l 

name=NPX_MakeValues_test 
export FOLD=/tmp/$name 
mkdir -p $FOLD 

#opts="-DWITH_VERBOSE"
opts=""

gcc $name.cc -std=c++11 -lstdc++ $opts -I.. -o $FOLD/$name 
[ $? -ne 0 ] && echo $BASH_SOURCE build error && exit 1 

$FOLD/$name
[ $? -ne 0 ] && echo $BASH_SOURCE run error && exit 2 

${IPYTHON:-ipython} --pdb -i $name.py 
[ $? -ne 0 ] && echo $BASH_SOURCE ana error && exit 3 

exit 0 


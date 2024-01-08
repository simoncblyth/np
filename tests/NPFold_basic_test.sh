#!/bin/bash -l
usage(){ cat << EOU
NPFold_basic_test.sh
=====================

::

   ~/np/tests/NPFold_basic_test.sh


EOU
}

cd $(dirname $(realpath $BASH_SOURCE))

name=NPFold_basic_test 
export FOLD=/tmp/$name 
bin=$FOLD/$name 
script=$name.py 


mkdir -p $FOLD 
gcc $name.cc -std=c++11 -lstdc++ -I.. -o $bin
[ $? -ne 0 ] && echo $BASH_SOURCE build error && exit 1 

$FOLD/$name 
[ $? -ne 0 ] && echo $BASH_SOURCE run error && exit 2

${IPYTHON:-ipython} --pdb -i $script
[ $? -ne 0 ] && echo $BASH_SOURCE ana error && exit 3

exit 0 



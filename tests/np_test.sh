#!/bin/bash -l 
usage(){ cat << EOU

~/np/tests/np_test.sh 

EOU
}


cd $(dirname $(realpath $BASH_SOURCE))

name=np_test 
script=$name.py 
export FOLD=/tmp/$name 
export NPY=$FOLD/a.npy 

mkdir -p $FOLD
bin=$FOLD/$name 

gcc $name.cc -std=c++11 -lstdc++ -I.. -o $bin
[ $? -ne 0 ] && echo $BASH_SOURCE : build error && exit 1

$bin
[ $? -ne 0 ] && echo $BASH_SOURCE : run error && exit 2

${IPYTHON:-ipython} --pdb -i $script 
[ $? -ne 0 ] && echo $BASH_SOURCE : ana error && exit 3


exit 0   



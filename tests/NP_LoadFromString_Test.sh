#!/bin/bash -l 

name=NP_LoadFromString_Test 
export FOLD=/tmp/$name
bin=$FOLD/$name
mkdir -p $FOLD 

gcc $name.cc -std=c++11 -lstdc++ -I.. -o $bin 
[ $? -ne 0 ] && echo $BASH_SOURCE : build error && exit 1 

$bin
[ $? -ne 0 ] && echo $BASH_SOURCE : run error && exit 2

${IPYTHON:-ipython} --pdb -i $name.py 
[ $? -ne 0 ] && echo $BASH_SOURCE : ana error && exit 3

exit 0 



#!/bin/bash
usage(){ cat << EOU

~/np/tests/NP_labels_test.sh 

EOU
}

name=NP_labels_test 
export FOLD=/tmp/$name 
mkdir -p $FOLD
bin=$FOLD/$name 

vars="0 BASH_SOURCE name FOLD bin"
for var in $vars ; do printf "%30s : %s \n" "$var" "${!var}" ; done 

gcc $name.cc -std=c++11 -lstdc++ -Wall -I.. -o $bin
[ $? -ne 0 ] && echo $BASH_SOURCE : build error && exit 1

$bin 
[ $? -ne 0 ] && echo $BASH_SOURCE : run error && exit 2

exit 0 



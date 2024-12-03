#!/bin/bash
usage(){ cat << EOU

~/np/tests/NPFold_test.sh

EOU
}

cd $(dirname $(realpath BASH_SOURCE))

name=NPFold_test 
export FOLD=/tmp/$name 
mkdir -p $FOLD 

bin=$FOLD/$name

gcc $name.cc -std=c++11 -Wall -lstdc++ -I.. -o $bin
[ $? -ne 0 ] && echo $BASH_SOURCE : build error && exit 1

$bin
[ $? -ne 0 ] && echo $BASH_SOURCE : run error && exit 2

exit 0 



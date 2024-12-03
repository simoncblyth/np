#!/bin/bash

usage(){ cat << EOU

~/np/tests/NPFold_meta_test

EOU
}
cd $(dirname $(realpath $BASH_SOURCE))

name=NPFold_meta_test 
export FOLD=/tmp/$name 
mkdir -p $FOLD 

bin=$FOLD/$name


defopt=build_run
arg=${1:-$defopt}

if [ "${arg/build}" != "$arg" ]; then 
   gcc $name.cc -std=c++11 -lstdc++ -I.. -o $bin
   [ $? -ne 0 ] && echo $BASH_SOURCE build error && exit 1 
fi 

if [ "${arg/run}" != "$arg" ]; then 
   $bin
   [ $? -ne 0 ] && echo $BASH_SOURCE run error && exit 2 
fi 

exit 0 


#!/bin/bash -l 

name=NPFold_meta_test 
export FOLD=/tmp/$name 
mkdir -p $FOLD 

defopt=build_run
arg=${1:-$defopt}

if [ "${arg/build}" != "$arg" ]; then 
    gcc $name.cc -std=c++11 -lstdc++ -I.. -o $FOLD/$name 
    [ $? -ne 0 ] && echo $BASH_SOURCE build error && exit 1 
fi 

if [ "${arg/run}" != "$arg" ]; then 
    $FOLD/$name 
    [ $? -ne 0 ] && echo $BASH_SOURCE run error && exit 2 
fi 

exit 0 


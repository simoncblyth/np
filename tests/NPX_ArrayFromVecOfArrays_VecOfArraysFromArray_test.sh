#!/bin/bash

usage(){ cat << EOU

~/np/tests/NPX_ArrayFromVecOfArrays_VecOfArraysFromArray_test.sh

EOU
}

cd $(dirname $(realpath $BASH_SOURCE)) 

name=NPX_ArrayFromVecOfArrays_VecOfArraysFromArray_test
export FOLD=/tmp/$name 
mkdir -p $FOLD

bin=$FOLD/$name
script=$name.py

defarg="build_run_ana"
arg=${1:-$defarg}

if [ "${arg/build}" != "$arg" ]; then 
    gcc $name.cc -std=c++17 -Wall -lstdc++ -I.. -o $bin
    [ $? -ne 0 ] && echo $BASH_SOURCE build error && exit 1 
fi 

if [ "${arg/run}" != "$arg" ]; then 
    $bin
    [ $? -ne 0 ] && echo $BASH_SOURCE run error && exit 2 
fi

if [ -f "$script" -a "${arg/ana}" != "$arg" ]; then 
    ${IPYTHON:-ipython} --pdb -i $script
    [ $? -ne 0 ] && echo $BASH_SOURCE ana error && exit 3 
fi 


#!/bin/bash
usage(){ cat << EOU

~/np/tests/NP_ReadKV_test.sh

EOU
}

cd $(dirname $(realpath $BASH_SOURCE))
source dbg__.sh 

name=NP_ReadKV_test 
export FOLD=/tmp/$name
mkdir -p $FOLD
bin=$FOLD/$name

arg=${1:-build_run}

if [ "${arg/build}" != "$arg" ]; then
    gcc $name.cc -g -std=c++17 -Wall -Wsign-compare -lstdc++ -I.. -o $bin
    [ $? -ne 0 ] && echo $BASH_SOURCE build error && exit 1 
fi 

if [ "${arg/run}" != "$arg" ]; then
    $bin
    [ $? -ne 0 ] && echo $BASH_SOURCE run error && exit 2 
fi 

if [ "${arg/dbg}" != "$arg" ]; then
   dbg__ $bin
   [ $? -ne 0 ] && echo $BASH_SOURCE dbg error && exit 3 
fi

exit 0 



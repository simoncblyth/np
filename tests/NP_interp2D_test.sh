#!/bin/bash -l
usage(){ cat << EOU
NP_interp2D_test.sh
====================

EOU
}

name=NP_interp2D_test
tmp=/tmp/$name
TMP=${TMP:-$tmp}
bin=$TMP/$name
script=$name.py 

mkdir -p $TMP
cd $(dirname $(realpath $BASH_SOURCE))

defarg=build_run_ana
arg=${1:-$defarg}


if [ "${arg/build}" != "$arg" ]; then 
    gcc $name.cc -g -std=c++11  -I.. -lstdc++ -o $bin
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

if [ "${arg/ana}" != "$arg" ]; then 
    ipython -i $script
    [ $? -ne 0 ] && echo ana error && exit 4
fi 

exit 0 


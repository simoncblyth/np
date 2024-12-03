#!/bin/bash

usage(){ cat << EOU

~/np/tests/demoTexNP.sh

EOU
}

cd $(dirname $(realpath $BASH_SOURCE))

name=demoTexNP

export FOLD=/tmp/$name
bin=$FOLD/$name
script=$name.py 
mkdir -p $FOLD

defarg=build_run_ana
arg=${1:-$defarg}

if [ "${arg/build}" != "$arg" ]; then 
    which nvcc 
    [ $? -ne 0 ] && echo $msg env error : NO nvcc && exit 1

    nvcc $name.cu -o $bin -std=c++11 -I..
    [ $? -ne 0 ] && echo $msg compile error && exit 2
fi 

if [ "${arg/run}" != "$arg" ]; then 
    $bin
    [ $? -ne 0 ] && echo $msg run error && exit 3
fi 

if [ "${arg/pdb}" != "$arg" ]; then 
   ${IPYTHON:-ipython} -i --pdb $script
   [ $? -ne 0 ] && echo $msg pdb error && exit 4
fi 

if [ "${arg/ana}" != "$arg" ]; then 
   ${PYTHON:-python} $script 
   [ $? -ne 0 ] && echo $msg ana error && exit 4
fi 

exit 0 



#!/bin/bash

usage(){ cat << EOU

~/np/tests/NP_copy_if_test.sh

EOU
}


cd $(dirname $(realpath $BASH_SOURCE))
source dbg__.sh 

defarg="info_build_run_ana"
arg=${1:-$defarg}
name=NP_copy_if_test
script=$name.py

export FOLD=/tmp/$name
mkdir -p $FOLD

export PYTHONPATH=../..

bin=$FOLD/$name
vars="BASH_SOURCE arg name FOLD bin"

if [ "${arg/info}" != "$arg" ]; then
    for var in $vars ; do printf "%20s : %s \n" "$var" "${!var}" ; done
fi 

if [ "${arg/build}" != "$arg" ]; then
    gcc $name.cc -I.. -g -std=c++17 -lstdc++ -o $bin
    [ $? -ne 0 ] && echo $BASH_SOURCE : build error && exit 1 
fi 

if [ "${arg/run}" != "$arg" ]; then
    $bin
    [ $? -ne 0 ] && echo $BASH_SOURCE : run error && exit 2 
fi 

if [ "${arg/dbg}" != "$arg" ]; then
    dbg__ $bin
    [ $? -ne 0 ] && echo $BASH_SOURCE : dbg error && exit 3
fi 

if [ "${arg/pdb}" != "$arg" ]; then
    ${IPYTHON:-ipython} --pdb -i $script
    [ $? -ne 0 ] && echo $BASH_SOURCE : pdb error && exit 4 
fi 

if [ "${arg/ana}" != "$arg" ]; then
    ${PYTHON:-python}  $script 
    [ $? -ne 0 ] && echo $BASH_SOURCE : ana error && exit 5 
fi 

exit 0 


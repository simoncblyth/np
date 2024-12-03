#!/bin/bash

usage(){ cat << EOU

~/np/tests/NPX_MakeCharArray_test.sh

EOU
}

name=NPX_MakeCharArray_test
cd $(dirname $(realpath $BASH_SOURCE))
export PYTHONPATH=../..

SDIR=$PWD

export FOLD=${TMP:-/tmp/$USER/opticks}/$name
mkdir -p $FOLD
bin=$FOLD/$name
script=$name.py



defarg="info_build_run_ana"
arg=${1:-$defarg}

vars="BASH_SOURCE PWD SDIR name FOLD bin arg"

if [ "${arg/info}" != "$arg" ]; then 
   for var in $vars ; do printf "%25s : %s\n" "$var" "${!var}" ; done 
fi

if [ "${arg/build}" != "$arg" ]; then 
   gcc $name.cc -g -std=c++11 -Wall -lstdc++ -I$SDIR/.. -o $bin
   [ $? -ne 0 ] && echo $BASH_SOURCE : build error && exit 1 
fi 

if [ "${arg/run}" != "$arg" ]; then 
   $bin
   [ $? -ne 0 ] && echo $BASH_SOURCE : run error && exit 2 
fi 

if [ "${arg/pdb}" != "$arg" ]; then 
   ${IPYTHON:-ipython} --pdb -i $script
   [ $? -ne 0 ] && echo $BASH_SOURCE : pdb error && exit 3
fi 

if [ "${arg/ana}" != "$arg" ]; then 
   ${PYTHON:-python} $script 
   [ $? -ne 0 ] && echo $BASH_SOURCE : run error && exit 4
fi 

exit 0 


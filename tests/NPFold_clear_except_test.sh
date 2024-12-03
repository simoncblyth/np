#!/bin/bash
usage(){ cat << EOU
NPFold_clear_except_test.sh
=============================

~/np/tests/NPFold_clear_except_test.sh


EOU
}

defarg="info_build_run_ana"
arg=${1:-$defarg}

cd $(dirname $(realpath $BASH_SOURCE))
source dbg__.sh 

name=NPFold_clear_except_test 
export FOLD=/tmp/$name
mkdir -p $FOLD
bin=$FOLD/$name
script=$name.py

export PYTHONPATH=../..

vars="BASH_SOURCE name defarg arg FOLD bin"

if [ "${arg/info}" != "$arg" ]; then
   for var in $vars ; do printf "%20s : %s \n" "$var" "${!var}" ; done  
fi 

if [ "${arg/clean}" != "$arg" ]; then
   rm -rf $FOLD
fi 

if [ "${arg/build}" != "$arg" ]; then 
   gcc $name.cc -g -std=c++11 -Wall -lstdc++ -I.. -o $bin
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
   [ $? -ne 0 ] && echo $BASH_SOURCE : ana error && exit 4
fi 

if [ "${arg/ana}" != "$arg" ]; then 
   ${PYTHON:-python} $script 
   [ $? -ne 0 ] && echo $BASH_SOURCE : ana error && exit 5
fi 


exit 0 


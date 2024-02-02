#!/bin/bash -l 

name=NPX_ArrayFromDiscoMapUnordered_test

cd $(dirname $(realpath $BASH_SOURCE)) 

export FOLD=/tmp/$name
mkdir -p $FOLD

defarg=build_run_ana
arg=${1:-$defarg}


if [ "${arg/build}" != "$arg" ]; then
   gcc $name.cc -std=c++11 -lstdc++ -I.. -o $FOLD/$name 
   [ $? -ne 0 ] && echo $BASH_SOURCE build error && exit 1 
fi 

if [ "${arg/run}" != "$arg" ]; then
   $FOLD/$name 
   [ $? -ne 0 ] && echo $BASH_SOURCE run error && exit 2
fi 

if [ "${arg/ana}" != "$arg" ]; then
   ${IPYTHON:-ipython} --pdb -i $name.py 
   [ $? -ne 0 ] && echo $BASH_SOURCE ana error && exit 3
fi 

exit 0 


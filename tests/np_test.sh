#!/bin/bash
usage(){ cat << EOU

~/np/tests/np_test.sh 

EOU
}


cd $(dirname $(realpath $BASH_SOURCE))

name=np_test 
script=$name.py 
export FOLD=/tmp/$name 
export NPY=$FOLD/a.npy 


mkdir -p $FOLD
bin=$FOLD/$name 

defarg="info_build_run_ana"
arg=${1:-$defarg}

vars="name anaopt ANAOPT FOLD"

if [ "${arg/info}" != "$arg" ]; then
   for var in $vars ; do printf "%20s : %s\n" "$var" "${!var}" ; done 
fi 

if [ "${arg/build}" != "$arg" ]; then
   gcc $name.cc -std=c++11 -lstdc++ -I.. -o $bin
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
   [ $? -ne 0 ] && echo $BASH_SOURCE : ana error && exit 4
fi 


exit 0   



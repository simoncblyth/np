#!/bin/bash -l 
usage(){ cat << EOU

::

   ~/np/tests/NPFold_copy_test.sh  


EOU
}


defarg="info_build_run_ana"
arg=${1:-$defarg}

cd $(dirname $BASH_SOURCE)

name=NPFold_copy_test 
export FOLD=/tmp/$name
mkdir -p $FOLD
bin=$FOLD/$name

vars="BASH_SOURCE name defarg arg FOLD bin"

if [ "${arg/info}" != "$arg" ]; then
   for var in $vars ; do printf "%20s : %s \n" "$var" "${!var}" ; done  
fi 

if [ "${arg/clean}" != "$arg" ]; then
   rm -rf $FOLD
fi 

if [ "${arg/build}" != "$arg" ]; then 
   gcc $name.cc -std=c++11 -lstdc++ -I.. -o $bin
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

if [ "${arg/ana}" != "$arg" ]; then 
   ${IPYTHON:-ipython} --pdb -i $name.py 
   [ $? -ne 0 ] && echo $BASH_SOURCE : ana error && exit 4
fi 

exit 0 


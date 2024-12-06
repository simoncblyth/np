#!/bin/bash
usage(){ cat << EOU
NPFold_concat_test.sh
=====================

::

   ~/np/tests/NPFold_concat_test.sh


EOU
}

cd $(dirname $(realpath $BASH_SOURCE))
source dbg__.sh 

name=NPFold_concat_test 
export FOLD=/tmp/$name 
bin=$FOLD/$name 
script=$name.py 
mkdir -p $FOLD 

export PYTHONPATH=../..

defarg="build_run_ana"
arg=${1:-$defarg}

if [ "${arg/build}" != "$arg" ]; then
   gcc $name.cc -std=c++11 -lstdc++ -g -I.. -o $bin
   [ $? -ne 0 ] && echo $BASH_SOURCE build error && exit 1 
fi 

if [ "${arg/run}" != "$arg" ]; then
   rm -rf /tmp/NPFold_concat_test/concat  ## hardcode for safety
   $bin 
   [ $? -ne 0 ] && echo $BASH_SOURCE run error && exit 2
fi

if [ "${arg/dbg}" != "$arg" ]; then
   rm -rf /tmp/NPFold_concat_test/concat  ## hardcode for safety
   gdb__ $bin 
   [ $? -ne 0 ] && echo $BASH_SOURCE dbg error && exit 2
fi

if [ "${arg/pdb}" != "$arg" ]; then
   ${IPYTHON:-ipython} --pdb -i $script
   [ $? -ne 0 ] && echo $BASH_SOURCE pdb error && exit 3
fi 

if [ "${arg/ana}" != "$arg" ]; then
   ${PYTHON:-python} $script
   [ $? -ne 0 ] && echo $BASH_SOURCE ana error && exit 4
fi 

exit 0 



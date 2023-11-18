#!/bin/bash -l 

name=NPX_MakeCharArray_test
cd $(dirname $BASH_SOURCE)
SDIR=$PWD

export FOLD=${TMP:-/tmp/$USER/opticks}/$name
mkdir -p $FOLD
bin=$FOLD/$name

defarg="info_build_run_ana"
arg=${1:-$defarg}

vars="BASH_SOURCE PWD SDIR name FOLD bin arg"

if [ "${arg/info}" != "$arg" ]; then 
   for var in $vars ; do printf "%25s : %s\n" "$var" "${!var}" ; done 
fi

if [ "${arg/build}" != "$arg" ]; then 
   gcc $name.cc -g -std=c++11 -lstdc++ -I$SDIR/.. -o $bin
   [ $? -ne 0 ] && echo $BASH_SOURCE : build error && exit 1 
fi 

if [ "${arg/run}" != "$arg" ]; then 
   $bin
   [ $? -ne 0 ] && echo $BASH_SOURCE : run error && exit 2 
fi 

if [ "${arg/ana}" != "$arg" ]; then 
   ${IPYTHON:-ipython} --pdb -i $name.py 
   [ $? -ne 0 ] && echo $BASH_SOURCE : run error && exit 3
fi 


exit 0 

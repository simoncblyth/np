#!/bin/bash
usage(){ cat << EOU
NPFold_save_load_empty_test.sh
==========================

::

   ~/np/tests/NPFold_save_load_empty_test.sh


EOU
}

cd $(dirname $(realpath $BASH_SOURCE))
source dbg__.sh 

name=NPFold_save_load_empty_test 
TMP=${TMP:-/tmp/$USER/opticks}
bin=$TMP/$name

export FOLD=$TMP/${name}_fold
mkdir -p $FOLD 
rm -rf $FOLD

vars="name SDIR FOLD"

defarg="info_build_run"
arg=${1:-$defarg}

if [ "${arg/info}" != "$arg" ]; then
    for var in $vars ; do printf "%20s : %s \n" "$var" "${!var}" ; done
fi

if [ "${arg/build}" != "$arg" ]; then
    gcc $name.cc -std=c++11 -Wall -g -lstdc++ -I.. -o $bin 
    [ $? -ne 0 ] && echo $BASH_SOURCE : build error && exit 1
fi 


if [ "${arg/run}" != "$arg" ]; then
   $bin
   [ $? -ne 0 ] && echo $BASH_SOURCE : run error && exit 2
fi 

if [ "${arg/dbg}" != "$arg" ]; then
   dbg__ $bin
   [ $? -ne 0 ] && echo $BASH_SOURCE : dbg error && exit 2
fi 

exit 0 


#!/bin/bash
usage(){ cat << EOU

~/np/tests/NPFold_Load_test.sh

EOU
}

cd $(dirname $(realpath $BASH_SOURCE))
source dbg__.sh 

name=NPFold_Load_test 
bin=/tmp/$name 

#export NPFold__load_DUMP=1
export NPFold__load_index_DUMP=1
export NPFold__load_dir_DUMP=1

source $HOME/.opticks/GEOM/GEOM.sh 

defarg="build_run"
arg=${1:-$defarg}

if [ "${arg/build}" != "$arg" ]; then 
    gcc $name.cc -g -I.. -std=c++11 -Wall -lstdc++ -o $bin 
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




exit 0 


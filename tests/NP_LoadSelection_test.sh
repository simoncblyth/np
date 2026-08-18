#!/bin/bash

usage(){ cat << EOU

~/np/tests/NP_LoadSelection_test.sh

EOU
}

cd $(dirname $(realpath $BASH_SOURCE))
export PYTHONPATH=../..
source dbg__.sh

name=NP_LoadSelection_test

tmp=/tmp/$USER/np
TMP=${TMP:-$tmp}

export FOLD=$TMP/$name
bin=$FOLD/$name

script=$name.py
mkdir -p $FOLD

defarg="gcc_run_ana"
arg=${1:-$defarg}

if [ "${arg/gcc}" != "$arg" ]; then
    gcc $name.cc -g -std=c++17 -lstdc++ -I.. -o $bin
    [ $? -ne 0 ] && echo $BASH_SOURCE build fail && exit 1
fi

if [ "${arg/run}" != "$arg" ]; then
    $bin
    [ $? -ne 0 ] && echo $BASH_SOURCE run fail && exit 2
fi

if [ "${arg/dbg}" != "$arg" ]; then
    dbg__  $bin
    [ $? -ne 0 ] && echo $BASH_SOURCE dbg fail && exit 3
fi

if [ "${arg/pdb}" != "$arg" ]; then
    ${IPYTHON:-ipython} --pdb -i $script
    [ $? -ne 0 ] && echo $BASH_SOURCE pdb fail && exit 4
fi

if [ "${arg/ana}" != "$arg" ]; then
    ${PYTHON:-python} $script
    [ $? -ne 0 ] && echo $BASH_SOURCE ana fail && exit 4
fi

exit 0



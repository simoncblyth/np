#!/bin/bash

usage(){ cat << EOU

~/np/tests/NPX_PLoad_test.sh

EOU
}

cd $(dirname $(realpath $BASH_SOURCE))

name=NPX_PLoad_test

tmp=/tmp/$USER/np
TMP=${TMP:-$tmp}


export FOLD=$TMP/$name
mkdir -p $FOLD

bin=$FOLD/$name
script=$name.py

defarg=info_gcc_run_pdb
arg=${1:-$defarg}

if [[ "$arg" =~ info ]]; then
   vv="BASH_SOURCE name tmp TMP FOLD bin script PWD defarg arg"
   for v in $vv ; do printf "%30s : %s\n" "$v" "${!v}" ; done
fi

if [[ "$arg" =~ gcc ]]; then
   gcc $name.cc -std=c++17 -lstdc++ -lm -I.. -o $bin
   [ $? -ne 0 ] && echo $BASH_SOURCE - gcc ERROR && exit 1
fi

if [[ "$arg" =~ run ]]; then
   $bin
   [ $? -ne 0 ] && echo $BASH_SOURCE - run ERROR && exit 2
fi

if [[ "$arg" =~ pdb ]]; then
   PYTHONPATH=$HOME ${IPYTHON:-ipython} --pdb -i $script
   [ $? -ne 0 ] && echo $BASH_SOURCE - pdb ERROR && exit 3
fi


exit 0


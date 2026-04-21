#!/usr/bin/env bash

usage(){ cat << EOU

~/np/tests/NP_MakePCopyStripZeroPadding_test.sh

EOU
}


cd $(dirname $(realpath $BASH_SOURCE))

name=NP_MakePCopyStripZeroPadding_test

defarg=info_gcc_run_pdb
arg=${1:-$defarg}

tmp=/tmp/$USER/np
export TMP=${TMP:-$tmp}
export FOLD=$TMP/$name

mkdir -p $FOLD
bin=$FOLD/$name
script=$name.py


vv="BASH_SOURCE PWD defarg arg name tmp TMP FOLD bin script"


if [ "${arg/info}" != "$arg" ]; then
    for v in $vv ; do printf "%30s : %s\n" "$v" "${!v}" ; done
fi

if [ "${arg/gcc}" != "$arg" ]; then

    gcc $name.cc \
       -g -std=c++17 -lstdc++ \
       -I.. \
       -o $bin

   [ $? -ne 0 ] && echo $BASH_SOURCE gcc error && exit 1
fi

if [ "${arg/run}" != "$arg" ]; then
   $bin
   [ $? -ne 0 ] && echo $BASH_SOURCE run error && exit 2
fi

if [ "${arg/pdb}" != "$arg" ]; then
   PYTHONPATH=../.. ${IPYTHON:-ipython} --pdb -i $script
   [ $? -ne 0 ] && echo $BASH_SOURCE pdb error && exit 3
fi

exit 0



#!/bin/bash

usage(){ cat << EOU

~/np/tests/NP_Load_test.sh

EOU
}

cd $(dirname $(realpath $BASH_SOURCE))

name=NP_Load_test

tmp=/tmp/$NAME/np
export TMP=${TMP:-$tmp}
export FOLD=$TMP/$name
mkdir -p $FOLD

export HITFOLD=/data1/blyth/tmp/GEOM/J25_4_0_opticks_Debug/CSGOptiXSMTest/ALL1_Debug_Philox_vvvlarge_evt/A000


bin=$FOLD/$name

defarg="info_build_run"
arg=${1:-$defarg}

vv="BASH_SOURCE PWD name bin PWD defarg arg tmp TMP FOLD HITFOLD"


if [ "${arg/info}" != "$arg" ]; then
   for v in $vv ; do printf "%30s : %s\n" "$v" "${!v}" ; done
fi

if [ "${arg/build}" != "$arg" ]; then
   gcc $name.cc -std=c++17 -lstdc++ -I.. -g -o $bin
   [ $? -ne 0 ] && echo $BASH_SOURCE build error && exit 1
fi

if [ "${arg/run}" != "$arg" ]; then
   $bin
   [ $? -ne 0 ] && echo $BASH_SOURCE run error && exit 2
fi

exit 0



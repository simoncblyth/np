#!/bin/bash
usage(){ cat << EOU

~/np/tests/NPFold_test.sh

EOU
}

cd $(dirname $(realpath $BASH_SOURCE))

name=NPFold_test
export FOLD=/tmp/$USER/np/$name
mkdir -p $FOLD

export TESTFOLD=/data1/blyth/tmp/GEOM/J26_4_1_opticks_Debug_g411/CSGOptiXSMTest/ALL1_Release_Philox_medium_evt/A000
#export TESTFOLD=/data1/blyth/tmp/GEOM/J26_4_1_opticks_Debug_g411/CSGOptiXSMTest/ALL1_Debug_Philox_medium_evt/A000


bin=$FOLD/$name

gcc $name.cc -std=c++17 -Wall -lstdc++ -I.. -g -o $bin
[ $? -ne 0 ] && echo $BASH_SOURCE : build error && exit 1

export NPFold__load_DUMP=1
export NPFold__save_DUMP=1

gdb $bin
[ $? -ne 0 ] && echo $BASH_SOURCE : run error && exit 2






exit 0



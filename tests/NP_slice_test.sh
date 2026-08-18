#!/bin/bash

usage(){ cat << EOU

~/np/tests/NP_slice_test.sh

EOU
}


name=NP_slice_test

tmp=/tmp/$USER/np
TMP=${TMP:-$tmp}
export FOLD=$TMP/$name
mkdir -p $FOLD

bin=$FOLD/$name

vv="name tmp TMP FOLD bin"
for v in $vv ; do printf "%30s : %s\n" "$v" "${!v}" ; done


cd $(dirname $(realpath $BASH_SOURCE))

gcc $name.cc -DNOT_WITH_VERBOSE -std=c++17 -lstdc++ -I.. -o $bin
[ $? -ne 0 ] && echo $BASH_SOURCE - gcc error && exit 1

$bin
[ $? -ne 0 ] && echo $BASH_SOURCE - run error && exit 1

exit 0


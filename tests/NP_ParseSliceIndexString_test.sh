#!/bin/bash
usage(){ cat << EOU

~/np/tests/NP_ParseSliceIndexString_test.sh

EOU
}

name=NP_ParseSliceIndexString_test

tmp=/tmp/$NAME/np
export TMP=${TMP:-$tmp}
export FOLD=$TMP/$name
mkdir -p $FOLD

bin=$FOLD/$name

gcc $name.cc -I.. -std=c++17 -lstdc++ -o $bin && $bin




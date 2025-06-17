#!/bin/bash
usage(){ cat << EOU

~/np/tests/NP_Load_test.sh

EOU
}

name=NP_Load_test

tmp=/tmp/$NAME/np
export TMP=${TMP:-$tmp}
export FOLD=$TMP/$name
mkdir -p $FOLD

bin=$FOLD/$name

gcc $name.cc -std=c++17 -lstdc++ -I.. -g -o $bin  && $bin



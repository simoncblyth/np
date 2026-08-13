#!/bin/bash
usage(){ cat << EOU

~/np/tests/NPX_FromString_test.sh

EOU
}

name=NPX_FromString_test 

tmp=/tmp/$USER/np
TMP=${TMP:-$tmp}
FOLD=$TMP/$name
mkdir -p $FOLD

bin=$FOLD/$name


cd $(dirname $(realpath $BASH_SOURCE))


vv="BASH_SOURCE name tmp TMP FOLD bin PWD"
for v in $vv ; do printf "%30s : %s\n" "$v" "${!v}" ; done


gcc $name.cc -std=c++17 -lstdc++ -I.. -o $bin && $bin


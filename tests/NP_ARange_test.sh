#!/usr/bin/env bash
usage(){ cat << EOU

~/np/tests/NP_ARange_test.sh

EOU
}

cd $(dirname $(realpath $BASH_SOURCE))

name=NP_ARange_test

tmp=/tmp/$USER/np
TMP=${TMP:-$tmp}

export FOLD=$TMP/$name
mkdir -p $FOLD
bin=$FOLD/$name


vv="BASH_SOURCE PWD name tmp TMP FOLD bin"
for v in $vv ; do printf "%30s : %s\n" "$v" "${!v}" ; done

gcc $name.cc -I.. -std=c++11 -lstdc++ -o $bin
[ $? -ne 0 ] && echo $BASH_SOURCE - build error && exit 1

$bin
[ $? -ne 0 ] && echo $BASH_SOURCE - run error && exit 2

exit 0



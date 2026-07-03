#!/bin/bash

usage(){ cat << EOU

~/np/tests/NP_get_meta_string_test.sh

EOU
}


cd $(dirname $(realpath $BASH_SOURCE))

defarg="info_gcc_run"
arg=${1:-$defarg}

name="NP_get_meta_string_test"

tmp=/tmp/$USER/np/$name
TMP=${TMP:-$tmp}
FOLD=$TMP/$name
mkdir -p $FOLD

bin=$FOLD/$name


vv="BASH_SOURCE PWD defarg arg name tmp TMP FOLD bin"

if [[ "$arg" =~ info ]]; then
    for v in $vv ; do printf "%30s : %s\n" "$v" "${!v}" ; done
fi

if [[ "$arg" =~ gcc ]]; then
    gcc $name.cc -std=c++17 -lstdc++ -I.. -o $bin
    [ $? -ne 0 ] && echo $BASH_SOURCE - gcc error && exit 1
fi

if [[ "$arg" =~ run ]]; then
    $bin
    [ $? -ne 0 ] && echo $BASH_SOURCE - run error && exit 1
fi

exit 0


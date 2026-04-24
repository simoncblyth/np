#!/bin/bash

usage(){ cat << EOU

~/np/tests/NP_set_meta_get_meta_test.sh

EOU
}
cd $(dirname $(realpath $BASH_SOURCE))

name=NP_set_meta_get_meta_test
export FOLD=/tmp/$name

mkdir -p $FOLD
bin=$FOLD/$name

defarg=info_gcc_run
arg=${1:-$defarg}


vv="BASH_SOURCE PWD name FOLD bin defarg arg"

if [[ "$arg" =~ info ]]; then
    for v in $vv ; do printf "%30s : %s\n" "$v" "${!v}" ; done
fi

if [[ "$arg" =~ gcc ]]; then
    gcc $name.cc -std=c++17 -Wall -lstdc++ -g -I.. -DDEBUG -o $bin
    [ $? -ne 0 ] && echo $BASH_SOURCE - gcc fail && exit 1
fi

if [[ "$arg" =~ run ]]; then
    $bin
    [ $? -ne 0 ] && echo $BASH_SOURCE - run fail && exit 2
fi

if [[ "$arg" =~ dbg ]]; then
    gdb -ex r --args $bin
    [ $? -ne 0 ] && echo $BASH_SOURCE - run fail && exit 2
fi

exit 0



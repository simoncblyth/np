#!/bin/bash

usage(){ cat << EOU

~/np/tests/NP_LoadOptional_test.sh

EOU
}


name=NP_LoadOptional_test
bin=/tmp/$name

cd $(dirname $(realpath $BASH_SOURCE))

gcc $name.cc -std=c++11 -Wall -lstdc++ -I.. -DWITH_VERBOSE  -o $bin && $bin




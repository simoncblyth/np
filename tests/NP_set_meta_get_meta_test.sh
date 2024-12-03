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

gcc $name.cc -std=c++11 -Wall -lstdc++ -I.. -DDEBUG -o $bin && $bin


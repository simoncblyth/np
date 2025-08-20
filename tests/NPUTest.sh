#!/bin/bash
usage(){ cat << EOU

~/np/tests/NPUTest.sh

EOU
}

name=NPUTest
bin=/tmp/$name

cd $(dirname $(realpath $BASH_SOURCE))
gcc $name.cc -std=c++17 -I.. -lstdc++ -o $bin && $bin



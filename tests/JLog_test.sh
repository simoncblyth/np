#!/bin/bash
usage(){ cat << EOU

~/np/tests/JLog_test.sh

EOU
}

cd $(dirname $(realpath $BASH_SOURCE))

name=JLog_test
bin=/tmp/$name

gcc $name.cc -std=c++17 -lstdc++ -I.. -o $bin
[ $? -ne 0 ] && echo $BASH_SOURCE gcc error && exit 1

$bin
[ $? -ne 0 ] && echo $BASH_SOURCE run error && exit 2

exit 0


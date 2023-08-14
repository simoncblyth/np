#!/bin/bash -l 

SDIR=$(cd $(dirname $BASH_SOURCE) && pwd)
name=NPFold_test 
export FOLD=/tmp/$name 
mkdir -p $FOLD 

bin=$FOLD/$name

gcc $SDIR/$name.cc \
    -std=c++11 -lstdc++ \
    -I$SDIR/.. -o $bin
[ $? -ne 0 ] && echo $BASH_SOURCE : build error && exit 1

$bin
[ $? -ne 0 ] && echo $BASH_SOURCE : run error && exit 2



exit 0 



#!/bin/bash -l 

name=NPFold_Load_test 
bin=/tmp/$name 

source $HOME/.opticks/GEOM/GEOM.sh 

gcc $name.cc -I.. -std=c++11 -lstdc++ -o $bin 
[ $? -ne 0 ] && echo $BASH_SOURCE : build error && exit 1 

$bin
[ $? -ne 0 ] && echo $BASH_SOURCE : run error && exit 2

exit 0 


#!/bin/bash 

name=NPInterp2DSimpleTest 

mkdir -p /tmp/$name

arg=${1:-build_run_ana}


if [ "${arg/build}" != "$arg" ]; then 
    gcc $name.cc -std=c++11  -I.. -lstdc++ -o /tmp/$name/$name 
    [ $? -ne 0 ] && echo compile error && exit 1 
fi 

if [ "${arg/run}" != "$arg" ]; then 
    /tmp/$name/$name
    [ $? -ne 0 ] && echo run error && exit 2
fi 

if [ "${arg/ana}" != "$arg" ]; then 
    ipython -i $name.py 
    [ $? -ne 0 ] && echo ana error && exit 3
fi 


exit 0 



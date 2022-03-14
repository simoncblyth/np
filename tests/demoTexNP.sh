#!/bin/bash -l 

msg="=== $BASH_SOURCE :"

name=demoTexNP
bin=/tmp/$name/$name

mkdir -p /tmp/$name

arg=${1:-build_run_ana}

if [ "${arg/build}" != "$arg" ]; then 

    which nvcc 
    [ $? -ne 0 ] && echo $msg env error : NO nvcc && exit 1

    nvcc $name.cu -o $bin -std=c++11 -I..
    [ $? -ne 0 ] && echo $msg compile error && exit 2
fi 

if [ "${arg/run}" != "$arg" ]; then 
    echo $bin
    ls -l $bin
    $bin
    [ $? -ne 0 ] && echo $msg run error && exit 3
fi 

if [ "${arg/ana}" != "$arg" ]; then 
    ipython -i $name.py 
    [ $? -ne 0 ] && echo $msg ana error && exit 4
fi 

exit 0 



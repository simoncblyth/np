#!/bin/bash -l 

name=NP_ReadKV_test 

arg=${1:-build_run}

if [ "${arg/build}" != "$arg" ]; then
    gcc $name.cc -g -std=c++11 -Wall -Wsign-compare -lstdc++ -I.. -o /tmp/$name
    [ $? -ne 0 ] && echo $BASH_SOURCE build error && exit 1 
fi 

if [ "${arg/run}" != "$arg" ]; then
    /tmp/$name
    [ $? -ne 0 ] && echo $BASH_SOURCE run error && exit 2 
fi 

if [ "${arg/dbg}" != "$arg" ]; then
   case $(uname) in 
      Darwin) lldb__ /tmp/$name ;;
      Linux)  gdb__ /tmp/$name ;;
   esac
   [ $? -ne 0 ] && echo $BASH_SOURCE dbg error && exit 3 
fi

exit 0 



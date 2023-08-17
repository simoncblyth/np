#!/bin/bash -l 


SDIR=$(cd $(dirname $BASH_SOURCE) && pwd)
name=NPX_ArrayFromVec_test
FOLD=/tmp/$name
mkdir -p $FOLD

export FOLD

bin=$FOLD/$name
script=$SDIR/$name.py 

defarg="info_build_run_ana"
arg=${1:-$defarg}
vars="BASH_SOURCE FOLD"


if [ "${arg/info}" != "$arg" ]; then 
    for var in $vars ; do printf "%30s : %s \n" "$var" "${!var}" ; done 
fi 

if [ "${arg/build}" != "$arg" ]; then 
    gcc $SDIR/$name.cc -std=c++11 -lstdc++ -I$SDIR/.. -o $bin 
    [ $? -ne 0 ] && echo $BASH_SOURCE build error && exit 1 
fi 

if [ "${arg/run}" != "$arg" ]; then 
    $bin
    [ $? -ne 0 ] && echo $BASH_SOURCE run error && exit 1 
fi 

if [ "${arg/dbg}" != "$arg" ]; then 
    case $(uname) in
    Darwin) lldb__ $bin ;;
    Linux)  gdb__ $bin ;;
    esac
    [ $? -ne 0 ] && echo $BASH_SOURCE dbg error && exit 3
fi 

if [ "${arg/ana}" != "$arg" ]; then 
    ${IPYTHON:-ipython} --pdb -i $script
    [ $? -ne 0 ] && echo $BASH_SOURCE ana error && exit 4
fi 

exit 0 


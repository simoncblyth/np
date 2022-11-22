#!/bin/bash -l 

deftest=NP_MakeSelectCopy_test
name=${TEST:-$deftest}

fold=/tmp/$name
bin=$fold/$name
mkdir -p $fold 

export FOLD=$fold

defarg="build_run_ana" 
arg=${1:-$defarg}

if [ "${arg/build}" != "$arg" ]; then 
    #opt="-DDEBUG"
    opt=""
    gcc $name.cc -g $opt -std=c++11 -lstdc++ -I.. -o $bin
    [ $? -ne 0 ] && echo $BASH_SOURCE build fail && exit 1 
fi 

if [ "${arg/run}" != "$arg" ]; then 
    $bin
    [ $? -ne 0 ] && echo $BASH_SOURCE run fail && exit 2
fi 

if [ "${arg/dbg}" != "$arg" ]; then 
    case $(uname) in 
       Darwin) lldb__ $bin ;;
       Linux)  gdb__  $bin ;;
    esac
    [ $? -ne 0 ] && echo $BASH_SOURCE dbg fail && exit 3
fi 

if [ "${arg/ana}" != "$arg" ]; then 
    ${IPYTHON:-ipython} --pdb -i $name.py 
    [ $? -ne 0 ] && echo $BASH_SOURCE ana fail && exit 4
fi 

exit 0 




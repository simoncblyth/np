#!/bin/bash
usage(){ cat << EOU

~/np/tests/NPMakeICDFTest.sh

EOU
}

cd $(dirname $(realpath $BASH_SOURCE))

name=NPMakeICDFTest

export FOLD=/tmp/$name
mkdir -p $FOLD 
bin=$FOLD/$name
script=$name.py

defarg=build_run_ana
arg=${1:-$defarg}

#opt=-DDEBUG
opt=

if [ "${arg/build}" != "$arg" ]; then
   gcc $name.cc -std=c++17 -I.. -Wall $opt  -lstdc++ -o $bin
   [ $? -ne 0 ] && echo $BASH_SOURCE build fail && exit 1 
fi 

if [ "${arg/run}" != "$arg" ]; then
   $bin
   [ $? -ne 0 ] && echo $BASH_SOURCE run fail && exit 2 
fi

if [ "${arg/pdb}" != "$arg" ]; then
   ${IPYTHON:-ipython} --pdb -i $script
   [ $? -ne 0 ] && echo $BASH_SOURCE pdb  fail && exit 3
fi

if [ "${arg/ana}" != "$arg" ]; then
   ${PYTHON:-python} $script
   [ $? -ne 0 ] && echo $BASH_SOURCE ana  fail && exit 4
fi

exit 0 


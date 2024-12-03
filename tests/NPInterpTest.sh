#!/bin/bash 

usage(){ cat << EOU

~/np/tests/NPInterpTest.sh

EOU
}
cd $(dirname $(realpath $BASH_SOURCE))

name=NPInterpTest 
export FOLD=/tmp/$name
bin=$FOLD/$name
script=$name.py

mkdir -p $FOLD

defarg=build_run_ana
arg=${1:-$defarg}


if [ "${arg/build}" != "$arg" ]; then  
   gcc $name.cc -std=c++17 -Wall -I.. -lstdc++ -o $bin
   [ $? -ne 0 ] && echo $BASH_SOURCE compile error && exit 1 
fi 

if [ "${arg/run}" != "$arg" ]; then  
   $bin
   [ $? -ne 0 ] && echo $BASH_SOURCE run error && exit 2
fi

if [ "${arg/pdb}" != "$arg" ]; then  
   ${IPYTHON:-ipython} --pdb -i $script
   [ $? -ne 0 ] && echo $BASH_SOURCE pdb  error && exit 3
fi

if [ "${arg/ana}" != "$arg" ]; then  
   ${PYTHON:-python} $script
   [ $? -ne 0 ] && echo $BASH_SOURCE ana error && exit 4
fi

exit 0 


#!/bin/bash
usage(){ cat << EOU

~/np/tests/NPpdomainTest.sh

EOU
}

cd $(dirname $(realpath $BASH_SOURCE))

name=NPpdomainTest 
export FOLD=/tmp/$name

bin=$FOLD/$name
script=$name.py 

mkdir -p $FOLD
mkdir -p $FOLD/3d 


defarg=build_run_ana
arg=${1:-$defarg}

if [ "${arg/build}" != "$arg" ]; then 
   gcc $name.cc -DDEBUG -I.. -std=c++11 -lstdc++ -o $bin
   [ $? -ne 0 ] && echo $BASH_SOURCE build FAIL && exit 1 
fi

if [ "${arg/run}" != "$arg" ]; then 
   $bin
   [ $? -ne 0 ] && echo $BASH_SOURCE run FAIL && exit 2
fi

if [ "${arg/pdb}" != "$arg" ]; then 
   ${IPYTHON:-ipython} --pdb  -i $script
   [ $? -ne 0 ] && echo $BASH_SOURCE pdb FAIL && exit 3
fi

if [ "${arg/ana}" != "$arg" ]; then 
   ${PYTHON:-python} $script
   [ $? -ne 0 ] && echo $BASH_SOURCE ana FAIL && exit 3
fi


exit 0 


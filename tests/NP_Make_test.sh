#!/bin/bash
usage(){ cat << EOU
NP_Make_test.sh
=================

~/np/tests/NP_Make_test.sh 

EOU
}

cd $(dirname $(realpath $BASH_SOURCE))

name=NP_Make_test 

test=Large
export TEST=${TEST:-$test}

tmp=/data/$USER/np
TMP=${TMP:-$tmp}

export FOLD=$tmp/$name 
mkdir -p $FOLD 

bin=$FOLD/$name
sauce=$name.cc
script=$name.py

defarg="info_build_run_ana"
arg=${1:-$defarg}

vars="BASH_SOURCE name sauce script tmp TMP FOLD defarg arg test TEST opt" 

## both these stop at first error : but max-errors gives context 
#opt=-Wfatal-errors
opt=-fmax-errors=1

if [ "${arg/info}" != "$arg" ]; then
    for var in $vars ; do printf "%20s : %s\n" "$var" "${!var}" ; done
fi 

if [ "${arg/build}" != "$arg" ]; then
   gcc $sauce -std=c++11 -lstdc++ -I.. -Wall $opt -o $bin
   [ $? -ne 0 ] && echo $BASH_SOURCE build error && exit 1 
fi 

if [ "${arg/run}" != "$arg" ]; then
   $bin 
   [ $? -ne 0 ] && echo $BASH_SOURCE run error && exit 2
fi

if [ "${arg/pdb}" != "$arg" ]; then
   ${IPYTHON:-ipython} --pdb -i $script
   [ $? -ne 0 ] && echo $BASH_SOURCE pdb error && exit 3
fi

if [ "${arg/ana}" != "$arg" ]; then
   ${PYTHON:-python} $script
   [ $? -ne 0 ] && echo $BASH_SOURCE ana error && exit 4
fi

exit 0 


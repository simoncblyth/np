#!/bin/bash 
usage(){ cat << EOU

~/np/tests/NPInterp2DTest.sh


P[blyth@localhost ~]$ ~/np/tests/NPInterp2DTest.sh
NPInterp2DTest: ../NP.hh:3880: T NP::interp2D(T, T, NP::INT) const [with T = double; NP::INT = long int]: Assertion i < ni && i > -1 failed.
/home/blyth/np/tests/NPInterp2DTest.sh: line 29: 166566 Aborted                 (core dumped) $bin
/home/blyth/np/tests/NPInterp2DTest.sh run error


EOU
}
cd $(dirname $(realpath $BASH_SOURCE))
source dbg__.sh

defarg=build_run_ana
arg=${1:-$defarg}

name=NPInterp2DTest 
export FOLD=/tmp/$name

mkdir -p $FOLD
bin=$FOLD/$name
script=$name.py 


if [ "${arg/build}" != "$arg" ]; then 
    gcc $name.cc -std=c++11 -g -I.. -lstdc++ -lm -o $bin
    [ $? -ne 0 ] && echo $BASH_SOURCE build error && exit 1 
fi 

if [ "${arg/run}" != "$arg" ]; then 
    $bin
    [ $? -ne 0 ] && echo $BASH_SOURCE run error && exit 2
fi 

if [ "${arg/dbg}" != "$arg" ]; then 
    dbg__ $bin
    [ $? -ne 0 ] && echo $BASH_SOURCE dbg error && exit 2
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


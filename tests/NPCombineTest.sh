#!/bin/bash 

usage(){ cat << EOU

~/np/tests/NPCombineTest.sh
~/np/tests/NPCombineTest.sh dbg


P[blyth@localhost LS]$ ~/np/tests/NPCombineTest.sh 
 na 3 ndom 1000 dom NP  dtype <f4(1000, ) size 1000 uifc f ebyte 4 shape.size 1 data.size 4000 meta.size 0 names.size 0 c NP  dtype <f4(3, 19, 2, ) size 114 uifc f ebyte 4 shape.size 3 data.size 456 meta.size 0 names.size 0 r NP  dtype <f4(3, 1000, ) size 3000 uifc f ebyte 4 shape.size 2 data.size 12000 meta.size 0 names.size 0
NPCombineTest::scan NP  dtype <f4(18, 2, ) size 36 uifc f ebyte 4 shape.size 2 data.size 144 meta.size 0 names.size 0
NPCombineTest: NPCombineTest.cc:106: void NPCombineTest<T>::scan() [with T = float]: Assertion y0 == y1 failed.
/home/blyth/np/tests/NPCombineTest.sh: line 29: 216465 Aborted                 (core dumped) $bin
/home/blyth/np/tests/NPCombineTest.sh run error
P[blyth@localhost LS]$ 


EOU
}
cd $(dirname $(realpath $BASH_SOURCE))
source dbg__.sh

source $HOME/.opticks/GEOM/GEOM.sh
name=NPCombineTest 
export FOLD=/tmp/$name
mkdir -p $FOLD

bin=$FOLD/$name
script=$name.py 

defarg=build_run_ana
arg=${1:-$defarg}

if [ "${arg/build}" != "$arg" ]; then 
   gcc $name.cc -std=c++17  -g -I.. -Wall -lstdc++ -o $bin
   [ $? -ne 0 ] && echo $BASH_SOURCE compile error && exit 1 
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


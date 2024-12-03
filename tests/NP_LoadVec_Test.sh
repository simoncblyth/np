#!/bin/bash
usage(){ cat << EOU
NP_LoadVec_Test.sh
====================

~/np/tests/NP_LoadVec_Test.sh

This is a brief look at loading ".root" files
without depending on ROOT.  

Concluded that its just not worth the effort for the PMT data. 
Can just grab the uncompressed contiguous array of PMT data 
from PMTSimParamSvc during geometry translation instead
and persist that as .npy with the SSim

EOU
}

cd $(dirname $(realpath $BASH_SOURCE))
name=NP_LoadVec_Test

export FOLD=/tmp/$name
mkdir -p $FOLD

defarg=build_run
arg=${1:-$defarg}

bin=$FOLD/$name


if [ "${arg/build}" != "$arg" ]; then
    gcc $name.cc -std=c++11 -lstdc++ -Wall -I.. -o $bin 
    [ $? -ne 0 ] && echo $BASH_SOURCE build error  && exit 1
fi 

if [ "${arg/run}" != "$arg" ]; then
    $bin
    [ $? -ne 0 ] && echo $BASH_SOURCE run error && exit 2
fi 

exit 0



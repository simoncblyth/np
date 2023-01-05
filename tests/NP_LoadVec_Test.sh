#!/bin/bash -l 
usage(){ cat << EOU
NP_LoadVec_Test.sh
====================

This is a brief look at loading ".root" files
without depending on ROOT.  

Concluded that its just not worth the effort for the PMT data. 
Can just grab the uncompressed contiguous array of PMT data 
from PMTSimParamSvc during geometry translation instead
and persist that as .npy with the SSim

EOU
}

name=NP_LoadVec_Test

defarg=build_run
arg=${1:-$defarg}

if [ "${arg/build}" != "$arg" ]; then

    gcc $name.cc -std=c++11 -lstdc++  \
        -I.. \
        -o /tmp/$name 

    [ $? -ne 0 ] && echo $BASH_SOURCE build error  && exit 1
fi 

if [ "${arg/run}" != "$arg" ]; then
    /tmp/$name
    [ $? -ne 0 ] && echo $BASH_SOURCE run error && exit 2
fi 

exit 0



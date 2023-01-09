#!/bin/bash -l 
usage(){ cat << EOU
NP_RootCheck_Test.sh
======================

Very unusually this depends on ROOT. 

This can serve as the baseline to compare with the 
non-ROOT dependent approach using the PMTSimParamSvc 
pd_vector converted into .npy within the SSim NPFold.

EOU
}


name=NP_RootCheck_Test

root-

LIBS=$($(root-prefix)/bin/root-config --noauxlibs --libs)


defarg=build_run
arg=${1:-$defarg}

export FOLD=/tmp/$name
mkdir -p $FOLD


if [ "${arg/build}" != "$arg" ]; then 
    gcc $name.cc -std=c++14 -lstdc++ \
           -I$HOME/opticks/sysrap \
           -I$(root-prefix)/include \
           $LIBS \
           -o $FOLD/$name 
    [ $? -ne 0 ] && echo $BASH_SOURCE build error && exit 1 
fi


if [ "${arg/run}" != "$arg" ]; then 

    DYLD_LIBRARY_PATH=$($(root-prefix)/bin/root-config --libdir)  $FOLD/$name 
    [ $? -ne 0 ] && echo $BASH_SOURCE run error && exit 2
fi


if [ "${arg/lpmt}" != "$arg" ]; then
    export FOLD=$JUNOTOP/data/Simulation/SimSvc/PMTSimParamSvc/PMTParam_CD_LPMT_root
    ${IPYTHON:-ipython} --pdb -i $name.py 
    [ $? -ne 0 ] && echo $BASH_SOURCE lpmt error && exit 3
fi

if [ "${arg/spmt}" != "$arg" ]; then
    export FOLD=$JUNOTOP/data/Simulation/SimSvc/PMTSimParamSvc/PMTParam_CD_SPMT_root
    ${IPYTHON:-ipython} --pdb -i $name.py 
    [ $? -ne 0 ] && echo $BASH_SOURCE spmt error && exit 3
fi







exit 0 






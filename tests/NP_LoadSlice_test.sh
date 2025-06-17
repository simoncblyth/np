#!/bin/bash
usage(){ cat << EOU

~/np/tests/NP_LoadSlice_test.sh

EOU
}

source ~/.opticks/GEOM/GEOM.sh
source ~/.opticks/GEOM/EVT.sh


cd $(dirname $(realpath $BASH_SOURCE))

name=NP_LoadSlice_test
script=$name.py

tmp=/tmp/$USER/np
export TMP=${TMP:-$tmp}
export FOLD=$TMP/$name
mkdir -p $FOLD

bin=$FOLD/$name

defarg="info_build_run_pdb"
arg=${1:-$defarg}

export PYTHONPATH=$HOME

#test=LoadSlice
test=LoadSliceLarge

export TEST=${TEST:-$test}


vv="BASH_SOURCE PWD name tmp TMP FOLD bin script defarg arg TEST"

if [ "${arg/info}" != "$arg" ]; then
   for v in $vv ; do printf "%20s : %s\n" "$v" "${!v}" ; done
fi

if [ "${arg/build}" != "$arg" ]; then
   gcc $name.cc -I.. -std=c++17 -lstdc++ -o $bin
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


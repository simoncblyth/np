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
#test=LoadSliceLarge
test=LoadSliceWhere

export TEST=${TEST:-$test}

opt=""
[ "$VERBOSE" == "1" ] && opt=-DWITH_VERBOSE

pp="BASH_SOURCE EVT EVT_CHECK AFOLD AFOLD_RECORD_SLICE VERBOSE opt"
if [ "$TEST" == "LoadSliceWhere" ]; then
    for p in $pp ; do printf "%20s : %s\n" "$p" "${!p}" ; done

else
    afold_record_slice=[::100]
    export AFOLD_RECORD_SLICE=${AFOLD_RECORD_SLICE:-$afold_record_slice}
fi

vv="BASH_SOURCE PWD name tmp TMP FOLD bin script defarg arg TEST AFOLD_RECORD_SLICE VERBOSE opt"

if [ "${arg/info}" != "$arg" ]; then
   for v in $vv ; do printf "%20s : %s\n" "$v" "${!v}" ; done
fi

if [ "${arg/build}" != "$arg" ]; then
   gcc $name.cc -I.. -std=c++17 -lstdc++ $opt -o $bin
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


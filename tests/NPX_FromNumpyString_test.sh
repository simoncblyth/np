#!/usr/bin/env bash
usage(){ cat << EOU

~/np/tests/NPX_FromNumpyString_test.sh

EOU
}

cd $(dirname $(realpath $BASH_SOURCE))

name=NPX_FromNumpyString_test
script=$name.py

tmp=/tmp/$USER/np
export TMP=${TMP:-$tmp}
export FOLD=$TMP/$name
mkdir -p $FOLD

bin=$FOLD/$name

test="FromNumpyString"
export TEST=${TEST:-$test}

defarg="info_build_run_pdb"
arg=${1:-$defarg}

export PYTHONPATH=$HOME  # assuming $HOME/np is the repo

vv="BASH_SOURCE defarg arg name script TMP FOLD bin test TEST PWD PYTHONPATH"

if [ "${arg/info}" != "$arg" ]; then
    for v in $vv ; do printf "%20s : %s\n" "$v" "${!v}" ; done
fi

if [ "${arg/build}" != "$arg" ]; then
   gcc $name.cc -std=c++17 -g  -lstdc++ -I.. -o $bin
   [ $? -ne 0 ] && echo $BASH_SOURCE build error && exit 1
fi

if [ "${arg/run}" != "$arg" ]; then
   $bin
   [ $? -ne 0 ] && echo $BASH_SOURCE run error && exit 2
fi

if [ "${arg/dbg}" != "$arg" ]; then
   gdb -ex r --args $bin
   [ $? -ne 0 ] && echo $BASH_SOURCE dbg error && exit 2
fi

if [ "${arg/ana}" != "$arg" ]; then
   ${PYTHON:-python} $script
   [ $? -ne 0 ] && echo $BASH_SOURCE ana error && exit 3
fi

if [ "${arg/pdb}" != "$arg" ]; then
   ${IPYTHON:-ipython} --pdb -i $script
   [ $? -ne 0 ] && echo $BASH_SOURCE pdb error && exit 4
fi

exit 0


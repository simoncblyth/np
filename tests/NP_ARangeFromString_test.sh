#!/bin/bash

usage(){ cat << EOU

~/np/tests/NP_ARangeFromString_test.sh

EOU
}

cd $(dirname $(realpath $BASH_SOURCE))
export PYTHONPATH=../..

name=NP_ARangeFromString_test

export FOLD=/tmp/$name
bin=$FOLD/$name
script=$name.py
mkdir -p $FOLD

defarg="info_build_run_ana"
#defarg="info_build_run_pdb"

arg=${1:-$defarg}

vv="BASH_SOURCE BASH_VERSION name FOLD bin script defarg arg"

if [ "${arg/info}" != "$arg" ]; then
   for v in $vv ; do printf "%20s : %s\n" "$v" "${!v}" ; done
fi

if [ "${arg/build}" != "$arg" ]; then
   gcc $name.cc -std=c++17 -Wall -g -lstdc++ -I.. -o $bin
   [ $? -ne 0 ] && echo $BASH_SOURCE : build error && exit 1
fi

if [ "${arg/run}" != "$arg" ]; then
   $bin
   [ $? -ne 0 ] && echo $BASH_SOURCE : run error && exit 2
fi

if [ "${arg/pdb}" != "$arg" ]; then
   ${IPYTHON:-ipython} --pdb -i $script
   [ $? -ne 0 ] && echo $BASH_SOURCE : pdb error && exit 3
fi

if [ "${arg/ana}" != "$arg" ]; then
   ${PYTHON:-python} $script
   [ $? -ne 0 ] && echo $BASH_SOURCE : ana error && exit 4
fi

exit 0



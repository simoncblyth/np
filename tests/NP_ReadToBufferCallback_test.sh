#!/usr/bin/env bash
usage(){ cat << EOU

~/np/tests/NP_ReadToBufferCallback_test.sh

EOU
}

cd $(dirname $(realpath $BASH_SOURCE))

name=NP_ReadToBufferCallback_test
script=$name.py

defarg="info_build_run"
arg=${1:-$defarg}

tmp=/tmp/$USER/np
TMP=${TMP:-$tmp}
export FOLD=$TMP/$name
mkdir -p $FOLD
bin=$FOLD/$name

vv="BASH_SOURCE name PWD defarg arg FOLD bin"

if [ "${arg/info}" != "$arg" ]; then
   for v in $vv ; do printf "%30s : %s\n" "$v" "${!v}" ; done
fi

if [ "${arg/build}" != "$arg" ]; then
   gcc $name.cc \
      -std=c++17 -lstdc++ -g \
      -I.. \
      -o $bin
   [ $? -ne 0 ] && echo $BASH_SOURCE - build error && exit 1
fi

if [ "${arg/run}" != "$arg" ]; then
   $bin
   [ $? -ne 0 ] && echo $BASH_SOURCE - run error && exit 2
fi

if [ "${arg/dbg}" != "$arg" ]; then
   source dbg__.sh
   dbg__ $bin
   [ $? -ne 0 ] && echo $BASH_SOURCE - dbg error && exit 3
fi

if [ "${arg/pdb}" != "$arg" ]; then
   ${IPYTHON:-ipython} -i --pdb  $script
   [ $? -ne 0 ] && echo $BASH_SOURCE - pdb error && exit 4
fi

if [ "${arg/ls}" != "$arg" ]; then
   echo ls -alst $FOLD
   ls -alst $FOLD
fi

if [ "${arg/xxd}" != "$arg" ]; then
   aa="a0 a1 a2"
   for a in $aa ; do
       echo xxd -l 512 $FOLD/$a.npy
       xxd -l 512 $FOLD/$a.npy

       echo diff -b $FOLD/a0.npy $FOLD/$a.npy
       diff -b $FOLD/a0.npy $FOLD/$a.npy
   done
fi



exit 0



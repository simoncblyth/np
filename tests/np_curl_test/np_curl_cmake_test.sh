#!/bin/bash

usage(){ cat << EOU

~/np/tests/np_curl_test/np_curl_cmake_test.sh

EOU
}

name=np_curl_cmake_test

cd $(dirname $(realpath $BASH_SOURCE))
SDIR=$PWD

tmp=/tmp/$USER/np
TMP=${TMP:-$tmp}

FOLD=$TMP/$name
bdir=$FOLD/build
bin=$FOLD/bin/np_curl_test

vv="BASH_SOURCE name SDIR PWD tmp TMP FOLD bdir bin"
for v in $vv ; do printf "%30s : %s\n" "$v" "${!v}" ; done


rm -rf $bdir
mkdir -p $bdir
pushd $bdir


export CMAKE_PREFIX_PATH=/home/blyth/miniconda3/envs/ok

cmake $SDIR \
   -DCMAKE_BUILD_TYPE=Debug \
   -DCMAKE_INSTALL_PREFIX=$FOLD

# "oje" environment does not have libcurl, at least from within oje the old system curl 7.76.1 is picked up
#cmake $SDIR -DCMAKE_BUILD_TYPE=Debug

cmake --build .
cmake --install .

popd


$bin
[ $? -ne 0 ] && echo $BASH_SOURCE run error && exit 1


exit 0



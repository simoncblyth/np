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

vv="BASH_SOURCE name SDIR PWD tmp TMP FOLD bdir"
for v in $vv ; do printf "%30s : %s\n" "$v" "${!v}" ; done


rm -rf $bdir
mkdir -p $bdir
pushd $bdir

# THIS WORKS
#cmake $SDIR \
#  -DCMAKE_PREFIX_PATH=/home/blyth/miniconda3/envs/ok \
#  -DCMAKE_BUILD_TYPE=Debug

# THIS WORKS TOO
#CMAKE_PREFIX_PATH=/home/blyth/miniconda3/envs/ok cmake $SDIR -DCMAKE_BUILD_TYPE=Debug

# THIS WORKS TOO
export CMAKE_PREFIX_PATH=/home/blyth/miniconda3/envs/ok
cmake $SDIR -DCMAKE_BUILD_TYPE=Debug

# "oje" environment does not have libcurl, at least from within oje the old system curl 7.76.1 is picked up
#cmake $SDIR -DCMAKE_BUILD_TYPE=Debug

cmake --build .

popd



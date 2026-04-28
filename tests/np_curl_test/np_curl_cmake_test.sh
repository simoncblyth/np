#!/bin/bash

usage(){ cat << EOU

~/np/tests/np_curl_test/np_curl_cmake_test.sh

EOU
}

name=np_curl_cmake_test

cd $(dirname $(realpath $BASH_SOURCE))
SDIR=$PWD

export FOLD=/data1/blyth/tmp/SEvt__createInputGenstep_configuredTest

tmp=/tmp/$USER/np
TMP=${TMP:-$tmp}
PREFIX=$TMP/$name
bdir=$PREFIX/build
bin=$PREFIX/bin/np_curl_test

vv="BASH_SOURCE name SDIR PWD tmp TMP PREFIX FOLD bdir bin"

defarg="info_build_run"
arg=${1:-$defarg}


if [[ "$arg" =~ env|info|chk|build|run|dbg|ana ]]; then
   source environment.sh
fi

if [[ "$arg" =~ info ]]; then
   for v in $vv ; do printf "%30s : %s\n" "$v" "${!v}" ; done
fi

if [[ "$arg" =~ chk ]]; then

    checkfor="8.12.1"
    which curl-config
    which curl

    curl-config --libs
    curl-config --cflags
    curl-config --vernum
    curl-config --version

    if curl-config --checkfor "$checkfor" >/dev/null 2>&1; then
        echo "$BASH_SOURCE - OK - $(curl-config --version) meets requirements."
    else
        echo "$BASH_SOURCE - FAIL - Need curl-config with checkfor and version of at least $checkfor, but have $(curl-config --version)."
        echo "$BASH_SOURCE - TRY ACTIVATING YOUR CONDA ENV TO USE ITS LIBCURL eg with \"lo\" "
        exit 1
    fi
fi


if [[ "$arg" =~ clean ]]; then
   rm -rf $bdir
   mkdir -p $bdir
fi

if [[ "$arg" =~ build ]]; then
   pushd $bdir
       cmake $SDIR \
       -DCMAKE_BUILD_TYPE=Debug \
       -DCMAKE_INSTALL_PREFIX=$PREFIX

        cmake --build .
        cmake --install .
   popd
fi

if [[ "$arg" =~ run ]]; then
   $bin
   [ $? -ne 0 ] && echo $BASH_SOURCE run error && exit 1
fi

if [[ "$arg" =~ dbg ]]; then
   gdb -ex r --args $bin
   [ $? -ne 0 ] && echo $BASH_SOURCE dbg error && exit 1
fi

exit 0



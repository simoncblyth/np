#!/usr/bin/env bash

usage(){ cat << EOU
np_curl_test.sh
================

Started from the  ~/env/tools/curl_check investigations.
This test was used to develop the integration with NP.hh
adding flexible array shape handling and making into a realistic API::

Build and start the endpoint "server"::

   ~/opticks/CSGOptiX/tests/CSGOptiXService_FastAPI_test/CSGOptiXService_FastAPI_test.sh
   ~/env/tools/fastapi_check/dev.sh  ## NOT THIS OLD ONE

Usage::

   ~/np/tests/np_curl_test/np_curl_test.sh
   LEVEL=1 ~/np/tests/np_curl_test/np_curl_test.sh                ## more verbosity
   MULTIPART=0 LEVEL=1 ~/np/tests/np_curl_test/np_curl_test.sh    ## switch off multipart which is enabled by default


   ~/np/tests/np_curl_test/np_curl_test.sh cli



EOU
}

cd $(dirname $(realpath $BASH_SOURCE))

defarg="info_build_check_run"
arg=${1:-$defarg}

name=np_curl_test
script=$name.py

#name=curl_mime_test

bin=/tmp/$USER/np/$name
mkdir -p $(dirname $bin)

#level=1
level=0
export NP_CURL_API_LEVEL=${LEVEL:-$level}

endpoint=http://127.0.0.1:8000/simulate

export NP_CURL_API_URL=$endpoint

export FOLD=/data1/blyth/tmp/SEvt__createInputGenstep_configuredTest


which curl-config

opt="-DWITH_MULTIPART"
OPT=$opt
[ "$MULTIPART" == "0" ] && OPT=""


if [ "${arg/info}" != "$arg" ]; then
   vv="BASH_SOURCE PWD name bin opt OPT"
   for v in $vv ; do printf "%30s : %s\n" "$v" "${!v}" ; done

   env | grep NP_CURL

   which curl-config
   curl-config --libs
   curl-config --cflags
   curl-config --vernum
   curl-config --version

   checkfor=8.12.1
   curl-config --checkfor $checkfor
   [ $? -ne 0 ] && echo $BASH_SOURCE - constrain libcurl checkfor $checkfor - ACTIVATE CONDA ENV TO USE ITS LIBCURL && exit 1

fi


if [ "${arg/build}" != "$arg" ]; then
    gcc $name.cc -o $bin \
    -Wall -std=c++17 -lstdc++ -g $OPT \
    -I../.. \
    $(curl-config --cflags) \
    $(curl-config --libs)
    [ $? -ne 0 ] && echo $BASH_SOURCE - build error && exit 1
fi


if [ "${arg/check}" != "$arg" ]; then
   test -f $FOLD/gs.npy
   [ $? -ne 0 ] && echo $BASH_SOURCE - check $FOLD/gs.npy FAILED - CREATE IT WITH THAT SYSRAP TEST - && exit 5
fi


if [ "${arg/run}" != "$arg" ]; then
   $bin
   [ $? -ne 0 ] && echo $BASH_SOURCE - run error && exit 2
fi

if [ "${arg/dbg}" != "$arg" ]; then

   case $(uname) in
      Darwin) lldb $bin ;;
      Linux)  gdb $bin ;;
   esac
   [ $? -ne 0 ] && echo $BASH_SOURCE - dbg error && exit 3
fi

if [ "${arg/ls}" != "$arg" ]; then
    echo ls -alst $FOLD
    ls -alst $FOLD

    md5sum $FOLD/*.npy


fi

if [ "${arg/xxd}" != "$arg" ]; then
    tail -c 300 $FOLD/ht000.npy | xxd
fi


if [ "${arg/cli}" != "$arg" ]; then

    index=100
    htname=$(printf  "ht%0.3d_cli.npy" $index)

    curl \
    --disable \
    -s \
    -v \
    --fail-with-body \
    -H "Content-Type: multipart/form-data" \
    -H "x-opticks-token: secret" \
    -H "x-opticks-level: 1" \
    -H "x-opticks-index: $index" \
    -F "upload=@$FOLD/gs.npy" \
    --output $FOLD/$htname \
    "$NP_CURL_API_URL"

    echo ls -alst $FOLD/$htname
    ls -alst $FOLD/$htname

    [ $? -ne 0 ] && echo $BASH_SOURCE - non zero rc from curl cli && exit 4
fi

if [ "${arg/pdb}" != "$arg" ]; then
   ${IPYTHON:-ipython} -i --pdb $script
fi


exit 0



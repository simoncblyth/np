#!/usr/bin/env bash

usage(){ cat << EOU
np_curl_test.sh
================

Started from the  ~/env/tools/curl_check investigations.
This test was used to develop the integration with NP.hh
adding flexible array shape handling and making into a realistic API::


Build and start the endpoint "server"::

   ~/env/tools/fastapi_check/dev.sh
   ~/opticks/CSGOptiX/tests/CSGOptiXService_FastAPI_test/CSGOptiXService_FastAPI_test.sh


Usage::

   ~/np/tests/np_curl_test/np_curl_test.sh
   LEVEL=1 ~/np/tests/np_curl_test/np_curl_test.sh                ## more verbosity
   MULTIPART=0 LEVEL=1 ~/np/tests/np_curl_test/np_curl_test.sh    ## switch off multipart which is enabled by default


EOU
}

cd $(dirname $(realpath $BASH_SOURCE))

defarg="info_build_check_run"
arg=${1:-$defarg}

name=np_curl_test
#name=curl_mime_test

bin=/tmp/$USER/np/$name
mkdir -p $(dirname $bin)

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
    ls -alst $FOLD
fi

if [ "${arg/cli}" != "$arg" ]; then

   ${IPYTHON:-ipython} -c "import os, numpy as np ; fold = os.path.expandvars(\"$FOLD\") ; gs = np.load(os.path.join(fold,\"gs.npy\")) ; open(os.path.join(fold,\"gs\"),'wb').write(gs.tobytes())"
   # TODO: FIND BETTER WAY : SUCH AS SKIPPING THE HEADER WHEN READING : SO DONT HAVE TO CHOP HEADER OFF

    curl \
    --disable \
    -s \
    -v \
    --fail-with-body \
    -H "Content-Type: multipart/form-data" \
    -H "x-opticks-token: secret" \
    -H "x-opticks-dtype: float32" \
    -H "x-opticks-shape: (1,6,4)" \
    -H "x-opticks-level: 1" \
    -H "x-opticks-index: 0" \
    -F "upload=@$FOLD/gs" \
    --output $FOLD/ht \
    "$NP_CURL_API_URL"

    ## THE gs and ht FILES DO NOT HAVE .npy ENDING
    ## AS THE HEADER IS NOT INCLUDED IN THE BODY : ITS IN THE HTTP HEADER
    ## TODO: PROVIDE HEADER OPTION TO INCLUDE THE HEADER IN THE BODY

    [ $? -ne 0 ] && echo $BASH_SOURCE - non zero rc from curl cli && exit 4
fi



exit 0



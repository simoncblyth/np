#!/usr/bin/env bash

usage(){ cat << EOU
np_curl_test.sh
================

Started from the  ~/env/tools/curl_check investigations.
This test was used to develop the integration with NP.hh
adding flexible array shape handling and making into a realistic API::

Build and start the endpoint "server"::

   lo  ## env setup for opticks + miniconda-python?
   ~/opticks/CSGOptiX/tests/CSGOptiXService_FastAPI_test/CSGOptiXService_FastAPI_test.sh
   ~/env/tools/fastapi_check/dev.sh  ## NOT THIS OLD ONE

Usage::

   lo  ## need newer curl-config than default
   ~/np/tests/np_curl_test/np_curl_test.sh
   LEVEL=1 ~/np/tests/np_curl_test/np_curl_test.sh                ## more verbosity
   MULTIPART=0 LEVEL=1 ~/np/tests/np_curl_test/np_curl_test.sh    ## switch off multipart which is enabled by default


   ~/np/tests/np_curl_test/np_curl_test.sh cli



info
   dump variables

chk
   checks the version of curl-config plucked from PATH meets the requirements

gcc
   build the binary linking against libcurl

igs
   check the input genstep file exists

run
   invoke binary np_curl_test which repeats NP_CURL::TransformRemote
   with the same gensteps multiple times

dbg
   run under debugger

ls
   list hit and genstep files under FOLD $FOLD

xxd
   hexdump the tail of a hit file

cli
   invoke the server with curl from commandline by uploading gensteps and downloading hits



EOU
}

cd $(dirname $(realpath $BASH_SOURCE))

defarg="info_chk_gcc_igs_run_cli_ana"
arg=${1:-$defarg}

name=np_curl_test
script=$name.py

#name=curl_mime_test

bin=/tmp/$USER/np/$name
mkdir -p $(dirname $bin)

#level=1
level=0
endpoint=http://127.0.0.1:8000/simulate

export NP_CURL_API_LEVEL=${LEVEL:-$level}
export NP_CURL_API_URL=$endpoint

tmp=/tmp/$USER/opticks
export TMP=${TMP:-$tmp}
export FOLD=$TMP/SEvt__createInputGenstep_configuredTest

opt="-DWITH_MULTIPART"
OPT=$opt
[ "$MULTIPART" == "0" ] && OPT=""

if [ "${arg/info}" != "$arg" ]; then
   vv="BASH_SOURCE PWD name bin script opt OPT NP_CURL_API_LEVEL NP_CURL_API_URL tmp TMP FOLD"
   for v in $vv ; do printf "%30s : %s\n" "$v" "${!v}" ; done
fi


if [ "${arg/chk}" != "$arg" ]; then

    checkfor="8.12.1"
    which curl-config

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

if [ "${arg/gcc}" != "$arg" ]; then
    gcc $name.cc \
         -o $bin \
         -DWITH_CURL \
         -Wall -std=c++17 -lstdc++ -g $OPT \
         -I../.. \
         $(curl-config --cflags) \
         $(curl-config --libs)
    [ $? -ne 0 ] && echo $BASH_SOURCE - gcc error && exit 1
fi


if [ "${arg/igs}" != "$arg" ]; then
   ls -alst $FOLD/gs.npy
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


cli-notes(){ cat << EON

--disable
    inhibits use of ~/.curlrc  (--disable-config in newer curl)

EON
}

if [ "${arg/cli}" != "$arg" ]; then

    index=0
    level=0
    token=secret
    htname=$(printf  "ht%0.3d_cli.npy" $index)

    curl \
        --disable \
        -s \
        -v \
        --fail-with-body \
        -H "x-opticks-token: $token" \
        -H "x-opticks-level: $level" \
        -H "x-opticks-index: $index" \
        -F "upload=@$FOLD/gs.npy" \
        --output $FOLD/$htname \
        "$NP_CURL_API_URL"

    [ $? -ne 0 ] && echo $BASH_SOURCE - non zero rc from curl cli && exit 4

    echo ls -alst $FOLD/$htname
    ls -alst $FOLD/$htname
fi

if [ "${arg/pdb}" != "$arg" ]; then
   ${IPYTHON:-ipython} -i --pdb $script
fi

if [ "${arg/ana}" != "$arg" ]; then
   ${PYTHON:-python} $script
fi

exit 0



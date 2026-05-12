#!/usr/bin/env bash

usage(){ cat << EOU
np_curl_test.sh
================

Started from the  ~/env/tools/curl_check investigations.
This test was used to develop the integration with NP.hh
adding flexible array shape handling and making into a realistic API::

Build and start the endpoint "server"::

   lo  ## opticks env setup
   lco ## miniconda "ok" python virtual env activation required for "fastapi" binary
   ~/opticks/CSGOptiX/tests/CSGOptiXService_FastAPI_test/CSGOptiXService_FastAPI_test.sh

Usage::

   ## following  addition of handling for older libcurl - the default system libcurl can  be used

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

k6_load
   * if get hang check vip-init-all-proxy which sets ALL_PROXY and the socks proxy
   * initially must create small/medium/large.npy input gensteps with::

       ~/o/sysrap/tests/SEvt__createInputGenstep_configuredTest_SML.sh



EOU
}

cd $(dirname $(realpath $BASH_SOURCE))

defarg="env_info_chk_gcc_igs_run_cli_ana"
arg=${1:-$defarg}

name=np_curl_test
script=$name.py


tmp=/tmp/$USER/np
TMP=${TMP:-$tmp}

bin=$TMP/$name
mkdir -p $(dirname $bin)

#level=1
level=0
endpoint=http://127.0.0.1:8000/simulate

export NP_CURL_API_LEVEL=${LEVEL:-$level}
export NP_CURL_API_URL=$endpoint
export FOLD=/data1/blyth/tmp/SEvt__createInputGenstep_configuredTest

export K6FOLD=$TMP/k6
mkdir -p $K6FOLD


opt="-DWITH_MULTIPART"
OPT=$opt
[ "$MULTIPART" == "0" ] && OPT=""


if [[ "$arg" =~ env|chk|gcc|run|dbg|ana ]]; then
   source environment.sh
fi

if [ "${arg/info}" != "$arg" ]; then
   vv="BASH_SOURCE PWD name bin script opt OPT NP_CURL_API_LEVEL NP_CURL_API_URL tmp TMP FOLD K6FOLD"
   for v in $vv ; do printf "%30s : %s\n" "$v" "${!v}" ; done
fi


if [ "${arg/chk}" != "$arg" ]; then

    #checkfor="8.12.1"
    checkfor="7.76.1"
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
      Linux)  gdb -ex r --args $bin ;;
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

    index=99
    count=1000000
    level=0
    token=secret
    meta=via-curl-cli
    htname=$(printf  "ht%0.3d_cli.npy" $index)

    curl \
        --disable \
        -s \
        -v \
        --fail-with-body \
        -H "x-opticks-token: $token" \
        -H "x-opticks-level: $level" \
        -H "x-opticks-index: $index" \
        -H "x-opticks-count: $count" \
        -H "x-opticks-meta: $meta" \
        -F "upload=@$FOLD/gs.npy" \
        --output $FOLD/$htname \
        "$NP_CURL_API_URL"

    [ $? -ne 0 ] && echo $BASH_SOURCE - non zero rc from curl cli && exit 4

    echo ls -alst $FOLD/$htname
    ls -alst $FOLD/$htname
fi

if [[ "$arg" =~ k6_post ]]; then
   k6 run --vus 1 --iterations 10 k6_post.js
   [ $? -ne 0 ] && echo $BASH_SOURCE k6_post error && exit 1
fi

if [[ "$arg" =~ k6_load ]]; then
   #xtr=--verbose
   xtr=""
   vus=1
   iter=10
   XTR=${XTR:-$xtr}
   VUS=${VUS:-$vus}
   ITER=${ITER:-$iter}
   qq="xtr XTR vus VUS iter ITER"
   for q in $qq ; do printf "%30s : %s\n" "$q" "${!q}" ; done

   k6 run --vus $VUS --iterations $ITER $XTR k6_load.js
   [ $? -ne 0 ] && echo $BASH_SOURCE k6_load error && exit 1
fi


if [ "${arg/pdb}" != "$arg" ]; then
   PYTHONPATH=../../.. ${IPYTHON:-ipython} -i --pdb $script
fi

if [ "${arg/ana}" != "$arg" ]; then
   PYTHONPATH=../../.. ${PYTHON:-python} $script
fi

exit 0



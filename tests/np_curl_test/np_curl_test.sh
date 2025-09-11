#!/usr/bin/env bash

usage(){ cat << EOU
np_curl_test.sh
================

Started from the  ~/env/tools/curl_check investigations.
This test was used to develop the integration with NP.hh
adding flexible array shape handling and making into a realistic API::

Usage::

   ~/np/tests/np_curl_test/np_curl_test.sh
   LEVEL=1 ~/np/tests/np_curl_test/np_curl_test.sh                ## more verbosity
   MULTIPART=1 LEVEL=1 ~/np/tests/np_curl_test/np_curl_test.sh    ## test multipart upload


EOU
}

cd $(dirname $(realpath $BASH_SOURCE))

defarg="info_build_run"
arg=${1:-$defarg}

name=np_curl_test
#name=curl_mime_test

bin=/tmp/$USER/np/$name
mkdir -p $(dirname $bin)

level=0
export NP_CURL_API_LEVEL=${LEVEL:-$level}
which curl-config

opt=""
OPT=$opt
[ "$MULTIPART" == "1" ] && OPT=-DWITH_MULTIPART


if [ "${arg/info}" != "$arg" ]; then
   vv="BASH_SOURCE PWD name bin opt OPT"
   for v in $vv ; do printf "%30s : %s\n" "$v" "${!v}" ; done

   env | grep NP_CURL
fi



if [ "${arg/build}" != "$arg" ]; then
    gcc $name.cc -o $bin \
    -Wall -std=c++17 -lstdc++ -g $OPT \
    -I../.. \
    $(curl-config --cflags) \
    $(curl-config --libs)
    [ $? -ne 0 ] && echo $BASH_SOURCE - build error && exit 1
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

exit 0



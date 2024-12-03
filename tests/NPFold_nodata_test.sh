#!/bin/bash

usage(){ cat << EOU

~/np/tests/NPFold_nodata_test.sh

EOU
}

name=NPFold_nodata_test

FOLD=${TMP:-/tmp/$USER/opticks}/$name
bin=$FOLD/$name
mkdir -p $FOLD

cd $(dirname $(realpath $BASH_SOURCE))
SDIR=$(pwd)
source dbg__.sh 

#opt=-DWITH_VERBOSE
opt=


defarg="build_run_info"
arg=${1:-$defarg}

if [ "${arg/build}" != "$arg" ]; then
   gcc $name.cc -I.. -g -std=c++11 -lstdc++ $opt -o $bin
   [ $? -ne 0 ] && echo $BASH_SOURCE : build error && exit 1 
fi

##L
#cd /hpcfs/juno/junogpu/blyth/tmp/GEOM/J23_1_0_rc3_ok0/jok-tds/ALL0/p001
#cd /hpcfs/juno/junogpu/blyth/tmp/GEOM/J23_1_0_rc3_ok0/jok-tds/ALL0
#cd /hpcfs/juno/junogpu/blyth/tmp/GEOM/J23_1_0_rc3_ok0/jok-tds/ALL0/n010
##N
cd /data/blyth/opticks/GEOM/J23_1_0_rc3_ok0/jok-tds/ALL0
#cd /data/blyth/opticks/GEOM/J23_1_0_rc3_ok0/jok-tds/ALL0/p010


[ $? -ne 0 ] && echo $BASH_SOURCE : NO SUCH DIRECTORY && exit 0 

if [ "${arg/dbg}" != "$arg" ]; then 
    #dbg__ $bin  $PWD
    #[ $? -ne 0 ] && echo $BASH_SOURCE : dbg0 error && exit 2

    dbg__ $bin @$PWD
    [ $? -ne 0 ] && echo $BASH_SOURCE : dbg1 error && exit 3
fi

if [ "${arg/run}" != "$arg" ]; then 
    #$bin  $PWD
    #[ $? -ne 0 ] && echo $BASH_SOURCE : run0 error && exit 2

    $bin @$PWD
    [ $? -ne 0 ] && echo $BASH_SOURCE : run1 error && exit 3
fi


vars="0 BASH_SOURCE SDIR FOLD PWD bin"
if [ "${arg/info}" != "$arg" ]; then
    for var in $vars ; do printf "%25s : %s \n" "$var" "${!var}" ; done 
fi 

exit 0 


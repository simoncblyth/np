#!/bin/bash
usage(){ cat << EOU
NPFold_LoadNoData_test.sh
==========================

::

   ~/np/tests/NPFold_LoadNoData_test.sh

   TEST=substamp ~/np/tests/NPFold_LoadNoData_test.sh dbg


EOU
}
cd $(dirname $(realpath $BASH_SOURCE))
source dbg__.sh
SDIR=$(pwd)

name=NPFold_LoadNoData_test 
TMP=${TMP:-/tmp/$USER/opticks}
bin=$TMP/$name

#jdir=/data/blyth/opticks/GEOM/J23_1_0_rc3_ok0/jok-tds/ALL0
jdir=/data/blyth/opticks/GEOM/J_2024nov27/CSGOptiXSMTest/ALL1
JDIR=${JDIR:-$jdir}

test=substamp
TEST=${TEST:-$test}

defarg=info_build_run
arg=${1:-$defarg}


export NPFold__substamp_DUMP=1

vars="BASH_SOURCE name SDIR PWD bin defarg arg JDIR test TEST"

if [ "${arg/info}" != "$arg" ]; then
   for var in $vars ; do printf "%20s : %s\n" "$var" "${!var}" ; done 
fi 

if [ "${arg/build}" != "$arg" ]; then
   gcc $SDIR/$name.cc -g -std=c++11 -lstdc++ -I$SDIR/.. -o $bin 
   [ $? -ne 0 ] && echo $BASH_SOURCE : build error && exit 1
fi 

if [ "${arg/run}" != "$arg" ]; then
    cd $JDIR
    [ $? -ne 0 ] && echo $BASH_SOURCE : no such directory && exit 0
    $bin
    [ $? -ne 0 ] && echo $BASH_SOURCE : run error && exit 3
fi


if [ "${arg/dbg}" != "$arg" ]; then
    cd $JDIR
    [ $? -ne 0 ] && echo $BASH_SOURCE : no such directory && exit 0
    dbg__ $bin
    [ $? -ne 0 ] && echo $BASH_SOURCE : dbg error && exit 4
fi


exit 0 


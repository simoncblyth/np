#!/bin/bash -l 
usage(){ cat << EOU
NPFold_stamps_test.sh
=======================

::

   ~/np/tests/NPFold_stamps_test.sh ana


EOU
}


name=NPFold_stamps_test

export FOLD=${TMP:-/tmp/$USER/opticks}/$name
export MODE=2
bin=$FOLD/$name
mkdir -p $FOLD

cd $(dirname $BASH_SOURCE)
SDIR=$(pwd)

#opt=-DWITH_VERBOSE
opt=

vars="0 BASH_SOURCE SDIR FOLD PWD bin"
defarg="build_run_info_ana"
#defarg="run_info"
arg=${1:-$defarg}


if [ "${arg/info}" != "$arg" ]; then
    for var in $vars ; do printf "%25s : %s \n" "$var" "${!var}" ; done 
fi 

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

if [ "${arg/ana}" != "$arg" ]; then 
    ${IPYTHON:-ipython} --pdb -i $SDIR/$name.py 
    [ $? -ne 0 ] && echo $BASH_SOURCE : ana error && exit 3
fi

if [ "${arg/info}" != "$arg" ]; then
    for var in $vars ; do printf "%25s : %s \n" "$var" "${!var}" ; done 
fi 

exit 0 


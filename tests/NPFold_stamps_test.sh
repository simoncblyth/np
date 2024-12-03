#!/bin/bash
usage(){ cat << EOU
NPFold_stamps_test.sh
=======================

::

   ~/np/tests/NPFold_stamps_test.sh

   PICK=AB ~/np/tests/NPFold_stamps_test.sh ana
   PICK=A TLIM=-5,500  ~/np/tests/NPFold_stamps_test.sh ana


For SEvt "run" folder containing p001 n001 etc.., eg::

   /data/blyth/opticks/GEOM/J23_1_0_rc3_ok0/CSGOptiXSMTest/ALL/

The default output FOLD when no envvar is "../$ExecutableName" eg:: 

   /data/blyth/opticks/GEOM/J23_1_0_rc3_ok0/CSGOptiXSMTest/NPFold_stamps_test/

EOU
}

name=NPFold_stamps_test
cd $(dirname $(realpath $BASH_SOURCE))
SDIR=$(pwd)
source dbg__.sh 

export FOLD=${TMP:-/tmp/$USER/opticks}/$name  ## run + ana
export MODE=${MODE:-2}                        ## ana

bin=$FOLD/$name
mkdir -p $FOLD

script=$SDIR/$name.py

##L
#cd /hpcfs/juno/junogpu/blyth/tmp/GEOM/J23_1_0_rc3_ok0/jok-tds/ALL0/p001
#cd /hpcfs/juno/junogpu/blyth/tmp/GEOM/J23_1_0_rc3_ok0/jok-tds/ALL0
#cd /hpcfs/juno/junogpu/blyth/tmp/GEOM/J23_1_0_rc3_ok0/jok-tds/ALL0/n010
##N
cd /data/blyth/opticks/GEOM/J23_1_0_rc3_ok0/jok-tds/ALL0
#cd /data/blyth/opticks/GEOM/J23_1_0_rc3_ok0/jok-tds/ALL0/p010

#cd /data/blyth/opticks/GEOM/J23_1_0_rc3_ok0/CSGOptiXSMTest/ALL
[ $? -ne 0 ] && echo $BASH_SOURCE : NO SUCH DIRECTORY && exit 0 


defarg="build_run_info_ana"
#defarg="run_info"
arg=${1:-$defarg}

vars="0 BASH_SOURCE SDIR FOLD PWD bin"

if [ "${arg/info}" != "$arg" ]; then
    for var in $vars ; do printf "%25s : %s \n" "$var" "${!var}" ; done 
fi 

if [ "${arg/build}" != "$arg" ]; then
   #opt=-DWITH_VERBOSE
   opt=
   gcc $SDIR/$name.cc -I$SDIR/.. -g -std=c++11 -lstdc++ $opt -o $bin
   [ $? -ne 0 ] && echo $BASH_SOURCE : build error && exit 1 
fi

if [ "${arg/dbg}" != "$arg" ]; then 
    dbg__ $bin
    [ $? -ne 0 ] && echo $BASH_SOURCE : dbg1 error && exit 3
fi

if [ "${arg/run}" != "$arg" ]; then 
    $bin
    [ $? -ne 0 ] && echo $BASH_SOURCE : run1 error && exit 3
fi

if [ "${arg/runo}" != "$arg" ]; then 
    echo $BASH_SOURCE : runo exit && exit 3
fi


if [ "${arg/pdb}" != "$arg" ]; then 
    ${IPYTHON:-ipython} --pdb -i $script
    [ $? -ne 0 ] && echo $BASH_SOURCE : pdb error && exit 3
fi


if [ "${arg/ana}" != "$arg" ]; then 
    ${PYTHON:-python} $script
    [ $? -ne 0 ] && echo $BASH_SOURCE : ana error && exit 3
fi

if [ "${arg/info}" != "$arg" ]; then
    for var in $vars ; do printf "%25s : %s \n" "$var" "${!var}" ; done 
fi 

exit 0 


#!/bin/bash
usage(){ cat << EOU
NPFold_submeta_test.sh 
=======================

::

   ~/np/tests/NPFold_submeta_test.sh 


EOU
}


name=NPFold_submeta_test

export FOLD=${TMP:-/tmp/$USER/opticks}/$name
export MODE=2
bin=$FOLD/$name
mkdir -p $FOLD

SDIR=$(dirname $(realpath $BASH_SOURCE))
export PYTHONPATH=$SDIR/../..
script=$SDIR/$name.py

source $HOME/.opticks/GEOM/GEOM.sh 

job=N7
JOB=${JOB:-$job}

DIR=unknown 
case $JOB in  
  L1) DIR=/hpcfs/juno/junogpu/$USER/tmp/GEOM/$GEOM/jok-tds/ALL0 ;;
  N1) DIR=/data/$USER/opticks/GEOM/$GEOM/jok-tds/ALL0 ;;
  N2) DIR=/data/$USER/opticks/GEOM/$GEOM/G4CXTest/ALL0 ;;
  N3) DIR=/data/$USER/opticks/GEOM/$GEOM/CSGOptiXSMTest/ALL2 ;;
  N4) DIR=/data/$USER/opticks/GEOM/$GEOM/G4CXTest/ALL2 ;;
  N5) DIR=/data/$USER/opticks/GEOM/$GEOM/G4CXTest/ALL3 ;;
  N6) DIR=/data/$USER/opticks/GEOM/$GEOM/CSGOptiXSMTest/ALL3 ;;
  N7) DIR=/data/$USER/opticks/GEOM/$GEOM/CSGOptiXSMTest/ALL1 ;;
esac

cd $DIR
[ $? -ne 0 ] && echo $BASH_SOURCE : NO SUCH DIRECTORY $DIR JOB $JOB && exit 0 



#opt=-DWITH_VERBOSE
opt=

vars="0 BASH_SOURCE SDIR FOLD PWD bin"
defarg="info_build_run_ana"
arg=${1:-$defarg}


if [ "${arg/info}" != "$arg" ]; then
    for var in $vars ; do printf "%25s : %s \n" "$var" "${!var}" ; done 
fi 

if [ "${arg/build}" != "$arg" ]; then
   gcc $SDIR/$name.cc -I$SDIR/.. -g -Wall -std=c++11 -lstdc++ $opt -o $bin
   [ $? -ne 0 ] && echo $BASH_SOURCE : build error && exit 1 
fi

if [ "${arg/dbg}" != "$arg" ]; then 
    dbg__ $bin $PWD
    [ $? -ne 0 ] && echo $BASH_SOURCE : dbg1 error && exit 3
fi

if [ "${arg/run}" != "$arg" ]; then 
    $bin $PWD
    [ $? -ne 0 ] && echo $BASH_SOURCE : run1 error && exit 3
fi

if [ "${arg/noana}" != "$arg" ]; then 
    exit 0 
fi 

if [ "${arg/pdb}" != "$arg" ]; then 
    ${IPYTHON:-ipython} --pdb -i $script
    [ $? -ne 0 ] && echo $BASH_SOURCE : pdb error && exit 3
fi

if [ "${arg/ana}" != "$arg" ]; then 
    ${PYTHON:-python} $script
    [ $? -ne 0 ] && echo $BASH_SOURCE : ana error && exit 4
fi


exit 0 


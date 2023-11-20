#!/bin/bash -l 
usage(){ cat << EOU
NPFold_profile_test.sh 
=======================

::

   ~/np/tests/NPFold_profile_test.sh info

   PICK=CF TLIM=1290000,1350000 ~/np/tests/NPFold_profile_test.sh ana

   PICK=CF PLOT=PWE ~/np/tests/NPFold_profile_test.sh ana
   PICK=CF PLOT=PWE ~/np/tests/NPFold_profile_test.sh mpcap
   PICK=CF PLOT=PWE ~/np/tests/NPFold_profile_test.sh mppub

   MODE=0 ~/np/tests/NPFold_profile_test.sh ana   ## non-graphical remote node


EOU
}


name=NPFold_profile_test

export FOLD=${TMP:-/tmp/$USER/opticks}/$name
export MODE=${MODE:-2}
bin=${FOLD}.build/$name
mkdir -p ${FOLD}.build
mkdir -p $FOLD 

SDIR=$(cd $(dirname $BASH_SOURCE) && pwd)


##L
#cd /hpcfs/juno/junogpu/blyth/tmp/GEOM/J23_1_0_rc3_ok0/jok-tds/ALL0/p001
#cd /hpcfs/juno/junogpu/blyth/tmp/GEOM/J23_1_0_rc3_ok0/jok-tds/ALL0
#cd /hpcfs/juno/junogpu/blyth/tmp/GEOM/J23_1_0_rc3_ok0/jok-tds/ALL0/n010
##N
cd /data/blyth/opticks/GEOM/J23_1_0_rc3_ok0/jok-tds/ALL0
#cd /data/blyth/opticks/GEOM/J23_1_0_rc3_ok0/jok-tds/ALL0/p010
[ $? -ne 0 ] && echo $BASH_SOURCE : NO SUCH DIRECTORY && exit 0 

#opt=-DWITH_VERBOSE
opt=

vars="0 BASH_SOURCE SDIR FOLD PWD bin"
defarg="info_build_run_ana"
arg=${1:-$defarg}


if [ "${arg/info}" != "$arg" ]; then
    for var in $vars ; do printf "%25s : %s \n" "$var" "${!var}" ; done 
fi 

if [ "${arg/build}" != "$arg" ]; then
   gcc $SDIR/$name.cc -I$SDIR/.. -g -std=c++11 -lstdc++ $opt -o $bin
   [ $? -ne 0 ] && echo $BASH_SOURCE : build error && exit 1 
fi

if [ "${arg/dbg}" != "$arg" ]; then 
    dbg__ $bin @$PWD
    [ $? -ne 0 ] && echo $BASH_SOURCE : dbg1 error && exit 3
fi

if [ "${arg/run}" != "$arg" ]; then 
    $bin @$PWD
    [ $? -ne 0 ] && echo $BASH_SOURCE : run1 error && exit 3
fi

if [ "${arg/grab}" != "$arg" ]; then 
    ~/opticks/bin/rsync.sh $FOLD
    [ $? -ne 0 ] && echo $BASH_SOURCE : grab error && exit 4
fi

if [ "${arg/ana}" != "$arg" ]; then 
    ${IPYTHON:-ipython} --pdb -i $SDIR/$name.py 
    [ $? -ne 0 ] && echo $BASH_SOURCE : ana error && exit 3
fi

if [ "$arg" == "pvcap" -o "$arg" == "pvpub" -o "$arg" == "mpcap" -o "$arg" == "mppub" ]; then
    export CAP_STEM=NPFold_profile_test_$PICK_$PLOT   # stem of the .png screencaptures
    export CAP_BASE=$PWD
    export CAP_REL=NPFold_profile
    case $arg in  
       pvcap) source pvcap.sh cap  ;;  
       mpcap) source mpcap.sh cap  ;;  
       pvpub) source pvcap.sh env  ;;  
       mppub) source mpcap.sh env  ;;  
    esac
    if [ "$arg" == "pvpub" -o "$arg" == "mppub" ]; then 
        source epub.sh 
    fi  
fi 

exit 0 


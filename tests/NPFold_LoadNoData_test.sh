#!/bin/bash -l 
usage(){ cat << EOU
NPFold_LoadNoData_test.sh
==========================

::

   ~/np/tests/NPFold_LoadNoData_test.sh


EOU
}

SDIR=$(cd $(dirname $BASH_SOURCE) && pwd)
name=NPFold_LoadNoData_test 
TMP=${TMP:-/tmp/$USER/opticks}
bin=$TMP/$name


gcc $SDIR/$name.cc -std=c++11 -lstdc++ -I$SDIR/.. -o $bin 
[ $? -ne 0 ] && echo $BASH_SOURCE : build error && exit 1

cd /data/blyth/opticks/GEOM/J23_1_0_rc3_ok0/jok-tds/ALL0
[ $? -ne 0 ] && echo $BASH_SOURCE : no such directory && exit 2

$bin
[ $? -ne 0 ] && echo $BASH_SOURCE : run error && exit 3

exit 0 


#!/bin/bash -l 
usage(){ cat << EOU
NPX_BOA_test.sh
==========================

::

   ~/np/tests/NPX_BOA_test.sh


EOU
}

SDIR=$(cd $(dirname $BASH_SOURCE) && pwd)
name=NPX_BOA_test 
TMP=${TMP:-/tmp/$USER/opticks}
bin=$TMP/$name


gcc $SDIR/$name.cc -std=c++11 -lstdc++ -I$SDIR/.. -o $bin 
[ $? -ne 0 ] && echo $BASH_SOURCE : build error && exit 1

$bin
[ $? -ne 0 ] && echo $BASH_SOURCE : run error && exit 3

exit 0 


#!/bin/bash
usage(){ cat << EOU
NPX_BOA_test.sh
==========================

::

   ~/np/tests/NPX_BOA_test.sh


EOU
}

cd $(dirname $(realpath $BASH_SOURCE))

name=NPX_BOA_test 
TMP=${TMP:-/tmp/$USER/opticks}
bin=$TMP/$name


gcc $name.cc -std=c++17 -Wall -lstdc++ -I.. -o $bin 
[ $? -ne 0 ] && echo $BASH_SOURCE : build error && exit 1

$bin
[ $? -ne 0 ] && echo $BASH_SOURCE : run error && exit 3

exit 0 


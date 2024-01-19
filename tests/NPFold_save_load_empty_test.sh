#!/bin/bash -l 
usage(){ cat << EOU
NPFold_save_load_empty_test.sh
==========================

::

   ~/np/tests/NPFold_save_load_empty_test.sh


EOU
}

SDIR=$(cd $(dirname $BASH_SOURCE) && pwd)
name=NPFold_save_load_empty_test 
TMP=${TMP:-/tmp/$USER/opticks}
bin=$TMP/$name

export FOLD=$TMP/${name}_fold
mkdir -p $FOLD 
rm -rf $FOLD

vars="name SDIR FOLD"
for var in $vars ; do printf "%20s : %s \n" "$var" "${!var}" ; done

gcc $SDIR/$name.cc -std=c++11 -g -lstdc++ -I$SDIR/.. -o $bin 
[ $? -ne 0 ] && echo $BASH_SOURCE : build error && exit 1

dbg__ $bin
[ $? -ne 0 ] && echo $BASH_SOURCE : run error && exit 3

exit 0 


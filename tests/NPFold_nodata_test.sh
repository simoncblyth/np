#!/bin/bash -l 

name=NPFold_nodata_test

FOLD=${TMP:-/tmp/$USER/opticks}/$name
bin=$FOLD/$name
mkdir -p $FOLD

cd $(dirname $BASH_SOURCE)

#opt=-DWITH_VERBOSE
opt=

gcc $name.cc -I.. -g -std=c++11 -lstdc++ $opt -o $bin
[ $? -ne 0 ] && echo $BASH_SOURCE : build error && exit 1 

#cd /hpcfs/juno/junogpu/blyth/tmp/GEOM/J23_1_0_rc3_ok0/jok-tds/ALL0/p001
#cd /hpcfs/juno/junogpu/blyth/tmp/GEOM/J23_1_0_rc3_ok0/jok-tds/ALL0
cd /hpcfs/juno/junogpu/blyth/tmp/GEOM/J23_1_0_rc3_ok0/jok-tds/ALL0/n010

[ $? -ne 0 ] && echo $BASH_SOURCE : NO SUCH DIRECTORY && exit 0 

dbg__ $bin  $PWD
[ $? -ne 0 ] && echo $BASH_SOURCE : run0 error && exit 2

#dbg__ $bin @$PWD
#[ $? -ne 0 ] && echo $BASH_SOURCE : run1 error && exit 3

echo $PWD
echo $bin


exit 0 

